
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            main.c
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "type.h"
#include "const.h"
#include "protect.h"
#include "proto.h"
#include "string.h"
#include "proc.h"
#include "global.h"

#define A_PRI 3
#define B_PRI 5
#define C_PRI 15

#define A_KEEP 9
#define B_KEEP 15
#define C_KEEP 30

/*======================================================================*
                            kernel_main
 *======================================================================*/
PUBLIC int kernel_main()
{
	disp_str("-----\"kernel_main\" begins-----\n");

	TASK*		p_task		= task_table;
	PROCESS*	p_proc		= proc_table;
	char*		p_task_stack	= task_stack + STACK_SIZE_TOTAL;
	u16		selector_ldt	= SELECTOR_LDT_FIRST;
	int i;
	for (i = 0; i < NR_TASKS; i++) {
		strcpy(p_proc->p_name, p_task->name);	// name of the process
		p_proc->pid = i;			// pid

		p_proc->ldt_sel = selector_ldt;

		memcpy(&p_proc->ldts[0], &gdt[SELECTOR_KERNEL_CS >> 3],
		       sizeof(DESCRIPTOR));
		p_proc->ldts[0].attr1 = DA_C | PRIVILEGE_TASK << 5;
		memcpy(&p_proc->ldts[1], &gdt[SELECTOR_KERNEL_DS >> 3],
		       sizeof(DESCRIPTOR));
		p_proc->ldts[1].attr1 = DA_DRW | PRIVILEGE_TASK << 5;
		p_proc->regs.cs	= ((8 * 0) & SA_RPL_MASK & SA_TI_MASK)
			| SA_TIL | RPL_TASK;
		p_proc->regs.ds	= ((8 * 1) & SA_RPL_MASK & SA_TI_MASK)
			| SA_TIL | RPL_TASK;
		p_proc->regs.es	= ((8 * 1) & SA_RPL_MASK & SA_TI_MASK)
			| SA_TIL | RPL_TASK;
		p_proc->regs.fs	= ((8 * 1) & SA_RPL_MASK & SA_TI_MASK)
			| SA_TIL | RPL_TASK;
		p_proc->regs.ss	= ((8 * 1) & SA_RPL_MASK & SA_TI_MASK)
			| SA_TIL | RPL_TASK;
		p_proc->regs.gs	= (SELECTOR_KERNEL_GS & SA_RPL_MASK)
			| RPL_TASK;

		p_proc->regs.eip = (u32)p_task->initial_eip;
		p_proc->regs.esp = (u32)p_task_stack;
		p_proc->regs.eflags = 0x1202; /* IF=1, IOPL=1 */
               
		p_task_stack -= p_task->stacksize;
		p_proc++;
		p_task++;
		selector_ldt += 1 << 3;
	}

	/*proc_table[0].ticks = proc_table[0].priority = 3;
	proc_table[1].ticks = proc_table[1].priority =  5;
	proc_table[2].ticks = proc_table[2].priority =  15;
	//改动
	proc_table[0].keep = 90;
	proc_table[1].keep = 50;
	proc_table[2].keep = 30;
	
	proc_table[0].active = 1;
	proc_table[1].active = 1;
	proc_table[2].active = 1;*/
	
	for(i=0;i<NR_TASKS-2;i++)
	{
	    if(i%3==0)
	    {
	        proc_table[i].ticks=proc_table[i].priority = A_PRI;
	        proc_table[i].keep = A_KEEP;
	    }
	    else if(i%3==1)
	    {
	        proc_table[i].ticks=proc_table[i].priority = B_PRI;
	        proc_table[i].keep = B_KEEP;
	    }
	    else
	    {
	        proc_table[i].ticks=proc_table[i].priority = C_PRI;
	        proc_table[i].keep = C_KEEP;
	    }
	    if(i<3)
	        proc_table[i].active = PRO_ACTIVE;
	    else
	        proc_table[i].active = PRO_STOP;
	}
        
        proc_table[NR_TASKS-1].ticks=proc_table[NR_TASKS-1].priority = 99;
	proc_table[NR_TASKS-1].keep = 99;
	proc_table[NR_TASKS-1].active = PRO_STOP;
	
	proc_table[NR_TASKS-2].ticks=proc_table[NR_TASKS-2].priority = 99;
	proc_table[NR_TASKS-2].keep = 99;
	proc_table[NR_TASKS-2].active = PRO_STOP;
	keep=proc_table[2].keep;

	k_reenter = 0;
	ticks = 0;
	sign=0;sign1=0;
	active_process=3;

	p_proc_ready	= proc_table;
	p_proc_ready++;
	p_proc_ready++;
	

        /* 初始化 8253 PIT */
        out_byte(TIMER_MODE, RATE_GENERATOR);
        out_byte(TIMER0, (u8) (TIMER_FREQ/HZ) );
        out_byte(TIMER0, (u8) ((TIMER_FREQ/HZ) >> 8));

        put_irq_handler(CLOCK_IRQ, clock_handler); /* 设定时钟中断处理程序 */
        enable_irq(CLOCK_IRQ);                     /* 让8259A可以接收时钟中断 */

	restart();

	while(1){}
}


/*======================================================================*
                               PROCESS_C
 *======================================================================*/

void Process_c()
{
    int i;
    while(1)
    {
        if(sign==1)
            continue;
        for(i=NR_TASKS-3;i>=0;i--)
        {
            if(proc_table[i].active==PRO_STOP&&proc_table[i].keep>0)
            {
                active_process+=1;
                proc_table[i].active=PRO_ACTIVE;
                disp_str(": ");
                disp_str(proc_table[i].p_name);
                disp_str(".");
                sign=1;
                break;
            }
        }
    }
}

/*======================================================================*
                               PROCESS_K
 *======================================================================*/

void Process_k()
{
    int i;
    while(1)
    {
        if(sign1==1)
            continue;
        for(i=0;i<NR_TASKS-2;i++)
        {
            if(proc_table[i].active==PRO_ACTIVE&&active_process>1)
            {
                active_process-=1;
                proc_table[i].active=PRO_STOP;
                disp_str(": ");
                disp_str(proc_table[i].p_name);
                disp_str(".");
                sign1=1;
                break;
            }
        }
    }
}

/*======================================================================*
                               TestA
 *======================================================================*/
void TestA()
{
	int i = 0;
	while (1) {
		disp_str("A.");
		/*disp_int(get_keep());*/
		
		milli_delay(20);
		
	}
}

/*======================================================================*
                               TestB
 *======================================================================*/
void TestB()
{
	int i = 0x1000;
	while(1){
		disp_str("B.");
		/*disp_int(get_keep());*/
		
		milli_delay(20);
		
	}
}

/*======================================================================*
                               TestC
 *======================================================================*/
void TestC()
{
	int i = 0x2000;
	while(1){
		disp_str("C.");
		/*disp_int(get_keep());*/
		
		milli_delay(20);
		
	}
}

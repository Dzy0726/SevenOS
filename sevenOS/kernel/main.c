
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            main.c
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "type.h"
#include "stdio.h"
#include "const.h"
#include "protect.h"
#include "string.h"
#include "fs.h"
#include "proc.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "proto.h"

/*======================================================================*
                            kernel_main
 *======================================================================*/
PUBLIC int kernel_main()
{
    disp_str("-----\"kernel_main\" begins-----\n");

    struct task* p_task;
    struct proc* p_proc = proc_table;
    char* p_task_stack = task_stack + STACK_SIZE_TOTAL;
    u16   selector_ldt = SELECTOR_LDT_FIRST;
    u8    privilege;
    u8    rpl;
    int   eflags;
    int   i, j;
    int   prio;
    for (i = 0; i < NR_TASKS + NR_PROCS; i++) {
        if (i < NR_TASKS) {     /* 任务 */
            p_task = task_table + i;
            privilege = PRIVILEGE_TASK;
            rpl = RPL_TASK;
            eflags = 0x1202; /* IF=1, IOPL=1, bit 2 is always 1 */
            prio = 15;
        }
        else {                  /* 用户进程 */
            p_task = user_proc_table + (i - NR_TASKS);
            privilege = PRIVILEGE_USER;
            rpl = RPL_USER;
            eflags = 0x202; /* IF=1, bit 2 is always 1 */
            prio = 5;
        }

        strcpy(p_proc->name, p_task->name); /* name of the process */
        p_proc->pid = i;            /* pid */

        p_proc->ldt_sel = selector_ldt;

        memcpy(&p_proc->ldts[0], &gdt[SELECTOR_KERNEL_CS >> 3],
            sizeof(struct descriptor));
        p_proc->ldts[0].attr1 = DA_C | privilege << 5;
        memcpy(&p_proc->ldts[1], &gdt[SELECTOR_KERNEL_DS >> 3],
            sizeof(struct descriptor));
        p_proc->ldts[1].attr1 = DA_DRW | privilege << 5;
        p_proc->regs.cs = (0 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
        p_proc->regs.ds = (8 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
        p_proc->regs.es = (8 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
        p_proc->regs.fs = (8 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
        p_proc->regs.ss = (8 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
        p_proc->regs.gs = (SELECTOR_KERNEL_GS & SA_RPL_MASK) | rpl;

        p_proc->regs.eip = (u32)p_task->initial_eip;
        p_proc->regs.esp = (u32)p_task_stack;
        p_proc->regs.eflags = eflags;

        /* p_proc->nr_tty       = 0; */

        p_proc->p_flags = 0;
        p_proc->p_msg = 0;
        p_proc->p_recvfrom = NO_TASK;
        p_proc->p_sendto = NO_TASK;
        p_proc->has_int_msg = 0;
        p_proc->q_sending = 0;
        p_proc->next_sending = 0;

        for (j = 0; j < NR_FILES; j++)
            p_proc->filp[j] = 0;

        p_proc->ticks = p_proc->priority = prio;

        p_task_stack -= p_task->stacksize;
        p_proc++;
        p_task++;
        selector_ldt += 1 << 3;
    }

    k_reenter = 0;
    ticks = 0;

    p_proc_ready = proc_table;

    init_clock();
    init_keyboard();

    restart();

    while (1) {}
}

/*****************************************************************************
 *                                get_ticks
 *****************************************************************************/
PUBLIC int get_ticks()
{
    MESSAGE msg;
    reset_msg(&msg);
    msg.type = GET_TICKS;
    send_recv(BOTH, TASK_SYS, &msg);
    return msg.RETVAL;
}



#define NULL ((void*)0)

/*======================================================================*
                               TestA
 *======================================================================*/
void TestA()
{
    int fd;
    int i, n;

    char tty_name[] = "/dev_tty0";

    char readbuf[128];
    char command3[100], command4[100], command5[100];

    int fd_stdin = open(tty_name, O_RDWR);
    assert(fd_stdin == 0);
    int fd_stdout = open(tty_name, O_RDWR);
    assert(fd_stdout == 1);

    const char bufw[80] = { 0 };

    clear();

    /*================================= 开机动画 ===============================*/
    bootAnimation();

    clear();
    /*=============================显示在上面的系统信息 ===============================*/

    commandList();

    while (1) 
    {
        printf("root@sevenOS: $ ");

        memset(command3, 0, sizeof(command3));
        memset(command4, 0, sizeof(command4));
        memset(command5, 0, sizeof(command5));

        int r = read(fd_stdin, readbuf, 70);
        readbuf[r] = 0;
        mystrncpy(command3, readbuf, 3);
        mystrncpy(command4, readbuf, 4);
        mystrncpy(command5, readbuf, 5);

        if (!strcmp(command4, "help"))
        {
            clear();
            commandList();
        }
        else if (!strcmp(command5, "clear"))
        {
            clear();
        }
        else if (!strcmp(command4, "more"))
        {
            if (strlen(readbuf) > 5) 
            {
                moreMain(readbuf + 5);
            }
            else 
            {
                char* str = "NULL";
                moreMain(str);
            }

            continue;
        }
        else if (!strcmp(command4, "game"))
        {
            if (strlen(readbuf) > 5) {
                gameMain(readbuf + 5, fd_stdin, fd_stdout);
            }
            else {
                char* str = "NULL";
                gameMain(str, fd_stdin, fd_stdout);
            }
            continue;
        }
        else if (!strcmp(command3, "cal"))
        {
        	rili(fd_stdin,fd_stdout);
        	continue;
        }
        else if (!strcmp(command4, "math"))
        {
            if (strlen(readbuf) > 5) 
            {
                mathMain(readbuf + 5);
            }
            else 
            {
                char* str = "NULL";
                mathMain(str);
            }

            continue;
        }
        else if (!strcmp(readbuf, "file")) 
        {
            clear();
            FSManage(fd_stdin);
        }
        else if (!strcmp(readbuf, ""))
        {
            continue;
        }
        else
        {
            clear();
            notFound();//命令不存在
        }

    }
}


/*======================================================================*
                               TestB
 *======================================================================*/
void TestB()
{
    spin("TestB");
}
/*======================================================================*
                               TestC
 *======================================================================*/
void TestC()
{
    spin("TestC");
}


/*****************************************************************************
 *                                panic
 *****************************************************************************/
PUBLIC void panic(const char *fmt, ...)
{
    int i;
    char buf[256];

    /* 4 is the size of fmt in the stack */
    va_list arg = (va_list)((char*)&fmt + 4);

    i = vsprintf(buf, fmt, arg);

    printl("%c !!panic!! %s", MAG_CH_PANIC, buf);

    /* should never arrive here */
    __asm__ __volatile__("ud2");
}

void clear()
{
    clear_screen(0,console_table[current_console].cursor);
    console_table[current_console].crtc_start = 0;
    console_table[current_console].cursor = 0;

}

void mystrncpy(char* dest, char* src, int len)
{
    assert(dest != NULL && src != NULL);

    char* temp = dest;
    int i = 0;
    while (i++ < len && (*temp++ = *src++) != '\0');

    if (*(temp) != '\0') 
    {
        *temp = '\0';
    }
}









/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                               clock.c
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


/*======================================================================*
                           clock_handler
 *======================================================================*/
PUBLIC void clock_handler(int irq)
{
	ticks++;
	
	if(p_proc_ready->active==PRO_STOP)
	{
	    /*p_proc_ready=last_proc_ready;
	    disp_str(p_proc_ready->p_name);disp_str(": ");*/
	    schedule();
	    disp_str(p_proc_ready->p_name);disp_str(": ");
	    return;
	}
	else
	{
	    p_proc_ready->ticks--;
	    p_proc_ready->keep--;
	
	if(p_proc_ready->ticks==0)
	     p_proc_ready->active=PRO_WAIT;
	
	if(p_proc_ready->keep==0)
	{
	    p_proc_ready->active=PRO_STOP;
	    disp_str(p_proc_ready->p_name);
	    disp_str(" END .");
	}
	else
	    keep=p_proc_ready->keep;
	}
	//¸Ä¶¯
	
	if(ticks%25==0)
	{
	    p_proc_ready=proc_table+NR_TASKS-2;
	    disp_str(p_proc_ready->p_name);disp_str(": ");
	    sign=0;
	}
	
	else if(ticks%43==0)
	{
	    p_proc_ready=proc_table+NR_TASKS-1;
	    disp_str(p_proc_ready->p_name);disp_str(": ");
	    sign1=0;
	}
	
	if (k_reenter != 0) {
		return;
	}

	if (p_proc_ready->ticks > 0) {
		return;
	}

	schedule();
	disp_str(p_proc_ready->p_name);disp_str(": ");
}

/*======================================================================*
                              milli_delay
 *======================================================================*/
PUBLIC void milli_delay(int milli_sec)
{
        int t = get_ticks();

        while(((get_ticks() - t) * 1000 / HZ) < milli_sec) {}
}


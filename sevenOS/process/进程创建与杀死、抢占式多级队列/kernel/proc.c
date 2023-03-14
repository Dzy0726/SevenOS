
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                               proc.c
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
                              schedule
 *======================================================================*/
PUBLIC void schedule()
{
	//¸Ä¶¯
	PROCESS* p;
	int    greatest_ticks = 0;
	int	 greatest_keep = 0;
	
	while (!greatest_keep) {
		for (p = proc_table; p < proc_table + NR_TASKS; p++) {
		
		if(p->active!=PRO_STOP){
			if (p->keep > greatest_keep) {
				greatest_keep = p->keep;
			}
			}
		}
	}
	while (!greatest_ticks) {
		for (p = proc_table; p < proc_table + NR_TASKS; p++) {
		        /*disp_str("sdsa");*/
			if(p->active==PRO_ACTIVE){
			if (p->ticks > greatest_ticks) {
				greatest_ticks = p->ticks;
				p_proc_ready = p;
				keep=p_proc_ready->keep;
			}
			}
		}
                
		if (!greatest_ticks) {
			for (p = proc_table; p < proc_table + NR_TASKS; p++) {
			       if(p->keep>0&&p->active!=PRO_STOP){
				p->ticks = p->priority;
				p->active=PRO_ACTIVE;}
			}
		}
	}
	
}

/*======================================================================*
                           sys_get_ticks
 *======================================================================*/
PUBLIC int sys_get_ticks()
{
	return ticks;
}

/*======================================================================*
                           sys_get_keep
 *======================================================================*/
 PUBLIC int sys_get_keep()
 {
       return keep;
}


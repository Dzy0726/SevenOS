
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
	
	PROCESS* p;
	int    greatest_ticks = 0;
	int	 greatest_keep = 0;
	while (!greatest_keep) {
		for (p = proc_table; p < proc_table + NR_TASKS; p++) {
		if(p->active==1){
			if (p->keep > greatest_keep) {
				greatest_keep = p->keep;
			}
			}
		}
	}
	while (!greatest_ticks) {
		for (p = proc_table; p < proc_table + NR_TASKS; p++) {
			if(p->active){
			if (p->ticks > greatest_ticks) {
				greatest_ticks = p->ticks;
				p_proc_ready = p;
				keep=p_proc_ready->keep;
			}
			}
		}
                
		if (!greatest_ticks) {
			for (p = proc_table; p < proc_table + NR_TASKS; p++) {
			       if(p->keep>0){
				p->ticks = p->priority;
				p->active=1;}
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


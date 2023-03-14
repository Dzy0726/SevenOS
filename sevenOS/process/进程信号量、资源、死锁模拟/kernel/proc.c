
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
	int	 greatest_ticks = 0;

	while (!greatest_ticks) {
		for (p = proc_table; p < proc_table+NR_TASKS; p++) {
			if (p->ticks > greatest_ticks) {
				greatest_ticks = p->ticks;
				p_proc_ready = p;
			}
		}

		if (!greatest_ticks) {
			for (p = proc_table; p < proc_table+NR_TASKS; p++) {
				p->ticks = p->priority;
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
                           sys_apply_resrc
 *======================================================================*/
PUBLIC int sys_apply_resrc(int resrc,PROCESS* p_proc)
{
        if(resrc_process_table[p_proc->num][resrc]==0)
        {
            resrc_table[resrc].signal-=1;
            resrc_process_table[p_proc->num][resrc]=1;
            if(resrc_table[resrc].signal<0)
                p_proc->need_num+=1;
            else
            {
                p_proc->get_num+=1;
                p_proc->get[p_proc->get_num-1]=resrc;
            }
        }
        
        return dead_lock(p_proc);
}

/*======================================================================*
                           sys_print_resrc
 *======================================================================*/
PUBLIC void sys_print_resrc(PROCESS* p_proc)
{
        disp_str("TASK ");
        /*disp_str(p_proc->p_name);*/
       
        disp_str("need resource: ");
        
        int i,j;
        for(i=0;i<NR_TASKS;i++)
            for(j=0;j<NR_RESOURCE;j++)
                {
                     int g=resrc_process_table[i][j];
                     if(g==1)
                     {
                         disp_str(resrc_table[j].name);
                         disp_str(".\n");
                      }
                }
        
}

/*======================================================================*
                           sys_release_resrc
 *======================================================================*/
 PUBLIC void sys_release_resrc(int resrc,PROCESS* p_proc)
 {
       if(resrc_process_table[p_proc->num][resrc]==1)
       {
           resrc_process_table[p_proc->num][resrc]=0;
           p_proc->get_num-=1;
           resrc_table[resrc].signal+=1;
       }
 }
 
 /*======================================================================*
                           dead_lock
 *======================================================================*/
 PUBLIC int dead_lock(PROCESS* p_proc)
 {
     int p=1;
     int i;
     for(i=0;i<NR_RESOURCE;i++)
         if(resrc_table[i].signal>0)
         {
             p=0;
         }
     return p;
 }
 
 
 

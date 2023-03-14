
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

	/***每个进程都有一个ticks数，每个tick代表一次时钟中断的时间，也就是说每个进程都有ticks个时间片的执行时间，根据ticks越大优先级越低，
	这里就是选ticks最大的进程执行。schedule()会选择一个将要执行的进程赋值到p_proc_ready，在时钟中断返回时就会跳入到p_proc_ready所指向的进程执行。
	当greatest_ticks变为0时代表所有进程都已经用完自己的时间片，此时会给所有进程重新赋予时间片，进而重新执行。***/
	
	while (!greatest_ticks) {
		for (p = proc_table; p < proc_table+NR_TASKS; p++) {
			if (p->ticks > greatest_ticks) {
				greatest_ticks = p->ticks;
				p_proc_ready = p;
			}
		}
/*
		if (!greatest_ticks) {
			for (p = proc_table; p < proc_table+NR_TASKS; p++) {
				p->ticks = p->enter_ticks;
			}
		}
*/
	}
}

/*======================================================================*
                           sys_get_ticks
 *======================================================================*/
PUBLIC int sys_get_ticks()
{
	return ticks;
}


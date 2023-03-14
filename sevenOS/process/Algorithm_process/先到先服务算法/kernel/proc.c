
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

	/***ÿ�����̶���һ��ticks����ÿ��tick����һ��ʱ���жϵ�ʱ�䣬Ҳ����˵ÿ�����̶���ticks��ʱ��Ƭ��ִ��ʱ�䣬����ticksԽ�����ȼ�Խ�ͣ�
	�������ѡticks���Ľ���ִ�С�schedule()��ѡ��һ����Ҫִ�еĽ��̸�ֵ��p_proc_ready����ʱ���жϷ���ʱ�ͻ����뵽p_proc_ready��ָ��Ľ���ִ�С�
	��greatest_ticks��Ϊ0ʱ�������н��̶��Ѿ������Լ���ʱ��Ƭ����ʱ������н������¸���ʱ��Ƭ����������ִ�С�***/
	
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


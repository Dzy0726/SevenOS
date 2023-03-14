
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            global.c
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#define GLOBAL_VARIABLES_HERE

#include "type.h"
#include "const.h"
#include "protect.h"
#include "proto.h"
#include "proc.h"
#include "global.h"


PUBLIC	PROCESS			proc_table[NR_TASKS];

PUBLIC	char			task_stack[STACK_SIZE_TOTAL];

PUBLIC	TASK	task_table[NR_TASKS] = {{TestA, STACK_SIZE_TESTA, "TestA"},
					{TestB, STACK_SIZE_TESTB, "TestB"},
					{TestC, STACK_SIZE_TESTC, "TestC"},
					{TestA, STACK_SIZE_TESTA, "TestA1"},
					{TestB, STACK_SIZE_TESTB, "TestB1"},
					{TestC, STACK_SIZE_TESTC, "TestC1"},
					{TestA, STACK_SIZE_TESTA, "TestA2"},
					{TestB, STACK_SIZE_TESTB, "TestB2"},
					{TestC, STACK_SIZE_TESTC, "TestC2"},
					{Process_c, STACK_SIZE_TESTA, "Create"},
					{Process_k, STACK_SIZE_TESTA, "Remove"}};

PUBLIC	irq_handler		irq_table[NR_IRQ];

PUBLIC	system_call		sys_call_table[NR_SYS_CALL] = {sys_get_ticks,sys_get_keep};


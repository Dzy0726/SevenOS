
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                               proc.h
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


typedef struct s_stackframe {	/* proc_ptr points here				↑ Low			*/
	u32	gs;		/* ┓						│			*/
	u32	fs;		/* ┃						│			*/
	u32	es;		/* ┃						│			*/
	u32	ds;		/* ┃						│			*/
	u32	edi;		/* ┃						│			*/
	u32	esi;		/* ┣ pushed by save()				│			*/
	u32	ebp;		/* ┃						│			*/
	u32	kernel_esp;	/* <- 'popad' will ignore it			│			*/
	u32	ebx;		/* ┃						↑栈从高地址往低地址增长*/		
	u32	edx;		/* ┃						│			*/
	u32	ecx;		/* ┃						│			*/
	u32	eax;		/* ┛						│			*/
	u32	retaddr;	/* return address for assembly code save()	│			*/
	u32	eip;		/*  ┓						│			*/
	u32	cs;		/*  ┃						│			*/
	u32	eflags;		/*  ┣ these are pushed by CPU during interrupt	│			*/
	u32	esp;		/*  ┃						│			*/
	u32	ss;		/*  ┛						┷High			*/
}STACK_FRAME;


typedef struct s_proc {
	STACK_FRAME regs;          /* process registers saved in stack frame */

	u16 ldt_sel;               /* gdt selector giving ldt base and limit */
	DESCRIPTOR ldts[LDT_SIZE]; /* local descriptors for code and data */

        int num;
        int ticks;                 /* remained ticks */
        int priority;

        int get_num;
        int get[5];
        int need[5];
        int need_num;

	u32 pid;                   /* process id passed in from MM */
	char p_name[16];           /* name of the process */
}PROCESS;

typedef struct s_task {
	task_f	initial_eip;
	int	stacksize;
	char	name[32];
}TASK;

/*system resource*/
typedef struct resrc{
       char    name[32];
       int     num;
       int     signal;
}RESRC;
/* Number of tasks */
#define NR_TASKS	3

/* resource*/
#define NR_RESOURCE    3

/* stacks of tasks */
#define STACK_SIZE_TESTA	0x9000
#define STACK_SIZE_TESTB	0x9000
#define STACK_SIZE_TESTC	0x9000

#define STACK_SIZE_TOTAL	(STACK_SIZE_TESTA + \
				STACK_SIZE_TESTB + \
				STACK_SIZE_TESTC)
				
PUBLIC  int    sys_apply_resrc(int resrc, PROCESS* p_proc);
PUBLIC  void    sys_print_resrc(PROCESS* p_proc);
PUBLIC  void    sys_release_resrc(int resrc, PROCESS* p_proc);
PUBLIC  int     sys_get_ticks(); 


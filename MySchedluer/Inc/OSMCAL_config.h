/*************************************************/
/* AUTHOR           : Youssef Hamed              */
/* Date             : 14 MAR 2024                 */
/* Version          : v01                        */ 
/*************************************************/



#ifndef OSMCAL_CONFIG_H_
#define OSMCAL_CONFIG_H_


#define HSI_CLK    				 8000000UL
#define SYSTICK_TIM_CLK 	     HSI_CLK

#define MAX_TASK_NUM  		5u   /* (4 Task + 1 Ideal Task */



#define T1_STACK_START							(SRAM_END)
#define T2_STACK_START							((SRAM_END) - (1*(SIZE_TASK_STACK)))
#define T3_STACK_START							((SRAM_END) - (2*(SIZE_TASK_STACK)))
#define T4_STACK_START							((SRAM_END) - (3*(SIZE_TASK_STACK)))
#define IDEL_TASK_STACK_START					((SRAM_END) - (4*(SIZE_TASK_STACK)))
#define SCHED_STACK_START						((SRAM_END) - (5*(SIZE_TASK_STACK)))




#endif

/*************************************************/
/* AUTHOR           : Youssef Hamed              */
/* Date             : 14 SEP 2024                 */
/* Version          : v01                        */ 
/*************************************************/
#include "STD_type.h"
#include "BIT_math.h"

#include "main.h"
#include "NVIC_private.h"

#include "OSMCAL_interface.h"
#include "OSMCAL_private.h"
#include "OSMCAL_config.h"


typedef enum
{
	ReadyState ,
	BlockedState
} TaskState_t;



typedef struct
{
	u32 PSPValue ;
	u32 BlockCount ;
	TaskState_t CurrentState ;
	void (*TaskHandler)(void) ;

}TCB_t;



u32 CurrentTask = 1u ;     /* ignor ideal task */

TCB_t UserTasks[MAX_TASK_NUM] ;

u32 GlobalTickCount = 0 ;





__attribute__((naked)) void Stack_voidSchedulerStackInit(u32 Copy_u32SchedTOS)
{
	__asm volatile ("MSR MSP , R0") ;

	__asm volatile("BX LR") ;
}



void MSTK_voidInit(u32 Copy_u8TickHz)
{

	u32 Local_u32ReloadVal = SYSTICK_TIM_CLK / Copy_u8TickHz ;

	Local_u32ReloadVal-- ;

	MSTK->LOAD = Local_u32ReloadVal ;

	/* ُenable systick exception */
	MSTK->CTRL  |=1<<1 ;
	/* enable systick clock source */
	MSTK->CTRL  |=1<<2 ;
	/* enable systick Timer */
	MSTK->CTRL  |=1<<0 ;

}

__attribute ((naked))void PendSV_Handler(void)
{
	/*A -  save context  current task */
	/*1- Get  current running Task PSP value */
	__asm volatile ("MRS R0 , PSP ") ;
	/* 2- using PSP value , Store SF2 (R4 -> R11 ) */
	__asm volatile ("STMDB R0! , {R4-R11}") ;

	__asm volatile ("PUSH {LR}  ") ;
	/* 3- Save Current Value of PSP */
	__asm volatile ("BL SaveCurrentPSPValue  ") ;
	/*B-  retrieve context of next task*/

	/*1 - Decide Next Task To Run */
	__asm volatile ("Bl UpdateNextTask") ;
	/* 2 Get PSP value */
	__asm volatile ("BL GetCurrentPSPValue") ;

	__asm volatile ("POP {LR}  ") ;

	/* 3- retrieve SF2 */
	__asm volatile ("LDMIA R0! , {R4-R11}") ;
	/* 4-UPDATE PSP VALUE */
	__asm volatile ("MSR PSP , R0 ") ;
	/*5-EXIT*/
	__asm volatile ("BX LR") ;


}

static void UnBlockTask(void)
{
	u8 Local_u8TaskCounter ;

	for (Local_u8TaskCounter = 1 ; Local_u8TaskCounter< MAX_TASK_NUM ; Local_u8TaskCounter++ )
	{
		if(UserTasks[Local_u8TaskCounter].CurrentState == BlockedState)
		{
			if (UserTasks[Local_u8TaskCounter].BlockCount ==GlobalTickCount)
			{

				UserTasks[Local_u8TaskCounter].CurrentState = ReadyState ;

			}
		}
	}
}


void SysTick_Handler(void)
{
	/* Udate Global TickCount */
	GlobalTickCount++ ;

	/* un Block Task */
	UnBlockTask() ;

	/* Pend PendSV  */
	SCB->ICSR |= (1 <<28) ;



}



void InitTasksStack(void)
{

	u32* Local_pu32TaskPSP ;
	u8 Local_u8LoopIndex ;
	u8 Local_u8LoopIndexGPRS ;
	/*init task psp*/
	UserTasks[0].PSPValue = IDEL_TASK_STACK_START ;
	UserTasks[1].PSPValue = T1_STACK_START ;
	UserTasks[2].PSPValue = T2_STACK_START ;
	UserTasks[3].PSPValue = T3_STACK_START ;
	UserTasks[4].PSPValue = T4_STACK_START ;


	/*init task handler */
	UserTasks[0].TaskHandler = &IdealTaskHandler ;
	UserTasks[1].TaskHandler = &Task1_Handler ;
	UserTasks[2].TaskHandler = &Task2_Handler ;
	UserTasks[3].TaskHandler = &Task3_Handler ;
	UserTasks[4].TaskHandler = &Task4_Handler ;



	for (Local_u8LoopIndex = 0 ; Local_u8LoopIndex < MAX_TASK_NUM ; Local_u8LoopIndex++)
	{
		/*init task is ready */
		UserTasks[Local_u8LoopIndex].CurrentState = ReadyState ;

		Local_pu32TaskPSP = (u32*) UserTasks[Local_u8LoopIndex].PSPValue ;

		Local_pu32TaskPSP-- ;
		*Local_pu32TaskPSP = DUMMY_XPSR ;

		Local_pu32TaskPSP-- ;
		*Local_pu32TaskPSP = (u32)UserTasks[Local_u8LoopIndex].TaskHandler ;

		Local_pu32TaskPSP-- ;
		*Local_pu32TaskPSP = DUMMY_LR ;

		for(Local_u8LoopIndexGPRS =0 ; Local_u8LoopIndexGPRS < 13 ; Local_u8LoopIndexGPRS++ )
		{
			Local_pu32TaskPSP-- ;
			*Local_pu32TaskPSP = 0 ;
		}

		UserTasks[Local_u8LoopIndex].PSPValue = (u32)Local_pu32TaskPSP ;

	}
}

u32 GetCurrentPSPValue(void)
{
	return UserTasks[CurrentTask].PSPValue ;

}

void SaveCurrentPSPValue(u32 Copy_u32CurrentPSPValue)
{
	UserTasks[CurrentTask].PSPValue = Copy_u32CurrentPSPValue ;

}

__attribute__((naked)) void ChangePSP(void)
{


	/* 1 init PSP WITH TASK1 STACK */
	__asm volatile ("PUSH {LR}  ") ;

	__asm volatile ("BL GetCurrentPSPValue") ;

	__asm volatile ("MSR PSP , R0") ;

	__asm volatile ("POP {LR}  ") ;

	/*change SP To PSP Using Control Register */
	__asm volatile ("MOV R0 , #0x02") ;

	__asm volatile ("MSR CONTROL , R0") ;

	/*EXIT*/
	__asm volatile("BX LR") ;
}

void EnableSystemFaults(void)
{

	SCB ->SHCSR |= (1<<16) ;       /* Mem Mange Fault enable */

	SCB ->SHCSR |= (1<<17) ;       /* Bus  Fault enable */

	SCB ->SHCSR |= (1<<18) ;       /* Usage  Fault enable */

}

void UpdateNextTask(void)
{
	u8 Local_u8loopCount ;
	for(Local_u8loopCount = 0 ; Local_u8loopCount < MAX_TASK_NUM ; Local_u8loopCount++)
	{
		CurrentTask++ ;
		CurrentTask%= MAX_TASK_NUM ;

		if ((UserTasks[CurrentTask].CurrentState == ReadyState) &&( Local_u8loopCount !=0) )
		{
			break ;
		}

	}
	if( (UserTasks[CurrentTask].CurrentState != ReadyState) )   /* All Task is block Run ideal task */
	{
		CurrentTask = 0 ;
	}
}



void TaskDelay(u32 Copy_u32BlockTick)
{
		/*disable Gloable interrupt */
		ENTER_CRITICAL_SECTION() ;

	if (CurrentTask != 0U )   /* zero for ideal task cant be blocked  */
	{
		UserTasks[CurrentTask].BlockCount =  Copy_u32BlockTick + GlobalTickCount ;

		UserTasks[CurrentTask].CurrentState = BlockedState ;

		EXIT_CRITICAL_SECTION() ;
		/* Call the scheduler by pendsv */
		SCB->ICSR |= (1 <<28) ;

	}

}

static void IdealTaskHandler (void)
{

	while(1) ;

}

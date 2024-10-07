/*************************************************/
/* AUTHOR           : Youssef Hamed              */
/* Date             : 14 MAR 2024                 */
/* Version          : v01                        */ 
/*************************************************/



#ifndef OSMCAL_INTERFACE_H_
#define OSMCAL_INTERFACE_H_




void MSTK_voidInit(u32 Copy_u8TickHz) ;

void SysTick_Handler(void) ;

__attribute ((naked))void PendSV_Handler(void)  ;


__attribute__((naked)) void Stack_voidSchedulerStackInit(u32 Copy_u32SchedTOS) ;

void InitTasksStack(void) ;

__attribute__((naked)) void ChangePSP(void) ;

u32 GetCurrentPSPValue(void) ;

void EnableSystemFaults(void);

void SaveCurrentPSPValue(u32 Copy_u32CurrentPSPValue) ;

void UpdateNextTask(void) ;

void TaskDelay(u32 Copy_u32BlockTick) ;


#endif

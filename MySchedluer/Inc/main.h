#ifndef MAIN_H_
#define MAIN_H_

#include "OSMCAL_config.h"

#define SIZE_TASK_STACK		1024U
#define SIZE_SCHED_STACK    1024U


#define SRAM_START			 0x20000000U
#define SRAM_SIZE 			(20*1024)
#define SRAM_END   			((SRAM_START)+(SRAM_SIZE))


#define DELAY_COUNT_1ms  	 (1250U)
#define DELAY_COUNT_1s   	 (1000U * (DELAY_COUNT_1ms))
#define DELAY_COUNT_500ms    (500U * (DELAY_COUNT_1ms))
#define DELAY_COUNT_250ms    (250U * (DELAY_COUNT_1ms))
#define DELAY_COUNT_125ms    (125U * (DELAY_COUNT_1ms))


void Task1_Handler(void) ;
void Task2_Handler(void) ;
void Task3_Handler(void) ;
void Task4_Handler(void) ;


#endif /* MAIN_H_ */

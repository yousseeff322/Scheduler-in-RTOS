#include "STD_type.h"
#include "BIT_math.h"
#include "main.h"
#include "OSMCAL_interface.h"
#include "RCC_interface.h"
#include "DIO_interface.h"




void Delay (u32 Copy_u32Count)
{
	u32 count ;
	for (count = 0 ; count <Copy_u32Count ; count++ ) ;
}


int main(void)
{

	MRCC_VidInit() ;
	MRCC_VidEnablePeripheralClock(RCC_APB2, GPIOA_RCC) ;

	MGPIO_VidSetPinDirection(GPIOA, PIN1, OUT_SPEED_10MHZ_PP) ;
	MGPIO_VidSetPinDirection(GPIOA, PIN2, OUT_SPEED_10MHZ_PP) ;
	MGPIO_VidSetPinDirection(GPIOA, PIN3, OUT_SPEED_10MHZ_PP) ;
	MGPIO_VidSetPinDirection(GPIOA, PIN4, OUT_SPEED_10MHZ_PP) ;

	EnableSystemFaults();

	MSTK_voidInit(1000);

	Stack_voidSchedulerStackInit(SCHED_STACK_START) ;

	InitTasksStack() ;

	ChangePSP() ;

	Task1_Handler();
	/* Loop forever */
	for(;;);
}


void Task1_Handler(void) {


	while(1) {

		MGPIO_VidTogglePin(GPIOA, PIN1) ;
		TaskDelay(1000) ;
	}
}
void Task2_Handler(void)
{

	while(1) {
		MGPIO_VidTogglePin(GPIOA, PIN2) ;
			TaskDelay(500) ;

	}

}
void Task3_Handler(void)
{

	while(1) {
		MGPIO_VidTogglePin(GPIOA, PIN3) ;
			TaskDelay(250) ;


	}

}
void Task4_Handler(void)
{


	while(1) {
		MGPIO_VidTogglePin(GPIOA, PIN4) ;
			TaskDelay(125) ;


	}

}

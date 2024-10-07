/*************************************************/
/* AUTHOR           : Youssef Hamed              */
/* Date             : 14 MAR 2024                 */
/* Version          : v01                        */ 
/*************************************************/



#ifndef OSMCAL_PRIVATE_H_
#define OSMCAL_PRIVATE_H_

typedef struct{

	volatile u32 CTRL ;
	volatile u32 LOAD ;
	volatile u32 VAL  ;
	volatile u32 CALIB;

}SYSTICK;

#define MSTK ((volatile SYSTICK*)0xE000E010)


#define DUMMY_XPSR   0x01000000
#define DUMMY_LR     0xFFFFFFFD


static void IdealTaskHandler (void) ;
static void UnBlockTask(void) ;


#define ENTER_CRITICAL_SECTION()		do{__asm volatile("MOV R0 , #1"); __asm volatile("MSR PRIMASK , R0"); } while(0)
#define EXIT_CRITICAL_SECTION()		do{__asm volatile("MOV R0 , #0"); __asm volatile("MSR PRIMASK , R0"); } while(0)

#endif

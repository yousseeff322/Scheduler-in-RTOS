/*************************************************/
/* AUTHOR           : Youssef Hamed              */
/* Date             : 8 MAR 2024                 */
/* Version          : v01                        */ 
/*************************************************/


#ifndef NVIC_PRIVATE_H_
#define NVIC_PRIVATE_H_


#define NVIC_ISER0       *((u32*)0xE000E100) /* Enable External interrupts from 0  to 31 */
#define NVIC_ISER1       *((u32*)0xE000E104) /* Enable External interrupts from 32 to 63 */

#define NVIC_ICER0       *((u32*)0xE000E180)
#define NVIC_ICER1       *((u32*)0xE000E184)

#define NVIC_ISPR0       *((u32*)0xE000E200)
#define NVIC_ISPR1       *((u32*)0xE000E204)

#define NVIC_ICPR0       *((u32*)0xE000E280)
#define NVIC_ICPR1       *((u32*)0xE000E284)

#define NVIC_IABR0       *((volatile u32*)0xE000E300)
#define NVIC_IABR1       *((volatile u32*)0xE000E304)


#define NVIC_IPR          ((u8*)0xE000E400)


//SCB
typedef struct{

	volatile u32 CPUID;
	volatile u32 ICSR;
	volatile u32 VTOR;
	volatile u32 AIRCR;
	volatile u32 SCR;
	volatile u32 CCR;
	volatile u32 SHPR1;
	volatile u32 SHPR2;
	volatile u32 SHPR3;
	volatile u32 SHCSR;
	volatile u32 CFSR;
	volatile u32 HFSR;
	volatile u32 RESERVED;
	volatile u32 MMFAR;
	volatile u32 BFAR;

}SCB_Type;

#define SCB ((volatile SCB_Type *) 0xE000ED00 )



#endif /* NVIC_REG_H_ */



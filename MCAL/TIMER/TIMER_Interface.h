/*************  DRIVER : TIMER             *******************
**************  DEV_NAME : ALAA            ******************
**************  DATE :5 SEP 2023         ******************
**************  SOFTWARE VERSION : V1.0    ******************
************************************************************/

#ifndef MCAL_TIMER_INTERFACE_H_
#define MCAL_TIMER_INTERFACE_H_
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.H"
#include "TIMER_Private.h"
#include "TIMER_Register.h"
#include "TIMER_Config.h"

void TIMER0_voidInit(void);
void TIMER1_voidInit(void);
void TIMER2_voidInit(void);
u8 TIMER_u8SetPreloadValue(u8 Copy_u8Timer,u16 Copy_u16Value);
void TIMER0_voidSetCtcInterruptState(u8 Copy_u8State);
u8 TIMER0_2_u8SetCompMatchValue(u8 Copy_u8Timer,u8 Copy_u8Value);
u8 TIMER1_u8SetCompMatchValue(u8 Copy_u8Channel,u16 Copy_u16_Value);
u8 TIMER_u8ReadValue(u8 Copy_u8Timer,u16* Copy_puValue);
void TIMER1_u16SetTopValue(u16 Copy_u16Value);
void TIMER1_ICU_Init(void);
u16 ICU_u16ReadICUREG(void);
void TIMER1_SetChannel(u8 Copy_u8Channel);
u8 TIMER1_voidICUISetTriggerMode(u8 Copy_u8Mode);

void TIMER1_voidICUInterruptState(u8 Copy_u8State);
u8 TIMER_voidSetCallBackFunc (void (*Copy_pvCallBack)(void),u8 Copy_u8TimerIndex);
#endif/*MCAL_TIMER_INTERFACE_H_*/

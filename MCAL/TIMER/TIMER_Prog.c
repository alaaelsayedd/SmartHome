/*************  DRIVER : TIMER             *******************
 **************  DEV_NAME : ALAA            ******************
 **************  DATE :5 SEP 2023         ******************
 **************  SOFTWARE VERSION : V1.0    ******************
 ************************************************************/
#include "TIMER_Interface.h"
void (*Copypv_SetCallBackFunc[8])(void) ={NULL};
void TIMER0_voidInit(void)
{
#if TIMER0_MODE== NORMAL
	/*SET Normal Mode*/
	CLR_BIT(TCCR0_REG,TCCR0_WGM00);
	CLR_BIT(TCCR0_REG,TCCR0_WGM01);

#elif TIMER0_MODE == PWM_PHASE_CORRECT
	/*SET PHASE CORRECT Mode*/
	SET_BIT(TCCR0_REG,TCCR0_WGM00);
	CLR_BIT(TCCR0_REG,TCCR0_WGM01);

	/*SET OC0 pin Behavior */
	TCCR0_REG&=TCCR0_COM_MASK;
	TCCR0_REG|=TIMER0_PWM_PHASE_CORRECT;

#elif TIMER0_MODE== CTC
	/*SET Compare Match Mode */
	CLR_BIT(TCCR0_REG,TCCR0_WGM00);
	SET_BIT(TCCR0_REG,TCCR0_WGM01);

	/*SET OC0 pin Behavior */
	TCCR0_REG&=TCCR0_COM_MASK;
	TCCR0_REG|=TIMER0_CTC;

#elif TIMER0_MODE== FAST_PWM
	/*SET Fast PWM Mode */
	SET_BIT(TCCR0_REG,TCCR0_WGM00);
	SET_BIT(TCCR0_REG,TCCR0_WGM01);

	/*SET OC0 pin Behavior */
	TCCR0_REG&=TCCR0_COM_MASK;
	TCCR0_REG|=TIMER0_FASTPWM;

#else
#error "Wrong Timer0 Mode"
#endif


#if TIMER0_OVERFLOW_INTERRUPT == DISABLE
	/*Disable timer 0 overflow Event*/
	CLR_BIT(TIMSK_REG,TIMSK_TOIE0);

#elif TIMER0_OVERFLOW_INTERRUPT == ENABLE
	/*Enable  timer 0 overflow Event*/
	SET_BIT(TIMSK_REG,TIMSK_TOIE0);
#else
#error   "Wrong Choose For Timer0 OverFlow Interrupt"
#endif
#if TIMER0_COMP_INTERRUPT == DISABLE
	/*Disable timer 0 Compare match Event*/
	CLR_BIT(TIMSK_REG,TIMSK_OCIE0);

#elif TIMER0_COMP_INTERRUPT == ENABLE
	/*Enable  timer 0 Compare match  Event*/
	SET_BIT(TIMSK_REG,TIMSK_OCIE0);
#else
#error   "Wrong Choose For Timer0 CTC Interrupt"
#endif

	/*Set Timer Prescaler */
	TCCR0_REG&=TCCR_PRES_MASK;
	TCCR0_REG|=TIMER0_PRES;
}
void TIMER2_voidInit(void)
{
#if TIMER2_MODE== NORMAL
	/*SET Normal Mode*/
	CLR_BIT(TCCR2_REG,TCCR2_WGM20);
	CLR_BIT(TCCR2_REG,TCCR2_WGM21);
#elif TIMER2_MODE == PWM_PHASE_CORRECT
	/*SET PHASE CORRECT Mode*/
	SET_BIT(TCCR2_REG,TCCR2_WGM20);
	CLR_BIT(TCCR2_REG,TCCR2_WGM21);
	/*SET OC2 pin Behavior */
	TCCR2_REG&=TCCR2_COM_MASK;
	TCCR2_REG|=TIMER0_PWM_PHASE_CORRECT;
#elif TIMER2_MODE== CTC
	/*SET Compare Match Mode */
	CLR_BIT(TCCR2_REG,TCCR2_WGM20);
	SET_BIT(TCCR2_REG,TCCR2_WGM21);

	/*SET OC2 pin Behavior */
	TCCR2_REG&=TCCR2_COM_MASK;
	TCCR2_REG|=TIMER0_CTC;
#elif TIMER2_MODE== FAST_PWM
	/*SET Fast PWM Mode */
	SET_BIT(TCCR2_REG,TCCR2_WGM20);
	SET_BIT(TCCR2_REG,TCCR2_WGM21);

	/*SET OC2 pin Behavior */
	TCCR2_REG&=TCCR2_COM_MASK;
	TCCR2_REG|=TIMER0_FASTPWM;

#else
#error "Wrong Timer2 Mode"
#endif
#if TIMER2_OVERFLOW_INTERRUPT == DISABLE
	/*Disable timer 2 overflow Event*/
	CLR_BIT(TIMSK_REG,TIMSK_TOIE2);

#elif TIMER2_OVERFLOW_INTERRUPT == ENABLE
	/*Enable  timer 2 overflow Event*/
	SET_BIT(TIMSK_REG,TIMSK_TOIE2);
#else
#error   "Wrong Choose For Timer2 OverFlow Interrupt"
#endif
#if TIMER2_COMP_INTERRUPT == DISABLE
	/*Disable timer 2 Compare match Event*/
	CLR_BIT(TIMSK_REG,TIMSK_OCIE2);

#elif TIMER2_COMP_INTERRUPT == ENABLE
	/*Enable  timer 2 Compare match  Event*/
	SET_BIT(TIMSK_REG,TIMSK_OCIE2);
#else
#error   "Wrong Choose For Timer2 CTC Interrupt"
#endif
	/*Set Timer Prescaler */
	TCCR2_REG&=TCCR_PRES_MASK;
	TCCR2_REG|=TIMER0_PRES;



}


u8 TIMER_u8SetPreloadValue(u8 Copy_u8Timer,u16 Copy_u16Value)
{
	u8 Local_u8ErrorSate=OK;
	switch (Copy_u8Timer)
	{
	case TIMER_0:
		TCNT0_REG=(u8)Copy_u16Value;
		break;
	case TIMER_1:
		TCNT1_REG=Copy_u16Value;
		break;
	case TIMER_2:
		TCNT2_REG=(u8)Copy_u16Value;
		break;
	default:
		Local_u8ErrorSate=NOK;
	}
	return Local_u8ErrorSate;

}
u8 TIMER0_2_u8SetCompMatchValue(u8 Copy_u8Timer,u8 Copy_u8Value)
{
	u8 Local_u8ErrorSate=OK;
	switch (Copy_u8Timer)
	{
	case TIMER_0:
		OCR0_REG=Copy_u8Value;
		break;
	case TIMER_2:
		OCR2_REG=Copy_u8Value;
		break;
	default:
		Local_u8ErrorSate=NOK;
	}
	return Local_u8ErrorSate;

}
void TIMER1_voidInit(void)
{
#if TIMER1_MODE == NORMAL
	TCCR1A_REG=0;
	/*Choose Timer1 Channel A or B*/
#elif  TIMER1_MODE == PWM_PHASE_CORRECT
	/*Set PWM_Phase Correct Mode*/
	SET_BIT(TCCR1A_REG,TCCR1A_WGM10);
	CLR_BIT(TCCR1A_REG,TCCR1A_WGM11);
	CLR_BIT(TCCR1B_REG,TCCR1B_WGM12);
	SET_BIT(TCCR1B_REG,TCCR1B_WGM13);
#if TIMER1_COM1A_CHANNEL== ENABLE

	/*SET OCRA pin Behavior */
	TCCR1A_REG&=TCCR1A_COM1A_MASK;
	TCCR1A_REG|=TIMER1_COM1A_PWM_PHASE_CORRECT;
#endif
#if TIMER1_COM1B_CHANNEL== ENABLE
	/*SET OCRB pin Behavior */
	TCCR1A_REG&=TCCR1A_COM1B_MASK;
	TCCR1A_REG|=TIMER1_COM1B_PWM_PHASE_CORRECT;
#endif

#elif  TIMER1_MODE ==	CTC
	/*Set Compare Match Mode */
	CLR_BIT(TCCR1A_REG,TCCR1A_WGM10);
	CLR_BIT(TCCR1A_REG,TCCR1A_WGM11);
	SET_BIT(TCCR1B_REG,TCCR1B_WGM12);
	CLR_BIT(TCCR1B_REG,TCCR1B_WGM13);
#if TIMER1_COM1A_CHANNEL== ENABLE
	/*SET OCRA pin Behavior */
	TCCR1A_REG&=TCCR1A_COM1A_MASK;
	TCCR1A_REG|=TIMER1_COM1A_CTC;
#endif
#if TIMER1_COM1B_CHANNEL== ENABLE
	/*SET OCRB pin Behavior */
	TCCR1A_REG&=TCCR1A_COM1B_MASK;
	TCCR1A_REG|=TIMER1_COM1B_CTC;
#endif

#elif  TIMER1_MODE ==	FAST_PWM
	/*Set Fast PWM Mode */
	SET_BIT(TCCR1A_REG,TCCR1A_WGM10);
	SET_BIT(TCCR1A_REG,TCCR1A_WGM11);
	SET_BIT(TCCR1B_REG,TCCR1B_WGM12);
	SET_BIT(TCCR1B_REG,TCCR1B_WGM13);
#if TIMER1_COM1A_CHANNEL== ENABLE
	/*SET OCRA pin Behavior */
	TCCR1A_REG&=TCCR1A_COM1A_MASK;
	TCCR1A_REG|=TIMER1_COM1A_FASTPWM;
#endif
#if TIMER1_COM1B_CHANNEL== ENABLE

	/*SET OCRB pin Behavior */
	TCCR1A_REG&=TCCR1A_COM1B_MASK;
	TCCR1A_REG|=TIMER1_COM1B_FASTPWM;
#endif
#elif TIMER1_MODE==PWM_PHASE_CORRECT_TOP_VALUE
	/*Set PWM_Phase Correct Mode With ICR Value*/
	CLR_BIT(TCCR1A_REG,TCCR1A_WGM10);
	SET_BIT(TCCR1A_REG,TCCR1A_WGM11);
	CLR_BIT(TCCR1B_REG,TCCR1B_WGM12);
	SET_BIT(TCCR1B_REG,TCCR1B_WGM13);
#if TIMER1_COM1A_CHANNEL== ENABLE
	/*SET OCRA pin Behavior */
	TCCR1A_REG&=TCCR1A_COM1A_MASK;
	TCCR1A_REG|=TIMER1_COM1A_PWM_PHASE_CORRECT;
#endif
#if TIMER1_COM1B_CHANNEL== ENABLE
	/*SET OCRB pin Behavior */
	TCCR1A_REG&=TCCR1A_COM1B_MASK;
	TCCR1A_REG|=TIMER1_COM1B_PWM_PHASE_CORRECT;
#endif
#elif TIMER1_MODE==FAST_PWM_TOP_VALUE
	/*Set Fast PWM Mode */
	CLR_BIT(TCCR1A_REG,TCCR1A_WGM10);
	SET_BIT(TCCR1A_REG,TCCR1A_WGM11);
	SET_BIT(TCCR1B_REG,TCCR1B_WGM12);
	SET_BIT(TCCR1B_REG,TCCR1B_WGM13);
#if TIMER1_COM1A_CHANNEL== ENABLE
	/*SET OCRA pin Behavior */
	TCCR1A_REG&=TCCR1A_COM1A_MASK;
	TCCR1A_REG|=TIMER1_COM1A_FASTPWM;
#endif
#if TIMER1_COM1B_CHANNEL== ENABLE

	/*SET OCRB pin Behavior */
	TCCR1A_REG&=TCCR1A_COM1B_MASK;
	TCCR1A_REG|=TIMER1_COM1B_FASTPWM;
#endif
#elif TIMER1_MODE==CTC_TOP_VALUE
	/*Set Compare Match Mode */
	CLR_BIT(TCCR1A_REG,TCCR1A_WGM10);
	CLR_BIT(TCCR1A_REG,TCCR1A_WGM11);
	SET_BIT(TCCR1B_REG,TCCR1B_WGM12);
	SET_BIT(TCCR1B_REG,TCCR1B_WGM13);
#if TIMER1_COM1A_CHANNEL== ENABLE
	/*SET OCRA pin Behavior */
	TCCR1A_REG&=TCCR1A_COM1A_MASK;
	TCCR1A_REG|=TIMER1_COM1A_CTC;
#endif
#if TIMER1_COM1B_CHANNEL== ENABLE
	/*SET OCRB pin Behavior */
	TCCR1A_REG&=TCCR1A_COM1B_MASK;
	TCCR1A_REG|=TIMER1_COM1B_CTC;
#endif
#endif
#if TIMER1_OVERFLOW_INTERRUPT== ENABLE
	/*ENABLE timer 1 overflow Event*/
	SET_BIT(TIMSK_REG,TIMSK_TICIE1);
#elif  TIMER1_OVERFLOW_INTERRUPT== DISABLE
	/*Disable timer 1 overflow Event*/
	CLR_BIT(TIMSK_REG,TIMSK_TICIE1);
#endif
#if TIMER1_COMPA_INTERRUPT== ENABLE
	/*Enable  timer 1 Compare match Channel A  Event*/
	SET_BIT(TIMSK_REG,TIMSK_OCIE1A);
#elif  TIMER1_OVERFLOW_INTERRUPT== DISABLE
	/*Disable  timer 1 Compare match Channel A  Event*/
	CLR_BIT(TIMSK_REG,TIMSK_OCIE1A);
#endif
#if TIMER1_COMPB_INTERRUPT== ENABLE
	/*Enable  timer 1 Compare match Channel B  Event*/
	SET_BIT(TIMSK_REG,TIMSK_OCIE1B);
#elif  TIMER1_OVERFLOW_INTERRUPT== DISABLE
	/*Disable  timer 1 Compare match Channel B  Event*/
	CLR_BIT(TIMSK_REG,TIMSK_OCIE1A);
#endif

	/*Set Timer1 Prescaler */
	TCCR1B_REG&=TCCR_PRES_MASK;
	TCCR1B_REG|=TIMER1_PRES;

}
void TIMER1_SetChannel(u8 Copy_u8Channel)
{
	if (Copy_u8Channel==TIMER1_COMA)
	{
		TCCR1A_REG&=TCCR1A_COM1A_MASK;
		TCCR1A_REG|=TIMER1_COM1A_FASTPWM;



	}
	else if (Copy_u8Channel==TIMER1_COMB)
	{
		/*SET OCRB pin Behavior */
		TCCR1A_REG&=TCCR1A_COM1B_MASK;
		TCCR1A_REG|=TIMER1_COM1B_FASTPWM;
	}
}



u8 TIMER1_u8SetCompMatchValue(u8 Copy_u8Channel,u16 Copy_u16_Value)
{
	u8 Local_u8ErrorState =OK;
	if (Copy_u8Channel==TIMER1_COMA)
	{
		OCR1A_REG =Copy_u16_Value;
	}
	else if (Copy_u8Channel==TIMER1_COMB)
	{
		OCR1B_REG =Copy_u16_Value;
	}
	else
	{
		Local_u8ErrorState =NOK;
	}


	return Local_u8ErrorState;
}
u8 TIMER_u8ReadValue(u8 Copy_u8Timer,u16* Copy_puValue)
{
	u8 Local_u8ErrorSate=OK;
	switch (Copy_u8Timer)
	{
	case TIMER_0:
		*Copy_puValue=TCNT0_REG;
		break;
	case TIMER_1:
		*Copy_puValue=TCNT1_REG;

		break;
	case TIMER_2:
		*Copy_puValue=TCNT2_REG;
		break;
	default:
		Local_u8ErrorSate=NOK;
	}
	return Local_u8ErrorSate;
}
void TIMER1_u16SetTopValue(u16 Copy_u16Value)
{
	/*Set Top Value */
	ICR1_REG=Copy_u16Value;
}
void TIMER1_ICU_Init(void)
{
#if TIMER1_ICU_MODE==RISING_EDGE
	/*Enable ICU At Rising Trigger Mode*/
	SET_BIT(TCCR1B_REG,TCCR1B_ICES1);
#elif 	TIMER1_ICU_MODE == FALLING_EDGE
	/*Enable ICU At Falling Trigger Mode*/
	CLR_BIT(TCCR1B_REG,TCCR1B_ICES1);
#endif
#if TIMER1_ICU_INTERRUPT==ENABLE
	/*Enable ICU Interrupt*/
	SET_BIT(TIMSK_REG,TIMSK_TICIE1);
#elif TIMER1_ICU_INTERRUPT==DISABLE
	/*Disable ICU Interrupt*/
	CLR_BIT(TIMSK_REG,TIMSK_TICIE1);
#endif
}
void TIMER0_voidSetCtcInterruptState(u8 Copy_u8State)
{
	switch(Copy_u8State)
	{
	case ENABLE:
		/*Enable  timer 0 Compare match  Event*/
		SET_BIT(TIMSK_REG,TIMSK_OCIE0);
		break;
	case DISABLE:
		/*Disable  timer 0 Compare match  Event*/
		CLR_BIT(TIMSK_REG,TIMSK_OCIE0);
		break;
	}
}

u8 TIMER1_voidICUISetTriggerMode(u8 Copy_u8Mode)
{
	u8 Local_u8ErrorState=OK;
	if(Copy_u8Mode==RISING_EDGE)
	{
		/*Enable ICU At Rising Trigger Mode*/
		SET_BIT(TCCR1B_REG,TCCR1B_ICES1);
	}
	else if(Copy_u8Mode==FALLING_EDGE)
	{
		/*Enable ICU At Falling Trigger Mode*/
		CLR_BIT(TCCR1B_REG,TCCR1B_ICES1);

	}
	else
	{
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}
void TIMER1_voidICUInterruptState(u8 Copy_u8State)
{
	if(Copy_u8State==ENABLE)
	{
		/*Enable ICU Interrupt*/
		SET_BIT(TIMSK_REG,TIMSK_TICIE1);
	}
	else if(Copy_u8State==DISABLE)
	{
		/*DISABLE ICU Interrupt*/
		CLR_BIT(TIMSK_REG,TIMSK_TICIE1);
	}
}
u8 TIMER_voidSetCallBackFunc (void (*Copy_pvCallBack)(void),u8 Copy_u8TimerIndex)
{
	u8  Local_u8ErrorState=OK;
	if(Copy_pvCallBack!=NULL)
	{
		Copypv_SetCallBackFunc[Copy_u8TimerIndex]=Copy_pvCallBack;
	}
	else
	{
		Local_u8ErrorState=NOK;
	}

	return Local_u8ErrorState;
}
u16 ICU_u16ReadICUREG(void)
{
	return ICR1_REG;
}

/*
TIMER_COUNTER0_OVERFLOW   0
TIMER_COUNTER1_OVERFLOW   1
TIMER_COUNTER2_OVERFLOW   2
TIMER_COUNTER0_COM        3
TIMER_COUNTER1_COMA       4
TIMER_COUNTER1_COMB       5
TIMER_COUNTER2_COM        6
TIMER_COUNTER1_ICU        7
 */
/*Timer/Counter2 Compare Match*/
void __vector_4 (void) __attribute__((signal));
void __vector_4 (void)
{
	if(Copypv_SetCallBackFunc[TIMER_COUNTER2_COM]!=NULL)
	{
		Copypv_SetCallBackFunc[TIMER_COUNTER2_COM]();
	}
	else
	{
		/*DO Nothing*/
	}

}
/*Timer/Counter2 Overflow*/
void __vector_5 (void) __attribute__((signal));
void __vector_5 (void)
{
	if(Copypv_SetCallBackFunc[TIMER_COUNTER2_OVERFLOW]!=NULL)
	{
		Copypv_SetCallBackFunc[TIMER_COUNTER2_OVERFLOW]();
	}
	else
	{
		/*DO Nothing*/
	}
}
/*Timer/Counter1 Capture Event*/
void __vector_6 (void) __attribute__((signal));
void __vector_6 (void)
{
	if(Copypv_SetCallBackFunc[TIMER_COUNTER1_ICU]!=NULL)
	{
		Copypv_SetCallBackFunc[TIMER_COUNTER1_ICU]();
	}
	else
	{
		/*DO Nothing*/
	}
}
/*Timer/Counter1 Compare Match A*/
void __vector_7 (void) __attribute__((signal));
void __vector_7 (void)
{
	if(Copypv_SetCallBackFunc[TIMER_COUNTER1_COMA]!=NULL)
	{
		Copypv_SetCallBackFunc[TIMER_COUNTER1_COMA]();
	}
	else
	{
		/*DO Nothing*/
	}
}
/*Timer/Counter1 Compare Match B*/
void __vector_8 (void) __attribute__((signal));
void __vector_8 (void)
{
	if(Copypv_SetCallBackFunc[TIMER_COUNTER1_COMB]!=NULL)
	{
		Copypv_SetCallBackFunc[TIMER_COUNTER1_COMB]();
	}
	else
	{
		/*DO Nothing*/
	}
}
/*Timer/Counter1 Overflow*/
void __vector_9 (void) __attribute__((signal));
void __vector_9 (void)
{
	if(Copypv_SetCallBackFunc[TIMER_COUNTER1_OVERFLOW]!=NULL)
	{
		Copypv_SetCallBackFunc[TIMER_COUNTER1_OVERFLOW]();
	}
	else
	{
		/*DO Nothing*/
	}
}
/*Timer/Counter0 Compare Match*/
void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{
	if(Copypv_SetCallBackFunc[TIMER_COUNTER0_COM]!=NULL)
	{
		Copypv_SetCallBackFunc[TIMER_COUNTER0_COM]();
	}
	else
	{
		/*DO Nothing*/
	}
}
///*Timer/Counter0 Overflow*/
void __vector_11 (void) __attribute__((signal));
void __vector_11 (void)
{
	if(Copypv_SetCallBackFunc[TIMER_COUNTER0_OVERFLOW]!=NULL)
	{
		Copypv_SetCallBackFunc[TIMER_COUNTER0_OVERFLOW]();
	}
	else
	{
		/*DO Nothing*/
	}
}



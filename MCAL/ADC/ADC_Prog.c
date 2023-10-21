
#include "ADC_Interface.h"
u8  ADC_STATE = IDEL;
static void(*Copy_pvCallBackNotificateFunc)(void) =NULL;
static u8 * Copy_puAdcReading =NULL;
u8  *Ptr_puArray= NULL;
static void(*Copy_pvCallBackChainNotifiacteFunc)(void) =NULL;
u8  Chain_Id;
u8 Size_Chain;
u8 Index;
u8 Chain_Conv_Flag;


/*
*FUNC_Name: ADC_voidInit
*FUNC_Discrption: ADC Initialization
*FUNC_input: void
*FUNC_Output: void 
*/
void ADC_voidInit(void)
{
/*Clear REF Bits on ADMUX Before Setting Voltage Refer*/
ADMUX_REG&=ADMUX_REF_VOLT_MASK;

/* SET ADC Voltage Reference */
ADMUX_REG|=ADC_VOLT_REF;

/*Check for ADC Work with Left Adjust result Or Right Adjust Result*/
#if ADC_LEFT_ADJUST == ENABLE

/*SET ADLAR IN ADMUX REG*/
SET_BIT(ADMUX_REG,ADMUX_ADLAR);

#elif ADC_LEFT_ADJUST == DISABLE

/*Clear ADLAR IN ADMUX REG FOR Right Adjust Result */
CLR_BIT(ADMUX_REG,ADMUX_ADLAR);

#else

#error  "Wrong Selection for ADC_LEFT_ADJUST"

#endif

/*Check for ADC Auto Trigger Mode*/
#if ADC_AUTO_TRIGGER  == ENABLE
/* Set ADATE bit  In ADCSRA REG for Enable Auto Trigger*/
SET_BIT(ADCSRA_REG,ADCSRA_ADATE);

/*Set Auto Trigger Source Mode */
SFIOR_REG&=SFIOR_ADTS_MASK;
SFIOR_REG|=TRIGGER_SOURCE;
/*Set ADC Channel */
ADMUX_REG&=ADMUX_MUX_MASK;
ADMUX_REG|=ADC_TRIGGER_CHANNEL;
/*ADC Start Conversion*/
SET_BIT(ADCSRA_REG,ADCSRA_ADSC);

#elif ADC_AUTO_TRIGGER  == DISABLE

/* Clear ADATE bit  In ADCSRA REG for Disable Auto Trigger*/
CLR_BIT(ADCSRA_REG,ADCSRA_ADATE);
#else

#error  "Wrong Selection for ADC Auto Trigger Enable"

#endif

/*Check For Interrupt Enable or Disable*/
#if ADC_INTERRUPT == ENABLE

/*Enable ADC Interrupt By Set ADIE Bit on ADCSRA REG*/
SET_BIT(ADCSRA_REG,ADCSRA_ADIE);

#elif ADC_INTERRUPT == DISABLE

/* Disable ADC Interrupt By Clear ADIE Bit on ADCSRA REG*/
CLR_BIT(ADCSRA_REG,ADCSRA_ADIE);

#else

#error  "Wrong Selection for ADC Interrupt Enable"

#endif

/*Clear ADPS Bits on ADCSRA  Before Setting ADC Prescaler Bits*/
ADCSRA_REG&=ADCSRA_ADPS_MASK;

/*Set ADC Prescaler Select Bits*/
ADCSRA_REG|=ADC_PRESCALER;

/* Enable ADC BY set ADEN IN ADSRA REG*/
SET_BIT(ADCSRA_REG,ADCSRA_ADEN);

}

/**********************************************************************************************************************/
/*FUNC_Name: ADC_u8StartConvSynch
*FUNC_Discrption: Get ADC Reading   
*FUNC_input:Copy_u8Channel Type(u8): ADC_Channel  , Copy_puRead Type(u8*):Address of Variable to Store Value 
*FUNC_Output: Error State  :option 
                            1-OK: 0
							2-NOK: 1
							3-BUSY_FUNC: 3*/
/*************************************************************************************************************************/
 

u8 ADC_u8StartConvSynch(u8 Copy_u8Channel, u8* Copy_puRead)
{
u8 Local_u8ErrorState =OK;
u32 Local_u32Counter=0;
if (ADC_STATE==IDEL)
{
/*SET ADC STATE BUSY */
ADC_STATE=BUSY;
/*Clear Mux Bits in ADMUX REG*/
ADMUX_REG&=ADMUX_MUX_MASK;
/*ADC SET Channel*/
ADMUX_REG|=Copy_u8Channel;
/*ADC Start Conversion*/
SET_BIT(ADCSRA_REG,ADCSRA_ADSC);

while(READ_BIT(ADCSRA_REG,ADCSRA_ADIF)==0 && Local_u32Counter!=ADC_TIMEOUT)
{
	Local_u32Counter++;
}

if(Local_u32Counter==ADC_TIMEOUT)
{
	/*if counter equal adc_count and flag not raised return not ok error state*/
	Local_u8ErrorState=NOK;
}
else
{
	/*Flag is Raised*/
	/*Clear Flag By Set ADIF in ADCSRA_REG*/
	SET_BIT(ADCSRA_REG,ADCSRA_ADIF);

	/*Get ADC Reading Value */
	*Copy_puRead=ADCH_REG;

	/*return ADC State to IDEL*/
	 ADC_STATE=IDEL;


}
}
else
{
	Local_u8ErrorState=BUSY_FUNC;
}

return Local_u8ErrorState;


}
/**********************************************************************************************************************/
/*FUNC_Name: ADC_u8StartConvSynch
*FUNC_Discrption: Get ADC Reading   
*FUNC_input:Copy_u8Channel Type(u8): ADC_Channel  , Copy_puRead Type(u8*):Address of Variable to Store Value ,
  Copy_pvNotificateFunc :pointer to Function  
                         input:void 
						 output:void
*FUNC_Output: Error State  :option 
                            1-OK: 0
							2-NOK: 1
		                    3-NULL_POINTER: 2
		                    4-BUSY_FUNC  :3 */
/**********************************************************************************************************************/
u8 ADC_u8StartConvAsynch(u8 Copy_u8Channel, u8* Copy_puRead,void(*Copy_pvNotificateFunc)(void))
{
u8 Local_u8ErrorState=OK;
if(ADC_STATE==IDEL)
{
/*Check Pointer & Pointer to Function return ErrorState if equal Null*/
if(Copy_puRead==NULL ||Copy_pvNotificateFunc==NULL)
{
	 Local_u8ErrorState=NULL_POINTER;
}
else
{

	ADC_STATE= BUSY;
	/*Initialize ADC Reading Globally && Notification Function */
	Copy_pvCallBackNotificateFunc=Copy_pvNotificateFunc;
	Copy_puAdcReading=Copy_puRead;

	/*Clear Mux Bits in ADMUX REG*/
	ADMUX_REG&=ADMUX_MUX_MASK;

	/*ADC SET Channel*/
	ADMUX_REG|=Copy_u8Channel;

	/*ADC Start Conversion*/
	SET_BIT(ADCSRA_REG,ADCSRA_ADSC);

	/*Enable ADC Interrupt */
	SET_BIT(ADCSRA_REG,ADCSRA_ADIE);
	Chain_Conv_Flag=0;
}

}
else
{
	Local_u8ErrorState=BUSY_FUNC;
}




return Local_u8ErrorState;
}
/**********************************************************************************************************************/
/*FUNC_Name: ADC_u8StartAsynchChainConversion
*FUNC_Discrption: Get ADC Chain Reading
*FUNC_input: Pointer to struct
*FUNC_Output: Error State  :option
                            1-OK: 0
							2-NOK: 1
		                    3-NULL_POINTER: 2
		                    4-BUSY_FUNC  :3 */
/**********************************************************************************************************************/
u8 ADC_u8StartAsynchChainConversion(struct ADC_Chain_t * Chain)
{
	u8 Local_u8ErrorState=OK;

	if(ADC_STATE==IDEL)
	{
	/*Check Pointer to Struct not equal null*/
	if(Chain==NULL)
	{
		 Local_u8ErrorState=NULL_POINTER;
	}
	else
	{
	ADC_STATE= BUSY;
	/*Initialize ADC Notificate Function && Size Of Chain && Array Of Reading && Chain_id */
	Size_Chain = Chain->Size_of_Chain;
	Chain_Id= Chain->Chain_id;
	Ptr_puArray=Chain->ptrArr;
	Copy_pvCallBackChainNotifiacteFunc=Chain->Notifiacte_func;

	/*Clear Mux Bits in ADMUX REG*/
	ADMUX_REG&=ADMUX_MUX_MASK;

	/*ADC SET Channel*/
	ADMUX_REG|=Chain_Id;

	/*ADC Start Conversion*/
	SET_BIT(ADCSRA_REG,ADCSRA_ADSC);

	/*Enable ADC Interrupt */
	SET_BIT(ADCSRA_REG,ADCSRA_ADIE);
	Index=0;
	Chain_Conv_Flag=1;

	}

	}
	else
	{
		Local_u8ErrorState=BUSY_FUNC;
	}





	return Local_u8ErrorState;

}
s32 Map(s32 InputMin,s32 InputMax,s32 OutputMin,s32 OutputMax,s32 InputVar)
{
	s32 Y,X,Y_Div_x,Result;
	Y=OutputMax-OutputMin;
	X=InputMax-InputMin;
	Y_Div_x=Y/X;
	Result=((InputVar-InputMin)*Y_Div_x)+OutputMin;

	return Result;

}

void __vector_16 (void) __attribute__ ((signal));
void __vector_16 (void)
{
u8 Counter;
if(Chain_Conv_Flag==0)
{
/*Read ADC*/
*Copy_puAdcReading=ADCH_REG;

/*Return ADC State To IDEL*/
ADC_STATE=IDEL;

/*Call ADC Notificate Function*/
Copy_pvCallBackNotificateFunc();

/*Disable ADC Interrupt*/
CLR_BIT(ADCSRA_REG,ADCSRA_ADIE);
}
else
{
if(Index==Size_Chain)
{
/*Call ADC Notificate Function*/
Copy_pvCallBackChainNotifiacteFunc();

/*Disable ADC Interrupt*/
CLR_BIT(ADCSRA_REG,ADCSRA_ADIE);

/*Return Index TO Zero*/
Index=0;

/*Return ADC state To Idel State*/
ADC_STATE=IDEL;


}
else
{
for(Counter=0;Counter<Size_Chain;Counter++)
{
	/*Check of Index*/
	if(Index==Counter)
	{
	Ptr_puArray[Index]=ADCH_REG;
	}
}
/*Clear Mux Bits in ADMUX REG*/
ADMUX_REG&=ADMUX_MUX_MASK;

/*ADC SET  New Channel*/
ADMUX_REG|=Chain_Id+1;

/*ADC Start New  Conversion*/
SET_BIT(ADCSRA_REG,ADCSRA_ADSC);
Index++;
}
}

}

/********************DRIVER : USART           **********************
 *********************DEV_NAME : ALAA          **********************
 *********************DATE :18 SEP 2023        **********************
 *********************SOFTWARE VERSION : V1.0  **********************
 ********************************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.H"
#include "USART_Interface.h"
#include "USART_Register.h"
#include "USART_Private.h"
#include "USART_Config.h"
#include <avr/delay.h>
void (*CallBackNotificateFunc)(void)=NULL;
static u8 USART_TrData,*USART_ReData;
static u8 USART_STATE = IDEL;
static u8 String_Flag;
static u8 *ptr_String;
static u8 String_Size;
void USART_voidInit(void)
{
	u8 UCSRC_Value =0;
	/*Control OF USART Interrupt */
#if USART_RX_INTERRUPT ==ENABLE
	/*Enable USART Receive Complete Interrupt*/
	SET_BIT(UCSRB_REG,UCSRB_RXCIE);

#elif USART_RX_INTERRUPT ==DISABLE
	/*Disable USART Receive Complete Interrupt*/
	CLR_BIT(UCSRB_REG,UCSRB_RXCIE);
#endif

#if USART_TX_INTERRUPT ==ENABLE
	/*Enable USART Transmit Complete Interrupt*/
	SET_BIT(UCSRB_REG,UCSRB_TXCIE);
#elif USART_TX_INTERRUPT ==DISABLE
	/*Disable USART Transmit Complete Interrupt*/
	CLR_BIT(UCSRB_REG,UCSRB_TXCIE);
#endif

#if USART_DRE_INTERRUPT==ENABLE
	/*Enable USART Data Register Empty Interrupt*/
	SET_BIT(UCSRB_REG,UCSRB_UDRIE);
#elif USART_DRE_INTERRUPT ==DISABLE
	/*Disable USART Data Register Empty Interrupt*/
	CLR_BIT(UCSRB_REG,UCSRB_UDRIE);
#endif

	/*Choose UCSRC REG */
	SET_BIT(UCSRC_Value,UCSRC_URSEL);
	/*Choose USART Mode Synch OR Asynch */
#if USART_MODE_SELECT  ==ASYNCH
	/*Enable  Asynch Mode */
	CLR_BIT(UCSRC_Value,UCSRC_UMSEL);
#elif USART_MODE_SELECT  ==SYNCH
	/*Enable  synch Mode */
	SET_BIT(UCSRC_Value,UCSRC_UMSEL);
	/*Choose Clock Polarity*/
#if USART_CLOCK_POLARITY==TR_RISING_RE_FALLING
	/*Set Clock Polarity Transmit at Rising Edge and Sampling At Falling Edge*/
	CLR_BIT(UCSRC_Value,UCSRC_UCPOL);
#elif USART_CLOCK_POLARITY==TR_FALLING_RE_RISING
	/*Set Clock Polarity Transmit at Falling Edge and Sampling At Rising Edge*/
	SET_BIT(UCSRC_Value,UCSRC_UCPOL);
#endif

#endif
	/*Set Parity Mode */
	UCSRC_Value&=UCSRC_PARITY_MASK;
	UCSRC_Value|=USART_PARITY_MODE;
#if USART_STOP_BIT==ONE
	/*Select stop bit One bit*/
	CLR_BIT(UCSRC_Value,UCSRC_USBS);
#elif USART_STOP_BIT==TWO
	/*Select stop bit TWO BIT bit*/
	SET_BIT(UCSRC_Value,UCSRC_USBS);
#endif
	/*Set USART  Character Size */
	UCSRC_Value&=UCSRC_UCSZ_MASK;
#if USART_CHARACTER_SIZE==NINE_BIT
	/*Choose Nine Bit Character Size */
	SET_BIT(UCSRB_REG,UCSRB_UCSZ2);
	UCSRC_Value|=(USART_CHARACTER_SIZE-1);
#else
	UCSRC_Value|=USART_CHARACTER_SIZE;
#endif
	/*Set UCSRC Register Value */
	UCSRC_REG= UCSRC_Value;
	/*Choose USART Transmission Double Speed  */
#if  USART_DOUBLE_SPEED== ENABLE
	/*Enable USART Double Speed*/
	SET_BIT(UCSRA_REG,UCSRA_U2X);
	UBRRL_REG=103;
#elif  USART_DOUBLE_SPEED== DISABLE
	/*DISABLE USART Double Speed*/
	CLR_BIT(UCSRA_REG,UCSRA_U2X);
	UBRRL_REG=51;
#endif
#if USART_TRANSMITTER==ENABLE
	/*Enable USART To Be Transmitter*/
	SET_BIT(UCSRB_REG,UCSRB_TXEN);
#elif USART_TRANSMITTER== DISABLE
	/*Disable USART To Be Transmitter*/
	CLR_BIT(UCSRB_REG,UCSRB_TXEN);
#endif
#if USART_RECEVIER==ENABLE
	/*Enable USART To Be Receiver */
	SET_BIT(UCSRB_REG,UCSRB_RXEN);
#elif USART_RECEVIER== DISABLE
	/*Disable USART To Be Receiver*/
	CLR_BIT(UCSRB_REG,UCSRB_RXEN);
#endif

}
u8 USART_u8SendDataSynch(u8 Copy_u8Data)
{
	u8 Local_u8ErrorState=OK;
	u32 Local_u32Counter=0;

	/*Waiting for Empty Register Flag Raised */
	while(READ_BIT(UCSRA_REG,UCSRA_UDRE)==0);
	{
		Local_u32Counter++;
	}
	if (Local_u32Counter==USART_TIMEOUT)
	{
		Local_u8ErrorState=NOK;

	}
	else
	{
		UDR_REG= Copy_u8Data;

	}

	return Local_u8ErrorState;
}
u8 USART_u8ReceiveDataSynch(u8* Copy_puData)
{
	u8 Local_u8ErrorState=OK;
	u32 Local_u32Counter=0;
	/*Wait for Receive  Data Complete Is Raised or Counter overflow */
	while(READ_BIT(UCSRA_REG,UCSRA_RXC)!=1 )
	{
		Local_u32Counter++;
	}
	/*Check For Error */
	if(Local_u32Counter==USART_TIMEOUT)
	{
		Local_u8ErrorState=NOK;
	}
	else
	{
		*Copy_puData=UDR_REG;
	}

	return Local_u8ErrorState;
}
u8 USART_u8SendDataAsynch(u8 Copy_u8Data,void(*NotificateFunc)(void))
{
	u8 Local_u8ErrorState=OK;
	/*Check For USART State */
	if(USART_STATE==IDEL)
	{
		/*Change Status to Busy */
		USART_STATE=BUSY;
		if(NotificateFunc!=NULL)
		{
			/*Initialize Variable Globally*/
			CallBackNotificateFunc=NotificateFunc;
			USART_TrData=Copy_u8Data;

			/*Enable USART Data Register Empty Interrupt*/
			SET_BIT(UCSRB_REG,UCSRB_UDRIE);
		}
		else
		{
			Local_u8ErrorState=NULL_POINTER;
		}
	}
	else
	{
		Local_u8ErrorState=BUSY_FUNC;

	}

	return Local_u8ErrorState;
}
u8 USART_u8ReceiveDataAsynch(u8* Copy_u8Data,void(*NotificateFunc)(void))
{
	u8 Local_u8ErrorState=OK;
	/*Check For USART State */
	if(USART_STATE==IDEL)
	{
		/*Change Status to Busy */
		USART_STATE=BUSY;
		if(NotificateFunc!=NULL)
		{
			/*Initialize Variable Globally*/
			CallBackNotificateFunc=NotificateFunc;
			USART_ReData=Copy_u8Data;

			/*Enable USART Receive Complete  Interrupt*/
			SET_BIT(UCSRB_REG,UCSRB_RXCIE);
		}
		else
		{
			Local_u8ErrorState=NULL_POINTER;
		}
	}
	else
	{
		Local_u8ErrorState=BUSY_FUNC;

	}
	return Local_u8ErrorState;
}
u8 USART_u8SendStringSynch(const char *Copy_puString)
{
	u8 Local_ErrorState=OK;
	u8 Local_u8Counter=0;
	if(Copy_puString==NULL)
	{
		Local_ErrorState=NULL_POINTER;
	}
	else
	{
		while(Copy_puString[Local_u8Counter]!='\0')
		{
			USART_u8SendDataSynch(Copy_puString[Local_u8Counter]);
//			_delay_ms(20);
			Local_u8Counter++;

		}
	}



	return Local_ErrorState;
}
u8 USART_u8ReceiveStringSynch( char *Copy_puString,u8 Copy_u8StringSize)
{
	u8 Local_ErrorState=OK;
	u8 Local_u8Counter=0;
	if(Copy_puString==NULL)
	{
		Local_ErrorState=NULL_POINTER;
	}
	else
	{
		while(Local_u8Counter!=Copy_u8StringSize)
		{
			while(READ_BIT(UCSRA_REG,UCSRA_RXC)!=1);
			Copy_puString[Local_u8Counter]=UDR_REG;
//			_delay_ms(20);
			Local_u8Counter++;

		}

	}
	return Local_ErrorState;
}

u8 USART_u8SendStringAsynch( char *Copy_puString,void(*NotificateFunc)(void))
{
	u8 Local_u8ErrorState=OK;
	/*Check For USART State */
	if(USART_STATE==IDEL)
	{
		/*Change Status to Busy */
		USART_STATE=BUSY;
		String_Flag=1;
		if(NotificateFunc!=NULL)
		{
			/*Initialize Variable Globally*/
			CallBackNotificateFunc=NotificateFunc;
			ptr_String=Copy_puString;

			/*Enable USART Data Register Empty Interrupt*/
			SET_BIT(UCSRB_REG,UCSRB_UDRIE);
		}
		else
		{
			Local_u8ErrorState=NULL_POINTER;
		}
	}
	else
	{
		Local_u8ErrorState=BUSY_FUNC;

	}

	return Local_u8ErrorState;

}
u8 USART_u8ReceiveStringAsynch( char *Copy_puString,u8 Copy_u8StringSize,void(*NotificateFunc)(void))
{
	u8 Local_u8ErrorState=OK;
	/*Check For USART State */
	if(USART_STATE==IDEL)
	{
		/*Change Status to Busy */
		USART_STATE=BUSY;
		String_Flag=1;
		if(NotificateFunc!=NULL)
		{
			/*Initialize Variable Globally*/
			CallBackNotificateFunc=NotificateFunc;
			USART_ReData=Copy_puString;
			String_Size=Copy_u8StringSize;

			/*Enable USART Receive Complete  Interrupt*/
			SET_BIT(UCSRB_REG,UCSRB_RXCIE);
		}
		else
		{
			Local_u8ErrorState=NULL_POINTER;
		}
	}
	else
	{
		Local_u8ErrorState=BUSY_FUNC;

	}


	return Local_u8ErrorState;
}




void __vector_14 (void) __attribute__ ((signal));
void __vector_14 (void)
{
	if(String_Flag!=1)
	{
		/*Send Data*/
		UDR_REG=USART_TrData;
		/*Call Back NoItificate FUNC */
		CallBackNotificateFunc();
		/*Make USART SATE IDEL*/
		USART_STATE=IDEL;
		/*Disable Interrupt*/
		CLR_BIT(UCSRB_REG,UCSRB_UDRIE);
	}
	else if(String_Flag==1)
	{
		static u8 Local_u8Counter=0;

			UDR_REG=ptr_String[Local_u8Counter];
			_delay_ms(50);
			Local_u8Counter++;

	     if(ptr_String[Local_u8Counter]=='\0')
			{

			/*Call Back NoItificate FUNC */
			CallBackNotificateFunc();
			/*Make USART SATE IDEL*/
			USART_STATE=IDEL;
			/*Disable Interrupt*/
			CLR_BIT(UCSRB_REG,UCSRB_UDRIE);
			String_Flag=0;
			/*Return Index To Zero*/
			Local_u8Counter=0;

		}


	}

}
void __vector_13 (void) __attribute__ ((signal));
void __vector_13 (void)
{
	if(String_Flag!=1)
	{
		/*Receive Data*/
		*USART_ReData=UDR_REG;
		/*Call Back NoItificate FUNC */
		CallBackNotificateFunc();
		/*Make USART SATE IDEL*/
		USART_STATE=IDEL;
		/*Disable Interrupt*/
		CLR_BIT(UCSRB_REG,UCSRB_RXCIE);
	}
	else if (String_Flag==1)
	{
		static u8 Local_u8Counter=0;
			USART_ReData[Local_u8Counter]=UDR_REG;
			_delay_ms(20);
			Local_u8Counter++;

		if(Local_u8Counter==String_Size)
		{
			/*Make USART SATE IDEL*/
			USART_STATE=IDEL;
			/*Disable Interrupt*/
			CLR_BIT(UCSRB_REG,UCSRB_RXCIE);
			/*Clear String Flag*/
			String_Flag=0;
			/*Return Index To Zero*/
			Local_u8Counter=0;
			/*Call Back NoItificate FUNC */
			CallBackNotificateFunc();

		}

	}

}


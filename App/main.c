#include "../LIB/STD_TYPES.h"
#include "../MCAL/PORT/PORT_interface.h"
#include "../MCAL/DIO/DIO_Interface.h"
#include "../MCAL/USART/USART_Interface.h"
#include "../MCAL/TIMER/TIMER_Interface.h"
#include "../MCAL/ADC/ADC_Interface.h"
#include "../MCAL/GIE/GIE_Interface.h"
#include "../MCAL/WTD/WTD_Interfac.h"
#include "../HAL/CLCD/CLCD_Interface.h"
#include <avr/delay.h>
#include <stdlib.h>
void TakeUserName(void);
void TakePassword(void);
u8 DetectUserName(void);
u8 DetectPassword(void);
u8 CompareArrays(u8* Copy_puArr1,u8* Copy_puArr2,u8 Copy_u8ArrSize);
void Buzzer(void);
void DOOR (void);
void Light(void);
void LightIntensity(void);
typedef struct
{
	const char UserName[10];
	const u32 Password;
}User_info;
User_info  Users[10]=
{       {"ahmed ",1243},
		{"alaa ",5555},
		{"mohamed ",2579},
		{"mahmoud ",1368},
		{"mostafa ",1777},
		{"nourhan ",8989},
		{"areeg ",1212},
		{"nour ",7972},
		{"sherif ",3636},
		{"ehab ",1666}
};
u8 User_Name[10];
u32 User_Pass;
u8 Try_CounterName=0,Try_CounterPass=0,Flag=0;
u8 User_Index,Var,ADC_u8Reading;
void main ()
{
	PORT_voidInit();
	USART_voidInit();
	ADC_voidInit();
	GIF_voidEnable();
	CLCD_void_Init();
	u8 Local_u8Option;

	USART_u8SendStringSynch("Welcom");
	_delay_ms(200);
	TakeUserName();
	while(1)
	{
		/*Check for Trying Count*/
		if(Try_CounterName<=3 &&Try_CounterPass<=3)
		{
			/*Check for Correct User Name */
			if( DetectUserName())
			{
				/*Check for Login Flag*/
				if(Flag==0)
				{
				/*IF User Name Is Correct Take Password*/
				TakePassword();
				}
				/*Check for Correct Password For this UserName*/
				if(DetectPassword())
				{
					/*Raised Flag for Correct Login*/
					Flag=1;
					/*Open Menu*/
					USART_u8SendStringSynch("Control your home: 1-Door	2- lighT  3-Exit ");
					USART_u8ReceiveDataSynch(&Local_u8Option);
					if(Local_u8Option=='1')
					{
						/*Call Door Function*/
						DOOR();
					}
					else if(Local_u8Option=='2')
					{
						/*Call Light Function*/
						Light();
					}
					else if(Local_u8Option=='3')
					{
						/*Exit Project */
						USART_u8SendStringSynch("Thank You");
						/*Enable WatchDog Timer*/
						WDT_voidEnable();
						/*Restart After 2.1sec */
						WDT_voidSleep(7);
						while(Local_u8Option=='3')
						{
							/*Do Nothing */
						}
					}
				}
				else
				{
					/*Wrong Password Message*/
					USART_u8SendStringSynch("Wrong Password");
					_delay_ms(300);
					/* Take Password And UserName Again*/
					TakePassword();
				}
			}
			else
			{
				/*Wrong UserName Message*/
				USART_u8SendStringSynch("Wrong UserName");
				_delay_ms(300);
				/*Take Password And UserName Again*/
				TakeUserName();
			}
		}
		else
		{
				/*Alarm Work*/
				Buzzer();
		}
	}
}
void TakeUserName(void)
{
	u8 Local_u8Count;
	if(Try_CounterName<3)
	{
		USART_u8SendStringSynch(" Enter Your User Name:");
		Local_u8Count=0;
		/*User Enter User name */
		do
		{
			Local_u8Count++;
			USART_u8ReceiveDataSynch(&User_Name[Local_u8Count-1]);
		}
		while(User_Name[Local_u8Count-1] !=' ');

		Try_CounterName++;
	}
	else
	{
		USART_u8SendStringSynch(" Sorry You have no further attempts Try Later");
		Try_CounterName++;
	}

}
void TakePassword(void)
{
	u8 Local_u8Count,Local_puPass[10];
	User_Pass=0;
	if(Try_CounterPass<3)
	{
		USART_u8SendStringSynch(" Enter Your Password :");
		/*Loop for User Enter Password */
		Local_u8Count=0;
		do
		{
			Local_u8Count++;
			USART_u8ReceiveDataSynch(&Local_puPass[Local_u8Count-1]);
		}
		while(Local_puPass[Local_u8Count-1] !=' ');
		/*Convert Password to Number*/
		User_Pass= atoi(Local_puPass);
		Try_CounterPass++;
	}
	else
	{
		USART_u8SendStringSynch(" Sorry You have no further attempts Try Later");
		Try_CounterPass++;
	}


}
u8 DetectUserName(void)
{
	u8 Local_u8Counter=0,NameFlag=0;
	while(Local_u8Counter!=10)
	{
		if(CompareArrays(&Users[Local_u8Counter].UserName,&User_Name,10))
		{
			NameFlag=1;
			User_Index=Local_u8Counter;
			return NameFlag;
		}
		else
		{
			Local_u8Counter++;
		}
	}
	return NameFlag;
}
u8 DetectPassword(void)
{
	u8 PassFlag;
	if(Users[User_Index].Password==User_Pass)
	{
		PassFlag=1;
		return PassFlag;
	}
	else
	{
		PassFlag=0;
		return PassFlag;
	}
}
u8 CompareArrays(u8* Copy_puArr1,u8* Copy_puArr2,u8 Copy_u8ArrSize)
{
	u8 Counter;
	for(Counter=0;Counter<Copy_u8ArrSize;Counter++)
	{
		if(Copy_puArr1[Counter]!=Copy_puArr2[Counter])
		{
			return 0;
		}
	}
	return 1;
}

void Buzzer(void)
{

	DIO_vSetPinValue(GROUPC,PIN_0,HIGH);
	_delay_ms(20);
	DIO_vSetPinValue(GROUPC,PIN_0,LOW);
}
void DOOR (void)
{
	TIMER1_u16SetTopValue(20000);
	TIMER1_voidInit();
	u8 Local_u8Option;
	USART_u8SendStringSynch("1-OPEN DOOR  2- CLOSE DOOR  3-Back ");
	while(Local_u8Option!='3')
	{
	USART_u8ReceiveDataSynch(&Local_u8Option);
	if(Local_u8Option=='1')
	{
		/*Open Door*/
		TIMER1_u8SetCompMatchValue(TIMER1_COMA,2000);
	}
	else if(Local_u8Option=='2')
	{
		/*Close  Door*/
		TIMER1_u8SetCompMatchValue(TIMER1_COMA,850);
	}
	}

}
void Light(void)
{
	u8 Local_u8Option ;
	USART_u8SendStringSynch("1-OPEN Light  2- CLOSE Light 3-by lightintensity  4-Back");
	while(Local_u8Option!='4')
	{
	USART_u8ReceiveDataSynch(&Local_u8Option);
	if(Local_u8Option=='1')
	{
		/*Open 4 LEDS*/
		DIO_vSetPortValue(GROUPB,0x0F);
	}
	else if(Local_u8Option=='2')
	{
		/*Close 4 LEDS*/
		DIO_vSetPortValue(GROUPB,0);
	}
	else if(Local_u8Option=='3')
	{
		/*Start ADC Conversion */
		ADC_u8StartConvAsynch(3,&ADC_u8Reading,&LightIntensity);
	}
	}
}
void LightIntensity(void)
{
	/*Convert LightIntensity to Levels*/

	if(ADC_u8Reading>=2&&ADC_u8Reading<=60)
	{
		/*Level One Open all Led*/
		DIO_vSetPortValue(GROUPB,0x0F);
	}
	else if(ADC_u8Reading>60&&ADC_u8Reading<=100)
	{
		/*Level TWO Open 3 Led*/
		DIO_vSetPortValue(GROUPB,0x07);

	}
	else if(ADC_u8Reading>100&&ADC_u8Reading<=170)
	{
		/*Level three Open 2 Led*/
		DIO_vSetPortValue(GROUPB,0x03);
	}
	else if(ADC_u8Reading>170&&ADC_u8Reading<=220)
	{
		/*Level Four Open 1 Led*/
		DIO_vSetPortValue(GROUPB,0x01);
	}
	else
	{
		/*Level Five Close All LEDS*/
		DIO_vSetPortValue(GROUPB,0);
	}
}

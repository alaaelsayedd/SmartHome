
/*********************** DRIVERNAME: LCD *************************/
/*********************** VERSION : 1.0 ***************************/
/***********************DEV_NAME:ALAA ELSAYED*********************/
/***********************DATE:7/8/2023*****************************/

#include"../../LIB/STD_TYPES.h"
#include "CLCD_Interface.h"
#include <avr/delay.h>
#include "../../MCAL/DIO/DIO_Interface.h"

void CLCD_void_Init(void)
{
	_delay_ms(40);


#if  CLCD_MODE == FOUR_BIT

	CLCD_voidSetHalfData(0b0010);
	DIO_vSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,HIGH);
	_delay_ms(2);
	DIO_vSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,LOW);

	CLCD_voidSetHalfData(0b0010);
	DIO_vSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,HIGH);
	_delay_ms(2);
	DIO_vSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,LOW);
    CLCD_voidSetHalfData(0b1000);
    DIO_vSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,HIGH);
    _delay_ms(2);
    DIO_vSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,LOW);
#elif CLCD_MODE == EIGHT_BIT

	CLCD_voidSendCommand(0b00111000);

#endif
    CLCD_voidSendCommand(0b00001100);
    CLCD_voidSendCommand(1);

}
 void CLCD_voidSendData(u8 Copy_u8Data)
 {
	DIO_vSetPinValue(CLCD_CONTROL_PORT,CLCD_RS_PIN,HIGH);
	DIO_vSetPinValue(CLCD_CONTROL_PORT,CLCD_RW_PIN,LOW);

#if  CLCD_MODE == FOUR_BIT

	CLCD_voidSetHalfData(Copy_u8Data>>4);
	DIO_vSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,HIGH);
	_delay_ms(2);
	DIO_vSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,LOW);

	CLCD_voidSetHalfData(Copy_u8Data);

	DIO_vSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,HIGH);
	_delay_ms(2);
	DIO_vSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,LOW);

#elif CLCD_MODE== EIGHT_BIT

	DIO_vSetPortValue(CLCD_DATA_PORT,Copy_u8Data);
	DIO_vSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,HIGH);
		_delay_ms(2);
	DIO_vSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,LOW);



#endif
	u8 Local_u8CheckAddress;
    Local_u8CheckAddress=CLCD_u8ReadAddress();
	 if (Local_u8CheckAddress==0x55)
	{
	CLCD_voidGoToXY(0,0);
	}
	if(Local_u8CheckAddress==15)
	{
	CLCD_voidGoToXY(1,0);
	 }

 }


 void CLCD_voidSetHalfData(u8 Copy_u8Data)
 {
	 u8 Local_u8Data;
	 Local_u8Data= READ_BIT(Copy_u8Data,0);
	 DIO_vSetPinValue(CLCD_DATA_PORT,PIN_4,Local_u8Data);
	 Local_u8Data= READ_BIT(Copy_u8Data,1);
	 DIO_vSetPinValue(CLCD_DATA_PORT,PIN_5,Local_u8Data);
	 Local_u8Data= READ_BIT(Copy_u8Data,2);
	 DIO_vSetPinValue(CLCD_DATA_PORT,PIN_6,Local_u8Data);
	 Local_u8Data= READ_BIT(Copy_u8Data,3);
	 DIO_vSetPinValue(CLCD_DATA_PORT,PIN_7,Local_u8Data);


 }
 void CLCD_voidSendCommand(u8 Copy_u8Command)
 {
	    DIO_vSetPinValue(CLCD_CONTROL_PORT,CLCD_RS_PIN,LOW);
	 	DIO_vSetPinValue(CLCD_CONTROL_PORT,CLCD_RW_PIN,LOW);
#if CLCD_MODE == FOUR_BIT
	 	CLCD_voidSetHalfData(Copy_u8Command>>4);

	 	DIO_vSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,HIGH);
	 	_delay_ms(2);
	 	DIO_vSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,LOW);
	 	CLCD_voidSetHalfData(Copy_u8Command);
	 	DIO_vSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,HIGH);
	 	_delay_ms(2);
	 	DIO_vSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,LOW);
#elif CLCD_MODE == EIGHT_BIT
	 	DIO_vSetPortValue(CLCD_DATA_PORT,Copy_u8Command);
	 	DIO_vSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,HIGH);
	 	_delay_ms(2);
	 	DIO_vSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,LOW);


#endif
 }
 void CLCD_SendString(const char * Copy_pcString)
 {
	u8 Local_u8Counter=0;
	while(Copy_pcString[Local_u8Counter]!='\0')
	{
		CLCD_voidSendData(Copy_pcString[Local_u8Counter]);
		Local_u8Counter++;
	}


 }
 void CLCD_voidGoToXY(u8 Copy_XPos,u8 Copy_YPos)
 {
	 u8 Local_u8Address;
	 if(Copy_XPos==0)
	 {
		 Local_u8Address=Copy_YPos;
	 }
	 else if(Copy_XPos==1)
	 {
		 Local_u8Address= Copy_YPos + 0x40 ;
	 }
	 CLCD_voidSendCommand( Local_u8Address | (1<<7));
 }
 void CLCD_voidWriteSpeicalChar(u8* Copy_u8puPattern,u8 Copy_u8PatternNumber,u8 Copy_u8XPos,u8 Copy_u8YPos)
 {
	 u8 Local_u8CGRAMAddress=0 ,Local_u8iterative;
	 Local_u8CGRAMAddress= Copy_u8PatternNumber*8;
	 CLCD_voidSendCommand(Local_u8CGRAMAddress+64);
	 for(Local_u8iterative=0;Local_u8iterative<8;Local_u8iterative++)
	 {
		 CLCD_voidSendData(Copy_u8puPattern[Local_u8iterative]);

	 }
	 CLCD_voidGoToXY(Copy_u8XPos,Copy_u8YPos);
	 CLCD_voidSendData(Copy_u8PatternNumber);
 }
 void CLCD_voidSendNumber(u32 Copy_u8Number)
 {
	 u32 Local_u32Number,Local_u32Result=1;
	 Local_u32Number=Copy_u8Number;
	 if ( Local_u32Number==0)
	 {
		 CLCD_voidSendData('0');
		 return;
	 }

		 while( Local_u32Number!=0)
		 {
			 Local_u32Result = (Local_u32Result*10)+(Local_u32Number%10);
			 Local_u32Number/=10;
		 }
		 do{
			 CLCD_voidSendData(Local_u32Result%10 +'0');
			 Local_u32Result/=10;
		 }
		 while(Local_u32Result!=1);
	 }
 u8   CLCD_u8ReadAddress(void){
	 u8 Local_u8Adress=0;

	 DIO_vSetPinValue(CLCD_CONTROL_PORT,CLCD_RS_PIN,LOW);
	 DIO_vSetPinValue(CLCD_CONTROL_PORT,CLCD_RW_PIN,HIGH);
#if  CLCD_MODE == EIGHT_BIT
	 DIO_vSetPortDir(CLCD_DATA_PORT,PORT_INPUT);
	 DIO_vSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,HIGH);
	 Local_u8Adress=CLCD_DATA_REG;
	_delay_ms(2);
	DIO_vSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,LOW);

   #elif CLCD_MODE == FOUR_BIT
	 DIO_vSetPinDir(CLCD_DATA_PORT,PIN_4,INPUT);
	 DIO_vSetPinDir(CLCD_DATA_PORT,PIN_5,INPUT);
	 DIO_vSetPinDir(CLCD_DATA_PORT,PIN_6,INPUT);
	 DIO_vSetPinDir(CLCD_DATA_PORT,PIN_7,INPUT);
	 DIO_vSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,HIGH);
	 Local_u8Adress=CLCD_u8ReadHalfData();
	 _delay_ms(2);
	 DIO_vSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,LOW);
	 DIO_vSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,HIGH);
	 Local_u8Adress|=(CLCD_u8ReadHalfData()>>4);
	 _delay_ms(2);
	DIO_vSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,LOW);
#endif

	 DIO_vSetPortDir(CLCD_DATA_PORT,PORT_OUTPUT);
	 return  Local_u8Adress;
 }
 u8  CLCD_u8ReadHalfData(void)
 {  u8 Local_u8Adress=0;
   Local_u8Adress|=(DIO_u8ReadPinValue(CLCD_DATA_PORT,PIN_4)<<4);
   Local_u8Adress|=(DIO_u8ReadPinValue(CLCD_DATA_PORT,PIN_5)<<5);
   Local_u8Adress|=(DIO_u8ReadPinValue(CLCD_DATA_PORT,PIN_6)<<6);
   Local_u8Adress|=(DIO_u8ReadPinValue(CLCD_DATA_PORT,PIN_7)<<7);

	 return  Local_u8Adress;
 }




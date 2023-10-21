/*************  DRIVER : DIO              *******************
**************  DEV_NAME : ALAA            ******************
**************  DATE :19 JUNE 2023         ******************
**************  SOFTWARE VERSION : V1.0    ******************
************************************************************/

#include "../DIO/DIO_Interface.h"



void DIO_vSetPinDir(u8 Copy_u8Group,u8 Copy_u8PIN,u8 Copy_u8Direction)
{
	if (Copy_u8Direction==OUTPUT)
	{
	switch (Copy_u8Group)
	{
		case GROUPA:  
		      SET_BIT(DDRA_REG,Copy_u8PIN);
			  break;
		case GROUPB:  
		      SET_BIT(DDRB_REG,Copy_u8PIN);
			  break;
        case GROUPC:  
		      SET_BIT(DDRC_REG,Copy_u8PIN);
			  break;
        case GROUPD:  
		      SET_BIT(DDRD_REG,Copy_u8PIN);
			  break;			  
			  
	}
	}
	else 
	{
		switch (Copy_u8Group)
	{
		case GROUPA:  
		      CLR_BIT(DDRA_REG,Copy_u8PIN);
			  break;
		case GROUPB:  
		      CLR_BIT(DDRB_REG,Copy_u8PIN);
			  break;
        case GROUPC:  
		      CLR_BIT(DDRC_REG,Copy_u8PIN);
			  break;
        case GROUPD:  
		      CLR_BIT(DDRD_REG,Copy_u8PIN);
			  break;			  
			  
	}
	}
	
}
void DIO_vSetPinValue(u8 Copy_u8Group,u8 Copy_u8PIN,u8 Copy_u8Value)
{
	if (Copy_u8Value==HIGH)
	{
	switch (Copy_u8Group)
	{
		case GROUPA:  
		      SET_BIT(PORTA_REG,Copy_u8PIN);
			  break;
		case GROUPB:  
		      SET_BIT(PORTB_REG,Copy_u8PIN);
			  break;
        case GROUPC:  
		      SET_BIT(PORTC_REG,Copy_u8PIN);
			  break;
        case GROUPD:  
		      SET_BIT(PORTD_REG,Copy_u8PIN);
			  break;			  
			  
	}
	}
	else 
	{
		switch (Copy_u8Group)
	{
		case GROUPA:  
		      CLR_BIT(PORTA_REG,Copy_u8PIN);
			  break;
		case GROUPB:  
		      CLR_BIT(PORTB_REG,Copy_u8PIN);
			  break;
        case GROUPC:  
		      CLR_BIT(PORTC_REG,Copy_u8PIN);
			  break;
        case GROUPD:  
		      CLR_BIT(PORTD_REG,Copy_u8PIN);
			  break;			  
			  
	}
	}
}


void DIO_vSetPortDir(u8 Copy_u8Group,u8 Copy_u8Direction)
{
	switch (Copy_u8Group)
	{
		case GROUPA:  
		      DDRA_REG=Copy_u8Direction;
			  break;
		case GROUPB:  
		      DDRB_REG=Copy_u8Direction;
			  break;
        case GROUPC:  
		      DDRC_REG=Copy_u8Direction;
			  break;
        case GROUPD:  
		     DDRD_REG=Copy_u8Direction;
			  break;	
	}
	
}
void DIO_vSetPortValue(u8 Copy_u8Group,u8 Copy_u8Value)
{
	switch (Copy_u8Group)
	{
		case GROUPA:  
		      PORTA_REG=Copy_u8Value;
			  break;
		case GROUPB:  
		      PORTB_REG=Copy_u8Value;
			  break;
        case GROUPC:  
		      PORTC_REG=Copy_u8Value;
			  break;
        case GROUPD:  
		     PORTD_REG=Copy_u8Value;
			  break;	
	}
}
u8 DIO_u8ReadPinValue(u8 Copy_u8Group,u8 Copy_u8PIN )
{
	u8 Local_u8PinValue;
	switch (Copy_u8Group)
	{
		case GROUPA:  
		      Local_u8PinValue=READ_BIT(PINA_REG,Copy_u8PIN);
			  break;
		case GROUPB:  
		      Local_u8PinValue=READ_BIT(PINB_REG,Copy_u8PIN);
			  break;
        case GROUPC:  
		      Local_u8PinValue=READ_BIT(PINC_REG,Copy_u8PIN);
			  break;
        case GROUPD:  
		     Local_u8PinValue=READ_BIT(PIND_REG,Copy_u8PIN);
			  break;	
	}
	return Local_u8PinValue;
	
}
void DIO_vTogglePin(u8 Copy_u8Group,u8 Copy_u8PIN)
{
	switch (Copy_u8Group)
	{
		case GROUPA:  
		      TOGGLE_BIT(PORTA_REG,Copy_u8PIN);
			  break;
		case GROUPB:  
		     TOGGLE_BIT(PORTB_REG,Copy_u8PIN);
			  break;
        case GROUPC:  
		      TOGGLE_BIT(PORTC_REG,Copy_u8PIN);
			  break;
        case GROUPD:  
		     TOGGLE_BIT(PORTD_REG,Copy_u8PIN);
			  break;	
	}
}

/********************DRIVER : WatchDog           **********************
*********************DEV_NAME : ALAA          **********************
*********************DATE :15 OCT 2023        **********************
*********************SOFTWARE VERSION : V1.0  **********************
********************************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.H"
#include"WTD_Interfac.h"
#include"WTD_Register.h"
void WDT_voidSleep (u8 Copy_u8Sleep)
{
	WDTCR_REG&=0b11111000;
	WDTCR_REG|=Copy_u8Sleep;
}
void WDT_voidEnable (void)
{
	SET_BIT(WDTCR_REG,3);
}
void WDT_voidDisable (void )
{
	WDTCR_REG|=0b00011000;
	WDTCR_REG=0;
}

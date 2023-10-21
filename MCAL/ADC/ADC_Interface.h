/*************  DRIVER : ADC             *******************
**************  DEV_NAME : ALAA            ******************
**************  DATE :26 AUG 2023         ******************
**************  SOFTWARE VERSION : V2.0    ******************
************************************************************/

#ifndef ADC_INTERFACE_H_
#define ADC_ITERFACE_H_
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.H"

#include "ADC_Private.h"
#include "ADC_Register.h"
#include "ADC_Config.h"

void ADC_voidInit(void);

u8 ADC_u8StartConvSynch(u8 Copy_u8Channel, u8* Copy_puRead);

u8 ADC_u8StartConvAsynch(u8 Copy_u8Channel, u8* Copy_puRead,void(*Copy_pvNotificateFunc)(void));

u8 ADC_u8StartAsynchChainConversion(struct ADC_Chain_t *Chain);

s32 Map(s32 InputMin,s32 InputMax,s32 OutputMin,s32 OutputMax,s32 InputVar);




#endif

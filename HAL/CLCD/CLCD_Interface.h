/*********************** DRIVERNAME: LCD *************************/
/*********************** VERSION : 1.0 ***************************/
/***********************DEV_NAME:ALAA ELSAYED*********************/
/***********************DATE:7/8/2023*****************************/
#ifndef CLCD_INTERFACE_H
#define CLCD_INTERFACE_H
#include "CLCD_Config.h"


 void CLCD_void_Init(void);
 void CLCD_voidSendData(u8 Copy_u8Data);
 void CLCD_voidSetHalfData(u8 Copy_u8Data);
 void CLCD_voidSendCommand(u8 Copy_u8Command);
 void CLCD_voidGoToXY(u8 Copy_X,u8 Copy_Y);
 void CLCD_voidSendNumber(u32 Copy_u8Number);
 u8   CLCD_u8ReadAddress(void);
 u8  CLCD_u8ReadHalfData(void);

#endif

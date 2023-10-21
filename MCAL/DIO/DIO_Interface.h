/*************  DRIVER : DIO              *******************
**************  DEV_NAME : ALAA            ******************
**************  DATE :19 JUNE 2023         ******************
**************  SOFTWARE VERSION : V1.0    ******************
************************************************************/




#ifndef DIO_INTERFACE_H
#define DIO_ITERFACE_H
/******************************** includes ************************************************************/
 #include "../../LIB/BIT_MATH.H"
 #include"../../LIB/STD_TYPES.h"
 #include "../DIO/DIO_Config.h"
 #include "../DIO/DIO_Private.h"
 /**********************************fuction prtotype**************************************************/
 void DIO_vSetPinDir(u8 Copy_u8Group,u8 Copy_u8PIN,u8 Copy_u8Direction);
 void DIO_vSetPinValue(u8 Copy_u8Group,u8 Copy_u8PIN,u8 Copy_u8Value);
 void DIO_vSetPortDir(u8 Copy_u8Group,u8 Copy_u8Direction);
 void DIO_vSetPortValue(u8 Copy_u8Group,u8 Copy_u8Value);
 u8 DIO_u8ReadPinValue(u8 Copy_u8Group,u8 Copy_u8PIN );
 void DIO_vTogglePin(u8 Copy_u8Group,u8 Copy_u8PIN);

 
 
 





#endif

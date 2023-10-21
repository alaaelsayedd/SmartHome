/********************DRIVER : USART           **********************
*********************DEV_NAME : ALAA          **********************
*********************DATE :18 SEP 2023        **********************
*********************SOFTWARE VERSION : V1.0  **********************
********************************************************************/
#ifndef MCAL_USART_USART_INTERFACE_H_
#define MCAL_USART_USART_INTERFACE_H_

void USART_voidInit(void);

u8 USART_u8SendDataSynch(u8 Copy_u8Data);

u8 USART_u8ReceiveDataSynch(u8* Copy_puData);

u8 USART_u8SendDataAsynch(u8 Copy_u8Data,void(*NotificateFunc)(void));

u8 USART_u8ReceiveDataAsynch(u8* Copy_u8Data,void(*NotificateFunc)(void));

u8 USART_u8SendStringSynch( const char *Copy_puString);

u8 USART_u8ReceiveStringSynch( char *Copy_puString,u8 Copy_u8StringSize);

u8 USART_u8SendStringAsynch( char *Copy_puString,void(*NotificateFunc)(void));

u8 USART_u8ReceiveStringAsynch( char *Copy_puString,u8 Copy_u8StringSize,void(*NotificateFunc)(void));
#endif/*MCAL_USART_USART_INTERFACE_H_*/

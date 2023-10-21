/********************DRIVER : USART           **********************
*********************DEV_NAME : ALAA          **********************
*********************DATE :18 SEP 2023        **********************
*********************SOFTWARE VERSION : V1.0  **********************
********************************************************************/
#ifndef MCAL_USART_USART_PRIVATE_H_
#define MCAL_USART_USART_PRIVATE_H_

#define ENABLE     1
#define DISABLE    0
#define ASYNCH     0
#define SYNCH      1
#define UCSRC_PARITY_MASK  0b11001111
#define PARITY_DISABLED  0
#define PARITY_EVEN      32
#define PARITY_ODD       48
#define ONE       1
#define TWO       2
#define UCSRC_UCSZ_MASK   0b11111001
#define  FIVE_BIT          0
#define  SIX_BIT           2
#define  SEVEN_BIT         4
#define  EIGHT_BIT         6
#define  NINE_BIT          7

#define TR_RISING_RE_FALLING  1
#define TR_FALLING_RE_RISING  2
#define IDEL 0
#define BUSY  1


#endif/*MCAL_USART_USART_PRIVATE_H_*/

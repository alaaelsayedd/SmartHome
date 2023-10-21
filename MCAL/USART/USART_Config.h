/********************DRIVER : USART           **********************
*********************DEV_NAME : ALAA          **********************
*********************DATE :18 SEP 2023        **********************
*********************SOFTWARE VERSION : V1.0  **********************
********************************************************************/
#ifndef MCAL_USART_USART_CONFIG_H_
#define MCAL_USART_USART_CONFIG_H_
/*
 * Double the USART Transmission Speed:
 * 1- ENABLE
 * 2- DISABLE
 */

#define USART_DOUBLE_SPEED   ENABLE
/*
 * RX Complete Interrupt Enable:
 * TX Complete Interrupt Enable:
 * USART Data Register Empty Interrupt Enable:
 * 1- ENABLE
 * 2- DISABLE
 */
#define USART_RX_INTERRUPT   DISABLE
#define USART_TX_INTERRUPT   DISABLE
#define USART_DRE_INTERRUPT  DISABLE

/*Choose USART Receiver or Transmitter or both:
 * 1- ENABLE
 * 2- DISABLE
 */
#define USART_TRANSMITTER   ENABLE
#define USART_RECEVIER      ENABLE

/*Choose USART Mode :
 * 1- ASYNCH
 * 2- SYNCH
 * */

#define USART_MODE_SELECT     ASYNCH

#if USART_MODE_SELECT==SYNCH
/*
 * Choose CLOCK Polarity
 * 1- TR_RISING_RE_FALLING
 * 2- TR_FALLING_RE_RISING
 * */
#define USART_CLOCK_POLARITY   TR_RISING_RE_FALLING

#endif
/*Choose Parity Mode
 * 1- PARITY_DISABLED
 * 2- PARITY_EVEN
 * 3- PARITY_ODD
 * */
#define USART_PARITY_MODE   PARITY_DISABLED
/*Select Stop bit 1bit or Two Bit :
 * 1- ONE
 * 2- TWO
 * */
#define USART_STOP_BIT   ONE
/*
 * Choose  Character Size
 * 1- FIVE_BIT
 * 2- SIX_BIT
 * 3- SEVEN_BIT
 * 4- EIGHT_BIT
 * 5- NINE_BIT
 * */
#define  USART_CHARACTER_SIZE    EIGHT_BIT

#define USART_TIMEOUT     5000000



#endif/*MCAL_USART_USART_CONFIG_H_*/


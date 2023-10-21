/*************  DRIVER : TIMER             *******************
**************  DEV_NAME : ALAA            ******************
**************  DATE :5 SEP 2023         ******************
**************  SOFTWARE VERSION : V1.0    ******************
************************************************************/

#ifndef MCAL_TIMER_PRIVATE_H_
#define MCAL_TIMER_PRIVATE_H_


#define NORMAL               0
#define PWM_PHASE_CORRECT    1
#define CTC                  2
#define FAST_PWM             3

#define FAST_PWM_TOP_VALUE    4
#define CTC_TOP_VALUE         5
#define PWM_PHASE_CORRECT_TOP_VALUE   6

#define TCCR0_COM_MASK   0b11001111
#define TCCR_PRES_MASK   0b11111000
#define TCCR2_COM_MASK    0b11001111

#define PRES_NO_DIV      1
#define PRES_DIVBY_8     2
#define PRES_DIVBY_64    3
#define PRES_DIVBY_256   4
#define PRES_DIVBY_1024  5




#define  SET_ONCOMP    48
#define  CLEAR_ONCOMP  32
#define  TOGGLE_ONCOMP 16
#define  SET_ONCOMP_CLR_ONTOP  48
#define  CLR_ONCOMP_SET_ONTOP  32

#define  SET_UP_CLR_DOWM 0   48
#define  CLR_UP_SET_DOWM 1   32
#define   ENABLE   0
#define   DISABLE  1
/*Set COM1A CTC OCR1A behavior*/
#define TCCR1A_COM1A_MASK   0b00001111
#define TCCR1A_COM1B_MASK   0b00001111

#define  COM1A_SET_ONCOMP     192
#define  COM1A_CLEAR_ONCOMP   128
#define  COM1A_TOGGLE_ONCOMP  64

#define COM1A_SET_ONCOMP_CLR_ONTOP     192
#define COM1A_CLR_ONCOMP_SET_ONTOP     128
#define COM1A_SET_UP_CLR_DOWM    192
#define COM1A_CLR_UP_SET_DOWM    128



/*Set COM1b CTC OCR1B behavior*/
#define  COM1B_SET_ONCOMP     48
#define  COM1B_CLEAR_ONCOMP   32
#define  COM1B_TOGGLE_ONCOMP  16


#define COM1B_SET_UP_CLR_DOWM    48
#define COM1B_CLR_UP_SET_DOWM    32

#define COM1B_SET_ONCOMP_CLR_ONTOP     48
#define COM1B_CLR_ONCOMP_SET_ONTOP     32


#define  RISING_EDGE  0
#define  FALLING_EDGE 1


#endif/*MCAL_TIMER_PRIVATE_H_*/

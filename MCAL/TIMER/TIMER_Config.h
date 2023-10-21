/*************  DRIVER : TIMER             *******************
**************  DEV_NAME : ALAA            ******************
**************  DATE :5 SEP 2023         ******************
**************  SOFTWARE VERSION : V1.0    ******************
************************************************************/

#ifndef MCAL_TIMER_CONFIG_H_
#define MCAL_TIMER_CONFIG_H_

#define TIMER_0    0
#define TIMER_1    1
#define TIMER_2    2

#define TIMER1_COMA    0
#define TIMER1_COMB    1

#define TIMER_COUNTER0_OVERFLOW  0
#define TIMER_COUNTER1_OVERFLOW  1
#define TIMER_COUNTER2_OVERFLOW  2
#define TIMER_COUNTER0_COM       3
#define TIMER_COUNTER1_COMA      4
#define TIMER_COUNTER1_COMB      5
#define TIMER_COUNTER2_COM       6
#define TIMER_COUNTER1_ICU       7



/*******************************TIMER0/2 Configuartion******************************************/
/*Choose Timer mode
 * 1- NORMAL
 * 2- PWM_PHASE_CORRECT
 * 3- CTC
 * 4- FAST_PWM
 * */
#define TIMER0_MODE    CTC
#define TIMER2_MODE    FAST_PWM
/*control the Output Compare pin (OC0) (OC2)behavior*/

/*
 * 1- SET_ONCOMP
 * 2- CLEAR_ONCOMP
 * 3- TOGGLE_ONCOMP
 * 4- NORMAL
 *
 * */
#define TIMER0_CTC    NORMAL


/*
 * 1- SET_ONCOMP_CLR_ONTOP
 * 2- CLR_ONCOMP_SET_ONTOP
 * 3- NORMAL
 * */
#define TIMER0_FASTPWM   NORMAL
/*
 * 1- SET_UP_CLR_DOWM
 * 2- CLR_UP_SET_DOWM
 * 3- NORMAL
 * */


#define TIMER0_PWM_PHASE_CORRECT   NORMAL
/*
 * Choose TIMER0/2 Prescaler:
 *
 * 1-  PRES_NO_DIV
 * 2-  PRES_DIVBY_8
 * 3-  PRES_DIVBY_64
 * 4-  PRES_DIVBY_256
 * 5-  PRES_DIVBY_1024
 */

#define  TIMER0_PRES   PRES_DIVBY_64
#define  TIMER2_PRES   PRES_DIVBY_8
/*
 * 1- ENABLE
 * 2- DISABLE
 * */
#define TIMER0_OVERFLOW_INTERRUPT  DISABLE
#define TIMER0_COMP_INTERRUPT      ENABLE


#define TIMER2_OVERFLOW_INTERRUPT  DISABLE
/*
 * 1- ENABLE
 * 2- DISABLE
 * */

#define TIMER2_COMP_INTERRUPT  DISABLE
/**************************************************************************************************************************/


/*
 * Choose Timer1 mode
 *  1- NORMAL
 *  2- PWM_PHASE_CORRECT
 *  3- CTC
 *  4- FAST_PWM
 *  5- FAST_PWM_TOP_VALUE
 *  6- PWM_PHASE_CORRECT_TOP_VALUE
 *  7- CTC_TOP_VALUE
 *
 * */
#define TIMER1_MODE   FAST_PWM_TOP_VALUE
/*
 * Choose TIMER1 Prescaler:
 *
 * 1-  PRES_NO_DIV
 * 2-  PRES_DIVBY_8
 * 3-  PRES_DIVBY_64
 * 4-  PRES_DIVBY_256
 * 5-  PRES_DIVBY_1024
 */

#define  TIMER1_PRES   PRES_DIVBY_8

/*
 * 1- ENABLE
 * 2- DISABLE
 * */
#define TIMER1_COM1A_CHANNEL  ENABLE
#define TIMER1_COM1B_CHANNEL  DISABLE
/*control the Output Compare pin (OC1A) behavior*/

/*
 * 1- COM1A_SET_ONCOMP
 * 2- COM1A_CLEAR_ONCOMP
 * 3- COM1A_TOGGLE_ONCOMP
 * 4- NORMAL
 *
 * */
#define TIMER1_COM1A_CTC    NORMAL


/*
 * 1- COM1A_SET_ONCOMP_CLR_ONTOP
 * 2- COM1A_CLR_ONCOMP_SET_ONTOP
 * 3- NORMAL
 * */
#define TIMER1_COM1A_FASTPWM     COM1A_CLR_ONCOMP_SET_ONTOP
/*
 * 1- COM1A_SET_UP_CLR_DOWM
 * 2- COM1A_CLR_UP_SET_DOWM
 * 3- NORMAL
 * */


#define TIMER1_COM1A_PWM_PHASE_CORRECT   NORMAL
/*control the Output Compare pin (OC1B) behavior*/

/*
 * 1- COM1B_SET_ONCOMP
 * 2- COM1B_CLEAR_ONCOMP
 * 3- COM1B_TOGGLE_ONCOMP
 * 4- NORMAL
 *
 * */
#define TIMER1_COM1B_CTC    NORMAL


/*
 * 1- COM1B_SET_ONCOMP_CLR_ONTOP
 * 2- COM1B_CLR_ONCOMP_SET_ONTOP
 * 3- NORMAL
 * */
#define TIMER1_COM1B_FASTPWM      COM1B_CLR_ONCOMP_SET_ONTOP
/*
 * 1- COM1B_SET_UP_CLR_DOWM
 * 2- COM1B_CLR_UP_SET_DOWM
 * 3- NORMAL
 * */


#define TIMER1_COM1B_PWM_PHASE_CORRECT   NORMAL
/*
 * 1- ENABLE
 * 2- DISABLE
 * */
#define TIMER1_OVERFLOW_INTERRUPT  DISABLE
/*
 * 1- ENABLE
 * 2- DISABLE
 * */
#define TIMER1_COMPA_INTERRUPT  DISABLE
/*
 * 1- ENABLE
 * 2- DISABLE
 * */
#define TIMER1_COMPB_INTERRUPT  DISABLE
/*
 * TIMER 1 ICU Trigger Edge
 * 1- RISING_EDGE
 * 2- FALLING_EDGE
 * */
#define  TIMER1_ICU_MODE   RISING_EDGE
/*
 * 1- ENABLE
 * 2- DISABLE
 * */
#define TIMER1_ICU_INTERRUPT  DISABLE



#endif /* MCAL_TIMER_CONFIG_H_*/


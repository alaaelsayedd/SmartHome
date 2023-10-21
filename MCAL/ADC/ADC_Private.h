/*************  DRIVER : ADC             *******************
**************  DEV_NAME : ALAA            ******************
**************  DATE :26 AUG 2023         ******************
**************  SOFTWARE VERSION : V2.0    ******************
************************************************************/

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_
#define ADMUX_REF_VOLT_MASK  0b00111111
#define AREF_EXT      0
#define AVCC          64
#define AREF_INTERNAL 192
#define ENABLE    1
#define DISABLE   0
#define ADCSRA_ADPS_MASK  0b11111000
/*Prescaler Select Bits_DIV */
#define ADPS_DIV_BY2     0
#define ADPS_DIV_BY4     2
#define ADPS_DIV_BY8     3
#define ADPS_DIV_BY16    4
#define ADPS_DIV_BY32    5
#define ADPS_DIV_BY64    6
#define ADPS_DIV_BY128   7

#define SFIOR_ADTS_MASK   0b00011111

#define FREE_RUNNING                     0
#define ANALOG_COMPARATOR                32
#define EXTERNAL_INTERRUPT_REQUEST_0     64
#define TIMER_COUNTER0_COMPARE_MATCH     96
#define TIMER_COUNTER0_OVERFLOW          128
#define TIMER_COUNTER_COMPARE_MATCH_B    160
#define TIMER_COUNTER1_OVERFLOW          192
#define TIMER_COUNTER1_CAPTURE_EVENT     224

#define ADMUX_MUX_MASK  0b11100000

#define ADC0        0
#define ADC1        1
#define ADC2        2
#define ADC3        3
#define ADC4        4
#define ADC5        5
#define ADC6        6
#define ADC7        7





#endif

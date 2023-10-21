/*************  DRIVER : TIMER             *******************
**************  DEV_NAME : ALAA            ******************
**************  DATE :5 SEP 2023         ******************
**************  SOFTWARE VERSION : V1.0    ******************
************************************************************/

#ifndef MCAL_TIMER_REGISTER_H_
#define MCAL_TIMER_REGISTER_H_

#define OCR0_REG     *((volatile u8*)0x5C)

#define TCCR0_REG    *((volatile u8*)0x53)

#define TCCR0_FOC0       7
#define TCCR0_WGM00      6
#define TCCR0_COM01      5
#define TCCR0_COM00      4
#define TCCR0_WGM01      3
#define TCCR0_CS02       2
#define TCCR0_CS01       1
#define TCCR0_CS00       0
#define TCNT0_REG    *((volatile u8*)0x52)

#define TCCR1A_REG   *((volatile u8*)0x4F)
#define TCCR1A_COM1A1     7
#define TCCR1A_COM1A0     6
#define TCCR1A_COM1B1     5
#define TCCR1A_COM1B0     4
#define TCCR1A_FOC1A      3
#define TCCR1A_FOC1B      2
#define TCCR1A_WGM11      1
#define TCCR1A_WGM10      0

#define TCCR1B_REG   *((volatile u8*)0x4E)
#define TCCR1B_ICNC1     7
#define TCCR1B_ICES1     6
#define TCCR1B_WGM13     4
#define TCCR1B_WGM12     3
#define TCCR1B_CS12      2
#define TCCR1B_CS11      1
#define TCCR1B_CS10      0

#define TIMSK_REG    *((volatile u8*)0x59)
#define TIMSK_OCIE2    7
#define TIMSK_TOIE2    6
#define TIMSK_TICIE1   5
#define TIMSK_OCIE1A   4
#define TIMSK_OCIE1B   3
#define TIMSK_TOIE1    2
#define TIMSK_OCIE0    1
#define TIMSK_TOIE0    0

#define TIFR_REG     *((volatile u8*)0x58)
#define TIFR_OCF2      7
#define TIFR_TOV2      6
#define TIFR_ICF1      5
#define TIFR_OCF1A     4
#define TIFR_OCF1B     3
#define TIFR_TOV1      2
#define TIFR_OCF0      1
#define TIFR_TOV0      0


#define TCCR2_REG   *((volatile u8*)0x45)
#define TCCR2_FOC2     7
#define TCCR2_WGM20    6
#define TCCR2_COM21    5
#define TCCR2_COM20    4
#define TCCR2_WGM21    3
#define TCCR2_CS22     2
#define TCCR2_CS21     1
#define TCCR2_CS20     0

#define TCNT2_REG   *((volatile u8*)0x44)

#define OCR2_REG    *((volatile u8*)0x43)

#define TCNT1_REG   *((volatile u16*)0x4C)

#define OCR1A_REG   *((volatile u16*)0x4A)

#define OCR1B_REG   *((volatile u16*)0x48)

#define ICR1_REG    *((volatile u16*)0x46)







#endif/*MCAL_TIMER_REGISTER_H_*/

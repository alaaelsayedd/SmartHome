/*************  DRIVER : ADC             *******************
**************  DEV_NAME : ALAA            ******************
**************  DATE :26 AUG 2023         ******************
**************  SOFTWARE VERSION : V2.0    ******************
************************************************************/

#ifndef MCAL_ADC_REGISTER_H_
#define MCAL_ADC_REGISTER_H_
#define ADMUX_REG   *((volatile u8*) 0x27)
// Reference Selection Bits
#define ADMUX_REFS1    7
#define ADMUX_REFS0    6
//ADC Left Adjust Result
#define ADMUX_ADLAR    5

#define ADCSRA_REG  *((volatile u8*) 0x26)
#define ADCSRA_ADEN    7   //ADC Enable
#define ADCSRA_ADSC    6   //ADC Start Conversion
#define ADCSRA_ADATE   5   // ADC Auto Trigger Enable
#define ADCSRA_ADIF    4   //ADC Interrupt Flag
#define ADCSRA_ADIE    3   // ADC Interrupt Enable
//ADC Prescaler Select Bits
#define ADCSRA_ADPS2   2
#define ADCSRA_ADPS1   1
#define ADCSRA_ADPS0   0

#define ADCH_REG    *((volatile u8*) 0x25)
#define ADCL_REG    *((volatile u8*) 0x24)
#define SFIOR_REG   *((volatile u8*) 0x50)



#endif/*MCAL_ADC_REGISTER_H_*/

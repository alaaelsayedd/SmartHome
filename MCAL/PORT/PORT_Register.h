#ifndef MCAL_PORT_PORT_REGISTER_H_
#define MCAL_PORT_PORT_REGISTER_H_

#define DDRA_REG   *((volatile u8*)0x3A)
#define PORTA_REG  *((volatile u8*)0x3B)


#define DDRB_REG   *((volatile u8*)0x37)
#define PORTB_REG  *((volatile u8*)0x38)


#define DDRC_REG   *((volatile u8*)0x34)
#define PORTC_REG  *((volatile u8*)0x35)


#define DDRD_REG   *((volatile u8*)0x31)
#define PORTD_REG  *((volatile u8*)0x32)


#endif /* MCAL_PORT_PORT_REGISTER_H_ */
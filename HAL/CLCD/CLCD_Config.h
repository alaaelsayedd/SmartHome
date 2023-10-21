/*********************** DRIVERNAME: LCD *************************/
/*********************** VERSION : 1.0 ***************************/
/***********************DEV_NAME:ALAA ELSAYED*********************/
/***********************DATE:7/8/2023*****************************/
#ifndef CLCD_CONFIG_H
#define CLCD_CONFIG_H


#define CLCD_DATA_PORT    GROUPA
#define CLCD_CONTROL_PORT GROUPA
#define CLCD_DATA_REG   PINA_REG
#define CLCD_RS_PIN    PIN_0
#define CLCD_RW_PIN    PIN_1
#define CLCD_E_PIN     PIN_2
#define FOUR_BIT   0
#define EIGHT_BIT  1
/*
 * CLCD MODE
 * 1- FOUR_BIT
 * 2- EIGHT_BI
 */
#define CLCD_MODE  FOUR_BIT



#endif

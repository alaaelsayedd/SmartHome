/*
 * GIF_Prog.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: zas
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.H"
#include "../DIO/DIO_Interface.h"
#include "GIE_Interface.h"
#include "GIE_Register.h"

void GIF_voidEnable(void)
{
	SET_BIT(SRIC_REG,SRIC_I);
}
 void GIF_voidDisable(void)
 {
	 CLR_BIT(SRIC_REG,SRIC_I);
 }

/*
 * BIT_MATH.H
 *
 *  Created on: ??þ/??þ/????
 *      Author: zas
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(REG,BIT_NO)    REG |=(1<<BIT_NO)
#define CLR_BIT(REG,BIT_NO)    REG &=~((1<<BIT_NO))
#define TOGGLE_BIT(REG,BIT_NO) REG ^=(1<<BIT_NO)
#define READ_BIT(REG,BIT_NO)   ((REG>>BIT_NO)&1)

//s32 Map(s32 InputMin,s32 InputMax,s32 OutputMin,s32 OutputMax,s32 InputVar);

#endif /* BIT_MATH_H_ */

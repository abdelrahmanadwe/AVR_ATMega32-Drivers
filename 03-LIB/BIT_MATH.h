/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<   BIT_MATH.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdelrahman Adwe Ali 
 *  Layer  : LIB
 *
 *
 */
 
#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(var,bit)    var|=(1<<bit)
#define CLR_BIT(var,bit)    var&=(~(1<<bit))
#define TOG_BIT(var,bit)    var^=(1<<bit)
#define GET_BIT(var,bit)    (var>>bit)&1

#define IS_BIT_SET(var,bit)   (var>>bit)&1
#define IS_BIT_CLR(var,bit) !((var>>bit)&1)

#endif /* BIT_MATH_H_ */

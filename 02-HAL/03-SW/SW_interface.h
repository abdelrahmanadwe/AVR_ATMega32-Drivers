/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     SW_interface.h     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdelrahman Adwe Ali 
 *  Layer  : HAL
 *  SWC    : SW
 *
 */
 
#ifndef SW_INTERFACE_H_
#define SW_INTERFACE_H_
 
#define SW_PRESSED     1
#define SW_NOT_PRESSED 0
 
#define SW_INT_PUll_UP   0
#define SW_EXT_PUll_UP   1
#define SW_EXT_PUll_DOWN 2
#define SW_FLAUTING      3
 
typedef struct 
{
	u8 Port       ;
	u8 Pin        ;
	u8 Pull_State ;
	
}SW_Data;
 
 
void SW_voidInit      (SW_Data SW_Config );
u8 SW_u8GetPressed    (SW_Data SW_Config );
 
#endif /* SW_INTERFACE_H_ */
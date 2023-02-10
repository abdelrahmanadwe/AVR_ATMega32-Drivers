/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     DIO_interface.h     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdelrahman Adwe Ali 
 *  Layer  : HAL
 *  SWC    : LED
 *
 */
 
#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_
 
#define ACTIVE_HIGH 1
#define ACTIVE_LOW  0

#define LED_PORTA 0
#define LED_PORTB 1
#define LED_PORTC 2
#define LED_PORTD 3

#define LED_PIN0 0
#define LED_PIN1 1
#define LED_PIN2 2
#define LED_PIN2 3
#define LED_PIN4 4
#define LED_PIN5 5
#define LED_PIN6 6
#define LED_PIN7 7
 
 typedef struct
 {
	 u8 Port         ;                /* [LED_PORTA , LED_PORTB , LED_PORTC , LED_PORTD]                                         */
	 u8 Pin          ;                /* [LED_PIN0 , LED_PIN1 , LED_PIN2 , LED_PIN3 , LED_PIN4 , LED_PIN5 , LED_PIN6 , LED_PIN7] */
	 u8 Active_State ;                /* [ACTIVE_HIGH , ACTIVE_LOW]                                                              */
	 
 }LED_Data;
 
void LED_voidInit       (LED_Data LED_Configuration);
void LED_voidOn         (LED_Data LED_Configuration);
void LED_voidOff        (LED_Data LED_Configuration);
void LED_voidToggle     (LED_Data LED_Configuration);
 
 
#endif /* LED_INTERFACE_H_ */
/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<   DIO_interface.h   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdelrahman Adwe Ali 
 *  Layer  : MCAL
 *  SWC    : GPIO/DIO
 *
 */
 
#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_
 
 typedef enum{
	 
	DIO_NOK,
	DIO_OK
	
 }DIO_Status;
 
#define DIO_PIN_HIGH 1
#define DIO_PIN_LOW  0

#define DIO_PORT_HIGH 0xFF
#define DIO_PORT_LOW  0

#define DIO_PIN_OUTPUT 1
#define DIO_PIN_INPUT  0

#define DIO_PORT_OUTPUT 0xFF
#define DIO_PORT_INPUT  0

#define DIO_PORTA 0
#define DIO_PORTB 1
#define DIO_PORTC 2
#define DIO_PORTD 3

#define DIO_PIN0 0
#define DIO_PIN1 1
#define DIO_PIN2 2
#define DIO_PIN2 3
#define DIO_PIN4 4
#define DIO_PIN5 5
#define DIO_PIN6 6
#define DIO_PIN7 7

								/* for PINS */
DIO_Status DIO_enumSetPinDirection (u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8Directoin);
DIO_Status DIO_enumSetPinValue     (u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8Value    );
DIO_Status DIO_enumGetPinValue     (u8 Copy_u8Port , u8 Copy_u8Pin , u8 * Copy_PtrVar   );
DIO_Status DIO_enumTogglePinValue     (u8 Copy_u8Port , u8 Copy_u8Pin ,                    );

								/* for PORTS */
DIO_Status DIO_enumSetPortDirection(u8 Copy_u8Port , u8 Copy_u8Directoin );
DIO_Status DIO_enumSetPortValue    (u8 Copy_u8Port , u8 Copy_u8Value     );
DIO_Status DIO_enumGetPortValue    (u8 Copy_u8Port , u8 * Copy_PtrVar    );
DIO_Status DIO_enumTogglePortValue    (u8 Copy_u8Port                       );

#endif /* DIO_INTERFACE_H_ */

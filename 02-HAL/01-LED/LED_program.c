/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     DIO_interface.h     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdelrahman Adwe Ali 
 *  Layer  : HAL
 *  SWC    : LED
 *
 */
 
#include <Util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "LED_interface.h"


/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                   This function initialize the Pin which connected to led as output pin
 *                           *-----------------------------------------------------------------------*
 * Parameters :  
			=>LED_Configuration: struct(LED_Tupe)
				-> Port         [LED_PORTA , LED_PORTB , LED_PORTC , LED_PORTD]
				-> Pin          [LED_PIN0 , LED_PIN1 , LED_PIN2 , LED_PIN3 , LED_PIN4 , LED_PIN5 , LED_PIN6 , LED_PIN7]
				-> Active_State [ACTIVE_HIGH , ACTIVE_LOW]
			
 * return : void     
 */

void LED_voidInit( LED_Type LED_Configuration )
{
	
	DIO_enumSetPinDirection( LED_Configuration.Port , LED_Configuration.Pin , DIO_PIN_OUTPUT );
	
}


/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                   This function set high on led pin (turn on the led )
 *                           *------------------------------------------------------*
 * Parameters : 
			=>LED_Configuration: struct(LED_Tupe)
				-> Port         [LED_PORTA , LED_PORTB , LED_PORTC , LED_PORTD]
				-> Pin          [LED_PIN0 , LED_PIN1 , LED_PIN2 , LED_PIN3 , LED_PIN4 , LED_PIN5 , LED_PIN6 , LED_PIN7]
				-> Active_State [ACTIVE_HIGH , ACTIVE_LOW]
			
 * return : void     
 */
void LED_voidOn  ( LED_Type LED_Configuration )
{
	
	if( LED_Configuration.Active_State == ACTIVE_HIGH ){
		
		DIO_enumSetPinValue( LED_Configuration.Port , LED_Configuration.Pin , DIO_PIN_HIGH );
		
	}else if( LED_Configuration.Active_State == ACTIVE_LOW ){
		
		DIO_enumSetPinValue( LED_Configuration.Port , LED_Configuration.Pin , DIO_PIN_LOW  );
		
	}
	
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                   This function set low on led pin (turn off the led) 
 *                           *-----------------------------------------------------*
 * Parameters :
			=>LED_Configuration: struct(LED_Tupe)
				-> Port         [LED_PORTA , LED_PORTB , LED_PORTC , LED_PORTD]
				-> Pin          [LED_PIN0 , LED_PIN1 , LED_PIN2 , LED_PIN3 , LED_PIN4 , LED_PIN5 , LED_PIN6 , LED_PIN7]
				-> Active_State [ACTIVE_HIGH , ACTIVE_LOW]
					
 * return : void     
 */ 
 
void LED_voidOff ( LED_Type LED_Configuration )
{
	
	if( LED_Configuration.Active_State == ACTIVE_HIGH ){
		
		DIO_enumSetPinValue( LED_Configuration.Port , LED_Configuration.Pin , DIO_PIN_LOW  );
		
	}else if( LED_Configuration.Active_State == ACTIVE_LOW ){
		
		DIO_enumSetPinValue( LED_Configuration.Port , LED_Configuration.Pin , DIO_PIN_HIGH  );
		
	}
	
}


/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                        This function toggle led pin
 *                                                *------------------------------*
 * Parameters :
			=>LED_Configuration: struct(LED_Tupe)
				-> Port         [LED_PORTA , LED_PORTB , LED_PORTC , LED_PORTD]
				-> Pin          [LED_PIN0 , LED_PIN1 , LED_PIN2 , LED_PIN3 , LED_PIN4 , LED_PIN5 , LED_PIN6 , LED_PIN7]
				-> Active_State [ACTIVE_HIGH , ACTIVE_LOW]
			
 * return : void     
 */
 
void LED_voidToggle      ( LED_Type LED_Configuration )
{
	DIO_enumTogglePinValue  ( LED_Configuration.Port , LED_Configuration.Pin );
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    END    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>}

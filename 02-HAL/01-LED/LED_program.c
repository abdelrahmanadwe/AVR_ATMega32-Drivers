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
 *         	                                     This function initialize the Pin which connected to led as output pin
 *                                                *-----------------------------------------------------------------------*
 * Parameters :  
		-> Copy_u8Port         [LED_PORTA , LED_PORTB , LED_PORTC , LED_PORTD]
		-> Copy_u8Pin          [LED_PIN0 , LED_PIN1 , LED_PIN2 , LED_PIN3 , LED_PIN4 , LED_PIN5 , LED_PIN6 , LED_PIN7]
			
 * return : void     
 */

void LED_voidInit (u8 Copy_u8Port , u8 Copy_u8Pin)
{
	
	DIO_enumSetPinDirection(Copy_u8Port , Copy_u8Pin , DIO_PIN_OUTPUT);
	
}


/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                             This function set high on led pin (turn on the led )
 *                                                        *------------------------------------------------------*
 * Parameters : 
		-> Copy_u8Port         [LED_PORTA , LED_PORTB , LED_PORTC , LED_PORTD]
		-> Copy_u8Pin          [LED_PIN0 , LED_PIN1 , LED_PIN2 , LED_PIN3 , LED_PIN4 , LED_PIN5 , LED_PIN6 , LED_PIN7]
		-> Copy_u8ActiveState  [ACTIVE_HIGH , ACTIVE_LOW]
			
 * return : void     
 */
void LED_voidOn (u8 Copy_u8Port , u8 Copy_u8Pin ,u8 Copy_u8ActiveState)
{
	
	if(Copy_u8ActiveState == ACTIVE_HIGH)
	{
		
		DIO_enumSetPinValue (Copy_u8Port , Copy_u8Pin , DIO_PIN_HIGH );
		
	}
	else if(Copy_u8ActiveState == ACTIVE_LOW)
	{
		
		DIO_enumSetPinValue (Copy_u8Port , Copy_u8Pin , DIO_PIN_LOW );
		
	}
		
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                        This function set low on led pin (turn off the led) 
 *                                                   *-----------------------------------------------------*
 * Parameters :
		-> Copy_u8Port         [LED_PORTA , LED_PORTB , LED_PORTC , LED_PORTD]
		-> Copy_u8Pin          [LED_PIN0 , LED_PIN1 , LED_PIN2 , LED_PIN3 , LED_PIN4 , LED_PIN5 , LED_PIN6 , LED_PIN7]
		-> Copy_u8ActiveState  [ACTIVE_HIGH , ACTIVE_LOW]
			
 * return : void     
 */ 
 
void LED_voidOff (u8 Copy_u8Port , u8 Copy_u8Pin ,u8 Copy_u8ActiveState)
{
	
	if(Copy_u8ActiveState == ACTIVE_HIGH)
	{
		
		DIO_enumSetPinValue (Copy_u8Port , Copy_u8Pin , DIO_PIN_LoW );
		
	}
	else if(Copy_u8ActiveState == ACTIVE_LOW)
	{
		
		DIO_enumSetPinValue (Copy_u8Port , Copy_u8Pin , DIO_PIN_HIGH );
		
	}
		
}


/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                                       This function toggle led pin
 *                                                                  *------------------------------*
 * Parameters : 
		-> Copy_u8Port         [LED_PORTA , LED_PORTB , LED_PORTC , LED_PORTD]
		-> Copy_u8Pin          [LED_PIN0 , LED_PIN1 , LED_PIN2 , LED_PIN3 , LED_PIN4 , LED_PIN5 , LED_PIN6 , LED_PIN7]
			
 * return : void     
 */
 
void LED_voidTogglePin (u8 Copy_u8Port , u8 Copy_u8Pin)
{
	
	DIO_enumTogglePinValue(Copy_u8Por , Copy_u8Pin);
	
}


/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                        This function initialize the Port which connected to leds as output port
 *                                                   *--------------------------------------------------------------------------*
 * Parameters :  
		-> Copy_u8Port         [LED_PORTA , LED_PORTB , LED_PORTC , LED_PORTD]
			
 * return : void     
 */
void LED_voidPortInit (u8 Copy_u8Port )
{
	
	DIO_Status DIO_enumSetPortDirection(Copy_u8Port ,  DIO_PORT_OUTPUT);
	
}


void LED_voidTogglePort  (u8 Copy_u8Port )
{
	
	DIO_Status DIO_enumTogglePortValue(Copy_u8Port );
	
}


/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                                      This function flashing the led every x second
 *                                                                 *-----------------------------------------------*
 * Parameters :  
		-> Copy_u8Port         [LED_PORTA , LED_PORTB , LED_PORTC , LED_PORTD]
		-> Copy_u8Pin          [LED_PIN0 , LED_PIN1 , LED_PIN2 , LED_PIN3 , LED_PIN4 , LED_PIN5 , LED_PIN6 , LED_PIN7]
		-> delay        milliseconds
			
 * return : void     
 */
 
void LED_voidFlashPin (u8 Copy_u8Port , u8 Copy_u8Pin , u8 delay)
{
	
	DIO_enumTogglePinValue( Copy_u8Port , Copy_u8Pin);
	_delay_ms(delay);
	
}


/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                                 This function flashing the port every x milliseconds
 *                                                            *------------------------------------------------------*
 * Parameters :  
		-> Port         [LED_PORTA , LED_PORTB , LED_PORTC , LED_PORTD]
		-> delay        milliseconds
			
 * return : void     
 */
 
void LED_voidFlashPort  (u8 Copy_u8Port , u8 delay)
{
	
	DIO_Status DIO_enumTogglePortValue(Copy_u8Port );
	_delay_ms(delay);
	
}


/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                                   This function shifting left every x milliseconds
 *                                                              *---------------------------------------------------*
 * Parameters :  
		-> Port                [LED_PORTA , LED_PORTB , LED_PORTC , LED_PORTD]
            -> Copy_u8ActiveState  [ACTIVE_HIGH , ACTIVE_LOW]
		-> delay               milliseconds
			
 * return : void     
 */
 
void LED_voidShiftLeft (u8 Copy_u8Port , u8 Copy_u8ActiveState , u8 delay )
{
	u8 LOC_u8PinNum;
	
	for( LOC_u8PinNum = LED_PIN0 ; LOC_u8PinNum <= LED_PIN7 ; ++LOC_u8PinNum )
	{
		
		LED_voidOff(Copy_u8Port , LOC_u8PinNum-1 , Copy_u8ActiveState);
		LED_voidOn (Copy_u8Port , LOC_u8PinNum , Copy_u8ActiveState  );
		_delay_ms(delay);
		
	}
	LED_voidOff(Copy_u8Port , LOC_u8PinNum-1 , Copy_u8ActiveState);
	
}


/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                                    This function shifting right every x milliseconds
 *                                                               *---------------------------------------------------*
 * Parameters :  
		-> Port                [LED_PORTA , LED_PORTB , LED_PORTC , LED_PORTD]
            -> Copy_u8ActiveState  [ACTIVE_HIGH , ACTIVE_LOW]
		-> delay               milliseconds
			
 * return : void     
 */
 
void LED_voidShiftRight (u8 Copy_u8Port , u8 Copy_u8ActiveState , u8 delay )
{
	u8 LOC_u8PinNum;
	
	for( LOC_u8PinNum = LED_PIN7 ; LOC_u8PinNum >= LED_PIN0 ; --LOC_u8PinNum )
	{
		
		LED_voidOff(Copy_u8Port , LOC_u8PinNum+1 , Copy_u8ActiveState);
		LED_voidOn (Copy_u8Port , LOC_u8PinNum , Copy_u8ActiveState  );
		
		_delay_ms(delay);
		
	}
	LED_voidOff(Copy_u8Port , LOC_u8PinNum+1 , Copy_u8ActiveState);
	
}


/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                                  This function make Ping Pong effect every x milliseconds
 *                                                             *----------------------------------------------------------*
 * Parameters :  
		-> Port                [LED_PORTA , LED_PORTB , LED_PORTC , LED_PORTD]
            -> Copy_u8ActiveState  [ACTIVE_HIGH , ACTIVE_LOW]
		-> delay               milliseconds
			
 * return : void     
 */
 
void LED_voidPingPong   (u8 Copy_u8Port , u8 Copy_u8ActiveState , u8 delay )
{
	
	LED_voidShiftLeft  ( Copy_u8Port ,  Copy_u8ActiveState , delay );
	
	LED_voidShiftRight ( Copy_u8Port , Copy_u8ActiveState , delay  );
	
}


/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                                      This function make two leds converge every x milliseconds
 *                                                                 *-----------------------------------------------------------*
 * Parameters :  
		-> Port                [LED_PORTA , LED_PORTB , LED_PORTC , LED_PORTD]
            -> Copy_u8ActiveState  [ACTIVE_HIGH , ACTIVE_LOW]
		-> delay               milliseconds
			
 * return : void     
 */
void LED_voidConverge (u8 Copy_u8Port , u8 Copy_u8ActiveState , u8 delay )
{
	u8 LOC_u8PinNumL;
	u8 LOC_u8PinNumR;
	
	for(LOC_u8PinNumL = LED_PIN0 , LOC_u8PinNumR = LED_PIN7 ; (LOC_u8PinNumL <= LED_PIN3) && (LOC_u8PinNumR >= LED_PIN4) ; ++LOC_u8PinNumL , --LOC_u8PinNumR )
	{
		
		LED_voidOff(Copy_u8Port , LOC_u8PinNumL-1 , Copy_u8ActiveState);
		LED_voidOn (Copy_u8Port , LOC_u8PinNumL , Copy_u8ActiveState  );
		
		LED_voidOff(Copy_u8Port , LOC_u8PinNumR+1 , Copy_u8ActiveState);
		LED_voidOn (Copy_u8Port , LOC_u8PinNumR , Copy_u8ActiveState  );
		
		_delay_ms(delay);
	}
	LED_voidOff(Copy_u8Port , LOC_u8PinNumL-1 , Copy_u8ActiveState);
	LED_voidOff(Copy_u8Port , LOC_u8PinNumR+1 , Copy_u8ActiveState);
	
}


/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                                      This function make two leds diverge every x milliseconds
 *                                                                 *----------------------------------------------------------*
 * Parameters :  
		-> Port                [LED_PORTA , LED_PORTB , LED_PORTC , LED_PORTD]
            -> Copy_u8ActiveState  [ACTIVE_HIGH , ACTIVE_LOW]
		-> delay               milliseconds
			
 * return : void     
 */

void LED_voidDiverge (u8 Copy_u8Port , u8 Copy_u8ActiveState , u8 delay )
{
	u8 LOC_u8PinNumL;
	u8 LOC_u8PinNumR;
	
	for(LOC_u8PinNumL = LED_PIN3 , LOC_u8PinNumR = LED_PIN4 ; (LOC_u8PinNumL >= LED_PIN0) && (LOC_u8PinNumR <= LED_PIN7) ; --LOC_u8PinNumL , ++LOC_u8PinNumR )
	{
		
		LED_voidOff(Copy_u8Port , LOC_u8PinNumL+1 , Copy_u8ActiveState);
		LED_voidOff(Copy_u8Port , LOC_u8PinNumR-1 , Copy_u8ActiveState);
		
		LED_voidOn (Copy_u8Port , LOC_u8PinNumL , Copy_u8ActiveState  );
		LED_voidOn (Copy_u8Port , LOC_u8PinNumR , Copy_u8ActiveState  );
		
		_delay_ms(delay);
	}
	LED_voidOff(Copy_u8Port , LOC_u8PinNumL+1 , Copy_u8ActiveState);
	LED_voidOff(Copy_u8Port , LOC_u8PinNumR-1 , Copy_u8ActiveState);
	
}


/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                                 This function make two leds converging /diverging every x milliseconds
 *                                                            *------------------------------------------------------------------------*
 * Parameters :  
		-> Port                [LED_PORTA , LED_PORTB , LED_PORTC , LED_PORTD]
            -> Copy_u8ActiveState  [ACTIVE_HIGH , ACTIVE_LOW]
		-> delay               milliseconds
			
 * return : void     
 */
 
void LED_voidConverge_Diverge    ( u8 Copy_u8Port , u8 Copy_u8ActiveState , u8 delay )
{
	
	LED_voidConverge ( Copy_u8Port , Copy_u8ActiveState , delay );
	
	LED_voidDiverge  ( Copy_u8Port , Copy_u8ActiveState , delay );
	
}


/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                                    This function make Snake effect every x milliseconds
 *                                                               *------------------------------------------------------*
 * Parameters :  
		-> Port                [LED_PORTA , LED_PORTB , LED_PORTC , LED_PORTD]
            -> Copy_u8ActiveState  [ACTIVE_HIGH , ACTIVE_LOW]
		-> delay               milliseconds
			
 * return : void     
 */
 
void LED_voidSnakeEffect ( u8 Copy_u8Port , u8 Copy_u8ActiveState , u8 delay )
{
	
	u8 LOC_u8PinNum;
	
	for( LOC_u8PinNum = LED_PIN0 ; LOC_u8PinNum <= LED_PIN7 ; ++LOC_u8PinNum )
	{
		
		LED_voidOn ( Copy_u8Port , LOC_u8PinNum , Copy_u8ActiveState);
		
		_delay_ms(delay);
		
	}
	
	for( LOC_u8PinNum = LED_PIN0 ; LOC_u8PinNum <= LED_PIN7 ; ++LOC_u8PinNum )
	{
		
		LED_voidOff ( Copy_u8Port , LOC_u8PinNum , Copy_u8ActiveState);
		
		_delay_ms(delay);
		
	}
	
	
}
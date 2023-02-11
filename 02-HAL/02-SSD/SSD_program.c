/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     DIO_interface.h     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdelrahman Adwe Ali 
 *  Layer  : HAL
 *  SWC    : SSD
 *
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "SSD_interface.h"
#include "SSD_private.h"
 
u8 SSD_u8NUMBERS[10] = SSD_NUMBER_ARR ;

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                     This function initialize the Port which connected to SSD as output Port
 *                                                *------------------------------------------------------------------------*
 * Parameters : 
		=> struct (SSD_Data) :
			-> Type         [SSD_COMMON_CATHODE , SSD_COMMON_ANODE ]
			-> Port    			[SSD_PORTA , SSD_PORTB , SSD_PORTC , SSD_PORTD]
			-> EnablePort     [SSD_PORTA , SSD_PORTB , SSD_PORTC , SSD_PORTD]
			-> EnablePin          [SSD_PIN0 , SSD_PIN1 , SSD_PIN2 , SSD_PIN3 , SSD_PIN4 , SSD_PIN5 , SSD_PIN6 , SSD_PIN7]
			
 * return : void     
 */

void SSD_voidInit (SSD_Data SSD_Config )
{
	
	DIO_enumSetPortDirection( SSD_Config.Port , DIO_PORT_OUTPUT );
	
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                                         This function enable common pin
 *                                                                    *---------------------------------*
 * Parameters : 
		=> struct (SSD_Data) :
			-> Type         [SSD_COMMON_CATHODE , SSD_COMMON_ANODE ]
			-> Port    			[SSD_PORTA , SSD_PORTB , SSD_PORTC , SSD_PORTD]
			-> EnablePort     [SSD_PORTA , SSD_PORTB , SSD_PORTC , SSD_PORTD]
			-> EnablePin          [SSD_PIN0 , SSD_PIN1 , SSD_PIN2 , SSD_PIN3 , SSD_PIN4 , SSD_PIN5 , SSD_PIN6 , SSD_PIN7]
			
 * return : void     
 */
 
void SSD_voidEnable (SSD_Data SSD_Config )
{
	
	if(SSD_Config.Type == SSD_COMMON_CATHODE)
	{
		
		DIO_enumSetPinDirection (SSD_Config.EnablePort , SSD_Config.EnablePin , DIO_PIN_OUTPUT);
		
		DIO_enumSetPinValue     (SSD_Config.EnablePort , SSD_Config.EnablePin , DIO_PIN_LOW   );
		
	}
	else if(SSD_Config.Type == SSD_COMMON_ANODE)
	{
		
		DIO_enumSetPinDirection (SSD_Config.EnablePort , SSD_Config.EnablePin , DIO_PIN_OUTPUT);
		
		DIO_enumSetPinValue     (SSD_Config.EnablePort , SSD_Config.EnablePin , DIO_PIN_HIGH   );
		
	}
	
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                                         This function disable common pin
 *                                                                    *---------------------------------*
 * Parameters : 
		=> struct (SSD_Data) :
			-> Type         [SSD_COMMON_CATHODE , SSD_COMMON_ANODE ]
			-> Port    			[SSD_PORTA , SSD_PORTB , SSD_PORTC , SSD_PORTD]
			-> EnablePort     [SSD_PORTA , SSD_PORTB , SSD_PORTC , SSD_PORTD]
			-> EnablePin          [SSD_PIN0 , SSD_PIN1 , SSD_PIN2 , SSD_PIN3 , SSD_PIN4 , SSD_PIN5 , SSD_PIN6 , SSD_PIN7]
			
 * return : void     
 */
 
void SSD_voidDisable (SSD_Data SSD_Config )
{
	
	if(SSD_Config.Type == SSD_COMMON_CATHODE)
	{
		
		DIO_enumSetPinDirection (SSD_Config.EnablePort , SSD_Config.EnablePin , DIO_PIN_OUTPUT);
		
		DIO_enumSetPinValue     (SSD_Config.EnablePort , SSD_Config.EnablePin , DIO_PIN_HIGH  );
		
	}
	else if(SSD_Config.Type == SSD_COMMON_ANODE)
	{
		
		DIO_enumSetPinDirection (SSD_Config.EnablePort , SSD_Config.EnablePin , DIO_PIN_OUTPUT);
		
		DIO_enumSetPinValue     (SSD_Config.EnablePort , SSD_Config.EnablePin , DIO_PIN_LOW   );
		
	}
	
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                                         This function write a number on SSD [0:9]
 *                                                                    *------------------------------------------*
 * Parameters : 
		=> struct (SSD_Data) :
			-> Type         [SSD_COMMON_CATHODE , SSD_COMMON_ANODE ]
			-> Port    			[SSD_PORTA , SSD_PORTB , SSD_PORTC , SSD_PORTD]
			-> EnablePort     [SSD_PORTA , SSD_PORTB , SSD_PORTC , SSD_PORTD]
			-> EnablePin          [SSD_PIN0 , SSD_PIN1 , SSD_PIN2 , SSD_PIN3 , SSD_PIN4 , SSD_PIN5 , SSD_PIN6 , SSD_PIN7]
			
 * return : void     
 */
 
void SSD_voidSendNumber (SSD_Data SSD_Config , u8 Copy_u8Number )
{
	
	if(SSD_Config.Type == SSD_COMMON_CATHODE)
	{
		
		DIO_enumSetPortValue ( SSD_Config.Port , SSD_u8NUMBERS[Copy_u8Number] );
		
	}
	else if(SSD_Config.Type == SSD_COMMON_ANODE)
	{
		
		DIO_enumSetPortValue ( SSD_Config.Port , ~(SSD_u8NUMBERS[Copy_u8Number]) );
		
	}
	
}
/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     CLCD_program.c     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdelrahman Adwe Ali 
 *  Layer  : HAL
 *  SWC    : CLCD
 *
 */

#define F_CPU 8000000UL
#include <util/delay.h>

#include "BIT_MATH.h"
#include "STD_TYPE.h"

#include "DIO_interface.h"

#include "CLCD_interface.h"
#include "CLCD_config.h"
#include "CLCD_private.h"

void CLCD_voidInit          ( void )
{
	/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    8 Bits Mode     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
	
	#if CLCD_MODE == 8
	
	_delay_ms(50);       // must wait more than 30 ms befor any action (VDD rises to 4.5 v)
	
	DIO_enumSetPortDirection  (CLCD_DATA_PORT , DIO_PORT_OUTPUT             );
	DIO_enumSetPinDirection   (CLCD_CONTROL_PORT , CLCD_RS , DIO_PIN_OUTPUT );
	DIO_enumSetPinDirection   (CLCD_CONTROL_PORT , CLCD_RW , DIO_PIN_OUTPUT );
	DIO_enumSetPinDirection   (CLCD_CONTROL_PORT , CLCD_EN , DIO_PIN_OUTPUT );
	
	CLCD_voidSendCommand   (CLCD_HOME  );
	_delay_ms(10);
	
	CLCD_voidSendCommand   (EIGHT_BITS );
	_delay_ms(1);
	
	CLCD_voidSendCommand   (CLCD_DISPLAYON_CURSOROFF );
	_delay_ms(1);
	
	CLCD_voidClearScreen ();
	
	CLCD_voidSendCommand   (CLCD_ENTRYMODE );
	_delay_ms(1);
	
	/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    4 Bits Mode     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
	
	#elif CLCD_MODE == 4
	
	_delay_ms(50);       // maust wait more than 30 ms befor any action (VDD rises to 4.5 v)
	
	DIO_enumSetPinDirection   (CLCD_CONTROL_PORT , DIO_PIN4 , DIO_PIN_OUTPUT );
	DIO_enumSetPinDirection   (CLCD_CONTROL_PORT , DIO_PIN5 , DIO_PIN_OUTPUT );
	DIO_enumSetPinDirection   (CLCD_CONTROL_PORT , DIO_PIN6 , DIO_PIN_OUTPUT );
	DIO_enumSetPinDirection   (CLCD_CONTROL_PORT , DIO_PIN7 , DIO_PIN_OUTPUT );
	
	DIO_enumSetPinDirection   (CLCD_CONTROL_PORT , CLCD_RS , DIO_PIN_OUTPUT );
	DIO_enumSetPinDirection   (CLCD_CONTROL_PORT , CLCD_RW , DIO_PIN_OUTPUT );
	DIO_enumSetPinDirection   (CLCD_CONTROL_PORT , CLCD_EN , DIO_PIN_OUTPUT );
	
	CLCD_voidSendCommand   (CLCD_HOME  );
	_delay_ms(10);
	
	CLCD_voidSendCommand   (FOUR_BITS );
	_delay_ms(1);
	
	CLCD_voidSendCommand   (CLCD_DISPLAYON_CURSOROFF );
	_delay_ms(1);
	
	CLCD_voidClearScreen ();
	
	CLCD_voidSendCommand   (CLCD_ENTRYMODE );
	_delay_ms(1);
	
	#endif 
}

void CLCD_voidSendData      (u8 Copy_u8Data     )
{
	/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    8 Bits Mode     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
	
	#if CLCD_MODE == 8
	
	DIO_enumSetPortValue    (CLCD_DATA_PORT , Copy_u8Data                 );
	DIO_enumSetPinValue     (CLCD_CONTROL_PORT , CLCD_RS ,DIO_PIN_HIGH    );
	DIO_enumSetPinValue     (CLCD_CONTROL_PORT , CLCD_RW , DIO_PIN_LOW    );
	CLCD_voidSendFallingEdge();
	
	/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    4 Bits Mode     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
	
	#elif CLCD_MODE == 4
	
	DIO_enumSetPinValue     (CLCD_CONTROL_PORT , CLCD_RS , DIO_PIN_LOW     );
	DIO_enumSetPinValue     (CLCD_CONTROL_PORT , CLCD_RW , DIO_PIN_LOW     );
	DIO_enumWriteHighNibbles(u8 Copy_u8Port , (Copy_u8Data>>4)             );    // send the most 4 bits of data to high nibbles
	CLCD_voidSendFallingEdge();
	DIO_enumWriteHighNibbles(u8 Copy_u8Port , Copy_u8Data                  );   // send the least 4 bits of data to high nibbles
	CLCD_voidSendFallingEdge();
	
	#endif 
	_delay_ms(1);
}

void CLCD_voidSendCommand    (u8 Copy_u8Command )
{
	/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    8 Bits Mode     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
	
	#if CLCD_MODE == 8
	
	DIO_enumSetPortValue    (CLCD_DATA_PORT , Copy_u8Command              );
	DIO_enumSetPinValue     (CLCD_CONTROL_PORT , CLCD_RS ,DIO_PIN_LOW     );
	DIO_enumSetPinValue     (CLCD_CONTROL_PORT , CLCD_RW , DIO_PIN_LOW    );
	CLCD_voidSendFallingEdge();
	
	/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    4 Bits Mode     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
	
	#elif CLCD_MODE == 4
	
	DIO_enumSetPinValue     (CLCD_CONTROL_PORT , CLCD_RS , DIO_PIN_LOW     );
	DIO_enumSetPinValue     (CLCD_CONTROL_PORT , CLCD_RW , DIO_PIN_LOW     );
	DIO_enumWriteHighNibbles(u8 Copy_u8Port , (Copy_u8Command>>4)          );   // send the most 4 bits of data to high nibbles
	CLCD_voidSendFallingEdge();
	DIO_enumWriteHighNibbles(u8 Copy_u8Port , Copy_u8Command               );   // send the least 4 bits of data to high nibbles
	CLCD_voidSendFallingEdge();
	
	#endif 
	_delay_ms(1);
}


static void CLCD_voidSendFallingEdge (void)
{
	
	DIO_enumSetPinValue     (CLCD_CONTROL_PORT , CLCD_EN ,DIO_PIN_HIGH    );
	_delay_ms(1);
	DIO_enumSetPinValue     (CLCD_CONTROL_PORT , CLCD_EN , DIO_PIN_LOW    );
	_delay_ms(1);
	
}

void CLCD_voidClearScreen ( void )
{
	
	CLCD_voidSendCommand  ( CLCD_ClEAR );
	_delay_ms(10); //wait more than 1.53 ms
	
}

void CLCD_voidSendString  (u8 * Copy_u8PrtStrign )
{
	
	for(u8 LOC_u8Iterator = 0; Copy_u8PrtStrign[LOC_u8Iterator] != '\0' ; LOC_u8Iterator++)
	{
		CLCD_voidSendData( Copy_u8PrtStrign[LOC_u8Iterator] );
	}
	
}

void CLCD_voidSendNumber  (u8 Copy_u8Number      )
{
	
	LOC_u8Reverse = 1 ;
	
	if(Copy_u8Number == 0 )
	{
		CLCD_voidSendData( '0' );
	}
	else
	{
		
		while (Copy_u8Number != 0)
		{
			LOC_u8Reverse = (LOC_u8Reverse * 10 ) + (Copy_u8Number % 10);
			Copy_u8Number /= 10 ;
		}
		while (LOC_u8Reverse != 1)
		{
			CLCD_voidSendData( (LOC_u8Reverse % 10 ) + 48 );
			Copy_u8Number /= 10 ;
		}
		
	}
	
}

void CLCD_voidSetPosition (u8 Copy_u8ROW , u8 Copy_u8Col )
{
	u8 LOC_u8Data ;
	
	if( (Copy_u8ROW < CLCD_ROW_1 ) || (Copy_u8ROW > CLCD_ROW_2 ) || (Copy_u8Col < CLCD_COL_1) || (Copy_u8Col > CLCD_COL_16 )
	{
		
		LOC_u8Data = CLCD_SET_CURSOR ;
		
	}
	else if(Copy_u8ROW == CLCD_ROW_1)
	{
		
		LOC_u8Data = ( ( CLCD_SET_CURSOR ) + ( Copy_u8Col - 1 ) );
	
	}
	else if(Copy_u8ROW == CLCD_ROW_2)
	{
		
		LOC_u8Data = ( ( CLCD_SET_CURSOR ) + (64) + ( Copy_u8Col - 1 ) );
		
	}
	
	CLCD_voidSendCommand  ( LOC_u8Data );
	_delay_ms(1);
	
}
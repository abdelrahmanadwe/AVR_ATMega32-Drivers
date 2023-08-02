/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     KPD_program.c     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdelrahman Adwe Ali 
 *  Layer  : HAL
 *  SWC    : KPD
 *
 */
 
#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "KPD_interface.h"
#include "KPD_config.h"

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function used to get the pressed button of the kpd
 *                                                *------------------------------------------------------------*
 * Parameters : Nothing
 * return     : the pressed button  
 */
 
 void KPD_voidInit    ( void )
 {
	 
	 /*                connect pull up for the pins of the rows                                 */
	 
	DIO_enumSetPinDirection (KPD_PORT , KPD_R0 , DIO_PIN_INPUT );
	DIO_enumSetPinDirection (KPD_PORT , KPD_R1 , DIO_PIN_INPUT );
	DIO_enumSetPinDirection (KPD_PORT , KPD_R2 , DIO_PIN_INPUT );
	DIO_enumSetPinDirection (KPD_PORT , KPD_R3 , DIO_PIN_INPUT );
	                                                           
	DIO_enumSetPinValue     (KPD_PORT , KPD_R0 , DIO_PIN_HIGH  );
	DIO_enumSetPinValue     (KPD_PORT , KPD_R1 , DIO_PIN_HIGH  );
	DIO_enumSetPinValue     (KPD_PORT , KPD_R2 , DIO_PIN_HIGH  );
	DIO_enumSetPinValue     (KPD_PORT , KPD_R3 , DIO_PIN_HIGH  );
	
	/*                 connect the pins of the columns as output pins (HIGH)                    */
	
	DIO_enumSetPinDirection (KPD_PORT , KPD_C0 , DIO_PIN_OUTPUT);
	DIO_enumSetPinDirection (KPD_PORT , KPD_C1 , DIO_PIN_OUTPUT);
	DIO_enumSetPinDirection (KPD_PORT , KPD_C2 , DIO_PIN_OUTPUT);
	DIO_enumSetPinDirection (KPD_PORT , KPD_C3 , DIO_PIN_OUTPUT);
	
	DIO_enumSetPinValue     (KPD_PORT , KPD_C0 , DIO_PIN_HIGH  );
	DIO_enumSetPinValue     (KPD_PORT , KPD_C1 , DIO_PIN_HIGH  );
	DIO_enumSetPinValue     (KPD_PORT , KPD_C2 , DIO_PIN_HIGH  );
	DIO_enumSetPinValue     (KPD_PORT , KPD_C3 , DIO_PIN_HIGH  );
	
 }
 
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
 u8 KPD_u8GetPressed  ( void )
 {
	 
	u8 LOC_u8ReturnData = NOTPRESSED ;
	u8 LOC_u8GetPressed ;
	/* iterators  */
	u8 LOC_u8Row ;
	u8 LOC_u8Col ;

	for( LOC_u8Col = 0 + KPD_COL_INIT ; LOC_u8Col < KPD_COL_END + 1 ; LOC_u8Col++ )
	{

		DIO_enumSetPinValue    ( KPD_PORT , LOC_u8Col , DIO_PIN_LOW );   // Low on the columns

		for( LOC_u8Row = 0 + KPD_ROW_INIT ; LOC_u8Row < KPD_ROW_END + 1 ; LOC_u8Row++ )
		{

			DIO_enumGetPinValue( KPD_PORT , LOC_u8Row , &LOC_u8GetPressed ); // retun the row value
			/* 
			if the row is high ....there is no pressed buttons
			if the row is low ....there is pressed button ===>> I will check on this
			 */
			if( LOC_u8GetPressed == 0 )
			{

				_delay_ms(50);   // delay for bouncing

				DIO_enumGetPinValue( KPD_PORT , LOC_u8Row , &LOC_u8GetPressed );   // to make sure that the button is pressed & check again

				if( LOC_u8GetPressed == 0 )
				{
					/*      # Important Note #
					the button will know by the row and the column (ASCII Code)
					==> Hint1 : I already defined The ASCII Codes in 2D array at --> "KPD_config.h"
					==> Hint2 : if there is no pressed buttons , it will retured NOTPRESSED (0xff) and there is not any button has this ASCII (0xff)
					*/

					LOC_u8ReturnData = KPD_u8Buttons[ LOC_u8Row - KPD_ROW_INIT ][ LOC_u8Col - KPD_COL_INIT ];

				}

				// stay here if the button is pressed   # we could put delay 200 ms instead of that
				DIO_enumGetPinValue( KPD_PORT , LOC_u8Row , &LOC_u8GetPressed );
				while( DIO_PIN_LOW == LOC_u8GetPressed ) /*  This cond for safty instead of (LOC_u8GetPressed == DIO_PIN_LOW) if i foget = */
				{

					DIO_enumGetPinValue( KPD_PORT , LOC_u8Row , &LOC_u8GetPressed );

				}

				break ;

			}

		}

		// return this column’s pin to high
		DIO_enumSetPinValue    ( KPD_PORT , LOC_u8Col , DIO_PIN_HIGH );

	}

	return LOC_u8ReturnData ;
	 
 }
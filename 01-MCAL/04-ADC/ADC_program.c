/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     ADC_program.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdelrahman Adwe Ali 
 *  Layer  : MCAL
 *  SWC    : ADC
 *
 */

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "ADC_interface.h"
#include "ADC_config.h"
#include "ADC_private.h"

/*Hint : Must include ADC_CONFIG before ADC_PRIVATE*/

//=====================================================================================================================


/*Global pointer to carry the conversion result in the Asynchronous execution*/
static u16 * ADC_pu16AsynchConversionResult = NULL;

/*Global pointer to function to carry the notification function called by ISR*/
static void (* ADC_pvNotificationFunc)(void)= NULL;

/*Global flag for the ADC ISR State*/
static u8 ADC_u8ISRState ;

/*Global pointer to carry the chain Channel*/
static u8 * ADC_pu8ChainChannel ;

/*Global variable to carry the chain size*/
static u8 ADC_u8ChainSize ;

/*Global variable to indicate for the current ADC Chain*/
static u8 ADC_u8Index ;

/*Global flag for the ADC Busy State*/
static u8 ADC_u8State= IDLE ;

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function Init the ADC ( Prebuild Function)
 *                                                *-----------------------------------------------------*
 * Parameters : Nothing
 * return     : Nothing  
 */

void ADC_voidInit  ( void )
{
	
		/*Select the voltage reference*/
	#ifdef ADC_VREF
	
		ADMUX &= 0x3f;
		ADMUX |= (ADC_VREF<<6);
		
	#endif
	
		/*Set Left Adjust Result*/
	#ifdef ADC_ADJUSTMENT
	
		#if ADC_ADJUSTMENT == RIGHT_ADJUSTMENT
		
			CLR_BIT(ADMUX,ADMUX_ADLAR);
			
		#elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT
		
			SET_BIT(ADMUX,ADMUX_ADLAR);
			
		#else
			
			#error "Wrong ADC_ADJUSTMENT config"
			
		#endif
		
	#endif
	
		/*Set Prescaler Value*/
	#ifdef ADC_PRESCALLER
	
		ADCSRA &= 0xf9;
		ADCSRA |= ADC_PRESCALLER;
		
	#endif
	
		/*Set Trigger Source Value*/
	#ifdef ADC_TRIGGERING_SOURCE
	
		#if ADC_TRIGGERING_SOURCE <= ADC_SINGLE_CONVERSION
		
			#if ADC_TRIGGERING_SOURCE ==  ADC_SINGLE_CONVERSION
			
				CLR_BIT(ADCSRA,ADCSRA_ADATE);
				
			#else 
				
				SET_BIT(ADCSRA,ADCSRA_ADATE);
				SFIOR &= 0x1f;
				SFIOR |= (ADC_TRIGGERING_SOURCE<<5);
			
			#endif
			
		#else 
			
			#error "Wrong ADC_TRIGGERING_SOURCE config"
		
		#endif
		
	#endif
	
		/*Enable ADC Peripheral*/
	#ifdef ADC_STATUS
	
		#if ADC_STATUS == ADC_DISABLE
		
			CLR_BIT(ADCSRA , ADCSRA_ADEN) ;
			
		#elif ADC_STATUS == ADC_ENABLE
		
			SET_BIT(ADCSRA , ADCSRA_ADEN) ;
			
		#else
			
			#error "Wrong ADC_STATUS config"
		
		#endif 
		
	#endif
	
		/*Enable ADC Interrupt*/
	#ifdef ADC_INT_STATUS
	
		#if ADC_INT_STATUS == INT_DISABLE
		
			CLR_BIT(ADCSRA , ADCSRA_ADIE) ;
			
		#elif ADC_INT_STATUS == INT_ENABLE
		
			SET_BIT(ADCSRA , ADCSRA_ADIE) ;
			
		#else
			
			#error "Wrong INT_STATUS config"
		
		#endif 
		
	#endif
	
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function used to enable the ADC  
 *                                                *--------------------------------------*
 * Parameters : Nothing
 * return     : Nothing  
 */
void ADC_voidEnable (void)
{
	
	SET_BIT(ADCSRA , ADCSRA_ADEN) ;
	
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function used to disable the ADC  
 *                                                *--------------------------------------*
 * Parameters : Nothing
 * return     : Nothing  
 */
 
void ADC_voidDisable (void)
{
	
	CLR_BIT(ADCSRA , ADCSRA_ADEN) ;
	
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function used to enable the ADC Interrupt  
 *                                                *----------------------------------------------*
 * Parameters : Nothing
 * return     : Nothing  
 */
 
void ADC_voidInterruptEnable (void)
{
	
	SET_BIT(ADCSRA , ADCSRA_ADIE) ;
	
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function used to disable the ADC Interrupt  
 *                                                *----------------------------------------------*
 * Parameters : Nothing
 * return     : Nothing  
 */
 
void ADC_voidInterruptDisable (void)
{
	
	CLR_BIT(ADCSRA , ADCSRA_ADIE) ;
	
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to set the Prescaler of the ADC (CLK) using postbuild configuration
 *                                                *-----------------------------------------------------------------------------------*
 * Parameters : 
 *		=>Copy_u8Prescaler => [ADC_PRE_2 , ADC_PRE_4 , ADC_PRE_8 , ADC_PRE_16 , ADC_PRE_32 , ADC_PRE_64 , ADC_PRE_128]
 *		
 * return     : Error status with type u8  
 */
u8 ADC_u8SetPrescaler (u8 Copy_u8Prescaler)
{
	
	u8 Local_u8ErrorState = 0 ;

	if (Copy_u8Prescaler < 8)
	{
		/*Set Prescaler Value*/
		ADCSRA &= 0xf9;
		ADCSRA |= Copy_u8Prescaler;
		Local_u8ErrorState = 1 ;
	
	}

	return Local_u8ErrorState ;
	
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to get the result of the ADC conversoin using synch method
 *                                                *-----------------------------------------------------------------------------------*
 * Parameters : 
 *		=>Copy_u8Channel -> ADC channel 
 *      =>Copy_pu16Result -> pointer to u16
 *		
 * return     : Error status with type u8  
 */
 
u8 ADC_u8GetResultSync (u8 Copy_u8Channel , u16 * Copy_pu16Result)
{
	u8 Local_u8ErrorState = OK ;
	
	u32 Local_u32TimeoutCounter = 0 ;
	
	if (Copy_pu16Result != NULL)
	{
		
		if(ADC_u8State == IDLE )
		{
			
			/*ADC is now Busy*/
			ADC_u8State = BUSY ;

			/*Set required channel*/
			ADMUX &= 0xE0 ;
			ADMUX |= Copy_u8Channel ;
	
			/*Start Conversion*/
			SET_BIT(ADCSRA , ADCSRA_ADSC) ;
	
			/*Waiting until the conversion is complete*/
			while ( (GET_BIT(ADCSRA , ADCSRA_ADIF)==0) && (Local_u32TimeoutCounter < ADC_TIMEOUT) )
			{
				Local_u32TimeoutCounter++;
			}
			if(Local_u32TimeoutCounter == ADC_TIMEOUT )
			{
				
				Local_u8ErrorState = NOK ;
	
			}
			else
			{
			
				/*Clear the interrupt flag*/
				SET_BIT(ADCSRA , ADCSRA_ADIF) ;
	
				/*Return Conversion Result*/
				#if ADC_ADJUSTMENT == RIGHT_ADJUSTMENT
				
					*Copy_pu16Result = (ADCL|(ADCH << 8)) ;
	
				#elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT
				
					*Copy_pu16Result = (ADCH<<2) ;
					
				#else
					
					#error "Wrong ADC_ADJUSTMENT config"
	
				#endif
				
			}
			
			/*ADC is IDLE*/
			ADC_u8State = IDLE ;
		}
		else
		{
			Local_u8ErrorState = NOK ;
		}
		
	}
	else
	{
		Local_u8ErrorState = NOK ;
	}
	
	return Local_u8ErrorState ;
	
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to get the result of the ADC conversoin using Asynch method
 *                                                *-----------------------------------------------------------------------------------*
 * Parameters : 
 *		=>Copy_u8Channel : ADC channel 
 *      =>Copy_pu16Result: pointer to u16
 *      =>Copy_pvNotificationFunc : poiter to function
 *		
 * return     : Error status with type u8  
 */
 
u8 ADC_u8StartConversionAsynch (u8 Copy_u8Channel , u16 * Copy_pu16Result , void (*Copy_pvNotificationFunc)(void))
{
	u8 Local_u8ErrorState = OK ;

	if ((Copy_pu16Result != NULL) && (Copy_pvNotificationFunc != NULL))
	{
		if (ADC_u8State == IDLE)
		{
			/*ADC is now Busy*/
			ADC_u8State = BUSY ;

			/*Set ISR State*/
			ADC_u8ISRState = SINGLE_CHANNEL_ASYNCH ;

			/*Initialize the global result pointer*/
			ADC_pu16AsynchConversionResult = Copy_pu16Result;

			/*Initialize the global notification function pointer*/
			ADC_pvNotificationFunc = Copy_pvNotificationFunc;

			/*Set required channel*/
			ADMUX &= 0xE0 ;
			ADMUX |= Copy_u8Channel ;

			/*Start Conversion*/
			SET_BIT(ADCSRA , ADCSRA_ADSC) ;

			/*ADC Conversion Complete Interrupt Enable*/
			SET_BIT(ADCSRA , ADCSRA_ADIE) ;
			
		}
		else
		{
			Local_u8ErrorState = NOK ;
		}
		
	}
	else
	{
		Local_u8ErrorState = NOK ;
	}

	return Local_u8ErrorState ;
	
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to get the result of the ADC conversoin using Asynch method
 *                                                *-----------------------------------------------------------------------------------*
 * Parameters : 
 *		=>Copy_Chain :struct
 *    		->Channel:arry of u8
 *          ->Result :arry of u6
 *          ->Size   :size of arry
 *          ->NotificationFunc:poiter to function
 *      
 *		
 * return     : Error status with type u8  
 */
 
u8 ADC_u8StartChainAsynch (Chain_t * Copy_Chain)
{
	u8 Local_u8ErrorState = OK ;

	if ((Copy_Chain != NULL) && (Copy_Chain->Channel != NULL) && (Copy_Chain->NotificationFunc != NULL) && (Copy_Chain->Result!= NULL))
	{
		if (ADC_u8State == IDLE)
		{
			/*ADC is now Busy*/
			ADC_u8State = BUSY ;

			/*Set ISR State*/
			ADC_u8ISRState = CHAIN_CHANNEL_ASYNCH ;

			/*Assign the ADC data globally*/
			ADC_pu16AsynchConversionResult = Copy_Chain->Result ;
			ADC_pu8ChainChannel = Copy_Chain->Channel ;
			ADC_u8ChainSize = Copy_Chain->Size ;
			ADC_pvNotificationFunc = Copy_Chain->NotificationFunc ;

			/*Set Index to first element*/
			ADC_u8Index = 0 ;

			/*Set required channel*/
			ADMUX &= 0xE0 ;
			ADMUX |= ADC_pu8ChainChannel[ADC_u8Index] ;

			/*Start Conversion*/
			SET_BIT(ADCSRA , ADCSRA_ADSC) ;

			/*ADC Conversion Complete Interrupt Enable*/
			SET_BIT(ADCSRA , ADCSRA_ADIE) ;
			
		}
		else
		{
			Local_u8ErrorState = NOK ;
		}

	}
	else
	{
		Local_u8ErrorState = NOK ;
	}
	return Local_u8ErrorState ;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------

/* ISR for ADC conversion complete */
void __vector_16 (void)  __attribute__((signal)) ;
void __vector_16 (void)
{
	if (ADC_u8ISRState == SINGLE_CHANNEL_ASYNCH)
	{
		/*Return Conversion Result*/
		#if ADC_ADJUSTMENT == RIGHT_ADJUSTMENT
		
			*ADC_pu16AsynchConversionResult = (ADCL|(ADCH << 8)) ;

		#elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT
		
			*ADC_pu16AsynchConversionResult = (ADCH<<2) ;
			
		#else
			
			#error "Wrong ADC_ADJUSTMENT config"

		#endif

		/*ADC is IDLE*/
		ADC_u8State = IDLE ;

		/*Call Notification Function*/
		ADC_pvNotificationFunc() ;

		/*Disable the Conversion Complete Interrupt*/
		CLR_BIT(ADCSRA , ADCSRA_ADIE) ;
	}
	else
	{
		/*Return Conversion Result*/
		#if ADC_ADJUSTMENT == RIGHT_ADJUSTMENT
	
			ADC_pu16AsynchConversionResult[ADC_u8Index] = (ADCL|(ADCH << 8)) ;

		#elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT
		
			ADC_pu16AsynchConversionResult[ADC_u8Index] = (ADCH<<2) ;
			
		#else
			
			#error "Wrong ADC_ADJUSTMENT config"

		#endif

		/*Increment Data index of the chain*/
		ADC_u8Index++ ;

		if (ADC_u8Index == ADC_u8ChainSize)
		{
			/*ADC is IDLE*/
			ADC_u8State = IDLE ;

			/*Call Notification Function*/
			ADC_pvNotificationFunc() ;

			/*Disable the Conversion Complete Interrupt*/
			CLR_BIT(ADCSRA , ADCSRA_ADIE) ;
		}
		else
		{
			/*Set required channel*/
			ADMUX &= 0xE0 ;
			ADMUX |= ADC_pu8ChainChannel[ADC_u8Index] ;

			/*Start Conversion*/
			SET_BIT(ADCSRA , ADCSRA_ADSC) ;
			
		}
		
	}
	
}

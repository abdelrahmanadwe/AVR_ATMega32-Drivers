/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      EXTI_program.c     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdelrahman Adwe Ali 
 *  Layer  : MCAL
 *  SWC    : EXTI
 *
 */
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "EXTI_private.h"
#include "EXTI_interface.h"
#include "EXTI_config.h"

/* 
	       Global Pointer to Function => Carry The Adress of ISR func in the main 
	       Hint : I Made an array of pointers to carry EXTI 0,1,2 according to its index
	
*/ 
void (*EXTI_CallBack[3]) (void) = { NULL } ; 

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function Init THE EXTI ( Prebuild Function)
 *                                                *-----------------------------------------------------*
 * Parameters : Nothing
 * return     : Nothing  
 */
void EXTI_voidInit              ( void )
{
	
	#ifdef EXTI_LINE
	
		#if EXTI_LINE == EXTI_LINE0
			
			#if   EXTI_SENSE_MODE == EXTI_LOW_LEVEL
				
				CLR_BIT( MCUCR_REG,1) ;	CLR_BIT( MCUCR_REG,0) ; 
				
			#elif EXTI_SENSE_MODE == EXTI_ON_CHANGE
				
				CLR_BIT( MCUCR_REG,1) ;	SET_BIT( MCUCR_REG,0) ; 
				
			#elif EXTI_SENSE_MODE == EXTI_FALLING_EDGE
				
				SET_BIT( MCUCR_REG,1) ;	CLR_BIT( MCUCR_REG,0) ;
				
			#elif EXTI_SENSE_MODE == EXTI_RISING_EDGE
				
				SET_BIT( MCUCR_REG,1) ;	SET_BIT( MCUCR_REG,0) ; 
				
			#else 
			
				#error "Wrong EXTI_SENSE_MODE configuration option"
				
			#endif 
		
		#elif EXTI_LINE == EXTI_LINE1
		
			#if   EXTI_SENSE_MODE == EXTI_LOW_LEVEL
				
				CLR_BIT( MCUCR_REG,3) ;	CLR_BIT( MCUCR_REG,2) ; 
				
			#elif EXTI_SENSE_MODE == EXTI_ON_CHANGE
				
				CLR_BIT( MCUCR_REG,3) ;	SET_BIT( MCUCR_REG,2) ; 
				
			#elif EXTI_SENSE_MODE == EXTI_FALLING_EDGE
				
				SET_BIT( MCUCR_REG,3) ;	CLR_BIT( MCUCR_REG,2) ;
				
			#elif EXTI_SENSE_MODE == EXTI_RISING_EDGE
				
				SET_BIT( MCUCR_REG,3) ;	SET_BIT( MCUCR_REG,2) ; 
				
			#else 
			
				#error "Wrong EXTI_SENSE_MODE configuration option"
				
			#endif 
		
		#elif EXTI_LINE == EXTI_LINE2
		
			#if   EXTI_SENSE_MODE == EXTI_FALLING_EDGE
				
				CLR_BIT( MCUCSR_REG,6)
				
			#elif EXTI_SENSE_MODE == EXTI_RISING_EDGE
				
				SET_BIT( MCUCSR_REG,6)
				
			#else 
			
				#error "Wrong EXTI_SENSE_MODE configuration option"
			
			#endif
		
		#else 
			
			#error "Wrong EXTI_LINE configuration option"
		
		#endif
			
			
	#endif	
	
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      A function to set the required sense control of INT0 using postbuild configuration
 *                                                *-------------------------------------------------------------------------------------*
 * Parameters : 
 *		Copy_u8SenseMode => [EXTI_LOW_LEVEL,EXTI_ON_CHANGE,EXTI_FALLING_EDGE,EXTI_RISING_EDGE]
 *		Copy_u8Line      => [EXTI_LINE0,EXTI_LINE1,EXTI_LINE2]
 *		
 * return     : Error status with type u8  
 */
void EXTI_voidSetSignalLatch    ( u8 Copy_u8Line , u8 Copy_u8SenseMode )
{
	
	if(Copy_u8Line == EXTI_LINE0)
	{
		
		switch ( Copy_u8SenseMode )
		{
			
			case EXTI_LOW_LEVEL    : CLR_BIT( MCUCR_REG , 1) ; CLR_BIT( MCUCR_REG , 0) ; break ;
			case EXTI_ON_CHANGE    : CLR_BIT( MCUCR_REG , 1) ; SET_BIT( MCUCR_REG , 0) ; break ; 
			case EXTI_FALLING_EDGE : SET_BIT( MCUCR_REG , 1) ; CLR_BIT( MCUCR_REG , 0) ; break ;
			case EXTI_RISING_EDGE  : SET_BIT( MCUCR_REG , 1) ; SET_BIT( MCUCR_REG , 0) ; break ;  
			
		}
		
	}
	else if(Copy_u8Line == EXTI_LINE1)
	{
		
		switch ( Copy_u8SenseMode )
		{
			
			case EXTI_LOW_LEVEL    : CLR_BIT( MCUCR_REG , 3) ; CLR_BIT( MCUCR_REG , 2) ; break ;
			case EXTI_ON_CHANGE    : CLR_BIT( MCUCR_REG , 3) ; SET_BIT( MCUCR_REG , 2) ; break ; 
			case EXTI_FALLING_EDGE : SET_BIT( MCUCR_REG , 3) ; CLR_BIT( MCUCR_REG , 2) ; break ;
			case EXTI_RISING_EDGE  : SET_BIT( MCUCR_REG , 3) ; SET_BIT( MCUCR_REG , 2) ; break ;  
			
		}
		
	}
	else if(Copy_u8Line == EXTI_LINE2)
	{
		
		switch ( Copy_u8SenseMode )
		{
			
			case EXTI_FALLING_EDGE : CLR_BIT( MCUCSR_REG , 6) ; break ;
			case EXTI_RISING_EDGE  : SET_BIT( MCUCSR_REG , 6) ; break ; 
		
		}
		
	}
	
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function used to disable the EINT Line
 *                                                *-----------------------------------------------*
 * Parameters : 
 *		Copy_u8Line  => [EXTI_LINE0,EXTI_LINE1,EXTI_LINE2]
 *		
 * return     : Error status with type u8  
 */
u8 EXTI_voidDisableInterrupt  ( u8 Copy_u8Line )
{
	
	u8 Local_u8ErrorState = 1 ;
	
	if( (Copy_u8Line == EXTI_LINE0) || (Copy_u8Line == EXTI_LINE1) || (Copy_u8Line == EXTI_LINE2) )
	{
		
		/* Clear The Required BIT */
		CLR_BIT( GICR_REG, Copy_u8Line );
		
	}
	else 
	{
		Local_u8ErrorState = 0 ;
	}
	
	return Local_u8ErrorState ; 
	
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function used to enable the EINT Line
 *                                                *-----------------------------------------------*
 * Parameters : 
 *		Copy_u8Line  => [EXTI_LINE0,EXTI_LINE1,EXTI_LINE2]
 *		
 * return     : Error status with type u8  
 */
u8 EXTI_voidEnableInterrupt  ( u8 Copy_u8Line )
{
	
	u8 Local_u8ErrorState = 1 ;
	
	if( (Copy_u8Line == EXTI_LINE0) || (Copy_u8Line == EXTI_LINE1) || (Copy_u8Line == EXTI_LINE2) )
	{
		
		/* Set The Required BIT */
		SET_BIT( GICR_REG, Copy_u8Line );
		
	}
	else 
	{
		Local_u8ErrorState = 0 ;
	}
	
	return Local_u8ErrorState ; 
	
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function used to clear the EINT flag
 *                                                *----------------------------------------------*
 * Parameters : 
 *		Copy_u8Line  => [EXTI_LINE0,EXTI_LINE1,EXTI_LINE2]
 *		
 * return     : Error status with type u8  
 */
u8 EXTI_voidClearFlag ( u8 Copy_u8Line )
{
	u8 Local_u8ErrorState = 1 ;
	
	if( (Copy_u8Line == EXTI_LINE0) || (Copy_u8Line == EXTI_LINE1) || (Copy_u8Line == EXTI_LINE2) )
	{
		
		/* Set The Required BIT */
		SET_BIT( GIFR_REG , Copy_u8Line );
		
	}
	else 
	{
		Local_u8ErrorState = 0 ;
	}
	
	return Local_u8ErrorState ; 
	
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                      This Function used to Read the value of the EINT flag
 *                                                *------------------------------------------------------*
 * Parameters : 
 *		Copy_u8Line  => [EXTI_LINE0,EXTI_LINE1,EXTI_LINE2]
 *		
 * return     : Error status with type u8  
 */
u8 EXTI_voidGETFlag   ( u8 Copy_u8Line )
{
		
	return GET_BIT( GIFR_REG , Copy_u8Line );
	
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------
 *         	                                                    This Function Init THE EXTI
 *                                                              *--------------------------------*
 * Parameters : 
 *		Copy_pvoidCallBack => The Adress of ISR Func (its name)
 * 		Copy_u8Line        => [EXTI_LINE0 , EXTI_LINE1 , EXTI_LINE2]
 *		
 * return : Nothing  
 */
void EXTI_voidSetCallBack( void (*Copy_pvoidCallBack)(void) , u8 Copy_u8Line )
{

	if( Copy_pvoidCallBack != NULL )
	{
		if(Copy_u8Line == EXTI_LINE0)
		{
			
			EXTI_CallBack[0] = Copy_pvoidCallBack ; 
			
		}
		else if(Copy_u8Line == EXTI_LINE1)
		{
			
			EXTI_CallBack[1] = Copy_pvoidCallBack ; 
			
		}
		else if(Copy_u8Line == EXTI_LINE2)
		{
			
			EXTI_CallBack[2] = Copy_pvoidCallBack ; 
			
		}

	}

}

void __vector_1(void)        __attribute__((signal));
void __vector_1(void)
{
	
	if(EXTI_CallBack[0] != NULL)
	{
		
		EXTI_CallBack[0]();
		EXTI_voidClearFlag( EXTI_LINE0 );
		
	}
	
	
}


void __vector_2(void)        __attribute__((signal));
void __vector_2(void)
{ 
	
	if(EXTI_CallBack[1] != NULL)
	{
		
		EXTI_CallBack[1]();
		EXTI_voidClearFlag( EXTI_LINE1 );
		
	}
	
	
}


void __vector_3(void)        __attribute__((signal));
void __vector_3(void)
{
	
	if(EXTI_CallBack[2] != NULL)
	{
		
		EXTI_CallBack[2]();
		EXTI_voidClearFlag( EXTI_LINE2 );
		
	}
	
	
}
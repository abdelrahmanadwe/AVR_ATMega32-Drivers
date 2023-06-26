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


void (*EXTI_CallBack[3]) (void) = { NULL } ; 

void EXTI_voidInit              ( void )
{
	
	#ifdef EXTI_LINE
	
		#if EXTI_LINE == EXTI_LINE0
			
			#if   EXTI_SENSE_MODE == EXTI_FALLING_EDGE
				
				CLR_BIT( MCUCR_REG,0) ; SET_BIT( MCUCR_REG,1) ; 
				
			#elif EXTI_SENSE_MODE == EXTI_RISING_EDGE
				
				SET_BIT( MCUCR_REG,0) ; SET_BIT( MCUCR_REG,1) ;
				
			#elif EXTI_SENSE_MODE == EXTI_LOW_LEVEL
				
				CLR_BIT( MCUCR_REG,0) ; CLR_BIT( MCUCR_REG,1) ; 
				
			#elif EXTI_SENSE_MODE == EXTI_ON_CHANGE
				
				SET_BIT( MCUCR_REG,0) ; CLR_BIT( MCUCR_REG,1) ;
			
			#else 
			
				#error "Wrong EXTI_SENSE_MODE configuration option"
						
			#endif 
		
		#elif EXTI_LINE == EXTI_LINE1
		
			#if   EXTI_SENSE_MODE == EXTI_FALLING_EDGE
				
				CLR_BIT( MCUCR_REG,2) ; SET_BIT( MCUCR_REG,3) ; 
				
			#elif EXTI_SENSE_MODE == EXTI_RISING_EDGE
				
				SET_BIT( MCUCR_REG,2) ; SET_BIT( MCUCR_REG,3) ;
				
			#elif EXTI_SENSE_MODE == EXTI_LOW_LEVEL
				
				CLR_BIT( MCUCR_REG,2) ; CLR_BIT( MCUCR_REG,3) ; 
				
			#elif EXTI_SENSE_MODE == EXTI_ON_CHANGE
				
				SET_BIT( MCUCR_REG,2) ; CLR_BIT( MCUCR_REG,3) ;
				
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

void EXTI_voidSetSignalLatch    ( u8 Copy_u8Line , u8 Copy_u8SenseMode )
{
	
	if(Copy_u8Line == EXTI_LINE0)
	{
		
		switch ( Copy_u8SenseMode )
		{
			
			case EXTI_FALLING_EDGE : CLR_BIT( MCUCR_REG , 0) ; SET_BIT( MCUCR_REG , 1) ; break ;
			case EXTI_RISING_EDGE  : SET_BIT( MCUCR_REG , 0) ; SET_BIT( MCUCR_REG , 1) ; break ; 
			case EXTI_LOW_LEVEL    : CLR_BIT( MCUCR_REG , 0) ; CLR_BIT( MCUCR_REG , 1) ; break ; 
			case EXTI_ON_CHANGE    : SET_BIT( MCUCR_REG , 0) ; CLR_BIT( MCUCR_REG , 1) ; break ; 
			
		}
		
	}
	else if(Copy_u8Line == EXTI_LINE1)
	{
		
		switch ( Copy_u8SenseMode )
		{
			
			case EXTI_FALLING_EDGE : CLR_BIT( MCUCR_REG , 2) ; SET_BIT( MCUCR_REG , 3) ; break ;
			case EXTI_RISING_EDGE  : SET_BIT( MCUCR_REG , 2) ; SET_BIT( MCUCR_REG , 3) ; break ; 
			case EXTI_LOW_LEVEL    : CLR_BIT( MCUCR_REG , 2) ; CLR_BIT( MCUCR_REG , 3) ; break ; 
			case EXTI_ON_CHANGE    : SET_BIT( MCUCR_REG , 2) ; CLR_BIT( MCUCR_REG , 3) ; break ; 
			
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

u8 EXTI_voidDisableInterrupt  ( u8 Copy_u8Line )
{
	
	u8 Local_u8ErrorState = 1 ;
	
	if( (Copy_u8Line == EXTI_LINE0) || (Copy_u8Line == EXTI_LINE1) || (Copy_u8Line == EXTI_LINE2) )
	{
		
		CLR_BIT( GICR_REG, Copy_u8Line );
		
	}
	else 
	{
		Local_u8ErrorState = 0 ;
	}
	
	return Local_u8ErrorState ; 
	
}

u8 EXTI_voidEableInterrupt  ( u8 Copy_u8Line )
{
	
	u8 Local_u8ErrorState = 1 ;
	
	if( (Copy_u8Line == EXTI_LINE0) || (Copy_u8Line == EXTI_LINE1) || (Copy_u8Line == EXTI_LINE2) )
	{
		
		SET_BIT( GICR_REG, Copy_u8Line );
		
	}
	else 
	{
		Local_u8ErrorState = 0 ;
	}
	
	return Local_u8ErrorState ; 
	
}

u8 EXTI_voidClearFlag ( u8 Copy_u8Line )
{
	u8 Local_u8ErrorState = 1 ;
	
	if( (Copy_u8Line == EXTI_LINE0) || (Copy_u8Line == EXTI_LINE1) || (Copy_u8Line == EXTI_LINE2) )
	{
		
		SET_BIT( GIFR_REG , Copy_u8Line );
		
	}
	else 
	{
		Local_u8ErrorState = 0 ;
	}
	
	return Local_u8ErrorState ; 
	
}
u8 EXTI_voidGETFlag   ( u8 Copy_u8Line )
{
		
		return GET_BIT( GIFR_REG , Copy_u8Line );
	
}

void EXTI_voidSetCallBack( void (*Copy_pvoidCallBack)(void) , u8 Copy_u8Line )
{

	if( Copy_pvoidCallBack != NULL )
	{
		if(Copy_u8Line == EXTI_LINE0)
		{
			
			EXTI_CallBack[0] == Copy_pvoidCallBack ; 
			
		}
		else if(Copy_u8Line == EXTI_LINE1)
		{
			
			EXTI_CallBack[1] == Copy_pvoidCallBack ; 
			
		}
		else if(Copy_u8Line == EXTI_LINE2)
		{
			
			EXTI_CallBack[2] == Copy_pvoidCallBack ; 
			
		}

	}

}

void__vector_2(void)__attribute__((signal));
void__vector_2(void)
{
	
	if(EXTI_CallBack[0] != NULL)
	{
		
		EXTI_CallBack[0]();
		EXTI_voidClearFlag( EXTI_LINE0 );
		
	}
	
	
}


void__vector_3(void)__attribute__((signal));
void__vector_3(void)
{
	
	if(EXTI_CallBack[1] != NULL)
	{
		
		EXTI_CallBack[1]();
		EXTI_voidClearFlag( EXTI_LINE1 );
		
	}
	
	
}


void__vector_4(void)__attribute__((signal));
void__vector_4(void)
{
	
	if(EXTI_CallBack[2] != NULL)
	{
		
		EXTI_CallBack[2]();
		EXTI_voidClearFlag( EXTI_LINE2 );
		
	}
	
	
}
/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     TIMER_program.c     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdelrahman Adwe Ali 
 *  Layer  : MCAL
 *  SWC    : TIMER
 *
 */
 
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER_interface.h"
#include "TIMER_private.h" /*You have to include TIMER_private.h before TIMER_config.h*/
#include "TIMER_config.h"
#include "TIMER_register.h"

/*Global Pointer to array of Function to Hold the Call Back Function Address for Timer*/
static void (*TIMERS_pvCallBackFunc[16])(void) = {NULL} ;  /* we have 8 interrupt sources in timer  */

 
 /*******************************************************************************************************************/
void TIMER0_voidInit(void)
{
	/*Set Configurable Modes*/
		#if TIMER0_WAVEFORM_GENERATION_MODE == TIMER_NORMAL_MODE

			/*Initialize Waveform Generation Mode as Normal Mode*/
			
			CLR_BIT(TCCR0 , TCCR0_WGM01) ; CLR_BIT(TCCR0 , TCCR0_WGM00) ;

			/*Set the Required Preload Value*/
			TCNT0 = TIMER0_PRELOAD_VAL ;

			/*Timer0 Overflow Interrupt Enable*/
			#if TIMER0_OVERFLOW_INTERRUPT == DISABLE
			
				CLR_BIT(TIMSK , TIMSK_TOIE0) ;
				
			#elif TIMER0_OVERFLOW_INTERRUPT == ENABLE
			
				SET_BIT(TIMSK , TIMSK_TOIE0) ;
				
			#else
				
				#error "Wrong TIMER0_OVERFLOW_INTERRUPT Config"
				
			#endif

		#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER_CTC_MODE

			/*Initialize Waveform Generation Mode as CTC Mode*/
			
			SET_BIT(TCCR0 , TCCR0_WGM01) ; CLR_BIT(TCCR0 , TCCR0_WGM00) ;

			/*Set the Required CTC Value*/
			OCR0 = TIMER0_CTC_VAL ;

			/*Timer0 Compare Match Interrupt Enable*/
			#if TIMER0_CTC_INTERRUPT == DISABLE
			
				CLR_BIT(TIMSK , TIMSK_OCIE0) ;
				
			#elif TIMER0_CTC_INTERRUPT == ENABLE
			
				SET_BIT(TIMSK , TIMSK_OCIE0) ;
				
			#else
				
				#error "Wrong TIMER0_OVERFLOW_INTERRUPT Config"
				
			#endif

		#else
			
			#error "Wrong TIMER0_WAVEFORM_GENERATION_MODE Config"

		#endif

	/*Set the Required Prescaler*/
	TCCR0 &= TIMER_PRESCALER_MASK ;
	TCCR0 |= TIMER0_PRESCALER ;
}

void TIMER2_voidInit(void)
{
	/*Set Configurable Modes*/
		#if TIMER2_WAVEFORM_GENERATION_MODE == TIMER_NORMAL_MODE

			/*Initialize Waveform Generation Mode as Normal Mode*/
			
			CLR_BIT(TCCR2 , TCCR2_WGM21) ; CLR_BIT(TCCR2 , TCCR2_WGM20) ;

			/*Set the Required Preload Value*/
			TCNT2 = TIMER2_PRELOAD_VAL ;

			/*Timer2 Overflow Interrupt Enable*/
			#if TIMER2_OVERFLOW_INTERRUPT == DISABLE
			
				CLR_BIT(TIMSK , TIMSK_TOIE2) ;
				
			#elif TIMER2_OVERFLOW_INTERRUPT == ENABLE
			
				SET_BIT(TIMSK , TIMSK_TOIE2) ;
				
			#else
				
				#error "Wrong TIMER2_OVERFLOW_INTERRUPT Config"
			
			#endif

		#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER_CTC_MODE

			/*Initialize Waveform Generation Mode as CTC Mode*/
			
			SET_BIT(TCCR2 , TCCR2_WGM21) ; CLR_BIT(TCCR2 , TCCR2_WGM20) ;

			/*Set the Required CTC Value*/
			OCR2 = TIMER2_CTC_VAL ;

			/*Timer2 Compare Match Interrupt Enable*/
			#if TIMER2_CTC_INTERRUPT == DISABLE
			
				CLR_BIT(TIMSK , TIMSK_OCIE2) ;
				
			#elif TIMER2_CTC_INTERRUPT == ENABLE
			
				SET_BIT(TIMSK , TIMSK_OCIE2) ;
				
			#else
				
				#error "Wrong TIMER2_OVERFLOW_INTERRUPT Config"
				
			#endif

		#else
			
			#error "Wrong TIMER2_WAVEFORM_GENERATION_MODE Config"

		#endif

	/*Set the Required Prescaler*/
	TCCR2 &= TIMER_PRESCALER_MASK ;
	TCCR2 |= TIMER2_PRESCALER ;
}

void TIMER0_voidSetPreload (u8 Copy_u8Preload)
{
	TCNT0 = Copy_u8Preload ;
}


void TIMER2_voidSetPreload (u8 Copy_u8Preload)
{
	TCNT2 = Copy_u8Preload ;
}

void TIMER0_voidSetCTC (u8 Copy_u8CTC)
{
	OCR0 = Copy_u8CTC ;
}

void TIMER2_voidSetCTC (u8 Copy_u8CTC)
{
	OCR2 = Copy_u8CTC ;
}

u8 TIMER0_u8GetTimerCounterValue (void)
{
	return TCNT0 ;
}

u8 TIMER2_u8GetTimerCounterValue (void)
{
	return TCNT2 ;
}

/*******************************************************************************************************************/

u8 TIMER_u8SetCallBack(void (*Copy_pvCallBackFunc)(void) , u8 Copy_u8VectorID)
{
	u8 Local_u8ErrorState = 1 ;

	if (Copy_pvCallBackFunc != NULL)
	{
		TIMERS_pvCallBackFunc[Copy_u8VectorID] = Copy_pvCallBackFunc ;
	}
	else
	{
		Local_u8ErrorState = 0 ;
	}

	return Local_u8ErrorState ;
}

/*TIMER0 Normal Mode ISR*/
void __vector_11 (void)		__attribute__((signal)) ;
void __vector_11 (void)
{
	if (TIMERS_pvCallBackFunc[TIMER0_OVF_VECTOR_ID] != NULL)
	{
		TIMERS_pvCallBackFunc[TIMER0_OVF_VECTOR_ID]() ;
	}
}

/*TIMER0 CTC Mode ISR*/
void __vector_10 (void)		__attribute__((signal)) ;
void __vector_10 (void)
{
	if (TIMERS_pvCallBackFunc[TIMER0_CTC_VECTOR_ID] != NULL)
	{
		TIMERS_pvCallBackFunc[TIMER0_CTC_VECTOR_ID]() ;
	}
}

/*TIMER1 Normal Mode ISR*/
void __vector_9 (void)		__attribute__((signal)) ;
void __vector_9 (void)
{
	if (TIMERS_pvCallBackFunc[TIMER1_OVF_VECTOR_ID] != NULL)
	{
		TIMERS_pvCallBackFunc[TIMER1_OVF_VECTOR_ID]() ;
	}
}

/*TIMER1 CTCB Mode ISR*/
void __vector_8 (void)		__attribute__((signal)) ;
void __vector_8 (void)
{
	if (TIMERS_pvCallBackFunc[TIMER1_CTCB_VECTOR_ID] != NULL)
	{
		TIMERS_pvCallBackFunc[TIMER1_CTCB_VECTOR_ID]() ;
	}
}

/*TIMER1 CTCA Mode ISR*/
void __vector_7 (void)		__attribute__((signal)) ;
void __vector_7 (void)
{
	if (TIMERS_pvCallBackFunc[TIMER1_CTCA_VECTOR_ID] != NULL)
	{
		TIMERS_pvCallBackFunc[TIMER1_CTCA_VECTOR_ID]() ;
	}
}

/*TIMER1 ICU ISR*/
void __vector_6 (void)		__attribute__((signal)) ;
void __vector_6 (void)
{
	if (TIMERS_pvCallBackFunc[TIMER1_ICU_VECTOR_ID] != NULL)
	{
		TIMERS_pvCallBackFunc[TIMER1_ICU_VECTOR_ID]() ;
	}
}

/*TIMER2 Normal Mode ISR*/
void __vector_5 (void)		__attribute__((signal)) ;
void __vector_5 (void)
{
	if (TIMERS_pvCallBackFunc[TIMER2_OVF_VECTOR_ID] != NULL)
	{
		TIMERS_pvCallBackFunc[TIMER2_OVF_VECTOR_ID]() ;
	}
}

/*TIMER2 CTC Mode ISR*/
void __vector_4 (void)		__attribute__((signal)) ;
void __vector_4 (void)
{
	if (TIMERS_pvCallBackFunc[TIMER2_CTC_VECTOR_ID] != NULL)
	{
		TIMERS_pvCallBackFunc[TIMER2_CTC_VECTOR_ID]() ;
	}
}

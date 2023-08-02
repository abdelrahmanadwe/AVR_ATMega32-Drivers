/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     TIMER_config.h     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdelrahman Adwe Ali 
 *  Layer  : MCAL
 *  SWC    : TIMER
 *
 */
 

#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_


/***********************************************************************************************/
/***********************************************************************************************/
/***********************************************************************************************/

	/*Timer0 Config*/

	/*Set Timer0 Waveform Generation Mode
	 * Choose between
	 * 1. TIMER_NORMAL_MODE
	 * 2. TIMER_PWM_MODE
	 * 3. TIMER_CTC_MODE
	 * 4. TIMER_FAST_PWM_MODE
	 */
	#define TIMER0_WAVEFORM_GENERATION_MODE		TIMER_NORMAL_MODE

	/*Set the Required Prescaler
	 * Choose between
	 * - TIMER0_NO_CLOCK_SOURCE
	 * - TIMER0_NO_PRESCALER_FACTOR
	 * - TIMER0_DIVISION_FACTOR_8
	 * - TIMER0_DIVISION_FACTOR_64
	 * - TIMER0_DIVISION_FACTOR_256
	 * - TIMER0_DIVISION_FACTOR_1024
	 * - TIMER0_T0_EXTERNAL_CLOCK_SOURCE_FALLING
	 * - TIMER0_T0_EXTERNAL_CLOCK_SOURCE_RISING
	 */
	#define TIMER0_PRESCALER		TIMER0_DIVISION_FACTOR_8

	#if TIMER0_WAVEFORM_GENERATION_MODE == TIMER_NORMAL_MODE

		/*Set the Required Preload on TIMER0 Normal Mode*/
		#define TIMER0_PRELOAD_VAL					192

		/*Set Timer0 Overflow Interrupt
		 * Choose between
		 * 1. DISABLE
		 * 2. ENABLE
		 */
		#define TIMER0_OVERFLOW_INTERRUPT			ENABLE

	#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER_CTC_MODE

		/*Set the Required Compare Match Value on TIMER0 CTC Mode*/
		#define TIMER0_CTC_VAL						125

		/*Set Compare Match Output Mode
		 * Choose between
		 * 1. TIMER_OC_DISCONNECTED
		 * 2. TIMER_OC_TOGGEL
		 * 3. TIMER_OC_LOW
		 * 4. TIMER_OC_HIGH
		 */
		#define TIMER0_OC0_MODE						TIMER_OC_DISCONNECTED

		/*Set Timer0 CTC Interrupt
		 * Choose between
		 * 1. DISABLE
		 * 2. ENABLE
		 */
		#define TIMER0_CTC_INTERRUPT			ENABLE

	#else
		
		#error "Wrong TIMER0_WAVEFORM_GENERATION_MODE Config"

	#endif
	
/***********************************************************************************************/
/***********************************************************************************************/
/***********************************************************************************************/

	/*Timer2 Config*/

	/*Set Timer2 Waveform Generation Mode
	 * Choose between
	 * 1. TIMER_NORMAL_MODE
	 * 2. TIMER_PWM_MODE
	 * 3. TIMER_CTC_MODE
	 * 4. TIMER_FAST_PWM_MODE
	 */
	#define TIMER2_WAVEFORM_GENERATION_MODE		TIMER_CTC_MODE

	/*Set the Required Prescaler
	 * Choose between
	 * - TIMER2_NO_CLOCK_SOURCE
	 * - TIMER2_NO_PRESCALER_FACTOR
	 * - TIMER2_DIVISION_FACTOR_8
	 * - TIMER2_DIVISION_FACTOR_32
	 * - TIMER2_DIVISION_FACTOR_64
	 * - TIMER2_DIVISION_FACTOR_128
	 * - TIMER2_DIVISION_FACTOR_256
	 * - TIMER2_DIVISION_FACTOR_1024
	 */
	#define TIMER2_PRESCALER		TIMER2_DIVISION_FACTOR_64

	#if TIMER2_WAVEFORM_GENERATION_MODE == TIMER_NORMAL_MODE

		/*Set the Required Preload on TIMER2 Normal Mode*/
		#define TIMER2_PRELOAD_VAL					192

		/*Set Timer2 Overflow Interrupt
		 * Choose between
		 * 1. DISABLE
		 * 2. ENABLE
		 */
		#define TIMER2_OVERFLOW_INTERRUPT			ENABLE

	#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER_CTC_MODE

		/*Set the Required Compare Match Value on TIMER2 CTC Mode*/
		#define TIMER2_CTC_VAL						125

		/*Set Compare Match Output Mode
		 * Choose between
		 * 1. TIMER_OC_DISCONNECTED
		 * 2. TIMER_OC_TOGGEL
		 * 3. TIMER_OC_LOW
		 * 4. TIMER_OC_HIGH
		 */
		#define TIMER2_OC2_MODE						TIMER_OC_DISCONNECTED

		/*Set Timer2 CTC Interrupt
		 * Choose between
		 * 1. DISABLE
		 * 2. ENABLE
		 */
		#define TIMER2_CTC_INTERRUPT			ENABLE

	#else
		
		#error "Wrong TIMER2_WAVEFORM_GENERATION_MODE Config"

	#endif

#endif /* TIMER_CONFIG_H_ */

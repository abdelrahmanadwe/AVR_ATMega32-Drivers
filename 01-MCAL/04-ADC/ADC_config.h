/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     ADC_config.h      >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdelrahman Adwe Ali 
 *  Layer  : MCAL
 *  SWC    : ADC
 *
 */
 
#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

/*
 Options:-
 	 1-ADC_ENABLE
 	 2-ADC_DISABLE

 */

#define ADC_STATUS   ADC_ENABLE

/*
 Options:-
 	 1-INT_ENABLE
 	 2-INT_DISABLE

 */

#define ADC_INT_STATUS   INT_ENABLE


/*
 Options:-
 	 1-AREF
 	 2-AVCC
 	 3-INTERNAL_2_56

 */

#define ADC_VREF AVCC

/*
  Options :
 	 1-RIGHT_ADJUSTMENT
 	 2-LEFT_ADJUSTMENT

  */

#define ADC_ADJUSTMENT RIGHT_ADJUSTMENT

/*
 Options:-
 	 1-ADC_PRE_2
 	 2-ADC_PRE_4
 	 3-ADC_PRE_8
 	 4-ADC_PRE_16
 	 5-ADC_PRE_32
 	 6-ADC_PRE_64
 	 7-ADC_PRE_128

 */

#define  ADC_PRESCALLER   ADC_PRE_128

/*
 Options:-
 	 1-ADC_SINGLE_CONVERSION
 	 2-ADC_FREE_RUNNING
 	 3-ADC_ANALOG_COMPARATOR
 	 4-ADC_EXTI0
 	 5-ADC_TIM0_CTC
 	 6-ADC_TIM0_OVF
 	 7-ADC_TIM1_CTC_CHANNEL_B
 	 8-ADC_TIM1_OVF
 	 9-ADC_TIM1_ICU

 */

#define ADC_TRIGGERING_SOURCE   ADC_SINGLE_CONVERSION

#define ADC_TIMEOUT      50000

#endif /* ADC_CONFIG_H_ */


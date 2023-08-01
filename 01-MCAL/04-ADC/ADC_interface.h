/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     ADC_interface.h     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdelrahman Adwe Ali 
 *  Layer  : MCAL
 *  SWC    : ADC
 *
 */
 
#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_


#define NULL 0
#define OK   1
#define NOK  0

#define IDLE 1
#define BUSY 0

#define ADC_ENABLE  1
#define ADC_DISABLE 0

#define INT_ENABLE  1
#define INT_DISABLE 0

#define ADC_CHANNEL0            0
#define ADC_CHANNEL1            1
#define ADC_CHANNEL2            2
#define ADC_CHANNEL3            3
#define ADC_CHANNEL4            4
#define ADC_CHANNEL5            5
#define ADC_CHANNEL6            6
#define ADC_CHANNEL7            7
#define ADC_ADC0_ADC0_10x       8
#define ADC_ADC1_ADC0_10x       9
#define ADC_ADC0_ADC0_200x      10
#define ADC_ADC1_ADC0_200x      11
#define ADC_ADC2_ADC2_10x       12
#define ADC_ADC3_ADC2_10x       13
#define ADC_ADC2_ADC2_200x      14
#define ADC_ADC3_ADC2_200x      15
#define ADC_ADC0_ADC1           16   
#define ADC_ADC1_ADC1           17
#define ADC_ADC2_ADC1           18
#define ADC_ADC3_ADC1           19
#define ADC_ADC4_ADC1           20
#define ADC_ADC5_ADC1           21
#define ADC_ADC6_ADC1           22
#define ADC_ADC7_ADC1           23
#define ADC_ADC0_ADC2           24   
#define ADC_ADC1_ADC2           25
#define ADC_ADC2_ADC2           26
#define ADC_ADC3_ADC2           27
#define ADC_ADC4_ADC2           28
#define ADC_ADC5_ADC2           29
 	 
#define ADC_FREE_RUNNING        0
#define ADC_ANALOG_COMPARATOR   1
#define ADC_EXTI0               2
#define ADC_TIM0_CTC            3
#define ADC_TIM0_OVF            4
#define ADC_TIM1_CTC_CHANNEL_B  5
#define ADC_TIM1_OVF            6
#define ADC_TIM1_ICU            7
#define ADC_SINGLE_CONVERSION   8

#define ADC_PRE_2               0
#define ADC_PRE_4               2
#define ADC_PRE_8               3
#define ADC_PRE_16              4
#define ADC_PRE_32              5
#define ADC_PRE_64              6
#define ADC_PRE_128             7

#define AREF                    0
#define AVCC                    1
#define INTERNAL_2_56           3

#define RIGHT_ADJUSTMENT        0
#define LEFT_ADJUSTMENT         1


typedef struct 
{
	u8*  Channel ;
	u16* Result  ;
	u8   Size    ;
	void (*NotificationFunc)(void);
}Chain_t ;



void ADC_voidInit               ( void );

u8   ADC_u8GetResultSync        ( u8 Copy_u8Channel , u16* Copy_pu16Result );
u8   ADC_u8StartConversionAsynch( u8 Copy_u8Channel , u16* Copy_pu16Reading , void(*Copy_pvNotificationFunc)(void) );
u8   ADC_u8StartChainAsynch     ( Chain_t * Copy_Chain);

void ADC_voidEnable           (void);
void ADC_voidDisable          (void);
void ADC_voidInterruptEnable  (void);
void ADC_voidInterruptDisable (void);

u8 ADC_u8SetPrescaler (u8 Copy_u8Prescaler );

#endif /* ADC_INTERFACE_H_ */

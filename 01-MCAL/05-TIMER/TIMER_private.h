/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     TIMER_private.h     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdelrahman Adwe Ali 
 *  Layer  : MCAL
 *  SWC    : TIMER
 *
 */
 

#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

#define SREG            *((volatile u8*)0x5F)
#define TIMSK			*((volatile u8*)0X59)
#define TIFR			*((volatile u8*)0X58)

/*Timer0*/
#define TCCR0			*((volatile u8*)0X53)
#define TCNT0			*((volatile u8*)0X52)
#define OCR0			*((volatile u8*)0X5C)

/*Timer1*/
#define TCCR1A			*((volatile u8 *)0X4F)
#define TCCR1B			*((volatile u8 *)0X4E)
#define TCNT1H          *((volatile u8 *)0x4D)
#define TCNT1L          *((volatile u8 *)0x4C)
#define TCNT1			*((volatile u16*)0X4C)    /* u16 for HIGH & LOW */
#define OCR1AL          *((volatile u8 *)0x4A)
#define OCR1AH          *((volatile u8 *)0x4B)
#define OCR1A			*((volatile u16*)0X4A)
#define OCR1BL          *((volatile u8 *)0x48)
#define OCR1BH          *((volatile u8 *)0x49)
#define OCR1B			*((volatile u16*)0X48)
#define ICR1H           *((volatile u8 *)0x47)
#define ICR1L           *((volatile u8 *)0x46)
#define ICR1			*((volatile u16*)0X46)

/*Timer2*/

#define TCCR2			*((volatile u8*)0X45)
#define TCNT2			*((volatile u8*)0X44)
#define TCNT2			*((volatile u8*)0X44)
#define OCR2			*((volatile u8*)0X43)

#define WDTCR           *((volatile u8*)0x41)

/*Timer0 bits*/
#define TCCR0_FOC0      7
#define TCCR0_WGM00		6
#define TCCR0_COM01		5
#define TCCR0_COM00		4
#define TCCR0_WGM01		3
#define TCCR0_CS02      2
#define TCCR0_CS01		1
#define TCCR0_CS00		0


/*Timer2 bits*/
#define TCCR2_WGM20		6
#define TCCR2_COM21		5
#define TCCR2_COM20		4
#define TCCR2_WGM21		3

#define TIMER_PRESCALER_MASK					        0b11111000 /* This Value also could use for bit masking */

#define DISABLE						                    0
#define ENABLE						                    1

#define TIMER0_NO_CLOCK_SOURCE	 	                    0
#define TIMER0_NO_PRESCALER_FACTOR 	                    1
#define TIMER0_DIVISION_FACTOR_8	 	                2
#define TIMER0_DIVISION_FACTOR_64	                    3
#define TIMER0_DIVISION_FACTOR_256	                    4
#define TIMER0_DIVISION_FACTOR_1024	                    5
#define TIMER0_T0_EXTERNAL_CLOCK_SOURCE_FALLING	        6
#define TIMER0_T0_EXTERNAL_CLOCK_SOURCE_RISING	        7

#define TIMER1_NO_CLOCK_SOURCE	 	                    0
#define TIMER1_NO_PRESCALER_FACTOR 	                    1
#define TIMER1_DIVISION_FACTOR_8	 	                2
#define TIMER1_DIVISION_FACTOR_64	                    3
#define TIMER1_DIVISION_FACTOR_256	                    4
#define TIMER1_DIVISION_FACTOR_1024	                    5
#define TIMER1_T1_EXTERNAL_CLOCK_SOURCE_FALLING	        6
#define TIMER1_T1_EXTERNAL_CLOCK_SOURCE_RISING	        7

#define TIMER2_NO_CLOCK_SOURCE	 	                    0
#define TIMER2_NO_PRESCALER_FACTOR 	                    1
#define TIMER2_DIVISION_FACTOR_8	                    2
#define TIMER2_DIVISION_FACTOR_32 	                    3
#define TIMER2_DIVISION_FACTOR_64	                    4
#define TIMER2_DIVISION_FACTOR_128                      5
#define TIMER2_DIVISION_FACTOR_256	                    6
#define TIMER2_DIVISION_FACTOR_1024	                    7

#define TIMER_NORMAL_MODE						        0
#define TIMER_PWM_MODE							        1
#define TIMER_CTC_MODE							        2
#define TIMER_FAST_PWM_MODE						        3

#define TIMER_OC_DISCONNECTED					        0
#define TIMER_OC_TOGGEL							        1
#define TIMER_OC_LOW							        2
#define TIMER_OC_HIGH							        3

#endif /* TIMER_PRIVATE_H_ */
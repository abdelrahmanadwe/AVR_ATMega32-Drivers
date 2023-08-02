/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     TIMER_interface.h     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdelrahman Adwe Ali 
 *  Layer  : MCAL
 *  SWC    : TIMER
 *
 */
 

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

#define NULL 0

/* Define indexes for the global pointer to func for ISR  */
#define TIMER0_OVF_VECTOR_ID		11
#define TIMER0_CTC_VECTOR_ID		10

#define TIMER1_OVF_VECTOR_ID		9
#define TIMER1_CTCB_VECTOR_ID		8
#define TIMER1_CTCA_VECTOR_ID		7
#define TIMER1_ICU_VECTOR_ID		6

#define TIMER2_OVF_VECTOR_ID		5
#define TIMER2_CTC_VECTOR_ID		4

void TIMER0_voidInit               (void) ;
void TIMER0_voidSetPreload         (u8 Copy_u8Preload) ;
void TIMER0_voidSetCTC             (u8 Copy_u8CTC) ;
u8   TIMER0_u8GetTimerCounterValue (void) ;

void TIMER2_voidInit               (void) ;
void TIMER2_voidSetPreload         (u8 Copy_u8Preload) ;
void TIMER2_voidSetCTC             (u8 Copy_u8CTC) ;
u8   TIMER2_u8GetTimerCounterValue (void) ;

u8 TIMER_u8SetCallBack(void (*Copy_pvCallBackFunc)(void) , u8 Copy_u8VectorID);

#endif /* TIMER_INTERFACE_H_ */
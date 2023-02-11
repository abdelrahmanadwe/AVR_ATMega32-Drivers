/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     DIO_interface.h     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdelrahman Adwe Ali 
 *  Layer  : HAL
 *  SWC    : LED
 *
 */
 
#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_
 
#define ACTIVE_HIGH 1
#define ACTIVE_LOW  0

#define LED_PORTA 0
#define LED_PORTB 1
#define LED_PORTC 2
#define LED_PORTD 3

#define LED_PIN0 0
#define LED_PIN1 1
#define LED_PIN2 2
#define LED_PIN3 3
#define LED_PIN4 4
#define LED_PIN5 5
#define LED_PIN6 6
#define LED_PIN7 7
 
 
 
void LED_voidInit      (u8 Copy_u8Port , u8 Copy_u8Pin                       );
void LED_voidOn        (u8 Copy_u8Port , u8 Copy_u8Pin ,u8 Copy_u8ActiveState);
void LED_voidOff       (u8 Copy_u8Port , u8 Copy_u8Pin ,u8 Copy_u8ActiveState);
void LED_voidTogglePin (u8 Copy_u8Port , u8 Copy_u8Pin                       );
 
void LED_voidPortInit    (u8 Copy_u8Port );
void LED_voidTogglePort  (u8 Copy_u8Port );

void LED_voidFlashPin   (u8 Copy_u8Port , u8 Copy_u8Pin , f32 delay );
void LED_voidFlashPort  (u8 Copy_u8Port , f32 delay                 );

void LED_voidShiftLeft  (u8 Copy_u8Port , u8 Copy_u8ActiveState , f32 delay );
void LED_voidShiftRight (u8 Copy_u8Port , u8 Copy_u8ActiveState , f32 delay );
                                                                  
void LED_voidPingPong   (u8 Copy_u8Port , u8 Copy_u8ActiveState , f32 delay );

void LED_voidConverge            ( u8 Copy_u8Port , u8 Copy_u8ActiveState , f32 delay );
void LED_voidDiverge             ( u8 Copy_u8Port , u8 Copy_u8ActiveState , f32 delay );
void LED_voidConverge_Diverge    ( u8 Copy_u8Port , u8 Copy_u8ActiveState , f32 delay );
                                                                            
void LED_voidSnakeEffect         ( u8 Copy_u8Port , u8 Copy_u8ActiveState , f32 delay );

 
#endif /* LED_INTERFACE_H_ */
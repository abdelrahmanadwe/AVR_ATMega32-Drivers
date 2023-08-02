/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<     DIO_interface.h     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdelrahman Adwe Ali 
 *  Layer  : HAL
 *  SWC    : SSD
 *
 */
 
#ifndef SSD_INTERFACE_H_
#define SSD_INTERFACE_H_
 
#define SSD_COMMON_CATHODE 0
#define SSD_COMMON_ANODE   1
 
#define SSD_PIN0 0
#define SSD_PIN1 1
#define SSD_PIN2 2
#define SSD_PIN3 3
#define SSD_PIN4 4
#define SSD_PIN5 5
#define SSD_PIN6 6
#define SSD_PIN7 7

#define SSD_PORTA 0
#define SSD_PORTB 1
#define SSD_PORTC 2
#define SSD_PORTD 3

 
typedef struct 
{
	
	u8 Type       ;     /* SSD_COMMON_CATHODE or SSD_COMMON_ANODE */
	u8 Port       ;     /*[SSD_PORTA , SSD_PORTB , SSD_PORTC , SSD_PORTD]*/
	u8 EnablePort ;     /*[SSD_PORTA , SSD_PORTB , SSD_PORTC , SSD_PORTD]*/
	u8 EnablePin  ;     /*[SSD_PIN0 , SSD_PIN1 , SSD_PIN2 , SSD_PIN3 , SSD_PIN4 , SSD_PIN5 , SSD_PIN6 , SSD_PIN7]*/
	
	
}SSD_Data;


void SSD_voidInit (SSD_Data SSD_Config );
void SSD_voidEnable (SSD_Data SSD_Config );
void SSD_voidDisable (SSD_Data SSD_Config );
void SSD_voidSendNumber (SSD_Data SSD_Config , u8 Copy_u8Number );

 
#endif /* SSD_INTERFACE_H_ */
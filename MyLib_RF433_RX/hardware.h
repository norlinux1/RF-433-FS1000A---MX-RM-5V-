/*
 * hardware.h
 * Created: 08-04-2017
 *Author: Norlinux
 *http://maquina.96.lt
 *http://www.microelectronic.pt
 *https://www.facebook.com/MundoDosMicrocontroladores/
 *Released under GPLv3.
 *Please refer to LICENSE file for licensing information.
 *which can be found at http://www.gnu.org/licenses/gpl.txt
 */

#ifndef HARDWARE
#define HARDWARE
#include <avr/io.h>

#define LED_PORT          PORTD
#define LED_DDR           DDRD
#define LED_BIT           0
#define TOGGLE_LED        {LED_PORT^=_BV(LED_BIT);}


#define USART_BAUD_RATE                 (1200)

/*Harware*/
void HW_Init();	

/*USART*/
void uart_init(unsigned int baudrate);
void USART_Init( unsigned int baud );
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );
void USART_Transmit_string( unsigned char* string );
void USART_Transmit_buffer(unsigned char* buffer, unsigned char length);

#endif 

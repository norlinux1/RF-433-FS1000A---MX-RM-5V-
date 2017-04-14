/*
 * hardware.h
 * Created: 07-04-2017
 * Author: Norlinux
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

#define SWITCH_PORT       PORTD
#define SWITCH_DDR        DDRD
#define SWITCH_PIN        PIND
#define SWITCH_BIT        3

#define ESPERA_POR_SWITCH()  {while(bit_is_set(SWITCH_PIN, SWITCH_BIT));}
#define ESPERA_LOOP_SE_PRESSIONADO() {loop_until_bit_is_set(SWITCH_PIN, SWITCH_BIT);}     // nao faz nada enquanto estiver selecionado o switch
	
#define USART_BAUD_RATE                 (1200)
/*Harware*/
void HW_Init();	
/*USART*/
void USART_Init( unsigned int baud );
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );
void USART_Transmit_string( unsigned char* string );
void USART_Transmit_buffer(unsigned char* buffer, unsigned char length);

/* ADC */
void ADC_Init();
int Read_ADC(uint8_t ADC_NR);
int ler_AD(uint8_t ADC_NR);
#endif 

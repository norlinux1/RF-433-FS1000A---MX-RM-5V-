/*
 * hardware.c
 * Created: 07-04-2017
 * Author: Norlinux
 *http://maquina.96.lt
 *http://www.microelectronic.pt
 *https://www.facebook.com/MundoDosMicrocontroladores/
 *Released under GPLv3.
 *Please refer to LICENSE file for licensing information.
 *which can be found at http://www.gnu.org/licenses/gpl.txt
 */
#include <avr/io.h>
#include <avr/interrupt.h>  
#include <avr/sfr_defs.h>	//para bit especiais
#include <math.h>
#include "public_global.h"
#include "hardware.h"
// ATmega8 MCU
void HW_Init()
{
	SWITCH_DDR&=~_BV(SWITCH_BIT);
	SWITCH_PORT|=_BV(SWITCH_BIT);
}




/**
 * Initialize USART
 */
void USART_Init( unsigned int baud )
{
    /* Set baud rate */
    UBRRH = (F_CPU/(baud*16L)-1) >> 8; // Calculate register content to gain proper transmission speed
    UBRRL = (unsigned char)(F_CPU/(baud*16L)-1);
    /* Enable Interrupts on receive, Enable Receiver and Transmitter */
    UCSRB = (1<<RXCIE)|(1<<RXEN)|(1<<TXEN);
    /* Set frame format: 8data, 1stop bit */
    UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
}

/**
 * Transmit single byte
 */
void USART_Transmit( unsigned char data )
{
    /* Wait for empty transmit buffer */
    while ( !( UCSRA & (1<<UDRE)) );
    /* Put data into buffer, sends the data */
    UDR = data;
}

/**
 * Receive single byte
 */
unsigned char USART_Receive( void )
{
    /* Wait for data to be received */
    while ( !(UCSRA & (1<<RXC)) );
    /* Get and return received data from buffer */
    return UDR;
}


/**
 * Transmit string
 * Precondition: String have to be zero terminated
 */
void USART_Transmit_string( unsigned char* string )
{
    while(*string)
    {
        USART_Transmit(*string++);
        //string++;
    }
}


/**
 * Transmit buffer data
 */
void USART_Transmit_buffer(unsigned char* buffer, unsigned char length)
{
    unsigned char i = 0;
    for(i = 0; i < length; i++)
    {
        USART_Transmit(buffer[i]);
        //string++;
    }
}

void ADC_Init()
{
	ADMUX=(1<<REFS0);                                  	// For Aref=AVcc;
	//8Mhz/64= 125Khz ( ADLAR 1 to get only 8 bits ) (which is in range of 50KHz to 200KHz).
	ADCSRA|= 1<<ADEN | 1<<ADPS2 | 1<< ADPS1;
}

int Read_ADC(uint8_t ADC_NR)
{
	ADMUX = (ADMUX & 0xF0) | (ADC_NR & 0x0F);   //select channel (MUX0-4 bits)
	ADCSRA |= (1<<ADSC);			// start conversion
	while((ADCSRA & (1<<ADSC))!=0); // wait for end of conversion
	return (ADC);
}

int ler_AD(uint8_t ADC_NR)
{
	ADMUX = (ADMUX & 0xF0) | (ADC_NR & 0x0F);   //select channel (MUX0-4 bits)
	ADCSRA |= (1<<ADSC);                        // inicia a conversão
	while(ADCSRA & 0x40);                       //  while( ADCSRA & (1<<ADSC) );
	//return ADC;
	return (ADCW);
}

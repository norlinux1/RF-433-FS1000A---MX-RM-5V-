/*
 * hardware.c
 * Created: 08-04-2017
 *Author: Norlinux
 *http://maquina.96.lt
 *http://www.microelectronic.pt
 *https://www.facebook.com/MundoDosMicrocontroladores/
 *Released under GPLv3.
 *Please refer to LICENSE file for licensing information.
 *which can be found at http://www.gnu.org/licenses/gpl.txt
 */
#include <avr/io.h>
#include <avr/interrupt.h>  /* for sei() */
#include <avr/sfr_defs.h>	//para bit especiais
#include <math.h>
#include "public_global.h"
#include "hardware.h"
// ATmega8 board
void HW_Init()
{
LED_DDR  |=  _BV(LED_BIT);
LED_PORT &= ~_BV(LED_BIT);
sei();
}




/**
 * Initialize USART
 */
void USART_Init( unsigned int baud )
{
    /* Set baud rate */
    UBRR0H = (F_CPU/(baud*16L)-1) >> 8;  // Calculate register content to gain proper transmission speed
    UBRR0L = (unsigned char)(F_CPU/(baud*16L)-1);
    /* Enable Interrupts on receive, Enable Receiver and Transmitter */
    UCSR0B = (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);
    /* Set frame format: 8data, 1stop bit */
    //UCSR0C = (1<<URSEL)|(1<<UCSZ01)|(1<<UCSZ00);
	UCSR0C = (3<<UCSZ00);
}


void uart_init(unsigned int baudrate)
{
	/* Set baud rate */
	if ( baudrate & 0x8000 )
	{
		UCSR0A = (1<<U2X0);  //Enable 2x speed
		baudrate &= ~0x8000;
	}
	UBRR0H = (unsigned char)(baudrate>>8);
	UBRR0L = (unsigned char) baudrate;

	/* Enable USART receiver and transmitter and receive complete interrupt */
	UCSR0B = _BV(RXCIE0)|(1<<RXEN0)|(1<<TXEN0);

	/* Set frame format: asynchronous, 8data, no parity, 1stop bit */

	UCSR0C = (3<<UCSZ00);
}/* uart_init */
/**
 * Transmit single byte
 */
void USART_Transmit( unsigned char data )
{
    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)) );
    /* Put data into buffer, sends the data */
    UDR0 = data;
}

/**
 * Receive single byte
 */
unsigned char USART_Receive( void )
{
    /* Wait for data to be received */
    while ( !(UCSR0A & (1<<RXC)) );
    /* Get and return received data from buffer */
    return UDR0;
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

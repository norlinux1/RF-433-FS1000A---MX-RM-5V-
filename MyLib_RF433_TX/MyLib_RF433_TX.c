/*
 * MyLib_RF433_TX.c
 * Created: 07-04-2017
 * Author: Norlinux
 *http://maquina.96.lt
 *http://www.microelectronic.pt
 *https://www.facebook.com/MundoDosMicrocontroladores/
 *Released under GPLv3.
 *Please refer to LICENSE file for licensing information.
 *which can be found at http://www.gnu.org/licenses/gpl.txt
 */

/*MCU ATmega8 - 8 Mhz*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <stdint.h>
#include "public_global.h"
#include "hardware.h"
#include "tarefas.h"
#define ESPERA() _delay_ms(180)
int main(void)
{
	HW_Init();
	USART_Init(USART_BAUD_RATE);
	ADC_Init();

	while(1)
    {	
	CheckBotao();
    }
}
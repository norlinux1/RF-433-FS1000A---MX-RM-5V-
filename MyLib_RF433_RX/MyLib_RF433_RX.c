/*
 * MyLib_RF433_RX.c
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
#include <avr/interrupt.h>
#include "hardware.h"
#include "Tarefas.h"
#include "lcd/lcd_lib.h"

int main(void)
{
    HW_Init();
    USART_Init(USART_BAUD_RATE);
	LCDinit();
	while(1)
    {

    }
}

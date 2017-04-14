/*
 *Tarefas.c
 *Created: 10-04-2017
 *Author: Norlinux
 *http://maquina.96.lt
 *http://www.microelectronic.pt
 *https://www.facebook.com/MundoDosMicrocontroladores/
 *Released under GPLv3.
 *Please refer to LICENSE file for licensing information.
 *which can be found at http://www.gnu.org/licenses/gpl.txt
 */

#include <avr/interrupt.h>
#include "public_global.h"
#include "Tarefas.h"
#include "hardware.h"
#include "lcd/lcd_lib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ****************** DEFINIÇÕES ***********************************************
#define TAM_BUFFER_RECECCAO       (32)
// ****************** Global variaveis *****************************************
volatile unsigned char avucDadosRecebidos[TAM_BUFFER_RECECCAO];

// USART part
volatile unsigned char vucUltimoByte    = 0;
volatile unsigned int  vuiRXByteCont    = 0;


ISR(USART0_RX_vect)
{
	//unsigned char ucByteRX = UDR0;
	unsigned char ucByteRX = USART_Receive();
	char buffer0[20]={};
	char buffer1[20]={};
	if((vucUltimoByte == '*') && (ucByteRX == ':') && (vuiRXByteCont == 0))    //Detect Start frame
	{
		avucDadosRecebidos[vuiRXByteCont++] = vucUltimoByte;

	}

	if(vuiRXByteCont > 0)                                                // If true then start collecting data
	{
		avucDadosRecebidos[vuiRXByteCont++] = ucByteRX;
					
		if(vuiRXByteCont == TAM_BUFFER_RECECCAO) {
			vuiRXByteCont--;
		}

	}

	if((vucUltimoByte == ':') && (ucByteRX == '#')                                    // Detect end frame
	&& (vuiRXByteCont > TAM_BYTE)){
		unsigned char* pucChecksum    = 0;
		pucChecksum = malloc(TAM_BYTE);
		STRUCT_TRAMA stTrama = stDescoderTrama((unsigned char*)avucDadosRecebidos, (unsigned char)vuiRXByteCont);
		//memcpy(pucChecksum,stTrama.pucVRx,stTrama.ucVRxTam);
		//memcpy(pucChecksum + stTrama.ucVRxTam,stTrama.pucVRy,stTrama.ucVRyTam);
		sprintf((char*)pucChecksum,"%s%s",stTrama.pucVRx,stTrama.pucVRy);
		//unsigned int uiCrcTmp = uiCRC16(pucChecksum, strlen((char*)pucChecksum));          // Calculate CRC
		unsigned int uiCrcTmp = uiCRC16(pucChecksum, TAM_BYTE);          // Calculate CRC
		sprintf(buffer0,"%s",stTrama.pucVRx);
		//LCDGotoXY(2,0);
		//LCDstring((uint8_t*)buffer0,stTrama.ucVRxTam);
		LCDprintXY(buffer0,2,0);
		sprintf(buffer1,"%s",stTrama.pucVRy);
		//LCDGotoXY(2,1);
		//LCDstring((uint8_t*)buffer1,stTrama.ucVRyTam);
		LCDprintXY(buffer1,2,1);
		vuiRXByteCont = 0;
		free(pucChecksum);
		if((stTrama.ucSwitch ==TRUE) && (uiCrcTmp == stTrama.uiCrc16))  
		{
			TOGGLE_LED;
			free(pucChecksum);
		}
	
		
	}

	vucUltimoByte = ucByteRX;
}

STRUCT_TRAMA stDescoderTrama(unsigned char* pucTramaDados, unsigned char ucLength)
{
	STRUCT_TRAMA stTrama = {};
		const char ccCardinal[2] = "#";
		const char cc2Pontos[2]  = ":";
		char *pcTemp;
		
		
		pucTramaDados[BIT_SWITCH_POS_INICIO] -= '0';

		stTrama.ucSwitch = pucTramaDados[BIT_SWITCH_POS_INICIO]*1 ;

		pcTemp         = strtok((char*)(pucTramaDados + (TAM_BYTE>>1)) ,ccCardinal);
		stTrama.pucVRx = (unsigned char*)pcTemp;
		stTrama.ucVRxTam = (TAM_BYTE>>1);
		stTrama.uiCrc16  = pucTramaDados[BIT_CRC16_MSB_POS] << TAM_BYTE;
		stTrama.uiCrc16 += pucTramaDados[BIT_CRC16_LSB_POS];
		pcTemp           = strtok((char*)(pucTramaDados + TRAMA_DATA_VRy) ,cc2Pontos);
		stTrama.pucVRy   = (unsigned char*)pcTemp;
		stTrama.ucVRyTam = (TAM_BYTE>>1);

		return stTrama;
}

unsigned int uiCRC16(unsigned char* pucDadosCRC, unsigned char ucTam)
{
    unsigned int uiCRC16n = 0xFFFF;
    unsigned int uiTmp;

    for(unsigned char k = 0; k < ucTam; k++)
    {
        if(*pucDadosCRC == 0){
            uiTmp = (unsigned int) 0xFE;  
        }else{
            uiTmp = (unsigned int) *pucDadosCRC++;
        }
        uiCRC16n ^= uiTmp;
        for(unsigned char i = 0; i < 8; i++){                                   // Suppose magic 8 is bit counts
            uiCRC16n >>= 1;
            if(uiCRC16n & 0x0001){
                uiCRC16n ^= 0xA001;                                             // EXOR if first bit is 1
            }
        }
    }
    return uiCRC16n;
}

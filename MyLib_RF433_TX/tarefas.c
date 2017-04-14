/*
 * tasks.c
 * Created: 07-04-2017
 * Author: Norlinux
 *http://maquina.96.lt
 *http://www.microelectronic.pt
 *https://www.facebook.com/MundoDosMicrocontroladores/
 *Released under GPLv3.
 *Please refer to LICENSE file for licensing information.
 *which can be found at http://www.gnu.org/licenses/gpl.txt
 */

#include "public_global.h"
#include "tarefas.h"
#include "hardware.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct{
	unsigned char   ucSwitch;      // (inteiro switch 0-1)
	unsigned char*  pucVRx;        // ponteiro ADCx buffer
	unsigned char   ucVRxTam;      // Tamanho ponteiro ADCx
	unsigned int    uiCrc16;       // CRC16  (16-bit)
	unsigned char*  pucVRy;        // ponteiro ADC y buffer
	unsigned char   ucVRyTam;      // Tamanho ponteiro ADCx
}STRUCT_TRAMA;


#define INICIO_SEQ_TAM                  (2)              // Tamanho Inicio Sequência "*:"
#define FIM_SEQ_TAM                     (2)              // Tamanho Fim Sequência ":#"
#define CONCATENAR_SEQ_TAM              (1)              // Tamanho delimitador "#"
#define BIT_SWITCH_POS_INICIO           (2)              // Posicionamento do bit switch
#define BIT_TAM_SWITCH                  (1)              // Tamanho string do switch
#define BIT_CRC16_LSB_POS               (9)              // Posicionamento da String CRC16 (LSB)
#define BIT_CRC16_MSB_POS               (10)             // Posicionamento da String CRC16 (MSB)
#define TRAMA_CRC16_TAMANHO             (2)              // Tamanho da String CRC16
#define TRAMA_DATA_VRx                  (4)              // Inicio do Posicionamneto da String VRx
#define TAM_DATA_VRx_FIM                (7)              // Fim do Posicionamneto da String VRx
#define TRAMA_DATA_VRy                  (12)             // Inicio do Posicionamneto da String VRy
#define _16_BIT_LSB_MASK                (0x00FF)         // mask for 16-bit value (UINT) for LSB
#define TAM_BYTE                        (8)              // number of bits in byte
#define INICIO_SEQ                       "*:"            // String inicio sequencia "*:"
#define FIM_SEQ                          ":#"            // String fim sequencia ":#"
#define CONCATENAR_SEQ                   "#"             // delimitador da sequencia "#"

unsigned int uiCRC16(unsigned char* pucDadosCRC, unsigned char ucTam);
unsigned char  ucTramaEncoder(STRUCT_TRAMA stTrama, unsigned char * pucBufferDados);

void CheckBotao(void){
	char  cLerVRx[8] = {};
	char  cLerVRy[8] = {};
	STRUCT_TRAMA stTrama = {};
	unsigned char  ucTamTrama    = 0;
	unsigned char* pucChecksum    = 0;
	unsigned char* pucBufferDados = NULL;
	while(TRUE){
		ESPERA_POR_SWITCH();
		pucChecksum = malloc(TAM_BYTE);
		stTrama.ucSwitch     = TRUE;
		sprintf(cLerVRx,"%04i",ler_AD(0));                                                           //rand()
		stTrama.pucVRx       = (unsigned char *)cLerVRx;
		stTrama.ucVRxTam     = strlen(cLerVRy);
		sprintf(cLerVRy,"%04i",ler_AD(1));
		stTrama.pucVRy       = (unsigned char *)cLerVRy;
		stTrama.ucVRyTam     = strlen(cLerVRy);
		memcpy(pucChecksum,stTrama.pucVRx,stTrama.ucVRxTam);
		memcpy(pucChecksum + stTrama.ucVRxTam,stTrama.pucVRy,stTrama.ucVRyTam);
		//stTrama.uiCrc16      = uiCRC16(pucChecksum, strlen((char*)pucChecksum));
		stTrama.uiCrc16      = uiCRC16(pucChecksum, TAM_BYTE);
		ucTamTrama = ucTramaEncoder(stTrama, pucBufferDados);
		if (ucTamTrama!=0){free(pucBufferDados);}
		else {/*error*/}
		free(pucChecksum);
		ESPERA_LOOP_SE_PRESSIONADO();
	}
}

void JoyStick(uint16_t VRx, uint16_t VRy ,uint8_t Switch ){
	STRUCT_TRAMA stTrama = {};
		char  cLerVRx[8] = {};
		char  cLerVRy[8] = {};
	unsigned char  ucTamTrama    = 0;
	unsigned char* pucChecksum    = 0;
	unsigned char* pucBufferDados = NULL;
		pucChecksum = malloc(TAM_BYTE);
		stTrama.ucSwitch         = Switch;
		sprintf(cLerVRx,"%04i",VRx);                                                           //rand()
		stTrama.pucVRx       = (unsigned char *)cLerVRx;
		stTrama.ucVRxTam     = strlen(cLerVRx);
		sprintf(cLerVRy,"%04i",VRy);
		stTrama.pucVRy       = (unsigned char *)cLerVRy;
		stTrama.ucVRyTam     = strlen(cLerVRy);
		memcpy(pucChecksum,stTrama.pucVRx,stTrama.ucVRxTam);
		memcpy(pucChecksum + stTrama.ucVRxTam,stTrama.pucVRy,stTrama.ucVRyTam);
		//stTrama.uiCrc16      = uiCRC16(pucChecksum, strlen((char*)pucChecksum));
		stTrama.uiCrc16      = uiCRC16(pucChecksum, TAM_BYTE);
		ucTamTrama = ucTramaEncoder(stTrama, pucBufferDados);
		if (ucTamTrama!=0){free(pucBufferDados);}
		else {/*error*/}
		free(pucChecksum);
}

unsigned char  ucTramaEncoder(STRUCT_TRAMA stTrama, unsigned char * pucBufferDados){
       // *:s#VRx#LM#VRy:#

    unsigned char  ucTamTrama =  INICIO_SEQ_TAM                                // *:
                        + BIT_TAM_SWITCH                                       // x
                        + CONCATENAR_SEQ_TAM                                     // #
                        + stTrama.ucVRxTam                                      // Tamanho VRx
                        + CONCATENAR_SEQ_TAM                                     // #
                        + TRAMA_CRC16_TAMANHO                                    // LM
                        + CONCATENAR_SEQ_TAM                                     // #
                        + stTrama.ucVRyTam                                      // Tamanho VRy
                        + FIM_SEQ_TAM;                                         // :#

    pucBufferDados = malloc(ucTamTrama);

    if(pucBufferDados != NULL){
        sprintf((char*)pucBufferDados, INICIO_SEQ"%i"CONCATENAR_SEQ, stTrama.ucSwitch); // *:x#
		memcpy((pucBufferDados + TRAMA_DATA_VRx),                        stTrama.pucVRx, stTrama.ucVRxTam);           //pppp# VRx
		memcpy((pucBufferDados + TRAMA_DATA_VRx + stTrama.ucVRyTam), CONCATENAR_SEQ,        TRAMA_DATA_VRx);          // :#
		pucBufferDados[BIT_CRC16_LSB_POS] =  stTrama.uiCrc16                 & _16_BIT_LSB_MASK;                      // L
        pucBufferDados[BIT_CRC16_MSB_POS] = (stTrama.uiCrc16 >> TAM_BYTE)    & _16_BIT_LSB_MASK;                      // M
        memcpy((pucBufferDados + BIT_CRC16_MSB_POS + 1),                 CONCATENAR_SEQ,   CONCATENAR_SEQ_TAM);       // #
        memcpy((pucBufferDados + TRAMA_DATA_VRy),                       stTrama.pucVRy, stTrama.ucVRyTam);            // VRy
        memcpy((pucBufferDados + TRAMA_DATA_VRy + stTrama.ucVRyTam), FIM_SEQ,        FIM_SEQ_TAM);                    // :#
		USART_Transmit_buffer(pucBufferDados, ucTamTrama);
    }else{ucTamTrama = 0;}
    return ucTamTrama;
}


unsigned int uiCRC16(unsigned char* pucDadosCRC, unsigned char ucTam)
{
    unsigned int uiCRC16n = 0xFFFF;
    unsigned int uiTmp;

    for(unsigned char k = 0; k < ucTam; k++)
    {
        if(*pucDadosCRC == 0){
            uiTmp = (unsigned int) 0xFE;   //ZERO_SIGN
        }else{
            uiTmp = (unsigned int) *pucDadosCRC++;
        }
        uiCRC16n ^= uiTmp;
        for(unsigned char i = 0; i < 8; i++){                                           // Suppose magic 8 is bit counts
            uiCRC16n >>= 1;
            if(uiCRC16n & 0x0001){
                uiCRC16n ^= 0xA001;                                             // EXOR if first bit is 1
            }
        }
    }

    //*pucDadosCRC++ = (unsigned char) uiCRC16n;                                         // LSB of CRC16
    //*pucDadosCRC   = uiCRC16n >> 8;                                            // MSB of CRC16
    return uiCRC16n;
}
/*
 *Tarefas.h
 *Created: 10-04-2017
 *Author: Norlinux
 *http://maquina.96.lt
 *http://www.microelectronic.pt
 *https://www.facebook.com/MundoDosMicrocontroladores/
 *Released under GPLv3.
 *Please refer to LICENSE file for licensing information.
 *which can be found at http://www.gnu.org/licenses/gpl.txt
 */


#ifndef TAREFAS_H_
#define TAREFAS_H_

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

typedef struct{
	unsigned char   ucSwitch;      // (inteiro switch 0-1)
	unsigned char*  pucVRx;        // ponteiro ADCx buffer
	unsigned char   ucVRxTam;      // Tamanho ponteiro ADCx
	unsigned int    uiCrc16;       // CRC16  (16-bit)
	unsigned char*  pucVRy;        // ponteiro ADC y buffer
	unsigned char   ucVRyTam;      // Tamanho ponteiro ADCy
}STRUCT_TRAMA;



unsigned int   uiCRC16(unsigned char* pucDadosCRC, unsigned char ucTam);
unsigned char  ucTramaEncoder(STRUCT_TRAMA stTrama, unsigned char * pucBufferDados);
STRUCT_TRAMA   stDescoderTrama(unsigned char* pucTramaDados, unsigned char ucLength);





#endif /* TAREFAS_H_ */
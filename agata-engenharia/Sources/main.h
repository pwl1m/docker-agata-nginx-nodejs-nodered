/*
 * main.h
 *
 *  Created on: 07/11/2019
 *      Author: Alexandre Voigt da Poian
 */

#ifndef SOURCES_MAIN_H_
#define SOURCES_MAIN_H_

#include "AdcLdd1.h"
#include "AdcLdd2.h"
#include "AGUARDA.h"
#include "ASerialLdd1.h"
#include "ASerialLdd2.h"
#include "BitsIoLdd4.h"
#include "BitsIoLdd5.h"
#include "CAN.h"
#include "Control_LCD.h"
#include "Cpu.h"
#include "DADOS.h"
#include "DEBOUNCING_1ms.h"
#include "Events.h"
#include "FLASH_INTERNA.h"
#include "funcao.h"
#include "GPIO_PDD.h"
#include "IntFlashLdd1.h"
#include "IO_Map.h"
#include "lcd.h"
#include "PE_Const.h"
#include "PE_Error.h"
#include "PE_Types.h"
#include "PORT_PDD.h"
#include "PORTA.h"
#include "PORTB.h"
#include "PORTC.h"
#include "PORTD.h"
#include "PORTE.h"
#include "POTENCIOMETRO_DIGITAL.h"
#include "PWM_BUZZER.h"
#include "PWM_INFRAS.h"
#include "PWM_RX1.h"
#include "PWM_RX2.h"
#include "PWM_TX.h"
#include "PwmLdd1.h"
#include "PwmLdd2.h"
#include "PwmLdd3.h"
#include "PwmLdd4.h"
#include "PwmLdd5.h"
#include "PWMS.h"
#include "RTC1.h"
#include "SERIAL_ETHERNET.h"
#include "SINAL_DAS_AREAS.h"
#include "SMasterLdd1.h"
#include "telas.h"
#include "TEMPORIZADOR_10ms.h"
#include "TEMPORIZADOR_100ms.h"
#include "TEMPORIZADOR_1s.h"
#include "TENSAO_DAS_AREAS.h"
#include "TimerIntLdd1.h"
#include "TimerIntLdd2.h"
#include "TimerIntLdd3.h"
#include "TimerIntLdd4.h"
#include "TU1.h"
#include "TU2.h"
#include "TU3.h"
#include "TU4.h"
#include "TU5.h"
#include "USB_PC.h"
#include "stdio.h"
#include "string.h"
#include "stdint.h"
#include "aes.h"

//Definições das entradas ou saidas para facilitar a utilização dos PDDs INPUTS e OUTPUTs

/********************************** ENTRADAS **********************************/
//Bits das ENTRADAS
//| 8| 4| 2| 1|/| 8| 4| 2| 1|***| 8| 4| 2| 1|/| 8| 4| 2| 1|***| 8| 4| 2| 1|/| 8| 4| 2| 1|***| 8| 4| 2| 1|/| 8| 4| 2| 1| -
//|31|30|29|28|/|27|26|25|24|***|23|22|21|20|/|19|18|17|16|***|15|14|13|12|/|11|10|09|08|***|07|06|05|04|/|03|02|01|00| - Pino do microcontrolador - neste exemplo tecla decrementa é pino PTB0
//| 0| 0| 0| 0|/| 0| 1| 0| 0|***| 0| 0| 0| 0|/| 0| 0| 0| 0|***| 0| 0| 0| 0|/| 0| 0| 0| 0|***| 0| 0| 0| 0|/| 0| 0| 0| 0| - Exemplo para tecla decrementa em binario
//|     0     |/|     4     |***|     0     |/|     0     |***|     0     |/|     0     |***|     0     |/|     0     | - Exemplo para tecla decrementa em hexadecimal
/******************************************************************************/

#define PGDM_FECHADA											1
#define PGDM_ABERTA												0
#define BURLA													1
#define DETECCAO												0
/************************************* AC *************************************/
#define CONST_LIMITE_INFERIOR_AC						108
#define LIG												1
#define DES												0
/******************************************************************************/

/************************************* AD *************************************/
#define NIVEL_MAXIMO									65535
#define NIVEL_ZERO										32768
#define SINAL_LIMITE_AREA								200
/******************************************************************************/

/******************************* ALARME VISUAL ********************************/
#define _DESABILITA										0
#define _HABILITA										1
#define DESLIGADO										0
#define LIGADO											1
#define SA1_SET											GPIO_PDD_SetPortDataOutputMask(PTD_BASE_PTR,GPIO_PDD_PIN_8)
#define SA1_CLEAR										GPIO_PDD_ClearPortDataOutputMask(PTD_BASE_PTR,GPIO_PDD_PIN_8)
#define SA2_SET											GPIO_PDD_SetPortDataOutputMask(PTD_BASE_PTR,GPIO_PDD_PIN_9)
#define SA2_CLEAR										GPIO_PDD_ClearPortDataOutputMask(PTD_BASE_PTR,GPIO_PDD_PIN_9)
#define SA3_SET											GPIO_PDD_SetPortDataOutputMask(PTD_BASE_PTR,GPIO_PDD_PIN_10)
#define SA3_CLEAR										GPIO_PDD_ClearPortDataOutputMask(PTD_BASE_PTR,GPIO_PDD_PIN_10)
#define SA4_SET											GPIO_PDD_SetPortDataOutputMask(PTD_BASE_PTR,GPIO_PDD_PIN_11)
#define SA4_CLEAR										GPIO_PDD_ClearPortDataOutputMask(PTD_BASE_PTR,GPIO_PDD_PIN_11)
#define SA5_SET											GPIO_PDD_SetPortDataOutputMask(PTD_BASE_PTR,GPIO_PDD_PIN_12)
#define SA5_CLEAR										GPIO_PDD_ClearPortDataOutputMask(PTD_BASE_PTR,GPIO_PDD_PIN_12)
#define SA6_SET											GPIO_PDD_SetPortDataOutputMask(PTD_BASE_PTR,GPIO_PDD_PIN_13)
#define SA6_CLEAR										GPIO_PDD_ClearPortDataOutputMask(PTD_BASE_PTR,GPIO_PDD_PIN_13)
#define SA7_SET											GPIO_PDD_SetPortDataOutputMask(PTD_BASE_PTR,GPIO_PDD_PIN_14)
#define SA7_CLEAR										GPIO_PDD_ClearPortDataOutputMask(PTD_BASE_PTR,GPIO_PDD_PIN_14)
#define SA8_SET											GPIO_PDD_SetPortDataOutputMask(PTD_BASE_PTR,GPIO_PDD_PIN_15)
#define SA8_CLEAR										GPIO_PDD_ClearPortDataOutputMask(PTD_BASE_PTR,GPIO_PDD_PIN_15)

#define	ACENDE_AREA1									SA1_SET;//SA1_SET;SA2_CLEAR;SA3_CLEAR;SA4_CLEAR;SA5_CLEAR;SA6_CLEAR;SA7_CLEAR;SA8_CLEAR
#define	ACENDE_AREA2									SA2_SET;//SA1_CLEAR;SA2_SET;SA3_CLEAR;SA4_CLEAR;SA5_CLEAR;SA6_CLEAR;SA7_CLEAR;SA8_CLEAR
#define	ACENDE_AREA3									SA3_SET;//SA1_CLEAR;SA2_CLEAR;SA3_SET;SA4_CLEAR;SA5_CLEAR;SA6_CLEAR;SA7_CLEAR;SA8_CLEAR
#define	ACENDE_AREA4									SA4_SET;//SA1_CLEAR;SA2_CLEAR;SA3_CLEAR;SA4_SET;SA5_CLEAR;SA6_CLEAR;SA7_CLEAR;SA8_CLEAR
#define	ACENDE_AREA5									SA5_SET;//SA1_CLEAR;SA2_CLEAR;SA3_CLEAR;SA4_CLEAR;SA5_SET;SA6_CLEAR;SA7_CLEAR;SA8_CLEAR
#define	ACENDE_AREA6									SA6_SET;//SA1_CLEAR;SA2_CLEAR;SA3_CLEAR;SA4_CLEAR;SA5_CLEAR;SA6_SET;SA7_CLEAR;SA8_CLEAR
#define	ACENDE_AREA7									SA7_SET;//SA1_CLEAR;SA2_CLEAR;SA3_CLEAR;SA4_CLEAR;SA5_CLEAR;SA6_CLEAR;SA7_SET;SA8_CLEAR
#define	ACENDE_AREA8									SA8_SET;//SA1_CLEAR;SA2_CLEAR;SA3_CLEAR;SA4_CLEAR;SA5_CLEAR;SA6_CLEAR;SA7_CLEAR;SA8_SET

#define	APAGA_AREAS										SA1_CLEAR;SA2_CLEAR;SA3_CLEAR;SA4_CLEAR;SA5_CLEAR;SA6_CLEAR;SA7_CLEAR;SA8_CLEAR
#define ACENDE_AREAS									SA1_SET;SA2_SET;SA3_SET;SA4_SET;SA5_SET;SA6_SET;SA7_SET;SA8_SET
/******************************************************************************/

/*********************************** ÁREAS ************************************/
#define TODAS_AREAS										0
#define AREA_1											1
#define AREA_2											2
#define AREA_3											3
#define AREA_4											4
#define AREA_5											5
#define AREA_6											6
#define AREA_7											7
#define AREA_8											8
#define AREA1											0
#define AREA2											1
#define AREA3											2
#define AREA4											3
#define AREA5											4
#define AREA6											5
#define AREA7											6
#define AREA8											7
#define A01												0x01
#define A02												0x02
#define A03												0x04
#define A04												0x08
#define A05												0x10
#define A06												0x20
#define A07												0x40
#define A08												0x80
#define AREA01_DETECTADA								(areas_detectadas & 0x01)
#define AREA02_DETECTADA				 				(areas_detectadas & 0x02)
#define AREA03_DETECTADA								(areas_detectadas & 0x04)
#define AREA04_DETECTADA								(areas_detectadas & 0x08)
#define AREA05_DETECTADA								(areas_detectadas & 0x10)
#define AREA06_DETECTADA								(areas_detectadas & 0x20)
#define AREA07_DETECTADA								(areas_detectadas & 0x40)
#define AREA08_DETECTADA								(areas_detectadas & 0x80)
/******************************************************************************/

/********************************** BARGRAPH **********************************/
#define N_B1_SET										GPIO_PDD_SetPortDataOutputMask(PTC_BASE_PTR,GPIO_PDD_PIN_18)
#define N_B1_CLEAR										GPIO_PDD_ClearPortDataOutputMask(PTC_BASE_PTR,GPIO_PDD_PIN_18)
#define N_B2_SET										GPIO_PDD_SetPortDataOutputMask(PTC_BASE_PTR,GPIO_PDD_PIN_19)
#define N_B2_CLEAR										GPIO_PDD_ClearPortDataOutputMask(PTC_BASE_PTR,GPIO_PDD_PIN_19)
#define N_B3_SET										GPIO_PDD_SetPortDataOutputMask(PTD_BASE_PTR,GPIO_PDD_PIN_0)
#define N_B3_CLEAR										GPIO_PDD_ClearPortDataOutputMask(PTD_BASE_PTR,GPIO_PDD_PIN_0)
#define N_B4_SET										GPIO_PDD_SetPortDataOutputMask(PTD_BASE_PTR,GPIO_PDD_PIN_1)
#define N_B4_CLEAR										GPIO_PDD_ClearPortDataOutputMask(PTD_BASE_PTR,GPIO_PDD_PIN_1)
#define N_B5_SET										GPIO_PDD_SetPortDataOutputMask(PTD_BASE_PTR,GPIO_PDD_PIN_2)
#define N_B5_CLEAR										GPIO_PDD_ClearPortDataOutputMask(PTD_BASE_PTR,GPIO_PDD_PIN_2)
#define N_B6_SET										GPIO_PDD_SetPortDataOutputMask(PTD_BASE_PTR,GPIO_PDD_PIN_3)
#define N_B6_CLEAR										GPIO_PDD_ClearPortDataOutputMask(PTD_BASE_PTR,GPIO_PDD_PIN_3)
#define N_B7_SET										GPIO_PDD_SetPortDataOutputMask(PTD_BASE_PTR,GPIO_PDD_PIN_4)
#define N_B7_CLEAR										GPIO_PDD_ClearPortDataOutputMask(PTD_BASE_PTR,GPIO_PDD_PIN_4)
#define N_B8_SET										GPIO_PDD_SetPortDataOutputMask(PTD_BASE_PTR,GPIO_PDD_PIN_5)
#define N_B8_CLEAR										GPIO_PDD_ClearPortDataOutputMask(PTD_BASE_PTR,GPIO_PDD_PIN_5)
#define N_B9_SET										GPIO_PDD_SetPortDataOutputMask(PTD_BASE_PTR,GPIO_PDD_PIN_6)
#define N_B9_CLEAR										GPIO_PDD_ClearPortDataOutputMask(PTD_BASE_PTR,GPIO_PDD_PIN_6)
#define N_B10_SET										GPIO_PDD_SetPortDataOutputMask(PTD_BASE_PTR,GPIO_PDD_PIN_7)
#define N_B10_CLEAR										GPIO_PDD_ClearPortDataOutputMask(PTD_BASE_PTR,GPIO_PDD_PIN_7)

#define ACENDE_NIVEL0  									N_B1_CLEAR;N_B2_CLEAR;N_B3_CLEAR;N_B4_CLEAR;N_B5_CLEAR;N_B6_CLEAR;N_B7_CLEAR;N_B8_CLEAR;N_B9_CLEAR;N_B10_CLEAR
#define ACENDE_NIVEL1									N_B1_SET;N_B2_CLEAR;N_B3_CLEAR;N_B4_CLEAR;N_B5_CLEAR;N_B6_CLEAR;N_B7_CLEAR;N_B8_CLEAR;N_B9_CLEAR;N_B10_CLEAR
#define ACENDE_NIVEL2									N_B1_SET;N_B2_SET;N_B3_CLEAR;N_B4_CLEAR;N_B5_CLEAR;N_B6_CLEAR;N_B7_CLEAR;N_B8_CLEAR;N_B9_CLEAR;N_B10_CLEAR
#define ACENDE_NIVEL3									N_B1_SET;N_B2_SET;N_B3_SET;N_B4_CLEAR;N_B5_CLEAR;N_B6_CLEAR;N_B7_CLEAR;N_B8_CLEAR;N_B9_CLEAR;N_B10_CLEAR
#define ACENDE_NIVEL4									N_B1_SET;N_B2_SET;N_B3_SET;N_B4_SET;N_B5_CLEAR;N_B6_CLEAR;N_B7_CLEAR;N_B8_CLEAR;N_B9_CLEAR;N_B10_CLEAR
#define ACENDE_NIVEL5									N_B1_SET;N_B2_SET;N_B3_SET;N_B4_SET;N_B5_SET;N_B6_CLEAR;N_B7_CLEAR;N_B8_CLEAR;N_B9_CLEAR;N_B10_CLEAR
#define ACENDE_NIVEL6									N_B1_SET;N_B2_SET;N_B3_SET;N_B4_SET;N_B5_SET;N_B6_SET;N_B7_CLEAR;N_B8_CLEAR;N_B9_CLEAR;N_B10_CLEAR
#define ACENDE_NIVEL7									N_B1_SET;N_B2_SET;N_B3_SET;N_B4_SET;N_B5_SET;N_B6_SET;N_B7_SET;N_B8_CLEAR;N_B9_CLEAR;N_B10_CLEAR
#define ACENDE_NIVEL8									N_B1_SET;N_B2_SET;N_B3_SET;N_B4_SET;N_B5_SET;N_B6_SET;N_B7_SET;N_B8_SET;N_B9_CLEAR;N_B10_CLEAR
#define ACENDE_NIVEL9 									N_B1_SET;N_B2_SET;N_B3_SET;N_B4_SET;N_B5_SET;N_B6_SET;N_B7_SET;N_B8_SET;N_B9_SET;N_B10_CLEAR
#define ACENDE_NIVEL10									N_B1_SET;N_B2_SET;N_B3_SET;N_B4_SET;N_B5_SET;N_B6_SET;N_B7_SET;N_B8_SET;N_B9_SET;N_B10_SET
#define NIVEL_1											valor_bargraph <= 3276
#define NIVEL_2    										valor_bargraph >  3276  && valor_bargraph <= 6552
#define NIVEL_3											valor_bargraph >  6552  && valor_bargraph <= 9828
#define NIVEL_4     									valor_bargraph >  9828  && valor_bargraph <= 13104
#define NIVEL_5     									valor_bargraph >  13104 && valor_bargraph <= 16380
#define NIVEL_6											valor_bargraph >  16380 && valor_bargraph <= 19656
#define NIVEL_7     									valor_bargraph >  19656 && valor_bargraph <= 22932
#define NIVEL_8     									valor_bargraph >  22932 && valor_bargraph <= 26208
#define NIVEL_9											valor_bargraph >  26208 && valor_bargraph <= 29484
#define NIVEL_10    									valor_bargraph >  29484 && valor_bargraph <= 32768
#define _NIVEL_1										valor_bargraph1 <= 3276
#define _NIVEL_2    									valor_bargraph1 >  3276  && valor_bargraph1 <= 6552
#define _NIVEL_3										valor_bargraph1 >  6552  && valor_bargraph1 <= 9828
#define _NIVEL_4     									valor_bargraph1 >  9828  && valor_bargraph1 <= 13104
#define _NIVEL_5     									valor_bargraph1 >  13104 && valor_bargraph1 <= 16380
#define _NIVEL_6										valor_bargraph1 >  16380 && valor_bargraph1 <= 19656
#define _NIVEL_7     									valor_bargraph1 >  19656 && valor_bargraph1 <= 22932
#define _NIVEL_8     									valor_bargraph1 >  22932 && valor_bargraph1 <= 26208
#define _NIVEL_9										valor_bargraph1 >  26208 && valor_bargraph1 <= 29484
#define _NIVEL_10    									valor_bargraph1 >  29484 && valor_bargraph1 <= 32768
/******************************************************************************/

/********************************** BATERIA ***********************************/
#define	CONST_LIM_BATERIA_DESCARREGADA					215 //21.5V
#define CONST_LIMITE_INFERIOR_BATERIA					225 //22.5V
#define	CONST_LIM_MAX_BATERIA							250 //25.0V
#define DESCARREGADA									0
#define CARREGADA										1
#define BATABAIXO215									2
/******************************************************************************/

/*********************************** BUZZER ***********************************/
#define BUZZER_TOM										0
#define BUZZER_VOLUME									1
#define BUZZER_LIGA_DESLIGA								2
/******************************************************************************/

/*********************************** CANAL ************************************/
#define NUM_MAX_CANAIS									25
#define CANAL_CONFIGURADO_SETUP							11
/******************************************************************************/

/***************************** CONFIGURAÇÃO RELÉ ******************************/
#define rele_pulso										1
#define rele_retencao									2
#define LIGA_RELE										GPIO_PDD_SetPortDataOutputMask(PTE_BASE_PTR,GPIO_PDD_PIN_24)
#define DESLIGA_RELE									GPIO_PDD_ClearPortDataOutputMask(PTE_BASE_PTR,GPIO_PDD_PIN_24)
/******************************************************************************/

/***************************** CONFIGURAÇÃO TRAVA *****************************/
#define trava_pulso										1
#define trava_retencao_controle							2
#define trava_retencao_controle_teclado					3
#define LIGA_TRAVA										GPIO_PDD_SetPortDataOutputMask(PTE_BASE_PTR,GPIO_PDD_PIN_25)
#define DESLIGA_TRAVA									GPIO_PDD_ClearPortDataOutputMask(PTE_BASE_PTR,GPIO_PDD_PIN_25)
#define TRAVA_LIGADA									(GPIO_PDD_GetPortDataOutput(PORTE_DEVICE) & 0x02000000) == 0x02000000
/******************************************************************************/

/****************************** CONTROLE REMOTO *******************************/
#define TEMPO_MAXIMO_CADASTRO_CONTROLE					20 //20 x 100ms  = 20 segundos

#define NENHUM											0
#define APAGAR											1
#define CADASTRAR										2
#define APAGADO											3
#define CADASTRADO										4
#define NAO_APAGADO										5
#define CADASTRAR1										6
#define JA_CADASTRADO									7
#define AVALIA_CONTROLE									8
#define CONTROLE_TIPO_A									9
#define CONTROLE_TIPO_B									10

#define TRAVA_REMOTO									(GPIO_PDD_GetPortDataInput(PORTC_DEVICE) & 0x00000020) == 0x00000000
#define DESTRAVA_REMOTO					  				(GPIO_PDD_GetPortDataInput(PORTA_DEVICE) & 0x00020000) == 0x00000000
#define CANCELA_REMOTO									(GPIO_PDD_GetPortDataInput(PORTC_DEVICE) & 0x00000040) == 0x00000000
#define CONFIRMA_REMOTO									(GPIO_PDD_GetPortDataInput(PORTA_DEVICE) & 0x00000800) == 0x00000000
#define VT		 										(GPIO_PDD_GetPortDataInput(PORTA_DEVICE) & 0x00004000) == 0x00000000
#define CLEAR_PROG									    GPIO_PDD_SetPortDataOutputMask(PTC_BASE_PTR,GPIO_PDD_PIN_0)			//REV. 47 Invertido SET_PROG e CLEAR_PROG para funcionar com PIC16F628A Rampy
#define SET_PROG										GPIO_PDD_ClearPortDataOutputMask(PTC_BASE_PTR,GPIO_PDD_PIN_0)
/******************************************************************************/

/**************************** DEFINIÇÕES DE PLACA *****************************/
#define CONST_PLACA_PAINEL								0
#define CONST_PLACA_AUDIO								1
#define CONST_PLACA_FONTE								2
/******************************************************************************/

/******************************* ENDEREÇOS CAN ********************************/
#define FONTE_CAN										0x000U
#define PAINEL_CAN										0x009U + 0x080U
#define AUDIO_CAN										0x00BU + 0x080U
#define ZC_CAN											0x066U
/*****************************************************************************/

/**************************** ENDEREÇOS DA FLASH ******************************/
#define PAGINA_0										0x43008 //De 43000 a 43007 vai o número serial do equipamento que tem 8 bytes
#define END_INI_PARAMETROS								0x43000 //Vai de 0x43000 a 0x44000-1 = 0x1000 = 4096 bytes para a gravação dos parâmetros do equipamento
#define END_INI_LOG_EVENTOS								0x44000 //Vai de 0x44000 a 0x48000-1 = 0x4000 = 16384 bytes / 8 bytes  = 2048 registros de eventos
#define END_INI_FLAG_EVENTOS							0x48000 //Vai de 0x48000 a 49000-1 = 0x1000 = 4096 bytes livres para as flags de eventos
#define END_INI_LOG_AUDITORIAS							0x49000 //Vai de 0x49000 a 0x75000-1 = 44 blocos de 0x1000 sendo cada bloco 372 registros de 11 bytes cada e no total vai dar 44 x 372 = 16368 registros
#define END_INI_FLAG_AUDITORIA							0x75000 //Vai de 0x75000 a 0x79000-1 = 0x1000 = 4 blocos de 0x1000 que vai dar 4096 * 4 = 16384 flags de registros
#define END_INI_BACKUP									0x79000	//Vai de 0x79000 a 0x79FF0 - A partir de 790FF salva as vezes que houve backup
/******************************************************************************/

/***************************** ESTADOS DO DETECTOR ****************************/
#define ESTADO_INICIAL									1
#define ESTADO_AJUSTES_BASICOS							2
#define ESTADO_AJUSTE_MANUAL_SENSIBILIDADE				3
#define ESTADO_AJUSTE_AUTOMATICO_SENSIBILIDADE			4
#define ESTADO_MODO_DE_TRAVAMENTO						5
#define ESTADO_AJUSTES_AVANCADOS						6
#define ESTADO_AJUSTES_DO_SISTEMA						7
#define ESTADO_AJUSTES_DE_ALARME						8
#define ESTADO_INFORMACOES_DO_SISTEMA					9
#define ESTADO_INFORMACOES_DE_ENERGIA					10
#define ESTADO_DIAGNOSTICO_DO_SISTEMA					11
#define ESTADO_AJUSTES_TX_RX							12
#define ESTADO_MODELO_DE_ANTENA							13
#define ESTADO_POTENCIOMETRO_DE_GANHO					14
#define ESTADO_POTENCIOMETRO_DE_SELECAO_DE_METAIS		15
#define ESTADO_RELIGA_INTERRUPCOES						16
#define ATUALIZA_LCD									17
#define ESTADO_ESPERA									18
#define ESTADO_CARREGA_DADOS							19
#define ESTADO_NAVEGA_MENU								20
#define ESTADO_NAVEGA_MENU_FUNCOES						21
#define ESTADO_LER_TECLAS								22
#define ESTADO_DIGITE_SENHA								23
#define ESTADO_ALTERA_SENHA								24
#define ESTADO_CONFIRMA_SENHA							25
#define ESTADO_CONFIGURA_TRAVA							26
#define ESTADO_CONFIGURA_RELE							27
#define ESTADO_AJUSTE_MANUAL_CANAL						28
#define ESTADO_SELECAO_METAIS							29
#define ESTADO_AJUSTE_AUTOMATICO_CANAL					30
#define ESTADO_CONFIGURA_CONTROLE_REMOTO				31
#define ESTADO_CONFIGURA_INFRAVERMELHO					32
#define ESTADO_HORA_E_DATA								33
#define ESTADO_VISUALIZAR_DATA_E_HORA					34
#define ESTADO_ALTERAR_DATA_E_HORA						35
#define ESTADO_RESETAR_PADRAO_FABRICA					36
#define ESTADO_IDIOMA									37
#define ESTADO_CONFIGURA_ALARME_SONORO					38
#define ESTADO_CONFIGURA_ALARME_VISUAL					39
#define ESTADO_TOM_DO_BUZZER							40
#define ESTADO_VOLUME_DO_BUZZER							41
#define ESTADO_CONFIGURA_BUZZER  						42
#define ESTADO_CONFIGURA_MSG_VOZ						43
#define ESTADO_VOLUME_MSG_VOZ							44
#define ESTADO_LIG_DES_ALARME_VISUAL					45
#define ESTADO_CONTADOR_DETECCOES						46
#define ESTADO_CONTADOR_PASSAGENS						47
#define ESTADO_NUMERO_DE_SERIE							48
#define ESTADO_ZERA_CONTADOR_DETECCOES					49
#define ESTADO_ZERA_CONTADOR_PASSAGENS					50
#define ESTADO_TOTAL_BLOQUEIOS							51
#define ESTADO_TOTAL_DESBLOQUEIOS						52
#define ESTADO_ENTRADAS									53
#define ESTADO_SAIDAS									54
#define ESTADO_ENTRADAS_SAIDAS							55
#define ESTADO_CONFIGURA_CICLO_TRABALHO					56
#define ESTADO_CONFIGURA_DEFASAGEM						57
#define ESTADO_CONFIGURA_FREQUENCIA						58
#define ESTADO_DIAGNOSTICO_SISTEMA					    59
#define ESTADO_TRAVA									60
#define ESTADO_DESTRAVA									61
#define ESTADO_LE_AREAS_DETECCAO						62
#define ESTADO_GRAVA_CONTADOR							63
#define ESTADO_CARREGA_VERSOES							64
#define ESTADO_GET_ALIVES								65
#define ESTADO_TRATA_CAN								66
#define ESTADO_ANULA_AREAS								67
#define ESTADO_FILTRO_RUIDO								68
#define ESTADO_GRAVA_CONTADOR_ENTRA						69
#define ESTADO_GRAVA_CONTADOR_SAI						70
#define ESTADO_DESLIGA_DETECCAO							71
#define ESTADO_TRATA_SERIAL								72
#define ESTADO_MOSTRA_BARGRAPH							73
#define ESTADO_ESCREVE_BARGRAPH							74
#define ESTADO_MOSTRA_COMPATIBILIDADE_ELETROMAGNETICA	75
#define ESTADO_GRAVA_CONTADOR_BLOQUEIOS_DESBLOQUEIOS	76
#define ESTADO_GRAVA_FLASH								77
#define ESTADO_TRAVA_INTELIGENTE						78
#define ESTADO_NUMERO_DE_SERIE1							79
#define ESTADO_ZERAR_LOG_EVENTOS						80
#define ESTADO_MODO_AT_ON								81
#define ESTADO_COMANDO_OK								82
#define ESTADO_MODO_AT_OFF								83
#define ESTADO_CONFIGURACOES_DE_INTERNET				84
#define ESTADO_DIGITE_IP								85
#define ESTADO_DIGITE_MASCARA_SUB_REDE					86
#define ESTADO_DIGITE_GATEWAY							87
#define ESTADO_DIGITE_DNS								88
#define ESTADO_DIGITE_PORTA_WEB							89
#define ESTADO_ENVIAR									90
#define ESTADO_TIPO_DETECTOR							91
#define ESTADO_TRATA_ETHERNET           				92
#define ESTADO_ELIMINAR_FALHA_DAS_BOBINAS				93
#define ESTADO_TRATASERIAL2								94
#define ESTADO_ESCOLHE_STATIC_DHCP						95
#define ESTADO_PORTA_AUTOMATICA							96
#define ESTADO_OPCAO_SENSOR_CONTADOR					97
#define ESTADO_SORTEADOR_ELETRONICO						98
#define ESTADO_QUANTIDADE_SORTEADOS						99
#define ESTADO_CONFIRMA_SORTEADOR						100
#define ESTADO_HOUVE_BURLA								101
#define ESTADO_SOLICITA_TROCA_SENHA						102
/******************************************************************************/

/****************************** ETHERNET-SERIAL *******************************/
#define RESET_SERIAL_ETHERNET							GPIO_PDD_ClearPortDataOutputMask(PTE_BASE_PTR,GPIO_PDD_PIN_11)
#define SET_SERIAL_ETHERNET						 		GPIO_PDD_SetPortDataOutputMask(PTE_BASE_PTR,GPIO_PDD_PIN_11)
#define MODO_NORMAL										1
#define MODO_AT											2
#define MODO_SERIAL										3
#define _STATIC    										1
#define _STATIC_REMOTO									2
#define _DHCP_REMOTO									3
/******************************************************************************/

/***************************** FILTRO_DEBOUNCING ******************************/
#define FILTRO_DEBOUNCING								30
/******************************************************************************/

/******************************* FONTE_CHAVEADA *******************************/
#define CONST_LIMITE_INFERIOR_FONTE						235
#define CONST_LIMITE_SUPERIOR_FONTE						275
/******************************************************************************/

/******************************** FUNÇÕES CAN**********************************/
#define GET_FONTE										81
#define GET_TENSOES										82
#define GET_TENSOES1									85
#define GET_ALIVE										87
#define GET_BATERIA_BAIXA								88
#define GET_DESLIGAR									95
#define GET_GRAVADOR									118
#define	GET_STATUS_PGDM									10
#define TIMEOUT_CAN										1
#define ABRIR_PGDM										'A'
#define FECHAR_PGDM										'F'
/******************************************************************************/

/*********************************** GERAL ************************************/
#define NAO												0
#define SIM												1
#define LINHA											pos[0]
#define COLUNA											pos[1]
/******************************************************************************/

/*********************************** IDIOMA ***********************************/
#define COD_PORTUGUES									0
#define COD_ESPANHOL									1
#define COD_INGLES										2
/******************************************************************************/

/******************************* INFRAVERMELHOS *******************************/
#define _INFRA1_ATIVO									1
#define _INFRA2_ATIVO									2
#define _AMBOS_INFRAS_ATIVO								3
#define _AMBOS_INFRAS_INATIVO							4
#define _INFRA1_INATIVO									5
#define _INFRA2_INATIVO									6

#define INFRA1_ATIVO									(GPIO_PDD_GetPortDataInput(PORTB_DEVICE) & 0x00000002) == 0x00000002
#define INFRA1_INATIVO									(GPIO_PDD_GetPortDataInput(PORTB_DEVICE) & 0x00000002) == 0x00000000
#define INFRA2_ATIVO									(GPIO_PDD_GetPortDataInput(PORTB_DEVICE) & 0x00000004) == 0x00000004
#define INFRA2_INATIVO 									(GPIO_PDD_GetPortDataInput(PORTB_DEVICE) & 0x00000004) == 0x00000000
#define AMBOS_INFRAS_ATIVO								(INFRA1_ATIVO && INFRA2_ATIVO)
#define AMBOS_INFRAS_INATIVO							(INFRA1_INATIVO && INFRA2_INATIVO)
#define SENSOR_TETO_ENTRADA_ATIVO						(GPIO_PDD_GetPortDataInput(PORTB_DEVICE) & 0x00000002) == 0x00000002
#define SENSOR_TETO_ENTRADA_INATIVO						(GPIO_PDD_GetPortDataInput(PORTB_DEVICE) & 0x00000002) == 0x00000000
#define SENSOR_TETO_SAIDA_ATIVO							(GPIO_PDD_GetPortDataInput(PORTB_DEVICE) & 0x00000004) == 0x00000004
#define SENSOR_TETO_SAIDA_INATIVO						(GPIO_PDD_GetPortDataInput(PORTB_DEVICE) & 0x00000004) == 0x00000000
/******************************************************************************/

/*************************************LCD *************************************/
#define RS_ON											Control_LCD_SetBit(0)
#define RS_OFF											Control_LCD_ClrBit(0)
#define E_ON											Control_LCD_SetBit(1)
#define E_OFF											Control_LCD_ClrBit(1)
/******************************************************************************/

/******************************* MEMÓRIA FLASH ********************************/
#define SETA_PARAMETRO_ON								1
#define SETA_PARAMETRO_OFF								0
#define SETA_PWM_ON										1
#define SETA_PWM_OFF									0
#define SETA_GRAVA_FLASH_ON								1
#define SETA_GRAVA_FLASH_OFF							0
#define SETA_POT_GANHO_ON								1
#define SETA_POT_GANHO_OFF								0
#define MEMORIA_FLASH_VAZIA								0xFF
#define MEMORIA_FLASH_GRAVADA							1
#define CONST_CHECKSUM    								0x89CDE0D3
/******************************************************************************/

/****************************** MENSAGEM DE VOZ *******************************/
#define UP_SET											GPIO_PDD_SetPortDataOutputMask(PTE_BASE_PTR,GPIO_PDD_PIN_8)
#define UP_CLEAR										GPIO_PDD_ClearPortDataOutputMask(PTE_BASE_PTR,GPIO_PDD_PIN_8)
#define DOWN_SET										GPIO_PDD_SetPortDataOutputMask(PTE_BASE_PTR,GPIO_PDD_PIN_9)
#define DOWN_CLEAR										GPIO_PDD_ClearPortDataOutputMask(PTE_BASE_PTR,GPIO_PDD_PIN_9)
#define SINAL_MSG_CLEAR									GPIO_PDD_SetPortDataOutputMask(PTE_BASE_PTR,GPIO_PDD_PIN_10)	//Invertido SET e CLEAR p/ Painel R2
#define SINAL_MSG_SET									GPIO_PDD_ClearPortDataOutputMask(PTE_BASE_PTR,GPIO_PDD_PIN_10)
/******************************************************************************/

/**************************** MODO DE TRAVAMENTO ******************************/
#define SOMENTE_DESTRAVA								1
#define TRAVA_DESTRAVA									2
/******************************************************************************/

/******************************* NOTAS MUSICAIS	*******************************/
#define DO												261
#define RE												293
#define MI												329
#define FA												349
#define SOL												391
#define	LA												440
#define SI												493

#define	CA 												1635
#define	DbA												1732
#define	DA												1835
#define	EbA												1945
#define	EA												2060
#define	FAA												2183
#define	GbA												2312
#define	GA												2450
#define	AbA												2596
#define	LAA												2750
#define	BbA												2914
#define	BA												3087

#define	CB												3270
#define	DbB												3465
#define	DB												3671
#define	EbB												3889
#define	EB												4120
#define	FB												4365
#define	GbB												4625
#define	GB												4900
#define	AbB												5191
#define	LAB												5500
#define	BbB												5827
#define	BB												6174

#define	CC												6541
#define	DbC												6930
#define	DC												7342
#define	EbC												7778
#define	EC												8241
#define	FC												8731
#define	GbC												9250
#define	GC												9800
#define	AbC												10383
#define	LAC												11000
#define	BbC												11654
#define	BC												12347

#define	CD												13081
#define	DbD												13859
#define	DD												14683
#define	EbD												15556
#define	ED												16481
#define	FD												17461
#define	GbD												18500
#define	GD												19600
#define	AbD												20765
#define	LAD												22000
#define	BbD												23308
#define	BD												24694

#define	CE												26163
#define	DbE												27718
#define	DE												29366
#define	EbE												31113
#define	EE												32963
#define	FE												34923
#define	GbE												36999
#define	GE												39200
#define	AbE												41530
#define	LAE												44000
#define	BbE												46616
#define	BE												49388

#define	CF												52325
#define	DbF												55437
#define	DF												58733
#define	EbF												62225
#define	EF												65926
#define	FF												69846
#define	GbF												73999
#define	GF												78399
#define	AbF												83061
#define	LAF												88000
#define	BbF												93233
#define	BF												98777

#define	CG												104650
#define	DbG												110873
#define	DG												117466
#define	EbG												124451
#define	EG												131851
#define	FG												139691
#define	GbG												147998
#define	GG												156798
#define	AbG												166122
#define	LAG												176000
#define	BbG												186466
#define	BG												197553

#define	CH												209300
#define	DbH												221746
#define	DH												234932
#define	EbH												248902
#define	EH												263702
#define	FH												279383
#define	GbH												295996
#define	GH												313596
#define	AbH												332244
#define	LAH												352001
#define	BbH												372931
#define	BH												395107

#define	CI												418601
#define	DbI												443492
#define	DI												469864
#define	EbI												497803

//Duração das notas

#define BPM												200  //Você pode mudar esta valor alterando todos os outros
#define H   											600  //Metade 2/4
#define QX  											300
#define E   											150  //Oitava 1/8
#define ST  											75 	 //Décima sexta 1/16
#define W   											1200 //Inteira 4/4
/******************************************************************************/

/***************************** OPÇÃO DO CONTADOR ******************************/
#define SENSOR_FRONTAL									1
#define SENSOR_TETO										2
/******************************************************************************/

/*********************************** PERFIS ***********************************/
#define PLANA_ONIX_2000									0
#define PLANA_ONIX_2100									1
#define PLANA_ONIX_440									2
#define CIL_IECO_2000									3
#define CIL_IECO_2100									4
#define IECO_GT											5
#define PORTAL_750_BLINDADO								6
/******************************************************************************/

/*************************** POTENCIOMETROS DIGITAIS **************************/
#define	POT_DEFASAGEM									0
#define	POT_GANHO										1
#define CS_DEFASAGEM1_ON								GPIO_PDD_SetPortDataOutputMask(PTA_BASE_PTR,GPIO_PDD_PIN_29)
#define CS_DEFASAGEM1_OFF								GPIO_PDD_ClearPortDataOutputMask(PTA_BASE_PTR,GPIO_PDD_PIN_29)
#define CS_DEFASAGEM2_ON								GPIO_PDD_SetPortDataOutputMask(PTB_BASE_PTR,GPIO_PDD_PIN_4)
#define CS_DEFASAGEM2_OFF								GPIO_PDD_ClearPortDataOutputMask(PTB_BASE_PTR,GPIO_PDD_PIN_4)
#define CS_DEFASAGEM3_ON								GPIO_PDD_SetPortDataOutputMask(PTB_BASE_PTR,GPIO_PDD_PIN_6)
#define CS_DEFASAGEM3_OFF								GPIO_PDD_ClearPortDataOutputMask(PTB_BASE_PTR,GPIO_PDD_PIN_6)
#define CS_DEFASAGEM4_ON								GPIO_PDD_SetPortDataOutputMask(PTB_BASE_PTR,GPIO_PDD_PIN_8)
#define CS_DEFASAGEM4_OFF								GPIO_PDD_ClearPortDataOutputMask(PTB_BASE_PTR,GPIO_PDD_PIN_8)
#define CS_DEFASAGEM5_ON								GPIO_PDD_SetPortDataOutputMask(PTB_BASE_PTR,GPIO_PDD_PIN_10)
#define CS_DEFASAGEM5_OFF								GPIO_PDD_ClearPortDataOutputMask(PTB_BASE_PTR,GPIO_PDD_PIN_10)
#define CS_DEFASAGEM6_ON								GPIO_PDD_SetPortDataOutputMask(PTB_BASE_PTR,GPIO_PDD_PIN_19)
#define CS_DEFASAGEM6_OFF								GPIO_PDD_ClearPortDataOutputMask(PTB_BASE_PTR,GPIO_PDD_PIN_19)
#define CS_DEFASAGEM7_ON								GPIO_PDD_SetPortDataOutputMask(PTB_BASE_PTR,GPIO_PDD_PIN_21)
#define CS_DEFASAGEM7_OFF								GPIO_PDD_ClearPortDataOutputMask(PTB_BASE_PTR,GPIO_PDD_PIN_21)
#define CS_DEFASAGEM8_ON								GPIO_PDD_SetPortDataOutputMask(PTB_BASE_PTR,GPIO_PDD_PIN_23)
#define CS_DEFASAGEM8_OFF								GPIO_PDD_ClearPortDataOutputMask(PTB_BASE_PTR,GPIO_PDD_PIN_23)
#define CS_GANHO1_ON									GPIO_PDD_SetPortDataOutputMask(PTA_BASE_PTR,GPIO_PDD_PIN_28)
#define CS_GANHO1_OFF									GPIO_PDD_ClearPortDataOutputMask(PTA_BASE_PTR,GPIO_PDD_PIN_28)
#define CS_GANHO2_ON									GPIO_PDD_SetPortDataOutputMask(PTB_BASE_PTR,GPIO_PDD_PIN_3)
#define CS_GANHO2_OFF									GPIO_PDD_ClearPortDataOutputMask(PTB_BASE_PTR,GPIO_PDD_PIN_3)
#define CS_GANHO3_ON									GPIO_PDD_SetPortDataOutputMask(PTB_BASE_PTR,GPIO_PDD_PIN_5)
#define CS_GANHO3_OFF									GPIO_PDD_ClearPortDataOutputMask(PTB_BASE_PTR,GPIO_PDD_PIN_5)
#define CS_GANHO4_ON									GPIO_PDD_SetPortDataOutputMask(PTB_BASE_PTR,GPIO_PDD_PIN_7)
#define CS_GANHO4_OFF									GPIO_PDD_ClearPortDataOutputMask(PTB_BASE_PTR,GPIO_PDD_PIN_7)
#define CS_GANHO5_ON									GPIO_PDD_SetPortDataOutputMask(PTB_BASE_PTR,GPIO_PDD_PIN_9)
#define CS_GANHO5_OFF									GPIO_PDD_ClearPortDataOutputMask(PTB_BASE_PTR,GPIO_PDD_PIN_9)
#define CS_GANHO6_ON									GPIO_PDD_SetPortDataOutputMask(PTB_BASE_PTR,GPIO_PDD_PIN_11)
#define CS_GANHO6_OFF									GPIO_PDD_ClearPortDataOutputMask(PTB_BASE_PTR,GPIO_PDD_PIN_11)
#define CS_GANHO7_ON									GPIO_PDD_SetPortDataOutputMask(PTB_BASE_PTR,GPIO_PDD_PIN_20)
#define CS_GANHO7_OFF									GPIO_PDD_ClearPortDataOutputMask(PTB_BASE_PTR,GPIO_PDD_PIN_20)
#define CS_GANHO8_ON									GPIO_PDD_SetPortDataOutputMask(PTB_BASE_PTR,GPIO_PDD_PIN_22)
#define CS_GANHO8_OFF									GPIO_PDD_ClearPortDataOutputMask(PTB_BASE_PTR,GPIO_PDD_PIN_22)
/******************************************************************************/

/*********************************** SENHAS ***********************************/
#define SENHA_INCORRETA									0
//#define SENHA_CORRETA									1
#define NENHUMA_DELAS									2
#define	SENHA_DA_GERENCIA								1
#define	SENHA_DO_TECNICO								2
#define SENHA_DA_ENGENHARIA								3
/******************************************************************************/

/****************************** SENSOR INDUTIVO *******************************/
#define SENSOR_INDUTIVO_ATIVADO							(GPIO_PDD_GetPortDataInput(PORTE_DEVICE) & 0x04000000) == 0x00000000
/******************************************************************************/

/******************************************************************************/

/********************************** SINALEIRA *********************************/
#define LIGA_SINALEIRA_VERMELHA							GPIO_PDD_SetPortDataOutputMask(PTC_BASE_PTR,GPIO_PDD_PIN_7);GPIO_PDD_ClearPortDataOutputMask(PTE_BASE_PTR,GPIO_PDD_PIN_0)
#define DESLIGA_SINALEIRA_VERMELHA						GPIO_PDD_ClearPortDataOutputMask(PTC_BASE_PTR,GPIO_PDD_PIN_7)
#define LIGA_SINALEIRA_VERDE							GPIO_PDD_SetPortDataOutputMask(PTE_BASE_PTR,GPIO_PDD_PIN_0);GPIO_PDD_ClearPortDataOutputMask(PTC_BASE_PTR,GPIO_PDD_PIN_7)
#define DESLIGA_SINALEIRA_VERDE							GPIO_PDD_ClearPortDataOutputMask(PTE_BASE_PTR,GPIO_PDD_PIN_0)
#define LIGA_AC											GPIO_PDD_SetPortDataOutputMask(PTE_BASE_PTR,GPIO_PDD_PIN_6)
#define DESLIGA_AC										GPIO_PDD_ClearPortDataOutputMask(PTE_BASE_PTR,GPIO_PDD_PIN_6)
#define LIGA_BAT										GPIO_PDD_SetPortDataOutputMask(PTE_BASE_PTR,GPIO_PDD_PIN_7)
#define DESLIGA_BAT										GPIO_PDD_ClearPortDataOutputMask(PTE_BASE_PTR,GPIO_PDD_PIN_7)
/******************************************************************************/

/********************************** TECLADO ***********************************/
#define teclaConfirma									1
#define teclaIncrementa									2
#define	teclaDecrementa									3
#define teclaCancela									4
#define teclaDestrava									5
#define teclaTrava										6
#define teclaConfirma_Remoto							7
#define teclaAnalise									8
#define CONFIRMA 										(GPIO_PDD_GetPortDataInput(PORTA_DEVICE) & 0x01000000) == 0x00000000
#define INCREMENTA 										(GPIO_PDD_GetPortDataInput(PORTA_DEVICE) & 0x02000000) == 0x00000000
#define DECREMENTA 										(GPIO_PDD_GetPortDataInput(PORTA_DEVICE) & 0x04000000) == 0x00000000
#define CANCELA 										(GPIO_PDD_GetPortDataInput(PORTA_DEVICE) & 0x08000000) == 0x00000000
/******************************************************************************/

/*********************************** TESTES ***********************************/
#define TESTE_LEDS										1
#define TESTE_TRAVA										2
#define TESTE_RELE										3
#define TESTE_BUZZER									4
#define TESTE_MSG_VOZ									5
//TODO Remove below
#define TESTE_MSG_VOZ1									6
#define TESTE_MSG_VOZ2									7
#define TESTE_MSG_VOZ3									8
//TODO Till here
#define TESTE_TECLADO									9//6
#define TESTE_INFRAVERMELHO								10//7
#define TESTE_AUTONOMIA_BATERIA							11//8
#define TESTE_SINAL_RX_A1_A2							12//9
#define TESTE_SINAL_RX_A2_A3							13//10
#define TESTE_SINAL_RX_A3_A4							13//10
#define TESTE_SINAL_RX_A5_A6							14//11
#define TESTE_SINAL_RX_A7_A8							15//12

/******************************************************************************/

/****************************** TIPO DE DETECTOR ******************************/
#define Z3												1
#define Z8												2
/******************************************************************************/

/********************* CODIGO DE ERROS COMUNICAÇÃO REMOTA *********************/
#define ERRO_OK											'0'		//Comunicação sem erros
#define ERRO_COM										'1'		//Não recebeu resposta do servidor / Sem conexão com servidor
#define ERRO_SVD										'2'		//Recebeu resposta do servidor fora do padrão esperado
#define ERRO_FW											'3'		//Recebeu resposta do servidor mas não atualizou flag envio dos logs
/******************************************************************************/

/**************************** CODIGO DE WARNING AGATA ***************************/
#define NO_WRNG											'A'		//Comunicação sem erros
#define BURLA											'B'		//Não recebeu resposta do servidor / Sem conexão com servidor
/******************************************************************************/

/****************** OFFSET PARA ENDEREÇOS DA MEMÓRIA FLASH ********************/

/******************************** OFFSET SENHAS *******************************/
#define OFFSET											0x00000000
#define	OFFSET_SENHA_DA_GERENCIA						OFFSET												//decimal 0
#define	OFFSET_SENHA_DO_TECNICO							OFFSET + 6											//decimal 6
#define	OFFSET_SENHA_DA_ENGENHARIA						OFFSET + 12											//decimal 12
/******************************************************************************/

/**************************** OFFSET SENSIBILIDADE ****************************/
#define OFFSET_SENSIBILIDADE							OFFSET + 18
#define OFFSET_SENSIBILIDADE_AREA1						OFFSET_SENSIBILIDADE								//decimal 18
#define OFFSET_SENSIBILIDADE_AREA2						OFFSET_SENSIBILIDADE + 1							//decimal 19
#define OFFSET_SENSIBILIDADE_AREA3						OFFSET_SENSIBILIDADE + 2							//decimal 20
#define OFFSET_SENSIBILIDADE_AREA4						OFFSET_SENSIBILIDADE + 3							//decimal 21
#define OFFSET_SENSIBILIDADE_AREA5						OFFSET_SENSIBILIDADE + 4							//decimal 22
#define OFFSET_SENSIBILIDADE_AREA6						OFFSET_SENSIBILIDADE + 5							//decimal 23
#define OFFSET_SENSIBILIDADE_AREA7						OFFSET_SENSIBILIDADE + 6							//decimal 24
#define OFFSET_SENSIBILIDADE_AREA8						OFFSET_SENSIBILIDADE + 7							//decimal 25
/******************************************************************************/

/************************* OFFSET MODO DE TRAVAMENTO **************************/
#define OFFSET_MODO_TRAVAMENTO							OFFSET_SENSIBILIDADE + 8							//decimal 26
/******************************************************************************/

/******************************** OFFSET CANAL ********************************/
#define OFFSET_CANAL									OFFSET_MODO_TRAVAMENTO + 1							//decimal 27
/******************************************************************************/

/************************** OFFSET SELECAO DE METAIS **************************/
#define OFFSET_SELECAO_METAIS							OFFSET_CANAL + 1									//decimal 28
/******************************************************************************/

/******************************** OFFSET TRAVA ********************************/
#define OFFSET_TRAVA									OFFSET_SELECAO_METAIS + 1
#define OFFSET_PULSO_TRAVA								OFFSET_TRAVA										//decimal 29
#define OFFSET_SINAL_TRAVA								OFFSET_TRAVA + 1									//decimal 30
/******************************************************************************/

/******************************** OFFSET RELE *********************************/
#define OFFSET_RELE										OFFSET_TRAVA + 2
#define OFFSET_PULSO_RELE								OFFSET_RELE											//decimal 31
#define OFFSET_SINAL_RELE								OFFSET_RELE + 1										//decimal 32
/******************************************************************************/

/************************* OFFSET NÚMERO DE CONTROLES *************************/
#define OFFSET_NUMERO_CONTROLES							OFFSET_RELE + 2										//decimal 33
/******************************************************************************/

/**************************** OFFSET INFRAVERMELHO ****************************/
#define OFFSET_INFRAVERMELHO							OFFSET_NUMERO_CONTROLES + 1
#define OFFSET_SENSIBILIDADEIR							OFFSET_INFRAVERMELHO								//decimal 34
#define OFFSET_ANALISEIR								OFFSET_INFRAVERMELHO + 1							//decimal 35
/******************************************************************************/

/******************************* OFFSET FÁBRICA *******************************/
#define OFFSET_FABRICA									OFFSET_INFRAVERMELHO + 2							//decimal 36
/******************************************************************************/

/******************************* OFFSET IDIOMA ********************************/
#define OFFSET_IDIOMA									OFFSET_FABRICA + 1									//decimal 37
/******************************************************************************/

/******************************* OFFSET BUZZER ********************************/
#define OFFSET_BUZZER									OFFSET_IDIOMA + 1
#define OFFSET_BUZZER_TOM								OFFSET_BUZZER										//decimal 38
#define OFFSET_BUZZER_VOLUME							OFFSET_BUZZER + 1									//decimal 39
#define OFFSET_BUZZER_LIG_DES							OFFSET_BUZZER + 2									//decimal 40
/******************************************************************************/

/*************************** OFFSET MENSAGEM DE VOZ ***************************/
#define OFFSET_MSG_VOZ									OFFSET_BUZZER + 3
#define OFFSET_MSG_VOZ_VOLUME							OFFSET_MSG_VOZ										//decimal 41
#define OFFSET_MSG_VOZ_LIG_DES							OFFSET_MSG_VOZ + 1									//decimal 42
/******************************************************************************/

/**************************** OFFSET ALARME VISUAL ****************************/
#define OFFSET_ALARME_VISUAL_LIG_DES					OFFSET_MSG_VOZ + 2									//decimal 43
/******************************************************************************/

/************************* OFFSET CONTADOR DE DETECÇÕES ***********************/
#define OFFSET_CONTADOR_DETECCOES						OFFSET_ALARME_VISUAL_LIG_DES + 1
#define OFFSET_TOTAL_BLOQUEIOS							OFFSET_CONTADOR_DETECCOES 							//decimal 44
#define OFFSET_TOTAL_DESBLOQUEIOS						OFFSET_CONTADOR_DETECCOES + 4						//decimal 48
/******************************************************************************/

/*********************** OFFSET CONTADOR DE PASSAGENS *************************/
#define OFFSET_CONTADOR_PASSAGENS						OFFSET_CONTADOR_DETECCOES + 8
#define OFFSET_CONTADOR_ENTRADAS						OFFSET_CONTADOR_PASSAGENS							//decimal 52
#define OFFSET_CONTADOR_SAIDAS							OFFSET_CONTADOR_PASSAGENS + 4						//decimal 56
/******************************************************************************/

/******************** OFFSET CONTADOR DE PASSAGENS DIÁRIO *********************/
#define OFFSET_CONTADOR_PASSAGENS_D						OFFSET_CONTADOR_PASSAGENS + 8
#define OFFSET_CONTADOR_ENTRADAS_D						OFFSET_CONTADOR_PASSAGENS_D							//decimal 60
#define OFFSET_CONTADOR_SAIDAS_D						OFFSET_CONTADOR_PASSAGENS_D + 4						//decimal 64
#define OFFSET_CONFERENCIA_DO_DIA						OFFSET_CONTADOR_PASSAGENS_D + 8						//decimal 68
/******************************************************************************/


/******************************* OFFSET PERFIL ********************************/
#define OFFSET_PERFIL  									OFFSET_CONTADOR_PASSAGENS_D + 9						//decimal 69
/******************************************************************************/

/**************************** OFFSET AJUSTES TX RX ****************************/
#define	OFFSET_AJUSTES_TX_RX							OFFSET_PERFIL + 1
#define OFFSET_AJUSTES_TX_RX_CICLO_TRABALHO		 		OFFSET_AJUSTES_TX_RX								//decimal 70
#define OFFSET_AJUSTES_TX_RX_DEFASAGEM  				OFFSET_AJUSTES_TX_RX + 1							//decimal 71
#define OFFSET_AJUSTES_TX_RX_FREQUENCIA					OFFSET_AJUSTES_TX_RX + 3							//decimal 73
/******************************************************************************/

/************************** OFFSET MODELO DE ANTENA ***************************/
#define OFFSET_MODELO_ANTENA							OFFSET_AJUSTES_TX_RX + 5							//decimal 75
/******************************************************************************/

/*********************** OFFSET POTENCIÔMETROS DE GANHO ***********************/
#define OFFSET_POTENCIOMETRO_GANHO						OFFSET_MODELO_ANTENA + 1
#define OFFSET_POTENCIOMETRO_GANHO_AREA1				OFFSET_POTENCIOMETRO_GANHO							//decimal 76
#define OFFSET_POTENCIOMETRO_GANHO_AREA2				OFFSET_POTENCIOMETRO_GANHO + 1						//decimal 77
#define OFFSET_POTENCIOMETRO_GANHO_AREA3				OFFSET_POTENCIOMETRO_GANHO + 2						//decimal 78
#define OFFSET_POTENCIOMETRO_GANHO_AREA4				OFFSET_POTENCIOMETRO_GANHO + 3						//decimal 79
#define OFFSET_POTENCIOMETRO_GANHO_AREA5				OFFSET_POTENCIOMETRO_GANHO + 4						//decimal 80
#define OFFSET_POTENCIOMETRO_GANHO_AREA6				OFFSET_POTENCIOMETRO_GANHO + 5						//decimal 81
#define OFFSET_POTENCIOMETRO_GANHO_AREA7				OFFSET_POTENCIOMETRO_GANHO + 6						//decimal 82
#define OFFSET_POTENCIOMETRO_GANHO_AREA8				OFFSET_POTENCIOMETRO_GANHO + 7						//decimal 83
/******************************************************************************/

/********************** OFFSET POTENCIÔMETROS DE SELEÇÃO **********************/
#define OFFSET_POTENCIOMETRO_SELECAO					OFFSET_POTENCIOMETRO_GANHO + 8
#define OFFSET_POTENCIOMETRO_SELECAO_AREA1				OFFSET_POTENCIOMETRO_SELECAO						//decimal 84
#define OFFSET_POTENCIOMETRO_SELECAO_AREA2				OFFSET_POTENCIOMETRO_SELECAO + 1					//decimal 85
#define OFFSET_POTENCIOMETRO_SELECAO_AREA3				OFFSET_POTENCIOMETRO_SELECAO + 2					//decimal 86
#define OFFSET_POTENCIOMETRO_SELECAO_AREA4				OFFSET_POTENCIOMETRO_SELECAO + 3					//decimal 87
#define OFFSET_POTENCIOMETRO_SELECAO_AREA5				OFFSET_POTENCIOMETRO_SELECAO + 4					//decimal 88
#define OFFSET_POTENCIOMETRO_SELECAO_AREA6				OFFSET_POTENCIOMETRO_SELECAO + 5					//decimal 89
#define OFFSET_POTENCIOMETRO_SELECAO_AREA7				OFFSET_POTENCIOMETRO_SELECAO + 6					//decimal 90
#define OFFSET_POTENCIOMETRO_SELECAO_AREA8				OFFSET_POTENCIOMETRO_SELECAO + 7					//decimal 91
/******************************************************************************/

/**************************** OFFSET ANULA ÁREAS ******************************/
#define OFFSET_ANULA_AREAS								OFFSET_POTENCIOMETRO_SELECAO + 8
#define OFFSET_ANULA_AREA1								OFFSET_ANULA_AREAS									//decimal 92
#define OFFSET_ANULA_AREA2								OFFSET_ANULA_AREAS + 1								//decimal 93
#define OFFSET_ANULA_AREA3								OFFSET_ANULA_AREAS + 2								//decimal 94
#define OFFSET_ANULA_AREA4								OFFSET_ANULA_AREAS + 3								//decimal 95
#define OFFSET_ANULA_AREA5								OFFSET_ANULA_AREAS + 4								//decimal 96
#define OFFSET_ANULA_AREA6								OFFSET_ANULA_AREAS + 5								//decimal 97
#define OFFSET_ANULA_AREA7								OFFSET_ANULA_AREAS + 6								//decimal 98
#define OFFSET_ANULA_AREA8								OFFSET_ANULA_AREAS + 7								//decimal 99
/******************************************************************************/

/*************************** OFFSET FILTRO DE RUIDO ***************************/
#define OFFSET_FILTRO_RUIDO								OFFSET_ANULA_AREAS + 8								//decimal 100
/******************************************************************************/

/************************* OFFSET TRAVA INTELIGENTE ***************************/
#define OFFSET_TRAVA_INTELIGENTE						OFFSET_FILTRO_RUIDO + 1								//decimal 101
/******************************************************************************/

/************************* OFFSET TIPO DE DETECTOR ****************************/
#define OFFSET_TIPO_DETECTOR        					OFFSET_TRAVA_INTELIGENTE + 1					   	//decimal 102
/******************************************************************************/

/******************* OFFSET PONTEIROS DE LOG DE AUDITORIAS ********************/
#define OFFSET_PONTEIRO_BLOCO_A							OFFSET_TIPO_DETECTOR + 1							//decimal 103
#define OFFSET_PONTEIRO_BYTES_A							OFFSET_PONTEIRO_BLOCO_A + 1							//decimal 104
/******************************************************************************/

/********************* OFFSET PONTEIROS DE LOG DE EVENTOS *********************/
#define OFFSET_PONTEIRO_BLOCO_L							OFFSET_PONTEIRO_BYTES_A + 2							//decimal 106
#define OFFSET_PONTEIRO_BYTES_L							OFFSET_PONTEIRO_BLOCO_L + 1							//decimal 107
/******************************************************************************/

/*********************** OFFSET ELIMINA FALHA DA BOBINA ***********************/
#define OFFSET_FALHA_DA_BOBINA							OFFSET_PONTEIRO_BYTES_L + 2							//decimal 109
/******************************************************************************/

/**************************** OFFSET ENDEREÇO IP ******************************/
#define OFFSET_ENDERECO_IP								OFFSET_FALHA_DA_BOBINA + 1							//decimal 110
/******************************************************************************/

/******************** OFFSET ENDEREÇO MÁSCARA DE SUB REDE *********************/
#define OFFSET_ENDERECO_SUB_REDE						OFFSET_ENDERECO_IP + 15								//decimal 125
/******************************************************************************/

/************************** OFFSET ENDEREÇO GATEWAY ***************************/
#define OFFSET_ENDERECO_GATEWAY							OFFSET_ENDERECO_SUB_REDE + 15						//decimal 140																											//decimal 131
/******************************************************************************/

/**************************** OFFSET ENDEREÇO DNS *****************************/
#define OFFSET_ENDERECO_DNS								OFFSET_ENDERECO_GATEWAY + 15 						//decinal 155
/******************************************************************************/

/*********************** OFFSET PONTEIRO INDICE EVENTO ************************/
#define OFFSET_INDICE_EVENTOS_GRAVADOS		   			OFFSET_ENDERECO_DNS + 15							//decimal 170																							//decimal 161 - final vai ser 162
/******************************************************************************/

/********************* OFFSET PONTEIRO INDICE AUDITORIAS **********************/
#define OFFSET_INDICE_AUDITORIAS_GRAVADOS				OFFSET_INDICE_EVENTOS_GRAVADOS + 2					//decimal 172
/******************************************************************************/

/************************** OFFSET PORTA AUTOMATICA ***************************/
#define OFFSET_PORTA_AUTOMATICA							OFFSET_INDICE_AUDITORIAS_GRAVADOS + 2				//decimal 174
/******************************************************************************/

/************************** OFFSET PORTA AUTOMATICA ***************************/
#define OFFSET_OPCAO_SENSOR_CONTADOR					OFFSET_PORTA_AUTOMATICA + 1							//decimal 175
/******************************************************************************/

/************************** OFFSET PORTA AUTOMATICA ***************************/
#define OFFSET_OPCAO_MODO_ETHERNET						OFFSET_OPCAO_SENSOR_CONTADOR + 1							//decimal 176
/******************************************************************************/

/****************************** OFFSET SORTEADOR ******************************/
#define OFFSET_SORTEADOR								OFFSET_OPCAO_MODO_ETHERNET + 1						//decimal 177
/******************************************************************************/

/*************************** OFFSET CONT_SORTEADOR ****************************/
#define OFFSET_CONT_SORTEADOR							OFFSET_SORTEADOR + 1								//decimal 178
/******************************************************************************/

/************************ OFFSET PERCENTUAL_SORTEADOS *************************/
#define OFFSET_QUANTIDADE_SORTEADOS						OFFSET_CONT_SORTEADOR + 1					    	//decimal 179
/******************************************************************************/

/*************************** OFFSET NÚMERO SORTEADO ***************************/
#define OFFSET_NUMERO_SORTEADO							OFFSET_QUANTIDADE_SORTEADOS + 1						//decimal 180
/******************************************************************************/

/*************************** OFFSET SENHA TROCADA ***************************/
#define OFFSET_SENHA_GERENTE_TROCADA					OFFSET_NUMERO_SORTEADO + 1							//decimal 181
#define OFFSET_SENHA_TECNICO_TROCADA					OFFSET_SENHA_GERENTE_TROCADA + 1					//decimal 182
/******************************************************************************/

/*************************** OFFSET TIPO CONTROLE *****************************/
#define OFFSET_TIPO_CONTROLE							OFFSET_SENHA_TECNICO_TROCADA + 1					//decimal 183 até 185
/******************************************************************************/

/****************************** Endereço Inicial ******************************/
#define endFLASHInicial							 	 	(PAGINA_0 + OFFSET)									//0x43008
/******************************************************************************/

/**************************** Endereços das Senhas ****************************/
#define endFLASHSenhadaGerencia							(PAGINA_0 + OFFSET_SENHA_DA_GERENCIA)				//0x43008
#define endFLASHSenhadoTecnico    				    	(PAGINA_0 + OFFSET_SENHA_DO_TECNICO)				//0x4300E
#define endFLASHSenhadaEngenharia						(PAGINA_0 + OFFSET_SENHA_DA_ENGENHARIA)				//0x43014
/******************************************************************************/

/************************* Endereços da Sensibilidade *************************/
#define endFLASHSensibilidadeArea1						(PAGINA_0 + OFFSET_SENSIBILIDADE_AREA1)				//0x4301A
#define endFLASHSensibilidadeArea2						(PAGINA_0 + OFFSET_SENSIBILIDADE_AREA2)				//0x4301B
#define endFLASHSensibilidadeArea3						(PAGINA_0 + OFFSET_SENSIBILIDADE_AREA3)				//0x4301C
#define endFLASHSensibilidadeArea4						(PAGINA_0 + OFFSET_SENSIBILIDADE_AREA4)				//0x4301D
#define endFLASHSensibilidadeArea5						(PAGINA_0 + OFFSET_SENSIBILIDADE_AREA5)				//0x4301E
#define endFLASHSensibilidadeArea6						(PAGINA_0 + OFFSET_SENSIBILIDADE_AREA6)				//0x4301F
#define endFLASHSensibilidadeArea7						(PAGINA_0 + OFFSET_SENSIBILIDADE_AREA7)				//0x43020
#define endFLASHSensibilidadeArea8						(PAGINA_0 + OFFSET_SENSIBILIDADE_AREA8)				//0x43021
/******************************************************************************/

/*********************** Endereço do Modo de Travamento ***********************/
#define endFLASHModoTravamento							(PAGINA_0 + OFFSET_MODO_TRAVAMENTO)					//0x43022
/******************************************************************************/

/***************************** Endereço do Canal ******************************/
#define endFLASHCanal									(PAGINA_0 + OFFSET_CANAL)							//0x43023
/******************************************************************************/

/*********************** Endereço de Seleção de Metais ************************/
#define endFLASHSelecaoMetais							(PAGINA_0 + OFFSET_SELECAO_METAIS)					//0x43024
/******************************************************************************/

/**************************** Endereços da Trava ******************************/
#define endFLASHPulsoTrava								(PAGINA_0 + OFFSET_PULSO_TRAVA)						//0x43025
#define endFLASHSinalTrava								(PAGINA_0 + OFFSET_SINAL_TRAVA)						//0x43026
/******************************************************************************/

/***************************** Endereços do Relé ******************************/
#define endFLASHPulsoRele								(PAGINA_0 + OFFSET_PULSO_RELE)						//0x43027
#define endFLASHSinalRele								(PAGINA_0 + OFFSET_SINAL_RELE)						//0x43028
/******************************************************************************/

/********************** Endereços do Número de Controles **********************/
#define endFLASHNumeroControles							(PAGINA_0 + OFFSET_NUMERO_CONTROLES)				//0x43029
/******************************************************************************/

/************************* Endereços do Infravermelho *************************/
#define endFLASHSensibilidadeir							(PAGINA_0 + OFFSET_SENSIBILIDADEIR)					//0x4302A
#define endFLASHAnaliseir								(PAGINA_0 + OFFSET_ANALISEIR)						//0x4302B
/******************************************************************************/

/**************************** Endereço da Fábrica *****************************/
#define endFLASHFabrica									(PAGINA_0 + OFFSET_FABRICA)							//0x4302C
/******************************************************************************/

/**************************** Endereço de Idioma ******************************/
#define endFLASHIdioma									(PAGINA_0 + OFFSET_IDIOMA)							//0x4302D
/******************************************************************************/

/**************************** Endereços do Buzzer *****************************/
#define endFLASHBuzzerTom								(PAGINA_0 + OFFSET_BUZZER_TOM)						//0x4302E
#define endFLASHBuzzerVolume							(PAGINA_0 + OFFSET_BUZZER_VOLUME)					//0x4302F
#define endFLASHBuzzerLigDes							(PAGINA_0 + OFFSET_BUZZER_LIG_DES)					//0x43030
/******************************************************************************/

/*********************** Endereços da Mensagem de Voz *************************/
#define endFLASHMensagemVozVolume						(PAGINA_0 + OFFSET_MSG_VOZ_VOLUME)					//0x43031
#define endFLASHMensagemVozLigDes						(PAGINA_0 + OFFSET_MSG_VOZ_LIG_DES)					//0x43032
/******************************************************************************/

/************************* Endereço de Alarme Visual **************************/
#define endFLASHAlarmeVisualLigDes						(PAGINA_0 + OFFSET_ALARME_VISUAL_LIG_DES)			//0x43033
/******************************************************************************/

/********************* Endereços do Contador de Detecções *********************/
#define endFLASHTotalBloqueios							(PAGINA_0 + OFFSET_TOTAL_BLOQUEIOS)					//0x43034
#define endFLASHTotalDesbloqueios						(PAGINA_0 + OFFSET_TOTAL_DESBLOQUEIOS)				//0x43038
/******************************************************************************/

/********************* Endereços do Contador de Passagens *********************/
#define endFLASHContadorEntra							(PAGINA_0 + OFFSET_CONTADOR_ENTRADAS)				//0x4303C
#define endFLASHContadorSai								(PAGINA_0 + OFFSET_CONTADOR_SAIDAS)					//0x43040
/******************************************************************************/

/***************** Endereços do Contador de Passagens Diario ******************/
#define endFLASHContadorEntraDiario						(PAGINA_0 + OFFSET_CONTADOR_ENTRADAS_D)				//0x4303C
#define endFLASHContadorSaiDiario						(PAGINA_0 + OFFSET_CONTADOR_SAIDAS_D)			    //0x43040
#define endFLASHConferencia_do_Dia						(PAGINA_0 + OFFSET_CONFERENCIA_DO_DIA)			    //0x43040
/******************************************************************************/

/**************************** Endereço do Perfil ******************************/
#define endFLASHPerfil									(PAGINA_0 + OFFSET_PERFIL)				 			//0x43044
/******************************************************************************/


/************************* Endereços de AJUSTES TX RX *************************/
#define endFLASHCicloTrabalho							(PAGINA_0 + OFFSET_AJUSTES_TX_RX_CICLO_TRABALHO)	//0x43045
#define endFLASHDefasagem								(PAGINA_0 + OFFSET_AJUSTES_TX_RX_DEFASAGEM)			//0x43046
#define endFLASHFrequencia								(PAGINA_0 + OFFSET_AJUSTES_TX_RX_FREQUENCIA)		//0x43048
/******************************************************************************/

/*********************** Endereço de Modelo de Antena *************************/
#define endFLASHModeloAntena							(PAGINA_0 + OFFSET_MODELO_ANTENA)					//0x4304A
/******************************************************************************/

/******************** Endereços de Potenciômetros de Ganho ********************/
#define endFLASHPotenciometroGanho						(PAGINA_0 + OFFSET_POTENCIOMETRO_GANHO)
#define endFLASHPotenciometroGanhoArea1					(PAGINA_0 + OFFSET_POTENCIOMETRO_GANHO_AREA1)		//0x4304B
#define endFLASHPotenciometroGanhoArea2					(PAGINA_0 + OFFSET_POTENCIOMETRO_GANHO_AREA2)		//0x4304C
#define endFLASHPotenciometroGanhoArea3					(PAGINA_0 + OFFSET_POTENCIOMETRO_GANHO_AREA3)		//0x4304D
#define endFLASHPotenciometroGanhoArea4					(PAGINA_0 + OFFSET_POTENCIOMETRO_GANHO_AREA4)		//0x4304E
#define endFLASHPotenciometroGanhoArea5					(PAGINA_0 + OFFSET_POTENCIOMETRO_GANHO_AREA5)		//0x4304F
#define endFLASHPotenciometroGanhoArea6					(PAGINA_0 + OFFSET_POTENCIOMETRO_GANHO_AREA6)		//0x43050
#define endFLASHPotenciometroGanhoArea7					(PAGINA_0 + OFFSET_POTENCIOMETRO_GANHO_AREA7)		//0x43051
#define endFLASHPotenciometroGanhoArea8					(PAGINA_0 + OFFSET_POTENCIOMETRO_GANHO_AREA8)		//0x43052
/******************************************************************************/

/************* Endereços de Potenciômetros de Seleção de Metais ***************/
#define endFLASHPotenciometroSelecao					(PAGINA_0 + OFFSET_POTENCIOMETRO_SELECAO)
#define endFLASHPotenciometroSelecaoArea1				(PAGINA_0 + OFFSET_POTENCIOMETRO_SELECAO_AREA1)		//0x43053
#define endFLASHPotenciometroSelecaoArea2				(PAGINA_0 + OFFSET_POTENCIOMETRO_SELECAO_AREA2)		//0x43054
#define endFLASHPotenciometroSelecaoArea3				(PAGINA_0 + OFFSET_POTENCIOMETRO_SELECAO_AREA3)		//0x43055
#define endFLASHPotenciometroSelecaoArea4				(PAGINA_0 + OFFSET_POTENCIOMETRO_SELECAO_AREA4)		//0x43056
#define endFLASHPotenciometroSelecaoArea5				(PAGINA_0 + OFFSET_POTENCIOMETRO_SELECAO_AREA5)		//0x43057
#define endFLASHPotenciometroSelecaoArea6				(PAGINA_0 + OFFSET_POTENCIOMETRO_SELECAO_AREA6)		//0x43058
#define endFLASHPotenciometroSelecaoArea7				(PAGINA_0 + OFFSET_POTENCIOMETRO_SELECAO_AREA7)		//0x43059
#define endFLASHPotenciometroSelecaoArea8				(PAGINA_0 + OFFSET_POTENCIOMETRO_SELECAO_AREA8)		//0x4305A
/******************************************************************************/

/************************** Endereços de Anula Áreas **************************/
#define endFLASHAnulaAreas								(PAGINA_0 + OFFSET_ANULA_AREAS)
#define endFLASHAnulaArea1								(PAGINA_0 + OFFSET_ANULA_AREA1)						//0x4305B
#define endFLASHAnulaArea2								(PAGINA_0 + OFFSET_ANULA_AREA2)						//0x4305C
#define endFLASHAnulaArea3								(PAGINA_0 + OFFSET_ANULA_AREA3)						//0x4305D
#define endFLASHAnulaArea4								(PAGINA_0 + OFFSET_ANULA_AREA4)						//0x4305E
#define endFLASHAnulaArea5								(PAGINA_0 + OFFSET_ANULA_AREA5)						//0x4305F
#define endFLASHAnulaArea6								(PAGINA_0 + OFFSET_ANULA_AREA6)						//0x43060
#define endFLASHAnulaArea7								(PAGINA_0 + OFFSET_ANULA_AREA7)						//0x43061
#define endFLASHAnulaArea8								(PAGINA_0 + OFFSET_ANULA_AREA8)						//0x43062
/******************************************************************************/

/************************ Endereço do Filtro do Ruído *************************/
#define endFLASHFiltroRuido								(PAGINA_0 + OFFSET_FILTRO_RUIDO)					//0x43063
/******************************************************************************/

/*********************** Endereço da Trava Inteligente ************************/
#define endFLASHTravaInteligente						(PAGINA_0 + OFFSET_TRAVA_INTELIGENTE)				//0x43064
/******************************************************************************/

/************************* Endereço Tipo de Detector **************************/
#define endFLASHTipoDetector    						(PAGINA_0 + OFFSET_TIPO_DETECTOR)			    	//0x43065
/******************************************************************************/

/***************** Endereços Ponteiros de Log de Auditorias *******************/
#define endFLASHPonteiroBlocoA							(PAGINA_0 + OFFSET_PONTEIRO_BLOCO_A)				//0x43066
#define endFLASHPonteiroBytesA							(PAGINA_0 + OFFSET_PONTEIRO_BYTES_A)				//0x43067
/******************************************************************************/

/******************* Endereços Ponteiros de Log de Eventos ********************/
#define endFLASHPonteiroBlocoL							(PAGINA_0 + OFFSET_PONTEIRO_BLOCO_L)				//0x43069
#define endFLASHPonteiroBytesL							(PAGINA_0 + OFFSET_PONTEIRO_BYTES_L)				//0x4306A
/******************************************************************************/

/************************** Endereço Falha da Bobina **************************/
#define endFLASHFalhadaBobina							(PAGINA_0 + OFFSET_FALHA_DA_BOBINA)					//0x4306C
/******************************************************************************/

/******************************** Endereço IP *********************************/
#define endFLASHIP										(PAGINA_0 + OFFSET_ENDERECO_IP)						//0x4306D
/******************************************************************************/

/************************* Endereço MÁSCARA SUB-REDE **************************/
#define endFLASHMASCARASUBREDE							(PAGINA_0 + OFFSET_ENDERECO_SUB_REDE)				//0x4307C
/******************************************************************************/

/****************************** Endereço GATEWAY ******************************/
#define endFLASHGATEWAY									(PAGINA_0 + OFFSET_ENDERECO_GATEWAY)				//0x4308B
/******************************************************************************/

/******************************** Endereço DNS ********************************/
#define endFLASHDNS										(PAGINA_0 + OFFSET_ENDERECO_DNS)					//0x4309A
/******************************************************************************/

/**************** Endereço Ponteiro Indice de Eventos Gravado *****************/
#define endFLASHIndiceEventosGravados					(PAGINA_0 + OFFSET_INDICE_EVENTOS_GRAVADOS)			//0x430A9
/******************************************************************************/

/************** Endereço Ponteiro Indice de Auditorias Gravado ****************/
#define endFLASHIndiceAuditoriasGravados				(PAGINA_0 + OFFSET_INDICE_AUDITORIAS_GRAVADOS)		//0x430AB
/******************************************************************************/

/************************* Endereço Porta Automática **************************/
#define endFLASHPortaAutomatica							(PAGINA_0 + OFFSET_PORTA_AUTOMATICA)				//0x430AD
/******************************************************************************/

/*********************** Endereço Opção Sensor Contador ***********************/
#define endFLASHOpcaoSensorContador						(PAGINA_0 + OFFSET_OPCAO_SENSOR_CONTADOR)			//0x430AE
/******************************************************************************/

/************************ Endereço Opção Modo Ethernet ************************/
#define endFLASHModoEthernet							(PAGINA_0 + OFFSET_OPCAO_MODO_ETHERNET)				//0x430AF
/******************************************************************************/
/**************************** Endereço Sorteador ******************************/
#define endFLASHSorteador								(PAGINA_0 + OFFSET_SORTEADOR)						//0x430B0
/******************************************************************************/

/************************ Endereço Contador Sorteador *************************/
#define endFLASHContadorSorteador						(PAGINA_0 + OFFSET_CONT_SORTEADOR)					//0x430B1
/******************************************************************************/

/*********************** Endereço Quantidade Sorteados ************************/
#define endFLASHQuantidadeSorteados						(PAGINA_0 + OFFSET_QUANTIDADE_SORTEADOS)			//0x430B2
/******************************************************************************/

/************************** Endereço Número Sorteado **************************/
#define endFLASHNumeroSorteado							(PAGINA_0 + OFFSET_NUMERO_SORTEADO)					//0x430B3
/******************************************************************************/

/************************** Endereço Número Sorteado **************************/
#define endFLASH_SENHA_GERENTE_TROCADA					(PAGINA_0 + OFFSET_SENHA_GERENTE_TROCADA)			//0x430B4
#define endFLASH_SENHA_TECNICO_TROCADA					(PAGINA_0 + OFFSET_SENHA_TECNICO_TROCADA)			//0x430B5
/******************************************************************************/

/************************** Endereço Tipo Controle ****************************/
#define endFLASH_TIPO_CONTROLE							(PAGINA_0 + OFFSET_TIPO_CONTROLE)					//0x430B6 até 0x430B8
/******************************************************************************/

/************************** Endereço NÚMERO DE SÉRIE **************************/
#define endFLASHNumeroSerie								0x43000
/******************************************************************************/

/********************************* ESTRUTURAS *********************************/

/* Estrutura para data e hora */
typedef struct
{
	byte Dia;
	byte Mes;
	word Ano;
	byte Hora;
	byte Minuto;
	byte Segundo;
	byte DiaDaSemana;
}DataHora;

extern DataHora dataAtualizar;
/******************************************************************************/

/* Estrutura das tabelas de sinal, defasagem, frequência, ganho e sensibilidade com 10 canais */
typedef struct
{
	byte Sinal;
	word Defasagem;
	word Frequencia;
	byte Ganho[8];
	byte Sensibilidade[8];
}Stc_Tabela;

extern Stc_Tabela CanalAtual;
/******************************************************************************/

/* Estrutura do número serial das placas FONTE, PAINEL e GRAVADOR */
typedef struct
{
	byte Serial_number_Flash[8];
	byte Serial_Number_CAN[6];
}Stc_Placas;

extern Stc_Placas StcPlacas[3];
/******************************************************************************/

/******************************************************************************/

/****************************** Variáveis Globais *****************************/
LDD_TError Error;
LDD_TDeviceData *MyCANPtr,*MyRTCPtr,*MySPIPtr;
LDD_TDeviceData* SPI_DeviceData;

extern volatile byte menu;
extern volatile byte menu1;
extern volatile byte menu2;
extern volatile byte menu3;
extern volatile byte escolhe;
extern volatile byte flagretorno;
extern volatile word x,y,z,w,k,r;
extern volatile word num_geral;
extern volatile byte Err;
extern volatile byte confirma;

/******************************************************************************/

/******************************** Variáveis AD ********************************/
extern volatile bool FlagADC;
extern volatile bool FlagADC1;
extern volatile bool flagVelocidade1,flagVelocidade2,flagVelocidade3,flagVelocidade4;
extern volatile bool flagVelocidade5,flagVelocidade6,flagVelocidade7,flagVelocidade8;
extern volatile bool fimLeitura1,fimLeitura2,fimLeitura3,fimLeitura4;
extern volatile bool fimLeitura5,fimLeitura6,fimLeitura7,fimLeitura8;
extern volatile bool AREA1_DETECTOU,AREA2_DETECTOU,AREA3_DETECTOU,AREA4_DETECTOU;
extern volatile bool AREA5_DETECTOU,AREA6_DETECTOU,AREA7_DETECTOU,AREA8_DETECTOU;
extern volatile bool LENDO_AREAS,LENDO_AREAS1;
extern volatile byte detectou[8];
extern volatile byte nao_detectou[8];
extern volatile bool flag_antena_rx_sem_sinal;
extern volatile byte delta_t1,delta_t2,delta_t3,delta_t4;
extern volatile byte delta_t5,delta_t6,delta_t7,delta_t8;
extern volatile byte valorad;
extern volatile byte filtroruido;
extern volatile byte valor_sinal_area1,valor_sinal_area2,valor_sinal_area3,valor_sinal_area4,
		             valor_sinal_area5,valor_sinal_area6,valor_sinal_area7,valor_sinal_area8;
extern volatile byte anula_area[8];
extern volatile byte flagMonitoraAreas,areas_detectadas,flag_area_detectada;
/******************************************************************************/

/******************* Variáveis AJUSTE AUTOMÁTICO DE CANAL *********************/
extern volatile word Valor[8];
extern volatile word Valor1[8];
extern volatile dword Valor_Amostra_Area1[20];
extern volatile dword Valor_Amostra_Area2[20];
extern volatile dword Valor_Amostra_Area3[20];
extern volatile dword Valor_Amostra_Area4[20];
extern volatile dword Valor_Amostra_Area5[20];
extern volatile dword Valor_Amostra_Area6[20];
extern volatile dword Valor_Amostra_Area7[20];
extern volatile dword Valor_Amostra_Area8[20];
extern volatile dword numero_amostragens_canal[20];
extern volatile word tempo_leitura_canal;
/******************************************************************************/

/**************** Variáveis AJUSTE AUTOMÁTICO DE SENSIBILIDADE ****************/
extern volatile dword valor_amostragem[4];
extern volatile word tempo_amostragem;
extern volatile byte area_de_amostragem;
extern volatile byte ERRO_AUTOCALIBRACAO;
/******************************************************************************/

/*********************** Variáveis AJUSTES DO SISTEMA *************************/
extern volatile byte definicoes;
/******************************************************************************/

/************************** Variáveis AJUSTES TX-RX ***************************/
extern volatile byte ciclo_de_trabalho;
extern volatile word defasagem,aux_defasagem,frequencia;
/******************************************************************************/

/************************** Variáveis ALARME VISUAL ***************************/
extern volatile byte alarme_visual;
/******************************************************************************/

/***************************** Variáveis BARGRAPH *****************************/
extern volatile word valor_bargraph,valor_bargraph1,valor_presente,valor_presente1;
extern volatile word valor_anterior,valor_anterior1,valor_atual,valor_atual1;
extern volatile bool APAGA_BARGRAPH;
/******************************************************************************/

/***************************** Variáveis BATERIA ******************************/
extern volatile word percentual_bat;
extern volatile bool PISCA_LED_BAT;
extern volatile byte bateria_baixa;
/******************************************************************************/

/****************************** Variáveis BUZZER ******************************/
extern volatile byte buffer_buzzer[3];
extern volatile byte tempo_ativa_buzzer;
/******************************************************************************/

/******************************* Variáveis CAN ********************************/
LDD_CAN_TFrame Frame;
extern volatile uint8_t InData[8];
extern volatile uint8_t OutData[8];
extern volatile bool DataFrameTxFlg,DataFrameRxFlg;
extern volatile byte buffer_Presencas[3];
extern volatile byte estadoPresenca,estadoPresencaAnt,var_Tempo_Presenca;
extern volatile byte estado_CAN;
extern volatile word timeout_can;
extern volatile bool ERRO_CAN;
/******************************************************************************/

/****************************** Variáveis CANAL *******************************/
extern volatile byte canal;
extern volatile byte perfil;
/******************************************************************************/

/***************************** Variáveis CONTADOR *****************************/
extern volatile bool INICIA_TIME_OUT_CONTADOR_BLOQUEIOS_DESBLOQUEIOS;
extern volatile dword contador_bloqueios,contador_desbloqueios;
extern volatile dword contador_dia_entra,contador_dia_sai; //Contador de pessoas que entraram e sairam e total de pessoas que entrararam e sairam no dia
extern volatile byte conferencia_do_dia; //Variável que armazena o dia e se o dia for diferente zera os contadores diários.
extern volatile dword contador_entra,contador_sai,contador_passagens;
extern volatile byte flag_passagem,entrou,saiu,entrou_na_porta;
extern volatile byte flag_passagem1;
extern volatile byte estado_passagem,estado_passagem1,estado_CONTADOR,estado_CONTADOR_BLOQ_DESB,estado_BURLA;
extern volatile word tempo_permissao;
extern volatile word time_out_contador;
extern volatile byte opcaosensorcontador; //Variável que armazena o opção do sensor de contagem de pessoas a ser utilizado na PGDM, por padrão é SENSOR FRONTAL
/******************************************************************************/

/************************* Variáveis CONTROLE_REMOTO **************************/
extern volatile byte numero_controles;
extern volatile word tempo_cadastro_controle;
extern volatile bool ACAO_CONTROLE;
extern volatile bool RESULTADO_CONTROLE;
extern volatile bool INICIA_CONTADOR_PULSOS;
extern volatile word pulsos;
extern volatile word start_remoto;
extern volatile word start_remoto1;
extern volatile word tempo_leitura_botao_prog;
extern volatile word tempo_bt;
extern volatile word tempoVtInativo;
extern volatile byte tipoControle;
extern volatile byte indexControle[3];
extern volatile byte controlePressionado;
/******************************************************************************/

/*************************** Variáveis DATA e HORA ****************************/
extern volatile byte AtualizaDia,AtualizaMes,AtualizaAno,AtualizaHora,AtualizaMinuto,AtualizaSegundo;
/******************************************************************************/

/****************************** Variáveis DELAY *******************************/
extern volatile bool FIM_TEMPO_DELAY_S;
extern volatile word cont_ms,cont_s;
/******************************************************************************/

/****************************** Variáveis ESTADO ******************************/
extern volatile byte estado, estado_troca_senha,estado_LCD,estado_SERIAL,estado_MODULO_ETHERNET;
extern volatile byte estado_ENVIA_SERIAL_ETHERNET;
/******************************************************************************/

/************************* Variáveis ETHERNET-SERIAL **************************/
extern volatile byte envia_serial[512];
extern volatile byte recebe_serial[512];
//extern volatile byte aux_recebe_serial[255];
extern volatile byte byte_count;
extern volatile byte primeiro;
extern volatile byte dado_recebido;
extern volatile word Sent;
extern volatile byte aceito;
extern volatile byte num_auditorias;
extern volatile bool MANUTENCAO;
extern volatile bool emite_msg_manutencao;
extern volatile char str[3];
extern volatile char *str3;
extern volatile byte PADRAO;
extern volatile word time_out_ethernet;
extern volatile bool INICIA_TIME_OUT_ETHERNET;
extern volatile bool FIM_TIME_OUT_ETHERNET;

extern int contadorTentativasRecebimento;
extern volatile char erro_comunicacao;
extern volatile bool PRIMEIRO_ENVIO;
/******************************************************************************/

/***************************** Variáveis FABRICA ******************************/
extern volatile byte fabrica;
/******************************************************************************/

/************************ Variáveis FALHA DAS BOBINAS *************************/
extern volatile bool FALHA_DAS_BOBINAS;
extern volatile bool eliminar_falha;
/******************************************************************************/

/****************************** Variáveis FONTE *******************************/
extern volatile byte var_tensao_cinco;
extern volatile byte var_tensao_quinze;
extern volatile byte var_tensao_menos_quinze;
extern volatile byte var_tensao_rede;
extern volatile word var_tensao_bateria;
extern volatile word var_tensao_chaveada;
extern volatile byte estado_anterior_AC;
extern volatile byte estado_atual_AC;
extern volatile byte estado_anterior_BAT;
extern volatile byte estado_atual_BAT;
extern volatile byte estado_anterior_DT;
extern volatile byte estado_atual_DT;
extern volatile dword timer_tensoes;
extern volatile byte estado_da_fonte;
/******************************************************************************/

/****************************** Variáveis IDIOMA ******************************/
extern volatile byte idioma;
/******************************************************************************/

/************************** Variáveis INFRAVERMELHO ***************************/
extern volatile byte sensibilidadeir,aux_sensibilidadeir,var_infra1,var_infra2;
extern volatile byte analiseir;
extern volatile word time_debouncing_infra;
extern volatile bool anula_infras;
extern volatile int16 infra1_timer;
extern volatile int16 infra2_timer;
extern volatile bool INFRA1_TEMP;
extern volatile bool INFRA2_TEMP;
extern volatile bool sorteou;
/******************************************************************************/

/************************ Variáveis LOG DE AUDITORIAS *************************/
extern volatile dword num_bytes_a;
extern volatile dword num_bloco_a;
extern volatile dword end_bloco_a;
extern volatile dword n_bloco_a;
extern volatile word n_logauditorias;
extern volatile dword n_blocologauditorias;
extern volatile dword n_blocologauditorias_extra;
extern volatile byte posicao_bloco_a;
extern volatile word posicao_byte_a;
extern volatile word indice_auditorias;
extern volatile word indice_auditorias_cont;
extern volatile word indice_auditorias_lidos;
extern volatile word indice_auditorias_gravados;
extern volatile word indice_bloco_auditorias;
extern volatile char OPERADOR;
extern volatile char DISPOSITIVO;
extern volatile bool FIM_LOG_AUDITORIAS;
extern volatile dword ultimo_endereco_auditoria;
extern volatile byte flagAuditLido; //Do endereço 0x75000 a 0x79000-1 as flags inicializam com 0 o que significa que não foi preenchido, devemos preencher com 1 quando não foi lido e com 0 quando foi lido.
extern volatile byte AudToSend; //Flag para indicar que tem que ser reenviado o registro novamente pois o servidor perdeu a informação deste registro
extern volatile dword end_audit_reenvio; //Esta variavel inicia toda vez com 0x49000 ao iniciar o equipamento apontando para o primeiro endereço da flag de auditorias lidos
extern volatile word contador_endereco_audit; //Variável para contar os endereços na função Le os endereços das flags de auditorias.
/******************************************************************************/

/************ Variáveis LOG DE EVENTOS DE BLOQUEIOS E DESBLOQUEIOS ************/
extern volatile dword num_bytes_l;
extern volatile dword num_bloco_l;
extern volatile dword end_bloco_l;
extern volatile dword n_bloco_l;
extern volatile word n_logeventos;
extern volatile dword n_blocologeventos;
extern volatile dword n_blocologeventos_extra;
extern volatile byte posicao_bloco_l;
extern volatile word posicao_byte_l;
extern volatile word indice_eventos;
extern volatile word indice_eventos_cont;
extern volatile word indice_eventos_lidos;
extern volatile word indice_eventos_gravados;
extern volatile byte indice_bloco_eventos;
extern volatile bool INICIA_TIME_OUT_USB_SERIAL;
extern volatile word tempo_time_out_serial;
extern volatile bool FIM_LOG_EVENTOS;
extern volatile dword ultimo_endereco_eventos;
extern volatile byte estado_anterior_indice_eventos_gravados;
extern volatile byte estado_atual_indice_eventos_gravados;
extern volatile byte flagEventoLido;
extern volatile byte EventToSend;
extern volatile dword end_event_reenvio;
extern volatile word contador_endereco;
/******************************************************************************/

/************************** Variáveis MEMÓRIA FLASH ***************************/
extern volatile byte Write_Buffer_FLASH[4110];
extern volatile byte Read_Buffer_FLASH[4110];
extern volatile bool GRAVA_FLASH;
extern volatile dword numero_bloco;
extern volatile dword aux_numero_bloco;
extern volatile byte LEITURA_FLASH_FINALIZADA;
/******************************************************************************/

/************************* Variáveis MENSAGEM DE VOZ **************************/
extern volatile bool INICIA_TEMPO_MSG_VOZ;
extern volatile byte volume_mensagem_voz;
extern volatile byte lig_des_mensagem_voz;
extern volatile word tempo_msg_voz;
/******************************************************************************/

/************************* Variáveis MODELO DE ANTENA *************************/
extern volatile byte modelo_antena;
/******************************************************************************/

/*********************** Variáveis MODO DE TRAVAMENTO *************************/
extern volatile byte modo_travamento;
/******************************************************************************/

/*********************** Variáveis do MÓDULO ETHERNET *************************/
extern volatile byte modo_operacao_ethernet;
extern volatile byte end_IP[15];
extern volatile byte end_SUB_MASK[15];
extern volatile byte end_GATEWAY[15];
extern volatile byte end_DNS[15];
extern volatile byte end_aux[15];
extern volatile byte end_PORT[5];
extern volatile byte end_PORT1[5];
extern volatile byte HTTP[4];
extern volatile byte alterou;
extern volatile bool INICIA_TEMPO_ENVIO_ETHERNET;
extern volatile word tempo_envio_ethernet;
extern volatile byte recebendo;
extern volatile byte LIBERA_ENVIA_PACOTES;
/******************************************************************************/

/************************* Variáveis NÚMERO DE SÉRIE **************************/
extern volatile byte Num_Serie_Write[8];
extern volatile byte numero_serie[6];
extern volatile bool FIM_NUMERO_SERIE;
extern volatile dword senha_mestre_aux;
extern volatile byte var_senha_mestre[6];
extern volatile word tempo_numero_serie;
extern volatile bool INICIA_TEMPO_NUMERO_SERIE;
extern volatile bool flag_numero_serie;
/******************************************************************************/

/********************* Variáveis POTENCIÔMETROS DIGITAIS **********************/
extern volatile byte buffer_ganho[9],buffer_selecao[9];
/******************************************************************************/

/******************************* Variáveis RELÉ *******************************/
extern volatile byte pulso_rele;
extern volatile byte sinal_rele;
extern volatile word tempo_pulso_rele;
extern volatile bool HABILITA_TEMPO_PULSO_RELE;
/******************************************************************************/

/******************************* Variáveis RTC ********************************/
extern volatile unsigned char Vbat_powr_on;
extern LDD_RTC_TTime Time;
/******************************************************************************/

/************************ Variáveis SELEÇÃO DE METAIS *************************/
extern volatile byte selecao_metais,aux_selecao_metais;
/******************************************************************************/

/****************************** Variáveis SENHAS ******************************/
extern volatile byte senha_de_acesso,buffer_senhas[18],ch;
extern volatile byte senha[6];
extern volatile byte confirma_senha[6];
extern volatile char C;
extern volatile bool senha_gerente_trocada;
extern volatile bool senha_tecnico_trocada;
/******************************************************************************/

/************************** Variáveis SENSIBILIDADE ***************************/
extern volatile byte sensibilidade,buffer_sensibilidade[9],selecionaArea;
/******************************************************************************/

/************************* Variáveis SENSOR INDUTIVO **************************/
extern volatile byte INDUTIVO_ACIONADO;
extern volatile byte controle_ou_painel_travou;
extern volatile byte porta_automatica;
/******************************************************************************/

/*************************** Variáveis da SINALEIRA ***************************/
extern volatile bool fim_sinaleira;
/******************************************************************************/

/******************************* Variáveis TELA *******************************/
extern volatile bool INIBE_TELAS_DE_MSG;
extern volatile byte pos[2];
extern volatile word tela;
extern volatile word tempo_msg;
extern volatile byte tempo_tela_erro;
/******************************************************************************/

/****************************** Variáveis TECLAS ******************************/
extern volatile byte teclapressionada;
extern volatile byte tecla[9];
/******************************************************************************/

/*************************** Variáveis TEMPORIZADOR_10ms ***************************/
extern volatile word time_debouncing;
/******************************************************************************/

/************************* Variáveis TEMPORIZADOR_1s **************************/
extern volatile word tempo_leitura_tensoes;
extern volatile word tempo_contador_hora;
extern volatile byte rotina_hora;
/******************************************************************************/

/*************************** Variável Tipo Detector ***************************/
extern volatile byte tipo_detector;
/******************************************************************************/

/****************************** Variáveis TRAVA *******************************/
extern volatile byte pulso_trava;
extern volatile byte sinal_trava;
extern volatile word tempo_pulso_trava;
extern volatile bool HABILITA_TEMPO_PULSO_TRAVA;
extern volatile bool travado;
extern volatile byte trava_inteligente;
extern volatile bool INICIA_TEMPO_TRAVA_INTELIGENTE;
extern volatile word tempo_trava_inteligente;
extern volatile byte tempo_trava;
extern volatile byte pwm_trava;
extern volatile bool estado_trava;
/******************************************************************************/

/**************************** Variáveis USB-SERIAL ****************************/
extern volatile byte envia_serial1[70];
extern volatile byte recebe_serial1[70];
extern volatile byte byte_count1;
extern volatile byte primeiro1;
extern volatile byte dado_recebido1;
extern volatile word Sent1;
/******************************************************************************/

extern volatile char str[3];

/************************** Variáveis Integração ZC ***************************/
extern volatile bool statusPGDM;
/******************************************************************************/

/********************* Variáveis do SORTEADOR ELETRONICO **********************/
extern volatile byte sorteador;
extern volatile byte cont_sorteador;
extern volatile byte quantidade_sorteados;
extern volatile byte numero_sorteado;
/******************************************************************************/

/************************ Variáveis de ERRO do AGATA **************************/
extern volatile byte erroAgata;
/******************************************************************************/

extern volatile bool acao_cancelada;


/*************************** EXTRA FUNCTIONS ***********************************/

DataHora GetData(void);

/******************************************************************************/

#endif /* SOURCES_MAIN_H_ */

/*
 * telas.c
 *
 *  Created on: 07/11/2019
 *      Author: Alexandre Voigt da Poian
 */

#include "main.h"

volatile char telas_LCD[][3][16] =
{  //"1234567890123456","1234567890123456","1234567890123456","1234567890123456"}/
	{"ONIX TEC. BRASIL","ONIX TEC. BRASIL","ONIX TEC. BRASIL"},	//0 - TELA_INICIAL
	{"  AGATA 8 ZONAS ","  AGATA 8 ZONAS ","  AGATA 8 ZONES "},	//1

	{"ONIX TEC. BRASIL","ONIX TEC. BRASIL","ONIX TEC. BRASIL"},	//2 - TELA_INICIAL1
	{"  AGATA 8 ZONAS ","  AGATA 8 ZONAS ","  AGATA 8 ZONES "},	//3

	{"   AGUARDE...   ","    ESPERE...   ","     WAIT...    "},	//4 - TELA_AGUARDE

	{"    GERENCIA    ","    GESTION     ","   MANEGEMENT   "},	//5 - TELA_SENHA_DA_GERENCIA

	{"    TECNICO     ","    TECNICA     ","   TECHNICIAN   "},	//6 - TELA_SENHA_DO_TECNICO

	{"   ENGENHARIA   ","   INGINIERIA   ","   ENGINEERING  "},	//7 - TELA_SENHA_DA_ENGENHARIA

	{"SENHA INCORRETA ","   CONTRASENA   ","    INCORRECT   "},	//8 - TELA_SENHA_INCORRETA
	{"   DO SISTEMA   ","INCOR. DEL SIST.","SYSTEM PASSWORD "},	//9

	/****************************************************************************/

	/*** 1 - AJUSTES BÁSICOS ***/

	{"     AJUSTES    ","     AJUSTES    ","      BASIC     "},	//10 - TELA_AJUSTES_BASICOS
	{"     BASICOS    ","     BASICOS    ","   ADJUSTMENTS  "},	//11

	{"  AJUST. MANUAL ","  AJUST. MANUAL ","MANUAL ADJUSTM. "},	//12 - TELA_AJUSTE_MANUAL_DE_SENSIBILIDADE
	{"  SENSIBILIDADE ","  SENSIBILIDAD  ","   SENSITIVITY  "},	//13

	{" TODAS AS AREAS ","TODAS LAS AREAS ","  ALL THE AREAS "},	//14 - TELA_TODAS_AS_AREAS

	{"     AREA 1     ","     AREA 1     ","     AREA 1     "},	//15 - TELA_AREA_1

	{"     AREA 2     ","     AREA 2     ","     AREA 2     "},	//16 - TELA_AREA_2

	{"     AREA 3     ","     AREA 3     ","     AREA 3     "},	//17 - TELA_AREA_3

	{"     AREA 4     ","     AREA 4     ","     AREA 4     "},	//18 - TELA_AREA_4

	{"     AREA 5     ","     AREA 5     ","     AREA 5     "},	//19 - TELA_AREA_5

	{"     AREA 6     ","     AREA 6     ","     AREA 6     "},	//20 - TELA_AREA_6

	{"     AREA 7     ","     AREA 7     ","     AREA 7     "},	//21 - TELA_AREA_7

	{"     AREA 8     ","     AREA 8     ","     AREA 8     "},	//22 - TELA_AREA_8

	{"AJUST.AUTOMATICO","AJUST.AUTOMATICO","AUTOMATIC ADJUST"},	//23 - TELA_AJUSTE_AUTOMATICO_DA_SENSIBILIDADE
	{"  SENSIBILIDADE ","  SENSIBILIDAD  ","   SENSITIVITY  "},	//24

	{"PASSAR OBJETO NA","PASAR OBJETO EN "," PASS OBJECT ON "},	//25 - TELA_PASSAR_OBJETO_NA
	{"     AREA 4     ","     AREA 4     ","     AREA 4     "}, //26

	{"  PASSE AMOSTRA "," PASEO MUESTRA  ","   PASS SAMPLE  "}, //27 - TELA_PASSE_AMOSTRA

	{"     MODO DE    ","     MODO DE    ","    TRAVAMENT   "},	//28 - TELA_MODO_DE_TRAVAMENTO
	{"   TRAVAMENTO   ","     BLOQUEO    ","      MODE      "},	//29

	{"SOMENTE DESTRAVA","SOLAMEN.DESTRAVA","   ONLY UNLOCK  "}, //30 - TELA_SOMENTE_DESTRAVA

	{" TRAVA/DESTRAVA ","BLOQUEO/DESBLOQ.","   LOCK/UNLOCK  "}, //31 - TELA_TRAVA_DESTRAVA
	/****************************************************************************/

	/*** 2 - AJUSTES AVANÇADO ***/

	{"     AJUSTES    ","     AJUSTES    ","    ADVANCED    "}, //32 - TELA_AJUSTES_AVANCADOS
	{"    AVANCADOS   ","    AVANZADOS   ","    SETTINGS    "}, //33

	{"  AJUSTE MANUAL ","  AJUSTE MANUAL "," CHANNEL MANUAL "}, //34 - TELA_AJUSTE_MANUAL_DE_CANAL
	{"    DE CANAL    ","    DE CANAL    ","   ADJUSTMENT   "}, //35

	{"      CANAL     ","      CANAL     ","     CHANNEL    "}, //36 - TELA_CANAL
	{"       01       ","       01       ","       01       "}, //37

	{"AJUST.AUTOMATICO","  AJUSTE MANUAL "," CHANNEL MANUAL "}, //38 - TELA_AJUSTE_MANUAL_DE_CANAL
	{"    DE CANAL    ","    DE CANAL    ","   ADJUSTMENT   "}, //39

	{"SINTONIZANDO... ","  AFINACION...  ","  TUNING IN...  "}, //40 - TELA_SINTONIZANDO
	{"    CANAL       ","    CANAL       ","  CHANNEL       "}, //41

	{"  MELHOR CANAL  ","   MEJOR CANAL  ","  BEST CHANNEL  "}, //42 - TELA_MELHOR CANAL
	{"                ","                ","                "}, //43

	{" SELECAO METAIS ","SELECCIO.METALES","METAL SELECTION "}, //44 - TELA_SELECAO_DE_METAIS
	{"                ","                ","                "}, //45

	{"      TRAVA     ","    BLOQUEAR    ","      LOCK      "}, //46 - TELA_TRAVA
	{"                ","                ","                "}, //47

	{"      RELE      ","      RELAY     ","      RELAY     "}, //48 - TELA_RELE
	{"                ","                ","                "}, //49

	{"      PULSO     ","      PULSO     ","      PULSE     "}, //50 - TELA_PULSO
	{"      0.1s      ","      0.1s      ","      0.1s      "}, //51

	{"    RETENCAO    ","    RETENTION   ","    RETENCION   "}, //52 - TELA_RETENCAO_CONTROLE
	{"    CONTROLE    ","     CONTROL    ","   DE CONTROL   "}, //53

	{"    RETENCAO    ","    RETENTION   ","    RETENCION   "}, //54 - TELA_RETENCAO_CONTROLE_TECLADO
	{"CONTROLE+TECLADO","CONTROL+KEYBOARD","CONTROL+TECLADO "}, //55

	{"CONTROLE REMOTO "," CONTROL REMOTO "," REMOTE CONTROL "}, //56 - TELA_CONTROLE_REMOTO
	{"                ","                ","                "}, //57

	{"    CADASTRAR   ","    CADASTRAR   ","    REGISTER    "}, //58 - TELA_CADASTRAR_CONTROLES
	{"   CONTROLES?   ","   CONTROLES?   ","    CONTROLS?   "}, //59

	{"  DESCADASTRAR  ","  DESCADASTRAR  ","     REMOVE     "}, //60 - TELA_DESCADASTRAR_CONTROLES
	{"   CONTROLES?   ","   CONTROLES?   ","    CONTROLS?   "}, //61

	{"PRESS. QUALQUER ","PRESS. QUALQUIER","    PRESS ANY   "},	//62 - TELA_PRESSIONE_QUALQUER_TECLA_DO_CONTROLE
	{" TECLA CONTROLE ","  TECLA CONTROL ","  CONTROL KEY   "},	//63

	{" ERRO: CONTROLE ","ERROR:CONTROL NO"," ERROR: CONTROL "},	//64 - TELA_ERRO_CONTROLE_NAO_CADASTRADO
	{"NAO CADASTRADO! ","  CADASTRADO!   "," NOT REGISTERED "},	//65

	{"   CONTROLE JA  ","   CONTROL YA   ","   CONTROL HAS  "},	//66 - TELA_CONTROLE_JA_CADASTRADO
	{"   CADASTRADO!  ","   CADASTRADO!  "," ALREADY REGIST."},	//67

	{"   ADICIONADO   ","   ADICIONADO   ","  SUCCESSFULLY  "}, //68 - TELA_ADICIONADO_COM_SUCESSO
	{"  COM SUCESSO!  ","   CON EXITO!   ","     ADDED!     "},	//69

	{"DESCADASTRO COM ","DESCADASTRO CON ","     REMOVED    "},	//70 - TELA_DESCADASTRO_COM_SUCESSO
	{"  COM SUCESSO!  ","   CON EXITO!   ","  WITH SUCCESS! "},	//71

	{" INFRA VERMELHO ","   INFRA ROJO   ","   INFRA-RED    "},	//72 - TELA_INFRAVERMELHO

	{"   CALIBRAR IR  ","   CALIBRAR IR  ","  CALIBRATE IR  "}, //73 - TELA_CALBIBRAR_IR

	{"  CALIBRANDO... "," CALIBRADORA... "," CALIBRATING... "},	//74 - TELA_CALIBRANDO

	{"  CALIBRADO COM ","  CALIBRADO COM ","CALIBRATED WITH "},	//75 - TELA_CALIBRADO_COM

	{"   ANALISE IR   ","   ANALISIS IR  ","  ANALYZE IR   "},	//76 - TELA_ANALISE_IR
	/****************************************************************************/

	/*** 3 - AJUSTES DO SISTEMA ***/

	{"     AJUSTES    ","     AJUSTES    ","     SYSTEM     "}, //77 - TELA_AJUSTES_DO_SISTEMA
	{"   DO SISTEMA   ","   DEL SISTEMA  ","   ADJUSTMENTS  "},	//78

	{"   DATA E HORA  ","  FECHA Y HORA  ","  DATE AND TIME "},	//79 - TELA_DATA_E_HORA
	{"                ","                ","                "},	//80

	{"   VISUALIZAR   ","  DEMOSTRACION  ","      SHOW      "},	//81 - TELA_VISUALIZAR
	{"                ","                ","                "},	//82

	{"     ALTERAR    ","     CAMBIO     ","     CHANGE     "},	//83 - TELA_ALTERAR
	{"                ","                ","                "},	//84

	{"  ALTERA SENHA  ","CAMBIA CONTRAS. ","CHANGES PASSWORD"},	//85 - TELA_ALTERA_SENHA_DA_GERENCIA
	{"    GERENCIA    "," DE LA GERENCIA ","FROM MANEGEMENT "},	//86

	{"  ALTERA SENHA  ","CAMBIA CONTRAS. ","CHANGE TECHNICAL"},	//87 - TELA_ALTERA_SENHA_DO_TECNICO
	{"    TECNICO     ","   DEL TECNICO  ","    PASSWORD    "},	//88

	{"CONFIRME A SENHA","   CONFIRME LA  ","   CONFIRM THE  "},	//89 - TELA_CONFIRMAR_SENHA
	{"                ","   CONTRASENA   ","    PASSWORD    "},	//90

	{" RESETAR PADRAO ","RESETAR ESTANDAR"," RESET STANDARD "},	//91 - TELA RESETAR_PADROES_DE_FABRICA
	{"   DE FABRICA   ","   DE FABRICA   ","   OF FACTORY   "},	//92

	{"VOCE TEM CERTEZA","  ESTAS SEGURO? ","  ARE YOU SURE? "},	//93 - TELA_VOCE_TEM_CERTEZA
	{"[X] NAO  SIM [ ]","[X] NO    SI [ ]","[X] NO   YES [ ]"},	//94 - TELA_NAO_SIM

	{"     IDIOMA     ","     IDIOMA     ","    LANGUAGE    "},	//95 - TELA_IDIOMA
	{"    PORTUGUES   ","     ESPANOL    ","    ENGLISH     "},	//96
	/****************************************************************************/

	/*** 4 - AJUSTES DE ALARME ***/

	{"     AJUSTES    ","     AJUSTES    "," ALARM SETTINGS "},	//97 - TELA_AJUSTES_DE_ALARMES
	{"   DE ALARMES   ","   DE ALARMAS   ","                "},	//98

	{" ALARME SONORO  "," ALARMA SONORO  ","   ALARM SOUND  "},	//99 - TELA_ALARME_SONORO
	{"                ","                ","                "},	//100

	{"     BUZZER     ","     BUZZER     ","     BUZZER     "}, //101 - TELA_BUZZER

	{"  TOM DO BUZZER ","TONO DEL BUZZER ","   BUZZER TONE  "},	//102 - TELA_TOM_DO_BUZZER

	{"VOLUME DO BUZZER","VOLUMEN DEL BUZZ","  BUZZER VOLUME "}, //103 - TELA_VOLUME_DO_BUZZER

	{" LIGAR/DESLIGAR ","ENCENDER/APAGADO","     ON/OFF     "}, //104 - TELA_LIGAR_DESLIGAR

	{"MENSAGEM DE VOZ "," MENSAJE DE VOZ ","  VOICE MESSAGE "}, //105 - TELA_MENSAGEM_DE_VOZ

	{" VOLUME MSG VOZ "," VOLUMEN MSJ VOZ","VOLUME MSG VOICE"}, //106 - TELA_VOLUME_DA_MENSAGEM
	{"                ","                ","                "}, //107

	{"  ALARME VISUAL ","  ALARMA VISUAL ","  VISUAL ALARM  "},	//108 - TELA_ALARME_VISUAL

	{" LIGAR/DESLIGAR ","ENCENDER/APAGADO","     ON/OFF     "},	//109 - TELA_LIGAR_DESLIGAR_SINALEIRA_AREAS
	{" SINALEIRA AREAS","  ALARMA VISUAL ","  VISUAL ALARM  "},	//110
	/****************************************************************************/


	/*** 5- INFORMAÇÕES DO SISTEMA ***/

	{"   INFORMACOES  ","INFORMACION DEL ","     SYSTEM     "},	//111 - TELA_INFORMACOES_DO_SISTEMA
	{"   DO SISTEMA   ","     SISTEMA    ","  INFORMATION   "},	//112

	{"   CONTADOR DE  ","   CONTADOR DE  ","   DETECTION    "},	//113 - TELA_CONTADOR_DE_DETECCOES
	{"    DETECCOES   ","   DETECCIONES  ","     COUNTER    "},	//114

	{"TOTAL BLOQUEIOS "," TOTAL BLOQUEOS "," TOTAL LOCKINGS "}, //115 - TELA_TOTAL_BLOQUEIOS

	{"TOT.DESBLOQUEIOS","TOT.DESBLOQUEIOS","TOTAL UNLOCKINGS"},	//116 - TELA_TOTAL_DESBLOQUEIOS

	{"   CONTADOR DE  ","  PASS COUNTER  ","   CONTADOR DE  "}, //117 - TELA_CONTADOR_DE_PASSAGENS
	{"    PASSAGENS   ","                ","     PASAJES    "},	//118

	{"    ENTRADAS    ","    ENTRADAS    ","     ENTRIES    "}, //119 - TELA_ENTRADAS

	{"     SAIDAS     ","     SALIDAS    ","      EXITS     "}, //120 - TELA_SAIDAS

	{"ENTRADAS-SAIDAS ","ENTRADAS-SALIDAS"," ENTRIES-EXITS  "}, //121 - TELA_ENTRADAS_SAIDAS

	{"ZERAR CONTADORES","ZERAR CONTADORES","  ZERO COUNTERS "}, //122 - TELA_ZERAR_CONTADORES

	{"NUMERO DE SERIE ","NUMERO DE SERIE "," SERIAL NUMBER  "}, //123 - TELA_NUMERO_DE_SERIE
	/****************************************************************************/

	/*** 6 - INFORMAÇÕES DE ENERGIA ***/

	{" INFORMACOES DE ","     ENERGY     ","   INFORMACION  "},	//124 - TELA_INFORMACAOES_DE_ENERGIA
	{"    ENERGIA     ","   INFORMATION  ","   DE ENERGIA   "},	//125

	{"    TENSAO AC   ","   TENSION AC   ","   AC VOLTAGE   "}, //126 - TELA_TENSÃO_AC

	{"   TENSOES DC   ","  TENSIONES DC  ","    DC VOLTS    "}, //127 - TELA_TENSÃO_DC

	{" TENSAO BATERIAS","TENSION BATERIAS","TENS. BATTERIES "}, //128 - TELA_TENSÃO_DAS_BATERIAS

	/****************************************************************************/

	/*** 7 - DIAGNÓSTICO DO SISTEMA ***/

	{"   DIAGNOSTICO  ","  DIAGNOSTICO   ","     SYSTEM     "}, //129 - TELA_DIAGNOSTICO_DO_SISTEMA
	{"   DO SISTEMA   ","  DEL SISTEMA   ","   DIAGNOSIS    "}, //130

	{"   TESTE LEDS   ","   TESTE LEDS   ","    LED TEST    "}, //131 - TELA_TESTE_DE_LEDS
	{"                ","                ","                "}, //132

	{"   TESTE TRAVA  ","   TEST TRAVA   ","   TEST LOCK    "}, //133 - TELA_TESTE_DA TRAVA
	{"                ","                ","                "}, //134

	{"   TESTE RELE   ","   TESTE RELE   ","   RELAY TEST   "}, //135 - TELA_TESTE_DO_RELÉ
	{"                ","                ","                "}, //136

	{"  TESTE BUZZER  ","   TEST BUZZER  ","  BUZZER TEST   "}, //137 - TELA_TESTE_DO_BUZZER
	{"                ","                ","                "}, //138

	{"  TESTE MSG VOZ ","  TEST MSG VOZ  ","MSG VOICE TEST  "}, //139 - TELA_TESTE_DA_MENSAGEM_DE_VOZ
	{"                ","                ","                "}, //140

	{"     TESTE      ","      TEST      ","    INFRARED    "}, //141 - TELA_TESTE_DO_INFRAVERMELHO
	{" INFRAVERMELHO  ","   INFRARROJO   ","      TEST      "}, //142

	{"INFRA1 --> OFF  ","INFRA1 --> OFF  ","INFRA1 --> OFF  "}, //143 - TELA_INFRA1_OFF_E_INFRA2_OFF
	{"INFRA2 --> OFF  ","INFRA2 --> OFF  ","INFRA2 --> OFF  "}, //144

	{"INFRA1 --> ON   ","INFRA1 --> ON   ","INFRA1 --> ON   "}, //145 - TELA_INFRA1_ON_E_INFRA2_ON
	{"INFRA2 --> ON   ","INFRA2 --> ON   ","INFRA2 --> ON   "}, //146

	{"TENSAO SINAL RX "," TENSA SINAL RX ","RX SIGNAL TENS. "}, //147 - TELA_TENSAO_SINAL_RX
	{"                ","                ","                "}, //148

	{"SINAL A1:       ","SENAL A1:       ","SIGNAL A1:      "}, //149 - TELA_SINAL_A1_A2
	{"SINAL A2:       ","SENAL A2:       ","SIGNAL A2:      "}, //150

	{"SINAL A3:       ","SENAL A3:       ","SIGNAL A3:      "}, //151 - TELA_SINAL_A3_A4
	{"SINAL A4:       ","SENAL A4:       ","SIGNAL A4:      "}, //152

	{"SINAL A5:       ","SENAL A5:       ","SIGNAL A5:      "}, //153 - TELA_SINAL_A5_A6
	{"SINAL A6:       ","SENAL A6:       ","SIGNAL A6:      "}, //154

	{"SINAL A7:       ","SENAL A7:       ","SIGNAL A7:      "}, //155 - TELA_SINAL_A7_A8
	{"SINAL A8:       ","SENAL A8:       ","SIGNAL A8:      "}, //156
	/****************************************************************************/

	/*** 8 - AJUSTES TX-RX ***/

	{"     AJUSTES    ","     AJUSTES    ","      TX-RX     "},	//157 - TELA_AJUSTES_ENGENHARIA
	{"      TX-RX     ","      TX-RX     ","    SETTINGS    "}, //158

	{" CICLO DE TRAB. ","CICLO DE TRABAJO","   DUTY CICLE   "},	//159 - TELA_DUTY_CYCLE

	{"    DEFASAGEM   ","    DESFASAJE   ","    DEFASION    "}, //160 - TELA_DEFASAGEM

	{"   FREQUENCIA   ","   FRECUENCIA   ","   FREQUENCY    "}, //161 - TELA_FREQUENCIA
	/****************************************************************************/

	/*** 9 - MODELO DE ANTENA ***/

	{"MODELO DE ANTENA","MODELO DE ANTENA"," ANTENNA MODEL  "},	//162 - TELA_MODELO_DE_ANTENA
	{"                ","                ","                "}, //163
	/****************************************************************************/

	/*** 10 - POTENCIÔMETRO DE GANHO ***/

	{" POTENCIOMETRO  ","POTENCIOMETRO DE","      GAIN      "}, //164 - TELA_POTENCIOMETRO_DE_GANHO
	{"    DE GANHO    ","     GANADO     ","  POTENTIOMETER "}, //165

	{" POTENCIOMETRO  ","  POTENCIOMETRO "," POTENTIOMETER  "}, //166 - TELA_POTENCIOMETRO_DE_SELECAO_DE_METAIS
	{" SELECAO METAIS ","SELECCION METAL.","METAL SELECTION "}, //167
	/****************************************************************************/

	/*** TELAS DE USO GERAL ***/

	{"     ______     ","     ______     ","     ______     "},	//168 - TELA_SEIS_SUBSCRITOS

	{"                ","                ","                "},	//169 - TELA_LINHA_EM_BRANCO

	{"      001       ","      001       ","      001       "}, //170 - TELA_UM

	{"      100       ","      100       ","      100       "}, //171 - TELA_CEM

	{"      127       ","      127       ","      127       "}, //172 - TELA_CENTO_E_VINTE_E_SETE

	{"     FALHA      ","     FALLA      ","      COIL      "}, //173 - TELA_SEM_SINAL_NAS_ANTENAS
	{"  NAS BOBINAS!  ","  DELA BOBINA!  ","    FAILURE!    "}, //174

	{"     ERRO DE    ","    ERROR DE    ","  COMUNICATION  "}, //175 - TELA_ERRO_DE_COMUNICACAO
	{"  COMUNICACAO!  "," COMUNICACION!  ","     ERROR!     "}, //176

	{"CARGA DA BATERIA","CARGA DE LA BAT.","BATTERY CHARGING"},	//177 - TELA_CARGA_DA_BATERIA

	{" CARREGANDO...  ","  CARGANDO...   ","  CHARGING...   "}, //178 - TELA_CARREGANDO

	{"  MEMORIA FLASH ","  MEMORIA FLASH ","  FLASH MEMORY  "},	//179 - TELA_MEMORIA_FLASH_COM_DEFEITO
	{"   COM DEFEITO  ","   CON DEFECTO  ","   WITH DEFECT  "},	//180

	{"GRAVANDO PADROES","GRABANDO ESTAND.","    RECORDING   "},	//181 - TELA_GRAVANDO_PADROES_DE_FABRICA
	{"  DE FABRICA... ","  DE FABRICA... ","FACTORY DEFAULTS"},	//182

	{"  LENDO PADROES "," LENDO PATRONES ","READING RECORDED"},	//183 - TELA_LENDO_PADROES_GRAVADOS
	{"   GRAVADOS...  ","   GRABADOS...  ","   PATTERNS...  "},	//184

	{" ERRO NO INFRA1 ","ERROR EL INFRA1 ","ERROR ON INFRA1 "},	//185 - TELA_ERRO_NO_INFRA1

	{" ERRO NO INFRA2 ","ERROR EL INFRA2 ","ERROR ON INFRA2 "},	//186 - TELA_ERRO_NO_INFRA2

	{"INFRA1 DETECTADO","INFRA1 DETECTADO","INFRA1 DETECTED "},	//187 - TELA_INFRA1_DETECTADO

	{"INFRA2 DETECTADO","INFRA2 DETECTADO","INFRA2 DETECTED "},	//188 - TELA_INFRA2_DETECTADO

	{"    RETENCAO    ","   RETENCION    ","   RETENTION    "},	//189 - TELA_RETENCAO

	{"   APAGANDO...  ","   BORRANDO...  ","   ERASING...   "}, //190 - TELA_APAGANDO

	{"  ALTERA SENHA  ","CAMBIA CONTRAS. ","CHANGES PASSWORD"},	//191 - TELA_ALTERA_SENHA
	{"                ","                ","                "},	//192

	{" PLANA ONIX 2000"," PLANA ONIX 2000"," PLANA ONIX 2000"}, //193 - TELA_PLANA_ONIX_2000

	{" PLANA ONIX 2100"," PLANA ONIX 2100"," PLANA ONIX 2100"}, //194 - TELA_PLANA_ONIX_2100

	{" PLANA ONIX 440 "," PLANA ONIX 440 "," PLANA ONIX 440 "}, //195 - TELA_PLANA_ONIX_440

	{"CILIN. IECO 2000","CILIN. IECO 2000","CILIN. IECO 2000"}, //196 - TELA_CILINDRICA_IECO_2000

	{"CILIN. IECO 2100","CILIN. IECO 2100","CILIN. IECO 2100"}, //197 - TELA_CILINDRICA_IECO_2100

	{"     TECLADO    ","     TECLADO    ","    KEYBOARD    "}, //198 - TELA_TECLADO

	{"   AREA 1 E 2   ","   AREA 1 E 2   ","   AREA 1 E 2   "}, //199 - TELA_AREA_1_E_2

	{"   AREA 3 E 4   ","   AREA 3 E 4   ","   AREA 3 E 4   "}, //200 - TELA_AREA_3_E_4

	{"   AREA 5 E 6   ","   AREA 5 E 6   ","   AREA 5 E 6   "}, //201 - TELA_AREA_5_E_6

	{"   AREA 7 E 8   ","   AREA 7 E 8   ","   AREA 7 E 8   "}, //202 - TELA_AREA_7_E_8

	{"CAN DESCONECTADA","CAN DESCONECTADA","CAN DISCONNECTED"}, //203 - TELA_ERRO_COMUNICACAO
	{"ERRO COMUNICACAO","ERROR COMUNICAC.","COMUNICAT. ERROR"},

	{" TECLA CONFIRMA ","TECLA CONFIRMAC.","   CONFIRM KEY  "}, //205 - TELA_CONFIRMA

	{"TECLA INCREMENTA","TECLA INCREMENTA","  INCREMENT KEY "}, //206 - TELA_INCREMENTA

	{"TECLA DECREMENTA","TECLA CONFIRMAC.","  DECREMENT KEY "}, //207 - TELA_DECREMENTA

	{"  ANULA AREA 1  ","  ANULA AREA 1  ","  CANCEL AREA 1 "}, //208 - TELA_ANULA_AREA_1

	{"  ANULA AREA 2  ","  ANULA AREA 2  ","  CANCEL AREA 2 "}, //209 - TELA_ANULA_AREA_2

	{"  ANULA AREA 3  ","  ANULA AREA 3  ","  CANCEL AREA 3 "}, //210 - TELA_ANULA_AREA_3

	{"  ANULA AREA 4  ","  ANULA AREA 4  ","  CANCEL AREA 4 "}, //211 - TELA_ANULA_AREA_4

	{"  ANULA AREA 5  ","  ANULA AREA 5  ","  CANCEL AREA 5 "}, //212 - TELA_ANULA_AREA_5

	{"  ANULA AREA 6  ","  ANULA AREA 6  ","  CANCEL AREA 6 "}, //213 - TELA_ANULA_AREA_6

	{"  ANULA AREA 7  ","  ANULA AREA 7  ","  CANCEL AREA 7 "}, //214 - TELA_ANULA_AREA_7

	{"  ANULA AREA 8  ","  ANULA AREA 8  ","  CANCEL AREA 8 "}, //215 - TELA_ANULA_AREA_8

	{"   ANULA AREAS  ","   ANULA AREAS  ","  CANCEL AREAS  "}, //216 - TELA_ANULA_AREAS

	{"FILTRO DE RUIDO ","FILTRO DE RUIDO ","  NOISE FILTER  "}, //217 - TELA_FILTRO_DE_RUIDO

	{"COMPATIBILIDADE "," COMPATIBILIDAD ","ELETCROMAGNETIC "}, //218 - TELA_COMPATIBILIDADE_ELETROMAGNETICA_RX_A1_A2
	{"ELETROMAG. A1-A2","ELECTROMA. A1-A2","COMPATIBI. A1-A2"}, //219

	{"COMPATIBILIDADE "," COMPATIBILIDAD ","ELETCROMAGNETIC "}, //220 - TELA_COMPATIBILIDADE_ELETROMAGNETICA_RX_A3_A4
	{"ELETROMAG. A3-A4","ELECTROMA. A3-A4","COMPATIBI. A3-A4"}, //221

	{"COMPATIBILIDADE "," COMPATIBILIDAD ","ELETCROMAGNETIC "}, //222 - TELA_COMPATIBILIDADE_ELETROMAGNETICA_RX_A5_A6
	{"ELETROMAG. A5-A6","ELECTROMA. A5-A6","COMPATIBI. A5-A6"}, //223

	{"COMPATIBILIDADE "," COMPATIBILIDAD ","ELETCROMAGNETIC "}, //224 - TELA_COMPATIBILIDADE_ELETROMAGNETICA_RX_A7_A8
	{"ELETROMAG. A7-A8","ELECTROMA. A7-A8","COMPATIBI. A7-A8"}, //225

	{"A1:             ","A1:             ","A1:             "}, //226 - TELA_A1_A2
	{"A2:             ","A2:             ","A2:             "}, //227

	{"A3:             ","A3:             ","A3:             "}, //228 - TELA_A3_A4
	{"A4:             ","A4:             ","A4:             "}, //229

	{"A5:             ","A5:             ","A5:             "}, //230 - TELA_A5_A6
	{"A6:             ","A6:             ","A6:             "}, //231

	{"A7:             ","A7:             ","A7:             "}, //232 - TELA_A7_A8
	{"A8:             ","A8:             ","A8:             "}, //233

	{"    BARGRAPH    ","    BARGRAPH    ","    BARGRAPH    "}, //234 - TELA_BARGRAPH
	{"   AREAS 1 E 2  ","   AREAS 1 E 2  ","   AREAS 1 E 2  "}, //235 - TELA_AREA1E2
	{"   AREAS 3 E 4  ","   AREAS 3 E 4  ","   AREAS 3 E 4  "}, //236 - TELA_AREA3E4
	{"   AREAS 5 E 6  ","   AREAS 5 E 6  ","   AREAS 5 E 6  "}, //237 - TELA_AREA5E6
	{"   AREAS 7 E 8  ","   AREAS 7 E 8  ","   AREAS 7 E 8  "}, //238 - TELA_AREA7E8

	{"COMPATIBILIDADE "," COMPATIBILIDAD ","ELETCROMAGNETIC "}, //239 - TELA_COMPATIBILIDADE_ELETROMAGNETICA
	{"ELETROMAGNETICA ","ELECTROMAGNETICA"," COMPATIBILITY  "}, //240

	{"A1:             ","A1:             ","A1:             "}, //241 - TELA_A1_A2_COMPATIBILIDADE
	{"A2:             ","A2:             ","A2:             "}, //242

	{"A3:             ","A3:             ","A3:             "}, //243 - TELA_A3_A4_COMPATIBILIDADE
	{"A4:             ","A4:             ","A4:             "}, //244

	{"A5:             ","A5:             ","A5:             "}, //245 - TELA_A5_A6_COMPATIBILIDADE
	{"A6:             ","A6:             ","A6:             "}, //246

	{"A7:             ","A7:             ","A7:             "}, //247 - TELA_A7_A8_COMPATIBILIDADE
	{"A8:             ","A8:             ","A8:             "}, //248

	{"     TRAVA      ","   CERRADURA    ","      SMART     "}, //249 - TELA_TRAVA_INTELIGENTE
	{"  INTELIGENTE   ","  INTELIGENTE   ","      LOCK      "}, //250

	{"TRAVA INTELIGEN.","BLOQUEO INTELIG.","   SMART LOCK   "}, //251 - TELA_TRAVA_INTELIGENTE_ATIVADA
	{"     ATIVADA    ","       ON       ","       ON       "}, //252
	{"   DESATIVADA   ","       OFF      ","       OFF      "}, //253

	{"   CONTROLES    ","   CONTROLES    ","    CONTROLS    "}, //254 - TELA_CONTROLES_NAO_APAGADOS
	{"  NAO APAGADOS  ","  NO BORRADOS   ","   NOT ERASED   "}, //255

	{"PRESSIONE NOVAM.","PRESIONE NUEVAM.","   PRESS AGAIN  "}, //256 - TELA_PRESSIONE_NOVAMENTE_PARA_CONFIRMAR
	{" PARA CONFIRMAR "," PARA CONFIRMAR ","   TO CONFIRM   "}, //257

	{" NAO E POSSIVEL ","  NO SE PUEDEN  ","NO MORE CONTROLS"}, //258 - TELA_NUMERO_MAXIMO_CONTROLES
	{"CADAST.MAIS CTRL","REGISTR.MAS CTRL","CAN BE REGISTER."}, //259

	{"DETECTOR METAIS ","DETECTOR METALES"," METAL DETECTOR "}, //260 - TELA_DETECTOR_METAIS

	{" FONTE ALIMENT. ","FUENTE ALIMENT. ","  POWER SUPPLY  "}, //261 - TELA_FONTE_ALIMENTACAO

	{"   ZERAR LOGS   ","RESTABLECER REG.","   RESET LOGS   "}, //262 - TELA_ZERAR_LOG_EVENTOS

	{"___.___.___.___ ","___.___.___.___ ","___.___.___.___ "},	//263 - TELA_IP_SUBSCRITOS

	{"   ENDERECO IP  ","  DIRECCION IP  ","    IP ADRESS   "}, //264 - TELA_ENDERECO_IP

	{"MASCARA SUB-REDE","  DIRECCION IP  ","   SUBNET MASK  "}, //265 - TELA_MASCARA_SUB_REDE

	{"ENDERECO GATEWAY","DIRECCIO GATEWAY","GATEWAY ADDRESS "}, //266 - TELA_ENDERECO_GATEWAY

	{"    PORTA WEB   ","   PUERTO WEB   ","    WEB PORT    "}, //267 - TELA_PORTA_WEB

	{"CONFIGURACOES DE","CONFIGURACION DE","NETWORK SETTINGS"}, //268 - TELA_CONFIGURACOES_DE_INTERNET
	{"    INTERNET    ","    INTERNET    ","                "}, //269

	{"  ENDERECO DNS  ","  DIRECCION DNS ","   DNS ADDRESS  "}, //270 - TELA_ENDERECO_DNS

	{"TIPO DE DETECTOR","TIPO DE DETECTOR","  DETECTOR TYPE "}, //271 - TELA_TIPO_DETECTOR

	{"    3 AREAS     ","    3 AREAS     ","    3 AREAS     "}, //272 - TELA_3_AREAS

	{"    8 AREAS     ","    8 AREAS     ","    8 AREAS     "}, //273 - TELA_3_AREAS

	{"  AGATA 3 ZONAS ","  AGATA 3 ZONAS ","  AGATA 3 ZONES "},	//274 - TELA_INICIAL_3Z

	{"   AREAS 2 E 3  ","   AREAS 2 E 3  ","   AREAS 2 E 3  "}, //275 - TELA_AREA2E3

	{"A2:             ","A2:             ","A2:             "}, //276 - TELA_A2_A3
	{"A3:             ","A3:             ","A3:             "}, //277

	{"COMPATIBILIDADE "," COMPATIBILIDAD ","ELETCROMAGNETIC "}, //278 - TELA_COMPATIBILIDADE_ELETROMAGNETICA_RX_A2_A3
	{"ELETROMAG. A2-A3","ELECTROMA. A2-A3","COMPATIBI. A2-A3"}, //279

	{"A2:             ","A2:             ","A2:             "}, //280 - TELA_A2_A3_COMPATIBILIDADE
	{"A3:             ","A3:             ","A3:             "}, //281

	{"   AREA 2 E 3   ","   AREA 2 E 3   ","   AREA 2 E 3   "}, //282 - TELA_AREA_2_E_3

	{"SINAL A2:       ","SENAL A2:       ","SIGNAL A2:      "}, //283 - TELA_SINAL_A2_A3
	{"SINAL A3:       ","SENAL A3:       ","SIGNAL A3:      "}, //284

	{" ELIMINAR FALHA "," ELIMINAR FALHA "," ELIMINAR FALHA "}, //285 - TELA_ELIMINAR_FALHA_DAS_BOBINAS
	{"  DAS BOBINAS   ","  DAS BOBINAS   ","  DAS BOBINAS   "}, //286

	{"TENSAO FONTE 24V","VOLT. FUENTE 24V","24V SOURCE VOLT."}, //287 - TELA_FONTE_24V

	{"TESTE AUTONOMIA ","TESTE AUTONOMIA ","TESTE AUTONOMIA "}, //288 - TELA_TESTE_AUTONOMIA_DA_BATERIA
	{"   DA BATERIA   ","   DA BATERIA   ","   DA BATERIA   "}, //289

	{"BATERIA < 21.5V ","BATERIA < 21.5V ","BATERIA < 21.5V "}, //290 - TELA_DESLIGANDO_FONTE
	{"DESLIGANDO FONTE","DESLIGANDO FONTE","DESLIGANDO FONTE"}, //291

	{"      MODO      ","      MODO      ","      MODO      "}, //292 - TELA_MODO_PONTO_A_PONTO
	{" PONTO A PONTO  "," PONTO A PONTO  "," PONTO A PONTO  "}, //293

	{"      MODO      ","      MODO      ","      MODO      "}, //294 - TELA_MODO_PONTO_A_PONTO
	{" ACESSO REMOTO  "," ACESSO REMOTO  "," ACESSO REMOTO  "}, //295

	{" ENVIANDO LOGS  "," ENVIANDO LOGS  "," ENVIANDO LOGS  "}, //296 - TELA_EM_MANUTENCAO
	{"   AGUARDE...   ","   AGUARDE...   ","   AGUARDE...   "}, //297

	{"NUMERO DE SERIE ","NUMERO DE SERIE ","NUMERO DE SERIE "},	//298 - TELA_NUMERO_SERIE

	{"     GRAVAR     ","     GRAVAR     ","     GRAVAR     "}, //299 - TELA_GRAVAR_NUM_SERIE
	{"NUMERO DE SERIE ","NUMERO DE SERIE ","NUMERO DE SERIE "},	//300

	{"     STATIC     ","     STATIC     ","     STATIC     "},	//301 - TELA_STATIC
	{"                ","                ","                "}, //302

	{"      DHCP      ","      DHCP      ","      DHCP      "},	//303 - TELA_DHCP
	{"                ","                ","                "}, //304

	{" TECLE CONFIRMA "," TECLE CONFIRMA "," TECLE CONFIRMA "},	//305 - TELA_CONFIRMA_INICIAR
	{"  PARA INICIAR  ","  PARA INICIAR  ","  PARA INICIAR  "}, //306

	{"    ERRO NA     ","    ERRO NA     ","    ERRO NA     "},	//307 - TELA_ERRO_AUTOCALIBRACAO
	{" AUTOCALIBRACAO "," AUTOCALIBRACAO "," AUTOCALIBRACAO "}, //308

	{"PORTA AUTOMATICA","PORTA AUTOMATICA","PORTA AUTOMATICA"},	//309 - TELA_PORTA_AUTOMATICA

	{" OPCAO CONTADOR "," OPCAO CONTADOR "," OPCAO CONTADOR "},	//310 - TELA_OPCAO_DE_CONTADOR

	{" SENSOR FRONTAL "," SENSOR FRONTAL "," SENSOR FRONTAL "},	//311 - TELA_SENSOR_FRONTAL

	{"  SENSOR TETO   ","  SENSOR TETO   ","  SENSOR TETO   "},	//312 - TELA_SENSOR_TETO

	{"    IECO GT     ","    IECO GT     ","    IECO GT     "}, //313 - TELA IECO GT

	{" VALOR INVALIDO ","VALOR NO VALIDO ","  INVALID VALUE "}, //314 - TELA_VALOR_INVALIDO_EXE_BACKUP
	{"  RETROCEDENDO  "," RETROCEDIENDO  ","   GOING BACK   "}, //315

	{"MEM. CORROMPIDA ","MEMORIA CORRUPTA","CORRUPTED MEMORY"}, //316 - TELA_MEMORIA_CORROMPIDA_CONTATE
	{"CONTATE SUPORTE ","CONTACTE SOPORTE","   CALL SUPPORT "}, //317

	{"  MEM RESETADA  ","  MEM. RESETADA "," MEMORY RESETED "}, //318 - TELA_MEMORIA_CORROMPIDA_CONTATE
	{"    DESLIGUE    ","  APAGA APARATO ","   TURN OFF     "}, //319
	{"   SORTEADOR    ","   SORTEADOR    ","   SORTEADOR    "},	//320 - TELA_SORTEADOR_ELETRONICO
	{"   ELETRONICO   ","   ELETRONICO   ","   ELETRONICO   "},	//321
	{"CONFIRMA INICIAR","CONFIRMA INICIAR","CONFIRMA INICIAR"},	//322 - TELA_INICIAR_SORTEADOR
	{"QTD. SORTEADOS? ","QTD. SORTEADOS? ","QTD. SORTEADOS? "},	//323 - TELA_QUANTIDADE SORTEADOS
	{"PORTAL BLINDADO ","PORTAL BLINDADO "," SHIELDED WTMD  "},	//324
	{" TROQUE A SENHA ","CAMBIA PASSWORD ","CHANGE TECHNICAL"}, //325 - TELA_TROCAR_SENHA_GERENTE
	{"   DE GERENTE   ","  P/ CONTINUAR  ","    PASSWORD    "},
	{"TIPO DE CONTROLE","TIPO DE CONTROL ","  CONTROL TYPE  "},	//327 - TELA_TIPO_CONTROLE
	{"[X]USER  MENU[ ]","[X]USER  MENU[ ]","[X]USER  MENU[ ]"}, //328 - TELA_TIPO_A_B
	//TODO Remove below
	{" TESTE MSG VOZ1 ","  TEST MSG VOZ1 ","MSG VOICE TEST1 "}, //329 - TELA_TESTE_DA_MENSAGEM_DE_VOZ
	{"                ","                ","                "}, //330
	{" TESTE MSG VOZ2 ","  TEST MSG VOZ2 ","MSG VOICE TEST2 "}, //331 - TELA_TESTE_DA_MENSAGEM_DE_VOZ
	{"                ","                ","                "}, //332
	{" TESTE MSG VOZ3 ","  TEST MSG VOZ3 ","MSG VOICE TEST3 "}, //333 - TELA_TESTE_DA_MENSAGEM_DE_VOZ
	{"                ","                ","                "}, //334


};
	/****************************************************************************/


void Atualiza_LCD(void)
{
	estado_LCD = ESTADO_ESPERA; //Coloca a flag estado_LCD em ESTADO_ESPERA para não escrever novamente a mesma mensagem no LCD
	if(tela != TELA_VISUALIZAR_DATA_E_HORA) //Se a tela não for a TELA_VISUALIZAR_DATA_E_HORA limpa o LCD, senão não limpa porque tem que ficar atualizando a hora no LCD
	{
		LINHA = 1; //Posiciona na linha 1
		COLUNA = 1; //Posiciona na coluna 1
		LimpaLCD(); //Limpa o LCD
	}

	switch(tela) //Conforme variável tela vai para o case específico
	{
		/*** TELAS INICIAIS ***/

		case TELA_INICIAL:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_INICIAL][idioma]),pos);
			LINHA = 2;
			COLUNA = 5;
		 	PosicionaLCD(pos);
		  	EscreveChar((char)(StcPlacas[CONST_PLACA_PAINEL].Serial_number_Flash[0]));
		  	EscreveChar((char)(StcPlacas[CONST_PLACA_PAINEL].Serial_number_Flash[1]));
		  	EscreveChar((char)(StcPlacas[CONST_PLACA_PAINEL].Serial_number_Flash[2]));
		  	EscreveChar((char)(StcPlacas[CONST_PLACA_PAINEL].Serial_number_Flash[3]));
		  	EscreveChar((char)(StcPlacas[CONST_PLACA_PAINEL].Serial_number_Flash[4]));
		  	EscreveChar((char)(StcPlacas[CONST_PLACA_PAINEL].Serial_number_Flash[5]));
		  	EscreveChar((char)(StcPlacas[CONST_PLACA_PAINEL].Serial_number_Flash[6]));
		  	EscreveChar((char)(StcPlacas[CONST_PLACA_PAINEL].Serial_number_Flash[7]));
			break;
		}
		case TELA_INICIAL1:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_INICIAL1][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_INICIAL1+1][idioma]),pos);
		}

		case TELA_AGUARDE:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_AGUARDE][idioma]),pos);
			break;
		}
		case TELA_SENHA_DA_GERENCIA:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_SENHA_DA_GERENCIA][idioma]),pos);
			break;
		}
		case TELA_DIGITE_SENHA_DA_GERENCIA:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_SENHA_DA_GERENCIA][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD(telas_LCD[TELA_SEIS_SUBSCRITOS][idioma],pos);
			COLUNA = 6;
			PosicionaLCD(pos);
			break;
		}
		case TELA_SENHA_DO_TECNICO:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_SENHA_DO_TECNICO][idioma]),pos);
			break;
		}
		case TELA_DIGITE_SENHA_DO_TECNICO:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_SENHA_DO_TECNICO][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD(telas_LCD[TELA_SEIS_SUBSCRITOS][idioma],pos);
			COLUNA = 6;
			PosicionaLCD(pos);
			break;
		}
		case TELA_SENHA_DA_ENGENHARIA:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_SENHA_DA_ENGENHARIA][idioma]),pos);
			break;
		}
		case TELA_DIGITE_SENHA_DA_ENGENHARIA:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_SENHA_DA_ENGENHARIA][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD(telas_LCD[TELA_SEIS_SUBSCRITOS][idioma],pos);
			COLUNA = 6;
			PosicionaLCD(pos);
			break;
		}
		case TELA_SENHA_INCORRETA:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_SENHA_INCORRETA][idioma]),pos);
			delay_ms(2000);
			if(estado == ESTADO_AJUSTES_DO_SISTEMA)
			{
				tela = TELA_MOSTRA_AJUSTES_DO_SISTEMA;
			}
			else
			{
				tela = TELA_INICIAL;
			}
			estado_LCD = ATUALIZA_LCD;
			break;
		}
		/******************************************************************************/

		/*** 1 - AJUSTES BÁSICOS ***/

		case TELA_AJUSTES_BASICOS:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_AJUSTES_BASICOS][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_AJUSTES_BASICOS + 1][idioma]),pos);
			break;
		}
		case TELA_MOSTRA_AJUSTES_BASICOS:
		{
			if(menu == 1)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_AJUSTE_MANUAL_DE_SENSIBILIDADE][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_AJUSTE_MANUAL_DE_SENSIBILIDADE + 1][idioma]),pos);
			}
			else if(menu == 2)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_AJUSTE_AUTOMATICO_DA_SENSIBILIDADE][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_AJUSTE_AUTOMATICO_DA_SENSIBILIDADE + 1][idioma]),pos);
			}
			else if(menu == 3)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_MODO_DE_TRAVAMENTO][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_MODO_DE_TRAVAMENTO + 1][idioma]),pos);
			}
			else if(menu == 4)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_SORTEADOR_ELETRONICO][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_SORTEADOR_ELETRONICO + 1][idioma]),pos);
			}
			break;
		}
		case TELA_AJUSTE_MANUAL_DE_SENSIBILIDADE:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_AJUSTE_MANUAL_DE_SENSIBILIDADE][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_AJUSTE_MANUAL_DE_SENSIBILIDADE + 1][idioma]),pos);
			break;
		}
		case TELA_MOSTRA_SENSIBILIDADE_DAS_AREAS:
		{
			if(selecionaArea == TODAS_AREAS)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_TODAS_AS_AREAS][idioma]),pos);
				if(tipo_detector == Z3)
				{
					ACENDE_AREA1;
					ACENDE_AREA2;
					ACENDE_AREA4;
					ACENDE_AREA5;
					ACENDE_AREA7;
					ACENDE_AREA8;
				}
				else if(tipo_detector == Z8)
				{
					ACENDE_AREAS;
				}
			}
			else if(selecionaArea == AREA_1)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_AREA_1][idioma]),pos);
				APAGA_AREAS;
				if(tipo_detector == Z3)
				{
					ACENDE_AREA1;
					ACENDE_AREA2;
				}
				else if(tipo_detector == Z8)
				{
					ACENDE_AREA1;
				}
			}
			else if(selecionaArea == AREA_2)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_AREA_2][idioma]),pos);
				APAGA_AREAS;
				if(tipo_detector == Z3)
				{
					ACENDE_AREA4;
					ACENDE_AREA5;
				}
				else if(tipo_detector == Z8)
				{
					ACENDE_AREA2;
				}
			}
			else if(selecionaArea == AREA_3)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_AREA_3][idioma]),pos);
				APAGA_AREAS;
				if(tipo_detector == Z3)
				{
					ACENDE_AREA7;
					ACENDE_AREA8;
				}
				else if(tipo_detector == Z8)
				{
					ACENDE_AREA3;
				}
			}
			else if(selecionaArea == AREA_4)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_AREA_4][idioma]),pos);
				APAGA_AREAS;
				ACENDE_AREA4;
			}
			else if(selecionaArea == AREA_5)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_AREA_5][idioma]),pos);
				APAGA_AREAS;
				ACENDE_AREA5;
			}
			else if(selecionaArea == AREA_6)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_AREA_6][idioma]),pos);
				APAGA_AREAS;
				ACENDE_AREA6;
			}
			else if(selecionaArea == AREA_7)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_AREA_7][idioma]),pos);
				APAGA_AREAS;
				ACENDE_AREA7;
			}
			else if(selecionaArea == AREA_8)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_AREA_8][idioma]),pos);
				APAGA_AREAS;
				ACENDE_AREA8;
			}
			break;
		}
		case TELA_DIGITE_SENSIBILIDADE_DAS_AREAS:
		{
			if(selecionaArea == TODAS_AREAS)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_TODAS_AS_AREAS][idioma]),pos);
				if(tipo_detector == Z3)
				{
					ACENDE_AREA1;
					ACENDE_AREA2;
					ACENDE_AREA4;
					ACENDE_AREA5;
					ACENDE_AREA7;
					ACENDE_AREA8;
				}
				else if(tipo_detector == Z8)
				{
					ACENDE_AREAS;
				}
			}
			else if(selecionaArea == AREA_1)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_AREA_1][idioma]),pos);
				if(tipo_detector == Z3)
				{
					ACENDE_AREA1;
					ACENDE_AREA2;
				}
				else if(tipo_detector == Z8)
				{
					ACENDE_AREA1;
				}
			}
			else if(selecionaArea == AREA_2)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_AREA_2][idioma]),pos);
				if(tipo_detector == Z3)
				{
					ACENDE_AREA4;
					ACENDE_AREA5;
				}
				else if(tipo_detector == Z8)
				{
					ACENDE_AREA2;
				}
			}
			else if(selecionaArea == AREA_3)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_AREA_3][idioma]),pos);
				if(tipo_detector == Z3)
				{
					ACENDE_AREA7;
					ACENDE_AREA8;
				}
				else if(tipo_detector == Z8)
				{
					ACENDE_AREA3;
				}
			}
			else if(selecionaArea == AREA_4)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_AREA_4][idioma]),pos);
				ACENDE_AREA4;
			}
			else if(selecionaArea == AREA_5)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_AREA_5][idioma]),pos);
				ACENDE_AREA5;
			}
			else if(selecionaArea == AREA_6)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_AREA_6][idioma]),pos);
				ACENDE_AREA6;
			}
			else if(selecionaArea == AREA_7)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_AREA_7][idioma]),pos);
				ACENDE_AREA7;
			}
			else if(selecionaArea == AREA_8)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_AREA_8][idioma]),pos);
				ACENDE_AREA8;
			}
			LINHA = 2;
			COLUNA = 7;
			PosicionaLCD(pos);
			EscreveChar((char)((sensibilidade%1000)/100+48));
			EscreveChar((char)((sensibilidade%100)/10+48));
			EscreveChar((char)(sensibilidade%10+48));
			break;
		}
		case TELA_AJUSTE_AUTOMATICO_DA_SENSIBILIDADE:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_AJUSTE_AUTOMATICO_DA_SENSIBILIDADE][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_AJUSTE_AUTOMATICO_DA_SENSIBILIDADE + 1][idioma]),pos);
			break;
		}
		case TELA_PASSAR_OBJETO_NA:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_PASSAR_OBJETO_NA][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			if(area_de_amostragem == AREA_1)
			{
				ACENDE_AREA1;
				EscreveLCD((telas_LCD[TELA_AREA_1][idioma]),pos);
			}
			else if(area_de_amostragem == AREA_2)
			{
				ACENDE_AREA2;
				EscreveLCD((telas_LCD[TELA_AREA_2][idioma]),pos);
			}
			else if(area_de_amostragem == AREA_3)
			{
				ACENDE_AREA3;
				EscreveLCD((telas_LCD[TELA_AREA_3][idioma]),pos);
			}
			else if(area_de_amostragem == AREA_4)
			{
				ACENDE_AREA4;
				EscreveLCD((telas_LCD[TELA_AREA_4][idioma]),pos);
			}
			else if(area_de_amostragem == AREA_5)
			{
				ACENDE_AREA5;
				EscreveLCD((telas_LCD[TELA_AREA_5][idioma]),pos);
			}
			else if(area_de_amostragem == AREA_6)
			{
				ACENDE_AREA6;
				EscreveLCD((telas_LCD[TELA_AREA_6][idioma]),pos);
			}
			else if(area_de_amostragem == AREA_7)
			{
				ACENDE_AREA7;
				EscreveLCD((telas_LCD[TELA_AREA_7][idioma]),pos);
			}
			else if(area_de_amostragem == AREA_8)
			{
				ACENDE_AREA8;
				EscreveLCD((telas_LCD[TELA_AREA_8][idioma]),pos);
			}
			break;
		}
		case TELA_PASSE_AMOSTRA:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_PASSE_AMOSTRA][idioma]),pos);
			break;
		}
		case TELA_MODO_DE_TRAVAMENTO:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_MODO_DE_TRAVAMENTO][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_MODO_DE_TRAVAMENTO + 1][idioma]),pos);
			break;
		}
		case TELA_MOSTRA_MODO_DE_TRAVAMENTO:
		{
			if(modo_travamento == SOMENTE_DESTRAVA)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_SOMENTE_DESTRAVA][idioma]),pos);
			}
			else if(modo_travamento == TRAVA_DESTRAVA)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_TRAVA_DESTRAVA][idioma]),pos);
			}
			break;
		}
		case TELA_SOMENTE_DESTRAVA:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_SOMENTE_DESTRAVA][idioma]),pos);
			break;
		}
		case TELA_TRAVA_DESTRAVA:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_TRAVA_DESTRAVA][idioma]),pos);
			break;
		}
		/******************************************************************************/

		/*** 2 - AJUSTES AVANÇADOS ***/

		case TELA_AJUSTES_AVANCADOS:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_AJUSTES_AVANCADOS][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_AJUSTES_AVANCADOS + 1][idioma]),pos);
			break;
		}
		case TELA_MOSTRA_AJUSTES_AVANCADOS:
		{
			if(menu == 1)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_AJUSTE_MANUAL_DE_CANAL][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_AJUSTE_MANUAL_DE_CANAL + 1][idioma]),pos);
			}
			else if(menu == 2)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_AJUSTE_AUTOMATICO_DE_CANAL][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_AJUSTE_AUTOMATICO_DE_CANAL + 1][idioma]),pos);
			}
			else if(menu == 3)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_SELECAO_DE_METAIS][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_SELECAO_DE_METAIS + 1][idioma]),pos);
			}
			else if(menu == 4)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_TRAVA][idioma]),pos);
			}
			else if(menu == 5)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_RELE][idioma]),pos);
			}
			else if(menu == 6)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_CONTROLE_REMOTO][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_CONTROLE_REMOTO + 1][idioma]),pos);
			}
			else if(menu == 7)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_INFRAVERMELHO][idioma]),pos);
			}
			else if(menu == 8)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_ANULA_AREAS][idioma]),pos);
			}
			else if(menu == 9)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_FILTRO_DE_RUIDO][idioma]),pos);
			}
			else if(menu == 10)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_TRAVA_INTELIGENTE][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_TRAVA_INTELIGENTE + 1][idioma]),pos);
			}
			else if(menu == 11)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_PORTA_AUTOMATICA][idioma]),pos);
			}
			else if(menu == 12)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_ZERAR_LOG_EVENTOS][idioma]),pos);
			}
			else if(menu == 13)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_CONFIGURACOES_DE_INTERNET][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_CONFIGURACOES_DE_INTERNET + 1][idioma]),pos);
			}
			else if(menu == 14)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_ELIMINAR_FALHA_DAS_BOBINAS][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_ELIMINAR_FALHA_DAS_BOBINAS + 1][idioma]),pos);
			}
			else if(menu == 15)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_OPCAO_DE_CONTADOR][idioma]),pos);
			}
			else if(menu == 16)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_POTENCIOMETRO_DE_GANHO][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_POTENCIOMETRO_DE_GANHO + 1][idioma]),pos);
			}
			break;
		}
		case TELA_AJUSTE_MANUAL_DE_CANAL:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_AJUSTE_MANUAL_DE_CANAL][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_AJUSTE_MANUAL_DE_CANAL + 1][idioma]),pos);
			break;
		}
		case TELA_CANAL:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_CANAL][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_CANAL + 1][idioma]),pos);
			break;
		}
		case TELA_DIGITE_CANAL:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_CANAL][idioma]),pos);
			LINHA = 2;
			COLUNA = 8;
			PosicionaLCD(pos);
			EscreveChar((char)(canal/10+48));
			EscreveChar((char)(canal%10+48));
			break;
		}
		case TELA_AJUSTE_AUTOMATICO_DE_CANAL:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_AJUSTE_AUTOMATICO_DE_CANAL][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_AJUSTE_AUTOMATICO_DE_CANAL + 1][idioma]),pos);
			break;
		}
		case TELA_SINTONIZANDO:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_SINTONIZANDO][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_LINHA_EM_BRANCO][idioma]),pos);
			break;
		}
		case TELA_MELHOR_CANAL:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_MELHOR_CANAL][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_SINTONIZANDO + 1][idioma]),pos);
			COLUNA = 11;
			PosicionaLCD(pos);
			EscreveChar((char)(canal/10 + 48));
			EscreveChar((char)(canal%10 + 48));
			break;
		}
		case TELA_SELECAO_DE_METAIS:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_SELECAO_DE_METAIS][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_SELECAO_DE_METAIS + 1][idioma]),pos);
			break;
		}
		case TELA_MOSTRA_SELECAO_METAIS:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_SELECAO_DE_METAIS][idioma]),pos);
			LINHA = 2;
			COLUNA = 8;
			PosicionaLCD(pos);
			EscreveChar((char)(selecao_metais/100 + 48));
			EscreveChar((char)((selecao_metais%100)/10  + 48));
			EscreveChar((char)(selecao_metais%10  + 48));
			break;
		}
		case TELA_TRAVA:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_TRAVA][idioma]),pos);
			break;
		}
		case TELA_MOSTRA_TRAVA:
		{
			if(sinal_trava == trava_pulso)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_PULSO][idioma]),pos);
			}
			else if(sinal_trava == trava_retencao_controle)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_RETENCAO_CONTROLE][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_RETENCAO_CONTROLE + 1][idioma]),pos);
			}
			else if(sinal_trava == trava_retencao_controle_teclado)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_RETENCAO_CONTROLE_TECLADO][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_RETENCAO_CONTROLE_TECLADO + 1][idioma]),pos);
			}
			break;
		}
		case TELA_DIGITE_PULSO_TRAVA:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_PULSO][idioma]),pos);
			LINHA = 2;
			COLUNA = 8;
			PosicionaLCD(pos);
			EscreveChar((char)(pulso_trava/10 + 48));
			EscreveChar('.');
			EscreveChar((char)(pulso_trava%10 + 48));
			EscreveChar('s');
			break;
		}
		case TELA_RELE:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_RELE][idioma]),pos);
			break;
		}
		case TELA_MOSTRA_RELE:
		{
			if(sinal_rele == rele_pulso)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_PULSO][idioma]),pos);
			}
			else if(sinal_rele == rele_retencao)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_RETENCAO][idioma]),pos);
			}
			break;
		}
		case TELA_DIGITE_PULSO_RELE:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_PULSO][idioma]),pos);
			LINHA = 2;
			COLUNA = 7;
			PosicionaLCD(pos);
			EscreveChar((char)(pulso_rele/100 + 48));
			EscreveChar((char)((pulso_rele%100)/10 + 48));
			EscreveChar('.');
			EscreveChar((char)(pulso_rele%10 + 48));
			EscreveChar('s');
			break;
		}
		case TELA_PULSO:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_PULSO][idioma]),pos);
			break;
		}
		case TELA_RETENCAO:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_RETENCAO][idioma]),pos);
			break;
		}
		case TELA_RETENCAO_CONTROLE:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_RETENCAO_CONTROLE][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_RETENCAO_CONTROLE + 1][idioma]),pos);
			break;
		}
		case TELA_RETENCAO_CONTROLE_TECLADO:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_RETENCAO_CONTROLE_TECLADO][idioma]),pos);
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_RETENCAO_CONTROLE_TECLADO + 1][idioma]),pos);
			break;
		}
		case TELA_CONTROLE_REMOTO:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_CONTROLE_REMOTO][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_CONTROLE_REMOTO + 1][idioma]),pos);
			break;
		}
		case TELA_MOSTRA_CONTROLE_REMOTO:
		{
			if(menu1 == 1)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_CADASTRAR_CONTROLES][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_CADASTRAR_CONTROLES + 1][idioma]),pos);
			}
			else if(menu1 == 2)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_DESCADASTRAR_CONTROLES][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_DESCADASTRAR_CONTROLES + 1][idioma]),pos);
			}
			break;
		}
		case TELA_CADASTRAR_CONTROLES:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_CADASTRAR_CONTROLES][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_CADASTRAR_CONTROLES + 1][idioma]),pos);
			break;
		}
		case TELA_DESCADASTRAR_CONTROLES:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_DESCADASTRAR_CONTROLES][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_DESCADASTRAR_CONTROLES + 1][idioma]),pos);
			break;
		}
		case TELA_PRESSIONE_QUALQUER_TECLA_DO_CONTROLE:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_PRESSIONE_QUALQUER_TECLA_DO_CONTROLE][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_PRESSIONE_QUALQUER_TECLA_DO_CONTROLE + 1][idioma]),pos);
			break;
		}
		case TELA_PRESSIONE_NOVAMENTE_PARA_CONFIRMAR:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_PRESSIONE_NOVAMENTE_PARA_CONFIRMAR][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_PRESSIONE_NOVAMENTE_PARA_CONFIRMAR + 1][idioma]),pos);
			break;
		}
		case TELA_ERRO_CONTROLE_NAO_CADASTRADO:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_ERRO_CONTROLE_NAO_CADASTRADO][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_ERRO_CONTROLE_NAO_CADASTRADO + 1][idioma]),pos);
			delay_ms(2000);
			break;
		}
		case TELA_CONTROLE_JA_CADASTRADO:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_CONTROLE_JA_CADASTRADO][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_CONTROLE_JA_CADASTRADO + 1][idioma]),pos);
			delay_ms(2000);
			break;
		}
		case TELA_ADICIONADO_COM_SUCESSO:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_ADICIONADO_COM_SUCESSO][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_ADICIONADO_COM_SUCESSO + 1][idioma]),pos);
			delay_ms(2000);
			break;
		}
		case TELA_DESCADASTRO_COM_SUCESSO:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_DESCADASTRO_COM_SUCESSO][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_DESCADASTRO_COM_SUCESSO + 1][idioma]),pos);
			delay_ms(2000);
			break;
		}
		case TELA_CONTROLES_NAO_APAGADOS:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_CONTROLES_NAO_APAGADOS][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_CONTROLES_NAO_APAGADOS + 1][idioma]),pos);
			delay_ms(2000);
			break;
		}
		case TELA_NUMERO_MAXIMO_CONTROLES:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_NUMERO_MAXIMO_CONTROLES][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_NUMERO_MAXIMO_CONTROLES + 1][idioma]),pos);
			delay_ms(2000);
			break;
		}
		case TELA_INFRAVERMELHO:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_INFRAVERMELHO][idioma]),pos);
			break;
		}
		case TELA_MOSTRA_INFRAVERMELHO:
		{
			if(menu1 == 1)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_CALIBRAR_IR][idioma]),pos);
			}
			else if(menu1 == 2)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_ANALISE_IR][idioma]),pos);
			}
			break;
		}
		case TELA_SETA_CALIBRAR_IR:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_CALIBRAR_IR][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_NAO_SIM][idioma]),pos);
			confirma = NAO;
			LINHA = 2;
			COLUNA = 2;
			PosicionaLCD(pos);
			EscreveChar('X');
			LINHA = 2;
			COLUNA = 15;
			PosicionaLCD(pos);
			EscreveChar(' ');
			break;
		}
		case TELA_MOSTRA_CALIBRANDO:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_CALIBRANDO][idioma]),pos);
			LINHA = 2;
			COLUNA = 7;
			PosicionaLCD(pos);
			aux_sensibilidadeir = sensibilidadeir / 13;
			aux_sensibilidadeir = aux_sensibilidadeir * 5;
			EscreveChar((char)((aux_sensibilidadeir%1000)/100+48));
			EscreveChar((char)((aux_sensibilidadeir%100)/10+48));
			EscreveChar((char)(aux_sensibilidadeir%10+48));
			EscreveChar('%');
			break;
		}
		case TELA_MOSTRA_VALOR_CALIBRADO:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_CALIBRADO_COM][idioma]),pos);
			LINHA = 2;
			COLUNA = 7;
			PosicionaLCD(pos);
			aux_sensibilidadeir = sensibilidadeir / 13;
			aux_sensibilidadeir = aux_sensibilidadeir * 5;
			EscreveChar((char)((aux_sensibilidadeir%1000)/100+48));
			EscreveChar((char)((aux_sensibilidadeir%100)/10+48));
			EscreveChar((char)(aux_sensibilidadeir%10+48));
			EscreveChar('%');
			delay_ms(3000);
			break;
		}
		case TELA_SETA_ANALISE_IR:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_ANALISE_IR][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_NAO_SIM][idioma]),pos);
			if(analiseir == NAO)
			{
				LINHA = 2;
				COLUNA = 2;
				PosicionaLCD(pos);
				EscreveChar('X');
				LINHA = 2;
				COLUNA = 15;
				PosicionaLCD(pos);
				EscreveChar(' ');
			}
			else if(analiseir == SIM)
			{
				LINHA = 2;
				COLUNA = 2;
				PosicionaLCD(pos);
				EscreveChar(' ');
				LINHA = 2;
				COLUNA = 15;
				PosicionaLCD(pos);
				EscreveChar('X');
			}
			break;
		}
		case TELA_MOSTRA_ERRO_NOS_INFRAS:
		{
			LINHA = 1;
			COLUNA = 1;
			if(var_infra1 == 0)
			{
				EscreveLCD((telas_LCD[TELA_INFRA1_DETECTADO][idioma]),pos);
			}
			else if(var_infra1 == 1)
			{
				EscreveLCD((telas_LCD[TELA_ERRO_NO_INFRA1][idioma]),pos);
			}
			LINHA = 2;
			COLUNA = 1;
			if(var_infra2 == 0)
			{
				EscreveLCD((telas_LCD[TELA_INFRA2_DETECTADO][idioma]),pos);
			}
			else if(var_infra2 == 1)
			{
				EscreveLCD((telas_LCD[TELA_ERRO_NO_INFRA2][idioma]),pos);
			}
			delay_ms(3000);
			break;
		}
		case TELA_ANULA_AREAS:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_ANULA_AREAS][idioma]),pos);
			break;
		}
		case TELA_MOSTRA_ANULA_AREA:
		{
			if(menu1 == 1)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_ANULA_AREA_1][idioma]),pos);
			}
			else if(menu1 == 2)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_ANULA_AREA_2][idioma]),pos);
			}
			else if(menu1 == 3)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_ANULA_AREA_3][idioma]),pos);
			}
			else if(menu1 == 4)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_ANULA_AREA_4][idioma]),pos);
			}
			else if(menu1 == 5)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_ANULA_AREA_5][idioma]),pos);
			}
			else if(menu1 == 6)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_ANULA_AREA_6][idioma]),pos);
			}
			else if(menu1 == 7)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_ANULA_AREA_7][idioma]),pos);
			}
			else if(menu1 == 8)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_ANULA_AREA_8][idioma]),pos);
			}
			break;
		}
		case TELA_SETA_ANULAR_AREA:
		{
			tela = TELA_MOSTRA_ANULA_AREA;
			Atualiza_LCD();
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_NAO_SIM][idioma]),pos);
			if(anula_area[menu1 - 1] == NAO)
			{
				LINHA = 2;
				COLUNA = 2;
				PosicionaLCD(pos);
				EscreveChar('X');
				LINHA = 2;
				COLUNA = 15;
				PosicionaLCD(pos);
				EscreveChar(' ');
			}
			else if(anula_area[menu1 - 1] == SIM)
			{
				LINHA = 2;
				COLUNA = 2;
				PosicionaLCD(pos);
				EscreveChar(' ');
				LINHA = 2;
				COLUNA = 15;
				PosicionaLCD(pos);
				EscreveChar('X');
			}
			break;
		}
		case TELA_FILTRO_DE_RUIDO:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_FILTRO_DE_RUIDO][idioma]),pos);
			break;
		}
		case TELA_DIGITE_FILTRO_DE_RUIDO:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_FILTRO_DE_RUIDO][idioma]),pos);
			LINHA = 2;
			COLUNA = 8;
			PosicionaLCD(pos);
			EscreveChar((char)(filtroruido/10 + 48));
			EscreveChar((char)(filtroruido%10 + 48));
			break;
		}
		case TELA_SETA_TRAVA_INTELIGENTE:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_TRAVA_INTELIGENTE][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_NAO_SIM][idioma]),pos);
			if(trava_inteligente == NAO)
			{
				LINHA = 2;
				COLUNA = 2;
				PosicionaLCD(pos);
				EscreveChar('X');
				LINHA = 2;
				COLUNA = 15;
				PosicionaLCD(pos);
				EscreveChar(' ');
			}
			else if(trava_inteligente == SIM)
			{
				LINHA = 2;
				COLUNA = 2;
				PosicionaLCD(pos);
				EscreveChar(' ');
				LINHA = 2;
				COLUNA = 15;
				PosicionaLCD(pos);
				EscreveChar('X');
			}
			break;
		}
		case TELA_TRAVA_INTELIGENTE_ATIVADA:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_TRAVA_INTELIGENTE_ATIVADA][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_TRAVA_INTELIGENTE_ATIVADA + 1][idioma]),pos);
			delay_ms(3000);
			tela = TELA_INICIAL;
			estado_LCD = ATUALIZA_LCD;
			break;
		}
		case TELA_TRAVA_INTELIGENTE_DESATIVADA:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_TRAVA_INTELIGENTE_ATIVADA][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_TRAVA_INTELIGENTE_ATIVADA + 2][idioma]),pos);
			delay_ms(3000);
			tela = TELA_INICIAL;
			estado_LCD = ATUALIZA_LCD;
			break;
		}
		case TELA_MOSTRA_CONFIGURACOES_MODO_REDE:
		{
			if(menu1 == 1)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_MODO_PONTO_A_PONTO][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_MODO_PONTO_A_PONTO + 1][idioma]),pos);

			}
			else if(menu1 == 2)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_MODO_ACESSO_REMOTO][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_MODO_ACESSO_REMOTO + 1][idioma]),pos);
			}
			break;
		}
		case TELA_MOSTRA_CONFIGURACOES_DA_INTERNET:
		{
			if(menu2 == 1)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_ENDERECO_IP][idioma]),pos);
			}
			else if(menu2 == 2)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_MASCARA_SUB_REDE][idioma]),pos);
			}
			else if(menu2 == 3)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_ENDERECO_GATEWAY][idioma]),pos);
			}
			else if(menu2 == 4)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_ENDERECO_DNS][idioma]),pos);
			}
			else if(menu2 == 5)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_PORTA_WEB][idioma]),pos);
			}
			break;
		}
		case TELA_ENDERECO_IP:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_ENDERECO_IP][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			PosicionaLCD(pos);
			for(x = 0;x < 15;x++)
			{
				if(end_IP[x] != '.')
				{
					EscreveChar((char)(end_IP[x]));
				}
				else
				{
					EscreveChar('.');
				}
			}
			break;
		}
		case TELA_MASCARA_SUB_REDE:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_MASCARA_SUB_REDE][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			PosicionaLCD(pos);
			for(x = 0;x < 15;x++)
			{
				if(end_SUB_MASK[x] != '.')
				{
					EscreveChar((char)(end_SUB_MASK[x]));
				}
				else
				{
					EscreveChar('.');
				}
			}
			break;
		}
		case TELA_ENDERECO_GATEWAY:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_ENDERECO_GATEWAY][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			PosicionaLCD(pos);
			for(x = 0;x < 15;x++)
			{
				if(end_GATEWAY[x] != '.')
				{
					EscreveChar((char)(end_GATEWAY[x]));
				}
				else
				{
					EscreveChar('.');
				}
			}
			break;
		}
		case TELA_ENDERECO_DNS:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_ENDERECO_DNS][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			PosicionaLCD(pos);
			for(x = 0;x < 15;x++)
			{
				if(end_DNS[x] != '.')
				{
					EscreveChar((char)(end_DNS[x]));
				}
				else
				{
					EscreveChar('.');
				}
			}
			break;
		}
		case TELA_PORTA_WEB:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_PORTA_WEB][idioma]),pos);
			LINHA = 2;
			COLUNA = 6;
			PosicionaLCD(pos);
			for(x = 0;x < 5;x++)
			{
				EscreveChar((char)(end_PORT[x]));
			}
			break;
		}
		case TELA_TIPO_DETECTOR:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_TIPO_DETECTOR][idioma]),pos);
			break;
		}
		case TELA_3_AREAS:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_TIPO_DETECTOR][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_3_AREAS][idioma]),pos);
			break;
		}
		case TELA_8_AREAS:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_TIPO_DETECTOR][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_8_AREAS][idioma]),pos);
			break;
		}

		case TELA_ELIMINAR_FALHA_DAS_BOBINAS:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_ELIMINAR_FALHA_DAS_BOBINAS][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_ELIMINAR_FALHA_DAS_BOBINAS + 1][idioma]),pos);
			break;
		}
		case TELA_SETA_ELIMINAR_FALHA_DAS_BOBINAS:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_ELIMINAR_FALHA_DAS_BOBINAS][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_NAO_SIM][idioma]),pos);
			if(eliminar_falha == NAO)
			{
				LINHA = 2;
				COLUNA = 2;
				PosicionaLCD(pos);
				EscreveChar('X');
				LINHA = 2;
				COLUNA = 15;
				PosicionaLCD(pos);
				EscreveChar(' ');
			}
			else if(eliminar_falha == SIM)
			{
				LINHA = 2;
				COLUNA = 2;
				PosicionaLCD(pos);
				EscreveChar(' ');
				LINHA = 2;
				COLUNA = 15;
				PosicionaLCD(pos);
				EscreveChar('X');
			}
			break;
		}
		case TELA_OPCAO_DE_CONTADOR:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD(telas_LCD[TELA_OPCAO_DE_CONTADOR],pos);
			break;
		}
		case TELA_MOSTRA_OPCAO_SENSOR_CONTADOR:
		{
			if(opcaosensorcontador == SENSOR_FRONTAL)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD(telas_LCD[TELA_OPCAO_DE_CONTADOR],pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD(telas_LCD[TELA_SENSOR_FRONTAL],pos);
			}
			else if(opcaosensorcontador == SENSOR_TETO)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD(telas_LCD[TELA_OPCAO_DE_CONTADOR],pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD(telas_LCD[TELA_SENSOR_TETO],pos);
			}
			break;
		}


		/******************************************************************************/

		/*** 3 - AJUSTES DO SISTEMA ***/

		case TELA_AJUSTES_DO_SISTEMA:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_AJUSTES_DO_SISTEMA][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_AJUSTES_DO_SISTEMA + 1][idioma]),pos);
			break;
		}
		case TELA_MOSTRA_AJUSTES_DO_SISTEMA:
		{
			if(menu == 1)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_DATA_E_HORA][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_DATA_E_HORA + 1][idioma]),pos);
			}
			else if(menu == 2)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_ALTERA_SENHA_DA_GERENCIA][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_ALTERA_SENHA_DA_GERENCIA + 1][idioma]),pos);
			}
			else if(menu == 3)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_ALTERA_SENHA_DO_TECNICO][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_ALTERA_SENHA_DO_TECNICO + 1][idioma]),pos);
			}
			else if(menu == 4)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_RESETAR_PADROES_DE_FABRICA][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_RESETAR_PADROES_DE_FABRICA + 1][idioma]),pos);
			}
			else if(menu == 5)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_IDIOMA][idioma]),pos);
				break;
			}
			break;
		}
		case TELA_MOSTRA_OPCOES_DATA_E_HORA:
		{
			if(menu1 == 1)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_VISUALIZAR][idioma]),pos);
			}
			else if(menu1 == 2)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_ALTERAR][idioma]),pos);
			}
			break;
		}
		case TELA_VISUALIZAR_DATA_E_HORA:
		{
			if(AtualizaDia)
			{
				LINHA = 1;
				COLUNA = 4;
				PosicionaLCD(pos);
				EscreveChar((char)(dataAtualizar.Dia/10 + 48));
				EscreveChar((char)(dataAtualizar.Dia%10 + 48));
			}
			if(AtualizaMes)
			{
				LINHA = 1;
				COLUNA = 7;
				PosicionaLCD(pos);
				EscreveChar((char)(dataAtualizar.Mes/10 + 48));
				EscreveChar((char)(dataAtualizar.Mes%10 + 48));
			}
			if(AtualizaAno)
			{
				LINHA = 1;
				COLUNA = 10;
				PosicionaLCD(pos);
				EscreveChar((char)(dataAtualizar.Ano/1000 + 48));
				EscreveChar((char)((dataAtualizar.Ano%1000)/100 + 48));
				EscreveChar((char)((dataAtualizar.Ano%100)/10 + 48));
				EscreveChar((char)(dataAtualizar.Ano%10 + 48));
			}
			if(AtualizaHora)
			{
				LINHA = 2;
				COLUNA = 5;
				PosicionaLCD(pos);
				EscreveChar((char)(dataAtualizar.Hora/10 + 48));
				EscreveChar((char)(dataAtualizar.Hora%10 + 48));
			}
			if(AtualizaMinuto)
			{
				LINHA = 2;
				COLUNA = 8;
				PosicionaLCD(pos);
				EscreveChar((char)(dataAtualizar.Minuto/10 + 48));
				EscreveChar((char)(dataAtualizar.Minuto%10 + 48));
			}
			if(AtualizaSegundo)
			{
				LINHA = 2;
				COLUNA = 11;
				PosicionaLCD(pos);
				EscreveChar((char)(dataAtualizar.Segundo/10 + 48));
				EscreveChar((char)(dataAtualizar.Segundo%10 + 48));
			}
			break;
		}
		case TELA_ALTERA_SENHA:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_ALTERA_SENHA][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_SEIS_SUBSCRITOS][idioma]),pos);
			break;
		}
		case TELA_DIGITE_NOVA_SENHA:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_ALTERA_SENHA][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_SEIS_SUBSCRITOS][idioma]),pos);
			LINHA = 2;
			COLUNA = 6;
			PosicionaLCD(pos);
			break;
		}
		case TELA_CONFIRMAR_SENHA:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_CONFIRMAR_SENHA][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_SEIS_SUBSCRITOS][idioma]),pos);
			LINHA = 2;
			COLUNA = 6;
			break;
		}
		case TELA_VOCE_TEM_CERTEZA:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_VOCE_TEM_CERTEZA][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_NAO_SIM][idioma]),pos);
			break;
		}
		case TELA_MOSTRA_IDIOMA:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_IDIOMA][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_IDIOMA + 1][idioma]),pos);
			break;
		}
		case TELA_ATUALIZAR_DH:
		{
			LINHA = 1;
			COLUNA = 4;
			PosicionaLCD(pos);
			EscreveChar((char)(dataAtualizar.Dia/10 + 48));
			EscreveChar((char)(dataAtualizar.Dia%10 + 48));
			EscreveChar('/');
			EscreveChar((char)(dataAtualizar.Mes/10 + 48));
			EscreveChar((char)(dataAtualizar.Mes%10 + 48));
			EscreveChar('/');
			EscreveChar((char)(dataAtualizar.Ano/1000 + 48));
			EscreveChar((char)((dataAtualizar.Ano%1000)/100 + 48));
			EscreveChar((char)((dataAtualizar.Ano%100)/10 + 48));
			EscreveChar((char)(dataAtualizar.Ano%10 + 48));
			LINHA = 2;
			COLUNA = 5;
			PosicionaLCD(pos);
			EscreveChar((char)(dataAtualizar.Hora/10 + 48));
			EscreveChar((char)(dataAtualizar.Hora%10 + 48));
			EscreveChar(':');
			EscreveChar((char)(dataAtualizar.Minuto/10 + 48));
			EscreveChar((char)(dataAtualizar.Minuto%10 + 48));
			EscreveChar(':');
			EscreveChar((char)(dataAtualizar.Segundo/10+48));
			EscreveChar((char)(dataAtualizar.Segundo%10+48));
			break;
		}
		/******************************************************************************/

		/*** 4 - AJUSTES DE ALARME ***/

		case TELA_AJUSTES_DE_ALARME:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_AJUSTES_DE_ALARME][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_AJUSTES_DE_ALARME+1][idioma]),pos);
			break;
		}
		case TELA_MOSTRA_AJUSTES_DE_ALARME:
		{
			if(menu == 1)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_ALARME_SONORO][idioma]),pos);
			}
			else if(menu == 2)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_ALARME_VISUAL][idioma]),pos);
			}
			break;
		}
		case TELA_MOSTRA_ALARME_SONORO:
		{
			if(menu2 == 1)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_BUZZER][idioma]),pos);
			}
			else if(menu2 == 2)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_MENSAGEM_DE_VOZ][idioma]),pos);
			}
			break;
		}
		case TELA_BUZZER:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_BUZZER][idioma]),pos);
			break;
		}
		case TELA_MOSTRA_BUZZER:
		{
			if(menu3 == 0)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_TOM_DO_BUZZER][idioma]),pos);
			}
			else if(menu3 == 1)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_VOLUME_DO_BUZZER][idioma]),pos);
			}
			break;
		}
		case TELA_MOSTRA_TOM_DO_BUZZER:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_TOM_DO_BUZZER][idioma]),pos);
			LINHA = 2;
			COLUNA = 8;
			PosicionaLCD(pos);
			EscreveChar((char)(buffer_buzzer[BUZZER_TOM])/10 + 48);
			EscreveChar((char)(buffer_buzzer[BUZZER_TOM])%10 + 48);
			//TocaTomBuzzer();
			break;
		}
		case TELA_MOSTRA_VOLUME_DO_BUZZER:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_VOLUME_DO_BUZZER][idioma]),pos);
			LINHA = 2;
			COLUNA = 8;
			PosicionaLCD(pos);
			EscreveChar((char)(buffer_buzzer[BUZZER_VOLUME])/10 + 48);
			EscreveChar((char)(buffer_buzzer[BUZZER_VOLUME])%10 + 48);
			//TocaTomBuzzer();
			break;
		}
		case TELA_MENSAGEM_DE_VOZ:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_MENSAGEM_DE_VOZ][idioma]),pos);
			break;
		}
		case TELA_MOSTRA_MSG_VOZ:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_VOLUME_DA_MENSAGEM][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_VOLUME_DA_MENSAGEM + 1][idioma]),pos);
			break;
		}
		case TELA_MOSTRA_VOLUME_MSG_VOZ:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_VOLUME_DA_MENSAGEM][idioma]),pos);
			LINHA = 2;
			COLUNA = 8;
			PosicionaLCD(pos);
			EscreveChar((char)(volume_mensagem_voz/10 + 48));
			EscreveChar((char)(volume_mensagem_voz%10 + 48));
			break;
		}
		case TELA_ALARME_VISUAL:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_ALARME_VISUAL][idioma]),pos);
			break;
		}
		case TELA_SETA_ALARME_VISUAL_LIGAR_DESLIGAR:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_LIGAR_DESLIGAR][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_NAO_SIM][idioma]),pos);
			if(alarme_visual == NAO)
			{
				LINHA = 2;
				COLUNA = 2;
				PosicionaLCD(pos);
				EscreveChar('X');
				LINHA = 2;
				COLUNA = 15;
				PosicionaLCD(pos);
				EscreveChar(' ');
			}
			else if(alarme_visual == SIM)
			{
				LINHA = 2;
				COLUNA = 2;
				PosicionaLCD(pos);
				EscreveChar(' ');
				LINHA = 2;
				COLUNA = 15;
				PosicionaLCD(pos);
				EscreveChar('X');
			}
			break;
		}
		/******************************************************************************/

		/*** 5 - INFORMACOES DO SISTEMA ***/

		case TELA_INFORMACOES_DO_SISTEMA:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_INFORMACOES_DO_SISTEMA][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_INFORMACOES_DO_SISTEMA + 1][idioma]),pos);
			break;
		}
		case TELA_MOSTRA_INFORMACOES_DO_SISTEMA:
		{
			if(menu == 1)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_CONTADOR_DE_DETECCOES][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_CONTADOR_DE_DETECCOES + 1][idioma]),pos);
			}
			else if(menu == 2)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_CONTADOR_DE_PASSAGENS][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_CONTADOR_DE_PASSAGENS + 1][idioma]),pos);
			}
			else if(menu == 3)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_NUMERO_DE_SERIE][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_DETECTOR_METAIS][idioma]),pos);
			}
			else if(menu == 4)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_NUMERO_DE_SERIE][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_FONTE_ALIMENTACAO][idioma]),pos);
			}
			break;
		}
		case TELA_MOSTRA_CONTADOR_DE_DETECCOES:
		{
			if(menu1 == 1)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_TOTAL_BLOQUEIOS][idioma]),pos);
			}
			else if(menu1 == 2)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_TOTAL_DESBLOQUEIOS][idioma]),pos);
			}
			else if(menu1 == 3)
			{
				EscreveLCD((telas_LCD[TELA_ZERAR_CONTADORES][idioma]),pos);
			}
			break;
		}
		case TELA_TOTAL_BLOQUEIOS:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_TOTAL_BLOQUEIOS][idioma]),pos);
			LINHA = 2;
			if(contador_bloqueios < 10)
			{
				COLUNA = 8;
				PosicionaLCD(pos);
				EscreveChar((char)(contador_bloqueios + 48));
			}
			else if(contador_bloqueios < 100)
			{
				COLUNA = 8;
				PosicionaLCD(pos);
				EscreveChar((char)(contador_bloqueios/10 + 48));
				EscreveChar((char)(contador_bloqueios%10 + 48));
			}
			else if(contador_bloqueios < 1000)
			{
				COLUNA = 7;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_bloqueios/100) + 48));
				EscreveChar((char)((contador_bloqueios%100)/10 + 48));
				EscreveChar((char)((contador_bloqueios%10)+ 48));
			}
			else if(contador_bloqueios < 10000)
			{
				COLUNA = 7;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_bloqueios/1000) + 48));
				EscreveChar((char)(((contador_bloqueios%1000)/100) + 48));
				EscreveChar((char)(((contador_bloqueios%100)/10) + 48));
				EscreveChar((char)((contador_bloqueios%10) + 48));
			}
			else if(contador_bloqueios < 100000)
			{
				COLUNA = 6;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_bloqueios/10000) + 48));
				EscreveChar((char)(((contador_bloqueios%10000)/1000) + 48));
				EscreveChar((char)(((contador_bloqueios%1000)/100) + 48));
				EscreveChar((char)(((contador_bloqueios%100)/10) + 48));
				EscreveChar((char)((contador_bloqueios%10) + 48));
			}
			else if(contador_bloqueios < 1000000)
			{
				COLUNA = 6;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_bloqueios/100000) + 48));
				EscreveChar((char)(((contador_bloqueios%100000)/10000) + 48));
				EscreveChar((char)(((contador_bloqueios%10000)/1000) + 48));
				EscreveChar((char)(((contador_bloqueios%1000)/100) + 48));
				EscreveChar((char)(((contador_bloqueios%100)/10) + 48));
				EscreveChar((char)((contador_bloqueios%10) + 48));
			}
			else if(contador_bloqueios < 10000000)
			{
				COLUNA = 5;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_bloqueios/1000000) + 48));
				EscreveChar((char)(((contador_bloqueios%1000000)/100000) + 48));
				EscreveChar((char)(((contador_bloqueios%100000)/10000) + 48));
				EscreveChar((char)(((contador_bloqueios%10000)/1000) + 48));
				EscreveChar((char)(((contador_bloqueios%1000)/100) + 48));
				EscreveChar((char)(((contador_bloqueios%100)/10) + 48));
				EscreveChar((char)((contador_bloqueios%10) + 48));
			}
			else if(contador_bloqueios < 100000000)
			{
				COLUNA = 5;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_bloqueios/10000000) + 48));
				EscreveChar((char)(((contador_bloqueios%10000000)/1000000) + 48));
				EscreveChar((char)(((contador_bloqueios%1000000)/100000) + 48));
				EscreveChar((char)(((contador_bloqueios%100000)/10000) + 48));
				EscreveChar((char)(((contador_bloqueios%10000)/1000) + 48));
				EscreveChar((char)(((contador_bloqueios%1000)/100) + 48));
				EscreveChar((char)(((contador_bloqueios%100)/10) + 48));
				EscreveChar((char)((contador_bloqueios%10) + 48));
			}
			else if(contador_bloqueios < 1000000000)
			{
				COLUNA = 4;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_bloqueios/100000000) + 48));
				EscreveChar((char)(((contador_bloqueios%100000000)/10000000) + 48));
				EscreveChar((char)(((contador_bloqueios%10000000)/1000000) + 48));
				EscreveChar((char)(((contador_bloqueios%1000000)/100000) + 48));
				EscreveChar((char)(((contador_bloqueios%100000)/10000) + 48));
				EscreveChar((char)(((contador_bloqueios%10000)/1000) + 48));
				EscreveChar((char)(((contador_bloqueios%1000)/100) + 48));
				EscreveChar((char)(((contador_bloqueios%100)/10) + 48));
				EscreveChar((char)((contador_bloqueios%10) + 48));
			}
			else if(contador_bloqueios < 10000000000)
			{
				COLUNA = 4;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_bloqueios/1000000000) + 48));
				EscreveChar((char)(((contador_bloqueios%1000000000)/100000000) + 48));
				EscreveChar((char)(((contador_bloqueios%100000000)/10000000) + 48));
				EscreveChar((char)(((contador_bloqueios%10000000)/1000000) + 48));
				EscreveChar((char)(((contador_bloqueios%1000000)/100000) + 48));
				EscreveChar((char)(((contador_bloqueios%100000)/10000) + 48));
				EscreveChar((char)(((contador_bloqueios%10000)/1000) + 48));
				EscreveChar((char)(((contador_bloqueios%1000)/100) + 48));
				EscreveChar((char)(((contador_bloqueios%100)/10) + 48));
				EscreveChar((char)((contador_bloqueios%10) + 48));
			}
			break;
		}
		case TELA_TOTAL_DESBLOQUEIOS:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_TOTAL_DESBLOQUEIOS][idioma]),pos);
			LINHA = 2;
			if(contador_desbloqueios < 10)
			{
				COLUNA = 8;
				PosicionaLCD(pos);
				EscreveChar((char)(contador_desbloqueios + 48));
			}
			else if(contador_desbloqueios < 100)
			{
				COLUNA = 8;
				PosicionaLCD(pos);
				EscreveChar((char)(contador_desbloqueios/10 + 48));
				EscreveChar((char)(contador_desbloqueios%10 + 48));
			}
			else if(contador_desbloqueios < 1000)
			{
				COLUNA = 7;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_desbloqueios/100) + 48));
				EscreveChar((char)((contador_desbloqueios%100)/10 + 48));
				EscreveChar((char)((contador_desbloqueios%10)+ 48));
			}
			else if(contador_desbloqueios < 10000)
			{
				COLUNA = 7;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_desbloqueios/1000) + 48));
				EscreveChar((char)(((contador_desbloqueios%1000)/100) + 48));
				EscreveChar((char)(((contador_desbloqueios%100)/10) + 48));
				EscreveChar((char)((contador_desbloqueios%10) + 48));
			}
			else if(contador_desbloqueios < 100000)
			{
				COLUNA = 6;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_desbloqueios/10000) + 48));
				EscreveChar((char)(((contador_desbloqueios%10000)/1000) + 48));
				EscreveChar((char)(((contador_desbloqueios%1000)/100) + 48));
				EscreveChar((char)(((contador_desbloqueios%100)/10) + 48));
				EscreveChar((char)((contador_desbloqueios%10) + 48));
			}
			else if(contador_desbloqueios < 1000000)
			{
				COLUNA = 6;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_desbloqueios/100000) + 48));
				EscreveChar((char)(((contador_desbloqueios%100000)/10000) + 48));
				EscreveChar((char)(((contador_desbloqueios%10000)/1000) + 48));
				EscreveChar((char)(((contador_desbloqueios%1000)/100) + 48));
				EscreveChar((char)(((contador_desbloqueios%100)/10) + 48));
				EscreveChar((char)((contador_desbloqueios%10) + 48));
			}
			else if(contador_desbloqueios < 10000000)
			{
				COLUNA = 5;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_desbloqueios/1000000) + 48));
				EscreveChar((char)(((contador_desbloqueios%1000000)/100000) + 48));
				EscreveChar((char)(((contador_desbloqueios%100000)/10000) + 48));
				EscreveChar((char)(((contador_desbloqueios%10000)/1000) + 48));
				EscreveChar((char)(((contador_desbloqueios%1000)/100) + 48));
				EscreveChar((char)(((contador_desbloqueios%100)/10) + 48));
				EscreveChar((char)((contador_desbloqueios%10) + 48));
			}
			else if(contador_desbloqueios < 100000000)
			{
				COLUNA = 5;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_desbloqueios/10000000) + 48));
				EscreveChar((char)(((contador_desbloqueios%10000000)/1000000) + 48));
				EscreveChar((char)(((contador_desbloqueios%1000000)/100000) + 48));
				EscreveChar((char)(((contador_desbloqueios%100000)/10000) + 48));
				EscreveChar((char)(((contador_desbloqueios%10000)/1000) + 48));
				EscreveChar((char)(((contador_desbloqueios%1000)/100) + 48));
				EscreveChar((char)(((contador_desbloqueios%100)/10) + 48));
				EscreveChar((char)((contador_desbloqueios%10) + 48));
			}
			else if(contador_desbloqueios < 1000000000)
			{
				COLUNA = 4;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_desbloqueios/100000000) + 48));
				EscreveChar((char)(((contador_desbloqueios%100000000)/10000000) + 48));
				EscreveChar((char)(((contador_desbloqueios%10000000)/1000000) + 48));
				EscreveChar((char)(((contador_desbloqueios%1000000)/100000) + 48));
				EscreveChar((char)(((contador_desbloqueios%100000)/10000) + 48));
				EscreveChar((char)(((contador_desbloqueios%10000)/1000) + 48));
				EscreveChar((char)(((contador_desbloqueios%1000)/100) + 48));
				EscreveChar((char)(((contador_desbloqueios%100)/10) + 48));
				EscreveChar((char)((contador_desbloqueios%10) + 48));
			}
			else if(contador_desbloqueios < 10000000000)
			{
				COLUNA = 4;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_desbloqueios/1000000000) + 48));
				EscreveChar((char)(((contador_desbloqueios%1000000000)/100000000) + 48));
				EscreveChar((char)(((contador_desbloqueios%100000000)/10000000) + 48));
				EscreveChar((char)(((contador_desbloqueios%10000000)/1000000) + 48));
				EscreveChar((char)(((contador_desbloqueios%1000000)/100000) + 48));
				EscreveChar((char)(((contador_desbloqueios%100000)/10000) + 48));
				EscreveChar((char)(((contador_desbloqueios%10000)/1000) + 48));
				EscreveChar((char)(((contador_desbloqueios%1000)/100) + 48));
				EscreveChar((char)(((contador_desbloqueios%100)/10) + 48));
				EscreveChar((char)((contador_desbloqueios%10) + 48));
			}
			break;
		}
		case TELA_SETA_ZERAR_DETECCOES:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_ZERAR_CONTADORES][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_NAO_SIM][idioma]),pos);
			if(confirma == NAO)
			{
				LINHA = 2;
				COLUNA = 2;
				PosicionaLCD(pos);
				EscreveChar('X');
				LINHA = 2;
				COLUNA = 15;
				PosicionaLCD(pos);
				EscreveChar(' ');
			}
			else if(confirma == SIM)
			{
				LINHA = 2;
				COLUNA = 2;
				PosicionaLCD(pos);
				EscreveChar(' ');
				LINHA = 2;
				COLUNA = 15;
				PosicionaLCD(pos);
				EscreveChar('X');
			}
			break;
		}
		case TELA_MOSTRA_CONTADOR_DE_PASSAGENS:
		{
			if(menu1 == 1)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_ENTRADAS][idioma]),pos);
			}
			else if(menu1 == 2)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_SAIDAS][idioma]),pos);
			}
			else if(menu1 == 3)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_ENTRADAS_SAIDAS][idioma]),pos);
			}
			else if(menu1 == 4)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_ZERAR_CONTADORES][idioma]),pos);
			}
			break;
		}
		case TELA_ENTRADAS:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_ENTRADAS][idioma]),pos);
			LINHA = 2;
			if(contador_entra < 10)
			{
				COLUNA = 8;
				PosicionaLCD(pos);
				EscreveChar((char)(contador_entra + 48));
			}
			else if(contador_entra < 100)
			{
				COLUNA = 8;
				PosicionaLCD(pos);
				EscreveChar((char)(contador_entra/10 + 48));
				EscreveChar((char)(contador_entra%10 + 48));
			}
			else if(contador_entra < 1000)
			{
				COLUNA = 7;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_entra/100) + 48));
				EscreveChar((char)((contador_entra%100)/10 + 48));
				EscreveChar((char)((contador_entra%10)+ 48));
			}
			else if(contador_entra < 10000)
			{
				COLUNA = 7;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_entra/1000) + 48));
				EscreveChar((char)(((contador_entra%1000)/100) + 48));
				EscreveChar((char)(((contador_entra%100)/10) + 48));
				EscreveChar((char)((contador_entra%10) + 48));
			}
			else if(contador_entra < 100000)
			{
				COLUNA = 6;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_entra/10000) + 48));
				EscreveChar((char)(((contador_entra%10000)/1000) + 48));
				EscreveChar((char)(((contador_entra%1000)/100) + 48));
				EscreveChar((char)(((contador_entra%100)/10) + 48));
				EscreveChar((char)((contador_entra%10) + 48));
			}
			else if(contador_entra < 1000000)
			{
				COLUNA = 6;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_entra/100000) + 48));
				EscreveChar((char)(((contador_entra%100000)/10000) + 48));
				EscreveChar((char)(((contador_entra%10000)/1000) + 48));
				EscreveChar((char)(((contador_entra%1000)/100) + 48));
				EscreveChar((char)(((contador_entra%100)/10) + 48));
				EscreveChar((char)((contador_entra%10) + 48));
			}
			else if(contador_entra < 10000000)
			{
				COLUNA = 5;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_entra/1000000) + 48));
				EscreveChar((char)(((contador_entra%1000000)/100000) + 48));
				EscreveChar((char)(((contador_entra%100000)/10000) + 48));
				EscreveChar((char)(((contador_entra%10000)/1000) + 48));
				EscreveChar((char)(((contador_entra%1000)/100) + 48));
				EscreveChar((char)(((contador_entra%100)/10) + 48));
				EscreveChar((char)((contador_entra%10) + 48));
			}
			else if(contador_entra < 100000000)
			{
				COLUNA = 5;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_entra/10000000) + 48));
				EscreveChar((char)(((contador_entra%10000000)/1000000) + 48));
				EscreveChar((char)(((contador_entra%1000000)/100000) + 48));
				EscreveChar((char)(((contador_entra%100000)/10000) + 48));
				EscreveChar((char)(((contador_entra%10000)/1000) + 48));
				EscreveChar((char)(((contador_entra%1000)/100) + 48));
				EscreveChar((char)(((contador_entra%100)/10) + 48));
				EscreveChar((char)((contador_entra%10) + 48));
			}
			else if(contador_entra < 1000000000)
			{
				COLUNA = 4;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_entra/100000000) + 48));
				EscreveChar((char)(((contador_entra%100000000)/10000000) + 48));
				EscreveChar((char)(((contador_entra%10000000)/1000000) + 48));
				EscreveChar((char)(((contador_entra%1000000)/100000) + 48));
				EscreveChar((char)(((contador_entra%100000)/10000) + 48));
				EscreveChar((char)(((contador_entra%10000)/1000) + 48));
				EscreveChar((char)(((contador_entra%1000)/100) + 48));
				EscreveChar((char)(((contador_entra%100)/10) + 48));
				EscreveChar((char)((contador_entra%10) + 48));
			}
			else if(contador_entra < 10000000000)
			{
				COLUNA = 4;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_entra/1000000000) + 48));
				EscreveChar((char)(((contador_entra%1000000000)/100000000) + 48));
				EscreveChar((char)(((contador_entra%100000000)/10000000) + 48));
				EscreveChar((char)(((contador_entra%10000000)/1000000) + 48));
				EscreveChar((char)(((contador_entra%1000000)/100000) + 48));
				EscreveChar((char)(((contador_entra%100000)/10000) + 48));
				EscreveChar((char)(((contador_entra%10000)/1000) + 48));
				EscreveChar((char)(((contador_entra%1000)/100) + 48));
				EscreveChar((char)(((contador_entra%100)/10) + 48));
				EscreveChar((char)((contador_entra%10) + 48));
			}
			break;
		}
		case TELA_SAIDAS:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_SAIDAS][idioma]),pos);
			LINHA = 2;
			if(contador_sai < 10)
			{
				COLUNA = 8;
				PosicionaLCD(pos);
				EscreveChar((char)(contador_sai + 48));
			}
			else if(contador_sai < 100)
			{
				COLUNA = 8;
				PosicionaLCD(pos);
				EscreveChar((char)(contador_sai/10 + 48));
				EscreveChar((char)(contador_sai%10 + 48));
			}
			else if(contador_sai < 1000)
			{
				COLUNA = 7;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_sai/100) + 48));
				EscreveChar((char)((contador_sai%100)/10 + 48));
				EscreveChar((char)((contador_sai%10)+ 48));
			}
			else if(contador_sai < 10000)
			{
				COLUNA = 7;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_sai/1000) + 48));
				EscreveChar((char)(((contador_sai%1000)/100) + 48));
				EscreveChar((char)(((contador_sai%100)/10) + 48));
				EscreveChar((char)((contador_sai%10) + 48));
			}
			else if(contador_sai < 100000)
			{
				COLUNA = 6;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_sai/10000) + 48));
				EscreveChar((char)(((contador_sai%10000)/1000) + 48));
				EscreveChar((char)(((contador_sai%1000)/100) + 48));
				EscreveChar((char)(((contador_sai%100)/10) + 48));
				EscreveChar((char)((contador_sai%10) + 48));
			}
			else if(contador_sai < 1000000)
			{
				COLUNA = 6;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_sai/100000) + 48));
				EscreveChar((char)(((contador_sai%100000)/10000) + 48));
				EscreveChar((char)(((contador_sai%10000)/1000) + 48));
				EscreveChar((char)(((contador_sai%1000)/100) + 48));
				EscreveChar((char)(((contador_sai%100)/10) + 48));
				EscreveChar((char)((contador_sai%10) + 48));
			}
			else if(contador_sai < 10000000)
			{
				COLUNA = 5;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_sai/1000000) + 48));
				EscreveChar((char)(((contador_sai%1000000)/100000) + 48));
				EscreveChar((char)(((contador_sai%100000)/10000) + 48));
				EscreveChar((char)(((contador_sai%10000)/1000) + 48));
				EscreveChar((char)(((contador_sai%1000)/100) + 48));
				EscreveChar((char)(((contador_sai%100)/10) + 48));
				EscreveChar((char)((contador_sai%10) + 48));
			}
			else if(contador_sai < 100000000)
			{
				COLUNA = 5;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_sai/10000000) + 48));
				EscreveChar((char)(((contador_sai%10000000)/1000000) + 48));
				EscreveChar((char)(((contador_sai%1000000)/100000) + 48));
				EscreveChar((char)(((contador_sai%100000)/10000) + 48));
				EscreveChar((char)(((contador_sai%10000)/1000) + 48));
				EscreveChar((char)(((contador_sai%1000)/100) + 48));
				EscreveChar((char)(((contador_sai%100)/10) + 48));
				EscreveChar((char)((contador_sai%10) + 48));
			}
			else if(contador_sai < 1000000000)
			{
				COLUNA = 4;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_sai/100000000) + 48));
				EscreveChar((char)(((contador_sai%100000000)/10000000) + 48));
				EscreveChar((char)(((contador_sai%10000000)/1000000) + 48));
				EscreveChar((char)(((contador_sai%1000000)/100000) + 48));
				EscreveChar((char)(((contador_sai%100000)/10000) + 48));
				EscreveChar((char)(((contador_sai%10000)/1000) + 48));
				EscreveChar((char)(((contador_sai%1000)/100) + 48));
				EscreveChar((char)(((contador_sai%100)/10) + 48));
				EscreveChar((char)((contador_sai%10) + 48));
			}
			else if(contador_sai < 10000000000)
			{
				COLUNA = 4;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_sai/1000000000) + 48));
				EscreveChar((char)(((contador_sai%1000000000)/100000000) + 48));
				EscreveChar((char)(((contador_sai%100000000)/10000000) + 48));
				EscreveChar((char)(((contador_sai%10000000)/1000000) + 48));
				EscreveChar((char)(((contador_sai%1000000)/100000) + 48));
				EscreveChar((char)(((contador_sai%100000)/10000) + 48));
				EscreveChar((char)(((contador_sai%10000)/1000) + 48));
				EscreveChar((char)(((contador_sai%1000)/100) + 48));
				EscreveChar((char)(((contador_sai%100)/10) + 48));
				EscreveChar((char)((contador_sai%10) + 48));
			}
			break;
		}
		case TELA_ENTRADAS_SAIDAS:
		{
			contador_passagens = contador_entra - contador_sai;
			if(contador_sai > contador_entra){
				contador_passagens = 0;
			}
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_ENTRADAS_SAIDAS][idioma]),pos);
			LINHA = 2;
			if(contador_passagens < 10)
			{
				COLUNA = 8;
				PosicionaLCD(pos);
				EscreveChar((char)(contador_passagens + 48));
			}
			else if(contador_passagens < 100)
			{
				COLUNA = 8;
				PosicionaLCD(pos);
				EscreveChar((char)(contador_passagens/10 + 48));
				EscreveChar((char)(contador_passagens%10 + 48));
			}
			else if(contador_passagens < 1000)
			{
				COLUNA = 7;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_passagens/100) + 48));
				EscreveChar((char)((contador_passagens%100)/10 + 48));
				EscreveChar((char)((contador_passagens%10)+ 48));
			}
			else if(contador_passagens < 10000)
			{
				COLUNA = 7;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_passagens/1000) + 48));
				EscreveChar((char)(((contador_passagens%1000)/100) + 48));
				EscreveChar((char)(((contador_passagens%100)/10) + 48));
				EscreveChar((char)((contador_passagens%10) + 48));
			}
			else if(contador_passagens < 100000)
			{
				COLUNA = 6;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_passagens/10000) + 48));
				EscreveChar((char)(((contador_passagens%10000)/1000) + 48));
				EscreveChar((char)(((contador_passagens%1000)/100) + 48));
				EscreveChar((char)(((contador_passagens%100)/10) + 48));
				EscreveChar((char)((contador_passagens%10) + 48));
			}
			else if(contador_passagens < 1000000)
			{
				COLUNA = 6;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_passagens/100000) + 48));
				EscreveChar((char)(((contador_passagens%100000)/10000) + 48));
				EscreveChar((char)(((contador_passagens%10000)/1000) + 48));
				EscreveChar((char)(((contador_passagens%1000)/100) + 48));
				EscreveChar((char)(((contador_passagens%100)/10) + 48));
				EscreveChar((char)((contador_passagens%10) + 48));
			}
			else if(contador_passagens < 10000000)
			{
				COLUNA = 5;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_passagens/1000000) + 48));
				EscreveChar((char)(((contador_passagens%1000000)/100000) + 48));
				EscreveChar((char)(((contador_passagens%100000)/10000) + 48));
				EscreveChar((char)(((contador_passagens%10000)/1000) + 48));
				EscreveChar((char)(((contador_passagens%1000)/100) + 48));
				EscreveChar((char)(((contador_passagens%100)/10) + 48));
				EscreveChar((char)((contador_passagens%10) + 48));
			}
			else if(contador_passagens < 100000000)
			{
				COLUNA = 5;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_passagens/10000000) + 48));
				EscreveChar((char)(((contador_passagens%10000000)/1000000) + 48));
				EscreveChar((char)(((contador_passagens%1000000)/100000) + 48));
				EscreveChar((char)(((contador_passagens%100000)/10000) + 48));
				EscreveChar((char)(((contador_passagens%10000)/1000) + 48));
				EscreveChar((char)(((contador_passagens%1000)/100) + 48));
				EscreveChar((char)(((contador_passagens%100)/10) + 48));
				EscreveChar((char)((contador_passagens%10) + 48));
			}
			else if(contador_passagens < 1000000000)
			{
				COLUNA = 4;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_passagens/100000000) + 48));
				EscreveChar((char)(((contador_passagens%100000000)/10000000) + 48));
				EscreveChar((char)(((contador_passagens%10000000)/1000000) + 48));
				EscreveChar((char)(((contador_passagens%1000000)/100000) + 48));
				EscreveChar((char)(((contador_passagens%100000)/10000) + 48));
				EscreveChar((char)(((contador_passagens%10000)/1000) + 48));
				EscreveChar((char)(((contador_passagens%1000)/100) + 48));
				EscreveChar((char)(((contador_passagens%100)/10) + 48));
				EscreveChar((char)((contador_passagens%10) + 48));
			}
			else if(contador_passagens < 10000000000)
			{
				COLUNA = 4;
				PosicionaLCD(pos);
				EscreveChar((char)((contador_passagens/1000000000) + 48));
				EscreveChar((char)(((contador_passagens%1000000000)/100000000) + 48));
				EscreveChar((char)(((contador_passagens%100000000)/10000000) + 48));
				EscreveChar((char)(((contador_passagens%10000000)/1000000) + 48));
				EscreveChar((char)(((contador_passagens%1000000)/100000) + 48));
				EscreveChar((char)(((contador_passagens%100000)/10000) + 48));
				EscreveChar((char)(((contador_passagens%10000)/1000) + 48));
				EscreveChar((char)(((contador_passagens%1000)/100) + 48));
				EscreveChar((char)(((contador_passagens%100)/10) + 48));
				EscreveChar((char)((contador_passagens%10) + 48));
			}
			break;
		}
		case TELA_SETA_ZERAR_PASSAGENS:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_ZERAR_CONTADORES][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_NAO_SIM][idioma]),pos);
			if(confirma == NAO)
			{
				LINHA = 2;
				COLUNA = 2;
				PosicionaLCD(pos);
				EscreveChar('X');
				LINHA = 2;
				COLUNA = 15;
				PosicionaLCD(pos);
				EscreveChar(' ');
			}
			else if(confirma == SIM)
			{
				LINHA = 2;
				COLUNA = 2;
				PosicionaLCD(pos);
				EscreveChar(' ');
				LINHA = 2;
				COLUNA = 15;
				PosicionaLCD(pos);
				EscreveChar('X');
			}
			break;
		}
		case TELA_MOSTRA_NUMERO_DE_SERIE_PAINEL:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_NUMERO_DE_SERIE][idioma]),pos);
			LINHA = 2;
			COLUNA = 5;
			PosicionaLCD(pos);
			EscreveChar(Num_Serie_Write[2]);
			EscreveChar(Num_Serie_Write[3]);
			EscreveChar(Num_Serie_Write[4]);
			EscreveChar(Num_Serie_Write[5]);
			EscreveChar(Num_Serie_Write[6]);
			EscreveChar(Num_Serie_Write[7]);
			if(flag_numero_serie == TRUE)
			{
				delay_ms(2000);
				tela = TELA_INICIAL;
				estado_LCD = ATUALIZA_LCD;
				flag_numero_serie = FALSE;
			}
			break;
		}
		case TELA_MOSTRA_NUMERO_DE_SERIE_FONTE:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_NUMERO_DE_SERIE][idioma]),pos);
			LINHA = 2;
			COLUNA = 5;
			PosicionaLCD(pos);
			EscreveChar(StcPlacas[CONST_PLACA_FONTE].Serial_Number_CAN[0]);
			EscreveChar(StcPlacas[CONST_PLACA_FONTE].Serial_Number_CAN[1]);
			EscreveChar(StcPlacas[CONST_PLACA_FONTE].Serial_Number_CAN[2]);
			EscreveChar(StcPlacas[CONST_PLACA_FONTE].Serial_Number_CAN[3]);
			EscreveChar(StcPlacas[CONST_PLACA_FONTE].Serial_Number_CAN[4]);
			EscreveChar(StcPlacas[CONST_PLACA_FONTE].Serial_Number_CAN[5]);
			break;
		}
		/******************************************************************************/

		/*** 6 - INFORMAÇÕES DE ENERGIA ***/

		case TELA_INFORMACOES_DE_ENERGIA:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_INFORMACOES_DE_ENERGIA][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_INFORMACOES_DE_ENERGIA + 1][idioma]),pos);
			break;
		}
		case TELA_TENSAO_AC:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_TENSAO_AC][idioma]),pos);
			break;
		}
		case TELA_TENSAO_DC:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_TENSAO_DC][idioma]),pos);
			break;
		}
		case TELA_TENSAO_DAS_BATERIAS:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_TENSAO_DAS_BATERIAS][idioma]),pos);
			break;
		}
		case TELA_TENSAO_24V:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_TENSAO_24V][idioma]),pos);
			break;
		}
		case TELA_MOSTRA_INFORMACOES_DE_ENERGIA:
		{
			if(menu == 1)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_TENSAO_AC][idioma]),pos);
			}
			else if(menu == 2)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_TENSAO_DC][idioma]),pos);
			}
			else if(menu == 3)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_TENSAO_DAS_BATERIAS][idioma]),pos);
			}
			break;
		}
		/******************************************************************************/

		/*** 8 - DIAGNÓSTICO DO SISTEMA ***/

		case TELA_DIAGNOSTICO_DO_SISTEMA:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_DIAGNOSTICO_DO_SISTEMA][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_DIAGNOSTICO_DO_SISTEMA + 1][idioma]),pos);
			break;
		}
		case TELA_MOSTRA_DIAGNOSTICO_SISTEMA:
		{
			if(menu1 == TESTE_LEDS)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_TESTE_DE_LEDS][idioma]),pos);
			}
			else if(menu1 == TESTE_TRAVA)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_TESTE_DA_TRAVA][idioma]),pos);
			}
			else if(menu1 == TESTE_RELE)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_TESTE_RELE][idioma]),pos);
			}
			else if(menu1 == TESTE_BUZZER)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_TESTE_BUZZER][idioma]),pos);
			}
			else if(menu1 == TESTE_MSG_VOZ)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_TESTE_MSG_VOZ][idioma]),pos);
			}
			//TODO remove below
			else if(menu1 == TESTE_MSG_VOZ1)
						{
							LINHA = 1;
							COLUNA = 1;
							EscreveLCD((telas_LCD[TELA_TESTE_MSG_VOZ1][idioma]),pos);
						}
			else if(menu1 == TESTE_MSG_VOZ2)
						{
							LINHA = 1;
							COLUNA = 1;
							EscreveLCD((telas_LCD[TELA_TESTE_MSG_VOZ2][idioma]),pos);
						}
			else if(menu1 == TESTE_MSG_VOZ3)
						{
							LINHA = 1;
							COLUNA = 1;
							EscreveLCD((telas_LCD[TELA_TESTE_MSG_VOZ3][idioma]),pos);
						}
			//TODO till here
			else if(menu1 == TESTE_TECLADO)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_TECLADO][idioma]),pos);
			}
			else if(menu1 == TESTE_INFRAVERMELHO)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_TESTE_INFRAVERMELHO][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_TESTE_INFRAVERMELHO + 1][idioma]),pos);
			}
			else if(menu1 == TESTE_AUTONOMIA_BATERIA)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_TESTE_AUTONOMIA_DA_BATERIA][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_TESTE_AUTONOMIA_DA_BATERIA + 1][idioma]),pos);
			}
			else if(menu1 == TESTE_SINAL_RX_A1_A2)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_TENSAO_SINAL_RX][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_AREA_1_E_2][idioma]),pos);
			}
			else if(menu1 == TESTE_SINAL_RX_A2_A3 && tipo_detector == Z3)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_TENSAO_SINAL_RX][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_AREA_2_E_3][idioma]),pos);
			}
			else if(menu1 == TESTE_SINAL_RX_A3_A4 && tipo_detector == Z8)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_TENSAO_SINAL_RX][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_AREA_3_E_4][idioma]),pos);
			}
			else if(menu1 == TESTE_SINAL_RX_A5_A6 && tipo_detector == Z8)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_TENSAO_SINAL_RX][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_AREA_5_E_6][idioma]),pos);
			}
			else if(menu1 == TESTE_SINAL_RX_A7_A8 && tipo_detector == Z8)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_TENSAO_SINAL_RX][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_AREA_7_E_8][idioma]),pos);
			}
			break;
		}
		case TELA_BARGRAPH:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_BARGRAPH][idioma]),pos);
			break;
		}
		case TELA_MOSTRA_BARGRAPH:
		{
			if(selecionaArea == 1)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_BARGRAPH][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_AREA1E2][idioma]),pos);
				break;
			}
			else if(selecionaArea == 2)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_BARGRAPH][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				if(tipo_detector == Z3)
				{
					EscreveLCD((telas_LCD[TELA_AREA2E3][idioma]),pos);
				}
				else if(tipo_detector == Z8)
				{
					EscreveLCD((telas_LCD[TELA_AREA3E4][idioma]),pos);
				}
				break;
			}
			else if(selecionaArea == 3)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_BARGRAPH][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_AREA5E6][idioma]),pos);
				break;
			}
			else if(selecionaArea == 4)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_BARGRAPH][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_AREA7E8][idioma]),pos);
				break;
			}
		}
		case TELA_COMPATIBILIDADE_ELETROMAGNETICA:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_COMPATIBILIDADE_ELETROMAGNETICA][idioma]),pos);
			break;
		}
		case TELA_MOSTRA_COMPATIBILIDADE:
		{
			if(selecionaArea == 1)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_COMPATIBILIDADE_ELETROMAGNETICA_RX_A1_A2][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_COMPATIBILIDADE_ELETROMAGNETICA_RX_A1_A2 + 1][idioma]),pos);
				break;
			}
			else if(selecionaArea == 2)
			{
				if(tipo_detector == Z3) //Se tipo_detector for igual a Z3 então
				{
					LINHA = 1;
					COLUNA = 1;
					EscreveLCD((telas_LCD[TELA_COMPATIBILIDADE_ELETROMAGNETICA_RX_A2_A3][idioma]),pos);
					LINHA = 2;
					COLUNA = 1;
					EscreveLCD((telas_LCD[TELA_COMPATIBILIDADE_ELETROMAGNETICA_RX_A2_A3 + 1][idioma]),pos);
				}
				else if(tipo_detector == Z8) //Senão se tipo_detector for igual a Z8 então
				{
					LINHA = 1;
					COLUNA = 1;
					EscreveLCD((telas_LCD[TELA_COMPATIBILIDADE_ELETROMAGNETICA_RX_A3_A4][idioma]),pos);
					LINHA = 2;
					COLUNA = 1;
					EscreveLCD((telas_LCD[TELA_COMPATIBILIDADE_ELETROMAGNETICA_RX_A3_A4 + 1][idioma]),pos);
				}
				break;
			}
			else if(selecionaArea == 3)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_COMPATIBILIDADE_ELETROMAGNETICA_RX_A5_A6][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_COMPATIBILIDADE_ELETROMAGNETICA_RX_A5_A6 + 1][idioma]),pos);
				break;
			}
			else if(selecionaArea == 4)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_COMPATIBILIDADE_ELETROMAGNETICA_RX_A7_A8][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_COMPATIBILIDADE_ELETROMAGNETICA_RX_A7_A8 + 1][idioma]),pos);
				break;
			}
		}
		case TELA_SINAL_A1_A2:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_SINAL_A1_A2][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_SINAL_A1_A2 + 1][idioma]),pos);
			break;
		}
		case TELA_SINAL_A2_A3:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_SINAL_A2_A3][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_SINAL_A2_A3 + 1][idioma]),pos);
			break;
		}
		case TELA_SINAL_A3_A4:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_SINAL_A3_A4][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_SINAL_A3_A4 + 1][idioma]),pos);
			break;
		}
		case TELA_SINAL_A5_A6:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_SINAL_A5_A6][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_SINAL_A5_A6 + 1][idioma]),pos);
			break;
		}
		case TELA_SINAL_A7_A8:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_SINAL_A7_A8][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_SINAL_A7_A8 + 1][idioma]),pos);
			break;
		}
		case TELA_A1_A2:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_A1_A2][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_A1_A2 + 1][idioma]),pos);
			break;
		}
		case TELA_A2_A3:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_A2_A3][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_A2_A3 + 1][idioma]),pos);
			break;
		}
		case TELA_A3_A4:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_A3_A4][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_A3_A4 + 1][idioma]),pos);
			break;
		}
		case TELA_A5_A6:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_A5_A6][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_A5_A6 + 1][idioma]),pos);
			break;
		}
		case TELA_A7_A8:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_A7_A8][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_A7_A8 + 1][idioma]),pos);
			break;
		}
		case TELA_A1_A2_COMPATIBILIDADE:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_A1_A2][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_A1_A2 + 1][idioma]),pos);
			break;
		}
		case TELA_A2_A3_COMPATIBILIDADE:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_A2_A3][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_A2_A3 + 1][idioma]),pos);
			break;
		}
		case TELA_A3_A4_COMPATIBILIDADE:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_A3_A4][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_A3_A4 + 1][idioma]),pos);
			break;
		}
		case TELA_A5_A6_COMPATIBILIDADE:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_A5_A6][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_A5_A6 + 1][idioma]),pos);
			break;
		}
		case TELA_A7_A8_COMPATIBILIDADE:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_A7_A8][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_A7_A8 + 1][idioma]),pos);
			break;
		}
		case TELA_INFRA1_OFF_E_INFRA2_OFF:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_INFRA1_OFF_E_INFRA2_OFF][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_INFRA1_OFF_E_INFRA2_OFF + 1][idioma]),pos);
			break;
		}
		case TELA_INFRA1_ON_E_INFRA2_ON:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_INFRA1_ON_E_INFRA2_ON][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_INFRA1_ON_E_INFRA2_ON + 1][idioma]),pos);
			break;
		}
		/******************************************************************************/

		/*** 8 - AJUSTES TX-RX ***/

		case TELA_AJUSTES_TX_RX:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_AJUSTES_TX_RX][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_AJUSTES_TX_RX + 1][idioma]),pos);
			break;
		}
		case TELA_MOSTRA_AJUSTES_TX_RX:
		{
			if(menu == 1)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_CICLO_DE_TRABALHO][idioma]),pos);
				break;
			}
			else if(menu == 2)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_DEFASAGEM][idioma]),pos);
				break;
			}
			else if(menu == 3)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_FREQUENCIA][idioma]),pos);
				break;
			}
			break;
		}
		case TELA_DIGITE_CICLO_DE_TRABALHO:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_CICLO_DE_TRABALHO][idioma]),pos);
			LINHA = 2;
			COLUNA = 8;
			PosicionaLCD(pos);
			EscreveChar((char)(ciclo_de_trabalho/10 + 48));
			EscreveChar((char)(ciclo_de_trabalho%10 + 48));
			break;
		}
		case TELA_DIGITE_DEFASAGEM:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_DEFASAGEM][idioma]),pos);
			LINHA = 2;
			COLUNA = 7;
			PosicionaLCD(pos);
			EscreveChar((char)(defasagem/100 + 48));
			EscreveChar((char)(((defasagem%100)/10) + 48));
			EscreveChar((char)(defasagem%10 + 48));
			break;
		}
		case TELA_DIGITE_FREQUENCIA:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_FREQUENCIA][idioma]),pos);
			LINHA = 2;
			if(frequencia < 10000)
			{
				COLUNA = 7;
				PosicionaLCD(pos);
				EscreveChar((char)(frequencia/1000 + 48));
				EscreveChar((char)(((frequencia%1000)/100) + 48));
				EscreveChar((char)(((frequencia%100)/10) + 48));
				EscreveChar((char)(frequencia%10 + 48));
			}
			else
			{
				COLUNA = 6;
				PosicionaLCD(pos);
				EscreveChar((char)(frequencia/10000 + 48));
				EscreveChar((char)(((frequencia%10000)/1000) + 48));
				EscreveChar((char)(((frequencia%1000)/100) + 48));
				EscreveChar((char)(((frequencia%100)/10) + 48));
				EscreveChar((char)(frequencia%10 + 48));
			}
			break;
		}
		/******************************************************************************/

		/*** 9 - MODELO DE ANTENA ***/
		case TELA_MODELO_DE_ANTENA:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_MODELO_DE_ANTENA][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_MODELO_DE_ANTENA + 1][idioma]),pos);
			break;
		}
		case TELA_MOSTRA_MODELO_DE_ANTENA:
		{
			if(modelo_antena == PLANA_ONIX_2000)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_MODELO_DE_ANTENA][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_PLANA_ONIX_2000][idioma]),pos);
			}
			else if(modelo_antena == PLANA_ONIX_2100)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_MODELO_DE_ANTENA][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_PLANA_ONIX_2100][idioma]),pos);
			}
			else if(modelo_antena == PLANA_ONIX_440)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_MODELO_DE_ANTENA][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_PLANA_ONIX_440][idioma]),pos);
			}
			else if(modelo_antena == IECO_GT)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_MODELO_DE_ANTENA][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_IECO_GT][idioma]),pos);
			}
			else if(modelo_antena == CIL_IECO_2000)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_MODELO_DE_ANTENA][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_CILINDRICA_IECO_2000][idioma]),pos);
			}
			else if(modelo_antena == CIL_IECO_2100)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_MODELO_DE_ANTENA][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_CILINDRICA_IECO_2100][idioma]),pos);
			}
			else if(modelo_antena == PORTAL_750_BLINDADO)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_MODELO_DE_ANTENA][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_PORTAL_750_BLINDADO][idioma]),pos);
			}
			break;
		}
		/******************************************************************************/

		/*** 10 - POTENCIOMETRO DE GANHO ***/
		case TELA_POTENCIOMETRO_DE_GANHO:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_POTENCIOMETRO_DE_GANHO][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_POTENCIOMETRO_DE_GANHO + 1][idioma]),pos);
			break;
		}
		case TELA_MOSTRA_POTENCIOMETRO_DE_GANHO:
		{
			LINHA = 1;
			COLUNA = 1;
			if(selecionaArea == TODAS_AREAS)
			{
				EscreveLCD((telas_LCD[TELA_TODAS_AS_AREAS][idioma]),pos);
			}
			else if(selecionaArea == AREA_1)
			{
				EscreveLCD((telas_LCD[TELA_AREA_1][idioma]),pos);
			}
			else if(selecionaArea == AREA_2)
			{
				EscreveLCD((telas_LCD[TELA_AREA_2][idioma]),pos);
			}
			else if(selecionaArea == AREA_3)
			{
				EscreveLCD((telas_LCD[TELA_AREA_3][idioma]),pos);
			}
			else if(selecionaArea == AREA_4)
			{
				EscreveLCD((telas_LCD[TELA_AREA_4][idioma]),pos);
			}
			else if(selecionaArea == AREA_5)
			{
				EscreveLCD((telas_LCD[TELA_AREA_5][idioma]),pos);
			}
			else if(selecionaArea == AREA_6)
			{
				EscreveLCD((telas_LCD[TELA_AREA_6][idioma]),pos);
			}
			else if(selecionaArea == AREA_7)
			{
				EscreveLCD((telas_LCD[TELA_AREA_7][idioma]),pos);
			}
			else if(selecionaArea == AREA_8)
			{
				EscreveLCD((telas_LCD[TELA_AREA_8][idioma]),pos);
			}
			break;
		}
		case TELA_DIGITE_POTENCIOMETRO_DE_GANHO:
		{
			LINHA = 1;
			COLUNA = 1;
			if(selecionaArea == TODAS_AREAS)
			{
				EscreveLCD((telas_LCD[TELA_TODAS_AS_AREAS][idioma]),pos);
			}
			else if(selecionaArea == AREA_1)
			{
				EscreveLCD((telas_LCD[TELA_AREA_1][idioma]),pos);
			}
			else if(selecionaArea == AREA_2)
			{
				EscreveLCD((telas_LCD[TELA_AREA_2][idioma]),pos);
			}
			else if(selecionaArea == AREA_3)
			{
				EscreveLCD((telas_LCD[TELA_AREA_3][idioma]),pos);
			}
			else if(selecionaArea == AREA_4)
			{
				EscreveLCD((telas_LCD[TELA_AREA_4][idioma]),pos);
			}
			else if(selecionaArea == AREA_5)
			{
				EscreveLCD((telas_LCD[TELA_AREA_5][idioma]),pos);
			}
			else if(selecionaArea == AREA_6)
			{
				EscreveLCD((telas_LCD[TELA_AREA_6][idioma]),pos);
			}
			else if(selecionaArea == AREA_7)
			{
				EscreveLCD((telas_LCD[TELA_AREA_7][idioma]),pos);
			}
			else if(selecionaArea == AREA_8)
			{
				EscreveLCD((telas_LCD[TELA_AREA_8][idioma]),pos);
			}
			LINHA = 2;
			COLUNA = 7;
			PosicionaLCD(pos);
			EscreveChar((char)((buffer_ganho[selecionaArea]%1000)/100+48));
			EscreveChar((char)((buffer_ganho[selecionaArea]%100)/10+48));
			EscreveChar((char)(buffer_ganho[selecionaArea]%10+48));
			break;
		}
		case TELA_POTENCIOMETRO_DE_SELECAO_DE_METAIS:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_POTENCIOMETRO_DE_SELECAO_DE_METAIS][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_POTENCIOMETRO_DE_SELECAO_DE_METAIS + 1][idioma]),pos);
			break;
		}
		case TELA_MOSTRA_POTENCIOMETRO_DE_SELECAO_DE_METAIS:
		{
			LINHA = 1;
			COLUNA = 1;
			if(selecionaArea == TODAS_AREAS)
			{
				EscreveLCD((telas_LCD[TELA_TODAS_AS_AREAS][idioma]),pos);
			}
			else if(selecionaArea == AREA_1)
			{
				EscreveLCD((telas_LCD[TELA_AREA_1][idioma]),pos);
			}
			else if(selecionaArea == AREA_2)
			{
				EscreveLCD((telas_LCD[TELA_AREA_2][idioma]),pos);
			}
			else if(selecionaArea == AREA_3)
			{
				EscreveLCD((telas_LCD[TELA_AREA_3][idioma]),pos);
			}
			else if(selecionaArea == AREA_4)
			{
				EscreveLCD((telas_LCD[TELA_AREA_4][idioma]),pos);
			}
			else if(selecionaArea == AREA_5)
			{
				EscreveLCD((telas_LCD[TELA_AREA_5][idioma]),pos);
			}
			else if(selecionaArea == AREA_6)
			{
				EscreveLCD((telas_LCD[TELA_AREA_6][idioma]),pos);
			}
			else if(selecionaArea == AREA_7)
			{
				EscreveLCD((telas_LCD[TELA_AREA_7][idioma]),pos);
			}
			else if(selecionaArea == AREA_8)
			{
				EscreveLCD((telas_LCD[TELA_AREA_8][idioma]),pos);
			}
			break;
		}
		case TELA_DIGITE_POTENCIOMETRO_DE_SELECAO_DE_METAIS:
		{
			LINHA = 1;
			COLUNA = 1;
			if(selecionaArea == TODAS_AREAS)
			{
				EscreveLCD((telas_LCD[TELA_TODAS_AS_AREAS][idioma]),pos);
			}
			else if(selecionaArea == AREA_1)
			{
				EscreveLCD((telas_LCD[TELA_AREA_1][idioma]),pos);
			}
			else if(selecionaArea == AREA_2)
			{
				EscreveLCD((telas_LCD[TELA_AREA_2][idioma]),pos);
			}
			else if(selecionaArea == AREA_3)
			{
				EscreveLCD((telas_LCD[TELA_AREA_3][idioma]),pos);
			}
			else if(selecionaArea == AREA_4)
			{
				EscreveLCD((telas_LCD[TELA_AREA_4][idioma]),pos);
			}
			else if(selecionaArea == AREA_5)
			{
				EscreveLCD((telas_LCD[TELA_AREA_5][idioma]),pos);
			}
			else if(selecionaArea == AREA_6)
			{
				EscreveLCD((telas_LCD[TELA_AREA_6][idioma]),pos);
			}
			else if(selecionaArea == AREA_7)
			{
				EscreveLCD((telas_LCD[TELA_AREA_7][idioma]),pos);
			}
			else if(selecionaArea == AREA_8)
			{
				EscreveLCD((telas_LCD[TELA_AREA_8][idioma]),pos);
			}
			LINHA = 2;
			COLUNA = 7;
			PosicionaLCD(pos);
			EscreveChar((char)((buffer_selecao[selecionaArea]%1000)/100+48));
			EscreveChar((char)((buffer_selecao[selecionaArea]%100)/10+48));
			EscreveChar((char)(buffer_selecao[selecionaArea]%10+48));
			break;
		}

		case TELA_MOSTRA_TIPO_DETECTOR:
		{

			if(tipo_detector == Z3)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_TIPO_DETECTOR][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_3_AREAS][idioma]),pos);
			}
			else if(tipo_detector == Z8)
			{
				LINHA = 1;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_TIPO_DETECTOR][idioma]),pos);
				LINHA = 2;
				COLUNA = 1;
				EscreveLCD((telas_LCD[TELA_8_AREAS][idioma]),pos);
			}
			break;
		}
		/******************************************************************************/

		/*** TELAS DE USO GERAL ***/

		case TELA_SEM_SINAL_NAS_ANTENAS:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_SEM_SINAL_NAS_ANTENAS][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_SEM_SINAL_NAS_ANTENAS + 1][idioma]),pos);
			TocaTomBuzzer();
			break;
		}
		case TELA_ERRO_DE_COMUNICACAO:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_ERRO_DE_COMUNICACAO][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_ERRO_DE_COMUNICACAO + 1][idioma]),pos);
			break;
		}
		case TELA_CARGA_DA_BATERIA:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_CARGA_DA_BATERIA][idioma]),pos);
			LINHA = 2;
			COLUNA = 7;
			PosicionaLCD(pos);
			if( ((percentual_bat%1000)/100) == 0 )
			{
				EscreveChar(' ');
			}
			else
			{
				EscreveChar((char)((percentual_bat%1000)/100+48));
			}
			EscreveChar((char)((percentual_bat%100)/10+48));
			EscreveChar((char)(percentual_bat%10+48));
			EscreveChar('%');
			break;
		}
		case TELA_CARREGANDO:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_CARREGANDO][idioma]),pos);
			pos[0] = 2;
			pos[1] = 7;
			PosicionaLCD(pos);
			if( ((percentual_bat%1000)/100) == 0 )
			{
				EscreveChar(' ');
			}
			else
			{
				EscreveChar((char)((percentual_bat%1000)/100+48));
			}
			EscreveChar((char)((percentual_bat%100)/10+48));
			EscreveChar((char)(percentual_bat%10+48));
			EscreveChar('%');
			break;
		}
		case TELA_MEMORIA_FLASH_COM_DEFEITO:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_MEMORIA_FLASH_COM_DEFEITO][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD(telas_LCD[TELA_MEMORIA_FLASH_COM_DEFEITO + 1][idioma],pos);
			break;
		}
		case TELA_GRAVANDO_PADROES_DE_FABRICA:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_GRAVANDO_PADROES_DE_FABRICA][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD(telas_LCD[TELA_GRAVANDO_PADROES_DE_FABRICA + 1][idioma],pos);
			break;
		}
		case TELA_LENDO_PADROES_GRAVADOS:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_LENDO_PADROES_GRAVADOS][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD(telas_LCD[TELA_LENDO_PADROES_GRAVADOS + 1][idioma],pos);
			break;
		}
		case TELA_DESLIGANDO_FONTE:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_DESLIGANDO_FONTE][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD(telas_LCD[TELA_DESLIGANDO_FONTE + 1][idioma],pos);
			break;
		}
		case TELA_MODO_PONTO_A_PONTO:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_MODO_PONTO_A_PONTO][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD(telas_LCD[TELA_MODO_PONTO_A_PONTO + 1][idioma],pos);
			break;
		}
		case TELA_MODO_ACESSO_REMOTO:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_MODO_ACESSO_REMOTO][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD(telas_LCD[TELA_MODO_ACESSO_REMOTO + 1][idioma],pos);
			break;
		}
		case TELA_APAGANDO:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_APAGANDO][idioma]),pos);
			break;
		}
		case TELA_EM_MANUTENCAO:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_EM_MANUTENCAO][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD(telas_LCD[TELA_EM_MANUTENCAO+1][idioma],pos);
			break;
		}
		case TELA_DIGITE_NUMERO_SERIE:
		{
			EscreveLCD((telas_LCD[TELA_NUMERO_SERIE][idioma]),pos);
			LINHA = 2;
			EscreveLCD(telas_LCD[TELA_SEIS_SUBSCRITOS][idioma],pos);
			COLUNA = 6;
			PosicionaLCD(pos);
			break;
		}
		case TELA_GRAVAR_NUM_SERIE:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD(telas_LCD[TELA_GRAVAR_NUM_SERIE],pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD(telas_LCD[TELA_GRAVAR_NUM_SERIE + 1],pos);
			break;
		}
		case TELA_STATIC:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD(telas_LCD[TELA_STATIC],pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD(telas_LCD[TELA_STATIC + 1],pos);
			break;
		}
		case TELA_DHCP:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD(telas_LCD[TELA_DHCP],pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD(telas_LCD[TELA_DHCP + 1],pos);
			break;
		}
		case TELA_MOSTRA_STATIC_DHCP:
		{
			if(escolhe == 1)
			{
				tela = TELA_STATIC;
				Atualiza_LCD();
			}
			else if(escolhe == 2)
			{
				tela = TELA_DHCP;
				Atualiza_LCD();
			}
			break;
		}
		case TELA_CONFIRMA_INICIAR:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD(telas_LCD[TELA_CONFIRMA_INICIAR],pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD(telas_LCD[TELA_CONFIRMA_INICIAR + 1],pos);
			break;
		}
		case TELA_ERRO_AUTOCALIBRACAO:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD(telas_LCD[TELA_ERRO_AUTOCALIBRACAO],pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD(telas_LCD[TELA_ERRO_AUTOCALIBRACAO + 1],pos);
			break;
		}
		case TELA_PORTA_AUTOMATICA:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD(telas_LCD[TELA_PORTA_AUTOMATICA],pos);
			break;
		}
		case TELA_VALOR_INVALIDO_EXE_BACKUP:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD(telas_LCD[TELA_VALOR_INVALIDO_EXE_BACKUP],pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD(telas_LCD[TELA_VALOR_INVALIDO_EXE_BACKUP + 1],pos);
			break;
		}
		case TELA_MEMORIA_CORROMPIDA_CONTATE:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD(telas_LCD[TELA_MEMORIA_CORROMPIDA_CONTATE],pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD(telas_LCD[TELA_MEMORIA_CORROMPIDA_CONTATE + 1],pos);
			break;
		}
		case TELA_MEMORIA_CORROMPIDA_DESLIGUE:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD(telas_LCD[TELA_MEMORIA_CORROMPIDA_DESLIGUE],pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD(telas_LCD[TELA_MEMORIA_CORROMPIDA_DESLIGUE + 1],pos);
			break;
		}

		case TELA_SETA_PORTA_AUTOMATICA:
		{
			tela = TELA_PORTA_AUTOMATICA;
			Atualiza_LCD();
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_NAO_SIM][idioma]),pos);
			if(porta_automatica == NAO)
			{
				LINHA = 2;
				COLUNA = 2;
				PosicionaLCD(pos);
				EscreveChar('X');
				LINHA = 2;
				COLUNA = 15;
				PosicionaLCD(pos);
				EscreveChar(' ');
			}
			else if(porta_automatica == SIM)
			{
				LINHA = 2;
				COLUNA = 2;
				PosicionaLCD(pos);
				EscreveChar(' ');
				LINHA = 2;
				COLUNA = 15;
				PosicionaLCD(pos);
				EscreveChar('X');
			}
			break;
		}
		case TELA_SORTEADOR_ELETRONICO:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD(telas_LCD[TELA_SORTEADOR_ELETRONICO],pos);
			break;
		}
		case TELA_INICIAR_SORTEADOR:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD(telas_LCD[TELA_INICIAR_SORTEADOR],pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_NAO_SIM][idioma]),pos);
			if(sorteador == NAO)
			{
				LINHA = 2;
				COLUNA = 2;
				PosicionaLCD(pos);
				EscreveChar('X');
				LINHA = 2;
				COLUNA = 15;
				PosicionaLCD(pos);
				EscreveChar(' ');
			}
			else if(sorteador == SIM)
			{
				LINHA = 2;
				COLUNA = 2;
				PosicionaLCD(pos);
				EscreveChar(' ');
				LINHA = 2;
				COLUNA = 15;
				PosicionaLCD(pos);
				EscreveChar('X');
			}
			break;
		}
		case TELA_MOSTRA_QUANTIDADE_SORTEADOS:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_QUANTIDADE_SORTEADOS][idioma]),pos);
			LINHA = 2;
			COLUNA = 8;
			PosicionaLCD(pos);
			EscreveChar((char)(quantidade_sorteados/100 + 48));
			EscreveChar((char)((quantidade_sorteados%100)/10  + 48));
			EscreveChar((char)(quantidade_sorteados%10  + 48));
			break;
		}
//		case TELA_TROCAR_SENHA_GERENTE:
//		{
//			LINHA = 1;
//			COLUNA = 1;
//			EscreveLCD(telas_LCD[TELA_TROCAR_SENHA_GERENTE],pos);
//			LINHA = 2;
//			COLUNA = 1;
//			EscreveLCD(telas_LCD[TELA_TROCAR_SENHA_GERENTE + 1],pos);
//			break;
//		}
//		case TELA_TROCAR_SENHA_TECNICO:
//		{
//			LINHA = 1;
//			COLUNA = 1;
//			EscreveLCD(telas_LCD[TELA_TROCAR_SENHA_TECNICO],pos);
//			LINHA = 2;
//			COLUNA = 1;
//			EscreveLCD(telas_LCD[TELA_TROCAR_SENHA_TECNICO + 1],pos);
//			break;
//		}
		case TELA_TIPO_CONTROLE:
		{
			LINHA = 1;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_TIPO_CONTROLE][idioma]),pos);
			LINHA = 2;
			COLUNA = 1;
			EscreveLCD((telas_LCD[TELA_TIPO_A_B][idioma]),pos);
			if(tipoControle == 'B')
			{
				LINHA = 2;
				COLUNA = 2;
				PosicionaLCD(pos);
				EscreveChar('X');
				LINHA = 2;
				COLUNA = 15;
				PosicionaLCD(pos);
				EscreveChar(' ');
			}
			else if(tipoControle == 'A')
			{
				LINHA = 2;
				COLUNA = 2;
				PosicionaLCD(pos);
				EscreveChar(' ');
				LINHA = 2;
				COLUNA = 15;
				PosicionaLCD(pos);
				EscreveChar('X');
			}
			break;
		}
		break;
	}
	/******************************************************************************/

	if((tela == TELA_ATUALIZAR_DH) 			    ||
	   (tela == TELA_ALTERA_SENHA) 			    ||
	   (tela == TELA_CONFIRMAR_SENHA)	    	||
	   (tela == TELA_DIGITE_NOVA_SENHA)	    	||
	   (tela == TELA_DIGITE_SENHA_DA_GERENCIA)	||
	   (tela == TELA_DIGITE_SENHA_DO_TECNICO)   ||
	   (tela == TELA_ENDERECO_IP)				||
	   (tela == TELA_MASCARA_SUB_REDE)			||
	   (tela == TELA_ENDERECO_DNS)				||
	   (tela == TELA_ENDERECO_GATEWAY)			||
	   (tela == TELA_PORTA_WEB)					||
	   (tela == TELA_DIGITE_NUMERO_SERIE))
	{
		LigaDesligaCursor(LIGA);
	}
	else
	{
		LigaDesligaCursor(DESLIGA);
	}
}

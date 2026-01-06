/* ###################################################################
 **     Filename    : main.c
 **     Project     : PLACA_AGATA_REV16_04_12_2019
 **     Processor   : MK22FX512VLQ12
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 07-11-2019, 15:14, # CodeGen: 0
 **     Abstract    :
 **         Main module.
 **         This module contains user's application code.
 **     Settings    :
 **     Contents    :
 **         No public methods
 **
 ** ###################################################################*/
/*!
 ** @file main.c
 ** @version 01.01
 ** @brief
 **         Main module.
 **         This module contains user's application code.
 */
/*!
 **  @addtogroup main_module main module documentation
 **  @{
 */
/* MODULE main */

/* Including needed modules to compile this module/procedure */
#include "AdcLdd1.h"
#include "AdcLdd2.h"
#include "ASerialLdd1.h"
#include "ASerialLdd2.h"
#include "BitsIoLdd4.h"
#include "BitsIoLdd5.h"
#include "CAN.h"
#include "Control_LCD.h"
#include "Cpu.h"
#include "DADOS.h"
#include "BitsIoLdd1.h"
#include "Solenoide.h"
#include "TimerIntLdd5.h"
#include "TU6.h"
#include "Reserved_Solenoid.h"
#include "PwmLdd6.h"
#include "DEBOUNCING_1ms.h"
#include "Events.h"
#include "FLASH_INTERNA.h"
#include "IntFlashLdd1.h"
#include "IO_Map.h"
#include "main.h"
#include "PE_Const.h"
#include "PE_Error.h"
#include "PE_Types.h"
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
#include "RTC1.h"
#include "SERIAL_ETHERNET.h"
#include "SINAL_DAS_AREAS.h"
#include "SMasterLdd1.h"
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
#include "aes.h"
#include <stdio.h>
#include <string.h>

#include "agata_hc_definitions.h"
#include "agata_std_functions.h"

/* Including shared modules, which are used for whole project */

/* User includes (#include below this line is not maintained by Processor Expert) */

/****************************** Variáveis Globais *****************************/
LDD_TError Error;
LDD_TDeviceData *MyCANPtr,*MyRTCPtr,*MySPIPtr;
LDD_TDeviceData* SPI_DeviceData;



volatile byte menu = 1;
volatile byte menu1 = 1;
volatile byte menu2 = 1;
volatile byte menu3 = 1;
volatile byte escolhe = 0;
volatile byte flagretorno = 0;
volatile word x = 0,y = 0,z = 0,w = 0,k = 0,r = 0;
volatile byte Err = 0;
volatile byte confirma = NAO;
/******************************************************************************/

/**** Variaveis Struct***/

DataHora dataAtualizar;
Stc_Tabela CanalAtual;
Stc_Placas StcPlacas[3];

/******************************** Variáveis AD ********************************/
volatile bool FlagADC = 0;
volatile bool FlagADC1 = 0;
volatile bool flagVelocidade1 = FALSE,flagVelocidade2 = FALSE,flagVelocidade3 = FALSE,flagVelocidade4 = FALSE;
volatile bool flagVelocidade5 = FALSE,flagVelocidade6 = FALSE,flagVelocidade7 = FALSE,flagVelocidade8 = FALSE;
volatile bool fimLeitura1 = FALSE,fimLeitura2 = FALSE,fimLeitura3 = FALSE,fimLeitura4 = FALSE;
volatile bool fimLeitura5 = FALSE,fimLeitura6 = FALSE,fimLeitura7 = FALSE,fimLeitura8 = FALSE;
volatile bool AREA1_DETECTOU = NAO,AREA2_DETECTOU = NAO,AREA3_DETECTOU = NAO,AREA4_DETECTOU = NAO;
volatile bool AREA5_DETECTOU = NAO,AREA6_DETECTOU = NAO,AREA7_DETECTOU = NAO,AREA8_DETECTOU = NAO;
volatile bool LENDO_AREAS = FALSE,LENDO_AREAS1 = FALSE;
volatile byte detectou[8] = {NAO,NAO,NAO,NAO,NAO,NAO,NAO,NAO};
volatile byte nao_detectou[8] = {NAO,NAO,NAO,NAO,NAO,NAO,NAO,NAO};
volatile bool flag_antena_rx_sem_sinal = FALSE;
volatile byte delta_t1 = 0,delta_t2 = 0,delta_t3 = 0,delta_t4 = 0;
volatile byte delta_t5 = 0,delta_t6 = 0,delta_t7 = 0,delta_t8 = 0;
volatile byte valorad = 0;
volatile byte filtroruido = 1;
volatile byte valor_sinal_area1,valor_sinal_area2,valor_sinal_area3,valor_sinal_area4,
valor_sinal_area5,valor_sinal_area6,valor_sinal_area7,valor_sinal_area8;
volatile byte anula_area[8] = {0,0,0,0,0,0,0,0};
volatile byte flagMonitoraAreas = 0,areas_detectadas = 0,flag_area_detectada = 0;
/******************************************************************************/

/******************* Variáveis AJUSTE AUTOMÁTICO DE CANAL *********************/
volatile word Valor[8];
volatile word Valor1[8];
volatile dword Valor_Amostra_Area1[20];
volatile dword Valor_Amostra_Area2[20];
volatile dword Valor_Amostra_Area3[20];
volatile dword Valor_Amostra_Area4[20];
volatile dword Valor_Amostra_Area5[20];
volatile dword Valor_Amostra_Area6[20];
volatile dword Valor_Amostra_Area7[20];
volatile dword Valor_Amostra_Area8[20];
volatile dword numero_amostragens_canal[20];
volatile word tempo_leitura_canal = 0;
/******************************************************************************/

/**************** Variáveis AJUSTE AUTOMÁTICO DE SENSIBILIDADE ****************/
volatile dword valor_amostragem[4];
volatile word tempo_amostragem = 0;
volatile byte area_de_amostragem = 1;
volatile byte ERRO_AUTOCALIBRACAO = NAO;
/******************************************************************************/

/*********************** Variáveis AJUSTES DO SISTEMA *************************/
volatile byte definicoes = 1;
/******************************************************************************/

/************************** Variáveis AJUSTES TX-RX ***************************/
volatile byte ciclo_de_trabalho;
volatile word defasagem,aux_defasagem,frequencia;
/******************************************************************************/

/************************** Variáveis ALARME VISUAL ***************************/
volatile byte alarme_visual = NAO;
/******************************************************************************/

/***************************** Variáveis BARGRAPH *****************************/
volatile word valor_bargraph = 0,valor_bargraph1 = 0,valor_presente = 0,valor_presente1 = 0;
volatile word valor_anterior = 0,valor_anterior1 = 0,valor_atual = 0,valor_atual1 = 0;
volatile bool APAGA_BARGRAPH = TRUE;
/******************************************************************************/

/***************************** Variáveis BATERIA ******************************/
volatile word percentual_bat;
volatile bool PISCA_LED_BAT = FALSE;
volatile byte bateria_baixa = NAO;
/******************************************************************************/

/****************************** Variáveis BUZZER ******************************/
volatile byte buffer_buzzer[3] = {1,5,1};
volatile byte tempo_ativa_buzzer = 0;
/******************************************************************************/

/******************************* Variáveis CAN ********************************/
LDD_CAN_TFrame Frame;
volatile uint8_t InData[8] = {0x00U, 0x01U, 0x02U, 0x03U, 0x00U, 0x01U, 0x02U, 0x03U};
volatile uint8_t OutData[8] = {0x00U, 0x01U, 0x02U, 0x03U, 0x00U, 0x01U, 0x02U, 0x03U};
volatile bool DataFrameTxFlg = TRUE;
volatile bool DataFrameRxFlg;
volatile byte buffer_Presencas[3] = {0x01,0x00,0x00};
volatile byte estadoPresenca = GET_FONTE,estadoPresencaAnt = 0,var_Tempo_Presenca = 0;
volatile byte estado_CAN = ESTADO_ESPERA;
volatile word timeout_can = 0;
volatile bool ERRO_CAN = FALSE;
/******************************************************************************/

/****************************** Variáveis CANAL *******************************/
volatile byte canal = 1;
volatile byte perfil;
/******************************************************************************/

/***************************** Variáveis CONTADOR *****************************/
volatile bool INICIA_TIME_OUT_CONTADOR_BLOQUEIOS_DESBLOQUEIOS = ESTADO_ESPERA;
volatile dword contador_bloqueios,contador_desbloqueios;
volatile dword contador_entra,contador_sai,contador_passagens;
volatile dword contador_dia_entra,contador_dia_sai; //Contador de pessoas que entraram e sairam e total de pessoas que entrararam e sairam no dia
volatile byte conferencia_do_dia; //Variável que armazena o dia e se o dia for diferente zera os contadores diários.
volatile byte flag_passagem,entrou = NAO,saiu = SIM,entrou_na_porta = NAO; //flag_passagem para o sensor de teto de entrada quando em opção sensor de teto
volatile byte flag_passagem1; //flag_passagem1 para o sensor de teto de saida quando em opção sensor de teto
volatile byte estado_passagem = 10,estado_passagem1 = 10,estado_CONTADOR = ESTADO_ESPERA,estado_CONTADOR_BLOQ_DESB = ESTADO_ESPERA,estado_BURLA = ESTADO_ESPERA;
volatile word tempo_permissao = 0;
volatile word time_out_contador = 0;
volatile byte opcaosensorcontador = SENSOR_FRONTAL; //Variável que armazena o opção do sensor de contagem de pessoas a ser utilizado na PGDM, por padrão é SENSOR FRONTAL
/******************************************************************************/

/************************* Variáveis CONTROLE_REMOTO **************************/
volatile byte numero_controles = 0;
volatile word tempo_cadastro_controle = 0;
volatile bool ACAO_CONTROLE = AVALIA_CONTROLE;
volatile bool RESULTADO_CONTROLE = NENHUM;
volatile bool INICIA_CONTADOR_PULSOS = FALSE;
volatile word pulsos = 0;
volatile word start_remoto = 0;
volatile word start_remoto1 = 0;
volatile word tempo_leitura_botao_prog = 0;
volatile word tempo_bt = 0;
volatile word tempoVtInativo = 0;
volatile byte tipoControle = NENHUM;
volatile byte indexControle[] = {0};
volatile byte controlePressionado = 0;
/******************************************************************************/

/*************************** Variáveis DATA e HORA ****************************/
volatile byte AtualizaDia,AtualizaMes,AtualizaAno,AtualizaHora,AtualizaMinuto,AtualizaSegundo;
/******************************************************************************/

/****************************** Variáveis DELAY *******************************/
volatile bool FIM_TEMPO_DELAY_S = FALSE;
volatile word cont_ms,cont_s;
/******************************************************************************/

/****************************** Variáveis ESTADO ******************************/
volatile byte estado, estado_troca_senha,estado_LCD,estado_SERIAL = ESTADO_ESPERA,estado_MODULO_ETHERNET = ESTADO_ESPERA;
volatile byte estado_ENVIA_SERIAL_ETHERNET = ESTADO_ESPERA;
/******************************************************************************/

/************************* Variáveis ETHERNET-SERIAL **************************/
volatile byte envia_serial[512];
volatile byte recebe_serial[512];
volatile byte byte_count = 0;
volatile byte primeiro = 0;
volatile byte dado_recebido;
volatile word Sent;
volatile byte aceito = 0;
volatile bool MANUTENCAO = NAO;
volatile bool emite_msg_manutencao = NAO;
volatile char str[3];
volatile char *str3 = " ";
volatile byte PADRAO = _STATIC;
volatile word time_out_ethernet = 0;
volatile bool INICIA_TIME_OUT_ETHERNET = NAO;
volatile bool FIM_TIME_OUT_ETHERNET = NAO;
volatile char erro_comunicacao = '0';
volatile bool PRIMEIRO_ENVIO = SIM;
/******************************************************************************/

/***************************** Variáveis FABRICA ******************************/
volatile byte fabrica;
/******************************************************************************/

/************************ Variáveis FALHA DAS BOBINAS *************************/
volatile bool FALHA_DAS_BOBINAS = FALSE;
volatile bool eliminar_falha = NAO;
/******************************************************************************/

/****************************** Variáveis FONTE *******************************/
volatile byte var_tensao_cinco = 0;
volatile byte var_tensao_quinze = 0;
volatile byte var_tensao_menos_quinze = 0;
volatile byte var_tensao_rede = 0;
volatile word var_tensao_bateria = 0;
volatile word var_tensao_chaveada = 0;
volatile byte estado_anterior_AC = DES;
volatile byte estado_atual_AC = DES;
volatile byte estado_anterior_BAT = DESCARREGADA;
volatile byte estado_atual_BAT = DESCARREGADA;
volatile byte estado_anterior_DT = DES;
volatile byte estado_atual_DT = DES;
volatile dword timer_tensoes;
volatile byte estado_da_fonte = 0;
/******************************************************************************/

/****************************** Variáveis IDIOMA ******************************/
volatile byte idioma;
/******************************************************************************/

/************************** Variáveis INFRAVERMELHO ***************************/
volatile byte sensibilidadeir,aux_sensibilidadeir,var_infra1 = 1,var_infra2 = 1; //Coloquei 1 em var_infra1 e var_infra2 só para teste, depois colocar para 0
volatile byte analiseir;
volatile word time_debouncing_infra = 0;
volatile bool anula_infras = FALSE;
volatile bool sorteou = FALSE;
/******************************************************************************/

/************************ Variáveis LOG DE AUDITORIAS *************************/
volatile dword num_bytes_a = 0;
volatile dword num_bloco_a = 5;
volatile dword end_bloco_a = 0;
volatile dword n_bloco_a = 0;
volatile word n_logauditorias = 0;
volatile dword n_blocologauditorias = 0;
volatile dword n_blocologauditorias_extra = 0;
volatile byte posicao_bloco_a = 0;
volatile word posicao_byte_a = 0;
volatile word indice_auditorias = 0;
volatile word indice_auditorias_cont = 0;
volatile word indice_auditorias_lidos = 0;
volatile word indice_auditorias_gravados = 0;
volatile word indice_bloco_auditorias = 0;
volatile char OPERADOR = 0;
volatile char DISPOSITIVO = 0;
volatile bool FIM_LOG_AUDITORIAS = FALSE;
volatile dword ultimo_endereco_auditoria = 0x88000;
volatile byte flagAuditLido = 0; //Do endereço 0x75000 a 0x79000-1 as flags inicializam com 0 o que significa que não foi preenchido, devemos preencher com 1 quando não foi lido e com 0 quando foi lido.
volatile byte AudToSend = 0; //Flag para indicar que tem que ser reenviado o registro novamente pois o servidor perdeu a informação deste registro
volatile dword end_audit_reenvio = 0x75000; //Esta variavel inicia toda vez com 0x75000 ao iniciar o equipamento apontando para o primeiro endereço da flag de auditorias lidos
volatile word contador_endereco_audit = 0; //Variável para contar os endereços na função Le os endereços das flags de auditorias.
/******************************************************************************/

/************ Variáveis LOG DE EVENTOS DE BLOQUEIOS E DESBLOQUEIOS ************/
volatile dword num_bytes_l = 0;
volatile dword num_bloco_l = 1;
volatile dword end_bloco_l = 0;
volatile dword n_bloco_l = 0;
volatile word n_logeventos = 0;
volatile dword n_blocologeventos = 0;
volatile dword n_blocologeventos_extra = 0;
volatile byte posicao_bloco_l = 1;
volatile word posicao_byte_l = 0;
volatile word indice_eventos = 0;
volatile word indice_eventos_cont = 0;
volatile word indice_eventos_lidos = 0;
volatile word indice_eventos_gravados = 0;
volatile byte indice_bloco_eventos = 0;
volatile bool INICIA_TIME_OUT_USB_SERIAL = FALSE;
volatile word tempo_time_out_serial = 0;
volatile bool FIM_LOG_EVENTOS = FALSE;
volatile dword ultimo_endereco_eventos = 0x83000;
volatile byte flagEventoLido = 0; //Do endereço 0x48000 a 0x49000-1 as flags inicializam com 0 o que significa que não foi preenchido, devemos preencher com 1 quando não foi lido e com 0 quando foi lido.
volatile byte EventToSend = 0; //Flag para indicar que tem que ser reenviado o registro novamente pois o servidor perdeu a informação deste registro
volatile dword end_event_reenvio = 0x48000; //Esta variavel inicia toda vez com 0x48000 ao iniciar o equipamento apontando para o primeiro endereço da flag de eventos lidos
volatile word contador_endereco = 0; //Variável para contar os endereços na função Le os endereços das flags de eventos.
/******************************************************************************/

/************************** Variáveis MEMÓRIA FLASH ***************************/
volatile byte Write_Buffer_FLASH[4110];
volatile byte Read_Buffer_FLASH[4110];
volatile bool GRAVA_FLASH = FALSE;
volatile dword numero_bloco = 0;
volatile dword aux_numero_bloco = 0;
volatile byte LEITURA_FLASH_FINALIZADA = NAO;
/******************************************************************************/

/************************* Variáveis MENSAGEM DE VOZ **************************/
volatile bool INICIA_TEMPO_MSG_VOZ;
volatile byte volume_mensagem_voz;
volatile byte lig_des_mensagem_voz;
volatile word tempo_msg_voz = 0;
/******************************************************************************/

/************************* Variáveis MODELO DE ANTENA *************************/
volatile byte modelo_antena = PLANA_ONIX_2000;
/******************************************************************************/

/*********************** Variáveis MODO DE TRAVAMENTO *************************/
volatile byte modo_travamento = TRAVA_DESTRAVA;
/******************************************************************************/

/*********************** Variáveis do MÓDULO ETHERNET *************************/
volatile byte modo_operacao_ethernet = MODO_SERIAL;
volatile byte end_IP[15]; //Endereço IP para ponto a ponto
volatile byte end_SUB_MASK[15];
volatile byte end_GATEWAY[15];
volatile byte end_DNS[15];
volatile byte end_aux[15];
volatile byte end_PORT[5]; //HTTP port para ponto a ponto
volatile byte end_PORT1[5]; //remote port para acesso remoto
volatile byte HTTP[4];
volatile byte alterou = 0;
volatile bool INICIA_TEMPO_ENVIO_ETHERNET = FALSE;
volatile word tempo_envio_ethernet;
volatile byte recebendo = 0;
volatile byte num_auditorias = 1;
volatile byte LIBERA_ENVIA_PACOTES = NAO;
/******************************************************************************/

/************************* Variáveis NÚMERO DE SÉRIE **************************/
volatile byte Num_Serie_Write[8] = {'D','T','0','0','0','0','0','0'};
volatile byte numero_serie[6] = {'0','0','0','0','0','0'};
volatile bool FIM_NUMERO_SERIE = NAO;
volatile dword senha_mestre_aux = 0;
volatile byte var_senha_mestre[6];
volatile word tempo_numero_serie = 0;
volatile bool INICIA_TEMPO_NUMERO_SERIE = FALSE;
volatile bool flag_numero_serie = FALSE;
/******************************************************************************/

/********************* Variáveis POTENCIÔMETROS DIGITAIS **********************/
volatile byte buffer_ganho[9],buffer_selecao[9];
/******************************************************************************/

/******************************* Variáveis RELÉ *******************************/
volatile byte pulso_rele = 1;
volatile byte sinal_rele = rele_retencao;
volatile word tempo_pulso_rele = 1;
volatile bool HABILITA_TEMPO_PULSO_RELE = FALSE;
/******************************************************************************/

/******************************* Variáveis RTC ********************************/
volatile unsigned char Vbat_power_on = 0;
LDD_RTC_TTime Time;
/******************************************************************************/

/************************ Variáveis SELEÇÃO DE METAIS *************************/
volatile byte selecao_metais = 50,aux_selecao_metais = 0;;
/******************************************************************************/

/****************************** Variáveis SENHAS ******************************/
volatile byte senha_de_acesso,buffer_senhas[18],ch = 0x30;
volatile byte senha[6] = {'0','0','0','0','0','0'};
volatile byte confirma_senha[6] = {'0','0','0','0','0','0'};
volatile char C = 0x30;
volatile bool senha_gerente_trocada = FALSE;
volatile bool senha_tecnico_trocada = FALSE;
/******************************************************************************/

/************************** Variáveis SENSIBILIDADE ***************************/
volatile byte sensibilidade,buffer_sensibilidade[9],selecionaArea;
/******************************************************************************/

/************************* Variáveis SENSOR INDUTIVO **************************/
volatile byte INDUTIVO_ACIONADO = NAO;
volatile byte controle_ou_painel_travou = NAO;
volatile byte porta_automatica = NAO;
/******************************************************************************/

/******************************************************************************/

/*************************** Variáveis da SINALEIRA ***************************/
volatile bool fim_sinaleira = FALSE;
/******************************************************************************/

/******************************* Variáveis TELA *******************************/
volatile bool INIBE_TELAS_DE_MSG = FALSE;
volatile byte pos[2];
volatile word tela;
volatile word tempo_msg = 0;
volatile byte tempo_tela_erro = 0;
/******************************************************************************/

/****************************** Variáveis TECLAS ******************************/
volatile byte teclapressionada;
volatile byte tecla[9] = {0,0,0,0,0,0,0,0,0};
/******************************************************************************/

/*************************** Variáveis TEMPORIZADOR_10ms ***************************/
volatile word time_debouncing = 0;
/******************************************************************************/

/************************* Variáveis TEMPORIZADOR_1s **************************/
volatile word tempo_leitura_tensoes = 0;
volatile word tempo_contador_hora = 0;
volatile byte rotina_hora = 1;
/******************************************************************************/

/*************************** Variável Tipo Detector ***************************/
volatile byte tipo_detector = Z8;
/******************************************************************************/

/****************************** Variáveis TRAVA *******************************/
volatile byte pulso_trava = 1;
volatile byte sinal_trava = trava_retencao_controle;
volatile word tempo_pulso_trava = 1;
volatile bool HABILITA_TEMPO_PULSO_TRAVA = FALSE;
volatile bool travado = FALSE;
volatile byte trava_inteligente = NAO;
volatile bool INICIA_TEMPO_TRAVA_INTELIGENTE = FALSE;
volatile word tempo_trava_inteligente = 0;
volatile byte tempo_trava = 0;
volatile byte pwm_trava = 0;
volatile bool estado_trava;
/******************************************************************************/

/**************************** Variáveis USB-SERIAL ****************************/
volatile byte envia_serial1[70];
volatile byte recebe_serial1[70];
volatile byte byte_count1 = 0;
volatile byte primeiro1 = 0;
volatile byte dado_recebido1;
volatile word Sent1;
/******************************************************************************/

/********************* Variáveis do SORTEADOR ELETRONICO **********************/
volatile byte sorteador = NAO; //Variável para informar se será realizado detecção aleatória de 10 a 255 conforme sorteamento automático
volatile byte cont_sorteador = 0; //Variável que conta de 1 a 255 e reinicializa automaticamente ao final da quantidade de sorteados e será sempre comparada com os número sorteado
volatile byte quantidade_sorteados = 10; //Variável para definir a quantidade de sorteados entre 10 e 255
volatile byte numero_sorteado; //Variávle para armazenar o número sorteado
/******************************************************************************/

/************************** Variáveis Integração ZC ***************************/
volatile bool statusPGDM = PGDM_ABERTA;
/******************************************************************************/

/*************************** Variáveis Erro Agata *****************************/
volatile byte erroAgata = 'A';
/******************************************************************************/

volatile int16 infra1_timer = 0;
volatile int16 infra2_timer = 0;
volatile bool INFRA1_TEMP = 0;
volatile bool INFRA2_TEMP = 0;

volatile bool acao_cancelada = NAO;

int FLAG_CORRUPCAO_TESTE = 0; //TODO DELETAR - Teste de corrupcao

/******************** ÚLTIMA VERSÃO DE SOFTWARE DO PAINEL *********************/

//         NUMERO DE SERIE - FLASH		 NUMERO DE SERIE - CAN
Stc_Placas StcPlacas[3] = 	{	{ {'D','T','0','0','0','0','0','0'},{'0','0','0','0','0','0'}},  //PAINEL
		{ {'A','D','0','0','0','0','0','0'},{'0','0','0','0','0','0'}},  //AUDIO
		{ {'F','T','0','0','0','0','0','0'},{'0','0','0','0','0','0'}}}; //FONTE
/******************************************************************************/


/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/

	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/

	/* Write your code here */

	RESET:

	LIGA_SINALEIRA_VERMELHA;
	LIGA_TRAVA;


	memset(recebe_serial,0,sizeof(recebe_serial));

	/******************** Desabilita Buzzer na Inicialização **********************/
	PWM_BUZZER_Disable();
	/******************************************************************************/

	/************************ Inicializa comunicação CAN **************************/
	MyCANPtr = CAN_Init(NULL);
	/******************************************************************************/

	/********** Inicializa comunicação SPI dos potenciômetros digitais ************/
	POTENCIOMETRO_DIGITAL_Enable();
	/******************************************************************************/

	/*********************** Inicializa entradas e saidas *************************/
	PORTA_Init();
	PORTB_Init();
	PORTC_Init();
	PORTD_Init();
	PORTE_Init();
	/******************************************************************************/

	/************************* Inicializa_ETHERNET_SERIAL *************************/
	SERIAL_ETHERNET_Enable();

	RESET_SERIAL_ETHERNET; //Faz um reset no módulo ethernet
	delay_ms(400);
	SET_SERIAL_ETHERNET;
	/******************************************************************************/

	/*************************** Inicializa_USB_SERIAL ****************************/
	USB_PC_Enable();
	/******************************************************************************/

	/**** Inicializa PWM INFRAS com 5% para não queimar durante inicialização *****/
	PWM_INFRAS_SetRatio8(13);
	/******************************************************************************/

	/*** Inicializa PWM com um valor para não danificar transistor MOSFET da TX ***/
	InitPwm(); //Inicializa PWM TX,PWM RX1,PWM RX2
	ciclo_de_trabalho = 10; //Seta ciclo de trabalho PWM TX para 10% só para iniciar
	defasagem = 90; //Seta defasagem para metade do valor dos 180 graus só para iniciar
	SetFrequencia(4000); //Seta frequência do PWM TX para 4000Hz só para iniciar
	/******************************************************************************/

	/************************** Inicializa o módulo LCD ***************************/
	InitLCD(); //Inicializa LCD
	LimpaLCD(); //Limpa LCD
	LigaDesligaCursor(LIGA); //Liga Cursor
	/******************************************************************************/

	/*********** Escreve Nome do Produto e Nome da Empresa no LCD *****************/
	LINHA = 1;											//posiciona na linha 1 do LCD
	COLUNA = 1;											//posiciona na coluna 1 do LCD
	EscreveLCD((telas_LCD[TELA_INICIAL1][idioma]),pos);	//Escreve o nome da empresa

	LE_FLASH_INTERNA(endFLASHTipoDetector,1);
	tipo_detector = Read_Buffer_FLASH[0];


	if(tipo_detector == Z3)
	{
		LINHA = 2;											//posiciona na linha 2 do LCD
		COLUNA = 1;											//posiciona na coluna 1 do LCD
		EscreveLCD(telas_LCD[TELA_INICIAL_3Z][idioma],pos);	//Escreve o nome do produto
	}
	else if(tipo_detector == Z8 || tipo_detector == 0xFF)
	{
		LINHA = 2;											//posiciona na linha 2 do LCD
		COLUNA = 1;											//posiciona na coluna 1 do LCD
		EscreveLCD(telas_LCD[TELA_INICIAL1 + 1][idioma],pos);	//Escreve o nome do produto
	}
	/******************************************************************************/


	delay_ms(1000); //Aguarda 2 segundos

	//GravaPadroesFabrica();



	LE_FLASH_INTERNA(END_INI_PARAMETROS,8);
	if(Read_Buffer_FLASH[0] == 0xFF && Read_Buffer_FLASH[1] == 0xFF && Read_Buffer_FLASH[2] == 0xFF && Read_Buffer_FLASH[3] == 0xFF &&
			Read_Buffer_FLASH[4] == 0xFF && Read_Buffer_FLASH[5] == 0xFF && Read_Buffer_FLASH[6] == 0xFF && Read_Buffer_FLASH[7] == 0xFF)
	{
		LE_FLASH_INTERNA(END_INI_BACKUP,8);
		if(Read_Buffer_FLASH[0] == 0xFF && Read_Buffer_FLASH[1] == 0xFF && Read_Buffer_FLASH[2] == 0xFF && Read_Buffer_FLASH[3] == 0xFF &&
				Read_Buffer_FLASH[4] == 0xFF && Read_Buffer_FLASH[5] == 0xFF && Read_Buffer_FLASH[6] == 0xFF && Read_Buffer_FLASH[7] == 0xFF)
		{	//Caso exista algo salvo na memoria de backup houve falha na memoria: escapa e quando for feita a atribuicao (

			while(FIM_NUMERO_SERIE == NAO)
			{
				fnGravaNumSerie();
			}
		}
	}

	/************************ Escreve Aguarde no LCD ******************************/
	LimpaLCD();											//Limpa LCD
	LINHA = 1;											//posiciona na linha 1 do LCD
	COLUNA = 1;											//posiciona na coluna 1 do LCD
	EscreveLCD((telas_LCD[TELA_AGUARDE][idioma]),pos);	//Escreve AGUARDE... na tela
	/******************************************************************************/

	delay_ms(1000); //Aguarda 2 segundos

	if (Vbat_power_on == TRUE) //Se Vbat_power_on for 1 então inicializa o RTC e reseta todos os registro do RTC
	{
		MyRTCPtr = RTC1_Init((LDD_TUserData *)NULL, FALSE); /* Inicializa o RTC, reseta todos os registros do RTC */
		RTC1_GetTime(MyRTCPtr, &Time); //Captura o valor da hora atual para a estrutura Time
	}
	else //Se Vbat_power_on for 0 então somente inicializa o RTC e preserva os ajustes de tempo
	{
		MyRTCPtr = RTC1_Init((LDD_TUserData *)NULL, TRUE); /* Inicializa o RTC, preserva o ajustes de tempo */
		RTC1_GetTime(MyRTCPtr, &Time); //Captura o valor da hora atual para a estrutura Time
	}
	RTC1_SetTime(MyRTCPtr, &Time);

	/*** Lê o número de série gravado na FLASH na produção, caso não tenha sido gravado o valor padrão é DT000000 ***/
	fnMascaraNumeroSerie();
	/****************************************************************************/

	estado = ESTADO_GET_ALIVES; //Indica que o primeiro estado a ser executado a verificação da existência de todos os periféricos conectados na CAN
	fnConfereGravaResetaContadorDiario();



	while(1)
	{
		//Realiza teste para verificar se há memória corrompida
		//Serve para debug apenas
		if(TESTE_CORRUPCAO_MEMORIA == TRUE){		//Ativar
			if(buffer_sensibilidade[1] == 45) {
				FLAG_CORRUPCAO_TESTE = 2;
			}
			if(buffer_sensibilidade[1] == 43 && FLAG_CORRUPCAO_TESTE == 2){	//TODO TESTE DE CORRUPCAO - DELETAR

				memset(Write_Buffer_FLASH,0xFF,200);
				fnEscreveNoEndereco(END_INI_PARAMETROS,200);
				FLAG_CORRUPCAO_TESTE = 0;
				EscreveLCD("M CORROMP DESLIGUE" ,pos);

				delay_ms(2000); //Aguarda 2 segundos
				goto RESET;
			}
		}

		//Após configuração de fábrica/leitura de configuração verifica se as senhas já foram trocadas
		//Caso as senhas não tenham sido trocadas, solicita a troca de senha.
		if(tela == TELA_CONFIRMA_INICIAR)
		{
			if(senha_gerente_trocada == FALSE){
				estado_troca_senha = ESTADO_SOLICITA_TROCA_SENHA;

				teclapressionada = 0;
				menu = 2;
				definicoes = 1;
				delay_ms(10);
				LimpaLCD();
				tela = TELA_MOSTRA_AJUSTES_DO_SISTEMA;
				Atualiza_LCD();
				estado = ESTADO_ALTERA_SENHA;
				TocaTomBuzzer();
				tempo_ativa_buzzer = 0;
				while(senha_gerente_trocada == FALSE){
					//toca buzzer a cada 1.5 segundos
					if(tempo_ativa_buzzer == INTERVALO_BUZZER){
						TocaTomBuzzer();
						tempo_ativa_buzzer = 0;
					}
					if(teclapressionada == teclaConfirma || teclapressionada == teclaConfirma_Remoto){
						teclapressionada = 0;
						do{
							if(estado == ESTADO_ALTERA_SENHA){
								fnAlteraSenha();
							}
							if(estado == ESTADO_CONFIRMA_SENHA){
								fnConfirmaSenha();
							}

							if(acao_cancelada == SIM){
								acao_cancelada = NAO;
								LimpaLCD();
								tela = TELA_MOSTRA_AJUSTES_DO_SISTEMA;
								Atualiza_LCD();
								estado = ESTADO_ALTERA_SENHA;
								TocaTomBuzzer();
								tempo_ativa_buzzer = 0;
								break;
							}
						}while(senha_gerente_trocada == FALSE);
					}

					if(teclapressionada == teclaCancela){
						teclapressionada = 0;
						break;
					}
				}
			}
			if(senha_tecnico_trocada == FALSE){
				estado_troca_senha = ESTADO_SOLICITA_TROCA_SENHA;
				teclapressionada = 0;
				menu = 3;
				definicoes = 2;
				delay_ms(10);
				LimpaLCD();
				tela = TELA_MOSTRA_AJUSTES_DO_SISTEMA;
				Atualiza_LCD();
				estado = ESTADO_ALTERA_SENHA;
				TocaTomBuzzer();
				tempo_ativa_buzzer = 0;
				while(senha_tecnico_trocada == FALSE){
					//toca buzzer a cada 1.5 segundos
					if(tempo_ativa_buzzer == INTERVALO_BUZZER){
						TocaTomBuzzer();
						tempo_ativa_buzzer = 0;
					}

					if(teclapressionada == teclaConfirma || teclapressionada == teclaConfirma_Remoto){
						teclapressionada = 0;
						do{
							if(estado == ESTADO_ALTERA_SENHA){
								fnAlteraSenha();
							}
							if(estado == ESTADO_CONFIRMA_SENHA){
								fnConfirmaSenha();
							}
							if(acao_cancelada == SIM){
								acao_cancelada = NAO;
								estado = ESTADO_ALTERA_SENHA;
								LimpaLCD();
								tela = TELA_MOSTRA_AJUSTES_DO_SISTEMA;
								Atualiza_LCD();
								TocaTomBuzzer();
								tempo_ativa_buzzer = 0;
								break;
							}
						}while(senha_tecnico_trocada == FALSE);
					}

					if(teclapressionada == teclaCancela){
						teclapressionada = 0;
						break;
					}
				}
			}
			estado_troca_senha = ESTADO_ESPERA;
			estado = ESTADO_LER_TECLAS;

			//		  if(teclapressionada == teclaConfirma)
			//		  {
			teclapressionada = 0;
			delay_ms(10);
			LimpaLCD();
			tela = TELA_INICIAL;
			Atualiza_LCD();
			LIGA_SINALEIRA_VERDE;
			DESLIGA_TRAVA;
			TocaTomBuzzer();
			//		  }
		}

		if(estado_da_fonte == 1 && estado_anterior_DT == DES && estado_atual_DT == LIG && LEITURA_FLASH_FINALIZADA == SIM)
		{
			estado_anterior_DT = LIG;
			estado_atual_DT = DES;
			fnGravaAuditoria(195,estado_anterior_DT,estado_atual_DT,'D','P');
			delay_ms(100);
			SendCan(FONTE_CAN,GET_DESLIGAR);
		}
		if(estado_da_fonte == 2 && estado_anterior_DT == DES && estado_atual_DT == DES && LEITURA_FLASH_FINALIZADA == SIM)
		{
			estado_anterior_DT = DES;
			estado_atual_DT = LIG;
			delay_ms(100);
			fnGravaAuditoria(195,estado_anterior_DT,estado_atual_DT,'D','P');
		}


		if(FIM_LOG_EVENTOS == TRUE || FIM_LOG_AUDITORIAS == TRUE)
		{
			envia_serial[0] = '#'; //Caracter de inicio
			envia_serial[1] = 'l'; //log
			envia_serial[2] = 'f'; //fim
			envia_serial[3] = '!'; //
			envia_serial[4] = '\n';

			SERIAL_ETHERNET_SendBlock((byte*)&envia_serial,5,&Sent); //Envia os dados seriais
			FIM_LOG_EVENTOS = FALSE;
			FIM_LOG_AUDITORIAS = FALSE;
		}

		/************************************ INICIO TIMEOUT CAN ************************************/
		// Aborta envio da mensagem CAN se passar do tempo TIMEOUT_CAN
		if(!DataFrameTxFlg && timeout_can >= TIMEOUT_CAN) //Se timeout_can for maior ou igual a 2s então
		{
			abortTxCAN();	//Aborta envio da mensagem
			DataFrameTxFlg = TRUE;				//Indica que TX está livre pra nova mensagem
			tempo_leitura_tensoes = 0;
			timeout_can = 0;
			if(tela == TELA_INICIAL || tela == TELA_INICIAL1 || tela == TELA_INICIAL_3Z){
				LimpaLCD(); //Limpa LCD
				LINHA = 1; //Se posiciona na linha 1
				COLUNA = 1; //Se posiciona na coluna 1
				EscreveLCD((telas_LCD[TELA_ERRO_COMUNICACAO][idioma]),pos); //Escreve no LCD CAN DESCONECTADA
				LINHA = 2; //Se posiciona na linha 2
				COLUNA = 1; //Se posiciona na coluna 1
				EscreveLCD((telas_LCD[TELA_ERRO_COMUNICACAO + 1][idioma]),pos); //Escreve no LCD ERRO COMUNICACAO
				//			delay_ms(2000); //Espera 2 segundos
				//			Atualiza_LCD();
			}
			ERRO_CAN = TRUE; //Armazena na variável ERRO_CAN a informação TRUE para informar que houve problema na CAN
		}
		/************************************ FIM TIMEOUT CAN ************************************/

		//Reseta a tela de ERRO COMUNICAÇÃO CAN
		if(tempo_tela_erro > 2){
			ERRO_CAN = FALSE;
			tempo_tela_erro = 0;
			tempo_leitura_tensoes = 0;
			if(tela == TELA_INICIAL || tela == TELA_INICIAL1 || tela == TELA_INICIAL_3Z){
				Atualiza_LCD();
			}
		}

		/***************************** INICIO ENVIO DE MSG CAN *****************************/
		if(DataFrameTxFlg){

			if(tempo_leitura_tensoes == 3 && ERRO_CAN == FALSE)  //Realiza a requisição de tensões para a fonte a cada 2s se CAN conectada
			{
				SendCan(FONTE_CAN,GET_TENSOES); //Envia a requisição de tensões para a fonte
				tempo_leitura_tensoes++;
			}
			else if(tempo_leitura_tensoes == 7 && ERRO_CAN == FALSE)
			{
				SendCan(FONTE_CAN,GET_TENSOES1); //Envia a requisição de tensões para a fonte
				tempo_leitura_tensoes++;
				//		  tempo_leitura_tensoes = 0;
			}
			else if(tempo_leitura_tensoes > 10 && ERRO_CAN == FALSE)
			{
				SendCan(ZC_CAN,GET_STATUS_PGDM);
				tempo_leitura_tensoes = 0;		//Zera o contador de tempo_leitura_tensoes para poder ler novamente após 3s
			}
		}
		/****************************** FIM ENVIO DE MSG CAN ******************************/

		if(estado_SERIAL == ESTADO_TRATA_SERIAL) //Trata os dados recebidos da SERIAL-USB caso tenha ocorrido recebimento de dados por interrupção
		{
			TrataSerial(); //Trata os dados recebidos e toma as suas devidas ações
		}
		if(estado_BURLA == ESTADO_HOUVE_BURLA){
			//Se entrou com a PGDM fechada reproduz mensagem de burla
			fnReproduzMsgVoz(BURLA);
		}
		if(estado_MODULO_ETHERNET == ESTADO_TRATA_ETHERNET)
		{
			TrataSerial1(); //Trata as requisições feitas pelo software PC
		}
		if(estado_CONTADOR == ESTADO_GRAVA_CONTADOR) //Sempre entra aqui caso ocorra alguma passagem pelos infravermelhos para contar entrada e saida de pessoas
		{
			fnContadorPassagem();
		}
		if(estado_ENVIA_SERIAL_ETHERNET == ESTADO_ENVIAR && estado != ESTADO_ALTERAR_DATA_E_HORA &&
				LIBERA_ENVIA_PACOTES == SIM)
		{
			EnviaPacoteDados();	// Envia o pacote do monitoramento remoto
		}

		if(FIM_TIME_OUT_ETHERNET == SIM)
		{
			INICIA_TIME_OUT_ETHERNET = NAO;
			FIM_LOG_EVENTOS = TRUE;
			FIM_LOG_AUDITORIAS = TRUE;
			FIM_TIME_OUT_ETHERNET = NAO;
			recebe_serial[8] = '0';
			estado_MODULO_ETHERNET = ESTADO_TRATASERIAL2;
		}
		if(estado_MODULO_ETHERNET == ESTADO_TRATASERIAL2) //Trata os dados recebidos pela ethernet na comunicação remota
		{
			delay_ms(20);
			TrataSerial2();
		}
		if(estado_LCD == ATUALIZA_LCD) //Entra aqui toda vez que um menu solicitar a apresentação de uma informação no display LCD
		{
			Atualiza_LCD(); //Atualiza o LCD com a informação desejada
		}
		if(estado_CAN == ESTADO_TRATA_CAN) //Toda vez que houver um recebimento de dados pela CAN a rotina abaixo trata os dados recebidos
		{
			TrataCAN(); //Trata os dados recebidos e toma as suas devidas ações
		}
		if(estado_CONTADOR_BLOQ_DESB == ESTADO_GRAVA_CONTADOR_BLOQUEIOS_DESBLOQUEIOS) //Grava as informações de bloqueios após parar de pressionar as teclas
		{
			//Separa a variável dword contador de bloqueios em 4 bytes para armazenar na memória FLASH
			Write_Buffer_FLASH[0] = (byte)(contador_bloqueios >> 24);
			Write_Buffer_FLASH[1] = (byte)(contador_bloqueios >> 16);
			Write_Buffer_FLASH[2] = (byte)(contador_bloqueios >> 8);
			Write_Buffer_FLASH[3] = (byte)(contador_bloqueios);
			ESCREVE_FLASH_INTERNA(endFLASHTotalBloqueios,4,0); //Escreve no endereço especificado os 4 bytes

			//Separa a variável dword contador de desbloqueios em 4 bytes para armazenar na memória FLASH
			Write_Buffer_FLASH[0] = (byte)(contador_desbloqueios >> 24);
			Write_Buffer_FLASH[1] = (byte)(contador_desbloqueios >> 16);
			Write_Buffer_FLASH[2] = (byte)(contador_desbloqueios >> 8);
			Write_Buffer_FLASH[3] = (byte)(contador_desbloqueios);
			ESCREVE_FLASH_INTERNA(endFLASHTotalDesbloqueios,4,0);

			estado_CONTADOR_BLOQ_DESB = ESTADO_ESPERA; //Coloca a flag em ESTADO_ESPERA para não gravar os mesmos dados novamente
		}
		if( (INDUTIVO_ACIONADO == SIM || SENSOR_INDUTIVO_ATIVADO) && porta_automatica == SIM)
		{
			INDUTIVO_ACIONADO = NAO; //Indica que indutivo já acionou uma vez e não precisa acionar de novo, somente na próxima borda de descida
			flag_area_detectada = 0;
			DESLIGA_RELE; //Desenergiza o relé
			APAGA_AREAS; //Apaga os leds das áreas
			ACENDE_NIVEL0; //Apaga os leds do bargraph
			LIGA_SINALEIRA_VERDE; //Liga sinaleira verde
			fnCortaMsgVoz(); //Corta a mensagem de voz
			areas_detectadas = 0; //Zera a variável areas_detectadas
			Solenoide_DisableEvent();		//Desativa evento que gera PWM solenoide
			Solenoide_Disable();			//Desativa Timer que gera o evento do PWM solenoide
			tempo_trava = 0;				//Reseta contador de tempo para ativar PWM da solenoide
			pwm_trava = 0;					//Reseta contador PWM da solenoide
			DESLIGA_TRAVA; //Desenergiza a trava
			if(sinal_trava == trava_retencao_controle || sinal_trava == trava_retencao_controle_teclado) //Se sinal_trava for igual a trava_retencao_controle ou sinal_trava for igual a trava_retencao_controle_teclado então
			{
				if(travado == TRUE)
				{
					contador_desbloqueios++; //Incrementa contador_bloqueios
					INICIA_TIME_OUT_CONTADOR_BLOQUEIOS_DESBLOQUEIOS = TRUE; //Armazena na variável INICIA_TIME_OUT_CONTADOR_DESBLOQUEIOS a informação TRUE
					time_out_contador = 0; //Zera o time_out_contador
					travado = FALSE;
				}
			}
		}
		if(estado == ESTADO_CARREGA_DADOS) //Lê os parâmetros do detector
		{
			LeParametrosDetector(); //Decide se vai gravar os padrões de fábrica por ser a primeira vez que liga o detector ou se vai ler os parâmetros já gravados
		}
		else if(estado == ESTADO_GET_ALIVES) //Verifica a presença dos periféricos na rede CAN e marca a presença de quem esta presente na rede
		{
			fnGetAlives(); //Verifica a presença na rede
		}
		else if(estado== ESTADO_CARREGA_VERSOES) //Carrega os números dos periféricos conectados na rede CAN
		{
			fnCarregaVersoes(); //Carrega os números dos periféricos conectados na rede CAN
		}
		else if(estado == ESTADO_LE_AREAS_DETECCAO) //Permite ler os sinais de detecção recebidos em cada área da antena RX
		{
			if(statusPGDM == 1){
				estado = ESTADO_LER_TECLAS;
			}
			else if(analiseir == SIM && entrou_na_porta == SIM) //Se analiseir é SIM e alguma pessoa entrou pelo feixe infravermelho significa que pode liberar a leitura de detecção por um tempo de 5s
			{
				if(filtroruido < 1) //Se filtro de ruido for zero significa que não é necessário fazer nenhuma amostra antes de detectar
				{
					fnLeAreasDeteccao(); //Lê áreas de detecção sem amostrar durante certo período de tempo
				}
				else
				{
					fnLeAreasDeteccaocomVelocidade(); //Lê áreas de detecção amostrando durante um certo período de tempo de 10ms a 300ms
				}
			}
			else if (analiseir == SIM && entrou_na_porta == NAO) //Se analiseir é SIM e ninguém entrou pelo feixe infravermelho então somente faz a leitura das teclas
			{
				estado = ESTADO_LER_TECLAS;
			}
			else if(analiseir == NAO) //Se analiseir é NAO, a leitura do feixe infravermelho só serve para contagem de pessoas
			{
				if(filtroruido < 1) //Se filtro de ruido for zero significa que não é necessário fazer nenhuma amostra antes de detectar
				{
					fnLeAreasDeteccao(); //Lê áreas de detecção sem amostrar durante certo período de tempo
				}
				else
				{
					fnLeAreasDeteccaocomVelocidade(); //Lê áreas de detecção amostrando durante um certo período de tempo de 10ms a 300ms
				}
			}
		}
		else if(estado == ESTADO_NAVEGA_MENU)
		{
			Navega_Menu(); //Função que executa o menu que permite escolher entre senha da gerência, técnico ou engenharia e faz a leitura das teclas
		}
		else if(estado == ESTADO_NAVEGA_MENU_FUNCOES)
		{
			Navega_Menu_Funcoes(); //Função que executa o menu que permite escolher entre as funções que permitem configurar algum parâmetro do detector
		}

		//*** MENU 1 - AJUSTES BÁSICOS ***/
		else if(estado == ESTADO_AJUSTES_BASICOS)
		{
			fnAjustesBasicos(); //Função que executa os menus abaixo
		}
		else if(estado == ESTADO_AJUSTE_MANUAL_SENSIBILIDADE)
		{
			fnAjusteManualSensibilidade(); //Função que permite ajustar a sensibilidade das áreas manualmente de 1 a 100
		}
		else if(estado == ESTADO_AJUSTE_AUTOMATICO_SENSIBILIDADE)
		{
			fnAjusteAutomaticoSensibilidade(); //Função que permite a partir de uma amostra calibrar a sensibilidade automaticamente
		}
		else if(estado == ESTADO_MODO_DE_TRAVAMENTO)
		{
			fnModoTravamento(); //Função que permite configurar o modo de travamento para somente destrava ou trava/destrava
		}
		else if(estado == ESTADO_SORTEADOR_ELETRONICO) //Se estado for ESTADO_SORTEADOR_ELETRONICO então
		{
			fnSorteadorEletronico(); //Permite entrar no menu do sorteador eletrônico e configura-lo
		}
		else if(estado == ESTADO_QUANTIDADE_SORTEADOS) //Se estado for ESTADO_QUANTIDADE_SORTEADOS então
		{
			fnQuantidadeSorteados(); // Permite o usuário definir a quantidade de sorteados entre 10 e 255
		}
		/******************************************************************************/

		// *** MENU 2 - AJUSTES AVANÇADOS ***
		else if(estado == ESTADO_AJUSTES_AVANCADOS)
		{
			fnAjustesAvancados(); //Função que executa os menus abaixo
		}
		else if(estado == ESTADO_AJUSTE_AUTOMATICO_CANAL)
		{
			fnAjusteAutomaticoCanal(); //Função que permite encontrar o melhor canal de frequência analisando o sinal das áreas e escolher o canal que apresenta menor ruido nas áreas
		}
		else if(estado == ESTADO_AJUSTE_MANUAL_CANAL)
		{
			fnAjusteManualCanal(); //Função que permite escolher entre o canal de frequência 1 e 10
		}
		else if(estado == ESTADO_SELECAO_METAIS)
		{
			fnSelecaoMetais(); //Função que permite selecionar os metais de 1 a 100 sendo 50 ambos os metais
		}
		else if(estado == ESTADO_CONFIGURA_TRAVA)
		{
			fnTrava(); //Função que permite travar a porta giratória
		}
		else if(estado == ESTADO_CONFIGURA_RELE)
		{
			fnRele(); //Função que permite energizar e desenergizar o relé quando ocorre evento de detecção de metais
		}
		else if(estado == ESTADO_CONFIGURA_CONTROLE_REMOTO)
		{
			fnControleRemoto(); //Função que permite cadastrar controles remotos e descadastrar controles remotos
		}
		else if(estado == ESTADO_CONFIGURA_INFRAVERMELHO)
		{
			fnInfravermelho(); //Função que permite calibrar os infravermelhos e incluir analiseir (detecção de metais permitida somente quando entrar na agência)
		}
		else if(estado == ESTADO_ANULA_AREAS)
		{
			fnAnulaAreas(); //Função que permite anular áreas específicas que estão com problemas de ruído
		}
		else if(estado == ESTADO_FILTRO_RUIDO)
		{
			fnFiltroRuido(); //Função que permite incluir filtro de ruido para amostrar uma detecção por um periodo de tempo de 10ms a 300ms (1 a 30). 1 x 10ms = 10ms
		}
		else if(estado == ESTADO_TRAVA_INTELIGENTE)
		{
			fnTravaInteligente(); //Função que permite acionar a trava inteligente (sistema que causa detecção quando entra na agência já pelos infravermelhos)
		}
		else if(estado == ESTADO_PORTA_AUTOMATICA)
		{
			fnSetaPortaAutomatica(); //Função que permite setar se a porta é automática
		}
		else if(estado == ESTADO_ZERAR_LOG_EVENTOS)
		{
			fnZerarLogEventos(); //Função que permite zerar a memória de log de eventos
		}
		else if(estado == ESTADO_CONFIGURACOES_DE_INTERNET)
		{
			fnConfiguraInternet(); //Permite configurar o endereço IP, a máscara de sub-rede, o endereço gateway, o dns e a porta web
		}
		else if(estado == ESTADO_DIGITE_IP || estado == ESTADO_DIGITE_MASCARA_SUB_REDE || estado == ESTADO_DIGITE_GATEWAY || estado == ESTADO_DIGITE_DNS)
		{
			fnDigiteIP(); //Permite digitar o endereço IP
		}
		else if(estado == ESTADO_DIGITE_PORTA_WEB)
		{
			fnDigitePORT(); //Permite digitar a PORT da web
		}
		else if(estado == ESTADO_ELIMINAR_FALHA_DAS_BOBINAS)
		{
			fnEliminarFalhadasBobinas(); //Permite eliminar a falha das bobinas quando alguma bobina estiver com defeito e deseja que o equipamento opere mesmo com falha em alguma bobina
		}
		else if(estado == ESTADO_OPCAO_SENSOR_CONTADOR)
		{
			fnOpcaoSensorContador(); //Permite escolher entre sensores infravermelhos frontais na coluna de entrada da porta ou sensores infravermelhos de teto tanto de entrada como saida
		}
		/******************************************************************************/

		//*** MENU 3 - AJUSTES_DO_SISTEMA ***/
		else if(estado == ESTADO_AJUSTES_DO_SISTEMA)
		{
			fnAjustesdoSistema(); //Função que executa os menus abaixo
		}
		else if(estado == ESTADO_HORA_E_DATA)
		{
			fnConfigurarDataHora(); //Função executa os dois menus abaixo
		}
		else if(estado == ESTADO_VISUALIZAR_DATA_E_HORA)
		{
			fnVisualizarDataHora(); //Função que permite visualizar a data e a hora do sistema
		}
		else if(estado == ESTADO_ALTERAR_DATA_E_HORA)
		{
			fnAlterarDataHora(); //Função que permite alterar a data e a hora do sistema
		}
		else if(estado == ESTADO_ALTERA_SENHA)
		{
			fnAlteraSenha(); //Função que permite alterar a senha da gerência ou senha do técnico
		}
		else if(estado == ESTADO_RESETAR_PADRAO_FABRICA)
		{
			fnResetarPadraoFabrica(); //Função que permite retornar aos parâmetros de configuração de fábrica
		}
		else if(estado == ESTADO_IDIOMA)
		{
			fnConfigurarIdioma(); //Função que permite alterar o idioma para português, espanhol ou inglês
		}
		/******************************************************************************/

		//*** MENU 4 - AJUSTES DE ALARME ***/
		else if(estado == ESTADO_AJUSTES_DE_ALARME)
		{
			fnAjustesdeAlarme(); //Função que executa os menus abaixo
		}
		else if(estado == ESTADO_CONFIGURA_ALARME_SONORO)
		{
			fnConfiguraAlarmeSonoro(); //Função que executa os dois menus abaixo
		}
		else if(estado == ESTADO_CONFIGURA_MSG_VOZ)
		{
			fnConfiguraMsgVoz(); //Função que executa os menus de configuração da mensagem de voz
		}
		else if(estado == ESTADO_CONFIGURA_BUZZER)
		{
			fnConfiguraBuzzer(); //Função que executa os menus de configuração do buzzer
		}
		else if(estado == ESTADO_LIG_DES_ALARME_VISUAL)
		{
			fnConfiguraLigDesAlarmeVisual(); //Função que permite ligar e desligar o alarme visual de indicação das áreas
		}
		else if(estado == ESTADO_TOM_DO_BUZZER)
		{
			fnConfiguraTomBuzzer(); //Função que permite configurar o tom do buzzer de 1 a 10
		}
		else if(estado == ESTADO_VOLUME_DO_BUZZER)
		{
			fnConfiguraVolumeBuzzer(); //Função que permite configurar o volume do buzzer de 0 a 10, sendo zero desligado
		}
		else if(estado == ESTADO_VOLUME_MSG_VOZ)
		{
			fnConfiguraVolumeMsgVoz(); //Função que permite configurar o volume da mensagem de voz de 0 a 10, sendo zero desligado
		}
		/******************************************************************************/

		/*** MENU 5 - INFORMAÇÕES DO SISTEMA ***/
		else if(estado == ESTADO_INFORMACOES_DO_SISTEMA)
		{
			fnInformacoesdoSistema(); //Função que executa os menus abaixo
		}
		else if(estado == ESTADO_CONTADOR_DETECCOES)
		{
			fnContadorDeteccoes(); //Função que executa os três menus abaixo
		}
		else if(estado == ESTADO_TOTAL_BLOQUEIOS)
		{
			fnTotalBloqueios(); //Função que permite ver o total de bloqueios ocorridos por painel ou por controle remoto ou por detecção de metais
		}
		else if(estado == ESTADO_TOTAL_DESBLOQUEIOS)
		{
			fnTotalDesbloqueios(); //Função que permite ver o total de desbloqueios ocorridos por painel ou por controle remoto
		}
		else if(estado == ESTADO_ZERA_CONTADOR_DETECCOES)
		{
			fnZeraContadorDeteccoes(); //Função que permite zerar o contador de detecções
		}
		else if(estado == ESTADO_CONTADOR_PASSAGENS)
		{
			fnContadorPassagens(); //Função que permite visualizar as contagens de entradas e saidas, total de bloqueios e desbloqueios
		}
		else if(estado == ESTADO_ENTRADAS)
		{
			fnEntradas(); //Função que permite visualizar a contagem de entradas
		}
		else if(estado == ESTADO_SAIDAS)
		{
			fnSaidas(); //Função que permite visualizar a contagem de saidas
		}
		else if(estado == ESTADO_ENTRADAS_SAIDAS)
		{
			fnEntradasSaidas(); //Função que permite visualizar o total de entradas + saidas
		}
		else if(estado == ESTADO_ZERA_CONTADOR_PASSAGENS)
		{
			fnZeraContadorPassagens(); //Função que permite zerar o contador de passagens
		}
		else if(estado == ESTADO_NUMERO_DE_SERIE)
		{
			fnNumeroSeriePainel(); //Função que mostra o número de série da placa Agata
		}
		else if(estado == ESTADO_NUMERO_DE_SERIE1)
		{
			fnNumeroSerieFonte(); //Função que mostra o número de série da placa Fonte
		}
		/******************************************************************************/

		/*** MENU 6 - INFORMAÇÕES DE ENERGIA ***/
		else if(estado == ESTADO_INFORMACOES_DE_ENERGIA)
		{
			fnInformacoesdeEnergia(); //Função que permite mostra as informações de energia do sistema como tensão AC da rede elétrica, tensões DC +5V,-15V,+15V,+24V e tensão DC das baterias
		}
		/******************************************************************************/

		/*** MENU 7 - DIAGNÓSTICO DO SISTEMA ***/
		else if(estado == ESTADO_DIAGNOSTICO_DO_SISTEMA)
		{
			fnDiagnosticodoSistema(); //Função que permite fazer um autoteste da placa como teste de leds, teste da trava, teste do buzzer, etc
		}

		/*** MENU 8 - AJUSTES TX-RX ***/
		else if(estado == ESTADO_AJUSTES_TX_RX)
		{
			fnAjustesTXRX(); //Função que executa os menus abaixo
		}
		else if(estado == ESTADO_CONFIGURA_CICLO_TRABALHO)
		{
			fnCicloTrabalho(); //Função que permite calibrar o ciclo de trabalho do PWM da TX de 1% a 100%
		}
		else if(estado == ESTADO_CONFIGURA_DEFASAGEM)
		{
			fnDefasagem(); //Função que permite regular a defasagem para que seja possível pegar mais ferro ou mais alumínio ou ambos
		}
		else if(estado == ESTADO_CONFIGURA_FREQUENCIA)
		{
			fnFrequencia(); //Função que permite regular a frequência
		}
		/******************************************************************************/

		/***************************** MENU 8 - BARGRAPH ******************************/
		else if(estado == ESTADO_MOSTRA_BARGRAPH)
		{
			fnBargraph(); //Função que permite verificar o ruido mecânico e eletromagnético pois a antena TX e RX estão conectadas
		}
		else if(estado == ESTADO_ESCREVE_BARGRAPH) //Função que serve tanto para bargraph como compatibilidade eletromagnética
		{
			fnEscreveBargraph(); //Função que escreve os astericos a medida que o ruido aumenta
		}
		/******************************************************************************/

		/****************** MENU 9 - COMPATIBILIDADE ELETROMAGNÉTICA ******************/
		else if(estado == ESTADO_MOSTRA_COMPATIBILIDADE_ELETROMAGNETICA)
		{
			fnCompatibilidadeEletromagnetica(); //Função que permite verificar o ruido eletromagnético pois somente a antena RX esta conectada
		}
		/******************************************************************************/

		/*** MENU 10 - MODELO DE ANTENA ***/
		else if(estado == ESTADO_MODELO_DE_ANTENA)
		{
			fnModeloAntena(); //Função que permite escolher o modelo de antena
		}
		/******************************************************************************/

		/*** MENU 10 - POTÊNCIOMETRO DE GANHO ***/
		else if(estado == ESTADO_POTENCIOMETRO_DE_GANHO)
		{
			fnPotenciometrodeGanho(); //Função que permite alterar o ganho dos potenciômetros digitais das áreas 1 e 2
		}
		/******************************************************************************/

		/*** MENU 11 - POTENCIÔMETRO DE SELEÇÃO DE METAIS ***/
		else if(estado == ESTADO_POTENCIOMETRO_DE_SELECAO_DE_METAIS)
		{
			fnPotenciometrodeSelecaodeMetais(); //Função que permite alterar a seleção do potenciômetro digital da área 1 e 2
		}
		/******************************************************************************/

		/*** MENU 12 - TIPO DE DETECTOR ***/
		else if(estado == ESTADO_TIPO_DETECTOR)
		{
			fnTipoDetector(); //Permite escolher o tipo de detector se 3Z ou 8Z
		}
		/******************************************************************************/

		/*** Funções do AD ***/
		else if(estado == ESTADO_LER_TECLAS)
		{
			fnLerTeclas(); //Função que faz uma leitura das teclas do painel e das teclas do controle remoto
		}
		/******************************************************************************/

		/*** Funções da SENHA ***/
		else if(estado == ESTADO_DIGITE_SENHA)
		{
			fnDigiteSenha(); //Função que permite a digitação da senha
		}
		else if(estado == ESTADO_ALTERA_SENHA)
		{
			fnAlteraSenha(); //Função que permite alterar a senha da gerência ou do técnico
		}
		else if(estado == ESTADO_CONFIRMA_SENHA)
		{
			fnConfirmaSenha(); //Função que confirma a senha que vai ser alterada
		}
		/******************************************************************************/

		else if(estado == ESTADO_RELIGA_INTERRUPCOES)
		{
			INIBE_TELAS_DE_MSG = FALSE; //Não inibe mais as telas de mensagem
			if(!FALHA_DAS_BOBINAS)
			{
				LIGA_SINALEIRA_VERDE; //Liga a sinaleira verde
				Solenoide_DisableEvent();		//Desativa evento que gera PWM solenoide
				Solenoide_Disable();			//Desativa Timer que gera o evento do PWM solenoide
				tempo_trava = 0;				//Reseta contador de tempo para ativar PWM da solenoide
				pwm_trava = 0;				//Reseta contador PWM da solenoide
				DESLIGA_RELE; 				//Desenergiza o relé
				DESLIGA_TRAVA; 				//Desenergiza a trava
			}
			travado = FALSE; //Flag travado é falso
			estado = ESTADO_LER_TECLAS; //Põe no estado para dar uma lida nas teclas do painel e teclas do controle remto
		}
		else if(estado == ESTADO_TRAVA)
		{
			fnTravaDetector(); //Função que permite travar o detector de metais
		}
		else if(estado == ESTADO_DESTRAVA && MANUTENCAO == NAO)
		{
			fnDestravaDetector(); //Função que permite destravar o detector de metais
		}
		else if(estado == ESTADO_GRAVA_CONTADOR_ENTRA)
		{
			fnGravaContadorEntra(); //Função que permite gravar na FLASH o número de pessoas que entraram após periodo de inatividade pelos sensores
		}
		else if(estado == ESTADO_GRAVA_CONTADOR_SAI)
		{
			fnGravaContadorSai(); //Função que permite gravar na FLASH o número de pessoas que sairam após periodo de inatividade pelos sensores
		}
		else if(estado == ESTADO_ESCOLHE_STATIC_DHCP)
		{
			fnEscolheSTATICouDHCP();
		}

		if(rotina_hora)
		{
			fnConfereGravaResetaContadorDiario();
			rotina_hora=FALSE;
		}
	}

	/* For example: for(;;) { } */

	/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
 ** @}
 */
/*
 ** ###################################################################
 **
 **     This file was created by Processor Expert 10.5 [05.21]
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */

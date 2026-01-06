/* ###################################################################
**     Filename    : Events.c
**     Project     : PROJETO_AGATA_04_12_2019 - REV16
**     Processor   : MK22FN1M0VLL12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 07-11-2019, 10:32, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"
#include "agata_hc_definitions.h"

#ifdef __cplusplus
extern "C" {
#endif 

volatile uint16_t tempoAvisoBurla = 0;


//
/* User includes (#include below this line is not maintained by Processor Expert) */

/*
** ===================================================================
**     Event       :  DEBOUNCING_1ms_OnInterrupt (module Events)
**
**     Component   :  DEBOUNCING_1ms [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void DEBOUNCING_1ms_OnInterrupt(void)
{
	/* Write your code here ... */
	cont_ms--; //Variável do delay de milisegundos

	time_debouncing_infra++; //Variável do debouncing dos infravermelhos
	start_remoto1++; //Variável para calcular a largura de pulso no cadastro e descadastro dos controles remotos


	/*** Trecho do controle remoto para verificar os pulsos no LED do módulo receptor remoto ***/
	if(!VT && INICIA_CONTADOR_PULSOS == FALSE) //Se o sinal VT subir para nivel lógido 1 e flag INICIA_CONTADOR_PULSOS for FALSE inicia a medição do pulso
	{
		start_remoto = 0; //Variável para armazenar o tamanho do pulso em milisegundos
		INICIA_CONTADOR_PULSOS = TRUE; //Coloca a flag INICIA_CONTADOR_PULSOS em TRUE para não inicializar novamente a medição do pulso
	}
	if(INICIA_CONTADOR_PULSOS == TRUE) //Se flag INICIA_CONTAODR_PULSOS é TRUE então incrementa star_remoto para ir medindo o pulso
	{
		start_remoto++; //Vai armazenando o tempo nesta variável
	}
	if(ACAO_CONTROLE == AVALIA_CONTROLE && pulsos > 0){
		tempoVtInativo++;
	}
	if(tempoVtInativo > 300){
		validaControle();
	}
	/******************************************************************************/

	/*** Trecho para ler o feixe de infravermelhos ***/
	if(INIBE_TELAS_DE_MSG == FALSE) //Se flag INIBE_TELAS_DE_MSG for FALSE então pode ler o feixe de infravermelhos
	{
		if(opcaosensorcontador == SENSOR_FRONTAL)
		{
			fnLeInfras(); //Função que lê os feixes de infravermelhos da coluna frontal na entrada da porta
		}
		else if(opcaosensorcontador == SENSOR_TETO)
		{
			fnLeInfrasTeto(); //Função que os sensores infravermelhos de teto de entrada e de saida
		}
	}
	/******************************************************************************/


	/*****
	 *  Colocado debounce em 10ms para economia de processamento
	 *****/

	tempo_bt++;
	time_debouncing++;//Variável do debouncing das teclas

	if(time_debouncing == FILTRO_DEBOUNCING) //Se time_debouncing atingir 10ms verifica se tecla ainda esta pressionada pois ela foi pressionada na rotina do teclado
	{
		if(DECREMENTA && tecla[0] == 1) //Se tecla decrementa ainda pressionada e realmente foi pressionada antes
		{
			teclapressionada = teclaDecrementa; //Então teclapressionada é teclaDecrementa
			tecla[0] = 2; //Apaga a informação de que a tecla ainda esta pressionada
		}
		else if(CONFIRMA && tecla[1] == 1) //Se tecla confirma ainda pressionada e realmente foi pressionada antes
		{
			teclapressionada = teclaConfirma; //Então teclapressionada é teclaConfirma
			tecla[1] = 2; //Apaga a informação de que a tecla ainda esta pressionada
		}
		else if(INCREMENTA && tecla[2] == 1) //Se tecla incrementa ainda pressionada e realmente foi pressionada antes
		{
			teclapressionada = teclaIncrementa; //Então teclapressionada é teclaIncrementa
			tecla[2] = 2; //Apaga a informação de que a tecla ainda esta pressionada
		}
		else if(CANCELA && tecla[3] == 1) //Se tecla cancela ainda pressionada e realmente foi pressionada antes
		{
			teclapressionada = teclaCancela; //Então teclapressionada é teclaCancela
			tecla[3] = 2; //Apaga a informação de que a tecla ainda esta pressionada
		}
		else if(DESTRAVA_REMOTO && tecla[4] == 1) //Se tecla destrava_remoto ainda pressionada e realmente foi pressionada antes
		{
			teclapressionada = teclaDestrava; //Então teclapressionada é teclaTrava
			tecla[4] = 2; //Apaga a informação de que a tecla ainda esta pressionada
		}
		else if(CONFIRMA_REMOTO && tecla[5] == 1) //Se tecla confirma_remoto ainda pressionada e realmente foi pressionada antes
		{
			teclapressionada = teclaAnalise; //Então teclapressionada é teclaConfirma
			tecla[5] = 2; //Apaga a informação de que a tecla ainda esta pressionada
			tempo_bt = 0;
		}
		else if(TRAVA_REMOTO && tecla[6] == 1) //Se tecla trava_remoto ainda pressionada e realmente foi pressionada antes
		{
			teclapressionada = teclaTrava; //Então teclapressionada é teclaConfirma
			tecla[6] = 0; //Apaga a informação de que a tecla ainda esta pressionada
		}
		else if(CANCELA_REMOTO && tecla[7] == 1) //Se tecla cancela_remoto ainda pressionada e realmente foi pressionada antes
		{
			teclapressionada = teclaCancela; //Então teclapressionada é teclaCancela
			tecla[7] = 0; //Apaga a informação de que a tecla ainda esta pressionada

		}
		//Se sensor indutivo foi acionado e ainda ativado e realmente foi acionado antes e nenhum dispositivo como controle ou painel efetuou o bloqueio então pode destravar a porta
		else if(SENSOR_INDUTIVO_ATIVADO && tecla[8] == 1 && controle_ou_painel_travou == NAO && travado == TRUE)
		{
			INDUTIVO_ACIONADO = SIM;
			tecla[8] = 0;
		}
		else //Senão for nenhuma tecla conhecida acima então apaga as informações de qualquer tecla pressionada pois foi ruido
		{
			tecla[0] = 0; //Apaga a informação de que a tecla ainda esta pressionada
			tecla[1] = 0; //Apaga a informação de que a tecla ainda esta pressionada
			tecla[2] = 0; //Apaga a informação de que a tecla ainda esta pressionada
			tecla[3] = 0; //Apaga a informação de que a tecla ainda esta pressionada
			tecla[4] = 0; //Apaga a informação de que a tecla ainda esta pressionada
			tecla[5] = 0; //Apaga a informação de que a tecla ainda esta pressionada
			tecla[6] = 0; //Apaga a informação de que a tecla ainda esta pressionada
			tecla[7] = 0; //Apaga a informação de que a tecla ainda esta pressionada
			tecla[8] = 0;
		}
	}
	if(teclapressionada == teclaAnalise && CONFIRMA_REMOTO){	//Verifica se o botão confirma_remoto está pressionado por mais que 2 segundos
		if(tempo_bt > 2000){
			teclapressionada = teclaCancela;	//Se estiver pressionado por mais de 2 segundos, botão confirma_remoto faz função de cancela_remoto
		}
	}else if(teclapressionada == teclaAnalise && !CONFIRMA_REMOTO){ //Se o botão for solto antes de 2 segundos, faz a função normal de confirma_remoto
		teclapressionada = teclaConfirma_Remoto;
	}

	if(INFRA1_TEMP == 1){
		infra1_timer++;
		if(infra1_timer >= 250){
			INFRA1_TEMP = 0;
			infra1_timer = 0;
		}
	}
	if(INFRA2_TEMP == 1){
		infra2_timer++;
		if(infra2_timer >= 250){
			INFRA2_TEMP = 0;
			infra2_timer = 0;
		}
	}
}

/*
** ===================================================================
**     Event       :  TEMPORIZADOR_10ms_OnInterrupt (module Events)
**
**     Component   :  TEMPORIZADOR_10ms [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TEMPORIZADOR_10ms_OnInterrupt(void)
{
	static char decrementa_char;
	static char confirma_char;
	static char incrementa_char;
	static char cancela_char;
	static char destrava_char;
	static char confirma_remoto_char;
	static char somatorio_char;


  /* Write your code here ... */
	if (INIBE_TELAS_DE_MSG == FALSE) //Se flag INIBE_TELAS_MSG for FALSE então exibe as mensagens de informações na tela do LCD
	{
	/********************** Mensagem de ANTENAS DESALINHADAS **********************/
		if (flagMonitoraAreas == 1) //Se flagMonitoraAreas for igual a 1 significa que deve ser exibida a mensagem de ANTENAS DESALINHADAS de 5 em 5s
		{
			tempo_msg++; //Incrementa a variável tempo_msg para exibir as mensagens no tempo correto
		}
		if(tempo_msg == 50) //Se tempo_msg for igual a 1 segundos
		{
			tela = TELA_INICIAL; //tela a ser apresentada é TELA_INICIAL
			estado_LCD = ATUALIZA_LCD; //estado_LCD é ATUALIZA_LCD para exibir a mensagem da TELA_INICIAL
		}
		if(tempo_msg == 100) //Se tempo_msg for igual a 2 segundos
		{
			flagMonitoraAreas = 0; //flagMonitoraAreas é igual a zero para não ciclar mais as mensagens
			tempo_msg = 0; //tempo_msg é zero para iniciar novamente a exibição alternada das mensagens
		}
	}
	if(bateria_baixa == SIM)
	{
		tela = TELA_DESLIGANDO_FONTE;
		estado_LCD = ATUALIZA_LCD;
		bateria_baixa = NAO;
	}
	if(emite_msg_manutencao == SIM)
	{
		tela = TELA_EM_MANUTENCAO;
		estado_LCD = ATUALIZA_LCD;
		emite_msg_manutencao = NAO;
	}
	/******************************************************************************/

	/*************************** Tempo para Velocidade ****************************/
	if (flagVelocidade1 == TRUE && fimLeitura1 == FALSE) //Se flagVelocidade1 da área 1 é TRUE e fimleitura1 é FALSE indica que pode contar tempo de amostra da área para verificar se dentro do período de tempo o sinal de detecção foi maior durante todos o intervalo de tempo escolhido
	{
		delta_t1++; //Incrementa delta_t1
		if(delta_t1 == filtroruido) //Se delta_t1 for igual ao intervalo de tempo definido
		{
			fimLeitura1 = TRUE; //fimLeitura1 é TRUE indicando que termina o tempo de amostra do sinal
		}
	}
	if (flagVelocidade2 == TRUE && fimLeitura2 == FALSE) //Se flagVelocidade2 da área 2 é TRUE e fimleitura2 é FALSE indica que pode contar tempo de amostra da área para verificar se dentro do período de tempo o sinal de detecção foi maior durante todos o intervalo de tempo escolhido
	{
		delta_t2++; //Incrementa delta_t2
		if(delta_t2 == filtroruido) //Se delta_t2 for igual ao intervalo de tempo definido
		{
			fimLeitura2 = TRUE; //fimLeitura2 é TRUE indicando que termina o tempo de amostra do sinal
		}
	}
	if (flagVelocidade3 == TRUE && fimLeitura3 == FALSE) //Se flagVelocidade3 da área 3 é TRUE e fimleitura3 é FALSE indica que pode contar tempo de amostra da área para verificar se dentro do período de tempo o sinal de detecção foi maior durante todos o intervalo de tempo escolhido
	{
		delta_t3++; //Incrementa delta_t3
		if(delta_t3 == filtroruido) //Se delta_t3 for igual ao intervalo de tempo definido
		{
			fimLeitura3 = TRUE; //fimLeitura3 é TRUE indicando que termina o tempo de amostra do sinal
		}
	}
	if (flagVelocidade4 == TRUE && fimLeitura4 == FALSE) //Se flagVelocidade4 da área 4 é TRUE e fimleitura4 é FALSE indica que pode contar tempo de amostra da área para verificar se dentro do período de tempo o sinal de detecção foi maior durante todos o intervalo de tempo escolhido
	{
		delta_t4++; //Incrementa delta_t4
		if(delta_t4 == filtroruido) //Se delta_t4 for igual ao intervalo de tempo definido
		{
			fimLeitura4 = TRUE; //fimLeitura4 é TRUE indicando que termina o tempo de amostra do sinal
		}
	}
	if (flagVelocidade5 == TRUE && fimLeitura5 == FALSE) //Se flagVelocidade5 da área 5 é TRUE e fimleitura5 é FALSE indica que pode contar tempo de amostra da área para verificar se dentro do período de tempo o sinal de detecção foi maior durante todos o intervalo de tempo escolhido
	{
		delta_t5++; //Incrementa delta_t5
		if(delta_t5 == filtroruido) //Se delta_t5 for igual ao intervalo de tempo definido
		{
			fimLeitura5 = TRUE; //fimLeitura5 é TRUE indicando que termina o tempo de amostra do sinal
		}
	}
	if (flagVelocidade6 == TRUE && fimLeitura6 == FALSE) //Se flagVelocidade6 da área 6 é TRUE e fimleitura6 é FALSE indica que pode contar tempo de amostra da área para verificar se dentro do período de tempo o sinal de detecção foi maior durante todos o intervalo de tempo escolhido
	{
		delta_t6++; //Incrementa delta_t6
		if(delta_t6 == filtroruido) //Se delta_t6 for igual ao intervalo de tempo definido
		{
			fimLeitura6 = TRUE; //fimLeitura6 é TRUE indicando que termina o tempo de amostra do sinal
		}
	}
	if (flagVelocidade7 == TRUE && fimLeitura7 == FALSE) //Se flagVelocidade7 da área 7 é TRUE e fimleitura7 é FALSE indica que pode contar tempo de amostra da área para verificar se dentro do período de tempo o sinal de detecção foi maior durante todos o intervalo de tempo escolhido
	{
		delta_t7++; //Incrementa delta_t7
		if(delta_t7 == filtroruido) //Se delta_t7 for igual ao intervalo de tempo definido
		{
			fimLeitura7 = TRUE; //fimLeitura7 é TRUE indicando que termina o tempo de amostra do sinal
		}
	}
	if (flagVelocidade8 == TRUE && fimLeitura8 == FALSE) //Se flagVelocidade8 da área 8 é TRUE e fimleitura8 é FALSE indica que pode contar tempo de amostra da área para verificar se dentro do período de tempo o sinal de detecção foi maior durante todos o intervalo de tempo escolhido
	{
		delta_t8++; //Incrementa delta_t8
		if(delta_t8 == filtroruido) //Se delta_t8 for igual ao intervalo de tempo definido
		{
			fimLeitura8 = TRUE; //fimLeitura8 é TRUE indicando que termina o tempo de amostra do sinal
		}
	}
	/******************************************************************************/

	/*** Atraso para acendimento correto da sinaleira ***/
	/*
	if (flagAtraso == TRUE)
	{
		tempo_sinaleira++;
		if(tempo_sinaleira == 50)
		{
			tempo_sinaleira = 0;
			fim_sinaleira = TRUE;
		}
	}
	 */
	/******************************************************************************/

	/********************** Duração de permissão de detecção **********************/
	/*
	if(analiseir == SIM && entrou == SIM) //Se analiseir é SIM e entrou é SIM então libera a detecção por 5s pois esta entrando na agência
	{
		tempo_permissao++; //Incrementa tempo_permissao
		if (tempo_permissao == 500) //Se tempo_permissao for igual a 5 segundos
		{
			entrou = NAO; //Reseta a flag entrou para NAO
			tempo_permissao = 0; //Reseta o tempo_permissao para contar novamente
		}
	}
	*/
	/******************************************************************************/



	//Adendo: caso tenha sido duas teclas pressionadas, deve ignorar as teclas
	// Obs decrementa + cancela aciona a porta inteligente, deve ignorar

	 decrementa_char = DECREMENTA;
	 confirma_char = CONFIRMA;
	 incrementa_char = INCREMENTA;
	 cancela_char = CANCELA;
	 destrava_char = DESTRAVA_REMOTO;
	 confirma_remoto_char = CONFIRMA_REMOTO;
	 somatorio_char = (unsigned char)(DECREMENTA||CONFIRMA);

	 //somatorio_char = somatorio_char + ((unsigned char)INCREMENTA+(unsigned char)CANCELA+(unsigned char)DESTRAVA_REMOTO+(unsigned char)CONFIRMA_REMOTO);

	 somatorio_char = somatorio_char + incrementa_char + cancela_char + destrava_char + confirma_remoto_char;


	if((somatorio_char)>=2){
		tecla[0] = 0; //Apaga a informação de que a tecla ainda esta pressionada
		tecla[1] = 0; //Apaga a informação de que a tecla ainda esta pressionada
		tecla[2] = 0; //Apaga a informação de que a tecla ainda esta pressionada
		tecla[3] = 0; //Apaga a informação de que a tecla ainda esta pressionada
		tecla[4] = 0; //Apaga a informação de que a tecla ainda esta pressionada
		tecla[5] = 0; //Apaga a informação de que a tecla ainda esta pressionada
		tecla[6] = 0; //Apaga a informação de que a tecla ainda esta pressionada
		tecla[7] = 0; //Apaga a informação de que a tecla ainda esta pressionada
		tecla[8] = 0;
		time_debouncing = 0;
	}
	/******************************************************************************/
}

/*
** ===================================================================
**     Event       :  TEMPORIZADOR_100ms_OnInterrupt (module Events)
**
**     Component   :  TEMPORIZADOR_100ms [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TEMPORIZADOR_100ms_OnInterrupt(void)
{
  /* Write your code here ... */
	timer_tensoes++; //Incrementa a variável timer_tensões para amostrar as tensões a cada 1 segundo
	tempo_leitura_canal++; //Incrementa a variável tempo_leitura_canal para a amostragem dos canais
	tempo_amostragem++; //Incrementa a variável tempo_amostragem para o período de autocalibração
	tempo_ativa_buzzer++;

	/************ Trecho utilizado para a rotina de delay de segundos *************/
	cont_s--; //Decrementa cont_s para o delay de segundos
	if(cont_s == 0) //Se cont_s é zero então finaliza o delay de segundos
	{
		FIM_TEMPO_DELAY_S = TRUE; //Seta a flag FIM_TEMPO_DELAY_S para TRUE indicando o fim do tempo do delay de segundos
	}
	/******************************************************************************/

	/**** Trecho utilizado para dar o pulso especificado na TRAVA ****/
	if(HABILITA_TEMPO_PULSO_TRAVA == TRUE) //Se HABILITA_TEMPO_PULSO_TRAVA for TRUE então começa a contar o tempo após ativação da trava
	{
		tempo_pulso_trava++; //Incrementa tempo_pulso_trava
		if(tempo_pulso_trava == pulso_trava) //Se tempo_pulso_trava for igual ao tempo definido para pulso_trava então desliga a trava e o rele
		{


			if(sinal_rele != rele_pulso) //Se sinal_rele não for igual a relé pulso segue o pulso da trava e desliga o relé ao mesmo tempo
			{
				DESLIGA_RELE; //Desliga relé
			}
			LIGA_SINALEIRA_VERDE; //Liga sinaleira verde
			APAGA_AREAS; //Apaga os leds de todas as áreas
			HABILITA_TEMPO_PULSO_TRAVA = FALSE; //Coloca a flag HABILITA_TEMPO_PULSO_TRAVA para FALSE para não entrar nesta rotina de novo
			travado = FALSE; //Coloca a flag travado em FALSE para saber que esta destravada a porta
			flag_area_detectada = 0;		//Reseta as areas que foram detectadas
			Solenoide_DisableEvent();		//Desativa evento que gera PWM solenoide
			Solenoide_Disable();			//Desativa Timer que gera o evento do PWM solenoide
			tempo_trava = 0;				//Reseta contador de tempo para ativar PWM da solenoide
			pwm_trava = 0;					//Reseta contador PWM da solenoide
			DESLIGA_TRAVA;					//Desliga a trava
			ACENDE_NIVEL0;					//Apaga Bargrapha
		}
	}
	/******************************************************************************/

	/**** Trecho utilizado para dar o pulso especificado no RELE *****/
	if(HABILITA_TEMPO_PULSO_RELE == TRUE) //Se HABILITA_TEMPO_PULSO_TRAVA for TRUE então começa a contar o tempo após ativação da trava
	{
		tempo_pulso_rele++; //Incrementa tempo_pulso_rele
		if(tempo_pulso_rele == pulso_rele) //Se tempo_pulso_rele for igual ao tempo definido para pulso_rele então desliga o rele
		{
			DESLIGA_RELE; //Desliga relé
			HABILITA_TEMPO_PULSO_RELE = FALSE; //Coloca a flag HABILITA_TEMPO_PULSO_RELE para FALSE para não entrar nesta rotina de novo
		}
	}
	/******************************************************************************/

    //Trecho utilizado para contar um tempo e gravar os desbloqueios somente quando passar 2s sem atividade das teclas incrementa e decremeta para travar e destravar
	if(INICIA_TIME_OUT_CONTADOR_BLOQUEIOS_DESBLOQUEIOS == TRUE) //Se INICIA_TIME_OUT_CONTADOR_BLOQUEIOS_DESBLOQUEIOS for TRUE então começa a contar o tempo
	{
		time_out_contador++; //Incrementa time_out_contador
		if(time_out_contador > 20) //Se time_out_contador for maior que 2s então permite gravar BLOQUEIOS e DESBLOQUEIOS
		{
			estado_CONTADOR_BLOQ_DESB = ESTADO_GRAVA_CONTADOR_BLOQUEIOS_DESBLOQUEIOS; //estado_CONTADOR_BLOQ_DESB vai para ESTADO_GRAVA_CONTADOR_BLOQUEIOS_DESBLOQUEIOS
			INICIA_TIME_OUT_CONTADOR_BLOQUEIOS_DESBLOQUEIOS = FALSE; //INICIA_TIME_OUT_CONTADOR_BLOQUEIOS_DESBLOQUEIOS vai para FALSE para não contar mais o tempo
		}
	}
	/******************************************************************************/

	/*** Trecho para apagar o LED referente a bateria ***/
	if(PISCA_LED_BAT == TRUE) //Se flag PISCA_LED_BAT for TRUE então começa a piscar o LED correspondente
	{
		if((GPIO_PDD_GetPortDataOutput(PORTE_DEVICE) & 0x00000080) == 0x00000000) //Se LED apagado
		{
			LIGA_BAT; //então liga o LED
		}
		else //senão
		{
			DESLIGA_BAT; //desliga o LED
		}
	}
	/******************************************************************************/

	/*** Trecho para ativar ou desativar a trava inteligente mediante o pressionamento da tecla DECREMENTA e CANCELA ao mesmo tempo por 5 segundos ***/
	if(!INCREMENTA && DECREMENTA && CANCELA && INICIA_TEMPO_TRAVA_INTELIGENTE == FALSE) //Se incrementa não estiver pressionada e decrementa e cancela estiver pressionada e flag INICIA_TEMPO_TRAVA_INTELIGENTE for FALSE então
	{
		tempo_trava_inteligente = 0; //zera contador de tempo da trava inteligente
		INICIA_TEMPO_TRAVA_INTELIGENTE = TRUE; //Torna a flag INICIA_TEMPO_TRAVA_INTELIGENTE para TRUE para poder iniciar a contagem de tempo
	}
	else if((!(DECREMENTA && CANCELA)) && INICIA_TEMPO_TRAVA_INTELIGENTE == TRUE) //Se decrementa e cancela parar de ser pressionada e INICIA_TEMPO_TRAVA_INTELIGENTE for TRUE então
	{
		INICIA_TEMPO_TRAVA_INTELIGENTE = FALSE; //Torna a flag INICIA_TEMPO_TRAVA_INTELIGENTE para FALSE para não contar mais tempo
	}
	if(INICIA_TEMPO_TRAVA_INTELIGENTE == TRUE) //Se flag INICIA_TEMPO_TRAVA_INTELIGENTE for TRUE e tecla DECREMENTA e CANCELA pressionada então continua contando tempo
	{
		tempo_trava_inteligente++; //Incrementa tempo_trava_inteligente
		if(tempo_trava_inteligente == 20) //Se tempo_trava_inteligente atingir 5 segundos então
		{
			if(trava_inteligente == NAO) //Se trava_inteligente for NÃO, ativa trava_inteligente
			{
				trava_inteligente = SIM; //trava inteligente torna-se habilitada e o detector trava somente quando passa pelos feixes de infravermelhos no sentido rua-agência.
				tempo_trava_inteligente = 0; //zera tempo_trava_inteligente
				INICIA_TEMPO_TRAVA_INTELIGENTE = FALSE; //Torna flag INICIA_TEMPO_TRAVA_INTELIGENTE para FALSE
				tela = TELA_TRAVA_INTELIGENTE_ATIVADA; //tela = TELA_TRAVA_INTELIGENTE_ATIVADA
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD com a mensagem de TRAVA INTELIGENTE ATIVADA
			}
			else if(trava_inteligente == SIM) // Se trava inteligente for SIM, desativa trava_inteligente
			{
				trava_inteligente = NAO; //trava inteligente torna-se desabilitada e o detector esta liberado para detecção sem obedecer aos feixes de infravermelhos
				tempo_trava_inteligente = 0; //zera tempo_trava_inteligente
				INICIA_TEMPO_TRAVA_INTELIGENTE = FALSE; //Torna flag INICIA_TEMPO_TRAVA_INTELIGENTE para FALSE
				tela = TELA_TRAVA_INTELIGENTE_DESATIVADA; //tela = TELA_TRAVA_INTELIGENTE_DESATIVADA
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD com a mensagem de TRAVA INTELIGENTE DESATIVADA
			}
		}
	}
	/******************************************************************************/

	/*** Trecho para ativar ou desativar a trava inteligente mediante o pressionamento da tecla DECREMENTA e CANCELA ao mesmo tempo por 5 segundos ***/
	if(INCREMENTA && !DECREMENTA && CANCELA && INICIA_TEMPO_NUMERO_SERIE == FALSE) //Se decrementa não estiver pressionada e incrementa e cancela estiver pressionada e flag INICIA_TEMPO_NUMERO_SERIE for FALSE então
	{
		tempo_numero_serie = 0; //zera contador de tempo de numero de serie
		INICIA_TEMPO_NUMERO_SERIE = TRUE; //Torna a flag INICIA_TEMPO_NUMERO_SERIE para TRUE para poder iniciar a contagem de tempo
	}
	else if((!(INCREMENTA && CANCELA)) && INICIA_TEMPO_NUMERO_SERIE == TRUE) //Se incrementa e cancela parar de ser pressionada e INICIA_TEMPO_NUMERO_SERIE for TRUE então
	{
		INICIA_TEMPO_NUMERO_SERIE = FALSE; //Torna a flag INICIA_TEMPO_NUMERO_SERIE para FALSE para não contar mais tempo
	}
	if(INICIA_TEMPO_NUMERO_SERIE == TRUE) //Se flag INICIA_TEMPO_NUMERO_SERIE for TRUE e tecla INCREMENTA e CANCELA pressionada então continua contando tempo
	{
		tempo_numero_serie++; //Incrementa tempo_numero_serie
		if(tempo_numero_serie == 50) //Se tempo_numero_serie atingir 5 segundos então
		{
			tempo_numero_serie = 0; //zera tempo_numero_serie
			INICIA_TEMPO_NUMERO_SERIE = FALSE; //Torna flag INICIA_TEMPO_NUMERO_SERIE para FALSE
			if(tipo_detector == Z8){
				tipo_detector = Z3;
				Write_Buffer_FLASH[0] = tipo_detector;
				ESCREVE_FLASH_INTERNA(endFLASHTipoDetector,1,0);
			}
			if(tipo_detector == Z3){
				tipo_detector = Z8;
				Write_Buffer_FLASH[0] = tipo_detector;
				ESCREVE_FLASH_INTERNA(endFLASHTipoDetector,1,0);
			}
//			tela = TELA_MOSTRA_NUMERO_DE_SERIE_PAINEL; //tela = TELA_MOSTRA_NUMERO_SERIE
//			flag_numero_serie = TRUE;
			estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD com a mensagem de MOSTRA_NUMERO_SERIE
		}
	}
	/**************************************************************************/

	/*** Trecho para ativar a mensagem de voz ***/
	if(INICIA_TEMPO_MSG_VOZ == TRUE) //Se INICIA_TEMPO_MSG_VOZ for TRUE então
	{
		tempo_msg_voz++; //Incrementa tempo_msg_voz
		if(tempo_msg_voz == 50) //Se atingir 5 segundos então
		{
			tempo_msg_voz = 0; //zera tempo_msg_voz
			INICIA_TEMPO_MSG_VOZ = FALSE; //Torna a flag INICIA_TEMPO_MSG_VOZ para FALSE para não contar tempo
			if(FLAG_PLACA_OUT_2022){
				SINAL_MSG_CLEAR;		//NOTA: Na placa de 2022 o sinal para acionamento da voz esta invertido
			}	else{
				SINAL_MSG_SET; //Desliga a mensagem de voz
			}
		}
	}
	/******************************************************************************/

	/*** Duração de permissão de detecção ***/
	if(analiseir == SIM && entrou_na_porta == SIM) //Se analiseir for SIM e alguma pessoa entou na agência então libera a detecção de metais por 5 segundos
	{
		tempo_permissao++; //Incrementa tempo_permissão
		if (tempo_permissao == 25) //Se tempo_permissão for 2,5 segundos então
		{
			entrou_na_porta = NAO; //Torna a flag entrou para NAO para evitar liberar a detecção novamente
			tempo_permissao = 0; //Zera a flag tempo_permissão
			APAGA_BARGRAPH = TRUE;
			AcendeBargraph();
		}
	}
	/******************************************************************************/



	/*** Tempo de 2s entre envio de informações ***/
	if(INICIA_TIME_OUT_USB_SERIAL == TRUE) //Se INICIA_TIME_OUT_USB_SERIAL for TRUE então
	{
		tempo_time_out_serial++; //Incrementa tempo_time_out_serial
		if(tempo_time_out_serial == 20) //Se atingir 2 segundos então
		{
			tempo_time_out_serial = 0; //zera tempo_time_out_serial
			INICIA_TIME_OUT_USB_SERIAL = FALSE; //Torna a flag INICIA_TIME_OUT_USB_SERIAL para FALSE para não contar tempo
			FIM_LOG_EVENTOS = TRUE; //Indica para finalizar a transmissão de log de eventos por não houve mais requisição dentro de 2 segundos
		}
	}
}

/*
** ===================================================================
**     Event       :  TEMPORIZADOR_1s_OnInterrupt (module Events)
**
**     Component   :  TEMPORIZADOR_1s [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TEMPORIZADOR_1s_OnInterrupt(void)
{
  /* Write your code here ... */
	tempo_contador_hora++;
//	timeout_can++; //Incrementa timout_can
	var_Tempo_Presenca++; //Incrementa var_Tempo_Presenca
	tempo_leitura_tensoes++; //Incrementa tempo_leitura_tensoes
	tempo_leitura_botao_prog++; //Incrementa tempo_leitura_botao_prog
	tempo_cadastro_controle++; //Incrementa tempo_cadastro_controle
	/*** Tempo de 2s entre envio de informações ***/
	if(!DataFrameTxFlg){
		timeout_can++;
	}

	if(ERRO_CAN == TRUE){
		tempo_tela_erro++;
	}

	if(INICIA_TEMPO_ENVIO_ETHERNET == TRUE && modo_operacao_ethernet == MODO_NORMAL) //Se INICIA_TEMPO_MSG_VOZ for TRUE então
	{
		tempo_envio_ethernet++; //Incrementa tempo_msg_voz
		if(tempo_envio_ethernet == 30) //Se atingir 5 minutos então
		{
			tempo_envio_ethernet = 0; //zera tempo_msg_voz
			INICIA_TEMPO_ENVIO_ETHERNET = FALSE; //Torna a flag INICIA_TEMPO_MSG_VOZ para FALSE para não contar tempo
			estado_ENVIA_SERIAL_ETHERNET = ESTADO_ENVIAR;
		}
	}
	if(INICIA_TIME_OUT_ETHERNET == SIM)
	{
		time_out_ethernet++;
		if(time_out_ethernet > 45);
		{
			FIM_TIME_OUT_ETHERNET = SIM;
		}
	}
	if(tempo_contador_hora>=3600){
		rotina_hora=TRUE;
		tempo_contador_hora=0;
	}
	if(travado == TRUE){
		tempo_trava++;
		if(tempo_trava >= 10){
			Solenoide_EnableEvent();
			Solenoide_Enable();
			tempo_trava = 10;
		}
	}

}

void PORT_A(void)
{
	//Devido ao fato de existir problema nos componentes do KDS olhar o endereço da porta no MK22F12.h, procurar por PORT_MemMapPtr, desta forma zera as interrupções
	((PORTA_BASE_PTR)->ISFR) = (uint32_t)(PORT_PDD_PIN_11 | PORT_PDD_PIN_14 | PORT_PDD_PIN_17 | PORT_PDD_PIN_24 | PORT_PDD_PIN_25 | PORT_PDD_PIN_26 | PORT_PDD_PIN_27);

	GPIO_PDD_GetPortDataInput(PORTA_DEVICE); //Lê as variações nas entradas do PORTA

	if(DECREMENTA) //Se tecla DECREMENTA presionada
	{
		if(tecla[0] == 0){
			tecla[0] = 1; //Sinaliza através de tecla[0] = 1 indicando que tecla foi pressionada
			time_debouncing = 0; //Zera o contador de time_debouncing para analisar se foi ruido na tecla
		}
	}
	if(!DECREMENTA)
	{
		tecla[0] = 0;
	}
	if(CONFIRMA) //Se tecla CONFIRMA pressionada
	{
		if(tecla[1] == 0){
			tecla[1] = 1; //Sinaliza através de tecla[1] = 1 indicando que tecla foi pressionada
			time_debouncing = 0; //Zera o contador de time_debouncing para analisar se foi ruido na tecla
		}
	}
	if(!CONFIRMA){
		tecla[1] = 0;
	}
	if(INCREMENTA) //Se tecla INCREMENTA pressionada
	{
		if(tecla[2] == 0){
			tecla[2] = 1; //Sinaliza através de tecla[2] = 1 indicando que tecla foi pressionada
			time_debouncing = 0; //Zera o contador de time_debouncing para analisar se foi ruido na tecla
		}
	}
	if(!INCREMENTA){
		tecla[2] = 0;
	}
	if(CANCELA) //Se tecla CANCELA pressionada
	{
		if(tecla[3] == 0){
			tecla[3] = 1; //Sinaliza através de tecla[3] = 1 indicando que tecla foi pressionada
			time_debouncing = 0; //Zera o contador de time_debouncing para analisar se foi ruido na tecla
		}
	}
	if(!CANCELA){
		tecla[3] = 0;
	}
	if(DESTRAVA_REMOTO) //Se tecla DESTRAVA_REMOTO pressionada
	{
		if(tecla[4] == 0){
			tecla[4] = 1; //Sinaliza através de tecla[4] = 1 indicando que tecla foi pressionada
			time_debouncing = 0; //Zera o contador de time_debouncing para analisar se foi ruido na tecla
		}
	}
	if(!DESTRAVA_REMOTO){
		tecla[4] = 0;
	}
	if(CONFIRMA_REMOTO) //Se tecla CONFIRMA_REMOTO pressionada
	{
		if(tecla[5] == 0){
			tecla[5] = 1; //Sinaliza através de tecla[5] = 1 indicando que tecla foi pressionada
			time_debouncing = 0; //Zera o contador de time_debouncing para analisar se foi ruido na tecla
		}
	}
	if(!CONFIRMA_REMOTO){
		tecla[5] = 0;
	}
	if(VT) //Se sinal do LED do receptor do controle remoto for de nivel 1 para nivel 0 então
	{
		tempoVtInativo = 0;
		VALIDA_CODIGO(); //Inicia a validação do código para poder cadastrar ou descadastrar controles
	}


}

void PORT_C(void)
{
	//Devido ao fato de existir problema nos componentes do KDS olhar o endereço da porta no MK22F12.h, procurar por PORT_MemMapPtr, desta forma zera as interrupções
	((PORTC_BASE_PTR)->ISFR) = (uint32_t)(PORT_PDD_PIN_5 | PORT_PDD_PIN_6);

	GPIO_PDD_GetPortDataInput(PORTC_DEVICE); //Lê as variações nas entradas do PORTC

	if(TRAVA_REMOTO) //Se tecla TRAVA_REMOTO foi pressonada
	{
		tecla[6] = 1; //Sinaliza através de tecla[6] = 1 indicando que tecla foi pressionada
		time_debouncing = 0; //Zera o contador de time_debouncing para analisar se foi ruido na tecla
	}
	else if(CANCELA_REMOTO) //Se tecla CANCELA_REMOTO foi pressonada
	{
		tecla[7] = 1; //Sinaliza através de tecla[7] = 1 indicando que tecla foi pressionada
		time_debouncing = 0; //Zera o contador de time_debouncing para analisar se foi ruido na tecla
	}
}

void PORT_E(void)
{
	//Devido ao fato de existir problema nos componentes do KDS olhar o endereço da porta no MK22F12.h, procurar por PORT_MemMapPtr, desta forma zera as interrupções
	((PORTE_BASE_PTR)->ISFR) = (uint32_t)(PORT_PDD_PIN_26);

	GPIO_PDD_GetPortDataInput(PORTE_DEVICE); //Lê as variações nas entradas do PORTE

	if(SENSOR_INDUTIVO_ATIVADO) //Se sensor indutivo ativado
	{
		tecla[8] = 1; //Sinaliza através de tecla[8] = 1 indicando que tecla foi pressionada
		time_debouncing = 0; //Zera o contador de time_debouncing para analisar se foi ruido na tecla
	}
}

/*
** ===================================================================
**     Event       :  CAN_OnFreeTxBuffer (module Events)
**
**     Component   :  CAN [CAN_LDD]
*/
/*!
**     @brief
**         This event is called when the buffer is empty after a
**         successful transmit of a message. This event is available
**         only if method SendFrame is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
**     @param
**         BufferIdx       - Receive message buffer index.
*/
/* ===================================================================*/
void CAN_OnFreeTxBuffer(LDD_TUserData *UserDataPtr, LDD_CAN_TMBIndex BufferIdx)
{
  /* Write your code here ... */
	DataFrameTxFlg = TRUE; //Seta a flag DataFrameTxFlg indicando que a transmissão dos dados foi corretamente executada
}

/*
** ===================================================================
**     Event       :  CAN_OnFullRxBuffer (module Events)
**
**     Component   :  CAN [CAN_LDD]
*/
/*!
**     @brief
**         This event is called when the buffer is full after a
**         successful receive a message. This event is available only
**         if method ReadFrame or SetRxBufferState is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
**     @param
**         BufferIdx       - Transmit buffer index.
*/
/* ===================================================================*/
void CAN_OnFullRxBuffer(LDD_TUserData *UserDataPtr, LDD_CAN_TMBIndex BufferIdx)
{
  /* Write your code here ... */
	DataFrameRxFlg = TRUE; //Seta a flag DataFrameRxFlg indicando que a recepção dos dados foi corretamente recebida
	estado_CAN = ESTADO_TRATA_CAN; //Seta estado_CAN para ESTADO_TRATA_CAN para tratar os dados recebidos
}

/*
** ===================================================================
**     Event       :  SERIAL_ETHERNET_OnRxChar (module Events)
**
**     Component   :  SERIAL_ETHERNET [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
unsigned char visualizacaoRecebimento[255];
int indexRecebimento =0;

void SERIAL_ETHERNET_OnRxChar(void)
{
  /* Write your code here ... */
	static byte aux_dado_recebido;

	SERIAL_ETHERNET_TComData dado_recebido; //Indica que esta é a variável responsável pelos dados recebidos

	if(RECEBIMENTO_ETHERNET_EM_TRATASERIAL2 && modo_operacao_ethernet == MODO_NORMAL){
		estado_MODULO_ETHERNET = ESTADO_TRATASERIAL2;
		return;

	}
	SERIAL_ETHERNET_RecvChar(&dado_recebido); //Recebe os dados na variável dado_recebido
	visualizacaoRecebimento[indexRecebimento] = dado_recebido;
	indexRecebimento++;
	if(indexRecebimento>=254) indexRecebimento=0;
	recebendo = 1; //Armazena na variável recebendo o valor 1 para indicar que esta recebendo dados

	if(modo_operacao_ethernet == MODO_AT) //Se modo_operacao_ethernet for igual a MODO_AT então
	{
		if(dado_recebido == 'a') //Se dado_recebido for igual a 'a' significa que aceitou a entrada no modo de comandos AT
		{
			aceito = 1; //Torna aceito igual a 1 para informar que entrou no modo de comandos AT
			dado_recebido = 0; //Já faz dado recebido igual a zero para esperar próximo resultado
		}
		if(dado_recebido && !primeiro) //Se dado recebido e primeiro for igual a zero então marca o inicio da recepção de dados
		{
			primeiro = 1; //Torna primeiro igual a 1 para informar que é o primeiro byte
			byte_count = 0; //Inicia a contagem de byte_count para zero
			recebe_serial[byte_count] = dado_recebido; //Vetor recebe_serial[byte_count] é igual a dado_recebido
			byte_count++; //Incrementa byte_count
			if(byte_count > 255) //Se byte_count for maior que 69 então
			{
				byte_count = 0; //Zera variável byte_count para evitar estouro no vetor de dados
			}
		}
		else //senão
		{
			if(primeiro) //se primeiro for diferente de zero então
			{
				recebe_serial[byte_count] = dado_recebido; //Vetor recebe_serial[byte_count] é igual a dado_recebido
				byte_count++; //Incrementa byte_count
				if(byte_count > 255) //Se byte_count for maior que 69 então
				{
					byte_count = 0; //Zera variável byte_count para evitar estouro no vetor de dados
				}
			}
		}
		if(recebe_serial[0] == '+' && recebe_serial[1] == 'o' && recebe_serial[2] == 'k') //Se recebeu +ok significa que entrou no modo de comandos AT
		{
			dado_recebido = 0; //Zera a variável dado_recebido para próximos recebimentos de dados
			primeiro = 0; //Zera a variável primeiro para próximos recebimentos de dados
			byte_count = 0; //Zera a variável byte_count para próximos recebimentos de dados
			SERIAL_ETHERNET_ClearRxBuf(); //Limpa o buffer RX
			estado_MODULO_ETHERNET = ESTADO_MODO_AT_ON; //Faz estado_MODULO_ETHERNET ser igual a ESTADO_MODO_AT_ON
		}

		if(recebe_serial[0] == 0x0D && recebe_serial[1] == 0x0A && recebe_serial[2] == '+' &&
		   recebe_serial[3] == 'O' && recebe_serial[4] == 'K' && recebe_serial[5] == 0x0D && recebe_serial[6] == 0x0A) //Se for este resultado o envio das informações AT+WANN foi realizada com sucesso
		{
			dado_recebido = 0; //Zera a variável dado_recebido para poder capturar dados recebidos novamente
			primeiro = 0; //Zera a variável primeiro para poder capturar dados recebidos novamente
			byte_count = 0; //Zera a variável byte_count para poder contar os bytes recebidos novamente
			SERIAL_ETHERNET_ClearRxBuf(); //Limpa o buffer de recepção serial
			estado_MODULO_ETHERNET = ESTADO_COMANDO_OK; //Seta estado_MODULO_ETHERNET para ESTADO_COMANDO_OK para informar que comando foi executado corretamente
		}
		if(recebe_serial[0] == 0x0D && recebe_serial[1] == 0x0A && (recebe_serial[byte_count - 2] == 0x0D && recebe_serial[byte_count - 1] == 0x0A && byte_count > 5)) //Se recebeu conforme condições então
		{
			dado_recebido = 0; //Zera a variável dado_recebido para poder capturar dados recebidos novamente
			primeiro = 0; //Zera a variável primeiro para poder capturar dados recebidos novamente
			byte_count = 0; //Zera a variável byte_count para poder contar os bytes recebidos novamente
			SERIAL_ETHERNET_ClearRxBuf(); //Limpa o buffer de recepção serial
			estado_MODULO_ETHERNET = ESTADO_COMANDO_OK; //Seta estado_MODULO_ETHERNET para ESTADO_COMANDO_OK para informar que comando foi executado corretamente
		}
	}
	else if(modo_operacao_ethernet == MODO_NORMAL) //Senão se modo_operacao_ethernet for igual a MODO_NORMAL então -- ACESSO REMOTO
	{

		if(FORCAR_NAO_CONFIRMAR_RECEBIMENTO_SIMTRO){
			SERIAL_ETHERNET_ClearRxBuf(); //Limpa o buffer de recepção serial
			estado_MODULO_ETHERNET = ESTADO_TRATASERIAL2;
		}

		if(dado_recebido == '{' && !primeiro) //Se dado recebido for diferente de zero e primeiro for igual a zero então marca o inicio da recepção dos dados
		{
			primeiro = 1; //Torna primeiro igual a 1 para informar que é o primeiro byte
			byte_count = 0; //Inicia a contagem de byte_count para zero
			recebe_serial[byte_count] = dado_recebido; //Vetor recebe_serial[byte_count] é igual a dado_recebido
			byte_count++; //Incrementa byte_count
			if(byte_count > 300) //Se byte_count for maior que 69 então
			{
				primeiro = 0; //Zera variável primeiro para poder capturar dados recebidos novamente
				byte_count = 0; //Zera variável byte_count para poder contar os bytes recebidos novamente
				SERIAL_ETHERNET_ClearRxBuf(); //Limpa o buffer de recepção serial
			}
		}
		else //senão
		{
			if(primeiro) //se primeiro for diferente de zero então
			{
				recebe_serial[byte_count] = dado_recebido; //Vetor recebe_serial[byte_count] é igual a dado_recebido
				byte_count++; //Incrementa byte_count
				if(dado_recebido == '}' || byte_count > 254) //Se byte_count for maior que 69 então
				{
					primeiro = 0; //Zera variável primeiro para poder capturar dados recebidos novamente
					byte_count = 0; //Zera variável byte_count para poder contar os bytes recebidos novamente
					SERIAL_ETHERNET_ClearRxBuf(); //Limpa o buffer de recepção serial
					estado_MODULO_ETHERNET = ESTADO_TRATASERIAL2;
				}
			}
		}
	}
	else if(modo_operacao_ethernet == MODO_SERIAL)
	{
		if(dado_recebido == '#') //Se dado_recebido1 for igual a '#' então marca o inicio da recepção dos dados
			{
				primeiro = 1; //Torna primeiro1 igual a 1 para informar que é o primeiro byte
				byte_count = 0; //Inicia a contagem de byte_count1 para zero
				recebe_serial[byte_count] = dado_recebido; //Vetor recebe_serial1[byte_count] é igual a dado_recebido1
				byte_count++; //Incrementa byte_count1
			}
			else //senão
			{
				if(primeiro) //se primeiro1 for diferente de zero então
				{
					recebe_serial[byte_count] = dado_recebido; //Vetor recebe_serial1[byte_count1] é igual a dado_recebido1
					byte_count++; //Incrementa byte_count1
				}
			}
			if(recebe_serial[byte_count - 1] == '!') //Se vetor recebe_serial[byte_count - 1] for igual a '$' então é fim da mensagem e
			{
				primeiro = 0; //Zera variável primeiro1 para poder capturar dados recebidos novamente
				byte_count = 0; //Zera variável byte_count1 para poder contar os bytes recebidos novamente
				SERIAL_ETHERNET_ClearRxBuf(); //Limpa o buffer de recepção serial
				estado_MODULO_ETHERNET = ESTADO_TRATA_ETHERNET; //Seta estado_SERIAL para ESTADO_TRATA_SERIAL para poder tratar os dados recebidos
			}
	}


}

/*
** ===================================================================
**     Event       :  SERIAL_ETHERNET_OnTxChar (module Events)
**
**     Component   :  SERIAL_ETHERNET [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void SERIAL_ETHERNET_OnTxChar(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  USB_PC_OnError (module Events)
**
**     Component   :  USB_PC [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void USB_PC_OnError(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  USB_PC_OnRxChar (module Events)
**
**     Component   :  USB_PC [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void USB_PC_OnRxChar(void)
{
  /* Write your code here ... */
	USB_PC_TComData dado_recebido1; //Indica que esta é a variável responsável pelos dados recebidos

	USB_PC_RecvChar(&dado_recebido1); //Recebe caracter por caracter na variável dado_recebido1
	if(dado_recebido1 == '#') //Se dado_recebido1 for igual a '#' então marca o inicio da recepção dos dados
	{
		primeiro1 = 1; //Torna primeiro1 igual a 1 para informar que é o primeiro byte
		byte_count1 = 0; //Inicia a contagem de byte_count1 para zero
		recebe_serial1[byte_count1] = dado_recebido1; //Vetor recebe_serial1[byte_count] é igual a dado_recebido1
		byte_count1++; //Incrementa byte_count1
	}
	else //senão
	{
		if(primeiro1) //se primeiro1 for diferente de zero então
		{
			recebe_serial1[byte_count1] = dado_recebido1; //Vetor recebe_serial1[byte_count1] é igual a dado_recebido1
			byte_count1++; //Incrementa byte_count1
		}
	}
	if(recebe_serial1[byte_count1 - 1] == '!') //Se vetor recebe_serial[byte_count - 1] for igual a '!' então é fim da mensagem e
	{
		primeiro1 = 0; //Zera variável primeiro1 para poder capturar dados recebidos novamente
		byte_count1 = 0; //Zera variável byte_count1 para poder contar os bytes recebidos novamente
		USB_PC_ClearRxBuf(); //Limpa o buffer de recepção serial
		estado_SERIAL = ESTADO_TRATA_SERIAL; //Seta estado_SERIAL para ESTADO_TRATA_SERIAL para poder tratar os dados recebidos
	}
}

/*
** ===================================================================
**     Event       :  USB_PC_OnTxChar (module Events)
**
**     Component   :  USB_PC [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void USB_PC_OnTxChar(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  TENSAO_DAS_AREAS_OnEnd (module Events)
**
**     Component   :  TENSAO_DAS_AREAS [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TENSAO_DAS_AREAS_OnEnd(void)
{
  /* Write your code here ... */
	if(LENDO_AREAS1 == FALSE)
	{
		TENSAO_DAS_AREAS_GetValue16((word *)Valor1); //Captura o valor AD de tensão das áreas 1 a 8 e põe no vetor de 8 posições Valor1[]
		FlagADC1 = 1; //Torna flag FlagADC1 para 1 para indicar que houve captura do sinal no AD1
		LENDO_AREAS1 = TRUE;
	}
}

/*
** ===================================================================
**     Event       :  TENSAO_DAS_AREAS_OnCalibrationEnd (module Events)
**
**     Component   :  TENSAO_DAS_AREAS [ADC]
**     Description :
**         This event is called when the calibration has been finished.
**         User should check if the calibration pass or fail by
**         Calibration status method./nThis event is enabled only if
**         the <Interrupt service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TENSAO_DAS_AREAS_OnCalibrationEnd(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  SINAL_DAS_AREAS_OnEnd (module Events)
**
**     Component   :  SINAL_DAS_AREAS [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void SINAL_DAS_AREAS_OnEnd(void)
{
  /* Write your code here ... */
	if(LENDO_AREAS == FALSE) //Se LENDO_AREAS for FALSE não captura o sinal AD das áreas 1 a 8
	{
		SINAL_DAS_AREAS_GetValue16((word *)Valor); //Captura o valor AD de sinal de detecção das áreas 1 a 8 e põe no vetor de 8 posições Valor[]
		FlagADC = 1; //Torna flag FlagADC para 1 para indicar que houve captura do sinal no AD
		LENDO_AREAS = TRUE; //Torna flag LENDO_AREAS para TRUE para evitar nova leitura do AD, a não ser que torne a flag LENDO_AREAS para FALSE
		if(tipo_detector == Z3)
		{
			Valor[AREA4] = 0;
			Valor[AREA5] = 0;
			Valor[AREA6] = 0;
			Valor[AREA7] = 0;
			Valor[AREA8] = 0;
		}
	}
}

/*
** ===================================================================
**     Event       :  SINAL_DAS_AREAS_OnCalibrationEnd (module Events)
**
**     Component   :  SINAL_DAS_AREAS [ADC]
**     Description :
**         This event is called when the calibration has been finished.
**         User should check if the calibration pass or fail by
**         Calibration status method./nThis event is enabled only if
**         the <Interrupt service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void SINAL_DAS_AREAS_OnCalibrationEnd(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  USB_PC_OnFullRxBuf (module Events)
**
**     Component   :  USB_PC [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void USB_PC_OnFullRxBuf(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  USB_PC_OnFreeTxBuf (module Events)
**
**     Component   :  USB_PC [AsynchroSerial]
**     Description :
**         This event is called after the last character in output
**         buffer is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void USB_PC_OnFreeTxBuf(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  SERIAL_ETHERNET_OnFullRxBuf (module Events)
**
**     Component   :  SERIAL_ETHERNET [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void SERIAL_ETHERNET_OnFullRxBuf(void)
{
  /* Write your code here ... */
	volatile word quantidade;
	quantidade = SERIAL_ETHERNET_GetCharsInRxBuf();
}

/*
** ===================================================================
**     Event       :  Solenoide_OnInterrupt (module Events)
**
**     Component   :  Solenoide [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Solenoide_OnInterrupt(void)
{
  pwm_trava++;
  if(TRAVA_LIGADA){
	  estado_trava = TRUE;
  }else estado_trava = FALSE;
  if(estado_trava == TRUE && pwm_trava >= 8){
	  DESLIGA_TRAVA;
	  pwm_trava = 0;
  }else if (estado_trava == FALSE && pwm_trava >= 5){
	  LIGA_TRAVA;
	  pwm_trava = 0;
  }
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

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

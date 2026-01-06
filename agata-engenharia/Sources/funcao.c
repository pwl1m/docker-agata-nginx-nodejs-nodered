/*
 * funcao.c
 *
 *  Created on: 07/11/2019
 *      Author: Alexandre Voigt da Poian
 */

#include "funcao.h"

#include "agata_std_functions.h"
#include "agata_hc_definitions.h"
#include "stdlib.h"
#include "string.h"

#include "CAN_PDD.h"

volatile word qtdnl = 0;


/******************************************************************************/

DataHora GetData(void) //Fun��o que pega a hora e a data atual
{
	DataHora data_hora; //Define data_hora com a estrutura de DataHora
	RTC1_GetTime(MyRTCPtr, &Time); //Fun��o do processor experte que pega a hora e data atual
	data_hora.Dia = (byte)Time.Day; //Atualiza data_hora.Dia com o dia atual
	data_hora.Mes = (byte)Time.Month; //Atualiza data_hora.Mes com o m�s atual
	data_hora.Ano = (word)Time.Year; //Atualiza data_hora.Ano com o ano atual
	data_hora.Hora = (byte)Time.Hour; //Atualiza data_hora.Hora com o hora atual
	data_hora.Minuto = (byte)Time.Minute; //Atualiza data_hora.Minuto com o minuto atual
	data_hora.Segundo = (byte)Time.Second; //Atualiza data_hora.Segundo com o segundo atual
	return data_hora;
}

void fnVisualizarDataHora(void) //Permite visualizar a data e a hora do sistema
{
	static DataHora time_aux; //Vari�vel time_aux recebe a estrutura de DataHora
	static byte estadoVisualizarDataHora = 1; //Definindo a vari�vel estadoVisualizarDataHora para o switch case abaixo

	switch(estadoVisualizarDataHora) //Conforme valor da vari�vel estadoVisualizarDataHora vai para o case espec�fico
	{
		case 1: //ENTRA PARA MOSTRAR A DATA E A HORA ATUAIS
		{
			time_aux = GetData(); //A estrutura time_aux recebe as informa��es de data e hora atuais
			dataAtualizar = GetData(); //A estrutura dataAtualizar recebe os valores de data e hora atuais
			tela = TELA_ATUALIZAR_DH; //Tela � igual a TELA_ATUALIZAR_DH que coloca as informa��es de data e hora no LCD
			estado_LCD = ATUALIZA_LCD; //Atualiza o rel�gio no LCD
			estadoVisualizarDataHora = 2; //Coloca a vari�vel estadoVisualizarDataHora para 2 para ir para o case 2
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //ATUALIZA AS INFORMA��ES DE DATA E HORA CONTINUAMENTE
		{
			dataAtualizar = GetData(); //A estrutura dataAtualizar recebe os valores de data e hora atuais
			if(time_aux.Dia == dataAtualizar.Dia) //Se time_aux.Dia for igual a dataAtualizar.Dia ent�o n�o atualiza porque valor anterior � igual a valor presente
			{
				AtualizaDia = 0; //N�o atualiza
			}
			else //Sen�o
			{
				AtualizaDia = 1; //Atualiza
			}
			if(time_aux.Mes == dataAtualizar.Mes) //Se time_aux.Mes for igual a dataAtualizar.Mes ent�o n�o atualiza porque valor anterior � igual a valor presente
			{
				AtualizaMes = 0;
			}
			else
			{
				AtualizaMes = 1;
			}
			if(time_aux.Ano == dataAtualizar.Ano) //Se time_aux.Ano for igual a dataAtualizar.Ano ent�o n�o atualiza porque valor anterior � igual a valor presente
			{
				AtualizaAno = 0;
			}
			else
			{
				AtualizaAno = 1;
			}
			if(time_aux.Hora == dataAtualizar.Hora) //Se time_aux.Hora for igual a dataAtualizar.Hora ent�o n�o atualiza porque valor anterior � igual a valor presente
			{
				AtualizaHora = 0;
			}
			else
			{
				AtualizaHora = 1;
			}
			if(time_aux.Minuto == dataAtualizar.Minuto) //Se time_aux.Minuto for igual a dataAtualizar.Minuto ent�o n�o atualiza porque valor anterior � igual a valor presente
			{
				AtualizaMinuto = 0;
			}
			else
			{
				AtualizaMinuto = 1;
			}
			if(time_aux.Segundo == dataAtualizar.Segundo) //Se time_aux.Segundo for igual a dataAtualizar.Segundo ent�o n�o atualiza porque valor anterior � igual a valor presente
			{
				AtualizaSegundo = 0;
			}
			else
			{
				AtualizaSegundo = 1;
			}
			tela = TELA_VISUALIZAR_DATA_E_HORA; //Tela � igual a TELA_VISUALIZAR_DATA_E_HORA
			estado_LCD = ATUALIZA_LCD; //Atualiza o rel�gio no LCD
			time_aux = dataAtualizar; //Guarda o valor de data e hora na estrutura time_aux para ap�s um tempo comparar com nova data e hora capturadas em dataAtualizar

			if(teclapressionada) //Se alguma tecla pressionada ent�o
			{
				if(teclapressionada == teclaCancela || teclapressionada == teclaConfirma || teclapressionada == teclaConfirma_Remoto) //Se tecla CONFIRMA ou tecla CANCELA pressionada ent�o
				{
					tela = TELA_MOSTRA_OPCOES_DATA_E_HORA; //Tela � igual a TELA_MOSTRA_OPCOES_DATA_E_HORA
					estado_LCD = ATUALIZA_LCD; //Atualiza o rel�gio no LCD
					estado = ESTADO_HORA_E_DATA; //Estado a ser executado � ESTADO_HORA_E_DATA
				}
				estadoVisualizarDataHora = 1; //Coloca a vari�vel estadoVisualizarDataHora para 1 para ir para o primeiro nivel deste menu
				teclapressionada = 0; //Limpa teclapressionada
			}
			break;
		}
		break;
	}
}


/******************************************************************************/

/*** Fun��es do AD ***/
void fnLeAreasDeteccao(void) //Faz a leitura do sinal AD das �reas sem amostrar por um tempo
{
	//A vari�vel fim_sinaleira serve para que a fun��o bargraph s� funcione quando parar de ler o sinal AD das �reas
	if(FlagADC) //Faz a leitura do sinal AD das �reas sem amostrar por um tempo
	{
		//Quando anula_area for igual a zero pode executar a leitura da �rea, isto vale para qualquer �rea
		if(Valor[AREA1] >= NIVEL_ZERO && anula_area[AREA1] == 0) //Se valor do sinal da �rea 1 for maior que NIVEL_ZERO (32768) ent�o corrige valor para a faixa correta pois sinal � positivo
		{
			Valor[AREA1] = Valor[AREA1] - NIVEL_ZERO; //Valor do sinal da �rea 1 � igual ao valor lido da �rea 1 menos o valor NIVEL_ZERO (32768)
		}
		else if(Valor[AREA1] < NIVEL_ZERO && anula_area[AREA1] == 0) //Sen�o se valor do sinal da �rea 1 for menor que NIVEL_ZERO (32768) corrige valor para a faixa correta pois sinal � negativo
		{
			Valor[AREA1] = NIVEL_ZERO - Valor[AREA1]; //Valor do sinal da �rea 1 � igual ao valor NIVEL_ZERO (32768) menos o valor lido da �rea 1
		}

		if(Valor[AREA2] >= NIVEL_ZERO && anula_area[AREA2] == 0) //Se valor do sinal da �rea 2 for maior que NIVEL_ZERO (32768) ent�o corrige valor para a faixa correta pois sinal � positivo
		{
			Valor[AREA2] = Valor[AREA2] - NIVEL_ZERO; //Valor do sinal da �rea 2 � igual ao valor lido da �rea 2 menos o valor NIVEL_ZERO (32768)
		}
		else if(Valor[AREA2] < NIVEL_ZERO && anula_area[AREA2] == 0) //Sen�o se valor do sinal da �rea 2 for menor que NIVEL_ZERO (32768) corrige valor para a faixa correta pois sinal � negativo
		{
			Valor[AREA2] = NIVEL_ZERO - Valor[AREA2]; //Valor do sinal da �rea 2 � igual ao valor NIVEL_ZERO (32768) menos o valor lido da �rea 2
		}

		if(Valor[AREA3] >= NIVEL_ZERO && anula_area[AREA3] == 0) //Se valor do sinal da �rea 3 for maior que NIVEL_ZERO (32768) ent�o corrige valor para a faixa correta pois sinal � positivo
		{
			Valor[AREA3] = Valor[AREA3] - NIVEL_ZERO; //Valor do sinal da �rea 3 � igual ao valor lido da �rea 3 menos o valor NIVEL_ZERO (32768)
		}
		else if(Valor[AREA3] < NIVEL_ZERO && anula_area[AREA3] == 0) //Sen�o se valor do sinal da �rea 3 for menor que NIVEL_ZERO (32768) corrige valor para a faixa correta pois sinal � negativo
		{
			Valor[AREA3] = NIVEL_ZERO - Valor[AREA3]; //Valor do sinal da �rea 3 � igual ao valor NIVEL_ZERO (32768) menos o valor lido da �rea 3
		}

		if(tipo_detector == Z8)
		{
			if(Valor[AREA4] >= NIVEL_ZERO && anula_area[AREA4] == 0) //Se valor do sinal da �rea 4 for maior que NIVEL_ZERO (32768) ent�o corrige valor para a faixa correta pois sinal � positivo
			{
				Valor[AREA4] = Valor[AREA4] - NIVEL_ZERO; //Valor do sinal da �rea 4 � igual ao valor lido da �rea 4 menos o valor NIVEL_ZERO (32768)
			}
			else if(Valor[AREA4] < NIVEL_ZERO && anula_area[AREA4] == 0) //Sen�o se valor do sinal da �rea 4 for menor que NIVEL_ZERO (32768) corrige valor para a faixa correta pois sinal � negativo
			{
				Valor[AREA4] = NIVEL_ZERO - Valor[AREA4]; //Valor do sinal da �rea 4 � igual ao valor NIVEL_ZERO (32768) menos o valor lido da �rea 4
			}

			if(Valor[AREA5] >= NIVEL_ZERO && anula_area[AREA5] == 0) //Se valor do sinal da �rea 5 for maior que NIVEL_ZERO (32768) ent�o corrige valor para a faixa correta pois sinal � positivo
			{
				Valor[AREA5] = Valor[AREA5] - NIVEL_ZERO; //Valor do sinal da �rea 5 � igual ao valor lido da �rea 5 menos o valor NIVEL_ZERO (32768)
			}
			else if(Valor[AREA5] < NIVEL_ZERO && anula_area[AREA5] == 0) //Sen�o se valor do sinal da �rea 5 for menor que NIVEL_ZERO (32768) corrige valor para a faixa correta pois sinal � negativo
			{
				Valor[AREA5] = NIVEL_ZERO - Valor[AREA5]; //Valor do sinal da �rea 5 � igual ao valor NIVEL_ZERO (32768) menos o valor lido da �rea 5
			}

			if(Valor[AREA6] >= NIVEL_ZERO && anula_area[AREA6] == 0) //Se valor do sinal da �rea 6 for maior que NIVEL_ZERO (32768) ent�o corrige valor para a faixa correta pois sinal � positivo
			{
				Valor[AREA6] = Valor[AREA6] - NIVEL_ZERO; //Valor do sinal da �rea 6 � igual ao valor lido da �rea 6 menos o valor NIVEL_ZERO (32768)
			}
			else if(Valor[AREA6] < NIVEL_ZERO && anula_area[AREA6] == 0) //Sen�o se valor do sinal da �rea 6 for menor que NIVEL_ZERO (32768) corrige valor para a faixa correta pois sinal � negativo
			{
				Valor[AREA6] = NIVEL_ZERO - Valor[AREA6]; //Valor do sinal da �rea 6 � igual ao valor NIVEL_ZERO (32768) menos o valor lido da �rea 6
			}

			if(Valor[AREA7] >= NIVEL_ZERO && anula_area[AREA7] == 0) //Se valor do sinal da �rea 7 for maior que NIVEL_ZERO (32768) ent�o corrige valor para a faixa correta pois sinal � positivo
			{
				Valor[AREA7] = Valor[AREA7] - NIVEL_ZERO; //Valor do sinal da �rea 7 � igual ao valor lido da �rea 7 menos o valor NIVEL_ZERO (32768)
			}
			else if(Valor[AREA7] < NIVEL_ZERO && anula_area[AREA7] == 0) //Sen�o se valor do sinal da �rea 7 for menor que NIVEL_ZERO (32768) corrige valor para a faixa correta pois sinal � negativo
			{
				Valor[AREA7] = NIVEL_ZERO - Valor[AREA7]; //Valor do sinal da �rea 7 � igual ao valor NIVEL_ZERO (32768) menos o valor lido da �rea 7
			}

			if(Valor[AREA8] >= NIVEL_ZERO && anula_area[AREA8] == 0) //Se valor do sinal da �rea 8 for maior que NIVEL_ZERO (32768) ent�o corrige valor para a faixa correta pois sinal � positivo
			{
				Valor[AREA8] = Valor[AREA8] - NIVEL_ZERO; //Valor do sinal da �rea 8 � igual ao valor lido da �rea 8 menos o valor NIVEL_ZERO (32768)
			}
			else if(Valor[AREA8] < NIVEL_ZERO && anula_area[AREA8] == 0) //Sen�o se valor do sinal da �rea 8 for menor que NIVEL_ZERO (32768) corrige valor para a faixa correta pois sinal � negativo
			{
				Valor[AREA8] = NIVEL_ZERO - Valor[AREA8]; //Valor do sinal da �rea 8 � igual ao valor NIVEL_ZERO (32768) menos o valor lido da �rea 8
			}
		}

		if(anula_area[AREA1] == 1 || ((flag_area_detectada & A01) == A01) ) //Se anula_area[AREA1] for igual a 1 que significa realmente anular ent�o
		{
			Valor[AREA1] = 0; //Zera o valor da leitura de sinal do AD da �rea 1
		}
		if(anula_area[AREA2] == 1 || ((flag_area_detectada & A02) == A02) ) //Se anula_area[AREA2] for igual a 1 que significa realmente anular ent�o
		{
			Valor[AREA2] = 0; //Zera o valor da leitura de sinal do AD da �rea 2
		}
		if(anula_area[AREA3] == 1 || ((flag_area_detectada & A03) == A03) ) //Se anula_area[AREA3] for igual a 1 que significa realmente anular ent�o
		{
			Valor[AREA3] = 0; //Zera o valor da leitura de sinal do AD da �rea 3
		}
		if(tipo_detector == Z8)
		{
			if(anula_area[AREA4] == 1 || ((flag_area_detectada & A04) == A04) ) //Se anula_area[AREA4] for igual a 1 que significa realmente anular ent�o
			{
				Valor[AREA4] = 0; //Zera o valor da leitura de sinal do AD da �rea 4
			}
			if(anula_area[AREA5] == 1 || ((flag_area_detectada & A05) == A05) ) //Se anula_area[AREA5] for igual a 1 que significa realmente anular ent�o
			{
				Valor[AREA5] = 0; //Zera o valor da leitura de sinal do AD da �rea 5
			}
			if(anula_area[AREA6] == 1 || ((flag_area_detectada & A06) == A06) ) //Se anula_area[AREA6] for igual a 1 que significa realmente anular ent�o
			{
				Valor[AREA6] = 0; //Zera o valor da leitura de sinal do AD da �rea 6
			}
			if(anula_area[AREA7] == 1 || ((flag_area_detectada & A07) == A07) ) //Se anula_area[AREA7] for igual a 1 que significa realmente anular ent�o
			{
				Valor[AREA7] = 0; //Zera o valor da leitura de sinal do AD da �rea 7
			}
			if(anula_area[AREA8] == 1 || ((flag_area_detectada & A08) == A08) ) //Se anula_area[AREA8] for igual a 1 que significa realmente anular ent�o
			{
				Valor[AREA8] = 0; //Zera o valor da leitura de sinal do AD da �rea 8
			}
		}
		if ( (Valor[AREA1] >= ((NIVEL_ZERO*(101 - buffer_sensibilidade[AREA_1]))/100)) && anula_area[AREA1] == 0 && ((flag_area_detectada & A01) != A01)) //Se valor do sinal da �rea 1 for maior ou igual a sensibilidade convertida em valor correspondente AD e anula_area for zero ent�o
		{
			areas_detectadas = areas_detectadas | A01; //Armazena em �reas_detectadas que houve detec��o na �rea 1 para posteriorment acender o led da �rea correspondente
			flag_area_detectada = flag_area_detectada | A01;
			fim_sinaleira = TRUE; //Armazena na vari�vel fim_sinaleira a informa��o TRUE
		}

		if ( (Valor[AREA2] >= ((NIVEL_ZERO*(101 - buffer_sensibilidade[AREA_2]))/100)) && anula_area[AREA2] == 0 && ((flag_area_detectada & A02) != A02)) //Se valor do sinal da �rea 2 for maior ou igual a sensibilidade convertida em valor correspondente AD e anula_area for zero ent�o
		{
			areas_detectadas = areas_detectadas | A02; //Armazena em �reas_detectadas que houve detec��o na �rea 2 para posteriorment acender o led da �rea correspondente
			flag_area_detectada = flag_area_detectada | A02;
			fim_sinaleira = TRUE; //Armazena na vari�vel fim_sinaleira a informa��o TRUE
		}

		if ( (Valor[AREA3] >= ((NIVEL_ZERO*(101 - buffer_sensibilidade[AREA_3]))/100)) && anula_area[AREA3] == 0 && ((flag_area_detectada & A03) != A03)) //Se valor do sinal da �rea 3 for maior ou igual a sensibilidade convertida em valor correspondente AD e anula_area for zero ent�o
		{
			areas_detectadas = areas_detectadas | A03; //Armazena em �reas_detectadas que houve detec��o na �rea 3 para posteriorment acender o led da �rea correspondente
			flag_area_detectada = flag_area_detectada | A03;
			fim_sinaleira = TRUE; //Armazena na vari�vel fim_sinaleira a informa��o TRUE
		}

		if(tipo_detector == Z8)
		{
			if ( (Valor[AREA4] >= ((NIVEL_ZERO*(101 - buffer_sensibilidade[AREA_4]))/100)) && anula_area[AREA4] == 0 && ((flag_area_detectada & A04) != A04)) //Se valor do sinal da �rea 4 for maior ou igual a sensibilidade convertida em valor correspondente AD e anula_area for zero ent�o
			{
				areas_detectadas = areas_detectadas | A04; //Armazena em �reas_detectadas que houve detec��o na �rea 4 para posteriorment acender o led da �rea correspondente
				flag_area_detectada = flag_area_detectada | A04;
				fim_sinaleira = TRUE; //Armazena na vari�vel fim_sinaleira a informa��o TRUE
			}

			if ( (Valor[AREA5] >= ((NIVEL_ZERO*(101 - buffer_sensibilidade[AREA_5]))/100)) && anula_area[AREA5] == 0 && ((flag_area_detectada & A05) != A05)) //Se valor do sinal da �rea 5 for maior ou igual a sensibilidade convertida em valor correspondente AD e anula_area for zero ent�o
			{
				areas_detectadas = areas_detectadas | A05; //Armazena em �reas_detectadas que houve detec��o na �rea 5 para posteriorment acender o led da �rea correspondente
				flag_area_detectada = flag_area_detectada | A05;
				fim_sinaleira = TRUE; //Armazena na vari�vel fim_sinaleira a informa��o TRUE
			}

			if ( (Valor[AREA6] >= ((NIVEL_ZERO*(101 - buffer_sensibilidade[AREA_6]))/100)) && anula_area[AREA6] == 0 && ((flag_area_detectada & A06) != A06)) //Se valor do sinal da �rea 6 for maior ou igual a sensibilidade convertida em valor correspondente AD e anula_area for zero ent�o
			{
				areas_detectadas = areas_detectadas | A06; //Armazena em �reas_detectadas que houve detec��o na �rea 6 para posteriorment acender o led da �rea correspondente
				flag_area_detectada = flag_area_detectada | A06;
				fim_sinaleira = TRUE; //Armazena na vari�vel fim_sinaleira a informa��o TRUE
			}

			if ( (Valor[AREA7] >= ((NIVEL_ZERO*(101 - buffer_sensibilidade[AREA_7]))/100)) && anula_area[AREA7] == 0 && ((flag_area_detectada & A07) != A07)) //Se valor do sinal da �rea 7 for maior ou igual a sensibilidade convertida em valor correspondente AD e anula_area for zero ent�o
			{
				areas_detectadas = areas_detectadas | A07; //Armazena em �reas_detectadas que houve detec��o na �rea 7 para posteriorment acender o led da �rea correspondente
				flag_area_detectada = flag_area_detectada | A07;
				fim_sinaleira = TRUE; //Armazena na vari�vel fim_sinaleira a informa��o TRUE
			}

			if ( (Valor[AREA8] >= ((NIVEL_ZERO*(101 - buffer_sensibilidade[AREA_8]))/100)) && anula_area[AREA8] == 0 && ((flag_area_detectada & A08) != A08)) //Se valor do sinal da �rea 8 for maior ou igual a sensibilidade convertida em valor correspondente AD e anula_area for zero ent�o
			{
				areas_detectadas = areas_detectadas | A08; //Armazena em �reas_detectadas que houve detec��o na �rea 8 para posteriorment acender o led da �rea correspondente
				flag_area_detectada = flag_area_detectada | A08;
				fim_sinaleira = TRUE; //Armazena na vari�vel fim_sinaleira a informa��o TRUE
			}
		}

		AcendeBargraph(); //Acende a quantidade de n�veis de led de acordo com o valor de detec��o da �rea de maior valor

		if(areas_detectadas != 0x00) //Se areas_detectadas n�o for igual a 00 ent�o
		{
			if(travado == FALSE) //Se travado for igual a FALSE ent�o
			{
				APAGA_AREAS; //Apaga os leds das �reas
			}
			if(sinal_trava == trava_pulso) //Se sinal_trava for igual a trava_pulso ent�o
			{
				fnLigaPulsoTrava(); //Permite pulsar a trava
			}
			else if(sinal_trava == trava_retencao_controle || sinal_trava == trava_retencao_controle_teclado) //Sen�o se sinal_trava for igual a trava_retencao_controle ou sinal_trava for igual a trava_retencao_controle_teclado ent�o
			{
				LIGA_TRAVA; //Energiza a trava
				if(sinal_rele == rele_pulso) //Se sinal_rele for igual a rele_pulso ent�o
				{
					fnLigaPulsoRele(); //Permite pulsar o rel�
				}
				else //Sen�o
				{
					LIGA_RELE; //Energiza o rel�
				}
				LIGA_SINALEIRA_VERMELHA; //Liga a sinaleira vermelha
				fnReproduzMsgVoz(DETECCAO); //Fun��o que reproduz a mensagem de voz
			}

			fim_sinaleira = FALSE; //Armazena na vari�vel fim_sinaleira a informa��o FALSE

			AcendeBargraph(); //Acende a quantidade de n�veis de led de acordo com o valor de detec��o da �rea de maior valor

			if(AREA01_DETECTADA && alarme_visual == NAO) //Se �rea 1 detectada e alarme_visual for igual a NAO ent�o
			{
				if(tipo_detector == Z3) //Se tipo de detector for 3 zonas ent�o
				{
					ACENDE_AREA1; //Acende o led da �rea 1
					ACENDE_AREA2; //Acende o led da �rea 2
				}
				else if(tipo_detector == Z8) //Sen�o se tipo de detector for 8 zonas ent�o
				{
					ACENDE_AREA1; //Acende o led da �rea 1
				}
			}
			if(AREA02_DETECTADA && alarme_visual == NAO) //Se �rea 2 detectada e alarme_visual for igual a NAO ent�o
			{
				if(tipo_detector == Z3) //Se tipo de detector for 3 zonas ent�o
				{
					ACENDE_AREA4; //Acende o led da �rea 4
					ACENDE_AREA5; //Acende o led da �rea 5
				}
				else if(tipo_detector == Z8) //Sen�o se tipo de detector for 8 zonas ent�o
				{
					ACENDE_AREA2; //Acende o led da �rea 2
				}
			}
			if(AREA03_DETECTADA && alarme_visual == NAO) //Se �rea 3 detectada e alarme_visual for igual a NAO ent�o
			{
				if(tipo_detector == Z3) //Se tipo de detector for 3 zonas ent�o
				{
					ACENDE_AREA7; //Acende o led da �rea 7
					ACENDE_AREA8; //Acende o led da �rea 8
				}
				else if(tipo_detector == Z8) //Sen�o se tipo de detector for 8 zonas ent�o
				{
					ACENDE_AREA3; //Acende o led da �rea 3
				}
			}
			if(tipo_detector == Z8)
			{
				if(AREA04_DETECTADA && alarme_visual == NAO) //Se �rea 4 detectada e alarme_visual for igual a NAO ent�o
				{
					ACENDE_AREA4; //Acende o led da �rea 4
				}
				if(AREA05_DETECTADA && alarme_visual == NAO) //Se �rea 5 detectada e alarme_visual for igual a NAO ent�o
				{
					ACENDE_AREA5; //Acende o led da �rea 5
				}
				if(AREA06_DETECTADA && alarme_visual == NAO) //Se �rea 6 detectada e alarme_visual for igual a NAO ent�o
				{
					ACENDE_AREA6; //Acende o led da �rea 6
				}
				if(AREA07_DETECTADA && alarme_visual == NAO) //Se �rea 7 detectada e alarme_visual for igual a NAO ent�o
				{
					ACENDE_AREA7; //Acende o led da �rea 7
				}
				if(AREA08_DETECTADA && alarme_visual == NAO) //Se �rea 8 detectada e alarme_visual for igual a NAO ent�o
				{
					ACENDE_AREA8; //Acende o led da �rea 8
				}
			}

			TocaTomBuzzer(); //Toca tom do buzzer

			if(travado == FALSE) //Se travado for igual a FALSE ent�o
			{
				contador_bloqueios++; //Incrementa contador de bloqueios
				Write_Buffer_FLASH[0] = (byte)(contador_bloqueios >> 24); //Escreve o valor do quarto byte mais alto no vetor para grava��o na mem�ria FLASH
				Write_Buffer_FLASH[1] = (byte)(contador_bloqueios >> 16); //Escreve o valor do teceiro byte mais alto no vetor para grava��o na mem�ria FLASH
				Write_Buffer_FLASH[2] = (byte)(contador_bloqueios >> 8); //Escreve o valor do segundo byte mais alto no vetor para grava��o na mem�ria FLASH
				Write_Buffer_FLASH[3] = (byte)(contador_bloqueios); //Escreve o valor do primeiro byte mais alto no vetor para grava��o na mem�ria FLASH
				ESCREVE_FLASH_INTERNA(endFLASHTotalBloqueios,4,0); //Escreve na mem�ria FLASH as sele��es de metais dos potenciometros alterados no endere�o especificado
				fnGravaEvento(GRAVA_BLOQUE,GRAVA_DETECT); //Fun��o que grava os eventos de bloqueios e desbloqueios realizados por painel, controle remoto ou detec��o de metais
				travado = TRUE; //Armazena na vari�vel travado a informa��o TRUE para informar que a porta girat�ria esta travada
			}
		}

		areas_detectadas = 0x00; //Zera a vari�vel que informa as �reas detectadas

		//Se o valor do sinal AD lido de qualquer �rea for menor que o limite permitido de sinal para �rea ent�o
		if(!eliminar_falha)
		{
			LENDO_AREAS1 = FALSE;
			if ( (Valor1[AREA1] < 200) || (Valor1[AREA2] < 200) || (Valor1[AREA3] < 200) || (Valor1[AREA4] < 200) ||
			     (Valor1[AREA5] < 200) || (Valor1[AREA6] < 200) || (Valor1[AREA7] < 200) || (Valor1[AREA8] < 200) )
			{
				if (flagMonitoraAreas == 0) //Se flagMonitoraAreas for igual a zero ent�o
				{
					tempo_msg = 0; //Armazena na vari�vel tempo_msg o valor zero
					flagMonitoraAreas = 1; //Armazena na vari�vel flagMonitoraAreas o valor 1 para poder emitir a mensagem sem sinal nas antenas
					tela = TELA_SEM_SINAL_NAS_ANTENAS; //Tela � igual a TELA_SEM_SINAL_NAS_ANTENAS
					estado_LCD = ATUALIZA_LCD;  //Atualiza o LCD com a tela acima
					LIGA_TRAVA; //Energiza a trava
					LIGA_SINALEIRA_VERMELHA; //Liga a sinaleira vermelha
					FALHA_DAS_BOBINAS = TRUE;
					travado = TRUE;
				}
				flag_antena_rx_sem_sinal = TRUE; //Armazena na flag_antena_rx_sem_sinal a informa��o TRUE
				LENDO_AREAS1 = FALSE;

			}
			//Sen�o se o valor do sinal AD lido de cada �rea for maior que o sinal limite permitido de sinal para �rea ent�o
			else if ( (Valor1[AREA1] > 200 && Valor1[AREA2] > 200) && (Valor1[AREA3] > 200 && Valor1[AREA4] > 200) &&
					  (Valor1[AREA5] > 200 && Valor1[AREA6] > 200) && (Valor1[AREA7] > 200 && Valor1[AREA8] > 200)
					  && flag_antena_rx_sem_sinal != FALSE)	//Adicionado flag para evitar repeticao
			{
				flagMonitoraAreas = 0;
				flag_antena_rx_sem_sinal = FALSE;  //Armazena na flag_antena_rx_sem_sinal a informa��o FALSE
				LENDO_AREAS1 = FALSE;

				LIGA_SINALEIRA_VERDE; //Liga a sinaleira vermelha
				FALHA_DAS_BOBINAS = FALSE;
				travado = FALSE;
				Solenoide_DisableEvent();		//Desativa evento que gera PWM solenoide
				Solenoide_Disable();			//Desativa Timer que gera o evento do PWM solenoide
				tempo_trava = 0;				//Reseta contador de tempo para ativar PWM da solenoide
				pwm_trava = 0;					//Reseta contador PWM da solenoide
				DESLIGA_TRAVA;					//Desenergiza a trava
			}
		}
		FlagADC = 0; //Zera a flag FlagADC para realizar novas leituras no AD
		LENDO_AREAS = FALSE; //Armazena na vari�vel LENDO_AREAS a informa��o FALSE para poder habilitar a realiza��o de novas leituras no AD
	}
	estado = ESTADO_LER_TECLAS; //Estado a ser executado � ESTADO_LER_TECLAS
}

void fnLeAreasDeteccaocomVelocidade(void) //Faz a leitura do sinal AD das �reas amostrando por um tempo de 10ms a 300ms conforme valor do filtro (1 x 10ms = 10ms)
{
	if(FlagADC) //Se FlagADC for igual a 1 ent�o
	{
		//Quando anula_area for igual a zero pode executar a leitura da �rea, isto vale para qualquer �rea
		if(Valor[AREA1] >= NIVEL_ZERO && anula_area[AREA1] == 0) //Se valor do sinal da �rea 1 for maior que NIVEL_ZERO (32768) ent�o corrige valor para a faixa correta pois sinal � positivo
		{
			Valor[AREA1] = Valor[AREA1] - NIVEL_ZERO; //Valor do sinal da �rea 1 � igual ao valor lido da �rea 1 menos o valor NIVEL_ZERO (32768)
		}
		else if(Valor[AREA1] < NIVEL_ZERO && anula_area[AREA1] == 0) //Sen�o se valor do sinal da �rea 1 for menor que NIVEL_ZERO (32768) corrige valor para a faixa correta pois sinal � negativo
		{
			Valor[AREA1] = NIVEL_ZERO - Valor[AREA1]; //Valor do sinal da �rea 1 � igual ao valor NIVEL_ZERO (32768) menos o valor lido da �rea 1
		}

		if(Valor[AREA2] >= NIVEL_ZERO && anula_area[AREA2] == 0) //Se valor do sinal da �rea 2 for maior que NIVEL_ZERO (32768) ent�o corrige valor para a faixa correta pois sinal � positivo
		{
			Valor[AREA2] = Valor[AREA2] - NIVEL_ZERO; //Valor do sinal da �rea 2 � igual ao valor lido da �rea 2 menos o valor NIVEL_ZERO (32768)
		}
		else if(Valor[AREA2] < NIVEL_ZERO && anula_area[AREA2] == 0) //Sen�o se valor do sinal da �rea 2 for menor que NIVEL_ZERO (32768) corrige valor para a faixa correta pois sinal � negativo
		{
			Valor[AREA2] = NIVEL_ZERO - Valor[AREA2]; //Valor do sinal da �rea 2 � igual ao valor NIVEL_ZERO (32768) menos o valor lido da �rea 2
		}

		if(Valor[AREA3] >= NIVEL_ZERO && anula_area[AREA3] == 0) //Se valor do sinal da �rea 3 for maior que NIVEL_ZERO (32768) ent�o corrige valor para a faixa correta pois sinal � positivo
		{
			Valor[AREA3] = Valor[AREA3] - NIVEL_ZERO; //Valor do sinal da �rea 3 � igual ao valor lido da �rea 3 menos o valor NIVEL_ZERO (32768)
		}
		else if(Valor[AREA3] < NIVEL_ZERO && anula_area[AREA3] == 0) //Sen�o se valor do sinal da �rea 3 for menor que NIVEL_ZERO (32768) corrige valor para a faixa correta pois sinal � negativo
		{
			Valor[AREA3] = NIVEL_ZERO - Valor[AREA3]; //Valor do sinal da �rea 3 � igual ao valor NIVEL_ZERO (32768) menos o valor lido da �rea 3
		}

		if(tipo_detector == Z8)
		{
			if(Valor[AREA4] >= NIVEL_ZERO && anula_area[AREA4] == 0) //Se valor do sinal da �rea 4 for maior que NIVEL_ZERO (32768) ent�o corrige valor para a faixa correta pois sinal � positivo
			{
				Valor[AREA4] = Valor[AREA4] - NIVEL_ZERO; //Valor do sinal da �rea 4 � igual ao valor lido da �rea 4 menos o valor NIVEL_ZERO (32768)
			}
			else if(Valor[AREA4] < NIVEL_ZERO && anula_area[AREA4] == 0) //Sen�o se valor do sinal da �rea 4 for menor que NIVEL_ZERO (32768) corrige valor para a faixa correta pois sinal � negativo
			{
				Valor[AREA4] = NIVEL_ZERO - Valor[AREA4]; //Valor do sinal da �rea 4 � igual ao valor NIVEL_ZERO (32768) menos o valor lido da �rea 4
			}

			if(Valor[AREA5] >= NIVEL_ZERO && anula_area[AREA5] == 0) //Se valor do sinal da �rea 5 for maior que NIVEL_ZERO (32768) ent�o corrige valor para a faixa correta pois sinal � positivo
			{
				Valor[AREA5] = Valor[AREA5] - NIVEL_ZERO; //Valor do sinal da �rea 5 � igual ao valor lido da �rea 5 menos o valor NIVEL_ZERO (32768)
			}
			else if(Valor[AREA5] < NIVEL_ZERO && anula_area[AREA5] == 0) //Sen�o se valor do sinal da �rea 5 for menor que NIVEL_ZERO (32768) corrige valor para a faixa correta pois sinal � negativo
			{
				Valor[AREA5] = NIVEL_ZERO - Valor[AREA5]; //Valor do sinal da �rea 5 � igual ao valor NIVEL_ZERO (32768) menos o valor lido da �rea 5
			}

			if(Valor[AREA6] >= NIVEL_ZERO && anula_area[AREA6] == 0) //Se valor do sinal da �rea 6 for maior que NIVEL_ZERO (32768) ent�o corrige valor para a faixa correta pois sinal � positivo
			{
				Valor[AREA6] = Valor[AREA6] - NIVEL_ZERO; //Valor do sinal da �rea 6 � igual ao valor lido da �rea 6 menos o valor NIVEL_ZERO (32768)
			}
			else if(Valor[AREA6] < NIVEL_ZERO && anula_area[AREA6] == 0) //Sen�o se valor do sinal da �rea 6 for menor que NIVEL_ZERO (32768) corrige valor para a faixa correta pois sinal � negativo
			{
				Valor[AREA6] = NIVEL_ZERO - Valor[AREA6]; //Valor do sinal da �rea 6 � igual ao valor NIVEL_ZERO (32768) menos o valor lido da �rea 6
			}

			if(Valor[AREA7] >= NIVEL_ZERO && anula_area[AREA7] == 0) //Se valor do sinal da �rea 7 for maior que NIVEL_ZERO (32768) ent�o corrige valor para a faixa correta pois sinal � positivo
			{
				Valor[AREA7] = Valor[AREA7] - NIVEL_ZERO; //Valor do sinal da �rea 7 � igual ao valor lido da �rea 7 menos o valor NIVEL_ZERO (32768)
			}
			else if(Valor[AREA7] < NIVEL_ZERO && anula_area[AREA7] == 0) //Sen�o se valor do sinal da �rea 7 for menor que NIVEL_ZERO (32768) corrige valor para a faixa correta pois sinal � negativo
			{
				Valor[AREA7] = NIVEL_ZERO - Valor[AREA7]; //Valor do sinal da �rea 7 � igual ao valor NIVEL_ZERO (32768) menos o valor lido da �rea 7
			}

			if(Valor[AREA8] >= NIVEL_ZERO && anula_area[AREA8] == 0) //Se valor do sinal da �rea 8 for maior que NIVEL_ZERO (32768) ent�o corrige valor para a faixa correta pois sinal � positivo
			{
				Valor[AREA8] = Valor[AREA8] - NIVEL_ZERO; //Valor do sinal da �rea 8 � igual ao valor lido da �rea 8 menos o valor NIVEL_ZERO (32768)
			}
			else if(Valor[AREA8] < NIVEL_ZERO && anula_area[AREA8] == 0) //Sen�o se valor do sinal da �rea 8 for menor que NIVEL_ZERO (32768) corrige valor para a faixa correta pois sinal � negativo
			{
				Valor[AREA8] = NIVEL_ZERO - Valor[AREA8]; //Valor do sinal da �rea 8 � igual ao valor NIVEL_ZERO (32768) menos o valor lido da �rea 8
			}
		}
		if(anula_area[AREA1] == 1) //Se anula_area[AREA1] for igual a 1 que significa realmente anular ent�o
		{
			Valor[AREA1] = 0; //Zera o valor da leitura de sinal do AD da �rea 1
		}
		if(anula_area[AREA2] == 1) //Se anula_area[AREA2] for igual a 1 que significa realmente anular ent�o
		{
			Valor[AREA2] = 0; //Zera o valor da leitura de sinal do AD da �rea 2
		}
		if(anula_area[AREA3] == 1) //Se anula_area[AREA3] for igual a 1 que significa realmente anular ent�o
		{
			Valor[AREA3] = 0; //Zera o valor da leitura de sinal do AD da �rea 3
		}
		if(tipo_detector == Z8)
		{
			if(anula_area[AREA4] == 1) //Se anula_area[AREA4] for igual a 1 que significa realmente anular ent�o
			{
				Valor[AREA4] = 0; //Zera o valor da leitura de sinal do AD da �rea 4
			}
			if(anula_area[AREA5] == 1) //Se anula_area[AREA5] for igual a 1 que significa realmente anular ent�o
			{
				Valor[AREA5] = 0; //Zera o valor da leitura de sinal do AD da �rea 5
			}
			if(anula_area[AREA6] == 1) //Se anula_area[AREA6] for igual a 1 que significa realmente anular ent�o
			{
				Valor[AREA6] = 0; //Zera o valor da leitura de sinal do AD da �rea 6
			}
			if(anula_area[AREA7] == 1) //Se anula_area[AREA7] for igual a 1 que significa realmente anular ent�o
			{
				Valor[AREA7] = 0; //Zera o valor da leitura de sinal do AD da �rea 7
			}
			if(anula_area[AREA8] == 1) //Se anula_area[AREA8] for igual a 1 que significa realmente anular ent�o
			{
				Valor[AREA8] = 0; //Zera o valor da leitura de sinal do AD da �rea 8
			}
		}

		/*** Zera o contador de intervalo de tempo de velocidade para iniciar a an�lise da faixa temporal de detec��o verdadeira e elimina��o do ru�do ***/
		//Se valor do sinal AD da respectiva �rea for maior que o valor da sensibilidade da �rea convertida em n�mero de AD e flagVelocidade da �rea for FALSE e anula_area da area for FALSE ent�o
		if ( (Valor[AREA1] >= ( (NIVEL_ZERO * (101-buffer_sensibilidade[AREA1]) ) /100) )  && (flagVelocidade1 == FALSE) && (anula_area[AREA1] == 0) )
		{
			flagVelocidade1 = TRUE; //Armazena na vari�vel flagVelocidade1 a informa��o TRUE para permitir contar tempo de amostragem
			delta_t1 = 0; //Zera o contador de tempo de amostragem da �rea
		}
		if ( (Valor[AREA2] >= ( (NIVEL_ZERO *(101-buffer_sensibilidade[AREA2]) )/100) ) && (flagVelocidade2 == FALSE) && (anula_area[AREA2] == 0) )
		{
			flagVelocidade2 = TRUE; //Armazena na vari�vel flagVelocidade2 a informa��o TRUE para permitir contar tempo de amostragem
			delta_t2 = 0; //Zera o contador de tempo de amostragem da �rea
		}
		if ( (Valor[AREA3] >= ( (NIVEL_ZERO * (101-buffer_sensibilidade[AREA3]) ) /100) )  && (flagVelocidade3 == FALSE) && (anula_area[AREA3] == 0) )
		{
			flagVelocidade3 = TRUE; //Armazena na vari�vel flagVelocidade3 a informa��o TRUE para permitir contar tempo de amostragem
			delta_t3 = 0; //Zera o contador de tempo de amostragem da �rea
		}
		if(tipo_detector == Z8)
		{
			if ( (Valor[AREA4] >= ( (NIVEL_ZERO * (101-buffer_sensibilidade[AREA4]) ) / 100) ) && (flagVelocidade4 == FALSE) && (anula_area[AREA4] == 0) )
			{
				flagVelocidade4 = TRUE; //Armazena na vari�vel flagVelocidade4 a informa��o TRUE para permitir contar tempo de amostragem
				delta_t4 = 0; //Zera o contador de tempo de amostragem da �rea
			}
			if ( (Valor[AREA5] >= ( (NIVEL_ZERO*(101-buffer_sensibilidade[AREA5]) ) / 100) )  && (flagVelocidade5 == FALSE) && (anula_area[AREA5] == 0))
			{
				flagVelocidade5 = TRUE; //Armazena na vari�vel flagVelocidade5 a informa��o TRUE para permitir contar tempo de amostragem
				delta_t5 = 0; //Zera o contador de tempo de amostragem da �rea
			}
			if ( (Valor[AREA6] >= ( (NIVEL_ZERO * (101-buffer_sensibilidade[AREA6]) ) /100) ) && (flagVelocidade6 == FALSE) && (anula_area[AREA6] == 0))
			{
				flagVelocidade6 = TRUE; //Armazena na vari�vel flagVelocidade6 a informa��o TRUE para permitir contar tempo de amostragem
				delta_t6 = 0; //Zera o contador de tempo de amostragem da �rea
			}
			if ( (Valor[AREA7] >= ( (NIVEL_ZERO * (101-buffer_sensibilidade[AREA7]) ) /100) )  && (flagVelocidade7 == FALSE) && (anula_area[AREA7] == 0) )
			{
				flagVelocidade7 = TRUE; //Armazena na vari�vel flagVelocidade7 a informa��o TRUE para permitir contar tempo de amostragem
				delta_t7 = 0; //Zera o contador de tempo de amostragem da �rea
			}
			if ( (Valor[AREA8] >= ( (NIVEL_ZERO*(101-buffer_sensibilidade[AREA8]) ) / 100) ) && (flagVelocidade8 == FALSE) && (anula_area[AREA8] == 0))
			{
				flagVelocidade8 = TRUE; //Armazena na vari�vel flagVelocidade8 a informa��o TRUE para permitir contar tempo de amostragem
				delta_t8 = 0; //Zera o contador de tempo de amostragem da �rea
			}
		}
		/**********************************************************************/

		/*** An�lise da detec��o ap�s passar o intervalo de tempo definido pela velocidade ***/
		//Se valor do sinal AD da respectiva �rea for maior que o valor da sensibilidade da �rea convertida em n�mero de AD e fimLeitura da �rea for FALSE e anula_area da area for FALSE ent�o
		if ( (Valor[AREA1] >= ( (NIVEL_ZERO * (101-buffer_sensibilidade[AREA1]) ) /100) ) && (fimLeitura1 == FALSE) && (anula_area[AREA1] == 0) )
		{
			detectou[AREA1] = SIM; //Armazena no vetor detectou da �rea 1 a informa��o SIM
		}
		else if ( (Valor[AREA1] < ( (NIVEL_ZERO * (101-buffer_sensibilidade[AREA1]) ) /100) ) && (fimLeitura1 == FALSE) && (anula_area[AREA1] == 0))
		{
			nao_detectou[AREA1] = SIM; //Armazena no vetor nao_detectou da �rea 1 a informa��o SIM
		}

		if ( (Valor[AREA2] >= ( (NIVEL_ZERO * (101-buffer_sensibilidade[AREA2]) ) /100) ) && (fimLeitura2 == FALSE) && (anula_area[AREA2] == 0) )
		{
			detectou[AREA2] = SIM; //Armazena no vetor detectou da �rea 2 a informa��o SIM
		}
		else if ( (Valor[AREA2] < ( (NIVEL_ZERO * (101-buffer_sensibilidade[AREA2]) ) /100) ) && (fimLeitura2 == FALSE) && (anula_area[AREA2] == 0))
		{
			nao_detectou[AREA2] = SIM; //Armazena no vetor nao_detectou da �rea 2 a informa��o SIM
		}

		if ( (Valor[AREA3] >= ( (NIVEL_ZERO * (101-buffer_sensibilidade[AREA3]) ) /100) ) && (fimLeitura3 == FALSE) && (anula_area[AREA3] == 0) )
		{
			detectou[AREA3] = SIM; //Armazena no vetor detectou da �rea 3 a informa��o SIM
		}
		else if ( (Valor[AREA3] < ( (NIVEL_ZERO * (101-buffer_sensibilidade[AREA3]) ) /100) ) && (fimLeitura3 == FALSE) && (anula_area[AREA3] == 0))
		{
			nao_detectou[AREA3] = SIM; //Armazena no vetor nao_detectou da �rea 3 a informa��o SIM
		}

		if(tipo_detector == Z8)
		{
			if ( (Valor[AREA4] >= ( (NIVEL_ZERO * (101-buffer_sensibilidade[AREA4]) ) /100) ) && (fimLeitura4 == FALSE) && (anula_area[AREA4] == 0))
			{
				detectou[AREA4] = SIM; //Armazena no vetor detectou da �rea 4 a informa��o SIM
			}
			else if ( (Valor[AREA4] < ( (NIVEL_ZERO * (101-buffer_sensibilidade[AREA4]) ) /100) ) && (fimLeitura4 == FALSE) && (anula_area[AREA4] == 0))
			{
				nao_detectou[AREA4] = SIM; //Armazena no vetor nao_detectou da �rea 4 a informa��o SIM
			}

			if ( (Valor[AREA5] >= ( (NIVEL_ZERO * (101-buffer_sensibilidade[AREA5]) ) /100) ) && (fimLeitura5 == FALSE) && (anula_area[AREA5] == 0))
			{
				detectou[AREA5] = SIM; //Armazena no vetor detectou da �rea 5 a informa��o SIM
			}
			else if ( (Valor[AREA5] < ( (NIVEL_ZERO * (101-buffer_sensibilidade[AREA5]) ) /100) ) && (fimLeitura5 == FALSE) && (anula_area[AREA5] == 0))
			{
				nao_detectou[AREA5] = SIM; //Armazena no vetor nao_detectou da �rea 5 a informa��o SIM
			}

			if ( (Valor[AREA6] >= ( (NIVEL_ZERO * (101-buffer_sensibilidade[AREA6]) ) /100) ) && (fimLeitura6 == FALSE) && (anula_area[AREA6] == 0))
			{
				detectou[AREA6] = SIM; //Armazena no vetor detectou da �rea 6 a informa��o SIM
			}
			else if ( (Valor[AREA6] < ( (NIVEL_ZERO * (101-buffer_sensibilidade[AREA6]) ) /100) ) && (fimLeitura6 == FALSE) && (anula_area[AREA6] == 0))
			{
				nao_detectou[AREA6] = SIM; //Armazena no vetor nao_detectou da �rea 6 a informa��o SIM
			}

			if ( (Valor[AREA7] >= ( (NIVEL_ZERO * (101-buffer_sensibilidade[AREA7]) ) /100) ) && (fimLeitura7 == FALSE) && (anula_area[AREA7] == 0))
			{
				detectou[AREA7] = SIM; //Armazena no vetor detectou da �rea 7 a informa��o SIM
			}
			else if ( (Valor[AREA7] < ( (NIVEL_ZERO * (101-buffer_sensibilidade[AREA7]) ) /100) ) && (fimLeitura7 == FALSE) && (anula_area[AREA7] == 0))
			{
				nao_detectou[AREA7] = SIM; //Armazena no vetor nao_detectou da �rea 7 a informa��o SIM
			}

			if ( (Valor[AREA8] >= ( (NIVEL_ZERO * (101-buffer_sensibilidade[AREA8]) ) /100) ) && (fimLeitura8 == FALSE) && (anula_area[AREA8] == 0))
			{
				detectou[AREA8] = SIM; //Armazena no vetor detectou da �rea 8 a informa��o SIM
			}
			else if ( (Valor[AREA8] < ( (NIVEL_ZERO * (101-buffer_sensibilidade[AREA8]) ) /100) ) && (fimLeitura8 == FALSE) && (anula_area[AREA8] == 0))
			{
				nao_detectou[AREA8] = SIM; //Armazena no vetor nao_detectou da �rea 8 a informa��o SIM
			}
		}
		/**********************************************************************/

		/*** Conclus�es das an�lises para o acendimento correto da sinaleira de detec��o ***/

		//Se fimLeitura1 for igual a TRUE e se detectou na �rea 1 e delta_t1 for maior ou igual ao filtro de ruido estabelecido ent�o
		if ( (fimLeitura1 == TRUE) && (detectou[AREA1] == SIM) && (nao_detectou[AREA1] == NAO) && (delta_t1 >= filtroruido) )
		{
			AREA1_DETECTOU = SIM; //Armazena na vari�vel AREA1_DETECTOU a informa��o SIM
			fimLeitura1 = FALSE; //Armazena na vari�vel fimLeitura1 a informa��o FALSE
			flagVelocidade1 = FALSE; //Armazena na vari�vel flagVelocidade1 a informa��o FALSE
			detectou[AREA1] = NAO; //Armazena no vetor detectou da �rea 1 a informa��o NAO
			nao_detectou[AREA1] = NAO; //Armazena no vetor detectou da �rea 1 a informa��o NAO
		}
		//Sen�o se  fimLeitura1 for igual a TRUE e se nao_detectou na area 1 e delta_t1 for maior ou igual ao filtro de ruido estabelecido ent�o
		else if( (fimLeitura1 == TRUE) && (nao_detectou[AREA1] == SIM) && (delta_t1 >= filtroruido) )
		{
			AREA1_DETECTOU = NAO; //Armazena na vari�vel AREA1_DETECTOU a informa��o NAO
			fimLeitura1 = FALSE; //Armazena na vari�vel fimLeitura1 a informa��o FALSE
			flagVelocidade1 = FALSE; //Armazena na vari�vel flagVelocidade1 a informa��o FALSE
			detectou[AREA1] = NAO; //Armazena no vetor detectou da �rea 1 a informa��o NAO
			nao_detectou[AREA1] = NAO; //Armazena no vetor detectou da �rea 1 a informa��o NAO
		}
		//Se fimLeitura2 for igual a TRUE e se detectou na �rea 2 e delta_t2 for maior ou igual ao filtro de ruido estabelecido ent�o
		if ( (fimLeitura2 == TRUE) && (detectou[AREA2] == SIM) && (nao_detectou[AREA2] == NAO) && (delta_t2 >= filtroruido) )
		{
			AREA2_DETECTOU = SIM; //Armazena na vari�vel AREA2_DETECTOU a informa��o SIM
			fimLeitura2 = FALSE; //Armazena na vari�vel fimLeitura2 a informa��o FALSE
			flagVelocidade2 = FALSE; //Armazena na vari�vel flagVelocidade2 a informa��o FALSE
			detectou[AREA2] = NAO; //Armazena no vetor detectou da �rea 2 a informa��o NAO
			nao_detectou[AREA2] = NAO; //Armazena no vetor detectou da �rea 2 a informa��o NAO
		}
		//Sen�o se  fimLeitura2 for igual a TRUE e se nao_detectou na area 2 e delta_t2 for maior ou igual ao filtro de ruido estabelecido ent�o
		else if( (fimLeitura2 == TRUE) && (nao_detectou[AREA2] == SIM) && (delta_t2 >= filtroruido) )
		{
			AREA2_DETECTOU = NAO; //Armazena na vari�vel AREA2_DETECTOU a informa��o NAO
			fimLeitura2 = FALSE; //Armazena na vari�vel fimLeitura2 a informa��o FALSE
			flagVelocidade2 = FALSE; //Armazena na vari�vel flagVelocidade2 a informa��o FALSE
			detectou[AREA2] = NAO; //Armazena no vetor detectou da �rea 2 a informa��o NAO
			nao_detectou[AREA2] = NAO; //Armazena no vetor detectou da �rea 2 a informa��o NAO
		}
		//Se fimLeitura3 for igual a TRUE e se detectou na �rea 3 e delta_t3 for maior ou igual ao filtro de ruido estabelecido ent�o
		if ( (fimLeitura3 == TRUE) && (detectou[AREA3] == SIM) && (nao_detectou[AREA3] == NAO) && (delta_t3 >= filtroruido) )
		{
			AREA3_DETECTOU = SIM; //Armazena na vari�vel AREA3_DETECTOU a informa��o SIM
			fimLeitura3 = FALSE; //Armazena na vari�vel fimLeitura3 a informa��o FALSE
			flagVelocidade3 = FALSE; //Armazena na vari�vel flagVelocidade3 a informa��o FALSE
			detectou[AREA3] = NAO; //Armazena no vetor detectou da �rea 3 a informa��o NAO
			nao_detectou[AREA3] = NAO; //Armazena no vetor detectou da �rea 3 a informa��o NAO
		}
		//Sen�o se  fimLeitura3 for igual a TRUE e se nao_detectou na area 3 e delta_t3 for maior ou igual ao filtro de ruido estabelecido ent�o
		else if( (fimLeitura3 == TRUE) && (nao_detectou[AREA3] == SIM) && (delta_t3 >= filtroruido) )
		{
			AREA3_DETECTOU = NAO; //Armazena na vari�vel AREA3_DETECTOU a informa��o NAO
			fimLeitura3 = FALSE; //Armazena na vari�vel fimLeitura3 a informa��o FALSE
			flagVelocidade3 = FALSE; //Armazena na vari�vel flagVelocidade3 a informa��o FALSE
			detectou[AREA3] = NAO; //Armazena no vetor detectou da �rea 3 a informa��o NAO
			nao_detectou[AREA3] = NAO; //Armazena no vetor detectou da �rea 3 a informa��o NAO
		}
		if(tipo_detector == Z8)
		{
			//Se fimLeitura4 for igual a TRUE e se detectou na �rea 4 e delta_t4 for maior ou igual ao filtro de ruido estabelecido ent�o
			if ( (fimLeitura4 == TRUE) && (detectou[AREA4] == SIM) && (nao_detectou[AREA4] == NAO) && (delta_t4 >= filtroruido) )
			{
				AREA4_DETECTOU = SIM; //Armazena na vari�vel AREA4_DETECTOU a informa��o SIM
				fimLeitura4 = FALSE; //Armazena na vari�vel fimLeitura4 a informa��o FALSE
				flagVelocidade4 = FALSE; //Armazena na vari�vel flagVelocidade4 a informa��o FALSE
				detectou[AREA4] = NAO; //Armazena no vetor detectou da �rea 4 a informa��o NAO
				nao_detectou[AREA4] = NAO; //Armazena no vetor detectou da �rea 4 a informa��o NAO
			}
			//Sen�o se  fimLeitura4 for igual a TRUE e se nao_detectou na area 4 e delta_t4 for maior ou igual ao filtro de ruido estabelecido ent�o
			else if( (fimLeitura4 == TRUE) && (nao_detectou[AREA4] == SIM) && (delta_t4 >= filtroruido) )
			{
				AREA4_DETECTOU = NAO; //Armazena na vari�vel AREA4_DETECTOU a informa��o NAO
				fimLeitura4 = FALSE; //Armazena na vari�vel fimLeitura4 a informa��o FALSE
				flagVelocidade4 = FALSE; //Armazena na vari�vel flagVelocidade4 a informa��o FALSE
				detectou[AREA4] = NAO; //Armazena no vetor detectou da �rea 4 a informa��o NAO
				nao_detectou[AREA4] = NAO; //Armazena no vetor detectou da �rea 4 a informa��o NAO
			}
			//Se fimLeitura5 for igual a TRUE e se detectou na �rea 5 e delta_t5 for maior ou igual ao filtro de ruido estabelecido ent�o
			if ( (fimLeitura5 == TRUE) && (detectou[AREA5] == SIM) && (nao_detectou[AREA5] == NAO) && (delta_t5 >= filtroruido) )
			{
				AREA5_DETECTOU = SIM; //Armazena na vari�vel AREA5_DETECTOU a informa��o SIM
				fimLeitura5 = FALSE; //Armazena na vari�vel fimLeitura5 a informa��o FALSE
				flagVelocidade5 = FALSE; //Armazena na vari�vel flagVelocidade5 a informa��o FALSE
				detectou[AREA5] = NAO; //Armazena no vetor detectou da �rea 5 a informa��o NAO
				nao_detectou[AREA5] = NAO; //Armazena no vetor detectou da �rea 5 a informa��o NAO
			}
			//Sen�o se  fimLeitura5 for igual a TRUE e se nao_detectou na area 5 e delta_t5 for maior ou igual ao filtro de ruido estabelecido ent�o
			else if( (fimLeitura5 == TRUE) && (nao_detectou[AREA5] == SIM) && (delta_t5 >= filtroruido) )
			{
				AREA5_DETECTOU = NAO; //Armazena na vari�vel AREA5_DETECTOU a informa��o NAO
				fimLeitura5 = FALSE; //Armazena na vari�vel fimLeitura5 a informa��o FALSE
				flagVelocidade5 = FALSE; //Armazena na vari�vel flagVelocidade5 a informa��o FALSE
				detectou[AREA5] = NAO; //Armazena no vetor detectou da �rea 5 a informa��o NAO
				nao_detectou[AREA5] = NAO; //Armazena no vetor detectou da �rea 5 a informa��o NAO
			}
			//Se fimLeitura6 for igual a TRUE e se detectou na �rea 6 e delta_t6 for maior ou igual ao filtro de ruido estabelecido ent�o
			if ( (fimLeitura6 == TRUE) && (detectou[AREA6] == SIM) && (nao_detectou[AREA6] == NAO) && (delta_t6 >= filtroruido) )
			{
				AREA6_DETECTOU = SIM; //Armazena na vari�vel AREA6_DETECTOU a informa��o SIM
				fimLeitura6 = FALSE; //Armazena na vari�vel fimLeitura6 a informa��o FALSE
				flagVelocidade6 = FALSE; //Armazena na vari�vel flagVelocidade6 a informa��o FALSE
				detectou[AREA6] = NAO; //Armazena no vetor detectou da �rea 6 a informa��o NAO
				nao_detectou[AREA6] = NAO; //Armazena no vetor detectou da �rea 6 a informa��o NAO
			}
			//Sen�o se  fimLeitura6 for igual a TRUE e se nao_detectou na area 6 e delta_t6 for maior ou igual ao filtro de ruido estabelecido ent�o
			else if( (fimLeitura6 == TRUE) && (nao_detectou[AREA6] == SIM) && (delta_t6 >= filtroruido) )
			{
				AREA6_DETECTOU = NAO; //Armazena na vari�vel AREA6_DETECTOU a informa��o NAO
				fimLeitura6 = FALSE; //Armazena na vari�vel fimLeitura6 a informa��o FALSE
				flagVelocidade6 = FALSE; //Armazena na vari�vel flagVelocidade6 a informa��o FALSE
				detectou[AREA6] = NAO; //Armazena no vetor detectou da �rea 6 a informa��o NAO
				nao_detectou[AREA6] = NAO; //Armazena no vetor detectou da �rea 6 a informa��o NAO
			}
			//Se fimLeitura7 for igual a TRUE e se detectou na �rea 7 e delta_t7 for maior ou igual ao filtro de ruido estabelecido ent�o
			if ( (fimLeitura7 == TRUE) && (detectou[AREA7] == SIM) && (nao_detectou[AREA7] == NAO) && (delta_t7 >= filtroruido) )
			{
				AREA7_DETECTOU = SIM; //Armazena na vari�vel AREA7_DETECTOU a informa��o SIM
				fimLeitura7 = FALSE; //Armazena na vari�vel fimLeitura7 a informa��o FALSE
				flagVelocidade7 = FALSE; //Armazena na vari�vel flagVelocidade7 a informa��o FALSE
				detectou[AREA7] = NAO; //Armazena no vetor detectou da �rea 7 a informa��o NAO
				nao_detectou[AREA7] = NAO; //Armazena no vetor detectou da �rea 7 a informa��o NAO
			}
			//Sen�o se  fimLeitura7 for igual a TRUE e se nao_detectou na area 7 e delta_t7 for maior ou igual ao filtro de ruido estabelecido ent�o
			else if( (fimLeitura7 == TRUE) && (nao_detectou[AREA7] == SIM) && (delta_t7 >= filtroruido) )
			{
				AREA7_DETECTOU = NAO; //Armazena na vari�vel AREA7_DETECTOU a informa��o NAO
				fimLeitura7 = FALSE; //Armazena na vari�vel fimLeitura7 a informa��o FALSE
				flagVelocidade7 = FALSE; //Armazena na vari�vel flagVelocidade7 a informa��o FALSE
				detectou[AREA7] = NAO; //Armazena no vetor detectou da �rea 7 a informa��o NAO
				nao_detectou[AREA7] = NAO; //Armazena no vetor detectou da �rea 7 a informa��o NAO
			}
			//Se fimLeitura8 for igual a TRUE e se detectou na �rea 8 e delta_t8 for maior ou igual ao filtro de ruido estabelecido ent�o
			if ( (fimLeitura8 == TRUE) && (detectou[AREA8] == SIM) && (nao_detectou[AREA8] == NAO) && (delta_t8 >= filtroruido) )
			{
				AREA8_DETECTOU = SIM; //Armazena na vari�vel AREA8_DETECTOU a informa��o SIM
				fimLeitura8 = FALSE; //Armazena na vari�vel fimLeitura8 a informa��o FALSE
				flagVelocidade8 = FALSE; //Armazena na vari�vel flagVelocidade8 a informa��o FALSE
				detectou[AREA8] = NAO; //Armazena no vetor detectou da �rea 8 a informa��o NAO
				nao_detectou[AREA8] = NAO; //Armazena no vetor detectou da �rea 8 a informa��o NAO
			}
			//Sen�o se  fimLeitura8 for igual a TRUE e se nao_detectou na area 8 e delta_t8 for maior ou igual ao filtro de ruido estabelecido ent�o
			else if( (fimLeitura8 == TRUE) && (nao_detectou[AREA8] == SIM) && (delta_t8 >= filtroruido) )
			{
				AREA8_DETECTOU = NAO; //Armazena na vari�vel AREA8_DETECTOU a informa��o NAO
				fimLeitura8 = FALSE; //Armazena na vari�vel fimLeitura8 a informa��o FALSE
				flagVelocidade8 = FALSE; //Armazena na vari�vel flagVelocidade8 a informa��o FALSE
				detectou[AREA8] = NAO; //Armazena no vetor detectou da �rea 8 a informa��o NAO
				nao_detectou[AREA8] = NAO; //Armazena no vetor detectou da �rea 8 a informa��o NAO
			}
		}
		/**********************************************************************/

		/*** Acendimento correto da sinaleira conforme conclus�es das an�lises de detec��o ***/
		if (AREA1_DETECTOU == SIM && anula_area[AREA1] == 0) //Se �rea 1 detectou e anula_area for zero ent�o
		{
			AREA1_DETECTOU = NAO; //Armazena na vari�vel AREA1_DETECTOU a informa��o NAO
			areas_detectadas = areas_detectadas | A01; //Armazena na vari�vel areas_detectadas a informa��o de que houve detec��o na �rea 1
			fim_sinaleira = TRUE; //Armazena na vari�vel fim_sinaleira a informa��o TRUE
		}
		else if(AREA1_DETECTOU == SIM && anula_area[AREA1] == 1) //Sen�o se �rea 1 detectou e anula_area for 1 ent�o
		{
			AREA1_DETECTOU = NAO; //Armazena na vari�vel AREA1_DETECTOU a informa��o NAO
		}

		if (AREA2_DETECTOU == SIM && anula_area[AREA2] == 0) //Se �rea 2 detectou e anula_area for zero ent�o
		{
			AREA2_DETECTOU = NAO; //Armazena na vari�vel AREA2_DETECTOU a informa��o NAO
			areas_detectadas = areas_detectadas | A02; //Armazena na vari�vel areas_detectadas a informa��o de que houve detec��o na �rea 2
			fim_sinaleira = TRUE; //Armazena na vari�vel fim_sinaleira a informa��o TRUE
		}
		else if(AREA2_DETECTOU == SIM && anula_area[AREA2] == 1) //Sen�o se �rea 2 detectou e anula_area for 1 ent�o
		{
			AREA2_DETECTOU = NAO; //Armazena na vari�vel AREA2_DETECTOU a informa��o NAO
		}

		if (AREA3_DETECTOU == SIM && anula_area[AREA3] == 0) //Se �rea 3 detectou e anula_area for zero ent�o
		{
			AREA3_DETECTOU = NAO; //Armazena na vari�vel AREA3_DETECTOU a informa��o NAO
			areas_detectadas = areas_detectadas | A03; //Armazena na vari�vel areas_detectadas a informa��o de que houve detec��o na �rea 3
			fim_sinaleira = TRUE; //Armazena na vari�vel fim_sinaleira a informa��o TRUE
		}
		else if(AREA3_DETECTOU == SIM && anula_area[AREA3] == 1) //Sen�o se �rea 3 detectou e anula_area for 1 ent�o
		{
			AREA3_DETECTOU = NAO; //Armazena na vari�vel AREA3_DETECTOU a informa��o NAO
		}

		if(tipo_detector == Z8)
		{
			if (AREA4_DETECTOU == SIM && anula_area[AREA4] == 0) //Se �rea 4 detectou e anula_area for zero ent�o
			{
				AREA4_DETECTOU = NAO; //Armazena na vari�vel AREA4_DETECTOU a informa��o NAO
				areas_detectadas = areas_detectadas | A04; //Armazena na vari�vel areas_detectadas a informa��o de que houve detec��o na �rea 4
				fim_sinaleira = TRUE; //Armazena na vari�vel fim_sinaleira a informa��o TRUE
			}
			else if(AREA4_DETECTOU == SIM && anula_area[AREA4] == 1) //Sen�o se �rea 4 detectou e anula_area for 1 ent�o
			{
				AREA4_DETECTOU = NAO; //Armazena na vari�vel AREA4_DETECTOU a informa��o NAO
			}

			if (AREA5_DETECTOU == SIM && anula_area[AREA5] == 0) //Se �rea 5 detectou e anula_area for zero ent�o
			{
				AREA5_DETECTOU = NAO; //Armazena na vari�vel AREA5_DETECTOU a informa��o NAO
				areas_detectadas = areas_detectadas | A05; //Armazena na vari�vel areas_detectadas a informa��o de que houve detec��o na �rea 5
				fim_sinaleira = TRUE; //Armazena na vari�vel fim_sinaleira a informa��o TRUE
			}
			else if(AREA5_DETECTOU == SIM && anula_area[AREA5] == 1) //Sen�o se �rea 5 detectou e anula_area for 1 ent�o
			{
				AREA5_DETECTOU = NAO; //Armazena na vari�vel AREA5_DETECTOU a informa��o NAO
			}

			if (AREA6_DETECTOU == SIM && anula_area[AREA6] == 0) //Se �rea 6 detectou e anula_area for zero ent�o
			{
				AREA6_DETECTOU = NAO; //Armazena na vari�vel AREA6_DETECTOU a informa��o NAO
				areas_detectadas = areas_detectadas | A06; //Armazena na vari�vel areas_detectadas a informa��o de que houve detec��o na �rea 6
				fim_sinaleira = TRUE; //Armazena na vari�vel fim_sinaleira a informa��o TRUE
			}
			else if(AREA6_DETECTOU == SIM && anula_area[AREA6] == 1) //Sen�o se �rea 6 detectou e anula_area for 1 ent�o
			{
				AREA6_DETECTOU = NAO; //Armazena na vari�vel AREA6_DETECTOU a informa��o NAO
			}

			if (AREA7_DETECTOU == SIM && anula_area[AREA7] == 0) //Se �rea 7 detectou e anula_area for zero ent�o
			{
				AREA7_DETECTOU = NAO; //Armazena na vari�vel AREA7_DETECTOU a informa��o NAO
				areas_detectadas = areas_detectadas | A07; //Armazena na vari�vel areas_detectadas a informa��o de que houve detec��o na �rea 7
				fim_sinaleira = TRUE; //Armazena na vari�vel fim_sinaleira a informa��o TRUE
			}
			else if(AREA7_DETECTOU == SIM && anula_area[AREA7] == 1) //Sen�o se �rea 7 detectou e anula_area for 1 ent�o
			{
				AREA7_DETECTOU = NAO; //Armazena na vari�vel AREA7_DETECTOU a informa��o NAO
			}

			if (AREA8_DETECTOU == SIM && anula_area[AREA8] == 0) //Se �rea 8 detectou e anula_area for zero ent�o
			{
				AREA8_DETECTOU = NAO; //Armazena na vari�vel AREA8_DETECTOU a informa��o NAO
				areas_detectadas = areas_detectadas | A08; //Armazena na vari�vel areas_detectadas a informa��o de que houve detec��o na �rea 8
				fim_sinaleira = TRUE; //Armazena na vari�vel fim_sinaleira a informa��o TRUE
			}
			else if(AREA8_DETECTOU == SIM && anula_area[AREA8] == 1) //Sen�o se �rea 8 detectou e anula_area for 1 ent�o
			{
				AREA8_DETECTOU = NAO; //Armazena na vari�vel AREA8_DETECTOU a informa��o NAO
			}
		}
		/**********************************************************************/

		AcendeBargraph(); //Acende a quantidade de n�veis de led de acordo com o valor de detec��o da �rea de maior valor

		/*** Acende a respectiva �rea conforme resultado anterior ***/

		if(areas_detectadas != 0x00) //Se areas_detectadas n�o for igual a 00 ent�o
		{
			if(travado == FALSE) //Se travado for igual a FALSE ent�o
			{
				APAGA_AREAS; //Apaga os leds das �reas
			}
			if(sinal_trava == trava_pulso) //Se sinal_trava for igual a trava_pulso ent�o
			{
				fnLigaPulsoTrava(); //Permite pulsar a trava
			}
			else if(sinal_trava == trava_retencao_controle || sinal_trava == trava_retencao_controle_teclado) //Sen�o se sinal_trava for igual a trava_retencao_controle ou sinal_trava for igual a trava_retencao_controle_teclado ent�o
			{
				LIGA_TRAVA; //Energiza a trava
				if(sinal_rele == rele_pulso) //Se sinal_rele for igual a rele_pulso ent�o
				{
					fnLigaPulsoRele(); //Permite pulsar o rel�
				}
				else //Sen�o
				{
					LIGA_RELE; //Energiza o rel�
				}
				LIGA_SINALEIRA_VERMELHA; //Liga a sinaleira vermelha
				fnReproduzMsgVoz(DETECCAO); //Fun��o que reproduz a mensagem de voz
			}

			fim_sinaleira = FALSE; //Armazena na vari�vel fim_sinaleira a informa��o FALSE

			AcendeBargraph(); //Acende a quantidade de n�veis de led de acordo com o valor de detec��o da �rea de maior valor

			if(AREA01_DETECTADA && alarme_visual == NAO) //Se �rea 1 detectada e alarme_visual for igual a NAO ent�o
			{
				if(tipo_detector == Z3) //Se tipo de detector for 3 zonas ent�o
				{
					ACENDE_AREA1; //Acende o led da �rea 1
					ACENDE_AREA2; //Acende o led da �rea 2
				}
				else if(tipo_detector == Z8) //Sen�o se tipo de detector for 8 zonas ent�o
				{
					ACENDE_AREA1; //Acende o led da �rea 1
				}
			}
			if(AREA02_DETECTADA && alarme_visual == NAO) //Se �rea 2 detectada e alarme_visual for igual a NAO ent�o
			{
				if(tipo_detector == Z3) //Se tipo de detector for 3 zonas ent�o
				{
					ACENDE_AREA4; //Acende o led da �rea 4
					ACENDE_AREA5; //Acende o led da �rea 5
				}
				else if(tipo_detector == Z8) //Sen�o se tipo de detector for 8 zonas ent�o
				{
					ACENDE_AREA2; //Acende o led da �rea 2
				}
			}
			if(AREA03_DETECTADA && alarme_visual == NAO) //Se �rea 3 detectada e alarme_visual for igual a NAO ent�o
			{
				if(tipo_detector == Z3) //Se tipo de detector for 3 zonas ent�o
				{
					ACENDE_AREA7; //Acende o led da �rea 7
					ACENDE_AREA8; //Acende o led da �rea 8
				}
				else if(tipo_detector == Z8) //Sen�o se tipo de detector for 8 zonas ent�o
				{
					ACENDE_AREA3; //Acende o led da �rea 3
				}
			}

			if(tipo_detector == Z8)
			{
				if(AREA04_DETECTADA && alarme_visual == NAO) //Se �rea 4 detectada e alarme_visual for igual a NAO ent�o
				{
					ACENDE_AREA4; //Acende o led da �rea 4
				}
				if(AREA05_DETECTADA && alarme_visual == NAO) //Se �rea 5 detectada e alarme_visual for igual a NAO ent�o
				{
					ACENDE_AREA5; //Acende o led da �rea 5
				}
				if(AREA06_DETECTADA && alarme_visual == NAO) //Se �rea 6 detectada e alarme_visual for igual a NAO ent�o
				{
					ACENDE_AREA6; //Acende o led da �rea 6
				}
				if(AREA07_DETECTADA && alarme_visual == NAO) //Se �rea 7 detectada e alarme_visual for igual a NAO ent�o
				{
					ACENDE_AREA7; //Acende o led da �rea 7
				}
				if(AREA08_DETECTADA && alarme_visual == NAO) //Se �rea 8 detectada e alarme_visual for igual a NAO ent�o
				{
					ACENDE_AREA8; //Acende o led da �rea 8
				}
			}

			TocaTomBuzzer(); //Toca tom do buzzer

			if(travado == FALSE) //Se travado for igual a FALSE ent�o
			{
				contador_bloqueios++; //Incrementa contador de bloqueios
				Write_Buffer_FLASH[0] = (byte)(contador_bloqueios >> 24); //Escreve o valor do quarto byte mais alto no vetor para grava��o na mem�ria FLASH
				Write_Buffer_FLASH[1] = (byte)(contador_bloqueios >> 16); //Escreve o valor do teceiro byte mais alto no vetor para grava��o na mem�ria FLASH
				Write_Buffer_FLASH[2] = (byte)(contador_bloqueios >> 8); //Escreve o valor do segundo byte mais alto no vetor para grava��o na mem�ria FLASH
				Write_Buffer_FLASH[3] = (byte)(contador_bloqueios); //Escreve o valor do primeiro byte mais alto no vetor para grava��o na mem�ria FLASH
				ESCREVE_FLASH_INTERNA(endFLASHTotalBloqueios,4,0); //Escreve na mem�ria FLASH as sele��es de metais dos potenciometros alterados no endere�o especificado
				fnGravaEvento(GRAVA_BLOQUE,GRAVA_DETECT); //Fun��o que grava os eventos de bloqueios e desbloqueios realizados por painel, controle remoto ou detec��o de metais
				travado = TRUE; //Armazena na vari�vel travado a informa��o TRUE para informar que a porta girat�ria esta travada
			}
		}

		areas_detectadas = 0x00; //Zera a vari�vel que informa as �reas detectadas

		//Se o valor do sinal AD lido de qualquer �rea for menor que o limite permitido de sinal para �rea ent�o
		if(!eliminar_falha)
		{
			LENDO_AREAS1 = FALSE;
			if ( (Valor1[AREA1] < 200) || (Valor1[AREA2] < 200) || (Valor1[AREA3] < 200) || (Valor1[AREA4] < 200) ||
			     (Valor1[AREA5] < 200) || (Valor1[AREA6] < 200) || (Valor1[AREA7] < 200) || (Valor1[AREA8] < 200) )
			{
				if (flagMonitoraAreas == 0) //Se flagMonitoraAreas for igual a zero ent�o
				{
					tempo_msg = 0; //Armazena na vari�vel tempo_msg o valor zero
					flagMonitoraAreas = 1; //Armazena na vari�vel flagMonitoraAreas o valor 1 para poder emitir a mensagem sem sinal nas antenas
					tela = TELA_SEM_SINAL_NAS_ANTENAS; //Tela � igual a TELA_SEM_SINAL_NAS_ANTENAS
					estado_LCD = ATUALIZA_LCD;  //Atualiza o LCD com a tela acima
					LIGA_TRAVA; //Energiza a trava
					LIGA_SINALEIRA_VERMELHA; //Liga a sinaleira vermelha
					FALHA_DAS_BOBINAS = TRUE;
					travado = TRUE;
				}
				flag_antena_rx_sem_sinal = TRUE; //Armazena na flag_antena_rx_sem_sinal a informa��o TRUE
				LENDO_AREAS1 = FALSE;

			}
			//Sen�o se o valor do sinal AD lido de cada �rea for maior que o sinal limite permitido de sinal para �rea ent�o
			else if ( (Valor1[AREA1] > 200 && Valor[AREA2] > 200) && (Valor1[AREA3] > 200 && Valor1[AREA4] > 200) &&
					  (Valor1[AREA5] > 200 && Valor[AREA6] > 200) && (Valor1[AREA7] > 200 && Valor1[AREA8] > 200)
					  && flag_antena_rx_sem_sinal != FALSE)	 //Adicionado flag para evitar repeticao
			{
				flag_antena_rx_sem_sinal = FALSE;  //Armazena na flag_antena_rx_sem_sinal a informa��o FALSE
				LENDO_AREAS1 = FALSE;
				LIGA_SINALEIRA_VERDE; //Liga a sinaleira vermelha
				FALHA_DAS_BOBINAS = FALSE;
				travado = FALSE;
				Solenoide_DisableEvent();		//Desativa evento que gera PWM solenoide
				Solenoide_Disable();			//Desativa Timer que gera o evento do PWM solenoide
				tempo_trava = 0;				//Reseta contador de tempo para ativar PWM da solenoide
				pwm_trava = 0;					//Reseta contador PWM da solenoide
				DESLIGA_TRAVA; 					//Desenergiza a trava
				tela = TELA_INICIAL; //tela a ser apresentada � TELA_INICIAL
				estado_LCD = ATUALIZA_LCD; //estado_LCD � ATUALIZA_LCD para exibir a mensagem da TELA_INICIAL
			}
		}

		FlagADC = 0; //Zera a flag FlagADC para realizar novas leituras no AD
		LENDO_AREAS = FALSE; //Armazena na vari�vel LENDO_AREAS a informa��o FALSE para poder habilitar a realiza��o de novas leituras no AD
	}
	estado = ESTADO_LER_TECLAS;
}
/******************************************************************************/

/*** Fun��es do BARGRAPH ***/
void AcendeBargraph(void) //PERMITE ACENDER CORRETAMENTE OS LEDS DO BARGRAPH CONFORME MAIOR NIVEL DE SINAL RECEBIDO EM UMA DAS �REAS
{
	static word area_valor_maior = 0; //Define a vari�vel area_valor_maior com valor zero para poder apresentar no bargraph a �rea com maior sinal

	z = 0; //Armazena na vari�vel z o valor zero

	for(x = 0;x < 8;x++) //La�o com x das 8 �reas para comparar cada �rea contra todas as �reas
	{
		for(y = 0;y < 8;y++) //La�o com y das 8 �reas para variar as �reas e comparar com a �rea x
		{
			if(Valor[x] >= Valor[y]) //Se valor da �rea fixada em x for maior ou igual a valor y ent�o incrementa z
			{
				z++; //Incrementa z
			}
			if(z == 8) //Se z for igual a 8 significa que a �rea comparada com as demais � a maior de todas ent�o
			{
				area_valor_maior = x; //Armazena na vari�vel area_valor_maior a �rea que estava sendo comparada em x
				x = 8; //Para poder sair do primeiro la�o for
				y = 8; //Para poder sair do segundo la�o for
			}
		}
		z = 0; //Zera a vari�vel zero
	}

	if(fim_sinaleira == FALSE) //Se fim_sinaleira � FALSE ent�o
	{
		if(APAGA_BARGRAPH == FALSE) //Se APAGA_BARGRAPH for igual a FALSE ent�o
		{
			int nivel = ((NIVEL_ZERO * (101 - buffer_sensibilidade[area_valor_maior + 1])) / 100) /11; //faz + 1 no buffer_sensibilidade porque o vetor 0 � a sensibilidade de todas as �reas e calcula o nivel do bargraph
			valor_bargraph = (int)(Valor[area_valor_maior] / nivel); //Adaptad o valor_bargraph de acordo com o nivel de sensibilidade
			if(valor_bargraph >= 10) //Se valor_bargraph for maior ou igual a 10 ent�o
			{
				valor_bargraph = 10; //Armazena na vari�vel valor_bargraph o valor 10
			}
		}
		else if(APAGA_BARGRAPH == TRUE) //Sen�o se APAGA_BARGRAPH for igual a TRUE ent�o
		{
			valor_bargraph = 0; //Armazena na vari�vel valor_bargraph o valor 0
			APAGA_BARGRAPH = FALSE; //Armazena na vari�vel APAGA_BARGRAPH a informa��o FALSE
		}
		if (valor_bargraph == 0) //Se valor_bargraph for igual a zero ent�o
		{
			ACENDE_NIVEL0; //Apaga os leds do bargraph
		}
		else if (valor_bargraph == 1) //Sen�o se valor_bargraph for igual a 1 ent�o
		{
			ACENDE_NIVEL1; //Acende at� o primeiro led do bargraph
		}
		else if(valor_bargraph == 2) //Sen�o se valor_bargraph for igual a 2 ent�o
		{
			ACENDE_NIVEL2; //Acende at� o segundo led do bargraph
		}
		else if(valor_bargraph == 3) //Sen�o se valor_bargraph for igual a 3 ent�o
		{
			ACENDE_NIVEL3; //Acende at� o terceiro led do bargraph
		}
		else if(valor_bargraph == 4) //Sen�o se valor_bargraph for igual a 4 ent�o
		{
			ACENDE_NIVEL4; //Acende at� o quarto led do bargraph
		}
		else if(valor_bargraph == 5) //Sen�o se valor_bargraph for igual a 5 ent�o
		{
			ACENDE_NIVEL5; //Acende at� o quinto led do bargraph
		}
		else if(valor_bargraph == 6) //Sen�o se valor_bargraph for igual a 6 ent�o
		{
			ACENDE_NIVEL6; //Acende at� o sexto led do bargraph
		}
		else if(valor_bargraph == 7) //Sen�o se valor_bargraph for igual a 7 ent�o
		{
			ACENDE_NIVEL7; //Acende at� o s�timo led do bargraph
		}
		else if(valor_bargraph == 8) //Sen�o se valor_bargraph for igual a 8 ent�o
		{
			ACENDE_NIVEL8; //Acende at� o oitavo led do bargraph
		}
		else if(valor_bargraph == 9) //Sen�o se valor_bargraph for igual a 9 ent�o
		{
			ACENDE_NIVEL9; //Acende at� o nono led do bargraph
		}
		else if(valor_bargraph == 10) //Sen�o se valor_bargraph for igual a 10 ent�o
		{
			ACENDE_NIVEL10; //Acende at� o d�cimo led do bargraph
		}
	}
}
/******************************************************************************/

/*** Fun��es do BUZZER ***/
void Nota_Musical(word nota) //Define a nota m�sical
{
	static word valor_modulo;										//Define a vari�vel valor_modulo para c�lculos da frequ�ncia da nota
	FTM2_SC = (FTM_SC_CLKS(0x01) | FTM_SC_PS(0x02));				//PRESCALE = 60MHz/4 - 15MHz - Utilizado o bus clock que � o system clock - olhar no TU1.c
	valor_modulo = 15000000/nota;									//Calcula o valor do modulo para por no FTM2_MOD e definir a frequ�ncia da nota desejada
	FTM2_CNT = 0;													//Inicializa FTM2_CNT para poder alterar FTM2_MOD
	FTM2_MOD = valor_modulo;										//Define o per�odo que no caso � a frequ�ncia da nota - olhar no TU1.c
	FTM2_C0V = (valor_modulo/2); 									//Duty cycle 50% - olhar no TU1.c
	PWM_BUZZER_SetRatio8( (buffer_buzzer[BUZZER_VOLUME]*180) /10 );	//Define o volume da nota
}

void SetTomBuzzer (word tom) //Seta o tom do buzzer
{
	word nota1;
	word nota2;
	switch (tom) //Conforme tom executa o case espec�fico
	{
		case 1:
		{
			nota1=DO;
			nota2=RE;
			break;
		}
		case 2:
		{
			nota1=RE;
			nota2=MI;
			break;
		}
		case 3:
		{
			nota1=MI;
			nota2=FA;
			break;
		}
		case 4:
		{
			nota1=FA;
			nota2=SOL;
			break;
		}
		case 5:
		{
			nota1=SOL;
			nota2=LA;
			break;
		}
		case 6:
		{
			nota1=LA;
			nota2=SI;
			break;
		}
		case 7:
		{
			nota1=DO;
			nota2=FA;
			break;
		}
		case 8:
		{
			nota1=RE;
			nota2=SOL;
			break;
		}
		case 9:
		{
			nota1=MI;
			nota2=LA;
			break;
		}
		case 10:
		{
			nota1=FA;
			nota2=SI;
			break;
		}
		default:
		return;
	}

	Nota_Musical(nota1); //Emite nota musical DO
	AGUARDA_Waitms(60); //Aguarda 60 milisegundos
	PWM_BUZZER_Disable(); //Desabilita o buzzer
	AGUARDA_Waitms(60);  //Aguarda 60 milisegundos

	Nota_Musical(nota2); //Emite nota musical RE
	AGUARDA_Waitms(60); //Aguarda 60 milisegundos
	PWM_BUZZER_Disable(); //Desabilita o buzzer
	AGUARDA_Waitms(60);  //Aguarda 60 milisegundos

}

void TocaTomBuzzer(void)
{
	SetTomBuzzer (buffer_buzzer[BUZZER_TOM]); //Toca sonoramente a nota m�sical e o tom definido
	PWM_BUZZER_SetRatio8(0); //Coloca em zero o PWM do buzzer
}

/******************************************************************************/

/*** Fun��es da CAN ***/
void fnCarregaVersoes(void) //Carrega as vers�es dos perif�ricos conectados a rede CAN
{
	if(var_Tempo_Presenca >= 2) //Se var_Tempo_Presenca for maior ou igual a 2 (segundos) ent�o
	{
		if(estadoPresencaAnt == GET_FONTE) //Se estadoPresencaAnt for igual a GET_FONTE ent�o, ou seja, se antes tava verificando a presen�a da FONTE na rede CAN ent�o agora
		{
			estadoPresenca = GET_GRAVADOR; //Armazena na vari�vel estadoPresenca a informa��o GET_GRAVADOR para verificar a presen�a do GRAVADO na rede CAN
		}
		else if(estadoPresencaAnt == GET_GRAVADOR) //Sen�o se estadoPresencaAnt for igual a GET_GRAVADOR ent�o, ou seja, se antes tava verificando a presen�a do GRAVADOR na rede CAN ent�o agora
		{
			estadoPresenca = GET_FONTE; //Armazena na vari�vel estadoPresenca a informa��o GET_FONTE para verificar a presen�a da FONTE na rede CAN
		}
		var_Tempo_Presenca = 0; //Zera o contador de tempo var_tempo_Presenca para contar 2 segundos de verifica��o de presen�a de um dispositivo na rede CAN
	}
	switch(estadoPresenca )//Conforme estadoPresenca executa o case espec�fico
	{
		case GET_FONTE: //Caso GET_FONTE ent�o
		{
  			if(buffer_Presencas[CONST_PLACA_FONTE]) //Se buffer_Presencas[CONST_PLACA_FONTE] for 1 indicando que a FONTE foi encontrada na rede CAN
  			{
  				SendCan(FONTE_CAN,GET_TENSOES); //Requisita as informa��es de tens�es AC e DC da fonte
  				estadoPresencaAnt = estadoPresenca; //Armazena na vari�vel estadoPresencaAnt o conte�do de estadoPresenca que � o dispositivo que esta sendo pesquisado na rede CAN neste momento
  				estadoPresenca = 0; //Zera a vari�vel estadoPresenca
  			}
  			else //Sen�o
  			{
  				estadoPresenca = GET_GRAVADOR; //Armazena na vari�vel estadoPresenca a informa��o GET_GRAVADOR pois � o pr�ximo dispositivo que vai ser pesquisado na rede CAN
  			}
			break;
		}
		case GET_GRAVADOR: //Caso GET_GRAVADOR ent�o
		{
			estadoPresenca = 0; //Zera a vari�vel estadoPresenca
  			estado = ESTADO_CARREGA_DADOS; //Estado a ser executado agora � ESTADO_CARREGA_DADOS
  			break;
		}
	  	break;
	}
}

void fnGetAlives(void) //Verifica quem esta presente na rede CAN e sinaliza atrav�s de um vetor de flag
{
	if(var_Tempo_Presenca >= 2) //Se var_Tempo_Presenca for maior ou igual a 2 ent�o_
	  {
		  if(estadoPresencaAnt == GET_FONTE) //Se estadoPresencaAnt for igual a GET_FONTE ent�o, ou seja, se antes tava verificando a presen�a da FONTE na rede CAN ent�o agora
		  {
			  estadoPresenca = GET_GRAVADOR; //Armazena na vari�vel estadoPresenca a informa��o GET_GRAVADOR para verificar a presen�a do GRAVADO na rede CAN
		  }
		  else if(estadoPresencaAnt == GET_GRAVADOR) //Sen�o se estadoPresencaAnt for igual a GET_GRAVADOR ent�o, ou seja, se antes tava verificando a presen�a do GRAVADOR na rede CAN ent�o agora
		  {
			  estadoPresenca = 0; //Zera a vari�vel estadoPresenca
			  estado = ESTADO_CARREGA_VERSOES; //Estado a ser executado � ESTADO_CARREGA_VERSOES
		  }
		  var_Tempo_Presenca = 0; //Zera o contador de tempo var_tempo_Presenca para contar 2 segundos de verifica��o de presen�a de um dispositivo na rede CAN
	  }
	  LePresencas(); //L� as presen�a dos perif�ricos conectados a CAN
}

void LePresencas(void) //Le a presen�a de todas as placas
{
	switch(estadoPresenca) //Conforme vari�vel estadoPresenca executa o caso espec�fico
	{
		case GET_FONTE: //Caso GET_FONTE ent�o
		{
			SendCan(FONTE_CAN,GET_ALIVE); //Requisita o n�mero serial da FONTE CAN
			estadoPresencaAnt = estadoPresenca; //Armazena na vari�vel estadoPresencaAnt a informa��o contida em estadoPresenca, ou seja, o dispositivo que esta sendo procurado no momento
			estadoPresenca = 0; //Zera a vari�vel estadoPresenca
			delay_ms(100); //Espera 100 milisegundos
			break;
		}
		case GET_GRAVADOR: //Caso GET_GRAVADOR ent�o
		{
			SendCan(AUDIO_CAN,GET_ALIVE); //Requisita o n�mero serial da AUDIO_CAN
			estadoPresencaAnt = estadoPresenca; //Armazena na vari�vel estadoPresencaAnt a informa��o contida em estadoPresenca, ou seja, o dispositivo que esta sendo procurado no momento
			estadoPresenca = 0; //Zera a vari�vel estadoPresenca
			delay_ms(100); //Espera 100 milisegundos
			break;
		}
		break;
	}
}

void SendCan(LDD_CAN_TMessageID dst_ID,byte mensagem) //Envia informa��es pela CAN informando o destino (FONTE = endere�o, por exemplo) e a mensagem (GET_FONTE por exemplo)
{
	Frame.FrameType = LDD_CAN_DATA_FRAME; //Armazena na estrutura Frame o tipo de frame dos dados que � LDD_CAN_DATA_FRAME (Tipo de frame de dados recebidos ou transmitidos)
    Frame.MessageID = dst_ID; //Armazena na estrutura Frame o ID do dispositivo que vai ser requisitado informa��es
    OutData[0] = PAINEL_CAN; //Armazena no vetor OutData[0] o ID de quem esta requisitando as informa��es
    OutData[1] = mensagem; //Armazena no vetor OutData[1] qual a informa��o que deseja ser requisitada
    Frame.Data = OutData; //Armazena na estrutura Frame o vetor OutData que cont�m as informa��es a serem requisitadas ou enviadas para o destino
    Frame.Length = sizeof(OutData); //Armazena na estrutura Frame o tamanho dos dados de OutData que no caso sempre � no m�ximo 8 bytes
    DataFrameTxFlg = 0; //Zera a flag de sinaliza��o de fim de transmiss�o DataFrameTxFlg para zero
    timeout_can = 0; //Zera a vari�vel timeout_can contadora de tempo para que a comunica��o ocorra dentro do tempo determinado, se passar deste tempo a comunica��o n�o esta presente
    Error = CAN_SendFrame(MyCANPtr,1U,&Frame); //Envia o frame configurado acima para o dispositivo selecionado

}

void TrataCAN(void) //Trata as informa��es recebidas pela CAN
{
	static byte endereco = 0; //Define a vari�vel endereco com 8 bytes e zera a mesma neste momento

	Frame.Data = InData; //Armazena na estrutura Frame o vetor InData que cont�m as informa��es a serem requisitadas ou enviadas para o destino
	Error = CAN_ReadFrame(MyCANPtr,0U,&Frame); //Envia o frame configurado acima para o dispositivo selecionado

	switch(InData[0]) //Conforme valor recebido em InData[0] vai para o case espec�fico
	{
		case FONTE_CAN: //Caso FONTE_CAN
		{
			switch(InData[1]) //Conforme valor recebido em InData[1] vai para o case espec�fico
			{
				case GET_ALIVE: //Caso GET_ALIVE - requisitar n�mero serial
				{
					for(x = 0;x < 6;x++) //L� os 6 n�meros seriais recebido de InData[2] a InData[8] na vari�vel StcPlacas[CONS_PLACA_FONTE].Serial_Number_CAN[x] de x = 0 a x = 6
					{
						StcPlacas[CONST_PLACA_FONTE].Serial_Number_CAN[x] = InData[x + 2];
					}
					var_Tempo_Presenca = 0; //Zera o contador de tempo var_tempo_Presenca para contar 2 segundos de verifica��o de presen�a de um dispositivo na rede CAN
					estadoPresenca = GET_GRAVADOR; //Atualiza a vari�vel estadoPresenca com a informa��o GET_GRAVADOR para ler este dispositivo
					buffer_Presencas[CONST_PLACA_FONTE] = 1; //Armazena na vari�vel buffer_Presencas[CONST_PLACA_FONTE] o valor 1 para indicar que a FONTE esta presente na rede CAN
					estado = ESTADO_GET_ALIVES; //Estado a ser executado � ESTADO_GET_ALIVES
					break;
				}
				case GET_TENSOES: //CAso GET_TENSOES - requisita para a fonte as tens�es AC e DC
				{
					var_tensao_cinco = InData[2]; //Armazena na vari�vel var_tensao_cinco o conte�do de InData[2] - armazena a tens�o dos +5 volts
					var_tensao_quinze = InData[3]; //Armazena na vari�vel var_tensao_quize o conte�do de InData[3] - armazena a tens�o dos +15 volts
					var_tensao_menos_quinze = InData[4]; //Armazena na vari�vel var_tensao_meno_quinze o conte�do de Indata[4] - armazena a tens�o dos -15 volts
					var_tensao_rede = InData[5]; //Armazena na vari�vel var_tensao_rede o conte�do de InData[5] - armazena a tens�o AC
					var_tensao_bateria = ((InData[6] << 8) + InData[7]); //Armazena na vari�vel var_tensao_bateria o valor separado em 2 bytes da tens�o da bateria em InData[6] e InData[7]
					if(var_tensao_chaveada >= CONST_LIMITE_INFERIOR_FONTE) //Se tens�o da fonte chaveada for maior que 23,5V ent�o tem rede AC
					{
						LIGA_AC; //Liga o led AC
						if((estado_anterior_AC == DES && estado_atual_AC == DES) || (estado_anterior_AC == LIG && estado_atual_AC == DES))
						{

							if(var_tensao_bateria > CONST_LIMITE_INFERIOR_BATERIA && LEITURA_FLASH_FINALIZADA == SIM) //tens�o maior que 22,5V esta conectada a bateria e carregada
							{
								estado_anterior_AC = DES;
								estado_atual_AC = LIG;
								fnGravaAuditoria(190,estado_anterior_AC,estado_atual_AC,'D','P'); //AC ligado e BATERIA conectada e carregada
							}
							else if(var_tensao_bateria < 30 && LEITURA_FLASH_FINALIZADA == SIM) //tens�o menor que 3,0V esta desconectada a bateria
							{
								estado_anterior_AC = DES;
								estado_atual_AC = LIG;
								fnGravaAuditoria(191,estado_anterior_AC,estado_atual_AC,'D','P'); //AC ligado e BATERIA desconectada
							}
						}
					}
					else if(var_tensao_chaveada < (CONST_LIMITE_INFERIOR_FONTE - 5)) //Sen�o
					{
						DESLIGA_AC; //Desliga o led AC

						if((estado_anterior_AC == DES && estado_atual_AC == DES) || (estado_anterior_AC == DES && estado_atual_AC == LIG))
						{
							if(var_tensao_bateria >= CONST_LIMITE_INFERIOR_BATERIA && LEITURA_FLASH_FINALIZADA == SIM)
							{
								estado_anterior_AC = LIG;
								estado_atual_AC = DES;
								fnGravaAuditoria(190,estado_anterior_AC,estado_atual_AC,'D','P'); //AC desligado e BATERIA conectada e carregada
							}
						}
					}
					if(var_tensao_bateria >= CONST_LIMITE_INFERIOR_BATERIA)
					{
						LIGA_BAT; //Liga o led BAT
						PISCA_LED_BAT = FALSE; //Armazena na vari�vel PISCA_LED_BAT a informa��o FALSE para n�o piscar o led BAT

						if((estado_anterior_BAT == DESCARREGADA && estado_atual_BAT == DESCARREGADA) || (estado_anterior_BAT == CARREGADA && estado_atual_BAT == DESCARREGADA)) //Se var_tensao_bateria for maior que 22,5V ent�o
						{

							if(LEITURA_FLASH_FINALIZADA == SIM)
							{
								estado_anterior_BAT = DESCARREGADA;
								estado_atual_BAT = CARREGADA;
								fnGravaAuditoria(192,estado_anterior_BAT,estado_atual_BAT,'D','P'); //BATERIA conectada e carregada
							}
						}
					}
					else if(var_tensao_bateria < 100)
					{
						DESLIGA_BAT; //Desliga o led BAT
						PISCA_LED_BAT = FALSE; //Armazena na vari�vel PISCA_LED_BAT a informa��o FALSE para n�o piscar o led BAT
						if((estado_anterior_BAT == DESCARREGADA && estado_atual_BAT == DESCARREGADA) || (estado_anterior_BAT == DESCARREGADA && estado_atual_BAT == CARREGADA)) //Sen�o se var_tensao_bateria for menor que 10,0V ent�o
						{

							if(LEITURA_FLASH_FINALIZADA == SIM)
							{
								estado_anterior_BAT = CARREGADA;
								estado_atual_BAT = DESCARREGADA;
								fnGravaAuditoria(192,estado_anterior_BAT,estado_atual_BAT,'D','P'); //BATERIA desconectada
							}
						}
					}
					else if(var_tensao_bateria > CONST_LIM_BATERIA_DESCARREGADA && var_tensao_bateria < CONST_LIMITE_INFERIOR_BATERIA) //Sen�o se var_tensao_bateria for maior que 21.5V e var_tensao_bateria for menor que 22,5V ent�o
					{
						PISCA_LED_BAT = TRUE; //Armazena na vari�vel PISCA_LED_BAT a informa��o TRUE para piscar o led BAT
					}
					if(var_tensao_bateria < CONST_LIM_BATERIA_DESCARREGADA) //Se var_tensao_bateria for menor que 21,5V ent�o
					{
						percentual_bat = 0; //Armazena na vari�vel percentual_bat o valor zero porcento
					}
					else if(var_tensao_bateria >= CONST_LIM_MAX_BATERIA) //Sen�o se var_tensao_bateria for maior ou igual a 25,0V ent�o
					{
						percentual_bat = 100; //Armazena na vari�vel percentual_bat o valor cem porcento
					}
					else //Sen�o
					{
						//Armazena em percentual_bat o valor percentual da bateria, exemplo:
						//(100 * (237 - 215)) / (250 - 215) = (100 * 22) / (35) = 62.85 = 63%
						percentual_bat = (100 * (var_tensao_bateria - CONST_LIM_BATERIA_DESCARREGADA)) / (CONST_LIM_MAX_BATERIA - CONST_LIM_BATERIA_DESCARREGADA);
					}
					ERRO_CAN = FALSE; //Armazena na vari�vel ERRO_CAN a informa��o FALSE para informar que houve problema na CAN

					break;
				}
				case GET_TENSOES1: //CAso GET_TENSOES - requisita para a fonte a tens�o da fonte chaveada
				{
					var_tensao_chaveada = ((InData[2] << 8) + InData[3]); //Armazena na vari�vel var_tensao_bateria o valor separado em 2 bytes da tens�o da bateria em InData[6] e InData[7]
					estado_da_fonte = InData[4];
					ERRO_CAN = FALSE; //Armazena na vari�vel ERRO_CAN a informa��o FALSE para informar que houve problema na CAN

					break;
				}
				case GET_BATERIA_BAIXA: //Armazena em auditoria a data e a hora do evento e manda
				{
					/*** Fun��es dos LOGS de AUDITORIAS ***/
					//parametro: Conforme tabela indica se 91 por exemplo � sensibilidade da �rea 1
					//valor_velho: Valor que tinha anteriormente
					//valor_novo: Valor que foi inserido atualmente
					//operador: T para t�cnico ou G para gerente ou D para detector
					//dispositivo: P para painel ou C para controle ou S para software ou B para bateria
					fnGravaAuditoria(192, CARREGADA, BATABAIXO215, 'D', 'B'); //Informa AC desligado e bateria abaixo de 21,5V e a hora, min, dia, mes e ano do desligamento automatico
					bateria_baixa = SIM;
					ERRO_CAN = FALSE; //Armazena na vari�vel ERRO_CAN a informa��o FALSE para informar que houve problema na CAN
					break;
				}
				default: //Caso nenhuma das alternativas acima ent�o
				{
					var_tensao_cinco = InData[1]; //Armazena na vari�vel var_tensao_cinco o conte�do recebido no vetor InData[1]
					var_tensao_quinze = InData[2]; //Armazena na vari�vel var_tensao_quinze o conte�do recebido no vetor InData[2]
					var_tensao_menos_quinze = InData[3]; //Armazena na vari�vel var_tensao_menos_quinze o conte�do recebido no vetor InData[3]
					var_tensao_rede = InData[4]; //Armazena na vari�vel var_tensao_rede o conte�do recebido no vetor InData[4]
					var_tensao_bateria = ((InData[5] << 8) + InData[6]); //Armazena na vari�vel var_tensao_bateria o conte�do recebido no vetor InData[5] deslocado 8 bytes a esquerda e somado com InData[6]
					if(var_tensao_rede > CONST_LIMITE_INFERIOR_AC) //Se var_tensao_rede for maior que 108V ent�o
					{
						LIGA_AC; //Liga led AC
					}
					else
					{
						DESLIGA_AC; //Desliga led AC
					}
					if(var_tensao_bateria < CONST_LIMITE_INFERIOR_BATERIA) //Se var_tensao_bateria for menor que 22,5V ent�o
					{
						LIGA_BAT; //Liga led BAT
					}
					else //Sen�o
					{
						DESLIGA_BAT; //Desliga led BAT
					}
					delay_ms(10); //Espera 10ms
				}
				break;
			}
			break;
		}
		case ZC_CAN:
			if(InData[1]== 0 || InData[1]== 1){
				statusPGDM = InData[1];
			}
			else if (InData[1] == 2){
				erroAgata = BURLA;
			}
			break;
		default:
		{
			break;
		}
		break;
	}
	estado_CAN = ESTADO_ESPERA; //Armazena na vari�vel estado_CAN o valor ESTADO_ESPERA
}
/******************************************************************************/

/*** Fun��es do CONTROLE REMOTO ***/
void VALIDA_CODIGO(void) //Fun��o que permite cadastrar os controles remotos e apagar todos os controles remotos
{

	if(start_remoto > 1800 && INICIA_CONTADOR_PULSOS == TRUE) //Se start_remoto for maior que 6000ms ou 6 segundos e INICIA_CONTADOR_PULSO for TRUE ent�o
	{
		ACAO_CONTROLE = APAGAR; //Armazena na vari�vel ACAO_CONTROLE a informa��o APAGAR
		INICIA_CONTADOR_PULSOS = FALSE; //Torna a flag INICIA_CONTADOR_PULSOS para FALSE para poder mensurar corretamente a largura do pulso
		start_remoto = 0; //Zera a vari�vel start_remoto para mensurar os pr�ximos pulsos
		pulsos = 0; //Zera a vari�vel pulsos para poer contar a quantidade correta de pulsos

	}
	else if(ACAO_CONTROLE == AVALIA_CONTROLE && start_remoto > 60 && start_remoto < 160 && INICIA_CONTADOR_PULSOS == TRUE) //Verifica se est� no modo de opera��o de detec��o e sinal VT � trem de pulso
	{
		start_remoto1 = 0;
		pulsos++; //Incrementa pulsos
		tempoVtInativo = 0;
		INICIA_CONTADOR_PULSOS = FALSE; //Torna a flag INICIA_CONTADOR_PULSOS para FALSE para poder mensurar corretamente a largura do pulso
	}
	else if(ACAO_CONTROLE == AVALIA_CONTROLE && (start_remoto >= 160 || (tempoVtInativo > 200 && pulsos < 5))){
		pulsos = 0;
		tempoVtInativo = 0;
	}
	else if(ACAO_CONTROLE == CADASTRAR1 && start_remoto > 800 && start_remoto < 1500 && INICIA_CONTADOR_PULSOS == TRUE) //Sen�o se start_remoto for maior que 800ms e menor que 1200ms(Alterado limite m�x. para 1500) e INICIA_CONTADOR_PULSOS for igual a TRUE ent�o
	{
		ACAO_CONTROLE = CADASTRAR; //Armazena na vari�vel ACAO_CONTROLE a informa��o CADASTRAR
		INICIA_CONTADOR_PULSOS = FALSE; //Torna a flag INICIA_CONTADOR_PULSOS para FALSE para poder mensurar corretamente a largura do pulso
		start_remoto1 = 0;
		tela = TELA_PRESSIONE_QUALQUER_TECLA_DO_CONTROLE;
		Atualiza_LCD();
	}
	else if(ACAO_CONTROLE == CADASTRAR && start_remoto > 250 && start_remoto < 750 && INICIA_CONTADOR_PULSOS == TRUE) //Sen�o se ACAO_CONTROLE for igual a CADASTRAR e start_remoto for maior que 250ms e menor que 750ms e INICIA_CONTADOR_PULSOS for igual a TRUE ent�o
	{
		INICIA_CONTADOR_PULSOS = FALSE; //Torna a flag INICIA_CONTADOR_PULSOS para FALSE para poder mensurar corretamente a largura do pulso
		//ACAO_CONTROLE = CADASTRAR1; //Armazenar na vari�vel ACAO_CONTROLE a informa��o CADASTRAR1 que no caso seria a leitura dos pulsos para confirmar se novo cadastramento ou cadastramento existente
		start_remoto1 = 0; //Armazena na vari�vel start_remoto1 o valor zero
		pulsos = 0; //Zera a vari�vel pulsos para poer contar a quantidade correta de pulsos
		RESULTADO_CONTROLE = CADASTRADO; //Armazena na vari�vel RESULTADO_CONTROLE a informa��o CADASTRADO
		ACAO_CONTROLE = NENHUM; //Armazena na vari�vel ACAO_CONTROLE a informa��o NENHUM
		INICIA_CONTADOR_PULSOS = FALSE; //Torna a flag INICIA_CONTADOR_PULSOS para FALSE para poder mensurar corretamente a largura do pulso
		start_remoto = 0; //Zera a vari�vel start_remoto
		pulsos = 0; //Zera a vari�vel pulsos para poer contar a quantidade correta de pulsos
		numero_controles++; //Incrementa numero_controles
		Write_Buffer_FLASH[0] = numero_controles; //Escreve o valor do numero_controles no vetor para grava��o na mem�ria FLASH
		ESCREVE_FLASH_INTERNA(endFLASHNumeroControles,1,0); //Escreve na mem�ria FLASH o numero_controles alterado no endere�o especificado
	}
	else if(ACAO_CONTROLE == CADASTRAR && start_remoto > 60 && start_remoto < 160 && INICIA_CONTADOR_PULSOS == TRUE) //Sen�o se ACAO_CONTROLE for igual a CADASTRAR e star_remoto for maior que 60ms e menor que 140ms e INICIA_CONTADOR_PULSOS for igual a TRUE ent�o
	{
		pulsos++; //Incrementa pulsos
		INICIA_CONTADOR_PULSOS = FALSE; //Torna a flag INICIA_CONTADOR_PULSOS para FALSE para poder mensurar corretamente a largura do pulso
		if(pulsos == 3 && start_remoto1 < 15000) //Se pulsos for igual a 5 e start_remoto1 for menor que 15000ms ou 15 segundos ent�o
		{
			RESULTADO_CONTROLE = JA_CADASTRADO; //Armazena na vari�vel RESULTADO_CONTROLE a informa��o JA_CADASTRADO
			ACAO_CONTROLE = NENHUM; //Armazena na vari�vel ACAO_CONTROLE a informa��o NENHUM
			INICIA_CONTADOR_PULSOS = FALSE; //Torna a flag INICIA_CONTADOR_PULSOS para FALSE para poder mensurar corretamente a largura do pulso
			start_remoto = 0; //Zera a vari�vel start_remoto
			start_remoto1 = 0; //Zera a vari�vel start_remoto1
			pulsos = 0; //Zera a vari�vel pulsos para poer contar a quantidade correta de pulsos
		}
	}
	else if(ACAO_CONTROLE != AVALIA_CONTROLE && start_remoto1 > 18500) //Se pssou 18,5s e n�o foi cadastrado controle, retorna msg que n�o houve cadastro
			{
				RESULTADO_CONTROLE = NENHUM; //Armazena na vari�vel RESULTADO_CONTROLE a informa��o NENHUM
				ACAO_CONTROLE = NENHUM; //Armazena na vari�vel ACAO_CONTROLE a informa��o NENHUM
				INICIA_CONTADOR_PULSOS = FALSE; //Torna a flag INICIA_CONTADOR_PULSOS para FALSE para poder mensurar corretamente a largura do pulso
				start_remoto = 0; //Zera a vari�vel start_remoto
				start_remoto1 = 0; //Zera a vari�vel start_remoto1
				pulsos = 0; //Zera a vari�vel pulsos para poder contar a quantidade correta de pulsos
			}
	/*else if(ACAO_CONTROLE == CADASTRAR1 && start_remoto > 60 && start_remoto < 160 && INICIA_CONTADOR_PULSOS == TRUE) //Sen�o se ACAO_CONTROLE for igual a CADASTRAR1 e start_remoto for maior que 60ms e menor que 140ms e INICIA_CONTADOR_PULSOS for igual a TRUE ent�o
	{
		pulsos++; //Incrementa pulsos
		INICIA_CONTADOR_PULSOS = FALSE; //Torna a flag INICIA_CONTADOR_PULSOS para FALSE para poder mensurar corretamente a largura do pulso
		if(pulsos == 5 && start_remoto1 < 15000) //Se pulsos for igual a 5 e start_remoto1 for menor que 15000ms ou 15 segundos ent�o
		{
			RESULTADO_CONTROLE = CADASTRADO; //Armazena na vari�vel RESULTADO_CONTROLE a informa��o CADASTRADO
			ACAO_CONTROLE = NENHUM; //Armazena na vari�vel ACAO_CONTROLE a informa��o NENHUM
			INICIA_CONTADOR_PULSOS = FALSE; //Torna a flag INICIA_CONTADOR_PULSOS para FALSE para poder mensurar corretamente a largura do pulso
			start_remoto = 0; //Zera a vari�vel start_remoto
			start_remoto1 = 0; //Zera a vari�vel start_remoto1
			pulsos = 0; //Zera a vari�vel pulsos para poer contar a quantidade correta de pulsos
			numero_controles++; //Incrementa numero_controles
			Write_Buffer_FLASH[0] = numero_controles; //Escreve o valor do numero_controles no vetor para grava��o na mem�ria FLASH
			ESCREVE_FLASH_INTERNA(endFLASHNumeroControles,1,0); //Escreve na mem�ria FLASH o numero_controles alterado no endere�o especificado
		}
		else if(pulsos == 5 && start_remoto1 > 15000) //Sen�o se pulsos for igual a 5 e start_remoto1 for maior que 15000ms ou 15s ent�o
		{
			RESULTADO_CONTROLE = NENHUM; //Armazena na vari�vel RESULTADO_CONTROLE a informa��o NENHUM
			ACAO_CONTROLE = NENHUM; //Armazena na vari�vel ACAO_CONTROLE a informa��o NENHUM
			INICIA_CONTADOR_PULSOS = FALSE; //Torna a flag INICIA_CONTADOR_PULSOS para FALSE para poder mensurar corretamente a largura do pulso
			start_remoto = 0; //Zera a vari�vel start_remoto
			start_remoto1 = 0; //Zera a vari�vel start_remoto1
			pulsos = 0; //Zera a vari�vel pulsos para poder contar a quantidade correta de pulsos
		}
	}*/
	else INICIA_CONTADOR_PULSOS = FALSE;
}
/******************************************************************************/

void validaControle(){
	if(pulsos == 3) //Identifica que foi utilizado o primeiro controle cadastrado
	{
		INICIA_CONTADOR_PULSOS = FALSE; //Torna a flag INICIA_CONTADOR_PULSOS para FALSE para poder mensurar corretamente a largura do pulso
		tempoVtInativo = 0;
		start_remoto = 0;
		pulsos = 0;
		controlePressionado = indexControle[0];
		if(controlePressionado != 'A' || controlePressionado != 'B'){
			controlePressionado = 'B';
		}
	}
	else if(pulsos == 4) //Identifica que foi utilizado o segundo controle cadastrado
	{
		INICIA_CONTADOR_PULSOS = FALSE; //Torna a flag INICIA_CONTADOR_PULSOS para FALSE para poder mensurar corretamente a largura do pulso
		tempoVtInativo = 0;
		start_remoto = 0;
		pulsos = 0;
		controlePressionado = indexControle[1];
		if(controlePressionado != 'A' || controlePressionado != 'B'){
			controlePressionado = 'B';
		}
	}
	else if(pulsos == 5) //Identifica que foi utilizado o terceiro controle cadastrado
	{
		INICIA_CONTADOR_PULSOS = FALSE; //Torna a flag INICIA_CONTADOR_PULSOS para FALSE para poder mensurar corretamente a largura do pulso
		tempoVtInativo = 0;
		start_remoto = 0;
		pulsos = 0;
		controlePressionado = indexControle[2];
		if(controlePressionado != 'A' || controlePressionado != 'B'){
			controlePressionado = 'B';
		}
	}
	else{
		INICIA_CONTADOR_PULSOS = FALSE; //Torna a flag INICIA_CONTADOR_PULSOS para FALSE para poder mensurar corretamente a largura do pulso
		tempoVtInativo = 0;
		start_remoto = 0;
		pulsos = 0;
	}
}

/*** Fun��es de DELAY ***/
void delay_ms(word cont) //Fun��o que gasta tempo em milisegundos
{
	cont_ms = cont; //Armazena na vari�vel cont_ms o valor em cont passado na fun��o
	while(cont_ms > 0); //Enquanto cont_ms for maior que zero fica em loop
}

void delay_segundos(word cont) //Fun��o que gasta tempo em segundos
{
	cont_s = 0; //Armazena na vari�vel cont_s o valor zero
	cont_s = cont * 10; //Armazena na vari�vel cont_s o valor em cont passado na fun��o vezes 10
	FIM_TEMPO_DELAY_S = FALSE; //Armazena na flag FIM_TEMPO_DELAY_S a informa��o FALSE
	while(FIM_TEMPO_DELAY_S == FALSE && teclapressionada != teclaCancela); //Enquanto FIM_TEMPO_DELAY_S for igual a FALSE e teclapressionada n�o for igual a tecla CANCELA ent�o
}
/******************************************************************************/

/*** Fun��es do GRAVADOR DE VOZ ***/
void fnDiminuiTodoVolume(void) //Fun��o que diminui total o volume da mensagem de voz
{
	for(x = 0;x < 33;x++) //Diminui 32 unidades de volume, ou seja, total o volume da mensagem de voz do PAM8407
	{
		DOWN_CLEAR; //Reseta a tecla DOWN pra poder diminuir o volume da mensagem de voz
		delay_ms(50);
		DOWN_SET; //Seta a tecla SET para parar de abaixar o volume
		delay_ms(10);
	}
}

void fnDiminuiVolume(byte diminuir) //Fun��o que diminui o volume da mensagem de voz conforme valor passado em diminuir
{
	for(x = 0;x < diminuir;x++) //Diminui tantas unidades o volume da mensagem de voz
	{
		DOWN_CLEAR; //Reseta a tecla DOWN pra poder diminuir o volume da mensagem de voz
		delay_ms(50); //Espera 500ms
		DOWN_SET; //Seta a tecla SET para parar de abaixar o volume
		delay_ms(10);
	}
	fnReproduzMsgVoz(DETECCAO); //Reproduz a mensagem de voz como amostra, cada vez que altera o volume da mensagem de voz
	delay_ms(300);
	fnCortaMsgVoz(); //Corta msg de voz ap�s 300ms
}

void fnAumentaVolume(byte aumentar) //Fun��o que aumenta o volume da mensagem de voz conforme valor passado em aumentar
{
	for(x = 0;x < aumentar;x++) //Aumenta tantas unidades o volume da mensagem de voz
	{
		UP_CLEAR; //Reseta a tecla UP para poder aumentar o volume da mensagem de voz
		delay_ms(500); //Espera 500ms
		UP_SET; //Seta a tecla SET para parar de aumentar o volume
		delay_ms(10);
	}
	fnReproduzMsgVoz(DETECCAO); //Reproduz a mensagem de voz como amostra, cada vez que altera o volume da mensagem de voz
	delay_ms(300);
	fnCortaMsgVoz(); //Corta msg de voz ap�s 300ms
}

void fnCortaMsgVoz(void) //Fun��o que corta a mensagem de voz
{
	if(FLAG_PLACA_OUT_2022){
		SINAL_MSG_CLEAR;//NOTA: Na placa de 2022 o sinal para acionamento da voz esta invertido
	}	else{
		SINAL_MSG_SET; //Comanda a finaliza��o da emiss�o da mensagem de voz
	}
}

void fnReproduzMsgVoz(char origin) //Funcao que reproduz a mensagem de voz
{
	if(volume_mensagem_voz != 0){
//		if(FLAG_PLACA_OUT_2022){
//			SINAL_MSG_SET;		//NOTA: Na placa de 2022 o sinal para acionamento da voz esta invertido
//		}else{
			SINAL_MSG_CLEAR; 	//Comanda a emissao da mensagem de voz
//		}

		tempo_msg_voz = 0;
		INICIA_TEMPO_MSG_VOZ = TRUE; //Incia temporizador para parar mensagem de voz
//		if(origin == DETECCAO){
//			SINAL_MSG_CLEAR;
//			delay_ms(200);
//			SINAL_MSG_SET;
//		}else if (origin == BURLA){
//			SINAL_MSG_CLEAR;
//			delay_ms(600);
//			SINAL_MSG_SET;
//		}
	}
}
/******************************************************************************/

/*** Funcoes dos INFRAVERMELHOS ***/
/*
void fnLeInfras(void) //Fun��o que l� o estado dos infravermelhos para poder fazer a contagem de pessoas que entram e saem
{
	if(AMBOS_INFRAS_INATIVO) //Se ambos INFRAS INATIVOS ent�o n�o tem ningu�m na frente dos mesmos
	{
		flag_passagem = _AMBOS_INFRAS_INATIVO; //Armazena na vari�vel flag_passagem a informa��o _AMGOS_INFRAS_INATIVO
		estado_CONTADOR = ESTADO_GRAVA_CONTADOR; //Armazena na vari�vel estado_CONTADOR a informa��o ESTADO_GRAVA_CONTADOR
	}
	else if(INFRA1_ATIVO && INFRA2_INATIVO) //Sen�o se INFRA1_ATIVO (algu�m obstruindo o infra) e INFRA2_ATIVO (ningu�m obstruindo o infra)
	{
		flag_passagem = _INFRA1_ATIVO; //Armazena na vari�vel flag_passagem a informa��o _INFRA1_ATIVO
		estado_CONTADOR = ESTADO_GRAVA_CONTADOR; //Armazena na vari�vel estado_CONTADOR a informa��o ESTADO_GRAVA_CONTADOR
	}
	else if(INFRA1_INATIVO && INFRA2_ATIVO) //Sen�o se INFRA1_INATIVO e INFRA2_ATIVO ent�o n�o tem ningu�m na frente do INFRA1 e tem algu�m na frente do INFRA2
	{
		flag_passagem = _INFRA2_ATIVO; //Armazena na vari�vel flag_passagem a informa��o _INFRA2_ATIVO
		estado_CONTADOR = ESTADO_GRAVA_CONTADOR; //Armazena na vari�vel estado_CONTADOR a informa��o ESTADO_GRAVA_CONTADOR
	}
	else if(AMBOS_INFRAS_ATIVO) //Sen�o se ambos INFRAS ATIVOS ent�o tem algu�m na frente dos mesmos
	{
		flag_passagem = _AMBOS_INFRAS_ATIVO; //Armazena na vari�vel flag_passagem a informa��o _AMBOS_INFRAS_ATIVO
		estado_CONTADOR = ESTADO_GRAVA_CONTADOR; //Armazena na vari�vel estado_CONTADOR a informa��o ESTADO_GRAVA_CONTADOR
	}
}
*/

void fnLeInfras(void)
{
	if(INFRA1_ATIVO){
		if(analiseir == SIM && INFRA2_TEMP == 0) //Se analiseir for igual a SIM ent�o
		{
			entrou_na_porta = SIM; //Armazena na vari�vel entrou a informa��o SIM para informar que passou na sequ�ncia correta de entrada dos infras
			tempo_permissao = 0; //Zera a vari�vel tempo_permissao para liberar um tempo para poder detectar
		}
		INFRA1_TEMP = 1;
		infra1_timer = 0;
	}
	if(INFRA2_ATIVO){
		INFRA2_TEMP = 1;
		infra2_timer = 0;
	}

	if(INFRA1_TEMP == 0 && INFRA2_TEMP == 0) //Se ambos INFRAS INATIVOS ent�o n�o tem ningu�m na frente dos mesmos
	{
		flag_passagem = _AMBOS_INFRAS_INATIVO; //Armazena na vari�vel flag_passagem a informa��o _AMGOS_INFRAS_INATIVO
	}
	else if(INFRA1_TEMP == 1 && INFRA2_TEMP == 0) //Sen�o se INFRA1_ATIVO (algu�m obstruindo o infra) e INFRA2_ATIVO (ningu�m obstruindo o infra)
	{
		flag_passagem = _INFRA1_ATIVO; //Armazena na vari�vel flag_passagem a informa��o _INFRA1_ATIVO
	}
	else if(INFRA1_TEMP == 0 && INFRA2_TEMP == 1) //Sen�o se INFRA1_INATIVO e INFRA2_ATIVO ent�o n�o tem ningu�m na frente do INFRA1 e tem algu�m na frente do INFRA2
	{
		flag_passagem = _INFRA2_ATIVO; //Armazena na vari�vel flag_passagem a informa��o _INFRA2_ATIVO
	}
	else if(INFRA1_TEMP == 1 && INFRA2_TEMP == 1) //Sen�o se ambos INFRAS ATIVOS ent�o tem algu�m na frente dos mesmos
	{
		flag_passagem = _AMBOS_INFRAS_ATIVO; //Armazena na vari�vel flag_passagem a informa��o _AMBOS_INFRAS_ATIVO
	}
	switch(estado_passagem)
	{
		case 1:		//case ninguem
		{
			if(flag_passagem == _INFRA1_ATIVO)	//espera a entrada
			{
				estado_passagem = 2;
			}
			else if(flag_passagem == _INFRA2_ATIVO)	//espera terminar de sair
			{
				estado_passagem = 3;
			}
			break;
		}

		case 2:		//Entrando algu�m
		{
			if(flag_passagem == _AMBOS_INFRAS_ATIVO)	//espera finalizar a entrada
			{
				estado_passagem = 4;
				if(cont_sorteador == (numero_sorteado-1)) //Se cont_sorteador for igual a numero_sorteado entao
				{
					fnSortearNumero(); //Sorteia um n�mero
					cont_sorteador = 0; //Reinicializa cont_sorteador
					areas_detectadas = 0xFF; //Todas as �reas detectadas
					flag_area_detectada = 0xFF;
					fim_sinaleira = TRUE; //Armazena na vari�vel fim_sinaleira a informa��o TRUE
					fnTravaDetector(); //Trava imediatamente o detector
					ACENDE_AREAS; //Acende todas as �reas
					sorteou = SIM;
				}
			}
			else if(flag_passagem == _AMBOS_INFRAS_INATIVO)	//volta ao estado inicial
			{
				estado_passagem = 1;
			}
			break;
		}

		case 3:		//saindo algu�m
		{
			if(flag_passagem == _AMBOS_INFRAS_ATIVO)	//espera finalizar a entrada
			{
				estado_passagem = 5;
			}
			else if(flag_passagem == _AMBOS_INFRAS_INATIVO)	//volta ao estado inicial
			{
				estado_passagem = 1;
			}
			break;
		}

		case 4:		//Verifica se entrou algu�m
		{
			if(flag_passagem == _INFRA2_ATIVO)	//espera finalizar a entrada
			{
				estado_passagem = 6; //Verifica se realmente entrou pois precisa n�o ter ningu�m na frente dos contadores para confirmar que realmente entrou
			}
			else if(flag_passagem == _INFRA1_ATIVO) //Se retornou volta ao estado anterior
			{
				estado_passagem = 2;
			}
			break;
		}

		case 5:		//verifica se saiu algu�m
		{
			if(flag_passagem == _INFRA1_ATIVO)	//espera finalizar a sa�da
			{
				estado_passagem = 7; //Verifica se realmente saiu pois precisa n�o ter ningu�m na frente dos contadores para confirmar se realmente saiu
			}
			else if(flag_passagem == _INFRA2_ATIVO) //Se retornou volta ao estado anterior
			{
				estado_passagem = 3;
			}
			break;
		}

		case 6:
		{
			if(flag_passagem == _AMBOS_INFRAS_INATIVO)	//espera finalizar a entrada
			{
				estado_passagem = 1; //Armazena o valor 1 para iniciar toda a leitura novamente
				if(statusPGDM != 1){
					contador_entra++; //Incrementa contador_entra
					contador_dia_entra++;
					entrou = SIM;
					estado_CONTADOR = ESTADO_GRAVA_CONTADOR;
					if(trava_inteligente == SIM) //Se trava_inteligente for igual a SIM ent�o
					{
						fnTravaDetector(); //Trava a porta girat�ria
					}
					if(analiseir == SIM) //Se analiseir for igual a SIM ent�o
					{
						entrou_na_porta = SIM; //Armazena na vari�vel entrou a informa��o SIM para informar que passou na sequ�ncia correta de entrada dos infras
						tempo_permissao = 0; //Zera a vari�vel tempo_permissao para liberar um tempo para poder detectar
					}
					if(sorteador == SIM) //Se sorteador ativado ent�o realiza o sorteamento
					{
						if(sorteou == TRUE){
							sorteou = FALSE;
						}else cont_sorteador++; //Incrementa cont_sorteador
					}
				}else estado_BURLA = ESTADO_HOUVE_BURLA;
			}
			else if(flag_passagem == _AMBOS_INFRAS_ATIVO) //se retornou
			{
				estado_passagem = 4;
			}
			break;
		}

		case 7:
		{
			if(flag_passagem == _AMBOS_INFRAS_INATIVO)	//espera finalizar a sa�da
			{
				estado_passagem = 1; //Armazena o valor 1 para iniciar toda a leitura novamente
				if(statusPGDM != 1){
					contador_sai++; //Incrementa contador_sai
					contador_dia_sai++;
					saiu = SIM;
					estado_CONTADOR = ESTADO_GRAVA_CONTADOR;
				}
			}
			else if(flag_passagem == _AMBOS_INFRAS_ATIVO)
			{
				estado_passagem = 5;
			}
			break;
		}
		break;
	}
}

void fnLeInfrasTeto(void)
{
	if(SENSOR_TETO_ENTRADA_ATIVO ) //Se sensor de teto de entrada ativo ent�o
	{
		flag_passagem = _INFRA1_ATIVO; //Armazena na vari�vel flag_passagem a informa��o sensor de entrada ativo
	}
	else if(SENSOR_TETO_ENTRADA_INATIVO) //Sen�o se sensor de teto de entrada inativo ent�o
	{
		flag_passagem = _INFRA1_INATIVO; //Armazena na vari�vel flag_passagem a informa��o sensor de entrada inativo
	}
	if(SENSOR_TETO_SAIDA_ATIVO) //Sen�o se sensor de teto de saida ativo ent�o
	{
		flag_passagem1 = _INFRA2_ATIVO; //Armazena na vari�vel flag_passagem1 a informa��o sensor de saida ativo
	}
	else if(SENSOR_TETO_SAIDA_INATIVO) //Sen�o se sensor de teto de saida inativo ent�o
	{
		flag_passagem1 = _INFRA2_INATIVO; //Armazena na vari�vel flag_passagem1 a informa��o sensor de saida inativo
	}

	switch(estado_passagem) //Rotina de decis�o para o sensor de teto de entrada
	{
		case 1:	//case ninguem
		{
			if(flag_passagem == _INFRA1_INATIVO) //espera a entrada - sensor de teto de entrada n�o detectou continua no estado de passagem 1
			{
				estado_passagem = 1; //estado_passagem1 pessoa n�o entrou ainda
			}
			else if(flag_passagem == _INFRA1_ATIVO)	///espera terminar de entrar - sensor de teto de entrada detectou a entrada, vai para o estado de passagem 2 para esperar entrar
			{
				estado_passagem = 2; //estado_passagem pessoa esta entrando
			}
			break;
		}


		case 2: //Contabiliza a entrada da pessoa
		{
			estado_passagem = 3; //Armazena o valor 1 para iniciar toda a leitura novamente
			contador_entra++; //Incrementa contador de entrada
			contador_dia_entra++;
			entrou = SIM; //Marcar a flag entrou como SIM indicando a entrada da pessoa
			estado_CONTADOR = ESTADO_GRAVA_CONTADOR; //Torna a vari�vel estado_CONTADOR para ESTADO_GRAVA_CONTADOR que ir� gravar a contagem na mem�ria flash
			if(trava_inteligente == SIM) //Se trava_inteligente for igual a SIM ent�o
			{
				fnTravaDetector(); //Trava a porta girat�ria
			}
			if(analiseir == SIM) //Se analiseir for igual a SIM ent�o
			{
				entrou_na_porta = SIM; //Armazena na vari�vel entrou a informa��o SIM para informar que passou na sequ�ncia correta de entrada dos sensores de teto
				tempo_permissao = 0; //Zera a vari�vel tempo_permissao para liberar um tempo para poder detectar
			}
			if(cont_sorteador == (numero_sorteado-1)) //Se cont_sorteador for igual a numero_sorteado entao
							{
								fnSortearNumero(); //Sorteia um numero
								cont_sorteador = 0; //Reinicializa cont_sorteador
								areas_detectadas = 0xFF; //Todas as areas detectadas
								flag_area_detectada = 0xFF;
								fim_sinaleira = TRUE; //Armazena na variavel fim_sinaleira a informacao TRUE
								fnTravaDetector(); //Trava imediatamente o detector
								ACENDE_AREAS; //Acende todas as areas
								sorteou = SIM;
							}
			if(sorteador == SIM)
			{
				if(sorteou == TRUE){
					sorteou = FALSE;
				}else cont_sorteador++;
			}
			break;
		}
		case 3:	//Entrando alguem
		{
			if(flag_passagem == _INFRA1_INATIVO) //espera finalizar a entrada, caso ficar inativo o sensor de teto de entrada significa que a pessoa entrou e vai para o estado de passagem 3 contabilizar
			{
				estado_passagem = 1; //estado_passagem pessoa entrou
			}
			else if(flag_passagem == _INFRA1_ATIVO) //se sensor de entrada ativo de novo aguarda ate fazer a contabilizacao em estado de passagem 3 e continua no estado 2
			{
				estado_passagem = 3; //Foi pra ativo entao continua em estado 3 pois significa que a pessoa ainda esta no sensor e nao passou para dentro
			}
			break;
		}

		break;
	}
	switch(estado_passagem1) //Rotina de decis�o para o sensor de teto da saida
	{
		case 1:	//case ninguem
		{
			if(flag_passagem1 == _INFRA2_INATIVO) //espera a saida - sensor de teto de saida n�o detectou continua no estado de passagem 1
			{
				estado_passagem1 = 1; //estado_passagem1 pessoa nao saiu ainda
			}
			else if(flag_passagem1 == _INFRA2_ATIVO) //espera terminar de sair - sensor de teto de saida detectou a saida, vai para o estado de passagem 2 para esperar sair
			{
				estado_passagem1 = 2; //estado_passagem1 pessoa esta saindo
			}
			break;
		}
		case 2: //Contabiliza a saida da pessoa
		{
			estado_passagem1 = 3; //Armazena o valor 1 para iniciar toda a leitura novamente
			contador_sai++; //Incrementa contador de saida
			contador_dia_sai++;
			saiu = SIM; //Marcar a flag saiu como SIM indicando a saida da pessoa
			estado_CONTADOR = ESTADO_GRAVA_CONTADOR; //Torna a variavel estado_CONTADOR para ESTADO_GRAVA_CONTADOR que ira gravar a contagem na mem�ria flash
			break;
		}

		case 3:	//Saindo alguem
		{
			if(flag_passagem1 == _INFRA2_INATIVO) //espera finalizar a saida, caso ficar inativo o sensor de teto de saida significa que a pessoa saiu e vai para o estado de passagem 3 contabilizar a saida
			{
				estado_passagem1 = 1; //estado_passagem1 pessoa saiu
			}
			else if(flag_passagem1 == _INFRA2_ATIVO) //se sensor de saida ativo de novo aguarda ate fazer a contabilizacao em estado de passagem 3 e continua no estado 2
			{
				estado_passagem1 = 3; //Foi pra ativo entao continua em estado 3 pois significa que a pessoa ainda esta no sensor e nao passou para fora
			}
			break;
		}
	}
}

/******************************************************************************/

/*** Fun��es dos LOGS de AUDITORIAS ***/

/******************************************************************************/


/*** Fun��es dos LOGS de EVENTOS DE BLOQUEIOS e DESBLOQUEIOS ***/

/******************************************************************************/


/******************************************************************************/

/*** Fun��es do PWM TX e PWM RX ***/
// Escopo da fun��o:
// fnAtualizaPerfil(SETA_PARAMETROS_ON,SETA_PWM_ON,SETA_GRAVA_FLASH_ON,SETA_POT_GANHO_ON); ou
// fnAtualizaPerfil(SETA_PARAMETROS_OFF,SETA_PWM_OFF,SETA_GRAVA_FLASH_OFF,SETA_POT_GANHO_OFF);
// Tabelas que configuram sinal, defasagem, frequ�ncia, ganhos de cada �rea e sensibilidade de cada �rea
void fnAtualizaPerfil(byte seta_parametros,byte seta_pwm,byte grava_flash,byte set_pot_ganhos)
{
	if(perfil == PLANA_ONIX_2000) //PERFIL PLANA ONIX 2000 - MAIS FERRO E SEM ALUM�NIO
	{
		//							   				  Sinal	 Defasagem	 Frequ�ncia		       GANHOS	                SENSIBILIDADE
		if(tipo_detector == Z3){
			Stc_Tabela StcPerfilPLANA_ONIX_2000[NUM_MAX_CANAIS] =  {{   9  ,    145    ,    3500    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}}, 		//Canal 1
																	{   6  ,    140    ,    3550    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 2
																	{   6  ,    138    ,	3600	, { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 3
																	{   5  ,    133    ,    3650    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 4
																	{   5  ,    126    ,	3700	, { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 5
																	{   5  ,    120    ,    3750    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 6
																	{   6  ,    110    ,	3800	, { 7, 7, 7, 7, 7, 7, 7, 7} , {50,50,50,50,50,50,50,50}},		//Canal 7
																	{  43  ,    151    ,    3850    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 8
																	{  43  ,    145    ,	3900	, { 7, 7, 7, 7, 7, 7, 7, 7} , {50,50,50,50,50,50,50,50}},		//Canal 9
																	{  43  ,    138    ,    3950    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 10
																	{  43  ,    130    ,	4000	, {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}},		//Canal 11
																	{  43  ,    127    ,    4050    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 12
																	{  44  ,    115    ,	4100	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 13
																	{  46  ,    105    ,    4150    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 14
																	{  45  ,    100    ,	4200	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 15
																	{  45  ,     94    ,    4250    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 16
																	{  45  ,     88	   ,	4300	, {30,30,30,30,30,30,30,30} , {50,50,50,50,50,50,50,50}},		//Canal 17
																	{  45  ,     83    ,    4350    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 18
																	{  45  ,     78    ,	4400	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 19
																	{  45  ,     73    ,    4450    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 20
																	{  45  ,     62    ,    4500    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 21
																	{  45  ,     60    ,    4550    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 22
																	{  45  ,     56    ,    4600    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 23
																	{  45  ,     50    ,    4650    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 24
																	{  45  ,     44    ,    4700    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}}};		//Canal 25
			CanalAtual = StcPerfilPLANA_ONIX_2000[canal-1]; //Armazena na estrutura CanalAtual os dados capturados para o canal espec�fico
		}
		else{
			Stc_Tabela StcPerfilPLANA_ONIX_2000[NUM_MAX_CANAIS] =  {{   7  ,    160    ,    3500    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}}, 		//Canal 1
																	{   6  ,    155    ,    3550    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 2
																	{   6  ,    150    ,	3600	, { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 3
																	{   5  ,    145    ,    3650    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 4
																	{   5  ,    137    ,	3700	, {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}},		//Canal 5
																	{   5  ,    130    ,    3750    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 6
																	{   6  ,    118    ,	3800	, {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}},		//Canal 7
																	{  43  ,    155    ,    3850    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 8
																	{  43  ,    150    ,	3900	, {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}},		//Canal 9
																	{  43  ,    144    ,    3950    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 10
																	{  43  ,    140    ,	4000	, {15,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}},		//Canal 11
																	{  43  ,    135    ,    4050    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 12
																	{  44  ,    125    ,	4100	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 13
																	{  46  ,    115    ,    4150    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 14
																	{  45  ,    110    ,	4200	, {35,30,30,30,30,30,30,30} , {50,50,50,50,50,50,50,50}},		//Canal 15
																	{  45  ,    105    ,    4250    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 16
																	{  45  ,     97	   ,	4300	, {30,30,30,30,30,30,30,30} , {50,50,50,50,50,50,50,50}},		//Canal 17
																	{  45  ,     91    ,    4350    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 18
																	{  45  ,     85    ,	4400	, {30,30,30,30,30,30,30,30} , {50,50,50,50,50,50,50,50}},		//Canal 19
																	{  45  ,     80    ,    4450    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 20
																	{  45  ,     72    ,    4500    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 21
																	{  45  ,     67    ,    4550    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 22
																	{  45  ,     60    ,    4600    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 23
																	{  45  ,     55    ,    4650    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 24
																	{  45  ,     50    ,    4700    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}}};		//Canal 25

			CanalAtual = StcPerfilPLANA_ONIX_2000[canal-1]; //Armazena na estrutura CanalAtual os dados capturados para o canal espec�fico
		}
	}
	else if(perfil == PLANA_ONIX_2100) //PERFIL PLANA ONIX 2100 - MAIS FERRO E SEM ALUM�NIO
	{
		//							   				  Sinal	 Defasagem	 Frequ�ncia		       GANHOS	                SENSIBILIDADE
		if(tipo_detector == Z3){
			Stc_Tabela StcPerfilPLANA_ONIX_2100[NUM_MAX_CANAIS] =  {{   9  ,    151    ,    3500    , { 2, 2, 2, 2, 2, 2, 2, 2} , {50,50,50,50,50,50,50,50}}, 		//Canal 1
																	{   6  ,    147    ,    3550    , { 4, 4, 4, 4, 4, 4, 4, 4} , {50,50,50,50,50,50,50,50}},		//Canal 2
																	{   6  ,    138    ,	3600	, { 1, 1, 1, 1, 1, 1, 1, 1} , {50,50,50,50,50,50,50,50}},		//Canal 3
																	{   5  ,    142    ,    3650    , { 4, 4, 4, 4, 4, 4, 4, 4} , {50,50,50,50,50,50,50,50}},		//Canal 4
																	{   5  ,    133    ,	3700	, { 4, 4, 4, 4, 4, 4, 4, 4} , {50,50,50,50,50,50,50,50}},		//Canal 5
																	{   5  ,    126    ,    3750    , { 4, 4, 4, 4, 4, 4, 4, 4} , {50,50,50,50,50,50,50,50}},		//Canal 6
																	{   6  ,    115    ,	3800	, { 3, 3, 3, 3, 3, 3, 3, 3} , {50,50,50,50,50,50,50,50}},		//Canal 7
																	{  43  ,    156    ,    3850    , { 2, 2, 2, 2, 2, 2, 2, 2} , {50,50,50,50,50,50,50,50}},		//Canal 8
																	{  43  ,    150    ,	3900	, { 4, 4, 4, 4, 4, 4, 4, 4} , {50,50,50,50,50,50,50,50}},		//Canal 9
																	{  43  ,    143    ,    3950    , { 3, 3, 3, 3, 3, 3, 3, 3} , {50,50,50,50,50,50,50,50}},		//Canal 10
																	{  43  ,    137    ,	4000	, { 3, 3, 3, 3, 3, 3, 3, 3} , {50,50,50,50,50,50,50,50}},		//Canal 11
																	{  43  ,    130    ,    4050    , { 2, 2, 2, 2, 2, 2, 2, 2} , {50,50,50,50,50,50,50,50}},		//Canal 12
																	{  44  ,    120    ,	4100	, { 3, 3, 3, 3, 3, 3, 3, 3} , {50,50,50,50,50,50,50,50}},		//Canal 13
																	{  46  ,    110    ,    4150    , { 5, 5, 5, 5, 5, 5, 5, 5} , {50,50,50,50,50,50,50,50}},		//Canal 14
																	{  45  ,    107    ,	4200	, { 5, 5, 5, 5, 5, 5, 5, 5} , {50,50,50,50,50,50,50,50}},		//Canal 15
																	{  45  ,    101    ,    4250    , { 5, 5, 5, 5, 5, 5, 5, 5} , {50,50,50,50,50,50,50,50}},		//Canal 16
																	{  45  ,     94	   ,	4300	, { 7, 7, 7, 7, 7, 7, 7, 7} , {50,50,50,50,50,50,50,50}},		//Canal 17
																	{  45  ,     88    ,    4350    , { 7, 7, 7, 7, 7, 7, 7, 7} , {50,50,50,50,50,50,50,50}},		//Canal 18
																	{  45  ,     81    ,	4400	, {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}},		//Canal 19
																	{  45  ,     74    ,    4450    , { 9, 9, 9, 9, 9, 9, 9, 9} , {50,50,50,50,50,50,50,50}},		//Canal 20
																	{  45  ,     69    ,    4500    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 21
																	{  45  ,     62    ,    4550    , { 9, 9, 9, 9, 9, 9, 9, 9} , {50,50,50,50,50,50,50,50}},		//Canal 22
																	{  45  ,     60    ,    4600    , {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}},		//Canal 23
																	{  45  ,     51    ,    4650    , { 9, 9, 9, 9, 9, 9, 9, 9} , {50,50,50,50,50,50,50,50}},		//Canal 24
																	{  45  ,     46    ,    4700    , {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}}};		//Canal 25
			CanalAtual = StcPerfilPLANA_ONIX_2100[canal-1]; //Armazena na estrutura CanalAtual os dados capturados para o canal espec�fico
		}
		else{
			Stc_Tabela StcPerfilPLANA_ONIX_2100[NUM_MAX_CANAIS] =  {{   7  ,    151    ,    3500    , { 2, 2, 2, 2, 2, 2, 2, 2} , {50,50,50,50,50,50,50,50}}, 		//Canal 1
																	{   6  ,    147    ,    3550    , { 4, 4, 4, 4, 4, 4, 4, 4} , {50,50,50,50,50,50,50,50}},		//Canal 2
																	{   6  ,    138    ,	3600	, { 1, 1, 1, 1, 1, 1, 1, 1} , {50,50,50,50,50,50,50,50}},		//Canal 3
																	{   5  ,    142    ,    3650    , { 4, 4, 4, 4, 4, 4, 4, 4} , {50,50,50,50,50,50,50,50}},		//Canal 4
																	{   5  ,    133    ,	3700	, { 4, 4, 4, 4, 4, 4, 4, 4} , {50,50,50,50,50,50,50,50}},		//Canal 5
																	{   5  ,    126    ,    3750    , { 4, 4, 4, 4, 4, 4, 4, 4} , {50,50,50,50,50,50,50,50}},		//Canal 6
																	{   6  ,    115    ,	3800	, { 3, 3, 3, 3, 3, 3, 3, 3} , {50,50,50,50,50,50,50,50}},		//Canal 7
																	{  43  ,    156    ,    3850    , { 2, 2, 2, 2, 2, 2, 2, 2} , {50,50,50,50,50,50,50,50}},		//Canal 8
																	{  43  ,    150    ,	3900	, { 4, 4, 4, 4, 4, 4, 4, 4} , {50,50,50,50,50,50,50,50}},		//Canal 9
																	{  43  ,    143    ,    3950    , { 3, 3, 3, 3, 3, 3, 3, 3} , {50,50,50,50,50,50,50,50}},		//Canal 10
																	{  43  ,    137    ,	4000	, { 3, 3, 3, 3, 3, 3, 3, 3} , {50,50,50,50,50,50,50,50}},		//Canal 11
																	{  43  ,    130    ,    4050    , { 2, 2, 2, 2, 2, 2, 2, 2} , {50,50,50,50,50,50,50,50}},		//Canal 12
																	{  44  ,    120    ,	4100	, { 3, 3, 3, 3, 3, 3, 3, 3} , {50,50,50,50,50,50,50,50}},		//Canal 13
																	{  46  ,    110    ,    4150    , { 5, 5, 5, 5, 5, 5, 5, 5} , {50,50,50,50,50,50,50,50}},		//Canal 14
																	{  45  ,    107    ,	4200	, { 5, 5, 5, 5, 5, 5, 5, 5} , {50,50,50,50,50,50,50,50}},		//Canal 15
																	{  45  ,    101    ,    4250    , { 5, 5, 5, 5, 5, 5, 5, 5} , {50,50,50,50,50,50,50,50}},		//Canal 16
																	{  45  ,     94	   ,	4300	, { 7, 7, 7, 7, 7, 7, 7, 7} , {50,50,50,50,50,50,50,50}},		//Canal 17
																	{  45  ,     88    ,    4350    , { 7, 7, 7, 7, 7, 7, 7, 7} , {50,50,50,50,50,50,50,50}},		//Canal 18
																	{  45  ,     81    ,	4400	, {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}},		//Canal 19
																	{  45  ,     74    ,    4450    , { 9, 9, 9, 9, 9, 9, 9, 9} , {50,50,50,50,50,50,50,50}},		//Canal 20
																	{  45  ,     69    ,    4500    , { 8, 8, 8, 8, 8, 8, 8, 8} , {50,50,50,50,50,50,50,50}},		//Canal 21
																	{  45  ,     62    ,    4550    , { 9, 9, 9, 9, 9, 9, 9, 9} , {50,50,50,50,50,50,50,50}},		//Canal 22
																	{  45  ,     60    ,    4600    , {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}},		//Canal 23
																	{  45  ,     51    ,    4650    , { 9, 9, 9, 9, 9, 9, 9, 9} , {50,50,50,50,50,50,50,50}},		//Canal 24
																	{  45  ,     46    ,    4700    , {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}}};		//Canal 25
			CanalAtual = StcPerfilPLANA_ONIX_2100[canal-1]; //Armazena na estrutura CanalAtual os dados capturados para o canal espec�fico
		}
	}
	else if(perfil == PLANA_ONIX_440) //PERFIL PLANA ONIX 440 - MAIS FERRO E SEM ALUM�NIO
	{
		//							   				  Sinal	 Defasagem	 Frequ�ncia		       GANHOS	                SENSIBILIDADE
		Stc_Tabela StcPerfilPLANA_ONIX_440[NUM_MAX_CANAIS] =   {{  20  ,     98    ,    3600    , {25,25,25,25,25,25,25,25} , {53,53,53,53,53,53,53,53}}, 		//Canal 1
																{  50  ,    152    ,	3802	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 2
																{  50  ,    143    ,	3988	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 3
																{  50  ,    130    ,	4174	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 4
																{  50  ,    115    ,	4404	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 5
																{  50  ,    105    ,	4602	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 6
																{  20  ,    121    ,	3402	, {30,30,30,30,30,30,30,30} , {50,50,50,50,50,50,50,50}},		//Canal 7
																{  24  ,    140    ,	3194	, {30,30,30,30,30,30,30,30} , {50,50,50,50,50,50,50,50}},		//Canal 8
																{  29  ,    158	   ,	3006	, {30,30,30,30,30,30,30,30} , {50,50,50,50,50,50,50,50}},		//Canal 9
																{  20  ,     98    ,    3600    , {25,25,25,25,25,25,25,25} , {53,53,53,53,53,53,53,53}}, 		//Canal 10
																{  50  ,    152    ,	3802	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 11
																{  50  ,    143    ,	3988	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 12
																{  50  ,    130    ,	4174	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 13
																{  50  ,    115    ,	4404	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 14
																{  50  ,    105    ,	4602	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 15
																{  20  ,    121    ,	3402	, {30,30,30,30,30,30,30,30} , {50,50,50,50,50,50,50,50}},		//Canal 16
																{  24  ,    140    ,	3194	, {30,30,30,30,30,30,30,30} , {50,50,50,50,50,50,50,50}},		//Canal 17
																{  29  ,    158	   ,	3006	, {30,30,30,30,30,30,30,30} , {50,50,50,50,50,50,50,50}},		//Canal 18
																{  34  ,    175    ,	2804	, {30,30,30,30,30,30,30,30} , {50,50,50,50,50,50,50,50}},		//Canal 19
																{  34  ,    175    ,	2804	, {30,30,30,30,30,30,30,30} , {50,50,50,50,50,50,50,50}},		//Canal 20
																{  20  ,     98    ,    3600    , {25,25,25,25,25,25,25,25} , {53,53,53,53,53,53,53,53}}, 		//Canal 21
																{  50  ,    152    ,	3802	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 22
																{  50  ,    143    ,	3988	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 23
																{  50  ,    130    ,	4174	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 24
																{  50  ,    115    ,	4404	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}}};		//Canal 25

		CanalAtual = StcPerfilPLANA_ONIX_440[canal-1];
	}
	else if(perfil == IECO_GT) //PERFIL GT - MAIS FERRO E SEM ALUM�NIO
	{
		//							   				  Sinal	 Defasagem	 Frequ�ncia		       GANHOS	                SENSIBILIDADE
		Stc_Tabela StcPerfilIECO_GT[NUM_MAX_CANAIS] =    	   {{  1  ,    176   , 		3500    , {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}}, 		//Canal 1
																{  1  ,     80   ,		3600	, {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}},		//Canal 2
																{  1  ,     75   ,		3700	, {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}},		//Canal 3
																{  5  ,    150   ,		3800	, {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}},		//Canal 4
																{  5  ,    125   ,		3900	, {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}},		//Canal 5
																{  5  ,    115   ,		4000	, {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}},		//Canal 6
																{  2  ,    150   ,		4100	, {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}},		//Canal 7
																{  1  ,    135   ,		4200	, {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}},		//Canal 8
																{  1  ,    120	 ,		4300	, {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}},		//Canal 9
																{  1  ,    100   ,		4400	, {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}},		//Canal 10
																{  1  ,    176   , 		3500    , {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}}, 		//Canal 11
																{  1  ,     80   ,		3600	, {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}},		//Canal 12
																{  1  ,     75   ,		3700	, {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}},		//Canal 13
																{  5  ,    150   ,		3800	, {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}},		//Canal 14
																{  5  ,    125   ,		3900	, {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}},		//Canal 15
																{  5  ,    115   ,		4000	, {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}},		//Canal 16
																{  2  ,    150   ,		4100	, {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}},		//Canal 17
																{  1  ,    135   ,		4200	, {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}},		//Canal 18
																{  1  ,    120	 ,		4300	, {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}},		//Canal 19
																{  1  ,    100   ,		4400	, {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}},		//Canal 20
																{  1  ,    176   , 		3500    , {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}}, 		//Canal 21
																{  1  ,     80   ,		3600	, {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}},		//Canal 22
																{  1  ,     75   ,		3700	, {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}},		//Canal 23
																{  5  ,    150   ,		3800	, {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}},		//Canal 24
																{  5  ,    125   ,		3900	, {10,10,10,10,10,10,10,10} , {50,50,50,50,50,50,50,50}}};		//Canal 25
		CanalAtual = StcPerfilIECO_GT[canal-1]; //Armazena na estrutura CanalAtual os dados capturados para o canal espec�fico
	}
	else if(perfil == CIL_IECO_2000) //PERFIL CILINDRICA IECO 2000 - MAIS FERRO E SEM ALUM�NIO
	{
		//							   				  Sinal	 Defasagem	 Frequ�ncia		       GANHOS	                SENSIBILIDADE
		Stc_Tabela StcPerfilCIL_IECO_2000[NUM_MAX_CANAIS] =    {{  15  ,    133    ,    3500    , {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}}, 		//Canal 1
																{  15  ,    132    ,	3600	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 2
																{  10  ,    130    ,	3700	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 3
																{  42  ,    175    ,	3800	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 4
																{  48  ,    162    ,	3900	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 5
																{  46  ,    158    ,	4000	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 6
																{  20  ,    188    ,	4100	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 7
																{  10  ,    170    ,	4200	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 8
																{  10  ,    150	   ,	4300	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 9
																{  10  ,    136    ,	4400	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 10
																{  15  ,    133    ,    3500    , {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}}, 		//Canal 11
																{  15  ,    132    ,	3600	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 12
																{  10  ,    130    ,	3700	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 13
																{  42  ,    175    ,	3800	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 14
																{  48  ,    162    ,	3900	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 15
																{  46  ,    158    ,	4000	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 16
																{  20  ,    188    ,	4100	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 17
																{  10  ,    170    ,	4200	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 18
																{  10  ,    150	   ,	4300	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 19
																{  10  ,    136    ,	4400	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 20
																{  15  ,    133    ,    3500    , {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}}, 		//Canal 2																																							{  15  ,    132    ,	3600	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 22
																{  10  ,    130    ,	3700	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 23
																{  42  ,    175    ,	3800	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 24
																{  48  ,    162    ,	3900	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}}};		//Canal 25
		CanalAtual = StcPerfilCIL_IECO_2000[canal-1]; //Armazena na estrutura CanalAtual os dados capturados para o canal espec�fico
	}
	else if(perfil == CIL_IECO_2100) //PERFIL CILINDRICA IECO 2100 - MAIS FERRO E SEM ALUM�NIO
	{
		//							   				  Sinal	 Defasagem	 Frequ�ncia		       GANHOS	                SENSIBILIDADE
		Stc_Tabela StcPerfilCIL_IECO_2100[NUM_MAX_CANAIS] =    {{  20  ,     98    ,    3600    , {25,25,25,25,25,25,25,25} , {55,55,55,55,55,55,55,55}}, 		//Canal 1
																{  50  ,    152    ,	3802	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 2
																{  50  ,    143    ,	3988	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 3
																{  50  ,    130    ,	4174	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 4
																{  50  ,    115    ,	4404	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 5
																{  50  ,    105    ,	4602	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 6
																{  20  ,    121    ,	3402	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 7
																{  24  ,    140    ,	3194	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 8
																{  29  ,    158	   ,	3006	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 9
																{  34  ,    175    ,	2804	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 10
																{  20  ,     98    ,    3600    , {25,25,25,25,25,25,25,25} , {55,55,55,55,55,55,55,55}}, 		//Canal 11
																{  50  ,    152    ,	3802	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 12
																{  50  ,    143    ,	3988	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 13
																{  50  ,    130    ,	4174	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 14
																{  50  ,    115    ,	4404	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 15
																{  50  ,    105    ,	4602	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 16
																{  20  ,    121    ,	3402	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 17
																{  24  ,    140    ,	3194	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 18
																{  29  ,    158	   ,	3006	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 19
																{  34  ,    175    ,	2804	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 20
																{  20  ,     98    ,    3600    , {25,25,25,25,25,25,25,25} , {55,55,55,55,55,55,55,55}}, 		//Canal 21
																{  50  ,    152    ,	3802	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 22
																{  50  ,    143    ,	3988	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 23
																{  50  ,    130    ,	4174	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}},		//Canal 24
																{  50  ,    115    ,	4404	, {25,25,25,25,25,25,25,25} , {50,50,50,50,50,50,50,50}}};		//Canal 25
		CanalAtual = StcPerfilCIL_IECO_2100[canal-1]; //Armazena na estrutura CanalAtual os dados capturados para o canal espec�fico
	}
	else if(perfil == PORTAL_750_BLINDADO) //PERFIL PORTAL ONIX 750mm BLINDADO - MAIS FERRO E SEM ALUM�NIO
	{
		//							   				  Sinal	 Defasagem	 Frequ�ncia		       GANHOS	                SENSIBILIDADE
		Stc_Tabela StcPerfilPORTAL_750_BLIND[NUM_MAX_CANAIS] = {{   1  ,    108    ,    4050    , {50,50,50,50,50,50,50,50} , {60,60,60,60,60,60,60,60}}, 		//Canal 1
																{   1  ,    104    ,	4100	, {50,50,50,50,50,50,50,50} , {60,60,60,60,60,60,60,60}},		//Canal 2
																{   1  ,     96    ,	4150	, {50,50,50,50,50,50,50,50} , {60,60,60,60,60,60,60,60}},		//Canal 3
																{   1  ,     90    ,	4200	, {50,50,50,50,50,50,50,50} , {60,60,60,60,60,60,60,60}},		//Canal 4
																{   1  ,     81    ,	4250	, {50,50,50,50,50,50,50,50} , {60,60,60,60,60,60,60,60}},		//Canal 5
																{   1  ,     74    ,	4300	, {50,50,50,50,50,50,50,50} , {60,60,60,60,60,60,60,60}},		//Canal 6
																{  30  ,    154    ,	4350	, {50,50,50,50,50,50,50,50} , {60,60,60,60,60,60,60,60}},		//Canal 7
																{  30  ,    146    ,	4400	, {50,50,50,50,50,50,50,50} , {60,60,60,60,60,60,60,60}},		//Canal 8
																{  30  ,    135	   ,	4450	, {50,50,50,50,50,50,50,50} , {60,60,60,60,60,60,60,60}},		//Canal 9
																{  30  ,    135    ,	4500	, {50,50,50,50,50,50,50,50} , {60,60,60,60,60,60,60,60}},		//Canal 10
																{   1  ,    108    ,    4050    , {50,50,50,50,50,50,50,50} , {60,60,60,60,60,60,60,60}}, 		//Canal 11
																{   1  ,    104    ,	4100	, {50,50,50,50,50,50,50,50} , {60,60,60,60,60,60,60,60}},		//Canal 12
																{   1  ,     96    ,	4150	, {50,50,50,50,50,50,50,50} , {60,60,60,60,60,60,60,60}},		//Canal 13
																{   1  ,     90    ,	4200	, {50,50,50,50,50,50,50,50} , {60,60,60,60,60,60,60,60}},		//Canal 14
																{   1  ,     81    ,	4250	, {50,50,50,50,50,50,50,50} , {60,60,60,60,60,60,60,60}},		//Canal 15
																{   1  ,     74    ,	4300	, {50,50,50,50,50,50,50,50} , {60,60,60,60,60,60,60,60}},		//Canal 16
																{  30  ,    154    ,	4350	, {50,50,50,50,50,50,50,50} , {60,60,60,60,60,60,60,60}},		//Canal 17
																{  30  ,    146    ,	4400	, {50,50,50,50,50,50,50,50} , {60,60,60,60,60,60,60,60}},		//Canal 18
																{  30  ,    135	   ,	4450	, {50,50,50,50,50,50,50,50} , {60,60,60,60,60,60,60,60}},		//Canal 19
																{  30  ,    135    ,	4500	, {50,50,50,50,50,50,50,50} , {60,60,60,60,60,60,60,60}},		//Canal 20
																{   1  ,    108    ,    4050    , {50,50,50,50,50,50,50,50} , {60,60,60,60,60,60,60,60}}, 		//Canal 21
																{   1  ,    104    ,	4100	, {50,50,50,50,50,50,50,50} , {60,60,60,60,60,60,60,60}},		//Canal 22
																{   1  ,     96    ,	4150	, {50,50,50,50,50,50,50,50} , {60,60,60,60,60,60,60,60}},		//Canal 23
																{   1  ,     90    ,	4200	, {50,50,50,50,50,50,50,50} , {60,60,60,60,60,60,60,60}},		//Canal 24
																{   1  ,     81    ,	4250	, {50,50,50,50,50,50,50,50} , {60,60,60,60,60,60,60,60}}};		//Canal 25

		CanalAtual = StcPerfilPORTAL_750_BLIND[canal-1]; //Armazena na estrutura CanalAtual os dados capturados para o canal espec�fico
	}

	if(seta_parametros) //Se seta_parametros for 1 ent�o
	{
		static volatile byte x2; //Define a vari�vel x

		for(x2 = 0;x2 < 8;x2++) //Armazena o valor nas 8 posi��es do buffer_ganho do vetor estrutura CanalAtual.Ganho
		{
			buffer_ganho[x2+1] = CanalAtual.Ganho[x2];
		}
		for(x2 = 0;x2 < 8;x2++) //Armazena o valor nas 8 posi��es do buffer_sensibilidade do vetor estrutura CanalAtual.Sensibilidade
		{
			buffer_sensibilidade[x2+1] = CanalAtual.Sensibilidade[x2];
		}
		buffer_ganho[0] = buffer_ganho[1]; //Armazena na posi��o 0 do vetor buffer_ganho o valor de buffer_ganho da posi��o 1 para TODAS_AREAS
		buffer_sensibilidade[0] = buffer_sensibilidade[1]; //Armazena na posi��o 0 do vetor buffer_sensibilidade o valor de buffer_sensibilidade da posi��o 1 para TODAS_AREAS
		ciclo_de_trabalho = CanalAtual.Sinal; //Armazena na vari�vel ciclo_de_trabalho o valor lido da estrutura CanalAtual.Sinal
		defasagem = CanalAtual.Defasagem; //Armazena na vari�vel defasagem o valor lido da estrutura CanalAtual.Defasagem
		frequencia = CanalAtual.Frequencia; //Armazena na vari�vel frequencia o valor lido da estrutura CanalAtual.Frequencia
	}
	if(seta_pwm) //Se seta_pwm for 1 ent�o
	{
		SetDutyCycle_TX(0); //Fun��o que ajusta o ciclo de trabalho do PWM da TX para 0% no come�o

		AGUARDA_Waitms(100); //Espera 100ms

		SetFrequencia(frequencia); //Fun��o que altera o ciclo de trabalho, defasagem e frequ�ncia do sinal
	}
	if(grava_flash) //Se grava_flash for 1 ent�o
	{
		Write_Buffer_FLASH[0] = canal; //Escreve no vetor de grava��o da mem�ria FLASH o valor de canal
		ESCREVE_FLASH_INTERNA(endFLASHCanal,1,0); //Escreve no endere�o espec�fico da mem�ria FALSH o valor do canal
		AGUARDA_Waitms(1); //Espera 1ms

		Write_Buffer_FLASH[0] = (byte)(ciclo_de_trabalho); //Armazena no vetor de grava��o da flash o ciclo de trabalho
		Write_Buffer_FLASH[1] = (byte)(defasagem >> 8); //Armazena no vetor de grava��o da flash o byte alto da defasagem
		Write_Buffer_FLASH[2] = (byte)(defasagem); //Armazena no vetor de grava��o da flash o byte baixo da defasagem
		Write_Buffer_FLASH[3] = (byte)(frequencia >> 8); //Armazena no vetor de grava��o da flash o byte alto da frequ�ncia
		Write_Buffer_FLASH[4] = (byte)(frequencia); //Armazena no vetor de grava��o da flash o byte baixo da frequ�ncia
		ESCREVE_FLASH_INTERNA(endFLASHCicloTrabalho,5,0); //Escreve no endere�o especificado os dados acima colocadas no vetor de grava��o da mem�ria FLASH
		AGUARDA_Waitms(1); //Espera 1ms

		Write_Buffer_FLASH[0] = buffer_sensibilidade[1]; //Armazena no vetor de grava��o da flash a sensibilidade da �rea 1
		Write_Buffer_FLASH[1] = buffer_sensibilidade[2]; //Armazena no vetor de grava��o da flash a sensibilidade da �rea 2
		Write_Buffer_FLASH[2] = buffer_sensibilidade[3]; //Armazena no vetor de grava��o da flash a sensibilidade da �rea 3
		Write_Buffer_FLASH[3] = buffer_sensibilidade[4]; //Armazena no vetor de grava��o da flash a sensibilidade da �rea 4
		Write_Buffer_FLASH[4] = buffer_sensibilidade[5]; //Armazena no vetor de grava��o da flash a sensibilidade da �rea 5
		Write_Buffer_FLASH[5] = buffer_sensibilidade[6]; //Armazena no vetor de grava��o da flash a sensibilidade da �rea 6
		Write_Buffer_FLASH[6] = buffer_sensibilidade[7]; //Armazena no vetor de grava��o da flash a sensibilidade da �rea 7
		Write_Buffer_FLASH[7] = buffer_sensibilidade[8]; //Armazena no vetor de grava��o da flash a sensibilidade da �rea 8
		ESCREVE_FLASH_INTERNA(endFLASHSensibilidadeArea1,8,0); //Escreve no endere�o especificado os dados acima colocadas no vetor de grava��o da mem�ria FLASH
		AGUARDA_Waitms(1); //Espera 1ms

		Write_Buffer_FLASH[0] = buffer_ganho[1]; //Armazena no vetor de grava��o da flash o ganho da �rea 1
		Write_Buffer_FLASH[1] = buffer_ganho[2]; //Armazena no vetor de grava��o da flash o ganho da �rea 2
		Write_Buffer_FLASH[2] = buffer_ganho[3]; //Armazena no vetor de grava��o da flash o ganho da �rea 3
		Write_Buffer_FLASH[3] = buffer_ganho[4]; //Armazena no vetor de grava��o da flash o ganho da �rea 4
		Write_Buffer_FLASH[4] = buffer_ganho[5]; //Armazena no vetor de grava��o da flash o ganho da �rea 5
		Write_Buffer_FLASH[5] = buffer_ganho[6]; //Armazena no vetor de grava��o da flash o ganho da �rea 6
		Write_Buffer_FLASH[6] = buffer_ganho[7]; //Armazena no vetor de grava��o da flash o ganho da �rea 7
		Write_Buffer_FLASH[7] = buffer_ganho[8]; //Armazena no vetor de grava��o da flash o ganho da �rea 8
		ESCREVE_FLASH_INTERNA(endFLASHPotenciometroGanhoArea1,8,0); //Escreve no endere�o especificado os dados acima colocadas no vetor de grava��o da mem�ria FLASH
		AGUARDA_Waitms(1); //Espera 1ms
	}
	if(set_pot_ganhos) //Se set_pot_ganhos for igual a 1 ent�o
	{
		fnEnviaSPI(POT_GANHO,1,buffer_ganho[1]); //Envia a configura��o do potenci�metro de ganho da �rea 1
		fnEnviaSPI(POT_GANHO,2,buffer_ganho[2]); //Envia a configura��o do potenci�metro de ganho da �rea 2
		fnEnviaSPI(POT_GANHO,3,buffer_ganho[3]); //Envia a configura��o do potenci�metro de ganho da �rea 3
		fnEnviaSPI(POT_GANHO,4,buffer_ganho[4]); //Envia a configura��o do potenci�metro de ganho da �rea 4
		fnEnviaSPI(POT_GANHO,5,buffer_ganho[5]); //Envia a configura��o do potenci�metro de ganho da �rea 5
		fnEnviaSPI(POT_GANHO,6,buffer_ganho[6]); //Envia a configura��o do potenci�metro de ganho da �rea 6
		fnEnviaSPI(POT_GANHO,7,buffer_ganho[7]); //Envia a configura��o do potenci�metro de ganho da �rea 7
		fnEnviaSPI(POT_GANHO,8,buffer_ganho[8]); //Envia a configura��o do potenci�metro de ganho da �rea 8
	}
}

void SetDutyCycle_TX(byte duty) //Fun��o que ajusta o ciclo de trabalho do PWM da TX
{
	//Armazena na vari�vel percent o valor para acertar o pwm
	//exemplo com ciclo de trabalho 20 e frequ�ncia 3600Hz percent = (600000 * 20) / 3600 = 3333
	//Ciclo de m�quina = 60MHz = 1/60000000 = (1,66667*(10^-8))
	//3600Hz em decimal para o FTM0 � (1/3600) / (1,66667*(10^-8)) = 16666 (FTM0_MOD) e por conseguinte 16666 * 20% ciclo de trabalho = 3333
	dword percent = (dword)(600000 * duty) / (frequencia);
	FTM_CHAN_SetValue(FTM0,CH1,(dword)(percent + FTM0_C0V)); //Seta o valor de FTM0 em CH1 (3333 + FTM0_C0V)
}

void SetDutyCycle_RX(void) //Fun��o que ajusta o ciclo de trabalho dos sinais RX1 e RX2
{
	//Ajusta o PWM em 50%
	//percent = (6000*5001) / frequencia
	//Exemplo com 3600Hz: percent = (6000*5001) / 3600 = 8335
	dword percent = (dword)6000 * 5001 / (frequencia); //Conforme exemplo anterior
	FTM_CHAN_SetValue(FTM0,CH2,0); //Seta o PMW a 50% no zero graus
	FTM_CHAN_SetValue(FTM0,CH3,percent); //Seta o segundo PWM a 50% a 180 graus um do outro
}

void SetDefasagem(word def) //Fun��o que altera a defasagem do sinal
{
	//Como exemplo ciclo_de_trabalho = 20, frequencia = 3600, def = 90
	//Como exemplo posiciona o sinal da TX neste exemplo a 90 graus em rela��o ao inicio que seria 360/90 = 4 ent�o
	//divide os 16666 / 4 = 4166,50. Como o sinal do PWM TX neste caso � 20% (3333) ent�o soma 4166,50 + 3333 = 7500
	//Com base no valor acima do FTM0_MOD = 16666 como exemplo e fazendo def = 90 como exemplo teremos:
	//Para CH0 (FTM0_MOD * def) / 360 = (16666 * 90) / 360 = 4166
	//Para CH1 (600000 * ciclo_de_trabalho) / (frequencia) + ((FTM0_MOD * def) / 360))) = (600000 * 20) / (3600) + (16666 * 90) / 360))) = 3333 + 4166 = 7500
	delay_ms(10); //Espera 10ms para estabilizar
	FTM_CHAN_SetValue(FTM0,CH0,(dword)((FTM0_MOD * def) / 360));
	FTM_CHAN_SetValue(FTM0,CH1,(dword)((600000 * ciclo_de_trabalho) / (frequencia) + ((FTM0_MOD * def) / 360)));
}

void SetFrequencia(dword freq) //Fun��o que altera a frequ�ncia do sinal
{
	//Vamos usar como exemplo freq = 3600 e defasagem 90 e selecao_metais 75
	FTM0_CNT = 0; //Zera o contador do FTM0
	FTM0_MOD = 60000000 / (freq + 11); //60000000 / (3600 + 11) = 16615

	frequencia = freq; //Armazena na vari�vel frequencia o valor 3600
	SetDutyCycle_RX(); //Fun��o que ajusta o ciclo de trabalho dos sinais RX1 e RX2
	SetDutyCycle_TX(ciclo_de_trabalho); //Fun��o que ajusta o ciclo de trabalho do PWM da TX

	fnCorrigeSelecao();	//Corrige a sele��o de metais

	if(selecao_metais > 50) //Se selecao_metais for maior que 50 ent�o
	{
		aux_defasagem = defasagem + (selecao_metais - 50); //aux_defasagem =  90 + (75 - 50) = 115
	}
	else if(selecao_metais <= 50) //Sen�o se selecao_metais for menor igual a 50 ent�o
	{
		aux_defasagem = (defasagem - (50 - selecao_metais)); //Como exemplo tomamos selecao_metais = 40 ent�o aux_defasagem = (90 - (50 - 40)) = 80
	}
	SetDefasagem(aux_defasagem); //Fun��o que altera a defasagem do sinal

	selecao_metais = aux_selecao_metais; //Recupera o valor da sele��o de metais para apresentar no display
}

void InitPwm (void)
{
	FTM_Init (FTM0,FTM_MODULE_SYSCLK_DIVBY1_COMBINE_IRQ_CONFIG(0),0,36000); //Inicializa o PMW combinado com interrup��o

	//CH0 e CH1 s�o para o PWM da TX
	FTM_CHAN_Init (FTM0, CH0, FTM_CHANNEL_PWMNORMAL_COMBINE_COMP_DTEN_CONFIG, 0); //Inicializa o PWM da TX no canal 0
	FTM_CHAN_Init (FTM0, CH1, FTM_CHANNEL_PWMNORMAL_COMBINE_COMP_DTEN_CONFIG, 0); //Inicializa o PWM da TX no canal 1

	FTM_CHAN_Init (FTM0, CH2, FTM_CHANNEL_PWMNORMAL_COMBINE_COMP_DTEN_CONFIG, 0); //Inicializa o PWM da RX do canal 2
	FTM_CHAN_Init (FTM0, CH3, FTM_CHANNEL_PWMNORMAL_COMBINE_COMP_DTEN_CONFIG, 0); //Inicializa o PWM da RX do canal 3

	FTM0CH0_SetValue(0); //Seta zero para o canal zero para o canal 0
	FTM0CH1_SetValue((int) 0x258); //Seta 0x258 para o canal 1

	FTM0CH2_SetValue(0); //Seta zero para o canal zero para o canal 2
	FTM0CH3_SetValue((int) 0x258); //Seta 0x258 para o canal 3
}
/******************************************************************************/


/*** Fun��o das TECLAS ***/
void fnLerTeclas(void) //Fun��o que l� as teclas do painel e controle remoto
{
	estado = ESTADO_LE_AREAS_DETECCAO; //Estado a ser executado � ESTADO_LE_AREAS_DETECCAO

	//Entra no menu atrav�s das senhas somente conforme configura��es do sinal_trava, e trava e destrava pelo painel conforme modo_travamento
	if(tela != TELA_CONFIRMA_INICIAR)
	{
		if( (teclapressionada == teclaIncrementa && sinal_trava == trava_retencao_controle_teclado) ||
			(teclapressionada == teclaDecrementa && sinal_trava == trava_retencao_controle_teclado)                                      ||
			(teclapressionada == teclaTrava && sinal_trava == trava_retencao_controle_teclado && modo_travamento == TRAVA_DESTRAVA)      ||
			(teclapressionada == teclaDestrava && sinal_trava == trava_retencao_controle_teclado)                                        ||
			(teclapressionada == teclaTrava && sinal_trava == trava_retencao_controle && modo_travamento == TRAVA_DESTRAVA)              ||
			(teclapressionada == teclaDestrava && sinal_trava == trava_retencao_controle)                                                ||
			(teclapressionada == teclaConfirma) 																						 ||
			(teclapressionada == teclaConfirma_Remoto))
		{
			estado = ESTADO_NAVEGA_MENU; //Estado a ser executado � ESTADO_NAVEGA_MENU
			if(teclapressionada == teclaConfirma || teclapressionada == teclaConfirma_Remoto) //Se teclapressionada for igual a tecla CONFIRMA ent�o
			{
				INIBE_TELAS_DE_MSG = TRUE; //Armazena na flag INIBE_TELAS_DE_MSG a informa��o TRUE
			}
		}
	}
}
/******************************************************************************/

/*** Fun��es da TRAVA ***/
void fnTravaDetector(void) //Fun��o que trava a porta girat�ria
{
	if(statusPGDM != 1){
		if(sinal_trava == trava_pulso) //Se sinal_trava for igual a trava_pulso ent�o
		{
			fnLigaPulsoTrava(); //Permite pulsar a trava
		}
		else
		{
			LIGA_TRAVA; //Energiza a trava
			LIGA_RELE; //Energiza o rel�
		}
		LIGA_SINALEIRA_VERMELHA; //Liga a sinaleira vermelha
		if(sinal_trava == trava_retencao_controle || sinal_trava == trava_retencao_controle_teclado) //Se sinal_trava for igual a trava_retencao_controle ou sinal_trava for igual a trava_retencao_controle_teclado ent�o
		{
			if(travado == FALSE)
			{
				contador_bloqueios++; //Incrementa contador_bloqueios
				INICIA_TIME_OUT_CONTADOR_BLOQUEIOS_DESBLOQUEIOS = TRUE; //Armazena na vari�vel INICIA_TIME_OUT_CONTADOR_DESBLOQUEIOS a informa��o TRUE
				time_out_contador = 0; //Zera o time_out_contador
				travado = TRUE;
			}
		}
	}
	estado = ESTADO_LE_AREAS_DETECCAO; //Estado a ser executado � ESTADO_LE_AREAS_DETECCAO
}

void fnDestravaDetector(void) //Fun��o que destrava a porta girat�ria
{
	tempo_cadastro_controle = 0;
//	while((DECREMENTA || DESTRAVA_REMOTO) && tempo_cadastro_controle < 2); //Aqui segura o tempo por 2s se tecla decrementa ou destrava remoto pressionada antes de destravar a porta
//	tempo_cadastro_controle = 0;

	flag_area_detectada = 0;
	DESLIGA_RELE; //Desenergiza o rel�
	APAGA_AREAS; //Apaga os leds das �reas
	ACENDE_NIVEL0; //Apaga os leds do bargraph
	LIGA_SINALEIRA_VERDE; //Liga sinaleira verde
	fnCortaMsgVoz(); //Corta a mensagem de voz
	areas_detectadas = 0; //Zera a vari�vel areas_detectadas
	Solenoide_DisableEvent();		//Desativa evento que gera PWM solenoide
	Solenoide_Disable();			//Desativa Timer que gera o evento do PWM solenoide
	tempo_trava = 0;				//Reseta contador de tempo para ativar PWM da solenoide
	pwm_trava = 0;					//Reseta contador PWM da solenoide
	DESLIGA_TRAVA; 					//Desenergiza a trava
	if(sinal_trava == trava_retencao_controle || sinal_trava == trava_retencao_controle_teclado) //Se sinal_trava for igual a trava_retencao_controle ou sinal_trava for igual a trava_retencao_controle_teclado ent�o
	{
		if(travado == TRUE)
		{
			contador_desbloqueios++; //Incrementa contador_bloqueios
			INICIA_TIME_OUT_CONTADOR_BLOQUEIOS_DESBLOQUEIOS = TRUE; //Armazena na vari�vel INICIA_TIME_OUT_CONTADOR_DESBLOQUEIOS a informa��o TRUE
			time_out_contador = 0; //Zera o time_out_contador
			travado = FALSE;
		}
		delay_ms(300);
		while(DECREMENTA || DESTRAVA_REMOTO)
		{
			TocaTomBuzzer();
			delay_ms(500);
		}
	}
	estado = ESTADO_LE_AREAS_DETECCAO; //Estado a ser executado � ESTADO_LE_AREAS_DETECCAO
}
/******************************************************************************/

/*** Fun��es da USB-SERIAL ***/
void TrataSerial(void) //Fun��o que recebe os dados seriais do PC e toma as devidas a��es
{

	static word ano = 0;
	static word numero_registros = 0;
	static dword aux_numero_registros = 0;
	static dword aux_num_bytes;
	static dword aux_num_bloco;
	static DataHora time_aux; //Vari�vel time_aux recebe a estrutura de DataHora

	static int numeroEventosUltimoChamado;
	static int indexEventLog = 0;

	static int numeroAuditoriasUltimoChamado;
	static int indexAuditoriasLog = 0;

	int indexAuditLog = 0;
	int enderecoAuditLog = 0;

	aux_numero_registros = 0;

	if(recebe_serial1[1] == 'c' && recebe_serial1[2] == 'd') //Se condi��o satisfeita ent�o estabelece conex�o
	{
		static byte envia_serial1[5]; //Define vetor envia_serial com 5 posi��es
		//Armazena em cada posi��o do vetor envia_serial uma informa��o
		envia_serial1[0] = '#'; //Caracter de inicio
		envia_serial1[1] = 'd';
		envia_serial1[2] = 'c';
		envia_serial1[3] = '!'; //Caracter de fim
		envia_serial1[4] = 0xFF; //Caracter de fim
		USB_PC_SendBlock((byte*)&envia_serial1,5,&Sent1); //Envia os dados seriais
	}
	else if(recebe_serial1[1] == 'r' && recebe_serial1[2] == 'p') //Sen�o se condi��o satisfeitas significa que o software do PC solicitou
	{
		//Armazena em cada posi��o do vetor envia_serial uma informa��o
		envia_serial1[0] = '#'; //Caracter de inicio
		for(x = 1;x < 9;x++) //Envia a sensibilidade da �rea 1 a �rea 8
		{
			envia_serial1[x] = buffer_sensibilidade[x];
		}
		envia_serial1[9] = selecao_metais; //Envia a sele��o de metais
		envia_serial1[10] = filtroruido; //Envia o valor do filtro de ruido
		envia_serial1[11] = var_tensao_cinco; //Envia a tens�o de cinco volts multiplicada por 10
		envia_serial1[12] = var_tensao_quinze; //Envia a tens�o de quize volts multiplicada por 10
		envia_serial1[13] = var_tensao_menos_quinze; //Envia a tens�o de quinze volts multiplicada por 10
		envia_serial1[14] = var_tensao_rede; //Envia a tens�o da rede
		envia_serial1[15] = (byte)(var_tensao_bateria >> 8); //Envia o byte alto da tens�o da bateria
		envia_serial1[16] = (byte)(var_tensao_bateria); //Envia o byte baixo da tens�o da bateria
		for(x = 17;x < 25;x++) //Envia o anula_area da �rea 1 a �rea 8, se 0 n�o anula, se 1 anula
		{
			envia_serial1[x] = anula_area[x-17];
		}
		envia_serial1[25] = (byte)(contador_entra >> 24); //Escreve o valor do quarto byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial1[26] = (byte)(contador_entra >> 16); //Escreve o valor do terceiro byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial1[27] = (byte)(contador_entra >> 8); //Escreve o valor do segundo byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial1[28] = (byte)(contador_entra); //Escreve o valor do primeiro byte no vetor para grava��o na mem�ria FLASH

		envia_serial1[29] = (byte)(contador_sai >> 24); //Escreve o valor do quarto byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial1[30] = (byte)(contador_sai >> 16); //Escreve o valor do terceiro byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial1[31] = (byte)(contador_sai >> 8); //Escreve o valor do segundo byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial1[32] = (byte)(contador_sai); //Escreve o valor do primeiro byte no vetor para grava��o na mem�ria FLASH

		envia_serial1[33] = (byte)(contador_bloqueios >> 24); //Escreve o valor do quarto byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial1[34] = (byte)(contador_bloqueios >> 16); //Escreve o valor do terceiro byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial1[35] = (byte)(contador_bloqueios >> 8); //Escreve o valor do segundo byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial1[36] = (byte)(contador_bloqueios); //Escreve o valor do primeiro byte no vetor para grava��o na mem�ria FLASH

		envia_serial1[37] = (byte)(contador_desbloqueios >> 24); //Escreve o valor do quarto byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial1[38] = (byte)(contador_desbloqueios >> 16); //Escreve o valor do terceiro byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial1[39] = (byte)(contador_desbloqueios >> 8); //Escreve o valor do segundo byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial1[40] = (byte)(contador_desbloqueios); //Escreve o valor do primeiro byte no vetor para grava��o na mem�ria FLASH

		time_aux = GetData(); //A estrutura time_aux recebe as informa��es de data e hora atuais
		dataAtualizar = GetData(); //A estrutura dataAtualizar recebe os valores de data e hora atuais

		envia_serial1[41] = dataAtualizar.Dia; //Envia o dia atual
		envia_serial1[42] = dataAtualizar.Mes; //Envia o m�s atual

		ano = dataAtualizar.Ano; //Armazena na vari�vel ano o ano atual
		envia_serial1[43] = (byte)(ano >> 8); //Envia o byte alto do ano
		envia_serial1[44] = (byte)(ano); //Envia o byte baixo do ano

		envia_serial1[45] = sinal_rele; //Envia o sinal do rel� - se pulso ou reten��o

		envia_serial1[46] = sinal_trava; //Envia o sinal da trava - se pulso ou reten��o e controle somente ou reten��o e controle e teclado

		envia_serial1[47] = pulso_rele; //Envia o pulso do rel� multiplicado por 10

		envia_serial1[48] = pulso_trava; //Envia o pulso da trava multiplicado por 10

		envia_serial1[49] = modo_travamento; //Envia o modo de travamento do controle - somente destrava ou trava/destrava

		envia_serial1[50] = buffer_buzzer[BUZZER_VOLUME]; //Envia o volume do buzzer - 0 a 10, sendo 0 desligado

		envia_serial1[51] = volume_mensagem_voz; //Envia o volume da mensagem de voz - 0 a 10, sendo 0 desligado

		envia_serial1[52] = canal; //Envia o canal

		if(tipo_detector == Z3)
		{
			envia_serial1[53] = 3;
		}
		else if(tipo_detector == Z8)
		{
			envia_serial1[53] = 8;
		}

		envia_serial1[54] = '!'; //Caracter de fim

		envia_serial1[55] = 0xFF; //Caracter de fim

		USB_PC_SendBlock((byte*)&envia_serial1,56,&Sent1); //Envia os 55 byte de dados para o PC
	}

	else if(recebe_serial1[1] == 'a' && recebe_serial1[2] == 'p') //Sen�o se condi��o satisfeitas significa que o software do PC solicitou
	{
		//Armazena os valores recebidos nos par�metros correspondentes

		for(int y1 = 3;y1 < 11;y1++) //Armazena a sensibilidade da �rea 1 a �rea 8
		{
			if(buffer_sensibilidade[y1 - 2] != recebe_serial1[y1])
			{
				fnGravaAuditoria((90 + (y1 - 2)),buffer_sensibilidade[y1 - 2],recebe_serial1[y1],'G','S');
			}
			buffer_sensibilidade[y1 - 2] = recebe_serial1[y1];
		}

		Write_Buffer_FLASH[0] = buffer_sensibilidade[AREA_1]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o da sensibilidade
		Write_Buffer_FLASH[1] = buffer_sensibilidade[AREA_2]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o da sensibilidade
		Write_Buffer_FLASH[2] = buffer_sensibilidade[AREA_3]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o da sensibilidade
		Write_Buffer_FLASH[3] = buffer_sensibilidade[AREA_4]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o da sensibilidade
		Write_Buffer_FLASH[4] = buffer_sensibilidade[AREA_5]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o da sensibilidade
		Write_Buffer_FLASH[5] = buffer_sensibilidade[AREA_6]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o da sensibilidade
		Write_Buffer_FLASH[6] = buffer_sensibilidade[AREA_7]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o da sensibilidade
		Write_Buffer_FLASH[7] = buffer_sensibilidade[AREA_8]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o da sensibilidade
		ESCREVE_FLASH_INTERNA(endFLASHSensibilidadeArea1,8,0); //Escreve os valores de sensibilidade das �reas na mem�ria FLASH no endere�o especificado

		delay_ms(10); //Espera 10ms

		if(selecao_metais != recebe_serial1[11])
		{
			fnGravaAuditoria(3,selecao_metais,recebe_serial1[11],'G','S');
		}
		selecao_metais = recebe_serial1[11]; //Armazena a sele��o de metais

		Write_Buffer_FLASH[0] = selecao_metais; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o da selecao de metais
		ESCREVE_FLASH_INTERNA(endFLASHSelecaoMetais,1,0); //Escreve o valor da selecao de metais na mem�ria FLASH no endere�o especificado

		delay_ms(10); //Espera 10ms

		if(filtroruido != recebe_serial1[12])
		{
			fnGravaAuditoria(12,filtroruido,recebe_serial1[12],'G','S');
		}

		filtroruido = recebe_serial1[12]; //Armazena o valor do filtro de ruido

		Write_Buffer_FLASH[0] = filtroruido; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o do filtro de ruido
		ESCREVE_FLASH_INTERNA(endFLASHFiltroRuido,1,0); //Escreve o valor do filtro de ruido na mem�ria FLASH no endere�o especificado

		delay_ms(10); //Espera 10ms

		for(int y1 = 13;y1 < 21;y1++) //Armazena o anula_area da �rea 1 a �rea 8, se 0 n�o anula, se 1 anula
		{
			if(anula_area[y1 - 13] != recebe_serial1[y1])
			{
				fnGravaAuditoria((80 + (y1 - 12)),anula_area[y1 - 13],recebe_serial1[y1],'G','S');
			}

			anula_area[y1 - 13] = recebe_serial1[y1];
		}

		Write_Buffer_FLASH[0] = anula_area[AREA1]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o de anula_area
		Write_Buffer_FLASH[1] = anula_area[AREA2]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o de anula_area
		Write_Buffer_FLASH[2] = anula_area[AREA3]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o de anula_area
		Write_Buffer_FLASH[3] = anula_area[AREA4]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o de anula_area
		Write_Buffer_FLASH[4] = anula_area[AREA5]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o de anula_area
		Write_Buffer_FLASH[5] = anula_area[AREA6]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o de anula_area
		Write_Buffer_FLASH[6] = anula_area[AREA7]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o de anula_area
		Write_Buffer_FLASH[7] = anula_area[AREA8]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o de anula_area
		ESCREVE_FLASH_INTERNA(endFLASHAnulaArea1,8,0); //Escreve os valores de anula_area das �reas na mem�ria FLASH no endere�o especificado

		delay_ms(10); //Espera 10ms

		if(sinal_rele != recebe_serial1[21])
		{
			fnGravaAuditoria(6,sinal_rele,recebe_serial1[21],'G','S');
		}

		sinal_rele = recebe_serial1[21]; //Armazena o sinal do rel� - se pulso ou reten��o

		Write_Buffer_FLASH[0] = sinal_rele; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o do sinal do rel�
		ESCREVE_FLASH_INTERNA(endFLASHSinalRele,1,0); //Escreve o valor do sinal do rel� na mem�ria FLASH no endere�o especificado

		delay_ms(10); //Espera 10ms

		if(sinal_trava != recebe_serial1[22])
		{
			fnGravaAuditoria(4,sinal_trava,recebe_serial1[22],'G','S');
		}

		sinal_trava = recebe_serial1[22]; //Armazena o sinal da trava - se pulso ou reten��o e controle somente ou reten��o e controle e teclado

		Write_Buffer_FLASH[0] = sinal_trava; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o do sinal da trava
		ESCREVE_FLASH_INTERNA(endFLASHSinalTrava,1,0); //Escreve o valor do sinal da trava na mem�ria FLASH no endere�o especificado

		delay_ms(10); //Espera 10ms

		if(pulso_rele != recebe_serial1[23])
		{
			fnGravaAuditoria(7,pulso_rele,recebe_serial1[23],'G','S');
		}

		pulso_rele = recebe_serial1[23]; //Armazena o pulso do rel� multiplicado por 10

		Write_Buffer_FLASH[0] = pulso_rele; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o do pulso do rel�
		ESCREVE_FLASH_INTERNA(endFLASHPulsoRele,1,0); //Escreve o valor do pulso do rel� na mem�ria FLASH no endere�o especificado

		delay_ms(10); //Espera 10ms

		if(pulso_trava != recebe_serial1[24])
		{
			fnGravaAuditoria(5,pulso_trava,recebe_serial1[24],'G','S');
		}

		pulso_trava = recebe_serial1[24]; //Armazena o pulso da trava multiplicado por 10

		Write_Buffer_FLASH[0] = pulso_trava; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o do pulso do rel�
		ESCREVE_FLASH_INTERNA(endFLASHPulsoTrava,1,0); //Escreve o valor do pulso da trava na mem�ria FLASH no endere�o especificado

		delay_ms(10); //Espera 10ms

		if(modo_travamento != recebe_serial1[25])
		{
			fnGravaAuditoria(1,modo_travamento,recebe_serial1[25],'G','S');
		}

		modo_travamento = recebe_serial1[25]; //Armazena o modo de travamento do controle - somente destrava ou trava/destrava

		Write_Buffer_FLASH[0] = modo_travamento; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o do modo de travamento
		ESCREVE_FLASH_INTERNA(endFLASHModoTravamento,1,0); //Escreve o valor do modo de travamento na mem�ria FLASH no endere�o especificado

		delay_ms(10); //Espera 10ms

		if(buffer_buzzer[BUZZER_VOLUME] != recebe_serial1[26])
		{
			fnGravaAuditoria(24,buffer_buzzer[BUZZER_VOLUME],recebe_serial1[26],'G','S');
		}

		buffer_buzzer[BUZZER_VOLUME] = recebe_serial1[26]; //Armazena o volume do buzzer - 0 a 10, sendo 0 desligado

		Write_Buffer_FLASH[0] = buffer_buzzer[BUZZER_VOLUME]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o do volume do buzzer
		ESCREVE_FLASH_INTERNA(endFLASHBuzzerVolume,1,0); //Escreve o valor do volume do buzzer na mem�ria FLASH no endere�o especificado

		delay_ms(10); //Espera 10ms

		if(volume_mensagem_voz != recebe_serial1[27])
		{
			fnGravaAuditoria(25,volume_mensagem_voz,recebe_serial1[27],'G','S');
		}

		volume_mensagem_voz = recebe_serial1[27]; //Armazena o volume da mensagem de voz - 0 a 10, sendo 0 desligado

		Write_Buffer_FLASH[0] = volume_mensagem_voz; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o do volume da mensagem de voz
		ESCREVE_FLASH_INTERNA(endFLASHMensagemVozVolume,1,0); //Escreve o valor do volume da mensagem de voz na mem�ria FLASH no endere�o especificado

		delay_ms(10); //Espera 10ms

		if(canal != recebe_serial1[28])
		{
			fnGravaAuditoria(2,canal,recebe_serial1[28],'G','S');
		}

		canal = recebe_serial1[28]; //Armazena o canal

		Write_Buffer_FLASH[0] = canal; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o do canal
		ESCREVE_FLASH_INTERNA(endFLASHCanal,1,0); //Escreve o valor do canal na mem�ria FLASH no endere�o especificado

		delay_ms(10); //Espera 10ms
	}

	//(recebe_serial1[1] == 'r' && recebe_serial1[2] == 'l')
	else if(recebe_serial1[1] == 'r' && recebe_serial1[2] == 'l') //Sen�o se condi��o satisfeitas significa que o software do PC solicitou - r  = requisi��o e l = log
	{// l = evento

		qtdnl = qtdnl + 1;
		memset(envia_serial1,0,sizeof(envia_serial1));


		LE_FLASH_INTERNA((END_INI_LOG_EVENTOS+(indexEventLog*8)),8);

		envia_serial1[0] = '#'; //Caracter de inicio

		envia_serial1[1] = Read_Buffer_FLASH[0]; //evento
		envia_serial1[2] = Read_Buffer_FLASH[1]; //dispositivo
		envia_serial1[3] = Read_Buffer_FLASH[2]; //hora
		envia_serial1[4] = Read_Buffer_FLASH[3]; //minuto
		envia_serial1[5] = Read_Buffer_FLASH[4]; //dia
		envia_serial1[6] = Read_Buffer_FLASH[5]; //mes
		envia_serial1[7] = Read_Buffer_FLASH[6]; //ano byte alto - quando receber fazer sua_variavel[7] << 8 + sua_variavel[8]
		envia_serial1[8] = Read_Buffer_FLASH[7]; //ano byte baixo

		envia_serial1[9] = '!'; //Caracter de fim
		envia_serial1[10] = 0xFF; //Caracter de fim

		USB_PC_SendBlock((byte*)&envia_serial1,11,&Sent1); //Envia os dados seriais

		indexEventLog++;

		if(indexEventLog == numeroEventosUltimoChamado || indexEventLog >= 2048) indexEventLog = 0;

	}

	else if(recebe_serial1[1] == 'r' && recebe_serial1[2] == 'a') //Sen�o se condi��o satisfeitas significa que o software do PC solicitou - r  = requisi��o e a = auditoria
	{ // a = auditoria

		memset(envia_serial1,0,sizeof(envia_serial1));

		LE_FLASH_INTERNA((END_INI_LOG_AUDITORIAS+(indexAuditoriasLog*11)),11);

		envia_serial1[0] = '#'; //Caracter de inicio

		envia_serial1[1] = Read_Buffer_FLASH[0];	//Parametro
		envia_serial1[2] = Read_Buffer_FLASH[1];	//valor_velho
		envia_serial1[3] = Read_Buffer_FLASH[2]; 	//valor_novo
		envia_serial1[4] = Read_Buffer_FLASH[3];	//operador
		envia_serial1[5] = Read_Buffer_FLASH[4];	//dispositivo
		envia_serial1[6] = Read_Buffer_FLASH[5];	//Hora
		envia_serial1[7] = Read_Buffer_FLASH[6];	//Minuto
		envia_serial1[8] = Read_Buffer_FLASH[7];	//Dia
		envia_serial1[9] = Read_Buffer_FLASH[8];	//Mes
		envia_serial1[10] = Read_Buffer_FLASH[9];	//Ano - byte alto
		envia_serial1[11] = Read_Buffer_FLASH[10];  	//Ano - byte baixo

		envia_serial1[12] = '!'; //Caracter de fim
		envia_serial1[13] = 0xFF; //Caracter de fim

		USB_PC_SendBlock((byte*)&envia_serial1,14,&Sent1); //Envia os dados seriais

		indexAuditoriasLog++;

		if(indexAuditoriasLog == numeroAuditoriasUltimoChamado || indexAuditoriasLog >= 2048) indexAuditoriasLog = 0;

/*

		indexAuditLog = 0;
		enderecoAuditLog = 0x49000;
		memset(envia_serial1,0,sizeof(envia_serial1));

		if(enderecoAuditLog < 0x75000 && (Read_Buffer_FLASH[0]!='\0')){

			LE_FLASH_INTERNA(enderecoAuditLog,11);

			envia_serial1[0] = '#'; //Caracter de inicio
			envia_serial1[1] = Read_Buffer_FLASH[0]; //par�metro
			envia_serial1[2] = Read_Buffer_FLASH[1]; //valor_velho
			envia_serial1[3] = Read_Buffer_FLASH[2]; //valor_novo
			envia_serial1[4] = Read_Buffer_FLASH[3]; //operador
			envia_serial1[5] = Read_Buffer_FLASH[4]; //dispositivo
			envia_serial1[6] = Read_Buffer_FLASH[5]; //hora
			envia_serial1[7] = Read_Buffer_FLASH[6]; //minuto
			envia_serial1[8] = Read_Buffer_FLASH[7]; //dia
			envia_serial1[9] = Read_Buffer_FLASH[8]; //mes
			envia_serial1[10] = Read_Buffer_FLASH[9]; //ano byte alto - quando receber fazer sua_variavel[7] << 8 + sua_variavel[8]
			envia_serial1[11] = Read_Buffer_FLASH[10]; //ano byte baixo
			envia_serial1[12] = '!'; //Caracter de fim
			envia_serial1[13] = 0xFF; //Caracter de fim

			if(Read_Buffer_FLASH[0]!='\0')	USB_PC_SendBlock((byte*)&envia_serial1,strlen(envia_serial1),&Sent1); //Envia os dados seriais

			indexAuditLog++;
			enderecoAuditLog = (indexAuditLog/372)*0x1000 + ((indexAuditLog)%372)*11 + END_INI_LOG_AUDITORIAS;
		};

		memset(envia_serial1,0,sizeof(envia_serial1));
		strcpy(envia_serial1,"#ra!�");
		USB_PC_SendBlock((byte*)&envia_serial1,strlen(envia_serial1),&Sent1);
	*/
		/*

		if(num_bytes_a == 4092 && num_bloco_a == 120) //Se n�mero de bytes for igual a 4092 e n�mero do bloco for igual a 120 ent�o
		{
			num_bloco_a = 5;
			num_bytes_a = 0;
		}
		else if(num_bytes_a == 4092 && num_bloco_a < 120) //Sen�o se n�mero de bytes for igual a 4096 e n�mero do bloco for igual a 124 ent�o
		{
			num_bloco_a++;
			num_bytes_a = 0;
		}

		end_bloco_a = 0x83000 + num_bytes_a + (num_bloco_a * 4096); //end_bloco = 0x83000 + 0 bytes + (5 * 4096) = 0x88000

		LE_FLASH_INTERNA(end_bloco_a,11); //L� os 11 bytes a partir do endere�o especificado

		//Armazena em cada posi��o do vetor envia_serial uma informa��o
		envia_serial1[0] = '#'; //Caracter de inicio
		envia_serial1[1] = Read_Buffer_FLASH[0]; //par�metro
		envia_serial1[2] = Read_Buffer_FLASH[1]; //valor_velho
		envia_serial1[3] = Read_Buffer_FLASH[2]; //valor_novo
		envia_serial1[4] = Read_Buffer_FLASH[3]; //operador
		envia_serial1[5] = Read_Buffer_FLASH[4]; //dispositivo
		envia_serial1[6] = Read_Buffer_FLASH[5]; //hora
		envia_serial1[7] = Read_Buffer_FLASH[6]; //minuto
		envia_serial1[8] = Read_Buffer_FLASH[7]; //dia
		envia_serial1[9] = Read_Buffer_FLASH[8]; //mes
		envia_serial1[10] = Read_Buffer_FLASH[9]; //ano byte alto - quando receber fazer sua_variavel[7] << 8 + sua_variavel[8]
		envia_serial1[11] = Read_Buffer_FLASH[10]; //ano byte baixo
		envia_serial1[12] = '!'; //Caracter de fim
		envia_serial1[13] = '\n'; //Caracter de fim

		USB_PC_SendBlock((byte*)&envia_serial1,14,&Sent1); //Envia os dados seriais

		num_bytes_a = num_bytes_a + 11; //Incrementa o num_bytes 8 posi��es para ler o pr�ximo log

		*/
	}

	else if(recebe_serial1[1] == 'n' && recebe_serial1[2] == 'l') //Sen�o se condi��o satisfeitas significa que o software do PC solicitou - n  = n�mero e l = log
	{	//NUMERO DE EVENTOS

		indexEventLog = 0;
		numeroEventosUltimoChamado = 0;
		for(numeroEventosUltimoChamado = 0; numeroEventosUltimoChamado<2048;){

			LE_FLASH_INTERNA(END_INI_LOG_EVENTOS + (numeroEventosUltimoChamado*8),8);
			if((Read_Buffer_FLASH[0] == 0xFF && Read_Buffer_FLASH[1] == 0xFF && Read_Buffer_FLASH[2] == 0xFF && Read_Buffer_FLASH[3] == 0xFF &&
			Read_Buffer_FLASH[4] == 0xFF && Read_Buffer_FLASH[5] == 0xFF && Read_Buffer_FLASH[6] == 0xFF && Read_Buffer_FLASH[7] == 0xFF) ||
					(Read_Buffer_FLASH[0] == 0x00 && Read_Buffer_FLASH[1] == 0x00 && Read_Buffer_FLASH[2] == 0x00 && Read_Buffer_FLASH[3] == 0x00 &&
					Read_Buffer_FLASH[4] == 0x00 && Read_Buffer_FLASH[5] == 0x00 && Read_Buffer_FLASH[6] == 0x00 && Read_Buffer_FLASH[7] == 0x00) ) {
				break;
			}
			numeroEventosUltimoChamado++;
		}

		//Armazena em cada posi��o do vetor envia_serial uma informa��o
		envia_serial1[0] = '#'; //Caracter de inicio
		envia_serial1[1] = (byte)(numeroEventosUltimoChamado >> 8);
		envia_serial1[2] = (byte)(numeroEventosUltimoChamado);
		envia_serial1[3] = '!'; //Caracter de fim
		envia_serial1[4] = 0xFF; //Caracter de fim

		USB_PC_SendBlock((byte*)&envia_serial1,5,&Sent1); //Envia os dados seriais
		/*



		LE_FLASH_INTERNA(end_bloco_l,8);

		for(num_bloco_l = 1;num_bloco_l < 5;num_bloco_l++)
		{
			for(num_bytes_l = 0;num_bytes_l < 4096;num_bytes_l = num_bytes_l + 8)
			{
				end_bloco_l = 0x83000 + num_bytes_l + (num_bloco_l * 4096); //end_bloco_l = 0x83000 + 0 bytes + (1 * 4096) = 0x84000

				LE_FLASH_INTERNA(end_bloco_l,8); //L� os 8 bytes a partir do endere�o especificado

				if(Read_Buffer_FLASH[0] == 0xFF && Read_Buffer_FLASH[1] == 0xFF && Read_Buffer_FLASH[2] == 0xFF && Read_Buffer_FLASH[3] == 0xFF &&
				   Read_Buffer_FLASH[4] == 0xFF && Read_Buffer_FLASH[5] == 0xFF && Read_Buffer_FLASH[6] == 0xFF && Read_Buffer_FLASH[7] == 0xFF) //Se todos os 8 bytes forem igual 0xFF ent�o
				{
					if(num_bytes_l > 0 && num_bytes_l < 4096)
					{
						aux_num_bytes = num_bytes_l;
						aux_num_bloco = (num_bloco_l - 1);
						num_bytes_l = 4096;
						num_bloco_l = 5;
					}
					else if(num_bytes_l == 0 && num_bloco_l > 0)
					{
						aux_num_bytes = num_bytes_l;
						aux_num_bloco = (num_bloco_l - 1);

						num_bytes_l = 4096;
						num_bloco_l = 5;
					}
					else if(num_bytes_l == 4104 && num_bloco_l > 0)
					{
						aux_num_bytes = 0;
						aux_num_bloco = (num_bloco_l - 1);

						num_bytes_l = 4096;
						num_bloco_a = 5;
					}
				}
			}
		}
		if(aux_num_bloco >= 1)
		{
			aux_numero_registros = (aux_num_bloco * 4096) + (aux_num_bytes);
		}
		else if(aux_num_bytes == 0 && aux_num_bloco == 1)
		{
			aux_numero_registros = 0;
		}
		else if(aux_num_bytes > 0 && aux_num_bloco == 0)
		{
			aux_numero_registros = aux_num_bytes;
		}
		else if(num_bytes_l == 4096 && num_bloco_l == 5)
		{
			aux_numero_registros = (num_bloco_l - 1) * 4096;
		}

		numero_registros = (word)(aux_numero_registros / 8);

		num_bytes_l = 0;
		num_bloco_l = 1;

		//Armazena em cada posi��o do vetor envia_serial uma informa��o
		envia_serial1[0] = '#'; //Caracter de inicio
		envia_serial1[1] = (byte)(numero_registros >> 8);
		envia_serial1[2] = (byte)(numero_registros);
		envia_serial1[3] = '!'; //Caracter de fim
		envia_serial1[4] = '\n'; //Caracter de fim

		USB_PC_SendBlock((byte*)&envia_serial1,5,&Sent1); //Envia os dados seriais

		*/
	}

	else if(recebe_serial1[1] == 'n' && recebe_serial1[2] == 'a') //Sen�o se condi��o satisfeitas significa que o software do PC solicitou - n  = n�mero e a = auditorias
	{	//NUMERO DE AUDITORIAS

		indexAuditoriasLog = 0;
		numeroAuditoriasUltimoChamado = 0;
		for(numeroAuditoriasUltimoChamado = 0; numeroAuditoriasUltimoChamado<2048;){

			LE_FLASH_INTERNA(END_INI_LOG_AUDITORIAS + (numeroAuditoriasUltimoChamado*11),11);
			if((Read_Buffer_FLASH[0] == 0xFF && Read_Buffer_FLASH[1] == 0xFF && Read_Buffer_FLASH[2] == 0xFF && Read_Buffer_FLASH[3] == 0xFF &&
			Read_Buffer_FLASH[4] == 0xFF && Read_Buffer_FLASH[5] == 0xFF && Read_Buffer_FLASH[6] == 0xFF && Read_Buffer_FLASH[7] == 0xFF) ||
					(Read_Buffer_FLASH[0] == 0x00 && Read_Buffer_FLASH[1] == 0x00 && Read_Buffer_FLASH[2] == 0x00 && Read_Buffer_FLASH[3] == 0x00 &&
					Read_Buffer_FLASH[4] == 0x00 && Read_Buffer_FLASH[5] == 0x00 && Read_Buffer_FLASH[6] == 0x00 && Read_Buffer_FLASH[7] == 0x00) ) {
				break;
			}
			numeroAuditoriasUltimoChamado++;
		}

		//Armazena em cada posi��o do vetor envia_serial uma informa��o
		envia_serial1[0] = '#'; //Caracter de inicio
		envia_serial1[1] = (byte)(numeroAuditoriasUltimoChamado >> 8);
		envia_serial1[2] = (byte)(numeroAuditoriasUltimoChamado);
		envia_serial1[3] = '!'; //Caracter de fim
		envia_serial1[4] = 0xFF; //Caracter de fim

		USB_PC_SendBlock((byte*)&envia_serial1,5,&Sent1); //Envia os dados seriais

		/*
		for(num_bloco_a = 5;num_bloco_a < 125;num_bloco_a++)
		{
			for(num_bytes_a = 0;num_bytes_a < 4092;num_bytes_a = num_bytes_a + 11)
			{
				end_bloco_a = 0x83000 + num_bytes_a + (num_bloco_a * 4096); //end_bloco = 0x83000 + 0 bytes + (5 * 4096) = 0x84000

				LE_FLASH_INTERNA(end_bloco_a,11); //L� os 11 bytes a partir do endere�o especificado

				if(Read_Buffer_FLASH[0] == 0xFF && Read_Buffer_FLASH[1] == 0xFF && Read_Buffer_FLASH[2] == 0xFF && Read_Buffer_FLASH[3] == 0xFF &&
				   Read_Buffer_FLASH[4] == 0xFF && Read_Buffer_FLASH[5] == 0xFF && Read_Buffer_FLASH[6] == 0xFF && Read_Buffer_FLASH[7] == 0xFF &&
				   Read_Buffer_FLASH[8] == 0xFF && Read_Buffer_FLASH[9] == 0xFF && Read_Buffer_FLASH[10] == 0xFF) //Se todos os 11 bytes forem igual 0xFF ent�o
				{
					if(num_bytes_a > 0 && num_bytes_a < 4096)
					{
						aux_num_bytes = num_bytes_a;
						aux_num_bloco = (num_bloco_a - 5);
						num_bytes_a = 4092;
						num_bloco_a = 125;
					}
					else if(num_bytes_a == 0 && num_bloco_a > 0)
					{
						aux_num_bytes = num_bytes_a;
						aux_num_bloco = (num_bloco_a - 5);

						num_bytes_a = 4092;
						num_bloco_a = 125;
					}
					else if(num_bytes_a == 4103 && num_bloco_a > 0)
					{
						aux_num_bytes = 0;
						aux_num_bloco = (num_bloco_a - 5);

						num_bytes_a = 4092;
						num_bloco_a = 125;
					}
				}
			}
		}
		if(aux_num_bloco >= 1)
		{
			aux_numero_registros = (aux_num_bloco * 4092) + (aux_num_bytes);
		}
		else if(aux_num_bytes == 0 && aux_num_bloco == 1)
		{
			aux_numero_registros = 0;
		}
		else if(aux_num_bytes > 0 && aux_num_bloco == 0)
		{
			aux_numero_registros = aux_num_bytes;
		}
		else if(num_bytes_a == 4092 && num_bloco_a == 125)
		{
			aux_numero_registros = (num_bloco_a - 5) * 4092;
		}

		numero_registros = (word)(aux_numero_registros / 11);

		num_bytes_a = 0;
		num_bloco_a = 5;

		//Armazena em cada posi��o do vetor envia_serial uma informa��o
		envia_serial1[0] = '#'; //Caracter de inicio
		envia_serial1[1] = (byte)(numero_registros >> 8);
		envia_serial1[2] = (byte)(numero_registros);
		envia_serial1[3] = '!'; //Caracter de fim
		envia_serial1[4] = 0xFF; //Caracter de fim

		USB_PC_SendBlock((byte*)&envia_serial1,5,&Sent1); //Envia os dados seriais
		*/
	}

	estado_SERIAL = ESTADO_ESPERA; //Estado a ser executado � ESTADO_ESPERA
}
/******************************************************************************/

/*** Fun��es da ETHERNET-SERIAL ***/
void TrataSerial1(void) //Fun��o que recebe os dados seriais do PC e toma as devidas a��es
{
	static word ano = 0;
	static word numero_registros = 0;
	static dword aux_numero_registros = 0;
	static dword aux_num_bytes;
	static dword aux_num_bloco;
	static DataHora time_aux; //Vari�vel time_aux recebe a estrutura de DataHora
	aux_numero_registros = 0;

	if(recebe_serial[1] == 'c' && recebe_serial[2] == 'd') //Se condi��o satisfeita ent�o estabelece conex�o
	{
		static byte envia_serial[5]; //Define vetor envia_serial com 5 posi��es
		//Armazena em cada posi��o do vetor envia_serial uma informa��o
		envia_serial[0] = '#'; //Caracter de inicio
		envia_serial[1] = 'd';
		envia_serial[2] = 'c';
		envia_serial[3] = '!'; //Caracter de fim
		envia_serial[4] = '\n'; //Caracter de fim
		SERIAL_ETHERNET_SendBlock((byte*)&envia_serial,5,&Sent); //Envia os dados seriais
	}
	else if(recebe_serial[1] == 'r' && recebe_serial[2] == 'p') //Sen�o se condi��o satisfeitas significa que o software do PC solicitou
	{
		//Armazena em cada posi��o do vetor envia_serial uma informa��o
		envia_serial[0] = '#'; //Caracter de inicio
		for(x = 1;x < 9;x++) //Envia a sensibilidade da �rea 1 a �rea 8
		{
			envia_serial[x] = buffer_sensibilidade[x];
		}
		envia_serial[9] = selecao_metais; //Envia a sele��o de metais
		envia_serial[10] = filtroruido; //Envia o valor do filtro de ruido
		envia_serial[11] = var_tensao_cinco; //Envia a tens�o de cinco volts multiplicada por 10
		envia_serial[12] = var_tensao_quinze; //Envia a tens�o de quize volts multiplicada por 10
		envia_serial[13] = var_tensao_menos_quinze; //Envia a tens�o de quinze volts multiplicada por 10
		envia_serial[14] = var_tensao_rede; //Envia a tens�o da rede
		envia_serial[15] = (byte)(var_tensao_bateria >> 8); //Envia o byte alto da tens�o da bateria
		envia_serial[16] = (byte)(var_tensao_bateria); //Envia o byte baixo da tens�o da bateria
		for(x = 17;x < 25;x++) //Envia o anula_area da �rea 1 a �rea 8, se 0 n�o anula, se 1 anula
		{
			envia_serial[x] = anula_area[x-17];
		}
		envia_serial[25] = (byte)(contador_entra >> 24); //Escreve o valor do quarto byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial[26] = (byte)(contador_entra >> 16); //Escreve o valor do terceiro byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial[27] = (byte)(contador_entra >> 8); //Escreve o valor do segundo byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial[28] = (byte)(contador_entra); //Escreve o valor do primeiro byte no vetor para grava��o na mem�ria FLASH

		envia_serial[29] = (byte)(contador_sai >> 24); //Escreve o valor do quarto byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial[30] = (byte)(contador_sai >> 16); //Escreve o valor do terceiro byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial[31] = (byte)(contador_sai >> 8); //Escreve o valor do segundo byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial[32] = (byte)(contador_sai); //Escreve o valor do primeiro byte no vetor para grava��o na mem�ria FLASH

		envia_serial[33] = (byte)(contador_bloqueios >> 24); //Escreve o valor do quarto byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial[34] = (byte)(contador_bloqueios >> 16); //Escreve o valor do terceiro byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial[35] = (byte)(contador_bloqueios >> 8); //Escreve o valor do segundo byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial[36] = (byte)(contador_bloqueios); //Escreve o valor do primeiro byte no vetor para grava��o na mem�ria FLASH

		envia_serial[37] = (byte)(contador_desbloqueios >> 24); //Escreve o valor do quarto byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial[38] = (byte)(contador_desbloqueios >> 16); //Escreve o valor do terceiro byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial[39] = (byte)(contador_desbloqueios >> 8); //Escreve o valor do segundo byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial[40] = (byte)(contador_desbloqueios); //Escreve o valor do primeiro byte no vetor para grava��o na mem�ria FLASH

		time_aux = GetData(); //A estrutura time_aux recebe as informa��es de data e hora atuais
		dataAtualizar = GetData(); //A estrutura dataAtualizar recebe os valores de data e hora atuais

		envia_serial[41] = dataAtualizar.Dia; //Envia o dia atual
		envia_serial[42] = dataAtualizar.Mes; //Envia o m�s atual

		ano = dataAtualizar.Ano; //Armazena na vari�vel ano o ano atual
		envia_serial[43] = (byte)(ano >> 8); //Envia o byte alto do ano
		envia_serial[44] = (byte)(ano); //Envia o byte baixo do ano

		envia_serial[45] = sinal_rele; //Envia o sinal do rel� - se pulso ou reten��o

		envia_serial[46] = sinal_trava; //Envia o sinal da trava - se pulso ou reten��o e controle somente ou reten��o e controle e teclado

		envia_serial[47] = pulso_rele; //Envia o pulso do rel� multiplicado por 10

		envia_serial[48] = pulso_trava; //Envia o pulso da trava multiplicado por 10

		envia_serial[49] = modo_travamento; //Envia o modo de travamento do controle - somente destrava ou trava/destrava

		envia_serial[50] = buffer_buzzer[BUZZER_VOLUME]; //Envia o volume do buzzer - 0 a 10, sendo 0 desligado

		envia_serial[51] = volume_mensagem_voz; //Envia o volume da mensagem de voz - 0 a 10, sendo 0 desligado

		envia_serial[52] = canal; //Envia o canal

		if(tipo_detector == Z3)
		{
			envia_serial[53] = 3;
		}
		else if(tipo_detector == Z8)
		{
			envia_serial[53] = 8;
		}

		envia_serial[54] = '!'; //Caracter de fim

		envia_serial[55] = '\n'; //Caracter de fim

		SERIAL_ETHERNET_SendBlock((byte*)&envia_serial,56,&Sent); //Envia os 56 byte de dados para o PC
	}

	else if(recebe_serial[1] == 'a' && recebe_serial[2] == 'p') //Sen�o se condi��o satisfeitas significa que o software do PC solicitou
	{
		//Armazena os valores recebidos nos par�metros correspondentes

		if(tipo_detector == Z3)
		{
			y = 6;
		}
		else if(tipo_detector == Z8)
		{
			y = 11;
		}

		for(x = 3;x < y;x++) //Armazena a sensibilidade da �rea 1 a �rea 8
		{
			if(buffer_sensibilidade[x - 2] != recebe_serial[x])
			{
				fnGravaAuditoria((90 + (x - 2)),buffer_sensibilidade[x - 2],recebe_serial[x],'G','S');
			}
			buffer_sensibilidade[x - 2] = recebe_serial[x];
		}

		Write_Buffer_FLASH[0] = buffer_sensibilidade[AREA_1]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o da sensibilidade
		Write_Buffer_FLASH[1] = buffer_sensibilidade[AREA_2]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o da sensibilidade
		Write_Buffer_FLASH[2] = buffer_sensibilidade[AREA_3]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o da sensibilidade
		Write_Buffer_FLASH[3] = buffer_sensibilidade[AREA_4]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o da sensibilidade
		Write_Buffer_FLASH[4] = buffer_sensibilidade[AREA_5]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o da sensibilidade
		Write_Buffer_FLASH[5] = buffer_sensibilidade[AREA_6]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o da sensibilidade
		Write_Buffer_FLASH[6] = buffer_sensibilidade[AREA_7]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o da sensibilidade
		Write_Buffer_FLASH[7] = buffer_sensibilidade[AREA_8]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o da sensibilidade
		ESCREVE_FLASH_INTERNA(endFLASHSensibilidadeArea1,8,0); //Escreve os valores de sensibilidade das �reas na mem�ria FLASH no endere�o especificado

		delay_ms(10); //Espera 10ms

		if(selecao_metais != recebe_serial[11])
		{
			fnGravaAuditoria(3,selecao_metais,recebe_serial[11],'G','S');
		}
		selecao_metais = recebe_serial[11]; //Armazena a sele��o de metais

		Write_Buffer_FLASH[0] = selecao_metais; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o da selecao de metais
		ESCREVE_FLASH_INTERNA(endFLASHSelecaoMetais,1,0); //Escreve o valor da selecao de metais na mem�ria FLASH no endere�o especificado

		delay_ms(10); //Espera 10ms

		if(filtroruido != recebe_serial[12])
		{
			fnGravaAuditoria(12,filtroruido,recebe_serial[12],'G','S');
		}

		filtroruido = recebe_serial[12]; //Armazena o valor do filtro de ruido

		Write_Buffer_FLASH[0] = filtroruido; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o do filtro de ruido
		ESCREVE_FLASH_INTERNA(endFLASHFiltroRuido,1,0); //Escreve o valor do filtro de ruido na mem�ria FLASH no endere�o especificado

		delay_ms(10); //Espera 10ms

		if(tipo_detector == Z3)
		{
			y = 16;
		}
		else if(tipo_detector == Z8)
		{
			y = 21;
		}

		for(x = 13;x < y;x++) //Armazena o anula_area da �rea 1 a �rea 8, se 0 n�o anula, se 1 anula
		{
			if(anula_area[x - 13] != recebe_serial[x])
			{
				fnGravaAuditoria((80 + (x - 12)),anula_area[x - 13],recebe_serial[x],'G','S');
			}
			buffer_sensibilidade[x - 2] = recebe_serial[x];

			anula_area[x - 13] = recebe_serial[x];
		}

		Write_Buffer_FLASH[0] = anula_area[AREA1]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o de anula_area
		Write_Buffer_FLASH[1] = anula_area[AREA2]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o de anula_area
		Write_Buffer_FLASH[2] = anula_area[AREA3]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o de anula_area
		Write_Buffer_FLASH[3] = anula_area[AREA4]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o de anula_area
		Write_Buffer_FLASH[4] = anula_area[AREA5]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o de anula_area
		Write_Buffer_FLASH[5] = anula_area[AREA6]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o de anula_area
		Write_Buffer_FLASH[6] = anula_area[AREA7]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o de anula_area
		Write_Buffer_FLASH[7] = anula_area[AREA8]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o de anula_area
		ESCREVE_FLASH_INTERNA(endFLASHAnulaArea1,8,0); //Escreve os valores de anula_area das �reas na mem�ria FLASH no endere�o especificado

		delay_ms(10); //Espera 10ms

		if(sinal_rele != recebe_serial[21])
		{
			fnGravaAuditoria(6,sinal_rele,recebe_serial[21],'G','S');
		}

		sinal_rele = recebe_serial[21]; //Armazena o sinal do rel� - se pulso ou reten��o

		Write_Buffer_FLASH[0] = sinal_rele; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o do sinal do rel�
		ESCREVE_FLASH_INTERNA(endFLASHSinalRele,1,0); //Escreve o valor do sinal do rel� na mem�ria FLASH no endere�o especificado

		delay_ms(10); //Espera 10ms

		if(sinal_trava != recebe_serial[22])
		{
			fnGravaAuditoria(4,sinal_trava,recebe_serial[22],'G','S');
		}

		sinal_trava = recebe_serial[22]; //Armazena o sinal da trava - se pulso ou reten��o e controle somente ou reten��o e controle e teclado

		Write_Buffer_FLASH[0] = sinal_trava; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o do sinal da trava
		ESCREVE_FLASH_INTERNA(endFLASHSinalTrava,1,0); //Escreve o valor do sinal da trava na mem�ria FLASH no endere�o especificado

		delay_ms(10); //Espera 10ms

		if(pulso_rele != recebe_serial[23])
		{
			fnGravaAuditoria(7,pulso_rele,recebe_serial[23],'G','S');
		}

		pulso_rele = recebe_serial[23]; //Armazena o pulso do rel� multiplicado por 10

		Write_Buffer_FLASH[0] = pulso_rele; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o do pulso do rel�
		ESCREVE_FLASH_INTERNA(endFLASHPulsoRele,1,0); //Escreve o valor do pulso do rel� na mem�ria FLASH no endere�o especificado

		delay_ms(10); //Espera 10ms

		if(pulso_trava != recebe_serial[24])
		{
			fnGravaAuditoria(5,pulso_trava,recebe_serial[24],'G','S');
		}

		pulso_trava = recebe_serial[24]; //Armazena o pulso da trava multiplicado por 10

		Write_Buffer_FLASH[0] = pulso_trava; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o do pulso do rel�
		ESCREVE_FLASH_INTERNA(endFLASHPulsoTrava,1,0); //Escreve o valor do pulso da trava na mem�ria FLASH no endere�o especificado

		delay_ms(10); //Espera 10ms

		if(modo_travamento != recebe_serial[25])
		{
			fnGravaAuditoria(1,modo_travamento,recebe_serial[25],'G','S');
		}

		modo_travamento = recebe_serial[25]; //Armazena o modo de travamento do controle - somente destrava ou trava/destrava

		Write_Buffer_FLASH[0] = modo_travamento; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o do modo de travamento
		ESCREVE_FLASH_INTERNA(endFLASHModoTravamento,1,0); //Escreve o valor do modo de travamento na mem�ria FLASH no endere�o especificado

		delay_ms(10); //Espera 10ms

		if(buffer_buzzer[BUZZER_VOLUME] != recebe_serial[26])
		{
			fnGravaAuditoria(24,buffer_buzzer[BUZZER_VOLUME],recebe_serial[26],'G','S');
		}

		buffer_buzzer[BUZZER_VOLUME] = recebe_serial[26]; //Armazena o volume do buzzer - 0 a 10, sendo 0 desligado

		Write_Buffer_FLASH[0] = buffer_buzzer[BUZZER_VOLUME]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o do volume do buzzer
		ESCREVE_FLASH_INTERNA(endFLASHBuzzerVolume,1,0); //Escreve o valor do volume do buzzer na mem�ria FLASH no endere�o especificado

		delay_ms(10); //Espera 10ms

		if(volume_mensagem_voz != recebe_serial[27])
		{
			fnGravaAuditoria(25,volume_mensagem_voz,recebe_serial[27],'G','S');
		}

		volume_mensagem_voz = recebe_serial[27]; //Armazena o volume da mensagem de voz - 0 a 10, sendo 0 desligado

		Write_Buffer_FLASH[0] = volume_mensagem_voz; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o do volume da mensagem de voz
		ESCREVE_FLASH_INTERNA(endFLASHMensagemVozVolume,1,0); //Escreve o valor do volume da mensagem de voz na mem�ria FLASH no endere�o especificado

		delay_ms(10); //Espera 10ms

		if(canal != recebe_serial[28])
		{
			fnGravaAuditoria(2,canal,recebe_serial[28],'G','S');
		}

		canal = recebe_serial[28]; //Armazena o canal

		Write_Buffer_FLASH[0] = canal; //Guarda no vetor Write_Buffer_FLASH para poder gravar na mem�ria FLASH a altera��o do canal
		ESCREVE_FLASH_INTERNA(endFLASHCanal,1,0); //Escreve o valor do canal na mem�ria FLASH no endere�o especificado

		delay_ms(10); //Espera 10ms
	}

	else if(recebe_serial[1] == 'r' && recebe_serial[2] == 'l') //Sen�o se condi��o satisfeitas significa que o software do PC solicitou - r  = requisi��o e l = log
	{
		if(num_bytes_l == 4096 && num_bloco_l == 4) //Se n�mero de bytes for igual a 4096 e n�mero do bloco for igual a 4 ent�o
		{
			num_bloco_l = 1;
			num_bytes_l = 0;
		}
		else if(num_bytes_l == 4096 && num_bloco_l < 4) //Sen�o se numero de bytes for igual a 4096 e n�mero do bloco for menor que 4
		{
			num_bloco_l++;
			num_bytes_l = 0;
		}

		end_bloco_l = END_INI_PARAMETROS + num_bytes_l + (num_bloco_l * 4096); //end_bloco_l = 0x83000 + 0 bytes + (1 * 4096) = 0x84000

		LE_FLASH_INTERNA(end_bloco_l,8); //L� os 8 bytes a partir do endere�o especificado

		//Armazena em cada posi��o do vetor envia_serial uma informa��o
		envia_serial[0] = '#'; //Caracter de inicio
		envia_serial[1] = Read_Buffer_FLASH[0]; //evento
		envia_serial[2] = Read_Buffer_FLASH[1]; //dispositivo
		envia_serial[3] = Read_Buffer_FLASH[2]; //hora
		envia_serial[4] = Read_Buffer_FLASH[3]; //minuto
		envia_serial[5] = Read_Buffer_FLASH[4]; //dia
		envia_serial[6] = Read_Buffer_FLASH[5]; //mes
		envia_serial[7] = Read_Buffer_FLASH[6]; //ano byte alto - quando receber fazer sua_variavel[7] << 8 + sua_variavel[8]
		envia_serial[8] = Read_Buffer_FLASH[7]; //ano byte baixo
		envia_serial[9] = '!'; //Caracter de fim
		envia_serial[10] = '\n'; //Caracter de fim

		SERIAL_ETHERNET_SendBlock((byte*)&envia_serial,11,&Sent); //Envia os dados seriais

		num_bytes_l = num_bytes_l + 8; //Incrementa o num_bytes 8 posi��es para ler o pr�ximo log
	}

	else if(recebe_serial[1] == 'r' && recebe_serial[2] == 'a') //Sen�o se condi��o satisfeitas significa que o software do PC solicitou - r  = requisi��o e a = auditoria
	{
		if(num_bytes_a == 4092 && num_bloco_a == 120) //Se n�mero de bytes for igual a 4092 e n�mero do bloco for igual a 120 ent�o
		{
			num_bloco_a = 5;
			num_bytes_a = 0;
		}
		else if(num_bytes_a == 4092 && num_bloco_a < 120) //Sen�o se n�mero de bytes for igual a 4096 e n�mero do bloco for igual a 124 ent�o
		{
			num_bloco_a++;
			num_bytes_a = 0;
		}

		end_bloco_a = END_INI_PARAMETROS + num_bytes_a + (num_bloco_a * 4096); //end_bloco = 0x83000 + 0 bytes + (5 * 4096) = 0x88000

		LE_FLASH_INTERNA(end_bloco_a,11); //L� os 11 bytes a partir do endere�o especificado

		//Armazena em cada posi��o do vetor envia_serial uma informa��o
		envia_serial[0] = '#'; //Caracter de inicio
		envia_serial[1] = Read_Buffer_FLASH[0]; //par�metro
		envia_serial[2] = Read_Buffer_FLASH[1]; //valor_velho
		envia_serial[3] = Read_Buffer_FLASH[2]; //valor_novo
		envia_serial[4] = Read_Buffer_FLASH[3]; //operador
		envia_serial[5] = Read_Buffer_FLASH[4]; //dispositivo
		envia_serial[6] = Read_Buffer_FLASH[5]; //hora
		envia_serial[7] = Read_Buffer_FLASH[6]; //minuto
		envia_serial[8] = Read_Buffer_FLASH[7]; //dia
		envia_serial[9] = Read_Buffer_FLASH[8]; //mes
		envia_serial[10] = Read_Buffer_FLASH[9]; //ano byte alto - quando receber fazer sua_variavel[7] << 8 + sua_variavel[8]
		envia_serial[11] = Read_Buffer_FLASH[10]; //ano byte baixo
		envia_serial[12] = '!'; //Caracter de fim
		envia_serial[13] = '\n'; //Caracter de fim

		SERIAL_ETHERNET_SendBlock((byte*)&envia_serial,14,&Sent); //Envia os dados seriais

		num_bytes_a = num_bytes_a + 11; //Incrementa o num_bytes 8 posi��es para ler o pr�ximo log
	}

	else if(recebe_serial[1] == 'n' && recebe_serial[2] == 'l') //Sen�o se condi��o satisfeitas significa que o software do PC solicitou - n  = n�mero e l = log
	{
		for(num_bloco_l = 1;num_bloco_l < 5;num_bloco_l++)
		{
			for(num_bytes_l = 0;num_bytes_l < 4096;num_bytes_l = num_bytes_l + 8)
			{
				end_bloco_l = END_INI_PARAMETROS + num_bytes_l + (num_bloco_l * 4096); //end_bloco_l = 0x83000 + 0 bytes + (1 * 4096) = 0x84000

				LE_FLASH_INTERNA(end_bloco_l,8); //L� os 8 bytes a partir do endere�o especificado

				if(Read_Buffer_FLASH[0] == 0xFF && Read_Buffer_FLASH[1] == 0xFF && Read_Buffer_FLASH[2] == 0xFF && Read_Buffer_FLASH[3] == 0xFF &&
					Read_Buffer_FLASH[4] == 0xFF && Read_Buffer_FLASH[5] == 0xFF && Read_Buffer_FLASH[6] == 0xFF && Read_Buffer_FLASH[7] == 0xFF) //Se todos os 8 bytes forem igual 0xFF ent�o
				{
					if(num_bytes_l > 0 && num_bytes_l < 4096)
					{
						aux_num_bytes = num_bytes_l;
						aux_num_bloco = (num_bloco_l - 1);
						num_bytes_l = 4096;
						num_bloco_l = 5;
					}
					else if(num_bytes_l == 0 && num_bloco_l > 0)
					{
						aux_num_bytes = num_bytes_l;
						aux_num_bloco = (num_bloco_l - 1);

						num_bytes_l = 4096;
						num_bloco_l = 5;
					}
					else if(num_bytes_l == 4104 && num_bloco_l > 0)
					{
						aux_num_bytes = 0;
						aux_num_bloco = (num_bloco_l - 1);

						num_bytes_l = 4096;
						num_bloco_a = 5;
					}
				}
			}
		}
		if(aux_num_bloco >= 1)
		{
			aux_numero_registros = (aux_num_bloco * 4096) + (aux_num_bytes);
		}
		else if(aux_num_bytes == 0 && aux_num_bloco == 1)
		{
			aux_numero_registros = 0;
		}
		else if(aux_num_bytes > 0 && aux_num_bloco == 0)
		{
			aux_numero_registros = aux_num_bytes;
		}
		else if(num_bytes_l == 4096 && num_bloco_l == 5)
		{
			aux_numero_registros = (num_bloco_l - 1) * 4096;
		}

		numero_registros = (word)(aux_numero_registros / 8);

		num_bytes_l = 0;
		num_bloco_l = 1;

		//Armazena em cada posi��o do vetor envia_serial uma informa��o
		envia_serial[0] = '#'; //Caracter de inicio
		envia_serial[1] = (byte)(numero_registros >> 8);
		envia_serial[2] = (byte)(numero_registros);
		envia_serial[3] = '!'; //Caracter de fim
		envia_serial[4] = '\n'; //Caracter de fim

		SERIAL_ETHERNET_SendBlock((byte*)&envia_serial,5,&Sent); //Envia os dados seriais
	}

	else if(recebe_serial[1] == 'n' && recebe_serial[2] == 'a') //Sen�o se condi��o satisfeitas significa que o software do PC solicitou - n  = n�mero e a = auditorias
	{
		for(num_bloco_a = 6;num_bloco_a < 44;num_bloco_a++)
		{
			for(num_bytes_a = 0;num_bytes_a < 4092;num_bytes_a = num_bytes_a + 11)
			{
				end_bloco_a = END_INI_PARAMETROS + num_bytes_a + (num_bloco_a * 4096); //end_bloco = 0x83000 + 0 bytes + (5 * 4096) = 0x84000

				LE_FLASH_INTERNA(end_bloco_a,11); //L� os 11 bytes a partir do endere�o especificado

				if(Read_Buffer_FLASH[0] == 0xFF && Read_Buffer_FLASH[1] == 0xFF && Read_Buffer_FLASH[2] == 0xFF && Read_Buffer_FLASH[3] == 0xFF &&
				   Read_Buffer_FLASH[4] == 0xFF && Read_Buffer_FLASH[5] == 0xFF && Read_Buffer_FLASH[6] == 0xFF && Read_Buffer_FLASH[7] == 0xFF &&
				   Read_Buffer_FLASH[8] == 0xFF && Read_Buffer_FLASH[9] == 0xFF && Read_Buffer_FLASH[10] == 0xFF) //Se todos os 11 bytes forem igual 0xFF ent�o
				{
					if(num_bytes_a > 0 && num_bytes_a < 4096)
					{
						aux_num_bytes = num_bytes_a;
						aux_num_bloco = (num_bloco_a - 6);
						num_bytes_a = 4092;
						num_bloco_a = 44;
					}
					else if(num_bytes_a == 0 && num_bloco_a > 0)
					{
						aux_num_bytes = num_bytes_a;
						aux_num_bloco = (num_bloco_a - 6);

						num_bytes_a = 4092;
						num_bloco_a = 44;
					}
					else if(num_bytes_a == 4103 && num_bloco_a > 0)
					{
						aux_num_bytes = 0;
						aux_num_bloco = (num_bloco_a - 6);

						num_bytes_a = 4092;
						num_bloco_a = 44;
					}
				}
			}
		}
		if(aux_num_bloco >= 1)
		{
			aux_numero_registros = (aux_num_bloco * 4092) + (aux_num_bytes);
		}
		else if(aux_num_bytes == 0 && aux_num_bloco == 1)
		{
			aux_numero_registros = 0;
		}
		else if(aux_num_bytes > 0 && aux_num_bloco == 0)
		{
			aux_numero_registros = aux_num_bytes;
		}
		else if(num_bytes_a == 4092 && num_bloco_a == 44)
		{
			aux_numero_registros = (num_bloco_a - 6) * 4092;
		}

		numero_registros = (word)(aux_numero_registros / 11);

		num_bytes_a = 0;
		num_bloco_a = 6;

		//Armazena em cada posi��o do vetor envia_serial uma informa��o
		envia_serial[0] = '#'; //Caracter de inicio
		envia_serial[1] = (byte)(numero_registros >> 8);
		envia_serial[2] = (byte)(numero_registros);
		envia_serial[3] = '!'; //Caracter de fim
		envia_serial[4] = '\n'; //Caracter de fim

		SERIAL_ETHERNET_SendBlock((byte*)&envia_serial,5,&Sent); //Envia os dados seriais
	}
	else if(recebe_serial[1] == 'e' && recebe_serial[2] == 'a') //Sen�o se condi��o satisfeitas significa que o software do PC solicitou - n  = n�mero e a = auditorias
	{
		envia_serial[0] = '#'; //Envia o caracter inicial do pacote de dados
		for(x = 1;x < 9;x++) //Envia a sensibilidade atual das 8 �reas
		{
			envia_serial[x] = buffer_sensibilidade[x];
		}
		envia_serial[9] = selecao_metais; //Envia a sele��o de metais atual
		envia_serial[10] = filtroruido; //Envia o valor do filtro de ruido atual
		envia_serial[11] = var_tensao_cinco; //Envia a tens�o de cinco volts multiplicada por 10
		envia_serial[12] = var_tensao_quinze; //Envia a tens�o de quinze volts multiplicada por 10
		envia_serial[13] = var_tensao_menos_quinze; //Envia a tens�o de menos quinze volts multiplicada por 10
		envia_serial[14] = var_tensao_rede; //Envia a tens�o da rede que vai de 108 a 253 VAC
		envia_serial[15] = (byte)(var_tensao_bateria >> 8); //Envia o primeiro byte alto da tens�o da bateria
		envia_serial[16] = (byte)(var_tensao_bateria); //Envia o segundo byte baixo da tens�o da bateria
		for(x = 17;x < 25;x++) //Envia o anula_area de cada �rea se zero n�o anula e se 1 anula
		{
			envia_serial[x] = anula_area[x-17];
		}
		envia_serial[25] = (byte)(contador_entra >> 24); //Escreve o valor do quarto byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial[26] = (byte)(contador_entra >> 16); //Escreve o valor do terceiro byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial[27] = (byte)(contador_entra >> 8); //Escreve o valor do segundo byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial[28] = (byte)(contador_entra); //Escreve o valor do primeiro byte no vetor para grava��o na mem�ria FLASH

		envia_serial[29] = (byte)(contador_sai >> 24); //Escreve o valor do quarto byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial[30] = (byte)(contador_sai >> 16); //Escreve o valor do terceiro byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial[31] = (byte)(contador_sai >> 8); //Escreve o valor do segundo byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial[32] = (byte)(contador_sai); //Escreve o valor do primeiro byte no vetor para grava��o na mem�ria FLASH

		envia_serial[33] = (byte)(contador_bloqueios >> 24); //Escreve o valor do quarto byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial[34] = (byte)(contador_bloqueios >> 16); //Escreve o valor do terceiro byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial[35] = (byte)(contador_bloqueios >> 8); //Escreve o valor do segundo byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial[36] = (byte)(contador_bloqueios); //Escreve o valor do primeiro byte no vetor para grava��o na mem�ria FLASH

		envia_serial[37] = (byte)(contador_bloqueios >> 24); //Escreve o valor do quarto byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial[38] = (byte)(contador_bloqueios >> 16); //Escreve o valor do terceiro byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial[39] = (byte)(contador_bloqueios >> 8); //Escreve o valor do segundo byte mais alto no vetor para grava��o na mem�ria FLASH
		envia_serial[40] = (byte)(contador_bloqueios); //Escreve o valor do primeiro byte no vetor para grava��o na mem�ria FLASH

		time_aux = GetData(); //A estrutura time_aux recebe as informa��es de data e hora atuais
		dataAtualizar = GetData(); //A estrutura dataAtualizar recebe os valores de data e hora atuais

		envia_serial[41] = dataAtualizar.Dia; //Envia o dia atual
		envia_serial[42] = dataAtualizar.Mes; //Envia o m�s atual

		ano = dataAtualizar.Ano; //Armazena na vari�vel ano o ano atula
		envia_serial[43] = (byte)(ano >> 8); //Envia o byte alto do ano
		envia_serial[44] = (byte)(ano); //Envia o byte baixo do ano

		envia_serial[45] = sinal_rele; //Envia o sinal do rel�

		envia_serial[46] = sinal_trava; //Envia o sinal da trava

		envia_serial[47] = pulso_rele; //Envia o pulso do rel� multiplicado por 10

		envia_serial[48] = pulso_trava; //Envia o pulso da trava multiplicado por 10

		envia_serial[49] = modo_travamento; //Envia o modo_travamento

		envia_serial[50] = buffer_buzzer[BUZZER_VOLUME]; //Envia o volume do buzzer

		envia_serial[51] = volume_mensagem_voz; //Envia o volume da mensagem de voz

		envia_serial[52] = canal; //Envia o canal

		LE_FLASH_INTERNA(ultimo_endereco_eventos,8);

		envia_serial[53] = Read_Buffer_FLASH[0]; //Armazena o evento, se foi BLOQUEIO (B) ou DESBLOQUEIO (D)

		envia_serial[54] = Read_Buffer_FLASH[1]; //Armazena o dispositivo que causou o travamento ou destravamento, se foi PAINEL (P), CONTROLE (C) ou DETECTOR(D)

		envia_serial[55] = Read_Buffer_FLASH[2]; //Armazena a hora do evento

		envia_serial[56] = Read_Buffer_FLASH[3]; //Armazena o minuto do evento

		envia_serial[57] = Read_Buffer_FLASH[4]; //Armazena o dia do evento

		LE_FLASH_INTERNA(ultimo_endereco_auditoria,11);

		envia_serial[58] = Read_Buffer_FLASH[3]; //Armazena quem que mexeu nas configura��es, se gerente(G) ou t�cnico(T)

		envia_serial[59] = Read_Buffer_FLASH[5]; //Armazena a hora da auditoria

		envia_serial[60] = Read_Buffer_FLASH[6]; //Armazena o minuto da auditoria

		envia_serial[61] = Read_Buffer_FLASH[7]; //Armazena o dia da auditoria

		envia_serial[62] = '!'; //Envia o caracter final do pacote de dados

		envia_serial[63] = '\n'; //Envia o caracter de im

		SERIAL_ETHERNET_SendBlock((byte*)&envia_serial,64,&Sent); //Envia para o m�dulo ethernet os 54 bytes de dados
	}
	estado_MODULO_ETHERNET = ESTADO_ESPERA; //Estado a ser executado � ESTADO_ESPERA
	memset(recebe_serial,0,sizeof(recebe_serial));
}


/*** Fun��es da ETHERNET-SERIAL ***/


void AtualizaSensibilidadeGravaAuditoria(volatile char sensibilidadeAnterior[], char sensibilidadeAtual[], char operador, char dispositivo){
	for(int x = 0;x < 8;x++) //Armazena a sensibilidade da �rea 1 a �rea 8
	{
		if(buffer_sensibilidade[x + 1] != sensibilidadeAtual[x])
		{
			fnGravaAuditoria((91 + x),buffer_sensibilidade[x + 1],sensibilidadeAtual[x],operador,dispositivo);
		}
		buffer_sensibilidade[x + 1] = sensibilidadeAtual[x];
	}
}

void AtualizaAnulaAreaGravaAuditoria(volatile char AnulaAreaAnterior[], char AnulaAreaAtual[], char operador, char dispositivo){
	for(int x = 0;x < 8;x++) //Armazena o anula_area da �rea 1 a �rea 8, se 0 n�o anula, se 1 anula
	{
		if(anula_area[x] != AnulaAreaAtual[x])
		{
			fnGravaAuditoria((81 + x),anula_area[x],AnulaAreaAtual[x],operador,dispositivo);
		}
		anula_area[x] = AnulaAreaAtual[x];
	}
}

/*
 * Fun��o para gravar todos os valores atuais na memoria flash
 *
 */
void EscreveBufferFlashInterna() //Fun��o que escreve os dados na mem�ria FLASH
{
	for(x = 0;x < 6;x++) //Armazena o valor das 6 posi��es do buffer_senhas no vetor de grava��o da mem�ria FLASH para a senha da ger�ncia
	{
		Write_Buffer_FLASH[OFFSET_SENHA_DA_GERENCIA + x] = buffer_senhas[x];
	}

	for(x = 0;x < 6;x++) //Armazena o valor das 6 posi��es do buffer_senhas no vetor de grava��o da mem�ria FLASH para a senha do t�cnico
	{
		Write_Buffer_FLASH[OFFSET_SENHA_DO_TECNICO + x] = buffer_senhas[x + 6];
	}
	for(x = 0;x < 6;x++) //Armazena o valor das 6 posi��es do buffer_senhas no vetor de grava��o da mem�ria FLASH para a senha da engenharia
	{
		Write_Buffer_FLASH[OFFSET_SENHA_DA_ENGENHARIA + x] = buffer_senhas[x + 12];
	}

	//SENSIBILIDADE
	for(x = 0;x < 8;x++) //Armazena o valor das 8 posi��es do buffer_sensibilidade no vetor de grava��o da mem�ria FLASH para as sensibilidades das �reas
	{
		Write_Buffer_FLASH[OFFSET_SENSIBILIDADE + x] = buffer_sensibilidade[x + 1];
	}

	//MODO DE TRAVAMENTO
	Write_Buffer_FLASH[OFFSET_MODO_TRAVAMENTO] = modo_travamento; //Armazena o valor do modo_travamento no vetor de grava��o da mem�ria FLASH para o modo de travamento

	//CANAL
	Write_Buffer_FLASH[OFFSET_CANAL] = canal; //Armazena o valor do canal no vetor de grava��o da mem�ria FLASH para o canal

	//SELE��O DE METAIS
	Write_Buffer_FLASH[OFFSET_SELECAO_METAIS] = selecao_metais; //Armazena o valor de selecao_metais no vetor de grava��o da mem�ria FLASH para a sele��o de metais

	//TRAVA
	Write_Buffer_FLASH[OFFSET_PULSO_TRAVA] = pulso_trava; //Armazena o valor de pulso_trava no vetor de grava��o da mem�ria FLASH para o pulso_trava
	Write_Buffer_FLASH[OFFSET_SINAL_TRAVA] = sinal_trava; //Armazena o valor do sinal_trava no vetor de grava��o da mem�ria FLASH para o sinal_trava

	//RELE
	Write_Buffer_FLASH[OFFSET_PULSO_RELE] = pulso_rele; //Armazena o valor de pulso_rele no vetor de grava��o da mem�ria FLASH para o pulso_rele
	Write_Buffer_FLASH[OFFSET_SINAL_RELE] = sinal_rele; //Armazena o valor de sinal_rele no vetor de grava��o da mem�ria FLASH para o sinal_rele

	//N�MERO DE CONTROLES
	Write_Buffer_FLASH[OFFSET_NUMERO_CONTROLES] = numero_controles; //Armazena o numero no vetor de grava��o da mem�ria FLASH para a trava_inteligente

	//SENSIBILIDADE IR
	Write_Buffer_FLASH[OFFSET_SENSIBILIDADEIR] = sensibilidadeir; //Armazena o valor de sensibilidadeir no vetor de grava��o da mem�ria FLASH para a sensibilidadeir

	//AN�LISE IR
	Write_Buffer_FLASH[OFFSET_ANALISEIR] = analiseir; //Armazena o valor de analiseir no vetor de grava��o da mem�ria FLASH para a analiseir

	//F�BRICA
	Write_Buffer_FLASH[OFFSET_FABRICA] = fabrica; //Armazena o valor de fabrica no vetor de grava��o da mem�ria FLASH para a fabrica

	//IDIOMA
	Write_Buffer_FLASH[OFFSET_IDIOMA] = idioma; //Armazena o valor de idioma no vetor de grava��o da mem�ria FLASH para o idioma

	//BUZZER
	Write_Buffer_FLASH[OFFSET_BUZZER_TOM]	  = buffer_buzzer[BUZZER_TOM]; //Armazena o valor do tom no vetor de grava��o da mem�ria FLASH para o tom
	Write_Buffer_FLASH[OFFSET_BUZZER_VOLUME]  = buffer_buzzer[BUZZER_VOLUME]; //Armazena o valor do volume no vetor de grava��o da mem�ria FLASH para o volume
	Write_Buffer_FLASH[OFFSET_BUZZER_LIG_DES] = buffer_buzzer[BUZZER_LIGA_DESLIGA]; //Armazena o valor de ligado ou desligado no vetor de grava��o da mem�ria FLASH para o estado ligado ou desligado

	//MENSAGEM DE VOZ
	Write_Buffer_FLASH[OFFSET_MSG_VOZ_VOLUME] = volume_mensagem_voz; //Armazena o valor do volume da mensagem de voz no vetor de grava��o da mem�ria FLASH para o volume da mensagem de voz
	Write_Buffer_FLASH[OFFSET_MSG_VOZ_LIG_DES] = lig_des_mensagem_voz; //Armazena o valor de lig_des_mensagem_voz no vetor de grava��o da mem�ria FLASH para o lig_des_mensagem_voz

	//ALARME VISUAL
	Write_Buffer_FLASH[OFFSET_ALARME_VISUAL_LIG_DES] = alarme_visual; //Armazena o valor do alarme_visual no vetor de grava��o da mem�ria FLASH para o alarme_visual

	//CONTADOR DE BLOQUEIOS
	Write_Buffer_FLASH[OFFSET_TOTAL_BLOQUEIOS]     = (byte)(contador_bloqueios >> 24); //Escreve o valor do quarto byte mais alto no vetor para grava��o na mem�ria FLASH
	Write_Buffer_FLASH[OFFSET_TOTAL_BLOQUEIOS + 1] = (byte)(contador_bloqueios >> 16); //Escreve o valor do terceiro byte mais alto no vetor para grava��o na mem�ria FLASH
	Write_Buffer_FLASH[OFFSET_TOTAL_BLOQUEIOS + 2] = (byte)(contador_bloqueios >> 8); //Escreve o valor do segundo byte mais alto no vetor para grava��o na mem�ria FLASH
	Write_Buffer_FLASH[OFFSET_TOTAL_BLOQUEIOS + 3] = (byte)(contador_bloqueios); //Escreve o valor do primeiro byte no vetor para grava��o na mem�ria FLASH

	//CONTADOR DE DESBLOQUEIOS
	Write_Buffer_FLASH[OFFSET_TOTAL_DESBLOQUEIOS]   = (byte)(contador_desbloqueios >> 24); //Escreve o valor do quarto byte mais alto no vetor para grava��o na mem�ria FLASH
	Write_Buffer_FLASH[OFFSET_TOTAL_DESBLOQUEIOS + 1] = (byte)(contador_desbloqueios >> 16); //Escreve o valor do terceiro byte mais alto no vetor para grava��o na mem�ria FLASH
	Write_Buffer_FLASH[OFFSET_TOTAL_DESBLOQUEIOS + 2] = (byte)(contador_desbloqueios >> 8); //Escreve o valor do segundo byte mais alto no vetor para grava��o na mem�ria FLASH
	Write_Buffer_FLASH[OFFSET_TOTAL_DESBLOQUEIOS + 3] = (byte)(contador_desbloqueios); //Escreve o valor do primeiro byte no vetor para grava��o na mem�ria FLASH

	//CONTADOR DE PASSAGENS - ENTRADAS
	Write_Buffer_FLASH[OFFSET_CONTADOR_ENTRADAS]   = (byte)(contador_entra >> 24); //Escreve o valor do quarto byte mais alto no vetor para grava��o na mem�ria FLASH
	Write_Buffer_FLASH[OFFSET_CONTADOR_ENTRADAS + 1] = (byte)(contador_entra >> 16); //Escreve o valor do terceiro byte mais alto no vetor para grava��o na mem�ria FLASH
	Write_Buffer_FLASH[OFFSET_CONTADOR_ENTRADAS + 2] = (byte)(contador_entra >> 8); //Escreve o valor do segundo byte mais alto no vetor para grava��o na mem�ria FLASH
	Write_Buffer_FLASH[OFFSET_CONTADOR_ENTRADAS + 3] = (byte)(contador_entra); //Escreve o valor do primeiro byte no vetor para grava��o na mem�ria FLASH

	//CONTADOR DE PASSAGENS - SAIDAS
	Write_Buffer_FLASH[OFFSET_CONTADOR_SAIDAS] 	= (byte)(contador_sai >> 24); //Escreve o valor do quarto byte mais alto no vetor para grava��o na mem�ria FLASH
	Write_Buffer_FLASH[OFFSET_CONTADOR_SAIDAS + 1] = (byte)(contador_sai >> 16); //Escreve o valor do terceiro byte mais alto no vetor para grava��o na mem�ria FLASH
	Write_Buffer_FLASH[OFFSET_CONTADOR_SAIDAS + 2] = (byte)(contador_sai >> 8); //Escreve o valor do segundo byte mais alto no vetor para grava��o na mem�ria FLASH
	Write_Buffer_FLASH[OFFSET_CONTADOR_SAIDAS + 3] = (byte)(contador_sai); //Escreve o valor do primeiro byte no vetor para grava��o na mem�ria FLASH

	//CONTADOR DE PASSAGENS - ENTRADAS DIARIAS
	Write_Buffer_FLASH[OFFSET_CONTADOR_ENTRADAS_D]   = (byte)(contador_dia_entra >> 24); //Escreve o valor do quarto byte mais alto no vetor para grava��o na mem�ria FLASH
	Write_Buffer_FLASH[OFFSET_CONTADOR_ENTRADAS_D + 1] = (byte)(contador_dia_entra >> 16); //Escreve o valor do terceiro byte mais alto no vetor para grava��o na mem�ria FLASH
	Write_Buffer_FLASH[OFFSET_CONTADOR_ENTRADAS_D + 2] = (byte)(contador_dia_entra >> 8); //Escreve o valor do segundo byte mais alto no vetor para grava��o na mem�ria FLASH
	Write_Buffer_FLASH[OFFSET_CONTADOR_ENTRADAS_D + 3] = (byte)(contador_dia_entra); //Escreve o valor do primeiro byte no vetor para grava��o na mem�ria FLASH

	//CONTADOR DE PASSAGENS - SAIDAS DIARIAS
	Write_Buffer_FLASH[OFFSET_CONTADOR_SAIDAS_D] 	= (byte)(contador_dia_sai >> 24); //Escreve o valor do quarto byte mais alto no vetor para grava��o na mem�ria FLASH
	Write_Buffer_FLASH[OFFSET_CONTADOR_SAIDAS_D + 1] = (byte)(contador_dia_sai >> 16); //Escreve o valor do terceiro byte mais alto no vetor para grava��o na mem�ria FLASH
	Write_Buffer_FLASH[OFFSET_CONTADOR_SAIDAS_D + 2] = (byte)(contador_dia_sai >> 8); //Escreve o valor do segundo byte mais alto no vetor para grava��o na mem�ria FLASH
	Write_Buffer_FLASH[OFFSET_CONTADOR_SAIDAS_D + 3] = (byte)(contador_dia_sai); //Escreve o valor do primeiro byte no vetor para grava��o na mem�ria FLASH

	//CONFERENCIA DO DIA
	Write_Buffer_FLASH[OFFSET_CONFERENCIA_DO_DIA] = conferencia_do_dia;

	//PERFIL
	Write_Buffer_FLASH[OFFSET_PERFIL] = perfil; //Armazena o valor de perfil no vetor de grava��o da mem�ria FLASH para o perfil

	//AJUSTES TX-RX
	Write_Buffer_FLASH[OFFSET_AJUSTES_TX_RX_CICLO_TRABALHO] = ciclo_de_trabalho; //Escreve o valor do ciclo de trabalho no vetor para grava��o na mem�ria FLASH
	Write_Buffer_FLASH[OFFSET_AJUSTES_TX_RX_DEFASAGEM] = (byte)(defasagem >> 8); //Escreve o byte alto da defasagem no vetor para grava��o na mem�ria FLASH
	Write_Buffer_FLASH[OFFSET_AJUSTES_TX_RX_DEFASAGEM + 1] = (byte)(defasagem); //Escreve o byte baixo da defasagem no vetor para grava��o na mem�ria FLASH
	Write_Buffer_FLASH[OFFSET_AJUSTES_TX_RX_FREQUENCIA] = (byte)(frequencia >> 8); //Escreve o byte alto da frequencia no vetor para grava��o na mem�ria FLASH
	Write_Buffer_FLASH[OFFSET_AJUSTES_TX_RX_FREQUENCIA + 1] = (byte)(frequencia); //Escreve o byte baixo da frequencia no vetor para grava��o na mem�ria FLASH

	//MODELO DE ANTENA
	Write_Buffer_FLASH[OFFSET_MODELO_ANTENA] = modelo_antena; //Armazena o valor de modelo_antena no vetor de grava��o da mem�ria FLASH para o modelo_antena

	//POTENCI�METROS DE GANHO
	for(x = 0;x < 8;x++) //Armazena o valor das 8 posi��es do buffer_ganho no vetor de grava��o da mem�ria FLASH para o ganho dos potenci�metros digitais
	{
		Write_Buffer_FLASH[OFFSET_POTENCIOMETRO_GANHO + x] = buffer_ganho[x + 1];
	}

	//POTENCI�METROS DE SELE��O
	for(x = 0;x < 8;x++) //Armazena o valor das 8 posi��es do buffer_selecao no vetor de grava��o da mem�ria FLASH para a sele��o de metais dos potenci�metros digitais
	{
		Write_Buffer_FLASH[OFFSET_POTENCIOMETRO_SELECAO + x] = buffer_selecao[x + 1];
	}

	//ANULA �REAS
	for(x = 0;x < 8;x++) //Armazena o valor das 8 posi��es de anula_area no vetor de grava��o da mem�ria FLASH para o vetor anula_area
	{
		Write_Buffer_FLASH[OFFSET_ANULA_AREA1 + x] = anula_area[x];
	}

	//FILTRO RUIDO
	Write_Buffer_FLASH[OFFSET_FILTRO_RUIDO] = filtroruido; //Armazena o valor de filtroruido no vetor de grava��o da mem�ria FLASH para o filtroruido

	//TRAVA INTELIGENTE
	Write_Buffer_FLASH[OFFSET_TRAVA_INTELIGENTE] = trava_inteligente; //Armazena o valor da trava_inteligente no vetor de grava��o da mem�ria FLASH para a trava_inteligente


	//TIPO DE DETECTOR
	Write_Buffer_FLASH[OFFSET_TIPO_DETECTOR] = tipo_detector; //Armazena o numero no vetor de grava��o da mem�ria FLASH para o tipo de detector

	//PONTEIROS DE LOG DE AUDITORIAS
	Write_Buffer_FLASH[OFFSET_PONTEIRO_BLOCO_A] = posicao_bloco_a;
	Write_Buffer_FLASH[OFFSET_PONTEIRO_BYTES_A] = (byte)(posicao_byte_a >> 8);
	Write_Buffer_FLASH[OFFSET_PONTEIRO_BYTES_A + 1] = (byte)(posicao_byte_a);

	//PONTEIROS DE LOG DE EVENTOS
	Write_Buffer_FLASH[OFFSET_PONTEIRO_BLOCO_L] = posicao_bloco_l;
	Write_Buffer_FLASH[OFFSET_PONTEIRO_BYTES_L] = (byte)(posicao_byte_l >> 8);
	Write_Buffer_FLASH[OFFSET_PONTEIRO_BYTES_L + 1] = (byte)(posicao_byte_l);

	//ELIMINAR FALHA DA BOBINA
	Write_Buffer_FLASH[OFFSET_FALHA_DA_BOBINA] = eliminar_falha;

	//IP
	for(x = 0;x < 15;x++)
	{
		Write_Buffer_FLASH[OFFSET_ENDERECO_IP + x] = end_IP[x];
	}

	//MASCARA DE SUB-REDE
	for(x = 0;x < 15;x++)
	{
		Write_Buffer_FLASH[OFFSET_ENDERECO_SUB_REDE + x] = end_SUB_MASK[x];
	}

	//GATEWAY
	for(x = 0;x < 15;x++)
	{
		Write_Buffer_FLASH[OFFSET_ENDERECO_GATEWAY + x] = end_GATEWAY[x];
	}

	//DNS
	for(x = 0;x < 15;x++)
	{
		Write_Buffer_FLASH[OFFSET_ENDERECO_DNS + x] = end_DNS[x];
	}

	Write_Buffer_FLASH[OFFSET_INDICE_EVENTOS_GRAVADOS] = (byte)(indice_eventos_gravados >> 8);
	Write_Buffer_FLASH[OFFSET_INDICE_EVENTOS_GRAVADOS + 1] = (byte)(indice_eventos_gravados);

	Write_Buffer_FLASH[OFFSET_INDICE_AUDITORIAS_GRAVADOS] = (byte)(indice_auditorias_gravados >> 8);
	Write_Buffer_FLASH[OFFSET_INDICE_AUDITORIAS_GRAVADOS + 1] = (byte)(indice_auditorias_gravados);

	Write_Buffer_FLASH[OFFSET_PORTA_AUTOMATICA] = porta_automatica;

	Write_Buffer_FLASH[OFFSET_OPCAO_SENSOR_CONTADOR] = opcaosensorcontador;

	ESCREVE_FLASH_INTERNA(endFLASHInicial,176,0); //Escreve no endere�o especificado os 176 bytes de informa��es colocadas no vetor de grava��o da mem�ria FLASH


	/*
	static volatile word x1 = 0; //Define a vari�vel x para zero
	static volatile dword aux_endereco; //Define a vari�vel aux_endereco para auxiliar no c�lculo do endere�o
	static volatile dword address; //Define a vari�vel address para especificar o endere�o e o bloco que ser� gravado
//	char readBufferFlash_temp[4100];


	Cpu_DisableInt(); //Desabilita as interrup��es

	address = END_INI_PARAMETROS + (block_number * 0x1000); //Armazena address com o valor (0x43000 + (0 * 0x1000)) = 0x43000

	for(x1 = 0;x1 < 4096;x1++) //L� os 4096 bytes do bloco para salvar na RAM pois o m�todo de escrita � destructive write with erase
	{
		FLASH_INTERNA_GetByteFlash(address + x1, &Read_Buffer_FLASH[x1]);
	}

	aux_endereco = endereco - address; //Armazena na vari�vel aux_endereco o valor (endereco - address) que � o endere�o passado na fun��o - 0x8300. Exemplo 0x83012 - 0x83000 = 0x12 = 18 em decimal

	strncpy(&Read_Buffer_FLASH[aux_endereco],bufferToWrite, numero_dados);

	FLASH_INTERNA_SetBlockFlash(&Read_Buffer_FLASH[0],address,4096); //Grava os 4096 bytes no bloco de mem�ria especificado na mem�ria FLASH

	Cpu_EnableInt(); //Habilita as interrup��es
	*/
}

// Exemplo de recebimento
//"{\"code\":200,\"config\":0,\"data\":\"\"}", '\0'

void TrataSerial2(void) //Fun��o que recebe os dados via comunica��o remota e toma as devidas a��es
{
	static word numero_do_bloco = 0;

	char configType = '0';
	char softwareEditId = 'N';

	char receivedTokenTemp[16];
	memset(receivedTokenTemp,0,sizeof(receivedTokenTemp));

	static char connect_tryout = 0;

	struct AES_ctx ctx;
	uint8_t trataSerial2Key[16] =  "\0";
	char *recebeSerialCriptografado;
	int tamanhoCriptografado;

	char recebe_serial_decriptografado[400] =  "\0";
	byte sensibilidade_temp[9];

	unsigned char recebe_serial_temp[400];
	word tamanho_recebido_serial;

	char parametrosGravar[255];
	ParametrosAgata parametrosFromSerial;
	char reading_pointer[400];
	memset(reading_pointer, 0, sizeof(reading_pointer));


	//Gera a chave para decriptografar - a partir do numero de serie
	agataKeyGenerator(numero_serie, sizeof(numero_serie),trataSerial2Key,sizeof(trataSerial2Key));

	if(RECEBIMENTO_ETHERNET_EM_TRATASERIAL2){	//Caso deseja-se receber os dados do modulo no trataserial2
		SERIAL_ETHERNET_RecvBlock(recebe_serial, sizeof(recebe_serial), &tamanho_recebido_serial);
	}

	//Limpa e retira o cabecalho http
	memset(reading_pointer, 0, sizeof(reading_pointer));
	strcpy(reading_pointer,strstr(recebe_serial,STRING_OK_HTTP));

	if(reading_pointer==NULL) {						// N�o recebeu mensagem v�lida (code!=200)
		memset(recebe_serial,0,sizeof(recebe_serial));
		estado_MODULO_ETHERNET = ESTADO_ESPERA;
		erro_comunicacao = ERRO_SVD;
		return;
		//Se nao receber mensagem valida, interrompe a leitura, nao confirma o envio
		//  e repete as ultima mensagem (eventos e autidoria) quando passar o tempo especificado
	}

	// Limpa o reading pointer, busca o "config" para que saiba se o configtype e
	//		1: altera os valores atuais do detector e confirma
	//		0: apenas confirma
	memset(reading_pointer, 0, sizeof(reading_pointer));
	strcpy(reading_pointer,strstr(recebe_serial,STRING_CONFIG_HTTP));
	configType = reading_pointer[strlen(STRING_CONFIG_HTTP)];
	erro_comunicacao = ERRO_OK;


	if(FORCAR_NAO_CONFIRMAR_RECEBIMENTO_SIMTRO){	//Para teste, confirmar independente do config
		configType = '0';
	}

	//Define a rotina dependendo do config da mensagem do Asset Care
	switch (configType){
	case '1':

		//Nota: A mensagem da Simtro vem descriptografada, com excecao da parte de data
		//	referente aos dados a serem utilizados para configurar o detector de metal
		if(MODO_CRIPTOGRAFIA_ECB_SIMTRO){

			//Limpa e remove os caracteres invalidos da mensagem recebida
			memset(recebe_serial_temp,0,sizeof(recebe_serial_temp));
			strcpy(recebe_serial_temp,(strstr(recebe_serial,STRING_DATA_START_HTTP)));
			recebe_serial_temp[strlen(recebe_serial_temp)-1] = 0;
			strcpy(recebe_serial_temp,&recebe_serial_temp[strlen(STRING_DATA_START_HTTP)]);
			memset(strstr(recebe_serial_temp,"\""), 0, strlen(STRING_DATA_START_HTTP)+1);	//Seta ultimo caractere do campo data como nulo para indicar o fim
			removeChar(recebe_serial_temp,'\\');			//Remove caracteres invalidos da base64 - no caso simtro esta enviando \

			//Decodifica de base64 para mensagem criptografada AES
			base64_decode_aux(recebe_serial_temp, strlen(recebe_serial_temp), &tamanhoCriptografado, recebe_serial_decriptografado, sizeof(recebe_serial_decriptografado));
			for(int k=0;k<tamanhoCriptografado;k++){
				recebe_serial_temp[k]=recebe_serial_decriptografado[k];
			}

			//Executa a decriptografia, bloco por bloco (16 caracteres)
			AES_init_ctx(&ctx, trataSerial2Key); //Inicializa o vetor para descriptografar
			for(int i = 0; i<tamanhoCriptografado;i = i+16){
				AES_ECB_decrypt(&ctx, &recebe_serial_temp[i]);
			}

			//Limpa e atribui para o array recebe_serial a ser usado
			memset(recebe_serial_decriptografado,0,sizeof(recebe_serial_decriptografado));
			memset(recebe_serial,0, sizeof(recebe_serial));
			strcpy(recebe_serial,recebe_serial_temp);
			memset(recebe_serial_temp,0, sizeof(recebe_serial_temp));
		}

		//Limpeza do buffer e copia do recebido da serial para o buffer de leitura
		memset(reading_pointer, 0, sizeof(reading_pointer));
		strcpy(reading_pointer,(strstr(recebe_serial,STRING_DATA_ALTERACAO_HTTP)+strlen(STRING_DATA_ALTERACAO_HTTP)));

		//Busca se tem o caractere final, se nao houver a mensagem esta quebrada e deve ignorar
		if(strstr(reading_pointer,"]")==NULL){
			memset(recebe_serial,0,sizeof(recebe_serial));
			estado_MODULO_ETHERNET = ESTADO_ESPERA;
			return;
		}
		memset(strstr(reading_pointer,"]"), 0, 1);

		//*** Atribuicao dos valores do JSON para a struct
		//Seta os valores atuais para a struct, para comparar se sao valores diferentes
		for (int i=0; i<=7; i++){
			parametrosFromSerial.sensibilidade[i] = buffer_sensibilidade[i + 1];
		}
		for (int j=0; j<=7; j++){
			parametrosFromSerial.anulaAreas[j] = anula_area[j];
		}
		parametrosFromSerial.canal = canal;
		parametrosFromSerial.filtroRuido = filtroruido;
		parametrosFromSerial.sinalRele = sinal_rele;
		parametrosFromSerial.pulsoRele = pulso_rele; //Armazena o pulso do rel� multiplicado por 10
		parametrosFromSerial.sinalTrava = sinal_trava; //Armazena o sinal da trava - se pulso ou reten��o e controle somente ou reten��o e controle e teclado
		parametrosFromSerial.pulsoTrava = pulso_trava; //Armazena o pulso da trava multiplicado por 10
		parametrosFromSerial.modoTravamento = modo_travamento;
		parametrosFromSerial.selecaoMetais = selecao_metais;
		parametrosFromSerial.volumeVoz = volume_mensagem_voz; //Armazena o volume da mensagem de voz - 0 a 10, sendo 0 desligado
		parametrosFromSerial.volumeBuzzer = buffer_buzzer[BUZZER_VOLUME]; //Armazena o volume do buzzer - 0 a 10, sendo 0 desligado
		parametrosFromSerial.tomBuzzer = buffer_buzzer[BUZZER_TOM]; //Armazena o volume do buzzer - 0 a 10, sendo 0 desligado

		//Executa a seguinte rotina para cada dado:
		//	1o - Checa se e um valor valido (invalido e ignorado)
		// 	2o - Grava os valores na struct
		//	3o - Checa se o valor gravado e igual ao anterior
		//		3a - Se for igual, ignora - nao salva auditoria
		//		3b - Se for diferente, salva a auditoria
		strncpy(receivedTokenTemp,strtok(reading_pointer,STRING_DATA_SEPARATOR_HTTP),sizeof(receivedTokenTemp));
		if(agataIsValidNumber(receivedTokenTemp, DadoSnZona1)){
			parametrosFromSerial.sensibilidade[0]= (char) atoi(receivedTokenTemp);
		}
		memset(receivedTokenTemp,0, sizeof(receivedTokenTemp));

		for (int i=1; i<=7; i++){
			strncpy(receivedTokenTemp,strtok(NULL,STRING_DATA_SEPARATOR_HTTP),sizeof(receivedTokenTemp));
			if(agataIsValidNumber(receivedTokenTemp, DadoSnZonaDefault)){
				parametrosFromSerial.sensibilidade[i]= (char) atoi(receivedTokenTemp);
			}
			memset(receivedTokenTemp,0, sizeof(receivedTokenTemp));
		}

		for (int j=0; j<=7; j++){
			strncpy(receivedTokenTemp,strtok(NULL,STRING_DATA_SEPARATOR_HTTP),sizeof(receivedTokenTemp));
			if(agataIsValidNumber(receivedTokenTemp, DadoAnZonaDefault)){
				parametrosFromSerial.anulaAreas[j]= (char) atoi(receivedTokenTemp);
			}
			memset(receivedTokenTemp,0, sizeof(receivedTokenTemp));
		}

		strncpy(receivedTokenTemp,strtok(NULL,STRING_DATA_SEPARATOR_HTTP),sizeof(receivedTokenTemp));
		if(agataIsValidNumber(receivedTokenTemp, DadoCanal)){
			parametrosFromSerial.canal= (char) atoi(receivedTokenTemp);
		}
		memset(receivedTokenTemp,0, sizeof(receivedTokenTemp));

		strncpy(receivedTokenTemp,strtok(NULL,STRING_DATA_SEPARATOR_HTTP),sizeof(receivedTokenTemp));
		if(agataIsValidNumber(receivedTokenTemp, DadoFlRuido)){
			parametrosFromSerial.filtroRuido= (char) atoi(receivedTokenTemp);
		}
		memset(receivedTokenTemp,0, sizeof(receivedTokenTemp));

		strncpy(receivedTokenTemp,strtok(NULL,STRING_DATA_SEPARATOR_HTTP),sizeof(receivedTokenTemp));
		if(agataIsValidNumber(receivedTokenTemp, DadoSnRele)){
			parametrosFromSerial.sinalRele= (char) atoi(receivedTokenTemp);
		}
		memset(receivedTokenTemp,0, sizeof(receivedTokenTemp));

		strncpy(receivedTokenTemp,strtok(NULL,STRING_DATA_SEPARATOR_HTTP),sizeof(receivedTokenTemp));
		if(agataIsValidNumber(receivedTokenTemp, DadoPlRele)){
			parametrosFromSerial.pulsoRele= (char) atoi(receivedTokenTemp);
		}
		memset(receivedTokenTemp,0, sizeof(receivedTokenTemp));

		strncpy(receivedTokenTemp,strtok(NULL,STRING_DATA_SEPARATOR_HTTP),sizeof(receivedTokenTemp));
		if(agataIsValidNumber(receivedTokenTemp, DadoSnTrava)){
			parametrosFromSerial.sinalTrava= (char) atoi(receivedTokenTemp);
		}
		memset(receivedTokenTemp,0, sizeof(receivedTokenTemp));

		strncpy(receivedTokenTemp,strtok(NULL,STRING_DATA_SEPARATOR_HTTP),sizeof(receivedTokenTemp));
		if(agataIsValidNumber(receivedTokenTemp, DadoPlTrava)){
			parametrosFromSerial.pulsoTrava= (char) atoi(receivedTokenTemp);
		}
		memset(receivedTokenTemp,0, sizeof(receivedTokenTemp));

		strncpy(receivedTokenTemp,strtok(NULL,STRING_DATA_SEPARATOR_HTTP),sizeof(receivedTokenTemp));
		if(agataIsValidNumber(receivedTokenTemp, DadoMdTravamento)){
			parametrosFromSerial.modoTravamento= (char) atoi(receivedTokenTemp);
		}
		memset(receivedTokenTemp,0, sizeof(receivedTokenTemp));

		strncpy(receivedTokenTemp,strtok(NULL,STRING_DATA_SEPARATOR_HTTP),sizeof(receivedTokenTemp));
		if(agataIsValidNumber(receivedTokenTemp, DadoSlMetal)){
			parametrosFromSerial.selecaoMetais= (char) atoi(receivedTokenTemp);
		}
		memset(receivedTokenTemp,0, sizeof(receivedTokenTemp));

		strncpy(receivedTokenTemp,strtok(NULL,STRING_DATA_SEPARATOR_HTTP),sizeof(receivedTokenTemp));
		if(agataIsValidNumber(receivedTokenTemp, DadoVlVoz)){
			parametrosFromSerial.volumeVoz= (char) atoi(receivedTokenTemp);
		}
		memset(receivedTokenTemp,0, sizeof(receivedTokenTemp));

		strncpy(receivedTokenTemp,strtok(NULL,STRING_DATA_SEPARATOR_HTTP),sizeof(receivedTokenTemp));
		if(agataIsValidNumber(receivedTokenTemp, DadoVlBuzzer)){
			parametrosFromSerial.volumeBuzzer= (char) atoi(receivedTokenTemp);
		}
		memset(receivedTokenTemp,0, sizeof(receivedTokenTemp));

		strncpy(receivedTokenTemp,strtok(NULL,STRING_DATA_SEPARATOR_HTTP),sizeof(receivedTokenTemp));
		if(agataIsValidNumber(receivedTokenTemp, DadoTmBuzzer)){
			parametrosFromSerial.tomBuzzer= (char) atoi(receivedTokenTemp);
		}

		strncpy(receivedTokenTemp,strtok(NULL,STRING_DATA_SEPARATOR_HTTP),sizeof(receivedTokenTemp));
		if(agataIsValidNumber(receivedTokenTemp, DadoTsAgata)){
			//TODO Converter o valor de timestamp para usar no agata
		}

		strncpy(receivedTokenTemp,strtok(NULL,STRING_DATA_SEPARATOR_HTTP),sizeof(receivedTokenTemp));
		if(agataIsValidNumber(receivedTokenTemp, DadoSwUser)){
			softwareEditId = (char) atoi(receivedTokenTemp);
		}

		//Checa se a mensagem veio correta - com a quantidade de dados ok

		if(fnChecaMensagemRecebida(receivedTokenTemp, MensagemRemSimtroValidCharCheck) != 0){
			memset(recebe_serial,0,sizeof(recebe_serial));
			estado_MODULO_ETHERNET = ESTADO_ESPERA;
			return;
		}

		//CONFIGURA COM NOVOS PARAMETROS
		memset(receivedTokenTemp,0, sizeof(receivedTokenTemp));

		//O canal deve ser salvo de primeira pois ele altera a sensibilidade
		if(canal != parametrosFromSerial.canal){
			fnGravaAuditoria(MonitCanal,canal,parametrosFromSerial.canal,softwareEditId,'S');
			canal = parametrosFromSerial.canal;
			for(int i = 1;i <= 8;i++) sensibilidade_temp[i] = buffer_sensibilidade[i];	// Necessario para salvar sensibilidade sem considerar o canal
			fnAtualizaPerfil(SETA_PARAMETRO_ON,SETA_PWM_ON,SETA_GRAVA_FLASH_ON,SETA_POT_GANHO_ON);
			for(int j = 1;j <= 8;j++) buffer_sensibilidade[j] = sensibilidade_temp[j];
		}

		//**Gravacao de valores de auditoria (A preparar funcoes para cada caso)
		AtualizaSensibilidadeGravaAuditoria(buffer_sensibilidade, parametrosFromSerial.sensibilidade, softwareEditId, 'S');
		AtualizaAnulaAreaGravaAuditoria(anula_area, parametrosFromSerial.anulaAreas,softwareEditId,'S');

		if(filtroruido != parametrosFromSerial.filtroRuido)
			fnGravaAuditoria(MonitFlRuido,filtroruido,parametrosFromSerial.filtroRuido,softwareEditId,'S');
		filtroruido = parametrosFromSerial.filtroRuido;

		if(sinal_rele != parametrosFromSerial.sinalRele)
			fnGravaAuditoria(MonitSnRele,sinal_rele,parametrosFromSerial.sinalRele,softwareEditId,'S');
		sinal_rele = parametrosFromSerial.sinalRele;

		if(pulso_rele != parametrosFromSerial.pulsoRele)
			fnGravaAuditoria(MonitPlRele,pulso_rele,parametrosFromSerial.pulsoRele,softwareEditId,'S');
		pulso_rele = parametrosFromSerial.pulsoRele; //Armazena o pulso do rel� multiplicado por 10

		if(sinal_trava != parametrosFromSerial.sinalTrava)
			fnGravaAuditoria(MonitSnTrava,sinal_trava,parametrosFromSerial.sinalTrava,softwareEditId,'S');
		sinal_trava = parametrosFromSerial.sinalTrava; //Armazena o sinal da trava - se pulso ou reten��o e controle somente ou reten��o e controle e teclado

		if(pulso_trava != parametrosFromSerial.pulsoTrava)
			fnGravaAuditoria(MonitPlTrava,pulso_trava,parametrosFromSerial.pulsoTrava,softwareEditId,'S');
		pulso_trava = parametrosFromSerial.pulsoTrava; //Armazena o pulso da trava multiplicado por 10

		if(modo_travamento != parametrosFromSerial.modoTravamento)
			fnGravaAuditoria(MonitMdTravamento,modo_travamento,parametrosFromSerial.modoTravamento,softwareEditId,'S');
		modo_travamento = parametrosFromSerial.modoTravamento;

		if(selecao_metais != parametrosFromSerial.selecaoMetais)
			fnGravaAuditoria(MonitSlMetal,selecao_metais,parametrosFromSerial.selecaoMetais,softwareEditId,'S');
		selecao_metais = parametrosFromSerial.selecaoMetais; //Armazena a selecao de metais

		if(volume_mensagem_voz != parametrosFromSerial.volumeVoz)
			fnGravaAuditoria(MonitVlVoz,volume_mensagem_voz,parametrosFromSerial.volumeVoz,softwareEditId,'S');
		volume_mensagem_voz = parametrosFromSerial.volumeVoz; //Armazena o volume da mensagem de voz - 0 a 10, sendo 0 desligado

		if(buffer_buzzer[BUZZER_VOLUME] != parametrosFromSerial.volumeBuzzer)
			fnGravaAuditoria(MonitVlBuzzer,buffer_buzzer[BUZZER_VOLUME],parametrosFromSerial.volumeBuzzer,softwareEditId,'S');
		buffer_buzzer[BUZZER_VOLUME] = parametrosFromSerial.volumeBuzzer; //Armazena o volume do buzzer - 0 a 10, sendo 0 desligado

		if(buffer_buzzer[BUZZER_TOM] != parametrosFromSerial.tomBuzzer)
			fnGravaAuditoria(MonitTmBuzzer,buffer_buzzer[BUZZER_TOM],parametrosFromSerial.tomBuzzer,softwareEditId,'S');
		buffer_buzzer[BUZZER_TOM] = parametrosFromSerial.tomBuzzer; //Armazena o volume do buzzer - 0 a 10, sendo 0 desligado


		//Atribuicao dos valores da struct para o  Write_Buffer_FLASH - usado para gravacao
		memset(parametrosGravar,0,sizeof(parametrosGravar));
		AtribuiParametrosAgataParaWriteBuffer(parametrosFromSerial,parametrosGravar);

		//Escrita e limpeza do Write_Buffer_FLASH (com as configuracoes) na flash interena
		//EscreveBufferFlashInterna(parametrosGravar, endFLASHSensibilidadeArea1, strlen(parametrosGravar), 0);
		EscreveBufferFlashInterna();
		fnCarregaParametros();
		memset(parametrosGravar,0,sizeof(parametrosGravar));

		delay_ms(10); //Espera 10ms para iniciar a confirmacao
		estado_MODULO_ETHERNET = ESTADO_ESPERA;
		break;

	case '0':	//Inicia a confirmacao

		if(EventToSend)	//Se enviou um evento, confima na memoria interna que foi enviado e recebido
		{
			numero_do_bloco = ( (end_event_reenvio - 0x48000) / 4096) + 5; //Coloquei 5 porque aponta no endere�o 0x48000,se estiver na faixa dos 48000 a 49000 a divis�o vai dar zero e somando a 5 vai dar 5 x 0x1000 = 0x5000, sendo 0x43000 + 0x5000 = 0x48000 que vai estar no endere�o certo
			if(!FORCAR_TESTE_ENVIO_EVENTO_SIMTRO){
				Write_Buffer_FLASH[0] = 0; //coloca 0 para zerar a posi��o especifica de mem�ria.
				ESCREVE_FLASH_INTERNA(end_event_reenvio,1,numero_do_bloco); //Escreve zero no endere�o correspondente
				flagEventoLido = 0; //Zera a var�avel flagEventoLido
			}
		}
		if(AudToSend) //Se enviou uma auditoria, confima na memoria interna que foi enviado e recebido
		{
			numero_do_bloco = ( (end_audit_reenvio - 0x75000) / 4096) + 50; //Coloquei 50 porque aponta no endere�o 0x75000,se estiver na faixa dos 75000 a 76000 a divis�o vai dar zero e somando a 50 vai dar 50(0x32 em hexa) x 0x1000 = 0x32000, sendo 0x43000 + 0x32000 = 0x75000 que vai estar no endere�o certo
			if(!FORCAR_TESTE_ENVIO_AUDITO_SIMTRO){
				Write_Buffer_FLASH[0] = 0; //coloca 0 para zerar a posi��o especifica de mem�ria.
				ESCREVE_FLASH_INTERNA(end_audit_reenvio,1,numero_do_bloco); //Escreve zero no endere�o correspondente
				flagAuditLido = 0; //Zera a var�avel flagEventoLido
			}
		}


		break;

	case '2':

		//Nota: A mensagem da Simtro vem descriptografada, com excecao da parte de data
		//	referente aos dados a serem utilizados para configurar o detector de metal
		if(MODO_CRIPTOGRAFIA_ECB_SIMTRO){

			//Limpa e remove os caracteres invalidos da mensagem recebida
			memset(recebe_serial_temp,0,sizeof(recebe_serial_temp));
			strcpy(recebe_serial_temp,(strstr(recebe_serial,STRING_DATA_START_HTTP)));
			recebe_serial_temp[strlen(recebe_serial_temp)-1] = 0;
			strcpy(recebe_serial_temp,&recebe_serial_temp[strlen(STRING_DATA_START_HTTP)]);
			memset(strstr(recebe_serial_temp,"\""), 0, strlen(STRING_DATA_START_HTTP)+1);	//Seta ultimo caractere do campo data como nulo para indicar o fim
			removeChar(recebe_serial_temp,'\\');			//Remove caracteres invalidos da base64 - no caso simtro esta enviando \

			//Decodifica de base64 para mensagem criptografada AES
			base64_decode_aux(recebe_serial_temp, strlen(recebe_serial_temp), &tamanhoCriptografado, recebe_serial_decriptografado, sizeof(recebe_serial_decriptografado));
			for(int k=0;k<tamanhoCriptografado;k++){
				recebe_serial_temp[k]=recebe_serial_decriptografado[k];
			}

			//Executa a decriptografia, bloco por bloco (16 caracteres)
			AES_init_ctx(&ctx, trataSerial2Key); //Inicializa o vetor para descriptografar
			for(int i = 0; i<tamanhoCriptografado;i = i+16){
				AES_ECB_decrypt(&ctx, &recebe_serial_temp[i]);
			}

			//Limpa e atribui para o array recebe_serial a ser usado
			memset(recebe_serial_decriptografado,0,sizeof(recebe_serial_decriptografado));
			memset(recebe_serial,0, sizeof(recebe_serial));
			strcpy(recebe_serial,recebe_serial_temp);
			memset(recebe_serial_temp,0, sizeof(recebe_serial_temp));
		}


		//Limpeza do buffer e copia do recebido da serial para o buffer de leitura
		memset(reading_pointer, 0, sizeof(reading_pointer));
		strcpy(reading_pointer,(strstr(recebe_serial,STRING_DATA_COMANDO_HTTP)+strlen(STRING_DATA_COMANDO_HTTP)));

		//Busca se tem o caractere final, se nao houver a mensagem esta quebrada e deve ignorar
		if(strstr(reading_pointer,"]")==NULL){
			memset(recebe_serial,0,sizeof(recebe_serial));
			estado_MODULO_ETHERNET = ESTADO_ESPERA;
			return;
		}
		memset(strstr(reading_pointer,"]"), 0, 1);

		memset(receivedTokenTemp,0,sizeof(receivedTokenTemp));
		strncpy(receivedTokenTemp,strtok(reading_pointer,STRING_TERMINATOR_COMANDO),sizeof(receivedTokenTemp));
		if(receivedTokenTemp == ABRIR_PGDM){
			SendCan(ZC_CAN, ABRIR_PGDM);
		}

//		if(receivedTokenTemp == 'A' || receivedTokenTemp == 'F') statusPGDM = !statusPGDM; //DEBUG: Validar comunica��o simtro

		estado_MODULO_ETHERNET = ESTADO_ESPERA;
		break;

	default:		// Falha na comunica��o, volta para a rotina de aguardar 30 segundos
		memset(recebe_serial,0,sizeof(recebe_serial));
		estado_MODULO_ETHERNET = ESTADO_ESPERA;
		return;
	}

	memset(recebe_serial,0,sizeof(recebe_serial));	//Limpa o valor e escapa para a rotina normal

	return;

}

void fnChecksum(byte numero_de_bytes)
{
	static byte checksum = 0;

	for(x = 0;x < numero_de_bytes;x++)
	{
		checksum = checksum + envia_serial1[x];
	}

	checksum = (0xFF - checksum) + 1;
}

void ZeraReadWriteBufferFLASH(void)
{
	for(x = 0;x < 4096;x++)
	{
		Write_Buffer_FLASH[x] = 0;
		Read_Buffer_FLASH[x] = 0;
	}
}

void fnGravaNumSerie(void)
{
	static byte estadoNumSerie = 1, identador = 6;

	switch(estadoNumSerie)
	{
		case 1:
		{
			tela = TELA_DIGITE_NUMERO_SERIE;
			Atualiza_LCD();
			SetaCaracterSenha(identador);
			estadoNumSerie = 2;
			teclapressionada = 0;
			break;
		}
		case 2:
		{
			if(teclapressionada == teclaCancela)
			{
				estadoNumSerie = 1;
				identador = 6;
				teclapressionada = 0;
				ch = 0x30;
				FIM_NUMERO_SERIE = NAO;
				LigaDesligaCursor(DESLIGA);
			}
			if(teclapressionada == teclaConfirma)
			{
				SetaCaracterSenha(identador);
				numero_serie[identador - 6] = ch;
				identador++;
				COLUNA = identador;
				PosicionaLCD(pos);
				ch = 0x30;
				C = ch;
				teclapressionada = 0;
			}
			if(teclapressionada == teclaIncrementa)
			{
				if(C == 0X39)	//'9'
				{
					C = 0X30;	//'0';
					EscreveChar(C);
					COLUNA = identador;
					PosicionaLCD(pos);
				}
				else
				{
					C++;
					EscreveChar(C);
					COLUNA = identador;
					PosicionaLCD(pos);
				}
				ch = C;
				teclapressionada = 0;
			}
			if(teclapressionada == teclaDecrementa)
			{
				if(C == 0x30)	//'0'
				{
					C = 0x39;	//'9'
					EscreveChar(C);
					pos[1] = identador;
					PosicionaLCD(pos);
				}
				else
				{
					C--;
					EscreveChar(C);
					COLUNA = identador;
					PosicionaLCD(pos);
				}
				ch = C;
				teclapressionada = 0;
			}
			if(identador >= 12)
			{
				estadoNumSerie = 3;
				identador = 6;
				ch = 0x30;
			}
			break;
		}
		case 3:
		{
			if(!!agataChecaSerialValido(numero_serie)){
				estadoNumSerie = 1;
				identador = 6;
				teclapressionada = 0;
				ch = 0x30;
				FIM_NUMERO_SERIE = NAO;
				LigaDesligaCursor(DESLIGA);
				return;
			}
			Write_Buffer_FLASH[0] = 'D';
			Write_Buffer_FLASH[1] = 'T';
			for(x = 0;x < 6;x++)
			{
				Write_Buffer_FLASH[x+2] = numero_serie[x];
			}
			ESCREVE_FLASH_INTERNA(END_INI_PARAMETROS,8,0);
			estadoNumSerie = 1;
			identador = 6;
			teclapressionada = 0;
			ch = 0x30;
			FIM_NUMERO_SERIE = SIM;
			LigaDesligaCursor(DESLIGA);
			break;
		}
		break;
	}
}

void fnEscolheSTATICouDHCP(void)
{
	static byte estadoEscolhe = 1; //Definindo vari�vel estadoModoTravamento para o switch case abaixo e a vari�vel modo_travamento_aux para salvar a �ltima altera��o caso desista da altera��o pela tecla cancela

	switch(estadoEscolhe) //Conforme vari�vel vai para o case espec�fico
	{
		case 1: //ENTRA NO MENU DE ESCOLHA DO MODO STATIC OU DHCP
		{
			tela = TELA_MOSTRA_STATIC_DHCP; //Tela � igual a TELA_MOSTRA_STATIC_DHCP
			estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
			estadoEscolhe = 2; //Coloca a vari�vel para 2 para entrar no case 2
			escolhe = 1; //Armazena em modo_travamento_aux o �ltimo valor do modo_travamento sem alterar para recuperar quando cancela
			teclapressionada = 0; //Limpa a teclapressionada
			break;
		}
		case 2: //ESCOLHE ENTRE AS OP��ES SOMENTE_DESTRAVA ou TRAVA_DESTRAVA
		{
			switch (teclapressionada) //Conforme tecla pressionada executa o case espec�fico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada ent�o
				case teclaTrava:
				{
					escolhe++; //Incrementa modo_travamento
					if(escolhe > 2) //Se modo_travamento for maior que TRAVA_DESTRAVA ent�o
					{
						escolhe = 1; //Armazena em modo_travamento o valor SOMENTE_DESTRAVA
					}
					tela = TELA_MOSTRA_STATIC_DHCP; //Tela � igual a TELA_MOSTRA_MODO_DE_TRAVAMENTO
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada ent�o
				case teclaDestrava:
				{
					escolhe--; //Decrementa modo_travamento
					if(escolhe < 1) //Se modo_travamento for menor que SOMENTE_DESTRAVA ent�o
					{
						escolhe = 2; //Armazena em modo_travamento o valor TRAVA_DESTRAVA
					}
					tela = TELA_MOSTRA_STATIC_DHCP; //Tela � igual a TELA_MOSTRA_MODO_DE_TRAVAMENTO
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada ent�o
				case teclaConfirma_Remoto:
				{
					if(escolhe == 1)
					{
						PADRAO = _STATIC_REMOTO;
						fnLeEnderecosAcessoRemotoSTATIC();
						tela = TELA_MOSTRA_CONFIGURACOES_DA_INTERNET; //Tela � igual a TELA_MODO_DE_TRAVAMENTO
						estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
						estado = ESTADO_CONFIGURACOES_DE_INTERNET; //Estado a ser executado � ESTADO_AJUSTES_BASICOS
						estadoEscolhe = 1; //Coloca a vari�vel estadoModoTravamento para 1 para voltar a camada 1 desta fun��o
						teclapressionada = 0; //Limpa a teclapressionada
					}
					else if(escolhe == 2)
					{
						PADRAO = _DHCP_REMOTO;
						fnLeEnderecosAcessoRemotoDHCP();
						tela = TELA_MOSTRA_CONFIGURACOES_MODO_REDE; //Tela � igual a TELA_MODO_DE_TRAVAMENTO
						estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
						estado = ESTADO_CONFIGURACOES_DE_INTERNET; //Estado a ser executado � ESTADO_AJUSTES_BASICOS
						estadoEscolhe = 1; //Coloca a vari�vel estadoModoTravamento para 1 para voltar a camada 1 desta fun��o
						teclapressionada = 0; //Limpa a teclapressionada
					}
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada ent�o
				{
					tela = TELA_MOSTRA_CONFIGURACOES_MODO_REDE; //Tela � igual a TELA_MODO_DE_TRAVAMENTO
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					estado = ESTADO_CONFIGURACOES_DE_INTERNET; //Estado a ser executado � ESTADO_AJUSTES_BASICOS
					estadoEscolhe = 1; //Coloca a vari�vel estadoModoTravamento para 1 para voltar a camada 1 desta fun��o
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				break;
			}
			break;
		}
		break;
	}
}


// Bloco de log de eventos vai de 84000 a 87FFF. Cada bloco tem 4096 bytes, ou seja, 512 registros de 8 bytes cada, totalizando 4 blocos de 512 registros =  2048 registros
// A vari�vel n_bloco_l j� come�a em 1 para shiftar a mem�ria em 0x1000 iniciando corretamente em 84000 e para efeitos de c�lculos foi utilizado assim.
void fnLeRegistroEventos(void)
{
	if(!FIM_LOG_EVENTOS)
	{
		if(n_bloco_l <= n_blocologeventos)
		{
			end_bloco_l = END_INI_PARAMETROS + ((indice_eventos_cont - 1) * 8) + (n_bloco_l * 4096); //end_bloco_l = 0x83000 + 0 bytes + (1 * 4096) = 0x84000
			LE_FLASH_INTERNA(end_bloco_l,8); //L� os 8 bytes a partir do endere�o especificado

			if(indice_eventos_cont == 512)
			{
				n_bloco_l++;
				indice_eventos_cont = 0;
			}
		}
		else if(n_blocologeventos_extra > 0)
		{
			end_bloco_l = END_INI_PARAMETROS + ((indice_eventos_cont - 1) * 8) + (n_bloco_l * 4096); //end_bloco_l = 0x83000 + 0 bytes + (1 * 4096) = 0x84000
			LE_FLASH_INTERNA(end_bloco_l,8); //L� os 8 bytes a partir do endere�o especificado

			if(indice_eventos_cont == (n_logeventos - ((n_bloco_l - 1) * 512)))
			{
				indice_eventos_lidos = indice_eventos;
//				indice_eventos = 0;
				indice_eventos_cont = 0;
				n_logeventos = 0;
				n_blocologeventos_extra = 0;
				FIM_LOG_EVENTOS = TRUE;
			}

		}
		if(n_bloco_l > n_blocologeventos && n_blocologeventos_extra != 1)
		{
			indice_eventos_lidos = indice_eventos;
//			indice_eventos = 0;
			indice_eventos_cont = 0;
			n_logeventos = 0;
			n_blocologeventos_extra = 0;
			FIM_LOG_EVENTOS = TRUE;
		}
	}
}

// Bloco de log de auditorias vai de 88000 a 87FFF. Cada bloco tem 3960 bytes, ou seja, 360 registros de 11 bytes cada, totalizando 120 blocos de 360 registros =  43200 registros
// A vari�vel n_bloco_a j� come�a em 1 para shiftar a mem�ria em 0x1000 iniciando corretamente em 88000 e para efeitos de c�lculos foi utilizado assim.
void fnLeRegistroAuditorias(void)
{
	if(!FIM_LOG_AUDITORIAS)
	{
		if(n_bloco_a <= n_blocologauditorias)
		{
			end_bloco_a = (END_INI_LOG_AUDITORIAS - 0x1000) + ((indice_auditorias_cont - 1) * 11) + (n_bloco_a * 4096); //end_bloco_a = 0x87000 + 0 bytes + (1 * 4096) = 0x88000
			LE_FLASH_INTERNA(end_bloco_a,11); //L� os 11 bytes a partir do endere�o especificado

			if(indice_auditorias_cont == 360)
			{
				n_bloco_a++;
				indice_auditorias_cont = 0;
			}
		}
		else if(n_blocologauditorias_extra > 0)
		{
			end_bloco_a = (END_INI_LOG_AUDITORIAS - 0x1000) + ((indice_auditorias_cont - 1) * 11) + ((n_bloco_a) * 4096); //end_bloco_a = 0x87000 + 0 bytes + (1 * 4096) = 0x88000
			LE_FLASH_INTERNA(end_bloco_a,11); //L� os 8 bytes a partir do endere�o especificado

			if(indice_auditorias_cont == (n_logauditorias - ((n_bloco_a - 1) * 360)))
			{
				indice_auditorias_lidos = indice_auditorias;
//				indice_auditorias = 0;
				indice_auditorias_cont = 0;
				n_logauditorias = 0;
				n_blocologauditorias_extra = 0;
				FIM_LOG_AUDITORIAS = TRUE;
			}

		}
		if(n_bloco_a > n_blocologauditorias && n_blocologauditorias_extra != 1)
		{
			indice_auditorias_lidos = indice_auditorias;
//			indice_auditorias = 0;
			indice_auditorias_cont = 0;
			n_logauditorias = 0;
			n_blocologauditorias_extra = 0;
			FIM_LOG_AUDITORIAS = TRUE;
		}
	}
}

void abortTxCAN(void){

	CAN0_CS1 = 0x09;								//Escreve no CODE do MB1 para abortar transmiss�o
	delay_ms(5);

	EnterCritical();								//Desabilita interrup��es

	//Configura o m�dulo CAN em modo Freeze
	CAN0_MCR |= CAN_MCR_FRZ_MASK;
	CAN0_MCR |= CAN_MCR_HALT_MASK;

	while(!(CAN0_MCR & CAN_MCR_FRZACK_MASK)){}		//Aguarda o m�dulo entra no modo Freeza


	CAN0_MCR &= ~CAN_MCR_HALT_MASK;					//Sair do modo Freeze
	while (CAN0_MCR & CAN_MCR_FRZACK_MASK){}		//Aguarda confirmar que CAN saiu do modo Freeze

	CAN_PDD_ClearMessageBufferInterruptFlagMask1(CAN0_BASE_PTR,0x02);				//Apaga a flag do Mailbox 1 (MB utilizado na fun��o SendCan)
	CAN_PDD_SetMessageBufferCode(CAN0_BASE_PTR, 1U, CAN_PDD_MB_TX_NOT_ACTIVE);		//Libera o MB1 para uso como TX
	ExitCritical();									//Habilita interrup��es
}

void configAnaliseControle(void){
	ACAO_CONTROLE = AVALIA_CONTROLE;
	pulsos = 0;
	tempoVtInativo = 0;
	start_remoto = 0;
	INICIA_CONTADOR_PULSOS = FALSE;
}

void defineTipoControle(void){
	bool sairFunc = FALSE;
	teclapressionada = 0;
	tela = TELA_TIPO_CONTROLE;
	tipoControle = 'B';
	Atualiza_LCD();
	do {
		switch(teclapressionada)
		{
			case teclaIncrementa: //Caso tecla INCREMENTA ou tecla DECREMENTA ou tecla TRAVA ou tecla DESTRAVA pressionada vai ent�o
			case teclaDecrementa:
			case teclaTrava:
			case teclaDestrava:
			{
				if(tipoControle == 'B') //Se trava_inteligente for igual a NAO ent�o
				{
					tipoControle = 'A'; //Se trava_inteligente for igual a SIM ent�o
					LINHA = 2; //Se posiciona na linha 2
					COLUNA = 2; //Se posiciona na coluna 2
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna desejadas
					EscreveChar(' '); //Escreve espa�o na posi��o especificada
					COLUNA = 15; //Se posiciona na coluna 15
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada anteriormente
					EscreveChar('X'); //Escreve X na posi��o especificada
					teclapressionada = 0; //Limpa teclapressionada
				}
				else if(tipoControle == 'A') //Se trava_inteligente for igual a SIM ent�o
				{
					tipoControle = 'B'; //Se trava_inteligente for igual a NAO ent�o
					LINHA = 2; //Se posiciona na linha 2
					COLUNA = 2; //Se posiciona na coluna 2
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificadas
					EscreveChar('X'); //Escreve X na posi��o especificada
					COLUNA = 15; //Se posiciona na coluna 15
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada anteriormente
					EscreveChar(' '); //Escreve espa�o na posi��o especificada
					teclapressionada = 0; //Limpa teclapressionada
				}
				break;
			}
				case teclaConfirma:
				case teclaConfirma_Remoto:
				{
					sairFunc = TRUE;
					teclapressionada = 0;
					break;
				}
				case teclaCancela:
				{
					sairFunc = TRUE;
					teclapressionada = 0;
					break;
				}
		}
	}while(sairFunc == FALSE);
	sairFunc = 0;
}

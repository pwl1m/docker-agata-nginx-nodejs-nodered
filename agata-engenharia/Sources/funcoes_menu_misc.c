/*
 * funcoes_menu_misc.c
 *
 *  Created on: 23/06/2023
 *      Author: marcos.butignol
 */

//Funções gerais - Caso um grupo de funcoes fique grande demais criar novo arquivo para abranger grupo.

#include "funcao.h"

#include "agata_std_functions.h"
#include "agata_hc_definitions.h"
#include "stdlib.h"






/*** Funções do MENU BARGRAPH ***/

void fnEscreveBargraph(void) //Serve tanto para BARGRAPH como COMPATIBILIDADE ELETROMAGNÉTICA, escreve os asteriscos conforme o nível do ruido
{
	if(FlagADC) //Se FlagADC for igual a 1 então
	{
		if(Valor[AREA1] >= NIVEL_ZERO) //Se valor do sinal da área 1 for maior que NIVEL_ZERO (32768) então corrige valor para a faixa correta pois sinal é positivo
		{
			Valor[AREA1] = Valor[AREA1] - NIVEL_ZERO; //Valor do sinal da área 1 é igual ao valor lido da área 1 menos o valor NIVEL_ZERO (32768)
		}
		else //Senão se valor do sinal da área 1 for menor que NIVEL_ZERO (32768) corrige valor para a faixa correta pois sinal é negativo
		{
			Valor[AREA1] = NIVEL_ZERO - Valor[AREA1]; //Valor do sinal da área 1 é igual ao valor NIVEL_ZERO (32768) menos o valor lido da área 1
		}

		if(Valor[AREA2] >= NIVEL_ZERO) //Se valor do sinal da área 2 for maior que NIVEL_ZERO (32768) então corrige valor para a faixa correta pois sinal é positivo
		{
			Valor[AREA2] = Valor[AREA2] - NIVEL_ZERO; //Valor do sinal da área 2 é igual ao valor lido da área 2 menos o valor NIVEL_ZERO (32768)
		}
		else //Senão se valor do sinal da área 2 for menor que NIVEL_ZERO (32768) corrige valor para a faixa correta pois sinal é negativo
		{
			Valor[AREA2] = NIVEL_ZERO - Valor[AREA2]; //Valor do sinal da área 2 é igual ao valor NIVEL_ZERO (32768) menos o valor lido da área 2
		}

		if(Valor[AREA3] >= NIVEL_ZERO) //Se valor do sinal da área 3 for maior que NIVEL_ZERO (32768) então corrige valor para a faixa correta pois sinal é positivo
		{
			Valor[AREA3] = Valor[AREA3] - NIVEL_ZERO; //Valor do sinal da área 3 é igual ao valor lido da área 3 menos o valor NIVEL_ZERO (32768)
		}
		else //Senão se valor do sinal da área 3 for menor que NIVEL_ZERO (32768) corrige valor para a faixa correta pois sinal é negativo
		{
			Valor[AREA3] = NIVEL_ZERO - Valor[AREA3]; //Valor do sinal da área 3 é igual ao valor NIVEL_ZERO (32768) menos o valor lido da área 3
		}

		if(tipo_detector == Z8)
		{
			if(Valor[AREA4] >= NIVEL_ZERO) //Se valor do sinal da área 4 for maior que NIVEL_ZERO (32768) então corrige valor para a faixa correta pois sinal é positivo
			{
				Valor[AREA4] = Valor[AREA4] - NIVEL_ZERO; //Valor do sinal da área 4 é igual ao valor lido da área 4 menos o valor NIVEL_ZERO (32768)
			}
			else //Senão se valor do sinal da área 4 for menor que NIVEL_ZERO (32768) corrige valor para a faixa correta pois sinal é negativo
			{
				Valor[AREA4] = NIVEL_ZERO - Valor[AREA4]; //Valor do sinal da área 4 é igual ao valor NIVEL_ZERO (32768) menos o valor lido da área 4
			}

			if(Valor[AREA5] >= NIVEL_ZERO) //Se valor do sinal da área 5 for maior que NIVEL_ZERO (32768) então corrige valor para a faixa correta pois sinal é positivo
			{
				Valor[AREA5] = Valor[AREA5] - NIVEL_ZERO; //Valor do sinal da área 5 é igual ao valor lido da área 5 menos o valor NIVEL_ZERO (32768)
			}
			else //Senão se valor do sinal da área 5 for menor que NIVEL_ZERO (32768) corrige valor para a faixa correta pois sinal é negativo
			{
				Valor[AREA5] = NIVEL_ZERO - Valor[AREA5]; //Valor do sinal da área 5 é igual ao valor NIVEL_ZERO (32768) menos o valor lido da área 5
			}

			if(Valor[AREA6] >= NIVEL_ZERO) //Se valor do sinal da área 6 for maior que NIVEL_ZERO (32768) então corrige valor para a faixa correta pois sinal é positivo
			{
				Valor[AREA6] = Valor[AREA6] - NIVEL_ZERO; //Valor do sinal da área 6 é igual ao valor lido da área 6 menos o valor NIVEL_ZERO (32768)
			}
			else //Senão se valor do sinal da área 6 for menor que NIVEL_ZERO (32768) corrige valor para a faixa correta pois sinal é negativo
			{
				Valor[AREA6] = NIVEL_ZERO - Valor[AREA6]; //Valor do sinal da área 6 é igual ao valor NIVEL_ZERO (32768) menos o valor lido da área 6
			}

			if(Valor[AREA7] >= NIVEL_ZERO) //Se valor do sinal da área 7 for maior que NIVEL_ZERO (32768) então corrige valor para a faixa correta pois sinal é positivo
			{
				Valor[AREA7] = Valor[AREA7] - NIVEL_ZERO; //Valor do sinal da área 7 é igual ao valor lido da área 7 menos o valor NIVEL_ZERO (32768)
			}
			else //Senão se valor do sinal da área 7 for menor que NIVEL_ZERO (32768) corrige valor para a faixa correta pois sinal é negativo
			{
				Valor[AREA7] = NIVEL_ZERO - Valor[AREA7]; //Valor do sinal da área 7 é igual ao valor NIVEL_ZERO (32768) menos o valor lido da área 7
			}

			if(Valor[AREA8] >= NIVEL_ZERO) //Se valor do sinal da área 8 for maior que NIVEL_ZERO (32768) então corrige valor para a faixa correta pois sinal é positivo
			{
				Valor[AREA8] = Valor[AREA8] - NIVEL_ZERO; //Valor do sinal da área 8 é igual ao valor lido da área 8 menos o valor NIVEL_ZERO (32768)
			}
			else //Senão se valor do sinal da área 8 for menor que NIVEL_ZERO (32768) corrige valor para a faixa correta pois sinal é negativo
			{
				Valor[AREA8] = NIVEL_ZERO - Valor[AREA8]; //Valor do sinal da área 8 é igual ao valor NIVEL_ZERO (32768) menos o valor lido da área 8
			}
		}

		if(selecionaArea == 1) //Se selecionaArea for igual a 1 então
		{
			valor_bargraph = Valor[AREA1]; //Armazena na variável_bargraph o valor de sinal lido da área 1
			valor_bargraph1 = Valor[AREA2]; //Armazena na variável_bargraph1 o valor de sinal lido da área 2
		}
		else if(selecionaArea == 2) //Senão se selecionaArea for igual a 2 então
		{
			if(tipo_detector == Z3)
			{
				valor_bargraph = Valor[AREA2]; //Armazena na variável_bargraph o valor de sinal lido da área 2
				valor_bargraph1 = Valor[AREA3]; //Armazena na variável_bargraph1 o valor de sinal lido da área 3
			}
			else if(tipo_detector == Z8)
			{
				valor_bargraph = Valor[AREA3]; //Armazena na variável_bargraph o valor de sinal lido da área 3
				valor_bargraph1 = Valor[AREA4]; //Armazena na variável_bargraph1 o valor de sinal lido da área 4
			}
		}
		else if(selecionaArea == 3)  //Senão se selecionaArea for igual a 3 então
		{
			valor_bargraph = Valor[AREA5]; //Armazena na variável_bargraph o valor de sinal lido da área 5
			valor_bargraph1 = Valor[AREA6]; //Armazena na variável_bargraph1 o valor de sinal lido da área 6
		}
		else if(selecionaArea == 4)  //Senão se selecionaArea for igual a 4 então
		{
			valor_bargraph = Valor[AREA7]; //Armazena na variável_bargraph o valor de sinal lido da área 7
			valor_bargraph1 = Valor[AREA8]; //Armazena na variável_bargraph1 o valor de sinal lido da área 8
		}

		//Cada nivel ou asterisco corresponde a uma tensão RMS de 0.17V. Como 3,3V/2 = 1,65V então 0,17 * 10 níveis =~ 1,70V

		//Estes ifs servem para a área 1 por exemplo, sempre um para 1 e 2 ou 3 e 4 ou 5 e 6 ou 7 e 8
		if (NIVEL_1) //Se nivel 1 então
		{
			valor_atual = 1; //Armazena na variável valor_atual o valor 1
		}
		else if(NIVEL_2) //Senão se nivel 2 então
		{
			valor_atual = 2; //Armazena na variável valor_atual o valor 2
		}
		else if(NIVEL_3) //Senão se nivel 3 então
		{
			valor_atual = 3; //Armazena na variável valor_atual o valor 3
		}
		else if(NIVEL_4) //Senão se nivel 4 então
		{
			valor_atual = 4; //Armazena na variável valor_atual o valor 4
		}
		else if(NIVEL_5) //Senão se nivel 5 então
		{
			valor_atual = 5; //Armazena na variável valor_atual o valor 5
		}
		else if(NIVEL_6) //Senão se nivel 6 então
		{
			valor_atual = 6; //Armazena na variável valor_atual o valor 6
		}
		else if(NIVEL_7) //Senão se nivel 7 então
		{
			valor_atual = 7; //Armazena na variável valor_atual o valor 7
		}
		else if(NIVEL_8) //Senão se nivel 8 então
		{
			valor_atual = 8; //Armazena na variável valor_atual o valor 8
		}
		else if(NIVEL_9) //Senão se nivel 9 então
		{
			valor_atual = 9; //Armazena na variável valor_atual o valor 9
		}
		else if(NIVEL_10) //Senão se nivel 10 então
		{
			valor_atual = 10; //Armazena na variável valor_atual o valor 10
		}

		//Estes ifs servem para a área 2 por exemplo, sempre um para 1 e 2 ou 3 e 4 ou 5 e 6 ou 7 e 8
		if (_NIVEL_1) //Se nivel 1 então
		{
			valor_atual1 = 1; //Armazena na variável valor_atual1 o valor 1
		}
		else if(_NIVEL_2) //Senão se nivel 2 então
		{
			valor_atual1 = 2; //Armazena na variável valor_atual1 o valor 2
		}
		else if(_NIVEL_3) //Senão se nivel 3 então
		{
			valor_atual1 = 3; //Armazena na variável valor_atual1 o valor 3
		}
		else if(_NIVEL_4) //Senão se nivel 4 então
		{
			valor_atual1 = 4; //Armazena na variável valor_atual1 o valor 4
		}
		else if(_NIVEL_5) //Senão se nivel 5 então
		{
			valor_atual1 = 5; //Armazena na variável valor_atual1 o valor 5
		}
		else if(_NIVEL_6) //Senão se nivel 6 então
		{
			valor_atual1 = 6; //Armazena na variável valor_atual1 o valor 6
		}
		else if(_NIVEL_7) //Senão se nivel 7 então
		{
			valor_atual1 = 7; //Armazena na variável valor_atual1 o valor 7
		}
		else if(_NIVEL_8) //Senão se nivel 8 então
		{
			valor_atual1 = 8; //Armazena na variável valor_atual1 o valor 8
		}
		else if(_NIVEL_9) //Senão se nivel 9 então
		{
			valor_atual1 = 9; //Armazena na variável valor_atual1 o valor 9
		}
		else if(_NIVEL_10) //Senão se nivel 10 então
		{
			valor_atual1 = 10; //Armazena na variável valor_atual1 o valor 10
		}

		LigaDesligaCursor(DESLIGA); //Desliga o cursor

		if (valor_atual > valor_anterior) //Se valor_atual for maior que valor_anterior então atualiza asteriscos na tela
		{
			for(valor_presente = valor_anterior;valor_presente < valor_atual;valor_presente++) //Para valor_presente igual a valor_anterior e se valor_presente for menor que valor atual incrementa valor_presente
			{
				LINHA = 1; //Se posiciona na linha 1
				COLUNA = valor_presente + 5; //Se posiciona na coluna 5 + o valor_presente
				PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificados
				EscreveChar('*'); //Escreve asterisco
			}
		}
		else if(valor_atual < valor_anterior) //Senão se valor_atual for menor que valor_anterior então atualiza espaços para ir apagando os asteriscos, ou seja, voltando
		{
			for(valor_presente = valor_anterior;valor_presente > valor_atual;valor_presente--) //Para valor_presente igual a valor_anterior e se valor_presente for maior que valor atual decrementa valor_presente
			{
				LINHA = 1; //Se posiciona na linha 1
				COLUNA = valor_presente + 4;  //Se posiciona na coluna 4 + o valor_presente
				PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificados
				EscreveChar(' '); //Escreve espaço
			}
		}

		if (valor_atual1 > valor_anterior1) //Se valor_atual1 for maior que valor_anterior1 então atualiza asteriscos na tela
		{
			for (valor_presente1 = valor_anterior1;valor_presente1 < valor_atual1;valor_presente1++)  //Para valor_presente1 igual a valor_anterior1 e se valor_presente1 for menor que valor atual1 incrementa valor_presente1
			{
				LINHA = 2; //Se posiciona na linha 2
				COLUNA = valor_presente1 + 5; //Se posiciona na coluna 5 + o valor_presente1
				PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificados
				EscreveChar('*'); //Escreve asterisco
				delay_ms(50); //Espera 50 milisegundos
			}
		}
		else if(valor_atual1 < valor_anterior1) //Senão se valor_atual1 for menor que valor_anterior1 então atualiza espaços para ir apagando os asteriscos, ou seja, voltando
		{
			for (valor_presente1 = valor_anterior1;valor_presente1 > valor_atual1;valor_presente1--)  //Para valor_presente1 igual a valor_anterior1 e se valor_presente1 for maior que valor atual decrementa valor_presente1
			{
				LINHA = 2; //Se posiciona na linha 2
				COLUNA = valor_presente1 + 4; //Se posiciona na coluna 4 + o valor_presente1
				PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificados
				EscreveChar(' '); //Escreve espaço
				delay_ms(50); //Espera 50 milisegundos
			}
		}
		valor_anterior = valor_atual; //Armazena na variável valor_anterior o conteúdo de valor_atual
		valor_anterior1 = valor_atual1; //Armazena na variável valor_anterior1 o conteúdo de valor_atual1
		FlagADC = 0; //Zera a flag flagADC para novas leituras no AD
		LENDO_AREAS = FALSE; //Torna a flag LENDO_AREAS para FALSE para permitir novas leituras do AD
	}
	if(tela == TELA_A1_A2 || tela == TELA_A2_A3 || tela == TELA_A3_A4 || tela == TELA_A5_A6 || tela == TELA_A7_A8) //Se tela for igual a TELA_A1_A2 ou tela for igual a TELA_A3_A4 ou tela for igual a TELA_A5_A6 ou tela for igual a TELA_A7_A8 então
	{
		estado = ESTADO_MOSTRA_BARGRAPH; //Estado a ser executado é ESTADO_MOSTRA_BARGRAPH
	}
	else if(tela == TELA_A1_A2_COMPATIBILIDADE || tela == TELA_A2_A3_COMPATIBILIDADE || tela == TELA_A3_A4_COMPATIBILIDADE || tela == TELA_A5_A6_COMPATIBILIDADE || TELA_A7_A8_COMPATIBILIDADE) //Senão se tela for igual a TELA_A1_A2_COMPATIBILIDADE ou tela for igual a TELA_A3_A4_COMPATIBILIDADE ou tela for igual a TELA_A5_A6_COMPATIBILIDADE ou tela for igual a TELA_A7_A8_COMPATIBILIDADE
	{
		estado = ESTADO_MOSTRA_COMPATIBILIDADE_ELETROMAGNETICA; //Estado a ser executado é ESTADO_MOSTRA_COMPATIBILIDADE_ELETROMAGNETICA
	}
}
/******************************************************************************/



/*** Funções dos POTENCIÔMETROS DIGITAIS ***/
//Escopo da função: fnEnviaSPI(POT_DEFASAGEM,TODAS_AREAS,63) - O primeiro campo pode ser POT_GANHO ou POT_DEFASAGEM, o segundo campo pode ser TODAS_AREAS, AREA_1 a AREA_8 e o terceiro campo é o valor de 1 a 127
void fnEnviaSPI(byte pot_dig, byte sel_area,byte valorad) //Permite enviar a configuração para alterar os potenciômetros digitais
{
	switch(pot_dig) //Conforme valor da variável pot_dig vai para o case específico
	{
		case POT_DEFASAGEM: //Caso POT_DEFASAGEM então
		{
			switch(sel_area) //Conforme valor da variável sel_area vai para o case específico
			{
				case TODAS_AREAS: //Caso TODAS_AREAS
				{
					CS_DEFASAGEM1_OFF; //Desliga o CS_DEFASAGEM1_OFF
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(0x00); //Envia 0x00 primeiramente para acessar o potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(valorad); //Envia na variável valorad para mudar a resistência do potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					CS_DEFASAGEM1_ON; //Liga o CS_DEFASAGEM1_ON para alterar o valor da resistência do potênciometro digital
					AGUARDA_Waitms(10); //Espera 10ms

					CS_DEFASAGEM2_OFF; //Desliga o CS_DEFASAGEM2_OFF
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(0x00); //Envia 0x00 primeiramente para acessar o potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(valorad); //Envia na variável valorad para mudar a resistência do potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					CS_DEFASAGEM2_ON; //Liga o CS_DEFASAGEM2_ON para alterar o valor da resistência do potênciometro digital
					AGUARDA_Waitms(10); //Espera 10ms

					CS_DEFASAGEM3_OFF; //Desliga o CS_DEFASAGEM3_OFF
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(0x00); //Envia 0x00 primeiramente para acessar o potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(valorad); //Envia na variável valorad para mudar a resistência do potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					CS_DEFASAGEM3_ON; //Liga o CS_DEFASAGEM3_ON para alterar o valor da resistência do potênciometro digital
					AGUARDA_Waitms(10); //Espera 10ms

					CS_DEFASAGEM4_OFF; //Desliga o CS_DEFASAGEM4_OFF
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(0x00); //Envia 0x00 primeiramente para acessar o potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(valorad); //Envia na variável valorad para mudar a resistência do potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					CS_DEFASAGEM4_ON; //Liga o CS_DEFASAGEM4_ON para alterar o valor da resistência do potênciometro digital
					AGUARDA_Waitms(10); //Espera 10ms

					CS_DEFASAGEM5_OFF; //Desliga o CS_DEFASAGEM5_OFF
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(0x00); //Envia 0x00 primeiramente para acessar o potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(valorad); //Envia na variável valorad para mudar a resistência do potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					CS_DEFASAGEM5_ON; //Liga o CS_DEFASAGEM5_ON para alterar o valor da resistência do potênciometro digital
					AGUARDA_Waitms(10); //Espera 10ms

					CS_DEFASAGEM6_OFF; //Desliga o CS_DEFASAGEM6_OFF
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(0x00); //Envia 0x00 primeiramente para acessar o potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(valorad); //Envia na variável valorad para mudar a resistência do potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					CS_DEFASAGEM6_ON; //Liga o CS_DEFASAGEM6_ON para alterar o valor da resistência do potênciometro digital
					AGUARDA_Waitms(10); //Espera 10ms

					CS_DEFASAGEM7_OFF; //Desliga o CS_DEFASAGEM7_OFF
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(0x00); //Envia 0x00 primeiramente para acessar o potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(valorad); //Envia na variável valorad para mudar a resistência do potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					CS_DEFASAGEM7_ON; //Liga o CS_DEFASAGEM7_ON para alterar o valor da resistência do potênciometro digital
					AGUARDA_Waitms(10); //Espera 10ms

					CS_DEFASAGEM8_OFF; //Desliga o CS_DEFASAGEM8_OFF
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(0x00); //Envia 0x00 primeiramente para acessar o potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(valorad); //Envia na variável valorad para mudar a resistência do potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					CS_DEFASAGEM8_ON; //Liga o CS_DEFASAGEM8_ON para alterar o valor da resistência do potênciometro digital
					AGUARDA_Waitms(10); //Espera 10ms

					break;
				}
				case AREA_1: //Caso área 1 então
				{
					CS_DEFASAGEM1_OFF; //Desliga o CS_DEFASAGEM1_OFF
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(0x00); //Envia 0x00 primeiramente para acessar o potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(valorad); //Envia na variável valorad para mudar a resistência do potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					CS_DEFASAGEM1_ON; //Liga o CS_DEFASAGEM1_ON para alterar o valor da resistência do potênciometro digital
					AGUARDA_Waitms(10); //Espera 10ms
					break;
				}
				case AREA_2: //Caso área 2 então
				{
					CS_DEFASAGEM2_OFF; //Desliga o CS_DEFASAGEM2_OFF
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(0x00); //Envia 0x00 primeiramente para acessar o potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(valorad); //Envia na variável valorad para mudar a resistência do potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					CS_DEFASAGEM2_ON; //Liga o CS_DEFASAGEM2_ON para alterar o valor da resistência do potênciometro digital
					AGUARDA_Waitms(10); //Espera 10ms
					break;
				}
				case AREA_3: //Caso área 3 então
				{
					CS_DEFASAGEM3_OFF; //Desliga o CS_DEFASAGEM3_OFF
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(0x00); //Envia 0x00 primeiramente para acessar o potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(valorad); //Envia na variável valorad para mudar a resistência do potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					CS_DEFASAGEM3_ON; //Liga o CS_DEFASAGEM3_ON para alterar o valor da resistência do potênciometro digital
					AGUARDA_Waitms(10); //Espera 10ms
					break;
				}
				case AREA_4: //Caso área 4 então
				{
					CS_DEFASAGEM4_OFF; //Desliga o CS_DEFASAGEM4_OFF
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(0x00); //Envia 0x00 primeiramente para acessar o potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(valorad); //Envia na variável valorad para mudar a resistência do potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					CS_DEFASAGEM4_ON; //Liga o CS_DEFASAGEM4_ON para alterar o valor da resistência do potênciometro digital
					AGUARDA_Waitms(10); //Espera 10ms
					break;
				}
				case AREA_5: //Caso área 5 então
				{
					CS_DEFASAGEM5_OFF; //Desliga o CS_DEFASAGEM5_OFF
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(0x00); //Envia 0x00 primeiramente para acessar o potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(valorad); //Envia na variável valorad para mudar a resistência do potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					CS_DEFASAGEM5_ON; //Liga o CS_DEFASAGEM5_ON para alterar o valor da resistência do potênciometro digital
					AGUARDA_Waitms(10); //Espera 10ms
					break;
				}
				case AREA_6: //Caso área 6 então
				{
					CS_DEFASAGEM6_OFF; //Desliga o CS_DEFASAGEM6_OFF
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(0x00); //Envia 0x00 primeiramente para acessar o potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(valorad); //Envia na variável valorad para mudar a resistência do potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					CS_DEFASAGEM6_ON; //Liga o CS_DEFASAGEM6_ON para alterar o valor da resistência do potênciometro digital
					AGUARDA_Waitms(10); //Espera 10ms
					break;
				}
				case AREA_7: //Caso área 7 então
				{
					CS_DEFASAGEM7_OFF; //Desliga o CS_DEFASAGEM7_OFF
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(0x00); //Envia 0x00 primeiramente para acessar o potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(valorad); //Envia na variável valorad para mudar a resistência do potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					CS_DEFASAGEM7_ON; //Liga o CS_DEFASAGEM7_ON para alterar o valor da resistência do potênciometro digital
					AGUARDA_Waitms(10); //Espera 10ms
					break;
				}
				case AREA_8: //Caso área 8 então
				{
					CS_DEFASAGEM8_OFF; //Desliga o CS_DEFASAGEM8_OFF
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(0x00); //Envia 0x00 primeiramente para acessar o potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(valorad); //Envia na variável valorad para mudar a resistência do potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					CS_DEFASAGEM8_ON; //Liga o CS_DEFASAGEM8_ON para alterar o valor da resistência do potênciometro digital
					AGUARDA_Waitms(10); //Espera 10ms
					break;
				}
				break;
			}
			break;
		}
		case POT_GANHO: //Caso POT_GANHO então
		{
			switch(sel_area) //Conforme valor da variável sel_area vai para o case específico
			{
				case TODAS_AREAS: //Caso TODAS_AREAS então
				{
					CS_GANHO1_OFF; //Desliga o CS_GANHO1_OFF
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(0x00); //Envia 0x00 primeiramente para acessar o potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(valorad); //Envia na variável valorad para mudar a resistência do potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					CS_GANHO1_ON; //Liga o CS_GANHO1_ON para alterar o valor da resistência do potênciometro digital
					AGUARDA_Waitms(10); //Espera 10ms

					CS_GANHO2_OFF; //Desliga o CS_GANHO2_OFF
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(0x00); //Envia 0x00 primeiramente para acessar o potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(valorad); //Envia na variável valorad para mudar a resistência do potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					CS_GANHO2_ON; //Liga o CS_GANHO2_ON para alterar o valor da resistência do potênciometro digital
					AGUARDA_Waitms(10); //Espera 10ms

					CS_GANHO3_OFF; //Desliga o CS_GANHO3_OFF
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(0x00); //Envia 0x00 primeiramente para acessar o potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(valorad); //Envia na variável valorad para mudar a resistência do potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					CS_GANHO3_ON; //Liga o CS_GANHO3_ON para alterar o valor da resistência do potênciometro digital
					AGUARDA_Waitms(10); //Espera 10ms

					CS_GANHO4_OFF; //Desliga o CS_GANHO4_OFF
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(0x00); //Envia 0x00 primeiramente para acessar o potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(valorad); //Envia na variável valorad para mudar a resistência do potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					CS_GANHO4_ON; //Liga o CS_GANHO4_ON para alterar o valor da resistência do potênciometro digital
					AGUARDA_Waitms(10); //Espera 10ms

					CS_GANHO5_OFF; //Desliga o CS_GANHO5_OFF
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(0x00); //Envia 0x00 primeiramente para acessar o potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(valorad); //Envia na variável valorad para mudar a resistência do potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					CS_GANHO5_ON; //Liga o CS_GANHO5_ON para alterar o valor da resistência do potênciometro digital
					AGUARDA_Waitms(10); //Espera 10ms

					CS_GANHO6_OFF; //Desliga o CS_GANHO6_OFF
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(0x00); //Envia 0x00 primeiramente para acessar o potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(valorad); //Envia na variável valorad para mudar a resistência do potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					CS_GANHO6_ON; //Liga o CS_GANHO6_ON para alterar o valor da resistência do potênciometro digital
					AGUARDA_Waitms(10); //Espera 10ms

					CS_GANHO7_OFF; //Desliga o CS_GANHO7_OFF
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(0x00); //Envia 0x00 primeiramente para acessar o potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(valorad); //Envia na variável valorad para mudar a resistência do potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					CS_GANHO7_ON; //Liga o CS_GANHO7_ON para alterar o valor da resistência do potênciometro digital
					AGUARDA_Waitms(10); //Espera 10ms

					CS_GANHO8_OFF; //Desliga o CS_GANHO8_OFF
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(0x00); //Envia 0x00 primeiramente para acessar o potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(valorad); //Envia na variável valorad para mudar a resistência do potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					CS_GANHO8_ON; //Liga o CS_GANHO8_ON para alterar o valor da resistência do potênciometro digital
					AGUARDA_Waitms(10); //Espera 10ms

					break;
				}
				case AREA_1: //Caso área 1 então
				{
					CS_GANHO1_OFF; //Desliga o CS_GANHO1_OFF
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(0x00); //Envia 0x00 primeiramente para acessar o potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(valorad); //Envia na variável valorad para mudar a resistência do potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					CS_GANHO1_ON; //Liga o CS_GANHO1_ON para alterar o valor da resistência do potênciometro digital
					AGUARDA_Waitms(10); //Espera 10ms
					break;
				}
				case AREA_2: //Caso área 2 então
				{
					CS_GANHO2_OFF; //Desliga o CS_GANHO2_OFF
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(0x00); //Envia 0x00 primeiramente para acessar o potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(valorad); //Envia na variável valorad para mudar a resistência do potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					CS_GANHO2_ON; //Liga o CS_GANHO2_ON para alterar o valor da resistência do potênciometro digital
					AGUARDA_Waitms(10); //Espera 10ms
					break;
				}
				case AREA_3: //Caso área 3 então
				{
					CS_GANHO3_OFF; //Desliga o CS_GANHO3_OFF
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(0x00); //Envia 0x00 primeiramente para acessar o potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(valorad); //Envia na variável valorad para mudar a resistência do potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					CS_GANHO3_ON; //Liga o CS_GANHO3_ON para alterar o valor da resistência do potênciometro digital
					AGUARDA_Waitms(10); //Espera 10ms
					break;
				}
				case AREA_4: //Caso área 4 então
				{
					CS_GANHO4_OFF; //Desliga o CS_GANHO4_OFF
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(0x00); //Envia 0x00 primeiramente para acessar o potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(valorad); //Envia na variável valorad para mudar a resistência do potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					CS_GANHO4_ON; //Liga o CS_GANHO4_ON para alterar o valor da resistência do potênciometro digital
					AGUARDA_Waitms(10); //Espera 10ms
					break;
				}
				case AREA_5: //Caso área 5 então
				{
					CS_GANHO5_OFF; //Desliga o CS_GANHO5_OFF
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(0x00); //Envia 0x00 primeiramente para acessar o potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(valorad); //Envia na variável valorad para mudar a resistência do potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					CS_GANHO5_ON; //Liga o CS_GANHO5_ON para alterar o valor da resistência do potênciometro digital
					AGUARDA_Waitms(10); //Espera 10ms
					break;
				}
				case AREA_6: //Caso área 6 então
				{
					CS_GANHO6_OFF; //Desliga o CS_GANHO6_OFF
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(0x00); //Envia 0x00 primeiramente para acessar o potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(valorad); //Envia na variável valorad para mudar a resistência do potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					CS_GANHO6_ON; //Liga o CS_GANHO6_ON para alterar o valor da resistência do potênciometro digital
					AGUARDA_Waitms(10); //Espera 10ms
					break;
				}
				case AREA_7: //Caso área 7 então
				{
					CS_GANHO7_OFF; //Desliga o CS_GANHO7_OFF
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(0x00); //Envia 0x00 primeiramente para acessar o potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(valorad); //Envia na variável valorad para mudar a resistência do potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					CS_GANHO7_ON; //Liga o CS_GANHO7_ON para alterar o valor da resistência do potênciometro digital
					AGUARDA_Waitms(10); //Espera 10ms
					break;
				}
				case AREA_8: //Caso área 8 então
				{
					CS_GANHO8_OFF; //Desliga o CS_GANHO8_OFF
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(0x00); //Envia 0x00 primeiramente para acessar o potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					POTENCIOMETRO_DIGITAL_SendChar(valorad); //Envia na variável valorad para mudar a resistência do potenciômetro digital
					AGUARDA_Waitms(10); //Espera 10ms
					CS_GANHO8_ON; //Liga o CS_GANHO8_ON para alterar o valor da resistência do potênciometro digital
					AGUARDA_Waitms(10); //Espera 10ms
					break;
				}
				break;
			}
			break;
		}
		break;
	}
}

/*** Funções da SENHA ***/
void fnDigiteSenha(void) //Função que permite digitar a senha corretamente dentro do campo senha
{
	static byte estadoDigitaSenha = 1; //Define a variável estadoDigitaSenha para o switch case abaixo
	static byte identador = 6; //Define identador para ir posicionando o cursor nos campos de digitação da senha

	switch(estadoDigitaSenha) //Conforme variável estadoDigitaSenha vai para o case específico
	{
		case 1: //Entra para digitar a senha
		{
			SetaCaracterSenha(identador); //Função que vai deslocando o caracter no campo senha
			estadoDigitaSenha = 2; //Armazena na variável estadoDigitaSenha o valor 2 para ir para o case 2
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //Permite ir digitando a senha
		{
			if(teclapressionada == teclaCancela) //Se teclapressionada for igual a tecla CANCELA então
			{
				if(tela == TELA_DIGITE_SENHA_DA_GERENCIA) //Se tela for igual a TELA_DIGITE_SENHA_DA_GERENCIA então
				{
					tela = TELA_SENHA_DA_GERENCIA; //Tela é igual a TELA_SENHA_DA_GERENCIA
				}
				else if(tela == TELA_DIGITE_SENHA_DO_TECNICO) //Senão se tela for igual a TELA_DIGITE_SENHA_DO_TECNICO
				{
					tela = TELA_SENHA_DO_TECNICO; //Tela é igual a TELA_SENHA_DO_TECNICO
				}
				estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
				estado = ESTADO_NAVEGA_MENU; //Estado a ser executado é ESTADO_NAVEGA_MENU
				estadoDigitaSenha = 1; //Armazena na variável estadoDigitaSenha o valor 1 para ir para o primeiro nivel deste menu
				identador = 6; //Armazena na variável identador o valor 6 para se posicionar no primeiro campo da senha
				teclapressionada = 0; //Limpa teclapressionada
				ch = 0x30; //Armazena na variável ch a informação 0
				break;
			}
			if(teclapressionada == teclaConfirma || teclapressionada == teclaConfirma_Remoto) //Se teclapressionada for igual a tecla CONFIRMA então
			{
				if(teclapressionada == teclaConfirma)
				{
					DISPOSITIVO = 'P';
				}
				else if(teclapressionada == teclaConfirma_Remoto)
				{
					DISPOSITIVO = 'C';
				}
				SetaCaracterSenha(identador); //Posiciona o cursor na coluna conforme o valor do identador passado
				senha[identador - 6] = ch; //Armazena no vetor senha na posição identador-6, exemplo: se identador é 6 será senha[0]. Armazena o conteúdo de ch
				identador++; //Incrementa identador para ir para o próximo campo da senha
				COLUNA = identador; //Armazena na variável COLUNA a posição identador
				PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada acima
				ch = 0x30; //Armazena na variável ch a informação 0
				C = ch; //Armazena na variável C o conteúdo da variável ch
				teclapressionada = 0; //Limpa teclapressionada
			}
			if(teclapressionada == teclaIncrementa || teclapressionada == teclaTrava) //Se teclapressionada for igual a tecla INCREMENTA ou teclapressionada for igual a tecla TRAVA então
			{
				if(C == 0X39) //Se C for igual a 9 então
				{
					C = 0X41; //Armazena na variável C a informação A
					EscreveChar(C); //Escreve A na posição especificada
					COLUNA = identador; //Armazena na variável COLUNA a posição identador
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada acima
				}
				else if(C == 0x5A) //Senão se C for igual a Z então
				{
					C = 0x30; //Armazena na variável C a informação 0
					EscreveChar(C); //Escreve 0 na posição especificada
					COLUNA = identador; //Armazena na variável COLUNA a posição identador
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada acima
				}
				else //Senão
				{
					C++; //Incrementa C
					EscreveChar(C); //Escreve o conteúdo de C
					COLUNA = identador; //Armazena na variável COLUNA a posição identador
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada acima
				}
				ch = C; //Armazena na variável ch o conteúdo da variável C
				teclapressionada = 0; //Limpa teclapressionada
			}
			if(teclapressionada == teclaDecrementa || teclapressionada == teclaDestrava) //Se teclapressionada for igual a tecla DECREMENTA ou teclapressionada for igual a tecla DESTRAVA então
			{
				if(C == 0x30) //Se C for igual a 0 então
				{
					C = 0x5A; //Armazena na variável C a informação Z
					EscreveChar(C); //Escreve o conteúdo de C
					COLUNA = identador; //Armazena na variável COLUNA a posição identador
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada acima
				}
				else if(C == 0x41) //Se C for igual a A
				{
					C = 0x39; //Armazena na variável C a informação 9
					EscreveChar(C); //Escreve o conteúdo de C
					COLUNA = identador; //Armazena na variável COLUNA a posição identador
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada acima
				}
				else //Senão
				{
					C--; //Decrementa C
					EscreveChar(C); //Escreve o conteúdo de C
					COLUNA = identador; //Armazena na variável COLUNA a posição identador
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada acima
				}
				ch = C; //Armazena na variável ch o conteúdo da variável C
				teclapressionada = 0; //Limpa teclapressionada
			}
			if(identador >= 12) //Se identador for maior ou igual a 12 então
			{
				estadoDigitaSenha = 3; //Armazena na variável estadoDigitaSenha o valor 3 para ir para o case 3
				identador = 6; //Armazena na variável identador o valor 6 para se posicionar no primeiro campo da senha
				ch = 0x30; //Armazena na variável ch a informação 0
				break;
			}
			break;
		}
		case 3: //Verifica se a senha esta correta
		{
			static byte j; //Define a variável j para os laços for abaixo
			static byte verifica_senha; //Define a variável verifica_senha para ser utilizado nas comparações abaixo
			if(tela == TELA_DIGITE_SENHA_DA_GERENCIA) //Se tela for igual a TELA_DIGITE_SENHA_DA_GERENCIA
			{
				for(j = 0; j < 6; j++) //Verifica se a senha da gerência é igual ao que foi digitado
				{
					if(buffer_senhas[j] != senha[j]) //Se as 6 posições do vetor buffer_senhas (armazenado na memória FLASH) não for igual as 6 posições do vetor senha (digitado) então
					{
						verifica_senha = SENHA_INCORRETA; //Armazena na variável verifica_senha a informação SENHA_INCORRETA
						break;
					}
				}
				if(j == 6) //Se j for igual a 6 então
				{
					senha_de_acesso = SENHA_DA_GERENCIA; //Armazena na variável senha_de_acesso a informação SENHA_DA_GERENCIA
					OPERADOR = 'G';
					estadoDigitaSenha = 4; //Armazena na variável estadoDigitaSenha o valor 4 para ir para o case 4
					break;
				}
				else //Senão
				{
					verifica_senha = NENHUMA_DELAS; //Armazena na variável verifica_senha a informação NENHUMA_DELAS
				}
				for(j = 12; j < 18; j++) //Verifica se a senha do técnico é igual ao que foi digitado
				{
					if(buffer_senhas[j] != senha[j-12]) //Se as 6 posições do vetor buffer_senhas (armazenado na memória FLASH) não for igual as 6 posições do vetor senha (digitado) então
					{
						verifica_senha = SENHA_INCORRETA; //Armazena na variável verifica_senha a informação SENHA_INCORRETA
						break;
					}
				}
				if(j == 18) //Se j for igual a 18 então finaliza
				{
					senha_de_acesso = SENHA_DA_ENGENHARIA; //Armazena na variável senha_de_acesso a informação SENHA_DA_ENGENHARIA
					estadoDigitaSenha = 4; //Armazena na variável estadoDigitaSenha o valor 4 para ir para o case 4
					break;
				}
				if(verifica_senha == SENHA_INCORRETA) //Se verifica_senha for igual a SENHA_INCORRETA então
				{
					tela = TELA_SENHA_INCORRETA; //Tela é igual a TELA_SENHA_INCORRETA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estadoDigitaSenha = 1; //Armazena na variável estadoDigitaSenha o valor 1 para ir para o primeiro nivel deste menu
					estado = ESTADO_NAVEGA_MENU; //Estado a ser executado é ESTADO_NAVEGA_MENU
					identador = 6; //Armazena na variável identador o valor 6 para se posicionar no primeiro campo da senha
					teclapressionada = 0; //Limpa teclapressionada
				}
				break;
			}
			else if(tela == TELA_DIGITE_SENHA_DO_TECNICO) //Senão se tela for igual a TELA_DIGITE_SENHA_DO_TECNICO então
			{
				for(j = 6; j < 12; j++) //Verifica se a senha do técnico é igual ao que foi digitado
				{
					if(buffer_senhas[j] != senha[j-6]) //Se as 6 posições do vetor buffer_senhas (armazenado na memória FLASH) não for igual as 6 posições do vetor senha (digitado) então
					{
						verifica_senha = SENHA_INCORRETA; //Armazena na variável verifica_senha a informação SENHA_INCORRETA
						break;
					}
				}
				if(j == 12) //Se j for igual a 12 então
				{
					senha_de_acesso = SENHA_DO_TECNICO; //Armazena na variável senha_de_acesso a informação SENHA_DO_TECNICO
					OPERADOR = 'T';
					estadoDigitaSenha = 4; //Armazena na variável estadoDigitaSenha o valor 4 para ir para o case 4
					break;
				}
				else //Senão
				{
					verifica_senha = NENHUMA_DELAS; //Armazena na variável verifica_senha a informação NENHUMA_DELAS
				}
				for(j = 12; j < 18; j++) //Verifica se a senha do técnico é igual ao que foi digitado
				{
					if(buffer_senhas[j] != senha[j-12]) //Verifica se a senha do técnico é igual ao que foi digitado
					{
						verifica_senha = SENHA_INCORRETA; //Armazena na variável verifica_senha a informação SENHA_INCORRETA
						break;
					}
				}
				if(j == 18) //Se j for igual a 18 então
				{
					senha_de_acesso = SENHA_DA_ENGENHARIA; //Armazena na variável senha_de_acesso a informação SENHA_DA_ENGENHARIA
					estadoDigitaSenha = 4; //Armazena na variável estadoDigitaSenha o valor 4 para ir para o case 4
					break;
				}
				if(verifica_senha == SENHA_INCORRETA) //Se verifica_senha for igual a SENHA_INCORRETA então
				{
					tela = TELA_SENHA_INCORRETA; //Tela é igual a TELA_SENHA_INCORRETA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estadoDigitaSenha = 1; //Armazena na variável estadoDigitaSenha o valor 1 para ir para o primeiro nivel deste menu
					estado = ESTADO_NAVEGA_MENU; //Estado a ser executado é ESTADO_NAVEGA_MENU
					identador = 6; //Armazena na variável identador o valor 6 para se posicionar no primeiro campo da senha
					teclapressionada = 0; //Limpa teclapressionada
				}
			}
			break;
		}
		case 4: //Retorna para o menu inicial AJUSTES_BASICOS
		{
			tela = TELA_AJUSTES_BASICOS; //Tela é igual a TELA_AJUSTES_BASICOS
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estado = ESTADO_NAVEGA_MENU_FUNCOES; //Estado a ser executado é ESTADO_NAVEGA_MENU_FUNCOES
			identador = 6; //Armazena na variável identador o valor 6 para se posicionar no primeiro campo da senha
			teclapressionada = 0; //Limpa teclapressionada
			estadoDigitaSenha = 1; //Armazena na variável estadoDigitaSenha o valor 1 para ir para o primeiro nivel deste menu
			break;
		}
		break;
	}
}

void SetaCaracterSenha(byte coluna) //Função que vai deslocando o caracter no campo senha
{
	C = ch; //Armazena na variável C o conteúdo contido em ch
	LINHA = 2; //Se posiciona na linha 2
	COLUNA = coluna; //Armazena na variável COLUNA a posição identador
	PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
	EscreveChar(C); //Escreve o conteúdo de C
	PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
	delay_ms(50); //Espera 50ms
	teclapressionada = 0; //Limpa teclapressionada
}

void fnMascaraNumeroSerie(void) //Função que faz a máscara do número de série gravado com um valor numérico e cria um novo número para senha mestre
{
	  LE_FLASH_INTERNA(END_INI_PARAMETROS,8);
	  for(x = 0; x < 8;x++) //Busca na memória FLASH o número de série da placa AGATA e coloca na estrutra StcPlacas[CONST_PLACA_PAINEL].Serial_number_Flash[x] composto de 8 bytes iniciando com DT e mais 6 números
	  {
		  StcPlacas[CONST_PLACA_PAINEL].Serial_number_Flash[x] = Read_Buffer_FLASH[x];

	  }
	  if(StcPlacas[CONST_PLACA_PAINEL].Serial_number_Flash[0] != 'D') //Se StcPlacas[CONST_PLACA_PAINEL].Serial_number_Flash[0] não for igual a D então
	  {
		  for(x = 0;x < 8;x++) //Armazena nos primeiros 8 bytes da memória flash o número de série padrão DT000000 caso não tenha sido pré-gravado o número de série durante a gravação do programa na produção
		  {
			  StcPlacas[CONST_PLACA_PAINEL].Serial_number_Flash[x] = Num_Serie_Write[x];
		  }
		  ESCREVE_FLASH_INTERNA(END_INI_PARAMETROS,8,0);
	  }
	  else //Senão se já tiver sido pré-gravado o número de série durante a gravação do programa na produção então
	  {
		  for(x = 0;x < 8;x++) //Armazena nas 8 posições do vetor Num_Serie_Write o número de série gravado na memória FLASH durante a gravação do programa na produção
		  {
			  Num_Serie_Write[x] = StcPlacas[CONST_PLACA_PAINEL].Serial_number_Flash[x];
		  }
	  }

	  //Armazena na variável senha_mestre_aux o conteúdo transformado em caracteres do vetor StcPlacas[CONST_PLACA_PAINEL].Serial_number_FLASh[ ] da posição 2 a 7
	  senha_mestre_aux = (StcPlacas[CONST_PLACA_PAINEL].Serial_number_Flash[2] - 48)*100000;
	  senha_mestre_aux += (StcPlacas[CONST_PLACA_PAINEL].Serial_number_Flash[3] - 48)*10000;
	  senha_mestre_aux += (StcPlacas[CONST_PLACA_PAINEL].Serial_number_Flash[4] - 48)*1000;
	  senha_mestre_aux += (StcPlacas[CONST_PLACA_PAINEL].Serial_number_Flash[5] - 48)*100;
	  senha_mestre_aux += (StcPlacas[CONST_PLACA_PAINEL].Serial_number_Flash[6] - 48)*10;
	  senha_mestre_aux += (StcPlacas[CONST_PLACA_PAINEL].Serial_number_Flash[7] - 48);

	  senha_mestre_aux = (CONST_CHECKSUM ^ senha_mestre_aux) & 0xFFFFF; //Faz uma máscara do número de série com um valor definido em CONST_CHECKSUM

	  //Armazena no vetor de 6 posições var_senha_mestre o conteúdo da senha_mestre_aux transformada em caracteres
//	  var_senha_mestre[0] = senha_mestre_aux/100000 + 48;
//	  var_senha_mestre[1] = (senha_mestre_aux%100000)/10000 + 48;
//	  var_senha_mestre[2] = (senha_mestre_aux%10000)/1000 + 48;
//	  var_senha_mestre[3] = (senha_mestre_aux%1000)/100 + 48;
//	  var_senha_mestre[4] = (senha_mestre_aux%100)/10 + 48;
//	  var_senha_mestre[5] = senha_mestre_aux%10 + 48;
	  var_senha_mestre[0] = '9';
	  var_senha_mestre[1] = '0';
	  var_senha_mestre[2] = '9';
	  var_senha_mestre[3] = '5';
	  var_senha_mestre[4] = '2';
	  var_senha_mestre[5] = '3';
}
/******************************************************************************/




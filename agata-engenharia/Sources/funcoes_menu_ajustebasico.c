/*
 * funcoes_menu_ajustebasico.c
 *
 *  Created on: 22/06/2023
 *      Author: marcos.butignol
 */


#include "funcao.h"

#include "agata_std_functions.h"
#include "agata_hc_definitions.h"
#include "stdlib.h"


void fnAjusteManualSensibilidade(void) //Função que permite ajustar a sensibilidade manualmente área por área
{
	static byte estadoAjusteManual = 1,sensibilidade_aux; //Definindo variável estadoAjusteManual para o switch case abaixo e a variável sensibilidade_aux para salvar a última alteração caso desista da alteração pela tecla cancela

	switch(estadoAjusteManual) //Conforme variável vai para o case específico
	{
		case 1: //ENTRA NO MENU DE AJUSTE DE SENSIBILIDADE
		{
			tela = TELA_MOSTRA_SENSIBILIDADE_DAS_AREAS; //Tela é igual a TELA_MOSTRA_SENSIBILIDADE_DAS_AREAS
			estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
			estadoAjusteManual = 2; //Coloca a variável para 2 para entrar no case 2
			selecionaArea = TODAS_AREAS; //Variável selecionaArea é igual a TODAS_AREAS
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //ESCOLHE ENTRE TODAS_AREAS, AREA_1 a AREA_8
		{
			switch (teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					selecionaArea++; //Incrementa selecionaArea
					if(tipo_detector == Z3) //Se tipo_detector for igual a Z3 então
					{
						if(selecionaArea > AREA_3) //Se selecionaArea for maior que AREA_3 então
						{
							selecionaArea = TODAS_AREAS; //Variável selecionaArea é igual a TODAS_AREAS
						}
					}
					else if(tipo_detector == Z8) //Senão se tipo_detector for igual a Z8 então
					{
						if(selecionaArea > AREA_8) //Se selecionaArea for maior que AREA_8 então
						{
							selecionaArea = TODAS_AREAS; //Variável selecionaArea é igual a TODAS_AREAS
						}
					}
					tela = TELA_MOSTRA_SENSIBILIDADE_DAS_AREAS; //tela é igual a TELA_MOSTRA_SENSIBILIDADE_DAS_AREAS
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					selecionaArea--; //Decrementa selecionaArea
					if(tipo_detector == Z3) //Se tipo_detector for igual a Z3 então
					{
						if(selecionaArea == 255) //Se selecionaArea for igual a 255 então
						{
							selecionaArea = AREA_3; //selecionaArea é igual a AREA_3
						}
					}
					else if(tipo_detector == Z8) //Senão se tipo_detector for igual a Z8 então
					{
						if(selecionaArea == 255) //Se selecionaArea for igual a 255 então
						{
							selecionaArea = AREA_8; //selecionaArea é igual a AREA_8
						}
					}
					tela = TELA_MOSTRA_SENSIBILIDADE_DAS_AREAS; //tela é igual a TELA_MOSTRA_SENSIBILIDADE_DAS_AREAS
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					sensibilidade = buffer_sensibilidade[selecionaArea]; //sensibilidade é igual ao valor do conteúdo do buffer_sensibilidade[selecionaArea]
					sensibilidade_aux = sensibilidade; //sensibilidade_aux guarda valor da sensibilidade que estava a área antes de mexer
					estadoAjusteManual = 3; //Coloca a variável para 3 para entrar no case 3
					tela = TELA_DIGITE_SENSIBILIDADE_DAS_AREAS; //tela é igual a TELA_DIGITE_SENSIBILIDADE_DAS_AREAS
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					estado = ESTADO_AJUSTE_MANUAL_SENSIBILIDADE; //Estado a ser executado é ESTADO_AJUSTE_MANUAL_SENSIBILIDADE
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tela = TELA_MOSTRA_AJUSTES_BASICOS; //tela é igual a TELA_MOSTRA_AJUSTES_BASICOS
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					estado = ESTADO_AJUSTES_BASICOS; //Estado a ser executado é ESTADO_AJUSTES_BASICOS
					estadoAjusteManual = 1; //Coloca a variável estadoAjustesBasicos para 1 para voltar a camada 1 desta função
					teclapressionada = 0; //Limpa teclapressionada
					APAGA_AREAS; //Apaga as áreas
					break;
				}
				break;
			}
			break;
		}
		case 3:	//ALTERA O VALOR DA ÁREA SELECIONADA
		{
			switch (teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tela TRAVA pressionada então
				case teclaTrava:
				{
					sensibilidade++; //Incrementa sensibilidade
					LINHA = 2; //Se posiciona na LINHA 2
					COLUNA = 1; //Se posiciona na COLUNA 1
					if(sensibilidade > 100) //Se sensibilidade maior que 100 então
					{
						sensibilidade = 1; //sensibilidade é igual a 1
						EscreveLCD((telas_LCD[TELA_UM][idioma]),pos); //Escreve no LCD 001
					}
					else //Senão
					{
						LINHA = 2; //Se posiciona na LINHA 2
						COLUNA = 7; //Se posiciona na COLUNA 7
						PosicionaLCD(pos); //Posiciona o cursor do LCD conforme coordenadas acima
						EscreveChar((char)((sensibilidade%1000)/100+48)); //Escreve a centena da sensibilidade
						EscreveChar((char)((sensibilidade%100)/10+48)); //Escreve a dezena da sensibilidade
						EscreveChar((char)(sensibilidade%10+48)); //Escreve a unidade da sensibilidade
					}
					if(INCREMENTA) //Se tecla INCREMENTA pressionada. Trecho que funciona para incrementar ao ficar mantendo pressionada a tecla pressionada
					{
						delay_ms(200); //Espera 200ms para verificar se não foi ruido, passando de 200ms a tecla é reconhecida
						if(!INCREMENTA) //Se tecla INCREMENTA parou de ser pressionada antes de 200ms então limpa teclapressionada
						{
							teclapressionada = 0; //Limpa a tecla pressionada
						}
					}
					else //Senão
					{
						teclapressionada = 0; //Limpa a tecla pressionada
					}
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA e tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					sensibilidade--; //Decrementa sensibilidade
					LINHA = 2; //Se posiciona na linha 2
					COLUNA = 1; //Se posiciona na coluna 1
					if(sensibilidade < 1) //Se sensbilidade for menor que 1 então
					{
						sensibilidade = 100; //sensibilidade é igual a 100
						EscreveLCD((telas_LCD[TELA_CEM][idioma]),pos); //Escreve no LCD 100
					}
					else //Senão
					{
						LINHA = 2; //Se posiciona na linha 2
						COLUNA = 7; //Se posiciona na coluna 7
						PosicionaLCD(pos); //Posiciona o cursor do LCD conforme coordenadas acima
						EscreveChar((char)((sensibilidade%1000)/100+48)); //Escreve a centena da sensibilidade
						EscreveChar((char)((sensibilidade%100)/10+48)); //Escreve a dezena da sensibilidade
						EscreveChar((char)(sensibilidade%10+48)); //Escreve a unidade da sensibilidade
					}
					if(DECREMENTA) //Se tecla DECREMENTA pressionada. Trecho que funciona para decrementar ao ficar mantendo a tecla pressionada
					{
						delay_ms(200); //Espera 200ms para verificar se não foi ruido, passando de 200ms a tecla é reconhecida
						if(!DECREMENTA) //Se tecla DECREMENTA parou de ser pressionada antes de 200ms então limpa teclapressionada
						{
							teclapressionada = 0; //Limpa a teclapressionada
						}
					}
					else //Senão
					{
						teclapressionada = 0; //Limpa a tecla pressionada
					}
					break;
				}
				case teclaConfirma: //Se tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					if(selecionaArea == TODAS_AREAS) //Se selecionaArea for igual a TODAS_AREAS então
					{
						for(x = 0;x < 9;x++) //Insere o valor da sensibilidade para todas as áreas
						{
							buffer_sensibilidade[x] = sensibilidade;
						}
						Write_Buffer_FLASH[0] = buffer_sensibilidade[AREA_1]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração da sensibilidade
						Write_Buffer_FLASH[1] = buffer_sensibilidade[AREA_2]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração da sensibilidade
						Write_Buffer_FLASH[2] = buffer_sensibilidade[AREA_3]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração da sensibilidade
						Write_Buffer_FLASH[3] = buffer_sensibilidade[AREA_4]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração da sensibilidade
						Write_Buffer_FLASH[4] = buffer_sensibilidade[AREA_5]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração da sensibilidade
						Write_Buffer_FLASH[5] = buffer_sensibilidade[AREA_6]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração da sensibilidade
						Write_Buffer_FLASH[6] = buffer_sensibilidade[AREA_7]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração da sensibilidade
						Write_Buffer_FLASH[7] = buffer_sensibilidade[AREA_8]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração da sensibilidade
						ESCREVE_FLASH_INTERNA(endFLASHSensibilidadeArea1,8,0); //Escreve os valores de sensibilidade das áreas na memória FLASH no endereço especificado
						fnGravaAuditoria(90,sensibilidade_aux,sensibilidade,OPERADOR,DISPOSITIVO);
					}
					else //Senão
					{
						buffer_sensibilidade[selecionaArea] = sensibilidade; //Guarda na área selecionada o valor da sensibilidade alterada
						Write_Buffer_FLASH[0] = buffer_sensibilidade[selecionaArea]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração da sensibilidade
						ESCREVE_FLASH_INTERNA((endFLASHSensibilidadeArea1 + (selecionaArea - 1)),1,0); //Escreve o valor da sensibilidade da área selecionada no endereço especificado
						fnGravaAuditoria((90 + selecionaArea),sensibilidade_aux,sensibilidade,OPERADOR,DISPOSITIVO);
					}
					tela = TELA_MOSTRA_SENSIBILIDADE_DAS_AREAS; //Tela é igual a TELA_MOSTRA_SENSIBILIDADE_DAS_AREAS
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					estado = ESTADO_AJUSTE_MANUAL_SENSIBILIDADE; //Estado a ser executado é ESTADO_AJUSTE_MANUAL_SENSIBILIDADE
					estadoAjusteManual = 2; //Coloca a variável para 2 para voltar ao estado de escolha de qual área alterar
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressiondas então
				{
					tela = TELA_MOSTRA_SENSIBILIDADE_DAS_AREAS; //tela é igual a TELA_MOSTRA_SENSIBILIDADE_DAS_AREAS
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					estado = ESTADO_AJUSTE_MANUAL_SENSIBILIDADE; //Estado a ser executado é ESTADO_AJUSTE_MANUAL_SENSIBILIDADE
					estadoAjusteManual = 2; //Coloca a variável para 2 para voltar ao estado de escolha de qual área alterar
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
void fnAjusteAutomaticoSensibilidade(void) //Função que permite ajustar automaticamente a sensibilidade de todas as áreas
{
	static word aux_Valor[8];

	for(x = 1;x < 8;x++)
	{
		aux_Valor[x] = 0;
	}

	for(w = 1;w <= 8;w++)
	{
		APAGA_AREAS;
		area_de_amostragem = w;
		selecionaArea = w;
		LENDO_AREAS = FALSE; //Torna a flag LENDO_AREAS para FALSE para poder fazer a leitura do AD das áreas
		for(x = 0;x < 4;x++) //Zera o vetor valor_amostragem
		{
			valor_amostragem[x] = 0;
		}
		for(x = 0;x < 2;x++) //Realiza duas amostras do objeto amostrado passando pelo detector de metais na área 5 e fazendo uma média das 3 amostras
		{
			tempo_amostragem = 0; //tempo_amostragem é igual a zero
			estado_LCD = ESTADO_ESPERA; //Coloca o LCD em estado de espera para não atualizar mensagens

			tela = TELA_AGUARDE; //Tela é igual a TELA_AGUARDE
			Atualiza_LCD(); //Atualiza LCD com a mensagem acima

			while(tempo_amostragem < 20);

			if(tempo_amostragem >= 20) //Se tempo_amostragem for maior ou igual a 2 segundos e o sinal sonoro parar neste momento deve-se passar a amostra pelo detector de metais
			{
				tela = TELA_PASSAR_OBJETO_NA; //Tela é igual a TELA_PASSE_AMOSTRA
				Atualiza_LCD(); //Atualiza LCD com a mensagem acima
			}

			while(tempo_amostragem < 40);

			TocaTomBuzzer();
			delay_ms(100);

			tela = TELA_MOSTRA_SENSIBILIDADE_DAS_AREAS;

			if(area_de_amostragem == AREA_1)
			{
				selecionaArea = AREA_1;
			}
			else if(area_de_amostragem == AREA_2)
			{
				selecionaArea = AREA_2;
			}
			else if(area_de_amostragem == AREA_3)
			{
				selecionaArea = AREA_3;
			}
			else if(area_de_amostragem == AREA_4)
			{
				selecionaArea = AREA_4;
			}
			else if(area_de_amostragem == AREA_5)
			{
				selecionaArea = AREA_5;
			}
			else if(area_de_amostragem == AREA_6)
			{
				selecionaArea = AREA_6;
			}
			else if(area_de_amostragem == AREA_7)
			{
				selecionaArea = AREA_7;
			}
			else if(area_de_amostragem == AREA_8)
			{
				selecionaArea = AREA_8;
			}
			Atualiza_LCD();

			while(tempo_amostragem < 90) //Enquanto tempo_amostragem for maior ou igual a 2 segundos e menor que 7 segundos fica amostrando o sinal
			{
				if(FlagADC == 1) //Se FlagADC for 1 significa que o valor foi amostrado no AD das áreas
				{
					if(Valor[area_de_amostragem-1] >= NIVEL_ZERO) //Se Valor[area_de_amostragem] for maior que o NIVEL_ZERO então
					{
						Valor[area_de_amostragem-1] = Valor[area_de_amostragem-1] - NIVEL_ZERO; //Corrige para apresentar o valor positivo
					}
					else //Senão
					{
						Valor[area_de_amostragem-1] = NIVEL_ZERO - Valor[area_de_amostragem-1]; //Corrige para apresentar o valor positivo
					}

					if (Valor[area_de_amostragem-1] > valor_amostragem[x]) //Se Valor[area_de_amostragem] for maior que o valor de amostragem anterior
					{
						valor_amostragem[x] = Valor[area_de_amostragem-1]; //valor_amostragem[x] recebe o valor do AD recebido em Valor[area_de_amostragem]
						LINHA = 2; //Se posiciona na linha 2
						/*** Trecho para escrever corretamente o valor lido do AD na área 5 e apresentar no LCD ***/
						if(valor_amostragem[x] < 10)
						{
							COLUNA = 8;
							PosicionaLCD(pos);
							EscreveChar((char)(valor_amostragem[x] + 48));
						}
						else if(valor_amostragem[x] < 100)
						{
							COLUNA = 8;
							PosicionaLCD(pos);
							EscreveChar((char)(valor_amostragem[x]/10 + 48));
							EscreveChar((char)(valor_amostragem[x]%10 + 48));
						}
						else if(valor_amostragem[x] < 1000)
						{
							COLUNA = 7;
							PosicionaLCD(pos);
							EscreveChar((char)((valor_amostragem[x]/100) + 48));
							EscreveChar((char)((valor_amostragem[x]%100)/10 + 48));
							EscreveChar((char)((valor_amostragem[x]%10)+ 48));
						}
						else if(valor_amostragem[x] < 10000)
						{
							COLUNA = 7;
							PosicionaLCD(pos);
							EscreveChar((char)((valor_amostragem[x]/1000) + 48));
							EscreveChar((char)(((valor_amostragem[x]%1000)/100) + 48));
							EscreveChar((char)(((valor_amostragem[x]%100)/10) + 48));
							EscreveChar((char)((valor_amostragem[x]%10) + 48));
						}
						else if(valor_amostragem[x] < 100000)
						{
							COLUNA = 6;
							PosicionaLCD(pos);
							EscreveChar((char)((valor_amostragem[x]/10000) + 48));
							EscreveChar((char)(((valor_amostragem[x]%10000)/1000) + 48));
							EscreveChar((char)(((valor_amostragem[x]%1000)/100) + 48));
							EscreveChar((char)(((valor_amostragem[x]%100)/10) + 48));
							EscreveChar((char)((valor_amostragem[x]%10) + 48));
						}
						else if(valor_amostragem[x] < 1000000)
						{
							COLUNA = 6;
							PosicionaLCD(pos);
							EscreveChar((char)((valor_amostragem[x]/100000) + 48));
							EscreveChar((char)(((valor_amostragem[x]%100000)/10000) + 48));
							EscreveChar((char)(((valor_amostragem[x]%10000)/1000) + 48));
							EscreveChar((char)(((valor_amostragem[x]%1000)/100) + 48));
							EscreveChar((char)(((valor_amostragem[x]%100)/10) + 48));
							EscreveChar((char)((valor_amostragem[x]%10) + 48));
						}
						else if(valor_amostragem[x] < 10000000)
						{
							COLUNA = 5;
							PosicionaLCD(pos);
							EscreveChar((char)((valor_amostragem[x]/1000000) + 48));
							EscreveChar((char)(((valor_amostragem[x]%1000000)/100000) + 48));
							EscreveChar((char)(((valor_amostragem[x]%100000)/10000) + 48));
							EscreveChar((char)(((valor_amostragem[x]%10000)/1000) + 48));
							EscreveChar((char)(((valor_amostragem[x]%1000)/100) + 48));
							EscreveChar((char)(((valor_amostragem[x]%100)/10) + 48));
							EscreveChar((char)((valor_amostragem[x]%10) + 48));
						}
						else if(valor_amostragem[x] < 100000000)
						{
							COLUNA = 5;
							PosicionaLCD(pos);
							EscreveChar((char)((valor_amostragem[x]/10000000) + 48));
							EscreveChar((char)(((valor_amostragem[x]%10000000)/1000000) + 48));
							EscreveChar((char)(((valor_amostragem[x]%1000000)/100000) + 48));
							EscreveChar((char)(((valor_amostragem[x]%100000)/10000) + 48));
							EscreveChar((char)(((valor_amostragem[x]%10000)/1000) + 48));
							EscreveChar((char)(((valor_amostragem[x]%1000)/100) + 48));
							EscreveChar((char)(((valor_amostragem[x]%100)/10) + 48));
							EscreveChar((char)((valor_amostragem[x]%10) + 48));
						}
						else if(valor_amostragem[x] < 1000000000)
						{
							COLUNA = 4;
							PosicionaLCD(pos);
							EscreveChar((char)((valor_amostragem[x]/100000000) + 48));
							EscreveChar((char)(((valor_amostragem[x]%100000000)/10000000) + 48));
							EscreveChar((char)(((valor_amostragem[x]%10000000)/1000000) + 48));
							EscreveChar((char)(((valor_amostragem[x]%1000000)/100000) + 48));
							EscreveChar((char)(((valor_amostragem[x]%100000)/10000) + 48));
							EscreveChar((char)(((valor_amostragem[x]%10000)/1000) + 48));
							EscreveChar((char)(((valor_amostragem[x]%1000)/100) + 48));
							EscreveChar((char)(((valor_amostragem[x]%100)/10) + 48));
							EscreveChar((char)((valor_amostragem[x]%10) + 48));
						}
						else if(valor_amostragem[x] < 10000000000)
						{
							COLUNA = 4;
							PosicionaLCD(pos);
							EscreveChar((char)((valor_amostragem[x]/1000000000) + 48));
							EscreveChar((char)(((valor_amostragem[x]%1000000000)/100000000) + 48));
							EscreveChar((char)(((valor_amostragem[x]%100000000)/10000000) + 48));
							EscreveChar((char)(((valor_amostragem[x]%10000000)/1000000) + 48));
							EscreveChar((char)(((valor_amostragem[x]%1000000)/100000) + 48));
							EscreveChar((char)(((valor_amostragem[x]%100000)/10000) + 48));
							EscreveChar((char)(((valor_amostragem[x]%10000)/1000) + 48));
							EscreveChar((char)(((valor_amostragem[x]%1000)/100) + 48));
							EscreveChar((char)(((valor_amostragem[x]%100)/10) + 48));
							EscreveChar((char)((valor_amostragem[x]%10) + 48));
						}
					}
					FlagADC = 0; //Zera a FlagADC para permitir novas leituras do AD
					LENDO_AREAS = FALSE; //Torna a flag LENDO_AREAS para FALSE para permitir novas leituras do AD
				}
				delay_ms(1); //Espera 1 milisegundo apenas
			}
			if (valor_amostragem[x] <= 5000)
			{
				ERRO_AUTOCALIBRACAO = SIM;
				x = 2;
				w = 9;
			}
		}

		/******************************************************************************/
		/* Das 2 amostragens pegar o menor valor porque este é o mais difícel de      */
		/* detectar, portanto a sensibilidade deve ser maior no pior caso             */
		/******************************************************************************/
		if(ERRO_AUTOCALIBRACAO == NAO)
		{
			for(x = 0;x < 2;x++)
			{
				//Guarda o valor da primeira amostra e compara com as 3 amostras, guarda o valor da segunta amostra e compara com as 3 amostras e assim por diante.
				z = 0;
				for(y = 0;y < 2;y++) //Este loop compara a amostra armazenada em auxiliar contra todas as amostras
				{
					if(valor_amostragem[x] <= valor_amostragem[y])
					{
						z++;
					}
				}
				if(z == 2) //Se z = 3 significa que esta é a amostra escolhida porque deu 3 vezes menor que as outras
				{
					valor_amostragem[2] = valor_amostragem[x];
				}
			}
		}
		/**************************************************************************/

		sensibilidade = (byte)((NIVEL_ZERO * 101 - valor_amostragem[2] * 100) / NIVEL_ZERO); //Cálculo da sensibilidade a ser armazenado em todas as áreas conforme autocalibração automática

		aux_Valor[area_de_amostragem-1] = sensibilidade;

		TocaTomBuzzer();
		delay_ms(1000);
		TocaTomBuzzer();
		delay_ms(1000);
	}

	APAGA_AREAS;

	if(ERRO_AUTOCALIBRACAO == NAO)
	{
		for(x = 1;x < 8;x++)
		{
			buffer_sensibilidade[x] = aux_Valor[x-1]; //Armazena o valor da sensibilidade acima calculado para todas as áreas e já salva no vetor responsável pela gravação dos dados na memória FLASH do microcontrolador
			Write_Buffer_FLASH[x-1] = aux_Valor[x-1];
		}

		ESCREVE_FLASH_INTERNA((endFLASHSensibilidadeArea1),8,0); //Escreve na memória FLASH no endereço especificado o valor de todas as áreas
	}
	else if(ERRO_AUTOCALIBRACAO == SIM)
	{
		tela = TELA_ERRO_AUTOCALIBRACAO;
		Atualiza_LCD();
		delay_ms(2000);
	}


    tela = TELA_AJUSTE_AUTOMATICO_DA_SENSIBILIDADE; //Tela é igual a TELA_AJUSTE_AUTOMATICO_DA_SENSIBILIDADE
    estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
    estado = ESTADO_AJUSTES_BASICOS; //Estado a ser executado é ESTADO_AJUSTES_BASICOS
    flagretorno = 1; //Torna a flagretorno para 1 para ao retornar voltar a função AJUSTE AUTOMATICO DE SENSIBILIDADE
}



void fnModoTravamento(void) ////Função para escolher entre modo de somente destrava ou modo trava e destrava
{
	static byte estadoModoTravamento = 1,modo_travamento_aux; //Definindo variável estadoModoTravamento para o switch case abaixo e a variável modo_travamento_aux para salvar a última alteração caso desista da alteração pela tecla cancela

	switch(estadoModoTravamento) //Conforme variável vai para o case específico
	{
		case 1: //ENTRA NO MENU MODO DE TRAVAMENTO
		{
			tela = TELA_MOSTRA_MODO_DE_TRAVAMENTO; //Tela é igual a TELA_MOSTRA_MODO_DE_TRAVAMENTO
			estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
			estadoModoTravamento = 2; //Coloca a variável para 2 para entrar no case 2
			modo_travamento_aux = modo_travamento; //Armazena em modo_travamento_aux o último valor do modo_travamento sem alterar para recuperar quando cancela
			teclapressionada = 0; //Limpa a teclapressionada
			break;
		}
		case 2: //ESCOLHE ENTRE AS OPÇÕES SOMENTE_DESTRAVA ou TRAVA_DESTRAVA
		{
			switch (teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					modo_travamento++; //Incrementa modo_travamento
					if(modo_travamento > TRAVA_DESTRAVA) //Se modo_travamento for maior que TRAVA_DESTRAVA então
					{
						modo_travamento = SOMENTE_DESTRAVA; //Armazena em modo_travamento o valor SOMENTE_DESTRAVA
					}
					tela = TELA_MOSTRA_MODO_DE_TRAVAMENTO; //Tela é igual a TELA_MOSTRA_MODO_DE_TRAVAMENTO
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					modo_travamento--; //Decrementa modo_travamento
					if(modo_travamento < SOMENTE_DESTRAVA) //Se modo_travamento for menor que SOMENTE_DESTRAVA então
					{
						modo_travamento = TRAVA_DESTRAVA; //Armazena em modo_travamento o valor TRAVA_DESTRAVA
					}
					tela = TELA_MOSTRA_MODO_DE_TRAVAMENTO; //Tela é igual a TELA_MOSTRA_MODO_DE_TRAVAMENTO
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					tela = TELA_MODO_DE_TRAVAMENTO; //Tela é igual a TELA_MODO_DE_TRAVAMENTO
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					estado = ESTADO_AJUSTES_BASICOS; //Estado a ser executado é ESTADO_AJUSTES_BASICOS
					estadoModoTravamento = 1; //Coloca a variável estadoModoTravamento para 1 para voltar a camada 1 desta função
					flagretorno = 1; //Torna a flagretorno para 1 para ao retornar voltar a função MODO DE TRAVAMENTO
					teclapressionada = 0; //Limpa a teclapressionada
					Write_Buffer_FLASH[0] = modo_travamento; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração do modo_travamento
					ESCREVE_FLASH_INTERNA(endFLASHModoTravamento,1,0); //Escreve o valor modo_travamento na memória FLASH no endereço especificado
					fnGravaAuditoria(1,modo_travamento_aux,modo_travamento,OPERADOR,DISPOSITIVO);
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					modo_travamento = modo_travamento_aux; //Variável modo_travamento recupera o último valor armazenado em modo_travamento_aux
					tela = TELA_MODO_DE_TRAVAMENTO; //Tela é igual a TELA_MODO_DE_TRAVAMENTO
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					estado = ESTADO_AJUSTES_BASICOS; //Estado a ser executado é ESTADO_AJUSTES_BASICOS
					estadoModoTravamento = 1; //Coloca a variável estadoModoTravamento para 1 para voltar a camada 1 desta função
					flagretorno = 1; //Torna a flagretorno para 1 para ao retornar voltar a função MODO DE TRAVAMENTO
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
/******************************************************************************/
void fnSorteadorEletronico(void)
{
	static byte estadofnSorteadorEletronico = 1,sorteador_aux; //Define variável estadofnSorteadorEletronico para o switch case abaixo e sorteador_aux para armazenar o último valor de sorteador e poder recuperar caso tenha sido alterado e pressionar NAO para abortar alteração

	switch(estadofnSorteadorEletronico) //Conforme variável vai para o case específico
	{
		case 1: //ENTRA NO MENU PARA CONFIRMAR SE SIM OU NAO PARA SORTEADOR
		{
			tela = TELA_INICIAR_SORTEADOR; //Tela é igual a TELA_INICIAR_SORTEADOR
			estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
			estadofnSorteadorEletronico = 2; //Coloca variável em 2 para poder ir para o case 2 quando voltar da rotina principal
			sorteador_aux = sorteador; //Armazena na variável temporária sorteador_aux o último valor do sorteador sem alteração
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //ALTERA O SORTEADOR PARA SIM OU NAO
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaDecrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaDestrava:
				{
					sorteador = SIM; //Define sorteador como SIM
					LINHA = 2; //Especifica posição da linha
					COLUNA = 2; //Especifica posição da coluna
					PosicionaLCD(pos); //Posiciona realmente na linha e coluna especificada
					EscreveChar(' '); //Escreve espaço em branco
					LINHA = 2; //Especifica posição da linha
					COLUNA = 15; //Especifica posição da coluna
					PosicionaLCD(pos); //Posiciona realmente na linha e coluna especificada
					EscreveChar('X'); //Escreve X
					teclapressionada = 0; //Limpa a tecla pressionada
					break;
				}
				case teclaIncrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaTrava:
				{
					sorteador = NAO; //Define sorteador como NAO
					LINHA = 2; //Especifica posição da linha
					COLUNA = 2; //Especifica posição da coluna
					PosicionaLCD(pos); //Posiciona realmente na linha e coluna especificada
					EscreveChar('X'); //Escreve X
					LINHA = 2; //Especifica posição da linha
					COLUNA = 15; //Especifica posição da coluna
					PosicionaLCD(pos); //Posiciona realmente na linha e coluna especificada
					EscreveChar(' '); //Escreve espaço em branco
					teclapressionada = 0; //Limpa a tecla pressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					if(sorteador == SIM) //Se sorteador é SIM então
					{
						tela = TELA_QUANTIDADE_SORTEADOS; //Tela é igual a TELA_SORTEADOR_ELETRONICO
						estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
						estado = ESTADO_QUANTIDADE_SORTEADOS; //Estado a ser executado é ESTADO_QUANTIDADE_SORTEADOS
						estadofnSorteadorEletronico = 1; //Coloca a variável estadofnSorteadorEletronico para 1 para voltar a camada 1 desta função
						teclapressionada = 0; //Limpa teclapressionada
						flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU SORTEADOR ELETRONICO no primeiro nível
						Write_Buffer_FLASH[0] = sorteador; //Coloca sorteador no vetor para gravação na memória FLASH
						ESCREVE_FLASH_INTERNA(endFLASHSorteador,1,0); //Escreve na memória FLASH a variável quantidade_sorteados no endereço especificado
						//fnGravaAuditoria(3,selecao_metais_aux,selecao_metais,OPERADOR,DISPOSITIVO);
					}
					else //Se sorteador é NAO então
					{
						tela = TELA_SORTEADOR_ELETRONICO; //Tela é igual a TELA_SORTEADOR_ELETRONICO
						estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
						estado = ESTADO_AJUSTES_BASICOS; //Estado a ser executado é ESTADO_AJUSTES_BASICOS
						estadofnSorteadorEletronico = 1; //Coloca a variável estadofnSorteadorEletronico para 1 para voltar a camada 1 desta função
						teclapressionada = 0; //Limpa teclapressionada
						flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU SORTEADOR ELETRONICO no primeiro nível
						Write_Buffer_FLASH[0] = sorteador; //Coloca sorteador no vetor para gravação na memória FLASH
						ESCREVE_FLASH_INTERNA(endFLASHSorteador,1,0); //Escreve na memória FLASH a variável quantidade_sorteados no endereço especificado
					}
					break;
				}
				case teclaCancela:
				{
					tela = TELA_SORTEADOR_ELETRONICO; //Tela é igual a TELA_SORTEADOR_ELETRONICO
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					estado = ESTADO_AJUSTES_BASICOS; //Estado a ser executado é ESTADO_AJUSTES_BASICOS
					estadofnSorteadorEletronico = 1; //Coloca a variável estadofnSorteadorEletronico para 1 para voltar a camada 1 desta função
					sorteador = sorteador_aux; //Retorno o último valor do quantidade_sorteados antes de entrar no menu de alteração
					teclapressionada = 0; //Limpa teclapressionada
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU SELEÇÃO DE METAIS no primeiro nível
					break;
				}
				break;
			}
			break;
		}
		break;
	}
}

void fnQuantidadeSorteados(void) //Permite escolher o percentual de sorteados entre 10 e 255
{
	static byte estadofnQuantidadeSorteados = 1,quantidade_sorteados_aux; //Definindo variável estadofnPercentualSorteados para o switch case abaixo e percentual_sorteados_aux para armazenar o último valor de percentual_sorteados e poder recuperar caso tenha sido alterado e pressionar cancela para abortar alteração

	switch(estadofnQuantidadeSorteados) //Conforme variável vai para o case específico
	{
		case 1: //ENTRA NO MENU PARA ALTERAR O PERCENTUAL DE SORTEADOS
		{
			tela = TELA_MOSTRA_QUANTIDADE_SORTEADOS; //Tela é igual a TELA_MOSTRA_QUANTIDADE_SORTEADOS
			estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
			estadofnQuantidadeSorteados = 2; //Coloca variável em 2 para poder ir para o case 2 quando voltar da rotina principal
			quantidade_sorteados_aux = quantidade_sorteados; //Armazena na variável temporária quantidade_sorteados_aux o último valor da quantidade_sorteados sem alteração
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //ALTERA A QUANTIDADE DE SORTEADOS
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					quantidade_sorteados++; //Incrementa quantidade de sorteados
					if(quantidade_sorteados > 255) //Se percentual_sorteados for maior que 255 então
					{
						quantidade_sorteados = 10; //quantidade_sorteados é igual a 10
					}
					if(INCREMENTA) //Se tecla INCREMENTA pressionada. Trecho que funciona para incrementar ao ficar mantendo pressionada a tecla pressionada
					{
						delay_ms(200); //Espera 200ms para verificar se não foi ruido, passando de 200ms a tecla é reconhecida
						if(!INCREMENTA) //Se tecla INCREMENTA parou de ser pressionada antes de 200ms então limpa teclapressionada
						{
							teclapressionada = 0; //Limpa a tecla pressionada
						}
					}
					else //Senão
					{
						teclapressionada = 0; //Limpa a tecla pressionada
					}
					tela = TELA_MOSTRA_QUANTIDADE_SORTEADOS; //Tela é igual a TELA_MOSTRA_QUANTIDADE_SORTEADOS
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					quantidade_sorteados--; //Decrementa quantidade_sorteados
					if(quantidade_sorteados < 10) //Se quantidade_sorteados for menor que 10 então
					{
						quantidade_sorteados = 255; //quantidade_sorteados é igual a 255
					}
					if(DECREMENTA) //Se tecla DECREMENTA pressionada. Trecho que funciona para incrementar ao ficar mantendo pressionada a tecla pressionada
						{
							delay_ms(200); //Espera 200ms para verificar se não foi ruido, passando de 200ms a tecla é reconhecida
							if(!DECREMENTA) //Se tecla DECREMENTA parou de ser pressionada antes de 200ms então limpa teclapressionada
							{
								teclapressionada = 0; //Limpa a tecla pressionada
							}
						}
						else //Senão
						{
							teclapressionada = 0; //Limpa a tecla pressionada
						}
					tela = TELA_MOSTRA_QUANTIDADE_SORTEADOS; //Tela é igual a TELA_MOSTRA_QUANTIDADE_SORTEADOS
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					tela = TELA_SORTEADOR_ELETRONICO; //Tela é igual a TELA_SORTEADOR_ELETRONICO
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					estado = ESTADO_AJUSTES_BASICOS; //Estado a ser executado é ESTADO_AJUSTES_BASICOS
					estadofnQuantidadeSorteados = 1; //Coloca a variável estadoQuantidadeSorteados para 1 para voltar a camada 1 desta função
					teclapressionada = 0; //Limpa teclapressionada
					Write_Buffer_FLASH[0] = quantidade_sorteados; //Coloca a quantidade_sorteados no vetor para gravação na memória FLASH
					ESCREVE_FLASH_INTERNA(endFLASHQuantidadeSorteados,1,0); //Escreve na memória FLASH a quantidade_sorteados no endereço especificado
					//fnGravaAuditoria(3,selecao_metais_aux,selecao_metais,OPERADOR,DISPOSITIVO);
					fnSortearNumero(); //Função que sorteia o número sorteado
					sorteou = FALSE;
					break;
				}
				case teclaCancela:
				{
					tela = TELA_SORTEADOR_ELETRONICO; //Tela é igual a TELA_SORTEADOR_ELETRONICO
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					estado = ESTADO_AJUSTES_BASICOS; //Estado a ser executado é ESTADO_AJUSTES_BASICOS
					estadofnQuantidadeSorteados = 1; //Coloca a variável estadoQuantidadeSorteados para 1 para voltar a camada 1 desta função
					quantidade_sorteados = quantidade_sorteados_aux; //Retorno o último valor da quantidade_sorteados antes de entrar no menu de alteração
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

void fnSortearNumero(void)
{
	numero_sorteado = 1 + (rand() %quantidade_sorteados); //Sorteia um número dentro da quantidade de sorteados especificada

	cont_sorteador = 0; //Zera o contador que compara com o número sorteado
}

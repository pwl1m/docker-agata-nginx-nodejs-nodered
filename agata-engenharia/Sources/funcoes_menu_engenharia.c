/*
 * funcoes_menu_engenharia.c
 *
 *  Created on: 23/06/2023
 *      Author: marcos.butignol
 */



#include "funcao.h"

#include "agata_std_functions.h"
#include "agata_hc_definitions.h"
#include "stdlib.h"


// FUNCOES RX TX


/*** Funções do MENU AJUSTES TX RX ***/
void fnAjustesTXRX(void) //Permite escolher entre as funções abaixo
{
	static byte estadoAjustesTXRX = 1; //Definindo variável estadoAjustesTXRX para o switch case abaixo

	switch(estadoAjustesTXRX) //Conforme valor da variável estadoAjustesTXRX vai para o case específico
	{
		case 1: //ENTRA NO MENU DE AJUSTES TX_RX
		{
			tela = TELA_MOSTRA_AJUSTES_TX_RX; //Tela é igual a TELA_MOSTRA_AJUSTES_TX_RX
			estadoAjustesTXRX = 2; //Coloca a variável estadoAjustesTXRX para 2 para ir para o case 2
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			if(!flagretorno) //Se flagretorno for igual a zero então
			{
				menu = 1; //Armazena na variável menu o valor 1
			}
			flagretorno = 0; //Zera a flag retorno
			break;
		}
		case 2: //ESCOLHE DENTRE UM DOS TRÊS MENUS DE AJUSTES TX_RX
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					menu++; //Incrementa menu
					if(menu > 3) //Se menu for maior que 3 então
					{
						menu = 1; //Armazena na variável menu o valor 1
					}
					tela = TELA_MOSTRA_AJUSTES_TX_RX; //Tela é igual a TELA_MOSTRA_AJUSTES_TX_RX
					estado_LCD = ATUALIZA_LCD;  //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					menu--; //Decrementa menu
					if(menu < 1) //Se menu for menor que 1 então
					{
						menu = 3;  //Armazena na variável menu o valor 3
					}
					tela = TELA_MOSTRA_AJUSTES_TX_RX; //Tela é igual a TELA_MOSTRA_AJUSTES_TX_RX
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					if(menu == 1) //Se menu for igual a 1 então
					{
						estado = ESTADO_CONFIGURA_CICLO_TRABALHO; //Estao a ser executado é ESTADO_CONFIGURA_CICLO_TRABALHO
					}
					else if(menu == 2) //Senão se menu for igual a 2 então
					{
						estado = ESTADO_CONFIGURA_DEFASAGEM; //EStado a ser executado é ESTADO_CONFIGURA_DEFASAGEM
					}
					else if(menu == 3) //Senão se menu for igual a 3 então
					{
						estado = ESTADO_CONFIGURA_FREQUENCIA; //Estado a ser executado é ESTADO_CONFIGURA_FREQUENCIA
					}
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estadoAjustesTXRX = 1; //Coloca a variável estadoAjustesTXRX para 1 para ir para o primeiro nivel deste menu
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tela = TELA_AJUSTES_TX_RX; //Tela é igual a TELA_AJUSTES_TX_RX
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estadoAjustesTXRX = 1; //Coloca a variável estadoAjustesTXRX para 1 para ir para o primeiro nivel deste menu
					estado = ESTADO_NAVEGA_MENU_FUNCOES; //Estado a ser executado é ESTADO_NAVEGA_MENU_FUNCOES
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



void fnCicloTrabalho(void)  //Permite alterar o ciclo de trabalho do PWM da TX de 1% a 100%
{
	static byte estadoCicloTrabalho = 1; //Definindo variável estadoAjustesTXRX para o switch case abaixo
	static byte ciclo_de_trabalho_aux = 0; //Define a variável ciclo_de_trabalho_aux para armazenar o valor do ciclo de trabalho antes de ser alterado

	switch(estadoCicloTrabalho) //Conforme valor da variável estadoCicloTrabalho vai para o case específico
	{
		case 1: //ENTRA NO MENU CICLO DE TRABALHO
		{
			ciclo_de_trabalho_aux = ciclo_de_trabalho; //Armazena na variável ciclo_de_trabalho_aux o valor da variável ciclo_de_trabalho antes de ser alterado
			tela = TELA_DIGITE_CICLO_DE_TRABALHO; //Tela é igual a TELA_DIGITE_CICLO_DE_TRABALHO
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estadoCicloTrabalho = 2; //Coloca a variável estadoCicloTrabalho para 2 para ir para o case 2
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //ALTERA O CICLO DE TRABALHO
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					LINHA = 2; //Se posiciona na linha 2
					COLUNA = 8; //Se posiciona na coluna 8
					ciclo_de_trabalho++; //Incrementa ciclo de trabalho
					if(ciclo_de_trabalho > 99) //Se ciclo de trabalho for maior que 99 então
					{
						ciclo_de_trabalho = 1; //Armazena na variável ciclo de trabalho o valor 1
					}
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
					EscreveChar((char)(ciclo_de_trabalho/10 + 48)); //Escreve a parte da dezena da variável ciclo_de_trabalho
					EscreveChar((char)(ciclo_de_trabalho%10 + 48)); //Escreve a parte da unidade da variável ciclo_de_trabalho
					SetDutyCycle_TX(ciclo_de_trabalho); //Função que ajusta o ciclo de trabalho do PWM da TX
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
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					LINHA = 2; //Se posiciona na linha 2
					COLUNA = 8; //Se posiciona na coluna 8
					ciclo_de_trabalho--; //Decrementa ciclo_de_trabalho
					if(ciclo_de_trabalho < 1) //Se ciclo_de_trabalho for menor que 1 então
					{
						ciclo_de_trabalho = 99; //Armazena na variável ciclo_de_trabalho o valor 99
					}
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
					EscreveChar((char)(ciclo_de_trabalho/10 + 48)); //Escreve a parte da dezena da variável ciclo_de_trabalho
					EscreveChar((char)(ciclo_de_trabalho%10 + 48)); //Escreve a parte da unidade da variável ciclo_de_trabalho
					SetDutyCycle_TX(ciclo_de_trabalho); //Função que ajusta o ciclo de trabalho do PWM da TX
					if(DECREMENTA) //Se tecla INCREMENTA pressionada. Trecho que funciona para incrementar ao ficar mantendo pressionada a tecla pressionada
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
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					Write_Buffer_FLASH[0] = ciclo_de_trabalho; //Armazena o valor de ciclo de trabalho no vetor para gravação na memória FLASH
					ESCREVE_FLASH_INTERNA(endFLASHCicloTrabalho,1,0); //Escreve na memória FLASH a variável ciclo_de_trabalho alterado no endereço especificado
					estadoCicloTrabalho = 1; //Coloca a variável estadoCicloTrabalho para 1 para ir para o primeiro nivel deste menu
					tela = TELA_MOSTRA_AJUSTES_TX_RX; //Tela é igual a TELA_MOSTRA_AJUSTES_TX_RX
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_AJUSTES_TX_RX; //Estado a ser executado é ESTADO_AJUSTES_TX_TX
					teclapressionada = 0; //Limpa teclapressionada
					flagretorno = 1;  //Torna a flag flag_retorno para 1 para poder retornar ao MENU AJUSTES TX_RX no primeiro nível
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					ciclo_de_trabalho = ciclo_de_trabalho_aux; //Armazena na variável ciclo_de_trabalho o valor de ciclo_de_trabalho antes de entrar neste menu para alterar, ou seja, recupa o valor caso seja pressionada a tecla CANCELA
					SetDutyCycle_TX(ciclo_de_trabalho); //Função que ajusta o ciclo de trabalho do PWM da TX
					estadoCicloTrabalho = 1; //Coloca a variável estadoCicloTrabalho para 1 para ir para o primeiro nivel deste menu
					tela = TELA_MOSTRA_AJUSTES_TX_RX; //Tela é igual a TELA_MOSTRA_AJUSTES_TX_RX
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_AJUSTES_TX_RX; //Estado a ser executado é ESTADO_AJUSTES_TX_TX
					teclapressionada = 0; //Limpa teclapressionada
					flagretorno = 1;  //Torna a flag flag_retorno para 1 para poder retornar ao MENU AJUSTES TX_RX no primeiro nível
					break;
				}
				break;
			}
			break;
		}
		break;
	}
}

void fnDefasagem(void) //Função que altera a defasagem do sinal
{
	static byte estadoDefasagem = 1; //Definindo variável estadoDefasagem para o switch case abaixo
	static word defasagem_aux = 0; //Define a variável defasagem_aux para armazenar o valor do ciclo de trabalho antes de ser alterado

	switch(estadoDefasagem) //Conforme valor da variável estadoCicloTrabalho vai para o case específico
	{
		case 1: //ENTRA NO MENU DA DEFASAGEM
		{
			defasagem_aux = defasagem; //Define a variável defasagem_aux para armazenar o valor da defasagem antes de ser alterado
			tela = TELA_DIGITE_DEFASAGEM; //Tela é igual a TELA_DIGITE_DEFASAGEM
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estadoDefasagem = 2; //Coloca a variável estadoDefasagem para 2 para ir para o case 2
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //ALTERA A DEFASAGEM
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					LINHA = 2; //Se posiciona na linha 2
					COLUNA = 7; //Se posiciona na coluna 7
					defasagem++; //Incrementa a defasagem
					if(defasagem > 360) //Se defasagem for maior que 360 então
					{
						defasagem = 1; //Armazena na variável defasagem o valor 1
					}
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
					EscreveChar((char)(defasagem/100 + 48)); //Escreve a parte da centena da variável defasagem
					EscreveChar((char)(((defasagem%100)/10) + 48)); //Escreve a parte da dezena da variável defasagem
					EscreveChar((char)(defasagem%10 + 48)); //Escreve a parte da unidade da variável defasagem
					SetFrequencia(frequencia); //Função que altera a defasagem do sinal
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
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla TRAVA pressionada então
				case teclaDestrava:
				{
					LINHA = 2; //Se posiciona na linha 2
					COLUNA = 7; //Se posiciona na coluna 7
					defasagem--; //Decrementa defasagem
					if(defasagem < 1) //Se defasagem for menor que 1 então
					{
						defasagem = 360; //Armazena na variável defasagem o valor 360
					}
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
					EscreveChar((char)(defasagem/100 + 48)); //Escreve a parte da centena da variável defasagem
					EscreveChar((char)(((defasagem%100)/10) + 48)); //Escreve a parte da dezena da variável defasagem
					EscreveChar((char)(defasagem%10 + 48)); //Escreve a parte da unidade da variável defasagem
					SetFrequencia(frequencia); //Função que altera a defasagem do sinal
					if(DECREMENTA) //Se tecla INCREMENTA pressionada. Trecho que funciona para incrementar ao ficar mantendo pressionada a tecla pressionada
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
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					Write_Buffer_FLASH[0] = (byte)(defasagem >> 8); //Armazena o valor do byte alto de defasagem no vetor para gravação na memória FLASH
					Write_Buffer_FLASH[1] = (byte)(defasagem); //Armazena o valor do byte baixo de defasagem no vetor para gravação na memória FLASH
					ESCREVE_FLASH_INTERNA(endFLASHDefasagem,2,0); //Escreve na memória FLASH a variável defasagem alterada no endereço especificado
					estadoDefasagem = 1; //Coloca a variável estadoDefasagem para 1 para ir para o primeiro nivel deste menu
					tela = TELA_MOSTRA_AJUSTES_TX_RX; //Tela é igual a TELA_MOSTRA_AJUSTES_TX_RX
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_AJUSTES_TX_RX; //Estado a ser executado é ESTADO_AJUSTES_TX_RX
					teclapressionada = 0; //Limpa teclapressionada
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU AJUSTES TX_RX no primeiro nível
					break;
				}
				case teclaCancela:
				{
					defasagem = defasagem_aux; //Armazena na variável defasagem o valor de defasagem antes da defasagem ser alterada
					SetFrequencia(frequencia); //Função que altera a defasagem do sinal
					tela = TELA_MOSTRA_AJUSTES_TX_RX; //Tela é igual a TELA_MOSTRA_AJUSTES_TX_RX
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_AJUSTES_TX_RX; //Estado a ser executado é ESTADO_AJUSTES_TX_RX
					estadoDefasagem = 1; //Coloca a variável estadoDefasagem para 1 para ir para o primeiro nivel deste menu
					teclapressionada = 0; //Limpa teclapressionada
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU AJUSTES TX_RX no primeiro nível
					break;
				}
				break;
			}
			break;
		}
		break;
	}
}

void fnFrequencia(void) //Função que altera a frequência do sinal
{
	static byte estadoFrequencia = 1; //Definindo variável estadoFrequencia para o switch case abaixo
	static word frequencia_aux = 0; //Define a variável frequencia_aux para armazenar o valor da frequência antes de ser alterado

	switch(estadoFrequencia) //Conforme valor da variável estadoFrequencia vai para o case específico
	{
		case 1: //ENTRA NO MENU FREQUÊNCIA
		{
			frequencia_aux = frequencia; //Define a variável frequencia_aux para armazenar o valor da frequência antes de ser alterado
			tela = TELA_DIGITE_FREQUENCIA; //Tela é igual a TELA_DIGITE_FREQUENCIA
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estadoFrequencia = 2; //Coloca a variável estadoFrequencia para 2 para ir para o case 2
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2:
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					LINHA = 2; //Se posiciona na linha 2
					frequencia += 10; //Incrementa frequência 10 unidades
					if(frequencia > 65000) //Se frequência for maior que 65000 então
					{
						frequencia = 2000; //Armazena na variável frequencia o valor 2000
					}
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
					if(frequencia < 10000) //Se frequência for menor que 10000 então
					{
						COLUNA = 6; //Se posiciona na coluna 6
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
						EscreveChar(' '); //Escreve espaço
						EscreveChar((char)(frequencia/1000 + 48)); //Escreve a parte do unidade do milhar da variável frequencia
						EscreveChar((char)(((frequencia%1000)/100) + 48)); //Escreve a parte da centena da variável frequencia
						EscreveChar((char)(((frequencia%100)/10) + 48)); //Escreve a parte da dezena da variável frequencia
						EscreveChar((char)(frequencia%10 + 48)); //Escreve a parte da unidade da variável frequencia
					}
					else //Senão
					{
						COLUNA = 6; //Se posiciona na coluna 6
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
						EscreveChar((char)(frequencia/10000 + 48)); //Escreve a parte da dezena do milhar da variável frequencia
						EscreveChar((char)(((frequencia%10000)/1000) + 48)); //Escreve a parte da unidade do milhar da variável frequencia
						EscreveChar((char)(((frequencia%1000)/100) + 48)); //Escreve a parte da centena da variável frequencia
						EscreveChar((char)(((frequencia%100)/10) + 48)); //Escreve a parte da dezena da variável frequencia
						EscreveChar((char)(frequencia%10 + 48)); //Escreve a parte da unidade da variável frequencia
					}
					SetFrequencia(frequencia); //Função que altera a frequência do sinal
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
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					LINHA = 2; //Se posiciona na linha 2
					frequencia -= 10; //Decrementa frequência 10 unidades
					if(frequencia < 2000) //Se frequencia for menor que 2000
					{
						frequencia = 65000; //Armazena na variável frequencia o valor 65000
					}
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
					if(frequencia < 10000) //Se frequencia for menor que 1000 então
					{
						COLUNA = 6; //Se posiciona na coluna 6
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
						EscreveChar(' '); //Escreve espaço
						EscreveChar((char)(frequencia/1000 + 48)); //Escreve a parte do unidade do milhar da variável frequencia
						EscreveChar((char)(((frequencia%1000)/100) + 48)); //Escreve a parte da centena da variável frequencia
						EscreveChar((char)(((frequencia%100)/10) + 48)); //Escreve a parte da dezena da variável frequencia
						EscreveChar((char)(frequencia%10 + 48)); //Escreve a parte da unidade da variável frequencia
					}
					else
					{
						COLUNA = 6; //Se posiciona na coluna 6
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
						EscreveChar((char)(frequencia/10000 + 48)); //Escreve a parte da dezena do milhar da variável frequencia
						EscreveChar((char)(((frequencia%10000)/1000) + 48)); //Escreve a parte da unidade do milhar da variável frequencia
						EscreveChar((char)(((frequencia%1000)/100) + 48)); //Escreve a parte da centena da variável frequencia
						EscreveChar((char)(((frequencia%100)/10) + 48)); //Escreve a parte da dezena da variável frequencia
						EscreveChar((char)(frequencia%10 + 48)); //Escreve a parte da unidade da variável frequencia
					}
					SetFrequencia(frequencia); //Função que altera a frequência do sinal
					if(DECREMENTA) //Se tecla INCREMENTA pressionada. Trecho que funciona para incrementar ao ficar mantendo pressionada a tecla pressionada
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
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					Write_Buffer_FLASH[0] = (byte)(frequencia >> 8); //Armazena o valor do byte alto da frequencia no vetor para gravação na memória FLASH
					Write_Buffer_FLASH[1] = (byte)(frequencia); //Armazena o valor do byte baixo da frequencia no vetor para gravação na memória FLASH
					ESCREVE_FLASH_INTERNA(endFLASHFrequencia,2,0); //Escreve na memória FLASH a variável frequencia alterada no endereço especificado
					tela = TELA_MOSTRA_AJUSTES_TX_RX; //Tela é igual a TELA_MOSTRA_AJUSTES_TX_RX
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_AJUSTES_TX_RX; //Estado a ser executado é ESTADO_AJUSTES_TX_RX
					estadoFrequencia = 1; //Coloca a variável estadoFrequencia para 1 para ir para o primeiro nivel deste menu
					teclapressionada = 0; //Limpa teclapressionada
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU AJUSTES TX_RX no primeiro nível
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					frequencia = frequencia_aux; //Armazena na variável frequencia o valor da frequencia antes da frequencia ser alterada
					SetFrequencia(frequencia); //Função que altera a frequência do sinal
					tela = TELA_MOSTRA_AJUSTES_TX_RX; //Tela é igual a TELA_MOSTRA_AJUSTES_TX_RX
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_AJUSTES_TX_RX; //Estado a ser executado é ESTADO_AJUSTES_TX_RX
					estadoFrequencia = 1; //Coloca a variável estadoFrequencia para 1 para ir para o primeiro nivel deste menu
					teclapressionada = 0; //Limpa teclapressionada
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU AJUSTES TX_RX no primeiro nível
					break;
				}
				break;
			}
			break;
		}
		break;
	}
}


void fnModeloAntena(void) //Permite escolher o modelo de antena a ser utilizado
{
	static byte estadoModeloAntena = 1; //Definindo variável estadoModeloAntena para o switch case abaixo
	static byte modelo_antena_aux = 0; //Define a variável modelo_antena_aux para armazenar o valor de modelo_antena antes de ser alterado

	switch(estadoModeloAntena) //Conforme valor da variável estadoModeloAntena vai para o case específico
	{
		case 1: //ENTRA NO MENU MODELO DE ANTENA
		{
			modelo_antena_aux = modelo_antena; //Define a variável modelo_antena_aux para armazenar o valor de modelo_antena antes de ser alterado
			tela = TELA_MOSTRA_MODELO_DE_ANTENA; //Tela é igual a TELA_MOSTRA_MODELO_DE_ANTENA
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estadoModeloAntena = 2; //Coloca a variável estadoModeloAntena para 2 para ir para o case 2
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //ALTERA O MODELO DE ANTENA
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					modelo_antena++; //Incrementa modelo_antena
					if(modelo_antena > PORTAL_750_BLINDADO) //Se modelo_antena for maior que CIL_IECO_2100 então
					{
						modelo_antena = PLANA_ONIX_2000; //Armazena na variável modelo_antena a informação PLANA_ONIX_2000
					}
					tela = TELA_MOSTRA_MODELO_DE_ANTENA; //Tela é igual a TELA_MOSTRA_MODELO_DE_ANTENA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					modelo_antena--; //Decrementa modelo_antena
					if(modelo_antena == 255) //Se modelo_antena for igual a 255 então
					{
						modelo_antena = PORTAL_750_BLINDADO; //Armazena na variável modelo_antena a informação CIL_IECO_2100
					}
					tela = TELA_MOSTRA_MODELO_DE_ANTENA; //Tela é igual a TELA_MOSTRA_MODELO_DE_ANTENA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					perfil = modelo_antena;
					Write_Buffer_FLASH[0] = modelo_antena;
					ESCREVE_FLASH_INTERNA(endFLASHPerfil,1,0);
					ESCREVE_FLASH_INTERNA(endFLASHModeloAntena,1,0);
					fnAtualizaPerfil(SETA_PARAMETRO_ON,SETA_PWM_ON,SETA_GRAVA_FLASH_ON,SETA_POT_GANHO_ON); //Atualiza informações de sinal, defasagem, frequência e ganho conforme perfil escolhido
					tela = TELA_MODELO_DE_ANTENA; //Tela é igual a TELA_MODELO_DE_ANTENA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_NAVEGA_MENU_FUNCOES; //Estado a ser executado é ESTADO_NAVEGA_MENU_FUNCOES
					estadoModeloAntena = 1; //Coloca a variável estadoModeloAntena para 1 para ir para o primeiro nivel deste menu
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					modelo_antena = modelo_antena_aux; //Armazena na variável modelo_antena o valor de modelo_antena antes de modelo_antena ser alterada
					tela = TELA_MODELO_DE_ANTENA; //Tela é igual a TELA_MODELO_DE_ANTENA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_NAVEGA_MENU_FUNCOES; //Estado a ser executado é ESTADO_NAVEGA_MENU_FUNCOES
					estadoModeloAntena = 1; //Coloca a variável estadoModeloAntena para 1 para ir para o primeiro nivel deste menu
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

void fnPotenciometrodeGanho(void) //Permite ajustar o ganho de sinal das áreas 1 a área 8
{
	static byte estadoPotGanho = 1; //Definindo variável estadoPotGanho para o switch case abaixo
	//Define as variáveis abaixo para armazenarem os valores de ganho das áreas antes de entrarem no menu para alterações
	static byte ganho_aux_todas_areas,ganho_aux_area1,ganho_aux_area2,ganho_aux_area3,ganho_aux_area4,ganho_aux_area5,ganho_aux_area6,ganho_aux_area7,ganho_aux_area8;

	switch(estadoPotGanho) //Conforme valor da variável estadoPotGanho vai para o case específico
	{
		case 1: //ENTRA NO MENU POTENCIOMETRO DE GANHO
		{
			//Armazena nas variáveis abaixo os ganhos das áreas antes de entrarem no menu para alterações
			ganho_aux_todas_areas = buffer_ganho[0];
			ganho_aux_area1 = buffer_ganho[1];
			ganho_aux_area2 = buffer_ganho[2];
			ganho_aux_area3 = buffer_ganho[3];
			ganho_aux_area4 = buffer_ganho[4];
			ganho_aux_area5 = buffer_ganho[5];
			ganho_aux_area6 = buffer_ganho[6];
			ganho_aux_area7 = buffer_ganho[7];
			ganho_aux_area8 = buffer_ganho[8];
			tela = TELA_MOSTRA_POTENCIOMETRO_DE_GANHO; //Tela é igual a TELA_MOSTRA_POTENCIOMETRO_DE_GANHO
			estadoPotGanho = 2; //Coloca a variável estadoPotGanho para 2 para ir para o case 2
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			selecionaArea = 0; //Armazena na variável selecionaArea o valor 0 que reprenten TODAS_AS_AREAS
			break;
		}
		case 2: //SELECIONA UMA DAS ÁREAS PARA ALTERAR OU TODAS AO MESMO TEMPO
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					selecionaArea++; //Incrementa selecionaArea
					if(tipo_detector == Z3) //Se tipo_detector for igual a Z3 então
					{
						if(selecionaArea > 3) //Se selecionaArea for maior que 3 então
						{
							selecionaArea = 0; //Armazena na variável selecionaArea o valor zero
						}
					}
					else if(tipo_detector == Z8) //Senão se tipo_detector for igual a Z8 então
					{
						if(selecionaArea > 8) //Se selecionaArea for maior que 8 então
						{
							selecionaArea = 0; //Armazena na variável selecionaArea o valor zero
						}
					}
					tela = TELA_MOSTRA_POTENCIOMETRO_DE_GANHO; //Tela é igual a TELA_MOSTRA_POTENCIOMETRO_DE_GANHO
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
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
							selecionaArea = 3; //Armazena na variável selecionaArea o valor 8
						}
					}
					else if(tipo_detector == Z8) //Senão se tipo_detector for igual a Z8 então
					{
						if(selecionaArea == 255) //Se selecionaArea for igual a 255 então
						{
							selecionaArea = 8; //Armazena na variável selecionaArea o valor 8
						}
					}
					tela = TELA_MOSTRA_POTENCIOMETRO_DE_GANHO; //Tela é igual a TELA_MOSTRA_POTENCIOMETRO_DE_GANHO
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					tela = TELA_DIGITE_POTENCIOMETRO_DE_GANHO; //Tela é igual a TELA_DIGITE_POTENCIOMETRO_DE_GANHO
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estadoPotGanho = 3;	//Coloca a variável estadoPotGanho para 3 para ir para o case 3
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tela = TELA_POTENCIOMETRO_DE_GANHO; //Tela é igual a TELA_POTENCIOMETRO_DE_GANHO
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estadoPotGanho = 1;	//Coloca a variável estadoPotGanho para 1 para ir para o primeiro nivel deste menu
					estado = ESTADO_AJUSTES_AVANCADOS; //Estado a ser executado é ESTADO_AJUSTES_AVANCADOS
					teclapressionada = 0; //Limpa teclapressionada
					flagretorno = 1;
					break;
				}
				break;
			}
			break;
		}
		case 3: //ALTERA O GANHO DO POTENCIOMETRO DIGITAL DA AREA SELECIONADA
		{
			switch (teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					buffer_ganho[selecionaArea]++; //Incrementa o valor do ganho da área selecionada
					LINHA = 2; //Se posiciona na linha 2
					COLUNA = 1; //Se posiciona na coluna 1
					if(buffer_ganho[selecionaArea] > 127) //Se o valor do ganho da área selecionada for maior que 127 então
					{
						buffer_ganho[selecionaArea] = 1; //Armazena o valor 1 no ganho da área selecionada
						EscreveLCD((telas_LCD[TELA_UM][idioma]),pos); //Escreve 001 no lcd
					}
					else //Senão
					{
						LINHA = 2; //Se posiciona na linha 2
						COLUNA = 7; //Se posiciona na coluna 7
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
						EscreveChar((char)((buffer_ganho[selecionaArea]%1000)/100+48)); //Escreve a parte da centena da variável ganho da área selecionada
						EscreveChar((char)((buffer_ganho[selecionaArea]%100)/10+48)); //Escreve a parte da dezena da variável ganho da área selecionada
						EscreveChar((char)(buffer_ganho[selecionaArea]%10+48)); //Escreve a parte da unidade da variável ganho da área selecionada
					}
					fnEnviaSPI(POT_GANHO,selecionaArea,buffer_ganho[selecionaArea]); //Permite enviar a configuração para alterar o valor de ganho da área selecionada
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					buffer_ganho[selecionaArea]--; //Decrementa o valor do ganho da área selecionada
					LINHA = 2; //Se posiciona na linha 2
					COLUNA = 1; //Se posiciona na coluna 1
					if(buffer_ganho[selecionaArea] < 1) //Se o valor do ganho da área selecionada for menor que 1 então
					{
						buffer_ganho[selecionaArea] = 127; //Armazena o valor 127 no ganho da área selecionada
						EscreveLCD((telas_LCD[TELA_CENTO_E_VINTE_E_SETE][idioma]),pos); //Escreve 127 no lcd
					}
					else //Senão
					{
						LINHA = 2; //Se posiciona na linha 2
						COLUNA = 7; //Se posiciona na coluna 7
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
						EscreveChar((char)((buffer_ganho[selecionaArea]%1000)/100+48)); //Escreve a parte da centena da variável ganho da área selecionada
						EscreveChar((char)((buffer_ganho[selecionaArea]%100)/10+48)); //Escreve a parte da dezena da variável ganho da área selecionada
						EscreveChar((char)(buffer_ganho[selecionaArea]%10+48)); //Escreve a parte da unidade da variável ganho da área selecionada
					}
					fnEnviaSPI(POT_GANHO,selecionaArea,buffer_ganho[selecionaArea]); //Permite enviar a configuração para alterar o valor de ganho da área selecionada
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					if(selecionaArea == TODAS_AREAS) //Se selecionaArea for igual a TODAS_AREAS então
					{
						for(x = 1;x < 9;x++) //Armazena o mesmo valor de ganho para todas as áreas
						{
							buffer_ganho[x] = buffer_ganho[TODAS_AREAS];
						}
					}
					//Escreve o valor de ganho de cada área nos vetores para gravação na memória FLASH
					Write_Buffer_FLASH[0] = buffer_ganho[AREA_1];
					Write_Buffer_FLASH[1] = buffer_ganho[AREA_2];
					Write_Buffer_FLASH[2] = buffer_ganho[AREA_3];
					Write_Buffer_FLASH[3] = buffer_ganho[AREA_4];
					Write_Buffer_FLASH[4] = buffer_ganho[AREA_5];
					Write_Buffer_FLASH[5] = buffer_ganho[AREA_6];
					Write_Buffer_FLASH[6] = buffer_ganho[AREA_7];
					Write_Buffer_FLASH[7] = buffer_ganho[AREA_8];
					ESCREVE_FLASH_INTERNA(endFLASHPotenciometroGanhoArea1,8,0); //Escreve na memória FLASH os ganhos dos potenciometros alterados no endereço especificado
					tela = TELA_MOSTRA_POTENCIOMETRO_DE_GANHO; //Tela é igual a TELA_MOSTRA_POTENCIOMENTRO_DE_GANHO
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estadoPotGanho = 2; //Coloca a variável estadoPotGanho para 2 para ir para o case 2
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					//Armazena no buffer de ganho os valores dos ganhos de cada área antes de entrar no menu para alterar
					buffer_ganho[0] = ganho_aux_todas_areas;
					buffer_ganho[1] = ganho_aux_area1;
					buffer_ganho[2] = ganho_aux_area2;
					buffer_ganho[3] = ganho_aux_area3;
					buffer_ganho[4] = ganho_aux_area4;
					buffer_ganho[5] = ganho_aux_area5;
					buffer_ganho[6] = ganho_aux_area6;
					buffer_ganho[7] = ganho_aux_area7;
					buffer_ganho[8] = ganho_aux_area8;
					//Configura cada potenciometro digital de cada área com o ganho especifico
					fnEnviaSPI(POT_GANHO,1,buffer_ganho[1]);
					fnEnviaSPI(POT_GANHO,2,buffer_ganho[2]);
					fnEnviaSPI(POT_GANHO,3,buffer_ganho[3]);
					fnEnviaSPI(POT_GANHO,4,buffer_ganho[4]);
					fnEnviaSPI(POT_GANHO,5,buffer_ganho[5]);
					fnEnviaSPI(POT_GANHO,6,buffer_ganho[6]);
					fnEnviaSPI(POT_GANHO,7,buffer_ganho[7]);
					fnEnviaSPI(POT_GANHO,8,buffer_ganho[8]);
					tela = TELA_MOSTRA_POTENCIOMETRO_DE_GANHO; //Tela é igual a TELA_MOSTRA_POTENCIOMENTRO_DE_GANHO
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estadoPotGanho = 2; //Coloca a variável estadoPotGanho para 2 para ir para o case 2
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

void fnPotenciometrodeSelecaodeMetais(void) //Permite ajustar a seleção de metais da área 1 a área 8
{

	static byte estadoPotSelecao = 1; //Definindo variável estadoPotSelecao para o switch case abaixo
	//Define as variáveis abaixo para armazenarem os valores de seleção de metais das áreas antes de entrarem no menu para alterações
	static byte selecao_aux_todas_areas,selecao_aux_area1,selecao_aux_area2,selecao_aux_area3,selecao_aux_area4,selecao_aux_area5,selecao_aux_area6,selecao_aux_area7,selecao_aux_area8;

	switch(estadoPotSelecao) //Conforme valor da variável estadoPotSelecao vai para o case específico
	{
		case 1: //ENTRA NO MENU POTENCIOMETRO DE SELECAO DE METAIS
		{
			//Armazena nas variáveis abaixo as seleções de metais das áreas antes de entrarem no menu para alterações
			selecao_aux_todas_areas = buffer_selecao[0];
			selecao_aux_area1 = buffer_selecao[1];
			selecao_aux_area2 = buffer_selecao[2];
			selecao_aux_area3 = buffer_selecao[3];
			selecao_aux_area4 = buffer_selecao[4];
			selecao_aux_area5 = buffer_selecao[5];
			selecao_aux_area6 = buffer_selecao[6];
			selecao_aux_area7 = buffer_selecao[7];
			selecao_aux_area8 = buffer_selecao[8];
			tela = TELA_MOSTRA_POTENCIOMETRO_DE_SELECAO_DE_METAIS; //Tela é igual a TELA_MOSTRA_POTENCIOMETRO_DE_SELECAO_DE_METAIS
			estadoPotSelecao = 2; //Coloca a variável estadoPotSelecao para 2 para ir para o case 2
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			selecionaArea = 0; //Armazena na variável selecionaArea o valor zero
			break;
		}
		case 2: //SELECIONA UMA DAS ÁREAS PARA ALTERAR OU TODAS AO MESMO TEMPO
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					selecionaArea++; //Incrementa selecionaArea
					if(tipo_detector == Z3) //Se tipo_detector for igual a Z3 então
					{
						if(selecionaArea > 3) //Se selecionaArea for maior que 3 então
						{
							selecionaArea = 0; //Armazena na variável selecionaArea o valor zero
						}
					}
					else if(tipo_detector == Z8) //Senão se tipo_detector for igual a Z8 então
					{
						if(selecionaArea > 8) //Se selecionaArea for maior que 8 então
						{
							selecionaArea = 0; //Armazena na variável selecionaArea o valor zero
						}
					}
					tela = TELA_MOSTRA_POTENCIOMETRO_DE_SELECAO_DE_METAIS; //Tela é igual a TELA_MOSTRA_POTENCIOMETRO_DE_SELECAO_DE_METAIS
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
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
							selecionaArea = 3; //Armazena na variável selecionaArea o valor 3
						}
					}
					else if(tipo_detector == Z8) //Senão se tipo_detector for igual a Z8 então
					{
						if(selecionaArea == 255) //Se selecionaArea for igual a 255 então
						{
							selecionaArea = 8; //Armazena na variável selecionaArea o valor 8
						}
					}
					tela = TELA_MOSTRA_POTENCIOMETRO_DE_SELECAO_DE_METAIS; //Tela é igual a TELA_MOSTRA_POTENCIOMETRO_DE_SELECAO_DE_METAIS
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					tela = TELA_DIGITE_POTENCIOMETRO_DE_SELECAO_DE_METAIS; //Tela é igual a TELA_DIGITE_POTENCIOMETRO_DE_SELECAO_DE_METAIS
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estadoPotSelecao = 3; //Coloca a variável estadoPotSelecao para 3 para ir para o case 3
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tela = TELA_POTENCIOMETRO_DE_SELECAO_DE_METAIS; //Tela é igual a TELA_POTENCIOMETRO_DE_SELECAO_DE_METAIS
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estadoPotSelecao = 1;  //Coloca a variável estadoPotSelecao para 1 para ir para o primeiro nivel deste menu
					estado = ESTADO_NAVEGA_MENU_FUNCOES; //Estado a ser executado é ESTADO_NAVEGA_MENU_FUNCOES
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				break;
			}
			break;
		}
		case 3: //ALTERA O GANHO DO POTENCIOMETRO DE SELEÇÃO DE METAIS DA AREA SELECIONADA
		{
			switch (teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					buffer_selecao[selecionaArea]++; //Incrementa o valor da seleção de metais da área selecionada
					LINHA = 2; //Se posiciona na linha 2
					COLUNA = 1; //Se posiciona na coluna 1
					if(buffer_selecao[selecionaArea] > 127) //Se o valor da seleção de metais da área selecionada for maior que 127 então
					{
						buffer_selecao[selecionaArea] = 1; //Armazena o valor 1 na seleção de metais da área selecionada
						EscreveLCD((telas_LCD[TELA_UM][idioma]),pos); //Escreve 001 no lcd
					}
					else //Senão
					{
						LINHA = 2; //Se posiciona na linha 2
						COLUNA = 7; //Se posiciona na coluna 7
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
						EscreveChar((char)((buffer_selecao[selecionaArea]%1000)/100+48)); //Escreve a parte da centena da variável seleção de metais da área selecionada
						EscreveChar((char)((buffer_selecao[selecionaArea]%100)/10+48)); //Escreve a parte da dezena da variável seleção de metais da área selecionada
						EscreveChar((char)(buffer_selecao[selecionaArea]%10+48)); //Escreve a parte da unidade da variável seleção de metais da área selecionada
					}
					fnEnviaSPI(POT_DEFASAGEM,selecionaArea,buffer_selecao[selecionaArea]); //Permite enviar a configuração para alterar o valor da seleção de metais da área selecionada
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa:  //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					buffer_selecao[selecionaArea]--; //Decrementa o valor da seleção de metais da área selecionada
					LINHA = 2; //Se posiciona na linha 2
					COLUNA = 1; //Se posiciona na coluna 1
					if(buffer_selecao[selecionaArea] < 1) //Se o valor da seleção de metais da área selecionada for menor que 1 então
					{
						buffer_selecao[selecionaArea] = 127; //Armazena o valor 127 na seleção de metais da área selecionada
						EscreveLCD((telas_LCD[TELA_CENTO_E_VINTE_E_SETE][idioma]),pos); //Escreve 127 no lcd
					}
					else //Senão
					{
						LINHA = 2; //Se posiciona na linha 2
						COLUNA = 7; //Se posiciona na coluna 7
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
						EscreveChar((char)((buffer_selecao[selecionaArea]%1000)/100+48)); //Escreve a parte da centena da variável seleção de metais da área selecionada
						EscreveChar((char)((buffer_selecao[selecionaArea]%100)/10+48)); //Escreve a parte da dezena da variável seleção de metais da área selecionada
						EscreveChar((char)(buffer_selecao[selecionaArea]%10+48)); //Escreve a parte da unidade da variável seleção de metais da área selecionada
					}
					fnEnviaSPI(POT_DEFASAGEM,selecionaArea,buffer_selecao[selecionaArea]); //Permite enviar a configuração para alterar o valor da seleção de metais da área selecionada
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					if(selecionaArea == TODAS_AREAS) //Se selecionaArea for igual a TODAS_AREAS
					{
						for(x = 1;x < 9;x++)
						{
							buffer_selecao[x] = buffer_selecao[TODAS_AREAS]; //Armazena o mesmo valor de seleção de metais para todas as áreas
						}
					}
					//Escreve o valor de seleção de metais de cada área nos vetores para gravação na memória FLASH
					Write_Buffer_FLASH[0] = buffer_selecao[AREA_1];
					Write_Buffer_FLASH[1] = buffer_selecao[AREA_2];
					Write_Buffer_FLASH[2] = buffer_selecao[AREA_3];
					Write_Buffer_FLASH[3] = buffer_selecao[AREA_4];
					Write_Buffer_FLASH[4] = buffer_selecao[AREA_5];
					Write_Buffer_FLASH[5] = buffer_selecao[AREA_6];
					Write_Buffer_FLASH[6] = buffer_selecao[AREA_7];
					Write_Buffer_FLASH[7] = buffer_selecao[AREA_8];
					ESCREVE_FLASH_INTERNA(endFLASHPotenciometroSelecaoArea1,8,0); //Escreve na memória FLASH as seleções de metais dos potenciometros alterados no endereço especificado
					tela = TELA_MOSTRA_POTENCIOMETRO_DE_SELECAO_DE_METAIS; //Tela é igual a TELA_MOSTRA_POTENCIOMETRO_DE_SELECAO_DE_METAIS
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estadoPotSelecao = 2; //Coloca a variável estadoPotSelecao para 2 para ir para o case 2
					teclapressionada = 0; //Limpa a teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					//Armazena no buffer de seleção de metais os valores das seleções de metais de cada área antes de entrar no menu para alterar
					buffer_selecao[0] = selecao_aux_todas_areas;
					buffer_selecao[1] = selecao_aux_area1;
					buffer_selecao[2] = selecao_aux_area2;
					buffer_selecao[3] = selecao_aux_area3;
					buffer_selecao[4] = selecao_aux_area4;
					buffer_selecao[5] = selecao_aux_area5;
					buffer_selecao[6] = selecao_aux_area6;
					buffer_selecao[7] = selecao_aux_area7;
					buffer_selecao[8] = selecao_aux_area8;
					//Configura cada potenciometro digital de cada área com a seleção de metais especifica
					fnEnviaSPI(POT_DEFASAGEM,1,buffer_selecao[1]);
					fnEnviaSPI(POT_DEFASAGEM,2,buffer_selecao[2]);
					fnEnviaSPI(POT_DEFASAGEM,3,buffer_selecao[3]);
					fnEnviaSPI(POT_DEFASAGEM,4,buffer_selecao[4]);
					fnEnviaSPI(POT_DEFASAGEM,5,buffer_selecao[5]);
					fnEnviaSPI(POT_DEFASAGEM,6,buffer_selecao[6]);
					fnEnviaSPI(POT_DEFASAGEM,7,buffer_selecao[7]);
					fnEnviaSPI(POT_DEFASAGEM,8,buffer_selecao[8]);
					tela = TELA_MOSTRA_POTENCIOMETRO_DE_SELECAO_DE_METAIS; //Tela é igual a TELA_MOSTRA_POTENCIOMETRO_DE_SELECAO_DE_METAIS
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estadoPotSelecao = 2; //Coloca a variável estadoPotSelecao para 2 para ir para o case 2
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

void fnTipoDetector(void)
{
	static byte estadoTipoDetector = 1; //Definindo variável estadoTipoDetector para o switch case abaixo
	static byte tipo_detector_aux = 0; //Define a variável tipo_detector_aux para armazenar o valor de modelo_antena antes de ser alterado

	switch(estadoTipoDetector) //Conforme valor da variável estadoTipoDetector vai para o case específico
	{
		case 1: //ENTRA NO MENU TIPO DE DETECTOR
		{
			tipo_detector_aux = tipo_detector; //Define a variável tipo_detector_aux para armazenar o valor do tipo de detector antes de ser alterado
			tela = TELA_MOSTRA_TIPO_DETECTOR; //Tela é igual a TELA_MOSTRA_TIPO_DETECTOR
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estadoTipoDetector = 2; //Coloca a variável estadoTipoDetector para 2 para ir para o case 2
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //ALTERA O TIPO DE DETECTOR
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					tipo_detector++; //Incrementa modelo_antena
					if(tipo_detector > Z8)
					{
						tipo_detector = Z3;
					}
					tela = TELA_MOSTRA_TIPO_DETECTOR; //Tela é igual a TELA_MOSTRA_TIPO_DETECTOR
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					tipo_detector--; //Decrementa modelo_antena
					if(tipo_detector < Z3)
					{
						tipo_detector = Z8;
					}
					tela = TELA_MOSTRA_TIPO_DETECTOR; //Tela é igual a TELA_MOSTRA_MODELO_DE_ANTENA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					for(x = 3;x < 8;x++)
					{
						Valor[x] = 0;
					}
					tela = TELA_TIPO_DETECTOR; //Tela é igual a TELA_MODELO_DE_ANTENA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_NAVEGA_MENU_FUNCOES; //Estado a ser executado é ESTADO_NAVEGA_MENU_FUNCOES
					Write_Buffer_FLASH[0] = tipo_detector;
					ESCREVE_FLASH_INTERNA(endFLASHTipoDetector,1,0);
					estadoTipoDetector = 1; //Coloca a variável estadoModeloAntena para 1 para ir para o primeiro nivel deste menu
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tipo_detector = tipo_detector_aux; //Armazena na variável modelo_antena o valor de modelo_antena antes de modelo_antena ser alterada
					tela = TELA_TIPO_DETECTOR; //Tela é igual a TELA_MODELO_DE_ANTENA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_NAVEGA_MENU_FUNCOES; //Estado a ser executado é ESTADO_NAVEGA_MENU_FUNCOES
					estadoTipoDetector = 1; //Coloca a variável estadoModeloAntena para 1 para ir para o primeiro nivel deste menu
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

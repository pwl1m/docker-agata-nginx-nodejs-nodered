/*
 * funcoes_menu_informacoessistema.c
 *
 *  Created on: 22/06/2023
 *      Author: marcos.butignol
 */

#include "funcao.h"

#include "agata_std_functions.h"
#include "agata_hc_definitions.h"
#include "stdlib.h"


void fnContadorDeteccoes(void) //Permite visualizar os bloqueios e desbloqueios pelas funções abaixo
{
	static byte estadoContadorDeteccoes = 1; //Definindo variável estadoContadorDeteccoes para o switch case abaixo

	switch(estadoContadorDeteccoes) //Conforme valor da variável estadoConfiguraAlarmeVisual vai para o case específico
	{
		case 1: //ENTRA NO MENU CONTADOR DE DETECCOES
		{
			tela = TELA_MOSTRA_CONTADOR_DE_DETECCOES; //Tela é igual a TELA_MOSTRA_CONTADOR_DE_DETECCOES
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estadoContadorDeteccoes = 2; //Coloca a variável estadoContadorDeteccoes para 2 para ir para o case 2
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //ESCOLHE UM DOS TRÊS MENUS DO MENU CONTADOR DE DETECÇÕES
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					menu1++; //Incrementa menu1
					if(menu1 > 3) //Se menu1 for maior que 3 então
					{
						menu1 = 1; //Armazena na variável menu1 o valor 1
					}
					tela = TELA_MOSTRA_CONTADOR_DE_DETECCOES; //Tela é igual a TELA_MOSTRA_CONTADOR_DE_DETECCOES
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					menu1--; //Decrementa menu1
					if(menu1 < 1) //Se menu1 for menor que 1 então
					{
						menu1 = 3; //Armazena na variável menu1 o valor 3
					}
					tela = TELA_MOSTRA_CONTADOR_DE_DETECCOES; //Tela é igual a TELA_MOSTRA_CONTADOR_DE_DETECCOES
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					if(menu1 == 1) //Se menu1 for igual a 1 então
					{
						estado = ESTADO_TOTAL_BLOQUEIOS; //Estado a ser executado é ESTADO_TOTAL_BLOQUEIOS
					}
					else if(menu1 == 2) //Senão se menu1 for igual a 2 então
					{
						estado = ESTADO_TOTAL_DESBLOQUEIOS; //Estado a ser executado é ESTADO_TOTAL_DESBLOQUEIOS
					}
					else if(menu1 == 3) //Senão se menu1 for igual a 3 então
					{
						estado = ESTADO_ZERA_CONTADOR_DETECCOES; //Estado a ser executado é ESTADO_ZERA_CONTADOR_DETECCOES
					}
					estadoContadorDeteccoes = 1; //Coloca a variável estadoContadorDeteccoes para 1 para ir para o primeiro nivel deste menu
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tela = TELA_MOSTRA_INFORMACOES_DO_SISTEMA; //Tela é igual a TELA_MOSTRA_INFORMACOES_DO_SISTEMA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_INFORMACOES_DO_SISTEMA; //Estado a ser executado é ESTADO_INFORMACOES_DO_SISTEMA
					estadoContadorDeteccoes = 1; //Coloca a variável estadoContadorDeteccoes para 1 para ir para o primeiro nivel deste menu
					teclapressionada = 0; //Limpa teclapressionada
					flagretorno = 0; //Zera flagretorno
					break;
				}
				break;
			}
			break;
		}
		break;
	}
}

void fnTotalBloqueios(void) //Permite visualizar o total de bloqueios ocorridos por painel, controle remoto ou detecção de metais
{
	static byte estadoTotalBloqueios = 1; //Definindo variável estadoTotalBloqueios para o switch case abaixo

	switch(estadoTotalBloqueios) //Conforme valor da variável estadoTotalBloqueios vai para o case específico
	{
		case 1: //ENTRA NO MENU TOTAL DE BLOQUEIOS
		{
			tela = TELA_TOTAL_BLOQUEIOS; //Tela é igual TELA_TOTAL_BLOQUEIOS
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estadoTotalBloqueios = 2; //Coloca a variável estadoTotalBloqueios para 2 para ir para o case 2
			break;
		}
		case 2: //VISUALIZA O TOTAL DE BLOQUEIOS
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tela = TELA_MOSTRA_CONTADOR_DE_DETECCOES; //Tela é igual a TELA_MOSTRA_CONTADOR_DE_DETECCOES
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_CONTADOR_DETECCOES; //Estado a ser executado é ESTADO_CONTADOR_DETECCOES
					estadoTotalBloqueios = 1; //Coloca a variável estadoTotalBloqueios para 1 para ir para o primeiro nivel deste menu
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

void fnTotalDesbloqueios(void) //Permite visualizar o total de desbloqueios ocorridos por painel ou controle remoto
{
	static byte estadoTotalDesbloqueios = 1; //Definindo variável estadoTotalDesbloqueios para o switch case abaixo

	switch(estadoTotalDesbloqueios) //Conforme valor da variável estadoTotalDesbloqueios vai para o case específico
	{
		case 1: //ENTRA NO MENU TOTAL DE DESBLOQUEIOS
		{
			tela = TELA_TOTAL_DESBLOQUEIOS; //Tela é igual a TELA_TOTAL_DESBLOQUEIOS
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estadoTotalDesbloqueios = 2; //Coloca a variável estadoTotalDesbloqueios para 2 para ir para o case 2
			break;
		}
		case 2: //VISUALIZA O TOTAL DE DESBLOQUEIOS
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tela = TELA_MOSTRA_CONTADOR_DE_DETECCOES; //Tela é igual a TELA_MOSTRA_CONTADOR_DE_DETECCOES
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_CONTADOR_DETECCOES; //Estado a ser executado é ESTADO_CONTADOR_DETECCOES
					estadoTotalDesbloqueios = 1; //Coloca a variável estadoTotalDesbloqueios para 1 para ir para o primeiro nivel deste menu
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

void fnZeraContadorDeteccoes(void) //Permite zerar os contadores de bloqueios e desbloqueios
{
	static byte estadoZeraContadorDeteccoes = 1; //Definindo variável estadoZeraContadorDeteccoes para o switch case abaixo

	switch(estadoZeraContadorDeteccoes) //Conforme valor da variável estadoZeraContadorDeteccoes vai para o case específico
	{
		case 1: //ENTRA NA TELA DE CONFIRMAÇÃO
		{
			confirma = NAO; //Armazena na variável confirma a informação NAO
			tela = TELA_VOCE_TEM_CERTEZA; //Tela é igual a TELA_VOCE_TEM_CERTEZA
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estadoZeraContadorDeteccoes = 2; //Coloca a variável estadoZeraContadorDeteccoes para 2 para ir para o case 2
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //CONFIRMA SE VAI ZERAR SIM OU NÃO
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla DECREMENTA ou tecla TRAVA ou tecla DESTRAVA pressionada então
				case teclaDecrementa:
				case teclaTrava:
				case teclaDestrava:
				{
					if(confirma == NAO) //Se confirma for igual a NAO então
					{
						confirma = SIM; //Armazena na variável confirma a informação SIM
						LINHA = 2; //Se posiciona na linha 2
						COLUNA = 2; //Se posiciona na coluna 2
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna desejadas
						EscreveChar(' '); //Escreve espaço na posição especificada
						COLUNA = 15; //Se posiciona na coluna 15
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada anteriormente
						EscreveChar('X'); //Escreve X na posição especificada
						teclapressionada = 0; //Limpa teclapressionada
						break;
					}
					else if(confirma == SIM) //Senão se confirma for igual a SIM então
					{
						confirma = NAO; //Armazena na variável confirma a informação NÃO
						LINHA = 2; //Se posiciona na linha 2
						COLUNA = 2; //Se posiciona na coluna 2
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificadas
						EscreveChar('X'); //Escreve X na posição especificada
						COLUNA = 15; //Se posiciona na coluna 15
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada anteriormente
						EscreveChar(' '); //Escreve espaço na posição especificada
						teclapressionada = 0; //Limpa teclapressionada
					}
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					contador_bloqueios = 0; //Armazena na variável contador_bloqueios o valor zero
					contador_desbloqueios = 0; //Armazena na variável contador_desbloqueios o valor zero
					for(x = 0;x < 8;x++) //Coloca o valor dos 4 bytes de contador_bloqueios e 4 bytes de contador_desbloqueios no vetor para gravação na memória FLASH
					{
						Write_Buffer_FLASH[x] = 0; //Armazena o valor zero no vetor para gravação na memória FLASH
					}
					ESCREVE_FLASH_INTERNA(endFLASHTotalBloqueios,8,0); //Escreve na memória FLASH o total de bloqueios e desbloqueios alterado no endereço especificado
					fnGravaAuditoria(26,0,1,OPERADOR,DISPOSITIVO);
					estadoZeraContadorDeteccoes = 1; //Coloca a variável estadoZeraContadorDeteccoes para 1 para ir para o primeiro nivel deste menu
					tela = TELA_MOSTRA_CONTADOR_DE_DETECCOES; //Tela é igual a TELA_MOSTRA_CONTADOR_DE_DETECCOES
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_CONTADOR_DETECCOES; //Estado a ser executado é ESTADO_CONTADOR_DETECCOES
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					estadoZeraContadorDeteccoes = 1; //Coloca a variável estadoZeraContadorDeteccoes para 1 para ir para o primeiro nivel deste menu
					tela = TELA_MOSTRA_CONTADOR_DE_DETECCOES; //Tela é igual a TELA_MOSTRA_CONTADOR_DE_DETECCOES
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_CONTADOR_DETECCOES; //Estado a ser executado é ESTADO_CONTADOR_DETECCOES
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

void fnContadorPassagens(void) //Permite visualizar as entradas e saidas pelas funções abaixo
{
	static byte estadoContadorPassagens = 1; //Definindo variável estadoContadorPassagens para o switch case abaixo

	switch(estadoContadorPassagens) //Conforme valor da variável estadoContadorPassagens vai para o case específico
	{
		case 1: //ENTRA NO MENU CONTADOR DE PASSAGENS
		{
			tela = TELA_MOSTRA_CONTADOR_DE_PASSAGENS; //Tela é igual a TELA_MOSTRA_CONTADOR_DE_PASSAGENS
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estadoContadorPassagens = 2; //Coloca a variável estadoContadorPassagens para 2 para ir para o case 2
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //ESCOLHE ENTRE VISUALIZAR ENTRADAS, SAIDAS ou ENTRADAS + SAIDAS
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					menu1++; //Incrementa menu1
					if(menu1 > 4) //Se menu1 for maior que 4 então
					{
						menu1 = 1; //Armazena na variável menu1 o valor 1
					}
					tela = TELA_MOSTRA_CONTADOR_DE_PASSAGENS; //Tela é igual a TELA_MOSTRA_CONTADOR_DE_PASSAGENS
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					menu1--; //Decrementa menu1
					if(menu1 < 1) //Se menu1 for menor que 1 então
					{
						menu1 = 4; //Armazena na variável menu1 o valor 4
					}
					tela = TELA_MOSTRA_CONTADOR_DE_PASSAGENS; //Tela é igual a TELA_MOSTRA_CONTADOR_DE_PASSAGENS
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					if(menu1 == 1) //Se menu1 for igual a 1 então
					{
						estado = ESTADO_ENTRADAS; //Estado a ser executado é ESTADO_ENTRADAS
					}
					else if(menu1 == 2) //Senão se menu1 for igual a 2 então
					{
						estado = ESTADO_SAIDAS; //Estado a ser executado é ESTADO_SAIDAS
					}
					else if(menu1 == 3) //Senão se menu1 for igual a 3 então
					{
						estado = ESTADO_ENTRADAS_SAIDAS; //Estado a ser executado é ESTADO_ENTRADAS_SAIDAS
					}
					else if(menu1 == 4) //Senão se menu1 for igual a 4 então
					{
						estado = ESTADO_ZERA_CONTADOR_PASSAGENS; //Estado a ser executado é ESTADO_ZERA_CONTADOR_PASSAGENS
					}
					estadoContadorPassagens = 1; //Coloca a variável estadoContadorPassagens para 1 para ir para o primeiro nivel deste menu
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tela = TELA_MOSTRA_INFORMACOES_DO_SISTEMA; //Tela é igual a TELA_MOSTRA_INFORMACOES_DO_SISTEMA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_INFORMACOES_DO_SISTEMA; //Estado a ser executado é ESTADO_INFORMACOES_DO_SISTEMA
					estadoContadorPassagens = 1; //Coloca a variável estadoContadorPassagens para 1 para ir para o primeiro nivel deste menu
					teclapressionada = 0; //Limpa teclapressionada
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU INFORMACOES DO SISTEMA no primeiro nível
					break;
				}
				break;
			}
			break;
		}
		break;
	}
}



void fnContadorPassagem(void)
{
	if(entrou == SIM) //Se houve entrada então incrementa o contador de entrada
	{
		entrou = NAO; //reseta entrou para para que não entre na condição novamente contando de forma errada
		Write_Buffer_FLASH[0] = (byte)(contador_entra >> 24); //Pega o primeiro byte mais alto e desloca 24 casas para poder separar em byte o conteúdo da dword contador_entra que tem 4 bytes
		Write_Buffer_FLASH[1] = (byte)(contador_entra >> 16); //Pega o segundo byte e desloca 16 casas para poder separar em byte o conteúdo da dword contador_entra que tem 4 bytes
		Write_Buffer_FLASH[2] = (byte)(contador_entra >> 8); //Pega o terceiro byte e desloca 8 casas para poder separar em byte o conteúdo da dword contador_entra que tem 4 bytes
		Write_Buffer_FLASH[3] = (byte)(contador_entra); //Pega o quarto byte e não desloca para poder separar em byte o conteúdo da dword contador_entra que tem 4 bytes
		ESCREVE_FLASH_INTERNA(endFLASHContadorEntra,4,0); //Escreve na memória FLASH a variável contador_entra alterado no endereço especificado

		Write_Buffer_FLASH[0] = (byte)(contador_dia_entra >> 24); //Pega o primeiro byte mais alto e desloca 24 casas para poder separar em byte o conteúdo da dword contador_dia_entra que tem 4 bytes
		Write_Buffer_FLASH[1] = (byte)(contador_dia_entra >> 16); //Pega o segundo byte e desloca 16 casas para poder separar em byte o conteúdo da dword contador_dia_entra que tem 4 bytes
		Write_Buffer_FLASH[2] = (byte)(contador_dia_entra >> 8); //Pega o terceiro byte e desloca 8 casas para poder separar em byte o conteúdo da dword contador_dia_entra que tem 4 bytes
		Write_Buffer_FLASH[3] = (byte)(contador_dia_entra); //Pega o quarto byte e não desloca para poder separar em byte o conteúdo da dword contador_dia_entra que tem 4 bytes
		ESCREVE_FLASH_INTERNA(endFLASHContadorEntraDiario,4,0); //Escreve na memória FLASH a variável contador_entra alterado no endereço especificado

		if(sorteador == SIM)
		{
			Write_Buffer_FLASH[0] = sorteador; //Prepara o vetor zero para receber a variável sorteador a ser gravada na memória flash
			Write_Buffer_FLASH[1] = cont_sorteador; //Prepara o vetor 1 para receber a variável cont_sorteador a ser gravada na memória flash
			Write_Buffer_FLASH[2] = quantidade_sorteados; //Prepara o vetor 2 para receber a variável quantidade_sorteados a ser gravada na memória flash
			Write_Buffer_FLASH[3] = numero_sorteado; //Prepara o vetor 3 para receber a variável numero_sorteado a ser gravada na memória flash
			ESCREVE_FLASH_INTERNA(endFLASHSorteador,4,0); //Escreve na memória FLASH a variável sorteador e numero_sorteado alterado nos endereços especificados
		}

		contador_passagens = contador_entra+contador_sai; //soma a contagem de pessoas que entraram e sairam
		estado_CONTADOR = ESTADO_ESPERA; //Coloca estado_CONTADOR em estado de espera até uma nova passagem pelos sensores infravermelhos
	}
	else if(saiu == SIM) //Se houve saida então incrementa o contador de saida
	{
		saiu = NAO; //reseta saiu para que não entre na condição novamente contando de forma errada
		Write_Buffer_FLASH[0] = (byte)(contador_sai >> 24); //Pega o primeiro byte mais alto e desloca 24 casas para poder separar em byte o conteúdo da dword contador_sai que tem 4 bytes
		Write_Buffer_FLASH[1] = (byte)(contador_sai >> 16); //Pega o segundo byte e desloca 16 casas para poder separar em byte o conteúdo da dword contador_sai que tem 4 bytes
		Write_Buffer_FLASH[2] = (byte)(contador_sai >> 8); //Pega o terceiro byte e desloca 8 casas para poder separar em byte o conteúdo da dword contador_sai que tem 4 bytes
		Write_Buffer_FLASH[3] = (byte)(contador_sai); //Pega o quarto byte e não desloca para poder separar em byte o conteúdo da dword contador_sai que tem 4 bytes
		ESCREVE_FLASH_INTERNA(endFLASHContadorSai,4,0); //Escreve na memória FLASH a variável contador_sai alterado no endereço especificado

		Write_Buffer_FLASH[0] = (byte)(contador_dia_sai >> 24); //Pega o primeiro byte mais alto e desloca 24 casas para poder separar em byte o conteúdo da dword contador_dia_sai que tem 4 bytes
		Write_Buffer_FLASH[1] = (byte)(contador_dia_sai >> 16); //Pega o segundo byte e desloca 16 casas para poder separar em byte o conteúdo da dword contador_dia_sai que tem 4 bytes
		Write_Buffer_FLASH[2] = (byte)(contador_dia_sai >> 8); //Pega o terceiro byte e desloca 8 casas para poder separar em byte o conteúdo da dword contador_dia_sai que tem 4 bytes
		Write_Buffer_FLASH[3] = (byte)(contador_dia_sai); //Pega o quarto byte e não desloca para poder separar em byte o conteúdo da dword contador_dia_sai que tem 4 bytes
		ESCREVE_FLASH_INTERNA(endFLASHContadorSaiDiario,4,0); //Escreve na memória FLASH a variável contador_dia_sai alterado no endereço especificado

		contador_passagens = contador_entra+contador_sai; //soma a contagem de pessoas que entraram e sairam
		estado_CONTADOR = ESTADO_ESPERA; //Coloca estado_CONTADOR em estado de espera até uma nova passagem pelos sensores infravermelhos
	}
}


void fnEntradas(void) //Permite visualizar as entradas
{
	static byte estadoEntradas = 1; //Definindo variável estadoEntradas para o switch case abaixo

	switch(estadoEntradas) //Conforme valor da variável estadoEntradas vai para o case específico
	{
		case 1: //ENTRA NO MENU ENTRADAS
		{
			tela = TELA_ENTRADAS; //Tela é igual a TELA_ENTRADAS
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estadoEntradas = 2; //Coloca a variável estadoEntradas para 2 para ir para o case 2
			break;
		}
		case 2: //VISUALIZA A CONTAGEM DE PESSOAS QUE ENTRARAM
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tela = TELA_MOSTRA_CONTADOR_DE_PASSAGENS; //Tela é igual a TELA_MOSTRA_CONTADOR_DE_PASSAGENS
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_CONTADOR_PASSAGENS; //Estado a ser executado é ESTADO_CONTADOR_PASSAGENS
					estadoEntradas = 1; //Coloca a variável estadoEntradas para 1 para ir para o primeiro nivel deste menu
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

void fnSaidas(void) //Permite visualizar as saidas
{
	static byte estadoSaidas = 1; //Definindo variável estadoSaidas para o switch case abaixo

	switch(estadoSaidas) //Conforme valor da variável estadoSaidas vai para o case específico
	{
		case 1: //ENTRA NO MENU SAIDAS
		{
			tela = TELA_SAIDAS; //Tela é igual a TELA_SAIDAS
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estadoSaidas = 2; //Coloca a variável estadoSaidas para 2 para ir para o case 2
			break;
		}
		case 2: //VISUALIZA A CONTAGEM DE PESSOAS QUE SAIRAM DA AGÊNCIA
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaCancela: //Caso tecla CANCELA pressionada
				{
					tela = TELA_MOSTRA_CONTADOR_DE_PASSAGENS; //Tela é igual a TELA_MOSTRA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_CONTADOR_PASSAGENS; //Estado a ser executado é ESTADO_CONTADOR_PASSAGENS
					estadoSaidas = 1; //Coloca a variável estadoSaidas para 1 para ir para o primeiro nivel deste menu
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

void fnEntradasSaidas(void) //Permite visualizar o somatório das entradas e saidas
{
	static byte estadoEntradasSaidas = 1; //Definindo variável estadoEntradasSaidas para o switch case abaixo

	switch(estadoEntradasSaidas) //Conforme valor da variável estadoEntradasSaidas vai para o case específico
	{
		case 1: //ENTRA NO MENU ENTRADAS_SAIDAS
		{
			tela = TELA_ENTRADAS_SAIDAS; //Tela é igual a TELA_ENTRADAS_SAIDAS
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estadoEntradasSaidas = 2; //Coloca a variável estadoEntradasSaidas para 2 para ir para o case 2
			break;
		}
		case 2: //VISUALIZA A SOMA DA CONTAGEM DE PESSOAS QUE ENTRARAM E SAIRAM DA AGÊNCIA
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tela = TELA_MOSTRA_CONTADOR_DE_PASSAGENS; //Tela é igual a TELA_MOSTRA_CONTADOR_DE_PASSAGENS
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_CONTADOR_PASSAGENS; //Estado a ser executado é ESTADO_CONTADOR_PASSAGENS
					estadoEntradasSaidas = 1; //Coloca a variável estadoEntradasSaidas para 1 para ir para o primeiro nivel deste menu
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

void fnZeraContadorPassagens(void) //Permite zerar os contadores de entradas e saidas
{
	static byte estadoZeraContadorPassagens = 1; //Definindo variável estadoZeraContadorPassagens para o switch case abaixo

	switch(estadoZeraContadorPassagens) //Conforme valor da variável estadoZeraContadorPassagens vai para o case específico
	{
		case 1: //ENTRA NO MENU DE CONFIRMAÇÃO
		{
			confirma = NAO; //Armazena na variável confirma a informação NAO
			tela = TELA_VOCE_TEM_CERTEZA; //Tela é igual a TELA_VOCE_TEM_CERTEZA
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estadoZeraContadorPassagens = 2; //Coloca a variável estadoZeraContadorPassagens para 2 para ir para o case 2
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //ALTERA PARA SIM OU NAO PARA CONFIRMAR
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla DECREMENTA ou tecla TRAVA ou tecla DESTRAVA pressionada
				case teclaDecrementa:
				case teclaTrava:
				case teclaDestrava:
				{
					if(confirma == NAO) //Se confirma for igual a NAO então
					{
						confirma = SIM; //Armazena na variável confirma a informação SIM
						LINHA = 2; //Se posiciona na linha 2
						COLUNA = 2; //Se posiciona na coluna 2
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna desejadas
						EscreveChar(' '); //Escreve espaço na posição especificada
						COLUNA = 15; //Se posiciona na coluna 15
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada anteriormente
						EscreveChar('X'); //Escreve X na posição especificada
						teclapressionada = 0; //Limpa teclapressionada
						break;
					}
					else if(confirma == SIM) //Se confirma for igual a SIM então
					{
						confirma = NAO; //Armazena na variável confirma a informação NÃO
						LINHA = 2; //Se posiciona na linha 2
						COLUNA = 2; //Se posiciona na coluna 2
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificadas
						EscreveChar('X'); //Escreve X na posição especificada
						COLUNA = 15; //Se posiciona na coluna 15
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada anteriormente
						EscreveChar(' '); //Escreve espaço na posição especificada
						teclapressionada = 0; //Limpa teclapressionada
						break;
					}
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					contador_passagens = 0; //Armazena na variável contador_passagens o valor zero
					contador_entra = 0; //Armazena na variável contador_entra o valor zero
					contador_dia_entra=0;
					contador_sai = 0; //Armazena na variável contador_sai o valor zero
					contador_dia_sai=0;
					for(x = 0;x < 8;x++) //Coloca o valor dos 4 bytes de contador_bloqueios e 4 bytes de contador_desbloqueios no vetor para gravação na memória FLASH
					{
						Write_Buffer_FLASH[x] = 0; //Armazena o valor zero no vetor para gravação na memória FLASH
					}
					ESCREVE_FLASH_INTERNA(endFLASHContadorEntra,8,0); //Escreve na memória FLASH a variável contador_entra alterado no endereço especificado
					fnGravaAuditoria(27,0,1,OPERADOR,DISPOSITIVO);
					estadoZeraContadorPassagens = 1; //Coloca a variável estadoZeraContadorPassagens para 1 para ir para o primeiro nivel deste menu
					tela = TELA_MOSTRA_CONTADOR_DE_PASSAGENS; //Tela é igual a TELA_MOSTRA_CONTADOR_DE_PASSAGENS
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_CONTADOR_PASSAGENS; //Estado a ser executado é ESTADO_CONTADOR_PASSAGENS
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					estadoZeraContadorPassagens = 1; //Coloca a variável estadoZeraContadorPassagens para 1 para ir para o primeiro nivel deste menu
					tela = TELA_MOSTRA_CONTADOR_DE_PASSAGENS; //Tela é igual a TELA_MOSTRA_CONTADOR_DE_PASSAGENS
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_CONTADOR_PASSAGENS; //Estado a ser executado é ESTADO_CONTADOR_PASSAGENS
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


void fnNumeroSeriePainel(void) //Permite visualizar o número de série da placa Agata
{
	static byte estadoNumeroSerie = 1; //Definindo variável estadoNumeroSerie para o switch case abaixo

	switch(estadoNumeroSerie) //Conforme valor da variável estadoNumeroSerie vai para o case específico
	{
		case 1: //ENTRA NO MENU NÚMERO DE SÉRIE
		{
			tela = TELA_MOSTRA_NUMERO_DE_SERIE_PAINEL; //Tela é igual a TELA_NUMERO_DE_SERIE
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			teclapressionada = 0; //Limpa teclapressionada
			estadoNumeroSerie = 2; //Coloca a variável estadoNumeroSerie para 2 para ir para o case 2
			break;
		}
		case 2: //VISUALIZA O NÚMERO DE SÉRIE DA PLACA AGATA
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tela = TELA_MOSTRA_INFORMACOES_DO_SISTEMA; //Tela é igual a TELA_MOSTRA_INFORMACOES_DO_SISTEMA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_INFORMACOES_DO_SISTEMA; //Estado a ser executado é ESTADO_INFORMACOES_DO_SISTEMA
					estadoNumeroSerie = 1; //Coloca a variável estadoNumeroSerie para 1 para ir para o primeiro nivel deste menu
					teclapressionada = 0; //Limpa teclapressionada
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU INFORMACOES DO SISTEMA no primeiro nível
					break;
				}
				break;
			}
			break;
		}
		break;
	}
}

void fnNumeroSerieFonte(void) //Permite visualizar o número de série da placa Fonte
{
	static byte estadoNumeroSerie1 = 1; //Definindo variável estadoNumeroSerie1 para o switch case abaixo

	switch(estadoNumeroSerie1) //Conforme valor da variável estadoNumeroSerie1 vai para o case específico
	{
		case 1: //ENTRA NO MENU NÚMERO DE SÉRIE 1
		{
			tela = TELA_MOSTRA_NUMERO_DE_SERIE_FONTE; //Tela é igual a TELA_MOSTRA_NUMERO_DE_SERIE1
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			teclapressionada = 0; //Limpa teclapressionada
			estadoNumeroSerie1 = 2; //Coloca a variável estadoNumeroSerie1 para 1 para ir para o primeiro nivel deste menu
			break;
		}
		case 2: //VISUALIA O NÚMERO DE SÉRIE DA PLACA FONTE
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tela = TELA_MOSTRA_INFORMACOES_DO_SISTEMA; //Tela é igual a TELA_MOSTRA_INFORMACOES_DO_SISTEMA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_INFORMACOES_DO_SISTEMA; //Estado a ser executado é ESTADO_INFORMACOES_DO_SISTEMA
					estadoNumeroSerie1 = 1; //Coloca a variável estadoNumeroSerie1 para 1 para ir para o primeiro nivel deste menu
					teclapressionada = 0; //Limpa teclapressionada
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU INFORMACOES DO SISTEMA no primeiro nível
					break;
				}
				break;
			}
			break;
		}
		break;
	}
}



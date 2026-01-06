/*
 * funcoes_menu_ajustesistema.c
 *
 *  Created on: 22/06/2023
 *      Author: marcos.butignol
 */

#include "funcao.h"

#include "agata_std_functions.h"
#include "agata_hc_definitions.h"
#include "stdlib.h"

void fnConfigurarDataHora(void) //Permite escolher entre as funções visualizar ou alterar DATA e HORA
{
	static byte estadoConfigurarDataHora = 1; //Definindo a variável estadoConfigurarDataHora para o switch case abaixo

	switch(estadoConfigurarDataHora) //Conforme valor da variável estadoConfigurarDataHora vai para o case específico
	{
		case 1: //ENTRA NO MENU PARA ESCOLHER ENTRE VISUALIZAR OU ALTERAR DATA E HORA
		{
			tela = TELA_MOSTRA_OPCOES_DATA_E_HORA; //Tela é igual a TELA_MOSTRA_OPCOES_DATA_E_HORA
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estadoConfigurarDataHora = 2; //Coloca a variável estadoConfigurarDataHora para 2 para ir para o case 2
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //ESCOLHE ENTRE O MENU VISUALIZAR OU ALTERAR DATA E HORA
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					menu1++; //Incrementa menu1
					if(menu1 > 2) //Se menu1 for maior que 2 então
					{
						menu1 = 1; //Armazena na variável menu1 o valor 1
					}
					tela = TELA_MOSTRA_OPCOES_DATA_E_HORA; //Tela é igual a TELA_MOSTRA_OPCOES_DATA_E_HORA
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
						menu1 = 2; //Armazena na variável menu1 o valor 2
					}
					tela = TELA_MOSTRA_OPCOES_DATA_E_HORA; //Tela é igual a TELA_MOSTRA_OPCOES_DATA_E_HORA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					if(menu1 == 1) //Se menu1 for igual a 1 então
					{
						estado = ESTADO_VISUALIZAR_DATA_E_HORA; //Estado a ser executado é ESTADO_VISUALIZAR_DATA_E_HORA
					}
					else if(menu1 == 2) //Senão se menu1 for igual a 2 então
					{
						estado = ESTADO_ALTERAR_DATA_E_HORA; //Estado a ser executado é ESTADO_ALTERAR_DATA_E_HORA
					}
					LINHA = 1; //Se posiciona na LINHA 1
					COLUNA = 1; //Se posiciona na COLUNA 1
					LimpaLCD(); //Limpa LCD
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tela = TELA_MOSTRA_AJUSTES_DO_SISTEMA; //Tela é igual a TELA_MOSTRA_AJUSTES_DO_SISTEMA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estadoConfigurarDataHora = 1; //Coloca a variável estadoConfigurarDataHora para 1 para ir para o nivel 1 deste menu
					estado = ESTADO_AJUSTES_DO_SISTEMA; //Estado a ser executado é ESTADO_AJUSTES_DO_SISTEMA
					teclapressionada = 0; //Limpa teclapressionada
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU AJUSTES DO SISTEMA no primeiro nível
					break;
				}
				break;
			}
			break;
		}
		break;
	}
}


void fnAlterarDataHora(void) //Permite alterar a data e a hora do sistema
{
	static estadoAj estadoAtual = data_hora; //Define para os estados estadoAj enumerados para servirem ao case estadoAtual conforme entrada por data_hora, segAjUn, segAjDez, etc...

	switch (estadoAtual) //Conforme valor da variável estadoAtual vai para o case específico
	{
		case data_hora: //Caso for data_hora então
		{
			dataAtualizar = GetData(); //Atualiza dataAtualizar com o valor da hora e data atual
			tela = TELA_ATUALIZAR_DH; //Tela é igual a TELA_ATUALIZAR_DH
			estado_LCD = ATUALIZA_LCD;	//Atualiza o relógio no LCD com a data e a hora atuais
			estadoAtual = diaAjDez; //Coloca a variável estadoAtual para diaAjDez para ir para o case específico
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case diaAjDez: //Caso diaAjDez atualiza o dia
		{
			LINHA = 1; //Se posiciona na linha 1
			COLUNA = 4; //Se posiciona na coluna 4
			PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificados
			switch (teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					dataAtualizar.Dia += 10; //dataAtualizar.Dia é igual a dataAtualizar.Dia mais 10
					if (dataAtualizar.Dia > 31) //Se dia for maior que 31 então
					{
						dataAtualizar.Dia = 31; //Armazena em dataAtualizar.Dia o valor 31
					}
					if(((dataAtualizar.Mes == 4) || (dataAtualizar.Mes == 6) || (dataAtualizar.Mes == 9) || (dataAtualizar.Mes == 11)) && (dataAtualizar.Dia >= 30)) //Se mês for 4 ou 6 ou 9 ou 11 e dia for maior ou igual a 30 então
					{
						dataAtualizar.Dia = 30; //Armazena em dataAtualizar.Dia o valor 30
					}
					else if((dataAtualizar.Mes == 2) && (dataAtualizar.Dia >= 28)) //Senão se mês for 2 e dia for maior igual a 28 então
					{
						if(dataAtualizar.Ano%4 == 0) //Se der zero o resto significa que o ano é bisexto e Fevereiro terá 29 dias
						{
							dataAtualizar.Dia = 29; //Armazena em dataAtualizar.Dia o valor 29
						}
						else //Senão
						{
							dataAtualizar.Dia = 28; //Armazena em dataAtualizar.Dia o valor 28
						}
					}
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA e tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					if (dataAtualizar.Dia > 10) //Se dia for maior que 10 então
					{
						dataAtualizar.Dia -= 10; //Armazena em dataAtualizar.Dia o valor do dia menos 10
					}
					if (dataAtualizar.Dia < 1) //Se dia for menor que 1 então
					{
						dataAtualizar.Dia = 1; //Armazena em dataAtualizar.Dia o valor 1
					}
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					estadoAtual = diaAjUn; //Coloca a variável estadoAtual para diaAjUn para ir para o case específico
					break;
				}
				case teclaCancela: //Caso tecla CANCELA Pressionada então
				{
					estadoAtual = retorna; //Coloca a variável estadoAtual para retorna para ir para o case específico
					break;
				}
			}
			if(teclapressionada) //Se teclapressionada então
			{
				LINHA = 1; //Se posiciona na linha 1
				COLUNA = 4; //Se posiciona na coluna 4
				PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificados
				//Escreve conforme diretrizes abaixo o dia, mês e ano
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
				teclapressionada = 0; //Limpa teclapressionada
			}
			break;
		}
		case diaAjUn: //Caso diaAjUn então
		{
			LINHA = 1; //Se posiciona na linha 1
			COLUNA = 5; //Se posiciona na coluna 5
			PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificados acima
			switch (teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA pressionada então
				{
					dataAtualizar.Dia++; //Incrementa dataAtualizar.Dia
					if (dataAtualizar.Dia > 31) //Se dia for maior que 31 então
					{
						dataAtualizar.Dia = 31; //Armazena em dataAtualizar.Dia o valor 31
					}
					if(((dataAtualizar.Mes == 4) || (dataAtualizar.Mes == 6) || (dataAtualizar.Mes == 9) || (dataAtualizar.Mes == 11)) && (dataAtualizar.Dia >= 30)) //Se mês for 4 ou 6 ou 9 ou 11 e dia for maior ou igual a 30 então
					{
						dataAtualizar.Dia = 30; //Armazena em dataAtualizar.Dia o valor 30
					}
					else if((dataAtualizar.Mes == 2) && (dataAtualizar.Dia >= 28)) //Senão se mês for 2 e dia for maior igual a 28 então
					{
						if(dataAtualizar.Ano%4 == 0) //Se der zero o resto significa que o ano é bisexto e Fevereiro terá 29 dias
						{
							dataAtualizar.Dia = 29; //Armazena em dataAtualizar.Dia o valor 29
						}
						else //Senão
						{
							dataAtualizar.Dia = 28; //Armazena em dataAtualizar.Dia o valor 28
						}
					}
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA pressionada então
				{
					dataAtualizar.Dia--; //Decrementa dataAtualizar.Dia
					if (dataAtualizar.Dia < 1) //Se dia for menor que 1 então
					{
						dataAtualizar.Dia = 1; //Armazena em dataAtualizar.Dia o valor 1
					}
					if((dataAtualizar.Mes == 2) && (dataAtualizar.Dia >= 28)) //Senão se mês for 2 e dia for maior igual a 28 então
					{
						if(dataAtualizar.Ano%4 == 0) //Se der zero o resto significa que o ano é bisexto e Fevereiro terá 29 dias
						{
							dataAtualizar.Dia = 29; //Armazena em dataAtualizar.Dia o valor 29
						}
						else //Senão
						{
							dataAtualizar.Dia = 28; //Armazena em dataAtualizar.Dia o valor 28
						}
					}
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					estadoAtual = mesAjDez; //Coloca a variável estadoAtual para mesAjDez para ir para o case específico
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					estadoAtual = retorna; //Coloca a variável estadoAtual para retorna para ir para o case específico
					break;
				}
			}
			if(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				LINHA = 1; //Se posiciona na linha 1
				COLUNA = 4; //Se posiciona na coluna 4
				PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificados
				//Escreve conforme diretrizes abaixo o dia, mês e ano
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
				teclapressionada = 0; //Limpa teclapressionada
			}
			break;
		}
		case mesAjDez: //Caso mesAjDez então
		{
			LINHA = 1; //Se posiciona na linha 1
			COLUNA = 7; //Se posiciona na coluna 7
			PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificados
			switch (teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA pressionada então
				{
					dataAtualizar.Mes += 10; //dataAtualizar.Mes é igual a dataAtualizar.Mes mais 10
					if (dataAtualizar.Mes > 12) //Se Mes for maior que 12 então
					{
						dataAtualizar.Mes = 12; //Armazena em dataAtualizar.Mes o valor 12
					}
					if((dataAtualizar.Mes == 11) && (dataAtualizar.Dia >= 30)) //Senão se mês for 11 e dia for maior igual a 30 então
					{
						dataAtualizar.Dia = 30; //Armazena em dataAtualizar.Dia o valor 30
					}
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA pressionada então
				{
					if (dataAtualizar.Mes > 10) //Se mês for maior que 10 então
					{
						dataAtualizar.Mes -= 10; //Armazena em dataAtualizar.Mes o valor do mês menos 10
					}
					if (dataAtualizar.Mes < 1) //Se mês for menor que 1 então
					{
						dataAtualizar.Mes = 1; //Armazena em dataAtualizar.Mes o valor 1
					}
					if((dataAtualizar.Mes == 2) && (dataAtualizar.Dia >= 28)) //Senão se mês for 2 e dia for maior igual a 28 então
					{
						if(dataAtualizar.Ano%4 == 0) //Se der zero o resto significa que o ano é bisexto e Fevereiro terá 29 dias
						{
							dataAtualizar.Dia = 29; //Armazena em dataAtualizar.Dia o valor 29
						}
						else //Senão
						{
							dataAtualizar.Dia = 28; //Armazena em dataAtualizar.Dia o valor 28
						}
					}
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA então
				case teclaConfirma_Remoto:
				{
					estadoAtual = mesAjUn; //Coloca a variável estadoAtual para mesAjUn para ir para o case específico
					break;
				}
				case teclaCancela: //Caso tecla CANCELA então
				{
					estadoAtual = retorna; //Coloca a variável estadoAtual para retorna para ir para o case específico
					break;
				}
			}
			if(teclapressionada) //Se teclapressionada então
			{
				LINHA = 1; //Se posiciona na linha 1
				COLUNA = 4; //Se posiciona na coluna 4
				PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
				//Escreve conforme diretrizes abaixo o dia, mês e ano
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
				teclapressionada = 0; //Limpa teclapressionada
			}
			break;
		}
		case mesAjUn: //Caso mesAjUn então
		{
			LINHA = 1; //Se posiciona na linha 1
			COLUNA = 8; //Se posiciona na coluna 8
			PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					dataAtualizar.Mes++; //Incrementa dataAtualizar.Mes
					if (dataAtualizar.Mes > 12) //Se Mês for maior que 12 então
					{
						dataAtualizar.Mes = 12; //Armazena em dataAtualizar.Mes o valor 12
					}
					if(((dataAtualizar.Mes == 4) || (dataAtualizar.Mes == 6) || (dataAtualizar.Mes == 9) || (dataAtualizar.Mes == 11)) && (dataAtualizar.Dia >= 30)) //Se mês for 4 ou 6 ou 9 ou 11 e dia for maior ou igual a 30 então
					{
						dataAtualizar.Dia = 30; //Armazena em dataAtualizar.Dia o valor 30
					}
					else if((dataAtualizar.Mes == 2) && (dataAtualizar.Dia >= 28)) //Senão se mês for 2 e dia for maior igual a 28 então
					{
						if(dataAtualizar.Ano%4 == 0) //Se der zero o resto significa que o ano é bisexto e Fevereiro terá 29 dias
						{
							dataAtualizar.Dia = 29; //Armazena em dataAtualizar.Dia o valor 29
						}
						else //Senão
						{
							dataAtualizar.Dia = 28; //Armazena em dataAtualizar.Dia o valor 28
						}
					}
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					dataAtualizar.Mes--; //Decrementa dataAtualizar.Mes
					if (dataAtualizar.Mes < 1) //Se mês for menor que 1 então
					{
						dataAtualizar.Mes = 1; //Armazena em dataAtualizar.Mes o valor 1
					}
					if(((dataAtualizar.Mes == 4) || (dataAtualizar.Mes == 6) || (dataAtualizar.Mes == 9) || (dataAtualizar.Mes == 11)) && (dataAtualizar.Dia >= 30)) //Se mês for 4 ou 6 ou 9 ou 11 e dia for maior ou igual a 30 então
					{
						dataAtualizar.Dia = 30; //Armazena em dataAtualizar.Dia o valor 30
					}
					else if((dataAtualizar.Mes == 2) && (dataAtualizar.Dia >= 28)) //Senão se mês for 2 e dia for maior igual a 28 então
					{
						if(dataAtualizar.Ano%4 == 0) //Se der zero o resto significa que o ano é bisexto e Fevereiro terá 29 dias
						{
							dataAtualizar.Dia = 29; //Armazena em dataAtualizar.Dia o valor 29
						}
						else //Senão
						{
							dataAtualizar.Dia = 28; //Armazena em dataAtualizar.Dia o valor 28
						}
					}
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					estadoAtual = anoAjDez; //Coloca a variável estadoAtual para mesAjDez para ir para o case específico
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					estadoAtual = retorna; //Coloca a variável estadoAtual para retorna para ir para o case específico
					break;
				}
			}
			if(teclapressionada) //Se teclapressionada então
			{
				LINHA = 1; //Se posiciona na linha 1
				COLUNA = 4; //Se posiciona na coluna 4
				PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
				//Escreve conforme diretrizes abaixo o dia, mês e ano
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
				teclapressionada = 0; //Limpa teclapressionada
			}
			break;
		}
		case anoAjDez: //Caso anoAjDez então
		{
			LINHA = 1; //Se posiciona na linha 1
			COLUNA = 12; //Se posiciona na coluna 12
			PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					dataAtualizar.Ano += 10; //dataAtualizar.Ano é igual a dataAtualizar.Ano mais 10
					if (dataAtualizar.Ano > 2099) //Se ano for maior que 2099 então
					{
						dataAtualizar.Ano = 2099; //Armazena em dataAtualizar.Ano o valor 2099
					}
					if(((dataAtualizar.Mes == 4) || (dataAtualizar.Mes == 6) || (dataAtualizar.Mes == 9) || (dataAtualizar.Mes == 11)) && (dataAtualizar.Dia >= 30)) //Se mês for 4 ou 6 ou 9 ou 11 e dia for maior ou igual a 30 então
					{
						dataAtualizar.Dia = 30; //Armazena em dataAtualizar.Dia o valor 30
					}
					else if((dataAtualizar.Mes == 2) && (dataAtualizar.Dia > 28)) //Senão se mês for 2 e dia for maior que 28 então
					{
						if(dataAtualizar.Ano%4 != 0) //Se der zero o resto significa que o ano não é bisexto e Fevereiro terá 28 dias
						{
							dataAtualizar.Dia = 28; //Armazena em dataAtualizar.Dia o valor 28
						}
						else //Senão
						{
							dataAtualizar.Dia = 29; //Armazena em dataAtualizar.Dia o valor 29
						}
					}
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					dataAtualizar.Ano -= 10; //dataAtualizar.Ano é igual a dataAtualizar.Ano menos 10
					if (dataAtualizar.Ano < 2013) //Se ano for menor que 2013 então
					{
						dataAtualizar.Ano = 2013; //Armazena em dataAtualizar.Ano o valor 2013
					}
					if(((dataAtualizar.Mes == 4) || (dataAtualizar.Mes == 6) || (dataAtualizar.Mes == 9) || (dataAtualizar.Mes == 11)) && (dataAtualizar.Dia >= 30)) //Se mês for 4 ou 6 ou 9 ou 11 e dia for maior ou igual a 30 então
					{
						dataAtualizar.Dia = 30; //Armazena em dataAtualizar.Dia o valor 30
					}
					else if((dataAtualizar.Mes == 2) && (dataAtualizar.Dia > 28)) //Senão se mês for 2 e dia for maior que 28 então
					{
						if(dataAtualizar.Ano%4 != 0) //Se der zero o resto significa que o ano não é bisexto e Fevereiro terá 28 dias
						{
							dataAtualizar.Dia = 28; //Armazena em dataAtualizar.Dia o valor 28
						}
						else //Senão
						{
							dataAtualizar.Dia = 29; //Armazena em dataAtualizar.Dia o valor 29
						}
					}
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					estadoAtual = anoAjUn; //Coloca a variável estadoAtual para anoAjUn para ir para o case específico
					break;
				}
				case teclaCancela: //Casp tecla CANCELA pressionada então
				{
					estadoAtual = retorna; //Coloca a variável estadoAtual para retorna para ir para o case específico
					break;
				}
			}
			if(teclapressionada) //Se teclapressionada então
			{
				LINHA = 1; //Se posiciona na linha 1
				COLUNA = 4; //Se posiciona na coluna 4
				PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
				//Escreve conforme diretrizes abaixo o dia, mês e ano
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
				teclapressionada = 0;
			}
			break;
		}
		case anoAjUn: //Caso anoAjUn então
		{
			LINHA = 1; //Se posicona na linha 1
			COLUNA = 13; //Se posiciona na coluna 4
			PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
			switch (teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso telca INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					dataAtualizar.Ano++; //Incrementa dataAtualizar.Ano
					if (dataAtualizar.Ano > 2099) //Se ano for maior que 2099 então
					{
						dataAtualizar.Ano = 2099; //Armazena em dataAtualizar.Ano o valor 2099
					}
					if(((dataAtualizar.Mes == 4) || (dataAtualizar.Mes == 6) || (dataAtualizar.Mes == 9) || (dataAtualizar.Mes == 11)) && (dataAtualizar.Dia >= 30)) //Se mês for 4 ou 6 ou 9 ou 11 e dia for maior ou igual a 30 então
					{
						dataAtualizar.Dia = 30; //Armazena em dataAtualizar.Dia o valor 30
					}
					else if((dataAtualizar.Mes == 2) && (dataAtualizar.Dia > 28)) //Senão se mês for 2 e dia for maior que 28 então
					{
						if(dataAtualizar.Ano%4 != 0) //Se der zero o resto significa que o ano não é bisexto e Fevereiro terá 28 dias
						{
							dataAtualizar.Dia = 28; //Armazena em dataAtualizar.Dia o valor 28
						}
						else //Senão
						{
							dataAtualizar.Dia = 29; //Armazena em dataAtualizar.Ano o valor 29
						}
					}
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					dataAtualizar.Ano--; //Decrementa dataAtualizar.Ano
					if (dataAtualizar.Ano < 2012) //Se ano for menor que 2012 então
					{
						dataAtualizar.Ano = 2012; //Armazena em dataAtualizar.Ano o valor 2012
					}
					if(((dataAtualizar.Mes == 4) || (dataAtualizar.Mes == 6) || (dataAtualizar.Mes == 9) || (dataAtualizar.Mes == 11)) && (dataAtualizar.Dia >= 30)) //Se mês for 4 ou 6 ou 9 ou 11 e dia for maior ou igual a 30 então
					{
						dataAtualizar.Dia = 30; //Armazena em dataAtualizar.Dia o valor 30
					}
					else if((dataAtualizar.Mes == 2) && (dataAtualizar.Dia > 28)) //Senão se mês for 2 e dia for maior que 28 então
					{
						if(dataAtualizar.Ano%4 != 0) //Se der zero o resto significa que o ano não é bisexto e Fevereiro terá 28 dias
						{
							dataAtualizar.Dia = 28; //Armazena em dataAtualizar.Dia o valor 28
						}
						else //Senão
						{
							dataAtualizar.Dia = 29; //Armazena em dataAtualizar.Dia o valor 29
						}
					}
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA então
				case teclaConfirma_Remoto:
				{
					estadoAtual = horaAjDez; //Coloca a variável estadoAtual para anoAjDez para ir para o case específico
					break;
				}
				case teclaCancela:
				{
					estadoAtual = retorna; //Coloca a variável estadoAtual para retorna para ir para o case específico
					break;
				}
			}
			if(teclapressionada) //Se teclapressionada então
			{
				LINHA = 1; //Se posiciona na linha 1
				COLUNA = 4; //Se posiciona na coluna 4
				PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
				//Escreve conforme diretrizes abaixo o dia, mês e ano
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
				teclapressionada = 0; //Limpa teclapressionada
			}
			break;
		}
		case horaAjDez: //Caso horaAjDez então
		{
			LINHA = 2; //Se posiciona na linha 2
			COLUNA = 5; //Se posiciona na coluna 5
			PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
			switch (teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					dataAtualizar.Hora += 10; //dataAtualizar.Hora é igual a dataAtualizar.Hora mais 10
					if (dataAtualizar.Hora > 23) //Se hora for maior que 23 então
					{
						dataAtualizar.Hora = 23; //Armazena em dataAtualizar.Hora o valor 23
					}
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					if (dataAtualizar.Hora > 10) //Se hora for maior 10 então
					{
						dataAtualizar.Hora -= 10; //dataAtualizar.Hora é igual a dataAtualizar.Hora menos 10
					}
					if (dataAtualizar.Hora < 0 || dataAtualizar.Hora == 255) //Se dataAtualizar.Hora for menor que 0 ou dataAtualizar.Hora for igual a 255 então
					{
						dataAtualizar.Hora = 0; //Armazena em dataAtualizar.Hora o valor 0
					}
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					estadoAtual = horaAjUn; //Coloca a variável estadoAtual para horaAjUn para ir para o case específico
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					estadoAtual = retorna; //Coloca a variável estadoAtual para retorna para ir para o case específico
					break;
				}
			}
			if(teclapressionada) //Se tecla pressionada então
			{
				LINHA = 2; //Se posiciona na linha 2
				COLUNA = 5; //Se posiciona na coluna 5
				PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificadas
				EscreveChar((char)(dataAtualizar.Hora/10 + 48)); //Escreve a parte da dezena da hora
				EscreveChar((char)(dataAtualizar.Hora%10 + 48)); //Escreve a parte da unidade da hora
				teclapressionada = 0; //Limpa teclapressionada
			}
			break;
		}
		case horaAjUn: //Caso horaAjUn então
		{
			LINHA = 2; //Se posiciona na linha 2
			COLUNA = 6; //Se posiciona na coluna 6
			PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
			switch (teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					dataAtualizar.Hora++; //Incrementa dataAtualizar.Hora
					if (dataAtualizar.Hora > 23) //Se hora for maior que 23 então
					{
						dataAtualizar.Hora = 23; //Armazena em dataAtualizar.Hora o valor 23
					}
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					dataAtualizar.Hora--; //Decrementa dataAtualizar.hora
					if (dataAtualizar.Hora < 0 || dataAtualizar.Hora == 255) //Se dataAtualizar.Hora for menor que 0 ou dataAtualizar.Hora for igual a 255 então
					{
						dataAtualizar.Hora = 0; //Armazena em dataAtualizar.Hora o valor 0
					}
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					estadoAtual = minAjDez; //Coloca a variável estadoAtual para minAjDez para ir para o case específico
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					estadoAtual = retorna; //Coloca a variável estadoAtual para retorna para ir para o case específico
					break;
				}
			}
			if(teclapressionada) //Se teclapressionada então
			{
				LINHA = 2; //Se posiciona na linha 2
				COLUNA = 5; //Se posiciona na coluna 5
				PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
				EscreveChar((char)(dataAtualizar.Hora/10 + 48)); //Escreve a parte da dezena da hora
				EscreveChar((char)(dataAtualizar.Hora%10 + 48)); //Escreve a parte da unidade da hora
				teclapressionada = 0; //Limpa teclapressionada
			}
			break;
		}
		case minAjDez: //Caso minAjDez então
		{
			LINHA = 2; //Se posiciona na linha 2
			COLUNA = 8; //Se posiciona na coluna 8
			PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
			switch (teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					dataAtualizar.Minuto += 10; //dataAtualizar.Minuto é igual a dataAtualizar.Minuto mais 10
					if (dataAtualizar.Minuto > 59) //Se minuto for maior que 59 então
					{
						dataAtualizar.Minuto = 59; //Armazena em dataAtualizar.Minuto o valor 59
					}
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					if (dataAtualizar.Minuto > 10) //Se minuto for maior que 10 então
					{
						dataAtualizar.Minuto -= 10; //dataAtualizar.Minuto é igual a dataAtualizar.Minuto menos 10
					}
					if (dataAtualizar.Minuto < 0 || dataAtualizar.Minuto == 255) //Se dataAtualizar.Minuto for menor que 0 ou dataAtualizar.Minuto for igual a 255 então
					{
						dataAtualizar.Minuto = 0; //Armazena em dataAtualizar.Minuto o valor 0
					}
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					estadoAtual = minAjUn; //Coloca a variável estadoAtual para minAjUn para ir para o case específico
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					estadoAtual = retorna; //Coloca a variável estadoAtual para retorna para ir para o case específico
					break;
				}
			}
			if(teclapressionada) //Se teclapressionada então
			{
				LINHA = 2; //Se posiciona na linha 2
				COLUNA = 8; //Se posiciona na coluna 8
				PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
				EscreveChar((char)(dataAtualizar.Minuto/10 + 48)); //Escreve a parte da dezena do minuto
				EscreveChar((char)(dataAtualizar.Minuto%10 + 48)); //Escreve a parte da unidade do minuto
				teclapressionada = 0; //Limpa teclapressionada
			}
			break;
		}
		case minAjUn: //Caso minAjUn então
		{
			LINHA = 2; //Se posiciona na linha 2
			COLUNA = 9; //Se posiciona na coluna 9
			PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
			switch (teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					dataAtualizar.Minuto++; //Incrementa dataAtualizar.Minuto
					if (dataAtualizar.Minuto > 59) //Se minuto for maior que 59 então
					{
						dataAtualizar.Minuto = 59; //Armazena em dataAtualizar.Minuto o valor 59
					}
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					dataAtualizar.Minuto--; //Decrementa dataAtualizar.Minuto
					if (dataAtualizar.Minuto < 0 || dataAtualizar.Minuto == 255) //Se dataAtualizar.Minuto for menor que 0 ou dataAtualizar.Minuto for igual a 255 então
					{
						dataAtualizar.Minuto = 0; //Armazena em dataAtualizar.Minuto o valor 0
					}
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					estadoAtual = segAjDez; //Coloca a variável estadoAtual para segAjDez para ir para o case específico
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					estadoAtual = retorna; //Coloca a variável estadoAtual para retorna para ir para o case específico
					break;
				}
			}
			if(teclapressionada) //Se teclapressionada então
			{
				LINHA = 2; //Se posiciona na linha 2
				COLUNA = 8; //Se posiciona na coluna 8
				PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
				EscreveChar((char)(dataAtualizar.Minuto/10 + 48)); //Escreve a parte da dezena do minuto
				EscreveChar((char)(dataAtualizar.Minuto%10 + 48)); //Escreve a parte da unidade do minuto
				teclapressionada = 0;
			}
			break;
		}
		case segAjDez: //Caso segAjDez então
		{
			LINHA = 2; //Se posiciona na linha 2
			COLUNA = 11; //Se posiciona na coluna 11
			PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
			switch (teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					dataAtualizar.Segundo += 10; //dataAtualizar.Segundo é igual a dataAtualizar.Segundo mais 10
					if (dataAtualizar.Segundo > 59) //Se segundo for maior que 59 então
					{
						dataAtualizar.Segundo = 59; //Armazena em dataAtualizar.Segundo o valor 59
					}
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					if (dataAtualizar.Segundo > 10) //Se segundo for maior que 10 então
					{
						dataAtualizar.Segundo -= 10; //dataAtualizar.Segundo é igual a dataAtualizar.Segundo menos 10
					}
					if (dataAtualizar.Segundo < 0 || dataAtualizar.Segundo == 255) //Se dataAtualizar.Segundo for menor que 0 ou dataAtualizar.Segundo for igual a 255 então
					{
						dataAtualizar.Segundo = 0; //Armazena em dataAtualizar.Segundo o valor 0
					}
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					estadoAtual = segAjUn; //Coloca a variável estadoAtual para segAjUn para ir para o case específico
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					estadoAtual = retorna; //Coloca a variável estadoAtual para retorna para ir para o case específico
					break;
				}
			}
			if(teclapressionada) //Se tecla pressionada então
			{
				LINHA = 2; //Se posiciona na linha 2
				COLUNA = 11; //Se posiciona na coluna 11
				PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
				EscreveChar((char)(dataAtualizar.Segundo/10 + 48)); //Escreve a parte da dezena do segundo
				EscreveChar((char)(dataAtualizar.Segundo%10 + 48)); //Escreve a parte da unidade do segundo
				teclapressionada = 0; //Limpa teclapressionada
			}
			break;
		}
		case segAjUn: //Caso segAjUn então
		{
			LINHA = 2; //Se posiciona na linha 2
			COLUNA = 12; //Se posiciona na coluna 12
			PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
			switch (teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					dataAtualizar.Segundo++; //Incrementa dataAtualizar.Segundo
					if (dataAtualizar.Segundo > 59) //Se segundo for maior que 59 então
					{
						dataAtualizar.Segundo = 59; //Armazena em dataAtualizar.Segundo o valor 59
					}
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					dataAtualizar.Segundo--; //Decrementa dataAtualizar.Segundo
					if (dataAtualizar.Segundo < 0 || dataAtualizar.Segundo == 255) //Se dataAtualizar.Segundo for menor que 0 ou dataAtualizar.Segundo for igual a 255 então
					{
						dataAtualizar.Segundo = 0; //Armazena em dataAtualizar.Segundo o valor 0
					}
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					estadoAtual = fim; //Coloca a variável estadoAtual para fim para ir para o case específico
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					estadoAtual = retorna; //Coloca a variável estadoAtual para retorna para ir para o case específico
					break;
				}
			}
			if(teclapressionada) //Se tecla presssionada então
			{
				LINHA = 2; //Se posiciona na linha 2
				COLUNA = 11; //Se posiciona na coluna 11
				PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
				EscreveChar((char)(dataAtualizar.Segundo/10 + 48)); //Escreve a parte da dezena do segundo
				EscreveChar((char)(dataAtualizar.Segundo%10 + 48)); //Escreve a parte da unidade do segundo
				teclapressionada = 0; //Limpa teclapressionada
			}
			break;
		}
		case fim: //Caso fim então
		{
			Time.Day = (uint32)dataAtualizar.Dia; //Atualiza o dia alterado acima no sistema
			Time.Month = (uint32)dataAtualizar.Mes; //Atualiza o mês alterado acima no sistema
			Time.Year = (uint32)dataAtualizar.Ano; //Atualiza o ano alterado acima no sistema
			Time.Hour = (uint32)dataAtualizar.Hora; //Atualiza a hora alterado acima no sistema
			Time.Minute = (uint32)dataAtualizar.Minuto; //Atualiza o minuto alterado acima no sistema
			Time.Second = (uint32)dataAtualizar.Segundo; //Atualiza o segundo alterado acima no sistema

			RTC1_SetTime(MyRTCPtr, &Time); //Atualiza a hora e a data conforme variáveis do sistema acima
			fnGravaAuditoria(22,0,1,OPERADOR,DISPOSITIVO);
			estadoAtual = data_hora; //Coloca a variável estadoAtual para data_hora para ir para o case específico
			teclapressionada = 0; //Limpa teclapressionada
			tela = TELA_MOSTRA_OPCOES_DATA_E_HORA; //Tela é igual a TELA_MOSTRA_OPCOES_DATA_E_HORA
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estado = ESTADO_HORA_E_DATA; //Estado a ser executado é ESTADO_HORA_E_DATA
			break;
		}
		default: //Caso default então
		{
			estadoAtual = data_hora; //Coloca a variável estadoAtual para data_hora para ir para o case específico
			tela = TELA_MOSTRA_OPCOES_DATA_E_HORA; //Tela é igual a TELA_MOSTRA_OPCOES_DATA_E_HORA
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estado = ESTADO_HORA_E_DATA; //Estado a ser executado é ESTADO_HORA_E_DATA
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		break;
	}
}



void fnAlteraSenha(void) //Função que realmente altera a senha conforme os dois acima
{
	static byte estadoAlteraSenha = 1,index = 6; //Definindo variável estadoAlteraSenha para o switch case abaixo, define a variável index para que o cursor caminhe pelos campos da senha

	switch(estadoAlteraSenha) //Conforme valor da variável estadoAlteraSenha vai para o case específico
	{
		case 1: //ENTRA NO MENU ALTERA SENHA
		{
			estadoAlteraSenha = 2; //Coloca a variável estadoAlteraSenha para 2 para ir para o próximo case
			tela = TELA_ALTERA_SENHA; //Tela é igual a TELA_ALTERA_SENHA
			Atualiza_LCD(); //Atualiza o LCD com a tela acima
			SetaCaracterSenha(index); //Função que vai deslocando o caracter no campo senha conforme coluna informada na variável index
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //ALTERA A SENHA
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					if(estado_troca_senha == ESTADO_SOLICITA_TROCA_SENHA){
						estadoAlteraSenha = 1; //Coloca a variável estadoConfirmaSenha para 1 para ir para o primeiro nivel deste menu
						index = 6; //Armazena em identador a posição de coluna 6 do cursor
						teclapressionada = 0; //Limpa teclapressionada
						ch = 0x30; //Armazena em ch o valor zero
						acao_cancelada = SIM;
						return;
					}
					tela = TELA_MOSTRA_AJUSTES_DO_SISTEMA; //Tela é igual TELA_MOSTRA_AJUSTES_DO_SISTEMA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_AJUSTES_DO_SISTEMA; //Estado a ser executado é ESTADO_AJUSTES_DO_SISTEMA
					estadoAlteraSenha = 1; //Coloca a variável estadoAlteraSenha para 1 para ir para o primeiro nivel deste menu
					index = 6; //Armzena em index a posição de coluna 6 do cursor
					teclapressionada = 0; //Limpa teclapressionada
					ch = 0x30; //Armazena o número zero em ch
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					SetaCaracterSenha(index); //Posiciona o cursor na coluna conforme o valor do indexador passado
					senha[index-6] = ch; //Armazena no vetor senha na posição index-6, exemplo: se index é 6 será senha[0]. Armazena o conteúdo de ch
					index++; //Incrementa o index para passar para o próximo campo da senha
					COLUNA = index; //Armazena em coluna a posição index
					PosicionaLCD(pos); //Posiciona o cursor na coluna informada
					ch = 0x30; //Armazena em ch o número zero
					C = 0x30; //Aramazena em C o número zero
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					if(C == 0X39) //Se C for igual ao número 9 então
					{
						C = 0X41; //Armazena em C o valor A
						EscreveChar(C); //Escreve na posição especificada o valor A
						COLUNA = index; //Armazena em coluna a posição index
						PosicionaLCD(pos); //Posiciona o cursor na coluna informada
					}
					else if(C == 0x5A) //Senão se C for igual a Z então
					{
						C = 0x30; //Aramazena em C o número zero
						EscreveChar(C); //Escreve na posição especificada o valor 0
						COLUNA = index; //Armazena em coluna a posição index
						PosicionaLCD(pos); //Posiciona o cursor na coluna informada
					}
					else //Senão
					{
						C++; //Incrementa C
						EscreveChar(C); //Escreve na posição especificada o valor correspondente na tabela ASCII
						COLUNA = index; //Armazena em coluna a posição index
						PosicionaLCD(pos); //Posiciona o cursor na coluna informada
					}
					ch = C; //Armazena na variável ch o último valor de C conforme alterações acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					if(C == 0x30) //Se C for igual a zero então
					{
						C = 0x5A; //Armazena em C o valor Z
						EscreveChar(C); //Escreve na posição especificada o valor correspondente na tabela ASCII
						COLUNA = index; //Armazena em coluna a posição index
						PosicionaLCD(pos); //Posiciona o cursor na coluna informada
					}
					else if(C == 0x41) //Se C for igual a A então
					{
						C = 0x39; //Armazena em C o valor 9
						EscreveChar(C); //Escreve na posição especificada o valor correspondente na tabela ASCII
						COLUNA = index; //Armazena em coluna a posição index
						PosicionaLCD(pos); //Posiciona o cursor na coluna informada
					}
					else //Senão
					{
						C--; //Decrementa C
						EscreveChar(C); //Escreve na posição especificada o valor correspondente na tabela ASCII
						COLUNA = index; //Armazena em coluna a posição index
						PosicionaLCD(pos); //Posiciona o cursor na coluna informada
					}
					ch = C; //Armazena na variável ch o último valor de C conforme alterações acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				break;
			}
			if(index >= 12) //Se index for maior igual a 12 significa que os 6 números ou letras da senha já foram preenchidos
			{
				estadoAlteraSenha = 3; //Coloca a variável estadoAlteraSenha para 3 para ir para o próximo case
				index = 6; //Retorna o valor de index para 6 para que a senha possa ser digitada novamente
				ch = 0x30; //Armazena em ch o valor zero
			}
			break;
		}
		case 3: //ENTRA NO MENU DE CONFIRMAÇÃO DA SENHA
		{
			tela = TELA_CONFIRMAR_SENHA; //Tela é igual a TELA_CONFIRMAR_SENHA
			if(senha_gerente_trocada == FALSE || senha_tecnico_trocada == FALSE){
				Atualiza_LCD();
			}else estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estadoAlteraSenha = 1; //Coloca a variável estadoAlteraSenha para 1 para ir para o primeiro nivel deste menu
			estado = ESTADO_CONFIRMA_SENHA; //Estado a ser executado é ESTADO_CONFIRMA_SENHA
			teclapressionada = 0; //Limpa teclapressionada

			break;
		}
		break;
	}
}

void fnConfirmaSenha(void) //Função que confirma a senha a ser alterada
{
	static byte estadoConfirmaSenha = 1,identador = 6; //Definindo variável estadoConfirmaSenha para o switch case abaixo, define a variável identador para que o cursor caminhe pelos campos da senha
	static byte j,verifica_senha; //Define a variável j para o laço for e a variável verifica_senha para poder armazenar o resultado da comparação

	switch(estadoConfirmaSenha) //Conforme valor da variável estadoConfirmaSenha vai para o case específico
	{
		case 1: //ENTRA NO MENU CONFIRMA SENHA
		{
			SetaCaracterSenha(identador); //Função que vai deslocando o caracter no campo senha conforme coluna informada na variável identador
			estadoConfirmaSenha = 2; //Coloca a variável estadoAlteraSenha para 2 para ir para o próximo case
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //ALTERA A SENHA
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					if(estado_troca_senha == ESTADO_SOLICITA_TROCA_SENHA){
						acao_cancelada = SIM;
						estadoConfirmaSenha = 1; //Coloca a variável estadoConfirmaSenha para 1 para ir para o primeiro nivel deste menu
						identador = 6; //Armazena em identador a posição de coluna 6 do cursor
						teclapressionada = 0; //Limpa teclapressionada
						ch = 0x30; //Armazena em ch o valor zero
						return;
					}
					tela = TELA_ALTERA_SENHA; //Tela é igual a TELA_ALTERA_SENHA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_ALTERA_SENHA; //Estado a ser executado é ESTADO_ALTERA_SENHA
					estadoConfirmaSenha = 1; //Coloca a variável estadoConfirmaSenha para 1 para ir para o primeiro nivel deste menu
					identador = 6; //Armazena em identador a posição de coluna 6 do cursor
					teclapressionada = 0; //Limpa teclapressionada
					ch = 0x30; //Armazena em ch o valor zero
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					SetaCaracterSenha(identador); //Posiciona o cursor na coluna conforme o valor do identador passado
					confirma_senha[identador-6] = ch; //Armazena no vetor confirma_senha na posição identador-6, exemplo: se identador é 6 será confirma_senha[0]. Armazena o conteúdo de ch
					identador++; //Incrementa identador
					COLUNA = identador; //Armazena em coluna a posição identador
					PosicionaLCD(pos); //Posiciona o cursor na coluna especificada
					ch = 0x30; //Armazena em ch o número zero
					C = 0x30; //Aramazena em C o número zero
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					if(C == 0X39) //Se C for igual a 9 então
					{
						C = 0X41; //Armazena em C o valor A
						EscreveChar(C); //Escreve na posição especificada o valor A
						COLUNA = identador; //Armazena em coluna a posição identador
						PosicionaLCD(pos); //Posiciona o cursor na coluna informada
					}
					else if(C == 0x5A) //Senão se C for igual a Z então
					{
						C = 0x30; //Aramazena em C o número zero
						EscreveChar(C); //Escreve na posição especificada o valor 0
						COLUNA = identador; //Armazena em coluna a posição identador
						PosicionaLCD(pos); //Posiciona o cursor na coluna informada
					}
					else //Senão
					{
						C++; //Incrementa C
						EscreveChar(C); //Escreve na posição especificada o valor correspondente na tabela ASCII
						COLUNA = identador; //Armazena em coluna a posição identador
						PosicionaLCD(pos); //Posiciona o cursor na coluna informada
					}
					ch = C; //Armazena na variável ch o último valor de C conforme alterações acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					if(C == 0x30) //Se C for igual a zero então
					{
						C = 0x5A; //Armazena em C o valor Z
						EscreveChar(C); //Escreve na posição especificada o valor correspondente na tabela ASCII
						COLUNA = identador; //Armazena em coluna a posição identador
						PosicionaLCD(pos); //Posiciona o cursor na coluna informada
					}
					else if(C == 0x41) //Se C for igual a A então
					{
						C = 0x39; //Armazena em C o valor 9
						EscreveChar(C); //Escreve na posição especificada o valor correspondente na tabela ASCII
						COLUNA = identador; //Armazena em coluna a posição identador
						PosicionaLCD(pos); //Posiciona o cursor na coluna informada
					}
					else //Senão
					{
						C--; //Decrementa C
						EscreveChar(C); //Escreve na posição especificada o valor correspondente na tabela ASCII
						COLUNA = identador; //Armazena em coluna a posição identador
						PosicionaLCD(pos); //Posiciona o cursor na coluna informada
					}
					ch = C; //Armazena na variável ch o último valor de C conforme alterações acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				break;
			}
			if(identador >= 12) //Se identador for maior igual a 12 então
			{
				estadoConfirmaSenha = 3; //Coloca a variável estadoConfirmaSenha para 3 para ir para o próximo case
				identador = 6; //Retorna o valor de identador para 6 para que a senha possa ser digitada novamente
				ch = 0x30; //Armazena em ch o valor zero
			}
			break;
		}
		case 3: //VERIFICA SE SENHA A SER ALTERADA É REALMENTE IGUAL A SENHA DE CONFIRMAÇÃO PARA REALMENTE ALTERAR
		{


			if(definicoes == 1)	//Se definicoes for igual a 1 então ALTERA SENHA DA GERENCIA
			{
				for(j = 0; j < 6; j++) //Confirma os 6 caracteres da senha
				{
					if(senha[j] != confirma_senha[j]) //Se em algum momento senha digitada não for igual a senha digitada de novo para confirmar então
					{
						verifica_senha = SENHA_INCORRETA; //Armazena na variável verifica_senha a informação SENHA_INCORRETA
						break;
					}
				}
				if(j == 6) //Se j for igual a 6 então
				{
					estadoConfirmaSenha = 4; //Coloca a variável estadoConfirmaSenha para 4 para ir para o próximo case
					break;
				}
			}
			else if(definicoes == 2) //Senão se definicoes for igual a 2 então ALTERA SENHA DO TÉCNICO
			{
				for(j = 0; j < 6; j++) //Confirma os 6 caracteres da senha
				{
					if(senha[j] != confirma_senha[j]) //Se em algum momento senha digitada não for igual a senha digitada de novo para confirmar então
					{
						verifica_senha = SENHA_INCORRETA; //Armazena na variável verifica_senha a informação SENHA_INCORRETA
						break;
					}
				}
				if(j == 6) //Se j for igual a 6 então
				{
					estadoConfirmaSenha = 5; //Coloca a variável estadoConfirmaSenha para 4 para ir para o próximo case
					break;
				}
			}
			if(verifica_senha == SENHA_INCORRETA) //Se verifica_senha for igual a SENHA_INCORRETA então
			{
				tela = TELA_SENHA_INCORRETA; //Tela é igual a TELA_SENHA_INCORRETA
				Atualiza_LCD(); //Atualiza o LCD com a tela acima
				estadoConfirmaSenha = 1; //Coloca a variável estadoConfirmaSenha para 1 para ir para o primeiro nivel deste menu
				delay_ms(2000);
				if(estado_troca_senha == ESTADO_SOLICITA_TROCA_SENHA){
					estado = ESTADO_ALTERA_SENHA;
				}else{
					estado = ESTADO_AJUSTES_DO_SISTEMA; //Estado a ser executado é ESTADO_AJUSTES_DO_SISTEMA
				}
				identador = 6; //Armazena a variável identador com o valor 6
				teclapressionada = 0; //Limpa teclapressionada
			}
			break;
		}
		case 4: //GRAVA A SENHA DA GERÊNCIA
		{
			for(j = 0;j < 6;j++) //Grava os 6 caracteres da senha
			{
				buffer_senhas[j] = confirma_senha[j]; //Armazena nas 6 posições de buffer_senhas nas 6  primeiras posições de confirma_senha
				Write_Buffer_FLASH[j] = confirma_senha[j]; //Coloca os 6 valores da senha da gerência alterada no vetor para gravação na memória FLASH
			}
			ESCREVE_FLASH_INTERNA(endFLASHSenhadaGerencia,6,0); //Escreve na memória FLASH a senha da gerência alterada no endereço especificado
			fnGravaAuditoria(19,0,1,OPERADOR,DISPOSITIVO);
			estadoConfirmaSenha = 6; //Coloca a variável estadoConfirmaSenha para 6 para ir para o próximo case
			if(senha_gerente_trocada == FALSE){
				identador = 6; //Armazena em identador a posição de coluna 6 do cursor
				teclapressionada = 0; //Limpa teclapressionada
				estadoConfirmaSenha = 1; //Coloca a variável estadoConfirmaSenha para 1 para ir para o primeiro nivel deste menu
				senha_gerente_trocada = TRUE;
				Write_Buffer_FLASH[0] = senha_gerente_trocada;
				ESCREVE_FLASH_INTERNA(endFLASH_SENHA_GERENTE_TROCADA,1,0);
			}
			break;
		}
		case 5: //GRAVA A SENHA DO TÉCNICO
		{
			for(j = 6;j < 12;j++) //Grava os 6 caracteres da senha
			{
				buffer_senhas[j] = confirma_senha[j - 6]; //Armazena nas 6 posições de buffer_senhas nas 6 segundas posições de confirma_senha
				Write_Buffer_FLASH[j - 6] = confirma_senha[j - 6]; //Coloca os 6 valores da senha do técnico alterada no vetor para gravação na memória FLASH
			}
			ESCREVE_FLASH_INTERNA(endFLASHSenhadoTecnico,6,0); //Escreve na memória FLASH a senha do técnico alterada no endereço especificado
			fnGravaAuditoria(20,0,1,OPERADOR,DISPOSITIVO);
			estadoConfirmaSenha = 6; //Coloca a variável estadoConfirmaSenha para 6 para ir para o próximo case
			if(senha_tecnico_trocada == FALSE){
				identador = 6; //Armazena em identador a posição de coluna 6 do cursor
				teclapressionada = 0; //Limpa teclapressionada
				estadoConfirmaSenha = 1; //Coloca a variável estadoConfirmaSenha para 1 para ir para o primeiro nivel deste menu
				senha_tecnico_trocada = TRUE;
				Write_Buffer_FLASH[0] = senha_tecnico_trocada;
				ESCREVE_FLASH_INTERNA(endFLASH_SENHA_TECNICO_TROCADA,1,0);
			}
			break;
			break;
		}
		case 6: //RETORNA AO PRIMEIRO NIVEL DO MENU ALTERA SENHA PARA ESCOLHER ENTRE ALTERAR SENHA DA GERENCIA OU TECNICO
		{
			tela = TELA_MOSTRA_AJUSTES_DO_SISTEMA; //Tela é igual a TELA_MOSTRA_AJUSTES_DO_SISTEMA
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estado = ESTADO_AJUSTES_DO_SISTEMA; //Estado a ser executado é ESTADO_AJUSTES_DO_SISTEMA
			identador = 6; //Armazena em identador a posição de coluna 6 do cursor
			teclapressionada = 0; //Limpa teclapressionada
			estadoConfirmaSenha = 1; //Coloca a variável estadoConfirmaSenha para 1 para ir para o primeiro nivel deste menu
		}
		break;
	}
}

void fnResetarPadraoFabrica(void) //Permite resetar todos os parâmetros do detector de metais para os valores padrões de fábrica
{
	static byte estadoResetarPadraoFabrica = 1; //Definindo variável estadoResetarPadraoFabrica para o switch case abaixo

	switch(estadoResetarPadraoFabrica) //Conforme valor da variável estadoResetarPadraoFabrica vai para o case específico
	{
		case 1: //ENTRA NO MENU RESETAR PADRÃO DE FÁBRICA
		{
			confirma = NAO; //Armazena na variável confirma a informação NAO
			tela = TELA_VOCE_TEM_CERTEZA; //Tela é igual a TELA_VOCE_TEM_CERTEZA
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estadoResetarPadraoFabrica = 2; //Coloca a variável estadoResetarPadraoFabrica para 2 para ir para o case específico
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //DECISÃO PARA RESETAR OU NÃO PARA OS PADRÕES DE FÁBRICA
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
						estadoResetarPadraoFabrica = 2; //Coloca a variável estadoResetarPadraoFabrica para 2 para ir para o case específico
						teclapressionada = 0; //Limpa teclapressionada
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
						estadoResetarPadraoFabrica = 2; //Coloca a variável estadoResetarPadraoFabrica para 2 para ir para o case específico
						teclapressionada = 0; //Limpa teclapressionada
					}
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					if(confirma == SIM) //Se confirma for igual a SIM então
					{
						GravaPadroesFabrica(); //Grava padrões de fábrica
					}
					fnGravaAuditoria(21,0,1,OPERADOR,DISPOSITIVO);
					estadoResetarPadraoFabrica = 1; //Coloca a variável estadoResetarPadraoFabrica para 1 para ir para o primeiro nivel deste menu
					tela = TELA_MOSTRA_AJUSTES_DO_SISTEMA; //Tela é igual a TELA_MOSTRA_AJUSTES_DO_SISTEMA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_AJUSTES_DO_SISTEMA; //Estado a ser executado é ESTADO_AJUSTES_DO_SISTEMA
					teclapressionada = 0; //Limpa teclapressionada
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU AJUSTES DO SISTEMA no primeiro nível
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					estadoResetarPadraoFabrica = 1; //Coloca a variável estadoResetarPadraoFabrica para 1 para ir para o primeiro nivel deste menu
					tela = TELA_MOSTRA_AJUSTES_DO_SISTEMA; //Tela é igual a TELA_MOSTRA_AJUSTES_DO_SISTEMA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_AJUSTES_DO_SISTEMA; //Estado a ser executado é ESTADO_AJUSTES_DO_SISTEMA
					teclapressionada = 0; //Limpa teclapressionada
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU AJUSTES DO SISTEMA no primeiro nível
					break;
				}
				break;
			}
			break;
		}
		break;
	}
}

void fnConfigurarIdioma(void) //Permite configurar o idioma para português, espanhol ou inglês
{
	static byte estadoConfiguraIdioma = 1,idioma_aux; //Definindo variável estadoConfiguraIdioma para o switch case abaixo, define varíavel idioma_aux para armazenar valor de idioma antes de ser alterado

	switch(estadoConfiguraIdioma) //Conforme valor da variável estadoConfiguraIdioma vai para o case específico
	{
		case 1: //ENTRA NO MENU IDIOMA
		{
			tela = TELA_MOSTRA_IDIOMA; //Tela é igual a TELA_MOSTRA_IDIOMA
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estadoConfiguraIdioma = 2; //Coloca a variável estadoConfiguraIdioma para 2 para ir para o case 2
			idioma_aux = idioma; //Armazena na variável idioma_aux a informação contida em idioma antes de ser alterado
			break;
		}
		case 2: //ALTERA O IDIOMA CORRENTE
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					idioma++; //Incrementa idioma
					if(idioma > 2) //Se idioma for maior que 2 então
					{
						idioma = COD_PORTUGUES; //Armazena na variável idioma a informação COD_PORTUGUES
					}
					tela = TELA_MOSTRA_IDIOMA; //Tela é igual a TELA_MOSTRA_IDIOMA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estadoConfiguraIdioma = 2; //Coloca a variável estadoConfiguraIdioma para 2 para ir para o case 2
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					idioma--; //Decrementa idioma
					if(idioma == 255) //Se idioma for igual a 255 então
					{
						idioma = COD_INGLES; //Armazena na variável idioma a informação COD_INGLES
					}
					tela = TELA_MOSTRA_IDIOMA; //Tela é igual a TELA_MOSTRA_IDIOMA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estadoConfiguraIdioma = 2; //Coloca a variável estadoConfiguraIdioma para 2 para ir para o case 2
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					tela = TELA_MOSTRA_AJUSTES_DO_SISTEMA; //Tela é igual a TELA_MOSTRA_AJUSTES_DO_SISTEMA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estadoConfiguraIdioma = 1; //Coloca a variável estadoConfiguraIdioma para 1 para ir para o primeiro nivel deste menu
					Write_Buffer_FLASH[0] = idioma; //Coloca o valor do idioma alterado no vetor para gravação na memória FLASH
					ESCREVE_FLASH_INTERNA(endFLASHIdioma,1,0); //Escreve na memória FLASH o idioma alterado no endereço especificado
					estado = ESTADO_AJUSTES_DO_SISTEMA; //Estado a ser executado é ESTADO_AJUSTES_DO_SISTEMA
					teclapressionada = 0; //Limpa teclapressionada
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU AJUSTES DO SISTEMA no primeiro nível
					break;
				}
				case teclaCancela:
				{
					idioma = idioma_aux; //Armazena na variável idioma o conteúdo de idioma_aux com a inforamção do idioma antes de alterar
					tela = TELA_MOSTRA_AJUSTES_DO_SISTEMA; //Tela é igual a TELA_MOSTRA_AJUSTES_DO_SISTEMA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estadoConfiguraIdioma = 1; //Coloca a variável estadoConfiguraIdioma para 1 para ir para o primeiro nivel deste menu
					estado = ESTADO_AJUSTES_DO_SISTEMA; //Estado a ser executado é ESTADO_AJUSTES_DO_SISTEMA
					teclapressionada = 0; //Limpa teclapressionada
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU AJUSTES DO SISTEMA no primeiro nível
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


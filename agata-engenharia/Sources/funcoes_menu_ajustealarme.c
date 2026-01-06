/*
 * funcoes_menu_ajustealarme.c
 *
 *  Created on: 22/06/2023
 *      Author: marcos.butignol
 */

#include "funcao.h"

#include "agata_std_functions.h"
#include "agata_hc_definitions.h"
#include "stdlib.h"


void fnConfiguraAlarmeSonoro(void) //Permite configurar o alarme sonoro pelas funções abaixo
{
	static byte estadoConfigurarAlarmeSonoro = 1; //Definindo variável estadoConfigurarAlarmeSonoro para o switch case abaixo

	switch(estadoConfigurarAlarmeSonoro) //Conforme valor da variável estadoAjustesdeAlarme vai para o case específico
	{
		case 1: //ENTRA NO MENU DO ALARME SONORO
		{
			tela = TELA_MOSTRA_ALARME_SONORO; //Tela é igual a TELA_MOSTRA_ALARME_SONORO
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estadoConfigurarAlarmeSonoro = 2; //Coloca a variável estadoConfigurarAlarmeSonoro para 2 para ir para o case 2
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //ESCOLHE ENTRE BUZZER OU MENSAGEM DE VOZ
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					menu2++; //Incrementa menu2
					if(menu2 > 2) //Se menu2 for maior que 2 então
					{
						menu2 = 1; //Armazena em menu2 o valor 1
					}
					tela = TELA_MOSTRA_ALARME_SONORO; //Tela é igual a TELA_MOSTRA_ALARME_SONORO
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					menu2--; //Decrementa menu2
					if(menu2 < 1) //Se menu2 for menor que 1 então
					{
						menu2 = 2; //Armazena em menu2 o valor 2
					}
					tela = TELA_MOSTRA_ALARME_SONORO; //Tela é igual a TELA_MOSTRA_ALARME_SONORO
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					if(menu2 == 1) //Se menu2 for igual a 1 então
					{
						estado = ESTADO_CONFIGURA_BUZZER; //Estado a ser executado é ESTADO_CONFIGURA_BUZZER
					}
					else if(menu2 == 2) //Se menu2 for igual a 2 então
					{
						estado = ESTADO_CONFIGURA_MSG_VOZ; //Estado a ser executado é ESTADO_CONFIGURA_MSG_VOZ
					}
					estadoConfigurarAlarmeSonoro = 1; //Coloca a variável estadoConfigurarAlarmeSonoro para 1 para ir para o primeiro nivel deste menu
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tela = TELA_MOSTRA_AJUSTES_DE_ALARME; //Tela é igual a TELA_MOSTRA_AJUSTES_DE_ALARME
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estadoConfigurarAlarmeSonoro = 1; //Coloca a variável estadoConfigurarAlarmeSonoro para 1 para ir para o primeiro nivel deste menu
					estado = ESTADO_AJUSTES_DE_ALARME; //Estado a ser executado é ESTADO_AJUSTES_DE_ALARME
					teclapressionada = 0; //Limpa teclapresssionada
					flagretorno = 1;  //Torna a flag flag_retorno para 1 para poder retornar ao MENU AJUSTES DE ALARME no primeiro nível
					break;
				}
				break;
			}
			break;
		}
		break;
	}
}

void fnConfiguraBuzzer(void) //Permite configurar o buzzer pelas funções abaixo
{
	static byte estadoConfigurarBuzzer = 1; //Definindo variável estadoConfigurarBuzzer para o switch case abaixo

	switch(estadoConfigurarBuzzer) //Conforme valor da variável estadoConfigurarBuzzer vai para o case específico
	{
		case 1: //ENTRA NO MENU DE CONFIGURAÇÃO DO BUZZER
		{
			tela = TELA_MOSTRA_BUZZER; //Tela é igual a TELA_MOSTRA_BUZZER
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estadoConfigurarBuzzer = 2; //Coloca a variável estadoConfigurarBuzzer para 2 para ir para o case 2
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //ESCOLHE ENTRE O MENU TOM OU VOLUME DO BUZZER
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					menu3++; //Incrementa menu3
					if(menu3 > BUZZER_VOLUME) //Se menu3 for maior que BUZZER_VOLUME então
					{
						menu3 = BUZZER_TOM; //Armazena na variável menu3 a informação BUZZER_TOM
					}
					tela = TELA_MOSTRA_BUZZER; //Tela é igual a TELA_MOSTRA_BUZZER
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTARAVA pressionada então
				case teclaDestrava:
				{
					menu3--; //Decrementa menu3
					if(menu3 == 255) //Se menu3 for igual a 255 então
					{
						menu3 = BUZZER_VOLUME; //Armazena em menu3 a informação BUZZER_VOLUME
					}
					tela = TELA_MOSTRA_BUZZER; //Tela é igual a TELA_MOSTRA_BUZZER
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					if(menu3 == 0) //Se menu3 for igual a zero então
					{
						estado = ESTADO_TOM_DO_BUZZER; //Estado a ser executado é ESTADO_TOM_DO_BUZZER
					}
					else if(menu3 == 1) //Se menu3 for igual a um então
					{
						estado = ESTADO_VOLUME_DO_BUZZER; //Estado a ser executado é ESTADO_VOLUME_DO_BUZZER
					}
					estadoConfigurarBuzzer = 1; //Coloca a variável estadoConfigurarBuzzer para 1 para ir para primeiro nivel deste menu
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					estado = ESTADO_CONFIGURA_ALARME_SONORO; //Estado a ser executado é ESTADO_CONFIGURA_ALARME_SONORO
					estadoConfigurarBuzzer = 1; //Coloca a variável estadoConfigurarBuzzer para 1 para ir para primeiro nivel deste menu
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

void fnConfiguraTomBuzzer(void) //Permite configurar o tom do buzzer
{
	static byte estadoConfiguraTomBuzzer = 1,buzzer_tom_aux = 0; //Definindo variável estadoConfiguraTomBuzzer para o switch case abaixo, define a variável buzzer_tom_aux para armazenar o valor do tom do buzzer antes de ser alterado

	switch(estadoConfiguraTomBuzzer) //Conforme valor da variável estadoConfiguraTomBuzzer vai para o case específico
	{
		case 1: //ENTRA NO MENU TOM DO BUZZER
		{
			tela = TELA_MOSTRA_TOM_DO_BUZZER; //Tela é igual a TELA_MOSTRA_TOM_DO_BUZZER
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			buzzer_tom_aux = buffer_buzzer[BUZZER_TOM]; //Armazena na variável buzzer_tom_aux o valor do tom do buzzer antes de ser alterado
			TocaTomBuzzer(); //Toca o tom do buzzer para dar uma amostra
			estadoConfiguraTomBuzzer = 2; //Coloca a variável estadoConfiguraTomBuzzer para 2 para ir para case 2
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //ESCOLHE O TOM DO BUZZER
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					LINHA = 2; //Se posiciona na linha 2
					COLUNA = 7; //Se posiciona na coluna 7
					buffer_buzzer[BUZZER_TOM]++; //Incrementa o tom o buzzer
					if(buffer_buzzer[BUZZER_TOM] > 10) //Se o tom do buzzer for maior que 10 então
					{
						buffer_buzzer[BUZZER_TOM] = 1; //Armazena no vetor buffer_buzzer[BUZZER_TOM] o valor 1
					}
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificadas
					EscreveChar(' '); //Escreve espaço
					EscreveChar((char)(buffer_buzzer[BUZZER_TOM]/10 + 48)); //Escreve a parte da dezena do tom
					EscreveChar((char)(buffer_buzzer[BUZZER_TOM]%10 + 48)); //Escreve a parte da unidade do tom
					TocaTomBuzzer(); //Toca o tom do buzzer para dar uma amostra
					estadoConfiguraTomBuzzer = 2; //Coloca a variável estadoConfiguraTomBuzzer para 2 para ir para case 2
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					LINHA = 2; //Se posiciona na linha 2
					COLUNA = 7; //Se posiciona na coluna 7
					buffer_buzzer[BUZZER_TOM]--; //Decrementa o tom do buzzer
					if(buffer_buzzer[BUZZER_TOM] < 1) //Se o tom do buzzer for menor que 1 então
					{
						buffer_buzzer[BUZZER_TOM] = 10; //Armazena no vetor buffer_buzzer[BUZZER_TOM] o valor 10
					}
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificadas
					EscreveChar(' '); //Escreve espaço
					EscreveChar((char)(buffer_buzzer[BUZZER_TOM]/10 + 48)); //Escreve a parte da dezena do tom
					EscreveChar((char)(buffer_buzzer[BUZZER_TOM]%10 + 48)); //Escreve a parte da unidade do tom
					TocaTomBuzzer(); //Toca o tom do buzzer para dar uma amostra
					estadoConfiguraTomBuzzer = 2; //Coloca a variável estadoConfiguraTomBuzzer para 2 para ir para case 2
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					tela = TELA_TOM_DO_BUZZER; //Tela é igual a TELA_TOM_DO_BUZZER
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_CONFIGURA_BUZZER; //Estado a ser executado é ESTADO_CONFIGURA_BUZZER
					estadoConfiguraTomBuzzer = 1; //Coloca a variável estadoConfiguraTomBuzzer para 1 para ir para o primeiro nivel deste menu
					Write_Buffer_FLASH[0] = buffer_buzzer[BUZZER_TOM]; //Coloca o valor do tom do buzzer alterado no vetor para gravação na memória FLASH
					ESCREVE_FLASH_INTERNA(endFLASHBuzzerTom,1,0); //Escreve na memória FLASH o tom do buzzer alterado no endereço especificado
					fnGravaAuditoria(23,buzzer_tom_aux,buffer_buzzer[BUZZER_TOM],OPERADOR,DISPOSITIVO);
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tela = TELA_TOM_DO_BUZZER; //Tela é igual a TELA_TOM_DO_BUZZER
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_CONFIGURA_BUZZER; //Estado a ser executado é ESTADO_CONFIGURA_BUZZER
					estadoConfiguraTomBuzzer = 1; //Coloca a variável estadoConfiguraTomBuzzer para 1 para ir para o primeiro nivel deste menu
					buffer_buzzer[BUZZER_TOM] = buzzer_tom_aux; //Armazena no vetor buffer_buzzer[BUZZER_TOM] o último valor do tom do buzzer antes de ser alterado
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

void fnConfiguraVolumeBuzzer(void) //Permite configurar o volume do buzzer
{
	static byte estadoConfiguraVolumeBuzzer = 1,buzzer_volume_aux = 0; //Definindo variável estadoConfiguraVolumeBuzzer para o switch case abaixo, define a variável volume_aux para armazenar o valor do volume antes de ser alterado

	switch(estadoConfiguraVolumeBuzzer) //Conforme valor da variável estadoConfiguraTomBuzzer vai para o case específico
	{
		case 1: //ENTRA NO MENU VOLUME DO BUZZER
		{
			tela = TELA_MOSTRA_VOLUME_DO_BUZZER; //Tela é igual a TELA_MOSTRA_VOLUME_DO_BUZZER
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			buzzer_volume_aux = buffer_buzzer[BUZZER_VOLUME]; //Armazena no buzzer_volume_aux o vetor buffer_buzzer[BUZZER_VOLUME] que é o último valor do volume antes de ser alterado
			TocaTomBuzzer(); //Toca o tom do buzzer para dar uma amostra
			estadoConfiguraVolumeBuzzer = 2; //Coloca a variável estadoConfiguraTomBuzzer para 2 para ir para o case 2
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //ALTERA O VOLUME DO BUZZER
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					LINHA = 2; //Se posiciona na linha 2
					COLUNA = 8; //Se posiciona na coluna 8
					buffer_buzzer[BUZZER_VOLUME]++; //Incrementa o volume do buzzer
					if(buffer_buzzer[BUZZER_VOLUME] > 5) //Se volume do buzzer for maior que 10 então
					{
						buffer_buzzer[BUZZER_VOLUME] = 0; //Armazena no vetor buffer_buzzer[BUZZER_VOLUME] o valor 0
					}
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
					EscreveChar((char)(buffer_buzzer[BUZZER_VOLUME])/10 + 48); //Escreve a parte da dezena do volume
					EscreveChar((char)(buffer_buzzer[BUZZER_VOLUME])%10 + 48); //Escreve a parte da unidade do volume
					TocaTomBuzzer(); //Toca o tom do buzzer para dar uma amostra
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					LINHA = 2; //Se posiciona na linha 2
					COLUNA = 8; //Se posiciona na coluna 8
					buffer_buzzer[BUZZER_VOLUME]--; //Decrementa o volume do buzzer
					if(buffer_buzzer[BUZZER_VOLUME] == 255) //Se volume do buzzer for igual a 255 então
					{
						buffer_buzzer[BUZZER_VOLUME] = 5; //Armazena no vetor buffer_buzzer[BUZZER_VOLUME] o valor 10
					}
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
					EscreveChar((char)(buffer_buzzer[BUZZER_VOLUME])/10 + 48); //Escreve a parte da dezena do volume
					EscreveChar((char)(buffer_buzzer[BUZZER_VOLUME])%10 + 48); //Escreve a parte da unidade do volume
					TocaTomBuzzer(); //Toca o tom do buzzer para dar uma amostra
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					Write_Buffer_FLASH[0] = buffer_buzzer[BUZZER_VOLUME]; //Coloca o valor do volume do buzzer alterado no vetor para gravação na memória FLASH
					ESCREVE_FLASH_INTERNA(endFLASHBuzzerVolume,1,0); //Escreve na memória FLASH o volume do buzzer alterado no endereço especificado
					fnGravaAuditoria(24,buzzer_volume_aux,buffer_buzzer[BUZZER_VOLUME],OPERADOR,DISPOSITIVO);
					tela = TELA_VOLUME_DO_BUZZER; //Tela é igual a TELA_VOLUME_DO_BUZZER
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_CONFIGURA_BUZZER; //Estado a ser executado é ESTADO_CONFIGURA_BUZZER
					estadoConfiguraVolumeBuzzer = 1; //Coloca a variável estadoConfiguraVolumeBuzzer para 1 para ir para o primeiro nivel deste menu
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tela = TELA_VOLUME_DO_BUZZER; //Tela é igual a TELA_VOLUME_DO_BUZZER
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_CONFIGURA_BUZZER; //Estado a ser executado é ESTADO_CONFIGURA_BUZZER
					estadoConfiguraVolumeBuzzer = 1; //Coloca a variável estadoConfiguraVolumeBuzzer para 1 para ir para o primeiro nivel deste menu
					buffer_buzzer[BUZZER_VOLUME] = buzzer_volume_aux; //Armazena no vetor buffer_buzzer[BUZZER_VOLUME] o último valor do volume antes de ser alterado
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

void fnConfiguraMsgVoz(void) //Permite configurar a mensagem de voz pelas funções abaixo
{
	static byte estadoConfigurarMsgVoz = 1; //Definindo variável estadoConfigurarMsgVoz para o switch case abaixo

	switch(estadoConfigurarMsgVoz) //Conforme valor da variável estadoConfigurarMsgVoz vai para o case específico
	{
		case 1: //ENTRA NO MENU MENSAGEM DE VOZ
		{
			tela = TELA_MOSTRA_MSG_VOZ; //Tela é igual a TELA_MOSTRA_MSG_VOZ
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estadoConfigurarMsgVoz = 2; //Coloca a variável estadoConfigurarMsgVoz para 2 para ir para o case 2
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //DECIDE ENTRAR PARA ALTERAR VOLUME DA MENSAGEM DE VOZ
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					estado = ESTADO_VOLUME_MSG_VOZ; //Estado a ser executado é ESTADO_VOLUME_MSG_VOZ
					estadoConfigurarMsgVoz = 1; //Coloca a variável estadoConfigurarMsgVoz para 1 para ir para o primeiro nivel deste menu
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					estado = ESTADO_CONFIGURA_ALARME_SONORO; //Estado a ser executado é ESTADO_CONFIGURA_ALARME_SONORO
					estadoConfigurarMsgVoz = 1; //Coloca a variável estadoConfigurarMsgVoz para 1 para ir para o primeiro nivel deste menu
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

void fnConfiguraVolumeMsgVoz(void) //Permite configurar o volume da mensagem de voz
{
	static byte estadoConfiguraVolumeMsgVoz = 1,volume_mensagem_voz_aux = 0; //Definindo variável estadoConfiguraVolumeMsgVoz para o switch case abaixo,  define a variável volume_mensagem_voz_aux para armazenar o valor do volume antes de ser alterado

	switch(estadoConfiguraVolumeMsgVoz) //Conforme valor da variável estadoConfiguraVolumeMsgVoz vai para o case específico
	{
		case 1: //ENTRA NO MENU VOLUME DA MENSAGEM DE VOZ
		{
			tela = TELA_MOSTRA_VOLUME_MSG_VOZ; //Tela é igual a TELA_MOSTRA_VOLUME_MSG_VOZ
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			volume_mensagem_voz_aux = volume_mensagem_voz; //Armazena na variável volume_mensagem_voz_aux o último valor de volume antes de ser alterado
			estadoConfiguraVolumeMsgVoz = 2; //Coloca a variável estadoConfiguraVolumeMsgVoz para 2 para ir para o case 2
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //ALTERA O VOLUME DA MENSAGEM DE VOZ
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					volume_mensagem_voz++; //Incrementa volume da mensagem de voz
					if(volume_mensagem_voz > 31) //Se volume da mensagem de voz for maior que 10 então
					{
						char lowerAllVolume[] = "    AGUARDE     ";
						volume_mensagem_voz = 0; //Armazena na variável volume_mensagem_voz o valor 0
						LINHA = 2; //Se posiciona na linha 2
						COLUNA = 1; //Se posiciona na coluna 8
						PosicionaLCD(pos);
						EscreveLCD(lowerAllVolume,pos);

						fnDiminuiTodoVolume(); //Diminui todo o volume da mensagem de voz

						memset(lowerAllVolume,' ',strlen(lowerAllVolume));
						LINHA = 2; //Se posiciona na linha 2
						COLUNA = 1; //Se posiciona na coluna 8
						PosicionaLCD(pos);
						EscreveLCD(lowerAllVolume,pos);
					}
					else //Senão
					{
						fnAumentaVolume(1); //Aumenta o volume da mensagem de voz em 1 unidade
					}
					LINHA = 2; //Se posiciona na linha 2
					COLUNA = 8; //Se posiciona na coluna 8
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
					EscreveChar((char)(volume_mensagem_voz)/10 + 48); //Escreve a parte da dezena do volume da mensagem de voz
					EscreveChar((char)(volume_mensagem_voz)%10 + 48); //Escreve a parte da unidade do volume da mensagem de voz
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					LINHA = 2; //Se posiciona na linha 2
					COLUNA = 8; //Se posiciona na coluna 8
					volume_mensagem_voz--; //Decrementa volume da mensagem de voz
					if(volume_mensagem_voz == 255) //Se volume da mensagem de voz for igual a 255 então
					{
						volume_mensagem_voz = 31; //Armazena na variável volume_mensagem_voz o valor 10
						fnAumentaVolume(31); //Aumenta o volume da mensagem de voz em 10 unidade
					}
					else
					{
						fnDiminuiVolume(1); //Diminui o volume da mensagem de voz em 1 unidade
					}
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
					EscreveChar((char)(volume_mensagem_voz)/10 + 48); //Escreve a parte da dezena do volume da mensagem de voz
					EscreveChar((char)(volume_mensagem_voz)%10 + 48); //Escreve a parte da unidade do volume da mensagem de voz
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA então
				case teclaConfirma_Remoto:
				{
					Write_Buffer_FLASH[0] = volume_mensagem_voz; //Coloca o valor do volume da mensagem de voz alterado no vetor para gravação na memória FLASH
					ESCREVE_FLASH_INTERNA(endFLASHMensagemVozVolume,1,0); //Escreve na memória FLASH o volume da mensagem de voz alterado no endereço especificado
					fnGravaAuditoria(25,volume_mensagem_voz_aux,volume_mensagem_voz,OPERADOR,DISPOSITIVO);
					tela = TELA_MOSTRA_MSG_VOZ; //Tela é igual a TELA_MOSTRA_MSG_VOZ
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_CONFIGURA_MSG_VOZ; //Estado a ser executado é ESTADO_CONFIGURA_MSG_VOZ
					estadoConfiguraVolumeMsgVoz = 1; //Coloca a variável estadoConfiguraVolumeMsgVoz para 1 para ir para o primeiro nivel deste menu
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA então
				{
					tela = TELA_MOSTRA_MSG_VOZ; //Tela é igual a TELA_MOSTRA_MSG_VOZ
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_CONFIGURA_MSG_VOZ; //Estado a ser executado é ESTADO_CONFIGURA_MSG_VOZ
					estadoConfiguraVolumeMsgVoz = 1; //Coloca a variável estadoConfiguraVolumeMsgVoz para 1 para ir para o primeiro nivel deste menu
					volume_mensagem_voz = volume_mensagem_voz_aux; //Armazena na variável volume_mensagem_voz o último valor do volume antes de ser alterado
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

void fnConfiguraLigDesAlarmeVisual(void) //Permite ligar e desligar o alarme visual
{
	static byte estadoConfiguraAlarmeVisual = 1; //Definindo variável estadoConfiguraAlarmeVisual para o switch case abaixo
	static byte alarme_visual_aux = 0; //Define a variável alarme_visual_aux para armazenar o valor do alarme antes de ser alterado

	switch(estadoConfiguraAlarmeVisual) //Conforme valor da variável estadoConfiguraAlarmeVisual vai para o case específico
	{
		case 1: //ENTRA NO MENU ALARME VISUAL
		{
			//alarme_visual_aux = alarme_visual; //Armazena na variável alarme_visual_aux o último valor do alarme_visual antes de ser alterado
			tela = TELA_SETA_ALARME_VISUAL_LIGAR_DESLIGAR; //Tela é igual a TELA_SETA_ALARME_VISUAL_LIGAR_DESLIGAR
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estadoConfiguraAlarmeVisual = 2; //Coloca a variável estadoConfiguraAlarmeVisual para 2 para ir para o case 2
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //ALTERA O ESTADO DO ALARME VISUAL
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla DECREMENTA ou tecla TRAVA ou tecla DESTRAVA pressionada então
				case teclaDecrementa:
				case teclaTrava:
				case teclaDestrava:
				{
					if(alarme_visual == NAO) //Se alarme_visual for igual a NAO então
					{
						alarme_visual = SIM; //Armazena na variável alarme_visual a informação SIM
						tela = TELA_SETA_ALARME_VISUAL_LIGAR_DESLIGAR; //Tela é igual a TELA_SETA_ALARME_VISUAL_LIGAR_DESLIGAR
						estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
						teclapressionada = 0; //Limpa teclapressionada
					}
					else if(alarme_visual == SIM) //Senão se alarme_visual for igual a SIM então
					{
						alarme_visual = NAO; //Armazena na variável alarme_visual a informação NAO
						tela = TELA_SETA_ALARME_VISUAL_LIGAR_DESLIGAR; //Tela é igual a TELA_SETA_ALARME_VISUAL_LIGAR_DESLIGAR
						estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
						teclapressionada = 0; //Limpa teclapressionada
					}
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					Write_Buffer_FLASH[0] = alarme_visual; //Coloca o valor do alarme_visual alterado no vetor para gravação na memória FLASH
					ESCREVE_FLASH_INTERNA(endFLASHAlarmeVisualLigDes,1,0); //Escreve na memória FLASH o alarme_visual alterado no endereço especificado
					tela = TELA_ALARME_VISUAL; //Tela é igual a TELA_ALARME_VISUAL
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estadoConfiguraAlarmeVisual = 1; //Coloca a variável estadoConfiguraAlarmeVisual para 1 para ir para o primeiro nivel deste menu
					estado = ESTADO_AJUSTES_DE_ALARME; //Estado a ser executado é ESTADO_AJUSTES_DE_ALARME
					teclapressionada = 0; //Limpa teclapressionada
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU AJUSTES DE ALARME no primeiro nível
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					alarme_visual = alarme_visual_aux; //Armazena na variável alarme_visual o último valor de alarme_visual antes de ser alterado
					tela = TELA_ALARME_VISUAL; //Tela é igual a TELA_ALARME_VISUAL
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estadoConfiguraAlarmeVisual = 1; //Coloca a variável estadoConfiguraAlarmeVisual para 1 para ir para o primeiro nivel deste menu
					estado = ESTADO_AJUSTES_DE_ALARME; //Estado a ser executado é ESTADO_AJUSTES_DE_ALARME
					teclapressionada = 0; //Limpa teclapressionada
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU AJUSTES DE ALARME no primeiro nível
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

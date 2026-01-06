
#include "funcao.h"
#include "main.h"

#include "agata_std_functions.h"
#include "agata_hc_definitions.h"
#include "stdlib.h"
#include "time.h"

#include "base64.h"

#include "SERIAL_ETHERNET.h"



#define JSON_ALPHANUM 90
#define JSON_NUMERICO 91


#define JSON_MEIO_OBJECT 100
#define JSON_FINAL_OBJECT 101


extern volatile byte numero_serie[6];

/*** Funções do MÓDULO ETHERNET ***/
void fnDigiteIP(void) //Função que permite digitar o IP corretamente dentro do campo IP
{
	static byte estadoDigitaIP = 1; //Define a variável estadoDigitaIP para o switch case abaixo
	static byte identador = 1; //Define identador para ir posicionando o cursor nos campos de digitação

	switch(estadoDigitaIP) //Conforme variável estadoDigitaIP vai para o case específico
	{
		case 1: //Entra para digitar o IP
		{
			if(estado == ESTADO_DIGITE_IP) //Se estado for igual a ESTADO_DIGITE_IP então
			{
				ch = end_IP[0]; //ch vai receber o primeiro byte do vetor end_IP[0]
			}
			else if(estado == ESTADO_DIGITE_MASCARA_SUB_REDE) //Senão se estado for igual a ESTADO_DIGITE_MASCARA_SUB_REDE então
			{
				ch = end_SUB_MASK[0]; //ch vai receber o primeiro byte do vetor end_SUB_MASK[0]
			}
			else if(estado == ESTADO_DIGITE_GATEWAY) //Senão se estado for igual a ESTADO_DIGITE_GATEWAY então
			{
				ch = end_GATEWAY[0]; //ch vai receber o primeiro byte do vetor end_GATEWAY[0]
			}
			else if(estado == ESTADO_DIGITE_DNS) //Senão se estado for igual a ESTADO_DIGITE_DNS então
			{
				ch = end_DNS[0]; //ch vai receber o primeiro byte do vetor end_DNS[0]
			}
			SetaCaracterIP(identador); //Função que vai deslocando o caracter no campo endereço
			estadoDigitaIP = 2; //Armazena na variável estadoDigitaIP o valor 2 para ir para o case 2
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //Permite ir digitando o IP
		{
			if(teclapressionada == teclaCancela) //Se teclapressionada for igual a tecla CANCELA então
			{
				tela = TELA_MOSTRA_CONFIGURACOES_DA_INTERNET; //Tela é igual a TELA_MOSTRA_CONFIGURACOES_DA_INTERNET
				estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
				estado = ESTADO_CONFIGURACOES_DE_INTERNET; //Estado a ser executado é ESTADO_CONFIGURACOES_DE_INTERNET
				estadoDigitaIP = 1; //Armazena na variável estadoDigitaIP o valor 1 para ir para o primeiro nivel deste menu
				identador = 1; //Armazena na variável identador o valor 1 para se posicionar no primeiro campo do endereço
				teclapressionada = 0; //Limpa teclapressionada
				ch = 0x30; //Armazena na variável ch a informação 0
				C = ch; //Armazena na variável C o conteúdo de ch
				break;
			}
			if(teclapressionada == teclaConfirma || teclapressionada == teclaConfirma_Remoto) //Se teclapressionada for igual a tecla CONFIRMA então
			{
				if(alterou == 1) //Se alterou for igual a 1
				{
					ch = C; //Armazena na variável ch o conteúdo de C
					end_aux[identador - 1] = ch; //Armazena no vetor end_aux[identador - 1] o conteúdo de ch
					alterou = 0; //Zera a variável alterou
				}
				else //Senão
				{
					if(estado == ESTADO_DIGITE_IP) //Se estado for igual a ESTADO_DIGITE_IP então
					{
						ch = end_IP[identador - 1]; //Armazena em ch o conteúdo de end_IP[identador - 1]
						end_aux[identador - 1] = ch; //Armazena em end_aux[identador - 1] o conteúdo de ch
					}
					else if(estado == ESTADO_DIGITE_MASCARA_SUB_REDE) //Senão se estado for igual a ESTADO_DIGITE_MASCARA_SUB_REDE então
					{
						ch = end_SUB_MASK[identador - 1]; //Armazena em ch o conteúdo de end_SUB_MASK[identador - 1]
						end_aux[identador - 1] = ch; //Armazena em end_aux[identador - 1] o conteúdo de ch
					}
					else if(estado == ESTADO_DIGITE_GATEWAY) //Senão se estado for igual a ESTADO_DIGITE_GATEWAY então
					{
						ch = end_GATEWAY[identador - 1]; //Armazena em ch o conteúdo de end_GATEWAY[identador - 1]
						end_aux[identador - 1] = ch; //Armazena em end_aux[identador - 1] o conteúdo de ch
					}
					else if(estado == ESTADO_DIGITE_DNS) //Senão se estado for igual a ESTADO_DIGITE_DNS então
					{
						ch = end_DNS[identador - 1]; //Armazena em ch o conteúdo de end_DNS[identador - 1]
						end_aux[identador - 1] = ch; //Armazena em end_aux[identador - 1] o conteúdo de ch
					}
				}
				SetaCaracterIP(identador); //Posiciona o cursor na coluna conforme o valor do identador passado
				if(identador == 4) //Se identador for igual a 4 então
				{
					end_aux[identador - 1] = '.'; //Armazena em end_aux[identador - 1] a informação '.'
				}
				else if(identador == 8) //Senão se identador for igual a 8 então
				{
					end_aux[identador - 1] = '.'; //Armazena em end_aux[identador - 1] a informação '.'
				}
				else if(identador == 12) //Senão se identador for igual a 12 então
				{
					end_aux[identador - 1] = '.'; //Armazena em end_aux[identador - 1] a informação '.'
				}
				else //senão
				{
					end_aux[identador - 1] = ch; //Armazena em end_aux[identador - 1] o conteúdo de ch
				}
				identador++; //Incrementa identador para ir para o próximo campo do endereço
				if(identador == 4) //Se identador for igual a 4 então
				{
					identador = 5; //Armazena em identador o valor 5
					if(estado == ESTADO_DIGITE_IP) //Se estado for igual a estado_DIGITE_IP então
					{
						ch = end_IP[identador - 1]; //Armazena na variável ch o conteúdo de end_IP[identador - 1]
					}
					else if(estado == ESTADO_DIGITE_MASCARA_SUB_REDE) //Senão se estado for igual a ESTADO_DIGITE_MASCARA_SUB_REDE então
					{
						ch = end_SUB_MASK[identador - 1]; //Armazena na variável ch o conteúdo de end_SUB_MASK[identador - 1]
					}
					else if(estado == ESTADO_DIGITE_GATEWAY) //Senão se estado for igual a ESTADO_DIGITE_GATEWAY então
					{
						ch = end_GATEWAY[identador - 1]; //Armazena na variável ch o conteúdo de end_GATEWAY[identador - 1]
					}
					else if(estado == ESTADO_DIGITE_DNS) //Senão se estado for igual a ESTADO_DIGITE_DNS então
					{
						ch = end_DNS[identador - 1]; //Armazena na variável ch o conteúdo de end_DNS[identador - 1]
					}
				}
				else if(identador == 8) //Senão se identador for igual a 8 então
				{
					identador = 9; //Armazena em identador o valor 9
					if(estado == ESTADO_DIGITE_IP) //Se estado for igual a estado_DIGITE_IP então
					{
						ch = end_IP[identador - 1]; //Armazena na variável ch o conteúdo de end_IP[identador - 1]
					}
					else if(estado == ESTADO_DIGITE_MASCARA_SUB_REDE) //Senão se estado for igual a ESTADO_DIGITE_MASCARA_SUB_REDE então
					{
						ch = end_SUB_MASK[identador - 1]; //Armazena na variável ch o conteúdo de end_SUB_MASK[identador - 1]
					}
					else if(estado == ESTADO_DIGITE_GATEWAY) //Senão se estado for igual a ESTADO_DIGITE_GATEWAY então
					{
						ch = end_GATEWAY[identador - 1]; //Armazena na variável ch o conteúdo de end_GATEWAY[identador - 1]
					}
					else if(estado == ESTADO_DIGITE_DNS) //Senão se estado for igual a ESTADO_DIGITE_DNS então
					{
						ch = end_DNS[identador - 1]; //Armazena na variável ch o conteúdo de end_DNS[identador - 1]
					}
				}
				else if(identador == 12) //Senão se identador for igual a 12 então
				{
					identador = 13; //Armazena em identador o valor 13
					if(estado == ESTADO_DIGITE_IP) //Se estado for igual a estado_DIGITE_IP então
					{
						ch = end_IP[identador - 1]; //Armazena na variável ch o conteúdo de end_IP[identador - 1]
						end_aux[identador - 1] = ch; //Armazena na variável end_aux[identador - 1] o conteúdo de ch
					}
					else if(estado == ESTADO_DIGITE_MASCARA_SUB_REDE) //Senão se estado for igual a ESTADO_DIGITE_MASCARA_SUB_REDE então
					{
						ch = end_SUB_MASK[identador - 1]; //Armazena na variável ch o conteúdo de end_SUB_MASK[identador - 1]
						end_aux[identador - 1] = ch; //Armazena na variável end_aux[identador - 1] o conteúdo de ch
					}
					else if(estado == ESTADO_DIGITE_GATEWAY) //Senão se estado for igual a ESTADO_DIGITE_GATEWAY então
					{
						ch = end_GATEWAY[identador - 1]; //Armazena na variável ch o conteúdo de end_GATEWAY[identador - 1]
						end_aux[identador - 1] = ch; //Armazena na variável end_aux[identador - 1] o conteúdo de ch
					}
					else if(estado == ESTADO_DIGITE_DNS) //Senão se estado for igual a ESTADO_DIGITE_DNS então
					{
						ch = end_DNS[identador - 1]; //Armazena na variável ch o conteúdo de end_DNS[identador - 1]
						end_aux[identador - 1] = ch; //Armazena na variável end_aux[identador - 1] o conteúdo de ch
					}
				}
				COLUNA = identador; //Armazena na variável COLUNA a posição identador
				PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada acima
				if(estado == ESTADO_DIGITE_IP) //Se estado for igual a ESTADO_DIGITE_IP
				{
					C = end_IP[identador - 1]; //Armazena na variável C o conteúdo de end_IP[identador - 1]
				}
				else if(estado == ESTADO_DIGITE_MASCARA_SUB_REDE) //Senão se estado for igual a ESTADO_DIGITE_MASCARA_SUB_REDE
				{
					C = end_SUB_MASK[identador - 1]; //Armazena na variável C o conteúdo de end_SUB_MASK[identador - 1]
				}
				else if(estado == ESTADO_DIGITE_GATEWAY) //Senão se estado for igual a ESTADO_DIGITE_GATEWAY
				{
					C = end_GATEWAY[identador - 1]; //Armazena na variável C o conteúdo de end_GATEWAY[identador - 1]
				}
				else if(estado == ESTADO_DIGITE_DNS) //Senão se estado for igual a ESTADO_DIGITE_DNS
				{
					C = end_DNS[identador - 1]; //Armazena na variável C o conteúdo de end_DNS[identador - 1]
				}
				teclapressionada = 0; //Limpa teclapressionada
			}
			if(teclapressionada == teclaIncrementa || teclapressionada == teclaTrava) //Se teclapressionada for igual a tecla INCREMENTA ou teclapressionada for igual a tecla TRAVA então
			{
				alterou = 1; //Armazena na variável alterou o valor 1
				if(C == 0X39) //Se C for igual a 9 então
				{
					C = 0X30; //Armazena na variável C a informação 0
					EscreveChar(C); //Escreve o conteúdo de C na posição especificada
					COLUNA = identador; //Armazena na variável COLUNA a posição identador
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada acima
				}
				else //Senão
				{
					C++; //Incrementa C
					EscreveChar(C); //Escreve o conteúdo de C na posição especificada
					COLUNA = identador; //Armazena na variável COLUNA a posição identador
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada acima
				}
				ch = C; //Armazena na variável ch o conteúdo da variável C
				teclapressionada = 0; //Limpa teclapressionada
			}
			if(teclapressionada == teclaDecrementa || teclapressionada == teclaDestrava) //Se teclapressionada for igual a tecla DECREMENTA ou teclapressionada for igual a tecla DESTRAVA então
			{
				alterou = 1; //Armazena na variável alterou o valor 1
				if(C == 0x30) //Se C for igual a 0 então
				{
					C = 0x39; //Armazena na variável C a informação 9
					EscreveChar(C); //Escreve o conteúdo de C na posição especificada
					COLUNA = identador; //Armazena na variável COLUNA a posição identador
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada acima
				}
				else //Senão
				{
					C--; //Decrementa C
					EscreveChar(C); //Escreve o conteúdo de C na posição especificada
					COLUNA = identador; //Armazena na variável COLUNA a posição identador
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada acima
				}
				ch = C; //Armazena na variável ch o conteúdo da variável C
				teclapressionada = 0; //Limpa teclapressionada
			}
			if(identador >= 16) //Se identador for maior ou igual a 16 então
			{
				estadoDigitaIP = 3; //Armazena na variável estadoDigitaIP o valor 3 para ir para o case 3
				identador = 1; //Armazena na variável identador o valor 1 para se posicionar no primeiro campo do IP
				ch = 0x30; //Armazena na variável ch a informação 0
				C = ch; //Armazena na variável C o conteúdo de ch
				if(estado == ESTADO_DIGITE_IP)
				{
					fnGravaAuditoria(14,0,1,OPERADOR,DISPOSITIVO);
				}
				else if(estado == ESTADO_DIGITE_MASCARA_SUB_REDE)
				{
					fnGravaAuditoria(15,0,1,OPERADOR,DISPOSITIVO);
				}
				else if(estado == ESTADO_DIGITE_GATEWAY)
				{
					fnGravaAuditoria(16,0,1,OPERADOR,DISPOSITIVO);
				}
				else if(estado == ESTADO_DIGITE_DNS)
				{
					fnGravaAuditoria(18,0,1,OPERADOR,DISPOSITIVO);
				}
				break;
			}
			break;
		}
		case 3: //Salva o IP,MASCARA DE SUB-REDE e GATEWAY no módulo ethernet
		{
			estadoDigitaIP = 1; //Armazena na variável estadoDigitaIP o valor 1 para ir para o primeiro nivel deste menu

			if(estado == ESTADO_DIGITE_IP) //Se estado for igual a ESTADO_DIGITE_IP então
			{
				for(x = 0;x < 15;x++) //Armazena em end_IP[x] todo o vetor end_aux alterado
				{
					end_IP[x] = end_aux[x];
				}
				fnGravaIPs(); //Grava os endereços IP, máscara de sub-rede e GATEWAY
			}
			else if(estado == ESTADO_DIGITE_MASCARA_SUB_REDE) //Senão se estado for igual a ESTADO_DIGITE_MASCARA_SUB_REDE então
			{
				for(x = 0;x < 15;x++) //Armazena em end_SUB_MASK[x] todo o vetor end_aux alterado
				{
					end_SUB_MASK[x] = end_aux[x];
				}
				fnGravaIPs(); //Grava os endereços IP, máscara de sub-rede e GATEWAY
			}
			else if(estado == ESTADO_DIGITE_GATEWAY) //Senão se estado for igual a ESTADO_DIGITE_GATEWAY então
			{
				for(x = 0;x < 15;x++) //Armazena em end_GATEWAY[x] todo o vetor end_aux alterado
				{
					end_GATEWAY[x] = end_aux[x];
				}
				fnGravaIPs(); //Grava os endereços IP, máscara de sub-rede e GATEWAY
			}
			else if(estado == ESTADO_DIGITE_DNS) //Senão se estado for igual a ESTADO_DIGITE_DNS então
			{
				for(x = 0;x < 15;x++) //Armazena em end_DNS[x] todo o vetor end_aux alterado
				{
					end_DNS[x] = end_aux[x];
				}
				fnGravaDNS(); //Grava o endereço DNS
			}
			tela = TELA_MOSTRA_CONFIGURACOES_DA_INTERNET; //Tela é igual a TELA_MOSTRA_CONFIGURACOES_DA_INTERNET
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a informação acima
			estado = ESTADO_CONFIGURACOES_DE_INTERNET; //Estado a ser executado é ESTADO_CONFIGURACOES_DE_INTERNET
			identador = 1; //Armazena na variável identador o valor 1 para se posicionar no primeiro campo do endereço
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 4: //Retorna para o menu inicial AJUSTES_AVANCADOS
		{
			tela = TELA_AJUSTES_AVANCADOS; //Tela é igual a TELA_AJUSTES_AVANCADOS
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estado = ESTADO_NAVEGA_MENU_FUNCOES; //Estado a ser executado é ESTADO_NAVEGA_MENU_FUNCOES
			identador = 1; //Armazena na variável identador o valor 1 para se posicionar no primeiro campo do endereço
			teclapressionada = 0; //Limpa teclapressionada
			estadoDigitaIP = 1; //Armazena na variável estadoDigitaIP o valor 1 para ir para o primeiro nivel deste menu
			break;
		}
		break;
	}
}

void SetaCaracterIP(byte coluna) //Função que vai deslocando o caracter no campo endereço
{
	C = ch; //Armazena na variável C o conteúdo contido em ch
	LINHA = 2; //Se posiciona na linha 2
	COLUNA = coluna; //Armazena na variável COLUNA a posição identador
	PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
	EscreveChar(C); //Escreve o conteúdo de C na posição especificada
	PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
	delay_ms(50); //Espera 50ms
	teclapressionada = 0; //Limpa teclapressionada
}

void fnDigitePORT(void) //Função que permite digitar o número da porta corretamente dentro do campo porta web
{
	static byte estadoDigitaPORT = 1; //Define a variável estadoDigitaPORT para o switch case abaixo
	static byte identador = 6; //Define identador para ir posicionando o cursor nos campos de digitação da porta web

	switch(estadoDigitaPORT) //Conforme variável estadoDigitaPORT vai para o case específico
	{
		case 1: //Entra para digitar a porta web
		{
			ch = end_PORT[0]; //Armazena em ch o primeiro byte de end_port[0]
			SetaCaracterPORT(identador); //Função que vai deslocando o caracter no campo porta web
			estadoDigitaPORT = 2; //Armazena na variável estadoDigitaPORT o valor 2 para ir para o case 2
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //Permite ir digitando a senha
		{
			if(teclapressionada == teclaCancela) //Se teclapressionada for igual a tecla CANCELA então
			{
				//fnEstadoComandoNormal();
				tela = TELA_MOSTRA_CONFIGURACOES_DA_INTERNET; //Tela é igual a TELA_MOSTRA_CONFIGURACAOES_DA_INTERNET
				estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
				estado = ESTADO_CONFIGURACOES_DE_INTERNET; //Estado a ser executado é ESTADO_CONFIGURACOES_DE_INTERNET
				estadoDigitaPORT = 1; //Armazena na variável estadoDigitaPORT o valor 1 para ir para o primeiro nivel deste menu
				identador = 6; //Armazena na variável identador o valor 6 para se posicionar no primeiro campo da porta web
				teclapressionada = 0; //Limpa teclapressionada
				ch = 0x30; //Armazena na variável ch a informação 0
				C = ch; //Armazena na variável C o conteúdo de ch
				break;
			}
			if(teclapressionada == teclaConfirma || teclapressionada == teclaConfirma_Remoto) //Se teclapressionada for igual a tecla CONFIRMA então
			{
				if(alterou == 1) //Se alterou for igual a 1 então
				{
					ch = C; //Armazena na variável ch o conteúdo de C
					end_aux[identador - 6] = ch; //Armazena em end_aux[identador - 6] o conteúdo de ch
					alterou = 0; //Zera a variável alterou
				}
				else //Senão
				{
					ch = end_PORT[identador-6]; //Armazena na variável ch o conteúdo de end_PORT[identador - 6]
					end_aux[identador - 6] = ch; //Armazena na variável end_aux[identador - 6] o conteúdo de ch
				}
				SetaCaracterPORT(identador); //Posiciona o cursor na coluna conforme o valor do identador passado
				end_aux[identador - 6] = ch; //Armazena em end_aux[identador - 6] o conteúdo de ch
				identador++; //Incrementa identador para ir para o próximo campo da senha
				COLUNA = identador; //Armazena na variável COLUNA a posição identador
				PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada acima
				C = end_PORT[identador - 6]; //Armazena na variável C o conteúdo de end_PORT[identador - 6]
				teclapressionada = 0; //Limpa teclapressionada
			}
			if(teclapressionada == teclaIncrementa || teclapressionada == teclaTrava) //Se teclapressionada for igual a tecla INCREMENTA ou teclapressionada for igual a tecla TRAVA então
			{
				alterou = 1; //Armazena na variável alterou o valor 1 para indicar que houve alteração
				if(C == 0X39) //Se C for igual a 9 então
				{
					C = 0X30; //Armazena na variável C a informação 0
					EscreveChar(C); //Escreve o conteúdo de C na posição especificada
					COLUNA = identador; //Armazena na variável COLUNA a posição identador
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada acima
				}
				else //Senão
				{
					C++; //Incrementa C
					EscreveChar(C); //Escreve o conteúdo de C na posição especificada
					COLUNA = identador; //Armazena na variável COLUNA a posição identador
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada acima
				}
				ch = C; //Armazena na variável ch o conteúdo da variável C
				teclapressionada = 0; //Limpa teclapressionada
			}
			if(teclapressionada == teclaDecrementa || teclapressionada == teclaDestrava) //Se teclapressionada for igual a tecla DECREMENTA ou teclapressionada for igual a tecla DESTRAVA então
			{
				alterou = 1; //Armazena na variável alterou o valor 1 para indicar que houve alteração
				if(C == 0x30) //Se C for igual a 0 então
				{
					C = 0x39; //Armazena na variável C a informação 9
					EscreveChar(C); //Escreve o conteúdo de C na posição especificada
					COLUNA = identador; //Armazena na variável COLUNA a posição identador
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada acima
				}
				else //Senão
				{
					C--; //Decrementa C
					EscreveChar(C); //Escreve o conteúdo de C na posição especificada
					COLUNA = identador; //Armazena na variável COLUNA a posição identador
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada acima
				}
				ch = C; //Armazena na variável ch o conteúdo da variável C
				teclapressionada = 0; //Limpa teclapressionada
			}
			if(identador >= 11) //Se identador for maior ou igual a 11 então
			{
				estadoDigitaPORT = 3; //Armazena na variável estadoDigitaPORT o valor 3 para ir para o case 3
				identador = 6; //Armazena na variável identador o valor 6 para se posicionar no primeiro campo da porta web
				ch = 0x30; //Armazena na variável ch a informação 0
				C = ch; //Armazena na variável C o conteúdo de ch
				fnGravaAuditoria(17,0,1,OPERADOR,DISPOSITIVO);
				break;
			}
			break;
		}
		case 3: //Salva o endereço DNS no módulo ethernet
		{
			estadoDigitaPORT = 1; //Armazena na variável estadoDigitaPORT o valor 1 para ir para o primeiro nivel deste menu
			for(x = 0;x < 5;x++) //Armazena em end_PORT[x] todo o vetor end_aux alterado
			{
				end_PORT[x] = end_aux[x];
			}
			fnGravaPORT(); //Grava o endereço da porta WEB no módulo ethernet
			tela = TELA_MOSTRA_CONFIGURACOES_DA_INTERNET; //Tela é igual a TELA_MOSTRA_CONFIGURACOES_DA_INTERNET
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estado = ESTADO_CONFIGURACOES_DE_INTERNET; //Estado a ser executado é ESTADO_CONFIGURACOES_DE_INTERNET
			identador = 6; //Armazena na variável identador o valor 6 para se posicionar no primeiro campo da porta web
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 4: //Retorna para o menu inicial AJUSTES_AVANCADOS
		{
			tela = TELA_AJUSTES_AVANCADOS; //Tela é igual a TELA_AJUSTES_AVANCADOS
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estado = ESTADO_NAVEGA_MENU_FUNCOES; //Estado a ser executado é ESTADO_NAVEGA_MENU_FUNCOES
			identador = 6; //Armazena na variável identador o valor 6 para se posicionar no primeiro campo da porta web
			teclapressionada = 0; //Limpa teclapressionada
			estadoDigitaPORT = 1; //Armazena na variável estadoDigitaPORT o valor 1 para ir para o primeiro nivel deste menu
			break;
		}
		break;
	}
}

void SetaCaracterPORT(byte coluna) //Função que vai deslocando o caracter no campo da porta web
{
	C = ch; //Armazena na variável C o conteúdo contido em ch
	LINHA = 2; //Se posiciona na linha 2
	COLUNA = coluna; //Armazena na variável COLUNA a posição identador
	PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
	EscreveChar(C); //Escreve o conteúdo de C na posição especificada
	PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
	delay_ms(50); //Espera 50ms
	teclapressionada = 0; //Limpa teclapressionada
}

void fnLeEnderecosPontoaPonto(void)
{
	INICIA_TEMPO_ENVIO_ETHERNET = FALSE; //Torna INICIA_TEMPO_ENVIO_ETHERNET como FALSE para poder parar o envio de informações a rede externa
	estado_ENVIA_SERIAL_ETHERNET = ESTADO_ESPERA; //Torna estado_ENVIA_SERIAL_ETHERNET para ESTADO_ESPERA para poder parar o envio de informações a rede externa

	delay_ms(1000); //Espera 1 segundo

	if((modo_operacao_ethernet == MODO_NORMAL) || (modo_operacao_ethernet == MODO_SERIAL))
	{
		modo_operacao_ethernet = MODO_AT;
		fnEstadoComandoAT(); //Entra no modo de comandos AT
	}

	fnComandoAT_DNS(); //Faz a leitura do endereço DNS armazenado no módulo

//	fnComandoAT_WEBPORT(); //Faz a leitura do endereço da porta WEB

	fnComandoAT_WANN(); //Faz a leitura dos endereços IP, MASCARA DE SUB-REDE e GATEWAY

	fnPosicionaIP(); //Reposiciona o IP nos campos corretamente para todos endereços que tenham o seguinte formato 000.000.000.000

	if(recebe_serial[6] == 'D' && recebe_serial[7] == 'H' && recebe_serial[8] == 'C' && recebe_serial[9] == 'P')
	{
		PADRAO = _STATIC;

		fnGravaNOME(); //Grava o nome do módulo
		fnGravaIPs_PADRAO(); //Grava os endereços IP padrão, máscara de sub-rede padrão, gateway padrão
		fnGravaDNS(); //Grava o endereço DNS padrão
		fnGravaSOCK(); //Grava o tipo de protocolo de rede que é o TCP Server mode
		fnGravaSOCKPORT(); //Grava a porta local que é sempre 20108
	}
	else
	{
		PADRAO = _STATIC;

		/*** Le o que esta gravado na memória FLASH pois foi alterado manualmente ***/
		LE_FLASH_INTERNA(endFLASHIP,15);
		for(x = 0;x < 15;x++)
		{
			end_IP[x] = Read_Buffer_FLASH[x];
		}

		LE_FLASH_INTERNA(endFLASHMASCARASUBREDE,15);
		for(x = 0;x < 15;x++)
		{
			end_SUB_MASK[x] = Read_Buffer_FLASH[x];
		}

		LE_FLASH_INTERNA(endFLASHGATEWAY,15);
		for(x = 0;x < 15;x++)
		{
			end_GATEWAY[x] = Read_Buffer_FLASH[x];
		}

		LE_FLASH_INTERNA(endFLASHDNS,15);
		for(x = 0;x < 15;x++)
		{
			end_DNS[x] = Read_Buffer_FLASH[x];
		}
		fnGravaNOME(); //Grava o nome do módulo
		fnGravaIPs(); //Grava os endereços IP, endereço MASCARÁ SUB REDE, endereço GATEWAY
		fnGravaDNS(); //Grava o endereço DNS
		fnGravaSOCK(); //Grava o tipo de protocolo de rede que é o TCP Server mode
		fnGravaSOCKPORT(); //Grava a porta local que é sempre 20108
	}
}

void fnLeEnderecosAcessoRemotoSTATIC(void)
{
	INICIA_TEMPO_ENVIO_ETHERNET = FALSE; //Torna INICIA_TEMPO_ENVIO_ETHERNET como FALSE para poder parar o envio de informações a rede externa
	estado_ENVIA_SERIAL_ETHERNET = ESTADO_ESPERA; //Torna estado_ENVIA_SERIAL_ETHERNET para ESTADO_ESPERA para poder parar o envio de informações a rede externa

	delay_ms(1000); //Espera 1 segundo

	if((modo_operacao_ethernet == MODO_NORMAL) || (modo_operacao_ethernet == MODO_SERIAL))
	{
		modo_operacao_ethernet = MODO_AT;
		fnEstadoComandoAT(); //Entra no modo de comandos AT
	}

	fnComandoAT_DNS(); //Faz a leitura do endereço DNS armazenado no módulo

	fnComandoAT_SOCK(); //Faz a leitura do protocolo de rede, da endereço IP do servidor remoto, da porta remoto do modo http modo cliente

	fnComandoAT_WANN(); //Faz a leitura de como é pego o endereço IP (STATIC ou DHCP),endereço IP, endereço máscara de sub-rede, endereço do GATEWAY

	fnPosicionaIP();

	fnGravaNOME(); //Grava o nome do módulo
	fnGravaHTPURL(); //Grava a HTTP URL do módulo que é /index.php?
	fnGravaSOCKPORT(); //Grava a porta local que é sempre 20108
	fnGravaIPs();
	fnGravaSOCK();
	fnGravaHTPHEAD();
}

void fnLeEnderecosAcessoRemotoDHCP(void)
{
	INICIA_TEMPO_ENVIO_ETHERNET = FALSE; //Torna INICIA_TEMPO_ENVIO_ETHERNET como FALSE para poder parar o envio de informações a rede externa
	estado_ENVIA_SERIAL_ETHERNET = ESTADO_ESPERA; //Torna estado_ENVIA_SERIAL_ETHERNET para ESTADO_ESPERA para poder parar o envio de informações a rede externa

	//delay_ms(1000); //Espera 1 segundo

	if((modo_operacao_ethernet == MODO_NORMAL) || (modo_operacao_ethernet == MODO_SERIAL))
	{
		modo_operacao_ethernet = MODO_AT;
		fnEstadoComandoAT(); //Entra no modo de comandos AT
	}

	fnComandoAT_DNS(); //Faz a leitura do endereço DNS armazenado no módulo

	fnComandoAT_SOCK(); //Faz a leitura do protocolo de rede, da endereço IP do servidor remoto, da porta remoto do modo http modo cliente

	fnComandoAT_WANN(); //Faz a leitura de como é pego o endereço IP (STATIC ou DHCP),endereço IP, endereço máscara de sub-rede, endereço do GATEWAY

	fnPosicionaIP();

	if(PADRAO == _STATIC_REMOTO)
	{
		fnGravaNOME(); //Grava o nome do módulo
		fnGravaHTPURL(); //Grava a HTTP URL do módulo que é /index.php?
		fnGravaSOCKPORT(); //Grava a porta local que é sempre 20108
		fnGravaIPs();
		fnGravaSOCK();
		fnGravaHTPHEAD();
	}
	else if(PADRAO == _DHCP_REMOTO)
	{
		fnGravaNOME(); //Grava o nome do módulo
		fnGravaHTPURL(); //Grava a HTTP URL do módulo que é /index.php?
		fnGravaSOCKPORT(); //Grava a porta local que é sempre 20108
		fnGravaIPs();
		fnGravaSOCK();
		fnGravaHTPHEAD();
		fnGravaHTTP();
	}
}


/* int fnPreparaModuloEthernet(int tipoSetup)
 * 		Função que prepara o modulo Serial Ethernet (interno do processador do detector) limpando as
 * 			variaveis interna
 *
 * 		int tipoSetup				- modo de reset
 *
 * 		retorno a ser implementado (desconsiderar no momento)
*/
int fnPreparaModuloEthernet(int tipoSetup){

	switch(tipoSetup){

	case EthernetEnviaPacote:
		SERIAL_ETHERNET_ClearTxBuf();
		memset(envia_serial,0,sizeof(envia_serial));
		break;
	case EthernetDescartaAnterior:
		SERIAL_ETHERNET_ClearRxBuf();
		memset(recebe_serial,0,sizeof(recebe_serial));
		primeiro = 0; 			//Zera variável primeiro para poder capturar dados recebidos novamente
		byte_count = 0; 		//Zera variável byte_count para poder contar os bytes recebidos novamente
		break;
	case EthernetResetModulo:

		break;
	}
	return -1;

}


/* int fnChecaMensagemRecebida(char *mensagem_recebida, int tipo_mensagem)
 * 		Função que checa se a mensagem recebida e valida ou nao (ex corrompida ou fora de padrao
 *
 * 		char *mensagem_recebida		- String da mensagem recebida
 * 		int tipo_mensagem			- Tipo da mensagem a ser conferida
 *
 * 		retorna 0 (sem erro) ou -1 (erro)
*/
int fnChecaMensagemRecebida(char *mensagem_recebida, int tipo_mensagem){

	char checking_message[256];
	memset(checking_message,0,sizeof(checking_message));

	switch(tipo_mensagem){
	case MensagemRemSimtroDefaultCheck:

		strncpy(checking_message, mensagem_recebida, sizeof(checking_message));

		if(checking_message[254] != '\0' && checking_message[254] != '}'){
			return -1;
		}
		memset(checking_message, 0, sizeof(checking_message));


		strncpy(checking_message,strstr(mensagem_recebida,STRING_OK_HTTP), sizeof(checking_message));

		if(*checking_message=='\0') {						// Não recebeu mensagem válida (code!=200) 3 tentativas
			return -1;
		}
		memset(checking_message, 0, sizeof(checking_message));

		strcpy(checking_message,strstr(recebe_serial,STRING_TERMINATOR_HTTP));

		if(*checking_message=='\0') {
			return -1;
		}
		memset(checking_message, 0, sizeof(checking_message));
		break;

	case MensagemRemSimtroSizeCheck:
		strncpy(checking_message, mensagem_recebida, sizeof(checking_message));

		if(checking_message[254] != '\0' && checking_message[254] != '}'){
			return -1;
		}
		memset(checking_message, 0, sizeof(checking_message));
		break;

	case	MensagemRemSimtroCodeCheck:
		strncpy(checking_message,strstr(mensagem_recebida,STRING_OK_HTTP), sizeof(checking_message));

		if(*checking_message=='\0') {						// Não recebeu mensagem válida (code!=200) 3 tentativas
			return -1;
		}
		memset(checking_message, 0, sizeof(checking_message));
		break;

	case	MensagemRemSimtroTermCheck:
		strcpy(checking_message,strstr(recebe_serial,STRING_TERMINATOR_HTTP));

		if(*checking_message=='\0') {						// Não recebeu mensagem válida (code!=200) 3 tentativas
			return -1;
		}
		memset(checking_message, 0, sizeof(checking_message));
		break;
	case	MensagemRemSimtroValidCharCheck:
		strncpy(checking_message, mensagem_recebida, sizeof(checking_message));
		if(*checking_message=='\0'){
			return -1;
		}
		memset(checking_message, 0, sizeof(checking_message));
	}
	return 0;
}

/* int agataKeyGenerator(uint8_t *serialNo, size_t serialNoSize, uint8_t *generatedKey, size_t generatedKeySize)
 * 		Gera a chave de criptografia
 *
 * 		uint8_t *serialNo		- Numero serial, usado como seed para gerar a chave
 * 		size_t serialNoSize		- Tamanho da string do numero de serie
 * 		uint8_t *generatedKey	- String gerada (16 caracteres)
 * 		size_t generatedKeySize	- Tamanho da string da key gerada
 *
 * 		sem retorno
*/
int agataKeyGenerator(uint8_t *serialNo, size_t serialNoSize, uint8_t *generatedKey, size_t generatedKeySize){

	memset(generatedKey,0,generatedKeySize);

	for(int i=0; i<generatedKeySize; i=i+serialNoSize){
		if(i+serialNoSize<generatedKeySize){
			strncat(generatedKey,serialNo,serialNoSize);
		} else{
			strncat(generatedKey,serialNo,(generatedKeySize-i));
		}
	}
	return 0;		//Sem erro

}

/* void EnviaPacoteDados(void)
 * 		Função que envia os parâmetros do detector para o módulo ehternet-serial
 *
 * 		sem retorno
*/
void EnviaPacoteDados(void)
{

	struct AES_ctx ctx;
    uint8_t enviaPacoteKey[16] =   "\0";

    char envia_serial_temp[400] = "\0";
    char *enviaSerialBase64;

    char base64encoded[400] = "\0";
    size_t tamanhoBase64;

    int enviaSerialSize;
    char paddingCharsAesPKCS7;

    //Limpa os buffers do modulo ethernet (interno, nao o USRIOT)
	fnPreparaModuloEthernet(EthernetDescartaAnterior);
	fnPreparaModuloEthernet(EthernetEnviaPacote);

	//Gera a chave para criptografia (baseado no numero de serie)
	agataKeyGenerator(numero_serie, sizeof(numero_serie),enviaPacoteKey,sizeof(enviaPacoteKey));

	//Definido a estrutura de envio como JSON
	if(MODO_ENVIO_JSON_SIMTRO){
		fnEnviaPacoteJson(); //Prepara os valores a serem enviados e estrutura-os em JSON

		//Executa a criptografia
		if(MODO_CRIPTOGRAFIA_ECB_SIMTRO){

			AES_init_ctx(&ctx, enviaPacoteKey); //Inicializa o vetor no momento do conectar

			//Determina o tamnho e inclui o padding (o tamanho da mensagem deve ser multiplo de 16)
			enviaSerialSize = strlen(envia_serial);
			paddingCharsAesPKCS7 = 16 - enviaSerialSize%16;
			strncat(envia_serial,&paddingCharsAesPKCS7,1);
			for(; !!((strlen(envia_serial))%16);){
				strncat(envia_serial,&paddingCharsAesPKCS7,1);
			}

			enviaSerialSize = strlen(envia_serial);

			//Encripta a mensagem utilizando a chave gerada
			for(int i = 0; i<enviaSerialSize;i = i+16){
				AES_ECB_encrypt(&ctx, &envia_serial[i]);
			}
			//Coloca o numero de serie (descriptografado) para o Asset Care
			strcpy(envia_serial_temp,numero_serie);


			//Converte o valor criptografado para base64 para ser enviado online
			base64_encode_aux(envia_serial, enviaSerialSize, &tamanhoBase64, base64encoded,sizeof(base64encoded));
			strncpy(envia_serial,base64encoded,tamanhoBase64);

			//Finaliza colocando a mensagem, JSON, criptografada e convertido para base64 no array envia_serial
			strncat(envia_serial_temp,envia_serial,(sizeof(envia_serial_temp)-strlen(envia_serial_temp)));
			memset(envia_serial,0, sizeof(envia_serial));
			strcpy(envia_serial,envia_serial_temp);

		}

		//Envia o array envia_serial para o Asset Care e set as variáveis
		SERIAL_ETHERNET_SendBlock((byte*)&envia_serial,strlen(envia_serial),&Sent); //Envia para o módulo ethernet os 90 bytes de dados
		estado_ENVIA_SERIAL_ETHERNET = ESTADO_ESPERA; //Coloca o estado_ENVIA_SERIAL_ETHERNET para ESTADO_ESPERA
		INICIA_TEMPO_ENVIO_ETHERNET = TRUE; //Inicializa a variável INICIA_TEMPO_ENVIO_ETHERNET para inicializar a contagem de tempo
		tempo_envio_ethernet = 0; //Zera o contador de tempo tempo_envio_ethernet
		erro_comunicacao = ERRO_COM;

		return;
	}

}
/******************************************************************************/


/* void intToCharArrayUTF(int valorConverter, char *emDecimal)
 * 		Converte o valor int valorConerter para um char array ASCII-UTF emDecimal
 *
 * 		int valorConverter 	- Valor a ser convertido
 * 		char *emDecimal 	- Retorna a string convertida
 *
 * 		sem retorno
*/
void intToCharArrayUTF(int valorConverter, char *emDecimal){

	char utfArrayTemp[11];
	memset(utfArrayTemp,0,sizeof(utfArrayTemp));

	//Convercao para uma string com 0 nos decimais
	utfArrayTemp[0] = (char)(valorConverter/1000000000) + '0';
	utfArrayTemp[1] = (char)((valorConverter%1000000000)/100000000) + '0';
	utfArrayTemp[2] = ((char)(((valorConverter%100000000)/10000000) + '0'));
	utfArrayTemp[3] = ((char)(((valorConverter%10000000)/1000000) + '0'));
	utfArrayTemp[4] = ((char)(((valorConverter%1000000)/100000) + '0'));
	utfArrayTemp[5] = ((char)(((valorConverter%100000)/10000) + '0'));
	utfArrayTemp[6] = ((char)(((valorConverter%10000)/1000) + '0'));
	utfArrayTemp[7] = ((char)(((valorConverter%1000)/100) + '0'));
	utfArrayTemp[8] = ((char)(((valorConverter%100)/10) + '0'));
	utfArrayTemp[9] = ((char)((valorConverter%10) + '0'));

	//Remove os zeros a esquerda
	for(int i = 0; i<9; i++){
		if (utfArrayTemp[0] == '0')    memmove(utfArrayTemp, utfArrayTemp+1, strlen(utfArrayTemp));
		else break;
	}

	//Move para o ponteiro de entrada
	memset(emDecimal,0,sizeof(utfArrayTemp));
	strcpy(emDecimal,utfArrayTemp);
}


//Descontinuado - legado - utilizar intToCharArrayUTF
void converteParaDecimalUTF(byte valor, unsigned char *emDecimal){

	memset(emDecimal,0,3);

	*emDecimal   = (byte) (valor/100) 	+ '0';
	if(*emDecimal == '0') {
		*emDecimal = (byte)(valor/10)	+ '0';
		if(*emDecimal == '0') {
			*emDecimal = (byte)(valor)	+ '0';
			return;
		}

		*(emDecimal+1) = (byte)(valor)%10	+ '0';
		return;
	}


	*(emDecimal+1) =  (byte)((valor%100)/10)	+ '0';
	*(emDecimal+2) =  (byte)(valor%10)	+ '0';
}


/*	DESCONTINUADO - utilizar fnEnviaPacoteJson()
 *
 *  void jsonInsereDadoEnviaSerial(char *nomeDado, char *dadoInserir, int tipo, int valor)
 * 		Apende o dado no envia_serial em formato json
 *
 * 		char *nomeDado		- adiciona o nome do dado
 * 		char *dadoInserir	- adiciona o dado
 * 		int tipo			- opcao que indica se e um valor numerico ou alpha
 * 		int valor  			- opcao que indica que e um valor final na string ou no meio
 *
 * 		sem retorno
*/
void jsonInsereDadoEnviaSerial(char *nomeDado, char *dadoInserir, int tipo, int valor){

	strcat(envia_serial, "\"");
	strncat(envia_serial, nomeDado, strlen(nomeDado));

	switch(valor){
	case JSON_NUMERICO:
		strcat(envia_serial, "\":");
		strncat(envia_serial, dadoInserir, strlen(dadoInserir));
	break;
	case JSON_ALPHANUM:
		strcat(envia_serial, "\":\"");
		strncat(envia_serial, dadoInserir, strlen(dadoInserir));
		strcat(envia_serial, "\"");
		break;
	}

	switch(tipo){
	case JSON_MEIO_OBJECT:
		strcat(envia_serial, ",");
	break;
	case JSON_FINAL_OBJECT:
		strcat(envia_serial, "}");
		break;
	}

}

/* void fnEnviaPacoteJson(void)
 * 		prepara os dados atuais do detector para json e coloca no array envia_serial
 *
 * 		sem retorno
*/
void fnEnviaPacoteJson(void){

	char valorUTF_temp[4];
	char nomeDadoUTF_temp[10];

	time_t tempoAtual = time(NULL);
	struct tm timeForJson;
	char timeUTF_temp[16];

	time_t eventTime_timet = time(NULL);
	struct tm eventTime_tm;
	struct tm auditTime_tm;

	int anoTemp;

	static dword end_event_temp = 0x00;
	static dword end_audit_temp = 0x00;

	DataHora monitTime = GetData();

	RTC1_GetTime(MyRTCPtr, &Time);					// Prepara a conversao do horario atual para time_t
	timeForJson.tm_sec = (int) Time.Second;
	timeForJson.tm_min = (int) Time.Minute;
	timeForJson.tm_hour = (int) Time.Hour;
	timeForJson.tm_mday = (int) Time.Day;
	timeForJson.tm_mon = (int) Time.Month - 1;
	timeForJson.tm_year = (int) Time.Year - 1900;

	tempoAtual = mktime(&timeForJson);				// Gera o time_t (long, ainda ser convertido para string)

	int endereco_log_auditoria_enviar = 0;

	//Limpa os arrays
	memset(valorUTF_temp,0,sizeof(valorUTF_temp));
	memset(envia_serial,0,sizeof(envia_serial));

	//Inicia o cabecalho, incluindo o numero de serie, e apende a abertura do array de monitoramento
	strcpy(envia_serial, "{\"blc\":\"#ea\",\"srl\":\""); //Removido caracter inicial "["
	strcat(envia_serial, numero_serie);
	strcat(envia_serial, "\",\"monit\":[");

	//*** Apende os valores atuais do detector
	for(x = 3;x < 10;x++) //Envia a sensibilidade atual das 8 áreas
	{
		converteParaDecimalUTF(buffer_sensibilidade[x-2],valorUTF_temp);
		strcat(envia_serial,valorUTF_temp);
		strcat(envia_serial,",");
	}
	converteParaDecimalUTF(buffer_sensibilidade[10-2],valorUTF_temp);	//TODO por que nao colocar no for?
	strcat(envia_serial,valorUTF_temp);
	strcat(envia_serial,",");

	converteParaDecimalUTF(selecao_metais,valorUTF_temp);	//SELECAO METAIS
	strcat(envia_serial,valorUTF_temp);
	strcat(envia_serial,",");

	converteParaDecimalUTF((byte)filtroruido,valorUTF_temp);	//FILTRO RUIDO
	strcat(envia_serial,valorUTF_temp);
	strcat(envia_serial,",");

	converteParaDecimalUTF((byte)var_tensao_cinco,valorUTF_temp);	//TENSAO CINCO
	strcat(envia_serial,valorUTF_temp);
	strcat(envia_serial,",");

	converteParaDecimalUTF((byte)var_tensao_quinze,valorUTF_temp);	//TENSAO QUINZE POS
	strcat(envia_serial,valorUTF_temp);
	strcat(envia_serial,",");

	converteParaDecimalUTF((byte)var_tensao_menos_quinze,valorUTF_temp);	//TENSAO QUINZE NEG
	strcat(envia_serial,valorUTF_temp);
	strcat(envia_serial,",");

	converteParaDecimalUTF((byte)var_tensao_rede,valorUTF_temp);		// TENSAO AC
	strcat(envia_serial,valorUTF_temp);
	strcat(envia_serial,",");

	intToCharArrayUTF((int)var_tensao_bateria,valorUTF_temp);			//TENSAO BAT
	strcat(envia_serial,valorUTF_temp);
	strcat(envia_serial,",");

	intToCharArrayUTF((int)var_tensao_chaveada,valorUTF_temp);			//TENSAO FONTE
	strcat(envia_serial,valorUTF_temp);
	strcat(envia_serial,",");

	for(x = 0;x < 8;x++) //Envia estado de ANULA_AREA atual das 8 áreas
	{
		converteParaDecimalUTF(anula_area[x],valorUTF_temp);
		strcat(envia_serial,valorUTF_temp);
		strcat(envia_serial,",");
	}

	intToCharArrayUTF((int)contador_dia_entra,valorUTF_temp);
	strcat(envia_serial,valorUTF_temp);
	strcat(envia_serial,",");

	intToCharArrayUTF((int)contador_dia_sai,valorUTF_temp);
	strcat(envia_serial,valorUTF_temp);
	strcat(envia_serial,",");

	intToCharArrayUTF((int)contador_bloqueios,valorUTF_temp);
	strcat(envia_serial,valorUTF_temp);
	strcat(envia_serial,",");

	intToCharArrayUTF((int)contador_desbloqueios,valorUTF_temp);
	strcat(envia_serial,valorUTF_temp);
	strcat(envia_serial,",");

	intToCharArrayUTF((int)tempoAtual,timeUTF_temp);	//TIMESTAMP
	strcat(envia_serial,timeUTF_temp);	//nota: timestamp unix pode chegar a ter 10 algarismos
	strcat(envia_serial,",");

	converteParaDecimalUTF((byte)sinal_rele,valorUTF_temp);	//SINAL RELE
	strcat(envia_serial,valorUTF_temp);
	strcat(envia_serial,",");

	converteParaDecimalUTF((byte)sinal_trava,valorUTF_temp);	//SINAL TRAVA
	strcat(envia_serial,valorUTF_temp);
	strcat(envia_serial,",");

	converteParaDecimalUTF((byte)pulso_rele,valorUTF_temp);	//PULSO RELE
	strcat(envia_serial,valorUTF_temp);
	strcat(envia_serial,",");

	converteParaDecimalUTF((byte)pulso_trava,valorUTF_temp);	//PULSO TRAVA
	strcat(envia_serial,valorUTF_temp);
	strcat(envia_serial,",");

	converteParaDecimalUTF((byte)modo_travamento,valorUTF_temp);	//MODO TRAVAMENTO
	strcat(envia_serial,valorUTF_temp);
	strcat(envia_serial,",");

	converteParaDecimalUTF((byte)buffer_buzzer[BUZZER_VOLUME],valorUTF_temp);	//VOLUME BUZZER
	strcat(envia_serial,valorUTF_temp);
	strcat(envia_serial,",");

	converteParaDecimalUTF((byte)volume_mensagem_voz,valorUTF_temp);	//MENSAGEM VOZ
	strcat(envia_serial,valorUTF_temp);
	strcat(envia_serial,",");

	converteParaDecimalUTF((byte)canal,valorUTF_temp);	//CANAL
	strcat(envia_serial,valorUTF_temp);
	strcat(envia_serial,",");

	converteParaDecimalUTF((byte)statusPGDM,valorUTF_temp); //PGDM ABERTA ou FECHADA
	strcat(envia_serial,valorUTF_temp);
	strcat(envia_serial,"]");
	//*** Fim do array de monitoramento

	//Confere se existe algum evento a ser enviado
	end_event_temp = end_event_reenvio;
	fnLeEnderecoFlagEventos(end_event_reenvio); //Le endereço da flag de eventos para verificar se tem que enviar

	if(flagEventoLido) //Se flagEventLido for 1 é porque o registro no endereço correspondente nunca foi enviado.
	{
		//No cálculo abaixo é multiplicado por 8 por que cada registro de eventos contém 8 bytes e o endereço dos registros de eventos vai de 0x44000 a 0x48000 - 1
		end_bloco_l = ((end_event_reenvio - END_INI_FLAG_EVENTOS) * 8) + END_INI_LOG_EVENTOS; //Acerta o endereço de leituro do registro de eventos a ser enviado ou reenviado de acordo com  posição em end_event_reenvio e se flag esta setada dentro da faixa dos endereços de flags de 0x48000 a 0x48800 que da 2048 registros de eventos
	}

	end_audit_temp = end_audit_reenvio;
	fnLeEnderecoFlagAuditorias(end_audit_reenvio); //Le endereço da flag de auditorias para verificar se tem que enviar

	//Se houver algum erro no armazenamento de evento ou de auditoria, armazena ERRO_FW para ser enviada
	if((end_event_temp == end_event_reenvio && erro_comunicacao == ERRO_OK) && PRIMEIRO_ENVIO == NAO){
		erro_comunicacao = ERRO_FW;
	}
	if((end_audit_temp == end_audit_reenvio && erro_comunicacao == ERRO_OK) && PRIMEIRO_ENVIO == NAO){
		erro_comunicacao = ERRO_FW;
	}

	//*** Apende o evento mais antigo (se houver)
	strcat(envia_serial, ",\"event\":[");	//Adicionado caracter "[" antes de "{" por se tratar de um array
	if(EventToSend)
	{
		LE_FLASH_INTERNA(end_bloco_l,8); //Le o registro de eventos apontado por end_bloco_l

		memset(valorUTF_temp,0,sizeof(valorUTF_temp));
		strcat(envia_serial,"\"");
		*valorUTF_temp = Read_Buffer_FLASH[0]; //Evento
		strcat(envia_serial,valorUTF_temp);
		strcat(envia_serial,"\",\"");

		memset(valorUTF_temp,0,sizeof(valorUTF_temp));
		*valorUTF_temp = Read_Buffer_FLASH[1]; //Dispositivo
		strcat(envia_serial,valorUTF_temp);
		strcat(envia_serial,"\",\"");

		anoTemp = (int)Read_Buffer_FLASH[6]*256 + (int) Read_Buffer_FLASH[7];

		eventTime_tm.tm_sec = (int) 0;
		eventTime_tm.tm_min = (int) Read_Buffer_FLASH[3];
		eventTime_tm.tm_hour = (int) Read_Buffer_FLASH[2];
		eventTime_tm.tm_mday = (int) Read_Buffer_FLASH[4];
		eventTime_tm.tm_mon = (int) Read_Buffer_FLASH[5] - 1;
		eventTime_tm.tm_year = (int) anoTemp - 1900;

		eventTime_timet = mktime(&eventTime_tm);

		memset(timeUTF_temp,0,sizeof(timeUTF_temp));
		intToCharArrayUTF(eventTime_timet,timeUTF_temp);
		strcat(envia_serial,timeUTF_temp);
		strcat(envia_serial, "\"");

	}
	else if(!EventToSend)	//Se nao houver evento, ignora, limpa o buffer e segue
	{
		memset(Read_Buffer_FLASH,0,sizeof(Read_Buffer_FLASH));
	}

	strcat(envia_serial, "]");	//Adicionado caracter "]" no final do log por se tratar de array
	//*** Fim do array de eventos

	//*** Apende a auditoria mais antiga (se houver)
	strcat(envia_serial, ",\"audit\":[");	//Adicionado caracter "[" antes de "{" por se tratar de um array


	if(AudToSend)
	{
		endereco_log_auditoria_enviar = ((end_audit_reenvio%0x1000)/372)*0x1000 + ((end_audit_reenvio%0x1000)%372)*11 + END_INI_LOG_AUDITORIAS;

		LE_FLASH_INTERNA(endereco_log_auditoria_enviar,11); //Le o registro de auditorias apontado por end_bloco_a

		memset(valorUTF_temp,0,sizeof(valorUTF_temp));
		strcat(envia_serial,"\"");
		converteParaDecimalUTF((byte)Read_Buffer_FLASH[0],valorUTF_temp);
		strcat(envia_serial,valorUTF_temp);
		strcat(envia_serial,"\",");


		memset(valorUTF_temp,0,sizeof(valorUTF_temp));
		strcat(envia_serial,"\"");
		converteParaDecimalUTF((byte)Read_Buffer_FLASH[1],valorUTF_temp);//VALOR VELHO
		strcat(envia_serial,valorUTF_temp);
		strcat(envia_serial,"\",");

		memset(valorUTF_temp,0,sizeof(valorUTF_temp));
		strcat(envia_serial,"\"");
		converteParaDecimalUTF((byte)Read_Buffer_FLASH[2],valorUTF_temp);//VALOR NOVO
		strcat(envia_serial,valorUTF_temp);
		strcat(envia_serial,"\",");


		memset(valorUTF_temp,0,sizeof(valorUTF_temp));
		strcat(envia_serial,"\"");
		if(Read_Buffer_FLASH[4] == 'S'){
			intToCharArrayUTF((int)Read_Buffer_FLASH[3] ,valorUTF_temp);	// Converte o OPERADOR para ID
		}
		else {
			valorUTF_temp[0] = Read_Buffer_FLASH[3];
		}

		//*valorUTF_temp = Read_Buffer_FLASH[3]; //OPERADOR
		strcat(envia_serial,valorUTF_temp);
		strcat(envia_serial,"\",");


		memset(valorUTF_temp,0,sizeof(valorUTF_temp));
		strcat(envia_serial,"\"");
		*valorUTF_temp = Read_Buffer_FLASH[4]; //Dispositivo
		strcat(envia_serial,valorUTF_temp);
		strcat(envia_serial,"\",\"");

		anoTemp = (int)Read_Buffer_FLASH[9]*256 + (int) Read_Buffer_FLASH[10];

		eventTime_tm.tm_sec = (int) 0;
		eventTime_tm.tm_min = (int) Read_Buffer_FLASH[6];
		eventTime_tm.tm_hour = (int) Read_Buffer_FLASH[5];
		eventTime_tm.tm_mday = (int) Read_Buffer_FLASH[7];
		eventTime_tm.tm_mon = (int) Read_Buffer_FLASH[8] - 1;
		eventTime_tm.tm_year = (int) anoTemp - 1900;

		eventTime_timet = mktime(&eventTime_tm);

		memset(timeUTF_temp,0,sizeof(timeUTF_temp));
		intToCharArrayUTF(eventTime_timet,timeUTF_temp);
		strcat(envia_serial,timeUTF_temp);

		strcat(envia_serial, "\"");	//Adicionado caracter "]" no final do log por se tratar de array

	}
	else if(!AudToSend)	//Se nao houver auditoria, ignora, limpa o buffer e segue
	{
		memset(Read_Buffer_FLASH,0,sizeof(Read_Buffer_FLASH));	//Caso não tenha novo log de auditoria para enviar, envia valor '0'
	}

	strcat(envia_serial, "]");				//Fecha o array de auditoria
	//*** Fim do array de auditoria


	//*** Apende o erro (se houver)
	strcat(envia_serial, ",\"erros\":[\"");	//Inicia array campo de erros
	envia_serial[strlen(envia_serial)] = erroAgata;	//Identificador de erro no circuito Ágata
	strcat(envia_serial, "\",\"");
	envia_serial[strlen(envia_serial)] = erro_comunicacao;
	//strncat(envia_serial, &erro_comunicacao, 1);	//Identificador de erro da comunicação remota
	strcat(envia_serial, "\"]");			//Fecha o array do campo de erros
	//*** Fim do array de erro

	strcat(envia_serial, "}");	//Final da mensagem
	erroAgata = NO_WRNG;

}

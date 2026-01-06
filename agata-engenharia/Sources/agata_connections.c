/*
 * agata_connections.c
 *
 *  Created on: 23/06/2023
 *      Author: marcos.butignol
 *
 *  220623 - agata_flash_handling.c
 *  	criado para definir funcoes de conexao
 */


#include "funcao.h"

#include "agata_std_functions.h"
#include "agata_hc_definitions.h"
#include "stdlib.h"


void fnEstadoComandoAT(void) //Permite entrar no modo comandos AT do módulo ethernet
{
	dado_recebido = 0; //Armazena zero na variável dado_recebido para poder receber os dados
	primeiro = 0; //Armazena zero na variável primeiro para poder sincronizar o primeiro dado
	for(x = 0;x < 255;x++) //Zera o vetor recebe_serial de recebimentos dos dados e o vetor envia_serial do envio dos dados
	{
		recebe_serial[x] = 0;
		envia_serial[x] = 0;
	}

	envia_serial[0] = '+'; //Envia + 3 vezes para entrar no modo de comandos AT
	envia_serial[1] = '+';
	envia_serial[2] = '+';
	SERIAL_ETHERNET_SendBlock((byte*)&envia_serial,3,&Sent); //Envia os 3 + pela serial ao módulo ethernet
	INICIA_TIME_OUT_ETHERNET = SIM;
	while(!aceito && FIM_TIME_OUT_ETHERNET == NAO); //Enquanto aceito não for 1 significa que +++ ainda não foi reconhecido
	INICIA_TIME_OUT_ETHERNET = NAO;
	FIM_TIME_OUT_ETHERNET = NAO;
	delay_ms(100);

    envia_serial[0] = 'a'; //Logo em seguida envia 'a' para realmente poder entrar no modo de comandos AT
	SERIAL_ETHERNET_SendBlock((byte*)&envia_serial,1,&Sent); //Envia o 'a' pela serial ao módulo ethernet
	INICIA_TIME_OUT_ETHERNET = SIM;
	while(estado_MODULO_ETHERNET != ESTADO_MODO_AT_ON && FIM_TIME_OUT_ETHERNET == NAO);
	INICIA_TIME_OUT_ETHERNET = NAO;
	FIM_TIME_OUT_ETHERNET = NAO;

	estado_MODULO_ETHERNET = ESTADO_ESPERA; //Faz com que estado_MODULO_ETHERNET fique em ESTADO_ESPERA novamente

	delay_ms(100); //Espera 100ms;
}

void fnComandoAT_WANN(void) //Permite fazer a leitura dos endereços de IP, máscara de sub-rede e GATEWAY configurado no módulo ethernet
{
	dado_recebido = 0; //Armazena zero na variável dado_recebido para poder receber os dados
	primeiro = 0; //Armazena zero na variável primeiro para poder sincronizar o primeiro dado
	for(x = 0;x < 255;x++) //Zera o vetor recebe_serial de recebimentos dos dados e o vetor envia_serial do envio dos dados
	{
		recebe_serial[x] = 0;
		envia_serial[x] = 0;
	}

	str3 = "AT+WANN"; //Comando para ler o endereço IP, endereço de MÁSCARA DE SUB REDE, endereço GATEWAY

	for(x = 0;x < strlen(str3);x++)
	{
		envia_serial[x] = str3[x];
	}

	envia_serial[x] = 0x0D;
	SERIAL_ETHERNET_SendBlock((byte*)&envia_serial,(x+1),&Sent); //Envia os 8 bytes pela serial ao módulo ethernet para executar o comando

	while(estado_MODULO_ETHERNET != ESTADO_COMANDO_OK); //Aguarda o módulo responder com ESTADO_WANN_OK informando que recebeu os dados corretamente
	estado_MODULO_ETHERNET = ESTADO_ESPERA;	//Faz com que estado_MODULO_ETHERNET fique em ESTADO_ESPERA novamente

	for(x = 0;x < 15;x++) //Preenche todos os vetores de endereços com X para que a funções de reposicionamente dos números nos campos IP funcionem corretamente
	{
		end_IP[x] = 'X';
		end_SUB_MASK[x] = 'X';
		end_GATEWAY[x] = 'X';
	}

	y = 0; //Faz y = 0 para poder contar as virgulas
	z = 0; //Faz z = 0 para poder separar os 3 endereços em cada vetor em separado
	for(x = 0;x < 70;x++) //Lê todos os 70 bytes
	{
		if(y == 1 && recebe_serial[x] != ',') //Se y for igual a 1 e recebe_serial for igual a ',' então
		{
			end_IP[z] = recebe_serial[x]; //end_IP[z] recebe o conteúdo de recebe_serial[x]
			z++; //Incrementa z
		}
		else if(y == 2 && recebe_serial[x] != ',') //Senão se y for igual a 2 e recebe_serial for igual a ',' então
		{
			end_SUB_MASK[z] = recebe_serial[x]; //end_SUB_MASK[z]  recebe o conteúdo de recebe_serial[x]
			z++; //Incrementa z
		}
		else if(y == 3 && recebe_serial[x] != 0x0D && recebe_serial[x] != 0x0A) //Senão se y for igual a 3 e recebe_serial não for igual a 0x0D e recebe_serial não for igual a 0x0A então
		{
			end_GATEWAY[z] = recebe_serial[x]; //end_GATEWAY[z] recebe o conteúdo de recebe_serial[x]
			z++; //Incrementa z
		}
		if(recebe_serial[x] == ',') //Se recebe_serial[x] for igual a ',' então
		{
			y++; //Incrementa y para informar que posição esta dentro do endereço
			z = 0; //Zera a variável z
		}
		if(y == 3 && recebe_serial[x - 1] == 0x0D && recebe_serial[x] == 0x0A) //Se y for igual a 3 e recebe_serial[x-1] for igual a 0x0D e recebe_serial[x] for igual a 0x0A então
		{
			x = 70; //Faz x igual 70 para sair do laço for
			y = 0; //Zera a variável y
			z = 0; //Zera a variável z
		}
	}
	delay_ms(100);
}

void fnEstadoComandoNormal(void) //Permite entrar no modo NORMAL do módulo ethernet
{
	dado_recebido = 0; //Armazena zero na variável dado_recebido para poder receber os dados
	primeiro = 0; //Armazena zero na variável primeiro para poder sincronizar o primeiro dado
	for(x = 0;x < 255;x++) //Zera o vetor recebe_serial de recebimentos dos dados e o vetor envia_serial do envio dos dados
	{
		recebe_serial[x] = 0;
		envia_serial[x] = 0;
	}

	envia_serial[0] = 'A'; //Comando para fazer com que o módulo volte ao estado NORMAL de transmissão e recepção
	envia_serial[1] = 'T';
	envia_serial[2] = '+';
	envia_serial[3] = 'E';
	envia_serial[4] = 'N';
	envia_serial[5] = 'T';
	envia_serial[6] = 'M';
	envia_serial[7] = 0x0D;
	SERIAL_ETHERNET_SendBlock((byte*)&envia_serial,8,&Sent); //Envia os 8 bytes pela serial ao módulo ethernet para executar o comando

	delay_ms(100);

	while(estado_MODULO_ETHERNET != ESTADO_COMANDO_OK); //Aguarda o módulo responder com ESTADO_WANN_OK informando que recebeu os dados corretamente
	estado_MODULO_ETHERNET = ESTADO_ESPERA;	//Faz com que estado_MODULO_ETHERNET fique em ESTADO_ESPERA novamente
}

void fnComandoAT_DNS(void) //Permite fazer a leitura do endereço DNS configurado no módulo ethernet
{
	dado_recebido = 0; //Armazena zero na variável dado_recebido para poder receber os dados
	primeiro = 0; //Armazena zero na variável primeiro para poder sincronizar o primeiro dado
	for(x = 0;x < 255;x++) //Zera o vetor recebe_serial de recebimentos dos dados e o vetor envia_serial do envio dos dados
	{
		recebe_serial[x] = 0;
		envia_serial[x] = 0;
	}

	str3 = "AT+DNS";

	for(x = 0;x < strlen(str3);x++) //Comando para ler o endereço DNS
	{
		envia_serial[x] = str3[x];
	}

	envia_serial[x] = 0x0D;
	SERIAL_ETHERNET_SendBlock((byte*)&envia_serial,(x+1),&Sent); //Envia os 8 bytes pela serial ao módulo ethernet para executar o comando

	delay_ms(100);

	while(estado_MODULO_ETHERNET != ESTADO_COMANDO_OK); //Aguarda o módulo responder com ESTADO_WANN_OK informando que recebeu os dados corretamente
	estado_MODULO_ETHERNET = ESTADO_ESPERA;	//Faz com que estado_MODULO_ETHERNET fique em ESTADO_ESPERA novamente

	for(x = 0;x < 15;x++) //Preenche o vetor de endereço com X para que a funções de reposicionamente dos números no campo IP funcione corretamente
	{
		end_DNS[x] = 'X';
	}

	y = 0; //Faz y = 0 para poder contar as virgulas
	z = 0; //Faz z = 0 para poder separar os 3 endereços em cada vetor em separado
	for(x = 6;x < 70;x++) //Lê todos os 70 caracteres
	{
		if(recebe_serial[x] != 0x0D && recebe_serial[x] != 0x0A) //Se recebe_serial[x] não for igual a 0x0D e recebe_serial[x] não for igual a 0x0A
		{
			end_DNS[z] = recebe_serial[x]; //end_DNS[z] recebe o conteúdo de recebe_serial[x]
			z++; //Incrementa z
			if(z == 15) //Se z for igual a 15 então
			{
				x = 70; //Faz x igual 70 para sair do laço for
				y = 0; //Zera a variável y
				z = 0; //Zera a variável z
			}
		}
		else //Senão
		{
			x = 70; //Faz x igual 70 para sair do laço for
			y = 0; //Zera a variável y
			z = 0; //Zera a variável z
		}
	}

	//Reposicionando o endereço corretamente dentro do vetor para apresentação no LCD
	y = 0; //Faz y = 0 para poder contar as virgulas
	z = 0; //Faz z = 0 para poder separar os 3 endereços em cada vetor em separado
	for(x = 0;x < 15;x++) //Reposiciona os 15 bytes
	{
		if(end_DNS[x] != '.' && end_DNS[x] != 'X') //Se end_DNS[x] não for igual a '.' e end_DNS[x] não for igual a 'X' então
		{
			y++; //Incrementa y
		}
		else if(end_DNS[x] == '.' || end_DNS[x] == 'X') //Senão se end_DNS[x] for igual a '.' ou end_DNS[x] for igual a 'X' então
		{
			z++; //Incrementa z
			if(y == 1 && z == 1) //Se y for igual a 1 e z for igual a 1 então
			{
				end_aux[0] = '0'; //end_aux[0] recebe '0'
				end_aux[1] = '0'; //end_aux[1] recebe '0'
				end_aux[2] = end_DNS[x-1]; //end_aux[2] recebe end_DNS[x-1]
				end_aux[3] = end_DNS[x]; //end_aux[3] recebe end_DNS[x]
				y = 0; //Zera a variável y
			}
			else if(y == 2 && z == 1) //Senão se y for igual a 2 e z for igual a 1 então
			{
				end_aux[0] = '0'; //end_aux[0] recebe '0'
				end_aux[1] = end_DNS[x-2]; //end_aux[1] recebe end_DNS[x-2]
				end_aux[2] = end_DNS[x-1]; //end_aux[2] recebe end_DNS[x-1]
				end_aux[3] = end_DNS[x]; //end_aux[3] recebe end_DNS[x]
				y = 0; //Zera a variável y
			}
			else if(y == 3 && z == 1) //Senão se y for igual a 3 e z for igual a 1 então
			{
				end_aux[0] = end_DNS[x-3]; //end_aux[1] recebe end_DNS[x-3]
				end_aux[1] = end_DNS[x-2]; //end_aux[1] recebe end_DNS[x-2]
				end_aux[2] = end_DNS[x-1]; //end_aux[1] recebe end_DNS[x-1]
				end_aux[3] = end_DNS[x]; //end_aux[1] recebe end_DNS[x]
				y = 0; //Zera a variável y
			}
			if(y == 1 && z == 2) //Se y for igual a 1 e z for igual a 2 então
			{
				end_aux[4] = '0'; //end_aux[4] recebe '0'
				end_aux[5] = '0'; //end_aux[5] recebe '0'
				end_aux[6] = end_DNS[x-1]; //end_aux[6] recebe end_DNS[x-1]
				end_aux[7] = end_DNS[x]; //end_aux[7] recebe end_DNS[x]
				y = 0; //Zera a variável y
			}
			else if(y == 2 && z == 2) //Senão se y for igual a 2 e z for igual a 2 então
			{
				end_aux[4] = '0'; //end_aux[4] recebe '0'
				end_aux[5] = end_DNS[x-2]; //end_aux[5] recebe end_DNS[x-2]
				end_aux[6] = end_DNS[x-1]; //end_aux[6] recebe end_DNS[x-1]
				end_aux[7] = end_DNS[x]; //end_aux[7] recebe end_DNS[x]
				y = 0; //Zera a variável y
			}
			else if(y == 3 && z == 2) //Senão se y for igual a 3 e z for igual a 2 então
			{
				end_aux[4] = end_DNS[x-3]; //end_aux[4] recebe end_DNS[x-3]
				end_aux[5] = end_DNS[x-2]; //end_aux[5] recebe end_DNS[x-2]
				end_aux[6] = end_DNS[x-1]; //end_aux[6] recebe end_DNS[x-1]
				end_aux[7] = end_DNS[x]; //end_aux[7] recebe end_DNS[x]
				y = 0; //Zera a variável y
			}
			if(y == 1 && z == 3) //Se y for igual a 1 e z for igual a 3 então
			{
				end_aux[8] = '0'; //end_aux[8] recebe '0'
				end_aux[9] = '0'; //end_aux[9] recebe '0'
				end_aux[10] = end_DNS[x-1]; //end_aux[10] recebe end_DNS[x-1]
				end_aux[11] = end_DNS[x]; //end_aux[11] recebe end_DNS[x]
				y = 0; //Zera a variável y
			}
			else if(y == 2 && z == 3) //Senão se y for igual a 2 e z for igual a 3 então
			{
				end_aux[8] = '0'; //end_aux[8] recebe '0'
				end_aux[9] = end_DNS[x-2]; //end_aux[9] recebe end_DNS[x-2]
				end_aux[10] = end_DNS[x-1]; //end_aux[10] recebe end_DNS[x-1]
				end_aux[11] = end_DNS[x]; //end_aux[11] recebe end_DNS[x]
				y = 0; //Zera a variável y
			}
			else if(y == 3 && z == 3) //Senão se y for igual a 3 e z for igual a 3 então
			{
				end_aux[8] = end_DNS[x-3]; //end_aux[8] recebe end_DNS[x-3]
				end_aux[9] = end_DNS[x-2]; //end_aux[9] recebe end_DNS[x-2]
				end_aux[10] = end_DNS[x-1]; //end_aux[10] recebe end_DNS[x-1]
				end_aux[11] = end_DNS[x]; //end_aux[11] recebe end_DNS[x]
				y = 0; //Zera a variável y
			}
			if(y == 1 && z == 4) //Se y for igual a 1 e z for igual a 4 então
			{
				end_aux[12] = '0'; //end_aux[12] recebe '0'
				end_aux[13] = '0'; //end_aux[13] recebe '0'
				end_aux[14] = end_DNS[x-1]; //end_aux[14] recebe end_DNS[x-1]
				y = 0; //Zera a variável y
				x = 15; //Faz x igual a 15 para sair do laço for
			}
			else if(y == 2 && z == 4) //Senão se y for igual a 2 e z for igual a 4 então
			{
				end_aux[12] = '0'; //end_aux[12] recebe '0'
				end_aux[13] = end_DNS[x-2]; //end_aux[13] recebe end_DNS[x-2]
				end_aux[14] = end_DNS[x-1]; //end_aux[14] recebe end_DNS[x-1]
				y = 0; //Zera a variável y
				x = 15; //Faz x igual a 15 para sair do laço for
			}
			else if(y == 3 && z == 4) //Senão se y for igual a 3 e z for igual a 4 então
			{
				end_aux[12] = end_DNS[x-3]; //end_aux[12] recebe end_DNS[x-3]
				end_aux[13] = end_DNS[x-2]; //end_aux[13] recebe end_DNS[x-2]
				end_aux[14] = end_DNS[x-1]; //end_aux[14] recebe end_DNS[x-1]
				y = 0; //Zera a variável y
				x = 15; //Faz x igual a 15 para sair do laço for
			}
	  }
	}
	for(x = 0;x < 15;x++) //Recebe em end_DNS[x] todo o reposicionamento do vetor end_aux[x]
	{
		end_DNS[x] = end_aux[x];
	}
	delay_ms(100);
}

void fnComandoAT_WEBPORT(void) //Permite fazer a leitura da PORTA WEB configurada no módulo ethernet
{
	dado_recebido = 0; //Armazena zero na variável dado_recebido para poder receber os dados
	primeiro = 0; //Armazena zero na variável primeiro para poder sincronizar o primeiro dado
	for(x = 0;x < 255;x++) //Zera o vetor recebe_serial de recebimentos dos dados e o vetor envia_serial do envio dos dados
	{
		recebe_serial[x] = 0;
		envia_serial[x] = 0;
	}

	str3 = "AT+WEBPORT"; //Comando para ler o endereço da porta WEB

	for(x = 0;x < strlen(str3);x++)
	{
		envia_serial[x] = str3[x];
	}

	envia_serial[x] = 0x0D;
	SERIAL_ETHERNET_SendBlock((byte*)&envia_serial,(x+1),&Sent); //Envia os 11 bytes pela serial ao módulo ethernet para executar o comando

	while(estado_MODULO_ETHERNET != ESTADO_COMANDO_OK); //Aguarda o módulo responder com ESTADO_WANN_OK informando que recebeu os dados corretamente
	estado_MODULO_ETHERNET = ESTADO_ESPERA;	//Faz com que estado_MODULO_ETHERNET fique em ESTADO_ESPERA novamente

	for(x = 0;x < 5;x++) //Preenche todo o vetor de endereço com X para que a funções de reposicionamente dos números no campo IP funcione corretamente
	{
		end_PORT[x] = 'X';
	}

	y = 0; //Faz y = 0 para poder contar as virgulas
	z = 0; //Faz z = 0 para poder separar os 3 endereços em cada vetor em separado
	for(x = 6;x < 70;x++) //Lê todos os 70 caracteres
	{
		if(recebe_serial[x] != 0x0D && recebe_serial[x] != 0x0A)  //Se recebe_serial[x] não for igual a 0x0D e recebe_serial[x] não for igual a 0x0A
		{
			end_PORT[z] = recebe_serial[x]; //end_PORT[z] recebe o conteúdo de recebe_serial[x]
			z++; //Incrementa z
			if(z == 6) //Se z for igual a 6 então
			{
				x = 70; //Faz x igual a 70 para sair do laço for
				y = 0; //Zera a variável y
				z = 0; //Zera a variável z
			}
		}
		else //Senão
		{
			x = 70; //Faz x igual a 70 para sair do laço for
			y = 0; //Zera a variável y
			z = 0; //Zera a variável z
		}
	}

	//Reposicionando o endereço corretamente dentro do vetor para apresentação no LCD
	y = 0; //Faz y = 0 para poder contar as virgulas
	z = 0; //Faz z = 0 para poder separar os 3 endereços em cada vetor em separado
	for(x = 0;x < 5;x++) //Reposiciona os 5 bytes
	{
		if(end_PORT[x] != 'X') //Se end_PORT[x] não for igual a 'X' então
		{
			y++; //Incrementa y
		}
		else if(end_PORT[x] == 'X') //Senão se end_PORT[x] for igual a 'X' então
		{
			z++; //Incrementa z
			if(y == 1 && z == 1) //Se y for igual a 1 e z for igual a 1 então
			{
				end_aux[0] = '0'; //end_aux[0] recebe '0'
				end_aux[1] = '0'; //end_aux[1] recebe '0'
				end_aux[2] = '0'; //end_aux[2] recebe '0'
				end_aux[3] = '0'; //end_aux[3] recebe '0'
				end_aux[4] = end_PORT[x-1]; //end_aux[4] recebe end_PORT[x-1]
				y = 0; //Zera a variável y
			}
			else if(y == 2 && z == 1) //Senão se y for igual a 2 e z for igual a 1 então
			{
				end_aux[0] = '0'; //end_aux[0] recebe '0'
				end_aux[1] = '0'; //end_aux[1] recebe '0'
				end_aux[2] = '0'; //end_aux[2] recebe '0'
				end_aux[3] = end_PORT[x-2]; //end_aux[3] recebe end_PORT[x-2]
				end_aux[4] = end_PORT[x-1]; //end_aux[4] recebe end_PORT[x-1]
				y = 0; //Zera a variável y
			}
			else if(y == 3 && z == 1) //Senão se y for igual a 3 e z for igual a 1 então
			{
				end_aux[0] = '0'; //end_aux[0] recebe '0'
				end_aux[1] = '0'; //end_aux[1] recebe '0'
				end_aux[2] = end_PORT[x-3]; //end_aux[2] recebe end_PORT[x-3]
				end_aux[3] = end_PORT[x-2]; //end_aux[3] recebe end_PORT[x-2]
				end_aux[4] = end_PORT[x-1]; //end_aux[4] recebe end_PORT[x-1]
				y = 0; //Zera a variável y
			}
			else if(y == 4 && z == 1) //Senão se y for igual a 4 e z for igual a 1 então
			{
				end_aux[0] = '0'; //end_aux[0] recebe '0'
				end_aux[1] = end_PORT[x-4]; //end_aux[1] recebe end_PORT[x-4]
				end_aux[2] = end_PORT[x-3]; //end_aux[2] recebe end_PORT[x-3]
				end_aux[3] = end_PORT[x-2]; //end_aux[3] recebe end_PORT[x-2]
				end_aux[4] = end_PORT[x-1]; //end_aux[4] recebe end_PORT[x-1]
				y = 0; //Zera a variável y
			}
			else if(y == 5 && z == 1) //Senão se y for igual a 5 e z for igual a 1 então
			{
				end_aux[0] = end_PORT[x-5]; //end_aux[0] recebe end_PORT[x-5]
				end_aux[1] = end_PORT[x-4]; //end_aux[1] recebe end_PORT[x-4]
				end_aux[2] = end_PORT[x-3]; //end_aux[2] recebe end_PORT[x-3]
				end_aux[3] = end_PORT[x-2]; //end_aux[3] recebe end_PORT[x-2]
				end_aux[4] = end_PORT[x-1]; //end_aux[4] recebe end_PORT[x-1]
				y = 0; //Zera a variável y
			}
	  }
	}
	if(y == 5 && z == 0)
	{
		z = 0;
	}
	else
	{
		for(x = 0;x < 5;x++) //Recebe em end_PORT[x] todo o reposicionamento do vetor end_aux[x]
		{
			end_PORT[x] = end_aux[x];
		}
	}
	delay_ms(100);
}

void fnComandoAT_SOCK(void)
{
	dado_recebido = 0; //Armazena zero na variável dado_recebido para poder receber os dados
	primeiro = 0; //Armazena zero na variável primeiro para poder sincronizar o primeiro dado
	for(x = 0;x < 255;x++) //Zera o vetor recebe_serial de recebimentos dos dados e o vetor envia_serial do envio dos dados
	{
		recebe_serial[x] = 0;
		envia_serial[x] = 0;
	}

	str3 = "AT+SOCK"; //Comando para ler o endereço da porta WEB

	for(x = 0;x < strlen(str3);x++)
	{
		envia_serial[x] = str3[x];
	}

	envia_serial[x] = 0x0D;
	SERIAL_ETHERNET_SendBlock((byte*)&envia_serial,(x+1),&Sent); //Envia os 11 bytes pela serial ao módulo ethernet para executar o comando

	while(estado_MODULO_ETHERNET != ESTADO_COMANDO_OK); //Aguarda o módulo responder com ESTADO_WANN_OK informando que recebeu os dados corretamente
	estado_MODULO_ETHERNET = ESTADO_ESPERA;	//Faz com que estado_MODULO_ETHERNET fique em ESTADO_ESPERA novamente

	delay_ms(100);
}

void fnComandoAT_SOCKPORT(void) //Permite fazer a leitura da porta remota
{
	dado_recebido = 0; //Armazena zero na variável dado_recebido para poder receber os dados
	primeiro = 0; //Armazena zero na variável primeiro para poder sincronizar o primeiro dado
	for(x = 0;x < 255;x++) //Zera o vetor recebe_serial de recebimentos dos dados e o vetor envia_serial do envio dos dados
	{
		recebe_serial[x] = 0;
		envia_serial[x] = 0;
	}

	str3 = "AT+SOCKPORT";

	for(x = 0;x < strlen(str3);x++)
	{
		envia_serial[x] = str3[x];
	}

	envia_serial[x] = 0x0D;
	SERIAL_ETHERNET_SendBlock((byte*)&envia_serial,(x+1),&Sent); //Envia os 11 bytes pela serial ao módulo ethernet para executar o comando

	while(estado_MODULO_ETHERNET != ESTADO_COMANDO_OK); //Aguarda o módulo responder com ESTADO_WANN_OK informando que recebeu os dados corretamente
	estado_MODULO_ETHERNET = ESTADO_ESPERA;	//Faz com que estado_MODULO_ETHERNET fique em ESTADO_ESPERA novamente

	for(x = 0;x < 5;x++) //Preenche todo o vetor de endereço com X para que a funções de reposicionamente dos números no campo IP funcione corretamente
	{
		end_PORT1[x] = 'X';
	}

	y = 0; //Faz y = 0 para poder contar as virgulas
	z = 0; //Faz z = 0 para poder separar os 3 endereços em cada vetor em separado
	for(x = 6;x < 70;x++) //Lê todos os 70 caracteres
	{
		if(recebe_serial[x] != 0x0D && recebe_serial[x] != 0x0A)  //Se recebe_serial[x] não for igual a 0x0D e recebe_serial[x] não for igual a 0x0A
		{
			end_PORT[z] = recebe_serial[x]; //end_PORT[z] recebe o conteúdo de recebe_serial[x]
			z++; //Incrementa z
			if(z == 6) //Se z for igual a 6 então
			{
				x = 70; //Faz x igual a 70 para sair do laço for
				y = 0; //Zera a variável y
				z = 0; //Zera a variável z
			}
		}
		else //Senão
		{
			x = 70; //Faz x igual a 70 para sair do laço for
			y = 0; //Zera a variável y
			z = 0; //Zera a variável z
		}
	}

	//Reposicionando o endereço corretamente dentro do vetor para apresentação no LCD
	y = 0; //Faz y = 0 para poder contar as virgulas
	z = 0; //Faz z = 0 para poder separar os 3 endereços em cada vetor em separado
	for(x = 0;x < 5;x++) //Reposiciona os 5 bytes
	{
		if(end_PORT1[x] != 'X') //Se end_PORT[x] não for igual a 'X' então
		{
			y++; //Incrementa y
		}
		else if(end_PORT1[x] == 'X') //Senão se end_PORT[x] for igual a 'X' então
		{
			z++; //Incrementa z
			if(y == 1 && z == 1) //Se y for igual a 1 e z for igual a 1 então
			{
				end_aux[0] = '0'; //end_aux[0] recebe '0'
				end_aux[1] = '0'; //end_aux[1] recebe '0'
				end_aux[2] = '0'; //end_aux[2] recebe '0'
				end_aux[3] = '0'; //end_aux[3] recebe '0'
				end_aux[4] = end_PORT1[x-1]; //end_aux[4] recebe end_PORT[x-1]
				y = 0; //Zera a variável y
			}
			else if(y == 2 && z == 1) //Senão se y for igual a 2 e z for igual a 1 então
			{
				end_aux[0] = '0'; //end_aux[0] recebe '0'
				end_aux[1] = '0'; //end_aux[1] recebe '0'
				end_aux[2] = '0'; //end_aux[2] recebe '0'
				end_aux[3] = end_PORT1[x-2]; //end_aux[3] recebe end_PORT[x-2]
				end_aux[4] = end_PORT1[x-1]; //end_aux[4] recebe end_PORT[x-1]
				y = 0; //Zera a variável y
			}
			else if(y == 3 && z == 1) //Senão se y for igual a 3 e z for igual a 1 então
			{
				end_aux[0] = '0'; //end_aux[0] recebe '0'
				end_aux[1] = '0'; //end_aux[1] recebe '0'
				end_aux[2] = end_PORT1[x-3]; //end_aux[2] recebe end_PORT[x-3]
				end_aux[3] = end_PORT1[x-2]; //end_aux[3] recebe end_PORT[x-2]
				end_aux[4] = end_PORT1[x-1]; //end_aux[4] recebe end_PORT[x-1]
				y = 0; //Zera a variável y
			}
			else if(y == 4 && z == 1) //Senão se y for igual a 4 e z for igual a 1 então
			{
				end_aux[0] = '0'; //end_aux[0] recebe '0'
				end_aux[1] = end_PORT1[x-4]; //end_aux[1] recebe end_PORT[x-4]
				end_aux[2] = end_PORT1[x-3]; //end_aux[2] recebe end_PORT[x-3]
				end_aux[3] = end_PORT1[x-2]; //end_aux[3] recebe end_PORT[x-2]
				end_aux[4] = end_PORT1[x-1]; //end_aux[4] recebe end_PORT[x-1]
				y = 0; //Zera a variável y
			}
			else if(y == 5 && z == 1) //Senão se y for igual a 5 e z for igual a 1 então
			{
				end_aux[0] = end_PORT1[x-5]; //end_aux[0] recebe end_PORT[x-5]
				end_aux[1] = end_PORT1[x-4]; //end_aux[1] recebe end_PORT[x-4]
				end_aux[2] = end_PORT1[x-3]; //end_aux[2] recebe end_PORT[x-3]
				end_aux[3] = end_PORT1[x-2]; //end_aux[3] recebe end_PORT[x-2]
				end_aux[4] = end_PORT1[x-1]; //end_aux[4] recebe end_PORT[x-1]
				y = 0; //Zera a variável y
			}
	  }
	}
	if(y == 5 && z == 0)
	{
		z = 0;
	}
	else
	{
		for(x = 0;x < 5;x++) //Recebe em end_PORT[x] todo o reposicionamento do vetor end_aux[x]
		{
			end_PORT1[x] = end_aux[x];
		}
	}
	delay_ms(100);
}

void fnComandoAT_HTTP(void) //Permite fazer a leitura da porta remota
{
	dado_recebido = 0; //Armazena zero na variável dado_recebido para poder receber os dados
	primeiro = 0; //Armazena zero na variável primeiro para poder sincronizar o primeiro dado
	for(x = 0;x < 255;x++) //Zera o vetor recebe_serial de recebimentos dos dados e o vetor envia_serial do envio dos dados
	{
		recebe_serial[x] = 0;
		envia_serial[x] = 0;
	}

	str3 = "AT+HTPTP";

	for(x = 0;x < strlen(str3);x++)
	{
		envia_serial[x] = str3[x];
	}

	envia_serial[x] = 0x0D;
	SERIAL_ETHERNET_SendBlock((byte*)&envia_serial,(x+1),&Sent); //Envia os 11 bytes pela serial ao módulo ethernet para executar o comando

	while(estado_MODULO_ETHERNET != ESTADO_COMANDO_OK); //Aguarda o módulo responder com ESTADO_WANN_OK informando que recebeu os dados corretamente
	estado_MODULO_ETHERNET = ESTADO_ESPERA;	//Faz com que estado_MODULO_ETHERNET fique em ESTADO_ESPERA novamente

	delay_ms(100);
}

void fnComandoAT_HTPHEAD(void) //Permite fazer a leitura da porta remota
{
	dado_recebido = 0; //Armazena zero na variável dado_recebido para poder receber os dados
	primeiro = 0; //Armazena zero na variável primeiro para poder sincronizar o primeiro dado
	for(x = 0;x < 255;x++) //Zera o vetor recebe_serial de recebimentos dos dados e o vetor envia_serial do envio dos dados
	{
		envia_serial[x] = 0;
		recebe_serial[x] = 0;
	}

	str3 = "AT+HTPHEAD";

	for(x = 0;x < strlen(str3);x++)
	{
		envia_serial[x] = str3[x];
	}

	envia_serial[x] = 0x0D;
	SERIAL_ETHERNET_SendBlock((byte*)&envia_serial,(x+1),&Sent); //Envia os 11 bytes pela serial ao módulo ethernet para executar o comando

	while(estado_MODULO_ETHERNET != ESTADO_COMANDO_OK); //Aguarda o módulo responder com ESTADO_WANN_OK informando que recebeu os dados corretamente
	estado_MODULO_ETHERNET = ESTADO_ESPERA;	//Faz com que estado_MODULO_ETHERNET fique em ESTADO_ESPERA novamente

	delay_ms(100);
}


void fnPosicionaIP(void) //Reposiciona os endereços IP, máscara de sub-rede e GATEWAY no módulo ethernet
{
	//Reposicionando o endereço corretamente dentro do vetor para apresentação no LCD
	y = 0; //Faz y = 0 para poder contar as virgulas
	z = 0; //Faz z = 0 para poder separar os 3 endereços em cada vetor em separado
	for(x = 0;x < 15;x++) //Reposiciona os 15 bytes
	{
		if(end_IP[x] != '.' && end_IP[x] != 'X') //Se end_IP[x] não for igual a '.' e end_IP[x] não for igual a 'X'
		{
			y++; //Incrementa y
		}
		else if(end_IP[x] == '.' || end_IP[x] == 'X') //Senão se end_IP[x] for igual a '.' ou end_IP[x] for igual a 'X' então
		{
			z++; //Incrementa z
			if(y == 1 && z == 1) //Se y for igual a 1 e z for igual a 1 então
			{
				end_aux[0] = '0'; //end_aux[0] recebe '0'
				end_aux[1] = '0'; //end_aux[1] recebe '0'
				end_aux[2] = end_IP[x-1]; //end_aux[2] recebe end_IP[x-1]
				end_aux[3] = end_IP[x]; //end_aux[3] recebe end_IP[x]
				y = 0; //Zera a variável y
			}
			else if(y == 2 && z == 1) //Senão se y for igual a 2 e z for igual a 1 então
			{
				end_aux[0] = '0'; //end_aux[0] recebe '0'
				end_aux[1] = end_IP[x-2]; //end_aux[1] recebe end_IP[x-2]
				end_aux[2] = end_IP[x-1]; //end_aux[2] recebe end_IP[x-1]
				end_aux[3] = end_IP[x]; //end_aux[0] recebe end_IP[x]
				y = 0; //Zera a variável y
			}
			else if(y == 3 && z == 1) //Senão se y for igual a 3 e z for igual a 1 então
			{
				end_aux[0] = end_IP[x-3]; //end_aux[0] recebe end_IP[x-3]
				end_aux[1] = end_IP[x-2]; //end_aux[1] recebe end_IP[x-2]
				end_aux[2] = end_IP[x-1]; //end_aux[2] recebe end_IP[x-1]
				end_aux[3] = end_IP[x]; //end_aux[3] recebe end_IP[x]
				y = 0; //Zera a variável y
			}
			else if(y == 1 && z == 2) //Senão se y for igual a 1 e z for igual a 2 então
			{
				end_aux[4] = '0'; //end_aux[4] recebe '0'
				end_aux[5] = '0'; //end_aux[5] recebe '0'
				end_aux[6] = end_IP[x-1]; //end_aux[6] recebe end_IP[x-1]
				end_aux[7] = end_IP[x]; //end_aux[7] recebe end_IP[x]
				y = 0; //Zera a variável y
			}
			else if(y == 2 && z == 2) //Senão se y for igual a 2 e z for igual a 2 então
			{
				end_aux[4] = '0'; //end_aux[4] recebe '0'
				end_aux[5] = end_IP[x-2]; //end_aux[5] recebe end_IP[x-2]
				end_aux[6] = end_IP[x-1]; //end_aux[6] recebe end_IP[x-1]
				end_aux[7] = end_IP[x]; //end_aux[7] recebe end_IP[x]
				y = 0; //Zera a variável y
			}
			else if(y == 3 && z == 2) //Senão se y for igual a 3 e z for igual a 2 então
			{
				end_aux[4] = end_IP[x-3]; //end_aux[4] recebe end_IP[x-3]
				end_aux[5] = end_IP[x-2]; //end_aux[5] recebe end_IP[x-2]
				end_aux[6] = end_IP[x-1]; //end_aux[6] recebe end_IP[x-1]
				end_aux[7] = end_IP[x]; //end_aux[7] recebe end_IP[x]
				y = 0; //Zera a variável y
			}
			if(y == 1 && z == 3) //Se y for igual a 1 e z for igual a 3 então
			{
				end_aux[8] = '0'; //end_aux[8] recebe '0'
				end_aux[9] = '0'; //end_aux[9] recebe '0'
				end_aux[10] = end_IP[x-1]; //end_aux[10] recebe end_IP[x-1]
				end_aux[11] = end_IP[x]; //end_aux[11] recebe end_IP[x]
				y = 0; //Zera a variável y
			}
			else if(y == 2 && z == 3) //Senão se y for igual a 2 e z for igual a 3 então
			{
				end_aux[8] = '0'; //end_aux[8] recebe '0'
				end_aux[9] = end_IP[x-2]; //end_aux[9] recebe end_IP[x-2]
				end_aux[10] = end_IP[x-1]; //end_aux[10] recebe end_IP[x-1]
				end_aux[11] = end_IP[x]; //end_aux[11] recebe end_IP[x]
				y = 0; //Zera a variável y
			}
			else if(y == 3 && z == 3) //Senão se y for igual a 3 e z for igual a 3 então
			{
				end_aux[8] = end_IP[x-3]; //end_aux[8] recebe end_IP[x-3]
				end_aux[9] = end_IP[x-2]; //end_aux[9] recebe end_IP[x-2]
				end_aux[10] = end_IP[x-1]; //end_aux[10] recebe end_IP[x-1]
				end_aux[11] = end_IP[x]; //end_aux[11] recebe end_IP[x]
				y = 0; //Zera a variável y
			}
			if(y == 1 && z == 4) //Se y for igual a 1 e z for igual a 4 então
			{
				end_aux[12] = '0'; //end_aux[12] recebe '0'
				end_aux[13] = '0'; //end_aux[13] recebe '0'
				end_aux[14] = end_IP[x-1]; //end_aux[14] recebe end_IP[x-1]
				y = 0; //Zera a variável y
				x = 15; //Faz x igual a 15 para sair do laço for
			}
			else if(y == 2 && z == 4) //Senão se y for igual a 2 e z for igual a 4 então
			{
				end_aux[12] = '0'; //end_aux[12] recebe '0'
				end_aux[13] = end_IP[x-2]; //end_aux[13] recebe end_IP[x-2]
				end_aux[14] = end_IP[x-1]; //end_aux[14] recebe end_IP[x-1]
				y = 0; //Zera a variável y
				x = 15; //Faz x igual a 15 para sair do laço for
			}
			else if(y == 3 && z == 4) //Senão se y for igual a 3 e z for igual a 4 então
			{
				end_aux[12] = end_IP[x-3]; //end_aux[12] recebe end_IP[x-3]
				end_aux[13] = end_IP[x-2]; //end_aux[13] recebe end_IP[x-2]
				end_aux[14] = end_IP[x-1]; //end_aux[14] recebe end_IP[x-1]
				y = 0; //Zera a variável y
				x = 15; //Faz x igual a 15 para sair do laço for
			}
	  }
	}
	for(x = 0;x < 15;x++) //Recebe em end_IP[x] todo o reposicionamento do vetor end_aux[x]
	{
		end_IP[x] = end_aux[x];
	}

	//Reposicionando o endereço corretamente dentro do vetor para apresentação no LCD
	y = 0; //Faz y = 0 para poder contar as virgulas
	z = 0; //Faz z = 0 para poder separar os 3 endereços em cada vetor em separado
	for(x = 0;x < 15;x++) //Reposiciona os 15 bytes
	{
		if(end_SUB_MASK[x] != '.' && end_SUB_MASK[x] != 'X') //Se end_SUB_MASK[x] não for igual a '.' e end_SUB_MASK[x] não for igual a 'X' então
		{
			y++; //Incrementa y
		}
		else if(end_SUB_MASK[x] == '.' || end_SUB_MASK[x] == 'X') //Senão se end_SUB_MASK[x] for igual a '.' ou end_SUB_MASK[x] for igual a 'X' então
		{
			z++; //Incrementa z
			if(y == 1 && z == 1) //Se y for igual a 1 e z for igual a 1 então
			{
				end_aux[0] = '0'; //end_aux[0] recebe '0'
				end_aux[1] = '0'; //end_aux[1] recebe '0'
				end_aux[2] = end_SUB_MASK[x-1]; //end_aux[2] recebe end_SUB_MASK[x-1]
				end_aux[3] = end_SUB_MASK[x]; //end_aux[3] recebe end_SUB_MASK[x]
				y = 0; //Zera a variável y
			}
			else if(y == 2 && z == 1) //Senão se y for igual a 2 e z for igual a 1 então
			{
				end_aux[0] = '0'; //end_aux[0] recebe '0'
				end_aux[1] = end_SUB_MASK[x-2]; //end_aux[1] recebe end_SUB_MASK[x-2]
				end_aux[2] = end_SUB_MASK[x-1]; //end_aux[2] recebe end_SUB_MASK[x-1]
				end_aux[3] = end_SUB_MASK[x]; //end_aux[0] recebe end_SUB_MASK[x]
				y = 0; //Zera a variável y
			}
			else if(y == 3 && z == 1) //Senão se y for igual a 3 e z for igual a 1 então
			{
				end_aux[0] = end_SUB_MASK[x-3]; //end_aux[0] recebe end_SUB_MASK[x-3]
				end_aux[1] = end_SUB_MASK[x-2]; //end_aux[1] recebe end_SUB_MASK[x-2]
				end_aux[2] = end_SUB_MASK[x-1]; //end_aux[2] recebe end_SUB_MASK[x-1]
				end_aux[3] = end_SUB_MASK[x]; //end_aux[3] recebe end_SUB_MASK[x]
				y = 0; //Zera a variável y
			}
			else if(y == 1 && z == 2) //Senão se y for igual a 1 e z for igual a 2 então
			{
				end_aux[4] = '0'; //end_aux[4] recebe '0'
				end_aux[5] = '0'; //end_aux[5] recebe '0'
				end_aux[6] = end_SUB_MASK[x-1]; //end_aux[6] recebe end_SUB_MASK[x-1]
				end_aux[7] = end_SUB_MASK[x]; //end_aux[7] recebe end_SUB_MASK[x]
				y = 0; //Zera a variável y
			}
			else if(y == 2 && z == 2) //Senão se y for igual a 2 e z for igual a 2 então
			{
				end_aux[4] = '0'; //end_aux[4] recebe '0'
				end_aux[5] = end_SUB_MASK[x-2]; //end_aux[5] recebe end_SUB_MASK[x-2]
				end_aux[6] = end_SUB_MASK[x-1]; //end_aux[6] recebe end_SUB_MASK[x-1]
				end_aux[7] = end_SUB_MASK[x]; //end_aux[7] recebe end_SUB_MASK[x]
				y = 0; //Zera a variável y
			}
			else if(y == 3 && z == 2) //Senão se y for igual a 3 e z for igual a 2 então
			{
				end_aux[4] = end_SUB_MASK[x-3]; //end_aux[4] recebe end_SUB_MASK[x-3]
				end_aux[5] = end_SUB_MASK[x-2]; //end_aux[5] recebe end_SUB_MASK[x-2]
				end_aux[6] = end_SUB_MASK[x-1]; //end_aux[6] recebe end_SUB_MASK[x-1]
				end_aux[7] = end_SUB_MASK[x]; //end_aux[7] recebe end_SUB_MASK[x]
				y = 0; //Zera a variável y
			}
			if(y == 1 && z == 3) //Se y for igual a 1 e z for igual a 3 então
			{
				end_aux[8] = '0'; //end_aux[8] recebe '0'
				end_aux[9] = '0'; //end_aux[9] recebe '0'
				end_aux[10] = end_SUB_MASK[x-1]; //end_aux[10] recebe end_SUB_MASK[x-1]
				end_aux[11] = end_SUB_MASK[x]; //end_aux[11] recebe end_SUB_MASK[x]
				y = 0; //Zera a variável y
			}
			else if(y == 2 && z == 3) //Senão se y for igual a 2 e z for igual a 3 então
			{
				end_aux[8] = '0'; //end_aux[8] recebe '0'
				end_aux[9] = end_SUB_MASK[x-2]; //end_aux[9] recebe end_SUB_MASK[x-2]
				end_aux[10] = end_SUB_MASK[x-1]; //end_aux[10] recebe end_SUB_MASK[x-1]
				end_aux[11] = end_SUB_MASK[x]; //end_aux[11] recebe end_SUB_MASK[x]
				y = 0; //Zera a variável y
			}
			else if(y == 3 && z == 3) //Senão se y for igual a 3 e z for igual a 3 então
			{
				end_aux[8] = end_SUB_MASK[x-3]; //end_aux[8] recebe end_SUB_MASK[x-3]
				end_aux[9] = end_SUB_MASK[x-2]; //end_aux[9] recebe end_SUB_MASK[x-2]
				end_aux[10] = end_SUB_MASK[x-1]; //end_aux[10] recebe end_SUB_MASK[x-1]
				end_aux[11] = end_SUB_MASK[x]; //end_aux[11] recebe end_SUB_MASK[x]
				y = 0; //Zera a variável y
			}
			if(y == 1 && z == 4) //Se y for igual a 1 e z for igual a 4 então
			{
				end_aux[12] = '0'; //end_aux[12] recebe '0'
				end_aux[13] = '0'; //end_aux[13] recebe '0'
				end_aux[14] = end_SUB_MASK[x-1]; //end_aux[14] recebe end_SUB_MASK[x-1]
				y = 0; //Zera a variável y
				x = 15; //Faz x igual a 15 para sair do laço for
			}
			else if(y == 2 && z == 4) //Senão se y for igual a 2 e z for igual a 4 então
			{
				end_aux[12] = '0'; //end_aux[12] recebe '0'
				end_aux[13] = end_SUB_MASK[x-2]; //end_aux[13] recebe end_SUB_MASK[x-2]
				end_aux[14] = end_SUB_MASK[x-1]; //end_aux[14] recebe end_SUB_MASK[x-1]
				y = 0; //Zera a variável y
				x = 15; //Faz x igual a 15 para sair do laço for
			}
			else if(y == 3 && z == 4) //Senão se y for igual a 3 e z for igual a 4 então
			{
				end_aux[12] = end_SUB_MASK[x-3]; //end_aux[12] recebe end_SUB_MASK[x-3]
				end_aux[13] = end_SUB_MASK[x-2]; //end_aux[13] recebe end_SUB_MASK[x-2]
				end_aux[14] = end_SUB_MASK[x-1]; //end_aux[14] recebe end_SUB_MASK[x-1]
				y = 0; //Zera a variável y
				x = 15; //Faz x igual a 15 para sair do laço for
			}
	  }
	}
	for(x = 0;x < 15;x++) //Recebe em end_SUB_MASK[x] todo o reposicionamento do vetor end_aux[x]
	{
		end_SUB_MASK[x] = end_aux[x];
	}

	//Reposicionando o endereço corretamente dentro do vetor para apresentação no LCD
	y = 0; //Faz y = 0 para poder contar as virgulas
	z = 0; //Faz z = 0 para poder separar os 3 endereços em cada vetor em separado
	for(x = 0;x < 15;x++) //Reposiciona os 15 bytes
	{
		if(end_GATEWAY[x] != '.' && end_GATEWAY[x] != 'X') //Se end_GATEWAY[x] não for igual a '.' e end_GATEWAY[x] não for igual a 'X' então
		{
			y++; //Incrementa y
		}
		else if(end_GATEWAY[x] == '.' || end_GATEWAY[x] == 'X') //Senão se end_GATEWAY for igual a '.' ou end_GATEWAY for igual a 'X' então
		{
			z++; //Incrementa z
			if(y == 1 && z == 1) //Se y for igual a 1 e z for igual a 1 então
			{
				end_aux[0] = '0'; //end_aux[0] recebe '0'
				end_aux[1] = '0'; //end_aux[1] recebe '0'
				end_aux[2] = end_GATEWAY[x-1]; //end_aux[2] recebe end_GATEWAY[x-1]
				end_aux[3] = end_GATEWAY[x]; //end_aux[3] recebe end_GATEWAY[x]
				y = 0; //Zera a variável y
			}
			else if(y == 2 && z == 1) //Senão se y for igual a 2 e z for igual a 1 então
			{
				end_aux[0] = '0'; //end_aux[0] recebe '0'
				end_aux[1] = end_GATEWAY[x-2]; //end_aux[1] recebe end_GATEWAY[x-2]
				end_aux[2] = end_GATEWAY[x-1]; //end_aux[2] recebe end_GATEWAY[x-1]
				end_aux[3] = end_GATEWAY[x]; //end_aux[0] recebe end_GATEWAY[x]
				y = 0; //Zera a variável y
			}
			else if(y == 3 && z == 1) //Senão se y for igual a 3 e z for igual a 1 então
			{
				end_aux[0] = end_GATEWAY[x-3]; //end_aux[0] recebe end_GATEWAY[x-3]
				end_aux[1] = end_GATEWAY[x-2]; //end_aux[1] recebe end_GATEWAY[x-2]
				end_aux[2] = end_GATEWAY[x-1]; //end_aux[2] recebe end_GATEWAY[x-1]
				end_aux[3] = end_GATEWAY[x]; //end_aux[3] recebe end_GATEWAY[x]
				y = 0; //Zera a variável y
			}
			else if(y == 1 && z == 2) //Senão se y for igual a 1 e z for igual a 2 então
			{
				end_aux[4] = '0'; //end_aux[4] recebe '0'
				end_aux[5] = '0'; //end_aux[5] recebe '0'
				end_aux[6] = end_GATEWAY[x-1]; //end_aux[6] recebe end_GATEWAY[x-1]
				end_aux[7] = end_GATEWAY[x]; //end_aux[7] recebe end_GATEWAY[x]
				y = 0; //Zera a variável y
			}
			else if(y == 2 && z == 2) //Senão se y for igual a 2 e z for igual a 2 então
			{
				end_aux[4] = '0'; //end_aux[4] recebe '0'
				end_aux[5] = end_GATEWAY[x-2]; //end_aux[5] recebe end_GATEWAY[x-2]
				end_aux[6] = end_GATEWAY[x-1]; //end_aux[6] recebe end_GATEWAY[x-1]
				end_aux[7] = end_GATEWAY[x]; //end_aux[7] recebe end_GATEWAY[x]
				y = 0; //Zera a variável y
			}
			else if(y == 3 && z == 2) //Senão se y for igual a 3 e z for igual a 2 então
			{
				end_aux[4] = end_GATEWAY[x-3]; //end_aux[4] recebe end_GATEWAY[x-3]
				end_aux[5] = end_GATEWAY[x-2]; //end_aux[5] recebe end_GATEWAY[x-2]
				end_aux[6] = end_GATEWAY[x-1]; //end_aux[6] recebe end_GATEWAY[x-1]
				end_aux[7] = end_GATEWAY[x]; //end_aux[7] recebe end_GATEWAY[x]
				y = 0; //Zera a variável y
			}
			if(y == 1 && z == 3) //Se y for igual a 1 e z for igual a 3 então
			{
				end_aux[8] = '0'; //end_aux[8] recebe '0'
				end_aux[9] = '0'; //end_aux[9] recebe '0'
				end_aux[10] = end_GATEWAY[x-1]; //end_aux[10] recebe end_GATEWAY[x-1]
				end_aux[11] = end_GATEWAY[x]; //end_aux[11] recebe end_GATEWAY[x]
				y = 0; //Zera a variável y
			}
			else if(y == 2 && z == 3) //Senão se y for igual a 2 e z for igual a 3 então
			{
				end_aux[8] = '0'; //end_aux[8] recebe '0'
				end_aux[9] = end_GATEWAY[x-2]; //end_aux[9] recebe end_GATEWAY[x-2]
				end_aux[10] = end_GATEWAY[x-1]; //end_aux[10] recebe end_GATEWAY[x-1]
				end_aux[11] = end_GATEWAY[x]; //end_aux[11] recebe end_GATEWAY[x]
				y = 0; //Zera a variável y
			}
			else if(y == 3 && z == 3) //Senão se y for igual a 3 e z for igual a 3 então
			{
				end_aux[8] = end_GATEWAY[x-3]; //end_aux[8] recebe end_GATEWAY[x-3]
				end_aux[9] = end_GATEWAY[x-2]; //end_aux[9] recebe end_GATEWAY[x-2]
				end_aux[10] = end_GATEWAY[x-1]; //end_aux[10] recebe end_GATEWAY[x-1]
				end_aux[11] = end_GATEWAY[x]; //end_aux[11] recebe end_GATEWAY[x]
				y = 0; //Zera a variável y
			}
			if(y == 1 && z == 4) //Se y for igual a 1 e z for igual a 4 então
			{
				end_aux[12] = '0'; //end_aux[12] recebe '0'
				end_aux[13] = '0'; //end_aux[13] recebe '0'
				end_aux[14] = end_GATEWAY[x-1]; //end_aux[14] recebe end_GATEWAY[x-1]
				y = 0; //Zera a variável y
				x = 15; //Faz x igual a 15 para sair do laço for
			}
			else if(y == 2 && z == 4) //Senão se y for igual a 2 e z for igual a 4 então
			{
				end_aux[12] = '0'; //end_aux[12] recebe '0'
				end_aux[13] = end_GATEWAY[x-2]; //end_aux[13] recebe end_GATEWAY[x-2]
				end_aux[14] = end_GATEWAY[x-1]; //end_aux[14] recebe end_GATEWAY[x-1]
				y = 0; //Zera a variável y
				x = 15; //Faz x igual a 15 para sair do laço for
			}
			else if(y == 3 && z == 4) //Senão se y for igual a 3 e z for igual a 4 então
			{
				end_aux[12] = end_GATEWAY[x-3]; //end_aux[12] recebe end_GATEWAY[x-3]
				end_aux[13] = end_GATEWAY[x-2]; //end_aux[13] recebe end_GATEWAY[x-2]
				end_aux[14] = end_GATEWAY[x-1]; //end_aux[14] recebe end_GATEWAY[x-1]
				y = 0; //Zera a variável y
				x = 15; //Faz x igual a 15 para sair do laço for
			}
	  }
	}
	for(x = 0;x < 15;x++) //Recebe em end_GATEWAY[x] todo o reposicionamento do vetor end_aux[x]
	{
		end_GATEWAY[x] = end_aux[x];
	}
	delay_ms(100);
}

void fnGravaIPs(void) //Grava os endereços IP, máscara de sub-rede e GATEWAY no módulo ethernet
{
	dado_recebido = 0; //Armazena zero na variável dado_recebido para poder receber os dados
	primeiro = 0; //Armazena zero na variável primeiro para poder sincronizar o primeiro dado
	for(x = 0;x < 255;x++) //Zera o vetor recebe_serial de recebimentos dos dados e o vetor envia_serial do envio dos dados
	{
		recebe_serial[x] = 0;
		envia_serial[x] = 0;
	}

	//fnEstadoComandoAT(); //Entra no modo de comandos AT

	if(PADRAO == _STATIC)
	{
		str3 = "AT+WANN=STATIC,";
		for(x = 0;x < strlen(str3);x++)
		{
			envia_serial[x] = str3[x];
		}

		for(x = 15;x < 30;x++) //Posiciona os 15 bytes do endereço IP corretamente no vetor envia_serial
		{
			envia_serial[x] = end_IP[x - 15];
			Write_Buffer_FLASH[x-15] = end_IP[x-15];
		}

		envia_serial[30] = ','; //envia_serial[30] recebe o valor ','

		for(x = 31;x < 46;x++) //Posiciona os 15 bytes do endereço da MASCARA DE SUB REDE corretamente no vetor envia_serial
		{
			envia_serial[x] = end_SUB_MASK[x - 31];
			Write_Buffer_FLASH[x-16] = end_SUB_MASK[x-31];
		}

		envia_serial[46] = ','; //envia_serial[46] recebe o valor ','

		for(x = 47;x < 62;x++) //Posiciona os 15 bytes do endereço GATEWAY corretamente no vetor envia_serial
		{
			envia_serial[x] = end_GATEWAY[x - 47];
			Write_Buffer_FLASH[x-17] = end_GATEWAY[x-47];
		}

		for(y = 63;y < 78;y++) //Posiciona os 15 bytes do endereço DNS corretamente no vetor envia_serial
		{
			Write_Buffer_FLASH[y-18] = end_DNS[y-63];
		}

		ESCREVE_FLASH_INTERNA(endFLASHIP,60,0);
	}
	else if(PADRAO == _STATIC_REMOTO)
	{
		str3 = "AT+WANN=STATIC,";
		for(x = 0;x < strlen(str3);x++)
		{
			envia_serial[x] = str3[x];
		}

		for(x = 15;x < 30;x++) //Posiciona os 15 bytes do endereço IP corretamente no vetor envia_serial
		{
			envia_serial[x] = end_IP[x - 15];
			Write_Buffer_FLASH[x-15] = end_IP[x-15];
		}

		envia_serial[30] = ','; //envia_serial[30] recebe o valor ','

		for(x = 31;x < 46;x++) //Posiciona os 15 bytes do endereço da MASCARA DE SUB REDE corretamente no vetor envia_serial
		{
			envia_serial[x] = end_SUB_MASK[x - 31];
			Write_Buffer_FLASH[x-16] = end_SUB_MASK[x-31];
		}

		envia_serial[46] = ','; //envia_serial[46] recebe o valor ','

		for(x = 47;x < 62;x++) //Posiciona os 15 bytes do endereço GATEWAY corretamente no vetor envia_serial
		{
			envia_serial[x] = end_GATEWAY[x - 47];
			Write_Buffer_FLASH[x-17] = end_GATEWAY[x-47];
		}

		for(y = 63;y < 78;y++) //Posiciona os 15 bytes do endereço DNS corretamente no vetor envia_serial
		{
			Write_Buffer_FLASH[y-18] = end_DNS[y-63];
		}

		ESCREVE_FLASH_INTERNA(endFLASHIP,60,0);
	}
	else if(PADRAO == _DHCP_REMOTO)
	{

		str3 = "AT+WANN=DHCP,192.168.010.098,255.255.255.000,192.168.010.001";
		for(x = 0;x < strlen(str3);x++)
		{
			envia_serial[x] = str3[x];
		}
	}

	envia_serial[x] = 0x0D; //envia_serial[62] recebe o valor 0x0D
	SERIAL_ETHERNET_SendBlock((byte*)&envia_serial,(x+1),&Sent); //Envia os 63 bytes pela serial ao módulo ethernet para executar o comando

	while(estado_MODULO_ETHERNET != ESTADO_COMANDO_OK); //Aguarda o módulo responder com ESTADO_WANN_OK informando que recebeu os dados corretamente
	estado_MODULO_ETHERNET = ESTADO_ESPERA;	//Faz com que estado_MODULO_ETHERNET fique em ESTADO_ESPERA novamente

	//fnResetaModulo(); //Reseta o módulo para que a alteração seja efetivada

	//fnEstadoComandoAT(); //Entra no modo de comandos AT pois ao resetar o módulo o mesmo volta para o modo NORMAL

	delay_ms(100);
}

void fnGravaIPs_PADRAO(void) //Grava os endereços IP, máscara de sub-rede e GATEWAY no módulo ethernet PADROES porque estava em DHCP anteriormente
{
	dado_recebido = 0; //Armazena zero na variável dado_recebido para poder receber os dados
	primeiro = 0; //Armazena zero na variável primeiro para poder sincronizar o primeiro dado
	for(x = 0;x < 255;x++) //Zera o vetor recebe_serial de recebimentos dos dados e o vetor envia_serial do envio dos dados
	{
		recebe_serial[x] = 0;
		envia_serial[x] = 0;
	}

	str3 = "AT+WANN=static,192.168.010.098,255.255.255.000,192.168.010.001";

	for(x = 0;x < strlen(str3);x++)
	{
		envia_serial[x] = str3[x];
	}

	envia_serial[x] = 0x0D; //envia_serial[62] recebe o valor 0x0D
	SERIAL_ETHERNET_SendBlock((byte*)&envia_serial,(x+1),&Sent); //Envia os 63 bytes pela serial ao módulo ethernet para executar o comando
	INICIA_TIME_OUT_ETHERNET = SIM;
	while(estado_MODULO_ETHERNET != ESTADO_COMANDO_OK && FIM_TIME_OUT_ETHERNET == NAO); //Aguarda o módulo responder com ESTADO_WANN_OK informando que recebeu os dados corretamente
	INICIA_TIME_OUT_ETHERNET = NAO;
	FIM_TIME_OUT_ETHERNET = NAO;
	estado_MODULO_ETHERNET = ESTADO_ESPERA;	//Faz com que estado_MODULO_ETHERNET fique em ESTADO_ESPERA novamente

	//fnResetaModulo(); //Reseta o módulo para que a alteração seja efetivada

	//fnEstadoComandoAT(); //Entra no modo de comandos AT pois ao resetar o módulo o mesmo volta para o modo NORMAL

	delay_ms(100);
}

void fnGravaDNS(void)
{
	dado_recebido = 0; //Armazena zero na variável dado_recebido para poder receber os dados
	primeiro = 0; //Armazena zero na variável primeiro para poder sincronizar o primeiro dado
	for(x = 0;x < 255;x++) //Zera o vetor recebe_serial de recebimentos dos dados e o vetor envia_serial do envio dos dados
	{
		recebe_serial[x] = 0;
		envia_serial[x] = 0;
	}

	str3 = "AT+DNS=";

	for(x = 0;x < strlen(str3);x++)
	{
		envia_serial[x] = str3[x];
	}

	y = x;

	for(y;y < (x+15);y++) //Posiciona os 15 bytes do endereço IP corretamente no vetor envia_serial
	{
		envia_serial[y] = end_DNS[y - x];
	}

	envia_serial[y] = 0x0D; //envia_serial[22] recebe o valor 0x0D
	SERIAL_ETHERNET_SendBlock((byte*)&envia_serial,(y+1),&Sent); //Envia os 23 bytes pela serial ao módulo ethernet para executar o comando

	INICIA_TIME_OUT_ETHERNET = SIM;
	while(estado_MODULO_ETHERNET != ESTADO_COMANDO_OK && FIM_TIME_OUT_ETHERNET == NAO); //Aguarda o módulo responder com ESTADO_WANN_OK informando que recebeu os dados corretamente
	INICIA_TIME_OUT_ETHERNET = NAO;
	FIM_TIME_OUT_ETHERNET = NAO;
	estado_MODULO_ETHERNET = ESTADO_ESPERA;	//Faz com que estado_MODULO_ETHERNET fique em ESTADO_ESPERA novamente

	//fnResetaModulo(); //Reseta o módulo para que a alteração seja efetivada

	//fnEstadoComandoAT(); //Entra no modo de comandos AT pois ao resetar o módulo o mesmo volta para o modo NORMAL

	for(x = 0;x < 15;x++)
	{
		Write_Buffer_FLASH[x] = end_DNS[x];
	}

	ESCREVE_FLASH_INTERNA(endFLASHDNS,15,0);

	delay_ms(100);
}

void fnGravaPORT(void) //Grava o endereço da PORTA WEB no módulo ethernet
{
	dado_recebido = 0; //Armazena zero na variável dado_recebido para poder receber os dados
	primeiro = 0; //Armazena zero na variável primeiro para poder sincronizar o primeiro dado
	for(x = 0;x < 70;x++) //Zera o vetor recebe_serial de recebimentos dos dados e o vetor envia_serial do envio dos dados
	{
		recebe_serial[x] = 0;
		envia_serial[x] = 0;
	}

	str3 = "AT+WEBPORT=";

	for(x = 0;x < strlen(str3);x++)
	{
		envia_serial[x] = str3[x];
	}
	envia_serial[x] = end_PORT[0];
	envia_serial[x+1] = end_PORT[1];
	envia_serial[x+2] = end_PORT[2];
	envia_serial[x+3] = end_PORT[3];
	envia_serial[x+4] = end_PORT[4];

	envia_serial[x+5] = 0x0D; //envia_serial[16] recebe o valor 0x0D
	SERIAL_ETHERNET_SendBlock((byte*)&envia_serial,(x+6),&Sent); //Envia os 17 bytes pela serial ao módulo ethernet para executar o comando

	while(estado_MODULO_ETHERNET != ESTADO_COMANDO_OK); //Aguarda o módulo responder com ESTADO_WANN_OK informando que recebeu os dados corretamente
	estado_MODULO_ETHERNET = ESTADO_ESPERA;	//Faz com que estado_MODULO_ETHERNET fique em ESTADO_ESPERA novamente

	//fnResetaModulo(); //Reseta o módulo para que a alteração seja efetivada

	//fnEstadoComandoAT(); //Entra no modo de comandos AT pois ao resetar o módulo o mesmo volta para o modo NORMAL

	delay_ms(100);
}

void fnGravaSOCK(void)
{
	dado_recebido = 0; //Armazena zero na variável dado_recebido para poder receber os dados
	primeiro = 0; //Armazena zero na variável primeiro para poder sincronizar o primeiro dado
	for(x = 0;x < 255;x++) //Zera o vetor recebe_serial de recebimentos dos dados e o vetor envia_serial do envio dos dados
	{
		recebe_serial[x] = 0;
		envia_serial[x] = 0;
	}

	if(PADRAO == _STATIC)
	{
		str3 = "AT+SOCK=TCPS,192.168.10.4,00080"; //Configura como TCP Server mode

		for(x = 0;x < strlen(str3);x++)
		{
			envia_serial[x] = str3[x];
		}
	}
	else if(PADRAO == _STATIC_REMOTO)
	{
		str3 = "AT+SOCK=HTPC,209.126.120.201,00080"; //Configura como HTTP Client mode

		for(x = 0;x < strlen(str3);x++)
		{
			envia_serial[x] = str3[x];
		}
	}
	else if(PADRAO == _DHCP_REMOTO)
	{
		str3 = "AT+SOCK=HTPC,209.126.120.201,00080"; //Configura como HTTP Client mode

		for(x = 0;x < strlen(str3);x++)
		{
			envia_serial[x] = str3[x];
		}
	}

	envia_serial[x] = 0x0D; //envia_serial[62] recebe o valor 0x0D
	SERIAL_ETHERNET_SendBlock((byte*)&envia_serial,(x+1),&Sent); //Envia os 17 bytes pela serial ao módulo ethernet para executar o comando

	while(estado_MODULO_ETHERNET != ESTADO_COMANDO_OK); //Aguarda o módulo responder com ESTADO_WANN_OK informando que recebeu os dados corretamente
	estado_MODULO_ETHERNET = ESTADO_ESPERA;	//Faz com que estado_MODULO_ETHERNET fique em ESTADO_ESPERA novamente

	//fnResetaModulo(); //Reseta o módulo para que a alteração seja efetivada

	//fnEstadoComandoAT(); //Entra no modo de comandos AT pois ao resetar o módulo o mesmo volta para o modo NORMAL

	delay_ms(100);
}


void fnGravaSOCKPORT(void) // Grava a porta local que é sempre 20108
{
	dado_recebido = 0; //Armazena zero na variável dado_recebido para poder receber os dados
	primeiro = 0; //Armazena zero na variável primeiro para poder sincronizar o primeiro dado
	for(x = 0;x < 255;x++) //Zera o vetor recebe_serial de recebimentos dos dados e o vetor envia_serial do envio dos dados
	{
		recebe_serial[x] = 0;
		envia_serial[x] = 0;
	}

	str3 = "AT+SOCKPORT=20108";

	for(x = 0;x < strlen(str3);x++)
	{
		envia_serial[x] = str3[x];
	}

	envia_serial[x] = 0x0D; //envia_serial[62] recebe o valor 0x0D
	SERIAL_ETHERNET_SendBlock((byte*)&envia_serial,(x+1),&Sent); //Envia os 17 bytes pela serial ao módulo ethernet para executar o comando

	INICIA_TIME_OUT_ETHERNET = SIM;
	while(estado_MODULO_ETHERNET != ESTADO_COMANDO_OK && FIM_TIME_OUT_ETHERNET == NAO); //Aguarda o módulo responder com ESTADO_WANN_OK informando que recebeu os dados corretamente
	INICIA_TIME_OUT_ETHERNET = NAO;
	FIM_TIME_OUT_ETHERNET = NAO;
	estado_MODULO_ETHERNET = ESTADO_ESPERA;	//Faz com que estado_MODULO_ETHERNET fique em ESTADO_ESPERA novamente

	//fnResetaModulo(); //Reseta o módulo para que a alteração seja efetivada

	//fnEstadoComandoAT(); //Entra no modo de comandos AT pois ao resetar o módulo o mesmo volta para o modo NORMAL

	delay_ms(100);
}

void fnGravaHTPURL(void)
{
	char mensagem_enviada[64];
	memset(mensagem_enviada,0,sizeof(mensagem_enviada));

	dado_recebido = 0; //Armazena zero na variável dado_recebido para poder receber os dados
	primeiro = 0; //Armazena zero na variável primeiro para poder sincronizar o primeiro dado
	for(x = 0;x < 255;x++) //Zera o vetor recebe_serial de recebimentos dos dados e o vetor envia_serial do envio dos dados
	{
		recebe_serial[x] = 0;
		envia_serial[x] = 0;
	}

	strcpy(mensagem_enviada,"AT+HTPURL=");
	strncat(mensagem_enviada,ATHTPURL_END,strlen(ATHTPURL_END));

	//str3 = "AT+HTPURL=/1/index.php?";

	/*for(x = 0;x < strlen(str3);x++)
	{
		//envia_serial[x] = str3[x];
	}
	*/

	for(x = 0;x < strlen(mensagem_enviada);x++)
	{
		envia_serial[x] = mensagem_enviada[x];
	}



	envia_serial[x] = 0x0D;
	SERIAL_ETHERNET_SendBlock((byte*)&envia_serial,(x+1),&Sent); //Envia os 11 bytes pela serial ao módulo ethernet para executar o comando

	while(estado_MODULO_ETHERNET != ESTADO_COMANDO_OK); //Aguarda o módulo responder com ESTADO_WANN_OK informando que recebeu os dados corretamente
	estado_MODULO_ETHERNET = ESTADO_ESPERA;	//Faz com que estado_MODULO_ETHERNET fique em ESTADO_ESPERA novamente

	//fnResetaModulo(); //Reseta o módulo para que a alteração seja efetivada

	//fnEstadoComandoAT(); //Entra no modo de comandos AT pois ao resetar o módulo o mesmo volta para o modo NORMAL

	delay_ms(100);
}

void fnGravaHTPHEAD(void)
{
	dado_recebido = 0; //Armazena zero na variável dado_recebido para poder receber os dados
	primeiro = 0; //Armazena zero na variável primeiro para poder sincronizar o primeiro dado
	for(x = 0;x < 255;x++) //Zera o vetor recebe_serial de recebimentos dos dados e o vetor envia_serial do envio dos dados
	{
		recebe_serial[x] = 0;
		envia_serial[x] = 0;
	}
	str3 = "AT+HTPHEAD=Connection: close        Content-Type:text/html";

	for(x = 0;x < strlen(str3);x++)
	{
		envia_serial[x] = str3[x];
	}

	envia_serial[x] = 0x0D;
	SERIAL_ETHERNET_SendBlock((byte*)&envia_serial,(x+1),&Sent); //Envia os 11 bytes pela serial ao módulo ethernet para executar o comando

	while(estado_MODULO_ETHERNET != ESTADO_COMANDO_OK); //Aguarda o módulo responder com ESTADO_WANN_OK informando que recebeu os dados corretamente
	estado_MODULO_ETHERNET = ESTADO_ESPERA;	//Faz com que estado_MODULO_ETHERNET fique em ESTADO_ESPERA novamente

	//fnResetaModulo(); //Reseta o módulo para que a alteração seja efetivada

	//fnEstadoComandoAT(); //Entra no modo de comandos AT pois ao resetar o módulo o mesmo volta para o modo NORMAL

	delay_ms(100);
}

void fnGravaNOME(void) //Grava o nome do módulo
{
	dado_recebido = 0; //Armazena zero na variável dado_recebido para poder receber os dados
	primeiro = 0; //Armazena zero na variável primeiro para poder sincronizar o primeiro dado
	for(x = 0;x < 255;x++) //Zera o vetor recebe_serial de recebimentos dos dados e o vetor envia_serial do envio dos dados
	{
		recebe_serial[x] = 0;
		envia_serial[x] = 0;
	}

	str3 = "AT+MID=AGATA";

	for(x = 0;x < strlen(str3);x++)
	{
		envia_serial[x] = str3[x];
	}

	envia_serial[x] = 0x0D; //envia_serial[62] recebe o valor 0x0D
	SERIAL_ETHERNET_SendBlock((byte*)&envia_serial,(x+1),&Sent); //Envia os 17 bytes pela serial ao módulo ethernet para executar o comando

	while(estado_MODULO_ETHERNET != ESTADO_COMANDO_OK); //Aguarda o módulo responder com ESTADO_WANN_OK informando que recebeu os dados corretamente
	estado_MODULO_ETHERNET = ESTADO_ESPERA;	//Faz com que estado_MODULO_ETHERNET fique em ESTADO_ESPERA novamente

	//fnResetaModulo(); //Reseta o módulo para que a alteração seja efetivada

	//fnEstadoComandoAT(); //Entra no modo de comandos AT pois ao resetar o módulo o mesmo volta para o modo NORMAL

	delay_ms(100);
}

void fnGravaHTTP(void)
{
	dado_recebido = 0; //Armazena zero na variável dado_recebido para poder receber os dados
	primeiro = 0; //Armazena zero na variável primeiro para poder sincronizar o primeiro dado
	for(x = 0;x < 255;x++) //Zera o vetor recebe_serial de recebimentos dos dados e o vetor envia_serial do envio dos dados
	{
		recebe_serial[x] = 0;
		envia_serial[x] = 0;
	}

	str3 = "AT+HTPTP=POST";

	for(x = 0;x < strlen(str3);x++)
	{
		envia_serial[x] = str3[x];
	}

	envia_serial[x] = 0x0D; //envia_serial[62] recebe o valor 0x0D
	SERIAL_ETHERNET_SendBlock((byte*)&envia_serial,(x+1),&Sent); //Envia os 17 bytes pela serial ao módulo ethernet para executar o comando

	while(estado_MODULO_ETHERNET != ESTADO_COMANDO_OK); //Aguarda o módulo responder com ESTADO_WANN_OK informando que recebeu os dados corretamente
	estado_MODULO_ETHERNET = ESTADO_ESPERA;	//Faz com que estado_MODULO_ETHERNET fique em ESTADO_ESPERA novamente

	//fnResetaModulo(); //Reseta o módulo para que a alteração seja efetivada

	//fnEstadoComandoAT(); //Entra no modo de comandos AT pois ao resetar o módulo o mesmo volta para o modo NORMAL

	delay_ms(100);
}



void fnResetaModulo(void) //Comando para resetar o módulo ethernet e efetivar as alterações comandadas
{
	dado_recebido = 0; //Armazena zero na variável dado_recebido para poder receber os dados
	primeiro = 0; //Armazena zero na variável primeiro para poder sincronizar o primeiro dado
	for(x = 0;x < 255;x++) //Zera o vetor recebe_serial de recebimentos dos dados e o vetor envia_serial do envio dos dados
	{
		recebe_serial[x] = 0;
		envia_serial[x] = 0;
	}

	str3 = "AT+Z"; //Comando para resetar o módulo ethernet

	for(x = 0;x < strlen(str3);x++)
	{
		envia_serial[x] = str3[x];
	}

	envia_serial[x] = 0x0D; //envia_serial[4] recebe o valor 0x0D
	SERIAL_ETHERNET_SendBlock((byte*)&envia_serial,(x+1),&Sent); //Envia os 5 bytes pela serial ao módulo ethernet para executar o comando

	//while(estado_MODULO_ETHERNET != ESTADO_COMANDO_OK); //Aguarda o módulo responder com ESTADO_WANN_OK informando que recebeu os dados corretamente
	estado_MODULO_ETHERNET = ESTADO_ESPERA;	//Faz com que estado_MODULO_ETHERNET fique em ESTADO_ESPERA novamente

    delay_ms(1000); //Espera 100 milisegundos
}

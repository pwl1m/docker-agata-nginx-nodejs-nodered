/*
 * agata_flash_handling.c
 *
 *  Created on: 23/06/2023
 *      Author: marcos.butignol
 *
 *  220623 - agata_flash_handling.c
 *  	criado para definir funcoes de manejo de memoria flash
 */


#include "funcao.h"
#include "time.h"

#include "agata_std_functions.h"
#include "agata_flash_handling.h"
#include "agata_hc_definitions.h"
#include "stdlib.h"

#define 	END_INI_BACKUP_PARAMETROS	0x79000
#define 	NUMERO_DE_PARAMETROS		185

#define  	VALOR_BINARIO 				0
#define 	ASCII_ALFANUMERICO  		1
#define  	ASCII_NUMERICO 				2
#define 	VALOR_BINARIO_MIN1_MAX100	3
#define 	ASCII_ALFANUM_MAIUSCULA		4
#define 	VALOR_BINARIO_MIN1_MAX2		5
#define 	VALOR_BINARIO_MIN1_MAX3		6
#define 	VALOR_BINARIO_MIN1_MAX10	7
#define 	VALOR_BINARIO_MIN1_MAX12	8
#define 	VALOR_BINARIO_MIN1_MAX150	9
#define		VALOR_BINARIO_MIN10_MAX50	10
#define		VALOR_BINARIO_MIN0_MAX1		11
#define		VALOR_BINARIO_MIN0_MAX2		12
#define 	VALOR_BINARIO_MIN0_MAX3		13
#define		VALOR_BINARIO_MIN0_MAX5		14
#define		VALOR_BINARIO_MIN0_MAX31	15


void fnConfereGravaResetaContadorDiario(void){

	/*** Inicializa contador diário se dia for diferente do dia armazenado ***/
	LE_FLASH_INTERNA(endFLASHConferencia_do_Dia,1); //Le o dado armazenado na FLASH
	conferencia_do_dia = Read_Buffer_FLASH[0]; //Armazena em conferencia_dodia o conteudo lido na posição de memória apontada na FLASH
	LE_FLASH_INTERNA(endFLASHFabrica,1); //Verifica se alguma vez a memória foi gravada, se não foi não executa a condição abaixo
	fabrica = Read_Buffer_FLASH[0]; //Armazena em fabrica o conteudo lido na posição de memória apontada na FLASH
	if(Time.Day != conferencia_do_dia && fabrica == MEMORIA_FLASH_GRAVADA) //Se dia de hoje não for igual ao dia gravado é porque é necessario zerar os contadores para começar o dia com novas contagens
	{
	  contador_dia_entra = 0;
	  contador_dia_sai = 0;

	  //CONTADOR DE PASSAGENS - ENTRADAS DIARIAS
	  contador_dia_entra = 0; //Armazena na variável contador_entra o valor 0
	  Write_Buffer_FLASH[OFFSET_CONTADOR_ENTRADAS_D]   = (byte)(contador_dia_entra >> 24); //Escreve o valor do quarto byte mais alto no vetor para gravação na memória FLASH
	  Write_Buffer_FLASH[OFFSET_CONTADOR_ENTRADAS_D + 1] = (byte)(contador_dia_entra >> 16); //Escreve o valor do terceiro byte mais alto no vetor para gravação na memória FLASH
	  Write_Buffer_FLASH[OFFSET_CONTADOR_ENTRADAS_D + 2] = (byte)(contador_dia_entra >> 8); //Escreve o valor do segundo byte mais alto no vetor para gravação na memória FLASH
	  Write_Buffer_FLASH[OFFSET_CONTADOR_ENTRADAS_D + 3] = (byte)(contador_dia_entra); //Escreve o valor do primeiro byte no vetor para gravação na memória FLASH
	  ESCREVE_FLASH_INTERNA(endFLASHContadorEntraDiario,4,0); //Armazena na memória FLASH o zeramento da contagem para entradas

	  //CONTADOR DE PASSAGENS - SAIDAS DIARIAS
	  contador_dia_sai = 0; //Armazena na variável contador_sai o valor 0
	  Write_Buffer_FLASH[OFFSET_CONTADOR_SAIDAS_D] 	= (byte)(contador_dia_sai >> 24); //Escreve o valor do quarto byte mais alto no vetor para gravação na memória FLASH
	  Write_Buffer_FLASH[OFFSET_CONTADOR_SAIDAS_D + 1] = (byte)(contador_dia_sai >> 16); //Escreve o valor do terceiro byte mais alto no vetor para gravação na memória FLASH
	  Write_Buffer_FLASH[OFFSET_CONTADOR_SAIDAS_D + 2] = (byte)(contador_dia_sai >> 8); //Escreve o valor do segundo byte mais alto no vetor para gravação na memória FLASH
	  Write_Buffer_FLASH[OFFSET_CONTADOR_SAIDAS_D + 3] = (byte)(contador_dia_sai); //Escreve o valor do primeiro byte no vetor para gravação na memória FLASH
	  ESCREVE_FLASH_INTERNA(endFLASHContadorSaiDiario,4,0); //Armazena na memória FLASH o zeramento da contagem para saidas

	  conferencia_do_dia = Time.Day;
	  Write_Buffer_FLASH[0] = conferencia_do_dia;
	  ESCREVE_FLASH_INTERNA(endFLASHConferencia_do_Dia,1,0);
	}
	/************************************************************************/
}

void fnGravaContadorEntra(void) //Grava na FLASH o número de entradas
{
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

	estado = ESTADO_ENTRADAS; //Estado a ser executado é ESTADO_ENTRADAS
}

void fnGravaContadorSai(void) //Grava na FLASH o número de saidas
{
	Write_Buffer_FLASH[0] = (byte)(contador_sai >> 24); //Pega o primeiro byte mais alto e desloca 24 casas para poder separar em byte o conteúdo da dword contador_sai que tem 4 bytes
	Write_Buffer_FLASH[1] = (byte)(contador_sai >> 16); //Pega o segundo byte e desloca 16 casas para poder separar em byte o conteúdo da dword contador_sai que tem 4 bytes
	Write_Buffer_FLASH[2] = (byte)(contador_sai >> 8); //Pega o terceiro byte e desloca 8 casas para poder separar em byte o conteúdo da dword contador_sai que tem 4 bytes
	Write_Buffer_FLASH[3] = (byte)(contador_sai); //Pega o quarto byte e não desloca para poder separar em byte o conteúdo da dword contador_sai que tem 4 bytes
	ESCREVE_FLASH_INTERNA(endFLASHContadorSai,4,0); //Escreve na memória FLASH a variável contador_sai alterado no endereço especificado

	Write_Buffer_FLASH[0] = (byte)(contador_dia_sai >> 24); //Pega o primeiro byte mais alto e desloca 24 casas para poder separar em byte o conteúdo da dword contador_sai que tem 4 bytes
	Write_Buffer_FLASH[1] = (byte)(contador_dia_sai >> 16); //Pega o segundo byte e desloca 16 casas para poder separar em byte o conteúdo da dword contador_sai que tem 4 bytes
	Write_Buffer_FLASH[2] = (byte)(contador_dia_sai >> 8); //Pega o terceiro byte e desloca 8 casas para poder separar em byte o conteúdo da dword contador_sai que tem 4 bytes
	Write_Buffer_FLASH[3] = (byte)(contador_dia_sai); //Pega o quarto byte e não desloca para poder separar em byte o conteúdo da dword contador_sai que tem 4 bytes
	ESCREVE_FLASH_INTERNA(endFLASHContadorSaiDiario,4,0); //Escreve na memória FLASH a variável contador_sai alterado no endereço especificado

	estado = ESTADO_SAIDAS; //Estado a ser executado é ESTADO_SAIDAS
}


void fnGravaAuditoria(byte parametro,byte valor_velho,byte valor_novo,char operador,char dispositivo) //Função que grava os eventos de bloqueios e desbloqueios realizados por painel, controle remoto ou detecção de metais
{
	volatile dword endereco = 0; //Zera a variável endereco
	volatile dword bloco = 0; //Zera a variável bloco
	volatile dword pedaco = 0; //Zera a variável pedaco

	int endereco_flag = 0;

	DataHora resultado; //Transforma resultado na estrutura DataHora
	RTC1_GetTime(MyRTCPtr,&Time); //Pega a hora e a data atual do sistema

	resultado.Hora = (byte)Time.Hour; //Armazena na variável resultado.Hora o hora atual
	resultado.Minuto = (byte)Time.Minute; //Armazena na variável resultado.Minuto o minuto atual
	resultado.Dia = (byte)Time.Day; //Armazena na variável resultado.Dia o dia atual
	resultado.Mes = (byte)Time.Month; //Armazena na variável resultado.Mes o mes atual
	resultado.Ano = (word)Time.Year; //Armazena na variável resultado.Ano o ano atual

	Write_Buffer_FLASH[0]  = parametro; //Armazena o parâmetro no vetor de gravação da memória FLASH
	Write_Buffer_FLASH[1]  = valor_velho; //Armazena o valor_velho no vetor de gravação da memória FLASH
	Write_Buffer_FLASH[2]  = valor_novo; //Armazena o valor_novo no vetor de gravação da memória FLASH
	Write_Buffer_FLASH[3]  = operador; //Armazena o operador no vetor de gravação da memória FLASH
	Write_Buffer_FLASH[4]  = dispositivo; //Armazena o dispositivo no vetor de gravação da memória FLASH
	Write_Buffer_FLASH[5]  = resultado.Hora; //Armazena a hora no vetor de gravação da memória FLASH
	Write_Buffer_FLASH[6]  = resultado.Minuto; //Armazena o minuto no vetor de gravação da memória FLASH
	Write_Buffer_FLASH[7]  = resultado.Dia; //Armazena o dia no vetor de gravação da memória FLASH
	Write_Buffer_FLASH[8]  = resultado.Mes; //Armazena o mês no vetor de gravação da memória FLASH
	Write_Buffer_FLASH[9]  = (byte)(resultado.Ano >> 8); //Armazena o byte alto ano no vetor de gravação da memória FLASH
	Write_Buffer_FLASH[10] = (byte)(resultado.Ano); //Armazena o byte baixo ano no vetor de gravação da memória FLASH

	if(posicao_byte_a == 4092){
		posicao_byte_a = 0; //Primeira posição dentro dos 4092 bytes disponíveis dentro de 1 bloco de memória
		if(posicao_bloco_a < 43){
			posicao_bloco_a++; //Caso a posição_byte_a seja a última e o bloco seja menor que 49 então
		} else if ((posicao_bloco_a >= 43)){
			posicao_bloco_a = 0; //Foi colocado 6 porque 6 * 0x1000 = 0x6000 mais o endereço inicial de definição que é 0x43000 vai dar em 0x49000 que é o inicio do bloco de memória para log de auditorias
		}
	}



	//O primeiro bloco é de 0x49000 a 0x49FFF, o segunda bloco de 0x50000 a 0x50FFF e assim por diante de 0x49000 até 0x74FFF
	endereco = END_INI_LOG_AUDITORIAS + posicao_byte_a + (posicao_bloco_a * 0x1000); //endereco é igual a 0x49000 mais pedaco que é a próxima posição dentro do bloco mais número do bloco vezes 4096 para se posicionar
	fnEscreveNoEndereco(endereco,11); //Escreve no endereço especificado os 11 bytes do log a ser armazenado

	endereco_flag = END_INI_FLAG_AUDITORIA + (posicao_byte_a/11) + (posicao_bloco_a * 372);
	Write_Buffer_FLASH[0] = 1; //Escreve 1 para informar que o registro nunca foi lido pelo servidor, seria a primeira vez que esta sendo gravado o novo registro
	fnEscreveNoEndereco(endereco_flag,1); //Escreve 1 na flag de auditorias correspondente
	posicao_byte_a = posicao_byte_a + 11; //Incrementa 11 bytes para se posicionar na próxima posição dentro do bloco

	Write_Buffer_FLASH[0] = posicao_bloco_a; //Escreve no vetor Write_Buffer_FLASH a posição_bloco_a para caso desligue o equipamento o mesmo retorne a gravar a partir do bloco de memória correto
	Write_Buffer_FLASH[1] = (byte)(posicao_byte_a >> 8); //Escreve no vetor Write_Buffer_FLASH a posição_byte_a (byte alto) para caso desligue o equipamento o mesmo retorne a gravar a partir da posição correta dentro do bloco de memória especificado
	Write_Buffer_FLASH[2] = (byte)(posicao_byte_a); //Escreve no vetor Write_Buffer_FLASH a posição_byte_a (byte baixo) para caso desligue o equipamento o mesmo retorne a gravar a partir da posição correta dentro do bloco de memória especificado
	ESCREVE_FLASH_INTERNA(endFLASHPonteiroBlocoA,3,0); //Armazena as variáveis posicao_bloco_a e posicao_byte_a no endereço de armazenamento reservado na memória FLASH

	fnRotinaBackupMemoriaConfiguracaoValida('A');

	return;





	//Foi feito da forma abaixo porque 1 bloco completa 4092 bytes e não 4096 bytes
	//((((endereco - 0x49000) / 4096) * 372) --> Esta parte pega o endereco acima e separa numa parte do valor cheio de registros dos blocos completos para saber o total de registos no número de blocos correspondentes
	//((endereco  - ((((endereco - 0x49000) / 4096) * 0x1000) + 0x49000)) / 11)) --> Esta parte pega o endereco acima e separa numa parte menor que não é o interio e divide por 11 para saber o número de registros restantes
	endereco = ((((endereco - END_INI_LOG_AUDITORIAS) / 4096) * 372) + ((endereco  - ((((endereco - END_INI_LOG_AUDITORIAS) / 4096) * 0x1000) + END_INI_LOG_AUDITORIAS)) / 11)) + END_INI_FLAG_AUDITORIA; //Soma a quantidade de registros de blocos inteiros mas a quantidade de registros restantes e soma com 0x75000 para se posicionar na flag de eventos correta
	Write_Buffer_FLASH[0] = 1; //Escreve 1 para informar que o registro nunca foi lido pelo servidor, seria a primeira vez que esta sendo gravado o novo registro
	n_bloco_a = ((endereco - END_INI_FLAG_AUDITORIA) / 0x1000) + 50; //Soma 50 para dar no inicio do bloco das flags de auditorias que é 0x75000
	ESCREVE_FLASH_INTERNA(endereco,1,n_bloco_a); //Escreve 1 na flag de auditorias correspondente

	posicao_byte_a = posicao_byte_a + 11; //Incrementa 11 bytes para se posicionar na próxima posição dentro do bloco
	Write_Buffer_FLASH[0] = posicao_bloco_a; //Escreve no vetor Write_Buffer_FLASH a posição_bloco_a para caso desligue o equipamento o mesmo retorne a gravar a partir do bloco de memória correto
	Write_Buffer_FLASH[1] = (byte)(posicao_byte_a >> 8); //Escreve no vetor Write_Buffer_FLASH a posição_byte_a (byte alto) para caso desligue o equipamento o mesmo retorne a gravar a partir da posição correta dentro do bloco de memória especificado
	Write_Buffer_FLASH[2] = (byte)(posicao_byte_a); //Escreve no vetor Write_Buffer_FLASH a posição_byte_a (byte baixo) para caso desligue o equipamento o mesmo retorne a gravar a partir da posição correta dentro do bloco de memória especificado
	ESCREVE_FLASH_INTERNA(endFLASHPonteiroBlocoA,3,0); //Armazena as variáveis posicao_bloco_a e posicao_byte_a no endereço de armazenamento reservado na memória FLASH
	if(posicao_byte_a == 4092 && posicao_bloco_a < 49)
	{
		posicao_byte_a = 0; //Primeira posição dentro dos 4092 bytes disponíveis dentro de 1 bloco de memória
		posicao_bloco_a++; //Caso a posição_byte_a seja a última e o bloco seja menor que 49 então

		//O primeiro bloco é de 0x49000 a 0x49FFF, o segunda bloco de 0x50000 a 0x50FFF e assim por diante de 0x49000 até 0x74FFF
		endereco = END_INI_PARAMETROS + posicao_byte_a + (posicao_bloco_a * 4096); //endereco é igual a 0x43000 mais pedaco que é a próxima posição dentro do bloco mais número do bloco vezes 4096 para se posicionar
		ESCREVE_FLASH_INTERNA(endereco,11,posicao_bloco_a); //Escreve no endereço especificado os 11 bytes do log a ser armazenado

		//Foi feito da forma abaixo porque 1 bloco completa 4092 bytes e não 4096 bytes
		//((((endereco - 0x49000) / 4096) * 372) --> Esta parte pega o endereco acima e separa numa parte do valor cheio de registros dos blocos completos para saber o total de registos no número de blocos correspondentes
		//((endereco  - ((((endereco - 0x49000) / 4096) * 0x1000) + 0x49000)) / 11)) --> Esta parte pega o endereco acima e separa numa parte menor que não é o interio e divide por 11 para saber o número de registros restantes
		endereco = ((((endereco - END_INI_LOG_AUDITORIAS) / 4096) * 372) + ((endereco  - ((((endereco - END_INI_LOG_AUDITORIAS) / 4096) * 0x1000) + END_INI_LOG_AUDITORIAS)) / 11)) + END_INI_FLAG_AUDITORIA; //Soma a quantidade de registros de blocos inteiros mas a quantidade de registros restantes e soma com 0x75000 para se posicionar na flag de eventos correta
		Write_Buffer_FLASH[0] = 1; //Escreve 1 para informar que o registro nunca foi lido pelo servidor, seria a primeira vez que esta sendo gravado o novo registro
		n_bloco_a = ((endereco - END_INI_FLAG_AUDITORIA) / 0x1000) + 50; //Soma 50 para dar no inicio do bloco das flags de auditorias que é 0x75000
		ESCREVE_FLASH_INTERNA(endereco,1,n_bloco_a); //Escreve 1 na flag de auditorias correspondente

		posicao_byte_a = posicao_byte_a + 11; //Incrementa 11 bytes para se posicionar na próxima posição dentro do bloco
		Write_Buffer_FLASH[0] = posicao_bloco_a; //Escreve no vetor Write_Buffer_FLASH a posição_bloco_a para caso desligue o equipamento o mesmo retorne a gravar a partir do bloco de memória correto
		Write_Buffer_FLASH[1] = (byte)(posicao_byte_a >> 8); //Escreve no vetor Write_Buffer_FLASH a posição_byte_a (byte alto) para caso desligue o equipamento o mesmo retorne a gravar a partir da posição correta dentro do bloco de memória especificado
		Write_Buffer_FLASH[2] = (byte)(posicao_byte_a); //Escreve no vetor Write_Buffer_FLASH a posição_byte_a (byte baixo) para caso desligue o equipamento o mesmo retorne a gravar a partir da posição correta dentro do bloco de memória especificado
		ESCREVE_FLASH_INTERNA(endFLASHPonteiroBlocoA,3,0); //Armazena as variáveis posicao_bloco_a e posicao_byte_a no endereço de armazenamento reservado na memória FLASH
	}
	else if(posicao_byte_a == 4092 && posicao_bloco_a == 49) //Vai até 49 porque 49 * 0x1000 = 0x31000 mais o endereço inicial de definição que é 0x43000 vai dar em 0x74000 que é o último bloco de dados da memória para log de auditorias
	{
		posicao_byte_a = 0; //Primeira posição dentro dos 4092 bytes disponíveis dentro de 1 bloco de memória
		posicao_bloco_a = 6; //Foi colocado 6 porque 6 * 0x1000 = 0x6000 mais o endereço inicial de definição que é 0x43000 vai dar em 0x49000 que é o inicio do bloco de memória para log de auditorias

		//O primeiro bloco é de 0x49000 a 0x49FFF, o segunda bloco de 0x50000 a 0x50FFF e assim por diante de 0x49000 até 0x74FFF
		endereco = END_INI_PARAMETROS + posicao_byte_a + (posicao_bloco_a * 4096); //endereco é igual a 0x43000 mais pedaco que é a próxima posição dentro do bloco mais número do bloco vezes 4096 para se posicionar
		ESCREVE_FLASH_INTERNA(endereco,11,posicao_bloco_a); //Escreve no endereço especificado os 11 bytes do log a ser armazenado

		//Foi feito da forma abaixo porque 1 bloco completa 4092 bytes e não 4096 bytes
		//((((endereco - 0x49000) / 4096) * 372) --> Esta parte pega o endereco acima e separa numa parte do valor cheio de registros dos blocos completos para saber o total de registos no número de blocos correspondentes
		//((endereco  - ((((endereco - 0x49000) / 4096) * 0x1000) + 0x49000)) / 11)) --> Esta parte pega o endereco acima e separa numa parte menor que não é o interio e divide por 11 para saber o número de registros restantes
		endereco = ((((endereco - END_INI_LOG_AUDITORIAS) / 4096) * 372) + ((endereco  - ((((endereco - END_INI_LOG_AUDITORIAS) / 4096) * 0x1000) + END_INI_LOG_AUDITORIAS)) / 11)) + END_INI_FLAG_AUDITORIA; //Soma a quantidade de registros de blocos inteiros mas a quantidade de registros restantes e soma com 0x75000 para se posicionar na flag de eventos correta
		Write_Buffer_FLASH[0] = 1; //Escreve 1 para informar que o registro nunca foi lido pelo servidor, seria a primeira vez que esta sendo gravado o novo registro
		n_bloco_a = ((endereco - END_INI_FLAG_AUDITORIA) / 0x1000) + 50; //Soma 50 para dar no inicio do bloco das flags de auditorias que é 0x75000
		ESCREVE_FLASH_INTERNA(endereco,1,n_bloco_a); //Escreve 1 na flag de auditorias correspondente

		posicao_byte_a = posicao_byte_a + 11; //Incrementa 11 bytes para se posicionar na próxima posição dentro do bloco
		Write_Buffer_FLASH[0] = posicao_bloco_a; //Escreve no vetor Write_Buffer_FLASH a posição_bloco_a para caso desligue o equipamento o mesmo retorne a gravar a partir do bloco de memória correto
		Write_Buffer_FLASH[1] = (byte)(posicao_byte_a >> 8); //Escreve no vetor Write_Buffer_FLASH a posição_byte_a (byte alto) para caso desligue o equipamento o mesmo retorne a gravar a partir da posição correta dentro do bloco de memória especificado
		Write_Buffer_FLASH[2] = (byte)(posicao_byte_a); //Escreve no vetor Write_Buffer_FLASH a posição_byte_a (byte baixo) para caso desligue o equipamento o mesmo retorne a gravar a partir da posição correta dentro do bloco de memória especificado
		ESCREVE_FLASH_INTERNA(endFLASHPonteiroBlocoA,3,0); //Armazena as variáveis posicao_bloco_a e posicao_byte_a no endereço de armazenamento reservado na memória FLASH
	}
	else if((posicao_byte_a > 0 && posicao_byte_a < 4092) && posicao_bloco_a <= 49)
	{
		//O primeiro bloco é de 0x49000 a 0x49FFF, o segunda bloco de 0x50000 a 0x50FFF e assim por diante de 0x49000 até 0x74FFF
		endereco = END_INI_PARAMETROS + posicao_byte_a + (posicao_bloco_a * 4096); //endereco é igual a 0x43000 mais pedaco que é a próxima posição dentro do bloco mais número do bloco vezes 4096 para se posicionar
		ESCREVE_FLASH_INTERNA(endereco,11,posicao_bloco_a); //Escreve no endereço especificado os 11 bytes do log a ser armazenado

		//Foi feito da forma abaixo porque 1 bloco completa 4092 bytes e não 4096 bytes
		//((((endereco - 0x49000) / 4096) * 372) --> Esta parte pega o endereco acima e separa numa parte do valor cheio de registros dos blocos completos para saber o total de registos no número de blocos correspondentes
		//((endereco  - ((((endereco - 0x49000) / 4096) * 0x1000) + 0x49000)) / 11)) --> Esta parte pega o endereco acima e separa numa parte menor que não é o interio e divide por 11 para saber o número de registros restantes
		endereco = ((((endereco - END_INI_LOG_AUDITORIAS) / 4096) * 372) + ((endereco  - ((((endereco - END_INI_LOG_AUDITORIAS) / 4096) * 0x1000) + END_INI_LOG_AUDITORIAS)) / 11)) + END_INI_FLAG_AUDITORIA; //Soma a quantidade de registros de blocos inteiros mas a quantidade de registros restantes e soma com 0x75000 para se posicionar na flag de eventos correta
		Write_Buffer_FLASH[0] = 1; //Escreve 1 para informar que o registro nunca foi lido pelo servidor, seria a primeira vez que esta sendo gravado o novo registro
		n_bloco_a = ((endereco - END_INI_FLAG_AUDITORIA) / 0x1000) + 50; //Soma 50 para dar no inicio do bloco das flags de auditorias que é 0x75000
		ESCREVE_FLASH_INTERNA(endereco,1,n_bloco_a); //Escreve 1 na flag de auditorias correspondente

		posicao_byte_a = posicao_byte_a + 11; //Incrementa 11 bytes para se posicionar na próxima posição dentro do bloco
		Write_Buffer_FLASH[0] = posicao_bloco_a; //Escreve no vetor Write_Buffer_FLASH a posição_bloco_a para caso desligue o equipamento o mesmo retorne a gravar a partir do bloco de memória correto
		Write_Buffer_FLASH[1] = (byte)(posicao_byte_a >> 8); //Escreve no vetor Write_Buffer_FLASH a posição_byte_a (byte alto) para caso desligue o equipamento o mesmo retorne a gravar a partir da posição correta dentro do bloco de memória especificado
		Write_Buffer_FLASH[2] = (byte)(posicao_byte_a); //Escreve no vetor Write_Buffer_FLASH a posição_byte_a (byte baixo) para caso desligue o equipamento o mesmo retorne a gravar a partir da posição correta dentro do bloco de memória especificado
		ESCREVE_FLASH_INTERNA(endFLASHPonteiroBlocoA,3,0); //Armazena as variáveis posicao_bloco_a e posicao_byte_a no endereço de armazenamento reservado na memória FLASH
	}
	else if(posicao_byte_a == 0 && posicao_bloco_a <= 49)
	{
		//O primeiro bloco é de 0x49000 a 0x49FFF, o segunda bloco de 0x50000 a 0x50FFF e assim por diante de 0x49000 até 0x74FFF
		endereco = END_INI_PARAMETROS + posicao_byte_a + (posicao_bloco_a * 4096); //endereco é igual a 0x43000 mais pedaco que é a próxima posição dentro do bloco mais número do bloco vezes 4096 para se posicionar
		ESCREVE_FLASH_INTERNA(endereco,11,posicao_bloco_a); //Escreve no endereço especificado os 11 bytes do log a ser armazenado

		//Foi feito da forma abaixo porque 1 bloco completa 4092 bytes e não 4096 bytes
		//((((endereco - 0x49000) / 4096) * 372) --> Esta parte pega o endereco acima e separa numa parte do valor cheio de registros dos blocos completos para saber o total de registos no número de blocos correspondentes
		//((endereco  - ((((endereco - 0x49000) / 4096) * 0x1000) + 0x49000)) / 11)) --> Esta parte pega o endereco acima e separa numa parte menor que não é o interio e divide por 11 para saber o número de registros restantes
		endereco = ((((endereco - END_INI_LOG_AUDITORIAS) / 4096) * 372) + ((endereco  - ((((endereco - END_INI_LOG_AUDITORIAS) / 4096) * 0x1000) + END_INI_LOG_AUDITORIAS)) / 11)) + END_INI_FLAG_AUDITORIA; //Soma a quantidade de registros de blocos inteiros mas a quantidade de registros restantes e soma com 0x75000 para se posicionar na flag de eventos correta
		Write_Buffer_FLASH[0] = 1; //Escreve 1 para informar que o registro nunca foi lido pelo servidor, seria a primeira vez que esta sendo gravado o novo registro
		n_bloco_a = ((endereco - END_INI_FLAG_AUDITORIA) / 0x1000) + 50; //Soma 50 para dar no inicio do bloco das flags de auditorias que é 0x75000
		ESCREVE_FLASH_INTERNA(endereco,1,n_bloco_a); //Escreve 1 na flag de auditorias correspondente

		posicao_byte_a = posicao_byte_a + 11; //Incrementa 11 bytes para se posicionar na próxima posição dentro do bloco
		Write_Buffer_FLASH[0] = posicao_bloco_a; //Escreve no vetor Write_Buffer_FLASH a posição_bloco_a para caso desligue o equipamento o mesmo retorne a gravar a partir do bloco de memória correto
		Write_Buffer_FLASH[1] = (byte)(posicao_byte_a >> 8); //Escreve no vetor Write_Buffer_FLASH a posição_byte_a (byte alto) para caso desligue o equipamento o mesmo retorne a gravar a partir da posição correta dentro do bloco de memória especificado
		Write_Buffer_FLASH[2] = (byte)(posicao_byte_a); //Escreve no vetor Write_Buffer_FLASH a posição_byte_a (byte baixo) para caso desligue o equipamento o mesmo retorne a gravar a partir da posição correta dentro do bloco de memória especificado
		ESCREVE_FLASH_INTERNA(endFLASHPonteiroBlocoA,3,0); //Armazena as variáveis posicao_bloco_a e posicao_byte_a no endereço de armazenamento reservado na memória FLASH
	}
}

void fnGravaEvento(char evento,char dispositivo) //Função que grava os eventos de bloqueios e desbloqueios realizados por painel, controle remoto ou detecção de metais
{
	volatile dword endereco = 0; //Zera a variável endereco

	DataHora resultado; //Transforma resultado na estrutura DataHora
	RTC1_GetTime(MyRTCPtr,&Time); //Pega a hora e a data atual do sistema

	resultado.Hora = (byte)Time.Hour; //Armazena na variável resultado.Hora o hora atual
	resultado.Minuto = (byte)Time.Minute; //Armazena na variável resultado.Minuto o minuto atual
	resultado.Dia = (byte)Time.Day; //Armazena na variável resultado.Dia o dia atual
	resultado.Mes = (byte)Time.Month; //Armazena na variável resultado.Mes o mes atual
	resultado.Ano = (word)Time.Year; //Armazena na variável resultado.Ano o ano atual

	Write_Buffer_FLASH[0] = evento; //Armazena o evento no vetor de gravação da memória FLASH
	Write_Buffer_FLASH[1] = dispositivo; //Armazena o dispositivo no vetor de gravação da memória FLASH
	Write_Buffer_FLASH[2] = resultado.Hora; //Armazena a hora no vetor de gravação da memória FLASH
	Write_Buffer_FLASH[3] = resultado.Minuto; //Armazena o minuto no vetor de gravação da memória FLASH
	Write_Buffer_FLASH[4] = resultado.Dia; //Armazena o dia no vetor de gravação da memória FLASH
	Write_Buffer_FLASH[5] = resultado.Mes; //Armazena o mês no vetor de gravação da memória FLASH
	Write_Buffer_FLASH[6] = (byte)(resultado.Ano >> 8); //Armazena o byte alto ano no vetor de gravação da memória FLASH
	Write_Buffer_FLASH[7] = (byte)(resultado.Ano); //Armazena o byte baixo ano no vetor de gravação da memória FLASH

	if(posicao_byte_l == 4096 && posicao_bloco_l < 4) //Se posicao_byte_l for igual a 4096 significa que ta no fim do bloco e se posicao_bloco_l for menor que 4 então se posiciona no próximo bloco
	{
		posicao_byte_l = 0; //Inicializa posicao_byte_l
		posicao_bloco_l++; //Incrementa posicao_bloco_l

		//O primeiro bloco é de 0x44000 a 0x44FFF, o segunda bloco de 0x45000 a 0x45FFF e assim por diante
		endereco = END_INI_PARAMETROS + posicao_byte_l + (posicao_bloco_l * 4096); //endereco é igual a 0x43000 mais pedaco que é a próxima posição dentro do bloco mais número do bloco vezes 4096 para se posicionar
		ESCREVE_FLASH_INTERNA(endereco,8,posicao_bloco_l); //Escreve no endereço especificado os 8 bytes do log a ser armazenado

		endereco = END_INI_FLAG_EVENTOS + ((endereco - 0x44000) / 8); //Acerta o endereço específico da flag de eventos para escrever 1 que significa nunca foi lido
		Write_Buffer_FLASH[0] = 1; //Escreve 1 na posição específica da flag para informar que o registro nunca foi lido desta posição de memória
		ESCREVE_FLASH_INTERNA(endereco,1,5); //Escreve no endereço específico da flag de eventos

		posicao_byte_l = posicao_byte_l + 8; //Incrementa 8 pois tem que se posicionar nos próximos 8 bytes dentro do bloco pois o registro de eventos tem 8 bytes de tamanho
		Write_Buffer_FLASH[0] = posicao_bloco_l; //Escreve no vetor Write_Buffer_FLASH na posição 0 posicao_bloco_l
		Write_Buffer_FLASH[1] = (byte)(posicao_byte_l >> 8); //Escreve no vetor Write_Buffer_FLASH na posição 1 posicao_byte_l o byte alto desta variável
		Write_Buffer_FLASH[2] = (byte)(posicao_byte_l); //Escreve no vetor Write_Buffer_FLASH na posição 2 posicao_byte_l o byte byte desta variável
		ESCREVE_FLASH_INTERNA(endFLASHPonteiroBlocoL,3,0); //Armazena na FLASH os ponteiros de posição de bloco e de posição de byte dentro do bloco para ao desligar e ligar o equipmento não perder as próximas posições
	}
	else if(posicao_byte_l == 4096 && posicao_bloco_l == 4)
	{
		posicao_byte_l = 0;
		posicao_bloco_l = 1;

		//O primeiro bloco é de 0x44000 a 0x44FFF, o segunda bloco de 0x45000 a 0x45FFF e assim por diante
		endereco = END_INI_PARAMETROS + posicao_byte_l + (posicao_bloco_l * 4096); //endereco é igual a 0x43000 mais pedaco que é a próxima posição dentro do bloco mais número do bloco vezes 4096 para se posicionar
		ESCREVE_FLASH_INTERNA(endereco,8,posicao_bloco_l); //Escreve no endereço especificado os 8 bytes do log a ser armazenado

		endereco = END_INI_FLAG_EVENTOS + ((endereco - 0x44000) / 8); //Acerta o endereço específico da flag de eventos para escrever 1 que significa nunca foi lido
		Write_Buffer_FLASH[0] = 1; //Escreve 1 na posição específica da flag para informar que o registro nunca foi lido desta posição de memória
		ESCREVE_FLASH_INTERNA(endereco,1,5); //Escreve no endereço específico da flag de eventos

		posicao_byte_l = posicao_byte_l + 8; //Incrementa 8 pois tem que se posicionar nos próximos 8 bytes dentro do bloco pois o registro de eventos tem 8 bytes de tamanho
		Write_Buffer_FLASH[0] = posicao_bloco_l; //Escreve no vetor Write_Buffer_FLASH na posição 0 posicao_bloco_l
		Write_Buffer_FLASH[1] = (byte)(posicao_byte_l >> 8); //Escreve no vetor Write_Buffer_FLASH na posição 1 posicao_byte_l o byte alto desta variável
		Write_Buffer_FLASH[2] = (byte)(posicao_byte_l); //Escreve no vetor Write_Buffer_FLASH na posição 2 posicao_byte_l o byte byte desta variável
		ESCREVE_FLASH_INTERNA(endFLASHPonteiroBlocoL,3,0); //Armazena na FLASH os ponteiros de posição de bloco e de posição de byte dentro do bloco para ao desligar e ligar o equipmento não perder as próximas posições
	}
	else if((posicao_byte_l > 0 && posicao_byte_l < 4096) && posicao_bloco_l <= 4)
	{
		//O primeiro bloco é de 0x44000 a 0x44FFF, o segunda bloco de 0x45000 a 0x45FFF e assim por diante
		endereco = END_INI_PARAMETROS + posicao_byte_l + (posicao_bloco_l * 4096); //endereco é igual a 0x43000 mais pedaco que é a próxima posição dentro do bloco mais número do bloco vezes 4096 para se posicionar
		ESCREVE_FLASH_INTERNA(endereco,8,posicao_bloco_l); //Escreve no endereço especificado os 8 bytes do log a ser armazenado

		endereco = END_INI_FLAG_EVENTOS + ((endereco - 0x44000) / 8); //Acerta o endereço específico da flag de eventos para escrever 1 que significa nunca foi lido
		Write_Buffer_FLASH[0] = 1; //Escreve 1 na posição específica da flag para informar que o registro nunca foi lido desta posição de memória
		ESCREVE_FLASH_INTERNA(endereco,1,5); //Escreve no endereço específico da flag de eventos

		posicao_byte_l = posicao_byte_l + 8; //Incrementa 8 pois tem que se posicionar nos próximos 8 bytes dentro do bloco pois o registro de eventos tem 8 bytes de tamanho
		Write_Buffer_FLASH[0] = posicao_bloco_l; //Escreve no vetor Write_Buffer_FLASH na posição 0 posicao_bloco_l
		Write_Buffer_FLASH[1] = (byte)(posicao_byte_l >> 8); //Escreve no vetor Write_Buffer_FLASH na posição 1 posicao_byte_l o byte alto desta variável
		Write_Buffer_FLASH[2] = (byte)(posicao_byte_l); //Escreve no vetor Write_Buffer_FLASH na posição 2 posicao_byte_l o byte byte desta variável
		ESCREVE_FLASH_INTERNA(endFLASHPonteiroBlocoL,3,0); //Armazena na FLASH os ponteiros de posição de bloco e de posição de byte dentro do bloco para ao desligar e ligar o equipmento não perder as próximas posições
	}
	else if(posicao_byte_l == 0 && posicao_bloco_l <= 4)
	{
		//O primeiro bloco é de 0x44000 a 0x44FFF, o segunda bloco de 0x45000 a 0x45FFF e assim por diante
		endereco = END_INI_PARAMETROS + posicao_byte_l + (posicao_bloco_l * 4096); //endereco é igual a 0x43000 mais pedaco que é a próxima posição dentro do bloco mais número do bloco vezes 4096 para se posicionar
		ESCREVE_FLASH_INTERNA(endereco,8,posicao_bloco_l); //Escreve no endereço especificado os 8 bytes do log a ser armazenado

		endereco = END_INI_FLAG_EVENTOS + ((endereco - 0x44000) / 8); //Acerta o endereço específico da flag de eventos para escrever 1 que significa nunca foi lido
		Write_Buffer_FLASH[0] = 1; //Escreve 1 na posição específica da flag para informar que o registro nunca foi lido desta posição de memória
		ESCREVE_FLASH_INTERNA(endereco,1,5); //Escreve no endereço específico da flag de eventos

		posicao_byte_l = posicao_byte_l + 8; //Incrementa 8 pois tem que se posicionar nos próximos 8 bytes dentro do bloco pois o registro de eventos tem 8 bytes de tamanho
		Write_Buffer_FLASH[0] = posicao_bloco_l; //Escreve no vetor Write_Buffer_FLASH na posição 0 posicao_bloco_l
		Write_Buffer_FLASH[1] = (byte)(posicao_byte_l >> 8); //Escreve no vetor Write_Buffer_FLASH na posição 1 posicao_byte_l o byte alto desta variável
		Write_Buffer_FLASH[2] = (byte)(posicao_byte_l); //Escreve no vetor Write_Buffer_FLASH na posição 2 posicao_byte_l o byte byte desta variável
		ESCREVE_FLASH_INTERNA(endFLASHPonteiroBlocoL,3,0); //Armazena na FLASH os ponteiros de posição de bloco e de posição de byte dentro do bloco para ao desligar e ligar o equipmento não perder as próximas posições
	}
}

void GravaPadroesFabrica(void) //Função que grava os parâmetros padrões de fábrica
{
	volatile dword endereco = 0;

	memset(buffer_senhas,0,sizeof(buffer_senhas));

	//SENHA DA GERÊNCIA
	strncat((char *)buffer_senhas,SENHA_GERENCIA, 6);
	for(x = 0;x < 6;x++) //Armazena o valor das 6 posições do buffer_senhas no vetor de gravação da memória FLASH para a senha da gerência
	{
		Write_Buffer_FLASH[OFFSET_SENHA_DA_GERENCIA + x] = buffer_senhas[x];
	}

	//SENHA DO TÉCNICO
	strncat((char *)buffer_senhas,SENHA_TECNICO, 6);
	for(x = 0;x < 6;x++) //Armazena o valor das 6 posições do buffer_senhas no vetor de gravação da memória FLASH para a senha do técnico
	{
		Write_Buffer_FLASH[OFFSET_SENHA_DO_TECNICO + x] = buffer_senhas[x + 6];
	}

	//SENHA DA ENGENHARIA
	buffer_senhas[12]= var_senha_mestre[0]; //Armazena no vetor buffer_senhas na posição 12 o conteúdo de var_senha_mestre[0]
	buffer_senhas[13]= var_senha_mestre[1]; //Armazena no vetor buffer_senhas na posição 13 o conteúdo de var_senha_mestre[1]
	buffer_senhas[14]= var_senha_mestre[2]; //Armazena no vetor buffer_senhas na posição 14 o conteúdo de var_senha_mestre[2]
	buffer_senhas[15]= var_senha_mestre[3]; //Armazena no vetor buffer_senhas na posição 15 o conteúdo de var_senha_mestre[3]
	buffer_senhas[16]= var_senha_mestre[4]; //Armazena no vetor buffer_senhas na posição 16 o conteúdo de var_senha_mestre[4]
	buffer_senhas[17]= var_senha_mestre[5]; //Armazena no vetor buffer_senhas na posição 17 o conteúdo de var_senha_mestre[5]
	for(x = 0;x < 6;x++) //Armazena o valor das 6 posições do buffer_senhas no vetor de gravação da memória FLASH para a senha da engenharia
	{
		Write_Buffer_FLASH[OFFSET_SENHA_DA_ENGENHARIA + x] = buffer_senhas[x + 12];
	}

	//SENSIBILIDADE
	for(x = 0;x < 9;x++) //Armazena nas 8 posições do buffer_sensibilidade o valor de sensibilidade 50
	{
		buffer_sensibilidade[x] = 50;
	}
	for(x = 0;x < 8;x++) //Armazena o valor das 8 posições do buffer_sensibilidade no vetor de gravação da memória FLASH para as sensibilidades das áreas
	{
		Write_Buffer_FLASH[OFFSET_SENSIBILIDADE + x] = buffer_sensibilidade[x + 1];
	}

	//MODO DE TRAVAMENTO
	modo_travamento = TRAVA_DESTRAVA; //Armazena na variável modo_travamento a informação TRAVA_DESTRAVA que permite a porta travar e destravar pelo controle ou painel conforme configuração do sinal da trava
	Write_Buffer_FLASH[OFFSET_MODO_TRAVAMENTO] = modo_travamento; //Armazena o valor do modo_travamento no vetor de gravação da memória FLASH para o modo de travamento

	//CANAL
	canal = 1; //Armazena na variável canal 1 o valor 1
	Write_Buffer_FLASH[OFFSET_CANAL] = canal; //Armazena o valor do canal no vetor de gravação da memória FLASH para o canal

	//SELEÇÃO DE METAIS
	selecao_metais = 80; //Armazena na variável selecao_metais o valor 80
	Write_Buffer_FLASH[OFFSET_SELECAO_METAIS] = selecao_metais; //Armazena o valor de selecao_metais no vetor de gravação da memória FLASH para a seleção de metais

	//TRAVA
	pulso_trava = 10; //Armazena na variável pulso_trava o valor 10 que é 1000ms, ou seja, cada unidade vale 100ms, portanto o resultado na tela é 1.0s
	sinal_trava = trava_retencao_controle_teclado; //Armazena na variável sinal_trava a informação trava_retencao_controle_teclado
	Write_Buffer_FLASH[OFFSET_PULSO_TRAVA] = pulso_trava; //Armazena o valor de pulso_trava no vetor de gravação da memória FLASH para o pulso_trava
	Write_Buffer_FLASH[OFFSET_SINAL_TRAVA] = sinal_trava; //Armazena o valor do sinal_trava no vetor de gravação da memória FLASH para o sinal_trava

	//RELE
	pulso_rele = 1; //Armazena na variável pulso_rele o valor 1 que é 100ms, ou seja, cada unidade vale 100ms, portanto o resultado na tela é 0.1s
	sinal_rele = rele_retencao; //Armazena na variável sinal_rele a informação rele_retencao
	Write_Buffer_FLASH[OFFSET_PULSO_RELE] = pulso_rele; //Armazena o valor de pulso_rele no vetor de gravação da memória FLASH para o pulso_rele
	Write_Buffer_FLASH[OFFSET_SINAL_RELE] = sinal_rele; //Armazena o valor de sinal_rele no vetor de gravação da memória FLASH para o sinal_rele

	//NÚMERO DE CONTROLES
	numero_controles = 0; //Armazena na variável numero_controles o valor 0
	Write_Buffer_FLASH[OFFSET_NUMERO_CONTROLES] = numero_controles; //Armazena o numero no vetor de gravação da memória FLASH para a trava_inteligente

	//SENSIBILIDADE IR
	sensibilidadeir = 26; //Armazena na variável sensibilidadeir o valor 26 que é 10% de PWM
	Write_Buffer_FLASH[OFFSET_SENSIBILIDADEIR] = sensibilidadeir; //Armazena o valor de sensibilidadeir no vetor de gravação da memória FLASH para a sensibilidadeir
	PWM_INFRAS_SetRatio8(sensibilidadeir); //Seta o pwm dos infras de acordo com o valor da sensibilidadeir

	//ANÁLISE IR
	analiseir = NAO; //Armazena na variável analiseir a informação NAO
	Write_Buffer_FLASH[OFFSET_ANALISEIR] = analiseir; //Armazena o valor de analiseir no vetor de gravação da memória FLASH para a analiseir

	//FÁBRICA
	fabrica = SIM; //Armazena na variável fabrica a informação SIM
	Write_Buffer_FLASH[OFFSET_FABRICA] = fabrica; //Armazena o valor de fabrica no vetor de gravação da memória FLASH para a fabrica

	//IDIOMA
	idioma = COD_PORTUGUES; //Armazena na variável idioma a informação COD_PORTUGUES
	Write_Buffer_FLASH[OFFSET_IDIOMA] = idioma; //Armazena o valor de idioma no vetor de gravação da memória FLASH para o idioma

	//BUZZER
	buffer_buzzer[BUZZER_TOM] = 7; //Armazena na posição 0 do vetor buffer_buzzer o valor 1
	buffer_buzzer[BUZZER_VOLUME] = 1; //Armazena na posição 1 do vetor buffer_buzzer o valor 5
	buffer_buzzer[BUZZER_LIGA_DESLIGA] = 1; //Armazena na posição 2 do vetor buffer_buzzer o valor 1
	Write_Buffer_FLASH[OFFSET_BUZZER_TOM]	  = buffer_buzzer[BUZZER_TOM]; //Armazena o valor do tom no vetor de gravação da memória FLASH para o tom
	Write_Buffer_FLASH[OFFSET_BUZZER_VOLUME]  = buffer_buzzer[BUZZER_VOLUME]; //Armazena o valor do volume no vetor de gravação da memória FLASH para o volume
	Write_Buffer_FLASH[OFFSET_BUZZER_LIG_DES] = buffer_buzzer[BUZZER_LIGA_DESLIGA]; //Armazena o valor de ligado ou desligado no vetor de gravação da memória FLASH para o estado ligado ou desligado

	//MENSAGEM DE VOZ
	volume_mensagem_voz = 5; //Armazena na variável volume_mensagem_voz o valor 5
	lig_des_mensagem_voz = SIM; //Armazena na variável lig_des_mensagem_voz a informação SIM
	Write_Buffer_FLASH[OFFSET_MSG_VOZ_VOLUME] = volume_mensagem_voz; //Armazena o valor do volume da mensagem de voz no vetor de gravação da memória FLASH para o volume da mensagem de voz
	Write_Buffer_FLASH[OFFSET_MSG_VOZ_LIG_DES] = lig_des_mensagem_voz; //Armazena o valor de lig_des_mensagem_voz no vetor de gravação da memória FLASH para o lig_des_mensagem_voz

	//ALARME VISUAL
	alarme_visual = NAO; //Armazena na variável alarme_visual a informação SIM
	Write_Buffer_FLASH[OFFSET_ALARME_VISUAL_LIG_DES] = alarme_visual; //Armazena o valor do alarme_visual no vetor de gravação da memória FLASH para o alarme_visual

	//CONTADOR DE BLOQUEIOS
	contador_bloqueios = 0; //Armazena na variável contador_bloqueios o valor 0
	Write_Buffer_FLASH[OFFSET_TOTAL_BLOQUEIOS]     = (byte)(contador_bloqueios >> 24); //Escreve o valor do quarto byte mais alto no vetor para gravação na memória FLASH
	Write_Buffer_FLASH[OFFSET_TOTAL_BLOQUEIOS + 1] = (byte)(contador_bloqueios >> 16); //Escreve o valor do terceiro byte mais alto no vetor para gravação na memória FLASH
	Write_Buffer_FLASH[OFFSET_TOTAL_BLOQUEIOS + 2] = (byte)(contador_bloqueios >> 8); //Escreve o valor do segundo byte mais alto no vetor para gravação na memória FLASH
	Write_Buffer_FLASH[OFFSET_TOTAL_BLOQUEIOS + 3] = (byte)(contador_bloqueios); //Escreve o valor do primeiro byte no vetor para gravação na memória FLASH

	//CONTADOR DE DESBLOQUEIOS
	contador_desbloqueios = 0; //Armazena na variável contador_desbloqueios o valor 0
	Write_Buffer_FLASH[OFFSET_TOTAL_DESBLOQUEIOS]   = (byte)(contador_desbloqueios >> 24); //Escreve o valor do quarto byte mais alto no vetor para gravação na memória FLASH
	Write_Buffer_FLASH[OFFSET_TOTAL_DESBLOQUEIOS + 1] = (byte)(contador_desbloqueios >> 16); //Escreve o valor do terceiro byte mais alto no vetor para gravação na memória FLASH
	Write_Buffer_FLASH[OFFSET_TOTAL_DESBLOQUEIOS + 2] = (byte)(contador_desbloqueios >> 8); //Escreve o valor do segundo byte mais alto no vetor para gravação na memória FLASH
	Write_Buffer_FLASH[OFFSET_TOTAL_DESBLOQUEIOS + 3] = (byte)(contador_desbloqueios); //Escreve o valor do primeiro byte no vetor para gravação na memória FLASH

	//CONTADOR DE PASSAGENS - ENTRADAS
	contador_entra = 0; //Armazena na variável contador_entra o valor 0
	Write_Buffer_FLASH[OFFSET_CONTADOR_ENTRADAS]   = (byte)(contador_entra >> 24); //Escreve o valor do quarto byte mais alto no vetor para gravação na memória FLASH
	Write_Buffer_FLASH[OFFSET_CONTADOR_ENTRADAS + 1] = (byte)(contador_entra >> 16); //Escreve o valor do terceiro byte mais alto no vetor para gravação na memória FLASH
	Write_Buffer_FLASH[OFFSET_CONTADOR_ENTRADAS + 2] = (byte)(contador_entra >> 8); //Escreve o valor do segundo byte mais alto no vetor para gravação na memória FLASH
	Write_Buffer_FLASH[OFFSET_CONTADOR_ENTRADAS + 3] = (byte)(contador_entra); //Escreve o valor do primeiro byte no vetor para gravação na memória FLASH

	//CONTADOR DE PASSAGENS - SAIDAS
	contador_sai = 0; //Armazena na variável contador_sai o valor 0
	Write_Buffer_FLASH[OFFSET_CONTADOR_SAIDAS] 	= (byte)(contador_sai >> 24); //Escreve o valor do quarto byte mais alto no vetor para gravação na memória FLASH
	Write_Buffer_FLASH[OFFSET_CONTADOR_SAIDAS + 1] = (byte)(contador_sai >> 16); //Escreve o valor do terceiro byte mais alto no vetor para gravação na memória FLASH
	Write_Buffer_FLASH[OFFSET_CONTADOR_SAIDAS + 2] = (byte)(contador_sai >> 8); //Escreve o valor do segundo byte mais alto no vetor para gravação na memória FLASH
	Write_Buffer_FLASH[OFFSET_CONTADOR_SAIDAS + 3] = (byte)(contador_sai); //Escreve o valor do primeiro byte no vetor para gravação na memória FLASH

	//CONTADOR DE PASSAGENS - ENTRADAS DIARIAS
	contador_dia_entra = 0; //Armazena na variável contador_entra o valor 0
	Write_Buffer_FLASH[OFFSET_CONTADOR_ENTRADAS_D]   = (byte)(contador_dia_entra >> 24); //Escreve o valor do quarto byte mais alto no vetor para gravação na memória FLASH
	Write_Buffer_FLASH[OFFSET_CONTADOR_ENTRADAS_D + 1] = (byte)(contador_dia_entra >> 16); //Escreve o valor do terceiro byte mais alto no vetor para gravação na memória FLASH
	Write_Buffer_FLASH[OFFSET_CONTADOR_ENTRADAS_D + 2] = (byte)(contador_dia_entra >> 8); //Escreve o valor do segundo byte mais alto no vetor para gravação na memória FLASH
	Write_Buffer_FLASH[OFFSET_CONTADOR_ENTRADAS_D + 3] = (byte)(contador_dia_entra); //Escreve o valor do primeiro byte no vetor para gravação na memória FLASH

	//CONTADOR DE PASSAGENS - SAIDAS DIARIAS
	contador_dia_sai = 0; //Armazena na variável contador_sai o valor 0
	Write_Buffer_FLASH[OFFSET_CONTADOR_SAIDAS_D] 	= (byte)(contador_dia_sai >> 24); //Escreve o valor do quarto byte mais alto no vetor para gravação na memória FLASH
	Write_Buffer_FLASH[OFFSET_CONTADOR_SAIDAS_D + 1] = (byte)(contador_dia_sai >> 16); //Escreve o valor do terceiro byte mais alto no vetor para gravação na memória FLASH
	Write_Buffer_FLASH[OFFSET_CONTADOR_SAIDAS_D + 2] = (byte)(contador_dia_sai >> 8); //Escreve o valor do segundo byte mais alto no vetor para gravação na memória FLASH
	Write_Buffer_FLASH[OFFSET_CONTADOR_SAIDAS_D + 3] = (byte)(contador_dia_sai); //Escreve o valor do primeiro byte no vetor para gravação na memória FLASH

	//CONFERENCIA DO DIA
	conferencia_do_dia = Time.Day;
	Write_Buffer_FLASH[OFFSET_CONFERENCIA_DO_DIA] = conferencia_do_dia;

	//PERFIL
	perfil = PLANA_ONIX_2100; //Armazena na variável perfil a informação PLANA_ONIX_2000
	Write_Buffer_FLASH[OFFSET_PERFIL] = perfil; //Armazena o valor de perfil no vetor de gravação da memória FLASH para o perfil
	fnAtualizaPerfil(SETA_PARAMETRO_ON,SETA_PWM_ON,SETA_GRAVA_FLASH_OFF,SETA_POT_GANHO_ON); //Atualiza informações de sinal, defasagem, frequência e ganho conforme perfil escolhido

	//AJUSTES TX-RX
	Write_Buffer_FLASH[OFFSET_AJUSTES_TX_RX_CICLO_TRABALHO] = ciclo_de_trabalho; //Escreve o valor do ciclo de trabalho no vetor para gravação na memória FLASH
	Write_Buffer_FLASH[OFFSET_AJUSTES_TX_RX_DEFASAGEM] = (byte)(defasagem >> 8); //Escreve o byte alto da defasagem no vetor para gravação na memória FLASH
	Write_Buffer_FLASH[OFFSET_AJUSTES_TX_RX_DEFASAGEM + 1] = (byte)(defasagem); //Escreve o byte baixo da defasagem no vetor para gravação na memória FLASH
	Write_Buffer_FLASH[OFFSET_AJUSTES_TX_RX_FREQUENCIA] = (byte)(frequencia >> 8); //Escreve o byte alto da frequencia no vetor para gravação na memória FLASH
	Write_Buffer_FLASH[OFFSET_AJUSTES_TX_RX_FREQUENCIA + 1] = (byte)(frequencia); //Escreve o byte baixo da frequencia no vetor para gravação na memória FLASH

	//MODELO DE ANTENA
	modelo_antena = PLANA_ONIX_2100; //Armazena na variável modelo_antena a informação PLANA_ONIX_2000
	Write_Buffer_FLASH[OFFSET_MODELO_ANTENA] = modelo_antena; //Armazena o valor de modelo_antena no vetor de gravação da memória FLASH para o modelo_antena

	//POTENCIÔMETROS DE GANHO
	// Adendo: se não estiver setado - via canal - coloca o ganho como 20
	if(buffer_ganho[1] == 0 && buffer_ganho[2] == 0 && buffer_ganho[3] == 0 && buffer_ganho[4] == 0 &&
			buffer_ganho[5] == 0 && buffer_ganho[6] == 0 && buffer_ganho[7] == 0 && buffer_ganho[8] == 0)
	{
		for(x = 0;x < 9;x++) //Armazena nas 8 posições do buffer_ganho o valor 22 - canal 6 padrao
		{
			buffer_ganho[x] = 20;
		}
	}

	for(x = 0;x < 8;x++) //Armazena o valor das 8 posições do buffer_ganho no vetor de gravação da memória FLASH para o ganho dos potenciômetros digitais
	{
		Write_Buffer_FLASH[OFFSET_POTENCIOMETRO_GANHO + x] = buffer_ganho[x + 1];
	}
	fnEnviaSPI(POT_GANHO,AREA_1,buffer_ganho[1]); //Envia a configuração de ganho para a área 1
	fnEnviaSPI(POT_GANHO,AREA_2,buffer_ganho[2]); //Envia a configuração de ganho para a área 2
	fnEnviaSPI(POT_GANHO,AREA_3,buffer_ganho[3]); //Envia a configuração de ganho para a área 3
	fnEnviaSPI(POT_GANHO,AREA_4,buffer_ganho[4]); //Envia a configuração de ganho para a área 4
	fnEnviaSPI(POT_GANHO,AREA_5,buffer_ganho[5]); //Envia a configuração de ganho para a área 5
	fnEnviaSPI(POT_GANHO,AREA_6,buffer_ganho[6]); //Envia a configuração de ganho para a área 6
	fnEnviaSPI(POT_GANHO,AREA_7,buffer_ganho[7]); //Envia a configuração de ganho para a área 7
	fnEnviaSPI(POT_GANHO,AREA_8,buffer_ganho[8]); //Envia a configuração de ganho para a área 8



	//POTENCIÔMETROS DE SELEÇÃO

//	for(x = 0;x < 9;x++) //Armazena nas 8 posições do buffer_selecao o valor 63
//	{
//		buffer_selecao[x] = 63;
//	}
	for(x = 0;x < 8;x++) //Armazena o valor das 8 posições do buffer_selecao no vetor de gravação da memória FLASH para a seleção de metais dos potenciômetros digitais
	{
		Write_Buffer_FLASH[OFFSET_POTENCIOMETRO_SELECAO + x] = buffer_selecao[x + 1];
	}

	fnEnviaSPI(POT_DEFASAGEM,TODAS_AREAS,63); //Permite enviar a configuração da seleção de metais para alterar os potenciômetros digitais

	//ANULA ÁREAS
	for(x = 0;x < 8;x++) //Armazena nas 8 posições de anula_area o valor 0 para não anular as áreas
	{
		anula_area[x] = 0;
	}
	for(x = 0;x < 8;x++) //Armazena o valor das 8 posições de anula_area no vetor de gravação da memória FLASH para o vetor anula_area
	{
		Write_Buffer_FLASH[OFFSET_ANULA_AREA1 + x] = anula_area[x];
	}

	//FILTRO RUIDO
	filtroruido = 0; //Armazena na variável filtroruido o valor 0
	Write_Buffer_FLASH[OFFSET_FILTRO_RUIDO] = filtroruido; //Armazena o valor de filtroruido no vetor de gravação da memória FLASH para o filtroruido

	//TRAVA INTELIGENTE
	trava_inteligente = NAO; //Armazena na variável trava_inteligente a informação NAO
	Write_Buffer_FLASH[OFFSET_TRAVA_INTELIGENTE] = trava_inteligente; //Armazena o valor da trava_inteligente no vetor de gravação da memória FLASH para a trava_inteligente


	//TIPO DE DETECTOR
	tipo_detector = Z8;
	Write_Buffer_FLASH[OFFSET_TIPO_DETECTOR] = tipo_detector; //Armazena o numero no vetor de gravação da memória FLASH para o tipo de detector

	//PONTEIROS DE LOG DE AUDITORIAS
	posicao_bloco_a = 0;
	Write_Buffer_FLASH[OFFSET_PONTEIRO_BLOCO_A] = posicao_bloco_a;
	posicao_byte_a = 0;
	Write_Buffer_FLASH[OFFSET_PONTEIRO_BYTES_A] = (byte)(posicao_byte_a >> 8);
	Write_Buffer_FLASH[OFFSET_PONTEIRO_BYTES_A + 1] = (byte)(posicao_byte_a);

	//PONTEIROS DE LOG DE EVENTOS
	posicao_bloco_l = 1;
	Write_Buffer_FLASH[OFFSET_PONTEIRO_BLOCO_L] = posicao_bloco_l;
	posicao_byte_l = 0;
	Write_Buffer_FLASH[OFFSET_PONTEIRO_BYTES_L] = (byte)(posicao_byte_l >> 8);
	Write_Buffer_FLASH[OFFSET_PONTEIRO_BYTES_L + 1] = (byte)(posicao_byte_l);

	//ELIMINAR FALHA DA BOBINA
	eliminar_falha = SIM;
	Write_Buffer_FLASH[OFFSET_FALHA_DA_BOBINA] = eliminar_falha;

	//IP
	str3 = IP_PADRAO_FABRICA;

	for(x = 0;x < strlen(str3);x++)
	{
		end_IP[x] = str3[x];
	}
	for(x = 0;x < 15;x++)
	{
		Write_Buffer_FLASH[OFFSET_ENDERECO_IP + x] = end_IP[x];
	}

	//MASCARA DE SUB-REDE
	str3 = MASCARA_PADRAO_FABRICA;

	for(x = 0;x < strlen(str3);x++)
	{
		end_SUB_MASK[x] = str3[x];
	}
	for(x = 0;x < 15;x++)
	{
		Write_Buffer_FLASH[OFFSET_ENDERECO_SUB_REDE + x] = end_SUB_MASK[x];
	}

	//GATEWAY
	str3 = GATEWAY_PADRAO_FABRICA;

	for(x = 0;x < strlen(str3);x++)
	{
		end_GATEWAY[x] = str3[x];
	}
	for(x = 0;x < 15;x++)
	{
		Write_Buffer_FLASH[OFFSET_ENDERECO_GATEWAY + x] = end_GATEWAY[x];
	}

	//DNS
	str3 = DNS_PADRAO_FABRICA;

	for(x = 0;x < strlen(str3);x++)
	{
		end_DNS[x] = str3[x];
	}
	for(x = 0;x < 15;x++)
	{
		Write_Buffer_FLASH[OFFSET_ENDERECO_DNS + x] = end_DNS[x];
	}


	indice_eventos_gravados = 0;
	Write_Buffer_FLASH[OFFSET_INDICE_EVENTOS_GRAVADOS] = (byte)(indice_eventos_gravados >> 8);
	Write_Buffer_FLASH[OFFSET_INDICE_EVENTOS_GRAVADOS + 1] = (byte)(indice_eventos_gravados);

	indice_auditorias_gravados = 0;
	Write_Buffer_FLASH[OFFSET_INDICE_AUDITORIAS_GRAVADOS] = (byte)(indice_auditorias_gravados >> 8);
	Write_Buffer_FLASH[OFFSET_INDICE_AUDITORIAS_GRAVADOS + 1] = (byte)(indice_auditorias_gravados);

	porta_automatica = NAO;
	Write_Buffer_FLASH[OFFSET_PORTA_AUTOMATICA] = porta_automatica;

	opcaosensorcontador = SENSOR_TETO;
	Write_Buffer_FLASH[OFFSET_OPCAO_SENSOR_CONTADOR] = opcaosensorcontador;


	Write_Buffer_FLASH[OFFSET_OPCAO_MODO_ETHERNET] = MODO_SERIAL;

	sorteador = NAO;
	Write_Buffer_FLASH[OFFSET_SORTEADOR] = sorteador;

	cont_sorteador = 0;
	Write_Buffer_FLASH[OFFSET_CONT_SORTEADOR] = cont_sorteador;

	quantidade_sorteados = 10;
	Write_Buffer_FLASH[OFFSET_QUANTIDADE_SORTEADOS] = quantidade_sorteados;

	numero_sorteado = 0;
	Write_Buffer_FLASH[OFFSET_NUMERO_SORTEADO] = numero_sorteado;

	senha_gerente_trocada = FALSE;
	Write_Buffer_FLASH[OFFSET_SENHA_GERENTE_TROCADA] = senha_gerente_trocada;

	senha_tecnico_trocada = FALSE;
	Write_Buffer_FLASH[OFFSET_SENHA_TECNICO_TROCADA] = senha_tecnico_trocada;

	//Index Tipo de Controle Cadastrado (Config. vs Trava/Destrava)
	for(x = 0;x < 3;x++) //Nenhum controle cadsatrado
	{
		indexControle[x] = 0;
	}
	for(x = 0;x < 3;x++)
	{
		Write_Buffer_FLASH[OFFSET_TIPO_CONTROLE + x] = anula_area[x];
	}


	ESCREVE_FLASH_INTERNA(endFLASHInicial,numParametros,0); //Escreve no endereço especificado todos os bytes (numParametros) de informações colocadas no vetor de gravação da memória FLASH

	modo_operacao_ethernet = MODO_AT;
	fnEstadoComandoAT(); 	//Entra no modo de comandos AT
	time_out_ethernet = 0;
	fnGravaIPs_PADRAO(); 	//Grava os endereços IP padrão, máscara de sub-rede padrão, gateway padrão
	time_out_ethernet = 0;
	fnGravaDNS(); 			//Grava o endereço DNS padrão
	time_out_ethernet = 0;
	fnGravaSOCKPORT(); 		//Grava a porta local que é sempre 20108
	time_out_ethernet = 0;
	fnResetaModulo(); 		//Reseta o módulo para que a alteração seja efetivada
	modo_operacao_ethernet = MODO_SERIAL;

	for(x = 0;x < 2048;x++) //Faz um for até 2048 para poder zerar a memória de flag de eventos
	{
		Write_Buffer_FLASH[x] = 0; //Escreve zero para inicializar
	}


	ESCREVE_FLASH_INTERNA(END_INI_FLAG_EVENTOS,2048,5); //address = END_INI_PARAMETROS + (block_number * 0x1000); //Armazena address com o valor (0x43000 + (5 * 0x1000)) = 0x48000

	endereco = END_INI_FLAG_AUDITORIA;



	for(y = 50;y < 54;y++) //Zera 4 blocos de 0x1000 (4096 bytes) que vai dar do endereço 0x75000 a 0x79000-1
	{
		for(x = 0;x < 4096;x++) //Faz um for até 2048 para poder zerar a memória de flag de eventos
		{
			Write_Buffer_FLASH[x] = 0; //Escreve zero para inicializar
		}
		ESCREVE_FLASH_INTERNA(endereco,4096,y); //address = END_INI_PARAMETROS + (block_number * 0x1000); //Armazena address com o valor (0x43000 + (50 * 0x1000)) = 0x75000
		endereco = endereco + 0x1000; //Aqui deve se apontar o endereço de inicio do bloco pois será preenchido com 4096 posicões desde o inicio.
	}


	//fnTesteEventos();
	//fnTesteAuditorias();

	//indice_eventos_lidos = 0;
	//indice_auditorias_lidos = 0;
	estado_passagem = 1;
	estado_passagem1 = 1;

	//Apaga controles remotos
	CLEAR_PROG;
	delay_segundos(12);
	SET_PROG;


}


// Esse codigo comentado estava aqui nessa altura no arquivo original

/*
y = 0;
for(x = 10;x < 330;x = x + 10) //Para chegar no x < 330 fazer 10 x 32 registros = 320 e depois somar 10 = 330
{
	indice_eventos = indice_eventos + 1;
	Write_Buffer_FLASH[x] = Read_Buffer_FLASH[y + z];
	Write_Buffer_FLASH[x+1] = Read_Buffer_FLASH[y + 1 + z];
	Write_Buffer_FLASH[x+2] = Read_Buffer_FLASH[y + 2 + z];
	Write_Buffer_FLASH[x+3] = Read_Buffer_FLASH[y + 3 + z];
	Write_Buffer_FLASH[x+4] = Read_Buffer_FLASH[y + 4 + z];
	Write_Buffer_FLASH[x+5] = Read_Buffer_FLASH[y + 5 + z];
	Write_Buffer_FLASH[x+6] = Read_Buffer_FLASH[y + 6 + z];
	Write_Buffer_FLASH[x+7] = Read_Buffer_FLASH[y + 7 + z];
	Write_Buffer_FLASH[x+8] = (byte)(indice_eventos >> 8);
	Write_Buffer_FLASH[x+9] = (byte)(indice_eventos);
	y = y + 8;

	if((indice_eventos > indice_eventos_lidos) && (indice_eventos_lidos != 0))
	{
		k = x;
		x = 330;
	}
	else
	{
		k = 0;
	}
}
if(k > 0)
{
	r = 10;
	for(x = k;x < 330;x = x + 10)
	{
		envia_serial[r] = Write_Buffer_FLASH[x];
		envia_serial[r+1] = Write_Buffer_FLASH[x+1];
		envia_serial[r+2] = Write_Buffer_FLASH[x+2];
		envia_serial[r+3] = Write_Buffer_FLASH[x+3];
		envia_serial[r+4] = Write_Buffer_FLASH[x+4];
		envia_serial[r+5] = Write_Buffer_FLASH[x+5];
		envia_serial[r+6] = Write_Buffer_FLASH[x+6];
		envia_serial[r+7] = Write_Buffer_FLASH[x+7];
		envia_serial[r+8] = Write_Buffer_FLASH[x+8];
		envia_serial[r+9] = Write_Buffer_FLASH[x+9];
		r = r + 10;
	}
	Write_Buffer_FLASH[r] = '!'; //Caracter de inicio
	Write_Buffer_FLASH[r+1] = '/n'; //Caracter de inicio
}
else
{
	Write_Buffer_FLASH[x] = '!'; //Caracter de inicio
	Write_Buffer_FLASH[x+1] = '/n'; //Caracter de inicio
}

SERIAL_ETHERNET_SendBlock((byte*)&Write_Buffer_FLASH,x+2,&Sent); //Envia para o módulo ethernet os 5 bytes de dados
AGUARDA_Waitms(5000);
SERIAL_ETHERNET_ClearTxBuf();
AGUARDA_Waitms(5000);
*/


//Endereços das flags inciam em 0x48000 e vão até 0x49000-1 que é um bloco de 0x1000 com capacidade para 4096 registros de eventos
void fnLeEnderecoFlagEventos(dword endereco_evento_lido) //Função para apontar o endereço do registro que não foi lido pelo servidor
{
	do
	{
		LE_FLASH_INTERNA((endereco_evento_lido + contador_endereco),1);
		flagEventoLido = Read_Buffer_FLASH[0];
		contador_endereco = contador_endereco + 1;
	}while (!flagEventoLido && (endereco_evento_lido + contador_endereco) < 0x48800); //Laço faça enquanto a flagEventoLido não for 1 ou até o endereço for menor que 48800 que da 2048 registros de eventos

	if(flagEventoLido) //Se flagEventoLido for 1 significa que o registro neste endereço não foi lido pelo servidor e envia o endereço que não foi lido e seta a flag EventToSend para dizer que tem que enviar o registro de novo
	{
		end_event_reenvio = endereco_evento_lido + (contador_endereco - 1); //Endereço do evento que não foi lido
		EventToSend = 1; //Seta a flag para indicar que o registro deste endereço deve ser enviado de novo
		contador_endereco = 0; //Zera a variável contador_endereço para na próxima rodada a lógica funcionar corretamente
	}
	else if((endereco_evento_lido + contador_endereco) == 0x48800) //Senão se não foi encontrado nenhuma registro que não foi lido e o endereço for maior que 0x48800 ou 2048 registros então zera a variável apontador de endereços e zera a flag EventToSend
	{
		end_event_reenvio = 0x48000; //Retorna o endereço para a primeira posição de leitura
		EventToSend = 0; //Zera a flag para indicar que nenhum registro deve ser enviado de novo
		contador_endereco = 0; //Zera a variável contador_endereço para na próxima rodada a lógica funcionar corretamente
	}
}

//Endereço das flags iniciam em 0x75000 e vão até 0x79000 - são 4 blocos de 0x1000, totalizando a capacidade máxima de 16384 registros de auditorias
void fnLeEnderecoFlagAuditorias(dword endereco_auditoria_lido) //Função para apontar o endereço do registro que não foi lido pelo servidor
{
	do
	{
		LE_FLASH_INTERNA((endereco_auditoria_lido + contador_endereco_audit),1);
		flagAuditLido = Read_Buffer_FLASH[0];
		contador_endereco_audit = contador_endereco_audit + 1;
	}while (!flagAuditLido && (endereco_auditoria_lido + contador_endereco_audit) < 0x79000); //Laço faça enquanto a flagEventoLido não for 1 ou até o endereço for menor que 48800 que da 2048 registros de eventos

	if(flagAuditLido) //Se flagEventoLido for 1 significa que que o registro neste endereço não foi lido pelo servidor e envia o endereço que não foi lido e seta a flag EventToSend para dizer que tem que enviar o registro de novo
	{
		end_audit_reenvio = endereco_auditoria_lido + (contador_endereco_audit - 1); //Endereço do evento que não foi lido
		AudToSend = 1; //Seta a flag para indicar que o registro deste endereço deve ser enviado de novo
		contador_endereco_audit = 0; //Zera a variável contador_endereço para na próxima rodada a lógica funcionar corretamente
	}
	else if((endereco_auditoria_lido + contador_endereco_audit) == 0x79000) //Senão se não foi encontrado nenhuma registro que não foi lido e o endereço for maior que 0x48800 ou 2048 registros então zera a variável apontador de endereços e zera a flag EventToSend
	{
		end_audit_reenvio = 0x75000; //Retorna o endereço para a primeira posição de leitura
		AudToSend = 0; //Zera a flag para indicar que nenhum registro deve ser enviado de novo
		contador_endereco_audit = 0; //Zera a variável contador_endereço para na próxima rodada a lógica funcionar corretamente
	}
}



/*** Funções da MEMÓRIA FLASH ***/
/******************************************************************************/

void LeParametrosDetector(void) //Função que carrega os parâmetros e decide se vai gravar padrões de fábrica ou se vai somente ler os parâmetros do detector de metais
{
	char existeFabricaBackup = MEMORIA_FLASH_VAZIA;

	LE_FLASH_INTERNA(END_INI_BACKUP_PARAMETROS,185); //Faz a leitura do endereco de backup para conferir se houve problema na memoria
	existeFabricaBackup = Read_Buffer_FLASH[44];

	LE_FLASH_INTERNA(endFLASHFabrica,1); //Lê no endereço especificado se já foi gravado dados de fábrica ou não

	fabrica = Read_Buffer_FLASH[0]; //Armazena na variável fábrica o valor lido da memória flash no endereço especificado

	if(fabrica != existeFabricaBackup && existeFabricaBackup == MEMORIA_FLASH_GRAVADA){
		//Checa se existe diferenca entre um e outro (se existir faz uma conferencia)
			// Essa rotina e necessaria caso a corrupcao esteja no bloco inteiro - E impede que faca uma gravacao de fabrica

		fnRotinaBackupMemoriaConfiguracaoValida(0);
		LE_FLASH_INTERNA(endFLASHFabrica,1);
		fabrica = Read_Buffer_FLASH[0];
	}

	if(fabrica == MEMORIA_FLASH_VAZIA) //Se fabrica for igual a 0xFF significa que a memória FLASH esta vazia e nunca foi gravado nada
	{
		tela = TELA_GRAVANDO_PADROES_DE_FABRICA; //Tela é igual a TELA_GRAVANDO_PADROES_DE_FABRICA
		Atualiza_LCD(); //Atualiza o LCD com a tela acima
		GravaPadroesFabrica(); //Grava parâmetros padrões de fábrica
		estado_ENVIA_SERIAL_ETHERNET = ESTADO_ENVIAR;
		LEITURA_FLASH_FINALIZADA = SIM;
	}
	else if(fabrica == MEMORIA_FLASH_GRAVADA) //Senão se fabrica for igual a 1 então já foi gravado os padrões de fábrica uma vez
	{
		tela = TELA_LENDO_PADROES_GRAVADOS; //Tela é igual a TELA_LENDO_PADROES_GRAVADOS
		Atualiza_LCD(); //Atualiza o LCD com a tela acima
		fnCarregaParametros(); //Carrega os parâmetros padrões de fábrica
		estado_ENVIA_SERIAL_ETHERNET = ESTADO_ENVIAR;
		LEITURA_FLASH_FINALIZADA = SIM;
	}
	else if(fabrica != MEMORIA_FLASH_VAZIA && fabrica != MEMORIA_FLASH_GRAVADA) //Senão se fabrica não for igual a MEMORIA_FLASH_VAZIA e fabrica não for igual a MEMORIA_FLASH_GRAVADA então grava uma senha padrão para acesso as funções
	{
		//SENHA DA ENGENHARIA
		buffer_senhas[12] = '1'; //Armazena no vetor buffer_senhas na posição 12 o valor 1
		buffer_senhas[13] = '0'; //Armazena no vetor buffer_senhas na posição 13 o valor 0
		buffer_senhas[14] = '9'; //Armazena no vetor buffer_senhas na posição 14 o valor 9
		buffer_senhas[15] = '0'; //Armazena no vetor buffer_senhas na posição 15 o valor 0
		buffer_senhas[16] = '7'; //Armazena no vetor buffer_senhas na posição 16 o valor 7
		buffer_senhas[17] = '1'; //Armazena no vetor buffer_senhas na posição 17 o valor 1

		tela = TELA_MEMORIA_FLASH_COM_DEFEITO; //Tela é igual a TELA_MEMORIA_FLASH_COM_DEFEITO
		Atualiza_LCD(); //Atualiza o LCD com a tela acima
	}

	//Confere se nao foi gravado uma memoria corrompida (em que a corrupcao esta apos o fabrica - apos o index 44)
	fnRotinaBackupMemoriaConfiguracaoValida(0);

//	delay_ms(1000);	//Espera 3s

	fnDiminuiTodoVolume(); //Função que diminui todo o volume da mensagem de voz

	fnAumentaVolume(volume_mensagem_voz); //Função que aumenta o volume da mensagem de voz de acordo com o valor pré-gravado na memória FLASH

	teclapressionada = 0; //Limpa teclapressionada

	//LIGA_SINALEIRA_VERDE; //Liga sinaleira verde

	//TocaTomBuzzer(); //Toca tom do buzzer

	ACENDE_NIVEL0; //Apaga leds do bargraph

	SINAL_DAS_AREAS_Start(); //Inicializa a leitura das áreas de detecção

	TENSAO_DAS_AREAS_Start();

	delay_ms(1000);

	LimpaLCD();
	tela = TELA_CONFIRMA_INICIAR;
	estado_LCD = ATUALIZA_LCD;

	/*********** Escreve Nome da Empresa e Número de Série no LCD *****************/
	//LimpaLCD();
	//tela = TELA_INICIAL;
	//Atualiza_LCD();
	/******************************************************************************/

	estado = ESTADO_LER_TECLAS; //Estado a ser executado é ESTADO_LER_TECLAS
}

void fnCarregaParametros(void) //Função que lê os parâmetros alterados e já gravados no detector de metais
{
	fnRotinaBackupMemoriaConfiguracaoValida(0);	//Confere se os dados estao validos ou corrompidos

	LE_FLASH_INTERNA(endFLASHInicial,numParametros); 		//Lê os 178 bytes gravados na memória FLASH e coloca no vetor Read_Buffer_FLASH
												//NOTA: a funcao anterior nao le o serial


	//SENHA DA GERÊNCIA
	for(x = 0;x < 6;x++) //Armazena nas 6 posições do vetor buffer_senhas de 0 a 5 o que foi lido da memória FLASH
	{
		buffer_senhas[x] = Read_Buffer_FLASH[OFFSET_SENHA_DA_GERENCIA + x];
	}

	//SENHA DO TÉCNICO
	for(x = 0;x < 6;x++) //Armazena nas 6 posições do vetor buffer_senhas de 6 à 11 o que foi lido da memória FLASH
	{
		buffer_senhas[x + 6] = Read_Buffer_FLASH[OFFSET_SENHA_DO_TECNICO + x];
	}

	//SENHA DA ENGENHARIA
	for(x = 0;x < 6;x++) //Armazena nas 6 posições do vetor buffer_senhas de 12 à 17 o que foi lido da memória FLASH
	{
		buffer_senhas[x + 12] = Read_Buffer_FLASH[OFFSET_SENHA_DA_ENGENHARIA + x];
	}

	//SENSIBILIDADE
	for(x = 0;x < 8;x++) //Armazena nas 8 posições do vetor buffer_sensibilidade o que foi lido da memória FLASH
	{
		buffer_sensibilidade[x + 1] = Read_Buffer_FLASH[OFFSET_SENSIBILIDADE + x];
	}
	buffer_sensibilidade[0] = buffer_sensibilidade[1]; //Armazena na posição 0 do vetor buffer_sensibilidade o valor da área 1 para TODAS_ÁREAS

	//MODO DE TRAVAMENTO
	modo_travamento = Read_Buffer_FLASH[OFFSET_MODO_TRAVAMENTO]; //Armazena na variável modo_travamento o que foi lido da memória FLASH

	//CANAL
	canal = Read_Buffer_FLASH[OFFSET_CANAL]; //Armazena na variável canal o que foi lido da memória FLASH

	//SELEÇÃO DE METAIS
	selecao_metais = Read_Buffer_FLASH[OFFSET_SELECAO_METAIS]; //Armazena na variável selecao_metais o que foi lido da memória FLASH

	//TRAVA
	pulso_trava = Read_Buffer_FLASH[OFFSET_PULSO_TRAVA]; //Armazena na variável pulso_trava o que foi lido da memória FLASH
	sinal_trava = Read_Buffer_FLASH[OFFSET_SINAL_TRAVA]; //Armazena na variável sinal_trava o que foi lido da memória FLASH

	//RELÉ
	pulso_rele = Read_Buffer_FLASH[OFFSET_PULSO_RELE]; //Armazena na variável pulso_rele o que foi lido da memória FLASH
	sinal_rele = Read_Buffer_FLASH[OFFSET_SINAL_RELE]; //Armazena na variável sinal_rele o que foi lido da memória FLASH

	//NÚMERO DE CONTROLES
	numero_controles = Read_Buffer_FLASH[OFFSET_NUMERO_CONTROLES]; //Armazena na variável numero_controles o que foi lido da memória FLASH

	//SENSIBILIDADE IR
	sensibilidadeir = Read_Buffer_FLASH[OFFSET_SENSIBILIDADEIR]; //Armazena na variável sensibilidadeir o que foi lido da memória FLASH
	PWM_INFRAS_SetRatio8(sensibilidadeir); //Seta o pwm dos infras de acordo com o valor da sensibilidadeir

	//ANALISE IR
	analiseir = Read_Buffer_FLASH[OFFSET_ANALISEIR]; //Armazena na variável analiseir o que foi lido da memória FLASH

	//FABRICA
	fabrica = Read_Buffer_FLASH[OFFSET_FABRICA]; //Armazena na variável fabrica o que foi lido da memória FLASH

	//IDIOMA
	idioma = Read_Buffer_FLASH[OFFSET_IDIOMA]; //Armazena na variável idioma o que foi lido da memória FLASH

	//BUZZER
	buffer_buzzer[BUZZER_TOM] = Read_Buffer_FLASH[OFFSET_BUZZER_TOM]; //Armazena na posição 0 do vetor buffer_buzzer o que foi lido da memória FLASH para o tom
	buffer_buzzer[BUZZER_VOLUME] = Read_Buffer_FLASH[OFFSET_BUZZER_VOLUME]; //Armazena na posição 1 do vetor buffer_buzzer o que foi lido da memória FLASH para o volume
	buffer_buzzer[BUZZER_LIGA_DESLIGA] = Read_Buffer_FLASH[OFFSET_BUZZER_LIG_DES]; //Armazena na posição 2 do vetor buffer_buzzer o que foi lido da memória FLASH para o estado lig/des

	//MENSAGEM DE VOZ
	volume_mensagem_voz = Read_Buffer_FLASH[OFFSET_MSG_VOZ_VOLUME]; //Armazena na variável volume_mensagem_voz o que foi lido da memória FLASH
	lig_des_mensagem_voz = Read_Buffer_FLASH[OFFSET_MSG_VOZ_LIG_DES]; //Armazena na variável lig_des_mensagem_voz o que foi lido da memória FLASH

	//ALARME VISUAL
	alarme_visual = Read_Buffer_FLASH[OFFSET_ALARME_VISUAL_LIG_DES]; //Armazena na variável alarme_visual o que foi lido da memória FLASH

	//CONTADOR DE DETECÇÕES - TOTAL DE BLOQUEIOS
	//Remonta os 4 bytes separados na memória FLASH para a variável contador_bloqueios através do deslocamento de bits abaixo
	contador_bloqueios = Read_Buffer_FLASH[OFFSET_TOTAL_BLOQUEIOS] << 24;
	contador_bloqueios += Read_Buffer_FLASH[OFFSET_TOTAL_BLOQUEIOS + 1] << 16;
	contador_bloqueios += Read_Buffer_FLASH[OFFSET_TOTAL_BLOQUEIOS + 2] << 8;
	contador_bloqueios += Read_Buffer_FLASH[OFFSET_TOTAL_BLOQUEIOS + 3];

	//CONTADOR DE DETECÇÕES - TOTAL DE DESBLOQUEIOS
	//Remonta os 4 bytes separados na memória FLASH para a variável contador_desbloqueios através do deslocamento de bits abaixo
	contador_desbloqueios = Read_Buffer_FLASH[OFFSET_TOTAL_DESBLOQUEIOS] << 24;
	contador_desbloqueios += Read_Buffer_FLASH[OFFSET_TOTAL_DESBLOQUEIOS + 1] << 16;
	contador_desbloqueios += Read_Buffer_FLASH[OFFSET_TOTAL_DESBLOQUEIOS + 2] << 8;
	contador_desbloqueios += Read_Buffer_FLASH[OFFSET_TOTAL_DESBLOQUEIOS + 3];

	//CONTADOR DE PASSAGENS - PROGRESSIVA
	//Remonta os 4 bytes separados na memória FLASH para a variável contador_entra através do deslocamento de bits abaixo
	contador_entra = Read_Buffer_FLASH[OFFSET_CONTADOR_ENTRADAS] << 24;
	contador_entra += Read_Buffer_FLASH[OFFSET_CONTADOR_ENTRADAS + 1] << 16;
	contador_entra += Read_Buffer_FLASH[OFFSET_CONTADOR_ENTRADAS + 2] << 8;
	contador_entra += Read_Buffer_FLASH[OFFSET_CONTADOR_ENTRADAS + 3];

	//CONTADOR DE PASSAGENS - REGRESSIVA
	//Remonta os 4 bytes separados na memória FLASH para a variável contador_sai através do deslocamento de bits abaixo
	contador_sai = Read_Buffer_FLASH[OFFSET_CONTADOR_SAIDAS] << 24;
	contador_sai += Read_Buffer_FLASH[OFFSET_CONTADOR_SAIDAS + 1] << 16;
	contador_sai += Read_Buffer_FLASH[OFFSET_CONTADOR_SAIDAS + 2] << 8;
	contador_sai += Read_Buffer_FLASH[OFFSET_CONTADOR_SAIDAS + 3];

	contador_passagens = contador_entra + contador_sai; //Armazena na variável contador_passagens a soma do contador_entra mais contador_sai

	//PERFIL
	perfil = Read_Buffer_FLASH[OFFSET_PERFIL]; //Armazena na variável perfil o que foi lido da memória FLASH

	//AJUSTES TX-RX
	ciclo_de_trabalho = Read_Buffer_FLASH[OFFSET_AJUSTES_TX_RX_CICLO_TRABALHO]; //Armazena na variável ciclo_de_trabalho o que foi lido da memória FLASH
	//Remonta os 2 bytes separados na memória FLASH para a variável defasagem através do deslocamento de bits abaixo
	defasagem = Read_Buffer_FLASH[OFFSET_AJUSTES_TX_RX_DEFASAGEM] << 8;
	defasagem += Read_Buffer_FLASH[OFFSET_AJUSTES_TX_RX_DEFASAGEM + 1];
	//Remonta os 2 bytes separados na memória FLASH para a variável frequencia através do deslocamento de bits abaixo
	frequencia = Read_Buffer_FLASH[OFFSET_AJUSTES_TX_RX_FREQUENCIA] << 8;
	frequencia += Read_Buffer_FLASH[OFFSET_AJUSTES_TX_RX_FREQUENCIA + 1];

	SetFrequencia(frequencia); //Seta a defasagen e frequência do PWM TX para o valor que foi recebido da memória FLASH acima

	//MODELO DE ANTENA
	modelo_antena = Read_Buffer_FLASH[OFFSET_MODELO_ANTENA]; //Armazena na variável modelo_antena o que foi lido da memória FLASH

	//POTENCIÔMETROS DE GANHO
	for(x = 0;x < 8;x++) //Armazena nas 8 posições do vetor buffer_ganho o que foi lido da memória FLASH
	{
		buffer_ganho[x + 1] = Read_Buffer_FLASH[OFFSET_POTENCIOMETRO_GANHO + x];
	}
	buffer_ganho[0] = buffer_ganho[1]; //Armazena na posição 0 do vetor buffer_ganho o valor da área 1 para TODAS_ÁREAS

	fnEnviaSPI(POT_GANHO,AREA_1,buffer_ganho[1]); //Envia a configuração de ganho para a área 1
	fnEnviaSPI(POT_GANHO,AREA_2,buffer_ganho[2]); //Envia a configuração de ganho para a área 2
	fnEnviaSPI(POT_GANHO,AREA_3,buffer_ganho[3]); //Envia a configuração de ganho para a área 3
	fnEnviaSPI(POT_GANHO,AREA_4,buffer_ganho[4]); //Envia a configuração de ganho para a área 4
	fnEnviaSPI(POT_GANHO,AREA_5,buffer_ganho[5]); //Envia a configuração de ganho para a área 5
	fnEnviaSPI(POT_GANHO,AREA_6,buffer_ganho[6]); //Envia a configuração de ganho para a área 6
	fnEnviaSPI(POT_GANHO,AREA_7,buffer_ganho[7]); //Envia a configuração de ganho para a área 7
	fnEnviaSPI(POT_GANHO,AREA_8,buffer_ganho[8]); //Envia a configuração de ganho para a área 8

	//POTENCIÔMETROS DE SELEÇÃO
	for(x = 0;x < 8;x++) //Armazena nas 8 posições do vetor buffer_selecao o que foi lido da memória FLASH
	{
		buffer_selecao[x + 1] = Read_Buffer_FLASH[OFFSET_POTENCIOMETRO_SELECAO + x];
	}
	buffer_selecao[0] = buffer_selecao[1]; //Armazena na posição 0 do vetor buffer_selecao o valor da área 1 para TODAS_ÁREAS

	fnEnviaSPI(POT_DEFASAGEM,AREA_1,buffer_selecao[1]); //Envia a configuração de seleção para a área 1
	fnEnviaSPI(POT_DEFASAGEM,AREA_2,buffer_selecao[2]); //Envia a configuração de seleção para a área 2
	fnEnviaSPI(POT_DEFASAGEM,AREA_3,buffer_selecao[3]); //Envia a configuração de seleção para a área 3
	fnEnviaSPI(POT_DEFASAGEM,AREA_4,buffer_selecao[4]); //Envia a configuração de seleção para a área 4
	fnEnviaSPI(POT_DEFASAGEM,AREA_5,buffer_selecao[5]); //Envia a configuração de seleção para a área 5
	fnEnviaSPI(POT_DEFASAGEM,AREA_6,buffer_selecao[6]); //Envia a configuração de seleção para a área 6
	fnEnviaSPI(POT_DEFASAGEM,AREA_7,buffer_selecao[7]); //Envia a configuração de seleção para a área 7
	fnEnviaSPI(POT_DEFASAGEM,AREA_8,buffer_selecao[8]); //Envia a configuração de seleção para a área 8

	//ANULA ÁREAS
	for(x = 0;x < 8;x++) //Armazena nas 8 posições do vetor anula_area o que foi lido da memória FLASH
	{
		anula_area[x] = Read_Buffer_FLASH[OFFSET_ANULA_AREAS + x];
	}

	//FILTRO DE RUÍDO
	filtroruido = Read_Buffer_FLASH[OFFSET_FILTRO_RUIDO]; //Armazena na variável filtroruido o que foi lido da memória FLASH

	//TRAVA INTELIGENTE
	trava_inteligente = Read_Buffer_FLASH[OFFSET_TRAVA_INTELIGENTE]; //Armazena na variável trava_inteligente o que foi lido da memória FLASH

	//NÚMERO DE CONTROLES
	numero_controles = Read_Buffer_FLASH[OFFSET_NUMERO_CONTROLES]; //Armazena na variável numero_controles o que foi lido da memória FLASH

	//TIPO DE DETECTOR
	tipo_detector = Read_Buffer_FLASH[OFFSET_TIPO_DETECTOR]; //Armazena na variável tipo_detector o que foi lido da memória FLASH

	//PONTEIROS DOS LOG DE AUDITORIAS
	posicao_byte_a = Read_Buffer_FLASH[OFFSET_PONTEIRO_BYTES_A] << 8;
	posicao_byte_a += Read_Buffer_FLASH[OFFSET_PONTEIRO_BYTES_A + 1];
	posicao_bloco_a = Read_Buffer_FLASH[OFFSET_PONTEIRO_BLOCO_A];

	//PONTEIROS DOS LOG DE EVENTOS
	posicao_byte_l = Read_Buffer_FLASH[OFFSET_PONTEIRO_BYTES_L] << 8;
	posicao_byte_l += Read_Buffer_FLASH[OFFSET_PONTEIRO_BYTES_L + 1];
	posicao_bloco_l = Read_Buffer_FLASH[OFFSET_PONTEIRO_BLOCO_L];

	//ELIMINAR FALHA DA BOBINA
	eliminar_falha = Read_Buffer_FLASH[OFFSET_FALHA_DA_BOBINA];

	for(x = 0;x < 15;x++)
	{
		end_IP[x] = Read_Buffer_FLASH[OFFSET_ENDERECO_IP + x];
	}

	for(x = 0;x < 15;x++)
	{
		end_SUB_MASK[x] = Read_Buffer_FLASH[OFFSET_ENDERECO_SUB_REDE + x];
	}

	for(x = 0;x < 15;x++)
	{
		end_GATEWAY[x] = Read_Buffer_FLASH[OFFSET_ENDERECO_GATEWAY + x];
	}

	for(x = 0;x < 15;x++)
	{
		end_DNS[x] = Read_Buffer_FLASH[OFFSET_ENDERECO_DNS + x];
	}

	//INDICE_EVENTOS_GRAVADOS
	indice_eventos_gravados = Read_Buffer_FLASH[OFFSET_INDICE_EVENTOS_GRAVADOS] << 8;
	indice_eventos_gravados += Read_Buffer_FLASH[OFFSET_INDICE_EVENTOS_GRAVADOS + 1];

	//INDICE_AUDITORIAS_GRAVADOS
	indice_auditorias_gravados = Read_Buffer_FLASH[OFFSET_INDICE_AUDITORIAS_GRAVADOS] << 8;
	indice_auditorias_gravados += Read_Buffer_FLASH[OFFSET_INDICE_AUDITORIAS_GRAVADOS + 1];

	//PORTA AUTOMÁTICA
	porta_automatica = Read_Buffer_FLASH[OFFSET_PORTA_AUTOMATICA];

	//OPÇÃO SENSOR CONTADOR
	opcaosensorcontador = Read_Buffer_FLASH[OFFSET_OPCAO_SENSOR_CONTADOR];

	//MODO ETHERNET
	modo_operacao_ethernet = Read_Buffer_FLASH[OFFSET_OPCAO_MODO_ETHERNET];

	//SORTEADOR
	sorteador = Read_Buffer_FLASH[OFFSET_SORTEADOR];

	//CONTADOR DO SORTEADOR
	cont_sorteador = Read_Buffer_FLASH[OFFSET_CONT_SORTEADOR];

	//QUANTIDADE DE SORTEADOS
	quantidade_sorteados = Read_Buffer_FLASH[OFFSET_QUANTIDADE_SORTEADOS];

	//NUMERO SORTEADO
	numero_sorteado = Read_Buffer_FLASH[OFFSET_NUMERO_SORTEADO];

	//SENHA TROCADA
	senha_gerente_trocada = Read_Buffer_FLASH[OFFSET_SENHA_GERENTE_TROCADA];
	senha_tecnico_trocada = Read_Buffer_FLASH[OFFSET_SENHA_TECNICO_TROCADA];

	//TIPOS DOS CONTROLES CADASTRADOS
	indexControle[0] = Read_Buffer_FLASH[OFFSET_TIPO_CONTROLE];
	indexControle[1] = Read_Buffer_FLASH[OFFSET_TIPO_CONTROLE + 1];
	indexControle[2] = Read_Buffer_FLASH[OFFSET_TIPO_CONTROLE + 2];

	indice_eventos_lidos = indice_eventos_gravados;
	indice_auditorias_lidos = indice_auditorias_gravados;
	estado_passagem = 1;
	estado_passagem1 = 1;

	for(int y3 = 0; y3 < sizeof(numero_serie); y3++){
		numero_serie[y3] = StcPlacas[CONST_PLACA_PAINEL].Serial_number_Flash[y3+2];
	}
}


void fnEscreveNoEndereco(dword endereco, word numero_dados){


	static volatile word x1 = 0; //Define a variável x para zero
	static volatile dword aux_endereco; //Define a variável aux_endereco para auxiliar no cálculo do endereço
	static volatile dword address; //Define a variável address para especificar o endereço e o bloco que será gravado

	dword endereco_bloco;

	aux_endereco = endereco % 0x1000;
	endereco_bloco = endereco - endereco % 0x1000;

	Cpu_DisableInt(); //Desabilita as interrupções

	for(x1 = 0;x1 < 4096;x1++) //Lê os 4096 bytes do bloco para salvar na RAM pois o método de escrita é destructive write with erase
	{
		FLASH_INTERNA_GetByteFlash(endereco_bloco + x1,&Read_Buffer_FLASH[x1]);
	}

	for(x1 = 0;x1 < numero_dados;x1++) //Coloca a quantidade de dados a ser gravada no vetor Read_Buffer_FLASH
	{
		Read_Buffer_FLASH[aux_endereco + x1] = Write_Buffer_FLASH[x1];
	}

	FLASH_INTERNA_SetBlockFlash(&Read_Buffer_FLASH[0],endereco_bloco,4096); //Grava os 4096 bytes no bloco de memória especificado na memória FLASH

	Cpu_EnableInt(); //Habilita as interrupções

}



int checaSeValorValidoMemoria(unsigned char byteParaChecar, int tipoByte, unsigned char valorMinimo, unsigned char valorMaximo){

	//Se o tipoByte for ASCII
	switch(tipoByte){
	case ASCII_ALFANUMERICO:
		if(byteParaChecar >= '.' && byteParaChecar <='z'){
			return 0;
		}
		break;
	case ASCII_NUMERICO:
		if(byteParaChecar >= '.' && byteParaChecar <='9'){
			return 0;
		}
		break;
	case ASCII_ALFANUM_MAIUSCULA:
		if((byteParaChecar >= '0' && byteParaChecar <='9') ||
			(byteParaChecar >= 'A' && byteParaChecar <= 'Z')){
			return 0;
		}

	}

	if(byteParaChecar >= valorMinimo && byteParaChecar <= valorMaximo){
		return 0;
	}

	return 1;

	switch(tipoByte){

	case VALOR_BINARIO:
		break;
	case VALOR_BINARIO_MIN0_MAX1:
		if(byteParaChecar >= 0 && byteParaChecar <= 1){
			return 0;
		}
	case VALOR_BINARIO_MIN0_MAX2:
		if(byteParaChecar >= 0 && byteParaChecar <= 2){
			return 0;
		}
	case VALOR_BINARIO_MIN0_MAX3:
		if(byteParaChecar >= 0 && byteParaChecar <= 3){
			return 0;
		}
	case VALOR_BINARIO_MIN1_MAX2:
		if(byteParaChecar >= 1 && byteParaChecar <= 2){
			return 0;
		}
		break;
	case VALOR_BINARIO_MIN1_MAX3:
		if(byteParaChecar >= 1 && byteParaChecar <= 3){
			return 0;
		}
		break;
	case VALOR_BINARIO_MIN0_MAX31:
		if(byteParaChecar >= 1 && byteParaChecar <= 31){
			return 0;
		}
		break;
	case VALOR_BINARIO_MIN1_MAX10:
		if(byteParaChecar >= 1 && byteParaChecar <= 10){
			return 0;
		}
		break;
	case VALOR_BINARIO_MIN1_MAX12:
		if(byteParaChecar >= 1 && byteParaChecar <= 12){
			return 0;
		}
		break;
	case VALOR_BINARIO_MIN10_MAX50:
		if(byteParaChecar >= 10 && byteParaChecar <= 50){
			return 0;
		}
		break;
	case VALOR_BINARIO_MIN1_MAX100:
		if(byteParaChecar >= 1 && byteParaChecar <= 100){
			return 0;
		}
		break;
	case VALOR_BINARIO_MIN1_MAX150:
		if(byteParaChecar >= 1 && byteParaChecar <= 150){
			return 0;
		}
		break;



	}


	return -1;
}

void fnRotinaBackupMemoriaConfiguracaoValida(int timeStampBackup){
	int i = 0;
	static int contagemBackUp = 10;
	volatile unsigned char retorno = 0;

	LE_FLASH_INTERNA(END_INI_PARAMETROS,NUMERO_DE_PARAMETROS);
	if(TESTE_CORRUPCAO_MEMORIA==TRUE){
		if(buffer_sensibilidade[1] == 51){
			  buffer_sensibilidade[1] = 0xF1;
		}

		if(buffer_sensibilidade[1] == 52){
			memset(Write_Buffer_FLASH, 0xFF, 100);

			fnEscreveNoEndereco(END_INI_PARAMETROS,100);
			fnEscreveNoEndereco(END_INI_BACKUP_PARAMETROS,100);
			buffer_sensibilidade[1] = 0xF1;
		}
	}

	//Faz a checagem se os valores estao corretos
	retorno = fnChecaMemoriaConfiguracaoValida();
	if(!!retorno){	//Valor invalidos
		LE_FLASH_INTERNA(END_INI_BACKUP_PARAMETROS,NUMERO_DE_PARAMETROS);	//TODO VERIFICAR OS PARAMETROS (DEVE INICIAR EM 08? 177 parametros?)

		tela = TELA_VALOR_INVALIDO_EXE_BACKUP; //Tela é igual a TELA_MEMORIA_FLASH_COM_DEFEITO
		Atualiza_LCD(); //Atualiza o LCD com a tela acima



		if(!!fnChecaMemoriaConfiguracaoValida()){
			//Rotina caso as duas memorias estejam corrompidas:
				//  Aperta decrementa e segura em seguida a Incrementa por 5 segundos: wipe da memoria (exceto auditoria) e desliga
			//OU	Aperta confirma e ignora (roda com memoria corrompida)
			tela = TELA_MEMORIA_CORROMPIDA_CONTATE;
			Atualiza_LCD();

			while(1){
				if(teclapressionada== teclaDecrementa){
					delay_ms(5000);
					if(teclapressionada==teclaIncrementa){
						memset(Write_Buffer_FLASH,0xFF,0xFFF);
						fnEscreveNoEndereco(END_INI_PARAMETROS,0xFF0);
						fnEscreveNoEndereco(END_INI_BACKUP_PARAMETROS,0xFF);

						tela = TELA_MEMORIA_CORROMPIDA_DESLIGUE;
						Atualiza_LCD();

						while(1);
					}
				}
				if(teclapressionada== teclaCancela){
					delay_ms(5000);
					if(teclapressionada== teclaConfirma) return;
				}
			}
			return;
		}

		for(i=0;i<NUMERO_DE_PARAMETROS;i++){
			Write_Buffer_FLASH[i] = Read_Buffer_FLASH[i];
		}

		fnEscreveNoEndereco(END_INI_PARAMETROS,NUMERO_DE_PARAMETROS); //Sobrescreve as configuracoes atuais com o backup



		LE_FLASH_INTERNA(END_INI_BACKUP_PARAMETROS,0xFF0);

		i = 0xFF;	// Para facilitar a leitura e dar espaco para eventuais mais configuracoes
		for(; (Read_Buffer_FLASH[i]!=0xFF && Read_Buffer_FLASH[i+1]!=0xFF &&
				Read_Buffer_FLASH[i+2]!=0xFF && Read_Buffer_FLASH[i+3]!=0xFF); ){
			i = i+8;
			if(i>0x0FF0){ //Memoria cheia
				return;
			}
		}

		if(timeStampBackup == 0){
			Write_Buffer_FLASH[i]	= 'I';
			Write_Buffer_FLASH[i+1]	= '0';
			Write_Buffer_FLASH[i+2]	= '0';
			Write_Buffer_FLASH[i+3]	= '0';
			Write_Buffer_FLASH[i+4]	= '0';
		}
		if(timeStampBackup != 0){

			time_t timeStampForBackup = time(NULL);
			struct tm timeForBackup;

			timeForBackup.tm_sec = (int) Time.Second;
			timeForBackup.tm_min = (int) Time.Minute;
			timeForBackup.tm_hour = (int) Time.Hour;
			timeForBackup.tm_mday = (int) Time.Day;
			timeForBackup.tm_mon = (int) Time.Month - 1;
			timeForBackup.tm_year = (int) Time.Year - 1900;

			timeStampForBackup = mktime(&timeForBackup);

			Write_Buffer_FLASH[i]	= 'A';
			Write_Buffer_FLASH[i+1]	= (byte) timeStampForBackup << 24;
			Write_Buffer_FLASH[i+2]	= (byte) timeStampForBackup << 16;
			Write_Buffer_FLASH[i+3]	= (byte) timeStampForBackup << 8;
			Write_Buffer_FLASH[i+4]	= (byte) timeStampForBackup;
		}
		Write_Buffer_FLASH[i+5]	= ((i-0xD8)/8);
		Write_Buffer_FLASH[i+6]	= retorno;
		Write_Buffer_FLASH[i+7]	= '!';

		fnEscreveNoEndereco(END_INI_BACKUP_PARAMETROS, i+8);


		LE_FLASH_INTERNA(END_INI_PARAMETROS + 8, 6);

		delay_ms(1000); //Aguarda 2 segundos para mostrar a tela

		fnCarregaParametros();

		return;

	}

	for(i=0;i<NUMERO_DE_PARAMETROS;i++){
		Write_Buffer_FLASH[i] = Read_Buffer_FLASH[i];
	}

	fnEscreveNoEndereco(END_INI_BACKUP_PARAMETROS, NUMERO_DE_PARAMETROS);



}

int fnChecaMemoriaConfiguracaoValida(){

	const int offSetNumeroSerie = 8;
	const int CHECA_MEMORIA_OFFSET_NUMERO_SERIE = 0;

	//NUMERO DE SERIE
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[CHECA_MEMORIA_OFFSET_NUMERO_SERIE], ASCII_ALFANUM_MAIUSCULA, 0, 0))	return (200);
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[CHECA_MEMORIA_OFFSET_NUMERO_SERIE + 1], ASCII_ALFANUM_MAIUSCULA, 0, 0))	return (201);

	for (x = 0; x < 6; x++){
		if(checaSeValorValidoMemoria(Read_Buffer_FLASH[CHECA_MEMORIA_OFFSET_NUMERO_SERIE + x + 2], ASCII_NUMERICO, 0, 0))	return (202+x);
	}


	//SENHA DA GERÊNCIA
	for(x = 0;x < 6;x++) //Armazena nas 6 posições do vetor buffer_senhas de 0 a 5 o que foi lido da memória FLASH
	{
		if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_SENHA_DA_GERENCIA + x + offSetNumeroSerie], ASCII_ALFANUM_MAIUSCULA, 0, 0))	return (1+x);
	}

	//SENHA DO TÉCNICO
	for(x = 0;x < 6;x++) //Armazena nas 6 posições do vetor buffer_senhas de 6 à 11 o que foi lido da memória FLASH
	{
		if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_SENHA_DO_TECNICO + x + offSetNumeroSerie], ASCII_ALFANUM_MAIUSCULA, 0, 0))	return (7+x);
	}

	//SENHA DA ENGENHARIA
	for(x = 0;x < 6;x++) //Armazena nas 6 posições do vetor buffer_senhas de 12 à 17 o que foi lido da memória FLASH
	{

		if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_SENHA_DA_ENGENHARIA + x + offSetNumeroSerie], ASCII_ALFANUM_MAIUSCULA, 0, 0))	return (13+x);
	}

	//SENSIBILIDADE
	for(x = 0;x < 8;x++) //Armazena nas 8 posições do vetor buffer_sensibilidade o que foi lido da memória FLASH
	{

		if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_SENSIBILIDADE + x + offSetNumeroSerie], VALOR_BINARIO, 1, 100))	return (19+x);
	}


	//MODO DE TRAVAMENTO
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_MODO_TRAVAMENTO + offSetNumeroSerie], VALOR_BINARIO, 1, 2))	return 27;

	//CANAL
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_CANAL + offSetNumeroSerie], VALOR_BINARIO, 1, 25))	return 28;

	//SELEÇÃO DE METAIS
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_SELECAO_METAIS + offSetNumeroSerie], VALOR_BINARIO, 1, 100))	return 29;


	//TRAVA
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_PULSO_TRAVA + offSetNumeroSerie], VALOR_BINARIO, 10, 50))	return 30;
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_SINAL_TRAVA + offSetNumeroSerie], VALOR_BINARIO, 1 , 3))	return 31;

	//RELÉ
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_PULSO_RELE + offSetNumeroSerie], VALOR_BINARIO, 1, 150))	return 32;
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_SINAL_RELE + offSetNumeroSerie], VALOR_BINARIO, 1, 2))	return 33;

	//NÚMERO DE CONTROLES
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_NUMERO_CONTROLES + offSetNumeroSerie], VALOR_BINARIO, 0, 3))	return 34;

	//SENSIBILIDADE IR
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_SENSIBILIDADEIR + offSetNumeroSerie], VALOR_BINARIO, 1, 169))	return 35;

	//ANALISE IR
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_ANALISEIR + offSetNumeroSerie], VALOR_BINARIO, 0, 1))	return 36; //Armazena na variável analiseir o que foi lido da memória FLASH

	//FABRICA
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_FABRICA + offSetNumeroSerie], VALOR_BINARIO, 0,1))	return 37; //Armazena na variável fabrica o que foi lido da memória FLASH

	//IDIOMA
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_IDIOMA + offSetNumeroSerie], VALOR_BINARIO, 0, 2))	return 38; //Armazena na variável idioma o que foi lido da memória FLASH

	//BUZZER
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_BUZZER_TOM + offSetNumeroSerie], VALOR_BINARIO, 1, 10))	return 39; //Armazena na posição 0 do vetor buffer_buzzer o que foi lido da memória FLASH para o tom
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_BUZZER_VOLUME + offSetNumeroSerie], VALOR_BINARIO, 0, 10))	return 40; //Armazena na posição 1 do vetor buffer_buzzer o que foi lido da memória FLASH para o volume
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_BUZZER_LIG_DES + offSetNumeroSerie], VALOR_BINARIO, 0 ,1))	return 41; //Armazena na posição 2 do vetor buffer_buzzer o que foi lido da memória FLASH para o estado lig/des

	//MENSAGEM DE VOZ
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_MSG_VOZ_VOLUME + offSetNumeroSerie], VALOR_BINARIO, 0, 31))	return 42;  //Armazena na variável volume_mensagem_voz o que foi lido da memória FLASH
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_MSG_VOZ_LIG_DES + offSetNumeroSerie], VALOR_BINARIO, 0, 1))	return 43; //Armazena na variável lig_des_mensagem_voz o que foi lido da memória FLASH

	//ALARME VISUAL
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_ALARME_VISUAL_LIG_DES + offSetNumeroSerie], VALOR_BINARIO, 0, 1))	return 44;  //Armazena na variável alarme_visual o que foi lido da memória FLASH

	//CONTADOR DE DETECÇÕES - TOTAL DE BLOQUEIOS
	//Remonta os 4 bytes separados na memória FLASH para a variável contador_bloqueios através do deslocamento de bits abaixo
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_TOTAL_BLOQUEIOS + offSetNumeroSerie] << 24, VALOR_BINARIO, 0, 255))	return 45;
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_TOTAL_BLOQUEIOS + 1 + offSetNumeroSerie] << 16, VALOR_BINARIO, 0, 255))	return 46;
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_TOTAL_BLOQUEIOS + 2 + offSetNumeroSerie] << 8, VALOR_BINARIO, 0, 255))	return 47;
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_TOTAL_BLOQUEIOS + 3 + offSetNumeroSerie], VALOR_BINARIO, 0, 255))	return 48;

	//CONTADOR DE DETECÇÕES - TOTAL DE DESBLOQUEIOS
	//Remonta os 4 bytes separados na memória FLASH para a variável contador_desbloqueios através do deslocamento de bits abaixo
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_TOTAL_DESBLOQUEIOS + offSetNumeroSerie] << 24, VALOR_BINARIO, 0, 255))	return 49;
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_TOTAL_DESBLOQUEIOS + 1 + offSetNumeroSerie] << 16, VALOR_BINARIO, 0, 255))	return 50;
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_TOTAL_DESBLOQUEIOS + 2 + offSetNumeroSerie] << 8, VALOR_BINARIO, 0, 255))	return 51;
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_TOTAL_DESBLOQUEIOS + 3 + offSetNumeroSerie], VALOR_BINARIO, 0, 255))	return 52;


	//CONTADOR DE PASSAGENS - PROGRESSIVA
	//Remonta os 4 bytes separados na memória FLASH para a variável contador_entra através do deslocamento de bits abaixo
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_CONTADOR_ENTRADAS + offSetNumeroSerie] << 24, VALOR_BINARIO, 0, 255))	return 53;
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_CONTADOR_ENTRADAS + 1 + offSetNumeroSerie] << 16, VALOR_BINARIO, 0, 255))	return 54;
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_CONTADOR_ENTRADAS + 2 + offSetNumeroSerie] << 8, VALOR_BINARIO, 0, 255))	return 55;
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_CONTADOR_ENTRADAS + 3 + offSetNumeroSerie], VALOR_BINARIO, 0, 255))	return 56;

	//CONTADOR DE PASSAGENS - REGRESSIVA
	//Remonta os 4 bytes separados na memória FLASH para a variável contador_sai através do deslocamento de bits abaixo
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_CONTADOR_SAIDAS + offSetNumeroSerie] << 24, VALOR_BINARIO, 0, 255))	return 57;
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_CONTADOR_SAIDAS + 1 + offSetNumeroSerie] << 16, VALOR_BINARIO, 0, 255))	return 58;
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_CONTADOR_SAIDAS + 2 + offSetNumeroSerie] << 8, VALOR_BINARIO, 0, 255))	return 59;
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_CONTADOR_SAIDAS + 3 + offSetNumeroSerie], VALOR_BINARIO, 0, 255))	return 60;

	//PERFIL
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_PERFIL + offSetNumeroSerie], VALOR_BINARIO, 0, 6))	return 61; //Armazena na variável perfil o que foi lido da memória FLASH

	//AJUSTES TX-RX
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_AJUSTES_TX_RX_CICLO_TRABALHO + offSetNumeroSerie], VALOR_BINARIO, 1, 99))	return 62; //Armazena na variável ciclo_de_trabalho o que foi lido da memória FLASH
	//Remonta os 2 bytes separados na memória FLASH para a variável defasagem através do deslocamento de bits abaixo
		// A soma dos valores nao pode ser maior que 360
	if((((int)(Read_Buffer_FLASH[OFFSET_AJUSTES_TX_RX_DEFASAGEM + offSetNumeroSerie] * 256)) +
			((int)Read_Buffer_FLASH[OFFSET_AJUSTES_TX_RX_DEFASAGEM + 1 + offSetNumeroSerie])) > 360){
		return 63;
	}


	//MODELO DE ANTENA
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_MODELO_ANTENA + offSetNumeroSerie], VALOR_BINARIO, 0, 6))	return 64; //Armazena na variável modelo_antena o que foi lido da memória FLASH

	//POTENCIÔMETROS DE GANHO
	for(x = 0; x < 8; x++)  //Armazena nas 8 posições do vetor buffer_ganho o que foi lido da memória FLASH
	{
		if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_POTENCIOMETRO_GANHO + x + offSetNumeroSerie], VALOR_BINARIO, 1, 127))	return 65;
	}

	//POTENCIÔMETROS DE SELEÇÃO
	for(x = 0; x < 8; x++) //Armazena nas 8 posições do vetor buffer_selecao o que foi lido da memória FLASH
	{
		if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_POTENCIOMETRO_SELECAO + x + offSetNumeroSerie], VALOR_BINARIO, 0, 127))	return 66;
	}

	//ANULA ÁREAS
	for(x = 0;x < 8;x++) //Armazena nas 8 posições do vetor anula_area o que foi lido da memória FLASH
	{

		if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_ANULA_AREAS + x + offSetNumeroSerie], VALOR_BINARIO, 0, 1))	return 67;
	}

	//FILTRO DE RUÍDO
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_FILTRO_RUIDO + offSetNumeroSerie], VALOR_BINARIO, 0, 15))	return 68; //Armazena na variável filtroruido o que foi lido da memória FLASH

	//TRAVA INTELIGENTE
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_TRAVA_INTELIGENTE + offSetNumeroSerie], VALOR_BINARIO, 0 ,1))	return 69; //Armazena na variável trava_inteligente o que foi lido da memória FLASH

	//TIPO DE DETECTOR
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_TIPO_DETECTOR + offSetNumeroSerie], VALOR_BINARIO, 1, 2))	return 70;  //Armazena na variável tipo_detector o que foi lido da memória FLASH

	//PONTEIROS DOS LOG DE AUDITORIAS


	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_PONTEIRO_BLOCO_A + offSetNumeroSerie], VALOR_BINARIO, 0, 43))	return 71;
	//Remonta os 2 bytes separados na memória FLASH para a variável ponteiro do bloco de auditoria
		// A soma dos valores nao pode ser maior que 4092
	if((((int)(Read_Buffer_FLASH[OFFSET_PONTEIRO_BYTES_A + offSetNumeroSerie] * 256)) +
			((int)Read_Buffer_FLASH[OFFSET_PONTEIRO_BYTES_A + 1 + offSetNumeroSerie])) > 4092){
		return 72;
	}

	//PONTEIROS DOS LOG DE EVENTOS

	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_PONTEIRO_BLOCO_L + offSetNumeroSerie], VALOR_BINARIO, 1, 4))	return 73;
	//Remonta os 2 bytes separados na memória FLASH para a variável ponteiro do bloco de eventos
		// A soma dos valores nao pode ser maior que 4096
	if((((int)(Read_Buffer_FLASH[OFFSET_PONTEIRO_BYTES_L + offSetNumeroSerie] * 256)) +
			((int)Read_Buffer_FLASH[OFFSET_PONTEIRO_BYTES_L + 1 + offSetNumeroSerie])) > 4096){
		return 74;
	}

	//ELIMINAR FALHA DA BOBINA
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_FALHA_DA_BOBINA + offSetNumeroSerie], VALOR_BINARIO,0,1))	return 75; //Armazena na variável tipo_detector o que foi lido da memória FLASH

	for(x = 0;x < 15;x++)
	{
		if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_ENDERECO_IP + x + offSetNumeroSerie], ASCII_NUMERICO,0,0))	return (76+x);
	}

	for(x = 0;x < 15;x++)
	{
		if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_ENDERECO_SUB_REDE + x + offSetNumeroSerie], ASCII_NUMERICO,0,0))	return (91+x);
	}

	for(x = 0;x < 15;x++)
	{
		if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_ENDERECO_GATEWAY + x + offSetNumeroSerie], ASCII_NUMERICO,0,0))	return (106+x);
	}

	for(x = 0;x < 15;x++)
	{
		if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_ENDERECO_DNS + x + offSetNumeroSerie], ASCII_NUMERICO,0,0))	return (121+x);
	}

	//INDICE_EVENTOS_GRAVADOS

	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_INDICE_EVENTOS_GRAVADOS + offSetNumeroSerie], VALOR_BINARIO,0, 255))	return 136;
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_INDICE_EVENTOS_GRAVADOS+ 1 + offSetNumeroSerie], VALOR_BINARIO,0, 255))	return 137;

	//INDICE_AUDITORIAS_GRAVADOS

	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_INDICE_AUDITORIAS_GRAVADOS + offSetNumeroSerie], VALOR_BINARIO,0, 255))	return 138;
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_INDICE_AUDITORIAS_GRAVADOS+ 1 + offSetNumeroSerie], VALOR_BINARIO,0, 255))	return 139;

	//PORTA AUTOMÁTICA
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_PORTA_AUTOMATICA + offSetNumeroSerie], VALOR_BINARIO,0, 1))	return 140;

	//OPÇÃO SENSOR CONTADOR
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_OPCAO_SENSOR_CONTADOR + offSetNumeroSerie], VALOR_BINARIO,0, 2))	return 141;


	//MODO ETHERNET
	if(checaSeValorValidoMemoria(Read_Buffer_FLASH[OFFSET_OPCAO_MODO_ETHERNET + offSetNumeroSerie], VALOR_BINARIO,1, 3))	return 142;

	return 0;

}


void LE_FLASH_INTERNA(dword endereco,word numero_dados) //Função que lê os dados da memória FLASH
{
	static volatile word x1 = 0; //Define a variável x para zero

	Cpu_DisableInt(); //Desabilita as interrupções

	for(x1 = 0;x1 < numero_dados;x1++) //Lê uma quantidade de dados passados para a função em número_dados da memória FLASH e põe no vetor Read_Buffer_FLASH
	{
		FLASH_INTERNA_GetByteFlash(endereco + x1,&Read_Buffer_FLASH[x1]);
	}

	Cpu_EnableInt(); //Habilita as interrupções
}

void ESCREVE_FLASH_INTERNA(dword endereco,word numero_dados, byte block_number) //Função que escreve os dados na memória FLASH
{
	static volatile word x1 = 0; //Define a variável x para zero
	static volatile dword aux_endereco; //Define a variável aux_endereco para auxiliar no cálculo do endereço
	static volatile dword address; //Define a variável address para especificar o endereço e o bloco que será gravado

	if(!TRAVA_LIGADA){
		  LIGA_TRAVA;
		  pwm_trava = 0;
	}else pwm_trava = 0;
	Cpu_DisableInt(); //Desabilita as interrupções

	address = END_INI_PARAMETROS + (block_number * 0x1000); //Armazena address com o valor (0x43000 + (0 * 0x1000)) = 0x43000

	for(x1 = 0;x1 < 4096;x1++) //Lê os 4096 bytes do bloco para salvar na RAM pois o método de escrita é destructive write with erase
	{
		FLASH_INTERNA_GetByteFlash(address + x1,&Read_Buffer_FLASH[x1]);
	}

	aux_endereco = endereco - address; //Armazena na variável aux_endereco o valor (endereco - address) que é o endereço passado na função - 0x8300. Exemplo 0x83012 - 0x83000 = 0x12 = 18 em decimal

	for(x1 = 0;x1 < numero_dados;x1++) //Coloca a quantidade de dados a ser gravada no vetor Read_Buffer_FLASH
	{
		Read_Buffer_FLASH[aux_endereco + x1] = Write_Buffer_FLASH[x1];
	}

	FLASH_INTERNA_SetBlockFlash(&Read_Buffer_FLASH[0],address,4096); //Grava os 4096 bytes no bloco de memória especificado na memória FLASH

	Cpu_EnableInt(); //Habilita as interrupções
}


/******************************************************************************/

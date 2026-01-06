/*
 * agata_std_functions.h
 *
 *  Created on: 21/06/2023
 *      Author: marcos.butignol
 *
 *  210623 - agata_std_functions.c criado para funcoes auxiliares e aliviar, provisoriamente
 *  			o arquivo funcao.c
 *  		A ideia sera criar funcoes basicas, tais como loops e rotinas padroes para diminuir
 *  		  	o tamanho de funcao.c
 */


#ifndef SOURCES_AGATA_STD_FUNCTIONS_H_
#define SOURCES_AGATA_STD_FUNCTIONS_H_


struct parametrosAgata{

	char sensibilidade[8];
	char anulaAreas[8];
	unsigned char canal;
	unsigned char filtroRuido;
	unsigned char sinalRele;
	unsigned char pulsoRele;
	unsigned char sinalTrava;
	unsigned char pulsoTrava;
	unsigned char modoTravamento;
	unsigned char selecaoMetais;
	unsigned char volumeVoz;
	unsigned char volumeBuzzer;
	unsigned char tomBuzzer;
};

typedef struct parametrosAgata ParametrosAgata;

typedef enum {
  EthernetEnviaPacote,
  EthernetDescartaAnterior,
  EthernetResetModulo
} TipoProcessoEthernet;


void volatile_memset(volatile char *buffer, char caractere, int tamanhoBuffer);

void array_char_append(char *bufferToBeApp, const char charToAppend, int bufferSize);

void volatile_array_char_append(volatile char bufferToBeApp[], const char charToAppend, int bufferSize);

int  agataIsValidNumber(char *characterArray, int dataType);

void removeChar(char *str, char garbage);

int agataChecaSerialValido(unsigned char *numeroSerial);

void AtribuiParametrosAgataParaWriteBuffer(ParametrosAgata paramAgata, char *bufferGravar);



#endif /* SOURCES_FUNCAO_H_ */

/*
 * agata_std_functions.c
 *
 *  Created on: 21/06/2023
 *      Author: marcos.butignol
 *
 *      Ver agata_std_functions.h
 *
 */

#include "agata_std_functions.h"
#include "agata_hc_definitions.h"

#include "stdlib.h"
#include "string.h"

//DESCONTINUADO
void volatile_memset(volatile char *buffer, char caractere, int tamanhoBuffer){
	int i=0;
	for(i=0;i<tamanhoBuffer;i++){
		buffer[tamanhoBuffer]=caractere;
	}
}

//DESCONTINUADO
int volatile_char_array_tok(volatile char *bufferTo, volatile char *bufferFrom, const char delimChar, int maxSearch){
	int i=0;
	int j=0;
	char tempChar;
	for(i=0;i<=maxSearch;i++){
		if(*(bufferFrom+i)==delimChar){
			i=j;
			i=maxSearch+1;
		}
		if(*(bufferFrom+i)==0){
			return -1;
		}
		if(i==maxSearch){
			return 1;
		}
	}
	for(i=0;i<j;i++){
		tempChar = *(bufferFrom+i);
		*(bufferTo+i)=tempChar;
	}
	return 0;

}

//DESCONTINUADO
void array_char_append(char *bufferToBeApp, const char charToAppend, int bufferSize){

	int i=0;

	for(i=0;i<bufferSize;i++){
		if(bufferToBeApp[i]==0){
			bufferToBeApp[i] = charToAppend;
			i=bufferSize;
		}

	}
	return;
}

//DESCONTINUADO
void volatile_array_char_append(volatile char bufferToBeApp[], const char charToAppend, int bufferSize){

	int i=0;

	for(i=0;i<bufferSize;i++){
		if(bufferToBeApp[i]==0){
			bufferToBeApp[i] = charToAppend;
			i=bufferSize;
		}

	}
	return;
}

/* int agataIsValidNumber(char *characterArray, int dataType)
 * 		Função que checa se o dado do campo e valido para a variavel
 *
 * 		char *characterArray		- String do dado recebido
 * 		int dataType				- Tipo de dado
 *
 * 		retorna 0 (nao valido) ou 1 (dado valido)
*/
int agataIsValidNumber(char *characterArray, int dataType){
	int tempValue;
	if(*characterArray == ' '){
		characterArray++;
	}

	if(*characterArray<'0' || *characterArray>'9'){
		return 0;
	}


	tempValue=atoi(characterArray);

	switch(dataType){
	case DadoMdTravamento:
		if(tempValue>=1 && tempValue<=2) return 1;
		break;
	case DadoCanal:
		if(tempValue>=0 && tempValue<=10) return 1;
		break;
	case DadoSlMetal:
		if(tempValue>=1 && tempValue<=100) return 1;
		break;
	case DadoSnTrava:
		if(tempValue>=1 && tempValue<=3) return 1;
		break;
	case DadoPlTrava:
		if(tempValue>=1 && tempValue<=50) return 1;
		break;
	case DadoSnRele:
		if(tempValue>=1 && tempValue<=2) return 1;
		break;
	case DadoPlRele:
		if(tempValue>=1 && tempValue<=150) return 1;
		break;
	case DadoFlRuido:
		if(tempValue>=0 && tempValue<=15) return 1;
		break;
	case DadoTmBuzzer:
		if(tempValue>=1 && tempValue<=10) return 1;
		break;
	case DadoVlBuzzer:
	case DadoVlVoz:
		if(tempValue>=0 && tempValue<=10) return 1;
		break;
	case DadoSnZona1:
	case DadoSnZona2:
	case DadoSnZona3:
	case DadoSnZona4:
	case DadoSnZona5:
	case DadoSnZona6:
	case DadoSnZona7:
	case DadoSnZona8:
	case DadoSnZonaDefault:
		if(tempValue>=1 && tempValue<=100) return 1;
		break;
	case DadoAnZona1:
	case DadoAnZona2:
	case DadoAnZona3:
	case DadoAnZona4:
	case DadoAnZona5:
	case DadoAnZona6:
	case DadoAnZona7:
	case DadoAnZona8:
	case DadoAnZonaDefault:
		if(tempValue>=0 && tempValue<=1) return 1;
		break;
	case DadoTsAgata:
		if(tempValue>=10 && tempValue<=2147483647) return 1;
		break;
	case DadoSwUser:
		if(tempValue>=0 && tempValue<=255) return 1;
		break;
	default:
		break;
	}
	return 0;
}


/* void removeChar(char *str, char garbage)
 * 		Função que remove o caractere selecionado de uma string
 *
 * 		char *str			- String da mensagem
 * 		char garbage		- Caractere a ser removido
 *
 * 	sem retorno
*/
void removeChar(char *str, char garbage) {

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != garbage) dst++;
    }
    *dst = '\0';
}


int agataChecaSerialValido(unsigned char *numeroSerial){
	/*	DESCONTINUADO
	unsigned char numeroSerialTemp[6];
	int somatoriaParidadeDecimal = 0;

	strncpy(numeroSerialTemp,numeroSerial,6);

	for (int i = 0; i<6 ; i++){
		if(numeroSerialTemp[i]<'0' && numeroSerialTemp[i]>'9'){
			return 1;
		}
	}

	for (int j=0; j<5 ; j++){
		somatoriaParidadeDecimal = somatoriaParidadeDecimal+(numeroSerialTemp[j]-'0');
	}
	if( ((unsigned char)somatoriaParidadeDecimal)%10 != (numeroSerialTemp[5]-'0')){
		return 2;
	}
	*/
	return 0;

}


void AtribuiParametrosAgataParaWriteBuffer(ParametrosAgata paramAgata, char *bufferGravar){

	strncat(bufferGravar,paramAgata.sensibilidade, sizeof(paramAgata.sensibilidade));
	strncat(bufferGravar,paramAgata.anulaAreas, sizeof(paramAgata.anulaAreas));
	strncat(bufferGravar,&paramAgata.modoTravamento,sizeof(char));
	strncat(bufferGravar,&paramAgata.canal, sizeof(char));
	strncat(bufferGravar,&paramAgata.selecaoMetais,sizeof(char));
	strncat(bufferGravar,&paramAgata.pulsoTrava,sizeof(char));
	strncat(bufferGravar,&paramAgata.sinalTrava,sizeof(char));
	strncat(bufferGravar,&paramAgata.pulsoRele,sizeof(char));
	strncat(bufferGravar,&paramAgata.sinalRele,sizeof(char));
	//NÚMERO DE CONTROLES
	//SENSIBILIDADE IR
	//ANÁLISE IR
	//FÁBRICA
	//IDIOMA

	//BUZZER [3]
	//MENSAGEM DE VOZ [2]

	//ALARME VISUAL
	//CONTADOR DE BLOQUEIOS
	//CONTADOR DE DESBLOQUEIOS
	//CONTADOR DE PASSAGENS - ENTRADAS
	//CONTADOR DE PASSAGENS - SAIDAS
	//CONTADOR DE PASSAGENS - ENTRADAS DIARIAS
	//CONTADOR DE PASSAGENS - SAIDAS DIARIAS
	//CONFERENCIA DO DIA
	//PERFIL
	//AJUSTES TX-RX
	//MODELO DE ANTENA
	//POTENCIÔMETROS DE GANHO
	//POTENCIÔMETROS DE SELEÇÃO
	//ANULA ÁREAS
	strncat(bufferGravar,&paramAgata.filtroRuido,sizeof(char));
	strncat(bufferGravar,&paramAgata.sinalRele,sizeof(char));
	strncat(bufferGravar,&paramAgata.pulsoRele,sizeof(char));
	strncat(bufferGravar,&paramAgata.sinalTrava,sizeof(char));
	strncat(bufferGravar,&paramAgata.modoTravamento,sizeof(char));
	strncat(bufferGravar,&paramAgata.selecaoMetais,sizeof(char));
	strncat(bufferGravar,&paramAgata.volumeVoz,sizeof(char));
	strncat(bufferGravar,&paramAgata.volumeBuzzer,sizeof(char));
	strncat(bufferGravar,&paramAgata.tomBuzzer,sizeof(char));

	//Ou verificar tamanho da STRUCT e fazer
	//strncat(bufferGravar,paramAgata.sensibilidade, sizeof(TAMANHOTOTALDASTRUCT));
}



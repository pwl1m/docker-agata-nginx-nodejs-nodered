/*
 * funcoes_menu_informacoesenergia.c
 *
 *  Created on: 23/06/2023
 *      Author: marcos.butignol
 */


#include "funcao.h"

#include "agata_std_functions.h"
#include "agata_hc_definitions.h"
#include "stdlib.h"

void fnEncaminhaImprimeTelaInformacoesdeEnergia(word telaSwitch, dword *timer_tensoes_aux_ptr){

	if(*timer_tensoes_aux_ptr == timer_tensoes) //Atualiza a cada segundo os valores de tensão, 10 x 100ms = 1 segundo
	{
		SendCan(FONTE_CAN,GET_TENSOES); //Envia para FONTE para requisitar as tensões
		SendCan(FONTE_CAN,GET_TENSOES1); //Envia para FONTE para requisitar as tensões
		timer_tensoes = 0; //Zera o contador de tempo de timer_tensoes

		//ESCREVE A TENSÃO AC
		switch(telaSwitch){
		case TELA_TENSAO_AC:
			fnEscreveTensaoAC();
		break;

		//ESCREVE A TENSÃO DC de 5V, de 15 e de -15
		case TELA_TENSAO_DC:
			fnEscreveTensoesDC();
		break;

		//ESCREVE A TENSÃO DAS BATERIAS
		case TELA_TENSAO_DAS_BATERIAS:
			fnEscreveTensaoBateria();
		break;
		}
	}
	else if(telaSwitch == TELA_TENSAO_24V) //Senão se tela é igual a TELA_TENSAO_DAS_BATERIAS
	{
		fnEscreveTensaoFonte();

	}
}


//ESCREVE A TENSÃO AC
void  fnEscreveTensaoAC(void){
	if(var_tensao_rede/100) //Se var_tensao_rede tiver 3 digitos então
		{
			LINHA = 2; //Se posiciona na linha 2
			COLUNA = 7; //Se posiciona na coluna 2
			PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
			EscreveChar(' '); //Escreve espaço
			EscreveChar((var_tensao_rede/100)+48); //Escreve a parte da centena de var_tensao_rede
			EscreveChar(((var_tensao_rede%100)/10)+48); //Escreve a parte da dezena de var_tensao_rede
			EscreveChar((var_tensao_rede%10)+48); //Escreve a parte da unidade de var_tensao_rede
			EscreveChar(' '); //Escreve espaço
		}
		else if((var_tensao_rede%100)/10) //Senão se var_tensao_rede tiver 2 digitos então
		{
			LINHA = 2; //Se posiciona na linha 2
			COLUNA = 7; //Se posiciona na coluna 2
			PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
			EscreveChar(' '); //Escreve espaço
			EscreveChar(' '); //Escreve espaço
			EscreveChar((var_tensao_rede/10)+48); //Escreve a parte da dezena de var_tensao_rede
			EscreveChar((var_tensao_rede%10)+48); //Escreve a parte da unidade de var_tensao_rede
			EscreveChar(' '); //Escreve espaço
		}
		else if(var_tensao_rede%10) //Senão se var_tensao_rede tiver 1 digitos então
		{
			LINHA = 2; //Se posiciona na linha 2
			COLUNA = 7; //Se posiciona na coluna 2
			PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
			EscreveChar(' '); //Escreve espaço
			EscreveChar(' '); //Escreve espaço
			EscreveChar((var_tensao_rede%10)+48); //Escreve a parte da unidade de var_tensao_rede
			EscreveChar(' '); //Escreve espaço
			EscreveChar(' '); //Escreve espaço
		}
		else if(!var_tensao_rede) //Senão se var_tensao_rede for zero então
		{
			LINHA = 2; //Se posiciona na linha 2
			COLUNA = 7; //Se posiciona na coluna 2
			PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
			EscreveChar(' '); //Escreve espaço
			EscreveChar(' '); //Escreve espaço
			EscreveChar('0'); //Escreve zero
			EscreveChar(' '); //Escreve espaço
			EscreveChar(' '); //Escreve espaço
		}

}

//ESCREVE TENSOES DC

void  fnEscreveTensoesDC(void){
	if(var_tensao_cinco/10) //Se var_tensao_cinco tiver 2 digitos então
	{
		LINHA = 2; //Se posiciona na linha 2
		COLUNA = 2; //Se posiciona na coluna 2
		PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
		EscreveChar((var_tensao_cinco/10) + 48); //Escreve a parte da unidade de var_tensao_cinco
		EscreveChar('.'); //Escreve o ponto
		EscreveChar((var_tensao_cinco%10) + 48); //Escreve a parte depois da virgula de var_tensao_cinco
	}
	else if(var_tensao_cinco%10) //Senão se var_tensao_cinco tiver 1 digitos então
	{
		LINHA = 2; //Se posiciona na linha 2
		COLUNA = 2; //Se posiciona na coluna 2
		PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
		EscreveChar('0'); //Escreve zero
		EscreveChar('.'); //Escreve o ponto
		EscreveChar(var_tensao_cinco + 48); //Escreve a parte depois da virgula de var_tensao_cinco
	}
	else if(!var_tensao_cinco) //Senão se var_tensao_cinco for zero então
	{
		LINHA = 2; //Se posiciona na linha 2
		COLUNA = 2; //Se posiciona na coluna 2
		PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
		EscreveChar('0'); //Escreve zero
		EscreveChar('.'); //Escreve o ponto
		EscreveChar('0'); //Escreve zero
	}
	//ESCREVE A TENSÂO DC DE 15V
	if(var_tensao_quinze/100) //Se var_tensao_quinze tiver 3 digitos então
	{
		LINHA = 2; //Se posiciona na linha 2
		COLUNA = 6; //Se posiciona na coluna 2
		PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
		EscreveChar((var_tensao_quinze/100) + 48); //Escreve a parte da dezena de var_tensao_quinze
		EscreveChar(((var_tensao_quinze%100)/10) + 48); //Escreve a parte da unidade de var_tensao_quinze
		EscreveChar('.'); //Escreve o ponto
		EscreveChar((var_tensao_quinze%10) + 48); //Escreve a parte depois da virgula de var_tensao_quinze
	}
	else if((var_tensao_quinze%100)/10) //Senão se var_tensao_quinze tiver 2 digito então
	{
		LINHA = 2; //Se posiciona na linha 2
		COLUNA = 6; //Se posiciona na coluna 2
		PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
		EscreveChar(' '); //Escreve espaço
		EscreveChar((var_tensao_quinze/10) + 48); //Escreve a parte da unidade de var_tensao_quinze
		EscreveChar('.'); //Escreve o ponto
		EscreveChar((var_tensao_quinze%10) + 48); //Escreve a parte depois da virgula de var_tensao_quinze
	}
	else if(var_tensao_quinze%10) //Senão se var_tensao_quinze tiver 1 digito então
	{
		LINHA = 2; //Se posiciona na linha 2
		COLUNA = 6; //Se posiciona na coluna 2
		PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
		EscreveChar(' '); //Escreve espaço
		EscreveChar('0'); //Escreve zero
		EscreveChar('.'); //Escreve ponto
		EscreveChar(var_tensao_quinze + 48); //Escreve a parte depois da virgula de var_tensao_quinze
	}
	else if(!var_tensao_quinze) //Senão se var_tensao_quinze for zero então
	{
		LINHA = 2; //Se posiciona na linha 2
		COLUNA = 6; //Se posiciona na coluna 2
		PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
		EscreveChar(' '); //Escreve espaço
		EscreveChar('0'); //Escreve zero
		EscreveChar('.'); //Escreve ponto
		EscreveChar('0'); //Escreve zero
	}
	//ESCREVE A TENSÃO DC DE -15V
	if(var_tensao_menos_quinze/100) //Se var_tensao_menos_quinze tiver 3 digitos então
	{
		LINHA = 2; //Se posiciona na linha 2
		COLUNA = 11; //Se posiciona na coluna 11
		PosicionaLCD(pos); //Posiciona o cursor na linha e coluna desejada
		EscreveChar('-'); //Escreve menos
		EscreveChar((var_tensao_menos_quinze/100) + 48); //Escreve a parte da dezena de var_tensao_menos_quinze
		EscreveChar(((var_tensao_menos_quinze%100)/10) + 48); //Escreve a parte da unidade de var_tensao_menos_quinze
		EscreveChar('.'); //Escreve ponto
		EscreveChar((var_tensao_menos_quinze%10) + 48); //Escreve a parte depois da virgula de var_tensao_menos_quinze
	}
	else if((var_tensao_menos_quinze%100)/10) //Senão se var_tensao_menos_quinze tiver 2 digitos então
	{
		LINHA = 2; //Se posiciona na linha 2
		COLUNA = 11; //Se posiciona na coluna 11
		PosicionaLCD(pos); //Posiciona o cursor na linha e coluna desejada
		EscreveChar('-'); //Escreve menos
		EscreveChar((var_tensao_menos_quinze/10) + 48); //Escreve a parte da unidade de var_tensao_menos_quinze
		EscreveChar('.'); //Escreve ponto
		EscreveChar((var_tensao_menos_quinze%10) + 48); //Escreve a parte depois da virgula de var_tensao_menos_quinze
	}
	else if(var_tensao_menos_quinze%10) //Senão se var_tensao_menos_quinze tiver 1 digitos então
	{
		LINHA = 2; //Se posiciona na linha 2
		COLUNA = 11; //Se posiciona na coluna 11
		PosicionaLCD(pos); //Posiciona o cursor na linha e coluna desejada
		EscreveChar('-'); //Escreve menos
		EscreveChar('0'); //Escreve zero
		EscreveChar('.'); //Escreve ponto
		EscreveChar(var_tensao_menos_quinze + 48); //Escreve a parte depois da virgula de var_tensao_menos_quinze
	}
	else if(!var_tensao_menos_quinze) //Senão se var_tensao_menos_quinze for zero então
	{
		LINHA = 2; //Se posiciona na linha 2
		COLUNA = 11; //Se posiciona na coluna 11
		PosicionaLCD(pos); //Posiciona o cursor na linha e coluna desejada
		EscreveChar('-'); //Escreve menos
		EscreveChar('0'); //Escreve zero
		EscreveChar('.'); //Escreve ponto
		EscreveChar('0'); //Escreve zero
	}
}


void  fnEscreveTensaoBateria(void){
	if(var_tensao_bateria/100) //Se var_tensao_bateria tiver 3 digitos então
	{
		LINHA = 2; //Se posiciona na linha 2
		COLUNA = 6; //Se posiciona na coluna 6
		PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
		EscreveChar(' '); //Escreve espaço
		EscreveChar((var_tensao_bateria/100) + 48); //Escreve a parte da dezena de var_tensao_bateria
		EscreveChar(((var_tensao_bateria%100)/10) + 48); //Escreve a parte da unidade de var_tensao_bateria
		EscreveChar('.'); //Escreve ponto
		EscreveChar((var_tensao_bateria%10) + 48); //Escreve a parte depois da virgula de var_tensao_bateria
		EscreveChar(' '); //Escreve espaço
	}
	else if((var_tensao_bateria%100)/10) //Senão se var_tensao_bateria tiver 2 digitos então
	{
		LINHA = 2; //Se posiciona na linha 2
		COLUNA = 6; //Se posiciona na coluna 6
		PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
		EscreveChar(' '); //Escreve espaço
		EscreveChar(' '); //Escreve espaço
		EscreveChar(((var_tensao_bateria%100)/10) + 48); //Escreve a parte da unidade de var_tensao_bateria
		EscreveChar('.'); //Escreve ponto
		EscreveChar((var_tensao_bateria%10) + 48); //Escreve a parte depois da virgula de var_tensao_bateria
		EscreveChar(' '); //Escreve espaço
	}
	else if(var_tensao_bateria%10)//Senão se var_tensao_bateria tiver 1 digitos então
	{
		LINHA = 2; //Se posiciona na linha 2
		COLUNA = 6; //Se posiciona na coluna 6
		PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
		EscreveChar(' '); //Escreve espaço
		EscreveChar(' '); //Escreve espaço
		EscreveChar('0'); //Escreve zero
		EscreveChar('.'); //Escreve ponto
		EscreveChar((var_tensao_bateria%10) + 48); //Escreve a parte depois da virgula de var_tensao_bateria
		EscreveChar(' '); //Escreve espaço
	}

	else if(!var_tensao_bateria) //Senão se var_tensao_bateria for zero então
	{
		LINHA = 2; //Se posiciona na linha 2
		COLUNA = 6; //Se posiciona na coluna 6
		PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
		EscreveChar(' '); //Escreve espaço
		EscreveChar(' '); //Escreve espaço
		EscreveChar('0'); //Escreve zero
		EscreveChar('.'); //Escreve ponto
		EscreveChar('0'); //Escreve zero
		EscreveChar(' '); //Escreve espaço
	}
}


void fnEscreveTensaoFonte(void){

	if(var_tensao_chaveada/100) //Se var_tensao_bateria tiver 3 digitos então
	{
		LINHA = 2; //Se posiciona na linha 2
		COLUNA = 6; //Se posiciona na coluna 6
		PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
		EscreveChar(' '); //Escreve espaço
		EscreveChar((var_tensao_chaveada/100) + 48); //Escreve a parte da dezena de var_tensao_bateria
		EscreveChar(((var_tensao_chaveada%100)/10) + 48); //Escreve a parte da unidade de var_tensao_bateria
		EscreveChar('.'); //Escreve ponto
		EscreveChar((var_tensao_chaveada%10) + 48); //Escreve a parte depois da virgula de var_tensao_bateria
		EscreveChar(' '); //Escreve espaço
	}
	else if((var_tensao_chaveada%100)/10) //Senão se var_tensao_bateria tiver 2 digitos então
	{
		LINHA = 2; //Se posiciona na linha 2
		COLUNA = 6; //Se posiciona na coluna 6
		PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
		EscreveChar(' '); //Escreve espaço
		EscreveChar(' '); //Escreve espaço
		EscreveChar(((var_tensao_chaveada%100)/10) + 48); //Escreve a parte da unidade de var_tensao_bateria
		EscreveChar('.'); //Escreve ponto
		EscreveChar((var_tensao_chaveada%10) + 48); //Escreve a parte depois da virgula de var_tensao_bateria
		EscreveChar(' '); //Escreve espaço
	}
	else if(var_tensao_chaveada%10)//Senão se var_tensao_bateria tiver 1 digitos então
	{
		LINHA = 2; //Se posiciona na linha 2
		COLUNA = 6; //Se posiciona na coluna 6
		PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
		EscreveChar(' '); //Escreve espaço
		EscreveChar(' '); //Escreve espaço
		EscreveChar('0'); //Escreve zero
		EscreveChar('.'); //Escreve ponto
		EscreveChar((var_tensao_chaveada%10) + 48); //Escreve a parte depois da virgula de var_tensao_bateria
		EscreveChar(' '); //Escreve espaço
	}

	else if(!var_tensao_chaveada) //Senão se var_tensao_bateria for zero então
	{
		LINHA = 2; //Se posiciona na linha 2
		COLUNA = 6; //Se posiciona na coluna 6
		PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
		EscreveChar(' '); //Escreve espaço
		EscreveChar(' '); //Escreve espaço
		EscreveChar('0'); //Escreve zero
		EscreveChar('.'); //Escreve ponto
		EscreveChar('0'); //Escreve zero
		EscreveChar(' '); //Escreve espaço
	}

}

/*
 * funcoes_menu_diagnosticosistema.c
 *
 *  Created on: 23/06/2023
 *      Author: marcos.butignol
 */

#include "funcao.h"

#include "agata_std_functions.h"
#include "agata_hc_definitions.h"
#include "stdlib.h"

//ESCREVE A TENSÃO AC
void  fnTesteLeds(void){
	while(teclapressionada != teclaCancela) //Enquanto teclapressionada não for igual a tecla CANCELA então
	{
		DESLIGA_SINALEIRA_VERMELHA; //Desliga sinaleira vermelha
		DESLIGA_SINALEIRA_VERDE; //Desliga sinaleira verde
		DESLIGA_AC; //Desliga led AC
		DESLIGA_BAT; //Desliga led BAT
		APAGA_AREAS; //Apaga leds das áreas
		ACENDE_NIVEL0; //Apaga leds do bargraph

		delay_ms(200); //Espera 200 milisegundos
		if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
		{
			LIGA_SINALEIRA_VERDE; //Liga sinaleira verde
		}

		delay_ms(200); //Espera 200 milisegundos
		if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
		{
			DESLIGA_SINALEIRA_VERDE; //Desliga sinaleira verde
		}

		delay_ms(200); //Espera 200 milisegundos
		if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
		{
			LIGA_SINALEIRA_VERMELHA; //Liga sinaleira vermelha
		}

		delay_ms(200); //Espera 200 milisegundos
		if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
		{
			DESLIGA_SINALEIRA_VERMELHA; //Desliga sinaleira vermelha
		}

		delay_ms(200); //Espera 200 milisegundos
		if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
		{
			LIGA_AC; //Liga led AC
		}

		delay_ms(200); //Espera 200 milisegundos
		if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
		{
			DESLIGA_AC; //Desliga led AC
		}

		delay_ms(200); //Espera 200 milisegundos
		if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
		{
			LIGA_BAT; //Liga led BAT
		}

		delay_ms(200); //Espera 200 milisegundos
		if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
		{
			DESLIGA_BAT; //Desliga led BAT
		}

		delay_ms(200); //Espera 200 milisegundos
		if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
		{
			ACENDE_NIVEL1; //Acende leds até nivel 1 do bargraph
		}

		delay_ms(200); //Espera 200 milisegundos
		if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
		{
			ACENDE_NIVEL2; //Acende leds até nivel 2 do bargraph
		}

		delay_ms(200); //Espera 200 milisegundos
		if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
		{
			ACENDE_NIVEL3; //Acende leds até nivel 3 do bargraph
		}

		delay_ms(200); //Espera 200 milisegundos
		if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
		{
			ACENDE_NIVEL4; //Acende leds até nivel 4 do bargraph
		}

		delay_ms(200); //Espera 200 milisegundos
		if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
		{
			ACENDE_NIVEL5; //Acende leds até nivel 5 do bargraph
		}

		delay_ms(200); //Espera 200 milisegundos
		if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
		{
			ACENDE_NIVEL6; //Acende leds até nivel 6 do bargraph
		}

		delay_ms(200); //Espera 200 milisegundos
		if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
		{
			ACENDE_NIVEL7; //Acende leds até nivel 7 do bargraph
		}

		delay_ms(200); //Espera 200 milisegundos
		if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
		{
			ACENDE_NIVEL8; //Acende leds até nivel 8 do bargraph
		}

		delay_ms(200); //Espera 200 milisegundos
		if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
		{
			ACENDE_NIVEL9; //Acende leds até nivel 9 do bargraph
		}

		delay_ms(200); //Espera 200 milisegundos
		if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
		{
			ACENDE_NIVEL10; //Acende leds até nivel 10 do bargraph
		}

		delay_ms(200); //Espera 200 milisegundos
		if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
		{
			ACENDE_NIVEL9; //Acende leds até nivel 9 do bargraph
		}

		delay_ms(200); //Espera 200 milisegundos
		if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
		{
			ACENDE_NIVEL8; //Acende leds até nivel 8 do bargraph
		}

		delay_ms(200); //Espera 200 milisegundos
		if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
		{
			ACENDE_NIVEL7; //Acende leds até nivel 7 do bargraph
		}

		delay_ms(200); //Espera 200 milisegundos
		if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
		{
			ACENDE_NIVEL6; //Acende leds até nivel 6 do bargraph
		}

		delay_ms(200); //Espera 200 milisegundos
		if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
		{
			ACENDE_NIVEL5; //Acende leds até nivel 5 do bargraph
		}

		delay_ms(200); //Espera 200 milisegundos
		if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
		{
			ACENDE_NIVEL4; //Acende leds até nivel 4 do bargraph
		}

		delay_ms(200); //Espera 200 milisegundos
		if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
		{
			ACENDE_NIVEL3; //Acende leds até nivel 3 do bargraph
		}

		delay_ms(200); //Espera 200 milisegundos
		if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
		{
			ACENDE_NIVEL2; //Acende leds até nivel 2 do bargraph
		}

		delay_ms(200); //Espera 200 milisegundos
		if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
		{
			ACENDE_NIVEL1; //Acende leds até nivel 1 do bargraph
		}

		delay_ms(200); //Espera 200 milisegundos
		if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
		{
			ACENDE_NIVEL0; //Apaga leds do bargraph
		}

		if(tipo_detector == Z3)
		{
			delay_ms(200); //Espera 200 milisegundos
			if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
			{
				ACENDE_AREA1; //Acende led da área 1
				ACENDE_AREA2; //Acende led da área 2
			}

			delay_ms(200); //Espera 200 milisegundos
			if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
			{
				APAGA_AREAS; //Apaga áreas
			}

			delay_ms(200); //Espera 200 milisegundos
			if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
			{
				ACENDE_AREA4; //Acende led da área 4
				ACENDE_AREA5; //Acende led da área 5
			}

			delay_ms(200); //Espera 200 milisegundos
			if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
			{
				APAGA_AREAS; //Apaga áreas
			}

			delay_ms(200); //Espera 200 milisegundos
			if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
			{
				ACENDE_AREA7; //Acende led da área 7
				ACENDE_AREA8; //Acende led da área 8
			}

			delay_ms(200); //Espera 200 milisegundos
			if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
			{
				APAGA_AREAS; //Apaga áreas
			}
		}
		else if(tipo_detector == Z8)
		{
			delay_ms(200); //Espera 200 milisegundos
			if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
			{
				ACENDE_AREA1; //Acende led da área 1
			}

			delay_ms(200); //Espera 200 milisegundos
			if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
			{
				APAGA_AREAS; //Apaga áreas
			}

			delay_ms(200); //Espera 200 milisegundos
			if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
			{
				ACENDE_AREA2; //Acende led da área 2
			}

			delay_ms(200); //Espera 200 milisegundos
			if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
			{
				APAGA_AREAS; //Apaga áreas
			}

			delay_ms(200); //Espera 200 milisegundos
			if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
			{
				ACENDE_AREA3; //Acende led da área 3
			}

			delay_ms(200); //Espera 200 milisegundos
			if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
			{
				APAGA_AREAS; //Apaga áreas
			}

			delay_ms(200); //Espera 200 milisegundos
			if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
			{
				ACENDE_AREA4; //Acende led da área 4
			}

			delay_ms(200); //Espera 200 milisegundos
			if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
			{
				APAGA_AREAS; //Apaga áreas
			}

			delay_ms(200); //Espera 200 milisegundos
			if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
			{
				ACENDE_AREA5; //Acende led da área 5
			}

			delay_ms(200); //Espera 200 milisegundos
			if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
			{
				APAGA_AREAS; //Apaga áreas
			}

			delay_ms(200); //Espera 200 milisegundos
			if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
			{
				ACENDE_AREA6; //Acende led da área 6
			}

			delay_ms(200); //Espera 200 milisegundos
			if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
			{
				APAGA_AREAS; //Apaga áreas
			}

			delay_ms(200); //Espera 200 milisegundos
			if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
			{
				ACENDE_AREA7; //Acende led da área 7
			}

			delay_ms(200); //Espera 200 milisegundos
			if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
			{
				APAGA_AREAS; //Apaga áreas
			}

			delay_ms(200); //Espera 200 milisegundos
			if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
			{
				ACENDE_AREA8; //Acende led da área 8
			}

			delay_ms(200); //Espera 200 milisegundos
			if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
			{
				APAGA_AREAS; //Apaga áreas
			}
		}
	}
	teclapressionada = 0; //Limpa teclapressionada
	DESLIGA_AC; //Desliga led AC
	DESLIGA_BAT; //Desliga led BAT
	LIGA_SINALEIRA_VERMELHA; //Liga sinaleira vermelha
	ACENDE_NIVEL0; //Apaga leds do bargraph
	APAGA_AREAS; //Apaga áreas

}

void fnTesteTrava(void){
	while(teclapressionada != teclaCancela) //Enquanto teclapressionada não for igual a tecla CANCELA então
	{
		LIGA_TRAVA; //Energiza trava
		delay_segundos(1); //Espera 1 segundo
		DESLIGA_TRAVA; //Desenergiza trava
		delay_segundos(1); //Espera 1 segundo
	}
	LIGA_TRAVA; //Liga trava
	teclapressionada = 0; //Limpa teclapressionada
}

void fnTesteRele(void){
	while(teclapressionada != teclaCancela) //Enquanto teclapressionada não for igual a tecla CANCELA então
	{
		LIGA_RELE; //Energiza relé
		delay_segundos(1); //Espera 1 segundo
		DESLIGA_RELE; //Desenergiza relé
		delay_segundos(1); //Espera 1 segundo
	}
	LIGA_RELE; //Energiza relé
	teclapressionada = 0; //Limpa teclapressionada
}


void fnTesteBuzzer(void){
	while(teclapressionada != teclaCancela) //Enquanto teclapressionada não for igual a tecla CANCELA então
	{
		TocaTomBuzzer(); //Toca tom do buzzer
		delay_segundos(1); //Espera 1 segundo
		TocaTomBuzzer(); //Toca tom do buzzer
		delay_segundos(1); //Espera 1 segundo
	}
	teclapressionada = 0; //Limpa teclapressionada

}

//TODO remove rest
void fnTesteMsgVoz(void){
	while(teclapressionada != teclaCancela) //Enquanto teclapressionada não for igual a tecla CANCELA então
	{
		SINAL_MSG_CLEAR; //Emite msg de voz
		//delay_segundos(5); //Espera 2 segundos
		delay_ms(75); //TODO delete
		fnCortaMsgVoz(); //Corta mensagem de voz
//		delay_segundos(1); //Espera 1 sergundo
//		SINAL_MSG_CLEAR; //Emite msg de voz
//		delay_segundos(5); //Espera 2 segundos
//		fnCortaMsgVoz(); //Corta mensagem de voz
		delay_segundos(3); //TODO delete
	}
	delay_segundos(2); //Espera 2 segundos
	if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
	{
		if(FLAG_PLACA_OUT_2022){
			SINAL_MSG_SET;//NOTA: Na placa de 2022 o sinal para acionamento da voz esta invertido
		}	else{
			SINAL_MSG_CLEAR; //Emite msg de voz
		}
	}
	if(FLAG_PLACA_OUT_2022){
		SINAL_MSG_CLEAR;//NOTA: Na placa de 2022 o sinal para acionamento da voz esta invertido
	}	else{
		SINAL_MSG_SET; //Desliga msg de voz
	}
	teclapressionada = 0; //Limpa teclapressionada
}

//TODO remove below
void fnTesteMsgVoz1(void){
	while(teclapressionada != teclaCancela) //Enquanto teclapressionada não for igual a tecla CANCELA então
	{
		SINAL_MSG_CLEAR; //Emite msg de voz
		//delay_segundos(5); //Espera 2 segundos
		delay_ms(150); //TODO delete
		fnCortaMsgVoz(); //Corta mensagem de voz
//		delay_segundos(1); //Espera 1 sergundo
//		SINAL_MSG_CLEAR; //Emite msg de voz
//		delay_segundos(5); //Espera 2 segundos
//		fnCortaMsgVoz(); //Corta mensagem de voz
		delay_segundos(3); //TODO delete
	}
	delay_segundos(2); //Espera 2 segundos
	if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
	{
		if(FLAG_PLACA_OUT_2022){
			SINAL_MSG_SET;//NOTA: Na placa de 2022 o sinal para acionamento da voz esta invertido
		}	else{
			SINAL_MSG_CLEAR; //Emite msg de voz
		}
	}
	if(FLAG_PLACA_OUT_2022){
		SINAL_MSG_CLEAR;//NOTA: Na placa de 2022 o sinal para acionamento da voz esta invertido
	}	else{
		SINAL_MSG_SET; //Desliga msg de voz
	}
	teclapressionada = 0; //Limpa teclapressionada
}

//TODO remove below
void fnTesteMsgVoz2(void){
	while(teclapressionada != teclaCancela) //Enquanto teclapressionada não for igual a tecla CANCELA então
	{
		SINAL_MSG_CLEAR; //Emite msg de voz
		//delay_segundos(5); //Espera 2 segundos
		delay_ms(225); //TODO delete
		fnCortaMsgVoz(); //Corta mensagem de voz
//		delay_segundos(1); //Espera 1 sergundo
//		SINAL_MSG_CLEAR; //Emite msg de voz
//		delay_segundos(5); //Espera 2 segundos
//		fnCortaMsgVoz(); //Corta mensagem de voz
		delay_segundos(3); //TODO delete
	}
	delay_segundos(2); //Espera 2 segundos
	if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
	{
		if(FLAG_PLACA_OUT_2022){
			SINAL_MSG_SET;//NOTA: Na placa de 2022 o sinal para acionamento da voz esta invertido
		}	else{
			SINAL_MSG_CLEAR; //Emite msg de voz
		}
	}
	if(FLAG_PLACA_OUT_2022){
		SINAL_MSG_CLEAR;//NOTA: Na placa de 2022 o sinal para acionamento da voz esta invertido
	}	else{
		SINAL_MSG_SET; //Desliga msg de voz
	}
	teclapressionada = 0; //Limpa teclapressionada
}

//TODO remove below
void fnTesteMsgVoz3(void){
	while(teclapressionada != teclaCancela) //Enquanto teclapressionada não for igual a tecla CANCELA então
	{
		SINAL_MSG_CLEAR; //Emite msg de voz
		//delay_segundos(5); //Espera 2 segundos
		delay_ms(300); //TODO delete
		fnCortaMsgVoz(); //Corta mensagem de voz
//		delay_segundos(1); //Espera 1 sergundo
//		SINAL_MSG_CLEAR; //Emite msg de voz
//		delay_segundos(5); //Espera 2 segundos
//		fnCortaMsgVoz(); //Corta mensagem de voz
		delay_segundos(3); //TODO delete
	}
	delay_segundos(2); //Espera 2 segundos
	if(teclapressionada != teclaCancela) //Se teclapressionada não for igual a tecla CANCELA então
	{
		if(FLAG_PLACA_OUT_2022){
			SINAL_MSG_SET;//NOTA: Na placa de 2022 o sinal para acionamento da voz esta invertido
		}	else{
			SINAL_MSG_CLEAR; //Emite msg de voz
		}
	}
	if(FLAG_PLACA_OUT_2022){
		SINAL_MSG_CLEAR;//NOTA: Na placa de 2022 o sinal para acionamento da voz esta invertido
	}	else{
		SINAL_MSG_SET; //Desliga msg de voz
	}
	teclapressionada = 0; //Limpa teclapressionada
}

void fnTesteTeclado(void){
	while(teclapressionada != teclaCancela) //Enquanto teclapressionada não for igual a tecla CANCELA então
	{
		if(teclapressionada == teclaConfirma || teclapressionada == teclaConfirma_Remoto) //Se teclapressionada for igual a tecla CONFIRMA então
		{
			LimpaLCD(); //Limpa LCD
			LINHA = 1; //Se posiciona na linha 1
			COLUNA = 1; //Se posiciona na coluna 1
			EscreveLCD((telas_LCD[TELA_CONFIRMA][idioma]),pos); //Escreve CONFIRMA na tela
			teclapressionada = 0; //Limpa teclapressionada
		}
		else if(teclapressionada == teclaIncrementa) //Senão se teclapressionada for igual a tecla CONFIRMA então
		{
			LimpaLCD(); //Limpa LCD
			LINHA = 1; //Se posiciona na linha 1
			COLUNA = 1; //Se posiciona na coluna 1
			EscreveLCD((telas_LCD[TELA_INCREMENTA][idioma]),pos); //Escreve INCREMENTA na tela
			teclapressionada = 0; //Limpa teclapressionada
		}
		else if(teclapressionada == teclaDecrementa) //Senão se teclapressionada for igual a tecla CONFIRMA então
		{
			LimpaLCD(); //Limpa LCD
			LINHA = 1; //Se posiciona na linha 1
			COLUNA = 1; //Se posiciona na coluna 1
			EscreveLCD((telas_LCD[TELA_DECREMENTA][idioma]),pos); //Escreve DECREMENTA na tela
			teclapressionada = 0; //Limpa teclapressionada
		}
	}
	teclapressionada = 0; //Limpa teclapressionada
	LimpaLCD(); //Limpa LCD
	LINHA = 1; //Se posiciona na linha 1
	COLUNA = 1; //Se posiciona na coluna 1
	EscreveLCD((telas_LCD[TELA_TECLADO][idioma]),pos); //Escreve TECLADO na tela

}


void fnTesteInfravermelho(void){
	LimpaLCD(); //Limpa LCD
	while(teclapressionada != teclaCancela) //Enquanto teclapressionada não for igual a tecla CANCELA então
	{
		if(AMBOS_INFRAS_INATIVO) //Se ambos infras não tiverem ninguém na frente então
		{
			flag_passagem = _AMBOS_INFRAS_INATIVO; //Armazena em flag_passagem a informação _AMBOS_INFRAS_INATIVO
		}
		else if(INFRA1_ATIVO && INFRA2_INATIVO) //Senão se tiver alguém no feixe1 do infravermelho e ninguém no feixe 2 do infravermelho então
		{
			flag_passagem = _INFRA1_ATIVO;  //Armazena em flag_passagem a informação _INFRA1_ATIVO
		}
		else if(INFRA1_INATIVO && INFRA2_ATIVO) //Senão se naõ tiver alguém no feixe1 do infravermelho e tiver alguém no feixe 2 do infravermelho então
		{
			flag_passagem = _INFRA2_ATIVO; //Armazena em flag_passagem a informação _INFRA2_ATIVO
		}
		else if(AMBOS_INFRAS_ATIVO) //Senão se tiver alguém no feixe 1 e no feixe 2 dos infravermelhos então
		{
			flag_passagem = _AMBOS_INFRAS_ATIVO; //Armazena em flag_passagem a informação _AMBOS_INFRAS_ATIVO
		}

		if(flag_passagem == _AMBOS_INFRAS_INATIVO) //Se flag_passagem for igual a _AMBOS_INFRAS_INATIVO então
		{
			LINHA = 1; //Se posiciona na linha 1
			COLUNA = 1; //Se posiciona na coluna 1
			EscreveLCD((telas_LCD[TELA_INFRA1_OFF_E_INFRA2_OFF][idioma]),pos); //Escreve na tela na posição especificada INFRA 1 --> OFF
			LINHA = 2; //Se posiciona na linha 2
			COLUNA = 1; //Se posiciona na coluna 1
			EscreveLCD((telas_LCD[TELA_INFRA1_OFF_E_INFRA2_OFF + 1][idioma]),pos); //Escreve na tela na posição especificada INFRA 2 --> OFF
		}
		else if(flag_passagem == _INFRA1_ATIVO) //Senão se flag_passagem for igual a _INFRA1_ATIVO então
		{
			LINHA = 1; //Se posiciona na linha 1
			COLUNA = 1; //Se posiciona na coluna 1
			EscreveLCD((telas_LCD[TELA_INFRA1_ON_E_INFRA2_ON][idioma]),pos); //Escreve na tela na posição especificada INFRA 1 --> ON
			LINHA = 2; //Se posiciona na linha 2
			COLUNA = 1; //Se posiciona na coluna 1
			EscreveLCD((telas_LCD[TELA_INFRA1_OFF_E_INFRA2_OFF + 1][idioma]),pos); //Escreve na tela na posição especificada INFRA 2 --> OFF
		}
		else if(flag_passagem == _INFRA2_ATIVO) //Senão se flag_passagem for igual a _INFRA2_ATIVO então
		{
			LINHA = 1; //Se posiciona na linha 1
			COLUNA = 1; //Se posiciona na coluna 1
			EscreveLCD((telas_LCD[TELA_INFRA1_OFF_E_INFRA2_OFF][idioma]),pos); //Escreve na tela na posição especificada INFRA 1 --> OFF
			LINHA = 2; //Se posiciona na linha 2
			COLUNA = 1; //Se posiciona na coluna 1
			EscreveLCD((telas_LCD[TELA_INFRA1_ON_E_INFRA2_ON + 1][idioma]),pos); //Escreve na tela na posição especificada INFRA 2 --> ON
		}
		else if(flag_passagem == _AMBOS_INFRAS_ATIVO) //Senão se flag_passagem for igual a _AMBOS_INFRAS_ATIVO então
		{
			LINHA = 1; //Se posiciona na linha 1
			COLUNA = 1; //Se posiciona na coluna 1
			EscreveLCD((telas_LCD[TELA_INFRA1_ON_E_INFRA2_ON][idioma]),pos); //Escreve na tela na posição especificada INFRA 1 --> ON
			LINHA = 2; //Se posiciona na linha 2
			COLUNA = 1; //Se posiciona na coluna 1
			EscreveLCD((telas_LCD[TELA_INFRA1_ON_E_INFRA2_ON + 1][idioma]),pos); //Escreve na tela na posição especificada INFRA 2 --> ON
		}
	}
	teclapressionada = 0; //Limpa teclapressionada

}

void fnTesteAutonomiaBateria(void){
	Solenoide_DisableEvent();		//Desativa evento que gera PWM solenoide
	Solenoide_Disable();			//Desativa Timer que gera o evento do PWM solenoide
	tempo_trava = 0;				//Reseta contador de tempo para ativar PWM da solenoide
	travado = FALSE;
	while(teclapressionada != teclaCancela) //Enquanto teclapressionada não for igual a tecla CANCELA então
	{
		ACENDE_AREAS;
		ACENDE_NIVEL10;
		LIGA_SINALEIRA_VERMELHA;
		LIGA_TRAVA;
		LIGA_RELE;
		delay_segundos(5);
		APAGA_AREAS;
		ACENDE_NIVEL0;
		DESLIGA_SINALEIRA_VERMELHA;
		DESLIGA_TRAVA;
		DESLIGA_RELE;
		delay_segundos(55);
	}
	APAGA_AREAS;
	ACENDE_NIVEL0;
	LIGA_SINALEIRA_VERMELHA;
	LIGA_TRAVA;
	LIGA_RELE;
	travado = TRUE;
}

void fnTesteSinalRxA1A2(void){
	tela = TELA_SINAL_A1_A2; //Tela é igual a TELA_SINAL_A1_A2
	Atualiza_LCD(); //Atualiza o LCD com a tela acima
	LENDO_AREAS1 = FALSE;

	//Cada valor lido do AD é divido por 1986 porque
	//3.3V/65535 = 5,0354772259098191805905241474022e-5 e
	//0.1V / 5,0354772259098191805905241474022e-5 = 1986
	//para que o resultado apresentado na tela apareça até 3.3V de 0.1V em 0.1V

	while(teclapressionada != teclaCancela) //Enquanto teclapressionada não for igual a tecla CANCELA então
	{
		TENSAO_DAS_AREAS_Measure(FALSE); //Ativa a leitura das tensões das áreas
		if(FlagADC1) //Se FlagADC1 for 1 então
		{
			valor_sinal_area1 = Valor1[0] / 1986; //Armazena na variável valor_sinal_area1 o valor rms da senoide recebido na área 1

			valor_sinal_area2 = Valor1[1] / 1986; //Armazena na variável valor_sinal_area2 o valor rms da senoide recebido na área 2

			LigaDesligaCursor(DESLIGA); //Desliga o cursor

			LINHA = 1; //Se posiciona na linha 1
			COLUNA = 10; //Se posiciona na coluna 10
			PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
			EscreveChar((char)(valor_sinal_area1/10 + 48)); //Escreve a parte da unidade do valor_sinal_area1
			EscreveChar('.'); //Escreve ponto
			EscreveChar((char)(valor_sinal_area1%10 + 48)); //Escreve a parte depois da virgula do valor_sinal_area1
			EscreveChar('V'); //Escreve V

			LINHA = 2; //Se posiciona na linha 2
			COLUNA = 10; //Se posiciona na coluna 10
			PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
			EscreveChar((char)(valor_sinal_area2/10 + 48)); //Escreve a parte da unidade do valor_sinal_area2
			EscreveChar('.'); //Escreve ponto
			EscreveChar((char)(valor_sinal_area2%10 + 48)); //Escreve a parte depois da virgula do valor_sinal_area2
			EscreveChar('V'); //Escreve V

			FlagADC1 = 0; //Zera a flagADC1
			TENSAO_DAS_AREAS_Measure(TRUE); //Desativa a leitura das tensões das áreas

			delay_ms(50); //Espera 50 milisegundos
		}
	}
	LINHA = 1; //Se posiciona na linha 1
	COLUNA = 1; //Se posiciona na coluna 1
	EscreveLCD((telas_LCD[TELA_TENSAO_SINAL_RX][idioma]),pos); //Escreve na tela TENSAO SINAL RX
	LINHA = 2; //Se posiciona na linha 2
	COLUNA = 1; //Se posiciona na coluna 1
	EscreveLCD((telas_LCD[TELA_AREA_1_E_2][idioma]),pos); //Escreve na tela AREA 1 E 2

}

void fnTesteSinalRxA2A3_Z3(void){
	tela = TELA_SINAL_A2_A3; //Tela é igual a TELA_SINAL_A2_A3
	Atualiza_LCD(); //Atualiza o LCD com a tela acima
	LENDO_AREAS1 = FALSE;

	while(teclapressionada != teclaCancela) //Enquanto teclapressionada não for igual a tecla CANCELA então
	{
		TENSAO_DAS_AREAS_Measure(FALSE); //Ativa a leitura das tensões das áreas
		if(FlagADC1) //Se FlagADC1 for 1 então
		{
			valor_sinal_area2 = Valor1[1] / 1986; //Armazena na variável valor_sinal_area3 o valor rms da senoide recebido na área 2

			valor_sinal_area3 = Valor1[2] / 1986; //Armazena na variável valor_sinal_area4 o valor rms da senoide recebido na área 3

			LigaDesligaCursor(DESLIGA); //Desliga o cursor

			LINHA = 1; //Se posiciona na linha 1
			COLUNA = 10; //Se posiciona na coluna 10
			PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
			EscreveChar((char)(valor_sinal_area2/10 + 48)); //Escreve a parte da unidade do valor_sinal_area2
			EscreveChar('.'); //Escreve ponto
			EscreveChar((char)(valor_sinal_area2%10 + 48)); //Escreve a parte depois da virgula do valor_sinal_area2
			EscreveChar('V'); //Escreve V

			LINHA = 2; //Se posiciona na linha 2
			COLUNA = 10; //Se posiciona na coluna 10
			PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
			EscreveChar((char)(valor_sinal_area3/10 + 48)); //Escreve a parte da unidade do valor_sinal_area3
			EscreveChar('.'); //Escreve ponto
			EscreveChar((char)(valor_sinal_area3%10 + 48)); //Escreve a parte depois da virgula do valor_sinal_area3
			EscreveChar('V'); //Escreve V

			FlagADC1 = 0; //Zera a flagADC1
			TENSAO_DAS_AREAS_Measure(TRUE); //Desativa a leitura das tensões das áreas

			delay_ms(50); //Espera 50 milisegundos
		}
	}
	LINHA = 1; //Se posiciona na linha 1
	COLUNA = 1; //Se posiciona na coluna 1
	EscreveLCD((telas_LCD[TELA_TENSAO_SINAL_RX][idioma]),pos); //Escreve na tela TENSAO SINAL RX
	LINHA = 2; //Se posiciona na linha 2
	COLUNA = 1; //Se posiciona na coluna 1
	EscreveLCD((telas_LCD[TELA_AREA_2_E_3][idioma]),pos);

}

void fnTesteSinalRxA3A4(void){
	tela = TELA_SINAL_A3_A4; //Tela é igual a TELA_SINAL_A3_A4
	Atualiza_LCD(); //Atualiza o LCD com a tela acima
	LENDO_AREAS1 = FALSE;

	while(teclapressionada != teclaCancela) //Enquanto teclapressionada não for igual a tecla CANCELA então
	{
		TENSAO_DAS_AREAS_Measure(FALSE); //Ativa a leitura das tensões das áreas
		if(FlagADC1) //Se FlagADC1 for 1 então
		{
			valor_sinal_area3 = Valor1[2] / 1986; //Armazena na variável valor_sinal_area3 o valor rms da senoide recebido na área 3

			valor_sinal_area4 = Valor1[3] / 1986; //Armazena na variável valor_sinal_area4 o valor rms da senoide recebido na área 4

			LigaDesligaCursor(DESLIGA); //Desliga o cursor

			LINHA = 1; //Se posiciona na linha 1
			COLUNA = 10; //Se posiciona na coluna 10
			PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
			EscreveChar((char)(valor_sinal_area3/10 + 48)); //Escreve a parte da unidade do valor_sinal_area3
			EscreveChar('.'); //Escreve ponto
			EscreveChar((char)(valor_sinal_area3%10 + 48)); //Escreve a parte depois da virgula do valor_sinal_area3
			EscreveChar('V'); //Escreve V

			LINHA = 2; //Se posiciona na linha 2
			COLUNA = 10; //Se posiciona na coluna 10
			PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
			EscreveChar((char)(valor_sinal_area4/10 + 48)); //Escreve a parte da unidade do valor_sinal_area4
			EscreveChar('.'); //Escreve ponto
			EscreveChar((char)(valor_sinal_area4%10 + 48)); //Escreve a parte depois da virgula do valor_sinal_area4
			EscreveChar('V'); //Escreve V

			FlagADC1 = 0; //Zera a flagADC1
			TENSAO_DAS_AREAS_Measure(TRUE); //Desativa a leitura das tensões das áreas

			delay_ms(50); //Espera 50 milisegundos
		}
	}
	LINHA = 1; //Se posiciona na linha 1
	COLUNA = 1; //Se posiciona na coluna 1
	EscreveLCD((telas_LCD[TELA_TENSAO_SINAL_RX][idioma]),pos); //Escreve na tela TENSAO SINAL RX
	LINHA = 2; //Se posiciona na linha 2
	COLUNA = 1; //Se posiciona na coluna 1
	EscreveLCD((telas_LCD[TELA_AREA_3_E_4][idioma]),pos);
}

void fnTesteSinalRxA5A6(void){
	tela = TELA_SINAL_A5_A6; //Tela é igual a TELA_SINAL_A5_A6
	Atualiza_LCD(); //Atualiza o LCD com a tela acima
	LENDO_AREAS1 = FALSE;

	while(teclapressionada != teclaCancela) //Enquanto teclapressionada não for igual a tecla CANCELA então
	{
		TENSAO_DAS_AREAS_Measure(FALSE); //Ativa a leitura das tensões das áreas
		if(FlagADC1) //Se FlagADC1 for 1 então
		{
			valor_sinal_area5 = Valor1[4] / 1986; //Armazena na variável valor_sinal_area4 o valor rms da senoide recebido na área 4

			valor_sinal_area6 = Valor1[5] / 1986; //Armazena na variável valor_sinal_area5 o valor rms da senoide recebido na área 5

			LigaDesligaCursor(DESLIGA); //Desliga o cursor

			LINHA = 1; //Se posiciona na linha 1
			COLUNA = 10; //Se posiciona na coluna 10
			PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
			EscreveChar((char)(valor_sinal_area5/10 + 48)); //Escreve a parte da unidade do valor_sinal_area5
			EscreveChar('.');
			EscreveChar((char)(valor_sinal_area5%10 + 48)); //Escreve a parte depois da virgula do valor_sinal_area5
			EscreveChar('V');

			LINHA = 2; //Se posiciona na linha 2
			COLUNA = 10; //Se posiciona na coluna 10
			PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
			EscreveChar((char)(valor_sinal_area6/10 + 48)); //Escreve a parte da unidade do valor_sinal_area6
			EscreveChar('.');
			EscreveChar((char)(valor_sinal_area6%10 + 48)); //Escreve a parte depois da virgula do valor_sinal_area6
			EscreveChar('V');

			FlagADC1 = 0; //Zera a flagADC1
			TENSAO_DAS_AREAS_Measure(TRUE); //Desativa a leitura das tensões das áreas

			delay_ms(50); //Espera 50 milisegundos
		}
	}
	LINHA = 1; //Se posiciona na linha 1
	COLUNA = 1; //Se posiciona na coluna 1
	EscreveLCD((telas_LCD[TELA_TENSAO_SINAL_RX][idioma]),pos); //Escreve na tela TENSAO SINAL RX
	LINHA = 2; //Se posiciona na linha 2
	COLUNA = 1; //Se posiciona na coluna 1
	EscreveLCD((telas_LCD[TELA_AREA_5_E_6][idioma]),pos); //Escreve na tela AREA 5 E 6
}

void fnTesteSinalRxA7A8(void){
	tela = TELA_SINAL_A7_A8; //Tela é igual a TELA_SINAL_A7_A8
	Atualiza_LCD(); //Atualiza o LCD com a tela acima
	LENDO_AREAS1 = FALSE;

	while(teclapressionada != teclaCancela) //Enquanto teclapressionada não for igual a tecla CANCELA então
	{
		TENSAO_DAS_AREAS_Measure(FALSE); //Ativa a leitura das tensões das áreas
		if(FlagADC1) //Se FlagADC1 for 1 então
		{
			valor_sinal_area7 = Valor1[6] / 1986; //Armazena na variável valor_sinal_area7 o valor rms da senoide recebido na área 7

			valor_sinal_area8 = Valor1[7] / 1986; //Armazena na variável valor_sinal_area8 o valor rms da senoide recebido na área 8

			LigaDesligaCursor(DESLIGA); //Desliga o cursor

			LINHA = 1; //Se posiciona na linha 1
			COLUNA = 10; //Se posiciona na coluna 10
			PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
			EscreveChar((char)(valor_sinal_area7/10 + 48)); //Escreve a parte da unidade do valor_sinal_area7
			EscreveChar('.'); //Escreve ponto
			EscreveChar((char)(valor_sinal_area7%10 + 48)); //Escreve a parte depois da virgula do valor_sinal_area7
			EscreveChar('V'); //Escreve V

			LINHA = 2; //Se posiciona na linha 2
			COLUNA = 10; //Se posiciona na coluna 10
			PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
			EscreveChar((char)(valor_sinal_area8/10 + 48)); //Escreve a parte da unidade do valor_sinal_area8
			EscreveChar('.'); //Escreve ponto
			EscreveChar((char)(valor_sinal_area8%10 + 48)); //Escreve a parte depois da virgula do valor_sinal_area8
			EscreveChar('V'); //Escreve V

			FlagADC1 = 0; //Zera a flagADC1
			TENSAO_DAS_AREAS_Measure(TRUE); //Desativa a leitura das tensões das áreas

			delay_ms(50); //Espera 50 milisegundos
		}
	}
	LINHA = 1; //Se posiciona na linha 1
	COLUNA = 1; //Se posiciona na coluna 1
	EscreveLCD((telas_LCD[TELA_TENSAO_SINAL_RX][idioma]),pos); //Escreve na tela TENSAO SINAL RX
	LINHA = 2; //Se posiciona na linha 2
	COLUNA = 1; //Se posiciona na coluna 1
	EscreveLCD((telas_LCD[TELA_AREA_7_E_8][idioma]),pos); //Escreve na tela AREA 7 E 8

}

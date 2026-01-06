/*
 * lcd.c
 *
 *  Created on: 07/11/2019
 *      Author: Alexandre Voigt da Poian
 */

#include "main.h"

void InitLCD(void)
{
	RS_OFF;								//Desliga RS para entrar no modo de instrução
	AGUARDA_Waitms(40);					//Espera 40ms

	LCD_Comando(0x03);	 				//Acorda
	LCD_Comando(0x02);	 				//Acorda
	LCD_Comando(0x28);					//0 0 1 DL N F X X (DL=0 modo 4 bits, N=1 2 linhas, F=0 modo display 5x8 pontos
	LCD_Comando(0x0C);					//0 0 0 0 1 D C B (D=1 display ligado, C=0 cursor desligado, B=0 cursor piscante desligado
	LCD_Comando(0x06);					//0 0 0 0 0 1 I/D S (I/D=1 cursor piscante move para a direita, S=0 rotaciona o display inteiro para a direita
	LCD_Comando(0x01);					//Limpa o display
	AGUARDA_Waitms(5);					//Aguarda 5ms
}

void LCD_Comando(byte comando) //Função para enviar comandos ao display
{
	RS_OFF;								//Desliga RS para entrar no modo de instrução

	DADOS_PutVal(comando >> 4);			//Desloca o dado 4 bits para a direita para por a parte alta do dado em DB7 a DB4
	E_ON;								//Coloca o enable para 1
	AGUARDA_Waitus(50);					//Espera 50us
	E_OFF;								//Coloca o enable para 0 para que a primeira parte do dado entre no display

	DADOS_PutVal(comando & 0x0F);		//Faz um AND com os 4 bits menos significativos para por a parte baixo do dado em DB7 a DB4
	E_ON;								//Coloca o enable para 1
	AGUARDA_Waitus(50);					//Aguarda 50us
	E_OFF;								//Coloca o enable para 0 para que a parte baixa do dado entre no display

	AGUARDA_Waitus(250);				//Aguarda 250us

	RS_ON;								//Liga RS para entrar no modo de dados
}

void LCD_Dado(byte dado) //Função para escrever dados no display
{
	RS_ON;								//Liga RS para entrar no modo de dados

	DADOS_PutVal(dado >> 4);			//Desloca o dado 4 bits para a direita para por a parte alta do dado em DB7 a DB4
	E_ON;								//Coloca o enable para 1
	AGUARDA_Waitus(50);					//Espera 50us
	E_OFF;								//Coloca o enable para 0 para que a primeira parte do dado entre no display


	DADOS_PutVal(dado & 0x0F);			//Faz um AND com os 4 bits menos significativos para por a parte baixo do dado em DB7 a DB4
	E_ON;								//Coloca o enable para 1
	AGUARDA_Waitus(50);					//Espera 50us
	E_OFF;								//Coloca o enable para 0 para que a primeira parte do dado entre no display


	AGUARDA_Waitus(250);				//Aguarda 250us

	RS_ON;								//Liga RS para entrar no modo de dados
}

void EscreveLCD(char *string, byte pos[2]) //Escreve textos nos display armazenados previamente na flash
{
	static byte numero_caracteres;		//Define que numero_caracteres será o contador da quantidade de caracteres
	PosicionaLCD(pos);					//Posiciona LCD - pos[0] = linha - pos[1] = coluna
	AGUARDA_Waitms(1);					//Aguarda 1ms
	do									//Executa o código abaixo
	{
		LCD_Dado((char)*string);		//Pega o dado que esta apontado em string
		string++;						//procura a próxima letra
		numero_caracteres = numero_caracteres + 1;	//Incrementa a variável contador de quantidade de caracteres
	}while (numero_caracteres < 17);	//enquanto string for menor que 17 continua o processo para poder escrever o texto no display
	numero_caracteres = 0;				//Reinicializa a variável numero_caracteres
}

void EscreveChar(char caracter) //Função que escreve somente um caracter no display
{
	LCD_Dado(caracter);					//Escreve o referido caracter no display
}

void LimpaLCD(void)	//Função que limpa o LCD
{
	LCD_Comando(0x01);					//Executa o comando de limpar o LCD
	AGUARDA_Waitms(2);					//Aguarda 2ms
}

void PosicionaLCD(byte pos[2])	//Função para posicionar o texto na linha e coluna especificada
{
	byte posLCD = 0x80;					//Define posLCD como byte e já na posição 0x80 do display

	if(pos[0] < 3)						//Se pos[0] que é a linha for menor que 3 então
	{
		posLCD = 0x80 + (byte)(pos[0]-1)*0x40 + (pos[1]-1); //Posiciona o cursor no diplay na coordenada especifica, ou seja, na linha e coluna
	}
	else								//senão
	{
		posLCD = 0x80 + (byte)(pos[0]-3)*0x40 + 20 + (pos[1]-1); //Retorna o cursor a posição inicial do display
	}

	LCD_Comando(posLCD);				//Executa o comando de posicionamento do cursor no display
}

void DesligaLCD(void) //Função que desliga o LCD
{
	LCD_Comando(0x08);					//Executa o comando desliga LCD
	while(BUSY){}						//Enquanto ocupado aguarda
}

void LigaDesligaCursor(byte ligdesl) //Função que desliga o cursor
{
	if(ligdesl == LIGA)					//Se ligdes1 = LIGA
	{
		LCD_Comando(0x0F);				//Executa o comando para liga o display
	}
	else								//senão
	{
		LCD_Comando(0x0C);				//Executa o comando para desligar o display
	}
}

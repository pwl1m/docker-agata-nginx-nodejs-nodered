/*
 * lcd.h
 *
 *  Created on: 07/11/2019
 *      Author: Alexandre Voigt da Poian
 */

#ifndef SOURCES_LCD_H_
#define SOURCES_LCD_H_

#define	BUSY	DADOS_GetVal() & 0x80
#define LIGA	1
#define DESLIGA	0

/*************************** Protótipos das Funções ***************************/
void InitLCD(void); //Função que inicializa o LCD
void EscreveLCD(char *string,byte pos[2]); //Função que escreve uma string no LCD na linha e coluna especificada
void PosicionaLCD(byte pos[2]); //Posiciona o cursor na linha e coluna especificada
void LimpaLCD(void); //Função que limpa o LCD
void EscreveChar(char caracter); //Função que escreve apenas um caracter no LCD
void LigaDesligaCursor(byte ligdesl); //Função que liga e desliga o cursor
void DesligaLCD(void); //Função que desliga o LCD
/******************************************************************************/

#endif /* SOURCES_LCD_H_ */

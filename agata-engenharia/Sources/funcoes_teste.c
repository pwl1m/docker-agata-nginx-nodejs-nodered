/*
 * funcoes_teste.c
 *
 *  Created on: 17/08/2023
 *      Author: marcos.butignol
 */
/*
	byte msgDigitada[16];

void fnTesteDigitarMensagem(void) //Função que permite digitar a senha corretamente dentro do campo senha
{
	static byte estadoDigitaMensagem = 1; //Define a variável estadoDigitaSenha para o switch case abaixo
	static byte identador = 1; //Define identador para ir posicionando o cursor nos campos de digitação da senha



	switch(estadoDigitaMensagem) //Conforme variável estadoDigitaSenha vai para o case específico
	{
		case TESTE_DMSG_INIT: //Entra para digitar a senha
		{
			memset(msgDigitada,0,sizeof(msgDigitada));
			SetaCaracterSenha(identador); //Função que vai deslocando o caracter no campo senha
			estadoDigitaMensagem = TESTE_DMSG_DIGITAR; //Armazena na variável estadoDigitaSenha o valor 2 para ir para o case 2
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case TESTE_DMSG_DIGITAR: //Permite ir digitando a senha
		{
			if(teclapressionada == teclaCancela) //Se teclapressionada for igual a tecla CANCELA então
			{
				teclapressionada = 0; //Limpa teclapressionada
				ch = 0x30; //Armazena na variável ch a informação 0
				return;
			}
			if(teclapressionada == teclaConfirma) //Se teclapressionada for igual a tecla CONFIRMA então
			{
				SetaCaracterSenha(identador); //Posiciona o cursor na coluna conforme o valor do identador passado
				senha[identador - 1] = ch; //Armazena no vetor senha na posição identador-6, exemplo: se identador é 6 será senha[0]. Armazena o conteúdo de ch
				identador++; //Incrementa identador para ir para o próximo campo da senha
				COLUNA = identador; //Armazena na variável COLUNA a posição identador
				PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada acima
				ch = 0x30; //Armazena na variável ch a informação 0
				C = ch; //Armazena na variável C o conteúdo da variável ch
				teclapressionada = 0; //Limpa teclapressionada
			}
			if(teclapressionada == teclaIncrementa || teclapressionada == teclaTrava) //Se teclapressionada for igual a tecla INCREMENTA ou teclapressionada for igual a tecla TRAVA então
			{
				if(C == 0X39) //Se C for igual a 9 então
				{
					C = 0X41; //Armazena na variável C a informação A
					EscreveChar(C); //Escreve A na posição especificada
					COLUNA = identador; //Armazena na variável COLUNA a posição identador
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada acima
				}
				else if(C == 0x5A) //Senão se C for igual a Z então
				{
					C = 0x30; //Armazena na variável C a informação 0
					EscreveChar(C); //Escreve 0 na posição especificada
					COLUNA = identador; //Armazena na variável COLUNA a posição identador
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada acima
				}
				else //Senão
				{
					C++; //Incrementa C
					EscreveChar(C); //Escreve o conteúdo de C
					COLUNA = identador; //Armazena na variável COLUNA a posição identador
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada acima
				}
				ch = C; //Armazena na variável ch o conteúdo da variável C
				teclapressionada = 0; //Limpa teclapressionada
			}
			if(teclapressionada == teclaDecrementa || teclapressionada == teclaDestrava) //Se teclapressionada for igual a tecla DECREMENTA ou teclapressionada for igual a tecla DESTRAVA então
			{
				if(C == 0x30) //Se C for igual a 0 então
				{
					C = 0x5A; //Armazena na variável C a informação Z
					EscreveChar(C); //Escreve o conteúdo de C
					COLUNA = identador; //Armazena na variável COLUNA a posição identador
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada acima
				}
				else if(C == 0x41) //Se C for igual a A
				{
					C = 0x39; //Armazena na variável C a informação 9
					EscreveChar(C); //Escreve o conteúdo de C
					COLUNA = identador; //Armazena na variável COLUNA a posição identador
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada acima
				}
				else //Senão
				{
					C--; //Decrementa C
					EscreveChar(C); //Escreve o conteúdo de C
					COLUNA = identador; //Armazena na variável COLUNA a posição identador
					PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada acima
				}
				ch = C; //Armazena na variável ch o conteúdo da variável C
				teclapressionada = 0; //Limpa teclapressionada
			}
			if(identador >= 16) //Se identador for maior ou igual a 12 então
			{
				estadoDigitaSenha = TESTE_DMSG_SEL_CRIPT; //Armazena na variável estadoDigitaSenha o valor 3 para ir para o case 3
				identador = 1; //Armazena na variável identador o valor 6 para se posicionar no primeiro campo da senha
				ch = 0x30; //Armazena na variável ch a informação 0
				break;
			}
			break;
		}
		case TESTE_DMSG_SEL_CRIPT: //Verifica se a senha esta correta
		{
			if(teclapressionada == teclaCancela) //Se teclapressionada for igual a tecla CANCELA então
			{
				AES_CBC_encrypt_buffer(struct AES_ctx *ctx, uint8_t* buf, size_t length)

				teclapressionada = 0; //Limpa teclapressionada
				ch = 0x30; //Armazena na variável ch a informação 0
				return;
			}
			if(teclapressionada == teclaConfirma) //Se teclapressionada for igual a tecla CONFIRMA então
			{
				SetaCaracterSenha(identador); //Posiciona o cursor na coluna conforme o valor do identador passado
				senha[identador - 6] = ch; //Armazena no vetor senha na posição identador-6, exemplo: se identador é 6 será senha[0]. Armazena o conteúdo de ch
				identador++; //Incrementa identador para ir para o próximo campo da senha
				COLUNA = identador; //Armazena na variável COLUNA a posição identador
				PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada acima
				ch = 0x30; //Armazena na variável ch a informação 0
				C = ch; //Armazena na variável C o conteúdo da variável ch
				teclapressionada = 0; //Limpa teclapressionada
			}

			break;
		}
		case 4: //Retorna para o menu inicial AJUSTES_BASICOS
		{
			tela = TELA_AJUSTES_BASICOS; //Tela é igual a TELA_AJUSTES_BASICOS
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estado = ESTADO_NAVEGA_MENU_FUNCOES; //Estado a ser executado é ESTADO_NAVEGA_MENU_FUNCOES
			identador = 6; //Armazena na variável identador o valor 6 para se posicionar no primeiro campo da senha
			teclapressionada = 0; //Limpa teclapressionada
			estadoDigitaSenha = 1; //Armazena na variável estadoDigitaSenha o valor 1 para ir para o primeiro nivel deste menu
			break;
		}
		break;
	}
}
*/

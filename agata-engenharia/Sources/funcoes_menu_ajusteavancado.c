/*
 * funcoes_menu_ajusteavancado.c
 *
 *  Created on: 22/06/2023
 *      Author: marcos.butignol
 */




#include "funcao.h"

#include "agata_std_functions.h"
#include "agata_hc_definitions.h"
#include "stdlib.h"


void fnAjusteManualCanal(void) //Permite ajustar o canal de forma manual de 1 a 10
{
	static byte estadoAjusteManualCanal = 1,canal_aux,defasagem_aux,sensibilidade_aux[8], ganho_aux[8]; //Definindo variável estadoAjusteManualCanal para o switch case abaixo e canal_aux para armazenar o último valor de canal e poder recuperar caso tenha sido alterado e pressionar cancela para abortar alteração

	switch(estadoAjusteManualCanal) //Conforme variável vai para o case específico
	{
		case 1: //ENTRA NO MENU PARA ALTERAR O CANAL
		{
			tela = TELA_DIGITE_CANAL; //Tela é igual a TELA_DIGITE_CANAL
			estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
			estadoAjusteManualCanal = 2; //Coloca a variável para 2 para entrar no case 2
			defasagem_aux = defasagem;
			canal_aux = canal; //Armazena em canal_aux o último valor do canal antes de começar a alterar
			for(byte i = 0; i < 8; i++){
				sensibilidade_aux[i] = buffer_sensibilidade[i+1];
			}
			for(byte i = 0; i < 8; i++){
				ganho_aux[i] = buffer_ganho[i+1];
			}
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2:	//ALTERAR CANAL
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					canal++; //Incrementa canal
					if(canal > NUM_MAX_CANAIS) //Se canal for maior que 10 então
					{
						canal = 1; //Armazena 1 na variável canal
					}
					LINHA = 2; //Se posiciona na linha 2
					COLUNA = 8; //Se posiciona na coluna 8
					PosicionaLCD(pos); //Posiciona o cursor conforme as coordenadas acima
					EscreveChar((char)(canal/10+48)); //Escreve a dezena da variável canal
					EscreveChar((char)(canal%10+48)); //Escreve a unidade da variável canal
					teclapressionada = 0; //Limpa a teclapressionada
					fnAtualizaPerfil(SETA_PARAMETRO_ON,SETA_PWM_ON,SETA_GRAVA_FLASH_OFF,SETA_POT_GANHO_OFF); //Atualiza valores de ciclo de trabalho e frequência do sinal da TX, valor correto de defasagem para pegar ambos os metais, valor correto dos potenciometros de ganho de cada área, valor correto dos potenciometros de seleção de cada área e valor correto de sensibilidade de cada área
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					canal--; //Decrementa canal
					if(canal < 1) //Se canal for menor que 1 então
					{
						canal = NUM_MAX_CANAIS; //Armazena 10 na variável canal
					}
					LINHA = 2; //Se posiciona na linha 2
					COLUNA = 8; //Se posiciona na coluna 8
					PosicionaLCD(pos); //Posiciona o cursor conforme as coordenadas acima
					EscreveChar((char)(canal/10+48)); //Escreve a dezena da variável canal
					EscreveChar((char)(canal%10+48)); //Escreve a unidade da variável canal
					teclapressionada = 0; //Limpa teclapressionada
					fnAtualizaPerfil(SETA_PARAMETRO_ON,SETA_PWM_ON,SETA_GRAVA_FLASH_OFF,SETA_POT_GANHO_OFF); //Atualiza valores de ciclo de trabalho e frequência do sinal da TX, valor correto de defasagem para pegar ambos os metais e valor correto de sensibilidade de cada área
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					tela = TELA_CANAL; //Tela é igual a TELA_CANAL
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					estado = ESTADO_AJUSTES_AVANCADOS; //Estado a ser executado é ESTADO_AJUSTES_AVANCADOS
					estadoAjusteManualCanal = 1; //Coloca a variável estadoAjusteManualCanal para 1 para voltar a camada 1 desta função
					teclapressionada = 0; //Limpa teclapressionada
					if(canal == canal_aux){
						for(byte i = 0; i < 8; i++){
							buffer_sensibilidade[i+1] = sensibilidade_aux[i];
						}
						for(byte i = 0; i < 8; i++){
							buffer_ganho[i+1] = ganho_aux[i];
						}
					}else{
						fnAtualizaPerfil(SETA_PARAMETRO_ON,SETA_PWM_ON,SETA_GRAVA_FLASH_ON,SETA_POT_GANHO_ON); //Grava e atualiza valores de ciclo de trabalho e frequência do sinal da TX, valor correto de defasagem para pegar ambos os metais e valor correto de sensibilidade de cada área
						fnGravaAuditoria(2,canal_aux,canal,OPERADOR,DISPOSITIVO);
					}
					break;
				}
				case teclaCancela:
				{
					tela = TELA_CANAL; //Tela é igual a TELA_CANAL
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					estado = ESTADO_AJUSTES_AVANCADOS; //Estado a ser executado é ESTADO_AJUSTES_AVANCADOS
					estadoAjusteManualCanal = 1; //Coloca a variável estadoAjusteManualCanal para 1 para voltar a camada 1 desta função
					canal = canal_aux; //Recupera o último canal armazenado antes de alterar, retornando o canal ao último valor escolhido antes de alterar
					teclapressionada = 0; //Limpa teclapressionada
					fnAtualizaPerfil(SETA_PARAMETRO_ON,SETA_PWM_OFF,SETA_GRAVA_FLASH_OFF,SETA_POT_GANHO_OFF); //Atualiza valores de ciclo de trabalho e frequência do sinal da TX, valor correto de defasagem para pegar ambos os metais e valor correto de sensibilidade de cada área
					defasagem = defasagem_aux;
					for(byte i = 0; i < 8; i++){
						buffer_sensibilidade[i+1] = sensibilidade_aux[i];
					}
					for(byte i = 0; i < 8; i++){
						buffer_ganho[i+1] = ganho_aux[i];
					}
					fnAtualizaPerfil(SETA_PARAMETRO_OFF,SETA_PWM_ON,SETA_GRAVA_FLASH_OFF,SETA_POT_GANHO_OFF);
					break;
				}
				break;
			}
			break;
		}
		break;
	}
}

void fnAjusteAutomaticoCanal(void) //Permite encontrar o melhor canal de frequência automaticamente verificando-se o ruido do ambiente
{
	volatile byte numero_canais_testados = 0; //Variável temporária para armazenar o número de canais já testados
	volatile byte canal_escolhido = 0; //Variável temporária para armazenar o canal escolhido
	volatile dword media_canal[10]; //Variável para armazenar a média dos 10 canais de frequência

	for(x = 0;x < NUM_MAX_CANAIS;x++) //Faz uma leitura de cada canal por 1 segundo a intervalos de 6s entre eles
	{
		numero_amostragens_canal[x] = 0; //Zera o contador de de número de amostragens do canal
		canal = x + 1; //Armazena em canal o primeiro canal a ser lido
		if(canal <= NUM_MAX_CANAIS)
		{
			fnAtualizaPerfil(SETA_PARAMETRO_ON,SETA_PWM_ON,SETA_GRAVA_FLASH_OFF,SETA_POT_GANHO_OFF); //Atualiza valores de ciclo de trabalho e frequência do sinal da TX, valor correto de defasagem para pegar ambos os metais e valor correto de sensibilidade de cada área
			delay_ms(6000); //Aguarda 6s para o sinal estabilizar ao trocar de canal
			tempo_leitura_canal = 0; //Zera o tempo_leitura_canal para fazer a varredura das áreas por um determinado intervalo de tempo
		}
		while(tempo_leitura_canal < 10 && canal <= NUM_MAX_CANAIS) //Faz a varredura das áreas no intervalo de 1 segundo enquanto canal for até 10
		{
			fnLeAreas(canal); //Faz a leitura das áreas e amostra o sinal das áreas durante este intervalo de tempo
		}
		LINHA = 2; //Se posiciona na linha 2
		COLUNA = 1; //Se posiciona na coluna 1
		EscreveLCD((telas_LCD[TELA_SINTONIZANDO + 1][idioma]),pos); //Escreve CANAL na posição acima especificada
		LINHA = 2; //Se posiciona na linha 2
		COLUNA = 11; //Se posiciona na coluna 11
		PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificados acima
		EscreveChar((char)(canal/10 + 48)); //Escreve a dezena do canal
		EscreveChar((char)(canal%10 + 48)); //Escreve a unidade do canal
	}

	delay_ms(2000); //Espera 2 segundos

	for(x = 0; x < NUM_MAX_CANAIS; x++) //Realiza a média do canal específico conforme as amostras realizadas
	{
		media_canal[x] = (Valor_Amostra_Area1[x] + Valor_Amostra_Area2[x] + Valor_Amostra_Area3[x] +
				          Valor_Amostra_Area4[x] + Valor_Amostra_Area5[x] + Valor_Amostra_Area6[x] +
						  Valor_Amostra_Area7[x] + Valor_Amostra_Area8[x])  / numero_amostragens_canal[x]; //Armazena a media do canal específico
	}

	for(x = 0;x < NUM_MAX_CANAIS;x++) //Escolhe o canal que tem o menor nível de ruído, este laço x indica o canal que será comparado com os demais
	{
		for(y = 0;y < NUM_MAX_CANAIS;y++) //Compara com os demais canais menos o que é igual a ele mesmo
		{
			if((media_canal[x] < media_canal[y]) && (x != y)) //Se media do canal for menor que a media dos demais canais e for 9 vezes menor significa que este é o melhor canal em relação aos outros
			{
				numero_canais_testados = numero_canais_testados + 1; //Vai incrementando para saber quantas vezes foi menor que os demais canais
			}
		}
		if (numero_canais_testados == (NUM_MAX_CANAIS-1)) //Se número de canais testados for igual a 9 significa que este é o canal escolhido
		{
			canal = x + 1;		//Muda de canal para proximo teste
		}
		numero_canais_testados = 0; //Zera a variável numero_canais_testados para poder descobrir o melhor canal
	}
	tela = TELA_MELHOR_CANAL; //Tela é TELA_MELHOR_CANAL
	Atualiza_LCD(); //Atualiza LCD com a tela especificada

	delay_ms(2000); //Espera 2 segundos

	Write_Buffer_FLASH[0] = canal; //Armazena no vetor para poder gravar o canal na memória FLASH
	ESCREVE_FLASH_INTERNA(endFLASHCanal,1,0); //Escreve na memória FLASH no endereço especificado
	fnAtualizaPerfil(SETA_PARAMETRO_ON,SETA_PWM_ON,SETA_GRAVA_FLASH_ON,SETA_POT_GANHO_ON); //Atualiza ciclo de trabalho, defasagem, frequência, sensibilidade e ganho dos potenciometros conforme canal escolhido

	flagretorno = 1; //Torna flag flagretorno para 1 para poder retornar ao menu AJUSTES AVANÇADOS
	estado = ESTADO_AJUSTES_AVANCADOS; //Estado a ser executado é ESTADO_AJUSTES_AVANCADOS
}


void fnLeAreas(byte canal_de_amostragem) //Função que trabalha em conjunto com o Ajuste Automático de canal lendo as áreas e amostrando para ver qual canal tem menos ruido
{
	LENDO_AREAS = FALSE; //Tornar a flag LENDO_AREAS para FALSE para poder fazer a análise do sinal das áreas
	if(FlagADC == 1) //Se flag FlagADC for igual a 1 então houve a captura do sinal em todas as áreas
	{
		if(Valor[AREA1] >= NIVEL_ZERO) //Se valor do sinal da área 1 for maior que NIVEL_ZERO (32768) então corrige valor para a faixa correta pois sinal é positivo
		{
			Valor[AREA1] = Valor[AREA1] - NIVEL_ZERO; //Valor do sinal da área 1 é igual ao valor lido da área 1 menos o valor NIVEL_ZERO (32768)
		}
		else //Senão se valor do sinal da área 1 for menor que NIVEL_ZERO (32768) corrige valor para a faixa correta pois sinal é negativo
		{
			Valor[AREA1] = NIVEL_ZERO - Valor[AREA1]; //Valor do sinal da área 1 é igual ao valor NIVEL_ZERO (32768) menos o valor lido da área 1
		}

		if(Valor[AREA2] >= NIVEL_ZERO) //Se valor do sinal da área 2 for maior que NIVEL_ZERO (32768) então corrige valor para a faixa correta pois sinal é positivo
		{
			Valor[AREA2] = Valor[AREA2] - NIVEL_ZERO; //Valor do sinal da área 2 é igual ao valor lido da área 2 menos o valor NIVEL_ZERO (32768)
		}
		else //Senão se valor do sinal da área 2 for menor que NIVEL_ZERO (32768) corrige valor para a faixa correta pois sinal é negativo
		{
			Valor[AREA2] = NIVEL_ZERO - Valor[AREA2]; //Valor do sinal da área 2 é igual ao valor NIVEL_ZERO (32768) menos o valor lido da área 2
		}

		if(Valor[AREA3] >= NIVEL_ZERO) //Se valor do sinal da área 3 for maior que NIVEL_ZERO (32768) então corrige valor para a faixa correta pois sinal é positivo
		{
			Valor[AREA3] = Valor[AREA3] - NIVEL_ZERO; //Valor do sinal da área 3 é igual ao valor lido da área 3 menos o valor NIVEL_ZERO (32768)
		}
		else //Senão se valor do sinal da área 3 for menor que NIVEL_ZERO (32768) corrige valor para a faixa correta pois sinal é negativo
		{
			Valor[AREA3] = NIVEL_ZERO - Valor[AREA3]; //Valor do sinal da área 3 é igual ao valor NIVEL_ZERO (32768) menos o valor lido da área 3
		}

		if(Valor[AREA4] >= NIVEL_ZERO) //Se valor do sinal da área 4 for maior que NIVEL_ZERO (32768) então corrige valor para a faixa correta pois sinal é positivo
		{
			Valor[AREA4] = Valor[AREA4] - NIVEL_ZERO; //Valor do sinal da área 4 é igual ao valor lido da área 4 menos o valor NIVEL_ZERO (32768)
		}
		else //Senão se valor do sinal da área 4 for menor que NIVEL_ZERO (32768) corrige valor para a faixa correta pois sinal é negativo
		{
			Valor[AREA4] = NIVEL_ZERO - Valor[AREA4]; //Valor do sinal da área 4 é igual ao valor NIVEL_ZERO (32768) menos o valor lido da área 4
		}

		if(Valor[AREA5] >= NIVEL_ZERO) //Se valor do sinal da área 5 for maior que NIVEL_ZERO (32768) então corrige valor para a faixa correta pois sinal é positivo
		{
			Valor[AREA5] = Valor[AREA5] - NIVEL_ZERO; //Valor do sinal da área 5 é igual ao valor lido da área 5 menos o valor NIVEL_ZERO (32768)
		}
		else //Senão se valor do sinal da área 5 for menor que NIVEL_ZERO (32768) corrige valor para a faixa correta pois sinal é negativo
		{
			Valor[AREA5] = NIVEL_ZERO - Valor[AREA5]; //Valor do sinal da área 5 é igual ao valor NIVEL_ZERO (32768) menos o valor lido da área 5
		}

		if(Valor[AREA6] >= NIVEL_ZERO) //Se valor do sinal da área 6 for maior que NIVEL_ZERO (32768) então corrige valor para a faixa correta pois sinal é positivo
		{
			Valor[AREA6] = Valor[AREA6] - NIVEL_ZERO; //Valor do sinal da área 6 é igual ao valor lido da área 6 menos o valor NIVEL_ZERO (32768)
		}
		else //Senão se valor do sinal da área 6 for menor que NIVEL_ZERO (32768) corrige valor para a faixa correta pois sinal é negativo
		{
			Valor[AREA6] = NIVEL_ZERO - Valor[AREA6]; //Valor do sinal da área 6 é igual ao valor NIVEL_ZERO (32768) menos o valor lido da área 6
		}

		if(Valor[AREA7] >= NIVEL_ZERO) //Se valor do sinal da área 7 for maior que NIVEL_ZERO (32768) então corrige valor para a faixa correta pois sinal é positivo
		{
			Valor[AREA7] = Valor[AREA7] - NIVEL_ZERO; //Valor do sinal da área 7 é igual ao valor lido da área 7 menos o valor NIVEL_ZERO (32768)
		}
		else //Senão se valor do sinal da área 7 for menor que NIVEL_ZERO (32768) corrige valor para a faixa correta pois sinal é negativo
		{
			Valor[AREA7] = NIVEL_ZERO - Valor[AREA7]; //Valor do sinal da área 7 é igual ao valor NIVEL_ZERO (32768) menos o valor lido da área 7
		}

		if(Valor[AREA8] >= NIVEL_ZERO) //Se valor do sinal da área 8 for maior que NIVEL_ZERO (32768) então corrige valor para a faixa correta pois sinal é positivo
		{
			Valor[AREA8] = Valor[AREA8] - NIVEL_ZERO; //Valor do sinal da área 8 é igual ao valor lido da área 8 menos o valor NIVEL_ZERO (32768)
		}
		else //Senão se valor do sinal da área 8 for menor que NIVEL_ZERO (32768) corrige valor para a faixa correta pois sinal é negativo
		{
			Valor[AREA8] = NIVEL_ZERO - Valor[AREA8]; //Valor do sinal da área 8 é igual ao valor NIVEL_ZERO (32768) menos o valor lido da área 8
		}

		//Vai somando os valores de cada área e acumulando no respectivo vetor do Valor de Amostra de cada Área
		Valor_Amostra_Area1[canal_de_amostragem - 1] = Valor_Amostra_Area1[canal_de_amostragem - 1] + Valor[AREA1];
		Valor_Amostra_Area2[canal_de_amostragem - 1] = Valor_Amostra_Area2[canal_de_amostragem - 1] + Valor[AREA2];
		Valor_Amostra_Area3[canal_de_amostragem - 1] = Valor_Amostra_Area3[canal_de_amostragem - 1] + Valor[AREA3];
		Valor_Amostra_Area4[canal_de_amostragem - 1] = Valor_Amostra_Area4[canal_de_amostragem - 1] + Valor[AREA4];
		Valor_Amostra_Area5[canal_de_amostragem - 1] = Valor_Amostra_Area5[canal_de_amostragem - 1] + Valor[AREA5];
		Valor_Amostra_Area6[canal_de_amostragem - 1] = Valor_Amostra_Area6[canal_de_amostragem - 1] + Valor[AREA6];
		Valor_Amostra_Area7[canal_de_amostragem - 1] = Valor_Amostra_Area7[canal_de_amostragem - 1] + Valor[AREA7];
		Valor_Amostra_Area8[canal_de_amostragem - 1] = Valor_Amostra_Area8[canal_de_amostragem - 1] + Valor[AREA8];

		numero_amostragens_canal[canal_de_amostragem - 1]++; //Incrementa para poder fazer a média no canal conforme número de amostras recolhidas
		FlagADC = 0; //Torna flag FlagADC = 0 para poder fazer nova leitura do AD das áreas
		LENDO_AREAS = FALSE; //Torna flag LENDO_AREAS para FALSE para poder fazer nova leitura do AD das áreas
	}
}


void fnSelecaoMetais(void) //Permite escolher a seleção de metais entre 1 e 100, sendo acima de 50 mais metais ferrosos e menos que 50 mais metais não ferrosos
{
	static byte estadofnSelecaoMetais = 1,selecao_metais_aux; //Definindo variável estadofnSelecaoMetais para o switch case abaixo e selecao_metais_aux para armazenar o último valor de seleção e poder recuperar caso tenha sido alterado e pressionar cancela para abortar alteração
	static byte monitorar = 0;

	switch(estadofnSelecaoMetais) //Conforme variável vai para o case específico
	{
		case 1: //ENTRA NO MENU PARA ALTERAR A SELEÇÃO DE METAIS
		{
			tela = TELA_MOSTRA_SELECAO_METAIS; //Tela é igual a TELA_MOSTRA_SELECAO_METAIS
			estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
			estadofnSelecaoMetais = 2; //Coloca variável em 2 para poder ir para o case 2 quando voltar da rotina principal
			selecao_metais_aux = selecao_metais; //Armazena na variável temporária selecao_metais_aux o último valor da seleção de metais sem alteração
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //ALTERA A SELEÇÃO DE METAIS
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					selecao_metais++; //Incrementa selecao_metais
					if(selecao_metais > 100) //Se seleção de metais for maior que 100 então
					{
						selecao_metais = 1; //Seleção de metais é igual a 1
					}
					if(INCREMENTA) //Se tecla INCREMENTA pressionada. Trecho que funciona para incrementar ao ficar mantendo pressionada a tecla pressionada
					{
						delay_ms(200); //Espera 200ms para verificar se não foi ruido, passando de 200ms a tecla é reconhecida
						if(!INCREMENTA) //Se tecla INCREMENTA parou de ser pressionada antes de 200ms então limpa teclapressionada
						{
							teclapressionada = 0; //Limpa a tecla pressionada
						}
					}
					else //Senão
					{
						teclapressionada = 0; //Limpa a tecla pressionada
					}
					tela = TELA_MOSTRA_SELECAO_METAIS; //Tela é igual a TELA_MOSTRA_SELECAO_METAIS
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					fnAtualizaPerfil(SETA_PARAMETRO_OFF,SETA_PWM_ON,SETA_GRAVA_FLASH_OFF,SETA_POT_GANHO_OFF); //Atualiza ciclo de trabalho, defasagem, frequência e sensibilidade sem gravar na memória FLASH
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					selecao_metais--; //Decrementa selecao_metais
					if(selecao_metais < 1) //Se seleção de metais for menor que 1 então
					{
						selecao_metais = 100; //Seleção de metais é igual a 100
					}
					if(DECREMENTA) //Se tecla DECREMENTA pressionada. Trecho que funciona para incrementar ao ficar mantendo pressionada a tecla pressionada
						{
							delay_ms(200); //Espera 200ms para verificar se não foi ruido, passando de 200ms a tecla é reconhecida
							if(!DECREMENTA) //Se tecla DECREMENTA parou de ser pressionada antes de 200ms então limpa teclapressionada
							{
								teclapressionada = 0; //Limpa a tecla pressionada
							}
						}
						else //Senão
						{
							teclapressionada = 0; //Limpa a tecla pressionada
						}
					tela = TELA_MOSTRA_SELECAO_METAIS; //Tela é igual a TELA_MOSTRA_SELECAO_METAIS
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					fnAtualizaPerfil(SETA_PARAMETRO_OFF,SETA_PWM_ON,SETA_GRAVA_FLASH_OFF,SETA_POT_GANHO_OFF); //Atualiza ciclo de trabalho, defasagem, frequência e sensibilidade sem gravar na memória FLASH
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					tela = TELA_SELECAO_DE_METAIS; //Tela é igual a TELA_SELECAO_DE_METAIS
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					estado = ESTADO_AJUSTES_AVANCADOS; //Estado a ser executado é ESTADO_AJUSTES_AVANCADOS
					estadofnSelecaoMetais = 1; //Coloca a variável estadoAjusteSelecaoMetais para 1 para voltar a camada 1 desta função
					teclapressionada = 0; //Limpa teclapressionada
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU SELEÇÃO DE METAIS no primeiro nível
					Write_Buffer_FLASH[0] = selecao_metais; //Coloco a seleção de metais no vetor para gravação na memória FLASH
					ESCREVE_FLASH_INTERNA(endFLASHSelecaoMetais,1,0); //Escreve na memória FLASH a seleção de metais no endereço especificado
					fnGravaAuditoria(3,selecao_metais_aux,selecao_metais,OPERADOR,DISPOSITIVO);
					break;
				}
				case teclaCancela:
				{
					tela = TELA_SELECAO_DE_METAIS; //Tela é igual a TELA_SELECAO_DE_METAIS
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					estado = ESTADO_AJUSTES_AVANCADOS; //Estado a ser executado é ESTADO_AJUSTES_AVANCADOS
					estadofnSelecaoMetais = 1; //Coloca a variável estadoAjusteSelecaoMetais para 1 para voltar a camada 1 desta função
					selecao_metais = selecao_metais_aux; //Retorno o último valor da seleção de metais antes de entrar no menu de alteração
					teclapressionada = 0; //Limpa teclapressionada
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU SELEÇÃO DE METAIS no primeiro nível
					fnAtualizaPerfil(SETA_PARAMETRO_OFF,SETA_PWM_ON,SETA_GRAVA_FLASH_OFF,SETA_POT_GANHO_OFF); //Atualiza ciclo de trabalho, defasagem, frequência e sensibilidade sem gravar na memória FLASH
					break;
				}
				break;
			}
			break;
		}
		break;
	}
}



void fnCorrigeSelecao(void)
{
	static float num;
	static int num_int;

	aux_selecao_metais = selecao_metais;
	if(selecao_metais > 50 && selecao_metais <= 90)
	{
		num = ((float)(selecao_metais) - 50) / 2;
		num_int = num;
		if( (num - num_int) >= 0.5)
		{
			selecao_metais = (((selecao_metais - 50) / 2) + 1) + 50;
		}
		else
		{
			selecao_metais = ((selecao_metais - 50) / 2) + 50;
		}
	 }
	 else if(selecao_metais > 90)
	 {
		 selecao_metais = (selecao_metais - 70) + 50;
	 }
	 else if(selecao_metais >= 10 && selecao_metais < 50)
	 {
		 num = (50 - (float)(selecao_metais)) / 2;
		 num_int = num;
		 if( (num - num_int) >= 0.5)
		 {
			 selecao_metais = 50 - (((50 - selecao_metais) / 2) + 1);
		 }
		 else
		 {
			 selecao_metais = 50 - ((50 - selecao_metais) / 2);
		 }
	  }
	  else if(selecao_metais < 10)
	  {
		  selecao_metais = 50 - (30 - selecao_metais);
	  }
}




void fnTrava(void) //Permite travar o detector
{
	static byte estadofnTrava = 1; //Definindo variável estadofnTrava para o switch case abaixo
	static byte aux_pulso_trava,aux_sinal_trava; //Definindo variáveis aux_pulso_trava e aux_sinal_trava para recuperar o último valor caso seja alterado e seja pressionado a tecla CANCELA

	switch(estadofnTrava) //Conforme variável vai para o case específico
	{
		case 1: //ENTRA NO MENU DE ALTERAÇÃO DO SINAL DA TRAVA
		{
			estadofnTrava = 2; //Coloca a variável estadofnTrava para 2 para ir para o próximo case
			tela = TELA_MOSTRA_TRAVA; //Tela é igual a TELA_MOSTRA_TRAVA
			estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
			aux_pulso_trava = pulso_trava; //Salva o último valor de pulso_trava antes de alterar
			aux_sinal_trava = sinal_trava; //Salva o último valor de sinal da trava antes de alterar
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2:	//ALTERA O SINAL DA TRAVA
		{
			switch(teclapressionada) //Conforme teclapressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					sinal_trava++; //Incrementa sinal_trava
					if(sinal_trava > trava_retencao_controle_teclado) //Se sinal_trava for maior que trava_retencao_controle_teclado então
					{
						sinal_trava = trava_pulso; //Armazena na variável sinal_trava o valor trava_pulso
					}
					tela = TELA_MOSTRA_TRAVA; //Tela é igual a TELA_MOSTRA_TRAVA
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					sinal_trava--; //Decrementa sinal_trava
					if(sinal_trava < trava_pulso) //Se sinal_trava for menor que trava_pulso então
					{
						sinal_trava = trava_retencao_controle_teclado; //Armazena na variável sinal_trava o valor trava_retencao_controle_teclado
					}
					tela = TELA_MOSTRA_TRAVA; //Tela é igual a TELA_MOSTRA_TRAVA
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					if(sinal_trava == trava_pulso) //Se sinal_trava for igual a trava_pulso
					{
						tela = TELA_DIGITE_PULSO_TRAVA; //Tela é igual a TELA_DIGITE_PULSO_TRAVA
						estadofnTrava = 3; //Coloca a variável estadofnTrava para 3 para ir para o próximo case
					}
					else if(sinal_trava == trava_retencao_controle || sinal_trava == trava_retencao_controle_teclado) //Se sinal_trava for igual a trava_retencao_controle ou trava_retencao_controle_teclado
					{
						Write_Buffer_FLASH[0] = sinal_trava; //Coloca o sinal da trava no vetor para gravação na memória FLASH
						ESCREVE_FLASH_INTERNA(endFLASHSinalTrava,1,0); //Escreve na memória FLASH o sinal da trava no endereço especificado
						fnGravaAuditoria(4,aux_sinal_trava,sinal_trava,OPERADOR,DISPOSITIVO);
						flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU TRAVA no primeiro nível
						estado = ESTADO_AJUSTES_AVANCADOS; //Estado a ser executado é ESTADO_AJUSTES_AVANCADOS
						estadofnTrava = 1; //Coloca a variável estadofnTrava para 1 para voltar a camada 1 desta função
					}
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					teclapressionada = 0; //Limpa a teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tela = TELA_TRAVA; //Tela é igual a TELA_TRAVA
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					estadofnTrava = 1; //Coloca a variável estadofnTrava para 1 para voltar a camada 1 desta função
					estado = ESTADO_AJUSTES_AVANCADOS; //Estado a ser executado é ESTADO_AJUSTES_AVANCADOS
					teclapressionada = 0; //Limpa teclapressionada
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU TRAVA no primeiro nível
					break;
				}
				break;
			}
			break;
		}
		case 3:	//ALTERA O TEMPO DE PULSO DA TRAVA DE 1s a 5s
		{
			switch(teclapressionada) //Conforme teclapressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					pulso_trava++; //Incrementa pulso_trava
					if(pulso_trava > 50) //Se pulso_trava for maior que 5 segundos então
					{
						pulso_trava = 10; //Armazena 1 segundo na variável pulso trava, 10 * 100ms = 1 segundo por causa do timer de 100ms
					}
					tela = TELA_DIGITE_PULSO_TRAVA; //Tela é igual a TELA_DIGITE_PULSO_TRAVA
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					pulso_trava--; //Decrementa pulso_trava
					if(pulso_trava < 10) //Se pulso_trava for menor que 1 segundo então
					{
						pulso_trava = 50; //Armazena 5 segundo na variável pulso trava, 50 * 100ms = 5 segundo por causa do timer de 100ms
					}
					tela = TELA_DIGITE_PULSO_TRAVA; //Tela é igual a TELA_DIGITE_PULSO_TRAVA
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					sinal_trava = trava_pulso; //Armazena na variável sinal_trava o valor trava_pulso
					Write_Buffer_FLASH[0] = sinal_trava; //Coloca o sinal da trava no vetor para gravação na memória FLASH
					ESCREVE_FLASH_INTERNA(endFLASHSinalTrava,1,0); //Escreve na memória FLASH o sinal da trava no endereço especificado
					fnGravaAuditoria(4,aux_sinal_trava,sinal_trava,OPERADOR,DISPOSITIVO);

					delay_ms(100); //Espera 100 milisegundos

					Write_Buffer_FLASH[0] = pulso_trava; //Armazena na variável pulso_trava o valor do tempo do pulso
					ESCREVE_FLASH_INTERNA(endFLASHPulsoTrava,1,0); //Escreve na memória FLASH o pulso da trava no endereço especificado
					fnGravaAuditoria(5,aux_pulso_trava,pulso_trava,OPERADOR,DISPOSITIVO);

					estadofnTrava = 2; //Coloca a variável estadofnTrava para 2 para ir para o case 2
					tela = TELA_MOSTRA_TRAVA; //Tela é igual a TELA_MOSTRA_TRAVA
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					fnLigaPulsoTrava(); //Permite pulsar a trava no tempo especificado
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU TRAVA no primeiro nível
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela:
				{
					estadofnTrava = 2; //Coloca a variável estadofnTrava para 2 para ir para o case 2
					tela = TELA_MOSTRA_TRAVA; //Tela é igual a TELA_MOSTRA_TRAVA
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU TRAVA no primeiro nível
					teclapressionada = 0; //Limpa teclapressionada
					pulso_trava = aux_pulso_trava; //Salva na variável pulso_trava o último valor armazenado antes de qualquer alteração
					break;
				}
				break;
			}
			break;
		}
		break;
	}
}


void fnLigaPulsoTrava(void) //Permite pulsar a trava
{
	if(statusPGDM !=1){
		LIGA_TRAVA; //Energiza a trava
		if(sinal_rele == rele_pulso) //Se sinal_rele for igual a rele_pulso então
		{
			fnLigaPulsoRele(); //Permite pulsar o relé pelo tempo especificado
		}
		else if(sinal_rele == trava_retencao_controle || sinal_rele == trava_retencao_controle_teclado) //Se sinal_rele for igual a trava_retencao_controle ou trava_retencao_controle_teclado então
		{
			LIGA_RELE; //Somente energiza relé sem pulsar
		}
		LIGA_SINALEIRA_VERMELHA; //Liga sinaleira vermelha
		tempo_pulso_trava = 0; //Zera a variável tempo_pulso_trava para reiniciar o tempo
		HABILITA_TEMPO_PULSO_TRAVA = TRUE; //Torna a flag HABILITA_TEMPO_PULSO_TRAVA para TRUE para voltar a contar o tempo de pulso da trava novamente
	}
}


void fnRele(void) //Permite ligar energizar o relé
{
	static byte estadofnRele = 1; //Definindo variável estadofnRele para o switch case abaixo
	static byte aux_pulso_rele,aux_sinal_rele; //Definindo variáveis aux_pulso_rele e aux_sinal_rele para recuperar o último valor caso seja alterado e seja pressionado a tecla CANCELA

	switch(estadofnRele) //Conforme variável vai para o case específico
	{
		case 1: //ENTRA NO MENU DE ALTERAÇÃO DO SINAL DO RELÉ
		{
			estadofnRele = 2; //Coloca a variável estadofnRele para 2 para ir para o case 2
			tela = TELA_MOSTRA_RELE; //Tela é igual a TELA_MOSTRA_RELE
			estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
			aux_pulso_rele = pulso_rele; //Salva o último valor de pulso_rele antes de alterar
			aux_sinal_rele = sinal_rele; //Salva o último valor de sinal_rele antes de alterar
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //ALTERA O SINAL DO RELÉ
		{
			switch(teclapressionada) //Conforme teclapressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					sinal_rele++; //Incrementa sinal_rele
					if(sinal_rele > rele_retencao) //Se sinal_rele for maior que rele_retencao então
					{
						sinal_rele = rele_pulso; //Armazena rele_pulso em sinal_rele
					}
					tela = TELA_MOSTRA_RELE; //Tela é igual a TELA_MOSTRA_RELE
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					sinal_rele--; //Decrementa sinal_rele
					if(sinal_rele < rele_pulso) //Se sinal_rele for menor que rele_pulso então
					{
						sinal_rele = rele_retencao; //Armazena rele_retencao em sinal_rele
					}
					tela = TELA_MOSTRA_RELE; //Tela é igual a TELA_MOSTRA_RELE
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					teclapressionada = 0; //Limpa teclapresionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					if(sinal_rele == rele_pulso) //Se sinal_rele for igual a rele_pulso então
					{
						tela = TELA_DIGITE_PULSO_RELE; //Tela é igual a TELA_DIGITE_PULSO_RELE
						estadofnRele = 3; //Coloca a variável estadofnRele para 3 para ir para o case 3
					}
					else if(sinal_rele == rele_retencao) //Senão se sinal_rele for igual a rele_retencao então
					{
						Write_Buffer_FLASH[0] = sinal_rele; //Coloca o sinal do rele no vetor para gravação na memória FLASH
						ESCREVE_FLASH_INTERNA(endFLASHSinalRele,1,0); //Escreve na memória FLASH o sinal do rele no endereço especificado
						fnGravaAuditoria(6,aux_sinal_rele,sinal_rele,OPERADOR,DISPOSITIVO);
						flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU RELE no primeiro nível
						estado = ESTADO_AJUSTES_AVANCADOS; //Estado a ser executado é ESTADO_AJUSTES_AVANCADOS
						estadofnRele = 1; //Coloca a variável estadofnRele para 1 para voltar ao primeiro nível deste menu
					}
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tela = TELA_RELE; //Tela é igual a TELA_RELE
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					estadofnRele = 1; //Coloca a variável estadofnRele para 1 para voltar ao primeiro nível deste menu
					estado = ESTADO_AJUSTES_AVANCADOS; //Estado a ser executado é ESTADO_AJUSTES_AVANCADOS
					teclapressionada = 0; //Limpa teclapressionada
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU RELE no primeiro nível
					break;
				}
				break;
			}
			break;
		}
		case 3:	//ALTERA O TEMPO DE PULSO DO RELÉ DE 0.1s a 15.0s
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					pulso_rele++; //Incrementa pulso_rele
					if(pulso_rele > 150) //Se pulso_rele for maior que 15 segundos então
					{
						pulso_rele = 1; //Armazena em pulso_rele 100 milisegundos pois 1 * 100ms do temporizador é 100ms.
					}
					tela = TELA_DIGITE_PULSO_RELE; //Tela é igual a TELA_DIGITE_PULSO_RELE
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					if(INCREMENTA) //Se tecla INCREMENTA pressionada. Trecho que funciona para incrementar ao ficar mantendo pressionada a tecla pressionada
					{
						delay_ms(200); //Espera 200ms para verificar se não foi ruido, passando de 200ms a tecla é reconhecida
						if(!INCREMENTA) //Se tecla INCREMENTA parou de ser pressionada antes de 200ms então limpa teclapressionada
						{
							teclapressionada = 0; //Limpa a tecla pressionada
						}
					}
					else //Senão
					{
						teclapressionada = 0; //Limpa a tecla pressionada
					}
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					pulso_rele--; //Decrementa pulso_rele
					if(pulso_rele < 1) //Se pulso_rele for menor que 100 milisegundos então
					{
						pulso_rele = 150; //Armazena em pulso_rele 15 segundos pois 15 * 100ms = 15000ms que é igual a 15 segundos
					}
					tela = TELA_DIGITE_PULSO_RELE; //Tela é igual a TELA_DIGITE_PULSO_RELE;
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					if(DECREMENTA) //Se tecla INCREMENTA pressionada. Trecho que funciona para incrementar ao ficar mantendo pressionada a tecla pressionada
					{
						delay_ms(200); //Espera 200ms para verificar se não foi ruido, passando de 200ms a tecla é reconhecida
						if(!DECREMENTA) //Se tecla DECREMENTA parou de ser pressionada antes de 200ms então limpa teclapressionada
						{
							teclapressionada = 0; //Limpa a tecla pressionada
						}
					}
					else //Senão
					{
						teclapressionada = 0; //Limpa a tecla pressionada
					}
					break;
				}
				case teclaConfirma: //Caso a tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					sinal_rele = rele_pulso; //Armazena em sinal_rele o valor rele_pulso
					Write_Buffer_FLASH[0] = sinal_rele; //Coloca o sinal do rele no vetor para gravação na memória FLASH
					ESCREVE_FLASH_INTERNA(endFLASHSinalRele,1,0); //Escreve na memória FLASH o sinal do rele no endereço especificado
					fnGravaAuditoria(6,aux_sinal_rele,sinal_rele,OPERADOR,DISPOSITIVO);

					delay_ms(100); //Espera 100 milisegundos

					Write_Buffer_FLASH[0] = pulso_rele; //Coloca o pulso do rele no vetor para gravação na memória FLASH
					ESCREVE_FLASH_INTERNA(endFLASHPulsoRele,1,0); //Escreve na memória FLASH o pulso do rele no endereço especificado
					fnGravaAuditoria(7,aux_pulso_rele,pulso_rele,OPERADOR,DISPOSITIVO);

					estadofnRele = 2; //Coloca a variável estadofnRele para 2 para ir para o case 2
					tela = TELA_MOSTRA_RELE; //Tela é igual a TELA_MOSTRA_RELE
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					fnLigaPulsoRele(); //Permite pulsar o relé pelo tempo especificado
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU RELE no primeiro nível
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Caso a tecla CANCELA pressionada então
				{
					estadofnRele = 2;  //Coloca a variável estadofnRele para 2 para ir para o case 2
					tela = TELA_MOSTRA_RELE; //Tela é igual a TELA_MOSTRA_RELE
					pulso_rele = aux_pulso_rele; //Retorno o último valor do pulso_rele antes de entrar no menu de alteração
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU RELE no primeiro nível
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				break;
			}
			break;
		}
		break;
	}
}


void fnLigaPulsoRele(void) //Permite pulsar o relé
{
	LIGA_RELE; //Energiza o relé
	tempo_pulso_rele = 0; //Zera a variável tempo_pulso_rele para contar o tempo
	HABILITA_TEMPO_PULSO_RELE = TRUE; //Torna a flag HABILITA_TEMPO_PULSO_RELE para TRUE para poder iniciar a contagem de tempo
}

void fnControleRemoto(void) //Permite cadastrar e descadastrar no máximo 3 controles remotos
{
	static byte estadofnControleRemoto = 1; //Definindo variável estadofnControleRemto para o switch case abaixo

	switch(estadofnControleRemoto) //Conforme valor da variável estadofnControleRemoto vai para o case específico
	{
		case 1: //ENTRA NO MENU PARA CADASTRAR OU DESCADASTRAR CONTROLES
		{
			menu1 = 1; //Faz com menu1 seja 1 para que apareça primeiro o submenu CADASTRAR CONTROLES
			estadofnControleRemoto = 2; //Coloca a variável estadofnControleRemoto para 2 para ir para o case 2
			tela = TELA_CADASTRAR_CONTROLES; //Tela é igual a TELA_CADASTRAR_CONTROLES
			estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2:	//PERMITE ESCOLHER ENTRE ENTRAR NO MENU CADASTRAR CONTROLES OU MENU DESCADASTRAR CONTROLES
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					menu1++; //Incrementa menu1
					if(menu1 > 2) //Se menu1 for maior que 2 então
					{
						menu1 = 1; //Armazena em menu1 o valor 1
					}
					tela = TELA_MOSTRA_CONTROLE_REMOTO; //Tela é igual a TELA_MOSTRA_CONTROLE_REMOTO
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					teclapressionada = 0; //Limpa tecla pressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					menu1--; //Decrementa menu1
					if(menu1 < 1) //Se menu1 for menor que 1 então
					{
						menu1 = 2; //Armazena em menu1 o valor 2
					}
					tela = TELA_MOSTRA_CONTROLE_REMOTO; //Tela é igual a TELA_MOSTRA_CONTROLE_REMOTO
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					if(menu1 == 1) //Se menu1 for igual a 1
					{
						defineTipoControle();
						if(numero_controles < 3) //Se numero_controles for menor que 3 então
						{
							INICIA_CONTADOR_PULSOS = FALSE; //Torna a flag INICIA_CONTADOR_PULSOS para FALSE para poder contar pulsos e poder reconhecer se o cadstro do controle foi efetuado com sucesso
							ACAO_CONTROLE = NENHUM; //Torna a flag ACAO_CONTROLE igual a NENHUM para poder após leitura de pulsos tomar a devida ação
							pulsos = 0;
							start_remoto = 0;
							start_remoto1 = 0;

							CLEAR_PROG; //Coloca para nivel zero a tecla PROG para poder informar ao receptor do controle que quer cadastrar controles
							delay_ms(350); //Espera 1 segundo em nivel baixo - Reduzido para 350ms
							SET_PROG; //Retorna para nivel 1 a tecla PROG
//							tela = TELA_PRESSIONE_QUALQUER_TECLA_DO_CONTROLE; //Tela é igual a TELA_PRESSIONE_QUALQUER_TECLA_DO_CONTROLE
							estadofnControleRemoto = 3; //Coloca a variável estadofnControleRemoto para 3 para ir para o case 3
							ACAO_CONTROLE = CADASTRAR1;
						}
						else //Senão
						{
							tela = TELA_NUMERO_MAXIMO_CONTROLES; //Tela é igual a TELA_NUMERO_MAXIMO_CONTROLES
							Atualiza_LCD(); //Atualiza o LCD com a mensagem NÃO É POSSÍVEL CADAST. MAIS CTRL (não é possível cadastrar mais controles)
							tela = TELA_MOSTRA_CONTROLE_REMOTO; //Tela é igual a TELA_MOSTRA_CONTROLE_REMOTO
							estadofnControleRemoto = 2; //Coloca a variável estadofnControleRemoto para 2 para ir para o case 2
							estado = ESTADO_CONFIGURA_CONTROLE_REMOTO; //Estado a ser executado é ESTADO_CONFIGURA_CONTROLE_REMOTO
						}
					}
					else if(menu1 == 2) //Senão se menu1 for igual a 2 então
					{
						estadofnControleRemoto = 4; //Coloca a variável estadofnControleRemoto para 4 para ir para o case 4
					}
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					teclapressionada = 0; //Limpa a teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tela = TELA_CONTROLE_REMOTO; //Tela é igual a TELA_CONTROLE_REMOTO
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					estadofnControleRemoto = 1; //Coloca a variável estadofnControleRemoto para 1 para ir para o nível 1 deste menu
					estado = ESTADO_AJUSTES_AVANCADOS; //Estado a ser executado é ESTADO_CONFIGURA_CONTROLE_REMOTO
					teclapressionada = 0; //Limpa teclapressionada
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU RELE no primeiro nível
					break;
				}
				break;
			}
			break;
		}
		case 3: //CADASTRO DOS CONTROLES REMOTOS
		{
			tempo_cadastro_controle = 0; //Zera a variável tempo_cadastro_controle para poder controlar o tempo de cadastro caso não seja pressionada nenhuma tecla
			while(tempo_cadastro_controle <= TEMPO_MAXIMO_CADASTRO_CONTROLE && RESULTADO_CONTROLE == NENHUM); //Enquanto tempo_cadastro_controle for menor que 25 segundos e RESULTADO_CONTROLE for NENHUM fica em loop aqui
			if(tempo_cadastro_controle < TEMPO_MAXIMO_CADASTRO_CONTROLE && RESULTADO_CONTROLE == CADASTRADO) //Se tempo_cadastro_controle for menor que 25 segundos e RESULTADO_CONTROLE for igual a CADASTRADO significa que o receptor envio uma informação de que foi cadastrado com sucesso
			{
				tela = TELA_ADICIONADO_COM_SUCESSO; //Tela é igual a TELA_ADICIONADO_COM_SUCESSO
				fnGravaAuditoria(8,0,1,OPERADOR,DISPOSITIVO);
				RESULTADO_CONTROLE = NENHUM; //Armazena em RESULTADO_CONTROLE a informação NENHUM para inicializar o método de cadastro
				indexControle[numero_controles - 1] = tipoControle;
				Write_Buffer_FLASH[0] = tipoControle;
				ESCREVE_FLASH_INTERNA((endFLASH_TIPO_CONTROLE + (numero_controles-1)),1,0);
			}
			else if(tempo_cadastro_controle < TEMPO_MAXIMO_CADASTRO_CONTROLE && RESULTADO_CONTROLE == JA_CADASTRADO) //Senão se tempo_cadastro_controle for menor que 25 segundos e RESULTADO_CONTROLE for igual a JA_CADASTRADO então
			{
				tela = TELA_CONTROLE_JA_CADASTRADO; //Tela é igual a TELA_CONTROLE_JA_CADASTRADO
				RESULTADO_CONTROLE = NENHUM; //Armazena em RESULTADO_CONTROLE a informação NENHUM para inicializar o método de cadastro
			}
			else if(tempo_cadastro_controle >= TEMPO_MAXIMO_CADASTRO_CONTROLE || RESULTADO_CONTROLE == NENHUM) //Senão se tempo_cadastro_controle for maior igual a 25 segundos ou RESULTADO_CONTROLE for igual a NENHUM então
			{
				tela = TELA_ERRO_CONTROLE_NAO_CADASTRADO; //Tela é igual a TELA_ERRO_CONTROLE_NAO_CADASTRADO
			}

			Atualiza_LCD(); //Atualiza o LCD com alguma das telas conforme decisão acima
			tela = TELA_MOSTRA_CONTROLE_REMOTO; //Tela é igual a TELA_MOSTRA_CONTROLE_REMOTO
			estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
			estadofnControleRemoto = 2; //Coloca a variável estadofnControleRemoto para 2 para ir para o case 2
			estado = ESTADO_CONFIGURA_CONTROLE_REMOTO; //Estado a ser executado é ESTADO_CONFIGURA_CONTROLE_REMOTO
			break;
		}
		case 4: //DESCADASTRO DE CONTROLES REMOTOS
		{
			INICIA_CONTADOR_PULSOS = FALSE;
			tela = TELA_APAGANDO; //Tela é igual a TELA_APAGANDO
			Atualiza_LCD(); //Atualiza o LCD com a tela acima
			CLEAR_PROG; //Coloca para nivel zero a tecla PROG para poder informar ao receptor do controle que quer descadastrar controles
			delay_ms(2000); //Alterado p/ 2s.Espera 100 milisegundos para dar tempo de entrar no while sem sair
			tempo_leitura_botao_prog = 0; //Zera a variável tempo_leitura_botao_prog para poder contar tempo e saber se o desejo é cadastrar ou apagar controles
			while(tempo_leitura_botao_prog < 10 && VT); //Invertido condição de VT. Enquanto tempo_leitura_botao_prog for menor que 10 segundos e o sinal do LED (VT) for nivel baixo fica em loop
			tempo_leitura_botao_prog = 0;	//Alterado para zerar variável após VT
			SET_PROG; //Retorna para nivel 1 a tecla PROG
			delay_ms(500);
			while(tempo_leitura_botao_prog < 10 && !VT); //Espera que VT retorne a FALSE p/ indicad descastro com sucesso, se não ocorrer após 10s dá continuidade com aviso de erro
			delay_ms(100);
			if(ACAO_CONTROLE == APAGAR && INICIA_CONTADOR_PULSOS == FALSE && VT && tempo_leitura_botao_prog < 10) //Se ACAO_CONTROLE for APAGAR e INICIA_CONTADOR_PULSOS for FALSE e sinal do LED (VT) for nivel alto e tempo_leitura_botao_prog for menor que 10 então
			{
				RESULTADO_CONTROLE = APAGADO; //Armazena na variável RESULTADO_CONTROLE a informação APAGADO
//				ACAO_CONTROLE = NENHUM; //Armazena na variável ACAO_CONTROLE a informação NENHUM
				INICIA_CONTADOR_PULSOS = FALSE; //Armazena na variável INICIA_CONTADOR_PULSOS a informação FALSE
				start_remoto = 0; //Zera a variável start_remoto que mede a largura dos pulsos
				pulsos = 0; //Zera a variável pulsos que conta o número de pulsos
				numero_controles = 0; //Zera a variável numero_controles
				Write_Buffer_FLASH[0] = numero_controles; //Coloca o numero_controles no vetor para gravação na memória FLASH
				ESCREVE_FLASH_INTERNA(endFLASHNumeroControles,1,0); //Escreve na memória FLASH o numero_controles no endereço especificado
				fnGravaAuditoria(9,0,1,OPERADOR,DISPOSITIVO);
			}
			else /*if(tempo_leitura_botao_prog >= 10) //Senão se tempo_leitura_botao_prog for maior igual a 10 segundos*/
			{
				RESULTADO_CONTROLE = NAO_APAGADO; //Armazena na variável RESULTADO_CONTROLE a informação NAO_APAGADO
			}
			if(RESULTADO_CONTROLE == APAGADO) //Se RESULTADO_CONTROLE for APAGADO então
			{
				RESULTADO_CONTROLE = NENHUM; //Armazena na variável RESULTADO_CONTROLE a informação NENHUM
				tela = TELA_DESCADASTRO_COM_SUCESSO; //Tela é igual a TELA_DESCADASTRO_COM_SUCESSO
				Atualiza_LCD(); //Atualiza o LCD com a tela acima
				tela = TELA_CONTROLE_REMOTO; //Tela é igual a TELA_CONTROLE_REMOTO
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				estadofnControleRemoto = 1; //Coloca a variável estadofnControleRemoto para 1 para ir para o nivel 1 deste menu
				estado = ESTADO_AJUSTES_AVANCADOS; //Estado a ser executado é ESTADO_AJUSTES_AVANCADOS
				flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU CONTROLE REMOTO no primeiro nível
				break;
			}
			else if(RESULTADO_CONTROLE == NAO_APAGADO) //Se RESULTADO_CONTROLE for NAO_APAGADO então
			{
				RESULTADO_CONTROLE = NENHUM; //Armazena na variável RESULTADO_CONTROLE a informação NENHUM
				tela = TELA_CONTROLES_NAO_APAGADOS; //Tela é igual a TELA_CONTROLES_NAO_APAGADOS
				Atualiza_LCD(); //Atualiza LCD com a tela acima
				tela = TELA_CONTROLE_REMOTO; //Tela é igual a TELA_CONTROLE_REMOTO
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				estadofnControleRemoto = 1; //Coloca a variável estadofnControleRemoto para 1 para ir para o nivel 1 deste menu
				estado = ESTADO_AJUSTES_AVANCADOS; //Estado a ser executado é ESTADO_AJUSTES_AVANCADOS
				flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU CONTROLE REMOTO no primeiro nível
				break;
			}
			break;
		}
		break;
	}
}

void fnInfravermelho(void) //Permite calibrar os infravermelhos e desativar ou ativar a permissão de detectar mediante passagem pelos infravermelhos no sentido rua-agência
{
	static byte estadoInfravermelho = 1; //Definindo variável estadoInfravermelho para o switch case abaixo
	static byte sensibilidadeir_aux,analiseir_aux; //Definindo variáveis sensibilidadeir_aux e analiseir_aux para recuperar o último valor caso seja alterado e seja pressionado a tecla CANCELA

	switch(estadoInfravermelho) //Conforme valor da variável estadoInfravermelho vai para o case específico
	{
		case 1: //ENTRA NO MENU INFRAVERMELHO PARA CALIBRAR IR ou SETAR ANALISE IR
		{
			tela = TELA_MOSTRA_INFRAVERMELHO; //Tela é igual a TELA_MOSTRA_INFRAVERMELHO
			estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
			estadoInfravermelho = 2; //Coloca a variável estadoInfravermelho para 2 para ir para o case 2
			sensibilidadeir_aux = sensibilidadeir; //Salva o último valor de sensibilidadeir antes de alterar
			analiseir_aux = analiseir; //Salva o último valor de analiseir antes de alterar
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //ESCOLHE ENTRE O MENU CALIBRA IR ou ANALISE IR
		{
			switch (teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					menu1++; //Incrementa menu1
					if(menu1 > 2) //Se menu1 for maior que 2 então
					{
						menu1 = 1; //Armazena na variável menu1 o valor 1
					}
					tela = TELA_MOSTRA_INFRAVERMELHO; //Tela é igual a TELA_MOSTRA_INFRAVERMELHO
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					teclapressionada = 0; //Limpa tecla pressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					menu1--; //Decrementa menu1
					if(menu1 < 1) //Se menu1 for menor que 1 então
					{
						menu1 = 2; //Armazena na variável menu1 o valor 2
					}
					tela = TELA_MOSTRA_INFRAVERMELHO; //Tela é igual a TELA_MOSTRA_INFRAVERMELHO
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					if(menu1 == 1) //Se menu1 for igual a 1 então
					{
						tela = TELA_SETA_CALIBRAR_IR; //Tela é igual a TELA_SETA_CALIBRAR_IR
						estadoInfravermelho = 3; //Coloca a variável estadoInfravermelho para 3 para ir para o case 3
					}
					else if(menu1 == 2) //Se menu1 for igual a 2 então
					{
						tela = TELA_SETA_ANALISE_IR; //Tela é igual a TELA_SETA_ANALISE_IR
						estadoInfravermelho = 4; //Coloca a variável estadoInfravermelho para 4 para ir para o case 4
					}
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tela = TELA_INFRAVERMELHO; //Tela é igual a TELA_INFRAVERMELHO
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					estado = ESTADO_AJUSTES_AVANCADOS; //Estado a ser executado é ESTADO_AJUSTES_AVANCADOS
					estadoInfravermelho = 1; //Coloca a variável estadoInfravermelho para 1 para ir para o nivel 1 deste menu
					teclapressionada = 0; //Limpa teclapressionada
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU INFRAVERMELHO no primeiro nível
					break;
				}
				break;
			}
			break;
		}
		case 3: //CALIBRA O IR
		{
			//O receptor infravermelho fica em nivel lógico 0 quando esta recebendo corretamente PWM do infravermelho
			//Quando o feixe infravermelho esta sendo interrompido o receptor infravermelho fica em nivel lógico 1
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla DECREMENTA ou tecla TRAVA ou tecla DESTRAVA pressionada então
				case teclaDecrementa:
				case teclaTrava:
				case teclaDestrava:
				{
					if(confirma == NAO) //Se confirma for igual a NAO então
					{
						confirma = SIM; //Armazena na variável confirma a informação SIM
						LINHA = 2; //Se posiciona na linha 2
						COLUNA = 2; //Se posiciona na coluna 2
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada anteriormente
						EscreveChar(' '); //Escreve espaço na posição especificada
						COLUNA = 15; //Se posiciona na coluna 15
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada anteriormente
						EscreveChar('X'); //Escreve X na posição especificada
						estadoInfravermelho = 3; //Coloca a variável estadoInfravermelho para 3 para ir para o case 3
						teclapressionada = 0; //Limpa a teclapressionada
						break;
					}
					else if(confirma == SIM) //Senão se confirma for igual a SIM então
					{
						confirma = NAO; //Armazena na variável confirma a informação NAO
						LINHA = 2; //Se posiciona na linha 2
						COLUNA = 2; //Se posiciona na coluna 2
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada anteriormente
						EscreveChar('X'); //Escreve X na posição especificada
						COLUNA = 15; //Se posiciona na coluna 15
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada anteriormente
						EscreveChar(' '); //Escreve espaço na posição especificada
						estadoInfravermelho = 3; //Coloca a variável estadoInfravermelho para 3 para ir para o case 3
						teclapressionada = 0; //Limpa a teclapressionada
						break;
					}
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					if(confirma == SIM) //Se confirma for igual a SIM então
					{
						  sensibilidadeir = 0; //Armazena na variável sensibilidadeir o valor zero

						  for(x = 1;x < 13;x++) //Ajuste de sensibilidade ir de 5% a 60% em passos de 5%
						  {
							  sensibilidadeir = x * 13; //255/13 = 19 passos de 5%, 13 é 5%, 26 é 10%
							  tela = TELA_MOSTRA_CALIBRANDO; //Tela é igual a TELA_MOSTRA_CALIBRANDO
							  Atualiza_LCD(); //Atualiza o LCD com a tela acima
							  PWM_INFRAS_SetRatio8(sensibilidadeir); //Seta o PWM do infra com a primeira proporção para verificar se esta detectando o feixe
							  delay_ms(200); //Espera 200 milisegundos
							  var_infra1 = 0; //Zera a variável var_infra1 para verificar se o receptor esta lendo o feixe de infravermelho
							  var_infra2 = 0; //Zera a variável var_infra2 para verificar se o receptor esta lendo o feixe de infravermelho
							  time_debouncing_infra = 0; //Zera a variável time_debouncing_infra para poder fazer a leitura do feixe IR durante 1000 milisegundos
							  while(time_debouncing_infra < 1000) //Enquanto time_debouncing_infra for menor que 1000 milisegundos então
							  {
								  if(INFRA1_ATIVO) //Se INFRA1 não esta detectando o PWM do infravermelho significa que houve uma interrupçao do feixe por algo então
								  {
									  var_infra1 = 1; //Armazena na variável var_infra1 o valor 1 para indicar que houve detecção do PWM do ir no receptor ir
								  }
								  if(INFRA2_ATIVO) //Se INFRA1 não esta detectando o PWM do infravermelho significa que houve uma interrupção do feixe por algo então
								  {
									  var_infra2 = 1; //Armazena na variável var_infra1 o valor 1 para indicar que houve detecção do PWM do ir no receptor ir
								  }
							  }
							  if(var_infra1 == 0 && var_infra2 == 0) //Se em algum momento os receptores infravermelhos estiverem lendo corretamente então
							  {
								  x = 13; //Faz isso para sair do laço for pois ambos os receptores infravermelhos estão lendo os feixes PWM emitidos pelos emissores infravermelhos
							  }
							  delay_ms(1000); //Espera 1000 milisegundos
						  }
						  if(!var_infra1 && !var_infra2) //Se var_infra1 e var_infra2 for zero então seta o valor da calibração para o PWM dos infras
						  {
							  sensibilidadeir = sensibilidadeir + 13;
							  PWM_INFRAS_SetRatio8(sensibilidadeir); //Seta o PWM dos infras com o valor calibrado
							  Write_Buffer_FLASH[0] = sensibilidadeir; //Coloca a sensibilidadeir no vetor para gravação na memória FLASH
							  ESCREVE_FLASH_INTERNA(endFLASHSensibilidadeir,1,0); //Escreve na memória FLASH a sensibilidadeir no endereço especificado
							  fnGravaAuditoria(11,0,1,OPERADOR,DISPOSITIVO);
							  tela = TELA_MOSTRA_VALOR_CALIBRADO; //Tela é igual a TELA_MOSTRA_VALOR_CALIBRADO
							  Atualiza_LCD(); //Atualiza o LCD com a tela acima
						  }
						  else if(var_infra1 == 1 || var_infra2 == 1) //Senão se var_infra1 ou var_infra2 for igual a 1 então
						  {
							  sensibilidadeir = 0; //Armazena na variável sensibilidadeir o valor zero
							  PWM_INFRAS_SetRatio8(sensibilidadeir); //Seta o PWM dos infras com o valor zero
							  Write_Buffer_FLASH[0] = sensibilidadeir; //Coloca a sensibilidadeir no vetor para gravação na memória FLASH
							  ESCREVE_FLASH_INTERNA(endFLASHSensibilidadeir,1,0); //Escreve na memória FLASH a sensibilidadeir no endereço especificado
							  fnGravaAuditoria(11,0,1,OPERADOR,DISPOSITIVO);
							  tela = TELA_MOSTRA_ERRO_NOS_INFRAS; //Tela é igual a TELA_MOSTRA_ERRO_NOS_INFRAS
							  Atualiza_LCD(); //Atualiza o LCD com a tela acima
						  }
						  estadoInfravermelho = 2; //Coloca a variável estadoInfravermelho para 2 para ir para o case 2
						  tela = TELA_MOSTRA_INFRAVERMELHO; //Tela é igual a TELA_MOSTRA_INFRAVERMELHO
						  estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
						  teclapressionada = 0; //Limpa teclapressionada
					}
					else if(confirma == NAO) //Senão se confirma for igual a NAO então
					{
						estadoInfravermelho = 2; //Coloca a variável estadoInfravermelho para 2 para ir para o case 2
					}
					tela = TELA_MOSTRA_INFRAVERMELHO; //Tela é igual a TELA_MOSTRA_INFRAVERMELHO
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					confirma = NAO; //Armazena na variável confirma a informação NAO
					estadoInfravermelho = 2; //Coloca a variável estadoInfravermelho para 2 para ir para o case 2
					tela = TELA_MOSTRA_INFRAVERMELHO; //Tela é igual a TELA_MOSTRA_INFRAVERMELHO
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				break;
			}
			break;
		}
		case 4: //ACERTA O ESTADO ANALISEIR PARA SIM OU NÃO
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla DECREMENTA ou tecla TRAVA ou tecla DESTRAVA pressiona então
				case teclaDecrementa:
				case teclaTrava:
				case teclaDestrava:
				{
					if(analiseir == NAO) //Se analiseir for igual a NAO então
					{
						analiseir = SIM; //Armazena na variável analiser a informação SIM
						LINHA = 2; //Se posiciona na linha 2
						COLUNA = 2; //Se posiciona na coluna 2
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada
						EscreveChar(' '); //Escreve espaço na posição especificada
						COLUNA = 15; //Se posiciona na coluna 15
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada anteriormente
						EscreveChar('X'); //Escreve X na posição especificada
						estadoInfravermelho = 4; //Coloca a variável estadoInfravermelho para 4 para ir para o case 4
						teclapressionada = 0; //Limpa a teclapressionada
						break;
					}
					else if(analiseir == SIM) //Armazena na variável analiser a informação NAO
					{
						analiseir = NAO; //Armazena na variável analiser a informação N
						LINHA = 2; //Se posiciona na linha 2
						COLUNA = 2; //Se posiciona na coluna 2
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada anteriormente
						EscreveChar('X'); //Escreve X na posição especificada
						COLUNA = 15; //Se posiciona na coluna 15
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada anteriormente
						EscreveChar(' '); //Escreve espaço na posição especificada
						estadoInfravermelho = 4; //Coloca a variável estadoInfravermelho para 4 para ir para o case 4
						teclapressionada = 0; //Limpa a teclapressionada
						break;
					}
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					if(analiseir == SIM) //Se analiseir for igual a SIM então
					{
						analiseir = SIM; //Armazena na variável analiser a informação SIM
					}
					else if(analiseir == NAO) //Se analiseir for igual a NAO então
					{
						analiseir = NAO; //Armazena na variável analiser a informação NAO
					}
					tela = TELA_MOSTRA_INFRAVERMELHO; //Tela é igual a TELA_MOSTRA_INFRAVERMELHO
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					Write_Buffer_FLASH[0] = analiseir; //Coloca a analiseir no vetor para gravação na memória FLASH
					ESCREVE_FLASH_INTERNA(endFLASHAnaliseir,1,0); //Escreve na memória FLASH a analiseir no endereço especificado
					fnGravaAuditoria(10,analiseir_aux,analiseir,OPERADOR,DISPOSITIVO);
					estadoInfravermelho = 2; //Coloca a variável estadoInfravermelho para 2 para ir para o case 2
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					analiseir = analiseir_aux; //Recupera o último valor de analiseir salvo antes de alterar
					estadoInfravermelho = 2; //Coloca a variável estadoInfravermelho para 2 para ir para o case 2
					tela = TELA_MOSTRA_INFRAVERMELHO; //Tela é igual a TELA_MOSTRA_INFRAVERMELHO
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				break;
			}
			break;
		}
		break;
	}
}

void fnAnulaAreas(void) //Permite anular áreas de detecção que estão com defeito
{
	static byte estadoAnulaAreas = 1; //Definindo variável estadoAnulaAreas para o switch case abaixo
	static byte aux_anula_area[8] = {0,0,0,0,0,0,0,0}; //Definindo o vetor aux_anula_areas para recuperar o último valor caso seja alterado e seja pressionado a tecla CANCELA

	switch(estadoAnulaAreas) //Conforme valor da variável estadoAnulaAreas vai para o case específico
	{
		case 1: //ENTRA NO MENU ANULA ÁREAS
		{
			tela = TELA_MOSTRA_ANULA_AREA; //Tela é igual a TELA_MOSTRA_ANULA_AREA
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estadoAnulaAreas = 2; //Coloca a variável estadoAnulaAreas para 2 para ir para o case 2
			for(x = 0;x < 8;x++) //Armazena no vetor aux_anula_area a última especificação de cada área se é para ser anulada ou não antes de alterar
			{
				aux_anula_area[x] = anula_area[x]; //Armazena na variável aux_anula_area o conteúdo da variável anula_area
			}
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //ESCOLHE UMA DAS ÁREAS PARA CONFIGURAR SE ANULAR SIM OU NÃO
		{
			switch (teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					menu1++; //Incrementa menu1
					if(tipo_detector == Z3) //Se tipo_detector for igual a Z3 então
					{
						if(menu1 > 3) //Se menu1 for maior que 3 então
						{
							menu1 = 1; //Armazena na variável menu1 o valor 1
						}
					}
					else if(tipo_detector == Z8) //Senão se tipo_detector for igual a Z8 então
					{
						if(menu1 > 8) //Se menu1 for maior que 8 então
						{
							menu1 = 1; //Armazena na variável menu1 o valor 1
						}
					}
					tela = TELA_MOSTRA_ANULA_AREA; //Tela é igual a TELA_MOSTRA_ANULA_AREA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa:  //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					menu1--; //Decrementa menu1
					if(tipo_detector == Z3) //Se tipo_detector for igual a Z3 então
					{
						if(menu1 < 1) //Se menu1 for menor que 1 então
						{
							menu1 = 3; //Armazena na variável menu1 o valor 3
						}
					}
					else if(tipo_detector == Z8) //Senão se tipo_detector for igual a Z8 então
					{
						if(menu1 < 1) //Se menu1 for menor que 1 então
						{
							menu1 = 8; //Armazena na variável menu1 o valor 8
						}
					}
					tela = TELA_MOSTRA_ANULA_AREA; //Tela é igual a TELA_MOSTRA_ANULA_AREA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					tela = TELA_SETA_ANULAR_AREA; //Tela é igual a TELA_SETA_ANULAR_AREA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estadoAnulaAreas = 3; //Coloca a variável estadoAnulaAreas para 3 para ir para o case 3
					teclapressionada = 0; //Limpa a teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tela = TELA_ANULA_AREAS; //Tela é igual a TELA_ANULA_AREAS
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_AJUSTES_AVANCADOS; //Estado a ser executado é ESTADO_AJUSTES_AVANCADOS
					estadoAnulaAreas = 1; //Coloca a variável estadoAnulaAreas para 1 para ir para o primeiro nivel deste menu
					teclapressionada = 0; //Limpa a teclapressionada
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU ANULA AREAS no primeiro nível
					break;
				}
				break;
			}
			break;
		}
		case 3: //ALTERA PARA ANULAR SIM OU NÃO A ÁREA SELECIONADA NO MENU ANTERIOR
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Se tecla INCREMENTE ou tecla DECREMENTA ou tecla TRAVA ou tecla DESTRAVA pressionada então
				case teclaDecrementa:
				case teclaTrava:
				case teclaDestrava:
				{
					if(anula_area[menu1 - 1] == NAO) //Se anula_area específica de 1 a 8 for igual a NÃO então
					{
						anula_area[menu1 - 1] = SIM; //Armazena no vetor da área a informação SIM
						LINHA = 2; //Se posiciona na linha 2
						COLUNA = 2; //Se posiciona na coluna 2
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificadas
						EscreveChar(' '); //Escreve espaço na posição especificada
						COLUNA = 15; //Se posiciona na coluna 15
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada anteriormente
						EscreveChar('X'); //Escreve X na posição especificada
						estadoAnulaAreas = 3; //Coloca a variável estadoAnulaAreas para 3 para ir para o case 3
						teclapressionada = 0; //Limpa teclapressionada
					}
					else if(anula_area[menu1 - 1] == SIM) //Se anula_area específica de 1 a 8 for igual a SIM então
					{
						anula_area[menu1 - 1] = NAO; //Armazena no vetor da área a informação NAO
						LINHA = 2; //Se posiciona na linha 2
						COLUNA = 2; //Se posiciona na coluna 2
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificadas
						EscreveChar('X'); //Escreve X na posição especificada
						COLUNA = 15; //Se posiciona na coluna 15
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada anteriormente
						EscreveChar(' '); //Escreve espaço na posição especificada
						estadoAnulaAreas = 3; //Coloca a variável estadoAnulaAreas para 3 para ir para o case 3
						teclapressionada = 0; //Limpa teclapressionada
					}
					break;
				}
				case teclaConfirma: //Se tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					estadoAnulaAreas = 2; //Coloca a variável estadoAnulaAreas para 2 para ir para o case 2
					tela = TELA_MOSTRA_ANULA_AREA; //Tela é igual a TELA_MOSTRA_ANULA_AREA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					for(x = 0;x < 8;x++) //Coloca as 8 posições do vetor anula_area nas 8 posições do vetor específico para gravação na memória FLASH
					{
						Write_Buffer_FLASH[x] = anula_area[x];
					}
					ESCREVE_FLASH_INTERNA(endFLASHAnulaAreas,8,0); //Escreve na memória FLASH as 8 posições do vetor Write_Buffer_FLASH no endereço especificado
					fnGravaAuditoria((80 + menu1),aux_anula_area[menu1 - 1],anula_area[menu1 - 1],OPERADOR,DISPOSITIVO);
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Se tecla CANCELA pressionada então
				{
					anula_area[menu1 - 1] = aux_anula_area[menu1 - 1]; //Salva os valores armazenados antes da alteração nas 8 posições do vetor anula_area
					estadoAnulaAreas = 2; //Coloca a variável estadoAnulaAreas para 2 para ir para o case 2
					tela = TELA_MOSTRA_ANULA_AREA; //Tela é igual a TELA_MOSTRA_INFRAVERMELHO
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				break;
			}
			break;
		}
		break;
	}
}

void fnFiltroRuido(void) //PERMITE INSERIR UM TEMPO DE AMOSTRAGEM DE 10ms A 300ms PARA QUE A DETECÇÃO SEJA MAIOR QUE O NIVEL DE SENSIBILIDADE ESCOLHIDO DURANTE ESTE TEMPO
{
	static byte estadoFiltroRuido = 1,aux_filtroruido = 0; //Definindo variável estadoFiltroRuido para o switch case abaixo e variável aux_filtroruido

	switch(estadoFiltroRuido) //Conforme valor da variável estadoInfravermelho vai para o case específico
	{
		case 1: //ENTRA NO MENU FILTRO DE RUIDO
		{
			tela = TELA_DIGITE_FILTRO_DE_RUIDO; //Tela é igual a TELA_DIGITE_FILTRO_DE_RUIDO
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estadoFiltroRuido = 2; //Coloca a variável estadoAnulaAreas para 2 para ir para o case 2
			aux_filtroruido = filtroruido; //Armazena na variável aux_filtroruido o conteúdo da variável filtroruido
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //ALTERA O FILTRO DE RUIDO
		{
			switch (teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					filtroruido++; //Incrementa filtroruido
					if(filtroruido > 15) //Se filtroruido for maior que 30 então
					{
						filtroruido = 0; //Armazena em filtroruido 0 significando que não há janela de tempo para analise do sinal de detecção
					}
					tela = TELA_DIGITE_FILTRO_DE_RUIDO; //Tela é igual a TELA_DIGITE_FILTRO_DE_RUIDO
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					filtroruido--; //Decrementa filtroruido
					if(filtroruido == 255) //Se filtroruido for igual a 255 então
					{
						filtroruido = 15; //Armazena em filtroruido 30 que significa que tem uma janela de 30 * 10ms = 300ms para verificar se o sinal de detecção em todo este intervalo foi maior que o valor de sensibilidade estabelecido
					}
					tela = TELA_DIGITE_FILTRO_DE_RUIDO; //Tela é igual a TELA_DIGITE_FILTRO_DE_RUIDO
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					Write_Buffer_FLASH[0] = filtroruido; //Coloca o filtroruido no vetor para gravação na memória FLASH
					ESCREVE_FLASH_INTERNA(endFLASHFiltroRuido,1,0); //Escreve na memória FLASH o filtroruido no endereço especificado
					fnGravaAuditoria(12,aux_filtroruido,filtroruido,OPERADOR,DISPOSITIVO);
					tela = TELA_FILTRO_DE_RUIDO; //Tela é igual a TELA_FILTRO_DE_RUIDO
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_AJUSTES_AVANCADOS; //Estado a ser executado é ESTADO_AJUSTES_AVANCADOS
					estadoFiltroRuido = 1; //Coloca a variável estadoFiltroRuido para 1 para ir para o nivel 1 deste menu
					teclapressionada = 0; //Limpa teclapressionada
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU FILTRO DE RUIDO no primeiro nível
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tela = TELA_FILTRO_DE_RUIDO; //Tela é igual a TELA_FILTRO_DE_RUIDO
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_AJUSTES_AVANCADOS; //Estado a ser executado é ESTADO_AJUSTES_AVANCADOS
					estadoFiltroRuido = 1; //Coloca a variável estadoFiltroRuido para 1 para ir para o nivel 1 deste menu
					teclapressionada = 0; //Limpa teclapressionada
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU FILTRO DE RUIDO no primeiro nível
					break;
				}
				break;
			}
			break;
		}
		break;
	}
}

void fnTravaInteligente(void) //Permite ligar a trava inteligente para que ocorra detecção ao passar pelo sensor infravermelho, para habilitar segura DECREMENTA e CANCELA ao mesmo tempo por 8s até aparecer a mensagem TRAVA INTELIGENTE ATIVADA e para desativar faça o mesmo
{
	static byte estadoTravaInteligente = 1,trava_inteligente_aux; //Definindo variável estadoTravaInteligente para o switch case abaixo e variável trava_inteligente_aux

	switch(estadoTravaInteligente) //Conforme valor da variável estadoTravaInteligente vai para o case específico
	{
		case 1: //ENTRA NO MENU TRAVA INTELIGENTE
		{
			tela = TELA_SETA_TRAVA_INTELIGENTE; //Tela é igual a TELA_SETA_TRAVA_INTELIGENTE
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			trava_inteligente_aux = trava_inteligente; //Armazena na variável trava_inteligente_aux o conteúdo da variável trava_inteligente
			estadoTravaInteligente = 2; //Coloca a variável estadoTravaInteligente para 2 para ir para o nivel 2 deste menu
			break;
		}
		case 2: //ALTERA O ESTADO DA TRAVA INTELIGENTE PARA SIM OU NÃO
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla DECREMENTA ou tecla TRAVA ou tecla DESTRAVA pressionada vai então
				case teclaDecrementa:
				case teclaTrava:
				case teclaDestrava:
				{
					if(trava_inteligente == NAO) //Se trava_inteligente for igual a NAO então
					{
						trava_inteligente = SIM; //Se trava_inteligente for igual a SIM então
						LINHA = 2; //Se posiciona na linha 2
						COLUNA = 2; //Se posiciona na coluna 2
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna desejadas
						EscreveChar(' '); //Escreve espaço na posição especificada
						COLUNA = 15; //Se posiciona na coluna 15
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada anteriormente
						EscreveChar('X'); //Escreve X na posição especificada
						estadoTravaInteligente = 2; //Coloca a variável estadoTravaInteligente para 2 para ir para o case 2
						teclapressionada = 0; //Limpa teclapressionada
					}
					else if(trava_inteligente == SIM) //Se trava_inteligente for igual a SIM então
					{
						trava_inteligente = NAO; //Se trava_inteligente for igual a NAO então
						LINHA = 2; //Se posiciona na linha 2
						COLUNA = 2; //Se posiciona na coluna 2
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificadas
						EscreveChar('X'); //Escreve X na posição especificada
						COLUNA = 15; //Se posiciona na coluna 15
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada anteriormente
						EscreveChar(' '); //Escreve espaço na posição especificada
						estadoTravaInteligente = 2; //Coloca a variável estadoTravaInteligente para 2 para ir para o case 2
						teclapressionada = 0; //Limpa teclapressionada
					}
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					tela = TELA_TRAVA_INTELIGENTE; //Tela é igual a TELA_TRAVA_INTELIGENTE
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_AJUSTES_AVANCADOS; //Estado a ser executado é ESTADO_AJUSTES_AVANCADOS
					estadoTravaInteligente = 1; //Coloca a variável estadoTravaInteligente para 1 para ir para o nivel 1 deste menu
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU FILTRO DE RUIDO no primeiro nível
					teclapressionada = 0; //Limpa teclapressionada
					fnGravaAuditoria(13,trava_inteligente_aux,trava_inteligente,OPERADOR,DISPOSITIVO);
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					trava_inteligente = trava_inteligente_aux; //Armazena na variável trava_inteligente o último valor antes de entrar para alterar
					tela = TELA_TRAVA_INTELIGENTE; //Tela é igual a TELA_TRAVA_INTELIGENTE
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_AJUSTES_AVANCADOS; //Estado a ser executado é ESTADO_AJUSTES_AVANCADOS
					estadoTravaInteligente = 1; //Coloca a variável estadoTravaInteligente para 1 para ir para o nivel 1 deste menu
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU TRAVA INTELIGENTE no primeiro nível
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				break;
			}
			break;
		}
		break;
	}
}



void fnSetaPortaAutomatica(void) //Permite ligar a trava inteligente para que ocorra detecção ao passar pelo sensor infravermelho, para habilitar segura DECREMENTA e CANCELA ao mesmo tempo por 8s até aparecer a mensagem TRAVA INTELIGENTE ATIVADA e para desativar faça o mesmo
{
	static byte estadoSetaPortaAutomatica = 1,porta_automatica_aux; //Definindo variável estadoTravaInteligente para o switch case abaixo e variável trava_inteligente_aux

	switch(estadoSetaPortaAutomatica) //Conforme valor da variável estadoTravaInteligente vai para o case específico
	{
		case 1: //ENTRA NO MENU TRAVA INTELIGENTE
		{
			tela = TELA_SETA_PORTA_AUTOMATICA; //Tela é igual a TELA_SETA_TRAVA_INTELIGENTE
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			porta_automatica_aux = porta_automatica; //Armazena na variável trava_inteligente_aux o conteúdo da variável trava_inteligente
			estadoSetaPortaAutomatica = 2; //Coloca a variável estadoTravaInteligente para 2 para ir para o nivel 2 deste menu
			break;
		}
		case 2: //ALTERA O ESTADO DA TRAVA INTELIGENTE PARA SIM OU NÃO
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla DECREMENTA ou tecla TRAVA ou tecla DESTRAVA pressionada vai então
				case teclaDecrementa:
				case teclaTrava:
				case teclaDestrava:
				{
					if(porta_automatica == NAO) //Se trava_inteligente for igual a NAO então
					{
						porta_automatica = SIM; //Se trava_inteligente for igual a SIM então
						LINHA = 2; //Se posiciona na linha 2
						COLUNA = 2; //Se posiciona na coluna 2
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna desejadas
						EscreveChar(' '); //Escreve espaço na posição especificada
						COLUNA = 15; //Se posiciona na coluna 15
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada anteriormente
						EscreveChar('X'); //Escreve X na posição especificada
						estadoSetaPortaAutomatica = 2; //Coloca a variável estadoTravaInteligente para 2 para ir para o case 2
						teclapressionada = 0; //Limpa teclapressionada
					}
					else if(porta_automatica == SIM) //Se trava_inteligente for igual a SIM então
					{
						porta_automatica = NAO; //Se trava_inteligente for igual a NAO então
						LINHA = 2; //Se posiciona na linha 2
						COLUNA = 2; //Se posiciona na coluna 2
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificadas
						EscreveChar('X'); //Escreve X na posição especificada
						COLUNA = 15; //Se posiciona na coluna 15
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada anteriormente
						EscreveChar(' '); //Escreve espaço na posição especificada
						estadoSetaPortaAutomatica = 2; //Coloca a variável estadoTravaInteligente para 2 para ir para o case 2
						teclapressionada = 0; //Limpa teclapressionada
					}
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					tela = TELA_PORTA_AUTOMATICA; //Tela é igual a TELA_TRAVA_INTELIGENTE
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_AJUSTES_AVANCADOS; //Estado a ser executado é ESTADO_AJUSTES_AVANCADOS
					estadoSetaPortaAutomatica = 1; //Coloca a variável estadoTravaInteligente para 1 para ir para o nivel 1 deste menu
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU FILTRO DE RUIDO no primeiro nível
					teclapressionada = 0; //Limpa teclapressionada
					fnGravaAuditoria(197,porta_automatica_aux,porta_automatica,OPERADOR,DISPOSITIVO);

					Write_Buffer_FLASH[0] = porta_automatica;
					ESCREVE_FLASH_INTERNA(endFLASHPortaAutomatica,1,0);
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					porta_automatica = porta_automatica_aux; //Armazena na variável trava_inteligente o último valor antes de entrar para alterar
					tela = TELA_PORTA_AUTOMATICA; //Tela é igual a TELA_TRAVA_INTELIGENTE
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_AJUSTES_AVANCADOS; //Estado a ser executado é ESTADO_AJUSTES_AVANCADOS
					estadoSetaPortaAutomatica = 1; //Coloca a variável estadoTravaInteligente para 1 para ir para o nivel 1 deste menu
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU TRAVA INTELIGENTE no primeiro nível
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				break;
			}
			break;
		}
		break;
	}
}




void fnZerarLogEventos(void) //Permite zerar a memória reservada para o log de eventos
{
	static byte estadoZerarLogEventos = 1; //Definindo variável estadoZerarLogEventos para o switch case abaixo
	static dword endereco; //Define a variável endereco para as operações com endereço abaixo

	switch(estadoZerarLogEventos) //Conforme valor da variável estadoZerarLogEventos vai para o case específico
	{
		case 1: //ENTRA NO MENU LOG EVENTOS
		{
			confirma = NAO; //Armazena na variável confirma a informação NAO
			tela = TELA_VOCE_TEM_CERTEZA; //Tela é igual a TELA_VOCE_TEM_CERTEZA
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estadoZerarLogEventos = 2; //Coloca a variável estadoZerarLogEventos para 2 para ir para o case 2
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //DEFINE ENTRE ZERAR SIM OU NÃO
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla DECREMENTA ou tecla TRAVA ou tecla DESTRAVA pressionada então
				case teclaDecrementa:
				case teclaTrava:
				case teclaDestrava:
				{
					if(confirma == NAO) //Se variável confirma for igual a NÃO então
					{
						confirma = SIM; //Armazena na variável confirma a informação SIM
						LINHA = 2; //Se posiciona na linha 2
						COLUNA = 2; //Se posiciona na coluna 2
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna desejadas
						EscreveChar(' '); //Escreve espaço na posição especificada
						COLUNA = 15; //Se posiciona na coluna 15
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada anteriormente
						EscreveChar('X'); //Escreve X na posição especificada
						teclapressionada = 0; //Limpa teclapressionada
					}
					else if(confirma == SIM) //Senão se variável confirma for igual a SIM então
					{
						confirma = NAO; //Armazena na variável confirma a informação NÃO
						LINHA = 2; //Se posiciona na linha 2
						COLUNA = 2; //Se posiciona na coluna 2
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificadas
						EscreveChar('X'); //Escreve X na posição especificada
						COLUNA = 15; //Se posiciona na coluna 15
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada anteriormente
						EscreveChar(' '); //Escreve espaço na posição especificada
						teclapressionada = 0; //Limpa teclapressionada
					}
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					if(confirma == SIM) //Se confirma for igual a SIM então
					{
						//PONTEIROS DE LOG DE AUDITORIAS
						posicao_bloco_a = 0;
						Write_Buffer_FLASH[0] = posicao_bloco_a;
						posicao_byte_a = 0;
						Write_Buffer_FLASH[1] = (byte)(posicao_byte_a >> 8);
						Write_Buffer_FLASH[2] = (byte)(posicao_byte_a);

						//PONTEIROS DE LOG DE EVENTOS
						posicao_bloco_l = 1;
						Write_Buffer_FLASH[3] = posicao_bloco_l;
						posicao_byte_l = 0;
						Write_Buffer_FLASH[4] = (byte)(posicao_byte_l >> 8);
						Write_Buffer_FLASH[5] = (byte)(posicao_byte_l);

						ESCREVE_FLASH_INTERNA(endFLASHPonteiroBlocoA,6,0);

						for(aux_numero_bloco = 0;aux_numero_bloco < 34;aux_numero_bloco++)
						{
							endereco = END_INI_LOG_EVENTOS + (aux_numero_bloco * 0x1000);
							FLASH_INTERNA_EraseSector(endereco); //Apaga a memória FLASH do endereço 0x84000 até FFFFF
						}
						fnGravaAuditoria(13,0,1,OPERADOR,DISPOSITIVO);
					}

					estadoZerarLogEventos = 1; //Coloca a variável estadoZerarLogEventos para 1 para ir para o primeiro nivel deste menu
					tela = TELA_ZERAR_LOG_EVENTOS; //tela é igual a TELA_ZERAR_LOG_EVENTOS
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_AJUSTES_AVANCADOS; //Estado a ser executado é ESTADO_AJUSTES_AVANCADOS
					teclapressionada = 0; //Limpa teclapressionada
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU ZERAR LOG EVENTOS no primeiro nível
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					estadoZerarLogEventos = 1; //Coloca a variável estadoZerarLogEventos para 1 para ir para o primeiro nivel deste menu
					tela = TELA_ZERAR_LOG_EVENTOS; //tela é igual a TELA_ZERAR_LOG_EVENTOS
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_AJUSTES_AVANCADOS; //Estado a ser executado é ESTADO_AJUSTES_AVANCADOS
					teclapressionada = 0; //Limpa teclapressionada
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU ZERAR LOG EVENTOS no primeiro nível
					break;
				}
				break;
			}
			break;
		}
		break;
	}
}
void fnConfiguraInternet(void) //Permite configurar o endereço IP, a máscara de sub-rede, o endereço gateway, o dns e a porta web
{
	static byte estadoConfiguraInternet = 1; //Definindo variável estadoConfiguraInternet para o switch case abaixo
	static byte modo_operacao_ethernet_aux;


	switch(estadoConfiguraInternet) //Conforme valor da variável estadoConfiguraInternet vai para o case específico
	{
		case 1: //ENTRA NO MENU CONFIGURAÇÕES DA INTERNET
		{
			menu1 = 1; //Faz menu1 igual a 1 para sempre entrar no primeiro menu da primeira vez
			tela = TELA_MOSTRA_CONFIGURACOES_MODO_REDE; //Tela é igual a TELA_MOSTRA_CONFIGURACOES_DA_INTERNET
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estadoConfiguraInternet = 2; //Coloca a variável estadoConfiguraInternet para 2 para ir para o case 2
			teclapressionada = 0; //Limpa teclapressionada
			LIBERA_ENVIA_PACOTES = NAO;

			//Tirei leitura dos endereços do ponto a ponto daqui para poder implementar a escolha ponto a ponto ou acesso remoto
			break;
		}
		case 2: //ESCOLHE UM DOS MODOS DE REDE PARA OPERAR: PONTO A PONTO ou ACESSO REMOTO
		{
			switch (teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					menu1++; //Incrementa menu1
					if(menu1 > 2) //Se menu1 for maior que 5 então
					{
						menu1 = 1; //Armazena na variável menu1 o valor 1
					}
					tela = TELA_MOSTRA_CONFIGURACOES_MODO_REDE; //Tela é igual a TELA_MOSTRA_CONFIGURACOES_DA_INTERNET
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					menu1--; //Decrementa menu1
					if(menu1 < 1) //Se menu1 for menor que 1 então
					{
						menu1 = 2; //Armazena na variável menu1 o valor 5
					}
					tela = TELA_MOSTRA_CONFIGURACOES_MODO_REDE; //Tela é igual a TELA_MOSTRA_CONFIGURACOES_DA_INTERNET
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					if(menu1 == 1)
					{
						modo_operacao_ethernet = MODO_SERIAL;
						modo_operacao_ethernet_aux = modo_operacao_ethernet;
						Write_Buffer_FLASH[0] = modo_operacao_ethernet;
						ESCREVE_FLASH_INTERNA(endFLASHModoEthernet,1,0);
						PADRAO = _STATIC;
						fnLeEnderecosPontoaPonto();
						menu2 = 1;
						tela = TELA_MOSTRA_CONFIGURACOES_DA_INTERNET; //Tela é igual a TELA_MOSTRA_CONFIGURACOES_DA_INTERNET
						estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
						estadoConfiguraInternet = 3; //Coloca a variável estadoConfiguraInternet para 3 para ir para o case 3
						teclapressionada = 0; //Limpa a teclapressionada
					}
					else if (menu1 == 2)
					{
						modo_operacao_ethernet = MODO_NORMAL;
						modo_operacao_ethernet_aux = modo_operacao_ethernet;
						Write_Buffer_FLASH[0] = modo_operacao_ethernet;
						ESCREVE_FLASH_INTERNA(endFLASHModoEthernet,1,0);
						estado = ESTADO_ESCOLHE_STATIC_DHCP;
						estadoConfiguraInternet = 3; //Coloca a variável estadoConfiguraInternet para 1 para ir para o primeiro nivel deste menu
						teclapressionada = 0; //Limpa a teclapressionada
					}
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
//					if(modo_operacao_ethernet == MODO_AT)
//					{
//						fnEstadoComandoNormal();
//					}
					if(modo_operacao_ethernet != MODO_AT){
						modo_operacao_ethernet = MODO_AT;
					}
					fnEstadoComandoAT();
					fnResetaModulo();
					modo_operacao_ethernet = modo_operacao_ethernet_aux; //Define modo_operacao_ethernet como MODO_NORMAL para transmitir os parâmetros do detector para a rede externa
					delay_ms(1000); //Espera 1 segundo
					estado_ENVIA_SERIAL_ETHERNET = ESTADO_ENVIAR; //Faz estado_EMVIA_SERIAL_ETHERNET para ESTADO_ENVIAR para poder transmitir
					tela = TELA_CONFIGURACOES_DE_INTERNET; //Tela é igual a TELA_CONFIGURACOES_DE_INTERNET
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_AJUSTES_AVANCADOS; //Estado a ser executado é ESTADO_AJUSTES_AVANCADOS
					estadoConfiguraInternet = 1; //Coloca a variável estadoConfiguraInternet para 1 para ir para o primeiro nivel deste menu
					teclapressionada = 0; //Limpa a teclapressionada
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU CONFIGURACOES DA INTERNET no primeiro nível
					LIBERA_ENVIA_PACOTES = SIM;
					break;
				}
				break;
			}
			break;
		}
		case 3: //ESCOLHE UMA DAS CONFIGURAÇÕES DA INTERNET PARA ALTERAR
		{
			if(escolhe == 2)
			{
				estadoConfiguraInternet = 2;
				escolhe = 0;
				break;
			}
			switch (teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					menu2++; //Incrementa menu1
					if(menu2 > 4) //Se menu1 for maior que 5 então
					{
						menu2 = 1; //Armazena na variável menu1 o valor 1
					}
					tela = TELA_MOSTRA_CONFIGURACOES_DA_INTERNET; //Tela é igual a TELA_MOSTRA_CONFIGURACOES_DA_INTERNET
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					menu2--; //Decrementa menu1
					if(menu2 < 1) //Se menu1 for menor que 1 então
					{
						menu2 = 4; //Armazena na variável menu1 o valor 5
					}
					tela = TELA_MOSTRA_CONFIGURACOES_DA_INTERNET; //Tela é igual a TELA_MOSTRA_CONFIGURACOES_DA_INTERNET
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					if(menu2 == 1) //Se menu1 for igual a 1 então
					{
						tela = TELA_ENDERECO_IP; //Tela é igual a TELA_ENDERECO_IP
						estado = ESTADO_DIGITE_IP; //Estado a ser executado é ESTADO_DIGITE_IP
					}
					else if(menu2 == 2) //Senão se menu1 for igual a 2 então
					{
						tela = TELA_MASCARA_SUB_REDE; //Tela é igual a TELA_MASCARA_SUB_REDE
						estado = ESTADO_DIGITE_MASCARA_SUB_REDE; //Estado a ser executado é ESTADO_DIGITE_MASCARA_SUB_REDE
					}
					else if(menu2 == 3) //Senão se menu1 for igual a 3 então
					{
						tela = TELA_ENDERECO_GATEWAY; //Tela é igual a TELA_ENDERECO_GATEWAY
						estado = ESTADO_DIGITE_GATEWAY; //Estado a ser executado é ESTADO_DIGITE_GATEWAY
					}
					else if(menu2 == 4) //Senão se menu1 for igual a 5 então
					{
						tela = TELA_ENDERECO_DNS; //Tela é igual a TELA_ENDERECO_DNS
						estado = ESTADO_DIGITE_DNS; //Estado a ser executado é ESTADO_DIGITE_DNS
					}
//					else if(menu2 == 5) //Senão se menu1 for igual a 4 então
//					{
//						tela = TELA_PORTA_WEB; //Tela é igual a TELA_PORTA_WEB
//						estado = ESTADO_DIGITE_PORTA_WEB; //Estado a ser executado é ESTADO_DIGITE_PORTA_WEB
//					}
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estadoConfiguraInternet = 3; //Coloca a variável estadoConfiguraInternet para 3 para ir para o case 3
					teclapressionada = 0; //Limpa a teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tela = TELA_MOSTRA_CONFIGURACOES_MODO_REDE; //Tela é igual a TELA_CONFIGURACOES_DE_INTERNET
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_CONFIGURACOES_DE_INTERNET; //Estado a ser executado é ESTADO_AJUSTES_AVANCADOS
					estadoConfiguraInternet = 2; //Coloca a variável estadoConfiguraInternet para 1 para ir para o primeiro nivel deste menu
					teclapressionada = 0; //Limpa a teclapressionada
					break;
				}
				break;
			}
			break;
		}
		break;
	}
}

void fnEliminarFalhadasBobinas(void) //Permite ligar a trava inteligente para que ocorra detecção ao passar pelo sensor infravermelho, para habilitar segura DECREMENTA e CANCELA ao mesmo tempo por 8s até aparecer a mensagem TRAVA INTELIGENTE ATIVADA e para desativar faça o mesmo
{
	static byte estadoEliminarFalha = 1,eliminar_falha_aux; //Definindo variável estadoTravaInteligente para o switch case abaixo e variável trava_inteligente_aux

	switch(estadoEliminarFalha) //Conforme valor da variável estadoTravaInteligente vai para o case específico
	{
		case 1: //ENTRA NO MENU TRAVA INTELIGENTE
		{
			tela = TELA_SETA_ELIMINAR_FALHA_DAS_BOBINAS; //Tela é igual a TELA_SETA_ELIMINAR_FALHA_DAS_BOBINAS
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			eliminar_falha_aux = eliminar_falha; //Armazena na variável trava_inteligente_aux o conteúdo da variável trava_inteligente
			estadoEliminarFalha = 2; //Coloca a variável estadoTravaInteligente para 2 para ir para o nivel 2 deste menu
			break;
		}
		case 2: //ALTERA O ESTADO DA TRAVA INTELIGENTE PARA SIM OU NÃO
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla DECREMENTA ou tecla TRAVA ou tecla DESTRAVA pressionada vai então
				case teclaDecrementa:
				case teclaTrava:
				case teclaDestrava:
				{
					if(eliminar_falha == NAO) //Se trava_inteligente for igual a NAO então
					{
						eliminar_falha = SIM; //Se trava_inteligente for igual a SIM então
						LINHA = 2; //Se posiciona na linha 2
						COLUNA = 2; //Se posiciona na coluna 2
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna desejadas
						EscreveChar(' '); //Escreve espaço na posição especificada
						COLUNA = 15; //Se posiciona na coluna 15
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada anteriormente
						EscreveChar('X'); //Escreve X na posição especificada
						estadoEliminarFalha = 2; //Coloca a variável estadoTravaInteligente para 2 para ir para o case 2
						teclapressionada = 0; //Limpa teclapressionada
					}
					else if(eliminar_falha == SIM) //Se trava_inteligente for igual a SIM então
					{
						eliminar_falha = NAO; //Se trava_inteligente for igual a NAO então
						LINHA = 2; //Se posiciona na linha 2
						COLUNA = 2; //Se posiciona na coluna 2
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificadas
						EscreveChar('X'); //Escreve X na posição especificada
						COLUNA = 15; //Se posiciona na coluna 15
						PosicionaLCD(pos); //Posiciona o cursor na linha e coluna especificada anteriormente
						EscreveChar(' '); //Escreve espaço na posição especificada
						estadoEliminarFalha = 2; //Coloca a variável estadoTravaInteligente para 2 para ir para o case 2
						teclapressionada = 0; //Limpa teclapressionada
					}
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{

					tela = TELA_ELIMINAR_FALHA_DAS_BOBINAS; //Tela é igual a TELA_ELIMINAR_FALHA_DAS_BOBINAS
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_AJUSTES_AVANCADOS; //Estado a ser executado é ESTADO_AJUSTES_AVANCADOS
					estadoEliminarFalha = 1; //Coloca a variável estadoTravaInteligente para 1 para ir para o nivel 1 deste menu
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU FILTRO DE RUIDO no primeiro nível
					teclapressionada = 0; //Limpa teclapressionada
					FALHA_DAS_BOBINAS = FALSE;
					flagMonitoraAreas = 0;
					Write_Buffer_FLASH[0] = eliminar_falha;
					ESCREVE_FLASH_INTERNA(endFLASHFalhadaBobina,1,0); //Escreve na memória FLASH 1 posição do vetor Write_Buffer_FLASH no endereço especificado
					fnGravaAuditoria(13,eliminar_falha_aux,eliminar_falha,OPERADOR,DISPOSITIVO);
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					eliminar_falha = eliminar_falha_aux; //Armazena na variável trava_inteligente o último valor antes de entrar para alterar
					tela = TELA_ELIMINAR_FALHA_DAS_BOBINAS; //Tela é igual a TELA_TRAVA_INTELIGENTE
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_AJUSTES_AVANCADOS; //Estado a ser executado é ESTADO_AJUSTES_AVANCADOS
					estadoEliminarFalha = 1; //Coloca a variável estadoTravaInteligente para 1 para ir para o nivel 1 deste menu
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU TRAVA INTELIGENTE no primeiro nível
					teclapressionada = 0; //Limpa teclapressionada


					break;
				}
				break;
			}
			break;
		}
		break;
	}
}


void fnOpcaoSensorContador(void) //Permite escolher se sensor de teto ou sensor frontal para a contagem de pessoas
{
	static byte estadofnOpcaoSensorContador = 1; //Definindo variável estadofnTrava para o switch case abaixo
	static byte aux_opcaosensorcontador; //Definindo variáveis aux_opcaosensorcontador para recuperar o último valor caso seja alterado e seja pressionado a tecla CANCELA

	switch(estadofnOpcaoSensorContador) //Conforme variável vai para o case específico
	{
		case 1: //ENTRA NO MENU DE ALTERAÇÃO DO SINAL DA TRAVA
		{
			estadofnOpcaoSensorContador = 2; //Coloca a variável estadofnOpcaoSensorContador para 2 para ir para o próximo case
			tela = TELA_MOSTRA_OPCAO_SENSOR_CONTADOR; //Tela é igual a TELA_MOSTRA_OPCAO_SENSOR_CONTADOR
			estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
			aux_opcaosensorcontador = opcaosensorcontador; //Salva o último valor de opcaosensorcontador antes de alterar
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2:	//ALTERA A OPÇÃO DO SENSOR DE CONTAGEM DA PGDM
		{
			switch(teclapressionada) //Conforme teclapressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					opcaosensorcontador++; //Incrementa sinal_trava
					if(opcaosensorcontador > SENSOR_TETO) //Se sinal_trava for maior que trava_retencao_controle_teclado então
					{
						opcaosensorcontador = SENSOR_FRONTAL; //Armazena na variável sinal_trava o valor trava_pulso
					}
					tela = TELA_MOSTRA_OPCAO_SENSOR_CONTADOR; //Tela é igual a TELA_MOSTRA_TRAVA
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					opcaosensorcontador--; //Decrementa sinal_trava
					if(opcaosensorcontador < SENSOR_FRONTAL) //Se sinal_trava for menor que trava_pulso então
					{
						opcaosensorcontador = SENSOR_TETO; //Armazena na variável sinal_trava o valor trava_retencao_controle_teclado
					}
					tela = TELA_MOSTRA_OPCAO_SENSOR_CONTADOR; //Tela é igual a TELA_MOSTRA_TRAVA
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					Write_Buffer_FLASH[0] = opcaosensorcontador; //Coloca o sinal da trava no vetor para gravação na memória FLASH
					ESCREVE_FLASH_INTERNA(endFLASHOpcaoSensorContador,1,0); //Escreve na memória FLASH a opção do sensor de contagem no endereço especificado
					//fnGravaAuditoria(4,aux_sinal_trava,sinal_trava,OPERADOR,DISPOSITIVO);
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU TRAVA no primeiro nível
					estado = ESTADO_AJUSTES_AVANCADOS; //Estado a ser executado é ESTADO_AJUSTES_AVANCADOS
					estadofnOpcaoSensorContador = 1; //Coloca a variável estadofnTrava para 1 para voltar a camada 1 desta função
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					teclapressionada = 0; //Limpa a teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tela = TELA_OPCAO_DE_CONTADOR; //Tela é igual a TELA_OPCAO_DE_CONTADOR
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					estadofnOpcaoSensorContador = 1; //Coloca a variável estadofnTrava para 1 para voltar a camada 1 desta função
					estado = ESTADO_AJUSTES_AVANCADOS; //Estado a ser executado é ESTADO_AJUSTES_AVANCADOS
					teclapressionada = 0; //Limpa teclapressionada
					flagretorno = 1; //Torna a flag flag_retorno para 1 para poder retornar ao MENU TRAVA no primeiro nível
					break;
				}
				break;
			}
			break;
		}
		break;
	}
}


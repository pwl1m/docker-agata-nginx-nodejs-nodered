/*
 * funcoes_navega_menu.c
 *
 *  Created on: 22/06/2023
 *      Author: marcos.butignol
 */


#include "funcao.h"

#include "agata_std_functions.h"
#include "agata_hc_definitions.h"
#include "stdlib.h"

/*** Funções do NAVEGA MENU ***/
void Navega_Menu(void) //Função para entrar com a senha da gerência, técnico ou engenharia
{
	//Se tela for TELA_INICIAL ou tela for TELA_SEM_SINAL_NAS_ANTENAS ou tela for TELA_CARGA_DA_BATERIA ou tela for TELA_CARREGANDO pode entrar nos menus de senha
	if (tela == TELA_INICIAL || tela == TELA_SEM_SINAL_NAS_ANTENAS || tela == TELA_CARGA_DA_BATERIA || tela == TELA_CARREGANDO)
	{
		switch (teclapressionada) //Conforme tecla pressionada executa o case específico
		{
			case teclaIncrementa: //Caso tecla INCREMENTA pressionada ou tecla TRAVA pressionada
			case teclaTrava:
			{
				if(!FALHA_DAS_BOBINAS)
				{
					controle_ou_painel_travou = SIM;
					if(teclapressionada == teclaIncrementa && travado == FALSE) //Se teclapressionada for igual a tecla INCREMENTA e travado for FALSE
					{
						fnGravaEvento(GRAVA_BLOQUE,GRAVA_PAINEL); //Grava o envento BLOQUEIO pelo dispositivo PAINEL com hora e data atuais na memória FLASH
					}
					else if(teclapressionada == teclaTrava && travado == FALSE) //Se teclapressionada for igual a tecla TRAVA e travado for FALSE
					{
						while(controlePressionado == 0);
						fnGravaEvento(GRAVA_BLOQUE,controlePressionado); //Grava o envento BLOQUEIO pelo dispositivo CONTROLE com hora e data atuais na memória FLASH
						controlePressionado = 0;
					}
					if(sinal_rele == rele_pulso) //Se sinal_rele for rele_pulso então
					{
						fnLigaPulsoRele(); //Pulsa o relé pelo tempo especificado no parâmetro
					}
					else if(sinal_trava == trava_pulso) //Se sinal_trava for trava_pulso então
					{
						fnLigaPulsoTrava(); //Pulsa a trava pelo tempo especificado no parâmetro
					}
					else if(sinal_rele == rele_retencao || sinal_trava == trava_retencao_controle_teclado)	//Se sinal_rele for rele_retencao ou sinal_trava for trava_retencao_controle_teclado e modo_travamento for TRAVA_DESTRAVA então
					{
						if(statusPGDM != 1){
							LIGA_RELE; //Liga relé
							LIGA_TRAVA; //Liga trava
						}
						LIGA_SINALEIRA_VERMELHA; //Liga sinaleira vermelha
					}
					if(modo_travamento == TRAVA_DESTRAVA) //Se modo_travamento for TRAVA_DESTRAVA então
					{
						estado = ESTADO_TRAVA; //estado é igual a ESTADO_TRAVA
					}
					estado = ESTADO_TRAVA;
					//travado = TRUE; //Torna flag travado para TRUE para indicar que sistema esta travado
				}
				if(FALHA_DAS_BOBINAS)
				{
					tela = TELA_INICIAL; //tela é igual a TELA_INICIAL
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					estado = ESTADO_RELIGA_INTERRUPCOES; //Estado a ser executado é ESTADO_RELIGA_INTERRUPCOES
					travado = FALSE; //Torna flag travado para FALSE para indicar que sistema esta destravado
				}
				teclapressionada = 0; //Limpa variável teclapressionada para uma nova avaliação
				break;
			}
			case teclaDecrementa: //Caso tecla DECREMENTA pressionada ou tecla DESTRAVA pressionada
			case teclaDestrava:
			{
				if(!FALHA_DAS_BOBINAS && !CANCELA)
				{
					if(teclapressionada == teclaDecrementa && travado == TRUE) //Se teclapressionada for igual a tecla DECREMENTA e travado for FALSE
					{
						fnGravaEvento(GRAVA_DSBLOQ,GRAVA_PAINEL); //Grava o envento DESBLOQUEIO pelo dispositivo PAINEL com hora e data atuais na memória FLASH
					}
					else if(teclapressionada == teclaDestrava && travado == TRUE) //Se teclapressionada for igual a tecla DESTRAVA e travado for FALSE
					{
						while(controlePressionado == 0);
						fnGravaEvento(GRAVA_DSBLOQ,controlePressionado); //Grava o envento DESBLOQUEIO
						controlePressionado = 0;
					}
					if(sinal_rele == rele_pulso) //Se sinal_rele for rele_pulso então
					{
						fnLigaPulsoRele(); //Pulsa o relé pelo tempo especificado no parâmetro
					}
					else if(sinal_trava == trava_pulso) //Se sinal_trava for trava_pulso então
					{
						fnLigaPulsoTrava(); //Pulsa a trava pelo tempo especificado no parâmetro
					}
					if((modo_travamento == TRAVA_DESTRAVA || modo_travamento == SOMENTE_DESTRAVA)) //Se modo_travamento é igual a TRAVA_DESTRAVA ou modo_travamento é igual a SOMENTE_DESTRAVA então
					{
						estado = ESTADO_DESTRAVA; //estado é igual a ESTADO_DESTRAVA
					}
					//travado = FALSE; //Torna flag travado para FALSE para indicar que sistema esta travado
				}
				if(FALHA_DAS_BOBINAS)
				{
					tela = TELA_INICIAL; //tela é igual a TELA_INICIAL
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					estado = ESTADO_RELIGA_INTERRUPCOES; //Estado a ser executado é ESTADO_RELIGA_INTERRUPCOES
					travado = FALSE; //Torna flag travado para FALSE para indicar que sistema esta destravado
				}
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaConfirma: //Caso tecla CONFIRMA
			case teclaConfirma_Remoto:
			{
				ACAO_CONTROLE = NENHUM;
				tela = TELA_SENHA_DA_GERENCIA; //A primeira tela que aparece é TELA_SENHA_DA_GERENCIA
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				APAGA_AREAS; //Apaga áreas
				LIGA_SINALEIRA_VERMELHA; //Liga sinaleira vermelha
				if(statusPGDM != 1){
					LIGA_TRAVA; //Liga trava
					LIGA_RELE; //Liga relé
					travado = TRUE;
				}
				break;
			}
			break;
		}
	}
	else if (tela == TELA_SENHA_DA_GERENCIA) //Se tela for igual a TELA_SENHA_DA_GERENCIA então
	{
		switch (teclapressionada) //Conforme tecla pressionada executa o case específico
		{
			case teclaConfirma: //Caso tecla CONFIRMA pressionada então
			case teclaConfirma_Remoto:
			{
				tela = TELA_DIGITE_SENHA_DA_GERENCIA; //tela é igual a TELA_DIGITE_SENHA_DA_GERENCIA
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				estado = ESTADO_DIGITE_SENHA; //Estado a ser executado é ESTADO_DIGITE_SENHA
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaIncrementa: //Caso tecla INCREMENTA pressionada ou tecla DECREMENTA ou tecla TRAVA ou tecla DESTRAVA então
			case teclaDecrementa:
			case teclaTrava:
			case teclaDestrava:
			{
				if(tela == TELA_SENHA_DA_GERENCIA) //Se tela for igual a TELA_SENHA_DA_GERENCIA
				{
					tela = TELA_SENHA_DO_TECNICO; //Chaveia para TELA_SENHA_DO_TECNICO
				}
				else if(tela == TELA_SENHA_DO_TECNICO) //Se tela for igual a TELA_SENHA_DO_TECNICO
				{
					tela = TELA_SENHA_DA_GERENCIA; //Chaveia para TELA_SENHA_DA_GERENCIA
				}
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaCancela: //Caso tecla CANCELA pressionada então
			{
				tela = TELA_INICIAL; //tela é igual a TELA_INICIAL
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				estado = ESTADO_RELIGA_INTERRUPCOES; //Estado a ser executado é ESTADO_RELIGA_INTERRUPCOES
				teclapressionada = 0; //Limpa teclapressionada
				LIGA_SINALEIRA_VERDE; //Liga sinaleira verde
				DESLIGA_RELE; //Desliga relé
				travado = FALSE; //Torna flag travado para FALSE para indicar que sistema esta destravado
				Solenoide_DisableEvent();		//Desativa evento que gera PWM solenoide
				Solenoide_Disable();			//Desativa Timer que gera o evento do PWM solenoide
				tempo_trava = 0;				//Reseta contador de tempo para ativar PWM da solenoide
				pwm_trava = 0;					//Reseta contador PWM da solenoide
				DESLIGA_TRAVA; 					//Desliga trava
				configAnaliseControle();
				break;
			}
			break;
		}
	}
	else if (tela == TELA_SENHA_DO_TECNICO)	//Se tela é igual a TELA_SENHA_DO_TECNICO
	{
		switch (teclapressionada) //Conforme tecla pressionada executa o case específico
		{
			case teclaConfirma: //Caso tecla CONFIRMA pressionada então
			case teclaConfirma_Remoto:
			{
				tela = TELA_DIGITE_SENHA_DO_TECNICO; //tela é igual a TELA_DIGITE_SENHA_DO_TECNICO
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				estado = ESTADO_DIGITE_SENHA; //Estado a ser executado é ESTADO_DIGITE_SENHA
				teclapressionada = 0; //Limpa tecla pressionada
				break;
			}
			case teclaIncrementa: //Caso tecla INCREMENTA pressionada ou tecla DECREMENTA ou tecla TRAVA ou tecla DESTRAVA então
			case teclaDecrementa:
			case teclaTrava:
			case teclaDestrava:
			{
				if(tela == TELA_SENHA_DA_GERENCIA) //Se tela for igual a TELA_SENHA_DA_GERENCIA então
				{
					tela = TELA_SENHA_DO_TECNICO; //tela é igual a TELA_SENHA_DO_TECNICO
				}
				else if(tela == TELA_SENHA_DO_TECNICO) //Se tela for igual a TELA_SENHA_DO_TECNICO
				{
					tela = TELA_SENHA_DA_GERENCIA; //tela é igual a TELA_SENHA_DA_GERENCIA
				}
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa tecla pressionada
				break;
			}
			case teclaCancela: //Caso tecla CANCELA pressionada então
			{
				tela = TELA_INICIAL; //tela é igual a TELA_INICIAL
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				estado = ESTADO_RELIGA_INTERRUPCOES; //Estado a ser executado é ESTADO_RELIGA_INTERRUPCOES
				teclapressionada = 0; //Limpa teclapressionada
				LIGA_SINALEIRA_VERDE; //Liga sinaleira verde
				DESLIGA_RELE; //Desliga relé
				travado = FALSE; //Torna flag travado para FALSE para indicar que sistema esta destravado
				Solenoide_DisableEvent();		//Desativa evento que gera PWM solenoide
				Solenoide_Disable();			//Desativa Timer que gera o evento do PWM solenoide
				tempo_trava = 0;				//Reseta contador de tempo para ativar PWM da solenoide
				pwm_trava = 0;					//Reseta contador PWM da solenoide
				DESLIGA_TRAVA; 					//Desliga trava
				configAnaliseControle();
				break;
			}
			break;
		}
	}
	else if (tela == TELA_SENHA_INCORRETA) //Se tela é TELA_SENHA_INCORRETA então
	{
		tela = TELA_SENHA_INCORRETA; //Tela é igual a TELA_SENHA_INCORRETA
		estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
		estado = ESTADO_RELIGA_INTERRUPCOES; //Estado a ser executado é ESTADO_RELIGA_INTERRUPÇÕES
		teclapressionada = 0; //Limpa teclapressionada
	}
}

void Navega_Menu_Funcoes(void) //Função para navegar entre as funções do sistema para alteração de parâmetros
{
	if (tela == TELA_AJUSTES_BASICOS) //MENU 1 - AJUSTES BASICOS - ACESSO PERMITIDO PARA TODOS
	{
		switch (teclapressionada) //Conforme tecla pressionada executa o case específico
		{
			case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
			case teclaTrava:
			{
				if(senha_de_acesso == SENHA_DA_GERENCIA) //Se senha_de_acesso for igual a SENHA_DA_GERENCIA então
				{
					tela = TELA_AJUSTES_DO_SISTEMA; //tela é igual a TELA_AJUSTES_DO_SISTEMA
				}
				else if(senha_de_acesso == SENHA_DO_TECNICO || senha_de_acesso == SENHA_DA_ENGENHARIA) //Se senha_de_acesso é igual a SENHA_DO_TECNICO ou SENHA_DA_ENGENHARIA então
				{
					tela = TELA_AJUSTES_AVANCADOS; //tela é igual a TELA_AJUSTES_AVANCADOS
				}
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
			case teclaDestrava:
			{
				if(senha_de_acesso == SENHA_DA_GERENCIA) //Se senha_de_acesso for igual a SENHA_DA_GERENCIA então
				{
					tela = TELA_INFORMACOES_DE_ENERGIA; //tela é igual a TELA_INFORMACAOES_DE_ENERGIA
				}
				else if(senha_de_acesso == SENHA_DO_TECNICO) //Se senha_de_acesso for igual a SENHA_DO_TECNICO então
				{
					tela = TELA_COMPATIBILIDADE_ELETROMAGNETICA; //tela é igual a TELA_COMPATIBILIDADE_ELETROMAGNETICA
				}
				else if(senha_de_acesso == SENHA_DA_ENGENHARIA) //Se senha_de_aceso for igual a SENHA_DA_ENGENHARIA então
				{
					tela = TELA_TIPO_DETECTOR; //tela é igual a TELA_POTENCIOMETRO_DE_SELECAO_DE_METAIS
				}
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaConfirma: //Caso tecla CONFIRMA pressionada então
			case teclaConfirma_Remoto:
			{
				estado = ESTADO_AJUSTES_BASICOS; //Estado a ser executado é ESTADO_AJUSTES_BASICOS
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaCancela: //Caso tecla CANCELA pressionada então
			{
				tela = TELA_INICIAL; //tela é igual a TELA_INICIAL
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				estado = ESTADO_RELIGA_INTERRUPCOES; //Estado a ser executado é ESTADO_RELIGA_INTERRUPÇÕES
				teclapressionada = 0; //Limpa teclapressionada
				configAnaliseControle();
				break;
			}
			break;
		}
	}
	else if (tela == TELA_AJUSTES_AVANCADOS) //MENU 2 - AJUSTES AVANÇADOS - ACESSO PERMITIDO PARA TECNICO E ENGENHARIA
	{
		switch (teclapressionada) //Conforme tecla pressionada executa o case específico
		{
			case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
			case teclaTrava:
			{
				tela = TELA_AJUSTES_DO_SISTEMA; //tela é igual a TELA_AJUSTES_DO_SISTEMA
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
			case teclaDestrava:
			{
				tela = TELA_AJUSTES_BASICOS; //tela é igual a TELA_AJUSTES_BASICOS
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaConfirma: //Caso tecla CONFIRMA pressionada então
			case teclaConfirma_Remoto:
			{
				estado = ESTADO_AJUSTES_AVANCADOS; //Estado a ser executado é ESTADO_AJUSTES_AVANÇADOS
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaCancela: //Caso tecla CANCELA então
			{
				tela = TELA_INICIAL; //tela é igual a TECLA_INICIAL
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				estado = ESTADO_RELIGA_INTERRUPCOES; //Estado a ser executado é ESTADO_RELIGINTERUPCOES
				teclapressionada = 0; //Limpa teclapressionada
				configAnaliseControle();
				break;
			}
			break;
		}
	}
	else if (tela == TELA_AJUSTES_DO_SISTEMA) //MENU 3 - AJUSTES DO SISTEMA - ACESSO PERMITIDO PARA TODOS
	{
		switch (teclapressionada) //Conforme tecla pressionada executa o case específico
		{
			case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
			case teclaTrava:
			{
				tela = TELA_AJUSTES_DE_ALARME; //tela é igual a TELA_AJUSTES_DE_ALARME
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
			case teclaDestrava:
			{
				if(senha_de_acesso == SENHA_DA_GERENCIA) //Se senha_de_acesso for igual a SENHA_DA_GERENCIA
				{
					tela = TELA_AJUSTES_BASICOS; //tela é igual a TELA_AJUSTES_BASICOS
				}
				else if(senha_de_acesso == SENHA_DO_TECNICO || senha_de_acesso == SENHA_DA_ENGENHARIA) //Se senha_de_acesso for igual a SENHA_DO_TECNICO ou SENHA_DA_ENGENHARIA então
				{
					tela = TELA_AJUSTES_AVANCADOS; //tela é igual a TELA_AJUSTES_AVANCADOS
				}
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaConfirma: //Caso tecla CONFIRMA pressionada então
			case teclaConfirma_Remoto:
			{
				estado = ESTADO_AJUSTES_DO_SISTEMA; //Estado a ser executado é ESTADO_AJUSTES_DO_SISTEMA
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaCancela: //Caso tecla CANCELA pressionada então
			{
				tela = TELA_INICIAL; //tela é igual a TELA_INICIAL
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				estado = ESTADO_RELIGA_INTERRUPCOES; //Estado a ser executado é ESTADO_RELIGA_INTERRUPCOES
				teclapressionada = 0; //Limpa teclapressionada
				configAnaliseControle();
				break;
			}
			break;
		}
	}
	else if(tela == TELA_AJUSTES_DE_ALARME) //MENU 4 - AJUSTES DE ALARME - ACESSO PERMITIDO PARA TODOS
	{
		switch (teclapressionada) //Conforme tecla pressionada executa o case específico
		{
			case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
			case teclaTrava:
			{
				tela = TELA_INFORMACOES_DO_SISTEMA; //tela é igual a TELA_INFORMACOES_DO_SISTEMA
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
			case teclaDestrava:
			{
				tela = TELA_AJUSTES_DO_SISTEMA; //tela é igual a TELA_AJUSTES_DO_SISTEMA
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaConfirma: //Caso tecla CONFIRMA pressionada então
			case teclaConfirma_Remoto:
			{
				estado = ESTADO_AJUSTES_DE_ALARME; //Estado a ser executado é ESTADO_AJUSTES_DE_ALARME
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaCancela: //Caso tecla CANCELA pressionada então
			{
				tela = TELA_INICIAL; //tela é igual a TELA_INICIAL
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				estado = ESTADO_RELIGA_INTERRUPCOES; //Estado a ser executado é ESTADO_RELIGA_INTERRUPCOES
				teclapressionada = 0; //Limpa teclapressionada
				configAnaliseControle();
				break;
			}
			break;
		}
	}
	else if (tela == TELA_INFORMACOES_DO_SISTEMA) //MENU 5 - INFORMACOES DO SISTEMA - ACESSO PERMITIDO PARA TODOS
	{
		switch (teclapressionada) //Conforme tecla pressionada executa o case específico
		{
			case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
			case teclaTrava:
			{
				tela = TELA_INFORMACOES_DE_ENERGIA; //tela é igual a TELA_INFORMACOES_DE_ENERGIA
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
			case teclaDestrava:
			{
				tela = TELA_AJUSTES_DE_ALARME; //tela é igual a TELA_AJUSTES_DE_ALARME
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaConfirma: //Caso tecla CONFIRMA pressionada então
			case teclaConfirma_Remoto:
			{
				estado = ESTADO_INFORMACOES_DO_SISTEMA; //Estado a ser executado é ESTADO_INFORMACOES_DO_SISTEMA
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaCancela: //Caso tecla CANCELA pressionada então
			{
				tela = TELA_INICIAL; //tela é igual a TELA_INICIAL
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				estado = ESTADO_RELIGA_INTERRUPCOES; //Estado a ser executado é ESTADO_RELIGA_INTERRUPCOES
				teclapressionada = 0; //Limpa teclapressionada
				configAnaliseControle();
				break;
			}
			break;
		}
	}
	else if (tela == TELA_INFORMACOES_DE_ENERGIA) //MENU 6 - INFORMACOES DE ENERGIA - ACESSO PERMITIDO PARA TODOS
	{
		switch (teclapressionada) //Conforme tecla pressionada executa o case específico
		{
			case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
			case teclaTrava:
			{
				if(senha_de_acesso == SENHA_DA_GERENCIA) //Se senha_de_acesso for igual a SENHA_DA_GERENCIA então
				{
					tela = TELA_AJUSTES_BASICOS; //tela é igual a TELA_AJUSTES_BASICOS
				}
				else if(senha_de_acesso == SENHA_DO_TECNICO || senha_de_acesso == SENHA_DA_ENGENHARIA) //Se senha_de_acesso for igual a SENHA_DO_TECNICO ou SENHA_DA_ENGENHARIA então
				{
					tela = TELA_DIAGNOSTICO_DO_SISTEMA; //tela é igual a TELA_DIAGNÓSTICO_DO_SISTEMA
				}
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
			case teclaDestrava:
			{
				tela = TELA_INFORMACOES_DO_SISTEMA; //tela é igual a TELA_INFORMACOES_DO_SISTEMA
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaConfirma: //Caso tecla CONFIRMA pressionada então
			case teclaConfirma_Remoto:
			{
				estado = ESTADO_INFORMACOES_DE_ENERGIA; //Estado a ser executado é ESTADO_INFORMACOES_DE_ENERGIA
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaCancela: //Caso tecla CANCELA pressionada então
			{
				tela = TELA_INICIAL; //tela é igual a TELA_INICIAL
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				estado = ESTADO_RELIGA_INTERRUPCOES; //Estado a ser executado é ESTADO_RELIGA_INTERRUPCOES
				teclapressionada = 0; //Limpa teclapressionada
				configAnaliseControle();
				break;
			}
			break;
		}
	}
	else if (tela == TELA_DIAGNOSTICO_DO_SISTEMA) //MENU 7 - DIAGNÓSTICO DO SISTEMA - ACESSO PERMITIDO PARA TÉCNICO E ENGENHARIA
	{
		switch (teclapressionada) //Conforme tecla pressionada executa o case específico
		{
			case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
			case teclaTrava:
			{
				tela = TELA_BARGRAPH; //tela é igual a TELA_BARGRAPH
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
			case teclaDestrava:
			{
				tela = TELA_INFORMACOES_DE_ENERGIA; //tela é igual a TELA_INFORMACOES_DE_ENERGIA
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaConfirma: //Caso tecla CONFIRMA pressionada então
			case teclaConfirma_Remoto:
			{
				estado = ESTADO_DIAGNOSTICO_DO_SISTEMA; //Estado a ser executado é ESTADO_DIAGNOSTICO_DO_SISTEMA
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaCancela: //Caso tecla CANCELA pressionada então
			{
				tela = TELA_INICIAL; //tela é igual a TELCA_INICIAL
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				estado = ESTADO_RELIGA_INTERRUPCOES; //Estado a ser executado é ESTADO_RELIGA_INTERRUPCOES
				teclapressionada = 0; //Limpa teclapressionada
				configAnaliseControle();
				break;
			}
			break;
		}
	}
	else if (tela == TELA_BARGRAPH) //MENU 8 - BARGRAPH - ACESSO PERMITIDO PARA TÉCNICO E ENGENHARIA
	{
		switch (teclapressionada) //Conforme tecla pressionada executa o case específico
		{
			case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
			case teclaTrava:
			{
				tela = TELA_COMPATIBILIDADE_ELETROMAGNETICA; //tela é igual a TELA_COMPATIBILIDADE_ELETROMAGNETICA
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
			case teclaDestrava:
			{
				tela = TELA_DIAGNOSTICO_DO_SISTEMA; //tela é igual a TELA_DIAGNOSTICO_DO_SISTEMA
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaConfirma: //Caso tecla CONFIRMA pressionada então
			case teclaConfirma_Remoto:
			{
				estado = ESTADO_MOSTRA_BARGRAPH; //Estado a ser executado é ESTADO_MOSTRA_BARGRAPH
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaCancela: //Caso tecla CANCELA pressionada então
			{
				tela = TELA_INICIAL; //tela é igual a TELA_INICIAL
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				estado = ESTADO_RELIGA_INTERRUPCOES; //Estado a ser executado é ESTADO_RELIGA_INTERRUPCOES
				teclapressionada = 0; //Limpa teclapressionada
				configAnaliseControle();
				break;
			}
			break;
		}
	}
	else if (tela == TELA_COMPATIBILIDADE_ELETROMAGNETICA) //MENU 9 - COMPATIBILIDADE ELETROMAGNETICA - ACESSO PERMITIDO PARA TÉCNICO E ENGENHARIA
	{
		switch (teclapressionada) //Conforme tecla pressionada executa o case específico
		{
			case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
			case teclaTrava:
			{
				if(senha_de_acesso == SENHA_DO_TECNICO) //Se senha_de_acesso for igual a SENHA_DO_TECNICO então
				{
					tela = TELA_AJUSTES_BASICOS; //tela é igual a TELA_AJUSTES_BASICOS
				}
				else if(senha_de_acesso == SENHA_DA_ENGENHARIA) //Se senha_de_acesso for igual a SENHA_DA_ENGENHARIA
				{
					tela = TELA_AJUSTES_TX_RX; //tela é igual a TELA_AJUSTES_TX_RX
				}
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
			case teclaDestrava:
			{
				tela = TELA_BARGRAPH; //tela é igual a TELA_BARGRAPH
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaConfirma: //Caso tecla CONFIRMA pressionada então
			case teclaConfirma_Remoto:
			{
				estado = ESTADO_MOSTRA_COMPATIBILIDADE_ELETROMAGNETICA; //Estado a ser executado é ESTADO_MOSTRA_COMPATIBILIDADE_ELETROMAGNETICA
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaCancela: //Caso tecla CANCELA pressionada então
			{
				tela = TELA_INICIAL; //tela é igual a TELA_INICIAL
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				estado = ESTADO_RELIGA_INTERRUPCOES; //Estado a ser executado é ESTADO_RELIGA_INTERRUPCOES
				teclapressionada = 0; //Limpa teclapressionada
				configAnaliseControle();
				break;
			}
			break;
		}
	}

	else if (tela == TELA_AJUSTES_TX_RX) //MENU 10 - AJUSTES_TX_RX - ACESSO PERMITIDO PARA ENGENHARIA
	{
		switch (teclapressionada) //Conforme tecla pressionada executa o case específico
		{
			case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
			case teclaTrava:
			{
				tela = TELA_MODELO_DE_ANTENA; //tela é igual a TELA_MODELO_DE_ANTENA
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
			case teclaDestrava:
			{
				tela = TELA_COMPATIBILIDADE_ELETROMAGNETICA; //tela é igual a TELA_COMPATIBILIDADE_ELETROMAGNETICA
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaConfirma: //Caso tecla CONFIRMA pressionada então
			case teclaConfirma_Remoto:
			{
				estado = ESTADO_AJUSTES_TX_RX; //Estado a ser executado é ESTADO_AJUSTES_TX_RX
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaCancela: //Caso tecla CANCELA pressionada então
			{
				tela = TELA_INICIAL; //tela é igual a TELA_INICIAL
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				estado = ESTADO_RELIGA_INTERRUPCOES; //Estado a ser executado é ESTADO_RELIGA_INTERRUPCOES
				teclapressionada = 0; //Limpa teclapressionada
				configAnaliseControle();
				break;
			}
			break;
		}
	}
	else if (tela == TELA_MODELO_DE_ANTENA)	//MENU 11 - MODELO DE ANTENA - ACESSO PERMITIDO PARA ENGENHARIA
	{
		switch (teclapressionada) //Conforme tecla pressionada executa o case específico
		{
			case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
			case teclaTrava:
			{
				tela = TELA_POTENCIOMETRO_DE_GANHO; //tela é igual a TELA_POTENCIOMETRO_DE_GANHO
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
			case teclaDestrava:
			{
				tela = TELA_AJUSTES_TX_RX; //tela é igual a TELA_AJUSTES_TX_RX
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaConfirma: //Caso tecla CONFIRMA pressionada então
			case teclaConfirma_Remoto:
			{
				estado = ESTADO_MODELO_DE_ANTENA; //Estado a ser executado é ESTADO_MODELO_DE_ANTENA
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaCancela: //Caso tecla CANCELA pressionada então
			{
				tela = TELA_INICIAL; //tela é igual a TELA_INICIAL
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				estado = ESTADO_RELIGA_INTERRUPCOES; //Estado a ser executado é ESTADO_RELIGA_INTERRUPCOES
				teclapressionada = 0; //Limpa teclapressionada
				configAnaliseControle();
				break;
			}
			break;
		}
	}
	else if (tela == TELA_POTENCIOMETRO_DE_GANHO) //MENU 12 - POTENCIOMETRO DE GANHO - ACESSO PERMITIDO PARA ENGENHARIA
	{
		//MENU REMOVIDO, COMENTE ESSE SNIP PARA RETORNAR O MENU

			if(INCREMENTA){
				tela = TELA_TIPO_DETECTOR;
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				return;
			} else {
				tela = TELA_MODELO_DE_ANTENA; //tela é igual a TELA_POTENCIOMETROS_DE_GANHO
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				return;
			}

		///////
		switch (teclapressionada) //Conforme tecla pressionada executa o case específico
		{
			case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
			case teclaTrava:
			{
				tela = TELA_POTENCIOMETRO_DE_SELECAO_DE_METAIS; //tela é igual a TELA_POTENCIOMETRO_DE_SELECAO_DE_METAIS
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
			case teclaDestrava:
			{
				tela = TELA_MODELO_DE_ANTENA; //tela é igual a TELA_MODELO_DE_ANTENA
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaConfirma: //Caso tecla CONFIRMA pressionada então
			case teclaConfirma_Remoto:
			{
				estado = ESTADO_POTENCIOMETRO_DE_GANHO; //Estado a ser executado é ESTADO_POTENCIOMENTO_DE_GANHO
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaCancela: //Caso tecla CANCELA pressionada então
			{
				tela = TELA_INICIAL; //tela é igual a TELA_INICIAL
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				estado = ESTADO_RELIGA_INTERRUPCOES; //Estado a ser executado é ESTADO_RELIGA_INTERRUPCOES
				teclapressionada = 0; //Limpa teclapressionada
				configAnaliseControle();
				break;
			}
			break;
		}
	}
	else if (tela == TELA_POTENCIOMETRO_DE_SELECAO_DE_METAIS) //MENU 13 - POTENCIOMETRO DE SELECAO DE METAIS - ACESSO PERMITIDO PARA ENGENHARIA
	{
		//MENU REMOVIDO, COMENTE ESSE SNIP PARA RETORNAR O MENU

			if(INCREMENTA){
				tela = TELA_TIPO_DETECTOR;
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				return;
			} else {
				tela = TELA_MODELO_DE_ANTENA; //tela é igual a TELA_POTENCIOMETROS_DE_GANHO
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				return;
			}

		///////



		switch (teclapressionada) //Conforme tecla pressionada executa o case específico
		{
			case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
			case teclaTrava:
			{
				tela = TELA_TIPO_DETECTOR; //tela é igual a TELA_AJUSTES_BASICOS
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
			case teclaDestrava:
			{
				tela = TELA_POTENCIOMETRO_DE_GANHO; //tela é igual a TELA_POTENCIOMETROS_DE_GANHO
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaConfirma: //Caso tecla CONFIRMA pressionada então
			case teclaConfirma_Remoto:
			{
				estado = ESTADO_POTENCIOMETRO_DE_SELECAO_DE_METAIS; //Estado a ser executado é ESTADO_POTENCIOMENTO_DE_SELECAO_DE_METAIS
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaCancela: //Caso tecla CANCELA pressionada então
			{
				tela = TELA_INICIAL; //tela é igual a TELA_INICIAL
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				estado = ESTADO_RELIGA_INTERRUPCOES; //Estado a ser executado é ESTADO_RELIGA_INTERRUPCOES
				teclapressionada = 0; //Limpa teclapressionada
				configAnaliseControle();
				break;
			}
			break;
		}
	}
	else if (tela == TELA_TIPO_DETECTOR) //MENU 13 - POTENCIOMETRO DE SELECAO DE METAIS - ACESSO PERMITIDO PARA ENGENHARIA
	{
		switch (teclapressionada) //Conforme tecla pressionada executa o case específico
		{
			case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
			case teclaTrava:
			{
				tela = TELA_AJUSTES_BASICOS; //tela é igual a TELA_AJUSTES_BASICOS
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
			case teclaDestrava:
			{
				tela = TELA_POTENCIOMETRO_DE_SELECAO_DE_METAIS; //tela é igual a TELA_POTENCIOMETROS_DE_GANHO
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaConfirma: //Caso tecla CONFIRMA pressionada então
			case teclaConfirma_Remoto:
			{
				estado = ESTADO_TIPO_DETECTOR; //Estado a ser executado é ESTADO_POTENCIOMENTO_DE_SELECAO_DE_METAIS
				teclapressionada = 0; //Limpa teclapressionada
				break;
			}
			case teclaCancela: //Caso tecla CANCELA pressionada então
			{
				tela = TELA_INICIAL; //tela é igual a TELA_INICIAL
				estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
				estado = ESTADO_RELIGA_INTERRUPCOES; //Estado a ser executado é ESTADO_RELIGA_INTERRUPCOES
				teclapressionada = 0; //Limpa teclapressionada
				configAnaliseControle();
				break;
			}
			break;
		}
	}
}
/******************************************************************************/

/*** Funções do MENU AJUSTES BÁSICOS ***/
void fnAjustesBasicos(void) //Menu para escolher entre as funções ajuste de sensibilidade manual, ajuste automático de sensibilidade e modo de travamento
{
	static byte estadoAjustesBasicos = 1; //Variável para o switch case abaixo

	switch(estadoAjustesBasicos) //Conforme variável vai para o case especificado
	{
		case 1: //Caso 1 então
		{
			tela = TELA_MOSTRA_AJUSTES_BASICOS; //tela é igual a TELA_MOSTRA_AJUSTES_BASICOS
			estadoAjustesBasicos = 2; //Coloca a variável para 2 para entrar no case 2
			estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
			if(!flagretorno) //Se flagretorno for zero então inicializa variável menu
			{
				menu = 1; //menu é igual a 1
			}
			flagretorno = 0; //flagretorno é zero
			break;
		}
		case 2:
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					menu++;	//Incrementa menu
					if(menu > 4) //Se menu for maior que 3
					{
						menu = 1; //menu é igual a 1
					}
					tela = TELA_MOSTRA_AJUSTES_BASICOS; //tela é igual a TELA_MOSTRA_AJUSTES_BASICOS
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					menu--; //Decrementa menu
					if(menu < 1) //Se menu for menor que 1
					{
						menu = 4; //menu é igual a 3
					}
					tela = TELA_MOSTRA_AJUSTES_BASICOS; //tela é igual a TELA_MOSTRA_AJUSTES_BASICOS
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					if(menu == 1) //Se menu for igual a 1 então
					{
						tela = TELA_AJUSTE_MANUAL_DE_SENSIBILIDADE; //tela é igual a TELA_AJUSTE_MANUAL_DE_SENSIBILIDADE
						estado = ESTADO_AJUSTE_MANUAL_SENSIBILIDADE; //Estado a ser executado é ESTADO_AJUSTE_MANUAL_SENSIBILIDADE
						estadoAjustesBasicos = 1; //Coloca a variável estadoAjustesBasicos para 1 para voltar a camada 1 desta função
					}
					else if(menu == 2) //Se menu for igual a 2 então
					{
						tela = TELA_AJUSTE_AUTOMATICO_DA_SENSIBILIDADE; //tela é igual a TELA_AJUSTE_AUTOMATICO_DA_SENSIBILIDADE
						estado = ESTADO_AJUSTE_AUTOMATICO_SENSIBILIDADE; //Estado a ser executado é ESTADO_AJUSTE_AUTOMATICO_SENSIBILIDADE
						estadoAjustesBasicos = 1; //Coloca a variável estadoAjustesBasicos para 1 para voltar a camada 1 desta função
					}
					else if(menu == 3) //Se menu for igual a 3 então
					{
						tela = TELA_MODO_DE_TRAVAMENTO; //tela é igual a TELA_MODO_DE_TRAVAMENTO
						estado = ESTADO_MODO_DE_TRAVAMENTO; //Estado a ser executado é ESTADO_MODO_DE_TRAVAMENTO
						estadoAjustesBasicos = 1; //Coloca a variável estadoAjustesBasicos para 1 para voltar a camada 1 desta função
					}
					else if(menu == 4) //Se menu for igual a 4 então
					{
						tela = TELA_INICIAR_SORTEADOR; //tela é igual a TELA_CONFIRMA_INICIAR1
						estado = ESTADO_SORTEADOR_ELETRONICO; //Estado a ser executado é ESTADO_SORTEADOR_ELETRONICO
						estadoAjustesBasicos = 1; //Coloca a variável estadoAjustesBasicos para 1 para voltar a camada 1 desta função
					}
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tela = TELA_AJUSTES_BASICOS; //tela é igual a TELA_AJUSTES_BASICOS
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					estadoAjustesBasicos = 1; //Coloca a variável estadoAjustesBasicos para 1 para voltar a camada 1 desta função
					estado = ESTADO_NAVEGA_MENU_FUNCOES; //Estado a ser executado é ESTADO_NAVEGA_MENU_FUNCOES com retorno a primeira camada da função que é AJUSTES BASICOS
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


/*** Funções do MENU AJUSTES AVANÇADOS ***/
void fnAjustesAvancados(void) //Permite escolher entre as funções do menu AJUSTES AVANÇADOS
{
	static byte estadoAjustesAvancados = 1; //Definindo variável estadoAjustesAvancaods para o switch case abaixo

	switch(estadoAjustesAvancados) //Conforme variável vai para o case específico
	{
		case 1: //ENTRA NO MENU AJUSTES AVANÇADOS
		{
			tela = TELA_MOSTRA_AJUSTES_AVANCADOS; //Tela é igual a TELA_MOSTRA_AJUSTES_AVANCADOS
			estadoAjustesAvancados = 2; //Coloca a variável para 2 para entrar no case 2
			estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
			if(!flagretorno) //Se flagretorno for zero então faz com que a variável menu seja 1 novamente
			{
				menu = 1; //Armazena 1 em menu
			}
			flagretorno = 0; //Zera flagretorno para retornar a última posição em que a variável menu estava
			break;
		}
		case 2: //ESCOLHE ENTRE AS OPÇÕES DO MENU AJUSTES AVANÇADOS
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					menu++; //Incrementa menu
					if(menu > 16) //Se menu for maior que 16 então
					{
						menu = 1; //Armazena 1 na variável menu
					}
					tela = TELA_MOSTRA_AJUSTES_AVANCADOS; //Tela é igual a TELA_MOSTRA_AJUSTES_AVANCADOS
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					menu--; //Decrementa menu
					if(menu < 1) //Se menu for menor que 1 então
					{
						menu = 16; //Armazena 16 na variável menu
					}
					tela = TELA_MOSTRA_AJUSTES_AVANCADOS; //Tela é igual a TELA_MOSTRA_AJUSTES_AVANCADOS
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					if(menu == 1) //Se menu for igual a 1 então
					{
						estado = ESTADO_AJUSTE_MANUAL_CANAL; //Estado a ser executado é ESTADO_AJUSTE_MANUAL_CANAL
					}
					else if(menu == 2) //Se menu for igual a 2 então
					{
						tela = TELA_SINTONIZANDO; //Tela é igual a TELA_SINTONIZANDO
						estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
						estado = ESTADO_AJUSTE_AUTOMATICO_CANAL; //Estado a ser executado é ESTADO_AJUSTE_AUTOMATICO_CANAL
					}
					else if(menu == 3) //Se menu for igual a 3 então
					{
						estado = ESTADO_SELECAO_METAIS; //Estado a ser executado é ESTADO_SELECAO_METAIS
					}
					else if(menu == 4) //Se menu for igual a 4 então
					{
						estado = ESTADO_CONFIGURA_TRAVA; //Estado a ser executado é ESTADO_CONFIGURA_TRAVA
					}
					else if(menu == 5) //Se menu for igual a 5 então
					{
						estado = ESTADO_CONFIGURA_RELE; //Estado a ser executado é ESTADO_CONFIGURA_RELE
					}
					else if(menu == 6) //Se menu for igual a 6 então
					{
						estado = ESTADO_CONFIGURA_CONTROLE_REMOTO; //Estado a ser executado é ESTADO_CONFIGURA_CONTROLE_REMOTO
					}
					else if(menu == 7) //Se menu for igual a 7 então
					{
						estado = ESTADO_CONFIGURA_INFRAVERMELHO; //Estado a ser executado é ESTADO_CONFIGURA_INFRAVERMELHO
					}
					else if(menu == 8) //Se menu for igual a 8 então
					{
						estado = ESTADO_ANULA_AREAS; //Estado a ser executado é ESTADO_ANULA_AREAS
					}
					else if(menu == 9) //Se menu for igual a 9 então
					{
						estado = ESTADO_FILTRO_RUIDO; //Estado a ser executado é ESTADO_FILTRO_RUIDO
					}
					else if(menu == 10) //Se menu for igual a 10 então
					{
						estado = ESTADO_TRAVA_INTELIGENTE; //Estado a ser executado é ESTADO_TRAVA_INTELIGENTE
					}
					else if(menu == 11) //Se menu for igual a 11 então
					{
						estado = ESTADO_PORTA_AUTOMATICA; //Estado a ser executado é ESTADO_TRAVA_INTELIGENTE
					}
					else if(menu == 12) //Se menu for igual a 12 então
					{
						estado = ESTADO_ZERAR_LOG_EVENTOS;  //Estado a ser executado é ESTADO_ZERAR_LOG_EVENTOS
					}
					else if(menu == 13) //Se menu for igual a 13 então
					{
						estado = ESTADO_CONFIGURACOES_DE_INTERNET; //Estado a ser executado é ESTADO_CONFIGURAÇÕES DE INTERNET
					}
					else if(menu == 14) //Se menu for igual a 14 então
					{
						estado = ESTADO_ELIMINAR_FALHA_DAS_BOBINAS; //Estado a ser executado é ESTADO ELIMINAR FALHA DAS BOBINAS
					}
					else if(menu == 15) //Se menu for igual a 15 então
					{
						estado = ESTADO_OPCAO_SENSOR_CONTADOR; //Estado a ser executado é ESTADO OPCAO SENSOR CONTADOR
					}
					else if(menu == 16)
					{
						estado = ESTADO_POTENCIOMETRO_DE_GANHO;
					}
					estadoAjustesAvancados = 1; //Coloca a variável estadoAjustesAvancados para 1 para voltar a camada 1 desta função
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tela = TELA_AJUSTES_AVANCADOS; //Tela é igual a TELA_AJUSTES_AVANCADOS
					estado_LCD = ATUALIZA_LCD; //Manda atualizar LCD fazendo estado_LCD ser igual a ATUALIZA_LCD
					estadoAjustesAvancados = 1; //Coloca a variável estadoAjustesAvancados para 1 para voltar a camada 1 desta função
					estado = ESTADO_NAVEGA_MENU_FUNCOES; //Estado a ser executado é ESTADO_NAVEGA_MENU_FUNCOES
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



/*** Funções do MENU AJUSTES DO SISTEMA ***/
void fnAjustesdoSistema(void) //Permite escolher entre as funções abaixo
{
	static byte estadoAjustesdoSistema = 1; //Definindo a variável estadoAjustesdoSistema para o switch case abaixo

	switch(estadoAjustesdoSistema) //Conforme valor da variável estadoAjustesdoSistema vai para o case específico
	{
		case 1: //ENTRA NO MENU AJUSTES DO SISTEMA PARA ESCOLHER ENTRE UMA DAS 4 FUNÇÕES
		{
			tela = TELA_MOSTRA_AJUSTES_DO_SISTEMA; //Tela é igual a TELA_MOSTRA_AJUSTES_DO_SISTEMA
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estadoAjustesdoSistema = 2; //Coloca a variável estadoAjustesdoSistema para 2 para ir para o case 2
			if(!flagretorno) //Se flagretorno for igual a zero então
			{
				menu = 1; //Armazena na variável menu o valor 1
			}
			flagretorno = 0; //Armazena na variável flagretorno o valor zero
			break;
		}
		case 2:
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					menu++; //Incrementa a variável menu
					if(senha_de_acesso == SENHA_DA_GERENCIA && menu == 3)
					{
						menu = 5;
					}
					if(menu > 5) //Se menu for maior que 4 então
					{
						menu = 1; //Armazena na variável menu o valor 1
					}
					tela = TELA_MOSTRA_AJUSTES_DO_SISTEMA; //Tela é igual a TELA_MOSTRA_AJUSTES_DO_SISTEMA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa a teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					menu--; //Decrementa a variável menu
					if(senha_de_acesso == SENHA_DA_GERENCIA && menu == 3)
					{
						menu = 2;
					}
					if(menu < 1) //Se menu for menor que 1 então
					{
						menu = 5; //Armazena na variável menu o valor 4
					}
					tela = TELA_MOSTRA_AJUSTES_DO_SISTEMA; //Tela é igual a TELA_MOSTRA_AJUSTES_DO_SISTEMA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa a teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					if(menu == 1) //Se menu for igual a 1 então
					{
						estado = ESTADO_HORA_E_DATA; //Estado a ser executado é ESTADO_HORA_E_DATA
					}
					else if(menu == 2) //Senão se menu for igual a 2 então
					{
						estado = ESTADO_ALTERA_SENHA; //Estado a ser executado é ESTADO_ALTERA_SENHA
						definicoes = 1; //Armazena na variável definicoes o valor 1
					}
					else if(menu == 3) //Senão se menu for igual a 3 então
					{
						estado = ESTADO_ALTERA_SENHA; //Estado a ser executado é ESTADO_ALTERA_SENHA
						definicoes = 2;
					}
					else if(menu == 4) //Senão se menu for igual a 4 então
					{
						estado = ESTADO_RESETAR_PADRAO_FABRICA; //Estado a ser executado é ESTADO_RESETAR_PADRAO_FABRICA
					}
					else if(menu == 5) //Senão se menu for igual a 5 então
					{
						estado = ESTADO_IDIOMA; //Estado a ser executado é ESTADO_IDIOMA
					}
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tela = TELA_AJUSTES_DO_SISTEMA; //Tela é igual a TELA_AJUSTES_DO_SISTEMA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estadoAjustesdoSistema = 1; //Coloca a variável estadoAjustesdoSistema para 1 para ir para o nivel 1 deste menu
					estado = ESTADO_NAVEGA_MENU_FUNCOES; //Estado a ser executado é ESTADO_NAVEGA_MENU_FUNCOES
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


/*** Funções do MENU AJUSTES DE ALARME ***/
void fnAjustesdeAlarme(void) //Permite escolher entre as funções abaixo
{
	static byte estadoAjustesdeAlarme = 1; //Definindo variável estadoAjustesdeAlarme para o switch case abaixo

	switch(estadoAjustesdeAlarme) //Conforme valor da variável estadoAjustesdeAlarme vai para o case específico
	{
		case 1: //ENTRA NO MENU AJUSTES DE ALARME
		{
			menu = 1;
			menu1 = 1; //Armazena na variável menu1 o valor 1
			menu2 = 1; //Armazena na variável menu2 o valor 1
			menu3 = 0; //Armazena na variável menu3 o valor 0
			tela = TELA_MOSTRA_AJUSTES_DE_ALARME; //Tela é igual a TELA_MOSTRA_AJUSTES_DE_ALARME
			estadoAjustesdeAlarme = 2; //Coloca a variável estadoAjustesdeAlarme para 2 para ir para o case 2
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			if(!flagretorno) //Se flagretorno for igual a zero então
			{
				menu = 1; //Inicializa a variável menu com o valor 1
			}
			flagretorno = 0; //Zera a flagretorno
			break;
		}
		case 2: //MENU PARA ESCOLHER ALARME SONORO
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					menu++; //Incrementa menu
					if(menu > 1) //Se menu for maior que 1 então
					{
						menu = 1; //Armazena na variável menu o valor 1
					}
					tela = TELA_MOSTRA_AJUSTES_DE_ALARME; //Tela é igual a TELA_MOSTRA_AJUSTES_DE_ALARME
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					menu--; //Decrementa menu
					if(menu < 1) //Se menu for menor que 1 então
					{
						menu = 1; //Armazena na variável menu o valor 1
					}
					tela = TELA_MOSTRA_AJUSTES_DE_ALARME; //Tela é igual a TELA_MOSTRA_AJUSTES_DE_ALARME
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					if(menu == 1) //Se menu for igual a 1 então
					{
						estado = ESTADO_CONFIGURA_ALARME_SONORO; //Estado a ser executado é ESTADO_CONFIGURA_ALARME_SONORO
					}
					else if(menu == 2) //Se menu for igual a 2 então
					{
						estado = ESTADO_LIG_DES_ALARME_VISUAL; //Estado a ser executado é ESTADO_LIG_DES_ALARME_VISUAL
					}
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estadoAjustesdeAlarme = 1; //Coloca a variável estadoAjustesdeAlarme para 2 para ir para o primeiro nivel deste menu
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tela = TELA_AJUSTES_DE_ALARME; //Tela é igual a TELA_AJUSTES_DE_ALARME
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_NAVEGA_MENU_FUNCOES; //Estado a ser executado é ESTADO_NAVEGA_MENU_FUNCOES
					estadoAjustesdeAlarme = 1; //Coloca a variável estadoAjustesdeAlarme para 2 para ir para o primeiro nivel deste menu
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

/*** Funções do MENU INFORMAÇÕES DO SISTEMA ***/
void fnInformacoesdoSistema(void) //Permite escolher entre as funções abaixo
{
	static byte estadoInformacoesdoSistema = 1; //Definindo variável estadoInformacoesdoSistema para o switch case abaixo

	switch(estadoInformacoesdoSistema) //Conforme valor da variável estadoConfiguraAlarmeVisual vai para o case específico
	{
		case 1: //ENTRA NO MENU INFORMAÇÕES DO SISTEMA PARA ESCOLHER UMA DAS FUNÇÕES
		{
			menu1 = 1; //Armazena na variável menu1 o valor 1
			tela = TELA_MOSTRA_INFORMACOES_DO_SISTEMA; //Tela é igual a TELA_MOSTRA_INFORMACOES_DO_SISTEMA
			estadoInformacoesdoSistema = 2; //Coloca a variável estadoInformacoesdoSistema para 2 para ir para o case 2
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			if(!flagretorno) //Se flagretorno for igual a zero então
			{
				menu = 1; //Armazena na variável menu o valor 1
			}
			flagretorno = 0; //Zera a flagretorno
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //ESCOLHE UMA DENTRE AS 5 FUNÇÕES DO MENU INFORMAÇÕES DO SISTEMA
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					menu++; //Incrementa menu
					if(menu > 4) //Se menu for maior que 5 então
					{
						menu = 1; //Armazena na variável menu o valor 1
					}
					tela = TELA_MOSTRA_INFORMACOES_DO_SISTEMA; //Tela é igual a TELA_MOSTRA_INFORMACOES_DO_SISTEMA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					menu--; //Decrementa menu
					if(menu < 1) //Se menu for menor que 1 então
					{
						menu = 4; //Armazena na variável menu o valor 5
					}
					tela = TELA_MOSTRA_INFORMACOES_DO_SISTEMA; //Tela é igual a TELA_MOSTRA_INFORMACOES_DO_SISTEMA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					if(menu == 1) //Se menu for igual a 1 então
					{
						estado = ESTADO_CONTADOR_DETECCOES; //Estado a ser executado é ESTADO_CONTADOR_DETECCOES
					}
					else if(menu == 2) //Se menu for igual a 1 então
					{
						estado = ESTADO_CONTADOR_PASSAGENS; //Estado a ser executado é ESTADO_CONTADOR_PASSAGENS
					}
					else if(menu == 3) //Se menu for igual a 1 então
					{
						estado = ESTADO_NUMERO_DE_SERIE; //Estado a ser executado é ESTADO_NUMERO_DE_SERIE
					}
					else if(menu == 4) //Se menu for igual a 1 então
					{
						estado = ESTADO_NUMERO_DE_SERIE1; //Estado a ser executado é ESTADO_NUMERO_DE_SERIE1 --
					}
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estadoInformacoesdoSistema = 1; //Coloca a variável estadoInformacoesdoSistema para 1 para ir para o primeiro nivel deste menu
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tela = TELA_INFORMACOES_DO_SISTEMA; //Tela é igual a TELA_INFORMACOES_DO_SISTEMA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estadoInformacoesdoSistema = 1; //Coloca a variável estadoInformacoesdoSistema para 1 para ir para o primeiro nivel deste menu
					estado = ESTADO_NAVEGA_MENU_FUNCOES; //Estado a ser executado é ESTADO_NAVEGA_MENU_FUNCOES
					teclapressionada = 0; //Limpa teclapressionada
					flagretorno = 0; //Zera flagretorno
					break;
				}
				break;
			}
			break;
		}
		break;
	}
}


/*** Funções do MENU INFORMAÇÕES DE ENERGIA ***/
void fnInformacoesdeEnergia(void) //Permite visualizar as tensões AC, tensões DC +5V,+15V,-15V,+24V e das tensões da BATERIA
{
	static byte estadoInformacoesdeEnergia = 1; //Definindo variável estadoInformacoesdeEnergia para o switch case abaixo
	static dword timer_tensoes_aux = 10; //Armazena a variável timer_tensoes_aux com o valor 10
	static byte cont_tela = 1;

	switch(estadoInformacoesdeEnergia) //Conforme valor da variável estadoInformacoesdeEnergia vai para o case específico
	{
		case 1: //ENTRA NO MENU DE INFORMACOES DE ENERGIA
		{
			tela = TELA_TENSAO_AC; //Tela é igual a TELA_TENSAO_AC
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estadoInformacoesdeEnergia = 2; //Coloca a variável estadoInformacoesdeEnergia para 2 para ir para o case 2
			timer_tensoes = 0; //Zera o contador de tempo de timer_tensoes
			SendCan(FONTE_CAN,GET_TENSOES); //Envia para FONTE para requisitar as tensões
			break;
		}
		case 2: //VISUALIZA AS TENSÕES A CADA SEGUNDO
		{
			//Imprime tela desejada
			fnEncaminhaImprimeTelaInformacoesdeEnergia(tela,&timer_tensoes_aux);


			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				{
					cont_tela++; //Incrementa tela
					if(cont_tela > 4) //Se tela for maior que TELA_TENSAO_DAS_BATERIAS
					{
						cont_tela = 1;
					}
					if(cont_tela == 1)
					{
						tela = TELA_TENSAO_AC;
					}
					else if(cont_tela == 2)
					{
						tela = TELA_TENSAO_DC;
					}
					else if(cont_tela == 3)
					{
						tela = TELA_TENSAO_DAS_BATERIAS;
					}
					else if(cont_tela == 4)
					{
						tela = TELA_TENSAO_24V;
					}
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				{
					cont_tela--; //Decrementa tela
					if(cont_tela < 1) //Se tela for menor que TELA_TENSAO_AC então
					{
						cont_tela = 4; //Tela é igual a TELA_TENSAO_DAS_BATERIAS
					}
					if(cont_tela == 1)
					{
						tela = TELA_TENSAO_AC;
					}
					else if(cont_tela == 2)
					{
						tela = TELA_TENSAO_DC;
					}
					else if(cont_tela == 3)
					{
						tela = TELA_TENSAO_DAS_BATERIAS;
					}
					else if(cont_tela == 4)
					{
						tela = TELA_TENSAO_24V;
					}
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					estadoInformacoesdeEnergia = 1; //Coloca a variável estadoInformacoesdeEnergia para 1 para ir para o primeiro nivel deste menu
					tela = TELA_INFORMACOES_DE_ENERGIA; //Tela é igual a TELA_INFORMACOES_DE_ENERGIA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_NAVEGA_MENU_FUNCOES; //Estado a ser executado é ESTADO_NAVEGA_MENU_FUNCOES
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
/******************************************************************************/

void fnDiagnosticodoSistema(void) //Permite testar alguns periféricos do sistema tais como leds, trava, relé, buzzer, etc
{
	static byte estadoDiagnosticoSistema = 1; //Definindo variável estadoDiagnosticoSistema para o switch case abaixo

	switch(estadoDiagnosticoSistema) //Conforme valor da variável estadoDiagnosticoSistema vai para o case específico
	{
		case 1: //ENTRA NO MENU DIAGNÓSTICO DO SISTEMA
		{
			menu1 = 1; //Aramazena na variável menu1 o valor 1
			tela = TELA_MOSTRA_DIAGNOSTICO_SISTEMA; //Tela é igual a TELA_MOSTRA_DIAGNOSTICO_SISTEMA
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estadoDiagnosticoSistema = 2; //Coloca a variável estadoDiagnosticoSistema para 2 para ir para o case 2
			break;
		}
		case 2: //ESCOLHE QUAL DIAGNÓSTICO REALIZAR
		{
			switch(teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					menu1++; //Incrementa menu1
					if(tipo_detector == Z3) //Se tipo_detector for igual a Z3 então
					{
						if(menu1 > TESTE_SINAL_RX_A2_A3) //Se menu1 for maior que TESTE_SINAL_RX_A2_A3 então
						{
							menu1 = TESTE_LEDS; //Armazena em menu1 a informação TESTE_LEDS
						}
					}
					else if(tipo_detector == Z8) //Senão se tipo_detector for igual a Z8 então
					{
						if(menu1 > TESTE_SINAL_RX_A7_A8) //Se menu1 for maior que TESTE_SINAL_RX_A7_A8 então
						{
							menu1 = TESTE_LEDS; //Armazena em menu1 a informação TESTE_LEDS
						}
					}
					tela = TELA_MOSTRA_DIAGNOSTICO_SISTEMA; //Tela é igual a TELA_MOSTRA_DIAGNOSTICO_SISTEMA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					menu1--; //Decrementa menu1
					if(tipo_detector == Z3) //Se tipo_detector for igual a Z3 então
					{
						if(menu1 < TESTE_LEDS) //Se menu1 for maior que TESTE_LEDS então
						{
							menu1 = TESTE_SINAL_RX_A2_A3; //Armazena em menu1 a informação TESTE_SINAL_RX_A2_A3
						}
					}
					else if(tipo_detector == Z8) //Senão se tipo_detector for igual a Z8 então
					{
						if(menu1 < TESTE_LEDS) //Se menu1 for maior que TESTE_LEDS então
						{
							menu1 = TESTE_SINAL_RX_A7_A8; //Armazena em menu1 a informação TESTE_SINAL_RX_A7_A8
						}
					}
					tela = TELA_MOSTRA_DIAGNOSTICO_SISTEMA; //Tela é igual a TELA_MOSTRA_DIAGNOSTICO_SISTEMA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa a teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					switch(menu1){
					case TESTE_LEDS:
						fnTesteLeds();
					break;
					case TESTE_TRAVA:
						fnTesteTrava();
					break;
					case TESTE_RELE:
						fnTesteRele();
					break;
					case TESTE_BUZZER:
						fnTesteBuzzer();
					break;
					case TESTE_MSG_VOZ:
						fnTesteMsgVoz();
					break;
					//TODO Remove below
					case TESTE_MSG_VOZ1:
						fnTesteMsgVoz1();
					break;
					case TESTE_MSG_VOZ2:
						fnTesteMsgVoz2();
					break;
					case TESTE_MSG_VOZ3:
						fnTesteMsgVoz3();
					break;
					//TODO Till here
					case TESTE_TECLADO:
						fnTesteTeclado();
					break;
					case TESTE_INFRAVERMELHO:
						fnTesteInfravermelho();
					break;
					case TESTE_AUTONOMIA_BATERIA:
						fnTesteAutonomiaBateria();
					break;
					case TESTE_SINAL_RX_A1_A2:
						fnTesteSinalRxA1A2();
					break;
					case TESTE_SINAL_RX_A3_A4:	//Mesma situacao que TESTE_SINAL_RX_A2_A3
						if (tipo_detector == Z3)	fnTesteSinalRxA2A3_Z3();
						if (tipo_detector == Z8)	fnTesteSinalRxA3A4();
					break;
					case TESTE_SINAL_RX_A5_A6:
						if (tipo_detector == Z8)  	fnTesteSinalRxA5A6();
					break;
					case TESTE_SINAL_RX_A7_A8:
						if (tipo_detector == Z8)	fnTesteSinalRxA7A8();
					break;
					default:
						if (menu1 == TESTE_SINAL_RX_A2_A3 && tipo_detector == Z3)
							fnTesteSinalRxA2A3_Z3();
							//Situação já abordada em case TESTE_SINAL_RX_A3_A4, que foi definido como o mesmo TESTE_SINAL_RX_A2_A3
						 	 //		colocada aqui para caso valor de TESTE_SINAL_RX_A2_A3 seja mudado
					break;
					}
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tela = TELA_DIAGNOSTICO_DO_SISTEMA; //Tela é igual a TELA_DIAGNOSTICO_DO_SISTEMA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estadoDiagnosticoSistema = 1;
					estado = ESTADO_NAVEGA_MENU_FUNCOES; //Estado a ser executado é ESTADO_NAVEGA_MENU_FUNCOES
					menu1 = 1; //Armazena na variável menu1 o valor 1
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
/******************************************************************************/

void fnBargraph(void) //Permite visualizar os ruidos mecânicos e eletromagnéticos estando a antena TX emitindo e a RX recebendo sinais da TX
{
	static byte estadoBargraph = 1; //Definindo variável estadoBargraph para o switch case abaixo

	switch(estadoBargraph) //Conforme valor da variável estadoBargraph vai para o case específico
	{
		case 1: //ENTRA NO MENU BARGRAPH
		{
			tela = TELA_MOSTRA_BARGRAPH; //Tela é igual a TELA_MOSTRA_BARGRAPH
			selecionaArea = 1; //Armazena na variável selecionaArea o valor 1
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estadoBargraph = 2; //Coloca a variável estadoBargraph para 2 para ir para o case 2
			teclapressionada = 0; //Limpa a teclapressionada
			break;
		}
		case 2: //ESCOLHE QUAL O PAR DE ÁREAS A SER VISUALIZADO
		{
			switch (teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					selecionaArea++; //Incrementa selecionaArea
					if(tipo_detector == Z3) //Se tipo_detector for igual a Z3 então
					{
						if(selecionaArea > 2) //Se selecionaArea for maior que 2 então
						{
							selecionaArea = 1; //Armazena na variável selecionaArea o valor 1
						}
					}
					else if(tipo_detector == Z8) //Senão se tipo_detector for igual a Z8 então
					{
						if(selecionaArea > 4) //Se selecionaArea for maior que 4 então
						{
							selecionaArea = 1; //Armazena na variável selecionaArea o valor 1
						}
					}
					tela = TELA_MOSTRA_BARGRAPH; //Tela é igual a TELA_MOSTRA_BARGRAPH
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					selecionaArea--; //Decrementa selecionaArea
					if(tipo_detector == Z3) //Se tipo_detector for igual a Z3 então
					{
						if(selecionaArea < 1) //Se selecionaArea for menor que 1 então
						{
							selecionaArea = 2; //Armazena na variável selecionaArea o valor 2
						}
					}
					else if(tipo_detector == Z8) //Senão se tipo_detector for igual a Z8 então
					{
						if(selecionaArea < 1) //Se selecionaArea for menor que 1 então
						{
							selecionaArea = 4; //Armazena na variável selecionaArea o valor 4
						}
					}
					tela = TELA_MOSTRA_BARGRAPH; //Tela é igual a TELA_MOSTRA_BARGRAPH
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					if(selecionaArea == 1) //Se selecionaArea for igual a 1 então
					{
						tela = TELA_A1_A2; //Apresenta o bargraph da área 1 e área 2
					}
					else if(selecionaArea == 2) //Senão se selecionaArea for igual a 2 então
					{
						if(tipo_detector == Z3)
						{
							tela = TELA_A2_A3; //Apresenta o bargraph da área 2 e área 3
						}
						else if(tipo_detector == Z8)
						{
							tela = TELA_A3_A4; //Apresenta o bargraph da área 3 e área 4
						}
					}
					else if(selecionaArea == 3) //Senão se selecionaArea for igual a 3 então
					{
						tela = TELA_A5_A6; //Apresenta o bargraph da área 5 e área 6
					}
					else if(selecionaArea == 4) //Senão se selecionaArea for igual a 4 então
					{
						tela = TELA_A7_A8; //Apresenta o bargraph da área 7 e área 8
					}
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_ESCREVE_BARGRAPH; //Estado a ser executado é ESTADO_ESCREVE_BARGRAPH
					estadoBargraph = 3; //Coloca a variável estadoBargraph para 3 para ir para o case 3
					teclapressionada = 0; //Limpa a teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tela = TELA_BARGRAPH; //Tela é igual a TELA_BARGRAPH
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_NAVEGA_MENU_FUNCOES; //Estado a ser executado é ESTADO_NAVEGA_MENU_FUNCOES
					estadoBargraph = 1; //Coloca a variável estadoBargraph para 1 para ir para o primeiro nivel deste menu
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				break;
			}
			break;
		}
		case 3: //VISUALIZA OS NIVEIS DE RUIDO DA ÁREA ESPECIFICA
		{
			estado = ESTADO_ESCREVE_BARGRAPH; //Estado a ser executado é ESTADO_ESCREVE_BARGRAPH
			switch (teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla DECREMENTA ou tecla TRAVA ou tecla DESTRAVA pressionada então
				case teclaDecrementa:
				case teclaTrava:
				case teclaDestrava:
				{
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA ou tecla CANCELA pressionada então
				case teclaConfirma_Remoto:
				case teclaCancela:
				{
					tela = TELA_BARGRAPH; //Tela é igual a TELA_BARGRAPH
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_NAVEGA_MENU_FUNCOES; //Estado a ser executado é ESTADO_NAVEGA_MENU_FUNCOES
					estadoBargraph = 1; //Coloca a variável estadoBargraph para 1 para ir para o primeiro nivel deste menu
					valor_anterior = 0; //Zera variável valor_anterior
					valor_anterior1 = 0; //Zera variável valor_anterior1
					valor_atual = 0; //Zera variável valor_atual
					valor_atual1 = 0; //Zera variável valor_atual1
					valor_bargraph = 0; //Zera variável valor_bargraph
					valor_bargraph1 = 0; //Zera variável valor_bargraph1
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


/*** Funções do MENU COMPATIBILIDADE ELETROMAGNÉTICA ***/
void fnCompatibilidadeEletromagnetica(void) //Permite visualizar os ruidos eletromagnéticos estando somente a antena RX recebendo sinais do meio ambiente
{
	static byte estadoCompatibilidade = 1; //Definindo variável estadoCompatibilidade para o switch case abaixo

	switch(estadoCompatibilidade) //Conforme valor da variável estadoCompatibilidade vai para o case específico
	{
		case 1: //ENTRA NO MENU COMPATIBILIDADE ELETROMAGNÉTICA
		{
			tela = TELA_MOSTRA_COMPATIBILIDADE; //Tela é igual a TELA_MOSTRA_COMPATIBILIDADE
			selecionaArea = 1; //Armanzena na variável selecionaArea o valor 1
			estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
			estadoCompatibilidade = 2; //Coloca a variável estadoCompatibilidade para 2 para ir para o case 2
			teclapressionada = 0; //Limpa teclapressionada
			break;
		}
		case 2: //SELECIONA O PAR DE ÁREAS A SER MONITORADO
		{
			switch (teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla TRAVA pressionada então
				case teclaTrava:
				{
					selecionaArea++; //Incrementa selecionaArea
					if(tipo_detector == Z3) //Se tipo_detector for igual a Z3 então
					{
						if(selecionaArea > 2) //Se selecionaArea for maior que 2 então
						{
							selecionaArea = 1; //Armazena na variável selecionaArea o valor 1
						}
					}
					else if(tipo_detector == Z8) //Senão se tipo_detector for igual a Z8 então
					{
						if(selecionaArea > 4) //Se selecionaArea for maior que 4 então
						{
							selecionaArea = 1; //Armazena na variável selecionaArea o valor 1
						}
					}
					tela = TELA_MOSTRA_COMPATIBILIDADE; //Tela é igual a TELA_MOSTRA_COMPATIBILIDADE
					estado_LCD = ATUALIZA_LCD;  //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaDecrementa: //Caso tecla DECREMENTA ou tecla DESTRAVA pressionada então
				case teclaDestrava:
				{
					selecionaArea--; //Decrementa selecionaArea
					if(tipo_detector == Z3) //Se tipo_detector for igual a Z3 então
					{
						if(selecionaArea < 1) //Se selecionaArea for menor que 1 então
						{
							selecionaArea = 2; //Armazena na variável selecionaArea o valor 2
						}
					}
					else if(tipo_detector == Z8) //Senão se tipo_detector for igual a Z8 então
					{
						if(selecionaArea < 1) //Se selecionaArea for menor que 1 então
						{
							selecionaArea = 4; //Armazena na variável selecionaArea o valor 4
						}
					}
					tela = TELA_MOSTRA_COMPATIBILIDADE; //Tela é igual a TELA_MOSTRA_COMPATIBILIDADE
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA pressionada então
				case teclaConfirma_Remoto:
				{
					if(selecionaArea == 1) //Se selecionaArea for igual a 1 então
					{
						tela = TELA_A1_A2_COMPATIBILIDADE; //Tela é igual a TELA_A1_A2_COMPATIBILIDADE
					}
					else if(selecionaArea == 2) //Senão se selecionaArea for igual a 2 então
					{
						if(tipo_detector == Z3) //Se tipo_detector for igual a Z3 então
						{
							tela = TELA_A2_A3_COMPATIBILIDADE; //Tela é igual a TELA_A2_A3_COMPATIBILIDADE
						}
						else if(tipo_detector == Z8) //Senão se tipo_detector for igual a Z8 então
						{
							tela = TELA_A3_A4_COMPATIBILIDADE; //Tela é igual a TELA_A3_A4_COMPATIBILIDADE
						}
					}
					else if(selecionaArea == 3) //Senão se selecionaArea for igual a 3 então
					{
						tela = TELA_A5_A6_COMPATIBILIDADE; //Tela é igual a TELA_A5_A6_COMPATIBILIDADE
					}
					else if(selecionaArea == 4) //Senão se selecionaArea for igual a 4 então
					{
						tela = TELA_A7_A8_COMPATIBILIDADE; //Tela é igual a TELA_A7_A8_COMPATIBILIDADE
					}
					FTM0_OUTMASK = 0xFFFFFF03; //desliga PWM TX
					delay_ms(100); //Espera 100 milisegundos
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_ESCREVE_BARGRAPH; //Estado a ser executado é ESTADO_ESCREVE_BARGRAPH
					estadoCompatibilidade = 3; //Coloca a variável estadoCompatibilidade para 3 para ir para o case 3
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaCancela: //Caso tecla CANCELA pressionada então
				{
					tela = TELA_COMPATIBILIDADE_ELETROMAGNETICA; //Tela é igual a TELA_COMPATIBILIDADE_ELETROMAGNETICA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_NAVEGA_MENU_FUNCOES; //Estado a ser executado é ESTADO_NAVEGA_MENU_FUNCOES
					estadoCompatibilidade = 1; //Coloca a variável estadoCompatibilidade para 1 para ir para o primeiro nivel deste menu
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				break;
			}
			break;
		}
		case 3: //ESCREVE BARGRAPH DE COMPATIBILIDADE NO LCD
		{
			estado = ESTADO_ESCREVE_BARGRAPH; //Estado a ser executado é ESTADO_ESCREVE_BARGRAPH

			switch (teclapressionada) //Conforme tecla pressionada executa o case específico
			{
				case teclaIncrementa: //Caso tecla INCREMENTA ou tecla DECREMENTA ou tecla TRAVA ou tecla DESTRAVA pressionada então
				case teclaDecrementa:
				case teclaTrava:
				case teclaDestrava:
				{
					teclapressionada = 0; //Limpa teclapressionada
					break;
				}
				case teclaConfirma: //Caso tecla CONFIRMA ou tecla CANCELA pressionada então
				case teclaConfirma_Remoto:
				case teclaCancela:
				{
					FTM0_OUTMASK = 0xFFFFFF00; //liga PWM RX
					delay_ms(100); //Espera 100 milisegundos
					tela = TELA_COMPATIBILIDADE_ELETROMAGNETICA; //Tela é igual a TELA_COMPATIBILIDADE_ELETROMAGNETICA
					estado_LCD = ATUALIZA_LCD; //Atualiza o LCD com a tela acima
					estado = ESTADO_NAVEGA_MENU_FUNCOES; //Estado a ser executado é ESTADO_NAVEGA_MENU_FUNCOES
					estadoCompatibilidade = 1; //Coloca a variável estadoCompatibilidade para 1 para ir para o primeiro nivel deste menu
					valor_anterior = 0; //Zera variável valor_anterior
					valor_anterior1 = 0; //Zera variável valor_anterior1
					valor_atual = 0; //Zera variável valor_atual
					valor_atual1 = 0; //Zera variável valor_atual1
					valor_bargraph = 0; //Zera variável valor_bargraph
					valor_bargraph1 = 0; //Zera variável valor_bargraph1
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
/******************************************************************************/


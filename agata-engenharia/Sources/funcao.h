/*
 * funcao.h
 *
 *  Created on: 07/11/2019
 *      Author: Alexandre Voigt da Poian
 */

#ifndef SOURCES_FUNCAO_H_
#define SOURCES_FUNCAO_H_

#include "main.h"
#include "stdint.h"
#include "stddef.h"

#define GRAVA_BLOQUE 'B'
#define GRAVA_DSBLOQ 'D'
#define GRAVA_PAINEL 'P'
#define GRAVA_CONTRO 'C'
#define GRAVA_DETECT 'D'


typedef enum {

	MonitMdTravamento 	= 1		,
	MonitCanal 			= 2		,
	MonitSlMetal 		= 3		,
	MonitSnTrava 		= 4		,
	MonitPlTrava		= 5		,
	MonitSnRele			= 6		,
	MonitPlRele			= 7		,
	MonitCdControle		= 8 	,
	MonitDcControle		= 9 	,
	MonitAnIr			= 10	,
	MonitClIr			= 11	,
	MonitFlRuido		= 12	,
	MonitZrLog			= 13	,
	MonitEndIp			= 14	,
	MonitSubRede		= 15	,
	MonitEndGateway		= 16	,
	MonitPrtWeb			= 17	,
	MonitEndDns			= 18	,
	MonitSnhGerencia	= 19	,
	MonitSnhTecnico		= 20	,
	MonitRstFabrica		= 21	,
	MonitAjData			= 22	,
	MonitTmBuzzer		= 23	,
	MonitVlBuzzer		= 24	,
	MonitVlVoz			= 25	,
	MonitZrDeteccoes	= 26	,
	MonitZrContadores	= 27	,

	MonitSnZonasTodas	= 90	,
	MonitSnZona1		= 91	,
	MonitSnZona2		= 92	,
	MonitSnZona3		= 93	,
	MonitSnZona4		= 94	,
	MonitSnZona5		= 95	,
	MonitSnZona6		= 96	,
	MonitSnZona7		= 97	,
	MonitSnZona8		= 98	,
	MonitAnZona1		= 81	,
	MonitAnZona2		= 82	,
	MonitAnZona3		= 83	,
	MonitAnZona4		= 84	,
	MonitAnZona5		= 85	,
	MonitAnZona6		= 86	,
	MonitAnZona7		= 87	,
	MonitAnZona8		= 88	,
	MonitLowBattery		= 89	,





} paramMonitoramento;

//Para a função de data e hora foi definido as variáveis abaixo
typedef enum {segAjUn,segAjDez,minAjUn,minAjDez,horaAjUn,horaAjDez,diaAjUn,diaAjDez,mesAjUn,mesAjDez,anoAjUn,anoAjDez,data_hora,retorna,fim} estadoAj;

/*************************** Protótipo das Funções ****************************/

/*** Funções do MENU NAVEGA MENU ***/
void Navega_Menu(void); //Serve para entras as senhas da gerência, técnico e engenharia e assim desta forma entrar nos menus de funções
void Navega_Menu_Funcoes(void); //Contém todas as funções de configurações de parâmetros do detector de metais.
/******************************************************************************/

/*** Funções do MENU AJUSTES BÁSICOS ***/
void fnAjustesBasicos(void); //Permite escolher entre as funções abaixo
void fnAjusteManualSensibilidade(void); //Função para entrar valores de sensibilidade de forma manual para as áreas
void fnAjusteAutomaticoSensibilidade(void); //Função para amostrar a sensibilidade de todas as áreas mediante a passagem de uma amostra 3 vezes pela área 1
void fnModoTravamento(void); //Função para escolher entre modo de somente destrava ou modo trava e destrava
void fnQuantidadeSorteados(void); //Função para escolher a quantidade de sorteados entre 10 e 255
void fnSorteadorEletronico(void); //Função para configurar o sorteador eletronico e iniciar
void fnSortearNumero(void); //Função que ira sortear o numero dentre a quantidade máxima de sorteados escolhidos
/******************************************************************************/

/*** Funções do MENU AJUSTES AVANCADOS ***/
void fnAjustesAvancados(void); //Permite escolher entre as funções abaixo
void fnAjusteManualCanal(void); //Permite ajustar o canal de forma manual de 1 a 10
void fnAjusteAutomaticoCanal(void); //Permite encontrar o melhor canal de frequência automaticamente verificando-se o ruido do ambiente
void fnLeAreas(byte canal_de_amostragem); //Função que trabalha em conjunto com o Ajuste Automático de canal lendo as áreas e amostrando para ver qual canal tem menos ruido
void fnSelecaoMetais(void); //Permite escolher a seleção de metais entre 1 e 100, sendo acima de 50 mais metais ferrosos e menos que 50 mais metais não ferrosos
void fnCorrigeSelecao(void); //Corrige a seleção para que o técnico perceba que 100 é com metal ferroso e sem metal não ferroso e para 1 é com metal não ferroso e sem metal ferroso.
void fnTrava(void); //Permite travar o detector
void fnLigaPulsoTrava(void); //Permite pulsar a trava
void fnRele(void); //Permite ligar energizar o relé
void fnLigaPulsoRele(void); //Permite pulsar o relé
void fnControleRemoto(void); //Permite cadastrar e descadastrar no máximo 3 controles remotos
void fnInfravermelho(void); //Permite calibrar os infravermelhos e desativar ou ativar a permissão de detectar mediante passagem pelos infravermelhos no sentido rua-agência
void fnAnulaAreas(void); //Permite anular áreas de detecção que estão com defeito
void fnFiltroRuido(void); //Permite incluir um períoro em que o sinal de detecção deve estar acima do limite para ser reconhecido como detecção, exemplo: 1 = 10ms, 2 = 20ms e assim por diante até 300ms
void fnTravaInteligente(void); //Permite ligar a trava inteligente para que ocorra detecção ao passar pelo sensor infravermelho, para habilitar segura DECREMENTA e CANCELA ao mesmo tempo por 8s até aparecer a mensagem TRAVA INTELIGENTE ATIVADA e para desativar faça o mesmo
void fnSetaPortaAutomatica(void); //Permite ligar o sensor indutivo para destravar a porta automaticamente quando porta automatica estiver escolhida como SIM, ou seja, habilitada.
void fnZerarLogEventos(void); //Permite zerar a memória reservada para o log de eventos
void fnConfiguraInternet(void); //Permite configurar o endereço IP, a máscara de sub-rede, o endereço gateway, o dns e a porta web
void fnEliminarFalhadasBobinas(void); //Permite eliminar a falha das bobinas
void fnOpcaoSensorContador(void); //Permite escolher se o contador funcionará com sensores de entrada e saida de teto ou se funcionará com sensores de entrada e saida frontais
void fnEstadoComandoAT(void); //Permite entrar no modo comandos AT do módulo ethernet
void fnEstadoComandoNormal(void); //Permite entrar no modo NORMAL do módulo ethernet
void fnComandoAT_WANN(void); //Permite fazer a leitura dos endereços de IP, máscara de sub-rede e GATEWAY configurado no módulo ethernet
void fnComandoAT_DNS(void); //Permite fazer a leitura do endereço DNS configurado no módulo ethernet
void fnComandoAT_WEBPORT(void); //Permite fazer a leitura da PORTA WEB para acesso ponto a ponto
void fnComandoAT_SOCK(void); //Permite fazer a leitura do protocolo de rede, endereço IP do servidor remoto, número da porta remota
void fnComandoAT_SOCKPORT(void); //Permite fazer a leitura da PORTA REMOTA para acesso remoto
void fnComandoAT_HTPTP(void); //Permite configurar o método HTTP: GET ou POST
void fnComandoAT_HTPHEAD(void); //Permite configurar o HEADER do HTTP, por padrão fica User_Agent:Mozilla/4.0
void fnPosicionaIP(void); //Reposiciona o endereço IP para que fique no formato completo 000.000.000.000
void fnPosicionaMASK(void); //Reposiciona o endereço máscara de sub-rede para que fique no formato completo 000.000.000.000
void fnPosicionaGATEWAY(void); //Reposiciona o endereço GATEWAY para que fique no formato completo 000.000.000.000
void fnPosicionaDNS(void); //Reposiciona o endereço DNS para que fique no formato completo 000.000.000.000
void fnGravaIPs(void); //Grava os endereços IP, máscara de sub-rede e GATEWAY no módulo ethernet
void fnGravaIPs_PADRAO(void); //Grava os endereços IP, máscara de sub-rede e GATEWAY no módulo ethernet padrões do módulo porque estava em DHCP anteriormente
void fnGravaDNS(void); //Grava o endereço DNS no módulo ethernet
void fnGravaPORT(void); //Grava o endereço da PORTA WEB no módulo ethernet
void fnGravaSOCK(void); //Grava o protocolo de rede utilizado HTPC (HTTP Client mode), o endereço IP do servidor remoto e a porta local
void fnGravaSOCKPORT(void); //Grava a porta local que é sempre 20108
void fnGravaHTPURL(void); //Permite configurar a URL do HTTP, por padrão é /1.php?
void fnGravaHTPHEAD(void); //Permite configurar o header do HTTP
void fnGravaNOME(void); //Grava o nome do módulo
void fnGravaHTTP(void); //Grava método HTTP para POST
void fnResetaModulo(void); //Reseta o módulo para que cada configuração tenha efeito
void fnDigiteIP(void); //Função que permite digitar o IP corretamente dentro do campo IP
void SetaCaracterIP(byte coluna); //Função que vai deslocando o caracter no campo IP
void fnDigitePORT(void); //Função que permite digitar a PORTA WEB corretamente dentro do campo PORTA WEB
void SetaCaracterPORT(byte coluna); //Função que vai deslocando o caracter no campo PORTA WEB
void fnLeEnderecosPontoaPonto(void); //Função que le os endereços do módulo para o ponto a ponto
void fnLeEnderecosAcessoRemotoSTATIC(void); //Função que le os endereços do módulo para o acesso remoto
void fnLeEnderecosAcessoRemotoDHCP(void); //Função que le os endereços do módulo para o acesso remoto
void fnEscolheSTATICouDHCP(void); //Função para escolher entre STATIC e DHCP dentro do menu ACESSO REMOTO
/******************************************************************************/

/*** Funções do MENU AJUSTES DO SISTEMA ***/
void fnAjustesdoSistema(void); //Permite escolher entre as funções abaixo
void fnConfigurarDataHora(void); //Permite escolher entre as funções visualizar ou alterar DATA e HORA
void fnVisualizarDataHora(void); //Permite visualizar a data e a hora do sistema
void fnAlterarDataHora(void); //Permite alterar a data e a hora do sistema
void fnAlteraSenhaGerencia(void); //Permite alterar a senha da gerência
void fnAlteraSenhaTecnico(void); //Permite alterar a senha do técnico
void fnAlteraSenha(void); //Função que realmente altera a senha conforme os dois acima
void fnConfirmaSenha(void); //Função que confirma a senha a ser alterada
void fnResetarPadraoFabrica(void); //Permite resetar todos os parâmetros do detector de metais para os valores padrões de fábrica
void fnConfigurarIdioma(void); //Permite configurar o idioma para português, espanhol ou inglês
/******************************************************************************/

/*** Funções do MENU AJUSTES DE ALARME ***/
void fnAjustesdeAlarme(void); //Permite escolher entre as funções abaixo
void fnConfiguraAlarmeSonoro(void); //Permite configurar o alarme sonoro pelas funções abaixo
void fnConfiguraBuzzer(void); //Permite configurar o buzzer pelas funções abaixo
void fnConfiguraTomBuzzer(void); //Permite configurar o tom do buzzer
void fnConfiguraVolumeBuzzer(void); //Permite configurar o volume do buzzer
void fnConfiguraMsgVoz(void); //Permite configurar a mensagem de voz pelas funções abaixo
void fnConfiguraVolumeMsgVoz(void); //Permite configurar o volume da mensagem de voz
void fnConfiguraLigDesAlarmeVisual(void); //Permite ligar e desligar o alarme visual
/******************************************************************************/

/*** Funções do MENU INFORMAÇÕES DO SISTEMA ***/
void fnInformacoesdoSistema(void); //Permite escolher entre as funções abaixo
void fnContadorDeteccoes(void); //Permite visualizar os bloqueios e desbloqueios pelas funções abaixo
void fnTotalBloqueios(void); //Permite visualizar o total de bloqueios ocorridos por painel, controle remoto ou detecção de metais
void fnTotalDesbloqueios(void); //Permite visualizar o total de desbloqueios ocorridos por painel ou controle remoto
void fnZeraContadorDeteccoes(void); //Permite zerar os contadores de bloqueios e desbloqueios
void fnContadorPassagens(void); //Permite visualizar as entradas e saidas pelas funções abaixo
void fnEntradas(void); //Permite visualizar as entradas
void fnSaidas(void); //Permite visualizar as saidas
void fnEntradasSaidas(void); //Permite visualizar o somatório das entradas e saidas
void fnZeraContadorPassagens(void); //Permite zerar os contadores de entradas e saidas
void fnConfereGravaResetaContadorDiario(void); 	//Faz a conferencia da data e grava e reseta o contador de passagens
void fnGravaContadorEntra(void); //Grava na FLASH o número de entradas
void fnGravaContadorSai(void); //Grava na FLASH o número de saidas
void fnNumeroSeriePainel(void); //Permite visualizar o número de série da placa Agata
void fnNumeroSerieFonte(void); //Permite visualizar o número de série da placa Fonte
/******************************************************************************/

/*** Funções do MENU INFORMAÇÕES DE ENERGIA ***/
void fnInformacoesdeEnergia(void); //Permite visualizar as tensões AC, tensões DC +5V,+15V,-15V,+24V e das tensões da BATERIA
void fnEncaminhaImprimeTelaInformacoesdeEnergia(word telaSwitch, dword *timer_tensoes_aux_ptr); //Recebe a infomacao de qual tela da IHM e imprime na segunda linha a tensao desejada
void fnEscreveTensaoAC(void);	//Escreve a tensao AC na segunda linha da tela LCD
void fnEscreveTensoesDC(void);	//Escreve as tensoes DC - na ordem 5V, 15V, -15V - na segunda linha da tela LCD
void fnEscreveTensaoBateria(void); //Escreve a tensao da bateria na segunda linha da tela LCD
void fnEscreveTensaoFonte(void); //Escreve a tensao da fonte 24v na segunda linha da tela LCD
/******************************************************************************/

/*** Funções do MENU DIAGNÓSTICO DO SISTEMA ***/
void fnDiagnosticodoSistema(void); //Permite testar alguns periféricos do sistema tais como leds, trava, relé, buzzer, etc
void fnTesteLeds(void);	// Executa a rotina de teste de leds para teste
void fnTesteTrava(void);	//Executa o diagnostico teste da trava ate o botao cancelar
void fnTesteRele(void);	//Executa o diagnostico teste do rele ate o botao cancelar
void fnTesteBuzzer(void);	// Executa o diagnostico teste do buzzer ate o botao cancelar
void fnTesteMsgVoz(void);	// Executa o diagnostico teste da mensagem de voz ate o botao cancelar
//TODO Remove
void fnTesteMsgVoz1(void);
void fnTesteMsgVoz2(void);
void fnTesteMsgVoz3(void);
//TODO Till here
void fnTesteTeclado(void);  // Executa o diagnostico teste do teclado (exceto cancelar) ate o botao cancelar
void fnTesteInfravermelho(void);	// Executa o diagnostico teste do infravermelho ate o botao cancelar
void fnTesteAutonomiaBateria(void);	//Aciona todas as saídas (LEDs e Solenoide) por 5 segundos, desativa-as por 55 segundos
void fnTesteSinalRxA1A2(void);
void fnTesteSinalRxA2A3_Z3(void);
void fnTesteSinalRxA3A4(void);
void fnTesteSinalRxA5A6(void);
void fnTesteSinalRxA7A8(void);
/******************************************************************************/

/*** Funções do MENU BARGRAPH ***/
void fnBargraph(void); //Permite visualizar os ruidos mecânicos e eletromagnéticos estando a antena TX emitindo e a RX recebendo sinais da TX
void fnEscreveBargraph(void); //Serve tanto para BARGRAPH como COMPATIBILIDADE ELETROMAGNÉTICA, escreve os asteriscos conforme o nível do ruido
/******************************************************************************/

/*** Funções do MENU COMPATIBILIDADE ELETROMAGNÉTICA ***/
void fnCompatibilidadeEletromagnetica(void); //Permite visualizar os ruidos eletromagnéticos estando somente a antena RX recebendo sinais do meio ambiente
/******************************************************************************/

/*** Funções do MENU AJUSTES TX-RX ***/
void fnAjustesTXRX(void); //Permite escolher entre as funções abaixo
void fnCicloTrabalho(void); //Permite alterar o ciclo de trabalho do PWM da TX de 1% a 100%
void fnDefasagem(void); //Permite alterar a defasagem para pegar mais metais ferrosos ou mais metais não ferrosos ou ambos
void fnFrequencia(void); //Permite alterar a frequência do PWM da TX
/******************************************************************************/

/*** Funções AJUSTES DE ENGENHARIA ***/
void fnModelodeAntena(void); //Permite escolher o modelo de antena a ser utilizado
void fnPotenciometrodeGanho(void); //Permite ajustar o ganho de sinal das áreas 1 a área 8
void fnPotenciometrodeSelecaodeMetais(void); //Permite ajustar a seleção de metais da área 1 a área 8
void fnTipoDetector(void); //Permite escolher o tipo de detector se 3Z ou 8Z
/******************************************************************************/

/*** Funções do AD ***/
void fnLeAreasDeteccao(void); //Faz a leitura do sinal AD das áreas sem amostrar por um tempo
void fnLeAreasDeteccaocomVelocidade(void); //Faz a leitura do sinal AD das áreas amostrando por um tempo de 10ms a 300ms conforme valor do filtro (1 x 10ms = 10ms)
/******************************************************************************/

/*** Funções AES-128 ***/
static void phex(uint8_t* str); //Imprime a string como hex
static int test_encrypt_cbc(void);
static int test_decrypt_cbc(void);
static int test_encrypt_ctr(void);
static int test_decrypt_ctr(void);
static int test_encrypt_ecb(void);
static int test_decrypt_ecb(void);
static void test_encrypt_ecb_verbose(void);
/***********************/

/*** Funções do BARGRAPH ***/
void AcendeBargraph(void); //Acende corretamente o bargraph conforme o nível de sinal recebido, sempre pegando a área que esta recebendo mais sinal
/******************************************************************************/

/*** Funções do BUZZER ***/
void Nota_Musical(word nota); //Define a nota músical
void SetTomBuzzer (word tom); //Seta o tom do buzzer
void TocaTomBuzzer(void); //Toca sonoramente a nota músical e o tom definido
void tone(word tom,word delay_); //Função que toca a nota músical correta para a função toca_star
/******************************************************************************/

/*** Funções da CAN ***/
void fnCarregaVersoes(void); //Carrega as versões dos periféricos conectados a rede CAN
void fnGetAlives(void); //Verifica quem esta presente na rede CAN e sinaliza através de um vetor de flag
void LePresencas(void); //Lê as presença dos periféricos conectados a CAN
void SendCan(LDD_CAN_TMessageID dst_ID, byte mensagem); //Envia informações pela CAN informando o destino (FONTE = endereço) e a mensagem
void TrataCAN(void); //Trata as informações recebidas pela CAN
void abortTxCAN(void);	//Aborta envio da mensagem pela CAN
/******************************************************************************/

/*** Função CHECKSUM ***/
void fnChecksum(byte numero_de_bytes); //Faz o checksum de todos os dados
/******************************************************************************/

/*** Funções do CONTROLE REMOTO ***/
void VALIDA_CODIGO(void); //Função que permite cadastrar os controles remotos e apagar todos os controles remotos
void configAnaliseControle(void); //Configuração para permitir analise de qual controle remoto foi utilizado
void defineTipoControle(void);
void validaControle(void);
/******************************************************************************/

/***Funções de DELAY ***/
void delay_ms(word cont); //Função que faz um delay de tempo em milisegundos
void delay_segundos(word cont); //Função que faz um delay de tempo em segundos
/******************************************************************************/

/*** Funções do GRAVADOR DE VOZ ***/
void fnDiminuiTodoVolume(void); //Função que diminui todo o volume da mensagem de voz
void fnDiminuiVolume(byte diminuir); //Função que diminui o volume da mensagem de voz
void fnAumentaVolume(byte aumentar); //Função que aumenta o volume da mensagem de voz
void fnCortaMsgVoz(void); //Função que corta a mensagem de voz
void fnReproduzMsgVoz(char origin); //Função que reproduz a mensagem de voz
/******************************************************************************/

/*** Funções dos INFRAVERMELHOS ***/
void fnLeInfras(void); //Função que lê o estado dos infravermelhos para poder fazer a contagem de pessoas que entram e saem
void fnLeInfrasTeto(void); //Função que lê o estado dos infravermelhos do teto para poder fazer a contagem de pessoas que entram e saem
void fnContadorPassagem(void); //Função que trata os estados lidos pela função anterior
/******************************************************************************/

/*** Funções dos LOGS de AUDITORIAS ***/
//parametro: Conforme tabela indica se 91 por exemplo é sensibilidade da área 1
//valor_velho: Valor que tinha anteriormente
//valor_novo: Valor que foi inserido atualmente
//operador: T para técnico ou G para gerente
//dispositivo: P para painel ou C para controle ou S para software
void fnGravaAuditoria(byte parametro, byte valor_velho, byte valor_novo, char operador,char dispositivo);
void fnLeRegistroAuditorias(void);
void fnLeEnderecoFlagAuditorias(dword endereco_auditoria_lido); //Aqui você diz qual o endereço de auditoria lido
/******************************************************************************/

/*** Funções dos LOGS de EVENTOS DE BLOQUEIOS e DESBLOQUEIOS ***/
//evento: B para bloqueio ou D para desbloqueio
//dispositivo: P para painel ou C para controle ou D para detecção
void fnGravaEvento(char evento,char dispositivo); //Função que grava os eventos de bloqueios e desbloqueios realizados por painel, controle remoto ou detecção de metais
void fnLeRegistroEventos(void);
void fnLeEnderecoFlagEventos(dword endereco_evento_lido); //Aqui você diz qual o endereço do endereço de evento lido
/******************************************************************************/

/*** Funções da MEMÓRIA FLASH ***/
void GravaPadroesFabrica(void); //Função que grava os parâmetros padrões de fábrica
void LeParametrosDetector(void); //Função que carrega os parâmetros e decide se vai gravar padrões de fábrica ou se vai somente ler os parâmetros do detector de metais
void fnCarregaParametros(void); //Função que lê os parâmetros alterados e já gravados no detector de metais
void fnEscreveNoEndereco(dword endereco, word numero_dados);
void LE_FLASH_INTERNA(dword endereco,word numero_dados); //Função que lê os dados da memória FLASH
void ESCREVE_FLASH_INTERNA(dword endereco,word numero_dados,byte block_number); //Função que escreve os dados na memória FLASH
void ZeraReadWriteBufferFLASH(void);
/******************************************************************************/

/*** Funções do MÓDULO ETHERNET ***/
int fnChecaMensagemRecebida(char *mensagem_recebida, int tipo_mensagem); //Função para conferência se é uma mensagem válida
void fnRotinaResetarInterfaceSerial(int modoResetar);
int agataKeyGenerator(uint8_t *serialNo, size_t serialNoSize, uint8_t *generatedKey, size_t generatedKeySize);
void EnviaPacoteDados(void); //Função que envia os parâmetros do detector para o módulo ehternet-serial
/******************************************************************************/

/*** Funções do NÚMERO DE SÉRIE ***/
void fnGravaNumSerie(void);
/******************************************************************************/

/*** Funções dos POTENCIÔMETROS DIGITAIS ***/
void fnEnviaSPI(byte pot_dig, byte sel_area,byte valorad); //Permite enviar a configuração para alterar os potenciômetros digitais
/******************************************************************************/

/*** Funções do PWM TX e PWM RX ***/
void fnAtualizaPerfil(byte seta_parametros, byte seta_pwm, byte grava_flash, byte set_pot_ganhos); //Atualiza informações de sinal, defasagem, frequência e ganho conforme perfil escolhido
void SetDutyCycle_TX(byte duty); //Função que ajusta o ciclo de trabalho do PWM da TX
void SetDutyCycle_RX(void); //Função que ajusta o ciclo de trabalho dos sinais RX1 e RX2
void SetDefasagem(word def); //Função que altera a defasagem do sinal
void SetFrequencia(dword freq); //Função que altera a frequência do sinal
void InitPwm(void); //Função que inicializa todos PWMs
/******************************************************************************/

/*** Funções da SENHA ***/
void fnDigiteSenha(void); //Função que permite digitar a senha corretamente dentro do campo senha
void SetaCaracterSenha(byte coluna); //Função que vai deslocando o caracter no campo senha
void fnMascaraNumeroSerie(void); //Função que faz a máscara do número de série gravado com um valor numérico e cria um novo número para senha mestre
/******************************************************************************/

/*** Funcções das TECLAS ***/
void fnLerTeclas(void); //Função que lê as teclas do painel e controle remoto
/******************************************************************************/

/*** Funções da TRAVA ***/
void fnTravaDetector(void); //Função que trava a porta giratória
void fnDestravaDetector(void); //Função que destrava a porta giratória
/******************************************************************************/

/*** Funções da USB-SERIAL ***/
void TrataSerial(void); //Função que recebe os dados seriais do PC e toma as devidas ações
extern volatile word qtdnl;
/******************************************************************************/

/*** Funções da ETHERNET-SERIAL PACOTES ***/
void TrataSerial2(void);
/******************************************************************************/

#endif /* SOURCES_FUNCAO_H_ */

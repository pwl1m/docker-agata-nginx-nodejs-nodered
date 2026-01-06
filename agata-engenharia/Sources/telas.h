/*
 * telas.h
 *
 *  Created on: 05/04/2019
 *      Author: Samsung
 */

#ifndef SOURCES_TELAS_H_
#define SOURCES_TELAS_H_

/*************************** Protótipo das Funções ****************************/
void Atualiza_LCD(void);
/******************************************************************************/

/*********************** Definições das TELAS_INICIAIS ************************/
#define TELA_INICIAL													0
#define	TELA_INICIAL1													2
#define	TELA_AGUARDE													4
#define	TELA_SENHA_DA_GERENCIA											5
#define TELA_SENHA_DO_TECNICO											6
#define	TELA_SENHA_DA_ENGENHARIA										7
#define TELA_SENHA_INCORRETA											8
/******************************************************************************/

/****************** 1 - Definições das TELAS AJUSTES BÁSICOS ******************/
#define TELA_AJUSTES_BASICOS											10
#define TELA_AJUSTE_MANUAL_DE_SENSIBILIDADE								12
#define	TELA_TODAS_AS_AREAS												14
#define TELA_AREA_1														15
#define TELA_AREA_2														16
#define TELA_AREA_3														17
#define TELA_AREA_4														18
#define TELA_AREA_5														19
#define TELA_AREA_6														20
#define TELA_AREA_7														21
#define TELA_AREA_8														22
#define TELA_AJUSTE_AUTOMATICO_DA_SENSIBILIDADE							23
#define TELA_PASSAR_OBJETO_NA									25
#define	TELA_PASSE_AMOSTRA												27
#define TELA_MODO_DE_TRAVAMENTO	        								28
#define TELA_SOMENTE_DESTRAVA											30
#define TELA_TRAVA_DESTRAVA												31
/******************************************************************************/

/***************** 2 - Definições das TELAS AJUSTES AVANÇADOS *****************/
#define	TELA_AJUSTES_AVANCADOS											32
#define TELA_AJUSTE_MANUAL_DE_CANAL										34
#define TELA_CANAL														36
#define TELA_AJUSTE_AUTOMATICO_DE_CANAL									38
#define TELA_SINTONIZANDO												40
#define TELA_MELHOR_CANAL												42
#define TELA_SELECAO_DE_METAIS											44
#define TELA_TRAVA														46
#define TELA_RELE														48
#define TELA_PULSO														50
#define TELA_RETENCAO_CONTROLE											52
#define TELA_RETENCAO_CONTROLE_TECLADO									54
#define TELA_CONTROLE_REMOTO											56
#define TELA_CADASTRAR_CONTROLES										58
#define TELA_DESCADASTRAR_CONTROLES										60
#define TELA_PRESSIONE_QUALQUER_TECLA_DO_CONTROLE						62
#define TELA_ERRO_CONTROLE_NAO_CADASTRADO								64
#define TELA_CONTROLE_JA_CADASTRADO										66
#define TELA_ADICIONADO_COM_SUCESSO										68
#define TELA_DESCADASTRO_COM_SUCESSO									70
#define TELA_INFRAVERMELHO												72
#define TELA_CALIBRAR_IR												73
#define TELA_CALIBRANDO													74
#define TELA_CALIBRADO_COM												75
#define TELA_ANALISE_IR													76
/******************************************************************************/

/**************** 3 - Definições das TELAS AJUSTES DO SISTEMA *****************/
#define TELA_AJUSTES_DO_SISTEMA											77
#define TELA_DATA_E_HORA												79
#define TELA_VISUALIZAR													81
#define TELA_ALTERAR													83
#define TELA_ALTERA_SENHA_DA_GERENCIA									85
#define TELA_ALTERA_SENHA_DO_TECNICO									87
#define TELA_CONFIRMAR_SENHA											89
#define TELA_RESETAR_PADROES_DE_FABRICA									91
#define TELA_VOCE_TEM_CERTEZA											93
#define TELA_NAO_SIM													94
#define TELA_IDIOMA														95
/******************************************************************************/

/**************** 4 - Definições das TELAS AJUSTES DE ALARME ******************/
#define TELA_AJUSTES_DE_ALARME											97
#define TELA_ALARME_SONORO												99
#define TELA_BUZZER														101
#define TELA_TOM_DO_BUZZER												102
#define TELA_VOLUME_DO_BUZZER											103
#define TELA_LIGAR_DESLIGAR												104
#define TELA_MENSAGEM_DE_VOZ											105
#define TELA_VOLUME_DA_MENSAGEM											106
#define TELA_ALARME_VISUAL												108
/******************************************************************************/

/************** 5 - Definições das TELAS INFORMAÇÕES DO SISTEMA ***************/
#define TELA_INFORMACOES_DO_SISTEMA										111
#define TELA_CONTADOR_DE_DETECCOES										113
#define TELA_TOTAL_BLOQUEIOS										    115
#define TELA_TOTAL_DESBLOQUEIOS											116
#define TELA_CONTADOR_DE_PASSAGENS										117
#define TELA_ENTRADAS													119
#define TELA_SAIDAS														120
#define TELA_ENTRADAS_SAIDAS											121
#define	TELA_ZERAR_CONTADORES											122
#define TELA_NUMERO_DE_SERIE											123
/******************************************************************************/

/************** 6 - Definições das TELAS INFORMAÇÕES DE ENERGIA ***************/
#define TELA_INFORMACOES_DE_ENERGIA										124
#define TELA_TENSAO_AC													126
#define TELA_TENSAO_DC													127
#define TELA_TENSAO_DAS_BATERIAS										128
/******************************************************************************/

/************** 7 - Definições das TELAS DIAGNÓSTICO DO SISTEMA ***************/
#define TELA_DIAGNOSTICO_DO_SISTEMA										129
#define TELA_TESTE_DE_LEDS												131
#define TELA_TESTE_DA_TRAVA												133
#define TELA_TESTE_RELE													135
#define TELA_TESTE_BUZZER												137
#define TELA_TESTE_MSG_VOZ												139
//TODO Remove below
#define TELA_TESTE_MSG_VOZ1												329
#define TELA_TESTE_MSG_VOZ2												331
#define TELA_TESTE_MSG_VOZ3												333
//TODO till here
#define TELA_TESTE_INFRAVERMELHO										141
#define TELA_INFRA1_OFF_E_INFRA2_OFF									143
#define TELA_INFRA1_ON_E_INFRA2_ON										145
#define TELA_TENSAO_SINAL_RX											147
#define TELA_SINAL_A1_A2												149
#define TELA_SINAL_A3_A4												151
#define TELA_SINAL_A5_A6												153
#define TELA_SINAL_A7_A8												155
/******************************************************************************/

/****************** 8 - Definições das TELAS AJUSTES TX-RX ********************/
#define TELA_AJUSTES_TX_RX												157
#define TELA_CICLO_DE_TRABALHO											159
#define TELA_DEFASAGEM													160
#define TELA_FREQUENCIA													161
/******************************************************************************/

/***************** 9 - Definições das TELAS MODELO DE ANTENA ******************/
#define TELA_MODELO_DE_ANTENA											162
/******************************************************************************/

/************* 10 - Definições das TELAS POTENCIÔMETRO DE GANHO ***************/
#define TELA_POTENCIOMETRO_DE_GANHO										164
/******************************************************************************/

/******** 11 - Definições das TELAS POTENCIÔMETRO DE SELEÇÃO DE METAIS ********/
#define TELA_POTENCIOMETRO_DE_SELECAO_DE_METAIS							166
/******************************************************************************/

/********************* Definições das TELAS DE USO GERAL **********************/
#define TELA_SEIS_SUBSCRITOS											168
#define TELA_LINHA_EM_BRANCO											169
#define TELA_UM															170
#define TELA_CEM														171
#define TELA_CENTO_E_VINTE_E_SETE										172
#define TELA_SEM_SINAL_NAS_ANTENAS					                    173
#define TELA_ERRO_DE_COMUNICACAO										175
#define TELA_CARGA_DA_BATERIA											177
#define TELA_CARREGANDO													178
#define TELA_MEMORIA_FLASH_COM_DEFEITO									179
#define TELA_GRAVANDO_PADROES_DE_FABRICA								181
#define TELA_LENDO_PADROES_GRAVADOS										183
#define TELA_ERRO_NO_INFRA1												185
#define TELA_ERRO_NO_INFRA2												186
#define TELA_INFRA1_DETECTADO											187
#define TELA_INFRA2_DETECTADO											188
#define TELA_RETENCAO													189
#define TELA_APAGANDO													190
#define TELA_ALTERA_SENHA												191
#define TELA_PLANA_ONIX_2000											193
#define TELA_PLANA_ONIX_2100											194
#define TELA_PLANA_ONIX_440												195
#define TELA_CILINDRICA_IECO_2000										196
#define TELA_CILINDRICA_IECO_2100										197
#define TELA_TECLADO													198
#define TELA_AREA_1_E_2													199
#define TELA_AREA_3_E_4													200
#define TELA_AREA_5_E_6													201
#define TELA_AREA_7_E_8													202
#define TELA_ERRO_COMUNICACAO											203
#define TELA_CONFIRMA													205
#define TELA_INCREMENTA													206
#define TELA_DECREMENTA													207
#define TELA_ANULA_AREA_1												208
#define TELA_ANULA_AREA_2												209
#define TELA_ANULA_AREA_3												210
#define TELA_ANULA_AREA_4												211
#define TELA_ANULA_AREA_5												212
#define TELA_ANULA_AREA_6												213
#define TELA_ANULA_AREA_7												214
#define TELA_ANULA_AREA_8												215
#define TELA_ANULA_AREAS												216
#define TELA_FILTRO_DE_RUIDO											217
#define TELA_COMPATIBILIDADE_ELETROMAGNETICA_RX_A1_A2					218
#define TELA_COMPATIBILIDADE_ELETROMAGNETICA_RX_A3_A4					220
#define TELA_COMPATIBILIDADE_ELETROMAGNETICA_RX_A5_A6					222
#define TELA_COMPATIBILIDADE_ELETROMAGNETICA_RX_A7_A8					224
#define TELA_A1_A2														226
#define TELA_A3_A4														228
#define TELA_A5_A6														230
#define TELA_A7_A8														232
#define TELA_BARGRAPH													234
#define TELA_AREA1E2													235
#define TELA_AREA3E4													236
#define TELA_AREA5E6													237
#define TELA_AREA7E8													238
#define TELA_COMPATIBILIDADE_ELETROMAGNETICA							239
#define TELA_A1_A2_COMPATIBILIDADE										241
#define TELA_A3_A4_COMPATIBILIDADE										243
#define TELA_A5_A6_COMPATIBILIDADE										245
#define TELA_A7_A8_COMPATIBILIDADE										247
#define TELA_TRAVA_INTELIGENTE											249
#define TELA_TRAVA_INTELIGENTE_ATIVADA									251
#define TELA_CONTROLES_NAO_APAGADOS										254
#define TELA_PRESSIONE_NOVAMENTE_PARA_CONFIRMAR							256
#define TELA_NUMERO_MAXIMO_CONTROLES									258
#define TELA_DETECTOR_METAIS											260
#define TELA_FONTE_ALIMENTACAO											261
#define TELA_ZERAR_LOG_EVENTOS											262
#define TELA_IP_SUBSCRITOS												263
#define TELA_ENDERECO_IP												264
#define TELA_MASCARA_SUB_REDE											265
#define TELA_ENDERECO_GATEWAY											266
#define TELA_PORTA_WEB													267
#define TELA_CONFIGURACOES_DE_INTERNET									268
#define TELA_ENDERECO_DNS												270
#define TELA_TIPO_DETECTOR												271
#define TELA_3_AREAS													272
#define TELA_8_AREAS													273
#define TELA_INICIAL_3Z													274
#define TELA_AREA2E3													275
#define TELA_A2_A3														276
#define TELA_COMPATIBILIDADE_ELETROMAGNETICA_RX_A2_A3					278
#define TELA_A2_A3_COMPATIBILIDADE										279
#define TELA_AREA_2_E_3													282
#define TELA_SINAL_A2_A3												283
#define TELA_ELIMINAR_FALHA_DAS_BOBINAS									285
#define TELA_TENSAO_24V													287
#define TELA_TESTE_AUTONOMIA_DA_BATERIA									288
#define TELA_DESLIGANDO_FONTE											290
#define TELA_MODO_PONTO_A_PONTO											292
#define TELA_MODO_ACESSO_REMOTO											294
#define TELA_EM_MANUTENCAO												296
#define TELA_NUMERO_SERIE												298
#define TELA_GRAVAR_NUM_SERIE											299
#define TELA_STATIC														301
#define TELA_DHCP														303
#define TELA_CONFIRMA_INICIAR											305
#define TELA_ERRO_AUTOCALIBRACAO										307
#define TELA_PORTA_AUTOMATICA											309
#define TELA_OPCAO_DE_CONTADOR											310
#define TELA_SENSOR_FRONTAL												311
#define TELA_SENSOR_TETO												312
#define TELA_IECO_GT													313
#define TELA_VALOR_INVALIDO_EXE_BACKUP									314
#define TELA_MEMORIA_CORROMPIDA_CONTATE									316
#define TELA_MEMORIA_CORROMPIDA_DESLIGUE								318
#define TELA_SORTEADOR_ELETRONICO										320
#define TELA_INICIAR_SORTEADOR											322
#define TELA_QUANTIDADE_SORTEADOS										323
#define TELA_PORTAL_750_BLINDADO										324
//#define TELA_TROCAR_SENHA_GERENTE										325
//#define TELA_TROCAR_SENHA_TECNICO										326
#define TELA_TIPO_CONTROLE												327
#define TELA_TIPO_A_B													328

/******************************************************************************/

/******************* Outras definições das TELAS INICIAIS *********************/
#define TELA_DIGITE_SENHA_DA_GERENCIA									1000
#define TELA_DIGITE_SENHA_DO_TECNICO									1001
#define TELA_DIGITE_SENHA_DA_ENGENHARIA									1002
/******************************************************************************/

/**************** Outras definições das TELAS AJUSTES BÁSICOS *****************/
#define TELA_MOSTRA_AJUSTES_BASICOS										1100
#define TELA_MOSTRA_SENSIBILIDADE_DAS_AREAS								1101
#define TELA_DIGITE_SENSIBILIDADE_DAS_AREAS								1102
#define TELA_MOSTRA_MODO_DE_TRAVAMENTO                                  1103
#define TELA_MOSTRA_QUANTIDADE_SORTEADOS								1104
/******************************************************************************/

/*************** Outras definições das TELAS AJUSTES AVANÇADOS ****************/
#define TELA_MOSTRA_AJUSTES_AVANCADOS									1200
#define TELA_DIGITE_CANAL												1201
#define TELA_MOSTRA_SELECAO_METAIS										1202
#define TELA_DIGITE_PULSO_TRAVA											1203
#define TELA_MOSTRA_TRAVA												1204
#define TELA_MOSTRA_RELE												1205
#define TELA_DIGITE_PULSO_RELE											1206
#define TELA_MOSTRA_CONTROLE_REMOTO										1207
#define TELA_MOSTRA_INFRAVERMELHO										1208
#define TELA_SETA_CALIBRAR_IR											1209
#define TELA_MOSTRA_CALIBRANDO											1210
#define TELA_MOSTRA_VALOR_CALIBRADO										1211
#define TELA_SETA_ANALISE_IR											1212
#define TELA_MOSTRA_ERRO_NOS_INFRAS										1213
#define TELA_MOSTRA_ANULA_AREA											1214
#define TELA_SETA_ANULAR_AREA											1215
#define TELA_SETA_TRAVA_INTELIGENTE										1216
#define TELA_TRAVA_INTELIGENTE_DESATIVADA								1217
#define TELA_MOSTRA_CONFIGURACOES_DA_INTERNET							1218
#define TELA_SETA_ELIMINAR_FALHA_DAS_BOBINAS							1219
#define TELA_MOSTRA_CONFIGURACOES_MODO_REDE								1220
#define TELA_SETA_PORTA_AUTOMATICA										1221
#define TELA_MOSTRA_OPCAO_SENSOR_CONTADOR								1222
/******************************************************************************/

/************** Outras definições das TELAS AJUSTES DO SISTEMA ****************/
#define TELA_MOSTRA_AJUSTES_DO_SISTEMA									1300
#define TELA_MOSTRA_OPCOES_DATA_E_HORA									1301
#define TELA_DIGITE_NOVA_SENHA											1302
#define TELA_MOSTRA_IDIOMA												1303
#define TELA_VISUALIZAR_DATA_E_HORA										1304
/******************************************************************************/

/*************** Outras definições das TELAS AJUSTES DE ALARME ****************/
#define TELA_MOSTRA_AJUSTES_DE_ALARME									1400
#define TELA_MOSTRA_ALARME_SONORO										1401
#define TELA_MOSTRA_BUZZER												1402
#define TELA_MOSTRA_TOM_DO_BUZZER										1403
#define TELA_MOSTRA_VOLUME_DO_BUZZER									1404
#define TELA_MOSTRA_MSG_VOZ												1405
#define TELA_MOSTRA_VOLUME_MSG_VOZ										1406
#define TELA_SETA_ALARME_VISUAL_LIGAR_DESLIGAR							1407
/******************************************************************************/

/************ Outras definições das TELAS INFORMAÇÕES DO SISTEMA **************/
#define TELA_MOSTRA_INFORMACOES_DO_SISTEMA								1500
#define TELA_MOSTRA_CONTADOR_DE_DETECCOES								1501
#define TELA_MOSTRA_CONTADOR_DE_PASSAGENS								1502
#define TELA_SETA_ZERAR_DETECCOES										1503
#define TELA_SETA_ZERAR_PASSAGENS										1504
#define TELA_MOSTRA_NUMERO_DE_SERIE_PAINEL								1505
#define TELA_MOSTRA_NUMERO_DE_SERIE_FONTE								1506
#define TELA_SETA_ZERAR_LOG_EVENTOS										1507
/******************************************************************************/

/************ Outras definições das TELAS INFORMAÇÕES DE ENERGIA **************/
#define TELA_MOSTRA_INFORMACOES_DE_ENERGIA								1600
/******************************************************************************/

/************ Outras definições das TELAS DIAGNOSTICO DO SISTEMA **************/
#define TELA_MOSTRA_DIAGNOSTICO_SISTEMA  				    			1700
/******************************************************************************/

/***************** Outras definições das TELAS AJUSTES TX-RX ******************/
#define TELA_MOSTRA_AJUSTES_TX_RX										1800
#define TELA_DIGITE_CICLO_DE_TRABALHO									1801
#define TELA_DIGITE_DEFASAGEM											1802
#define TELA_DIGITE_FREQUENCIA											1803
#define TELA_MOSTRA_MODELO_DE_ANTENA									1804
#define TELA_MOSTRA_POTENCIOMETRO_DE_GANHO								1805
#define TELA_DIGITE_POTENCIOMETRO_DE_GANHO								1806
#define TELA_MOSTRA_POTENCIOMETRO_DE_SELECAO_DE_METAIS					1807
#define TELA_DIGITE_POTENCIOMETRO_DE_SELECAO_DE_METAIS					1808
#define TELA_MOSTRA_TIPO_DETECTOR										1809
/******************************************************************************/

/****************** Outras definições das TELAS DE USO GERAL ******************/
#define TELA_ATUALIZAR_DH												1900
#define TELA_DIGITE_FILTRO_DE_RUIDO										1901
#define TELA_MOSTRA_BARGRAPH											1902
#define TELA_MOSTRA_COMPATIBILIDADE										1903
#define TELA_DIGITE_NUMERO_SERIE										1904
#define TELA_MOSTRA_STATIC_DHCP											1905
/******************************************************************************/

extern volatile char telas_LCD [][3][16];

#endif /* SOURCES_TELAS_H_ */

/*
 * agata_hc_definitions.h
 *
 *  Created on: 22/06/2023
 *      Author: marcos.butignol
 *
 *
 *  220623 - agata_hc_definitions.h criado para definir os modos e valores usados pelo
 *  			Agata sendo testado
 */

#ifndef SOURCES_AGATA_HC_DEFINITIONS_H_
#define SOURCES_AGATA_HC_DEFINITIONS_H_

#define FORCAR_TESTE_ENVIO_EVENTO_SIMTRO		FALSE
#define	FORCAR_TESTE_ENVIO_AUDITO_SIMTRO		FALSE

#define	FORCAR_NAO_CONFIRMAR_RECEBIMENTO_SIMTRO	FALSE

#define RECEBIMENTO_ETHERNET_EM_TRATASERIAL2	FALSE
#define TESTAR_RECEBIMENTO_CONFIG1 				FALSE

#define FLAG_PLACA_OUT_2022						FALSE

#define MODO_ENVIO_JSON_SIMTRO					TRUE
#define MODO_CRIPTOGRAFIA_ECB_SIMTRO			TRUE		//NECESSARIO MODO ACIMA SER TRUE

#define MODO_RECEBIMENTO_BASE64_SIMTRO			TRUE

#define FORCE_SERIAL_VALUE						FALSE
#define SERIAL_VALUE_TOFORCE					"PRT003"	//NECESSARIO MODO ACIMA SER TRUE

#define FORCE_AUDIT_VALUE						TRUE
#define TESTE_CORRUPCAO_MEMORIA					FALSE



//Valores alteraveis/ padroes de fabrica
#define	PACOTE_ENVIA_INICIO_CODIGO			"#ae"
#define PACOTE_ENVIA_SERIAL_CODIGO_UNICO 	"PRT003"

#define SENHA_GERENCIA						"100000"
#define SENHA_TECNICO						"200000"

#define IP_PADRAO_FABRICA					"192.168.010.098"
#define MASCARA_PADRAO_FABRICA				"255.255.255.000"
#define GATEWAY_PADRAO_FABRICA				"192.168.010.001"
#define DNS_PADRAO_FABRICA					"192.168.010.003"

#define ATHTPURL_END						"/simtro/communication/pgdm.php"

//Valores anteriores
//str3 = "192.168.000.007"
//str3 = "255.255.255.000"
//str3 = "192.168.000.001"
//str3 = "208.067.222.222";

//Valores definitivos

#define STRING_OK_HTTP  					"\"code\":200"
#define STRING_CONFIG_HTTP					"config\":"
#define STRING_DATA_START_HTTP				"data\":\""
#define STRING_DATA_ALTERACAO_HTTP			"alteracao\":["
#define STRING_DATA_COMANDO_HTTP			"comando\":["
#define STRING_DATA_SEPARATOR_HTTP			","
#define STRING_TERMINATOR_HTTP				"\"}"
#define STRING_TERMINATOR_COMANDO			"}"

#define numParametros						186

#define INTERVALO_BUZZER					15

/*
 const char *string_ok_http 	= "\"code\":200";	// "\"code\":200"
 const char *string_config_http = "config\":";
 const char *string_json_start = "data\":\"";
 const char *string_json_separator = ";";
 const char *string_json_terminator = "\"}";
 */

typedef enum {
	DadoSnZona1 = 6001,
	DadoSnZona2 = 6002,
	DadoSnZona3 = 6003,
	DadoSnZona4 = 6004,
	DadoSnZona5 = 6005,
	DadoSnZona6 = 6006,
	DadoSnZona7 = 6007,
	DadoSnZona8 = 6008,
	DadoAnZona1 = 6009,
	DadoAnZona2 = 6010,
	DadoAnZona3 = 6011,
	DadoAnZona4 = 6012,
	DadoAnZona5 = 6013,
	DadoAnZona6 = 6014,
	DadoAnZona7 = 6015,
	DadoAnZona8 = 6016,
	DadoCanal = 6017,
	DadoFlRuido = 6018,
	DadoSnRele = 6019,
	DadoPlRele = 6020,
	DadoSnTrava = 6021,
	DadoPlTrava = 6022,
	DadoMdTravamento = 6023,
	DadoSlMetal = 6024,
	DadoVlVoz = 6025,
	DadoVlBuzzer = 6026,
	DadoTmBuzzer = 6027,
	DadoTsAgata = 6028,
	DadoSwUser = 6029,

	DadoTimestampSimtro = 6200,

	DadoSnZonaDefault = 6100,
	DadoAnZonaDefault = 6101

} DadoAlteracaoSimtro;

typedef enum {
	MensagemRemSimtroDefaultCheck = 1001,
	MensagemRemSimtroSizeCheck = 1002,
	MensagemRemSimtroCodeCheck = 1003,
	MensagemRemSimtroTermCheck = 1004,
	MensagemRemSimtroValidCharCheck = 1005,

	MensagemSrlUsb = 2002,
	MensagemPntPonto = 3003

} TipoMensagemRecebida;

typedef enum {

	ModoResetaFullInterface = 1051,

} TipoModosGenericos;

#endif /* SOURCES_AGATA_HC_DEFINITIONS_H_ */

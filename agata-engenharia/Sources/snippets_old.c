/*
 * snippets_old.c
 *
 *  Created on: 22/06/2023
 *      Author: marcos.butignol
 */

/*
 * TRATASERIAL()


 *
 *
 */

/*
 * --RECEBESERIAL2
 *
if(recebe_serial[8] == '2' && recebe_serial[9] == '0' && recebe_serial[10] == '0' && recebe_serial[21] == '1') //Config1 serve para alterar parâmetros na placa e zerar as flags eventolido e auditorialido nos endereços correspondentes dos logs enviados
	{
		do
		{
			contador = 0;
			volatile_memset(str, 0, sizeof(str));

			while(recebe_serial[indexador] != ';' && recebe_serial[indexador] != '"')
			{
				str[contador] = (char)(recebe_serial[indexador]);
				contador++;
				indexador++;

			}
			aux_recebe_serial[y] = (char)(atoi(str));

			indexador++;
			y++;
		}while(recebe_serial[indexador - 1] != '"' && recebe_serial[indexador] != '}');

		//SENSIBILIDADE
		for(x = 0;x < 8;x++) //Armazena a sensibilidade da área 1 a área 8
		{
			if(buffer_sensibilidade[x + 1] != aux_recebe_serial[x])
			{
				fnGravaAuditoria((91 + x),buffer_sensibilidade[x + 1],aux_recebe_serial[x],'G','S');
			}
			buffer_sensibilidade[x + 1] = aux_recebe_serial[x];
		}

		Write_Buffer_FLASH[0] = buffer_sensibilidade[1]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração da sensibilidade
		Write_Buffer_FLASH[1] = buffer_sensibilidade[2]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração da sensibilidade
		Write_Buffer_FLASH[2] = buffer_sensibilidade[3]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração da sensibilidade
		Write_Buffer_FLASH[3] = buffer_sensibilidade[4]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração da sensibilidade
		Write_Buffer_FLASH[4] = buffer_sensibilidade[5]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração da sensibilidade
		Write_Buffer_FLASH[5] = buffer_sensibilidade[6]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração da sensibilidade
		Write_Buffer_FLASH[6] = buffer_sensibilidade[7]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração da sensibilidade
		Write_Buffer_FLASH[7] = buffer_sensibilidade[8]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração da sensibilidade
		ESCREVE_FLASH_INTERNA(endFLASHSensibilidadeArea1,8,0); //Escreve os valores de sensibilidade das áreas na memória FLASH no endereço especificado

		delay_ms(10); //Espera 10ms

		//ANULA AREAS
		for(x = 8;x < 16;x++) //Armazena o anula_area da área 1 a área 8, se 0 não anula, se 1 anula
		{
			if(anula_area[x - 8] != aux_recebe_serial[x])
			{
				fnGravaAuditoria((80 + x),anula_area[x - 8],aux_recebe_serial[x],'G','S');
			}
			anula_area[x - 8] = aux_recebe_serial[x];
		}

		Write_Buffer_FLASH[0] = anula_area[AREA1]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração de anula_area
		Write_Buffer_FLASH[1] = anula_area[AREA2]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração de anula_area
		Write_Buffer_FLASH[2] = anula_area[AREA3]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração de anula_area
		Write_Buffer_FLASH[3] = anula_area[AREA4]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração de anula_area
		Write_Buffer_FLASH[4] = anula_area[AREA5]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração de anula_area
		Write_Buffer_FLASH[5] = anula_area[AREA6]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração de anula_area
		Write_Buffer_FLASH[6] = anula_area[AREA7]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração de anula_area
		Write_Buffer_FLASH[7] = anula_area[AREA8]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração de anula_area
		ESCREVE_FLASH_INTERNA(endFLASHAnulaArea1,8,0); //Escreve os valores de anula_area das áreas na memória FLASH no endereço especificado

		//CANAL
		if(canal != aux_recebe_serial[16])
		{
			fnGravaAuditoria(2,canal,aux_recebe_serial[16],'G','S');
		}

		canal = aux_recebe_serial[16]; //Armazena o canal

		Write_Buffer_FLASH[0] = canal; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração do canal
		ESCREVE_FLASH_INTERNA(endFLASHCanal,1,0); //Escreve o valor do canal na memória FLASH no endereço especificado

		delay_ms(10); //Espera 10ms

		//FILTRO DE RUIDO
		if(filtroruido != aux_recebe_serial[17])
		{
			fnGravaAuditoria(12,filtroruido,aux_recebe_serial[17],'G','S');
		}

		filtroruido = aux_recebe_serial[17]; //Armazena o valor do filtro de ruido

		Write_Buffer_FLASH[0] = filtroruido; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração do filtro de ruido
		ESCREVE_FLASH_INTERNA(endFLASHFiltroRuido,1,0); //Escreve o valor do filtro de ruido na memória FLASH no endereço especificado

		delay_ms(10); //Espera 10ms

		//SINAL RELÉ
		if(sinal_rele != aux_recebe_serial[18])
		{
			fnGravaAuditoria(6,sinal_rele,aux_recebe_serial[18],'G','S');
		}

		sinal_rele = aux_recebe_serial[18]; //Armazena o sinal do relé - se pulso ou retenção

		Write_Buffer_FLASH[0] = sinal_rele; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração do sinal do relé
		ESCREVE_FLASH_INTERNA(endFLASHSinalRele,1,0); //Escreve o valor do sinal do relé na memória FLASH no endereço especificado

		delay_ms(10); //Espera 10ms

		//PULSO DO RELÉ
		if(pulso_rele != aux_recebe_serial[19])
		{
			fnGravaAuditoria(7,pulso_rele,aux_recebe_serial[19],'G','S');
		}

		pulso_rele = aux_recebe_serial[19]; //Armazena o pulso do relé multiplicado por 10

		Write_Buffer_FLASH[0] = pulso_rele; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração do pulso do relé
		ESCREVE_FLASH_INTERNA(endFLASHPulsoRele,1,0); //Escreve o valor do pulso do relé na memória FLASH no endereço especificado

		delay_ms(10); //Espera 10ms

		//SINAL DA TRAVA
		if(sinal_trava != aux_recebe_serial[20])
		{
			fnGravaAuditoria(4,sinal_trava,aux_recebe_serial[20],'G','S');
		}

		sinal_trava = aux_recebe_serial[20]; //Armazena o sinal da trava - se pulso ou retenção e controle somente ou retenção e controle e teclado

		Write_Buffer_FLASH[0] = sinal_trava; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração do sinal da trava
		ESCREVE_FLASH_INTERNA(endFLASHSinalTrava,1,0); //Escreve o valor do sinal da trava na memória FLASH no endereço especificado

		delay_ms(10); //Espera 10ms

		//PULSO DA TRAVA
		if(pulso_trava != aux_recebe_serial[21])
		{
			fnGravaAuditoria(5,pulso_trava,aux_recebe_serial[21],'G','S');
		}

		pulso_trava = aux_recebe_serial[21]; //Armazena o pulso da trava multiplicado por 10

		Write_Buffer_FLASH[0] = pulso_trava; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração do pulso do relé
		ESCREVE_FLASH_INTERNA(endFLASHPulsoTrava,1,0); //Escreve o valor do pulso da trava na memória FLASH no endereço especificado

		delay_ms(10); //Espera 10ms

		//MODO DE TRAVAMENTO
		if(modo_travamento != aux_recebe_serial[22])
		{
			fnGravaAuditoria(1,modo_travamento,aux_recebe_serial[22],'G','S');
		}

		modo_travamento = aux_recebe_serial[22]; //Armazena o modo de travamento do controle - somente destrava ou trava/destrava

		Write_Buffer_FLASH[0] = modo_travamento; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração do modo de travamento
		ESCREVE_FLASH_INTERNA(endFLASHModoTravamento,1,0); //Escreve o valor do modo de travamento na memória FLASH no endereço especificado

		delay_ms(10); //Espera 10ms

		//SELEÇÃO DE METAIS
		if(selecao_metais != aux_recebe_serial[23])
		{
			fnGravaAuditoria(3,selecao_metais,aux_recebe_serial[23],'G','S');
		}
		selecao_metais = aux_recebe_serial[23]; //Armazena a seleção de metais

		Write_Buffer_FLASH[0] = selecao_metais; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração da selecao de metais
		ESCREVE_FLASH_INTERNA(endFLASHSelecaoMetais,1,0); //Escreve o valor da selecao de metais na memória FLASH no endereço especificado

		delay_ms(10); //Espera 10ms

		//VOLUME DA MENSAGEM DE VOZ
		if(volume_mensagem_voz != aux_recebe_serial[24])
		{
			fnGravaAuditoria(25,volume_mensagem_voz,aux_recebe_serial[24],'G','S');
		}

		volume_mensagem_voz = aux_recebe_serial[24]; //Armazena o volume da mensagem de voz - 0 a 10, sendo 0 desligado

		Write_Buffer_FLASH[0] = volume_mensagem_voz; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração do volume da mensagem de voz
		ESCREVE_FLASH_INTERNA(endFLASHMensagemVozVolume,1,0); //Escreve o valor do volume da mensagem de voz na memória FLASH no endereço especificado

		delay_ms(10); //Espera 10ms

		//VOLUME DO BUZZER
		if(buffer_buzzer[BUZZER_VOLUME] != aux_recebe_serial[25])
		{
			fnGravaAuditoria(24,buffer_buzzer[BUZZER_VOLUME],aux_recebe_serial[25],'G','S');
		}

		buffer_buzzer[BUZZER_VOLUME] = aux_recebe_serial[25]; //Armazena o volume do buzzer - 0 a 10, sendo 0 desligado

		Write_Buffer_FLASH[0] = buffer_buzzer[BUZZER_VOLUME]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração do volume do buzzer
		ESCREVE_FLASH_INTERNA(endFLASHBuzzerVolume,1,0); //Escreve o valor do volume do buzzer na memória FLASH no endereço especificado

		delay_ms(10); //Espera 10ms

		//TOM DO BUZZER
		if(buffer_buzzer[BUZZER_TOM] != aux_recebe_serial[26])
		{
			fnGravaAuditoria(23,buffer_buzzer[BUZZER_TOM],aux_recebe_serial[26],'G','S');
		}

		buffer_buzzer[BUZZER_TOM] = aux_recebe_serial[26]; //Armazena o volume do buzzer - 0 a 10, sendo 0 desligado

		Write_Buffer_FLASH[0] = buffer_buzzer[BUZZER_TOM]; //Guarda no vetor Write_Buffer_FLASH para poder gravar na memória FLASH a alteração do volume do buzzer
		ESCREVE_FLASH_INTERNA(endFLASHBuzzerTom,1,0); //Escreve o valor do volume do buzzer na memória FLASH no endereço especificado

		delay_ms(10); //Espera 10ms

		if(EventToSend)
		{
			numero_do_bloco = ( (end_event_reenvio - 0x48000) / 4096) + 5; //Coloquei 5 porque aponta no endereço 0x48000,se estiver na faixa dos 48000 a 49000 a divisão vai dar zero e somando a 5 vai dar 5 x 0x1000 = 0x5000, sendo 0x43000 + 0x5000 = 0x48000 que vai estar no endereço certo
			Write_Buffer_FLASH[0] = 0; //coloca 0 para zerar a posição especifica de memória.
			ESCREVE_FLASH_INTERNA(end_event_reenvio,1,numero_do_bloco); //Escreve zero no endereço correspondente
			flagEventoLido = 0; //Zera a varíavel flagEventoLido
		}
		if(AudToSend)
		{
			numero_do_bloco = ( (end_audit_reenvio - 0x75000) / 4096) + 50; //Coloquei 50 porque aponta no endereço 0x75000,se estiver na faixa dos 75000 a 76000 a divisão vai dar zero e somando a 50 vai dar 50(0x32 em hexa) x 0x1000 = 0x32000, sendo 0x43000 + 0x32000 = 0x75000 que vai estar no endereço certo
			Write_Buffer_FLASH[0] = 0; //coloca 0 para zerar a posição especifica de memória.
			ESCREVE_FLASH_INTERNA(end_audit_reenvio,1,numero_do_bloco); //Escreve zero no endereço correspondente
			flagAuditLido = 0; //Zera a varíavel flagEventoLido
		}
	}


	y = 0;

	if(recebe_serial[8] == '2' && recebe_serial[9] == '0' && recebe_serial[10] == '0' && recebe_serial[21] == '2') //Config 2 serve somente para zerar as flags
	{
		if(EventToSend)
		{
			numero_do_bloco = ( (end_event_reenvio - 0x48000) / 4096) + 5; //Coloquei 5 porque aponta no endereço 0x48000,se estiver na faixa dos 48000 a 49000 a divisão vai dar zero e somando a 5 vai dar 5 x 0x1000 = 0x5000, sendo 0x43000 + 0x5000 = 0x48000 que vai estar no endereço certo
			Write_Buffer_FLASH[0] = 0; //coloca 0 para zerar a posição especifica de memória.
			ESCREVE_FLASH_INTERNA(end_event_reenvio,1,numero_do_bloco); //Escreve zero no endereço correspondente
			flagEventoLido = 0; //Zera a varíavel flagEventoLido
		}
		if(AudToSend)
		{
			numero_do_bloco = ( (end_audit_reenvio - 0x75000) / 4096) + 50; //Coloquei 50 porque aponta no endereço 0x75000,se estiver na faixa dos 75000 a 76000 a divisão vai dar zero e somando a 50 vai dar 50(0x32 em hexa) x 0x1000 = 0x32000, sendo 0x43000 + 0x32000 = 0x75000 que vai estar no endereço certo
			Write_Buffer_FLASH[0] = 0; //coloca 0 para zerar a posição especifica de memória.
			ESCREVE_FLASH_INTERNA(end_audit_reenvio,1,numero_do_bloco); //Escreve zero no endereço correspondente
			flagAuditLido = 0; //Zera a varíavel flagEventoLido
		}
	}

	if(recebe_serial[8] == '2' && recebe_serial[9] == '0' && recebe_serial[10] == '0' && recebe_serial[21] == '3') //Solicita a quantidade de log de eventos
	{
		LIBERA_ENVIA_PACOTES = SIM; //Libera o envio de pacotes
		tempo_envio_ethernet = 0; //zera a variável para enviar o pacote de dados novamente
		estado_ENVIA_SERIAL_ETHERNET = ESTADO_ENVIAR; //Troca para estado de enviar pacotes de dados novamente
	}
	if(recebe_serial[8] == '2' && recebe_serial[9] == '0' && recebe_serial[10] == '0' && recebe_serial[21] == '4') //Retorna um evento pois o anterior foi perdido
	{
		indice_eventos = indice_eventos - 1;
		indice_eventos_cont = indice_eventos_cont - 1;
		INICIA_TEMPO_ENVIO_ETHERNET = TRUE; //Inicializa a variável INICIA_TEMPO_ENVIO_ETHERNET para inicializar a contagem de tempo
		tempo_envio_ethernet = 0; //Zera o contador de tempo tempo_envio_ethernet
		delay_ms(100);
	}
	if(recebe_serial[8] == '2' && recebe_serial[9] == '0' && recebe_serial[10] == '0' && recebe_serial[21] == '5') //Solicito o log de auditorias
	{
		//Cpu_DisableInt(); //Desabilita Interrupções
		////////////////////////////////////////////////////////
		LIBERA_ENVIA_PACOTES = NAO;
		LIGA_TRAVA; //Energiza a trava
		LIGA_RELE; //Energiza o relé
		LIGA_SINALEIRA_VERMELHA; //Energiza sinaleira vermelha
		MANUTENCAO = SIM;
		emite_msg_manutencao = SIM;
		tela = TELA_EM_MANUTENCAO;
		Atualiza_LCD();
		emite_msg_manutencao = NAO;
		////////////////////////////////////////////////////////

		for(num_bloco_a = 5;num_bloco_a < 125;num_bloco_a++)
		{
			for(num_bytes_a = 0;num_bytes_a < 3960;num_bytes_a = num_bytes_a + 11)
			{
				end_bloco_a = END_INI_PARAMETROS + num_bytes_a + (num_bloco_a * 4096); //end_bloco = 0x83000 + 0 bytes + (5 * 4096) = 0x84000

				LE_FLASH_INTERNA(end_bloco_a,11); //Lê os 11 bytes a partir do endereço especificado

				if(Read_Buffer_FLASH[0] == 0xFF && Read_Buffer_FLASH[1] == 0xFF && Read_Buffer_FLASH[2] == 0xFF && Read_Buffer_FLASH[3] == 0xFF &&
				   Read_Buffer_FLASH[4] == 0xFF && Read_Buffer_FLASH[5] == 0xFF && Read_Buffer_FLASH[6] == 0xFF && Read_Buffer_FLASH[7] == 0xFF &&
				   Read_Buffer_FLASH[8] == 0xFF && Read_Buffer_FLASH[9] == 0xFF && Read_Buffer_FLASH[10] == 0xFF) //Se todos os 11 bytes forem igual 0xFF então
				{
					if(num_bytes_a > 0 && num_bytes_a < 4096)
					{
						aux_num_bytes = num_bytes_a;
						aux_num_bloco = (num_bloco_a - 5);
						num_bytes_a = 3960;
						num_bloco_a = 125;
					}
					else if(num_bytes_a == 0 && num_bloco_a > 0)
					{
						aux_num_bytes = num_bytes_a;
						aux_num_bloco = (num_bloco_a - 5);

						num_bytes_a = 3960;
						num_bloco_a = 125;
					}
					else if(num_bytes_a == 3971 && num_bloco_a > 0)
					{
						aux_num_bytes = 0;
						aux_num_bloco = (num_bloco_a - 5);

						num_bytes_a = 3960;
						num_bloco_a = 125;
					}
				}
			}
		}
		if(aux_num_bloco >= 1)
		{
			aux_numero_de_registros = (aux_num_bloco * 3960) + (aux_num_bytes);
		}
		else if(aux_num_bytes == 0 && aux_num_bloco == 1)
		{
			aux_numero_de_registros = 0;
		}
		else if(aux_num_bytes > 0 && aux_num_bloco == 0)
		{
			aux_numero_de_registros = aux_num_bytes;
		}
		else if(num_bytes_a == 3960 && num_bloco_a == 125)
		{
			aux_numero_de_registros = (num_bloco_a - 5) * 3960;
		}

		numero_de_registros = (word)(aux_numero_de_registros / 11);

		num_bytes_a = 0;
		num_bloco_a = 5;

		//Armazena em cada posição do vetor envia_serial uma informação
		//////////////////////////////////////////////////////////////////////////////////////////
		envia_serial[0] = '#'; //Caracter de inicio
		envia_serial[1] = 'e'; //Caracter de inicio
		envia_serial[2] = 'f'; //Caracter de inicio
		envia_serial[3] = 'P'; //Caracter de inicio
		envia_serial[4] = 'R'; //Caracter de inicio
		envia_serial[5] = 'T'; //Caracter de inicio
		envia_serial[6] = '0'; //Caracter de inicio
		envia_serial[7] = '0'; //Caracter de inicio
		envia_serial[8] = '1'; //Caracter de inicio
		envia_serial[9] = (byte)(numero_de_registros >> 8);
		envia_serial[10] = (byte)(numero_de_registros);
		envia_serial[11] = '!'; //Caracter de fim
		envia_serial[12] = '\n'; //Caracter de fim

		SERIAL_ETHERNET_SendBlock((byte*)&envia_serial,13,&Sent); //Envia os dados seriais

		SERIAL_ETHERNET_ClearTxBuf();
		//////////////////////////////////////////////////////////////////////////////////////////

		aux_numero_de_registros = numero_de_registros%360;
		if(aux_numero_de_registros > 0)
		{
			aux_num_bloco = numero_de_registros/360;
			aux_num_bloco_extra = 1;
		}
		else
		{
			aux_num_bloco = numero_de_registros/360;
			aux_num_bloco_extra = 0;
		}

		n_bloco_a = 1;

		indice_auditorias = 0;
		indice_auditorias_cont = 0;

		n_logauditorias = numero_de_registros;
		n_blocologauditorias = aux_num_bloco;
		n_blocologauditorias_extra = aux_num_bloco_extra;

		FIM_LOG_AUDITORIAS = FALSE;

		delay_ms(1000);

	}
	if(recebe_serial[8] == '2' && recebe_serial[9] == '0' && recebe_serial[10] == '0' && recebe_serial[21] == '6') //Retorna um evento pois o anterior foi perdido
	{
		indice_auditorias = indice_auditorias - 1;
		indice_auditorias_cont = indice_auditorias_cont - 1;
		INICIA_TEMPO_ENVIO_ETHERNET = TRUE; //Inicializa a variável INICIA_TEMPO_ENVIO_ETHERNET para inicializar a contagem de tempo
		tempo_envio_ethernet = 0; //Zera o contador de tempo tempo_envio_ethernet
		delay_ms(100);
	}

	if(recebe_serial[8] == '2' && recebe_serial[9] == '0' && recebe_serial[10] == '0' && recebe_serial[21] != '1' && recebe_serial[21] != '3' &&
	   recebe_serial[21] != '5' && recebe_serial[21] != '0') //Se config que esta no recebe_serial[21] for diferente de 1 e 2 e 3 e 5 e 6 então envia erro
	{
		Write_Buffer_FLASH[0] = '#';
		Write_Buffer_FLASH[1] = 'e'; //Caracter de inicio
		Write_Buffer_FLASH[2] = 'r'; //Caracter de inicio
		Write_Buffer_FLASH[3] = 'P'; //Caracter de inicio
		Write_Buffer_FLASH[4] = 'R'; //Caracter de inicio
		Write_Buffer_FLASH[5] = 'T'; //Caracter de inicio
		Write_Buffer_FLASH[6] = '0'; //Caracter de inicio
		Write_Buffer_FLASH[7] = '0'; //Caracter de inicio
		Write_Buffer_FLASH[8] = '2'; //Caracter de inicio
		Write_Buffer_FLASH[9] = '!'; //Caracter de inicio
		Write_Buffer_FLASH[10] = '/n'; //Caracter de inicio

		SERIAL_ETHERNET_SendBlock((byte*)&Write_Buffer_FLASH,11,&Sent); //Envia para o módulo ethernet os 352 bytes de dados
		SERIAL_ETHERNET_ClearTxBuf();
	}

	for(x = 0;x < 300;x++)
	{
		recebe_serial[x] = 0;
	}

	estado_MODULO_ETHERNET = ESTADO_ESPERA;

*/






//ETHERNET ENVIA
/*
 *
 * /*
	envia_serial[0] = '#'; //Envia o caracter inicial do pacote de dados
	envia_serial[1] = 'e';
	envia_serial[2] = 'a';
	for(x = 3;x < 11;x++) //Envia a sensibilidade atual das 8 áreas
	{
		envia_serial[x] = buffer_sensibilidade[x-2];
	}
	envia_serial[11] = selecao_metais; //Envia a seleção de metais atual
	envia_serial[12] = filtroruido; //Envia o valor do filtro de ruido atual
	envia_serial[13] = var_tensao_cinco; //Envia a tensão de cinco volts multiplicada por 10
	envia_serial[14] = var_tensao_quinze; //Envia a tensão de quinze volts multiplicada por 10
	envia_serial[15] = var_tensao_menos_quinze; //Envia a tensão de menos quinze volts multiplicada por 10
	envia_serial[16] = var_tensao_rede; //Envia a tensão da rede que vai de 108 a 253 VAC
	envia_serial[17] = (byte)(var_tensao_bateria >> 8); //Envia o primeiro byte alto da tensão da bateria
	envia_serial[18] = (byte)(var_tensao_bateria); //Envia o segundo byte baixo da tensão da bateria
	for(x = 19;x < 27;x++) //Envia o anula_area de cada área se zero não anula e se 1 anula
	{
		envia_serial[x] = anula_area[x-19];
	}
	envia_serial[27] = (byte)(contador_entra >> 24); //Escreve o valor do quarto byte mais alto no vetor para gravação na memória FLASH
	envia_serial[28] = (byte)(contador_entra >> 16); //Escreve o valor do terceiro byte mais alto no vetor para gravação na memória FLASH
	envia_serial[29] = (byte)(contador_entra >> 8); //Escreve o valor do segundo byte mais alto no vetor para gravação na memória FLASH
	envia_serial[30] = (byte)(contador_entra); //Escreve o valor do primeiro byte no vetor para gravação na memória FLASH

	envia_serial[31] = (byte)(contador_sai >> 24); //Escreve o valor do quarto byte mais alto no vetor para gravação na memória FLASH
	envia_serial[32] = (byte)(contador_sai >> 16); //Escreve o valor do terceiro byte mais alto no vetor para gravação na memória FLASH
	envia_serial[33] = (byte)(contador_sai >> 8); //Escreve o valor do segundo byte mais alto no vetor para gravação na memória FLASH
	envia_serial[34] = (byte)(contador_sai); //Escreve o valor do primeiro byte no vetor para gravação na memória FLASH

	envia_serial[35] = (byte)(contador_bloqueios >> 24); //Escreve o valor do quarto byte mais alto no vetor para gravação na memória FLASH
	envia_serial[36] = (byte)(contador_bloqueios >> 16); //Escreve o valor do terceiro byte mais alto no vetor para gravação na memória FLASH
	envia_serial[37] = (byte)(contador_bloqueios >> 8); //Escreve o valor do segundo byte mais alto no vetor para gravação na memória FLASH
	envia_serial[38] = (byte)(contador_bloqueios); //Escreve o valor do primeiro byte no vetor para gravação na memória FLASH

	envia_serial[39] = (byte)(contador_desbloqueios >> 24); //Escreve o valor do quarto byte mais alto no vetor para gravação na memória FLASH
	envia_serial[40] = (byte)(contador_desbloqueios >> 16); //Escreve o valor do terceiro byte mais alto no vetor para gravação na memória FLASH
	envia_serial[41] = (byte)(contador_desbloqueios >> 8); //Escreve o valor do segundo byte mais alto no vetor para gravação na memória FLASH
	envia_serial[42] = (byte)(contador_desbloqueios); //Escreve o valor do primeiro byte no vetor para gravação na memória FLASH

	time_aux = GetData(); //A estrutura time_aux recebe as informações de data e hora atuais
	dataAtualizar = GetData(); //A estrutura dataAtualizar recebe os valores de data e hora atuais

	envia_serial[43] = dataAtualizar.Dia; //Envia o dia atual
	envia_serial[44] = dataAtualizar.Mes; //Envia o mês atual

	ano = dataAtualizar.Ano; //Armazena na variável ano o ano atula
	envia_serial[45] = (byte)(ano >> 8); //Envia o byte alto do ano
	envia_serial[46] = (byte)(ano); //Envia o byte baixo do ano

	envia_serial[47] = sinal_rele; //Envia o sinal do relé

	envia_serial[48] = sinal_trava; //Envia o sinal da trava

	envia_serial[49] = pulso_rele; //Envia o pulso do relé multiplicado por 10

	envia_serial[50] = pulso_trava; //Envia o pulso da trava multiplicado por 10

	envia_serial[51] = modo_travamento; //Envia o modo_travamento

	envia_serial[52] = buffer_buzzer[BUZZER_VOLUME]; //Envia o volume do buzzer

	envia_serial[53] = volume_mensagem_voz; //Envia o volume da mensagem de voz

	envia_serial[54] = canal; //Envia o canal

	envia_serial[55] = 0;

	envia_serial[56] = 0;

	envia_serial[57] = 0;

	envia_serial[58] = 0;

	envia_serial[59] = 0;

	envia_serial[60] = 0;

	envia_serial[61] = 0;

	envia_serial[62] = 'P';

	envia_serial[63] = 'R';

	envia_serial[64] = 'T';

	envia_serial[65] = '0';

	envia_serial[66] = '0';

	envia_serial[67] = '2';

	envia_serial[68] = '!'; //Envia o caracter final do pacote de dados

	envia_serial[69] = '\n'; //Envia o caracter de im

*/

/*
void fnContadorPassagem(void) //Função que trata os estados lidos pela função anterior
{
	switch(estado_passagem) //Conforme valor da variável estado_passagem vai para o case específico
	{
		case 1: //Caso 1 significa que ninguém ainda passou pelos infras
		{
			if(flag_passagem == _INFRA1_ATIVO) //Se flag_passagem for igual a _INFRA1_ATIVO significa que esta entrando então
			{
				estado_passagem = 2; //Armazena na variável estado_passagem a informação 2
			}
			else if(flag_passagem == _INFRA2_ATIVO) //Senão se flag_passagem for igual a _INFRA2_ATIVO significa que esta saindo então
			{
				estado_passagem = 3; //Armazena na variável estado_passagem a informação 3
			}
			break;
		}

		case 2: //Caso 2 significa que esta entrando alguém
		{
			if(flag_passagem == _AMBOS_INFRAS_ATIVO) //Se flag_passagem for igual a _AMBOS_INFRAS_ATIVO significa que esta no meio dos dois sensores então espera finalizar a entrada
			{
				estado_passagem = 4; //Armazena na variável estado_passagem a informação 4
			}
			else if(flag_passagem == _AMBOS_INFRAS_INATIVO)	//Senão se flag_passagem for igual a _AMBOS_INFRAS_INATIVO significa que não esta na frente de nenhum sensor e então volta ao estado inicial
			{
				estado_passagem = 1; //Armazena na variável estado_passagem a informação 1
			}
			break;
		}

		case 3: //Caso 3 significa que esta saindo alguém
		{
			if(flag_passagem == _AMBOS_INFRAS_ATIVO) //Se flag_passagem for igual a _AMBOS_INFRAS_ATIVO significa que esta no meio dos dois sensores então espera finalizar a saida
			{
				estado_passagem = 5; //Armazena na variável estado_passagem a informação 5
			}
			else if(flag_passagem == _AMBOS_INFRAS_INATIVO)	//Senão se flag_passagem for igual a _AMBOS_INFRAS_INATIVO significa que não esta na frente de nenhum sensor e então volta ao estado inicial
			{
				estado_passagem = 1; //Armazena na variável estado_passagem a informação 1
			}
			break;
		}

		case 4:	//Caso 4 significa que entrou alguém e só esta esperando que entre ou passe pelo INFRA2
		{
			if(flag_passagem == _INFRA2_ATIVO) //Se flag_passagem for igual a _INFRA2_ATIVO significa que esta na frente do INFRA2, ou seja, entrando, esperando realmente entrar
			{
				estado_passagem = 1; //Armazena o valor 1 para iniciar toda a leitura novamente
				contador_entra++; //Incrementa contador_entra
				Write_Buffer_FLASH[0] = (byte)(contador_entra >> 24); //Pega o primeiro byte mais alto e desloca 24 casas para poder separar em byte o conteúdo da dword contador_entra que tem 4 bytes
				Write_Buffer_FLASH[1] = (byte)(contador_entra >> 16); //Pega o segundo byte e desloca 16 casas para poder separar em byte o conteúdo da dword contador_entra que tem 4 bytes
				Write_Buffer_FLASH[2] = (byte)(contador_entra >> 8); //Pega o terceiro byte e desloca 8 casas para poder separar em byte o conteúdo da dword contador_entra que tem 4 bytes
				Write_Buffer_FLASH[3] = (byte)(contador_entra); //Pega o quarto byte e não desloca para poder separar em byte o conteúdo da dword contador_entra que tem 4 bytes
				ESCREVE_FLASH_INTERNA(endFLASHContadorEntra,4,0); //Escreve na memória FLASH a variável contador_entra alterado no endereço especificado
				contador_passagens = contador_entra + contador_sai; //Armazena na variável contador_passagens a soma de contador_entra com contador_sai
				if(trava_inteligente == SIM) //Se trava_inteligente for igual a SIM então
				{
					fnTravaDetector(); //Trava a porta giratória
				}
				if(analiseir == SIM) //Se analiseir for igual a SIM então
				{
					entrou = SIM; //Armazena na variável entrou a informação SIM para informar que passou na sequência correta de entrada dos infras
					tempo_permissao = 0; //Zera a variável tempo_permissao para liberar um tempo para poder detectar
				}
				estado_CONTADOR = ESTADO_ESPERA; //Armazena na variável estado_CONTADOR a informação ESTADO_ESPERA
			}
			else if(flag_passagem == _INFRA1_ATIVO) //Senão se flag_passagem for igual a _INFRA1_ATIVO significa que esta na frente do INFRA1, ou seja, retornou, esperando retornar
			{
				estado_passagem = 2; //Armazena na variável estado_passagem a informação 2
			}
			break;
		}

		case 5: //Caso 5 significa que saiu alguém e só esta esperando que saia ou passe pelo INFRA 1
		{
			if(flag_passagem == _INFRA1_ATIVO) //Se flag_passagem for igual a _INFRA1_ATIVO significa que esta na frente do INFRA1, ou seja, saindo, esperando realmente sair
			{
				estado_passagem = 1; //Armazena o valor 1 para iniciar toda a leitura novamente
				contador_sai++; //Incrementa contador_sai
				Write_Buffer_FLASH[0] = (byte)(contador_sai >> 24); //Pega o primeiro byte mais alto e desloca 24 casas para poder separar em byte o conteúdo da dword contador_sai que tem 4 bytes
				Write_Buffer_FLASH[1] = (byte)(contador_sai >> 16); //Pega o segundo byte e desloca 16 casas para poder separar em byte o conteúdo da dword contador_sai que tem 4 bytes
				Write_Buffer_FLASH[2] = (byte)(contador_sai >> 8); //Pega o terceiro byte e desloca 8 casas para poder separar em byte o conteúdo da dword contador_sai que tem 4 bytes
				Write_Buffer_FLASH[3] = (byte)(contador_sai); //Pega o quarto byte e não desloca para poder separar em byte o conteúdo da dword contador_sai que tem 4 bytes
				ESCREVE_FLASH_INTERNA(endFLASHContadorSai,4,0); //Escreve na memória FLASH a variável contador_sai alterado no endereço especificado
				contador_passagens = contador_entra+contador_sai; //Armazena na variável contador_passagens a soma de contador_entra com contador_sai
				estado_CONTADOR = ESTADO_ESPERA; //Armazena na variável estado_CONTADOR a informação ESTADO_ESPERA
			}
			else if(flag_passagem == _INFRA2_ATIVO) //Senão se flag_passagem for igual a _INFRA2_ATIVO significa que esta na frente do INFRA2, ou seja, retornou, esperando retornar
			{
				estado_passagem = 3; //Armazena na variável estado_passagem a informação 3
			}
			break;
		}
		break;
	}
}
*/

/*********************************************
		 *
		 * modo_operacao_ethernet == MODO_SERIAL   --CODE 6#av



	  /*
	  */


/*
 *
 *
 */

/*
 */


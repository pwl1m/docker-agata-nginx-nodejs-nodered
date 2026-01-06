Detalhamento do Payload

# blc - Bloco/Código de Identificação
Valor: "#ea"
Identificador do tipo de pacote enviado
Definido em agata_hc_definitions.h como PACOTE_ENVIA_INICIO_CODIGO

# srl - Serial Number
Valor: "001042"
Número de série único do detector AGATA
Armazenado em numero_serie[6]
# monit - Array de Monitoramento (38 valores)
Valores em sequência:

- Posições 0-7: Sensibilidade das Zonas (50,50,50,50,50,50,50,50)

Valores de sensibilidade das 8 áreas de detecção (1-100)
Armazenados em buffer_sensibilidade[]

# Posição 8: Seleção de Metais (80)

Configuração de detecção de metais (1-100)
50: mais metais ferrosos; <50: mais não-ferrosos

Variável: selecao_metais

# Posição 9: Filtro de Ruído (0)

Tempo de amostragem em múltiplos de 10ms (0-15)
Variável: filtroruido

# Posições 10-12: Tensões DC (51,152,152,227)

Tensão 5V, +15V, -15V em décimos de volt
Variáveis: var_tensao_cinco, var_tensao_quinze, var_tensao_menos_quinze

# Posição 13: Tensão AC (284)

Tensão da rede elétrica
Variável: var_tensao_rede

# Posição 14: Tensão Bateria (290)

Tensão das baterias em décimos de volt
Variável: var_tensao_bateria

# Posição 15: Tensão Fonte (0)

Tensão da fonte chaveada 24V
Variável: var_tensao_chaveada

# Posições 16-23: Anulação de Áreas (0,0,0,0,0,0,0,0)

Estado de cada área (0=ativa, 1=anulada)
Array: anula_area[8]

# Posição 24: Canal (44)

Canal de frequência (1-25)
Variável: canal

# Posição 25: Modo Travamento (32)

1=Somente destrava, 2=Trava/destrava
Variável: modo_travamento

# Posição 26: Volume Mensagem Voz (22)

Volume 0-10 (0=desligado)
Variável: volume_mensagem_voz

# Posição 27: Sinal Relé (0)

1=Pulso, 2=Retenção
Variável: sinal_rele

# Posição 28: Timestamp AGATA (1762765470)

Unix timestamp do sistema
Obtido via time(NULL)

# Posição 29: Sinal Trava (2)

1=Pulso, 2=Retenção controle, 3=Retenção controle+teclado
Variável: sinal_trava

# Posição 30: Pulso Relé (1)

Duração em décimos de segundo (1-150)
Variável: pulso_rele

# Posição 31: Pulso Trava (1)

Duração em décimos de segundo (1-50)
Variável: pulso_trava

# Posição 32: Tom Buzzer (20)

Tom do buzzer (1-10)
Variável: buffer_buzzer[BUZZER_TOM]

# Posição 33: Volume Buzzer (2)

Volume 0-10 (0=desligado)
Variável: buffer_buzzer[BUZZER_VOLUME]

# Posição 34: Sorteador (1)

Estado do sorteador eletrônico (0=não, 1=sim)
Variável: sorteador

# Posição 35: Quantidade Sorteados (5)

Quantidade para sorteio (10-255)
Variável: quantidade_sorteados

# Posição 36: Porta Automática (1)

Estado da porta automática (0=não, 1=sim)
Variável: porta_automatica

--- 

# event - Eventos ["B","D","1762765440"]
[0]: Tipo de evento (B=Bloqueio, D=Desbloqueio, P=Painel, C=Controle, D=Detecção)
[1]: Dispositivo que originou o evento
[2]: Timestamp Unix do evento

# audit - Auditoria ["95","50","90","0","S","1666117800"]
[0]: Código do parâmetro alterado (1-98)
[1]: Valor antigo
[2]: Valor novo
[3]: Operador (0-9)
[4]: Dispositivo (S=Sistema, P=Painel, etc)
[5]: Timestamp Unix da alteração

Obs Sobre Dispositvo:
        P = Painel -> Utilizou-se do painel para fazer a mudança de parâmetro
        C = Controle -> Utilizou-se do controle para fazer a mudança de parâmetro
        S = Asset Care -> Utilizou-se do asset care para fazer a mudança de parâmetro
        E = Software PaP -> Utilizou-se do software pap para fazer a mudança de parâmetro
        R = Software USB -> Utilizou-se do software usb para fazer a mudança de parâmetro
        B = Bateria -> Aviso de baixo nível de energia 

Obs Sobre Operador:
        U = Usuario -> Usuário genérico - Utilizando Asset Care ou Software Serial
        G = Gerente -> Entrando no painel selecionando gerente e digitando a senha 
        T = Técnico -> Entrando no painel selecionando técnico e digitando a senha 
        D = Detector -> Ação feita automaticamente pelo detector em resposta às circunstâncias

# erros - Array de Erros ["A","0"]
[0]: Tipo de erro
[1]: Código/valor do erro
{"timestamp":"2025-11-25T18:25:26.459Z","data":
        {"blc":"#ea",
        "srl":"000000",
        "monit":
                [75,    //Sensibilidade Área 1 (1-100)
                44,     //Sensibilidade Área 2 (1-100)
                54,     //Sensibilidade Área 3 (1-100)
                25,     //Sensibilidade Área 4 (1-100)
                35,     //Sensibilidade Área 5 (1-100)
                77,     //Sensibilidade Área 6 (1-100)
                27,     //Sensibilidade Área 7 (1-100)
                32,     //Sensibilidade Área 8 (1-100)
                60,     //Seleção de Metais (1-100)
                9,      //Filtro Ruído / 0-15
                50,     //Tensão 5V / 0-100 -> em décimos
                160,    //Tensão +15V   ? qual valor minimo e maximo ou deixo o valor livre, gerar alerta?
                160,    //Tensão -15V   ? qual valor minimo e maximo ou deixo o valor livre, gerar alerta?
                255,    //Tensão AC     ? chamar de tensao_rede_ac ou tensao_ac_rede, gerar alerta?   
                280,    //Tensão Bateria? qual valor minimo e maximo ou deixo o valor livre, gerar alerta?
                290,    //Tensão Fonte  ? qual valor minimo e maximo ou deixo o valor livre , gerar alerta?
                0,      //Anula Área 1 / 0-1
                0,      //Anula Área 2 / 0-1
                0,      //Anula Área 3 / 0-1
                0,      //Anula Área 4 / 0-1
                0,      //Anula Área 5 / 0-1
                0,      //Anula Área 6 / 0-1
                0,      //Anula Área 7 / 0-1
                0,      //Anula Área 8 / 0-1
                0,      //Contador de entradas (reseta todo dia) - INT
                0,      //Contador de saídas (reseta todo dia) - INT
                53,     //Contador de bloqueios - INT
                48,     //Contador de desbloqueios - INT
                1666133783,     //Timestamp
                1,      //Sinal Relé / (1-2)
                3,      //Sinal Trava / sinal_trava (1*-2*-3*) 1=Pulso, 2=Retenção controle, 3=Retenção controle+teclado
                72,     //Tempo do puslo do Relé (Depende de Sinal Relé estar configurado como Pulso) - (1-150)
                27,     //Tempo do puslo da Trava (Depende de Sinal Trava estar configurado como Pulso) - (1-150)
                2,      //Modo Travamento / (1-2)
                7,      //Volume Buzzer - (0-10))
                5,      //Canal (1-25)
                0],     //Status da PGDM (Aberta/Fechada) / (0=não, 1=sim)

        "event":[],
        "audit":["195",         //Tipo da auditoria
                "0",            //Valor Antigo
                "1",            //Valor novo
                "D",            //Dispositivo
                "P",            //Origem
                "1666112400"],  //Timestamp de quando auditoria ocorreu
        "erros":["A",           //Erros relacionados ao Ágata
                "0"]            //Erros relacioandos a comunicação
        }
}

alteracao[
99,             //Sensibilidade Area 1
22,             //Sensibilidade Area 2
33,             //Sensibilidade Area 3
44,             //Sensibilidade Area 4
55,             //Sensibilidade Area 5
66,             //Sensibilidade Area 6
77,             //Sensibilidade Area 7
88,             //Sensibilidade Area 8
0,              //Anula Area 1
0,              //Anula Area 2
0,              //Anula Area 3
0,              //Anula Area 4
0,              //Anula Area 5
0,              //Anula Area 6
0,              //Anula Area 7
0,              //Anula Area 8
10,             //Canal
15,             //Filtro Ruido
1,              //Sinal Rele
10,             //Tempo Pulso Rele
1,              //Sinal Trava
10,             //Tempo Pulso Trava
1,              //Modo de travamento
50,             //Selecao de Metais
5,              //Volume mensagem de voz
5,              //Volume Buzzer
5,              //Tom buzzer
1733260800,     //Timestamp (do servidor)
1               //ID do usuário do Asset Care (Máx: 255)
]

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
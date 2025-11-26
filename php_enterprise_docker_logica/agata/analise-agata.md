Análise da Comunicação do Dispositivo PGDM
Após analisar o código, identifiquei como funciona a comunicação entre o dispositivo PGDM (Portal de Gestão deDetecção de Metais) e o sistema. Vou explicar o fluxo e criar um diagrama.

Resumo do Fluxo de Comunicação
1. Endpoints Principais
index.php: Endpoint legado (primeira versão)
pgdm.php: Endpoint principal atual
acesso_remoto.php: Controle de abertura/fechamento remoto
2. Protocolo de Comunicação
Criptografia
Algoritmo: AES-128-ECB
Estrutura do payload: [6 bytes de chave][dados criptografados em base64]
Chave: Os primeiros 6 caracteres são repetidos 3x e truncados para 16 bytes
Formato de Dados
{
  "blc": "#ea",
  "srl": "SERIAL123",
  "monit": [sens1, sens2, ..., sens8, metal, ruido, tensões, contadores, etc],
  "audit": [campo, valorAntigo, valorNovo, operador, dispositivo, timestamp],
  "event": [tipoBloqueio, tipoPainel, timestamp],
  "erros": [errorA, errorB]
}

3. Tipos de Configuração (Resposta)
Config	Significado	Ação
-1	Sem comunicação	Payload vazio ou inválido
0	Padrão	Sem alterações pendentes
1	Alterar parâmetros	ViewCare → AGATA (sensibilidades, volumes, etc)
2	Comando porta	Abrir/Fechar remotamente
Diagrama de Comunicação
sequenceDiagram
    participant D as Dispositivo PGDM
    participant E as Endpoint (pgdm.php)
    participant DB as Banco de Dados
    participant VC as ViewCare (Frontend)

    Note over D,VC: FLUXO 1: Monitoramento Normal
    
    D->>E: POST com payload criptografado
    Note over E: 1. Extrai chave (6 bytes)
    Note over E: 2. Descriptografa payload
    Note over E: 3. Valida JSON
    
    E->>DB: INSERT em tb_monitoramento_pgdm
    Note over DB: Armazena: sensibilidades,<br/>tensões, contadores, status porta
    
    opt Se houver auditoria
        E->>DB: INSERT em tb_monitoramento_pgdm_auditoria_detalhes
    end
    
    opt Se houver eventos
        E->>DB: INSERT em tb_monitoramento_pgdm_eventos_detalhes
    end
    
    opt Se houver erros
        E->>DB: INSERT em tb_monitoramento_pgdm_erros
    end
    
    E->>DB: SELECT de tb_alteracao_pgdm<br/>WHERE situacao IN (1,3)
    
    alt Sem alterações pendentes
        E-->>D: {config: 0, data: []}
    else Alteração de parâmetros (situacao=1)
        Note over E: Monta JSON com novos parâmetros
        Note over E: Criptografa resposta
        E-->>D: {config: 1, data: "[encrypted]"}
        E->>DB: UPDATE situacao = 2
    else Comando de porta (situacao=3)
        Note over E: Verifica status atual vs desejado
        Note over E: Define comando "A" (abrir) ou "F" (fechar)
        E-->>D: {config: 2, data: "[encrypted]"}
        E->>DB: UPDATE situacao = 2
    end

    Note over D,VC: FLUXO 2: Acesso Remoto (ViewCare)
    
    VC->>E: POST /acesso_remoto.php<br/>{tipo: "acessoRemotoAgata", id: serial}
    E->>DB: SELECT aberto FROM tb_monitoramento_pgdm<br/>ORDER BY id DESC LIMIT 1
    
    Note over E: Inverte estado:<br/>aberto=1 → 0 (fechar)<br/>aberto=0 → 1 (abrir)
    
    E->>DB: UPDATE tb_alteracao_pgdm SET situacao = -1<br/>(limpa fila)
    E->>DB: INSERT em tb_alteracao_pgdm<br/>(copia último + novo estado + situacao=3)
    E-->>VC: {code: 200, estadoPorta: novo_estado}
    
    Note over D: Na próxima comunicação,<br/>dispositivo receberá config=2

    Note over D,VC: FLUXO 3: Alteração de Parâmetros
    
    VC->>DB: INSERT em tb_alteracao_pgdm<br/>(situacao=1, novos parâmetros)
    
    Note over D: Na próxima comunicação...
    D->>E: POST monitoramento
    E->>DB: Detecta situacao=1
    E-->>D: {config: 1, data: novos_parametros}


Estrutura de Dados Principais
Tabela: tb_monitoramento_pgdm
- sensibilidade1-8: int (0-255)
- metais, ruidos: int
- tensaocinco, tensao_quinze, tensao_menos_quinze: float
- tensao_rede, tensao_bateria1: float
- anula1-8: int (0/1)
- cont_entrada1, cont_saida1, cont_bloqueio1, cont_des_bloqueio1: int
- sinal_rele, sinal_trava, sinal_pulso_rele, sinal_pulso_trava: int
- modo_travamento: int
- volume_buzzer, volume_voz, canal: int
- aberto: int (0=aberto, 1=fechado)
- serial: varchar


Tabela: tb_alteracao_pgdm
- Mesmos campos de configuração
- situacao: int
  * -1: cancelado
  * 1: pendente (alteração parâmetros)
  * 2: processado
  * 3: pendente (comando porta)
- usuario: varchar
- id_usuario: int
- aberto: int (comando de abertura/fechamento)

Regras de Negócio Identificadas
Fila de Comandos: Apenas 1 comando pendente por vez (situacao IN 1,3)
Prioridade: Acesso remoto limpa fila anterior (situacao = -1)
Log Completo: Toda comunicação é registrada na tabela logs
Auditoria: Mudanças feitas pelo software incluem id_usuario
Taxa de Comunicação: Sistema espera ~12 comunicações/hora (calculada em calculaTaxaComunicacao.php)
Pontos de Modernização Recomendados
🔴 Críticos
Criptografia: AES-ECB é inseguro, migrar para AES-GCM ou ChaCha20-Poly1305
Autenticação: Sem validação de origem do dispositivo
SQL Injection: Queries não preparadas em vários pontos
🟡 Importantes
API RESTful: Transformar em endpoints /api/v1/devices/{serial}/...
Validação de Dados: Usar DTOs e validadores
Rate Limiting: Proteger contra flood
Logs Estruturados: Migrar para sistema de logging profissional
🟢 Melhorias
WebSockets: Comunicação bidirecional em tempo real
Message Queue: Para comandos assíncronos (Redis/RabbitMQ)
Documentação OpenAPI: Swagger para a API
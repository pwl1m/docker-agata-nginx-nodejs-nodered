# Agata - Serviço Node.js

Serviço responsável por receber telemetria dos dispositivos Ágata, enfileirar comandos para devices e expor endpoints úteis para o front-end e integrações.

## Arquivos principais
- [nodejs/server.js](nodejs/server.js) — bootstrap do servidor e middlewares.
- [nodejs/routes/agata.js](nodejs/routes/agata.js) — todas as rotas públicas relacionadas ao Agata.

- Funções relacionadas ao database pode ser totalmente modificada pela PHP.
- [nodejs/database/repository.js](nodejs/database/repository.js) — funções de persistência: [`saveTelemetry`](nodejs/database/repository.js), [`saveAlteracaoUsuario`](nodejs/database/repository.js), [`updateAlteracaoStatus`](nodejs/database/repository.js), [`getLastTelemetry`](nodejs/database/repository.js), [`getActiveDevices`](nodejs/database/repository.js).
- [nodejs/database/connection.js](nodejs/database/connection.js) — pool MySQL: [`getPool`](nodejs/database/connection.js), [`query`](nodejs/database/connection.js), [`isEnabled`](nodejs/database/connection.js).
- [nodejs/database/schema.sql](nodejs/database/schema.sql) — modelo de banco (tabelas `devices`, `telemetria`, `eventos`, `auditoria`, `erros`, `alteracoes_usuario`).

- [nodejs/utils/crypto.js](nodejs/utils/crypto.js) — criptografia AES usada para comunicação com devices: [`encrypt`](nodejs/utils/crypto.js), [`decrypt`](nodejs/utils/crypto.js).
- [nodejs/utils/redisClient.js](nodejs/utils/redisClient.js) — cliente Redis: [`connect`](nodejs/utils/redisClient.js), [`get`](nodejs/utils/redisClient.js), [`set`](nodejs/utils/redisClient.js), [`setEx`](nodejs/utils/redisClient.js), [`publish`](nodejs/utils/redisClient.js), [`subscribe`](nodejs/utils/redisClient.js).
- [nodejs/utils/websocketManager.js](nodejs/utils/websocketManager.js) — Socket.IO manager: [`websocketManager.initialize`](nodejs/utils/websocketManager.js), [`websocketManager.broadcast`](nodejs/utils/websocketManager.js).
- [nodejs/utils/logger.js](nodejs/utils/logger.js) — logging e arquivos de log.


## Variáveis de ambiente importantes
- MYSQL_HOST, MYSQL_PORT, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE — configuração MySQL.
- REDIS_HOST, REDIS_PORT — Redis.
- PORT — porta HTTP (padrão 3000).
- DEBUG_RAW_PAYLOAD=true — salva payloads brutos em `logs/raw-incoming` e habilita `/debug/raw-incoming`.
- DEBUG_CRYPTO=true — imprime debug na criptografia.

## Rotas / APIs (resumo)

/agata                   POST   Recebe telemetria 
/agata/send-command      POST   Enfileira um comando para ser enviado ao próximo ciclo do device. 
/agata/queue/:serial     GET    Consulta se há comando pendente para um device específico. 
/agata/queue             GET    Lista todos os comandos pendentes para todos os devices. 
/agata/config/template   GET    Pegar estrutura padrão para formulário 
/agata/config/:serial    POST   Enviar nova configuração 
/agata/changes/:serial   GET    Histórico de alterações


- POST /agata  
  - Rota usada por dispositivos. Recebe RAW body (não JSON) com: first 6 char = serial (6 dígitos) + payload (base64 AES-128-ECB).
  - Processamento: [`utils/crypto.decrypt`](nodejs/utils/crypto.js) → JSON → grava via [`saveTelemetry`](nodejs/database/repository.js) (quando MySQL habilitado) → publica message Redis no canal `device_updates` → responde com comando pendente (se houver) ou `{ code: 200, config: 0, data: "" }`.
  - Observações: duplicação de payloads é detectada (cache 30s) — ver [nodejs/routes/agata.js](nodejs/routes/agata.js).

- POST /agata/send-command  
  - Enfileira comando para um device (Redis). Corpo JSON:
    {
      "serial": "123456",
      "comando": { ... } | { "alteracao": [...] },
      "formato": "array"?, 
      "usuario_id": 12?
    }
  - Valida `serial` (6 dígitos), criptografa com [`encrypt`](nodejs/utils/crypto.js) e armazena em Redis com TTL (`agata:cmd:{serial}`).
  - Registra alteração no banco via [`saveAlteracaoUsuario`](nodejs/database/repository.js) quando `usuario_id` presente.
  - Exemplo: curl -X POST http://localhost:3000/agata/send-command -H "Content-Type: application/json" -d "{\"serial\":\"000000\",\"comando\":{\"alteracao\":[1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,1736274360,9]}}"

- GET /agata/queue/:serial  
  - Retorna se há comando pendente para `serial`.

- GET /agata/queue  
  - Lista a fila de comandos (keys `agata:cmd:*`).

- GET /debug/raw-incoming  
  - Somente com `DEBUG_RAW_PAYLOAD=true`. Lista e mostra payloads brutos salvos.

- GET /health  
  - Status do serviço (clients WebSocket, pending commands, debug mode).

- GET /debug/state  
  - Estado interno: `pending_commands`, `recent_payloads`.


Exemplos cURL:
```sh
# Enfileirar comando (front-end / admin)
curl -X POST http://localhost:3000/agata/send-command \
  -H "Content-Type: application/json" \
  -d '{"serial":"123456","comando":{"acao":"toggle"},"usuario_id":12}'

# Verificar fila de um serial
curl http://localhost:3000/agata/queue/123456

# Health
curl http://localhost:3000/health
```

Para testes locais de telemetria (gera payload compatível): use `node` e [`utils/crypto.encrypt`](nodejs/utils/crypto.js) para criar o body:
```js
const AgataCrypto = require('./utils/crypto');
const serial = '123456';
const body = serial + AgataCrypto.encrypt(serial, JSON.stringify({ blc: 1 }));
// depois fazer curl com body como raw POST para /agata
```

## WebSocket / Redis
- Socket.IO servidor em path `/ws` (ver [nodejs/utils/websocketManager.js](nodejs/utils/websocketManager.js)).
  - Eventos: `device_update` (broadcast com payload publicado no Redis `device_updates`).
  - Inscrição por socket: enviar `{ serial }` em evento `subscribe` / `unsubscribe` (junta sala `device:{serial}`).
- Redis pub/sub: canal `device_updates` (mensagens publicadas em [`agata.js`](nodejs/routes/agata.js)), o `websocketManager` se inscreve para retransmitir a clients.

## Banco de dados
- Esquema base em [nodejs/database/schema.sql](nodejs/database/schema.sql).
- Principais funções de gravação/leitura: [`saveTelemetry`](nodejs/database/repository.js), [`getLastTelemetry`](nodejs/database/repository.js), [`getActiveDevices`](nodejs/database/repository.js).
- Quando MySQL não configurado o serviço continua em modo "offline" (veja logs de [nodejs/database/connection.js](nodejs/database/connection.js)).

## Logs
- Logs gerais: `logs/application.log` e `logs/processed-data.log` (implementado em [nodejs/utils/logger.js](nodejs/utils/logger.js)).
- Payloads brutos quando `DEBUG_RAW_PAYLOAD=true`: `logs/raw-incoming/*.log`.

## Troubleshooting
- Se MySQL não conectar: variável `MYSQL_HOST` ausente ou erro de conexão — ver [`connection.js`](nodejs/database/connection.js).
- Se Redis não conectar: ver configurações `REDIS_HOST`/`REDIS_PORT` e logs da inicialização (`redisClient.connect`).
- Erros de criptografia/compatibilidade com o device: habilitar `DEBUG_CRYPTO=true` para inspeção em [`utils/crypto.js`](nodejs/utils/crypto.js).
- Duplicação de payload detectada e ignorada (cache 30s) — se telemetria sumir, ver `/debug/raw-incoming` para inspecionar o raw.

---

## Payload do Ágata 
O payload enviado pelo dispositivo Ágata padrão:
```sh
{
  "code": 200,
  "config": 1,
  "data": "<base64_aes_encrypted>"
}
``` 

code: 200 para operação bem-sucedida.
config: 1 para alteração de parâmetros, 0 para confirmação, 2 para comandos.
data: campo criptografado (AES-128-ECB, chave = número de série repetido até 16 bytes, codificado em Base64).

## Exemplo de envio de alteracao
Antes da criptografia, o campo data contém:
```sh
{
  "alteracao": [50,50,50,50,50,50,50,50,0,0,0,0,0,0,0,0,10,15,1,10,1,10,1,50,5,5,5,1733260800,1]
}
```

- São 29 valores inteiros

Após criptografia e codificação, enviar via HTTP POST:
```sh
curl -X POST http://<IP_AGATA>:<PORTA>/agata \
  -H "Content-Type: application/json" \
  -d '{"code":200,"config":1,"data":"<PAYLOAD_BASE64_GERADO>"}'
```
- Exemplo de confirmação
```sh
curl -X POST http://<IP_AGATA>:<PORTA>/agata \
  -H "Content-Type: application/json" \
  -d '{"code":200,"config":0,"data":""}'
```
- Detalhes
Chave AES: número de série repetido até 16 bytes (ex: "0000000000000000")
Algoritmo: AES-128-ECB, sem IV, padding PKCS#7
Codificação: Base64
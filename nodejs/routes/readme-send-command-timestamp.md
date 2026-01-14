# send-command-timestamp — doc rápida

Resumo
- Endpoint: POST /agata/send-command-timestamp  
- Objetivo: Envio de comandos ao device onde o servidor injeta automaticamente o timestamp (segundos) no array de alteração, sem alterar a rota /agata/send-command existente.

Comportamento principal
- Se o payload é um array (comando.alteracao), o servidor sobrescreve o índice configurável (padrão 28 — posição 29) com o timestamp atual em segundos (Math.floor(Date.now()/1000)).
- Não é necessário enviar o timestamp no array; pode enviar um placeholder (ex.: 1) naquela posição — servidor substituirá.
- A rota criptografa o comando com a mesma lógica do send-command e publica/enfileira para o device.

Variáveis de ambiente relevantes
- AGATA_TIMESTAMP_INDEX (padrão: 28) — índice 0-based onde será injetado o timestamp.
- AGATA_TIMESTAMP_UNIT (padrão: 's') — unidade ('s' ou 'ms'). Atualmente usamos 's'.
- AGATA_QUEUE_CHANNEL (padrão: 'agata:commands') — canal Redis para publish (debug/monitor).
- AGATA_COMMAND_TTL_SECONDS (padrão: 3600) — TTL da chave Redis `agata:cmd:{serial}` que o device consulta.
- AGATA_ENABLE_SIGNATURE_CHECK (default: desligado) — se true, evita gravações redundantes no DB comparando assinatura normalizada.
- AGATA_LAST_ALTER_TTL_SECONDS (padrão: 86400) — TTL para cache da assinatura da última alteração em `agata:last-alteration:{serial}`.

Redis — chaves e fluxo
- Publicação: canal `agata:commands` recebe mensagens { serial, payload } quando a rota enfileira.
- Chave usada para fazer o device receber o comando: `agata:cmd:{serial}` = JSON { code:200, config:1, data: "<base64>" } (TTL AGATA_COMMAND_TTL_SECONDS).
- Assinatura/cache para evitar gravações duplicadas (se habilitado): `agata:last-alteration:{serial}` = assinatura normalizada (timestamp zerado) (TTL AGATA_LAST_ALTER_TTL_SECONDS).

Uso com o banco de dados
- A gravação usa o repositório já existente: repository.saveAlteracaoUsuario(...).
- Parâmetros:
  - serial, usuario_id, comando_enviado (JSON do comando com timestamp já injetado), ip_origem, user_agent.
- Se AGATA_ENABLE_SIGNATURE_CHECK='true', antes de salvar o serviço compara a assinatura normalizada com `agata:last-alteration:{serial}` e só salva se diferente (economiza escritas).
- Estrutura da tabela relevante: `alteracoes_usuario` com campo `comando_enviado` (JSON) e status (pendente/enviado/confirmado).

Exemplo de request (não passar o timestamp)
- Bash:
  ```
  curl -X POST http://localhost:3000/agata/send-command-timestamp \
    -H "Content-Type: application/json" \
    -d '{"serial":"000000","comando":{"alteracao":[30,30,30,30,30,30,30,30,50,15,51,153,152,224,286,291,0,0,0,0,0,0,0,0,4,12,13,0,1]}}'
  ```
  - O servidor vai substituir o índice 28 com o timestamp atual em segundos.

Validação / debug
- Logs esperados:
  - "Timestamp injetado (send-command-timestamp)"
  - "✅ Comando enfileirado no Redis (key agata:cmd)"
  - "Alteração registrada..." (se salvou)
- Redis checks:
  - `GET agata:cmd:000000` → deve retornar JSON com `data` = comando criptografado.
  - `SUBSCRIBE agata:commands` → ver mensagens publicadas.
  - `GET agata:last-alteration:000000` → assinatura quando AGATA_ENABLE_SIGNATURE_CHECK=true.

Obs:
- A rota /agata/send-command continua existindo e inalterada — esta rota é um caminho separado para testes e para habilitar o comportamento de injeção de timestamp sem risco.
- A lógica de assinatura e injeção está isolada em utils/agataHelpers.js e é opt-in via env vars.
- O device espera timestamp em segundos (10 dígitos), deixar AGATA_TIMESTAMP_UNIT='s'. Mudar para 'ms' só se o device aceitar 13 dígitos.

Problemas comuns:
- Device não recebe comando: verificar se chave `agata:cmd:{serial}` foi criada (mesmo formato usado por send-command).
- Comando enfileirado mas não enviado: verificar TTL, logs do device POST /agata e o tópico de publish.
- Gravação redundante no DB: habilitar AGATA_ENABLE_SIGNATURE_CHECK.

Diferenças no uso:
Caso for utilizar send-command/:
``` curl -X POST http://localhost:3000/agata/send-command -H "Content-Type: application/json" -d "{\"serial\":\"000000\",\"comando\":{\"alteracao\":[33,30,30,30,30,30,30,30,50,15,51,153,152,224,286,291,0,0,0,0,0,0,0,0,4,12,13,0,1666117727,1]}}" ```

Caso for utilizar send-command-timestamp/:
``` curl -X POST http://localhost:3000/agata/send-command-timestamp -H "Content-Type: application/json" -d "{\"serial\":\"000000\",\"comando\":{\"alteracao\":[33,33,33,33,30,30,30,30,50,15,51,153,152,224,286,291,0,0,0,0,0,0,0,0,4,12,13,0,1]}}" ```
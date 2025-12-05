AGATA Ingestão (Docker Stack)
Recepção de telemetria do Dispositivo Agata com: - Nginx (proxy); - Node.js (API/WebSocket) - Redis (cache/pub-sub).

Recebe payload criptografado > descriptografa (AES-128-ECB) > salva os dados brutos e versão normalizada (plana) para integração com banco relacional.

Componentes
Nginx: proxy reverso.
Node.js (Express + Socket.IO): API /agata, broadcast de eventos.
Redis: cache/pub-sub.
Node-RED (opcional): prototipação da equipe da Engenharia da Onix.
Fluxo de dados
POST /agata: "<serial:6><payload:base64>".
Descriptografia em utils/crypto.js (AES-128-ECB) (padrão do device).
Persistência:
Bruto descriptografado: nodejs/logs/raw-data/*.json.
Legado agregado: nodejs/logs/processed/*.json.
Normalizado (plano): nodejs/logs/processed-flat/*.json.
Normalização: utils/agataParser.js -> formato plano, adequado para MySQL.
Rotas disponíveis
POST /agata — ingestão de telemetria e comandos.
GET /health — status do serviço.
GET /ws — WebSocket.
Payload do Ágata Device
O payload enviado pelo dispositivo Ágata padrão:

{
  "code": 200,
  "config": 1,
  "data": "<base64_aes_encrypted>"
}
code: 200 para operação bem-sucedida.
config: 1 para alteração de parâmetros, 0 para confirmação, 2 para comandos.
data: campo criptografado (AES-128-ECB, chave = número de série repetido até 16 bytes, codificado em Base64).
Exemplo de envio de parâmetros
Antes da criptografia, o campo data contém:

{
  "alteracao": [50,50,50,50,50,50,50,50,0,0,0,0,0,0,0,0,10,15,1,10,1,10,1,50,5,5,5,1733260800,1]
}
São 29 valores inteiros, na ordem definida pelo firmware Ágata:

sensibilidade1-8, anulaAreas1-8, canal, filtroRuido, sinalRele, pulsoRele, sinalTrava, pulsoTrava, modoTravamento, selecaoMetais, volumeVoz, volumeBuzzer, tomBuzzer, timestamp, userId
Após criptografia e codificação, enviar via HTTP POST:

curl -X POST http://<IP_AGATA>:<PORTA>/agata \
  -H "Content-Type: application/json" \
  -d '{"code":200,"config":1,"data":"<PAYLOAD_BASE64_GERADO>"}'
Exemplo de confirmação
curl -X POST http://<IP_AGATA>:<PORTA>/agata \
  -H "Content-Type: application/json" \
  -d '{"code":200,"config":0,"data":""}'
Detalhes
Chave AES: número de série repetido até 16 bytes (ex: "0000000000000000")
Algoritmo: AES-128-ECB, sem IV, padding PKCS#7
Codificação: Base64
Segurança/Privacidade
Redis sem autenticação: usado apenas em desenvolvimento.
Criptografia ECB é padrão do device
Estrutura
docker-compose.yml
nginx/
nodejs/
  controllers/ middleware/ routes/ utils/ public/
  logs/
node-red/
Integração
Dados planos em processed-flat com campos nomeados (sensibilidadeX, tensões, contadores, sinais, etc.) para persistência direta em MySQL.

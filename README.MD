# AGATA Ingestão (Docker Stack)

Recepção de telemetria do Dispositivo Agata com: 
        - Nginx (proxy); 
        - Node.js (API/WebSocket)
        - Redis (cache/pub-sub). 

Recebe payload criptografado > descriptografa (AES-128-ECB) > salva os dados brutos e versão normalizada (plana) para integração com banco relacional.

## Componentes
- Nginx: proxy reverso.
- Node.js (Express + Socket.IO): API `/agata`, broadcast de eventos.
- Redis: cache/pub-sub.
- Node-RED (opcional): prototipação da equipe da Engenharia da Onix.

## Fluxo de dados
1) POST `/agata`: `"<serial:6><payload:base64>"`.
2) Descriptografia em `utils/crypto.js` (AES-128-ECB) (padrão do device).
3) Persistência:
   - Bruto descriptografado: `nodejs/logs/raw-data/*.json`.
   - Legado agregado: `nodejs/logs/processed/*.json`.
   - Normalizado (plano): `nodejs/logs/processed-flat/*.json`.
4) Normalização: `utils/agataParser.js` -> formato plano, adequado para MySQL.

## Rotas
- `POST /agata` — ingestão.
- `GET /stats` — métricas básicas.
- `GET /history/:serial` — histórico (legado).
- `GET /summary` — resumo por device.

## Execução 
- API: `http://localhost:3000`

## Segurança/Privacidade
- Não versionar `nodejs/logs/**`, `redis-data/**`, `node-red-data/**`.
- Redis sem autenticação: usado apenas em desenvolvimento.
- Criptografia ECB é padrão do device

## Estrutura
```
docker-compose.yml
nginx/
nodejs/
  controllers/ middleware/ routes/ utils/ public/
  logs/ (não versionado)
node-red/
```

## Integração
- Dados planos em `processed-flat` com campos nomeados (sensibilidadeX, tensões, contadores, sinais, etc.) para persistência direta em MySQL.
FROM node:20-alpine

WORKDIR /app

# Copiar manifestos
COPY package*.json ./

# Instalar dependências - reduzir tamanho
RUN npm install --omit=dev

# Copiar código
COPY . .

ENV NODE_ENV=production
ENV PORT=3000

EXPOSE 3000

USER node

CMD ["node", "server.js"]


#  * em package.json *

# "private": true: boa pratica 
# "main": "server.js": Arquivo principal de entrada do módulo (onde o código começa).

# "dev": "nodemon server.js": reinicia automaticamente com mudanças
# "dependencies": Pacotes necessários para o funcionamento do projeto (instalados com --omit=dev no Docker).
# "cors": "2.8.5": permitir requisições CORS.
# "express": "4.18.2": Framework web para Node.js.
# "helmet": "7.0.0": Middle de segurança para HTTP.
# "morgan": "1.10.0": Middle de log para  HTTP.
# "redis": "4.6.13": Cliente para Redis (banco de dados em memória).
# "socket.io": "^4.7.2": Biblioteca para WebSockets.
# "winston": "3.11.0": Logger flexível para Node.js.
# "winston-daily-rotate-file": "^5.0.0": Extensão para rotacionar logs diários.
# "devDependencies": Pacotes em questao ao --omit=dev do Dockerfile
# "nodemon": "3.0.2": Ferramenta para reiniciar o servidor automaticamente durante dev.
# "engines": Especifica versão mínima de ferramentas.
# "node": ">=20.0.0": 
FROM node:20-alpine

WORKDIR /app

# Dependências do sistema (se precisar no futuro)
RUN apk add --no-cache bash wget

# Copiar manifestos
COPY package*.json ./

# Instalar dependências (produção)
RUN npm install --omit=dev

# Copiar código
COPY . .

# Pastas de log
RUN mkdir -p /app/logs/raw-data /app/logs/text-logs && \
    chown -R node:node /app/logs

ENV NODE_ENV=production
ENV PORT=3000

EXPOSE 3000

USER node

CMD ["node", "server.js"]

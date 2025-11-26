const { Router } = require('express');
const ctrl = require('../controllers/agataController');
const { sanitizePayload } = require('../middleware/bodyValidator');

const router = Router();

// Recepção dos dados do device
router.post('/agata', sanitizePayload, ctrl.ingest);
router.post('/agata/command', ctrl.injectTestCommand); // teste manual de comando

// Último registro recebido
router.get('/node-red/agata-latest', ctrl.latest);

// Formato legado
router.get('/agata-data/legacy-format', ctrl.legacy);

// Histórico de um device específico
router.get('/agata/history/:serial', ctrl.history);
router.get('/agata/history', ctrl.history);

// Resumo de todos os devices
router.get('/agata/summary', ctrl.summary);

// Estatísticas do servidor
router.get('/agata/stats', ctrl.stats);

module.exports = router;
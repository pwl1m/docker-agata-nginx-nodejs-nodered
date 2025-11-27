const { Router } = require('express');
const ctrl = require('../controllers/agataController');
const { validateAgataBody } = require('../middleware/bodyValidator'); 

const router = Router();

// Recepção dos dados do device
router.post('/agata', validateAgataBody, ctrl.ingest); // ← Usar validateAgataBody
router.post('/agata/command', ctrl.injectTestCommand);

// Último registro recebido
router.get('/node-red/agata-latest', ctrl.latest);

// Formato legado
router.get('/agata-data/legacy-format', ctrl.legacy);

// Estatísticas do servidor
router.get('/agata/stats', ctrl.stats);

module.exports = router;
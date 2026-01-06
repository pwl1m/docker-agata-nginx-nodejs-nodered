-- Dispositivos cadastrados
CREATE TABLE devices (
    serial VARCHAR(6) PRIMARY KEY,
    primeira_comunicacao DATETIME NOT NULL,
    ultima_comunicacao DATETIME NOT NULL,
    total_comunicacoes INT UNSIGNED DEFAULT 0,
    ip_origem VARCHAR(45),
    ativo BOOLEAN DEFAULT TRUE,
    INDEX idx_ultima (ultima_comunicacao),
    INDEX idx_ativo (ativo)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- Telemetria principal (monit)
CREATE TABLE telemetria (
    id BIGINT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    serial VARCHAR(6) NOT NULL,
    data_registro DATETIME NOT NULL,
    
    -- Sensibilidades (1-100)
    sens1 TINYINT UNSIGNED,
    sens2 TINYINT UNSIGNED,
    sens3 TINYINT UNSIGNED,
    sens4 TINYINT UNSIGNED,
    sens5 TINYINT UNSIGNED,
    sens6 TINYINT UNSIGNED,
    sens7 TINYINT UNSIGNED,
    sens8 TINYINT UNSIGNED,
    
    -- Detecção
    selecao_metais TINYINT UNSIGNED,    -- (1-100)
    filtro_ruido TINYINT UNSIGNED,       -- (0-15)
    
    -- Tensões
    tensao_5v SMALLINT UNSIGNED,         -- décimos
    tensao_15v_pos SMALLINT UNSIGNED,
    tensao_15v_neg SMALLINT UNSIGNED,
    tensao_ac SMALLINT UNSIGNED,         -- rede
    tensao_bateria SMALLINT UNSIGNED,
    tensao_fonte SMALLINT UNSIGNED,
    
    -- Anulação de áreas (0/1)
    anula1 TINYINT UNSIGNED,
    anula2 TINYINT UNSIGNED,
    anula3 TINYINT UNSIGNED,
    anula4 TINYINT UNSIGNED,
    anula5 TINYINT UNSIGNED,
    anula6 TINYINT UNSIGNED,
    anula7 TINYINT UNSIGNED,
    anula8 TINYINT UNSIGNED,
    
    -- Contadores
    cont_entradas INT UNSIGNED,          -- reseta diário
    cont_saidas INT UNSIGNED,            -- reseta diário
    cont_bloqueios INT UNSIGNED,
    cont_desbloqueios INT UNSIGNED,
    
    -- Timestamp do device
    timestamp_device INT UNSIGNED,
    
    -- Configurações
    sinal_rele TINYINT UNSIGNED,         -- (1-2)
    sinal_trava TINYINT UNSIGNED,        -- (1-3)
    tempo_pulso_rele TINYINT UNSIGNED,   -- (1-150)
    tempo_pulso_trava TINYINT UNSIGNED,  -- (1-150)
    modo_travamento TINYINT UNSIGNED,    -- (1-2)
    volume_buzzer TINYINT UNSIGNED,      -- (0-10)
    canal TINYINT UNSIGNED,              -- (1-25)
    status_pgdm TINYINT UNSIGNED,        -- (0/1) aberta/fechada
    
    FOREIGN KEY (serial) REFERENCES devices(serial),
    INDEX idx_serial_data (serial, data_registro DESC)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- Eventos (passagens, detecções, bloqueios)
CREATE TABLE eventos (
    id BIGINT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    serial VARCHAR(6) NOT NULL,
    data_registro DATETIME NOT NULL,
    
    tipo CHAR(1) NOT NULL,              -- B=Bloqueio, D=Desbloqueio/Detecção, P=Painel, C=Controle
    dispositivo CHAR(1),                 -- Dispositivo que originou
    timestamp_evento INT UNSIGNED,       -- Unix timestamp do device
    
    FOREIGN KEY (serial) REFERENCES devices(serial),
    INDEX idx_serial_data (serial, data_registro DESC),
    INDEX idx_tipo (tipo)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- Auditoria (alterações de configuração)
CREATE TABLE auditoria (
    id BIGINT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    serial VARCHAR(6) NOT NULL,
    data_registro DATETIME NOT NULL,
    
    codigo_param SMALLINT UNSIGNED,      -- (1-98) código do parâmetro
    valor_antigo VARCHAR(20),
    valor_novo VARCHAR(20),
    operador CHAR(1),                    -- U=Usuario, G=Gerente, T=Técnico, D=Detector
    dispositivo CHAR(1),                 -- P=Painel, C=Controle, S=AssetCare, E=PaP, R=USB, B=Bateria
    timestamp_alteracao INT UNSIGNED,    -- Unix timestamp
    
    FOREIGN KEY (serial) REFERENCES devices(serial),
    INDEX idx_serial_data (serial, data_registro DESC),
    INDEX idx_param (codigo_param)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- Erros do hardware
CREATE TABLE erros (
    id BIGINT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    serial VARCHAR(6) NOT NULL,
    data_registro DATETIME NOT NULL,
    
    tipo_erro CHAR(1),                   -- A=Ágata, etc
    codigo_erro VARCHAR(10),             -- Código/valor
    
    FOREIGN KEY (serial) REFERENCES devices(serial),
    INDEX idx_serial_data (serial, data_registro DESC),
    INDEX idx_tipo (tipo_erro)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- Registro de alterações feitas pelo front-end (ANTES de enviar ao device)
CREATE TABLE alteracoes_usuario (
    id BIGINT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    serial VARCHAR(6) NOT NULL,
    usuario_id INT UNSIGNED NOT NULL,           -- ID do usuário no front-end
    data_solicitacao DATETIME NOT NULL,         -- Quando o usuário clicou
    data_confirmacao DATETIME DEFAULT NULL,     -- Quando o device confirmou (se aplicável)
    status ENUM('pendente', 'enviado', 'confirmado', 'falha') DEFAULT 'pendente',
    
    -- Detalhes da alteração
    parametros_alterados JSON NOT NULL,         -- { "sens1": { "de": 50, "para": 75 }, ... }
    comando_enviado JSON,                        -- O array completo enviado ao device
    
    -- Metadados
    ip_origem VARCHAR(45),
    user_agent VARCHAR(255),
    
    INDEX idx_serial (serial),
    INDEX idx_usuario (usuario_id),
    INDEX idx_status (status),
    INDEX idx_data (data_solicitacao DESC)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
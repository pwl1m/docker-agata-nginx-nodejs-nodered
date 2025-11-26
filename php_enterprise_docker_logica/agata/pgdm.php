<?php

ini_set('display_errors', 0);
error_reporting(false);

include_once  "../app/database/conexao.php";
include_once  "utils.php";

//define
$debug = false;

// Log type
// config -1 = sem comunicação
// config  0 = padrão, sem alterações
// config  1 = alterar parâmetro ViewCare -> agata
// config  2 = comando de abertura/fechamento ViewCare -> agata

try {

    // force json type response
    header('Content-Type: application/json; charset=utf-8');

    // default
    $dados = "";

    // get payload
    $info = file_get_contents('php://input');

    // validate payload / update log
    if (!isset($info) || is_null($info) || $info == '') {

        $retornoJson = json_encode([
            "code" => 200,
            "config" => -1,
            "data" => ($info) ? $info : "",
        ]) . "!!!!!!";
        echo $retornoJson;

        // $dadoLogJson = json_decode($retornoJson, true);

        $sql = "INSERT INTO logs (id, log, tipo, retorno) VALUES (null, '" . $info . "',-4, config:-1)";
        $conexao->query($sql);

        die($retornoJson);
    }

    // decode payloaded data
    if (!$debug) {
        $key = substr($info, 0, 6);
        $criptografia = substr($info, 6, strlen($info));
        $info = descriptografar($key, $criptografia);
        $info = preg_replace('/[\x00-\x1F\x80-\xFF]/', '', $info);
        $json = json_decode($info);
    }

    // register validation success log
    $sql = "INSERT INTO logs (id, log, tipo) VALUES (null, '" . $info . "',99)";
    $conexao->query($sql);
    $idLog = $conexao->insert_id;

    if (isset($json)) {
        $registro = $json->blc;
    }

    if ($registro == '#ea') {

        $serial = $json->srl;

        $sensibilidade1 = $json->monit[0];
        $sensibilidade2 = $json->monit[1];
        $sensibilidade3 = $json->monit[2];
        $sensibilidade4 = $json->monit[3];
        $sensibilidade5 = $json->monit[4];
        $sensibilidade6 = $json->monit[5];
        $sensibilidade7 = $json->monit[6];
        $sensibilidade8 = $json->monit[7];

        $metal = $json->monit[8];
        $ruido = $json->monit[9];
        $tensao5 = $json->monit[10];
        $tensaoN15 = $json->monit[11];
        $tensaoP15 = $json->monit[12];
        $tensaoVac = $json->monit[13];
        $tensaoBat = $json->monit[14];
        //$tensaoFonte = $json->monit[15];

        $anual1 = $json->monit[19];
        $anual2 = $json->monit[17];
        $anual3 = $json->monit[18];
        $anual4 = $json->monit[19];
        $anual5 = $json->monit[20];
        $anual6 = $json->monit[21];
        $anual7 = $json->monit[22];
        $anual8 = $json->monit[23];

        $contadorEntradas = $json->monit[24];
        $contadorSaidas = $json->monit[25];
        $contadorBloqueios = $json->monit[26];
        $contadorDesbloqueios = $json->monit[27];

        $tempo = $json->monit[28];
        $sinalRele = $json->monit[29];
        $sinalTrava = $json->monit[30];
        $pulsoRele = $json->monit[31];
        $pulsoTrav = $json->monit[32];
        $travamento = $json->monit[33];
        $volBuzzer = $json->monit[34];
        $volVoz = $json->monit[35];
        $canal = $json->monit[36];
        $status_porta = $json->monit[37];

        $sql = "INSERT INTO tb_monitoramento_pgdm (id, data_registro, sensibilidade1, sensibilidade2, sensibilidade3, 
        sensibilidade4, sensibilidade5, sensibilidade6, sensibilidade7, sensibilidade8, metais, ruidos, tensaocinco, 
        tensao_quinze, tensao_menos_quinze, tensao_rede, tensao_bateria1, tensao_bateria2, anula1, anula2, anula3, anula4, 
        anula5, anula6, anula7, anula8, cont_entrada1, cont_entrada2, cont_entrada3, cont_entrada4, cont_saida1, 
        cont_saida2, cont_saida3, cont_saida4, cont_bloqueio1,cont_bloqueio2, cont_bloqueio3, cont_bloqueio4, 
        cont_des_bloqueio1, cont_des_bloqueio2, cont_des_bloqueio3, cont_des_bloqueio4, cal_dia, cal_minuto, cal_ano1, cal_ano2, 
        sinal_rele, sinal_trava, sinal_pulso_rele, sinal_pulso_trava, modo_travamento, volume_buzzer, volume_voz, canal, serial, id_sincronizador, aberto) 
        VALUES (null, now(), 
        " . $sensibilidade1 . "," . $sensibilidade2 . "," . $sensibilidade3 . "," . $sensibilidade4 . "," . $sensibilidade5 . "," .
            $sensibilidade6 . "," . $sensibilidade7 . "," . $sensibilidade8 . "," . $metal . "," . $ruido . "," . $tensao5 . ","
            . $tensaoN15 . "," . $tensaoP15 . "," . $tensaoVac . "," . $tensaoBat . "," . 0 . "," . $anual1 . ","
            . $anual2 . "," . $anual3 . "," . $anual4 . "," . $anual5 . "," . $anual6 . "," . $anual7 . "," . $anual8 . "," .
            $contadorEntradas . "," . 0 . "," . 0 . "," . 0 . "," .
            $contadorSaidas . "," . 0 . "," . 0 . "," . 0 . "," .
            $contadorBloqueios . "," . 0 . "," . 0 . "," . 0 . "," .
            $contadorDesbloqueios . "," . 0 . "," . 0 . "," . 0 . "," .
            0 . "," . 0 . "," . 0 . "," . 0 . "," . $sinalRele . "," . $sinalTrava . "," . $pulsoRele . "," .
            $pulsoTrav . "," . $travamento . "," . $volBuzzer . ", " .  $volVoz . ", " .  $canal . ", '" . $serial . "', -1, " . $status_porta . ")";
        $conexao->query($sql);

        // register auditing
        $auditorias = $json->audit;
        if (!empty($auditorias)) {

            try {
                $campo = $auditorias[0];
                $valorAntigo = $auditorias[1];
                $valorNovo = $auditorias[2];
                $operador = $auditorias[3];
                $dispositivo = $auditorias[4];
                $timestamp_auditoria = $auditorias[5];

                $nome_usuario = "Alterado pelo Software";
                $data_hora_formatada_mysql = '0000-00-00 00:00:00';

                if ($operador == 1 && $dispositivo == 'S') {

                    $sqlAgata = "SELECT id_usuario FROM tb_alteracao_pgdm WHERE serial = $serial ORDER BY id DESC";
                    $resultAgata = $conexao->query($sqlAgata);
                    if ($resultAgata && $resultAgata->num_rows > 0) {
                        $rowAgata = $resultAgata->fetch_assoc();
                        $nome_usuario = $rowAgata["id_usuario"];
                    }
                }
                if ($timestamp_auditoria !== '/' && $timestamp_auditoria !== null && $timestamp_auditoria !== '') {
                    $currentTime = DateTime::createFromFormat('U', $timestamp_auditoria);

                    if ($currentTime) {
                        $data_hora_formatada_mysql = $currentTime->format('Y-m-d H:i:s');
                    }
                }

                $sql = "INSERT INTO tb_monitoramento_pgdm_auditoria_detalhes (id, id_evento, campo, valor_antigo, valor_novo, operador, dispositivo, data_hora, serial, id_usuario ) VALUES (null, " . -1 . ", " . $campo . ", " . $valorAntigo . ", " . $valorNovo . ", '" . $operador . "', '" . $dispositivo . "', '" . $data_hora_formatada_mysql . "', '" . $serial . "', " . $nome_usuario . ")";
                $conexao->query($sql);
            } catch (Exception $e) {
                // throw $th;
            }
        }

        // register event
        $eventos = $json->event;
        if (!empty($eventos)) {

            try {
                $tipoBloqueio = $eventos[0];
                $tipoPainel = $eventos[1];
                $timestamp_evento = $eventos[2];

                $data_hora_formatada_mysql = '0000-00-00 00:00:00';

                if ($timestamp_evento !== '/' && $timestamp_evento !== null && $timestamp_evento !== '') {
                    $currentTime = DateTime::createFromFormat('U', $timestamp_evento);

                    if ($currentTime) {
                        $data_hora_formatada_mysql = $currentTime->format('Y-m-d H:i:s');
                    }
                }

                $sql = "INSERT INTO tb_monitoramento_pgdm_eventos_detalhes (id, id_evento, bloqueio, painel, data_hora, serial ) VALUES (null, " . -1 . ", '" . $tipoBloqueio . "','" . $tipoPainel . "','" . $data_hora_formatada_mysql . "','" . $serial . "')";
                $conexao->query($sql);
            } catch (Exception $e) {
                // throw $th;
            }
        }

        // register errors
        $errosComunicacao = $json->erros;
        if (!empty($errosComunicacao)) {

            try {
                $erroa = $errosComunicacao[0];
                $errob = $errosComunicacao[1];

                $sql = "INSERT INTO tb_monitoramento_pgdm_erros (id, erroa, errob, serial) VALUES (null, '" . $erroa . "','" . $errob . "','" . $serial . "')";
                $conexao->query($sql);
            } catch (Exception $e) {
                // throw $th;
            }
        }

        //get system updates
        $sql = "SELECT * FROM tb_alteracao_pgdm WHERE situacao IN (1,3) AND serial = '" . $serial . "' ORDER BY id DESC LIMIT 1";

        $result = $conexao->query($sql);

        if ($result->num_rows > 0) {

            foreach ($result as $row) {

                $sensibilidade1 = $row["sensibilidade1"];
                $sensibilidade2 = $row["sensibilidade2"];
                $sensibilidade3 = $row["sensibilidade3"];
                $sensibilidade4 = $row["sensibilidade4"];
                $sensibilidade5 = $row["sensibilidade5"];
                $sensibilidade6 = $row["sensibilidade6"];
                $sensibilidade7 = $row["sensibilidade7"];
                $sensibilidade8 = $row["sensibilidade8"];

                $anula1 = $row["anula1"];
                $anula2 = $row["anula2"];
                $anula3 = $row["anula3"];
                $anula4 = $row["anula4"];
                $anula5 = $row["anula5"];
                $anula6 = $row["anula6"];
                $anula7 = $row["anula7"];
                $anula8 = $row["anula8"];

                $canal = $row["canal"];
                $filtroRuido = $row["ruidos"];
                $sinalRele = $row["sinal_rele"];
                $pulsoRele = $row["sinal_pulso_rele"];
                $sinalTrava = $row["sinal_trava"];
                $pulsoTrava = $row["sinal_pulso_trava"];
                $travamento = $row["modo_travamento"];
                $metais = $row["metais"];
                $volumeVoz = $row["volume_voz"];
                $volumeBuzzer = $row["volume_buzzer"];
                $tomBuzzer = $row["volume_buzzer"];
                $idUsuario = $row["id_usuario"];
                $status_alteracao = intval($row['aberto']);
                $situacao = intval($row['situacao']);
                $timestamp_atual = time();
                $status_codigo = "";

                if ($situacao == 1) {
                    $json = "{\"alteracao\":[" . $sensibilidade1 . "," . $sensibilidade2 . "," . $sensibilidade3 . "," . $sensibilidade4 . "," . $sensibilidade5 . "," . $sensibilidade6 . "," . $sensibilidade7 . "," . $sensibilidade8 . "," . $anula1 . "," . $anula2 . "," . $anula3 . "," . $anula4 . "," . $anula5 . "," . $anula6 . "," . $anula7 . "," . $anula8 . "," . $canal . "," . $filtroRuido . "," . $sinalRele . "," . $pulsoRele . "," . $sinalTrava . "," . $pulsoTrava . "," . $travamento . "," . $metais . "," . $volumeVoz . "," . $volumeBuzzer . "," . $tomBuzzer . "," . $timestamp_atual . "," . $idUsuario . "]}";

                    $info_altera_parametro = criptografar($serial, $json);

                    $retornoJson = json_encode([
                        "code" => 200,
                        "config" => 1,
                        "data" => $info_altera_parametro,
                    ]);
                } else if ($situacao == 3) {

                    // Status Porta/Sistema: 
                    // 0 = aberto
                    // 1 = fechado

                    if ($status_porta == 1 && $status_alteracao == 0) {
                        $status_codigo = "A";
                    } else if ($status_porta == 0 && $status_alteracao == 1) {
                        $status_codigo = "F";
                    }

                    $json = "{\"comando\":" . $status_codigo . "}";

                    $info_aberto_fechado = criptografar($serial, $json);

                    $retornoJson = json_encode([
                        "code" => 200,
                        "config" => 2,
                        "data" => $info_aberto_fechado,
                    ]);
                }

                echo $retornoJson;

                //$dadoLogJson = json_decode($retornoJson, true);

                //confirm update in log
                $sql = "UPDATE logs SET retorno = 'config:1' WHERE id = {$idLog}";
                $conexao->query($sql);

                //confirm update in system
                $sql = "UPDATE tb_alteracao_pgdm SET situacao = 2, dt_atualizacao = now() WHERE id = " . $row["id"];
                $conexao->query($sql);
            }
        } else {

            $retornoJson = json_encode([
                "code" => 200,
                "config" => 0,
                "data" => [],
            ]);
            echo $retornoJson;

            $sql = "UPDATE logs SET retorno = 'config:0' WHERE id = {$idLog}";
            $conexao->query($sql);
        }
    }
} catch (Exception $e) {

    $log = fopen("log_erro.txt", "w") or die("Unable to open file!");
    fwrite($log, $e->getMessage());
    fclose($log);
}

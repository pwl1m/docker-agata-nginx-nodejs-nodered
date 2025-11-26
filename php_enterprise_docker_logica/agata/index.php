<?php
header('Content-Type: application/json; charset=utf-8');

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);


include "../../app/database/conexao.php";
include "utils.php";

try {
    $planob = true;
    $dados = "";
    $info = file_get_contents('php://input');
    #$info = "000004YU9sD1K1+4eG9xWkrVF/XjVN0Jut8YwpzZ7z3RXoyN8ZivqwLKz8txndS0vsccnGCka5mA0ZJO4yC46sHltkN6WKJBbLIGLzB+w7MNFUhL3hMrdSn3FAQzmfzE3ImCuKXh0FrW7mg/km3ZnsL5odfXC+1pTtLWI7iLQMWJDGkumacF4gFVsdjO8CeKJK4a7JTvmxmfo+kBC8NnBxXJPYn/YGR6QdYIHD1OOZSWRpif5CIxQtVUCu3Ct3DGBw5FVHD29xeyNWrWcWNZ/2HhtySJf8yfwYl9e/2w5uX9PVjta5adFUq/65aZV+Px48wfJU";

    $sql = "INSERT INTO logs (id, log, tipo) VALUES (null, '{$info}', -2)";
    $conexao->query($sql);

    $idLog = $conexao->insert_id;

    if (!isset($info) || is_null($info) || $info == '') {

        $retornoJson = json_encode([
            "code" => 200,
            "config" => -1,
            "data" => $info,
        ]) . "!!!!!!";
        echo $retornoJson;

        $dadoLogJson = json_decode($retornoJson, true);

        $sql = "UPDATE logs SET retorno = 'config:-1' WHERE id = {$idLog}";
        $conexao->query($sql);
        exit;
    }



    $key = substr($info, 0, 6);
    $criptografia = substr($info, 6, strlen($info));
    $info = descriptografar($key, $criptografia);

    if ($planob) {
        $info = preg_replace('/[\x00-\x1F\x80-\xFF]/', '', $info);
    }
    $json = json_decode($info);

    #$sql = "INSERT INTO logs (id, log, tipo) VALUES (null, '" . $info . "',99)";
    #$conexao->query($sql);

    #$idLog = $conexao->insert_id;

    $registro = "xx";
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


        $sql = "INSERT INTO tb_monitoramento_pgdm (id, data_registro, sensibilidade1, sensibilidade2, sensibilidade3, 
        sensibilidade4, sensibilidade5, sensibilidade6, sensibilidade7, sensibilidade8, metais, ruidos, tensaocinco, 
        tensao_quinze, tensao_menos_quinze, tensao_rede, tensao_bateria1, tensao_bateria2, anula1, anula2, anula3, anula4, 
        anula5, anula6, anula7, anula8, cont_entrada1, cont_entrada2, cont_entrada3, cont_entrada4, cont_saida1, 
        cont_saida2, cont_saida3, cont_saida4, cont_bloqueio1,cont_bloqueio2, cont_bloqueio3, cont_bloqueio4, 
        cont_des_bloqueio1, cont_des_bloqueio2, cont_des_bloqueio3, cont_des_bloqueio4, cal_dia, cal_minuto, cal_ano1, cal_ano2, 
        sinal_rele, sinal_trava, sinal_pulso_rele, sinal_pulso_trava, modo_travamento, volume_buzzer, volume_voz, canal, serial, id_sincronizador ) 
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
            $pulsoTrav . "," . $travamento . "," . $volBuzzer . ", " .  $volVoz . ", " .  $canal . ", '" . $serial . "', -1)";
        $conexao->query($sql);


        $auditorias = $json->audit;
        if (!$planob && !empty($auditorias)) {

            try {

                $campo = $auditorias[0];
                $valorAntigo = $auditorias[1];
                $valorNovo = $auditorias[2];
                $operador = $auditorias[3];
                $dispositivo = $auditorias[4];
                $idUsuarioOac = 2;

                if ($auditorias[5] == '/') {
                    $currentTime = DateTime::createFromFormat('U', $auditorias[5]);

                    $hora = $currentTime->format('H');
                    $minuto = $currentTime->format('i');
                    $dia = $currentTime->format('d');
                    $mes = $currentTime->format('m');
                    $ano = $currentTime->format('Y');

                    $data_hora = ($dia . '/' . $mes . '/' . $ano . ' ' . $hora . ':' . $minuto);

                    $sql = "INSERT INTO tb_monitoramento_pgdm_auditoria_detalhes (id, id_evento, campo, valor_antigo, valor_novo, operador, dispositivo, data_hora, serial ) VALUES (null, " . -1 . ", " . $campo . ", " . $valorAntigo . ", " . $valorNovo . ", '" . $operador . "', '" . $dispositivo . "', STR_TO_DATE('" . $data_hora . "', '%d/%m/%Y %H:%i'), '" . $serial . "')";
                    $conexao->query($sql);
                }
            } catch (Exception $e) {
            }
        }


        $eventos = $json->event;
        if (!empty($eventos)) {

            try {

                $tipoBloqueio = $eventos[0];
                $tipoPainel = $eventos[1];

                $currentTime = DateTime::createFromFormat('U', $eventos[2]);

                $hora = $currentTime->format('H');
                $minuto = $currentTime->format('i');
                $dia = $currentTime->format('d');
                $mes = $currentTime->format('m');
                $ano = $currentTime->format('Y');


                $data_hora = ($dia . '/' . $mes . '/' . $ano . ' ' . $hora . ':' . $minuto);

                $sql = "INSERT INTO tb_monitoramento_pgdm_eventos_detalhes (id, id_evento, bloqueio, painel, data_hora, serial ) VALUES (null, " . -1 . ", '" . $tipoBloqueio . "','" . $tipoPainel . "',STR_TO_DATE('" . $data_hora . "', '%d/%m/%Y %H:%i'), '" . $serial . "')";
                $conexao->query($sql);
            } catch (Exception $e) {
                //throw $th;
            }
        }


        try {
            $errosComunicacao = $json->erros;
            if (!empty($errosComunicacao)) {

                $erroa = $errosComunicacao[0];
                $errob = $errosComunicacao[1];

                $sql = "INSERT INTO tb_monitoramento_pgdm_erros (id, erroa, errob, serial) VALUES (null, '" . $erroa . "','" . $errob . "','" . $serial . "')";
                $conexao->query($sql);
            }
        } catch (Exception $e) {
            //throw $th;
        }


        $sql = "SELECT * FROM tb_alteracao_pgdm a where situacao IN (1,3) and serial = '" . $serial . "' order by id desc limit 1";

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

                $json = "{\"alteracao\":[" . $sensibilidade1 . "," . $sensibilidade2 . "," . $sensibilidade3 . "," . $sensibilidade4 . "," . $sensibilidade5 . "," . $sensibilidade6 . "," . $sensibilidade7 . "," . $sensibilidade8 . "," . $anula1 . "," . $anula2 . "," . $anula3 . "," . $anula4 . "," . $anula5 . "," . $anula6 . "," . $anula7 . "," . $anula8 . "," . $canal . "," . $filtroRuido . "," . $sinalRele . "," . $pulsoRele . "," . $sinalTrava . "," . $pulsoTrava . "," . $travamento . "," . $metais . "," . $volumeVoz . "," . $volumeBuzzer . "," . $tomBuzzer . ",0]}";
                $info = criptografar($serial, $json);



                $retornoJson = json_encode([
                    "code" => 200,
                    "config" => 1,
                    "data" => $info,
                ]) . "!!!!!!";
                echo $retornoJson;

                $dadoLogJson = json_decode($retornoJson, true);

                $sql = "UPDATE logs SET retorno = 'config:1' WHERE id = {$idLog}";
                $conexao->query($sql);

                $sql = "update tb_alteracao_pgdm set situacao = 2, dt_atualizacao = now() where id = " . $row["id"];
                $conexao->query($sql);
            }
        } else {

            $retornoJson = json_encode([
                "code" => 200,
                "config" => 0,
                "data" => $info,
            ]) . "!!!!!!";
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

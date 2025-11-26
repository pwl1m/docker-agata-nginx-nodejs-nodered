<?php

header('Content-Type: application/json; charset=utf-8');
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

include_once "utils.php";
include "../app/database/conexao.php";

if ($_POST["tipo"] === "acessoRemotoAgata") {
    if (!isset($_POST["tipo"]) || $_POST["tipo"] !== "acessoRemotoAgata") {
        echo json_encode(["code" => 400, "error" => "Tipo inválido"]);
        return;
    }

    $serial = $_POST["id"] ?? '';

    if (empty($serial)) {
        echo json_encode(["code" => 400, "error" => "ID inválido"]);
        return;
    }

    // Buscar o último estado de "aberto" no banco
    $sql = "SELECT aberto FROM tb_monitoramento_pgdm WHERE serial = ? ORDER BY id DESC LIMIT 1";
    $stmt = $conexao->prepare($sql);
    $stmt->bind_param("s", $serial);
    $stmt->execute();
    $result = $stmt->get_result();
    $row = $result->fetch_assoc();
    $stmt->close();

    // Porta/Sistema: 0 = aberto, 1 = fechado
    $abrir_fechar = ($row && $row['aberto'] == 1) ? 0 : 1;

    // Limpa fila de comandos
    $sqlUltimoUpdate = "UPDATE tb_alteracao_pgdm SET situacao = -1 WHERE serial = '" . $serial . "' AND situacao IN (1,3)";
    $result = $conexao->query($sqlUltimoUpdate);

    // Criar novo registro no banco atualizando abertura
    $sql = "INSERT INTO tb_alteracao_pgdm (
            sensibilidade1, sensibilidade2, sensibilidade3, sensibilidade4,
            sensibilidade5, sensibilidade6, sensibilidade7, sensibilidade8, metais,ruidos,
            anula1, anula2, anula3, anula4, anula5, anula6, anula7, anula8,
            sinal_rele, sinal_trava, sinal_pulso_rele, sinal_pulso_trava, modo_travamento,
            volume_buzzer, volume_voz, canal, serial, situacao, usuario, id_usuario,
            aberto 
        )
        SELECT
            T.sensibilidade1, T.sensibilidade2, T.sensibilidade3, T.sensibilidade4,
            T.sensibilidade5, T.sensibilidade6, T.sensibilidade7, T.sensibilidade8, T.metais, T.ruidos,
            T.anula1, T.anula2, T.anula3, T.anula4, T.anula5, T.anula6, T.anula7, T.anula8,
             T.sinal_rele, T.sinal_trava, T.sinal_pulso_rele, T.sinal_pulso_trava, T.modo_travamento,
            T.volume_buzzer, T.volume_voz, T.canal, T.serial, 3, T.usuario, T.id_usuario,
            ?
        FROM tb_alteracao_pgdm T
        WHERE T.serial = ?
        ORDER BY T.id DESC
        LIMIT 1";

    $stmt = $conexao->prepare($sql);
    $stmt->bind_param("is", $abrir_fechar, $serial);
    $stmt->execute();

    if ($stmt->affected_rows > 0) {
        echo json_encode([
            "code" => 200,
            "estadoPorta" => $abrir_fechar
        ]);
    } else {
        echo json_encode([
            "code" => 500,
            "error" => "Falha ao atualizar banco de dados"
        ]);
    }
    $stmt->close();
}

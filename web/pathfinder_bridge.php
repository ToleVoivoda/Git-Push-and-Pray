<?php
header('Content-Type: application/json');

$data = json_decode(file_get_contents('php://input'), true);
$start = escapeshellarg($data['start']);
$end = escapeshellarg($data['end']);
$exePath = __DIR__ . '\graph_engine.exe';

function runEngine($path, $s, $e, $safety) {
    // Force path refresh
    shell_exec("$path $s $e " . escapeshellarg($safety) . " 2>&1");
    return file_get_contents('dijkstra_path.json');
}

// 1. Safe Path (Safety 0.7)
$safePath = json_decode(runEngine($exePath, $start, $end, "0.99"), true);

// 2. Shortest Path (Safety 0.0)
$shortestPath = json_decode(runEngine($exePath, $start, $end, "0.0"), true);

echo json_encode([
    "safe" => $safePath,
    "shortest" => $shortestPath
]);
<?php
header('Content-Type: application/json');

$data = json_decode(file_get_contents('php://input'), true);
$start = escapeshellarg($data['start']);
$end = escapeshellarg($data['end']);
$safety = escapeshellarg("0.7");

$exePath = __DIR__ . '\graph_engine.exe';
$command = "$exePath $start $end $safety 2>&1"; // 2>&1 redirects error messages to the output

$output = shell_exec($command);

// If $output is empty, the engine failed to run or crashed
if (empty($output)) {
    echo json_encode(["error" => "Engine returned no output", "debug" => "Check file permissions or path"]);
} else {
    $filePath = 'dijkstra_path.json';
if (!file_exists($filePath)) {
    http_response_code(404);
    echo json_encode(["error" => "File not found"]);
    exit;
}
echo file_get_contents($filePath);
}
?>
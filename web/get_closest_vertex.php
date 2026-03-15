<?php
header('Content-Type: application/json');
header('Access-Control-Allow-Origin: *');

$userLat = isset($_GET['lat']) ? (float)$_GET['lat'] : null;
$userLon = isset($_GET['lng']) ? (float)$_GET['lng'] : null;

if ($userLat === null || $userLon === null) {
    echo json_encode(["error" => "Missing coordinates"]);
    exit;
}

$filePath = 'verts_data.json';
if (!file_exists($filePath)) {
    http_response_code(404);
    echo json_encode(["error" => "File not found"]);
    exit;
}

$data = json_decode(file_get_contents($filePath), true);
$verts = $data['verts'];

$nearestVertex = null;
$minDistance = 1;

foreach ($verts as $v) {
    $dist = sqrt(pow($v['lat'] - $userLat, 2) + pow($v['lon'] - $userLon, 2));
    
    if ($dist < $minDistance) {
        $minDistance = $dist;
        $nearestVertex = $v;
    }
}

echo json_encode($nearestVertex);
<?php
header('Content-Type: application/json');
include "db_connection.php";

// Get the JSON body from the request
$data = json_decode(file_get_contents('php://input'), true);
$ids = $data['ids'] ?? [];

if (empty($ids)) {
    echo json_encode([]);
    exit;
}

// 1. Create placeholders for the IN clause: ?,?,?
$placeholders = implode(',', array_fill(0, count($ids), '?'));

// 2. Prepare and execute the query
$stmt = $con->prepare("SELECT id, lat, lon FROM vertex WHERE id IN ($placeholders)");
$stmt->execute($ids);

// 3. Re-index the result so the key is the vertex_idx for easy JS access
$results = [];
while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
    $results[$row['id']] = [
        'lat' => (float)$row['lat'],
        'lon' => (float)$row['lon']
    ];
}

echo json_encode($results);
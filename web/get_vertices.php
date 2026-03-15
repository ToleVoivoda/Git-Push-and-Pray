<?php
header('Content-Type: application/json');
include "db_connection.php";

$data = json_decode(file_get_contents('php://input'), true);
$ids = $data['ids'] ?? [];

if (empty($ids)) {
    echo json_encode([]);
    exit;
}

$placeholders = implode(',', array_fill(0, count($ids), '?'));
$stmt = $con->prepare("SELECT id, lat, lon FROM vertex WHERE id IN ($placeholders)");

// Dynamically bind parameters
$types = str_repeat('i', count($ids));
$stmt->bind_param($types, ...$ids);

$stmt->execute();
$result = $stmt->get_result();

// ... after fetching rows ...
$results = [];
while ($row = $result->fetch_assoc()) {
    // Ensure these keys exactly match the JS: ['lat'] and ['lon']
    $results[$row['id']] = [
        'lat' => (float)$row['lat'], 
        'lon' => (float)$row['lon']
    ];
}
echo json_encode($results);
echo json_encode($results);

$stmt->close();
$con->close();
?>
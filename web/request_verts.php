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

// Database Connection (Example using PDO)
$host = 'localhost';
$db   = 'your_database';
$user = 'root';
$pass = '';
$pdo = new PDO("mysql:host=$host;dbname=$db", $user, $pass);

// 1. Create placeholders for the IN clause: ?,?,?
$placeholders = implode(',', array_fill(0, count($ids), '?'));

// 2. Prepare and execute the query
$stmt = $pdo->prepare("SELECT vertex_idx, x, y FROM vertices WHERE vertex_idx IN ($placeholders)");
$stmt->execute($ids);

// 3. Re-index the result so the key is the vertex_idx for easy JS access
$results = [];
while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
    $results[$row['vertex_idx']] = [
        'x' => (float)$row['x'],
        'y' => (float)$row['y']
    ];
}

echo json_encode($results);
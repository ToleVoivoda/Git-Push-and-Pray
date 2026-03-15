<?php
header('Content-Type: application/json');
include "db_connection.php";

// Expecting an array of updates: [[id => 1, weight => 10], [id => 2, weight => 5]]
$data = json_decode(file_get_contents('php://input'), true);
$updates = $data['updates'] ?? []; 

if (empty($updates)) {
    echo json_encode(['status' => 'error', 'message' => 'No data']);
    exit;
}

// update na edge-ovete 1 po 1
$sql = $con->prepare("UPDATE `edge` SET `rating` = ?, `lastUpdated` = ? WHERE edge_id = ?");

foreach ($updates as $update) {
    // 2. Adjust bind_param: "sdi" 
    // 's' for string (lastUpdated), 'd' for double/float (rating), 'i' for int (edge_id)
    // Adjust these characters based on your actual column data types!
    $sql->bind_param("dii", $update['rating'], $update['lastUpdated'], $update['edgeId']);
    $sql->execute();
}

echo json_encode(['status' => 'success']);
$sql->close();
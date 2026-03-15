<?php
header('Content-Type: application/json');

$lat = $_GET['lat']; // Clicked Latitude (y)
$lng = $_GET['lng']; // Clicked Longitude (x)

// Database Connection
$pdo = new PDO("mysql:host=localhost;dbname=your_database", "root", "");

// The SQL Query
// We calculate: (x - click_x)^2 + (y - click_y)^2
$sql = "SELECT vertex_idx, x, y, 
        (POWER(x - :lng, 2) + POWER(y - :lat, 2)) AS distance 
        FROM vertices 
        ORDER BY distance ASC 
        LIMIT 1";

$stmt = $pdo->prepare($sql);
$stmt->execute(['lat' => $lat, 'lng' => $lng]);
$closestVertex = $stmt->fetch(PDO::FETCH_ASSOC);

echo json_encode($closestVertex);
<?php
// 1. Set the header so the browser knows this is JSON, not HTML
header('Content-Type: application/json');

// 2. (Optional) Allow other apps to access this (CORS)
header('Access-Control-Allow-Origin: *');

// 3. Define the path to your file
$filePath = 'dijkstra_path_test.json';

if (file_exists($filePath)) {
    // Read and output the file directly
    echo file_get_contents($filePath);
} else {
    // Return an error if the file is missing
    http_response_code(404);
    echo json_encode(["error" => "File not found"]);
}
?>
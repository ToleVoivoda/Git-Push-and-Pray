<?php
    session_start();
    //include "db_connection.php";
?>

<!DOCTYPE html>
<html lang="bg">

<head>
    <meta charset="UTF-8">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/css/bootstrap.min.css" rel="stylesheet">
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/js/bootstrap.bundle.min.js"></script>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="/css/index.css">
    <link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">
    <title>Safe streets</title>
</head>

<body>
    <div>
        <heading class="heading-main">Safe streets</heading>
    </div>

    <div id="map"></div>

    <div>
        <span ><a href="map.php">Начало</a></span>
    </div>
</body>
</html>
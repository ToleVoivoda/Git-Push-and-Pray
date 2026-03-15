<!DOCTYPE html>
<html>
<head>
    <title>Safe Route Map</title>

    <link rel="stylesheet" href="https://unpkg.com/leaflet/dist/leaflet.css"/>
    <link rel="stylesheet" href="css/leafletmap.css">
    <script src="js/localStorage.js"></script>
</head>
<body>

<div class="map" id="map"></div>

<div class="map-aside">
    <img src="img/guesticon.png" class="profile-img"/>

    <div class="data-box">
        <label class="email-label" id="emailShow"></label>
        <label class="label-message">Добави сигнал за опасност!</label>
        <div>
        <span><a class="homebtn" onclick="logout()" href="map.php">Изход</a></span>
    </div>
    </div>
    
</div>
<script src="https://unpkg.com/leaflet/dist/leaflet.js"></script>
<script type="module" src="js/map.js"></script>
<script type="module" src="js/readFromAidan.js"></script>

</body>
</html>
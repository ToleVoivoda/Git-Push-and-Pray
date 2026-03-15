//initialize map

const map = L.map('map').setView([42.6977, 23.3219], 13); // Sofia coordinates

L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
    attribution: '© OpenStreetMap'
}).addTo(map);

//izbirane na tochka i popup dali e nachalna tochka ili update
var popup = L.popup();

function onMapClick(e) {
    const content = `
        <div class="popup-content">
            <p>Coordinates: ${e.latlng.lat.toFixed(4)}, ${e.latlng.lng.toFixed(4)}</p>
            <button class="btn btn-startpoint" onclick="handleAction('node')">Начало на маршрут</button>
            <button class="btn btn-addupdate" onclick="handleAction('weight')">Добави опасност</button>
        </div>
    `;

    popup
        .setLatLng(e.latlng)
        .setContent(content)
        .openOn(map);
}

map.on('click', onMapClick);








//map click - get lat/lng and place nodes
let points = []; 

map.on('click', function(e) {
   points.push(e.latlng);
    L.marker(e.latlng).addTo(map);

    if (points.length === 2) {
        //start/end point, cpp call for path @Aydin
        fetchPath(points[0], points[1]);
        points = []; // Reset for next selection
    }
});

//path request



//
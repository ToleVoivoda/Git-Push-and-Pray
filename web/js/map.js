//initialize map

const map = L.map('map').setView([42.6977, 23.3219], 13); // Sofia coordinates

L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
    attribution: '© OpenStreetMap'
}).addTo(map);

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
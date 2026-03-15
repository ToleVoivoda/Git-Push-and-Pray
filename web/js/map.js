//initialize map

const map = L.map('map').setView([42.6977, 23.3219], 13); // Sofia coordinates

L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
    attribution: '© OpenStreetMap'
}).addTo(map);

//izbirane na tochka i popup dali e nachalna tochka ili update
var popup = L.popup();

// Define the action
function addupdate() {
    //
}

// Bind the action to the click event
myButton.addEventListener("click", triggerAction);

//idle, pick_end
let appState = 'IDLE';
let startPoint = null;

function onMapClick(e) {
    if(appState === 'IDLE')
    {
        const content = `
            <div class="popup-content">
                <p>Координати: ${e.latlng.lat.toFixed(4)}, ${e.latlng.lng.toFixed(4)}</p>
                <button style class="btn btn-startpoint" onclick="checkStart()">Начало на маршрут</button>
                <button class="btn btn-addupdate" onclick="updatePopupShow()">Добави опасност</button>
            </div>
        `;

        popup
            .setLatLng(e.latlng)
            .setContent(content)
            .openOn(map);
    } else if(appState === 'PICK_END')
    {
        const endPoint = e.latlng;
        L.marker(e.latlng).addTo(map).bindPopup("End Point");
        appState = 'IDLE';
        //api za executables
        fetchPath(startPoint, endPoint);
    }
}

map.on('click', onMapClick);

function checkStart()
{
    map.closePopup();
    alert("Избери крайна точка от картата!");
    appState = 'PICK_END';
}

function updatePopupShow()
{
    //to do content of popup
    const updatePopup = L.popup()
                    .setLatLng(map.getCenter())
        .setContent()
        .openOn(map);

}








// let points = []; 
// map.on('click', function(e) {
//    points.push(e.latlng);
//     L.marker(e.latlng).addTo(map);

//     if (points.length === 2) {
//         //start/end point, cpp call for path @Aydin  VIJ GORE line 45^
//         fetchPath(points[0], points[1]);
//         points = []; // Reset for next selection
//     }
// });

//path request



//
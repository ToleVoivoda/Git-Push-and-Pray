import { calculatePath } from './readFromAidan.js';

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

//idle, pick_end
//malko ti prepravih statemashinata:
//sustoqniqta sa IDLE, PICK_PATH, UPLOAD_REPORT
//napravih i podavtomat na PICK_PATH sustoqnieto

const IDLE_STATE_TOKEN = 'IDLE';

const PICK_PATH_STATE_TOKEN = 'PICK_PATH';
const PICK_PATH_START_STATE_TOKEN = 'PICK_PATH_START';
const PICK_PATH_END_STATE_TOKEN = 'PICK_PATH_END';

const SUBMIT_REPORT_STATE_TOKEN = 'SUBMIT_REPORT';

const PICK_END_STATE_TOKEN = 'PICK_END';

let appState = IDLE_STATE_TOKEN;
let startPoint = null;
let endPoint = null;

function onMapClick(e) {
    if(appState === IDLE_STATE_TOKEN) {
        const content = `
            <div class="popup-content">
                <p>Координати: ${e.latlng.lat.toFixed(4)}, ${e.latlng.lng.toFixed(4)}</p>
                <button style class="btn btn-startpoint" onclick="setStateToPickPath()">Начало на маршрут</button>
                <button class="btn btn-addupdate" onclick="updatePopupShow()">Добави опасност</button>
            </div>`;

        popup
            .setLatLng(e.latlng)
            .setContent(content)
            .openOn(map);
    } 
    if (appState === PICK_PATH_START_STATE_TOKEN) {
       handleStatePickPathStart(e);
    }
    if (appState === PICK_PATH_END_STATE_TOKEN) {
        handleStatePickPathEnd(e);
    }
    if (appState === SUBMIT_REPORT_STATE_TOKEN) { 
        handleStateSubmitReport(e);
    }
    
    // else if(appState === PICK_END_STATE_TOKEN)
    // {
    //     const endPoint = e.latlng;
    //     L.marker(e.latlng).addTo(map).bindPopup("End Point");
    //     appState = 'IDLE';
    //     //api za executables
    //     fetchPath(startPoint, endPoint);
    // }
    
    console.log(appState);
}

map.on('click', onMapClick);

function checkStart()
{
    map.closePopup();
    //alert("Избери крайна точка от картата!");
    appState = 'PICK_END';
}

function updatePopupShow()
{
    //to do content of popup
    const updatePopup = 
        L.popup()
        .setLatLng(map.getCenter())
        .setContent()
        .openOn(map);

}

//===ALEX===
function handleStateSubmitReport() {
    console.log("report red");
    




    appState = IDLE_STATE_TOKEN;
}


//===STATE MACHINE===
function handleStateIdle(e) {
    
            // const content = `
        //     <div class="popup-content">
        //         <p>Координати: ${e.latlng.lat.toFixed(4)}, ${e.latlng.lng.toFixed(4)}</p>
        //         <button style class="btn btn-startpoint" onclick="checkStart()">Начало на маршрут</button>
        //         <button class="btn btn-addupdate" onclick="updatePopupShow()">Добави опасност</button>
        //     </div>
        // `;

        
}

//tva se vika samo ot butona
function setStateToPickPath() {
    map.closePopup();

    appState = PICK_PATH_START_STATE_TOKEN;
}

// Change to async
async function handleStatePickPathStart(e) {
    L.marker(e.latlng).addTo(map).bindPopup("Start Point");

    // Must use AWAIT here
    startPoint = await getNearestVertex(e.latlng.lat, e.latlng.lng);

    appState = PICK_PATH_END_STATE_TOKEN;
    console.log("Start Point Set:", startPoint);
}

function handleStatePickPathEnd(e) {
    L.marker(e.latlng).addTo(map).bindPopup("End Point");

    lat = e.latlng.lat;
    lng = e.latlng.lng;

    //da se izpolzvat koordinatite na toq point 
    endPoint = getNearestVertex(lat, lng);

    //ot tuka da se vika na aidan neshtotto da izchislqva putq chrez koordinatite na tochkite
    invokePathfinder();

    appState = IDLE_STATE_TOKEN;
}

//===COORDINATES===
async function getNearestVertex(lat, lng) {
    const response = await fetch(`get_closest_vertex.php?lat=${lat}&lng=${lng}`);
    const data = await response.json();
    return data;
}

function invokePathfinder() {
    console.log("s: " + startPoint + " t: " + endPoint);

    calculatePath();
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
import { calculatePath } from './readFromAidan.js';

// --- INITIALIZATION ---
const map = L.map('map').setView([42.6977, 23.3219], 13);
L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
    attribution: '© OpenStreetMap'
}).addTo(map);

var popup = L.popup();
let reportedDangers = []; 
let dangerMarkers = L.layerGroup().addTo(map);

// --- STATES ---
const IDLE_STATE_TOKEN = 'IDLE';
const PICK_PATH_START_STATE_TOKEN = 'PICK_PATH_START';
const PICK_PATH_END_STATE_TOKEN = 'PICK_PATH_END';
const SUBMIT_REPORT_STATE_TOKEN = 'SUBMIT_REPORT';

// const PICK_END_STATE_TOKEN = 'PICK_END';

let appState = IDLE_STATE_TOKEN;
let startPoint = null;
let endPoint = null;

// --- MAIN CLICK HANDLER ---
function onMapClick(e) {
    console.log("Current State:", appState);
    if(appState === IDLE_STATE_TOKEN) {
        const content = `
            <div class="popup-content">
                <p>Координати: ${e.latlng.lat.toFixed(4)}, ${e.latlng.lng.toFixed(4)}</p>
                <button style class="btn btn-startpoint" onclick="setStateToPickPath()">Начало на маршрут</button>
                
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

// --- IDLE LOGIC ---
function handleStateIdle(e) {
    const lat = e.latlng.lat;
    const lng = e.latlng.lng;

    const content = `
        <div class="popup-content">
            <p>Координати: ${lat.toFixed(4)}, ${lng.toFixed(4)}</p>
            <button class="btn" style="background: pink;" onclick="setStateToPickPath()">Начало на маршрут</button>
            <button class="btn" style="background: brown; color: white;" onclick="openDangerFormDirectly(${lat}, ${lng})">Добави опасност</button>
        </div>`;

    popup.setLatLng(e.latlng).setContent(content).openOn(map);
}

// --- DANGER REPORTING (Directly from IDLE) ---
window.openDangerFormDirectly = async function(lat, lng) {
    // 1. Get Node ID from PHP or fallback to dummy
    let nodeId = 0;
    try {
        const nearest = await getNearestVertex(lat, lng);
        nodeId = nearest.vertex_idx || nearest.id || 999;
    } catch(e) {
        nodeId = Math.floor(Math.random() * 1000);
    }

    const reportHTML = `
        <div class="register-box" style="width: 280px; padding: 10px; background: white;">
            <h3 style="margin:0; color: brown;">Детайли за сигнала</h3>
            <hr>
            <label><b>Тип на опасността:</b></label><br>
            <div style="line-height: 1.8;">
                <input type="radio" name="evtType" value="3" checked>  ПТП<br>
                <input type="radio" name="evtType" value="6">  Ремонт<br>
                <input type="radio" name="evtType" value="10">  Опасни лица<br>
                <input type="radio" name="evtType" value="11"> Друго
            </div>
            <br>
            <label><b>Описание:</b></label>
            <textarea id="evt-desc" style="width:100%; height:50px; resize:none;"></textarea>

            <button class="btn" onclick="simulateSendReport(${nodeId}, ${lat}, ${lng})" 
                    style="width:100%; color:white; padding:10px; margin-top:10px; background: brown; border:none;">
                ЗАПАЗИ СИГНАЛ
            </button>
        </div>
    `;
    popup.setContent(reportHTML);
};

window.simulateSendReport = function(v1_id, lat, lng) {
    const catId = parseInt(document.querySelector('input[name="evtType"]:checked').value);
    const description = document.getElementById('evt-desc').value;

    const ratingMap = { 3: 8, 6: 5, 10: 10, 11: 2 };
    const automaticRating = ratingMap[catId] || 1;

    const graphUpdate = {
        v1: v1_id,
        v2: v1_id + 1, // Simulated neighbor
        rating: automaticRating,
        userEmail: "student@fmi.bg",
        categoryId: catId,
        details: description
    };

    reportedDangers.push(graphUpdate);
    console.log("Graph Edge Saved:", graphUpdate);
    
    // Draw visual marker
    drawDangerEdge(v1_id, graphUpdate.v2, lat, lng);

    alert("Сигналът е записан успешно!");
        
}

//tva se vika samo ot butona
function setStateToPickPath() {
    map.closePopup();
    appState = PICK_PATH_START_STATE_TOKEN;
};

function drawDangerEdge(v1, v2, lat, lng) {
    const marker = L.circle([lat, lng], {
        color: 'red',
        fillColor: '#f03',
        fillOpacity: 0.5,
        radius: 30
    }).addTo(dangerMarkers);

    marker.bindPopup(`<b>Сигнал за опасност</b><br>Възел: ${v1}<br>Свързан към: ${v2}`);
}

// --- PATHFINDING LOGIC ---
window.setStateToPickPath = function() {
    map.closePopup();
    appState = PICK_PATH_START_STATE_TOKEN;
    alert("Избери НАЧАЛНА точка от картата!");
};

// async function handleStatePickPathStart(e) {
//     L.marker(e.latlng).addTo(map).bindPopup("Start Point");
//     const nearest = await getNearestVertex(e.latlng.lat, e.latlng.lng);
//     startPoint = nearest.vertex_idx || nearest.id;
//     appState = PICK_PATH_END_STATE_TOKEN;
//     alert("Сега избери КРАЙНА точка!");
// }
    
// Change to async
async function handleStatePickPathStart(e) {
    startPoint = await getNearestVertex(e.latlng.lat, e.latlng.lng);
    
    L.marker(e.latlng).addTo(map).bindPopup("Start Point");
    // Must use AWAIT here

    console.log(startPoint);

    appState = PICK_PATH_END_STATE_TOKEN;
    console.log("Start Point Set:", startPoint);
}

async function handleStatePickPathEnd(e) {
    L.marker(e.latlng).addTo(map).bindPopup("End Point");

    // Must use AWAIT here
    endPoint = await getNearestVertex(e.latlng.lat, e.latlng.lng);
    
    invokePathfinder();
    appState = IDLE_STATE_TOKEN;
}

// --- HELPERS ---
async function getNearestVertex(lat, lng) {
    const response = await fetch(`get_closest_vertex.php?lat=${lat}&lng=${lng}`);
    return await response.json();
}

function invokePathfinder() {
    console.log("s: " + startPoint + " t: " + endPoint);

    calculatePath();
}

// Expose functions to the global scope so buttons can find them
window.setStateToPickPath = setStateToPickPath;
//window.updatePopupShow = updatePopupShow;

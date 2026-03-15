export function calculatePath() {
    console.log("rah");
}

async function getCoordinates(path, ids) {
    const response = await fetch('get_vertices.php', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ ids: ids })
    });

    const coords = await response.json(); 
    
    // Map coords into a format Leaflet understands: [[lat, lng], [lat, lng]]
    return path.map(edge => [
        [coords[edge.v1].y, coords[edge.v1].x], // LatLng pair 1
        [coords[edge.v2].y, coords[edge.v2].x]  // LatLng pair 2
    ]);
}

fetch('dijkstra_path_test.json')
    .then(response => response.json())
    .then(async (path) => { // Mark this as async
        const uniqueIds = [...new Set(path.flatMap(edge => [edge.v1, edge.v2]))];

        // Now we wait for the coordinates to be returned
        const pathCoords = await getCoordinates(path, uniqueIds);
        
        // Leaflet's polyline expects an array of LatLng arrays:
        // [ [lat, lng], [lat, lng], [lat, lng] ]
        // Since you have a list of segments, we flatten it:
        const flatPath = pathCoords.flat();
        
        L.polyline(flatPath, {color: 'blue', weight: 5}).addTo(map);
    });
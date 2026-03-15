export function calculatePath() {
    console.log("rah");

    fetch('./get_coordinates.php')
    .then(response => response.json())
    .then(async (path) => {
        console.log("path", path);
        const uniqueIds = [...new Set(path.flatMap(edge => [edge.v1, edge.v2]))];
        console.log("unique ids", uniqueIds)
        const pathCoords = await getPathCoordinates(path, uniqueIds);
        
        // Flatten and filter out any null/undefined points
        const flatPath = pathCoords.flat();
        
        // DEBUG: See what we are actually sending to Leaflet
        console.log("Drawing path with points:", flatPath);

        // ADD THIS CHECK
        if (flatPath.length > 0 && flatPath[0] !== undefined) {
            L.polyline(flatPath, {color: 'blue', weight: 5}).addTo(map);
        } else {
            console.error("Path data is empty or malformed!");
        }
    });
}

async function getPathCoordinates(path, ids) {
    const response = await fetch('get_vertices.php', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ ids: ids })
    });

    const coords = await response.json(); 
    
    // DEBUG: Print exactly what we got from the database
    console.log("PHP Response (Coords):", coords);
    
    // Now look at this log in the console. 
    // Are the keys 'lat' and 'lon'? Or something else?
    
    return path
        .filter(edge => coords[edge.v1] && coords[edge.v2])
        .map(edge => [
            [coords[edge.v1].lat, coords[edge.v1].lon], 
            [coords[edge.v2].lat, coords[edge.v2].lon]
        ]);
}


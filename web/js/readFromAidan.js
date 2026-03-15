export function calculatePath() {
    console.log("rah");
}


async function getCoordinates(ids) {
    const response = await fetch('get_vertices.php', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ ids: ids })
    });

    const coords = await response.json(); // Format: { "101": {x: 10, y: 20}, ... }
    
    // 3. Map coordinates back to your path
    const pathWithCoords = path.map(edge => ({
        start: coords[edge.v1],
        end: coords[edge.v2]
    }));

    console.log(pathWithCoords);
}

fetch('dijkstra_path_test.json')
    .then(response => response.json())
    .then(path => {
        const uniqueIds = [...new Set(path.flatMap(edge => [edge.v1, edge.v2]))];

        const pathCoordinates = getCoordinates(uniqueIds);
        
        // Draw the path
        L.polyline(pathCoordinates, {color: 'blue', weight: 5}).addTo(map);
    });





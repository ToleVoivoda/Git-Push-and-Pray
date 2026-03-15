export async function calculatePath(map, startVertIdx, endVertIdx) {
    const response = await fetch('./pathfinder_bridge.php', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ start: startVertIdx, end: endVertIdx })
    });

    const data = await response.json();

    const drawPath = async (pathData, color) => {
        if (!pathData || pathData.length === 0) return;
        
        const ids = [...new Set(pathData.flatMap(edge => [edge.v1, edge.v2]))];
        const coords = await getPathCoordinates(pathData, ids);
        
        if (coords.length > 0) {
            L.polyline(coords, { color: color, weight: 5 }).addTo(map);
        }
    };

    // Render Blue for Safe, Red for Shortest
    await drawPath(data.safe, 'blue');
    await drawPath(data.shortest, 'red');
}

async function getPathCoordinates(path, ids) {
    const response = await fetch('get_coordinates_from_json.php', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ ids: ids })
    });

    const data = await response.json();

    const vertsArray = data.verts || []; 

    const vertLookup = {};  
    vertsArray.forEach(v => {
        vertLookup[String(v.id)] = [v.lat, v.lon];
    });

    const orderedCoords = ids
        .map(id => vertLookup[String(id)])
        .filter(coord => coord !== undefined);

    return orderedCoords;
}

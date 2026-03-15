export async function calculatePath(map, startVertIdx, endVertIdx) {
    const response = await fetch('./pathfinder_bridge.php', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ start: startVertIdx, end: endVertIdx })
    });

    const path = await response.json(); // This receives the JSON from C++ via PHP

    // Now convert the path of edges into coordinates
    const uniqueIds = [...new Set(path.flatMap(edge => [edge.v1, edge.v2]))];
    const pathCoords = await getPathCoordinates(path, uniqueIds);

    if (pathCoords.length > 0) {
        L.polyline(pathCoords, {color: 'blue', weight: 5}).addTo(map);
    }
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
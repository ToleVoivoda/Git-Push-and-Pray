export function calculatePath(map, startVertIdx, endVertIdx) {
    console.log("rah");

    fetch('./get_coordinates.php')
    .then(response => response.json())
    .then(async (path) => {
        console.log("path", path);
        const uniqueIds = [...new Set(path.flatMap(edge => [edge.v1, edge.v2]))];
        console.log("unique ids", uniqueIds);

        const pathCoords = await getPathCoordinates(path, uniqueIds);

        const finalPath = pathCoords;

        if (finalPath.length > 0) {
            L.polyline(finalPath, {color: 'blue', weight: 5}).addTo(map);
        }
    });
}

async function getPathCoordinates(path, ids) {
    console.log("Requesting coordinates for IDs:", ids);

    const response = await fetch('get_coordinates_from_json.php', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ ids: ids })
    });

    const data = await response.json();
    console.log("Raw data from PHP:", data);

    // Ensure we are looking at the right property
    const vertsArray = data.verts || []; 

    // Create the lookup map, forcing keys to be Strings
    const vertLookup = {};
    vertsArray.forEach(v => {
        // v[0] is ID, v[1] is Lat, v[2] is Lon
        vertLookup[String(v.id)] = [v.lat, v.lon];
    });

    // Map over the ids array, forcing the ID to String for the lookup
    // Inside getPathCoordinates
    const orderedCoords = ids
        .map(id => vertLookup[String(id)])
        .filter(coord => coord !== undefined);

    console.log(orderedCoords);

    return orderedCoords;
}
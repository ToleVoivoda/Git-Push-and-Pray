const express = require('express');
const cors = require('cors');
const { execFile } = require('child_process');
const util = require('util');
const execFileAsync = util.promisify(execFile);

const app = express();
app.use(cors()); // Lets your frontend talk to this API without security blocks

// The endpoint your map frontend will call
const fs = require('fs').promises; // Make sure this is at the top!

app.get('/api/route', async (req, res) => {
    const { start, goal, safety } = req.query;
    console.log(`Request: Start ${start}, Goal ${goal}, Safety ${safety}`);

    try {
        // 1. Run C++ and capture the console output (stdout)
        const { stdout } = await execFileAsync('graph_engine.exe', [start, goal, safety, 'compressed_graph.txt']);

        if (!stdout || stdout.includes("No path found")) {
            return res.json({ success: true, path: [], message: "No path exists" });
        }

        // 2. Convert the "0,13416" lines into a JSON array
        const pathData = stdout.trim().split('\n').map(line => {
            const [v1, v2] = line.split(',');
            return { v1: parseInt(v1), v2: parseInt(v2) };
        });

        res.json({
            success: true,
            path: pathData
        });

    } catch (error) {
        console.error("C++ Error:", error.message);
        res.status(500).json({ success: false, error: "C++ engine crashed or file missing." });
    }
});
// Turn the server on
app.listen(3000, () => {
    console.log('🚀 Routing API is LIVE on http://localhost:3000');
});
const { execFile } = require('child_process');
const path = require('path');

/**
 * Executes the C++ routing engine with hardcoded safety
 * @param {string} start - Start Node ID
 * @param {string} end - End Node ID
 */
function runGraphEngine(start, end) {
    return new Promise((resolve, reject) => {
        const exePath = path.join(__dirname, 'graph_engine.exe');
        
        // Safety is hardcoded to 0.7 as per requirements
        const safety = "0.7"; 
        const args = [start.toString(), end.toString(), safety];

        execFile(exePath, args, (error, stdout, stderr) => {
            if (error) {
                return reject(error);
            }
            if (stderr) {
                return reject(new Error(stderr));
            }

            // stdout captures whatever your C++ 'cout' prints
            resolve(stdout.trim());
        });
    });
}
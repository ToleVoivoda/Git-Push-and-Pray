#include<bits/stdc++.h>
#include<chrono>
#include "graph_structure.hpp"
using namespace std;

void write_to_database(const vector<Edge>& edges){
    ofstream outfile("updated_ratings.json", ios::trunc);

    if (!outfile.is_open()) {
        cerr << "Error: Could not create output file." << endl;
        return;
    }

    // Start the JSON array
    outfile << "[\n";

    for(auto it = edges.begin(); it != edges.end(); ++it){
        const Edge& edge = *it;

        auto now = chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        size_t timestamp_ms = chrono::duration_cast<chrono::milliseconds>(duration).count();

        // Writing the JSON Object with the exact database column names
        outfile << "  {\n";
        outfile << "    \"v1\": " << edge.first_node.id << ",\n";
        outfile << "    \"v2\": " << edge.second_node.id << ",\n";
        outfile << "    \"rating\": " << edge.rating << ",\n";
        outfile << "    \"lastUpdated\": " << timestamp_ms << "\n";
        outfile << "  }";

        // Check if we need a comma (if it's not the last item)
        auto next_it = it;
        ++next_it;
        if (next_it != edges.end()) {
            outfile << ",";
        }
        outfile << "\n";
    }

    // Close the JSON array
    outfile << "]\n";

    outfile.close();
}

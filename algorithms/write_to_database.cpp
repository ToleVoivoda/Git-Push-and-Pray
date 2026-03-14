#include<bits/stdc++.h>
#include<chrono>
#include "graph_structure.hpp"
using namespace std;

void write_to_database(const vector<Edge>& edges){
    //v1 v2 w r
    ofstream outfile("updated_ratings.txt", ios::trunc); // Wipes file clean
    if (!outfile.is_open()) {
        cerr << "Error: Could not create output file." << endl;
        return;
    }

    for(vector<Edge>::const_iterator it = edges.begin(); it != edges.end(); ++it){
        const Edge& edge = *it;
        auto now = chrono::system_clock::now();

        // 2. Measure the time since the "Unix Epoch" (Jan 1, 1970)
        auto duration = now.time_since_epoch();

        // 3. Convert that duration into milliseconds
        size_t timestamp_ms = chrono::duration_cast<chrono::milliseconds>(duration).count();
        outfile << edge.first_node.id << " " << edge.second_node.id << " " <<edge.rating << " " << timestamp_ms <<"\n";
    }

    outfile.close();
}


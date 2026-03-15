#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "graph_structure.hpp"

using namespace std;

vector<pair<size_t, size_t>> dijkstra(size_t start, size_t goal, double safety_coefficient, const vector<vector<Edge>>& adj);

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cerr << "Error: Not enough arguments! Need start, goal, and safety." << endl;
        return 1;
    }

    size_t start_node = stoull(argv[1]);
    size_t goal_node = stoull(argv[2]);
    double safety = stod(argv[3]);
    string filename = (argc >= 5) ? argv[4] : "compressed_graph.txt";

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << ". Make sure it exists!" << endl;
        return 1;
    }

 cout << "Loading graph from: " << filename << "..." << endl;

    cout << "Loading graph from: " << filename << "..." << endl;

    Edge edge;
    // Using a large size to avoid out-of-bounds
    vector<vector<Edge>> adj(1000000); 
    size_t count = 0;

    while(file >> edge.first_node.id >> edge.second_node.id >> edge.length >> edge.rating >> edge.last_update) {
        // Use .id to access the number inside the Node struct
        if (edge.first_node.id >= 1000000 || edge.second_node.id >= 1000000) {
            cerr << "ERROR: Node ID too high!" << endl;
            return 1;
        }

        // Add forward edge
        adj[edge.first_node.id].push_back(edge);
        
        // Add backward edge for undirected graph
        Node u_node = {edge.first_node.id};
        Node v_node = {edge.second_node.id};
        // We use v_node.id for the index
        adj[v_node.id].push_back({v_node, u_node, edge.length, edge.rating, edge.last_update});
        
        count++;
    }
    file.close();
    
    cout << "Successfully loaded " << count << " edges." << endl;
    cout << "Running Dijkstra from " << start_node << " to " << goal_node << "..." << endl;

    // ONLY DECLARE THIS ONCE - Make sure there isn't another 'vector... path' line below this
    vector<pair<size_t, size_t>> path = dijkstra(start_node, goal_node, safety, adj);

    ofstream outfile("dijkstra_path.json", ios::trunc);

    if(!outfile.is_open()) {
        cerr << "Error: Could not open output file for writing." << endl;
        return 1;
    }

    outfile << "[\n";
    for(auto it = path.begin(); it != path.end(); ++it) {
        //outfile << "  {\"from\": " << it->first << ", \"to\": " << it->second << "}";

        outfile << " {\n";
        outfile << "   \"v1\": " << it->first << ",\n";
        outfile << "   \"v2\": " << it->second << "\n";
        outfile << " }";
        auto next_it = it;
        next_it++;
        if (next_it != path.end()) {
            outfile << ",";
        }
        outfile << "\n";
    }
    outfile << "]\n";
    outfile.close();
    if (path.empty()) {
        cout << "No path found" << endl;
    } else {
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i].first << "," << path[i].second << endl;
        }
    }

    return 0;
}
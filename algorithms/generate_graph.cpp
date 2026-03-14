#include<bits/stdc++.h>
#include "graph_structure.hpp"
#include "dijkstra.cpp"
using namespace std;
int main() {
    //  Open the text file
    ifstream file("compressed_graph.txt");
    if (!file.is_open()) {
        cerr << "Error: Could not open graph.txt. Make sure the file is in the same directory!" << endl;
        return 1;
    }
    Edge curr;
    vector<vector<Edge>> adj(73731);
    while(file >> curr.first_node.id >> curr.second_node.id >> curr.length >> curr.rating >> curr.last_update ){
        adj[curr.first_node.id].push_back(curr);
        swap(curr.first_node.id, curr.second_node.id);
        adj[curr.first_node.id].push_back(curr);
    }

    file.close();

    //  Run Dijkstra from Node 0 to the last node (n - 1)
    size_t start_node = 0;
    size_t goal_node = 70000;


    vector<pair<size_t, size_t>> shortest_path = dijkstra(start_node, goal_node, 0.7, adj);

    // Write the resulting edges to a text file
    ofstream outfile("path_edges.txt", ios::trunc);
    if (!outfile.is_open()) {
        cerr << "Error: Could not create output file." << endl;
        return 1;
    }

    // Print the results
    if (shortest_path.empty()) {
        cout << "Result: No path found from " << start_node << " to " << goal_node << ".\n";
        outfile << "No path found.\n";
    } else {

        for(size_t i = 0; i < (size_t)shortest_path.size(); ++i){
            size_t first_node = shortest_path[i].first;
            size_t second_node = shortest_path[i].second;
            outfile << first_node << " " << second_node << "\n";
        }
        outfile.close();

        /*cout << "Result: Shortest path is:\n";
        for (size_t i = 0; i < shortest_path.size(); ++i) {
            cout << shortest_path[i];
            if (i != shortest_path.size() - 1) cout << " -> ";
        }
        cout << "\n";*/
    }

    return 0;
}

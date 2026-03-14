#include<bits/stdc++.h>
#include "graph_structure.hpp"
#include "dijkstra.cpp"
using namespace std;
int main() {
    //  Open the text file
    ifstream file("graph.txt");
    if (!file.is_open()) {
        cerr << "Error: Could not open graph.txt. Make sure the file is in the same directory!" << endl;
        return 1;
    }

    //  Read 'n' (vertices) and 'm' (edges)
    size_t vertices, edges;
    if (!(file >> vertices >> edges)) {
        cerr << "Error: File format is incorrect or empty." << endl;
        return 1;
    }

    // Initialize nodes and adjacency list based on 'n'
    vector<Node> nodes(vertices);
    for (size_t i = 0; i < vertices; ++i) {
        nodes[i] = {i}; // Assign IDs from 0 to n-1
    }

    vector<vector<Edge>> adj(vertices);

    // Read the 'm' edges
    size_t begin_node, end_node;
    double distance_edge, rating_edge;
    for (size_t i = 0; i < edges; ++i) {
        file >> begin_node >> end_node >> distance_edge >> rating_edge;

        adj[begin_node].push_back({nodes[begin_node], nodes[end_node], distance_edge, rating_edge});
        adj[end_node].push_back({nodes[end_node], nodes[begin_node], distance_edge, rating_edge});
    }

    file.close();

    //  Run Dijkstra from Node 0 to the last node (n - 1)
    size_t start_node = 0;
    size_t goal_node = vertices - 1;

    cout << "Loaded graph with " << vertices << " vertices and " << edges << " edges." << endl;
    cout << "Running Dijkstra to find path from " << start_node << " to " << goal_node << "..." << endl;

    vector<size_t> shortest_path = dijkstra(start_node, goal_node, adj, nodes);

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

        for(size_t i = 0; i < (size_t)shortest_path.size() - 1; ++i){
            size_t first_node = shortest_path[i];
            size_t second_node = shortest_path[i+1];
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

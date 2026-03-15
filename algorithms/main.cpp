#include <iostream>
#include <vector>
#include <string>
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


    vector<vector<Edge>> adj(73731);


    vector<pair<size_t, size_t>> path = dijkstra(start_node, goal_node, safety, adj);

    if (path.empty()) {
        cout << "No path found" << endl;
    } else {
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i].first << "," << path[i].second << endl;
        }
    }

    return 0;
}
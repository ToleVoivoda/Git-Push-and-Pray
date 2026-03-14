#include<bits/stdc++.h>
#include "graph_structure.hpp"
#include<ctime>
#include<cstdlib>
using namespace std;

int main(){
    srand(time(0));
    ifstream my_file("graph_for_cpp.txt");

    if (!my_file.is_open()) {
        cerr << "Error: Could not open the file. Is it in the same folder as the .exe?" << endl;
        return 1;
    }
    vector<Edge> edges;
    vector<Node> nodes;
    set<size_t> set_nodes;
    size_t first_vertex, second_vertex;
    double edge_distance;
    unordered_map<size_t, size_t> compression;
    while(my_file >> first_vertex >> second_vertex >> edge_distance){
        set_nodes.insert(first_vertex);
        set_nodes.insert(second_vertex);
    }
    my_file.close();
    size_t index = 0;
    for(set<size_t>::const_iterator it = set_nodes.begin(); it != set_nodes.end(); ++it){
        compression[*it] = index;
        compression[index] = *it;
        index++;
    }
    ifstream my_file2("graph_for_cpp.txt");

    if (!my_file2.is_open()) {
        cerr << "Error: Could not open the file. Is it in the same folder as the .exe?" << endl;
        return 1;
    }
    while(my_file2 >> first_vertex >> second_vertex >> edge_distance){
        size_t first_node = compression[first_vertex];
        size_t second_node = compression[second_vertex];
        double curr_rating = ((double)(rand() % 100))/10.0 + 1.0;
        if(curr_rating >= 10.0){
            curr_rating = 10.0;
        }
        edges.push_back({first_node, second_node, edge_distance, curr_rating, 0});
    }
    my_file2.close();

    ofstream outfile("compressed_graph.txt", ios::trunc);
    if (!outfile.is_open()) {
        cerr << "Error: Could not create output file." << endl;
        return 1;
    }
    for(vector<Edge>::const_iterator it = edges.begin(); it != edges.end(); ++it){
        const Edge& edge = *it;
        auto now = chrono::system_clock::now();

        // 2. Measure the time since the "Unix Epoch" (Jan 1, 1970)
        auto duration = now.time_since_epoch();

        // 3. Convert that duration into milliseconds
        size_t timestamp_ms = chrono::duration_cast<chrono::milliseconds>(duration).count();
        outfile << edge.first_node.id << " " << edge.second_node.id << " " << edge.length << " " <<edge.rating << " " << timestamp_ms <<"\n";
    }

    outfile.close();
    cout<< set_nodes.size();
    return 0;
}

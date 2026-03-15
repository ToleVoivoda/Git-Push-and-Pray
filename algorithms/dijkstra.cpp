#include<bits/stdc++.h>
#include "graph_structure.hpp"
using namespace std;
vector<pair<size_t, size_t>> dijkstra( size_t start, size_t goal, double safety_coefficient, const vector<vector<Edge>>& adj){
    priority_queue<pair<double, size_t>, vector< pair<double, size_t> >, greater<pair<double, size_t> > > priority__dijkstra;
    vector<double> cost_from_source;
    vector<size_t> came_from;
    cost_from_source.resize( 73731 , numeric_limits<double>::infinity());
    came_from.resize(73731, SIZE_MAX);

    priority__dijkstra.push({0.0 , start});
    cost_from_source[start] = 0.0;
    came_from[start]=start;
    while(!priority__dijkstra.empty()){
        pair<double,size_t> current_top = priority__dijkstra.top();
        double current_cost = current_top.first;
        size_t current_node = current_top.second;
        priority__dijkstra.pop();

        //Reconstruct the path
        if(current_node == goal){
            vector<size_t> path;
            size_t curr = goal;
            while(came_from[curr] != curr){
                path.push_back(curr);
                curr = came_from[curr];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());

            vector<pair<size_t, size_t>> result;
            for(size_t i = 0; i < (size_t)path.size() - 1; ++i){
                result.push_back({path[i], path[i+1]});
            }
            return result;
        }

        if(current_cost > cost_from_source[current_node]){
            continue;
        }

        for(vector<Edge>::const_iterator it = adj[current_node].begin(); it != adj[current_node].end(); ++it){
            const Edge& edge = *it;
            size_t next_node = edge.second_node.id;

            //double rating = (edge.rating / 10.0) - 0.1;
            

            double edge_weight = safety_coefficient * edge.rating + (1 - safety_coefficient) * edge.length;
            double new_cost = current_cost + edge_weight;

            if(new_cost < cost_from_source[next_node]){
                cost_from_source[next_node] = new_cost;
                came_from[next_node] = current_node;
                priority__dijkstra.push({new_cost, next_node});
            }

        }


    }
    return vector<pair<size_t, size_t>>();
}






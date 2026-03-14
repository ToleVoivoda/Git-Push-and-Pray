#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include "../algorithms/graph_structure.hpp"
#include "AoEScale.h"
#include <iostream>
using namespace std;

void updateNearEdgesV2(vector<vector<Edge>>& adj, const size_t& srcNodeId, const double& modifier) {
    size_t V = adj.size();
    size_t PATH_LENGTH = 2;

    vector<int> hops(V, -1);
    queue<size_t> q;
    hops[srcNodeId] = 0;
    q.push(srcNodeId);

    while (!q.empty()) {
        size_t u = q.front();
        q.pop();
        int current_hop = hops[u];

        if (current_hop > PATH_LENGTH) continue;

        double decay_factor = pow(0.25, current_hop + 1);
        double added_danger = modifier * decay_factor;

        for (Edge& edge : adj[u]) {
            size_t v = edge.second_node.id;
            edge.rating += added_danger;
            edge.rating = std::min(edge.rating, 10.0);
            updateOppositeEdge(adj, edge.first_node.id, edge.second_node.id, edge.rating);

            if (hops[v] == -1) {
                hops[v] = current_hop + 1;
                q.push(v);
            }
        }
    }
}

void printGraph(const vector<vector<Edge>>& adj) {
    for (int i=0;i<adj.size();i++) {
        for (int j=0;j<adj[i].size();j++) {
            std::cout<<"("<<adj[i][j].first_node.id<<"; "<<adj[i][j].second_node.id<<"; "<<adj[i][j].length<<"; "
                    <<adj[i][j].rating<<")  ";
        }
        std::cout<<"\n";
    }
}

void updateOppositeEdge(vector<vector<Edge>>& adj, const size_t& first, const size_t& second, double& newRating) {
    for (int i=0;i<adj[second].size();i++) {
        if (adj[second][i].second_node.id==first) {
            newRating = std::min(newRating, 10.0);
            adj[second][i].rating = newRating;
            return;
        }
    }
}
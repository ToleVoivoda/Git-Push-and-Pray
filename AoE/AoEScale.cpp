#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include "../algorithms/graph_structure.hpp"
#include "AoEScale.h"
#include <iostream>
#include <chrono>
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
            // addTimeDecay(edge);
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
//
// void addTimeDecay(Edge &edge) {
//     auto now = chrono::system_clock::now().time_since_epoch();
//     auto diff = now-edge.last_update;
// }

#include <queue>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

void updateNearEdgesV3(vector<vector<Edge>>& adj, const size_t& srcNodeId, const double& modifier, const double maxDistance = 1000.0) {
    size_t V = adj.size();
    vector<double> dist(V, -1.0); // distance from srcNodeId
    queue<pair<size_t,double>> q; // pair: node id, accumulated distance

    dist[srcNodeId] = 0.0;
    q.push({srcNodeId, 0.0});

    while (!q.empty()) {
        auto [u, accDist] = q.front();
        q.pop();

        for (Edge& edge : adj[u]) {
            size_t v = edge.second_node.id;
            double newDist = accDist + edge.length;

            // stop if we exceed max distance
            if (newDist > maxDistance) continue;

            // decay factor based on distance (optional: linear or exponential)
            double decay_factor = 0.2*pow(0.25, newDist/ maxDistance); // example: 0–1000m scaled
            double added_danger = modifier * decay_factor;

            edge.rating += added_danger;
            edge.rating = std::min(edge.rating, 10.0);
            edge.rating = size_t(edge.rating*10) /10.0;

            // update opposite edge in undirected graph
            updateOppositeEdge(adj, edge.first_node.id, edge.second_node.id, edge.rating);

            // enqueue neighbor if not visited or found shorter path
            if (dist[v] == -1 || newDist < dist[v]) {
                dist[v] = newDist;
                q.push({v, newDist});
            }
        }
    }
}
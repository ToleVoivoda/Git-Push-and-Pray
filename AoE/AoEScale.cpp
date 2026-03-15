#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include "../algorithms/graph_structure.hpp"
#include "AoEScale.h"
#include <iostream>
#include "../algorithms/write_to_database.cpp"
#include <chrono>
using namespace std;

void printGraph(const vector<vector<Edge>>& adj) {
    for (int i=0;i<adj.size();i++) {
        for (int j=0;j<adj[i].size();j++) {
            std::cout<<"("<<adj[i][j].first_node.id<<"; "<<adj[i][j].second_node.id<<"; "<<adj[i][j].length<<"; "
                    <<adj[i][j].rating<<")  ";
        }
        std::cout<<"\n";
    }
}

void updateOppositeEdge(vector<vector<Edge>>& adj, const size_t& first, const size_t& second, double& newRating, vector<Edge>& UpdatedEdges) {
    for (Edge& edge : adj[second]) {
        if (edge.second_node.id==first) {
            edge.rating = newRating;
            edge.rating = std::min(edge.rating, 10.0);
            edge.rating = size_t(edge.rating*10) /10.0;
            UpdatedEdges.push_back(edge);
            return;
        }
    }
}

void updateNearEdgesV3(vector<vector<Edge>>& adj, const size_t& srcNodeId, const double& modifier, const double maxDistance = 1000.0) {
    size_t V = adj.size();
    vector<double> dist(V, -1.0); // distance from srcNodeId
    queue<pair<size_t,double>> q; // pair: node id, accumulated distance
    vector<Edge> updatedEdges;

    dist[srcNodeId] = 0.0;
    q.push({srcNodeId, 0.0});

    while (!q.empty()) {
        auto [u, accDist] = q.front();
        q.pop();

        for (Edge& edge : adj[u]) {
            size_t v = edge.second_node.id;
            if (dist[v]!=-1) continue;
            double newDist = accDist + edge.length;

            // stop if we exceed max distance
            if (newDist > maxDistance) continue;

            // decay factor based on distance (optional: linear or exponential)
            double decay_factor = 0.2*pow(0.25, newDist/ maxDistance); // example: 0–1000m scaled
            double added_danger = modifier * decay_factor - diffFromLastInHours(edge)/120.0;

            edge.rating += added_danger;
            edge.rating = std::min(edge.rating, 10.0);
            edge.rating = size_t(edge.rating*10) /10.0;
            updatedEdges.push_back(edge);

            // update opposite edge in undirected graph
            updateOppositeEdge(adj, edge.first_node.id, edge.second_node.id, edge.rating, updatedEdges);

            // enqueue neighbor if not visited or found shorter path
            if (dist[v] == -1 || newDist < dist[v]) {
                dist[v] = newDist;
                q.push({v, newDist});
            }
        }
    }
    write_to_database(updatedEdges);
}

size_t diffFromLastInHours(Edge &edge) {
    auto now = chrono::system_clock::now();
    auto timeFromEpoch = now.time_since_epoch();
    size_t timestamp_ms = chrono::duration_cast<chrono::milliseconds>(timeFromEpoch).count();
    size_t diff = timestamp_ms-edge.last_update;
    std::cout<<timestamp_ms<<"\n"<<diff<<"\n";
    diff = diff /1000 /60 /60;
    edge.last_update=timestamp_ms;
    return diff;
}

#include "AoEScale.h"
#include <iostream>
#include <limits>
#include <queue>
#include <cmath>
#include <set>
const size_t PATH_LENGTH = 2;


// void printGraph(const vector<vector<pair<size_t,size_t>>>& adj) {
//     size_t V = adj.size();
//     for (size_t i=0;i<V;i++) {
//         size_t numNeigh = adj[i].size();
//         for (size_t j=0;j<numNeigh;j++) {
//             std::cout<<"("<<adj[i][j].first<<","<<adj[i][j].second<<") ";
//         }
//         std::cout<<std::endl;
//     }
// }


std::queue<vector<Edge>> bfs(vector<vector<Edge>>& adj, const Node& src, vector<double>& dist) {
    size_t V = adj.size();
    vector<int> visited(V, 0);


    for (int i=0;i<dist.size();i++) dist[i] = numeric_limits<double>::infinity();
    dist[src.id]=0;
    std::queue<vector<Edge>> q;
    visited[src.id] = 2;
    vector<Edge> currPath;
    for (int i=0;i<adj[src.id].size();i++) {
        currPath.push_back(adj[src.id][i]);
        q.push(currPath);
        currPath.pop_back();
    }

    while (!q.empty()) {
        if (q.front().size()>=PATH_LENGTH) break;
        currPath = q.front();
        q.pop();

        for (auto x : adj[currPath.back().second_node.id]) {
            if (!visited[x.second_node.id]) {
                dist[x.second_node.id] = dist[currPath.back().second_node.id] + x.length;
                visited[x.second_node.id] = 1;
                currPath.push_back(x);
                q.push(currPath);
                currPath.pop_back();
            }
        }
        visited[currPath.back().second_node.id]=2;
    }
    return q;
}

void updateNearEdgesV2(vector<vector<Edge>> &adj, const Node &srcNode, const size_t &modifier) {
    vector<double> dist(adj.size());
    std::queue<vector<Edge>> bfsResult = bfs(adj,srcNode,dist);
    std::set<pair<size_t,size_t>> updatedEdges;

    while (!bfsResult.empty()) {
        vector<Edge> currPath = bfsResult.front();
        bfsResult.pop();
        for (int i=0;i<PATH_LENGTH;i++) {
            if (updatedEdges.find({currPath[i].first_node.id,currPath[i].second_node.id})==updatedEdges.end()) {
                currPath[i].rating += modifier*pow(0.4,i+1);
                currPath[i].rating = std::min(currPath[i].rating,10.0);
                updatedEdges.insert({currPath[i].first_node.id,currPath[i].second_node.id});
            }
        }
    }
}

#include "AoEScale.h"
#include <iostream>
#include <limits>
#include <queue>

// the current edge should be modified BEFORE using this function
void updateNearEdges(vector<vector<pair<size_t,size_t>>>& adj, const pair<size_t,size_t>& srcEdge, const size_t& diffInRating) {
    size_t v1=srcEdge.first, v2=srcEdge.second;

    /// За недиректни ребра:
    // vector<size_t> firstNeighbours;
    // for (auto &p: adj[v1]) {
    //     if (p.first!=v2) firstNeighbours.push_back(p.first);
    // }
    // for (auto &p: adj[v2]) {
    //     if (p.first!=v1) firstNeighbours.push_back(p.first);
    // }

    size_t numNeigh = adj[v1].size();
    for (size_t i=0;i<numNeigh;i++) {
        if (adj[v1][i].first!=v2) {
            size_t other = adj[v1][i].first;
            adj[v1][i].second += diffInRating * 0.6;
            updateOppositeSide(adj,v1,other,diffInRating*0.6);
        }
    }

    numNeigh = adj[v2].size();
    for (size_t i=0;i<numNeigh;i++) {
        if (adj[v2][i].first!=v1) {
            size_t other = adj[v2][i].first;
            adj[v2][i].second += diffInRating * 0.6;
            updateOppositeSide(adj,v2,other,diffInRating*0.6);
        }
    }
}

void updateOppositeSide(vector<vector<pair<size_t,size_t>>>& adj, const size_t& v1, const size_t& other, double modifier) {
    size_t numNeigh = adj[other].size();
    for (size_t i=0;i<numNeigh;i++) {
        if (adj[other][i].first==v1) {
            adj[other][i].second += modifier;
            return;
        }
    }
}


void printGraph(const vector<vector<pair<size_t,size_t>>>& adj) {
    size_t V = adj.size();
    for (size_t i=0;i<V;i++) {
        size_t numNeigh = adj[i].size();
        for (size_t j=0;j<numNeigh;j++) {
            std::cout<<"("<<adj[i][j].first<<","<<adj[i][j].second<<") ";
        }
        std::cout<<std::endl;
    }
}

void updateNearEdgesV2(vector<vector<Edge>> &adj, vector<Node> &nodes, const size_t &srcEdge, const size_t &endEdge, const size_t &modifier) {

}

vector<size_t> bfs(vector<vector<Edge>>& adj, Node src, vector<double>& dist) {
    size_t V = adj.size();
    vector<int> visited(V, 0);
    vector<size_t> ancestor(V,V);

    for (int i=0;i<dist.size();i++) dist[i] = numeric_limits<double>::infinity();
    dist[src.id]=0;
    std::queue<Node> q;
    visited[src.id] = 1;
    q.push(src);

    while (!q.empty()) {
        Node curr = q.front();
        q.pop();

        for (auto x : adj[curr.id]) {
            if (!visited[x.second_node.id]) {
                dist[x.second_node.id] = dist[curr.id] + x.length;
                visited[x.second_node.id] = 1;
                q.push(x.second_node);
            }
        }
        visited[curr.id]=2;
    }

    return ancestor;
}



#include "AoEScale.h"
#include <iostream>

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


void printGraph(vector<vector<pair<size_t,size_t>>>& adj) {
    size_t V = adj.size();
    for (size_t i=0;i<V;i++) {
        size_t numNeigh = adj[i].size();
        for (size_t j=0;j<numNeigh;j++) {
            std::cout<<"("<<adj[i][j].first<<","<<adj[i][j].second<<") ";
        }
        std::cout<<std::endl;
    }
}

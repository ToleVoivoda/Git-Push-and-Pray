#ifndef GIT_PUSH_AND_PRAY_AOESCALE_H
#define GIT_PUSH_AND_PRAY_AOESCALE_H

#include <vector>
#include <queue>
#include "..\algorithms/graph_structure.hpp"
using namespace std;

// void updateNearEdges(vector<vector<pair<size_t,size_t>>>& adj, const pair<size_t,size_t>& srcEdge, const size_t& diffInRating);
// void updateOppositeSide(vector<vector<pair<size_t,size_t>>>& adj, const size_t& v1, const size_t& other, double modifier);
// void printGraph(const vector<vector<pair<size_t,size_t>>>& adj);

void updateNearEdgesV2(vector<vector<Edge>> &adj, const Node &srcNode, const size_t &modifier);
std::queue<vector<Edge>> bfs(vector<vector<Edge>>& adj, const Node& src, vector<double>& dist);

#endif //GIT_PUSH_AND_PRAY_AOESCALE_H

#ifndef GIT_PUSH_AND_PRAY_AOESCALE_H
#define GIT_PUSH_AND_PRAY_AOESCALE_H

#include <vector>
#include <queue>
#include "../algorithms/graph_structure.hpp"
using namespace std;


void updateOppositeEdge(vector<vector<Edge>>& adj, const size_t& first, const size_t& second, double& newRating);
void printGraph(const vector<vector<Edge>>& adj);
void updateNearEdgesV2(vector<vector<Edge>>& adj, const size_t& srcNodeId, const double& modifier);
std::queue<vector<Edge>> bfs(vector<vector<Edge>>& adj, const Node& src, vector<double>& dist);


#endif //GIT_PUSH_AND_PRAY_AOESCALE_H

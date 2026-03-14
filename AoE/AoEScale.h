#ifndef GIT_PUSH_AND_PRAY_AOESCALE_H
#define GIT_PUSH_AND_PRAY_AOESCALE_H

#include <vector>
using namespace std;

void updateNearEdges(vector<vector<pair<size_t,size_t>>>& adj, const pair<size_t,size_t>& srcEdge, const size_t& diffInRating);
void updateOppositeSide(vector<vector<pair<size_t,size_t>>>& adj, const size_t& v1, const size_t& other, double modifier);
void printGraph(vector<vector<pair<size_t,size_t>>>& adj);

#endif //GIT_PUSH_AND_PRAY_AOESCALE_H

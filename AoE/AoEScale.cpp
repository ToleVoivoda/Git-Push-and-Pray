#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include "../algorithms/graph_structure.hpp"
#include "AoEScale.h"
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

        double decay_factor = pow(0.4, current_hop + 1);
        double added_danger = modifier * decay_factor;

        for (Edge& edge : adj[u]) {
            size_t v = edge.second_node.id;
            edge.rating += added_danger;
            edge.rating = std::min(edge.rating, 10.0);

            if (hops[v] == -1) {
                hops[v] = current_hop + 1;
                q.push(v);
            }
        }
    }
}
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <utility>

#include "graph_structure.hpp"
using namespace std;

vector<double> markov_step(
    const vector<double>& dist,
    const vector<vector<Edge>>& adj
) {
    size_t n = adj.size();

    vector<double> next(n, 0.0);

    for (size_t i = 0; i < n; ++i) {

        if (dist[i] == 0.0) continue;

        size_t degree = adj[i].size();

        if (degree == 0) continue;

        double total_weight = 0.0;

        for (const Edge& edge : adj[i]) {
            double rating = (edge.rating / 10.0) - 0.1;
            total_weight += (1.0 + rating);
        }

        for (const Edge& edge : adj[i]) {

            size_t j = edge.second_node.id;

            double rating = (edge.rating / 10.0) - 0.1;

            double transition_prob =
                (1.0 + rating) / total_weight;

            next[j] += dist[i] * transition_prob;
        }
    }

    return next;
}

vector<double> predict_danger(
    size_t start_node,
    const vector<vector<Edge>>& adj,
    size_t steps
) {
    size_t n = adj.size();

    vector<double> dist(n, 0.0);

    dist[start_node] = 1.0;

    for (size_t i = 0; i < steps; ++i) {
        dist = markov_step(dist, adj);
    }

    return dist;
}
int main() {

    vector<vector<Edge>> adj; // normally comes from your graph

    size_t start_node = 0;
    size_t steps = 5;

    vector<double> prediction = predict_danger(start_node, adj, steps);

    for (size_t i = 0; i < prediction.size(); i++) {
        cout << "Node " << i << " danger probability: "
            << prediction[i] << endl;
    }

    return 0;
}

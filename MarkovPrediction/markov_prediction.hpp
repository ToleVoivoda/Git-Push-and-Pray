#pragma once
#include <vector>
#include "graph_structure.hpp"

std::vector<double> predict_danger(
    size_t start_node,
    const std::vector<std::vector<Edge>>& adj,
    size_t steps
);
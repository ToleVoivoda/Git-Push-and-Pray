#include <iostream>
#include <vector>
#include "AoEScale.h"

int main() {
    vector<vector<pair<int,int>>> adj = {
        {{1,4},{2,8}},
        {{0,4},{4,6},{2,3}},
        {{0,8},{3,2},{1,3}},
        {{2,2},{4,10}},
        {{1,6},{3,10}}
    };

    printGraph(adj);

    updateNearEdges(adj,{0,1},3);

    printGraph(adj);
    return 0;
}
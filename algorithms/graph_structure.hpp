#ifndef __GRAPH__
#define __GRAPH__

struct Node {
    size_t id;
};

struct Edge {
    Node first_node;
    Node second_node;
    double length;
    double rating;
    size_t last_update;
};

#endif // __GRAPH__

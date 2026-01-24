#ifndef ASTAR_NODE_H
#define ASTAR_NODE_H

#include <limits>

struct Node {
    int x;
    int y;
    double g; // cost from start
    double h; // heuristic to goal
    bool walkable;
    Node* parent;

    Node(int x_ = 0, int y_ = 0)
        : x(x_), y(y_), g(std::numeric_limits<double>::infinity()), h(0.0), walkable(true), parent(nullptr) {}

    double f() const { return g + h; }
};

#endif // ASTAR_NODE_H

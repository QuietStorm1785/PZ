#ifndef ASTAR_GRID_H
#define ASTAR_GRID_H

#include <vector>
#include <utility>
#include <cmath>
#include <cassert>
#include "Node.h"

class Grid {
public:
    Grid(int width, int height)
        : w_(width), h_(height), nodes_() {
        nodes_.reserve(w_ * h_);
        for (int y = 0; y < h_; ++y) {
            for (int x = 0; x < w_; ++x) {
                nodes_.push_back(Node(x, y));
            }
        }
    }

    int width() const { return w_; }
    int height() const { return h_; }

    bool inBounds(int x, int y) const {
        return x >= 0 && x < w_ && y >= 0 && y < h_;
    }

    bool isWalkable(int x, int y) const {
        assert(inBounds(x, y));
        return nodes_[index(x, y)].walkable;
    }

    void setWalkable(int x, int y, bool walk) {
        assert(inBounds(x, y));
        nodes_[index(x, y)].walkable = walk;
    }

    std::vector<std::pair<int,int>> neighbors(int x, int y, bool allowDiagonals) const {
        static const int dx4[4] = {1, -1, 0, 0};
        static const int dy4[4] = {0, 0, 1, -1};
        static const int dx8[8] = {1, -1, 0, 0, 1, 1, -1, -1};
        static const int dy8[8] = {0, 0, 1, -1, 1, -1, 1, -1};

        std::vector<std::pair<int,int>> out;
        if (allowDiagonals) {
            for (int i = 0; i < 8; ++i) {
                int nx = x + dx8[i];
                int ny = y + dy8[i];
                if (inBounds(nx, ny) && isWalkable(nx, ny)) out.emplace_back(nx, ny);
            }
        } else {
            for (int i = 0; i < 4; ++i) {
                int nx = x + dx4[i];
                int ny = y + dy4[i];
                if (inBounds(nx, ny) && isWalkable(nx, ny)) out.emplace_back(nx, ny);
            }
        }
        return out;
    }

    Node& at(int x, int y) {
        assert(inBounds(x, y));
        return nodes_[index(x, y)];
    }

    const Node& at(int x, int y) const {
        assert(inBounds(x, y));
        return nodes_[index(x, y)];
    }

private:
    int w_;
    int h_;
    std::vector<Node> nodes_; // flattened row-major

    inline int index(int x, int y) const { return y * w_ + x; }
};

#endif // ASTAR_GRID_H

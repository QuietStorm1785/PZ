#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "astar/ISearchNode.h"

namespace astar {
namespace datastructures {


class IOpenSet {
public:
    virtual ~IOpenSet() = default;
    void add(ISearchNode var1);

    void remove(ISearchNode var1);

    ISearchNode poll();

    ISearchNode getNode(ISearchNode var1);

    int size();

    void clear();
}
} // namespace datastructures
} // namespace astar

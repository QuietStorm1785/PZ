#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace ai {
namespace astar {

class Mover {
public:
    virtual ~Mover() = default;
    int getID();

    int getPathFindIndex();
}
} // namespace astar
} // namespace ai
} // namespace zombie

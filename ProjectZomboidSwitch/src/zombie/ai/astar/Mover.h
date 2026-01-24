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
    virtual int getID() const = 0;
    virtual int getPathFindIndex() const = 0;
}
} // namespace astar
} // namespace ai
} // namespace zombie

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

class IPathfinder {
public:
    virtual ~IPathfinder() = default;
    void Failed(Mover var1);

    void Succeeded(Path var1, Mover var2);

    std::string getName();
}
} // namespace astar
} // namespace ai
} // namespace zombie

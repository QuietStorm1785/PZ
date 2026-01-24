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
    virtual void Failed(std::shared_ptr<Mover> mover) = 0;
    virtual void Succeeded(std::shared_ptr<Path> path, std::shared_ptr<Mover> mover) = 0;
    virtual std::string getName() const = 0;
}
} // namespace astar
} // namespace ai
} // namespace zombie

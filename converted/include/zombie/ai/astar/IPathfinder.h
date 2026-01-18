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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class IPathfinder {
public:
 virtual ~IPathfinder() = default;
 void Failed(Mover mover);

 void Succeeded(Path path, Mover mover);

 std::string getName();
}
} // namespace astar
} // namespace ai
} // namespace zombie

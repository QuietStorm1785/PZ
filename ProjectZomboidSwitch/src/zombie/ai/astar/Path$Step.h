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

class Path {
public:
    int x = 0;
    int y = 0;
    int z = 0;

    Path$Step() = default;
    Path$Step(int x_, int y_, int z_) : x(x_), y(y_), z(z_) {}

    bool equals(const Path$Step& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    int getX() const { return x; }
    int getY() const { return y; }
    int getZ() const { return z; }
    int hashCode() const { return x * y * z; }
}
} // namespace astar
} // namespace ai
} // namespace zombie

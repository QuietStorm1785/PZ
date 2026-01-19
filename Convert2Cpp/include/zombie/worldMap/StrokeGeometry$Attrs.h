#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace worldMap {

class StrokeGeometry {
public:
    std::string cap = "butt";
    std::string join = "bevel";
    float width = 1.0F;
    float miterLimit = 10.0F;
}
} // namespace worldMap
} // namespace zombie

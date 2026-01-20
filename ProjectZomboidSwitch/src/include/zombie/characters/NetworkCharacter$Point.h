#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace characters {

class NetworkCharacter {
public:
    float px = 0.0F;
    float py = 0.0F;
    float rx = 0.0F;
    float ry = 0.0F;
    int t = 0;
}
} // namespace characters
} // namespace zombie

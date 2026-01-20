#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace characters {

class MoveDeltaModifiers {
public:
    float turnDelta = -1.0F;
    float moveDelta = -1.0F;
    float twistDelta = -1.0F;
}
} // namespace characters
} // namespace zombie

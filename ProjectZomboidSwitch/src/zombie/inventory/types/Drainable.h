#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace inventory {
namespace types {

class Drainable {
public:
    virtual ~Drainable() = default;
    float getUsedDelta();

    void setUsedDelta(float var1);
}
} // namespace types
} // namespace inventory
} // namespace zombie

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace network {
namespace packets {
namespace hit {

class IPositional {
public:
    virtual ~IPositional() = default;
    float getX();

    float getY();
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

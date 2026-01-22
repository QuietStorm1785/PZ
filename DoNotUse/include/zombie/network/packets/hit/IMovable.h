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

class IMovable {
public:
    virtual ~IMovable() = default;
    float getSpeed();

    bool isVehicle();
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

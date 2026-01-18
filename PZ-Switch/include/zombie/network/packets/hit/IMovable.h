#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
namespace packets {
namespace hit {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

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

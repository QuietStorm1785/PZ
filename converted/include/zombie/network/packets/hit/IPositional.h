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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

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

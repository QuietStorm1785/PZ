#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {
namespace objects {
namespace interfaces {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class Activatable {
public:
 virtual ~Activatable() = default;
 bool Activated();

 void Toggle();

 std::string getActivatableType();
}
} // namespace interfaces
} // namespace objects
} // namespace iso
} // namespace zombie

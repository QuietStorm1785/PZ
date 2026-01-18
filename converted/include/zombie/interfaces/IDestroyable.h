#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace interfaces {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class IDestroyable {
public:
 virtual ~IDestroyable() = default;
 /**
 * destory the object
 */
 void destroy();

 /**
 * returns if the object is destryed or not
 */
 bool isDestroyed();
}
} // namespace interfaces
} // namespace zombie

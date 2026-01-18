#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace util {
namespace hash {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class IntHashFunction {
public:
 virtual ~IntHashFunction() = default;
 int hash(int var1);
}
} // namespace hash
} // namespace util
} // namespace zombie

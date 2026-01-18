#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace util {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class IntComparator {
public:
 virtual ~IntComparator() = default;
 int compare(int var1, int var2);
}
} // namespace util
} // namespace zombie

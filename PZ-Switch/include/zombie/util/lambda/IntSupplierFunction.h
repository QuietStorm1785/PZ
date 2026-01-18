#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace util {
namespace lambda {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IntSupplierFunction {
public:
 virtual ~IntSupplierFunction() = default;
 int getInt(E var1);
}
} // namespace lambda
} // namespace util
} // namespace zombie

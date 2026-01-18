#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace util {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class PooledObjectArrayObject {
public:
 void onReleased() {
 int int0 = 0;

 for (int int1 = this->length(); int0 < int1; int0++) {
 this->get(int0).release();
 }
 }
}
} // namespace util
} // namespace zombie

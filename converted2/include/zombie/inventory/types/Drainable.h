#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace inventory {
namespace types {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Drainable {
public:
  virtual ~Drainable() = default;
  float getUsedDelta();

  void setUsedDelta(float usedDelta);
}
} // namespace types
} // namespace inventory
} // namespace zombie

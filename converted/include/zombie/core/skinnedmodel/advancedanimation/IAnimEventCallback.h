#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IAnimEventCallback {
public:
  virtual ~IAnimEventCallback() = default;
  void OnAnimEvent(AnimLayer var1, AnimEvent var2);
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie

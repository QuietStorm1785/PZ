#pragma once
#include "zombie/core/textures/Mask.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace interfaces {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IMaskerable {
public:
  virtual ~IMaskerable() = default;
  Mask getMask();
}
} // namespace interfaces
} // namespace zombie

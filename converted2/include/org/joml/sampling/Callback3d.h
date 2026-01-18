#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace org {
namespace joml {
namespace sampling {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Callback3d {
public:
  virtual ~Callback3d() = default;
  void onNewSample(float var1, float var2, float var3);
}
} // namespace sampling
} // namespace joml
} // namespace org

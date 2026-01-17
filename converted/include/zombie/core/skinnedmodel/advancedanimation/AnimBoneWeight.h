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

class AnimBoneWeight {
public:
  std::string boneName;
  float weight = 1.0F;
  bool includeDescendants = true;

public
  AnimBoneWeight() {}

public
  AnimBoneWeight(const std::string &string, float float0) {
    this.boneName = string;
    this.weight = float0;
    this.includeDescendants = true;
  }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie

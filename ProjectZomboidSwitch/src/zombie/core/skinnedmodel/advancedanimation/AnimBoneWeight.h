#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {

class AnimBoneWeight {
public:
    std::string boneName;
    float weight = 1.0F;
    bool includeDescendants = true;

    public AnimBoneWeight() {
   }

    public AnimBoneWeight(const std::string& var1, float var2) {
      this.boneName = var1;
      this.weight = var2;
      this.includeDescendants = true;
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie

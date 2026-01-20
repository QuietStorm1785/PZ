#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/advancedanimation/AnimBoneWeight.h"
#include "zombie/core/skinnedmodel/model/SkinningBone.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {


class AnimationBoneWeightBinding : public AnimationBoneBinding {
public:
    float m_weight = 1.0F;
    bool m_includeDescendants = true;

    public AnimationBoneWeightBinding(AnimBoneWeight var1) {
      this(var1.boneName, var1.weight, var1.includeDescendants);
   }

    public AnimationBoneWeightBinding(const std::string& var1, float var2, bool var3) {
      super(var1);
      this.m_weight = var2;
      this.m_includeDescendants = var3;
   }

    float getWeight() {
      return this.m_weight;
   }

    void setWeight(float var1) {
      this.m_weight = var1;
   }

    bool getIncludeDescendants() {
      return this.m_includeDescendants;
   }

    void setIncludeDescendants(bool var1) {
      this.m_includeDescendants = var1;
   }

    void forEachDescendant(Consumer<SkinningBone> var1) {
      if (this.m_includeDescendants) {
    SkinningBone var2 = this.getBone();
         if (var2 != nullptr) {
            var2.forEachDescendant(var1);
         }
      }
   }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie

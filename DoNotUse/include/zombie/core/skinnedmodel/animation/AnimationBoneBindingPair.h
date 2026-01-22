#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/model/SkinningBone.h"
#include "zombie/core/skinnedmodel/model/SkinningData.h"
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {


class AnimationBoneBindingPair {
public:
    const AnimationBoneBinding boneBindingA;
    const AnimationBoneBinding boneBindingB;

    public AnimationBoneBindingPair(const std::string& var1, const std::string& var2) {
      this.boneBindingA = std::make_shared<AnimationBoneBinding>(var1);
      this.boneBindingB = std::make_shared<AnimationBoneBinding>(var2);
   }

    void setSkinningData(SkinningData var1) {
      this.boneBindingA.setSkinningData(var1);
      this.boneBindingB.setSkinningData(var1);
   }

    SkinningBone getBoneA() {
      return this.boneBindingA.getBone();
   }

    SkinningBone getBoneB() {
      return this.boneBindingB.getBone();
   }

    bool isValid() {
      return this.getBoneA() != nullptr && this.getBoneB() != nullptr;
   }

    bool matches(const std::string& var1, const std::string& var2) {
      return StringUtils.equalsIgnoreCase(this.boneBindingA.boneName, var1) && StringUtils.equalsIgnoreCase(this.boneBindingB.boneName, var2);
   }

    int getBoneIdxA() {
    return getBoneIdx();
   }

    int getBoneIdxB() {
    return getBoneIdx();
   }

    static int getBoneIdx(SkinningBone var0) {
      return var0 != nullptr ? var0.Index : -1;
   }

    std::string toString() {
    std::string var1 = System.lineSeparator();
      return this.getClass().getName()
         + var1
         + "{"
         + var1
         + "\tboneBindingA:"
         + StringUtils.indent(std::string.valueOf(this.boneBindingA))
         + var1
         + "\tboneBindingB:"
         + StringUtils.indent(std::string.valueOf(this.boneBindingB))
         + var1
         + "}";
   }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie

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


class AnimationBoneBinding {
public:
    const std::string boneName;
    SkinningBone m_bone = nullptr;
    SkinningData m_skinningData;

    public AnimationBoneBinding(const std::string& var1) {
      this.boneName = var1;
   }

    SkinningData getSkinningData() {
      return this.m_skinningData;
   }

    void setSkinningData(SkinningData var1) {
      if (this.m_skinningData != var1) {
         this.m_skinningData = var1;
         this.m_bone = nullptr;
      }
   }

    SkinningBone getBone() {
      if (this.m_bone == nullptr) {
         this.initBone();
      }

      return this.m_bone;
   }

    void initBone() {
      if (this.m_skinningData == nullptr) {
         this.m_bone = nullptr;
      } else {
         this.m_bone = this.m_skinningData.getBone(this.boneName);
      }
   }

    std::string toString() {
    std::string var1 = System.lineSeparator();
      return this.getClass().getName()
         + var1
         + "{"
         + var1
         + "\tboneName:\""
         + this.boneName
         + "\""
         + var1
         + "\tm_bone:"
         + StringUtils.indent(std::string.valueOf(this.m_bone))
         + var1
         + "}";
   }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/util/vector/Quaternion.h"
#include "zombie/core/skinnedmodel/animation/AnimationClip/KeyframeByBoneIndexElement.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {


class AnimationClip {
public:
    const std::string Name;
    StaticAnimation staticClip;
   private const KeyframeByBoneIndexElement[] m_KeyFramesByBoneIndex;
    float Duration;
   private const List<Keyframe> m_rootMotionKeyframes = std::make_unique<std::vector<>>();
   private const Keyframe[] KeyframeArray;
    static const Quaternion orientation = std::make_shared<Quaternion>(-0.07107F, 0.0F, 0.0F, 0.07107F);

    public AnimationClip(float var1, List<Keyframe> var2, const std::string& var3, bool var4) {
      this.Duration = var1;
      this.KeyframeArray = var2.toArray(new Keyframe[0]);
      this.Name = var3;
      this.m_KeyFramesByBoneIndex = new KeyframeByBoneIndexElement[60];
    std::vector var5 = new std::vector();
    int var6 = this.KeyframeArray.length - (var4 ? 0 : 1);

      for (int var7 = 0; var7 < 60; var7++) {
         var5.clear();

         for (int var8 = 0; var8 < var6; var8++) {
    Keyframe var9 = this.KeyframeArray[var8];
            if (var9.Bone == var7) {
               var5.push_back(var9);
            }
         }

         this.m_KeyFramesByBoneIndex[var7] = std::make_shared<KeyframeByBoneIndexElement>(var5);
      }
   }

   public Keyframe[] getBoneFramesAt(int var1) {
      return this.m_KeyFramesByBoneIndex[var1].m_keyframes;
   }

    int getRootMotionFrameCount() {
      return this.m_rootMotionKeyframes.size();
   }

    Keyframe getRootMotionFrameAt(int var1) {
      return this.m_rootMotionKeyframes.get(var1);
   }

   public Keyframe[] getKeyframes() {
      return this.KeyframeArray;
   }

    float getTranslationLength(BoneAxis var1) {
    float var3 = this.KeyframeArray[this.KeyframeArray.length - 1].Position.x - this.KeyframeArray[0].Position.x;
    float var2;
      if (var1 == BoneAxis.Y) {
         var2 = -this.KeyframeArray[this.KeyframeArray.length - 1].Position.z + this.KeyframeArray[0].Position.z;
      } else {
         var2 = this.KeyframeArray[this.KeyframeArray.length - 1].Position.y - this.KeyframeArray[0].Position.y;
      }

      return (float)Math.sqrt(var3 * var3 + var2 * var2);
   }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie

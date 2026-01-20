#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/math/PZMath.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/animation/AnimationClip.h"
#include "zombie/core/skinnedmodel/animation/Keyframe.h"
#include "zombie/scripting/ScriptParser/Block.h"
#include "zombie/scripting/ScriptParser/Value.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace runtime {


class CopyFrames {
public:
    int m_frame;
    int m_FPS = 30;
    std::string m_source;
    int m_sourceFrame1;
    int m_sourceFrame2;
    int m_sourceFPS = 30;

    void parse(Block var1) {
      for (Value var3 : var1.values) {
    std::string var4 = var3.getKey().trim();
    std::string var5 = var3.getValue().trim();
         if ("source".equalsIgnoreCase(var4)) {
            this.m_source = var5;
         } else if ("frame".equalsIgnoreCase(var4)) {
            this.m_frame = PZMath.tryParseInt(var5, 1);
         } else if ("sourceFrame1".equalsIgnoreCase(var4)) {
            this.m_sourceFrame1 = PZMath.tryParseInt(var5, 1);
         } else if ("sourceFrame2".equalsIgnoreCase(var4)) {
            this.m_sourceFrame2 = PZMath.tryParseInt(var5, 1);
         }
      }
   }

    void exec(List<Keyframe> var1) {
    AnimationClip var2 = ModelManager.instance.getAnimationClip(this.m_source);

      for (int var3 = 0; var3 < 60; var3++) {
         Keyframe[] var4 = var2.getBoneFramesAt(var3);
         if (var4.length != 0) {
            for (int var5 = this.m_sourceFrame1; var5 <= this.m_sourceFrame2; var5++) {
    Keyframe var6 = var4[0];
    Keyframe var7 = std::make_shared<Keyframe>();
               var7.Bone = var6.Bone;
               var7.BoneName = var6.BoneName;
               var7.Time = (float)(this.m_frame - 1 + (var5 - this.m_sourceFrame1)) / this.m_FPS;
               var7.Position = KeyframeUtil.GetKeyFramePosition(var4, (float)(var5 - 1) / this.m_sourceFPS, var2.Duration);
               var7.Rotation = KeyframeUtil.GetKeyFrameRotation(var4, (float)(var5 - 1) / this.m_sourceFPS, var2.Duration);
               var7.Scale = var6.Scale;
               var1.push_back(var7);
            }
         }
      }
   }
}
} // namespace runtime
} // namespace skinnedmodel
} // namespace core
} // namespace zombie

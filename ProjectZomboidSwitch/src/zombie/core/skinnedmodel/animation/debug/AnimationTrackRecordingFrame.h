#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/animation/AnimationTrack.h"
#include "zombie/iso/Vector2.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {
namespace debug {


class AnimationTrackRecordingFrame : public GenericNameWeightRecordingFrame {
public:
    Vector2 m_deferredMovement = std::make_shared<Vector2>();

    public AnimationTrackRecordingFrame(const std::string& var1) {
      super(var1);
   }

    void reset() {
      super.reset();
      this.m_deferredMovement.set(0.0F, 0.0F);
   }

    void logAnimWeights(List<AnimationTrack> var1, int[] var2, float[] var3, Vector2 var4) {
      for (int var5 = 0; var5 < var2.length; var5++) {
    int var6 = var2[var5];
         if (var6 < 0) {
            break;
         }

    float var7 = var3[var5];
    AnimationTrack var8 = (AnimationTrack)var1.get(var6);
    std::string var9 = var8.name;
    int var10 = var8.getLayerIdx();
         this.logWeight(var9, var10, var7);
      }

      this.m_deferredMovement.set(var4);
   }

    Vector2 getDeferredMovement() {
      return this.m_deferredMovement;
   }

    void writeHeader(std::stringstream var1) {
      var1.append(",");
      var1.append("dm.x").append(",").append("dm.y");
      super.writeHeader(var1);
   }

    void writeData(std::stringstream var1) {
      var1.append(",");
      var1.append(this.getDeferredMovement().x).append(",").append(this.getDeferredMovement().y);
      super.writeData(var1);
   }
}
} // namespace debug
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/util/vector/Quaternion.h"
#include "org/lwjgl/util/vector/Vector3f.h"
#include "zombie/core/PerformanceSettings.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {


class AnimationTrack {
public:
    Keyframe from;
    Keyframe to;
    int fromIdx = -1;
    int toIdx = -1;

   private AnimationTrack$KeyframeSpan() {
   }

    void clear() {
      this.from = nullptr;
      this.to = nullptr;
      this.fromIdx = -1;
      this.toIdx = -1;
   }

    Keyframe lerp(float var1, Keyframe var2) {
      var2.setIdentity();
      if (this.from == nullptr && this.to == nullptr) {
    return var2;
      } else if (this.to == nullptr) {
         var2.set(this.from);
    return var2;
      } else if (this.from == nullptr) {
         var2.set(this.to);
    return var2;
      } else {
         return Keyframe.lerp(this.from, this.to, var1, var2);
      }
   }

    void lerp(float var1, Vector3f var2, Quaternion var3, Vector3f var4) {
      if (this.from == nullptr && this.to == nullptr) {
         Keyframe.setIdentity(var2, var3, var4);
      } else if (this.to == nullptr) {
         this.from.get(var2, var3, var4);
      } else if (this.from == nullptr) {
         this.to.get(var2, var3, var4);
      } else if (!PerformanceSettings.InterpolateAnims) {
         this.to.get(var2, var3, var4);
      } else {
         Keyframe.lerp(this.from, this.to, var1, var2, var3, var4);
      }
   }

    bool isSpan() {
      return this.from != nullptr && this.to != nullptr;
   }

    bool isPost() {
      return (this.from == nullptr || this.to == nullptr) && this.from != this.to;
   }

    bool isEmpty() {
      return this.from == nullptr && this.to == nullptr;
   }

    bool containsTime(float var1) {
      return this.isSpan() && this.from.Time <= var1 && var1 <= this.to.Time;
   }

    bool isBone(int var1) {
      return this.from != nullptr && this.from.Bone == var1 || this.to != nullptr && this.to.Bone == var1;
   }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie

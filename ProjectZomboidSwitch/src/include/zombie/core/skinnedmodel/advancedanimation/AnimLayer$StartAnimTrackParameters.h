#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/animation/BoneAxis.h"
#include "zombie/util/Pool.h"
#include "zombie/util/PooledObject.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class AnimLayer {
public:
    int priority;
   List<AnimBoneWeight> subLayerBoneWeights;
    bool syncTrackingEnabled;
    float speedScale;
    float initialWeight;
    bool isLooped;
    bool isReversed;
    std::string deferredBoneName;
    BoneAxis deferredBoneAxis;
    bool useDeferredRotation;
   private static const Pool<AnimLayer$StartAnimTrackParameters> s_pool = std::make_shared<Pool>(AnimLayer$StartAnimTrackParameters::new);

    void reset() {
      this.priority = 0;
      this.subLayerBoneWeights = nullptr;
      this.syncTrackingEnabled = false;
      this.speedScale = 1.0F;
      this.initialWeight = 0.0F;
      this.isLooped = false;
      this.isReversed = false;
      this.deferredBoneName = nullptr;
      this.deferredBoneAxis = BoneAxis.Y;
      this.useDeferredRotation = false;
   }

    void onReleased() {
      this.reset();
   }

   protected AnimLayer$StartAnimTrackParameters() {
   }

   public static AnimLayer$StartAnimTrackParameters alloc() {
      return (AnimLayer$StartAnimTrackParameters)s_pool.alloc();
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie

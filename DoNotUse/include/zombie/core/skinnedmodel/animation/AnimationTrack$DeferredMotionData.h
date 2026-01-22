#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/util/vector/Quaternion.h"
#include "org/lwjgl/util/vector/Vector3f.h"
#include "zombie/iso/Vector2.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {


class AnimationTrack {
public:
    float m_targetDeferredRotation;
    float m_prevDeferredRotation;
    const Quaternion m_targetDeferredRotationQ = std::make_shared<Quaternion>();
    const Vector3f m_targetDeferredPosition = std::make_shared<Vector3f>();
    const Vector2 m_prevDeferredMovement = std::make_shared<Vector2>();
    const Vector2 m_targetDeferredMovement = std::make_shared<Vector2>();
    float m_deferredRotationDiff;
    const Vector2 m_deferredMovementDiff = std::make_shared<Vector2>();
    const Vector2 m_counterRotatedMovementDiff = std::make_shared<Vector2>();

   private AnimationTrack$DeferredMotionData() {
   }

    void reset() {
      this.m_deferredRotationDiff = 0.0F;
      this.m_targetDeferredRotation = 0.0F;
      this.m_prevDeferredRotation = 0.0F;
      this.m_targetDeferredRotationQ.setIdentity();
      this.m_targetDeferredMovement.set(0.0F, 0.0F);
      this.m_targetDeferredPosition.set(0.0F, 0.0F, 0.0F);
      this.m_prevDeferredMovement.set(0.0F, 0.0F);
      this.m_deferredMovementDiff.set(0.0F, 0.0F);
      this.m_counterRotatedMovementDiff.set(0.0F, 0.0F);
   }
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie

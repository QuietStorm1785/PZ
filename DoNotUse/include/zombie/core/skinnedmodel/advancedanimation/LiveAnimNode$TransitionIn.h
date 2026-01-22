#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/animation/AnimationTrack.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class LiveAnimNode {
public:
    float m_time;
    std::string m_transitionedFrom;
    bool m_active;
    AnimationTrack m_track;
    AnimTransition m_data;
    float m_weight;
    float m_rawWeight;
    bool m_blendingIn;
    bool m_blendingOut;

   private LiveAnimNode$TransitionIn() {
   }

    void reset() {
      this.m_time = 0.0F;
      this.m_transitionedFrom = nullptr;
      this.m_active = false;
      this.m_track = nullptr;
      this.m_data = nullptr;
      this.m_weight = 0.0F;
      this.m_rawWeight = 0.0F;
      this.m_blendingIn = false;
      this.m_blendingOut = false;
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie

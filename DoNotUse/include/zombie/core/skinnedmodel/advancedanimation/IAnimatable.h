#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/action/ActionContext.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer.h"
#include "zombie/core/skinnedmodel/animation/debug/AnimationPlayerRecorder.h"
#include "zombie/core/skinnedmodel/model/ModelInstance.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class IAnimatable {
public:
    virtual ~IAnimatable() = default;
    ActionContext getActionContext();

    AnimationPlayer getAnimationPlayer();

    AnimationPlayerRecorder getAnimationPlayerRecorder();

    bool isAnimationRecorderActive();

    AdvancedAnimator getAdvancedAnimator();

    ModelInstance getModelInstance();

    std::string GetAnimSetName();

    std::string getUID();

   default short getOnlineID() {
      return -1;
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie

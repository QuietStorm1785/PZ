#pragma once
#include "zombie/characters/action/ActionContext.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer.h"
#include "zombie/core/skinnedmodel/animation/debug/AnimationPlayerRecorder.h"
#include "zombie/core/skinnedmodel/model/ModelInstance.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

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

 default short getOnlineID() { return -1; }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie

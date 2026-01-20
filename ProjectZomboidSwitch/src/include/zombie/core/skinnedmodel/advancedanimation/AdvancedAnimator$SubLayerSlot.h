#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {

class AdvancedAnimator {
public:
    bool shouldBeActive = false;
    const AnimLayer animLayer;

   public AdvancedAnimator$SubLayerSlot(AnimLayer var1, IAnimatable var2, IAnimEventCallback var3) {
      this.animLayer = std::make_shared<AnimLayer>(var1, var2, var3);
   }

    void update() {
      this.animLayer.Update();
   }

    void transitionTo(AnimState var1, bool var2) {
      this.animLayer.TransitionTo(var1, var2);
      this.shouldBeActive = var1 != nullptr;
   }

    void applyTransition() {
      if (!this.shouldBeActive) {
         this.transitionTo(nullptr, false);
      }
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie

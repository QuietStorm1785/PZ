#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/BooleanDebugOption.h"
#include "zombie/debug/options/char/DebugOG/AnimateOG.h"
#include "zombie/debug/options/char/DebugOG/RenderOG.h"

namespace zombie {
namespace debug {
namespace options {


class char {
public:
    const RenderOG Render = std::make_shared<RenderOG>(this.Group);
    const AnimateOG Animate = std::make_shared<AnimateOG>(this.Group);
    const BooleanDebugOption RegisterDebugVariables = newDebugOnlyOption(this.Group, "DebugVariables", false);
    const BooleanDebugOption AlwaysTripOverFence = newDebugOnlyOption(this.Group, "AlwaysTripOverFence", false);
    const BooleanDebugOption PlaySoundWhenInvisible = newDebugOnlyOption(this.Group, "PlaySoundWhenInvisible", false);
    const BooleanDebugOption UpdateAlpha = newDebugOnlyOption(this.Group, "UpdateAlpha", true);
    const BooleanDebugOption UpdateAlphaEighthSpeed = newDebugOnlyOption(this.Group, "UpdateAlphaEighthSpeed", false);

   public char$DebugOG(IDebugOptionGroup var1) {
      super(var1, "Debug");
   }
}
} // namespace options
} // namespace debug
} // namespace zombie

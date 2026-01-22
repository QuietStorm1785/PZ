#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/BooleanDebugOption.h"

namespace zombie {
namespace debug {
namespace options {


class char {
public:
    const BooleanDebugOption DeferredRotationOnly = newDebugOnlyOption(this.Group, "DeferredRotationsOnly", false);
    const BooleanDebugOption NoBoneMasks = newDebugOnlyOption(this.Group, "NoBoneMasks", false);
    const BooleanDebugOption NoBoneTwists = newDebugOnlyOption(this.Group, "NoBoneTwists", false);
    const BooleanDebugOption ZeroCounterRotationBone = newDebugOnlyOption(this.Group, "ZeroCounterRotation", false);

   public char$DebugOG$AnimateOG(IDebugOptionGroup var1) {
      super(var1, "Animate");
   }
}
} // namespace options
} // namespace debug
} // namespace zombie

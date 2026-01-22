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


class Animation {
public:
    const BooleanDebugOption Enabled = newDebugOnlyOption(this.Group, "Enabled", true);
    const BooleanDebugOption AllowLerping = newDebugOnlyOption(this.Group, "AllowLerping", true);

   Animation$SharedSkelesOG(IDebugOptionGroup var1) {
      super(var1, "SharedSkeles");
   }
}
} // namespace options
} // namespace debug
} // namespace zombie

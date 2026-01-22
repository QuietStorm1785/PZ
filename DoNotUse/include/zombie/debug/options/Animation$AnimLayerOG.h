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
    const BooleanDebugOption LogStateChanges = newDebugOnlyOption(this.Group, "Debug.LogStateChanges", false);
    const BooleanDebugOption AllowAnimNodeOverride = newDebugOnlyOption(this.Group, "Debug.AllowAnimNodeOverride", false);

   Animation$AnimLayerOG(IDebugOptionGroup var1) {
      super(var1, "AnimLayer");
   }
}
} // namespace options
} // namespace debug
} // namespace zombie

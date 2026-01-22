#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/options/OptionGroup.h"

namespace zombie {
namespace debug {


class DebugOptions {
public:
    const BooleanDebugOption BoundTextures = newDebugOnlyOption(this.Group, "BoundTextures", false);
    const BooleanDebugOption SlowLuaEvents = newDebugOnlyOption(this.Group, "SlowLuaEvents", false);

   public DebugOptions$Checks() {
      super("Checks");
   }
}
} // namespace debug
} // namespace zombie

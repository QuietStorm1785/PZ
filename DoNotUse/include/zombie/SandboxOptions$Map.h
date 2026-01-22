#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/SandboxOptions/BooleanSandboxOption.h"

namespace zombie {


class SandboxOptions {
public:
    const BooleanSandboxOption AllowMiniMap;
    const BooleanSandboxOption AllowWorldMap;
    const BooleanSandboxOption MapAllKnown;

   SandboxOptions$Map(SandboxOptions var1) {
      this.this$0 = var1;
      this.AllowMiniMap = var1.newBooleanOption("Map.AllowMiniMap", false);
      this.AllowWorldMap = var1.newBooleanOption("Map.AllowWorldMap", true);
      this.MapAllKnown = var1.newBooleanOption("Map.MapAllKnown", false);
   }
}
} // namespace zombie

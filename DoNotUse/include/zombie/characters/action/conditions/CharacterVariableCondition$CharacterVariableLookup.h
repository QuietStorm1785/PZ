#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include "zombie/core/skinnedmodel/advancedanimation/debug/AnimatorDebugMonitor.h"

namespace zombie {
namespace characters {
namespace action {
namespace conditions {


class CharacterVariableCondition {
public:
    std::string variableName;

   public CharacterVariableCondition$CharacterVariableLookup(std::string var1) {
      this.variableName = var1;
      if (Core.bDebug) {
         AnimatorDebugMonitor.registerVariable(var1);
      }
   }

    std::string toString() {
      return this.variableName;
   }
}
} // namespace conditions
} // namespace action
} // namespace characters
} // namespace zombie

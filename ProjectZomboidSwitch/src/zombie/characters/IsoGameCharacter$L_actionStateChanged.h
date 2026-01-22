#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"

namespace zombie {
namespace characters {


class IsoGameCharacter {
public:
   static const std::vector<std::string> stateNames = std::make_unique<std::vector<>>();
   static const std::vector<State> states = std::make_unique<std::vector<>>();

   private IsoGameCharacter$L_actionStateChanged() {
   }
}
} // namespace characters
} // namespace zombie

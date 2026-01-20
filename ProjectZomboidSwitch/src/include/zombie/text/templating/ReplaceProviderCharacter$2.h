#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"

namespace zombie {
namespace text {
namespace templating {


class ReplaceProviderCharacter {
public:
   ReplaceProviderCharacter$2(ReplaceProviderCharacter var1, IsoGameCharacter var2) {
      this.this$0 = var1;
      this.val$character = var2;
   }

    std::string getString() {
      return this.val$character != nullptr && this.val$character.getDescriptor() != nullptr && this.val$character.getDescriptor().getSurname() != nullptr
         ? this.val$character.getDescriptor().getSurname()
         : "Smith";
   }
}
} // namespace templating
} // namespace text
} // namespace zombie

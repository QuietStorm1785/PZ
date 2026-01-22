#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/text/templating/ReplaceProviderCharacter/1.h"
#include "zombie/text/templating/ReplaceProviderCharacter/2.h"

namespace zombie {
namespace text {
namespace templating {


class ReplaceProviderCharacter : public ReplaceProvider {
public:
    public ReplaceProviderCharacter(IsoGameCharacter var1) {
      this.addReplacer("firstname", std::make_shared<1>(this, var1));
      this.addReplacer("lastname", std::make_shared<2>(this, var1));
   }
}
} // namespace templating
} // namespace text
} // namespace zombie

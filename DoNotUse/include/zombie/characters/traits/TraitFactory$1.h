#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/traits/TraitFactory/Trait.h"
#include <algorithm>

namespace zombie {
namespace characters {
namespace traits {


class TraitFactory {
public:
    int compare(Trait> var1, Trait> var2) {
      return ((Trait)var1.getValue()).name.compareTo(((Trait)var2.getValue()).name);
   }
}
} // namespace traits
} // namespace characters
} // namespace zombie

#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"

namespace zombie {


class PersistentOutfits {
:
    virtual ~PersistentOutfits() = default;
    void accept(int var1, std::string_view var2, IsoGameCharacter var3);
}
} // namespace zombie

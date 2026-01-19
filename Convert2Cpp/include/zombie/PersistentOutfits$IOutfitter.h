#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"

namespace zombie {


class PersistentOutfits {
public:
    virtual ~PersistentOutfits() = default;
    void accept(int var1, const std::string& var2, IsoGameCharacter var3);
}
} // namespace zombie

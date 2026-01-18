#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/population/ClothingItem.h"

namespace zombie {
namespace scripting {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ItemReplacement {
public:
 std::string clothingItemName;
 ClothingItem clothingItem;
 std::string maskVariableName;
 std::string maskVariableValue;
 std::string attachment;
}
} // namespace objects
} // namespace scripting
} // namespace zombie

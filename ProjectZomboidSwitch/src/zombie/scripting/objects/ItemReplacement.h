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

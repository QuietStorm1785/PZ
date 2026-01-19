#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/scripting/objects/Item.h"
#include "zombie/scripting/objects/Recipe.h"

namespace zombie {
namespace scripting {


class IScriptObjectStore {
:
    virtual ~IScriptObjectStore() = default;
    Item getItem(std::string_view var1);

    Recipe getRecipe(std::string_view var1);
}
} // namespace scripting
} // namespace zombie

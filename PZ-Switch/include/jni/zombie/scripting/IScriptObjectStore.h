#pragma once
#include <string>
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
    Item getItem(const std::string& var1);

    Recipe getRecipe(const std::string& var1);
}
} // namespace scripting
} // namespace zombie

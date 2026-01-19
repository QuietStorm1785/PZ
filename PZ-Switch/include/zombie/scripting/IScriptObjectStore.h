#pragma once
#include "zombie/scripting/objects/Item.h"
#include "zombie/scripting/objects/Recipe.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace scripting {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IScriptObjectStore {
public:
 virtual ~IScriptObjectStore() = default;
 Item getItem(std::string_view name);

 Recipe getRecipe(std::string_view name);
}
} // namespace scripting
} // namespace zombie

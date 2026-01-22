#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/array/TShortArrayList.h"
#include "se/krka/kahlua/vm/LuaClosure.h"

namespace zombie {
namespace Lua {


class MapObjects {
public:
    const std::string spriteName;
   const std::vector<LuaClosure> functions = std::make_unique<std::vector<>>();
    const TShortArrayList priority = std::make_shared<TShortArrayList>();

   MapObjects$Callback(std::string var1) {
      this.spriteName = var1;
   }
}
} // namespace Lua
} // namespace zombie

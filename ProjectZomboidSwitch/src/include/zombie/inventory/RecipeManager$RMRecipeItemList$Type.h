#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace inventory {

enum class RecipeManager {
   NONE,
   WATER,
   DRAINABLE,
   FOOD,
   OTHER,
   DESTROY;
}
} // namespace inventory
} // namespace zombie

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace characters {

enum class CharacterActionAnims {
   None,
   Drink,
   Read,
   Chop_tree,
   Disassemble,
   Paint,
   Eat,
   Reload,
   Dig,
   DigShovel,
   DigHoe,
   DigPickAxe,
   DigTrowel,
   Pour,
   Build,
   BuildLow,
   Craft,
   Bandage,
   TakePills,
   Destroy,
   Shave,
   InsertBullets,
   RemoveBullets;
}
} // namespace characters
} // namespace zombie

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace scripting {
namespace objects {

enum class Item {
   Normal,
   Weapon,
   Food,
   Literature,
   Drainable,
   Clothing,
   Container,
   WeaponPart,
   Key,
   KeyRing,
   Moveable,
   Radio,
   AlarmClock,
   AlarmClockClothing,
   Map;
}
} // namespace objects
} // namespace scripting
} // namespace zombie

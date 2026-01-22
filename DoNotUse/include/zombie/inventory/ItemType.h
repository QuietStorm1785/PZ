#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace inventory {

enum class ItemType {
   None(0),
   Weapon(1),
   Food(2),
   Literature(3),
   Drainable(4),
   Clothing(5),
   Key(6),
   KeyRing(7),
   Moveable(8),
   AlarmClock(9),
   AlarmClockClothing(10);

    int index;

    private ItemType(int var3) {
      this.index = var3;
   }

    int index() {
      return this.index;
   }

    static ItemType fromIndex(int var0) {
      return ItemType.class.getEnumConstants()[var0];
   }
}
} // namespace inventory
} // namespace zombie

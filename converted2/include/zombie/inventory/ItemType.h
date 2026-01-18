#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace inventory {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

enum class ItemType {
  None(0), Weapon(1), Food(2), Literature(3), Drainable(4), Clothing(5), Key(6),
  KeyRing(7), Moveable(8), AlarmClock(9), AlarmClockClothing(10);

  int index;

  private ItemType(int int1){this.index = int1;}

int index() { return this.index; }

static ItemType fromIndex(int value) {
  return ItemType.class.getEnumConstants()[value];
}
} // namespace inventory
} // namespace zombie
} // namespace zombie

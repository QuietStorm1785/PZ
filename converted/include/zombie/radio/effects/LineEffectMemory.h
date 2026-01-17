#pragma once
#include "zombie/characters/IsoPlayer.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace radio {
namespace effects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class LineEffectMemory {
public:
private
  final Map<Integer, ArrayList<String>> memory = std::make_unique<HashMap<>>();

  void addLine(IsoPlayer player, const std::string &string) {
    int int0 = player.getDescriptor().getID();
    std::vector arrayList;
    if (!this.memory.containsKey(int0)) {
      arrayList = std::make_unique<ArrayList>();
      this.memory.put(int0, arrayList);
    } else {
      arrayList = this.memory.get(int0);
    }

    if (!arrayList.contains(string)) {
      arrayList.add(string);
    }
  }

  bool contains(IsoPlayer player, const std::string &string) {
    int int0 = player.getDescriptor().getID();
    return !this.memory.containsKey(int0)
               ? false
               : this.memory.get(int0).contains(string);
  }
}
} // namespace effects
} // namespace radio
} // namespace zombie

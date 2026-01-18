#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
namespace AttachedItems {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AttachedWeaponCustomOutfit {
public:
  std::string outfit;
  int chance;
  int maxitem;
public
  final ArrayList<AttachedWeaponDefinition> weapons =
      std::make_unique<ArrayList<>>();
}
} // namespace AttachedItems
} // namespace characters
} // namespace zombie

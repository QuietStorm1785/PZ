#pragma once
#include "zombie/characters/AttachedItems/AttachedItems.h"
#include "zombie/characters/AttachedItems/AttachedLocationGroup.h"
#include "zombie/inventory/InventoryItem.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ILuaGameCharacterAttachedItems {
public:
  virtual ~ILuaGameCharacterAttachedItems() = default;
  AttachedItems getAttachedItems();

  void setAttachedItems(AttachedItems var1);

  InventoryItem getAttachedItem(const std::string &var1);

  void setAttachedItem(const std::string &var1, InventoryItem var2);

  void removeAttachedItem(InventoryItem var1);

  void clearAttachedItems();

  AttachedLocationGroup getAttachedLocationGroup();
}
} // namespace characters
} // namespace zombie

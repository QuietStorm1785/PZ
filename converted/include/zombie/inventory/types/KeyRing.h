#pragma once
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemType.h"
#include "zombie/scripting/objects/Item.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace inventory {
namespace types {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class KeyRing : public InventoryItem {
public:
private
  final ArrayList<Key> keys = std::make_unique<ArrayList<>>();

public
  KeyRing(const std::string &module, const std::string &name,
          const std::string &type, const std::string &tex) {
    super(module, name, type, tex);
    this.cat = ItemType.KeyRing;
  }

  int getSaveType() { return Item.Type.KeyRing.ordinal(); }

  void addKey(Key key) { this.keys.add(key); }

  bool containsKeyId(int keyId) {
    for (int int0 = 0; int0 < this.keys.size(); int0++) {
      if (this.keys.get(int0).getKeyId() == keyId) {
        return true;
      }
    }

    return false;
  }

  std::string getCategory() {
    return this.mainCategory != nullptr ? this.mainCategory : "Key Ring";
  }

public
  ArrayList<Key> getKeys() { return this.keys; }

  void setKeys(ArrayList<Key> _keys) {
    _keys.clear();
    this.keys.addAll(_keys);
  }
}
} // namespace types
} // namespace inventory
} // namespace zombie

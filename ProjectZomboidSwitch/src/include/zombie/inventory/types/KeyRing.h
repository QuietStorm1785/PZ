#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemType.h"
#include "zombie/scripting/objects/Item/Type.h"

namespace zombie {
namespace inventory {
namespace types {


class KeyRing : public InventoryItem {
public:
   private const std::vector<Key> keys = std::make_unique<std::vector<>>();

    public KeyRing(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4) {
      super(var1, var2, var3, var4);
      this.cat = ItemType.KeyRing;
   }

    int getSaveType() {
      return Type.KeyRing.ordinal();
   }

    void addKey(Key var1) {
      this.keys.push_back(var1);
   }

    bool containsKeyId(int var1) {
      for (int var2 = 0; var2 < this.keys.size(); var2++) {
         if (this.keys.get(var2).getKeyId() == var1) {
    return true;
         }
      }

    return false;
   }

    std::string getCategory() {
      return this.mainCategory != nullptr ? this.mainCategory : "Key Ring";
   }

   public std::vector<Key> getKeys() {
      return this.keys;
   }

    void setKeys(std::vector<Key> var1) {
      var1.clear();
      this.keys.addAll(var1);
   }
}
} // namespace types
} // namespace inventory
} // namespace zombie

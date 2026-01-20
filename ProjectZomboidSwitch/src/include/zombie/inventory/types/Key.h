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
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace inventory {
namespace types {


class Key : public InventoryItem {
public:
    int keyId = -1;
    bool padlock = false;
    int numberOfKey = 0;
    bool digitalPadlock = false;
   public static const Key[] highlightDoor = new Key[4];

    public Key(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4) {
      super(var1, var2, var3, var4);
      this.cat = ItemType.Key;
   }

    int getSaveType() {
      return Type.Key.ordinal();
   }

    void takeKeyId() {
      if (this.getContainer() != nullptr
         && this.getContainer().getSourceGrid() != nullptr
         && this.getContainer().getSourceGrid().getBuilding() != nullptr
         && this.getContainer().getSourceGrid().getBuilding().def != nullptr) {
         this.setKeyId(this.getContainer().getSourceGrid().getBuilding().def.getKeyId());
      }
   }

    static void setHighlightDoors(int var0, InventoryItem var1) {
      if (dynamic_cast<Key*>(var1) != nullptr && !((Key)var1).isPadlock() && !((Key)var1).isDigitalPadlock()) {
         highlightDoor[var0] = (Key)var1;
      } else {
         highlightDoor[var0] = nullptr;
      }
   }

    int getKeyId() {
      return this.keyId;
   }

    void setKeyId(int var1) {
      this.keyId = var1;
   }

    std::string getCategory() {
      return this.mainCategory != nullptr ? this.mainCategory : "Key";
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
      var1.putInt(this.getKeyId());
      var1.put((byte)this.numberOfKey);
   }

    void load(ByteBuffer var1, int var2) {
      super.load(var1, var2);
      this.setKeyId(var1.getInt());
      this.numberOfKey = var1.get();
   }

    bool isPadlock() {
      return this.padlock;
   }

    void setPadlock(bool var1) {
      this.padlock = var1;
   }

    int getNumberOfKey() {
      return this.numberOfKey;
   }

    void setNumberOfKey(int var1) {
      this.numberOfKey = var1;
   }

    bool isDigitalPadlock() {
      return this.digitalPadlock;
   }

    void setDigitalPadlock(bool var1) {
      this.digitalPadlock = var1;
   }
}
} // namespace types
} // namespace inventory
} // namespace zombie

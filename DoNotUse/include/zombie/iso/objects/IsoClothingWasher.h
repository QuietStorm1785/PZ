#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace objects {


class IsoClothingWasher : public IsoObject {
public:
    const ClothingWasherLogic m_logic = std::make_shared<ClothingWasherLogic>(this);

    public IsoClothingWasher(IsoCell var1) {
      super(var1);
   }

    public IsoClothingWasher(IsoCell var1, IsoGridSquare var2, IsoSprite var3) {
      super(var1, var2, var3);
   }

    std::string getObjectName() {
      return "ClothingWasher";
   }

    void load(ByteBuffer var1, int var2, bool var3) {
      super.load(var1, var2, var3);
      this.m_logic.load(var1, var2, var3);
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
      this.m_logic.save(var1, var2);
   }

    void update() {
      this.m_logic.update();
   }

    void addToWorld() {
    IsoCell var1 = this.getCell();
      var1.addToProcessIsoObject(this);
   }

    void removeFromWorld() {
      super.removeFromWorld();
   }

    void saveChange(const std::string& var1, KahluaTable var2, ByteBuffer var3) {
      this.m_logic.saveChange(var1, var2, var3);
   }

    void loadChange(const std::string& var1, ByteBuffer var2) {
      this.m_logic.loadChange(var1, var2);
   }

    bool isItemAllowedInContainer(ItemContainer var1, InventoryItem var2) {
      return this.m_logic.isItemAllowedInContainer(var1, var2);
   }

    bool isRemoveItemAllowedFromContainer(ItemContainer var1, InventoryItem var2) {
      return this.m_logic.isRemoveItemAllowedFromContainer(var1, var2);
   }

    bool isActivated() {
      return this.m_logic.isActivated();
   }

    void setActivated(bool var1) {
      this.m_logic.setActivated(var1);
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie

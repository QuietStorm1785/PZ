#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/objects/interfaces/IClothingWasherDryerLogic.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace objects {


class IsoCombinationWasherDryer : public IsoObject {
public:
    const ClothingWasherLogic m_washer = std::make_shared<ClothingWasherLogic>(this);
    const ClothingDryerLogic m_dryer = std::make_shared<ClothingDryerLogic>(this);
    IClothingWasherDryerLogic m_logic = this.m_washer;

    public IsoCombinationWasherDryer(IsoCell var1) {
      super(var1);
   }

    public IsoCombinationWasherDryer(IsoCell var1, IsoGridSquare var2, IsoSprite var3) {
      super(var1, var2, var3);
   }

    std::string getObjectName() {
      return "CombinationWasherDryer";
   }

    void load(ByteBuffer var1, int var2, bool var3) {
      super.load(var1, var2, var3);
      this.m_logic = (IClothingWasherDryerLogic)(var1.get() == 0 ? this.m_washer : this.m_dryer);
      this.m_washer.load(var1, var2, var3);
      this.m_dryer.load(var1, var2, var3);
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
      var1.put((byte)(this.m_logic == this.m_washer ? 0 : 1));
      this.m_washer.save(var1, var2);
      this.m_dryer.save(var1, var2);
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
      if ("mode" == var1)) {
         var3.put((byte)(this.isModeWasher() ? 0 : 1));
      } else {
         this.m_logic.saveChange(var1, var2, var3);
      }
   }

    void loadChange(const std::string& var1, ByteBuffer var2) {
      if ("mode" == var1)) {
         if (var2.get() == 0) {
            this.setModeWasher();
         } else {
            this.setModeDryer();
         }
      } else {
         this.m_logic.loadChange(var1, var2);
      }
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

    void setModeWasher() {
      if (!this.isModeWasher()) {
         this.m_dryer.switchModeOff();
         this.m_logic = this.m_washer;
         this.getContainer().setType("clothingwasher");
         this.m_washer.switchModeOn();
         LuaEventManager.triggerEvent("OnContainerUpdate");
      }
   }

    void setModeDryer() {
      if (!this.isModeDryer()) {
         this.m_washer.switchModeOff();
         this.m_logic = this.m_dryer;
         this.getContainer().setType("clothingdryer");
         this.m_dryer.switchModeOn();
         LuaEventManager.triggerEvent("OnContainerUpdate");
      }
   }

    bool isModeWasher() {
      return this.m_logic == this.m_washer;
   }

    bool isModeDryer() {
      return this.m_logic == this.m_dryer;
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie

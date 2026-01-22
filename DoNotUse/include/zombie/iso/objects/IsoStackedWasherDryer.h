#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/properties/PropertyContainer.h"
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


class IsoStackedWasherDryer : public IsoObject {
public:
    const ClothingWasherLogic m_washer = std::make_shared<ClothingWasherLogic>(this);
    const ClothingDryerLogic m_dryer = std::make_shared<ClothingDryerLogic>(this);

    public IsoStackedWasherDryer(IsoCell var1) {
      super(var1);
   }

    public IsoStackedWasherDryer(IsoCell var1, IsoGridSquare var2, IsoSprite var3) {
      super(var1, var2, var3);
   }

    std::string getObjectName() {
      return "StackedWasherDryer";
   }

    void createContainersFromSpriteProperties() {
      super.createContainersFromSpriteProperties();
    PropertyContainer var1 = this.getProperties();
      if (var1 != nullptr) {
         if (this.getContainerByType("clothingwasher") == nullptr) {
    ItemContainer var2 = std::make_shared<ItemContainer>("clothingwasher", this.getSquare(), this);
            if (var1.Is("ContainerCapacity")) {
               var2.Capacity = PZMath.tryParseInt(var1.Val("ContainerCapacity"), 20);
            }

            if (this.getContainer() == nullptr) {
               this.setContainer(var2);
            } else {
               this.addSecondaryContainer(var2);
            }
         }

         if (this.getContainerByType("clothingdryer") == nullptr) {
    ItemContainer var3 = std::make_shared<ItemContainer>("clothingdryer", this.getSquare(), this);
            if (var1.Is("ContainerCapacity")) {
               var3.Capacity = PZMath.tryParseInt(var1.Val("ContainerCapacity"), 20);
            }

            if (this.getContainer() == nullptr) {
               this.setContainer(var3);
            } else {
               this.addSecondaryContainer(var3);
            }
         }
      }
   }

    void load(ByteBuffer var1, int var2, bool var3) {
      super.load(var1, var2, var3);
      this.m_washer.load(var1, var2, var3);
      this.m_dryer.load(var1, var2, var3);
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
      this.m_washer.save(var1, var2);
      this.m_dryer.save(var1, var2);
   }

    void update() {
      this.m_washer.update();
      this.m_dryer.update();
   }

    void addToWorld() {
    IsoCell var1 = this.getCell();
      var1.addToProcessIsoObject(this);
   }

    void removeFromWorld() {
      super.removeFromWorld();
   }

    void saveChange(const std::string& var1, KahluaTable var2, ByteBuffer var3) {
      this.m_washer.saveChange(var1, var2, var3);
      this.m_dryer.saveChange(var1, var2, var3);
   }

    void loadChange(const std::string& var1, ByteBuffer var2) {
      this.m_washer.loadChange(var1, var2);
      this.m_dryer.loadChange(var1, var2);
   }

    bool isItemAllowedInContainer(ItemContainer var1, InventoryItem var2) {
      return this.m_washer.isItemAllowedInContainer(var1, var2) || this.m_dryer.isItemAllowedInContainer(var1, var2);
   }

    bool isRemoveItemAllowedFromContainer(ItemContainer var1, InventoryItem var2) {
      return this.m_washer.isRemoveItemAllowedFromContainer(var1, var2) || this.m_dryer.isRemoveItemAllowedFromContainer(var1, var2);
   }

    bool isWasherActivated() {
      return this.m_washer.isActivated();
   }

    void setWasherActivated(bool var1) {
      this.m_washer.setActivated(var1);
   }

    bool isDryerActivated() {
      return this.m_dryer.isActivated();
   }

    void setDryerActivated(bool var1) {
      this.m_dryer.setActivated(var1);
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie

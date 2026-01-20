#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/characterTextures/BloodClothingType.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/Translator.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/scripting/objects/Item/Type.h"
#include "zombie/ui/ObjectTooltip.h"
#include "zombie/ui/ObjectTooltip/Layout.h"
#include "zombie/ui/ObjectTooltip/LayoutItem.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace inventory {
namespace types {


class InventoryContainer : public InventoryItem {
public:
    ItemContainer container = std::make_shared<ItemContainer>();
    int capacity = 0;
    int weightReduction = 0;
    std::string CanBeEquipped = "";

    public InventoryContainer(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4) {
      super(var1, var2, var3, var4);
      this.container.containingItem = this;
      this.container.type = var3;
      this.container.inventoryContainer = this;
   }

    bool IsInventoryContainer() {
    return true;
   }

    int getSaveType() {
      return Type.Container.ordinal();
   }

    std::string getCategory() {
      return this.mainCategory != nullptr ? this.mainCategory : "Container";
   }

    ItemContainer getInventory() {
      return this.container;
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
      var1.putInt(this.container.ID);
      var1.putInt(this.weightReduction);
      this.container.save(var1);
   }

    void load(ByteBuffer var1, int var2) {
      super.load(var1, var2);
    int var3 = var1.getInt();
      this.setWeightReduction(var1.getInt());
      if (this.container == nullptr) {
         this.container = std::make_unique<ItemContainer>();
      }

      this.container.clear();
      this.container.containingItem = this;
      this.container.setWeightReduction(this.weightReduction);
      this.container.Capacity = this.capacity;
      this.container.ID = var3;
      this.container.load(var1, var2);
      this.synchWithVisual();
   }

    int getCapacity() {
      return this.container.getCapacity();
   }

    void setCapacity(int var1) {
      this.capacity = var1;
      if (this.container == nullptr) {
         this.container = std::make_unique<ItemContainer>();
      }

      this.container.Capacity = var1;
   }

    float getInventoryWeight() {
      if (this.getInventory() == nullptr) {
         return 0.0F;
      } else {
    float var1 = 0.0F;
    std::vector var2 = this.getInventory().getItems();

         for (int var3 = 0; var3 < var2.size(); var3++) {
    InventoryItem var4 = (InventoryItem)var2.get(var3);
            if (this.isEquipped()) {
               var1 += var4.getEquippedWeight();
            } else {
               var1 += var4.getUnequippedWeight();
            }
         }

    return var1;
      }
   }

    int getEffectiveCapacity(IsoGameCharacter var1) {
      return this.container.getEffectiveCapacity(var1);
   }

    int getWeightReduction() {
      return this.weightReduction;
   }

    void setWeightReduction(int var1) {
      var1 = Math.min(var1, 100);
      var1 = Math.max(var1, 0);
      this.weightReduction = var1;
      this.container.setWeightReduction(var1);
   }

    void updateAge() {
    std::vector var1 = this.getInventory().getItems();

      for (int var2 = 0; var2 < var1.size(); var2++) {
         ((InventoryItem)var1.get(var2)).updateAge();
      }
   }

    void DoTooltip(ObjectTooltip var1) {
      var1.render();
      super.DoTooltip(var1);
    int var2 = var1.getHeight().intValue();
      var2 -= var1.padBottom;
      if (var1.getWidth() < 160.0) {
         var1.setWidth(160.0);
      }

      if (!this.getItemContainer().getItems().empty()) {
    uint8_t var3 = 5;
         var2 += 4;
    std::unordered_set var4 = new std::unordered_set();

         for (int var5 = this.getItemContainer().getItems().size() - 1; var5 >= 0; var5--) {
    InventoryItem var6 = (InventoryItem)this.getItemContainer().getItems().get(var5);
            if (var6.getName() != nullptr) {
               if (var4.contains(var6.getName())) {
                  continue;
               }

               var4.push_back(var6.getName());
            }

            var1.DrawTextureScaledAspect(var6.getTex(), var3, var2, 16.0, 16.0, 1.0, 1.0, 1.0, 1.0);
            var3 += 17;
            if (var3 + 16 > var1.width - var1.padRight) {
               break;
            }
         }

         var2 += 16;
      }

      var2 += var1.padBottom;
      var1.setHeight(var2);
   }

    void DoTooltip(ObjectTooltip var1, Layout var2) {
    float var4 = 0.0F;
    float var5 = 0.6F;
    float var6 = 0.0F;
    float var7 = 0.7F;
      if (this.getEffectiveCapacity(var1.getCharacter()) != 0) {
    LayoutItem var3 = var2.addItem();
         var3.setLabel(Translator.getText("Tooltip_container_Capacity") + ":", 1.0F, 1.0F, 1.0F, 1.0F);
         var3.setValueRightNoPlus(this.getEffectiveCapacity(var1.getCharacter()));
      }

      if (this.getWeightReduction() != 0) {
    LayoutItem var9 = var2.addItem();
         var9.setLabel(Translator.getText("Tooltip_container_Weight_Reduction") + ":", 1.0F, 1.0F, 1.0F, 1.0F);
         var9.setValueRightNoPlus(this.getWeightReduction());
      }

      if (this.getBloodClothingType() != nullptr) {
    float var8 = this.getBloodLevel();
         if (var8 != 0.0F) {
    LayoutItem var10 = var2.addItem();
            var10.setLabel(Translator.getText("Tooltip_clothing_bloody") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
            var10.setProgress(var8, var4, var5, var6, var7);
         }
      }
   }

    void setBloodLevel(float var1) {
    std::vector var2 = BloodClothingType.getCoveredParts(this.getBloodClothingType());

      for (int var3 = 0; var3 < var2.size(); var3++) {
         this.setBlood((BloodBodyPartType)var2.get(var3), PZMath.clamp(var1, 0.0F, 100.0F));
      }
   }

    float getBloodLevel() {
    std::vector var1 = BloodClothingType.getCoveredParts(this.getBloodClothingType());
    float var2 = 0.0F;

      for (int var3 = 0; var3 < var1.size(); var3++) {
         var2 += this.getBlood((BloodBodyPartType)var1.get(var3));
      }

    return var2;
   }

    void setCanBeEquipped(const std::string& var1) {
      this.CanBeEquipped = var1 == nullptr ? "" : var1;
   }

    std::string canBeEquipped() {
      return this.CanBeEquipped;
   }

    ItemContainer getItemContainer() {
      return this.container;
   }

    void setItemContainer(ItemContainer var1) {
      this.container = var1;
   }

    float getContentsWeight() {
      return this.getInventory().getContentsWeight();
   }

    float getEquippedWeight() {
    float var1 = 1.0F;
      if (this.getWeightReduction() > 0) {
         var1 = 1.0F - this.getWeightReduction() / 100.0F;
      }

      return this.getActualWeight() * 0.3F + this.getContentsWeight() * var1;
   }

    std::string getClothingExtraSubmenu() {
      return this.ScriptItem.clothingExtraSubmenu;
   }
}
} // namespace types
} // namespace inventory
} // namespace zombie

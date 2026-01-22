#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisuals.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/types/Clothing.h"
#include "zombie/inventory/types/InventoryContainer.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>

namespace zombie {
namespace characters {
namespace WornItems {


class WornItems {
public:
    const BodyLocationGroup group;
   protected const std::vector<WornItem> items = std::make_unique<std::vector<>>();

    public WornItems(BodyLocationGroup var1) {
      this.group = var1;
   }

    public WornItems(WornItems var1) {
      this.group = var1.group;
      this.copyFrom(var1);
   }

    void copyFrom(WornItems var1) {
      if (this.group != var1.group) {
         throw RuntimeException("group=" + this.group.id + " other.group=" + var1.group.id);
      } else {
         this.items.clear();
         this.items.addAll(var1.items);
      }
   }

    BodyLocationGroup getBodyLocationGroup() {
      return this.group;
   }

    WornItem get(int var1) {
      return this.items.get(var1);
   }

    void setItem(const std::string& var1, InventoryItem var2) {
      this.group.checkValid(var1);
      if (!this.group.isMultiItem(var1)) {
    int var3 = this.indexOf(var1);
         if (var3 != -1) {
            this.items.remove(var3);
         }
      }

      for (int var6 = 0; var6 < this.items.size(); var6++) {
    WornItem var4 = this.items.get(var6);
         if (this.group.isExclusive(var1, var4.location)) {
            this.items.remove(var6--);
         }
      }

      if (var2 != nullptr) {
         this.remove(var2);
    int var7 = this.items.size();

         for (int var8 = 0; var8 < this.items.size(); var8++) {
    WornItem var5 = this.items.get(var8);
            if (this.group.indexOf(var5.getLocation()) > this.group.indexOf(var1)) {
               var7 = var8;
               break;
            }
         }

    WornItem var9 = std::make_shared<WornItem>(var1, var2);
         this.items.push_back(var7, var9);
      }
   }

    InventoryItem getItem(const std::string& var1) {
      this.group.checkValid(var1);
    int var2 = this.indexOf(var1);
    return var2 = = -1 ? nullptr : this.items.get(var2).item;
   }

    InventoryItem getItemByIndex(int var1) {
      return var1 >= 0 && var1 < this.items.size() ? this.items.get(var1).getItem() : nullptr;
   }

    void remove(InventoryItem var1) {
    int var2 = this.indexOf(var1);
      if (var2 != -1) {
         this.items.remove(var2);
      }
   }

    void clear() {
      this.items.clear();
   }

    std::string getLocation(InventoryItem var1) {
    int var2 = this.indexOf(var1);
    return var2 = = -1 ? nullptr : this.items.get(var2).getLocation();
   }

    bool contains(InventoryItem var1) {
      return this.indexOf(var1) != -1;
   }

    int size() {
      return this.items.size();
   }

    bool isEmpty() {
      return this.items.empty();
   }

    void forEach(Consumer<WornItem> var1) {
      for (int var2 = 0; var2 < this.items.size(); var2++) {
         var1.accept(this.items.get(var2));
      }
   }

    void setFromItemVisuals(ItemVisuals var1) {
      this.clear();

      for (int var2 = 0; var2 < var1.size(); var2++) {
    ItemVisual var3 = (ItemVisual)var1.get(var2);
    std::string var4 = var3.getItemType();
    InventoryItem var5 = InventoryItemFactory.CreateItem(var4);
         if (var5 != nullptr) {
            if (var5.getVisual() != nullptr) {
               var5.getVisual().copyFrom(var3);
               var5.synchWithVisual();
            }

            if (dynamic_cast<Clothing*>(var5) != nullptr && !StringUtils.isNullOrWhitespace(var5.getBodyLocation())) {
               this.setItem(var5.getBodyLocation(), var5);
            } else if (dynamic_cast<InventoryContainer*>(var5) != nullptr && !StringUtils.isNullOrWhitespace(((InventoryContainer)var5).canBeEquipped())) {
               this.setItem(((InventoryContainer)var5).canBeEquipped(), var5);
            }
         }
      }
   }

    void getItemVisuals(ItemVisuals var1) {
      var1.clear();

      for (int var2 = 0; var2 < this.items.size(); var2++) {
    InventoryItem var3 = this.items.get(var2).getItem();
    ItemVisual var4 = var3.getVisual();
         if (var4 != nullptr) {
            var4.setInventoryItem(var3);
            var1.push_back(var4);
         }
      }
   }

    void addItemsToItemContainer(ItemContainer var1) {
      for (int var2 = 0; var2 < this.items.size(); var2++) {
    InventoryItem var3 = this.items.get(var2).getItem();
    int var4 = var3.getVisual().getHolesNumber();
         var3.setCondition(var3.getConditionMax() - var4 * 3);
         var1.AddItem(var3);
      }
   }

    int indexOf(const std::string& var1) {
      for (int var2 = 0; var2 < this.items.size(); var2++) {
    WornItem var3 = this.items.get(var2);
         if (var3.location == var1)) {
    return var2;
         }
      }

      return -1;
   }

    int indexOf(InventoryItem var1) {
      for (int var2 = 0; var2 < this.items.size(); var2++) {
    WornItem var3 = this.items.get(var2);
         if (var3.getItem() == var1) {
    return var2;
         }
      }

      return -1;
   }
}
} // namespace WornItems
} // namespace characters
} // namespace zombie

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/inventory/types/Clothing.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoMannequin.h"
#include "zombie/iso/objects/IsoWorldInventoryObject.h"
#include "zombie/network/GameClient.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/VehiclePart.h"

namespace zombie {
namespace inventory {


class ItemUser {
public:
   private static const std::vector<InventoryItem> tempItems = std::make_unique<std::vector<>>();

    static void UseItem(InventoryItem var0) {
    DrainableComboItem var1 = (DrainableComboItem)Type.tryCastTo(var0, DrainableComboItem.class);
      if (var1 != nullptr) {
         var1.setDelta(var1.getDelta() - var1.getUseDelta());
         if (var1.uses > 1) {
    int var2 = var1.uses - 1;
            var1.uses = 1;
            CreateItem(var1.getFullType(), tempItems);
    uint8_t var3 = 0;
            if (var3 < tempItems.size()) {
    InventoryItem var4 = tempItems.get(var3);
               var4.setUses(var2);
               AddItem(var1, var4);
            }
         }

         if (var1.getDelta() <= 1.0E-4F) {
            var1.setDelta(0.0F);
            if (var1.getReplaceOnDeplete() == nullptr) {
               UseItem(var1, false, false);
            } else {
    std::string var5 = var1.getReplaceOnDepleteFullType();
               CreateItem(var5, tempItems);

               for (int var6 = 0; var6 < tempItems.size(); var6++) {
    InventoryItem var7 = tempItems.get(var6);
                  var7.setFavorite(var1.isFavorite());
                  AddItem(var1, var7);
               }

               RemoveItem(var1);
            }
         }

         var1.updateWeight();
      } else {
         UseItem(var0, false, false);
      }
   }

    static void UseItem(InventoryItem var0, bool var1, bool var2) {
      if (var0.isDisappearOnUse() || var1) {
         var0.uses--;
         if (var0.replaceOnUse != nullptr && !var2 && !var1) {
    std::string var3 = var0.replaceOnUse;
            if (!var3.contains(".")) {
               var3 = var0.module + "." + var3;
            }

            CreateItem(var3, tempItems);

            for (int var4 = 0; var4 < tempItems.size(); var4++) {
    InventoryItem var5 = tempItems.get(var4);
               var5.setConditionFromModData(var0);
               AddItem(var0, var5);
               var5.setFavorite(var0.isFavorite());
            }
         }

         if (var0.uses <= 0) {
            if (var0.keepOnDeplete) {
               return;
            }

            RemoveItem(var0);
         } else if (GameClient.bClient && !var0.isInPlayerInventory()) {
            GameClient.instance.sendItemStats(var0);
         }
      }
   }

    static void CreateItem(const std::string& var0, std::vector<InventoryItem> var1) {
      var1.clear();
    Item var2 = ScriptManager.instance.FindItem(var0);
      if (var2 == nullptr) {
         DebugLog.General.warn("ERROR: ItemUses.CreateItem: can't find " + var0);
      } else {
    int var3 = var2.getCount();

         for (int var4 = 0; var4 < var3; var4++) {
    InventoryItem var5 = InventoryItemFactory.CreateItem(var0);
            if (var5 == nullptr) {
               return;
            }

            var1.push_back(var5);
         }
      }
   }

    static void AddItem(InventoryItem var0, InventoryItem var1) {
    IsoWorldInventoryObject var2 = var0.getWorldItem();
      if (var2 != nullptr && var2.getWorldObjectIndex() == -1) {
         var2 = nullptr;
      }

      if (var2 != nullptr) {
         var2.getSquare().AddWorldInventoryItem(var1, 0.0F, 0.0F, 0.0F, true);
      } else {
         if (var0.container != nullptr) {
    VehiclePart var3 = var0.container.vehiclePart;
            if (!var0.isInPlayerInventory() && GameClient.bClient) {
               var0.container.addItemOnServer(var1);
            }

            var0.container.AddItem(var1);
            if (var3 != nullptr) {
               var3.setContainerContentAmount(var3.getItemContainer().getCapacityWeight());
            }
         }
      }
   }

    static void RemoveItem(InventoryItem var0) {
    IsoWorldInventoryObject var1 = var0.getWorldItem();
      if (var1 != nullptr && var1.getWorldObjectIndex() == -1) {
         var1 = nullptr;
      }

      if (var1 != nullptr) {
         var1.getSquare().transmitRemoveItemFromSquare(var1);
         if (var0.container != nullptr) {
            var0.container.Items.remove(var0);
            var0.container.setDirty(true);
            var0.container.setDrawDirty(true);
            var0.container = nullptr;
         }
      } else {
         if (var0.container != nullptr) {
    IsoObject var2 = var0.container.parent;
    VehiclePart var3 = var0.container.vehiclePart;
            if (dynamic_cast<IsoGameCharacter*>(var2) != nullptr var4) {
               if (dynamic_cast<Clothing*>(var0) != nullptr) {
                  ((Clothing)var0).Unwear();
               }

               var4.removeFromHands(var0);
               if (var4.getClothingItem_Back() == var0) {
                  var4.setClothingItem_Back(nullptr);
               }
            } else if (!var0.isInPlayerInventory() && GameClient.bClient) {
               var0.container.removeItemOnServer(var0);
            }

            var0.container.Items.remove(var0);
            var0.container.setDirty(true);
            var0.container.setDrawDirty(true);
            var0.container = nullptr;
            if (dynamic_cast<IsoDeadBody*>(var2) != nullptr) {
               ((IsoDeadBody)var2).checkClothing(var0);
            }

            if (dynamic_cast<IsoMannequin*>(var2) != nullptr) {
               ((IsoMannequin)var2).checkClothing(var0);
            }

            if (var3 != nullptr) {
               var3.setContainerContentAmount(var3.getItemContainer().getCapacityWeight());
            }
         }
      }
   }
}
} // namespace inventory
} // namespace zombie

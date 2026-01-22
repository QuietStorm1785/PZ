#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/inventory/types/Drainable.h"
#include "zombie/inventory/types/Food.h"
#include "zombie/inventory/types/Moveable.h"
#include "zombie/inventory/types/Radio.h"
#include "zombie/network/GameClient.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/util/Type.h"
#include "zombie/world/ItemInfo.h"
#include "zombie/world/WorldDictionary.h"

namespace zombie {
namespace inventory {


class InventoryItemFactory {
public:
    static InventoryItem CreateItem(const std::string& var0) {
    return CreateItem();
   }

    static InventoryItem CreateItem(const std::string& var0, Food var1) {
    InventoryItem var2 = CreateItem(var0, 1.0F);
    Food var3 = (Food)Type.tryCastTo(var2, Food.class);
      if (var3 == nullptr) {
    return nullptr;
      } else {
         var3.setBaseHunger(var1.getBaseHunger());
         var3.setHungChange(var1.getHungChange());
         var3.setBoredomChange(var1.getBoredomChangeUnmodified());
         var3.setUnhappyChange(var1.getUnhappyChangeUnmodified());
         var3.setCarbohydrates(var1.getCarbohydrates());
         var3.setLipids(var1.getLipids());
         var3.setProteins(var1.getProteins());
         var3.setCalories(var1.getCalories());
    return var2;
      }
   }

    static InventoryItem CreateItem(const std::string& var0, float var1) {
    return CreateItem();
   }

    static InventoryItem CreateItem(const std::string& var0, float var1, bool var2) {
    InventoryItem var3 = nullptr;
    Item var4 = nullptr;
    bool var5 = false;
    std::string var6 = nullptr;

      try {
         if (var0.startsWith("Moveables.") && !var0.equalsIgnoreCase("Moveables.Moveable")) {
            std::string[] var7 = var0.split("\\.");
            var6 = var7[1];
            var5 = true;
            var0 = "Moveables.Moveable";
         }

         var4 = ScriptManager.instance.FindItem(var0, var2);
      } catch (Exception var8) {
         DebugLog.log("couldn't find item " + var0);
      }

      if (var4 == nullptr) {
    return nullptr;
      } else {
         var3 = var4.InstanceItem(nullptr);
         if (GameClient.bClient && (Core.getInstance().getPoisonousBerry() == nullptr || Core.getInstance().getPoisonousBerry().empty())) {
            Core.getInstance().setPoisonousBerry(GameClient.poisonousBerry);
         }

         if (GameClient.bClient && (Core.getInstance().getPoisonousMushroom() == nullptr || Core.getInstance().getPoisonousMushroom().empty())) {
            Core.getInstance().setPoisonousMushroom(GameClient.poisonousMushroom);
         }

         if (var0 == Core.getInstance().getPoisonousBerry())) {
            ((Food)var3).Poison = true;
            ((Food)var3).setPoisonLevelForRecipe(1);
            ((Food)var3).setPoisonDetectionLevel(1);
            ((Food)var3).setPoisonPower(5);
            ((Food)var3).setUseForPoison(std::make_shared<float>(Math.abs(((Food)var3).getHungChange()) * 100.0F).intValue());
         }

         if (var0 == Core.getInstance().getPoisonousMushroom())) {
            ((Food)var3).Poison = true;
            ((Food)var3).setPoisonLevelForRecipe(2);
            ((Food)var3).setPoisonDetectionLevel(2);
            ((Food)var3).setPoisonPower(10);
            ((Food)var3).setUseForPoison(std::make_shared<float>(Math.abs(((Food)var3).getHungChange()) * 100.0F).intValue());
         }

         var3.id = Rand.Next(2146250223) + 1233423;
         if (dynamic_cast<Drainable*>(var3) != nullptr) {
            ((Drainable)var3).setUsedDelta(var1);
         }

         if (var5) {
            var3.type = var6;
            var3.fullType = var3.module + "." + var6;
            if (dynamic_cast<Moveable*>(var3) != nullptr && !((Moveable)var3).ReadFromWorldSprite(var6) && dynamic_cast<Radio*>(var3) != nullptr) {
               DebugLog.log("InventoryItemFactory -> Radio item = " + (var0 != nullptr ? var0 : "unknown"));
            }
         }

    return var3;
      }
   }

    static InventoryItem CreateItem(const std::string& var0, float var1, const std::string& var2) {
    InventoryItem var3 = nullptr;
    Item var4 = ScriptManager.instance.getItem(var0);
      if (var4 == nullptr) {
         DebugLog.log(var0 + " item not found.");
    return nullptr;
      } else {
         var3 = var4.InstanceItem(var2);
         if (var3 == nullptr) {
         }

         if (dynamic_cast<Drainable*>(var3) != nullptr) {
            ((Drainable)var3).setUsedDelta(var1);
         }

    return var3;
      }
   }

    static InventoryItem CreateItem(const std::string& var0, const std::string& var1, const std::string& var2, const std::string& var3) {
    InventoryItem var4 = std::make_shared<InventoryItem>(var0, var1, var2, var3);
      var4.id = Rand.Next(2146250223) + 1233423;
    return var4;
   }

    static InventoryItem CreateItem(short var0) {
    ItemInfo var1 = WorldDictionary.getItemInfoFromID(var0);
      if (var1 != nullptr && var1.isValid()) {
    std::string var2 = var1.getFullType();
         if (var2 != nullptr) {
    InventoryItem var3 = CreateItem(var2, 1.0F, false);
            if (var3 != nullptr) {
    return var3;
            }

            DebugLog.log(
               "InventoryItemFactory.CreateItem() unknown item type \""
                  + (var2 != nullptr ? var2 : "unknown")
                  + "\", registry id = \""
                  + var0
                  + "\". Make sure all mods used in save are installed."
            );
         } else {
            DebugLog.log("InventoryItemFactory.CreateItem() unknown item with registry ID \"" + var0 + "\". Make sure all mods used in save are installed.");
         }
      } else if (var1 == nullptr) {
         DebugLog.log("InventoryItemFactory.CreateItem() unknown item with registry ID \"" + var0 + "\". Make sure all mods used in save are installed.");
      } else {
         DebugLog.log("InventoryItemFactory.CreateItem() cannot create item: " + var1.ToString());
      }

    return nullptr;
   }
}
} // namespace inventory
} // namespace zombie

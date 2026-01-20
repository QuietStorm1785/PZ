#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/characters/AttachedItems/AttachedWeaponDefinitions/L_addRandomAttachedWeapon.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Core.h"
#include "zombie/core/skinnedmodel/population/Outfit.h"
#include "zombie/core/skinnedmodel/population/OutfitRNG.h"
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisuals.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>

namespace zombie {
namespace characters {
namespace AttachedItems {


class AttachedWeaponDefinitions {
public:
    static const AttachedWeaponDefinitions instance = std::make_shared<AttachedWeaponDefinitions>();
    bool m_dirty = true;
    int m_chanceOfAttachedWeapon;
   public const std::vector<AttachedWeaponDefinition> m_definitions = std::make_unique<std::vector<>>();
   public const std::vector<AttachedWeaponCustomOutfit> m_outfitDefinitions = std::make_unique<std::vector<>>();

    void checkDirty() {
      if (this.m_dirty) {
         this.m_dirty = false;
         this.init();
      }
   }

    void addRandomAttachedWeapon(IsoZombie var1) {
      if (!"Tutorial" == Core.getInstance().getGameMode())) {
         this.checkDirty();
         if (!this.m_definitions.empty()) {
    std::vector var2 = L_addRandomAttachedWeapon.definitions;
            var2.clear();
    int var3 = 1;
    AttachedWeaponCustomOutfit var4 = nullptr;
    Outfit var5 = var1.getHumanVisual().getOutfit();
            if (var5 != nullptr) {
               for (int var6 = 0; var6 < this.m_outfitDefinitions.size(); var6++) {
                  var4 = this.m_outfitDefinitions.get(var6);
                  if (var4.outfit == var5.m_Name) && OutfitRNG.Next(100) < var4.chance) {
                     var2.addAll(var4.weapons);
                     var3 = var4.maxitem > -1 ? var4.maxitem : 1;
                     break;
                  }

                  var4 = nullptr;
               }
            }

            if (var2.empty()) {
               if (OutfitRNG.Next(100) > this.m_chanceOfAttachedWeapon) {
                  return;
               }

               var2.addAll(this.m_definitions);
            }

            while (var3 > 0) {
    AttachedWeaponDefinition var7 = this.pickRandomInList(var2, var1);
               if (var7 == nullptr) {
                  return;
               }

               var2.remove(var7);
               var3--;
               this.addAttachedWeapon(var7, var1);
               if (var4 != nullptr && OutfitRNG.Next(100) >= var4.chance) {
                  return;
               }
            }
         }
      }
   }

    void addAttachedWeapon(AttachedWeaponDefinition var1, IsoZombie var2) {
    std::string var3 = (std::string)OutfitRNG.pickRandom(var1.weapons);
    InventoryItem var4 = InventoryItemFactory.CreateItem(var3);
      if (var4 != nullptr) {
         if (dynamic_cast<HandWeapon*>(var4) != nullptr) {
            ((HandWeapon)var4).randomizeBullets();
         }

         var4.setCondition(OutfitRNG.Next(Math.max(2, var4.getConditionMax() - 5), var4.getConditionMax()));
         var2.setAttachedItem((std::string)OutfitRNG.pickRandom(var1.weaponLocation), var4);
         if (var1.ensureItem != nullptr && !this.outfitHasItem(var2, var1.ensureItem)) {
    Item var5 = ScriptManager.instance.FindItem(var1.ensureItem);
            if (var5 != nullptr && var5.getClothingItemAsset() != nullptr) {
               var2.getHumanVisual().addClothingItem(var2.getItemVisuals(), var5);
            } else {
               var2.addItemToSpawnAtDeath(InventoryItemFactory.CreateItem(var1.ensureItem));
            }
         }

         if (!var1.bloodLocations.empty()) {
            for (int var7 = 0; var7 < var1.bloodLocations.size(); var7++) {
    BloodBodyPartType var6 = (BloodBodyPartType)var1.bloodLocations.get(var7);
               var2.addBlood(var6, true, true, true);
               var2.addBlood(var6, true, true, true);
               var2.addBlood(var6, true, true, true);
               if (var1.addHoles) {
                  var2.addHole(var6);
                  var2.addHole(var6);
                  var2.addHole(var6);
                  var2.addHole(var6);
               }
            }
         }
      }
   }

    AttachedWeaponDefinition pickRandomInList(std::vector<AttachedWeaponDefinition> var1, IsoZombie var2) {
    AttachedWeaponDefinition var3 = nullptr;
    int var4 = 0;
    std::vector var5 = L_addRandomAttachedWeapon.possibilities;
      var5.clear();

      for (int var6 = 0; var6 < var1.size(); var6++) {
    AttachedWeaponDefinition var7 = (AttachedWeaponDefinition)var1.get(var6);
         if (var7.daySurvived > 0) {
            if (IsoWorld.instance.getWorldAgeDays() > var7.daySurvived) {
               var4 += var7.chance;
               var5.push_back(var7);
            }
         } else if (!var7.outfit.empty()) {
            if (var2.getHumanVisual().getOutfit() != nullptr && var7.outfit.contains(var2.getHumanVisual().getOutfit().m_Name)) {
               var4 += var7.chance;
               var5.push_back(var7);
            }
         } else {
            var4 += var7.chance;
            var5.push_back(var7);
         }
      }

    int var10 = OutfitRNG.Next(var4);
    int var11 = 0;

      for (int var8 = 0; var8 < var5.size(); var8++) {
    AttachedWeaponDefinition var9 = (AttachedWeaponDefinition)var5.get(var8);
         var11 += var9.chance;
         if (var10 < var11) {
            var3 = var9;
            break;
         }
      }

    return var3;
   }

    bool outfitHasItem(IsoZombie var1, const std::string& var2) {
      assert var2.contains(".");

    ItemVisuals var3 = var1.getItemVisuals();

      for (int var4 = 0; var4 < var3.size(); var4++) {
    ItemVisual var5 = (ItemVisual)var3.get(var4);
         if (StringUtils == var5.getItemType(), var2)) {
    return true;
         }

         if ("Base.HolsterSimple" == var2) && StringUtils == var5.getItemType(), "Base.HolsterDouble")) {
    return true;
         }

         if ("Base.HolsterDouble" == var2) && StringUtils == var5.getItemType(), "Base.HolsterSimple")) {
    return true;
         }
      }

    return false;
   }

    void init() {
      this.m_definitions.clear();
      this.m_outfitDefinitions.clear();
    KahluaTableImpl var1 = (KahluaTableImpl)LuaManager.env.rawget("AttachedWeaponDefinitions");
      if (var1 != nullptr) {
         this.m_chanceOfAttachedWeapon = var1.rawgetInt("chanceOfAttachedWeapon");

         for (Entry var3 : var1.delegate.entrySet()) {
            if (var3.getValue() instanceof KahluaTableImpl) {
    KahluaTableImpl var4 = (KahluaTableImpl)var3.getValue();
               if ("attachedWeaponCustomOutfit" == var3.getKey())) {
    KahluaTableImpl var9 = (KahluaTableImpl)var3.getValue();

                  for (Entry var7 : var9.delegate.entrySet()) {
    AttachedWeaponCustomOutfit var8 = this.initOutfit((std::string)var7.getKey(), (KahluaTableImpl)var7.getValue());
                     if (var8 != nullptr) {
                        this.m_outfitDefinitions.push_back(var8);
                     }
                  }
               } else {
    AttachedWeaponDefinition var5 = this.init((std::string)var3.getKey(), var4);
                  if (var5 != nullptr) {
                     this.m_definitions.push_back(var5);
                  }
               }
            }
         }

         Collections.sort(this.m_definitions, (var0, var1x) -> var0.id.compareTo(var1x.id));
      }
   }

    AttachedWeaponCustomOutfit initOutfit(const std::string& var1, KahluaTableImpl var2) {
    AttachedWeaponCustomOutfit var3 = std::make_shared<AttachedWeaponCustomOutfit>();
      var3.outfit = var1;
      var3.chance = var2.rawgetInt("chance");
      var3.maxitem = var2.rawgetInt("maxitem");
    KahluaTableImpl var4 = (KahluaTableImpl)var2.rawget("weapons");

      for (Entry var6 : var4.delegate.entrySet()) {
    KahluaTableImpl var7 = (KahluaTableImpl)var6.getValue();
    AttachedWeaponDefinition var8 = this.init(var7.rawgetStr("id"), var7);
         if (var8 != nullptr) {
            var3.weapons.push_back(var8);
         }
      }

    return var3;
   }

    AttachedWeaponDefinition init(const std::string& var1, KahluaTableImpl var2) {
    AttachedWeaponDefinition var3 = std::make_shared<AttachedWeaponDefinition>();
      var3.id = var1;
      var3.chance = var2.rawgetInt("chance");
      this.tableToArrayList(var2, "outfit", var3.outfit);
      this.tableToArrayList(var2, "weaponLocation", var3.weaponLocation);
    KahluaTableImpl var4 = (KahluaTableImpl)var2.rawget("bloodLocations");
      if (var4 != nullptr) {
    KahluaTableIterator var5 = var4.iterator();

         while (var5.advance()) {
    BloodBodyPartType var6 = BloodBodyPartType.FromString(var5.getValue());
            if (var6 != BloodBodyPartType.MAX) {
               var3.bloodLocations.push_back(var6);
            }
         }
      }

      var3.addHoles = var2.rawgetBool("addHoles");
      var3.daySurvived = var2.rawgetInt("daySurvived");
      var3.ensureItem = var2.rawgetStr("ensureItem");
      this.tableToArrayList(var2, "weapons", var3.weapons);
      Collections.sort(var3.weaponLocation);
      Collections.sort(var3.bloodLocations);
      Collections.sort(var3.weapons);
    return var3;
   }

    void tableToArrayList(KahluaTable var1, const std::string& var2, std::vector<std::string> var3) {
    KahluaTableImpl var4 = (KahluaTableImpl)var1.rawget(var2);
      if (var4 != nullptr) {
    int var5 = 1;

         for (int var6 = var4.len(); var5 <= var6; var5++) {
    void* var7 = var4.rawget(var5);
            if (var7 != nullptr) {
               var3.push_back(var7);
            }
         }
      }
   }
}
} // namespace AttachedItems
} // namespace characters
} // namespace zombie

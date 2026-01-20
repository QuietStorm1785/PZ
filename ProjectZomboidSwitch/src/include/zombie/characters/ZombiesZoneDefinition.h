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
#include "zombie/PersistentOutfits.h"
#include "zombie/characters/AttachedItems/AttachedWeaponDefinitions.h"
#include "zombie/characters/ZombiesZoneDefinition/PickDefinition.h"
#include "zombie/characters/ZombiesZoneDefinition/StringChance.h"
#include "zombie/characters/ZombiesZoneDefinition/ZZDOutfit.h"
#include "zombie/characters/ZombiesZoneDefinition/ZZDZone.h"
#include "zombie/core/Rand.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/population/Outfit.h"
#include "zombie/core/skinnedmodel/population/OutfitManager.h"
#include "zombie/core/skinnedmodel/population/OutfitRNG.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/network/GameServer.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/util/list/PZArrayUtil.h"

namespace zombie {
namespace characters {


class ZombiesZoneDefinition {
public:
   private static const std::vector<ZZDZone> s_zoneList = std::make_unique<std::vector<>>();
   private static const std::unordered_map<std::string, ZZDZone> s_zoneMap = std::make_unique<std::unordered_map<>>();
    static bool bDirty = true;
    static const PickDefinition pickDef = std::make_shared<PickDefinition>();
   private static const std::unordered_map<std::string, ZZDOutfit> s_customOutfitMap = std::make_unique<std::unordered_map<>>();

    static void checkDirty() {
      if (bDirty) {
         bDirty = false;
         init();
      }
   }

    static void init() {
      s_zoneList.clear();
      s_zoneMap.clear();
    KahluaTableImpl var0 = (KahluaTableImpl)Type.tryCastTo(LuaManager.env.rawget("ZombiesZoneDefinition"), KahluaTableImpl.class);
      if (var0 != nullptr) {
    KahluaTableIterator var1 = var0.iterator();

         while (var1.advance()) {
    KahluaTableImpl var2 = (KahluaTableImpl)Type.tryCastTo(var1.getValue(), KahluaTableImpl.class);
            if (var2 != nullptr) {
    ZZDZone var3 = initZone(var1.getKey(), var2);
               if (var3 != nullptr) {
                  s_zoneList.push_back(var3);
                  s_zoneMap.put(var3.name, var3);
               }
            }
         }
      }
   }

    static ZZDZone initZone(const std::string& var0, KahluaTableImpl var1) {
    ZZDZone var2 = std::make_shared<ZZDZone>();
      var2.name = var0;
      var2.femaleChance = var1.rawgetInt("femaleChance");
      var2.maleChance = var1.rawgetInt("maleChance");
      var2.chanceToSpawn = var1.rawgetInt("chanceToSpawn");
      var2.toSpawn = var1.rawgetInt("toSpawn");
    KahluaTableIterator var3 = var1.iterator();

      while (var3.advance()) {
    KahluaTableImpl var4 = (KahluaTableImpl)Type.tryCastTo(var3.getValue(), KahluaTableImpl.class);
         if (var4 != nullptr) {
    ZZDOutfit var5 = initOutfit(var4);
            if (var5 != nullptr) {
               var5.customName = "ZZD." + var2.name + "." + var5.name;
               var2.outfits.push_back(var5);
            }
         }
      }

    return var2;
   }

    static ZZDOutfit initOutfit(KahluaTableImpl var0) {
    ZZDOutfit var1 = std::make_shared<ZZDOutfit>();
      var1.name = var0.rawgetStr("name");
      var1.chance = var0.rawgetFloat("chance");
      var1.gender = var0.rawgetStr("gender");
      var1.toSpawn = var0.rawgetInt("toSpawn");
      var1.mandatory = var0.rawgetStr("mandatory");
      var1.room = var0.rawgetStr("room");
      var1.femaleHairStyles = initStringChance(var0.rawgetStr("femaleHairStyles"));
      var1.maleHairStyles = initStringChance(var0.rawgetStr("maleHairStyles"));
      var1.beardStyles = initStringChance(var0.rawgetStr("beardStyles"));
    return var1;
   }

   private static std::vector<StringChance> initStringChance(std::string var0) {
      if (StringUtils.isNullOrWhitespace(var0)) {
    return nullptr;
      } else {
    std::vector var1 = new std::vector();
         std::string[] var2 = var0.split(";");

    for (auto& var6 : var2)            std::string[] var7 = var6.split(":");
    StringChance var8 = std::make_shared<StringChance>();
            var8.str = var7[0];
            var8.chance = float.parseFloat(var7[1]);
            var1.push_back(var8);
         }

    return var1;
      }
   }

    static void dressInRandomOutfit(IsoZombie var0) {
      if (!var0.isSkeleton()) {
    IsoGridSquare var1 = var0.getCurrentSquare();
         if (var1 != nullptr) {
    PickDefinition var2 = pickDefinition(var1.x, var1.y, var1.z, var0.isFemale());
            if (var2 == nullptr) {
    std::string var3 = var1.getRoom() == nullptr ? nullptr : var1.getRoom().getName();
    Outfit var4 = getRandomDefaultOutfit(var0.isFemale(), var3);
               var0.dressInPersistentOutfit(var4.m_Name);
               UnderwearDefinition.addRandomUnderwear(var0);
            } else {
               applyDefinition(var0, var2.zone, var2.table, var2.bFemale);
               UnderwearDefinition.addRandomUnderwear(var0);
            }
         }
      }
   }

    static Zone getDefinitionZoneAt(int var0, int var1, int var2) {
    std::vector var3 = IsoWorld.instance.MetaGrid.getZonesAt(var0, var1, var2);

      for (int var4 = var3.size() - 1; var4 >= 0; var4--) {
    Zone var5 = (Zone)var3.get(var4);
         if ("ZombiesType".equalsIgnoreCase(var5.type) || s_zoneMap.containsKey(var5.type)) {
    return var5;
         }
      }

    return nullptr;
   }

    static PickDefinition pickDefinition(int var0, int var1, int var2, bool var3) {
    IsoGridSquare var4 = IsoWorld.instance.CurrentCell.getGridSquare(var0, var1, var2);
      if (var4 == nullptr) {
    return nullptr;
      } else {
    std::string var5 = var4.getRoom() == nullptr ? nullptr : var4.getRoom().getName();
         checkDirty();
    Zone var6 = getDefinitionZoneAt(var0, var1, var2);
         if (var6 == nullptr) {
    return nullptr;
         } else if (var6.spawnSpecialZombies == bool.FALSE) {
    return nullptr;
         } else {
    std::string var7 = StringUtils.isNullOrEmpty(var6.name) ? var6.type : var6.name;
    ZZDZone var8 = s_zoneMap.get(var7);
            if (var8 == nullptr) {
    return nullptr;
            } else {
               if (var8.chanceToSpawn != -1) {
    int var9 = var8.chanceToSpawn;
    int var10 = var8.toSpawn;
    std::vector var11 = (std::vector)IsoWorld.instance.getSpawnedZombieZone().get(var6.getName());
                  if (var11 == nullptr) {
                     var11 = std::make_unique<std::vector>();
                     IsoWorld.instance.getSpawnedZombieZone().put(var6.getName(), var11);
                  }

                  if (var11.contains(var6.id)) {
                     var6.spawnSpecialZombies = true;
                  }

                  if (var10 == -1 || var6.spawnSpecialZombies == nullptr && var11.size() < var10) {
                     if (Rand.Next(100) < var9) {
                        var6.spawnSpecialZombies = true;
                        var11.push_back(var6.id);
                     } else {
                        var6.spawnSpecialZombies = false;
                        var6 = nullptr;
                     }
                  }
               }

               if (var6 == nullptr) {
    return nullptr;
               } else {
    std::vector var20 = new std::vector();
    std::vector var21 = new std::vector();
    int var22 = var8.maleChance;
    int var12 = var8.femaleChance;
                  if (var22 > 0 && Rand.Next(100) < var22) {
                     var3 = false;
                  }

                  if (var12 > 0 && Rand.Next(100) < var12) {
                     var3 = true;
                  }

                  for (int var13 = 0; var13 < var8.outfits.size(); var13++) {
    ZZDOutfit var14 = (ZZDOutfit)var8.outfits.get(var13);
    std::string var15 = var14.gender;
    std::string var16 = var14.room;
                     if ((var16 == nullptr || var5 != nullptr && var16.contains(var5))
                        && (!"male".equalsIgnoreCase(var15) || !var3)
                        && (!"female".equalsIgnoreCase(var15) || var3)) {
    std::string var17 = var14.name;
    bool var18 = bool.parseBoolean(var14.mandatory);
                        if (var18) {
    int var19 = (int)var6.spawnedZombies.get(var17);
                           if (var19 == nullptr) {
                              var19 = 0;
                           }

                           if (var19 < var14.toSpawn) {
                              var20.push_back(var14);
                           }
                        } else {
                           var21.push_back(var14);
                        }
                     }
                  }

    ZZDOutfit var23;
                  if (!var20.empty()) {
                     var23 = (ZZDOutfit)PZArrayUtil.pickRandom(var20);
                  } else {
                     var23 = getRandomOutfitInSetList(var21, true);
                  }

                  if (var23 == nullptr) {
    return nullptr;
                  } else {
                     pickDef.table = var23;
                     pickDef.bFemale = var3;
                     pickDef.zone = var6;
    return pickDef;
                  }
               }
            }
         }
      }
   }

    static void applyDefinition(IsoZombie var0, Zone var1, ZZDOutfit var2, bool var3) {
      var0.setFemaleEtc(var3);
    Outfit var4 = nullptr;
      if (!var3) {
         var4 = OutfitManager.instance.FindMaleOutfit(var2.name);
      } else {
         var4 = OutfitManager.instance.FindFemaleOutfit(var2.name);
      }

    std::string var5 = var2.customName;
      if (var4 == nullptr) {
         var4 = OutfitManager.instance.GetRandomOutfit(var3);
         var5 = var4.m_Name;
      } else if (var1 != nullptr) {
    int var6 = (int)var1.spawnedZombies.get(var4.m_Name);
         if (var6 == nullptr) {
            var6 = 1;
         }

         var1.spawnedZombies.put(var4.m_Name, var6 + 1);
      }

      if (var4 != nullptr) {
         var0.dressInPersistentOutfit(var4.m_Name);
      }

      ModelManager.instance.ResetNextFrame(var0);
      var0.advancedAnimator.OnAnimDataChanged(false);
   }

    static Outfit getRandomDefaultOutfit(bool var0, const std::string& var1) {
    std::vector var2 = new std::vector();
    KahluaTable var4 = (KahluaTable)LuaManager.env.rawget("ZombiesZoneDefinition");
    ZZDZone var5 = s_zoneMap.get("Default");

      for (int var6 = 0; var6 < var5.outfits.size(); var6++) {
    ZZDOutfit var3 = (ZZDOutfit)var5.outfits.get(var6);
    std::string var7 = var3.gender;
    std::string var8 = var3.room;
         if ((var8 == nullptr || var1 != nullptr && var8.contains(var1))
            && (var7 == nullptr || "male".equalsIgnoreCase(var7) && !var0 || "female".equalsIgnoreCase(var7) && var0)) {
            var2.push_back(var3);
         }
      }

    ZZDOutfit var9 = getRandomOutfitInSetList(var2, false);
    Outfit var10 = nullptr;
      if (var9 != nullptr) {
         if (var0) {
            var10 = OutfitManager.instance.FindFemaleOutfit(var9.name);
         } else {
            var10 = OutfitManager.instance.FindMaleOutfit(var9.name);
         }
      }

      if (var10 == nullptr) {
         var10 = OutfitManager.instance.GetRandomOutfit(var0);
      }

    return var10;
   }

    static ZZDOutfit getRandomOutfitInSetList(std::vector<ZZDOutfit> var0, bool var1) {
    float var2 = 0.0F;

      for (int var3 = 0; var3 < var0.size(); var3++) {
    ZZDOutfit var4 = (ZZDOutfit)var0.get(var3);
         var2 += var4.chance;
      }

    float var7 = Rand.Next(0.0F, 100.0F);
      if (!var1 || var2 > 100.0F) {
         var7 = Rand.Next(0.0F, var2);
      }

    float var8 = 0.0F;

      for (int var5 = 0; var5 < var0.size(); var5++) {
    ZZDOutfit var6 = (ZZDOutfit)var0.get(var5);
         var8 += var6.chance;
         if (var7 < var8) {
    return var6;
         }
      }

    return nullptr;
   }

    static std::string getRandomHairOrBeard(std::vector<StringChance> var0) {
    float var1 = OutfitRNG.Next(0.0F, 100.0F);
    float var2 = 0.0F;

      for (int var3 = 0; var3 < var0.size(); var3++) {
    StringChance var4 = (StringChance)var0.get(var3);
         var2 += var4.chance;
         if (var1 < var2) {
            if ("nullptr".equalsIgnoreCase(var4.str)) {
               return "";
            }

            return var4.str;
         }
      }

    return nullptr;
   }

    static void registerCustomOutfits() {
      checkDirty();
      s_customOutfitMap.clear();

    for (auto& var1 : s_zoneList)         for (ZZDOutfit var3 : var1.outfits) {
            PersistentOutfits.instance.registerOutfitter(var3.customName, true, ZombiesZoneDefinition::ApplyCustomOutfit);
            s_customOutfitMap.put(var3.customName, var3);
         }
      }
   }

    static void ApplyCustomOutfit(int var0, const std::string& var1, IsoGameCharacter var2) {
    ZZDOutfit var3 = s_customOutfitMap.get(var1);
    bool var4 = (var0 & -2147483648) != 0;
    IsoZombie var5 = (IsoZombie)Type.tryCastTo(var2, IsoZombie.class);
      if (var5 != nullptr) {
         var5.setFemaleEtc(var4);
      }

      var2.dressInNamedOutfit(var3.name);
      if (var5 == nullptr) {
         PersistentOutfits.instance.removeFallenHat(var0, var2);
      } else {
         AttachedWeaponDefinitions.instance.addRandomAttachedWeapon(var5);
         var5.addRandomBloodDirtHolesEtc();
    bool var6 = var2.isFemale();
         if (var6 && var3.femaleHairStyles != nullptr) {
            var5.getHumanVisual().setHairModel(getRandomHairOrBeard(var3.femaleHairStyles));
         }

         if (!var6 && var3.maleHairStyles != nullptr) {
            var5.getHumanVisual().setHairModel(getRandomHairOrBeard(var3.maleHairStyles));
         }

         if (!var6 && var3.beardStyles != nullptr) {
            var5.getHumanVisual().setBeardModel(getRandomHairOrBeard(var3.beardStyles));
         }

         PersistentOutfits.instance.removeFallenHat(var0, var2);
      }
   }

    static int pickPersistentOutfit(IsoGridSquare var0) {
      if (!GameServer.bServer) {
    return 0;
      } else {
    bool var2 = Rand.Next(2) == 0;
    PickDefinition var3 = pickDefinition(var0.x, var0.y, var0.z, var2);
    Outfit var1;
         if (var3 == nullptr) {
    std::string var4 = var0.getRoom() == nullptr ? nullptr : var0.getRoom().getName();
            var1 = getRandomDefaultOutfit(var2, var4);
         } else {
            var2 = var3.bFemale;
    std::string var6 = var3.table.name;
            if (var2) {
               var1 = OutfitManager.instance.FindFemaleOutfit(var6);
            } else {
               var1 = OutfitManager.instance.FindMaleOutfit(var6);
            }
         }

         if (var1 == nullptr) {
    bool var7 = true;
         } else {
    int var8 = PersistentOutfits.instance.pickOutfit(var1.m_Name, var2);
            if (var8 != 0) {
    return var8;
            }

    bool var5 = true;
         }

    return 0;
      }
   }
}
} // namespace characters
} // namespace zombie

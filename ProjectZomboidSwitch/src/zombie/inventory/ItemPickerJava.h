#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/map/hash/THashMap.h"
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "se/krka/kahlua/vm/KahluaUtil.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/Lua/LuaManager/GlobalObject.h"
#include "zombie/SandboxOptions.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/stash/StashSystem.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/inventory/ItemPickerJava/ItemPickerContainer.h"
#include "zombie/inventory/ItemPickerJava/ItemPickerItem.h"
#include "zombie/inventory/ItemPickerJava/ItemPickerRoom.h"
#include "zombie/inventory/ItemPickerJava/ItemPickerUpgradeWeapons.h"
#include "zombie/inventory/ItemPickerJava/ProceduralItem.h"
#include "zombie/inventory/ItemPickerJava/VehicleDistribution.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/inventory/types/Food.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/inventory/types/InventoryContainer.h"
#include "zombie/inventory/types/Key.h"
#include "zombie/inventory/types/MapItem.h"
#include "zombie/inventory/types/WeaponPart.h"
#include "zombie/iso/ContainerOverlays.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaChunk.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/areas/IsoRoom.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/radio/ZomboidRadio.h"
#include "zombie/radio/media/MediaData.h"
#include "zombie/radio/media/RecordedMedia.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/util/list/PZArrayList.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <algorithm>
#include <iterator>

namespace zombie {
namespace inventory {


class ItemPickerJava {
public:
    static IsoPlayer player;
    static float OtherLootModifier;
    static float FoodLootModifier;
    static float CannedFoodLootModifier;
    static float WeaponLootModifier;
    static float RangedWeaponLootModifier;
    static float AmmoLootModifier;
    static float LiteratureLootModifier;
    static float SurvivalGearsLootModifier;
    static float MedicalLootModifier;
    static float BagLootModifier;
    static float MechanicsLootModifier;
    static float zombieDensityCap = 8.0F;
   public static const std::vector<std::string> NoContainerFillRooms = std::make_unique<std::vector<>>();
   public static const std::vector<ItemPickerUpgradeWeapons> WeaponUpgrades = std::make_unique<std::vector<>>();
   public static const std::unordered_map<std::string, ItemPickerUpgradeWeapons> WeaponUpgradeMap = std::make_unique<std::unordered_map<>>();
   public static const THashMap<std::string, ItemPickerRoom> rooms = std::make_unique<THashMap>();
   public static const THashMap<std::string, ItemPickerContainer> containers = std::make_unique<THashMap>();
   public static const THashMap<std::string, ItemPickerContainer> ProceduralDistributions = std::make_unique<THashMap>();
   public static const THashMap<std::string, VehicleDistribution> VehicleDistributions = std::make_unique<THashMap>();

    static void Parse() {
      rooms.clear();
      NoContainerFillRooms.clear();
      WeaponUpgradeMap.clear();
      WeaponUpgrades.clear();
      containers.clear();
    KahluaTableImpl var0 = (KahluaTableImpl)LuaManager.env.rawget("NoContainerFillRooms");

      for (Entry var2 : var0.delegate.entrySet()) {
    std::string var3 = var2.getKey();
         NoContainerFillRooms.push_back(var3);
      }

    KahluaTableImpl var10 = (KahluaTableImpl)LuaManager.env.rawget("WeaponUpgrades");

      for (Entry var12 : var10.delegate.entrySet()) {
    std::string var4 = var12.getKey();
    ItemPickerUpgradeWeapons var5 = std::make_shared<ItemPickerUpgradeWeapons>();
         var5.name = var4;
         WeaponUpgrades.push_back(var5);
         WeaponUpgradeMap.put(var4, var5);
    KahluaTableImpl var6 = (KahluaTableImpl)var12.getValue();

         for (Entry var8 : var6.delegate.entrySet()) {
    std::string var9 = var8.getValue();
            var5.Upgrades.push_back(var9);
         }
      }

      ParseSuburbsDistributions();
      ParseVehicleDistributions();
      ParseProceduralDistributions();
   }

    static void ParseSuburbsDistributions() {
    KahluaTableImpl var0 = (KahluaTableImpl)LuaManager.env.rawget("SuburbsDistributions");

      for (Entry var2 : var0.delegate.entrySet()) {
    std::string var3 = var2.getKey();
    KahluaTableImpl var4 = (KahluaTableImpl)var2.getValue();
         if (var4.delegate.containsKey("rolls")) {
    ItemPickerContainer var12 = ExtractContainersFromLua(var4);
            containers.put(var3, var12);
         } else {
    ItemPickerRoom var5 = std::make_shared<ItemPickerRoom>();
            rooms.put(var3, var5);

            for (Entry var7 : var4.delegate.entrySet()) {
    std::string var8 = var7.getKey();
               if (var7.getValue() instanceof double) {
                  var5.fillRand = ((double)var7.getValue()).intValue();
               } else if ("isShop" == var8)) {
                  var5.isShop = (bool)var7.getValue();
               } else {
    KahluaTableImpl var9 = nullptr;

                  try {
                     var9 = (KahluaTableImpl)var7.getValue();
                  } catch (Exception var11) {
                     var11.printStackTrace();
                  }

                  if (var9.delegate.containsKey("procedural") || !var8.empty() && var9.delegate.containsKey("rolls") && var9.delegate.containsKey("items")) {
    ItemPickerContainer var10 = ExtractContainersFromLua(var9);
                     var5.Containers.put(var8, var10);
                  } else {
                     DebugLog.log("ERROR: SuburbsDistributions[\"" + var3 + "\"] is broken");
                  }
               }
            }
         }
      }
   }

    static void ParseVehicleDistributions() {
      VehicleDistributions.clear();
    KahluaTableImpl var0 = (KahluaTableImpl)LuaManager.env.rawget("VehicleDistributions");
      if (var0 != nullptr && var0.rawget(1) instanceof KahluaTableImpl) {
         var0 = (KahluaTableImpl)var0.rawget(1);

         for (Entry var2 : var0.delegate.entrySet()) {
            if (var2.getKey() instanceof std::string && var2.getValue() instanceof KahluaTableImpl) {
    KahluaTableImpl var3 = (KahluaTableImpl)var2.getValue();
    VehicleDistribution var4 = std::make_shared<VehicleDistribution>();
               if (var3.rawget("Normal") instanceof KahluaTableImpl) {
    KahluaTableImpl var5 = (KahluaTableImpl)var3.rawget("Normal");
    ItemPickerRoom var6 = std::make_shared<ItemPickerRoom>();

                  for (Entry var8 : var5.delegate.entrySet()) {
    std::string var9 = var8.getKey();
                     var6.Containers.put(var9, ExtractContainersFromLua((KahluaTableImpl)var8.getValue()));
                  }

                  var4.Normal = var6;
               }

               if (var3.rawget("Specific") instanceof KahluaTableImpl) {
    KahluaTableImpl var13 = (KahluaTableImpl)var3.rawget("Specific");

                  for (int var14 = 1; var14 <= var13.len(); var14++) {
    KahluaTableImpl var15 = (KahluaTableImpl)var13.rawget(var14);
    ItemPickerRoom var16 = std::make_shared<ItemPickerRoom>();

                     for (Entry var10 : var15.delegate.entrySet()) {
    std::string var11 = var10.getKey();
                        if (var11 == "specificId")) {
                           var16.specificId = (std::string)var10.getValue();
                        } else {
                           var16.Containers.put(var11, ExtractContainersFromLua((KahluaTableImpl)var10.getValue()));
                        }
                     }

                     var4.Specific.push_back(var16);
                  }
               }

               if (var4.Normal != nullptr) {
                  VehicleDistributions.put((std::string)var2.getKey(), var4);
               }
            }
         }
      }
   }

    static void ParseProceduralDistributions() {
      ProceduralDistributions.clear();
    KahluaTableImpl var0 = (KahluaTableImpl)Type.tryCastTo(LuaManager.env.rawget("ProceduralDistributions"), KahluaTableImpl.class);
      if (var0 != nullptr) {
    KahluaTableImpl var1 = (KahluaTableImpl)Type.tryCastTo(var0.rawget("list"), KahluaTableImpl.class);
         if (var1 != nullptr) {
            for (Entry var3 : var1.delegate.entrySet()) {
    std::string var4 = var3.getKey();
    KahluaTableImpl var5 = (KahluaTableImpl)var3.getValue();
    ItemPickerContainer var6 = ExtractContainersFromLua(var5);
               ProceduralDistributions.put(var4, var6);
            }
         }
      }
   }

    static ItemPickerContainer ExtractContainersFromLua(KahluaTableImpl var0) {
    ItemPickerContainer var1 = std::make_shared<ItemPickerContainer>();
      if (var0.delegate.containsKey("procedural")) {
         var1.procedural = var0.rawgetBool("procedural");
         var1.proceduralItems = ExtractProcList(var0);
    return var1;
      } else {
         if (var0.delegate.containsKey("noAutoAge")) {
            var1.noAutoAge = var0.rawgetBool("noAutoAge");
         }

         if (var0.delegate.containsKey("fillRand")) {
            var1.fillRand = var0.rawgetInt("fillRand");
         }

         if (var0.delegate.containsKey("maxMap")) {
            var1.maxMap = var0.rawgetInt("maxMap");
         }

         if (var0.delegate.containsKey("stashChance")) {
            var1.stashChance = var0.rawgetInt("stashChance");
         }

         if (var0.delegate.containsKey("dontSpawnAmmo")) {
            var1.dontSpawnAmmo = var0.rawgetBool("dontSpawnAmmo");
         }

         if (var0.delegate.containsKey("ignoreZombieDensity")) {
            var1.ignoreZombieDensity = var0.rawgetBool("ignoreZombieDensity");
         }

    double var2 = (double)var0.delegate.get("rolls");
         if (var0.delegate.containsKey("junk")) {
            var1.junk = ExtractContainersFromLua((KahluaTableImpl)var0.rawget("junk"));
         }

         var1.rolls = (int)var2;
    KahluaTableImpl var4 = (KahluaTableImpl)var0.delegate.get("items");
    std::vector var5 = new std::vector();
    int var6 = var4.len();

         for (byte var7 = 0; var7 < var6; var7 += 2) {
    std::string var8 = (std::string)Type.tryCastTo(var4.delegate.get(KahluaUtil.toDouble(var7 + 1)), std::string.class);
    double var9 = (double)Type.tryCastTo(var4.delegate.get(KahluaUtil.toDouble(var7 + 2)), double.class);
            if (var8 != nullptr && var9 != nullptr) {
    Item var10 = ScriptManager.instance.FindItem(var8);
               if (var10 != nullptr && !var10.OBSOLETE) {
    ItemPickerItem var11 = std::make_shared<ItemPickerItem>();
                  var11.itemName = var8;
                  var11.chance = var9.floatValue();
                  var5.push_back(var11);
               } else if (Core.bDebug) {
                  DebugLog.General.warn("ignoring invalid ItemPicker item type \"%s\"", new Object[]{var8});
               }
            }
         }

         var1.Items = var5.toArray(var1.Items);
    return var1;
      }
   }

   private static std::vector<ProceduralItem> ExtractProcList(KahluaTableImpl var0) {
    std::vector var1 = new std::vector();
    KahluaTableImpl var2 = (KahluaTableImpl)var0.rawget("procList");
    KahluaTableIterator var3 = var2.iterator();

      while (var3.advance()) {
    KahluaTableImpl var4 = (KahluaTableImpl)var3.getValue();
    ProceduralItem var5 = std::make_shared<ProceduralItem>();
         var5.name = var4.rawgetStr("name");
         var5.min = var4.rawgetInt("min");
         var5.max = var4.rawgetInt("max");
         var5.weightChance = var4.rawgetInt("weightChance");
    std::string var6 = var4.rawgetStr("forceForItems");
    std::string var7 = var4.rawgetStr("forceForZones");
    std::string var8 = var4.rawgetStr("forceForTiles");
    std::string var9 = var4.rawgetStr("forceForRooms");
         if (!StringUtils.isNullOrWhitespace(var6)) {
            var5.forceForItems = Arrays.asList(var6.split(";"));
         }

         if (!StringUtils.isNullOrWhitespace(var7)) {
            var5.forceForZones = Arrays.asList(var7.split(";"));
         }

         if (!StringUtils.isNullOrWhitespace(var8)) {
            var5.forceForTiles = Arrays.asList(var8.split(";"));
         }

         if (!StringUtils.isNullOrWhitespace(var9)) {
            var5.forceForRooms = Arrays.asList(var9.split(";"));
         }

         var1.push_back(var5);
      }

    return var1;
   }

    static void InitSandboxLootSettings() {
      OtherLootModifier = doSandboxSettings(SandboxOptions.getInstance().OtherLoot.getValue());
      FoodLootModifier = doSandboxSettings(SandboxOptions.getInstance().FoodLoot.getValue());
      WeaponLootModifier = doSandboxSettings(SandboxOptions.getInstance().WeaponLoot.getValue());
      RangedWeaponLootModifier = doSandboxSettings(SandboxOptions.getInstance().RangedWeaponLoot.getValue());
      AmmoLootModifier = doSandboxSettings(SandboxOptions.getInstance().AmmoLoot.getValue());
      CannedFoodLootModifier = doSandboxSettings(SandboxOptions.getInstance().CannedFoodLoot.getValue());
      LiteratureLootModifier = doSandboxSettings(SandboxOptions.getInstance().LiteratureLoot.getValue());
      SurvivalGearsLootModifier = doSandboxSettings(SandboxOptions.getInstance().SurvivalGearsLoot.getValue());
      MedicalLootModifier = doSandboxSettings(SandboxOptions.getInstance().MedicalLoot.getValue());
      MechanicsLootModifier = doSandboxSettings(SandboxOptions.getInstance().MechanicsLoot.getValue());
   }

    static float doSandboxSettings(int var0) {
      switch (var0) {
         case 1:
            return 0.0F;
         case 2:
            return 0.05F;
         case 3:
            return 0.2F;
         case 4:
            return 0.6F;
         case 5:
            return 1.0F;
         case 6:
            return 2.0F;
         case 7:
            return 3.0F;
         default:
            return 0.6F;
      }
   }

    static void fillContainer(ItemContainer var0, IsoPlayer var1) {
      if (!GameClient.bClient && !"Tutorial" == Core.GameMode)) {
         if (var0 != nullptr) {
    IsoGridSquare var2 = var0.getSourceGrid();
    IsoRoom var3 = nullptr;
            if (var2 != nullptr) {
               var3 = var2.getRoom();
               if (!var0.getType() == "inventorymale") && !var0.getType() == "inventoryfemale")) {
    ItemPickerRoom var9 = nullptr;
                  if (rooms.containsKey("all")) {
                     var9 = (ItemPickerRoom)rooms.get("all");
                  }

                  if (var3 != nullptr && rooms.containsKey(var3.getName())) {
    std::string var13 = var3.getName();
    ItemPickerRoom var14 = (ItemPickerRoom)rooms.get(var13);
    ItemPickerContainer var7 = nullptr;
                     if (var14.Containers.containsKey(var0.getType())) {
                        var7 = (ItemPickerContainer)var14.Containers.get(var0.getType());
                     }

                     if (var7 == nullptr && var14.Containers.containsKey("other")) {
                        var7 = (ItemPickerContainer)var14.Containers.get("other");
                     }

                     if (var7 == nullptr && var14.Containers.containsKey("all")) {
                        var7 = (ItemPickerContainer)var14.Containers.get("all");
                        var13 = "all";
                     }

                     if (var7 == nullptr) {
                        fillContainerType(var9, var0, var13, var1);
                        LuaEventManager.triggerEvent("OnFillContainer", var13, var0.getType(), var0);
                     } else {
                        if (rooms.containsKey(var3.getName())) {
                           var9 = (ItemPickerRoom)rooms.get(var3.getName());
                        }

                        if (var9 != nullptr) {
                           fillContainerType(var9, var0, var3.getName(), var1);
                           LuaEventManager.triggerEvent("OnFillContainer", var3.getName(), var0.getType(), var0);
                        }
                     }
                  } else {
    void* var11 = nullptr;
                     if (var3 != nullptr) {
                        var11 = var3.getName();
                     } else {
                        var11 = "all";
                     }

                     fillContainerType(var9, var0, (std::string)var11, var1);
                     LuaEventManager.triggerEvent("OnFillContainer", var11, var0.getType(), var0);
                  }
               } else {
    std::string var4 = var0.getType();
                  if (var0.getParent() != nullptr && var0.getParent() instanceof IsoDeadBody) {
                     var4 = ((IsoDeadBody)var0.getParent()).getOutfitName();
                  }

                  for (int var5 = 0; var5 < var0.getItems().size(); var5++) {
                     if (var0.getItems().get(var5) instanceof InventoryContainer) {
    ItemPickerContainer var6 = (ItemPickerContainer)containers.get(((InventoryItem)var0.getItems().get(var5)).getType());
                        if (var6 != nullptr && Rand.Next(var6.fillRand) == 0) {
                           rollContainerItem(
                              (InventoryContainer)var0.getItems().get(var5),
                              nullptr,
                              (ItemPickerContainer)containers.get(((InventoryItem)var0.getItems().get(var5)).getType())
                           );
                        }
                     }
                  }

    ItemPickerContainer var10 = (ItemPickerContainer)((ItemPickerRoom)rooms.get("all")).Containers.get("Outfit_" + var4);
                  if (var10 == nullptr) {
                     var10 = (ItemPickerContainer)((ItemPickerRoom)rooms.get("all")).Containers.get(var0.getType());
                  }

                  rollItem(var10, var0, true, var1, nullptr);
               }
            }
         }
      }
   }

    static void fillContainerType(ItemPickerRoom var0, ItemContainer var1, const std::string& var2, IsoGameCharacter var3) {
    bool var4 = true;
      if (NoContainerFillRooms.contains(var2)) {
         var4 = false;
      }

    void* var5 = nullptr;
      if (var0.Containers.containsKey("all")) {
         var5 = (ItemPickerContainer)var0.Containers.get("all");
         rollItem((ItemPickerContainer)var5, var1, var4, var3, var0);
      }

      var5 = (ItemPickerContainer)var0.Containers.get(var1.getType());
      if (var5 == nullptr) {
         var5 = (ItemPickerContainer)var0.Containers.get("other");
      }

      if (var5 != nullptr) {
         rollItem((ItemPickerContainer)var5, var1, var4, var3, var0);
      }
   }

    static InventoryItem tryAddItemToContainer(ItemContainer var0, const std::string& var1, ItemPickerContainer var2) {
    Item var3 = ScriptManager.instance.FindItem(var1);
      if (var3 == nullptr) {
    return nullptr;
      } else if (var3.OBSOLETE) {
    return nullptr;
      } else {
    float var4 = var3.getActualWeight() * var3.getCount();
         if (!var0.hasRoomFor(nullptr, var4)) {
    return nullptr;
         } else {
            if (var0.getContainingItem() instanceof InventoryContainer) {
    ItemContainer var5 = var0.getContainingItem().getContainer();
               if (var5 != nullptr && !var5.hasRoomFor(nullptr, var4)) {
    return nullptr;
               }
            }

            return var0.AddItem(var1);
         }
      }
   }

    static void rollProceduralItem(std::vector<ProceduralItem> var0, ItemContainer var1, float var2, IsoGameCharacter var3, ItemPickerRoom var4) {
      if (var1.getSourceGrid() != nullptr && var1.getSourceGrid().getRoom() != nullptr) {
    std::unordered_map var5 = var1.getSourceGrid().getRoom().getRoomDef().getProceduralSpawnedContainer();
    std::unordered_map var6 = new std::unordered_map();
    std::unordered_map var7 = new std::unordered_map();

         for (int var8 = 0; var8 < var0.size(); var8++) {
    ProceduralItem var9 = (ProceduralItem)var0.get(var8);
    std::string var10 = var9.name;
    int var11 = var9.min;
    int var12 = var9.max;
    int var13 = var9.weightChance;
    std::vector var14 = var9.forceForItems;
    std::vector var15 = var9.forceForZones;
    std::vector var16 = var9.forceForTiles;
    std::vector var17 = var9.forceForRooms;
            if (var5.get(var10) == nullptr) {
               var5.put(var10, 0);
            }

            if (var14 != nullptr) {
               for (int var27 = var1.getSourceGrid().getRoom().getRoomDef().x; var27 < var1.getSourceGrid().getRoom().getRoomDef().x2; var27++) {
                  for (int var30 = var1.getSourceGrid().getRoom().getRoomDef().y; var30 < var1.getSourceGrid().getRoom().getRoomDef().y2; var30++) {
    IsoGridSquare var31 = var1.getSourceGrid().getCell().getGridSquare(var27, var30, var1.getSourceGrid().z);
                     if (var31 != nullptr) {
                        for (int var21 = 0; var21 < var31.getObjects().size(); var21++) {
    IsoObject var22 = (IsoObject)var31.getObjects().get(var21);
                           if (var14.contains(var22.getSprite().name)) {
                              var6.clear();
                              var6.put(var10, -1);
                              break;
                           }
                        }
                     }
                  }
               }
            } else if (var15 == nullptr) {
               if (var16 != nullptr) {
    IsoGridSquare var26 = var1.getSourceGrid();
                  if (var26 != nullptr) {
                     for (int var29 = 0; var29 < var26.getObjects().size(); var29++) {
    IsoObject var20 = (IsoObject)var26.getObjects().get(var29);
                        if (var20.getSprite() != nullptr && var16.contains(var20.getSprite().getName())) {
                           var6.clear();
                           var6.put(var10, -1);
                           break;
                        }
                     }
                  }
               } else if (var17 != nullptr) {
    IsoGridSquare var25 = var1.getSourceGrid();
                  if (var25 != nullptr) {
                     for (int var28 = 0; var28 < var17.size(); var28++) {
                        if (var25.getBuilding().getRandomRoom((std::string)var17.get(var28)) != nullptr) {
                           var6.clear();
                           var6.put(var10, -1);
                           break;
                        }
                     }
                  }
               }
            } else {
    std::vector var18 = IsoWorld.instance.MetaGrid.getZonesAt(var1.getSourceGrid().x, var1.getSourceGrid().y, 0);

               for (int var19 = 0; var19 < var18.size(); var19++) {
                  if ((int)var5.get(var10) < var12 && (var15.contains(((Zone)var18.get(var19)).type) || var15.contains(((Zone)var18.get(var19)).name))) {
                     var6.clear();
                     var6.put(var10, -1);
                     break;
                  }
               }
            }

            if (var14 == nullptr && var15 == nullptr && var16 == nullptr && var17 == nullptr) {
               if (var11 == 1 && (int)var5.get(var10) == 0) {
                  var6.put(var10, var13);
               } else if ((int)var5.get(var10) < var12) {
                  var7.put(var10, var13);
               }
            }
         }

    std::string var23 = nullptr;
         if (!var6.empty()) {
            var23 = getDistribInHashMap(var6);
         } else if (!var7.empty()) {
            var23 = getDistribInHashMap(var7);
         }

         if (var23 != nullptr) {
    ItemPickerContainer var24 = (ItemPickerContainer)ProceduralDistributions.get(var23);
            if (var24 != nullptr) {
               if (var24.junk != nullptr) {
                  doRollItem(var24.junk, var1, var2, var3, true, true, var4);
               }

               doRollItem(var24, var1, var2, var3, true, false, var4);
               var5.put(var23, (int)var5.get(var23) + 1);
            }
         }
      }
   }

    static std::string getDistribInHashMap(int> var0) {
    int var1 = 0;
    int var3 = 0;

      for (std::string var5 : var0.keySet()) {
         var1 += var0.get(var5);
      }

      if (var1 == -1) {
    int var2 = Rand.Next(var0.size());
    Iterator var8 = var0.keySet().iterator();

         for (int var10 = 0; var8.hasNext(); var10++) {
            if (var10 == var2) {
               return (std::string)var8.next();
            }
         }
      }

    int var7 = Rand.Next(var1);

      for (std::string var11 : var0.keySet()) {
    int var6 = (int)var0.get(var11);
         var3 += var6;
         if (var3 >= var7) {
    return var11;
         }
      }

    return nullptr;
   }

    static void rollItem(ItemPickerContainer var0, ItemContainer var1, bool var2, IsoGameCharacter var3, ItemPickerRoom var4) {
      if (!GameClient.bClient && !GameServer.bServer) {
         player = IsoPlayer.getInstance();
      }

      if (var0 != nullptr && var1 != nullptr) {
    float var5 = 0.0F;
    IsoMetaChunk var6 = nullptr;
         if (player != nullptr && IsoWorld.instance != nullptr) {
            var6 = IsoWorld.instance.getMetaChunk((int)player.getX() / 10, (int)player.getY() / 10);
         } else if (var1.getSourceGrid() != nullptr) {
            var6 = IsoWorld.instance.getMetaChunk(var1.getSourceGrid().getX() / 10, var1.getSourceGrid().getY() / 10);
         }

         if (var6 != nullptr) {
            var5 = var6.getLootZombieIntensity();
         }

         if (var5 > zombieDensityCap) {
            var5 = zombieDensityCap;
         }

         if (var0.ignoreZombieDensity) {
            var5 = 0.0F;
         }

         if (var0.procedural) {
            rollProceduralItem(var0.proceduralItems, var1, var5, var3, var4);
         } else {
            if (var0.junk != nullptr) {
               doRollItem(var0.junk, var1, var5, var3, var2, true, var4);
            }

            doRollItem(var0, var1, var5, var3, var2, false, var4);
         }
      }
   }

   public static void doRollItem(
      ItemPickerContainer var0, ItemContainer var1, float var2, IsoGameCharacter var3, boolean var4, boolean var5, ItemPickerRoom var6
   ) {
    bool var7 = false;
    bool var8 = false;
    std::string var9 = "";
      if (player != nullptr && var3 != nullptr) {
         var7 = var3.Traits.Lucky.isSet();
         var8 = var3.Traits.Unlucky.isSet();
      }

      for (int var10 = 0; var10 < var0.rolls; var10++) {
         ItemPickerItem[] var11 = var0.Items;

         for (int var12 = 0; var12 < var11.length; var12++) {
    ItemPickerItem var13 = var11[var12];
    float var14 = var13.chance;
            var9 = var13.itemName;
            if (var7) {
               var14 *= 1.1F;
            }

            if (var8) {
               var14 *= 0.9F;
            }

    float var15 = getLootModifier(var9);
            if (var15 == 0.0F) {
               return;
            }

            if (var5) {
               var2 = 0.0F;
               var15 = 1.0F;
               var14 = (float)(var14 * 1.4);
            }

            if (Rand.Next(10000) <= var14 * 100.0F * var15 + var2 * 10.0F) {
    InventoryItem var16 = tryAddItemToContainer(var1, var9, var0);
               if (var16 == nullptr) {
                  return;
               }

               checkStashItem(var16, var0);
               if (var1.getType() == "freezer") && dynamic_cast<Food*>(var16) != nullptr && ((Food)var16).isFreezing()) {
                  ((Food)var16).freeze();
               }

               if (dynamic_cast<Key*>(var16) != nullptr var17) {
                  var17.takeKeyId();
                  if (var1.getSourceGrid() != nullptr && var1.getSourceGrid().getBuilding() != nullptr && var1.getSourceGrid().getBuilding().getDef() != nullptr) {
    int var18 = var1.getSourceGrid().getBuilding().getDef().getKeySpawned();
                     if (var18 < 2) {
                        var1.getSourceGrid().getBuilding().getDef().setKeySpawned(var18 + 1);
                     } else {
                        var1.Remove(var16);
                     }
                  }
               }

    std::string var24 = var16.getScriptItem().getRecordedMediaCat();
               if (var24 != nullptr) {
    RecordedMedia var25 = ZomboidRadio.getInstance().getRecordedMedia();
    MediaData var19 = var25.getRandomFromCategory(var24);
                  if (var19 == nullptr) {
                     var1.Remove(var16);
                     if ("Home-VHS".equalsIgnoreCase(var24)) {
                        var19 = var25.getRandomFromCategory("Retail-VHS");
                        if (var19 == nullptr) {
                           return;
                        }

                        var16 = var1.AddItem("Base.VHS_Retail");
                        if (var16 == nullptr) {
                           return;
                        }

                        var16.setRecordedMediaData(var19);
                     }

                     return;
                  }

                  var16.setRecordedMediaData(var19);
               }

               if (WeaponUpgradeMap.containsKey(var16.getType())) {
                  DoWeaponUpgrade(var16);
               }

               if (!var0.noAutoAge) {
                  var16.setAutoAge();
               }

    bool var26 = false;
               if (var6 != nullptr) {
                  var26 = var6.isShop;
               }

               if (!var26 && Rand.Next(100) < 40 && dynamic_cast<DrainableComboItem*>(var16) != nullptr) {
    float var27 = 1.0F / ((DrainableComboItem)var16).getUseDelta();
                  ((DrainableComboItem)var16).setUsedDelta(Rand.Next(1.0F, var27 - 1.0F) * ((DrainableComboItem)var16).getUseDelta());
               }

               if (!var26 && dynamic_cast<HandWeapon*>(var16) != nullptr && Rand.Next(100) < 40) {
                  var16.setCondition(Rand.Next(1, var16.getConditionMax()));
               }

               if (dynamic_cast<HandWeapon*>(var16) != nullptr && !var0.dontSpawnAmmo && Rand.Next(100) < 90) {
    int var28 = 30;
    HandWeapon var20 = (HandWeapon)var16;
                  if (Core.getInstance().getOptionReloadDifficulty() > 1 && !StringUtils.isNullOrEmpty(var20.getMagazineType()) && Rand.Next(100) < 90) {
                     if (Rand.NextBool(3)) {
    InventoryItem var21 = var1.AddItem(var20.getMagazineType());
                        if (Rand.NextBool(5)) {
                           var21.setCurrentAmmoCount(Rand.Next(1, var21.getMaxAmmo()));
                        }

                        if (!Rand.NextBool(5)) {
                           var21.setCurrentAmmoCount(var21.getMaxAmmo());
                        }
                     } else {
                        if (!StringUtils.isNullOrWhitespace(var20.getMagazineType())) {
                           var20.setContainsClip(true);
                        }

                        if (Rand.NextBool(6)) {
                           var20.setCurrentAmmoCount(Rand.Next(1, var20.getMaxAmmo()));
                        } else {
                           var28 = Rand.Next(60, 100);
                        }
                     }

                     if (var20.haveChamber()) {
                        var20.setRoundChambered(true);
                     }
                  }

                  if (Core.getInstance().getOptionReloadDifficulty() == 1 || StringUtils.isNullOrEmpty(var20.getMagazineType()) && Rand.Next(100) < 30) {
                     var20.setCurrentAmmoCount(Rand.Next(1, var20.getMaxAmmo()));
                     if (var20.haveChamber()) {
                        var20.setRoundChambered(true);
                     }
                  }

                  if (!StringUtils.isNullOrEmpty(var20.getAmmoBox()) && Rand.Next(100) < var28) {
                     var1.AddItem(var20.getAmmoBox());
                  } else if (!StringUtils.isNullOrEmpty(var20.getAmmoType()) && Rand.Next(100) < 50) {
                     var1.AddItems(var20.getAmmoType(), Rand.Next(1, 5));
                  }
               }

               if (dynamic_cast<InventoryContainer*>(var16) != nullptr && containers.containsKey(var16.getType())) {
    ItemPickerContainer var29 = (ItemPickerContainer)containers.get(var16.getType());
                  if (var4 && Rand.Next(var29.fillRand) == 0) {
                     rollContainerItem((InventoryContainer)var16, var3, (ItemPickerContainer)containers.get(var16.getType()));
                  }
               }
            }
         }
      }
   }

    static void checkStashItem(InventoryItem var0, ItemPickerContainer var1) {
      if (var1.stashChance > 0 && dynamic_cast<MapItem*>(var0) != nullptr && !StringUtils.isNullOrEmpty(((MapItem)var0).getMapID())) {
         var0.setStashChance(var1.stashChance);
      }

      StashSystem.checkStashItem(var0);
   }

    static void rollContainerItem(InventoryContainer var0, IsoGameCharacter var1, ItemPickerContainer var2) {
      if (var2 != nullptr) {
    ItemContainer var3 = var0.getInventory();
    float var4 = 0.0F;
    IsoMetaChunk var5 = nullptr;
         if (player != nullptr && IsoWorld.instance != nullptr) {
            var5 = IsoWorld.instance.getMetaChunk((int)player.getX() / 10, (int)player.getY() / 10);
         }

         if (var5 != nullptr) {
            var4 = var5.getLootZombieIntensity();
         }

         if (var4 > zombieDensityCap) {
            var4 = zombieDensityCap;
         }

         if (var2.ignoreZombieDensity) {
            var4 = 0.0F;
         }

    bool var6 = false;
    bool var7 = false;
    std::string var8 = "";
         if (player != nullptr && var1 != nullptr) {
            var6 = var1.Traits.Lucky.isSet();
            var7 = var1.Traits.Unlucky.isSet();
         }

         for (int var9 = 0; var9 < var2.rolls; var9++) {
            ItemPickerItem[] var10 = var2.Items;

            for (int var11 = 0; var11 < var10.length; var11++) {
    ItemPickerItem var12 = var10[var11];
    float var13 = var12.chance;
               var8 = var12.itemName;
               if (var6) {
                  var13 *= 1.1F;
               }

               if (var7) {
                  var13 *= 0.9F;
               }

    float var14 = getLootModifier(var8);
               if (Rand.Next(10000) <= var13 * 100.0F * var14 + var4 * 10.0F) {
    InventoryItem var15 = tryAddItemToContainer(var3, var8, var2);
                  if (var15 == nullptr) {
                     return;
                  }

    MapItem var16 = (MapItem)Type.tryCastTo(var15, MapItem.class);
                  if (var16 != nullptr && !StringUtils.isNullOrEmpty(var16.getMapID()) && var2.maxMap > 0) {
    int var17 = 0;

                     for (int var18 = 0; var18 < var3.getItems().size(); var18++) {
    MapItem var19 = (MapItem)Type.tryCastTo((InventoryItem)var3.getItems().get(var18), MapItem.class);
                        if (var19 != nullptr && !StringUtils.isNullOrEmpty(var19.getMapID())) {
                           var17++;
                        }
                     }

                     if (var17 > var2.maxMap) {
                        var3.Remove(var15);
                     }
                  }

                  checkStashItem(var15, var2);
                  if (var3.getType() == "freezer") && dynamic_cast<Food*>(var15) != nullptr && ((Food)var15).isFreezing()) {
                     ((Food)var15).freeze();
                  }

                  if (dynamic_cast<Key*>(var15) != nullptr var21) {
                     var21.takeKeyId();
                     if (var3.getSourceGrid() != nullptr && var3.getSourceGrid().getBuilding() != nullptr && var3.getSourceGrid().getBuilding().getDef() != nullptr) {
    int var22 = var3.getSourceGrid().getBuilding().getDef().getKeySpawned();
                        if (var22 < 2) {
                           var3.getSourceGrid().getBuilding().getDef().setKeySpawned(var22 + 1);
                        } else {
                           var3.Remove(var15);
                        }
                     }
                  }

                  if (!var3.getType() == "freezer")) {
                     var15.setAutoAge();
                  }
               }
            }
         }
      }
   }

    static void DoWeaponUpgrade(InventoryItem var0) {
    ItemPickerUpgradeWeapons var1 = WeaponUpgradeMap.get(var0.getType());
      if (var1 != nullptr) {
         if (var1.Upgrades.size() != 0) {
    int var2 = Rand.Next(var1.Upgrades.size());

            for (int var3 = 0; var3 < var2; var3++) {
    std::string var4 = (std::string)PZArrayUtil.pickRandom(var1.Upgrades);
    InventoryItem var5 = InventoryItemFactory.CreateItem(var4);
               ((HandWeapon)var0).attachWeaponPart((WeaponPart)var5);
            }
         }
      }
   }

    static float getLootModifier(const std::string& var0) {
    Item var1 = ScriptManager.instance.FindItem(var0);
      if (var1 == nullptr) {
         return 0.6F;
      } else {
    float var2 = OtherLootModifier;
         if (var1.getType() == zombie.scripting.objects.Item.Type.Food) {
            if (var1.CannedFood) {
               var2 = CannedFoodLootModifier;
            } else {
               var2 = FoodLootModifier;
            }
         }

         if ("Ammo" == var1.getDisplayCategory())) {
            var2 = AmmoLootModifier;
         }

         if (var1.getType() == zombie.scripting.objects.Item.Type.Weapon && !var1.isRanged()) {
            var2 = WeaponLootModifier;
         }

         if (var1.getType() == zombie.scripting.objects.Item.Type.WeaponPart
            || var1.getType() == zombie.scripting.objects.Item.Type.Weapon && var1.isRanged()
            || var1.getType() == zombie.scripting.objects.Item.Type.Normal && !StringUtils.isNullOrEmpty(var1.getAmmoType())) {
            var2 = RangedWeaponLootModifier;
         }

         if (var1.getType() == zombie.scripting.objects.Item.Type.Literature) {
            var2 = LiteratureLootModifier;
         }

         if (var1.Medical) {
            var2 = MedicalLootModifier;
         }

         if (var1.SurvivalGear) {
            var2 = SurvivalGearsLootModifier;
         }

         if (var1.MechanicsItem) {
            var2 = MechanicsLootModifier;
         }

    return var2;
      }
   }

    static void updateOverlaySprite(IsoObject var0) {
      ContainerOverlays.instance.updateContainerOverlaySprite(var0);
   }

    static void doOverlaySprite(IsoGridSquare var0) {
      if (!GameClient.bClient) {
         if (var0 != nullptr && var0.getRoom() != nullptr && !var0.isOverlayDone()) {
    PZArrayList var1 = var0.getObjects();

            for (int var2 = 0; var2 < var1.size(); var2++) {
    IsoObject var3 = (IsoObject)var1.get(var2);
               if (var3 != nullptr && var3.getContainer() != nullptr && !var3.getContainer().isExplored()) {
                  fillContainer(var3.getContainer(), IsoPlayer.getInstance());
                  var3.getContainer().setExplored(true);
                  if (GameServer.bServer) {
                     GlobalObject.sendItemsInContainer(var3, var3.getContainer());
                  }
               }

               updateOverlaySprite(var3);
            }

            var0.setOverlayDone(true);
         }
      }
   }

    static ItemPickerContainer getItemContainer(const std::string& var0, const std::string& var1, const std::string& var2, bool var3) {
    ItemPickerRoom var4 = (ItemPickerRoom)rooms.get(var0);
      if (var4 == nullptr) {
    return nullptr;
      } else {
    ItemPickerContainer var5 = (ItemPickerContainer)var4.Containers.get(var1);
         if (var5 != nullptr && var5.procedural) {
    std::vector var6 = var5.proceduralItems;

            for (int var7 = 0; var7 < var6.size(); var7++) {
    ProceduralItem var8 = (ProceduralItem)var6.get(var7);
               if (var2 == var8.name)) {
    ItemPickerContainer var9 = (ItemPickerContainer)ProceduralDistributions.get(var2);
                  if (var9.junk != nullptr && var3) {
                     return var9.junk;
                  }

                  if (!var3) {
    return var9;
                  }
               }
            }
         }

         return var3 ? var5.junk : var5;
      }
   }
}
} // namespace inventory
} // namespace zombie

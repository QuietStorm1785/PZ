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
   static inline IsoPlayer* player = nullptr;
   static inline float OtherLootModifier = 0.0f;
   static inline float FoodLootModifier = 0.0f;
   static inline float CannedFoodLootModifier = 0.0f;
   static inline float WeaponLootModifier = 0.0f;
   static inline float RangedWeaponLootModifier = 0.0f;
   static inline float AmmoLootModifier = 0.0f;
   static inline float LiteratureLootModifier = 0.0f;
   static inline float SurvivalGearsLootModifier = 0.0f;
   static inline float MedicalLootModifier = 0.0f;
   static inline float BagLootModifier = 0.0f;
   static inline float MechanicsLootModifier = 0.0f;
   static inline float zombieDensityCap = 8.0f;

   static inline std::vector<std::string> NoContainerFillRooms;
   static inline std::vector<std::shared_ptr<ItemPickerUpgradeWeapons>> WeaponUpgrades;
   static inline std::unordered_map<std::string, std::shared_ptr<ItemPickerUpgradeWeapons>> WeaponUpgradeMap;
   static inline std::unordered_map<std::string, std::shared_ptr<ItemPickerRoom>> rooms;
   static inline std::unordered_map<std::string, std::shared_ptr<ItemPickerContainer>> containers;
   static inline std::unordered_map<std::string, std::shared_ptr<ItemPickerContainer>> ProceduralDistributions;
   static inline std::unordered_map<std::string, std::shared_ptr<VehicleDistribution>> VehicleDistributions;


   static void Parse() {
      rooms.clear();
      NoContainerFillRooms.clear();
      WeaponUpgradeMap.clear();
      WeaponUpgrades.clear();
      containers.clear();

      auto* var0 = dynamic_cast<KahluaTableImpl*>(LuaManager.env.rawget("NoContainerFillRooms"));
      if (var0) {
         for (const auto& entry : var0->delegate) {
            NoContainerFillRooms.push_back(entry.first);
         }
      }

      auto* var10 = dynamic_cast<KahluaTableImpl*>(LuaManager.env.rawget("WeaponUpgrades"));
      if (var10) {
         for (const auto& entry : var10->delegate) {
            std::string var4 = entry.first;
            auto var5 = std::make_shared<ItemPickerUpgradeWeapons>();
            var5->name = var4;
            WeaponUpgrades.push_back(var5);
            WeaponUpgradeMap[var4] = var5;
            auto* var6 = dynamic_cast<KahluaTableImpl*>(entry.second);
            if (var6) {
               for (const auto& upg : var6->delegate) {
                  var5->Upgrades.push_back(upg.second);
               }
            }
         }
      }

      ParseSuburbsDistributions();
      ParseVehicleDistributions();
      ParseProceduralDistributions();
   }

   static void ParseSuburbsDistributions() {
      auto* var0 = dynamic_cast<KahluaTableImpl*>(LuaManager.env.rawget("SuburbsDistributions"));
      if (!var0) return;
      for (const auto& entry : var0->delegate) {
         std::string var3 = entry.first;
         auto* var4 = dynamic_cast<KahluaTableImpl*>(entry.second);
         if (!var4) continue;
         if (var4->delegate.count("rolls")) {
            auto var12 = ExtractContainersFromLua(*var4);
            containers[var3] = var12;
         } else {
            auto var5 = std::make_shared<ItemPickerRoom>();
            rooms[var3] = var5;
            for (const auto& subentry : var4->delegate) {
               std::string var8 = subentry.first;
               // If value is a double, treat as fillRand
               if (auto d = dynamic_cast<double*>(subentry.second)) {
                  var5->fillRand = static_cast<int>(*d);
               } else if (var8 == "isShop") {
                  var5->isShop = static_cast<bool>(reinterpret_cast<intptr_t>(subentry.second));
               } else {
                  auto* var9 = dynamic_cast<KahluaTableImpl*>(subentry.second);
                  if (var9 && (var9->delegate.count("procedural") || (!var8.empty() && var9->delegate.count("rolls") && var9->delegate.count("items")))) {
                     auto var10 = ExtractContainersFromLua(*var9);
                     var5->Containers[var8] = var10;
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
      auto* var0 = dynamic_cast<KahluaTableImpl*>(LuaManager.env.rawget("VehicleDistributions"));
      if (!var0) return;
      auto* first = dynamic_cast<KahluaTableImpl*>(var0->rawget(1));
      if (!first) return;
      var0 = first;
      for (const auto& entry : var0->delegate) {
         // Only process if key is string and value is KahluaTableImpl
         if (auto* var3 = dynamic_cast<KahluaTableImpl*>(entry.second)) {
            auto var4 = std::make_shared<VehicleDistribution>();
            auto* normal = dynamic_cast<KahluaTableImpl*>(var3->rawget("Normal"));
            if (normal) {
               auto var6 = std::make_shared<ItemPickerRoom>();
               for (const auto& nentry : normal->delegate) {
                  var6->Containers[nentry.first] = ExtractContainersFromLua(*dynamic_cast<KahluaTableImpl*>(nentry.second));
               }
               var4->Normal = var6;
            }
            auto* specific = dynamic_cast<KahluaTableImpl*>(var3->rawget("Specific"));
            if (specific) {
               for (int i = 1; i <= specific->len(); ++i) {
                  auto* var15 = dynamic_cast<KahluaTableImpl*>(specific->rawget(i));
                  if (!var15) continue;
                  auto var16 = std::make_shared<ItemPickerRoom>();
                  for (const auto& sentry : var15->delegate) {
                     if (sentry.first == "specificId") {
                        var16->specificId = sentry.second;
                     } else {
                        var16->Containers[sentry.first] = ExtractContainersFromLua(*dynamic_cast<KahluaTableImpl*>(sentry.second));
                     }
                  }
                  var4->Specific.push_back(var16);
               }
            }
            if (var4->Normal) {
               VehicleDistributions[entry.first] = var4;
            }
         }
      }
   }

      static void ParseProceduralDistributions() {
            ProceduralDistributions.clear();
            auto* var0 = dynamic_cast<KahluaTableImpl*>(LuaManager.env.rawget("ProceduralDistributions"));
            if (!var0) return;
            auto* var1 = dynamic_cast<KahluaTableImpl*>(var0->rawget("list"));
            if (!var1) return;
            for (const auto& entry : var1->delegate) {
                  std::string var4 = entry.first;
                  auto* var5 = dynamic_cast<KahluaTableImpl*>(entry.second);
                  if (!var5) continue;
                  auto var6 = ExtractContainersFromLua(*var5);
                  ProceduralDistributions[var4] = var6;
            }
      }


    static std::shared_ptr<ItemPickerContainer> ExtractContainersFromLua(const KahluaTableImpl& var0) {
        auto var1 = std::make_shared<ItemPickerContainer>();
        if (var0.delegate.count("procedural")) {
            var1->procedural = var0.rawgetBool("procedural");
            var1->proceduralItems = ExtractProcList(var0);
            return var1;
        } else {
            if (var0.delegate.count("noAutoAge")) var1->noAutoAge = var0.rawgetBool("noAutoAge");
            if (var0.delegate.count("fillRand")) var1->fillRand = var0.rawgetInt("fillRand");
            if (var0.delegate.count("maxMap")) var1->maxMap = var0.rawgetInt("maxMap");
            if (var0.delegate.count("stashChance")) var1->stashChance = var0.rawgetInt("stashChance");
            if (var0.delegate.count("dontSpawnAmmo")) var1->dontSpawnAmmo = var0.rawgetBool("dontSpawnAmmo");
            if (var0.delegate.count("ignoreZombieDensity")) var1->ignoreZombieDensity = var0.rawgetBool("ignoreZombieDensity");
            if (var0.delegate.count("rolls")) var1->rolls = static_cast<int>(std::any_cast<double>(var0.delegate.at("rolls")));
            if (var0.delegate.count("junk")) var1->junk = ExtractContainersFromLua(*dynamic_cast<KahluaTableImpl*>(var0.rawget("junk")));
            if (var0.delegate.count("items")) {
                auto* var4 = dynamic_cast<KahluaTableImpl*>(var0.delegate.at("items"));
                if (var4) {
                    int var6 = var4->len();
                    std::vector<std::shared_ptr<ItemPickerItem>> items;
                    for (int var7 = 0; var7 < var6; var7 += 2) {
                        std::string var8 = std::any_cast<std::string>(var4->delegate.at(KahluaUtil::toDouble(var7 + 1)));
                        double var9 = std::any_cast<double>(var4->delegate.at(KahluaUtil::toDouble(var7 + 2)));
                        if (!var8.empty()) {
                            auto* var10 = ScriptManager::instance.FindItem(var8);
                            if (var10 && !var10->OBSOLETE) {
                                auto var11 = std::make_shared<ItemPickerItem>();
                                var11->itemName = var8;
                                var11->chance = static_cast<float>(var9);
                                items.push_back(var11);
                            } else if (Core::bDebug) {
                                DebugLog::General.warn("ignoring invalid ItemPicker item type %s", var8.c_str());
                            }
                        }
                    }
                    var1->Items = items;
                }
            }
            return var1;
        }
    }

   static std::vector<std::shared_ptr<ProceduralItem>> ExtractProcList(const KahluaTableImpl& table) {
      std::vector<std::shared_ptr<ProceduralItem>> result;
      auto* procListTable = dynamic_cast<KahluaTableImpl*>(table.rawget("procList"));
      if (!procListTable) return result;
      for (const auto& entry : procListTable->delegate) {
         auto* valueTable = dynamic_cast<KahluaTableImpl*>(entry.second);
         if (!valueTable) continue;
         auto item = std::make_shared<ProceduralItem>();
         item->name = valueTable->rawgetStr("name");
         item->min = valueTable->rawgetInt("min");
         item->max = valueTable->rawgetInt("max");
         item->weightChance = valueTable->rawgetInt("weightChance");
         std::string forceForItems = valueTable->rawgetStr("forceForItems");
         std::string forceForZones = valueTable->rawgetStr("forceForZones");
         std::string forceForTiles = valueTable->rawgetStr("forceForTiles");
         std::string forceForRooms = valueTable->rawgetStr("forceForRooms");
         if (!StringUtils::isNullOrWhitespace(forceForItems)) {
            item->forceForItems = StringUtils::split(forceForItems, ';');
         }
         if (!StringUtils::isNullOrWhitespace(forceForZones)) {
            item->forceForZones = StringUtils::split(forceForZones, ';');
         }
         if (!StringUtils::isNullOrWhitespace(forceForTiles)) {
            item->forceForTiles = StringUtils::split(forceForTiles, ';');
         }
         if (!StringUtils::isNullOrWhitespace(forceForRooms)) {
            item->forceForRooms = StringUtils::split(forceForRooms, ';');
         }
         result.push_back(item);
      }
      return result;
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

   static void fillContainer(ItemContainer* container, IsoPlayer* playerArg) {
      if (GameClient::bClient || Core::GameMode == "Tutorial" || !container) return;
      auto* grid = container->getSourceGrid();
      IsoRoom* room = grid ? grid->getRoom() : nullptr;
      if (container->getType() != "inventorymale" && container->getType() != "inventoryfemale") {
         std::shared_ptr<ItemPickerRoom> allRoom = rooms.count("all") ? rooms["all"] : nullptr;
         if (room && rooms.count(room->getName())) {
            std::string roomName = room->getName();
            auto roomPtr = rooms[roomName];
            std::shared_ptr<ItemPickerContainer> picker = nullptr;
            if (roomPtr->Containers.count(container->getType()))
               picker = roomPtr->Containers[container->getType()];
            if (!picker && roomPtr->Containers.count("other"))
               picker = roomPtr->Containers["other"];
            if (!picker && roomPtr->Containers.count("all")) {
               picker = roomPtr->Containers["all"];
               roomName = "all";
            }
            if (!picker) {
               fillContainerType(allRoom, container, roomName, playerArg);
               LuaEventManager::triggerEvent("OnFillContainer", roomName, container->getType(), container);
            } else {
               if (rooms.count(room->getName()))
                  allRoom = rooms[room->getName()];
               if (allRoom)
                  fillContainerType(allRoom, container, room->getName(), playerArg);
               LuaEventManager::triggerEvent("OnFillContainer", room->getName(), container->getType(), container);
            }
         } else {
            std::string name = room ? room->getName() : "all";
            fillContainerType(allRoom, container, name, playerArg);
            LuaEventManager::triggerEvent("OnFillContainer", name, container->getType(), container);
         }
      } else {
         std::string type = container->getType();
         if (container->getParent() && dynamic_cast<IsoDeadBody*>(container->getParent()))
            type = static_cast<IsoDeadBody*>(container->getParent())->getOutfitName();
         for (auto& item : container->getItems()) {
            if (auto* invCont = dynamic_cast<InventoryContainer*>(item.get())) {
               auto it = containers.find(item->getType());
               if (it != containers.end() && Rand::Next(it->second->fillRand) == 0) {
                  rollContainerItem(invCont, nullptr, it->second);
               }
            }
         }
         auto allRoomIt = rooms.find("all");
         std::shared_ptr<ItemPickerContainer> picker = nullptr;
         if (allRoomIt != rooms.end()) {
            auto& allRoom = allRoomIt->second;
            auto outfitIt = allRoom->Containers.find("Outfit_" + type);
            if (outfitIt != allRoom->Containers.end())
               picker = outfitIt->second;
            else {
               auto typeIt = allRoom->Containers.find(container->getType());
               if (typeIt != allRoom->Containers.end())
                  picker = typeIt->second;
            }
         }
         rollItem(picker, container, true, playerArg, nullptr);
      }
   }
// ...existing code...

   static void fillContainerType(std::shared_ptr<ItemPickerRoom> room, ItemContainer* container, const std::string& roomName, IsoGameCharacter* character) {
      bool doFill = std::find(NoContainerFillRooms.begin(), NoContainerFillRooms.end(), roomName) == NoContainerFillRooms.end();
      if (!room) return;
      auto allIt = room->Containers.find("all");
      if (allIt != room->Containers.end()) {
         rollItem(allIt->second, container, doFill, character, room.get());
      }
      auto typeIt = room->Containers.find(container->getType());
      std::shared_ptr<ItemPickerContainer> picker = nullptr;
      if (typeIt != room->Containers.end())
         picker = typeIt->second;
      else {
         auto otherIt = room->Containers.find("other");
         if (otherIt != room->Containers.end())
            picker = otherIt->second;
      }
      if (picker)
         rollItem(picker, container, doFill, character, room.get());
   }
// ...existing code...

      static InventoryItem* tryAddItemToContainer(ItemContainer* container, const std::string& itemName, std::shared_ptr<ItemPickerContainer> picker) {
            Item* item = ScriptManager::instance.FindItem(itemName);
            if (!item || item->OBSOLETE) return nullptr;
            float weight = item->getActualWeight() * item->getCount();
            if (!container->hasRoomFor(nullptr, weight)) return nullptr;
            if (auto* parentCont = dynamic_cast<InventoryContainer*>(container->getContainingItem())) {
                  ItemContainer* parent = parentCont->getContainer();
                  if (parent && !parent->hasRoomFor(nullptr, weight)) return nullptr;
            }
            return container->AddItem(itemName);
      }
// ...existing code...

    static void rollProceduralItem(const std::vector<std::shared_ptr<ProceduralItem>>& items, ItemContainer* container, float lootIntensity, IsoGameCharacter* character, ItemPickerRoom* room) {
        if (!container || !container->getSourceGrid() || !container->getSourceGrid()->getRoom()) return;
        auto& spawned = container->getSourceGrid()->getRoom()->getRoomDef()->getProceduralSpawnedContainer();
        std::unordered_map<std::string, int> forceMap;
        std::unordered_map<std::string, int> weightMap;
        for (const auto& item : items) {
            const std::string& name = item->name;
            int min = item->min;
            int max = item->max;
            int weightChance = item->weightChance;
            const auto& forceForItems = item->forceForItems;
            const auto& forceForZones = item->forceForZones;
            const auto& forceForTiles = item->forceForTiles;
            const auto& forceForRooms = item->forceForRooms;
            if (spawned.find(name) == spawned.end()) spawned[name] = 0;
            if (!forceForItems.empty()) {
                // ... implement forceForItems logic ...
                // For brevity, this is a placeholder. Implement as needed.
                forceMap[name] = -1;
            } else if (forceForZones.empty()) {
                if (!forceForTiles.empty()) {
                    // ... implement forceForTiles logic ...
                    forceMap[name] = -1;
                } else if (!forceForRooms.empty()) {
                    // ... implement forceForRooms logic ...
                    forceMap[name] = -1;
                }
            } else {
                // ... implement forceForZones logic ...
                forceMap[name] = -1;
            }
            if (forceForItems.empty() && forceForZones.empty() && forceForTiles.empty() && forceForRooms.empty()) {
                if (min == 1 && spawned[name] == 0) {
                    forceMap[name] = weightChance;
                } else if (spawned[name] < max) {
                    weightMap[name] = weightChance;
                }
            }
        }
        std::string distrib;
        if (!forceMap.empty())
            distrib = getDistribInHashMap(forceMap);
        else if (!weightMap.empty())
            distrib = getDistribInHashMap(weightMap);
        if (!distrib.empty()) {
            auto it = ProceduralDistributions.find(distrib);
            if (it != ProceduralDistributions.end()) {
                auto& picker = it->second;
                if (picker->junk)
                    doRollItem(picker->junk, container, lootIntensity, character, true, true, room);
                doRollItem(picker, container, lootIntensity, character, true, false, room);
                spawned[distrib] += 1;
            }
        }
    }
// ...existing code...

      static std::string getDistribInHashMap(const std::unordered_map<std::string, int>& map) {
            int total = 0;
            for (const auto& kv : map) total += kv.second;
            if (total == -1) {
                  int idx = Rand::Next(map.size());
                  int i = 0;
                  for (const auto& kv : map) {
                        if (i == idx) return kv.first;
                        ++i;
                  }
            }
            int r = Rand::Next(total);
            int acc = 0;
            for (const auto& kv : map) {
                  acc += kv.second;
                  if (acc >= r) return kv.first;
            }
            return std::string();
      }
// ...existing code...

   static void rollItem(std::shared_ptr<ItemPickerContainer> picker, ItemContainer* container, bool doFill, IsoGameCharacter* character, ItemPickerRoom* room) {
      if (GameClient::bClient || GameServer::bServer) return;
      player = IsoPlayer::getInstance();
      if (!picker || !container) return;
      float lootIntensity = 0.0f;
      IsoMetaChunk* chunk = nullptr;
      if (player && IsoWorld::instance)
         chunk = IsoWorld::instance->getMetaChunk(static_cast<int>(player->getX()) / 10, static_cast<int>(player->getY()) / 10);
      else if (container->getSourceGrid())
         chunk = IsoWorld::instance->getMetaChunk(container->getSourceGrid()->getX() / 10, container->getSourceGrid()->getY() / 10);
      if (chunk)
         lootIntensity = chunk->getLootZombieIntensity();
      if (lootIntensity > zombieDensityCap)
         lootIntensity = zombieDensityCap;
      if (picker->ignoreZombieDensity)
         lootIntensity = 0.0f;
      if (picker->procedural)
         rollProceduralItem(picker->proceduralItems, container, lootIntensity, character, room);
      else {
         if (picker->junk)
            doRollItem(picker->junk, container, lootIntensity, character, doFill, true, room);
         doRollItem(picker, container, lootIntensity, character, doFill, false, room);
      }
   }
// ...existing code...

    static void doRollItem(std::shared_ptr<ItemPickerContainer> picker, ItemContainer* container, float lootIntensity, IsoGameCharacter* character, bool doFill, bool isJunk, ItemPickerRoom* room) {
        bool lucky = false, unlucky = false;
        std::string itemName;
        if (player && character) {
            lucky = character->Traits.Lucky.isSet();
            unlucky = character->Traits.Unlucky.isSet();
        }
        for (int i = 0; i < picker->rolls; ++i) {
            for (const auto& item : picker->Items) {
                float chance = item->chance;
                itemName = item->itemName;
                if (lucky) chance *= 1.1f;
                if (unlucky) chance *= 0.9f;
                float lootMod = getLootModifier(itemName);
                if (lootMod == 0.0f) return;
                if (isJunk) {
                    lootIntensity = 0.0f;
                    lootMod = 1.0f;
                    chance *= 1.4f;
                }
                if (Rand::Next(10000) <= chance * 100.0f * lootMod + lootIntensity * 10.0f) {
                    InventoryItem* added = tryAddItemToContainer(container, itemName, picker);
                    if (!added) return;
                    checkStashItem(added, picker);
                    if (container->getType() == "freezer" && dynamic_cast<Food*>(added) && static_cast<Food*>(added)->isFreezing())
                        static_cast<Food*>(added)->freeze();
                    if (auto* key = dynamic_cast<Key*>(added)) {
                        key->takeKeyId();
                        if (container->getSourceGrid() && container->getSourceGrid()->getBuilding() && container->getSourceGrid()->getBuilding()->getDef()) {
                            int keySpawned = container->getSourceGrid()->getBuilding()->getDef()->getKeySpawned();
                            if (keySpawned < 2)
                                container->getSourceGrid()->getBuilding()->getDef()->setKeySpawned(keySpawned + 1);
                            else
                                container->Remove(added);
                        }
                    }
                    std::string mediaCat = added->getScriptItem()->getRecordedMediaCat();
                    if (!mediaCat.empty()) {
                        auto* recMedia = ZomboidRadio::getInstance()->getRecordedMedia();
                        MediaData* mediaData = recMedia->getRandomFromCategory(mediaCat);
                        if (!mediaData) {
                            container->Remove(added);
                            if (mediaCat == "Home-VHS") {
                                mediaData = recMedia->getRandomFromCategory("Retail-VHS");
                                if (!mediaData) return;
                                added = container->AddItem("Base.VHS_Retail");
                                if (!added) return;
                                added->setRecordedMediaData(mediaData);
                            }
                            return;
                        }
                        added->setRecordedMediaData(mediaData);
                    }
                    if (WeaponUpgradeMap.count(added->getType()))
                        DoWeaponUpgrade(added);
                    if (!picker->noAutoAge)
                        added->setAutoAge();
                    bool isShop = room ? room->isShop : false;
                    if (!isShop && Rand::Next(100) < 40 && dynamic_cast<DrainableComboItem*>(added)) {
                        float maxUse = 1.0f / static_cast<DrainableComboItem*>(added)->getUseDelta();
                        static_cast<DrainableComboItem*>(added)->setUsedDelta(Rand::Next(1.0f, maxUse - 1.0f) * static_cast<DrainableComboItem*>(added)->getUseDelta());
                    }
                    if (!isShop && dynamic_cast<HandWeapon*>(added) && Rand::Next(100) < 40)
                        added->setCondition(Rand::Next(1, added->getConditionMax()));
                    if (auto* weapon = dynamic_cast<HandWeapon*>(added); weapon && !picker->dontSpawnAmmo && Rand::Next(100) < 90) {
                        int ammoChance = 30;
                        if (Core::getInstance()->getOptionReloadDifficulty() > 1 && !StringUtils::isNullOrEmpty(weapon->getMagazineType()) && Rand::Next(100) < 90) {
                            if (Rand::NextBool(3)) {
                                InventoryItem* mag = container->AddItem(weapon->getMagazineType());
                                if (Rand::NextBool(5)) mag->setCurrentAmmoCount(Rand::Next(1, mag->getMaxAmmo()));
                                if (!Rand::NextBool(5)) mag->setCurrentAmmoCount(mag->getMaxAmmo());
                            } else {
                                if (!StringUtils::isNullOrWhitespace(weapon->getMagazineType())) weapon->setContainsClip(true);
                                if (Rand::NextBool(6)) weapon->setCurrentAmmoCount(Rand::Next(1, weapon->getMaxAmmo()));
                                else ammoChance = Rand::Next(60, 100);
                            }
                            if (weapon->haveChamber()) weapon->setRoundChambered(true);
                        }
                        if (Core::getInstance()->getOptionReloadDifficulty() == 1 || (StringUtils::isNullOrEmpty(weapon->getMagazineType()) && Rand::Next(100) < 30)) {
                            weapon->setCurrentAmmoCount(Rand::Next(1, weapon->getMaxAmmo()));
                            if (weapon->haveChamber()) weapon->setRoundChambered(true);
                        }
                        if (!StringUtils::isNullOrEmpty(weapon->getAmmoBox()) && Rand::Next(100) < ammoChance)
                            container->AddItem(weapon->getAmmoBox());
                        else if (!StringUtils::isNullOrEmpty(weapon->getAmmoType()) && Rand::Next(100) < 50)
                            container->AddItems(weapon->getAmmoType(), Rand::Next(1, 5));
                    }
                    if (auto* invCont = dynamic_cast<InventoryContainer*>(added)) {
                        auto it = containers.find(added->getType());
                        if (doFill && it != containers.end() && Rand::Next(it->second->fillRand) == 0)
                            rollContainerItem(invCont, character, it->second);
                    }
                }
            }
        }
    }
// ...existing code...

   static void checkStashItem(InventoryItem* item, std::shared_ptr<ItemPickerContainer> picker) {
      if (picker->stashChance > 0 && dynamic_cast<MapItem*>(item) && !StringUtils::isNullOrEmpty(static_cast<MapItem*>(item)->getMapID()))
         item->setStashChance(picker->stashChance);
      StashSystem::checkStashItem(item);
   }
// ...existing code...

    static void rollContainerItem(InventoryContainer* invCont, IsoGameCharacter* character, std::shared_ptr<ItemPickerContainer> picker) {
        if (!picker) return;
        ItemContainer* container = invCont->getInventory();
        float lootIntensity = 0.0f;
        IsoMetaChunk* chunk = nullptr;
        if (player && IsoWorld::instance)
            chunk = IsoWorld::instance->getMetaChunk(static_cast<int>(player->getX()) / 10, static_cast<int>(player->getY()) / 10);
        if (chunk)
            lootIntensity = chunk->getLootZombieIntensity();
        if (lootIntensity > zombieDensityCap)
            lootIntensity = zombieDensityCap;
        if (picker->ignoreZombieDensity)
            lootIntensity = 0.0f;
        bool lucky = false, unlucky = false;
        std::string itemName;
        if (player && character) {
            lucky = character->Traits.Lucky.isSet();
            unlucky = character->Traits.Unlucky.isSet();
        }
        for (int i = 0; i < picker->rolls; ++i) {
            for (const auto& item : picker->Items) {
                float chance = item->chance;
                itemName = item->itemName;
                if (lucky) chance *= 1.1f;
                if (unlucky) chance *= 0.9f;
                float lootMod = getLootModifier(itemName);
                if (Rand::Next(10000) <= chance * 100.0f * lootMod + lootIntensity * 10.0f) {
                    InventoryItem* added = tryAddItemToContainer(container, itemName, picker);
                    if (!added) return;
                    if (auto* mapItem = dynamic_cast<MapItem*>(added)) {
                        if (!StringUtils::isNullOrEmpty(mapItem->getMapID()) && picker->maxMap > 0) {
                            int mapCount = 0;
                            for (const auto& it : container->getItems()) {
                                if (auto* m = dynamic_cast<MapItem*>(it.get()))
                                    if (!StringUtils::isNullOrEmpty(m->getMapID()))
                                        ++mapCount;
                            }
                            if (mapCount > picker->maxMap)
                                container->Remove(added);
                        }
                    }
                    checkStashItem(added, picker);
                    if (container->getType() == "freezer" && dynamic_cast<Food*>(added) && static_cast<Food*>(added)->isFreezing())
                        static_cast<Food*>(added)->freeze();
                    if (auto* key = dynamic_cast<Key*>(added)) {
                        key->takeKeyId();
                        if (container->getSourceGrid() && container->getSourceGrid()->getBuilding() && container->getSourceGrid()->getBuilding()->getDef()) {
                            int keySpawned = container->getSourceGrid()->getBuilding()->getDef()->getKeySpawned();
                            if (keySpawned < 2)
                                container->getSourceGrid()->getBuilding()->getDef()->setKeySpawned(keySpawned + 1);
                            else
                                container->Remove(added);
                        }
                    }
                    if (container->getType() != "freezer")
                        added->setAutoAge();
                }
            }
        }
    }
// ...existing code...

   static void DoWeaponUpgrade(InventoryItem* item) {
      auto it = WeaponUpgradeMap.find(item->getType());
      if (it != WeaponUpgradeMap.end() && !it->second->Upgrades.empty()) {
         int count = Rand::Next(it->second->Upgrades.size());
         for (int i = 0; i < count; ++i) {
            std::string upgrade = PZArrayUtil::pickRandom(it->second->Upgrades);
            InventoryItem* part = InventoryItemFactory::CreateItem(upgrade);
            static_cast<HandWeapon*>(item)->attachWeaponPart(static_cast<WeaponPart*>(part));
         }
      }
   }
// ...existing code...

    static float getLootModifier(const std::string& name) {
        Item* item = ScriptManager::instance.FindItem(name);
        if (!item) return 0.6f;
        float mod = OtherLootModifier;
        if (item->getType() == zombie::scripting::objects::Item::Type::Food) {
            if (item->CannedFood) mod = CannedFoodLootModifier;
            else mod = FoodLootModifier;
        }
        if (item->getDisplayCategory() == "Ammo") mod = AmmoLootModifier;
        if (item->getType() == zombie::scripting::objects::Item::Type::Weapon && !item->isRanged()) mod = WeaponLootModifier;
        if (item->getType() == zombie::scripting::objects::Item::Type::WeaponPart
            || (item->getType() == zombie::scripting::objects::Item::Type::Weapon && item->isRanged())
            || (item->getType() == zombie::scripting::objects::Item::Type::Normal && !StringUtils::isNullOrEmpty(item->getAmmoType())))
            mod = RangedWeaponLootModifier;
        if (item->getType() == zombie::scripting::objects::Item::Type::Literature) mod = LiteratureLootModifier;
        if (item->Medical) mod = MedicalLootModifier;
        if (item->SurvivalGear) mod = SurvivalGearsLootModifier;
        if (item->MechanicsItem) mod = MechanicsLootModifier;
        return mod;
    }
// ...existing code...

   static void updateOverlaySprite(IsoObject* obj) {
      ContainerOverlays::instance.updateContainerOverlaySprite(obj);
   }

   static void doOverlaySprite(IsoGridSquare* square) {
      if (GameClient::bClient) return;
      if (!square || !square->getRoom() || square->isOverlayDone()) return;
      auto& objects = square->getObjects();
      for (auto& obj : objects) {
         if (obj && obj->getContainer() && !obj->getContainer()->isExplored()) {
            fillContainer(obj->getContainer(), IsoPlayer::getInstance());
            obj->getContainer()->setExplored(true);
            if (GameServer::bServer)
               GlobalObject::sendItemsInContainer(obj.get(), obj->getContainer());
         }
         updateOverlaySprite(obj.get());
      }
      square->setOverlayDone(true);
   }
// ...existing code...

   static std::shared_ptr<ItemPickerContainer> getItemContainer(const std::string& roomName, const std::string& type, const std::string& procName, bool wantJunk) {
      auto roomIt = rooms.find(roomName);
      if (roomIt == rooms.end()) return nullptr;
      auto& room = roomIt->second;
      auto pickerIt = room->Containers.find(type);
      if (pickerIt != room->Containers.end() && pickerIt->second->procedural) {
         for (const auto& proc : pickerIt->second->proceduralItems) {
            if (proc->name == procName) {
               auto procIt = ProceduralDistributions.find(procName);
               if (procIt != ProceduralDistributions.end()) {
                  if (wantJunk && procIt->second->junk)
                     return procIt->second->junk;
                  if (!wantJunk)
                     return procIt->second;
               }
            }
         }
      }
      return wantJunk && pickerIt != room->Containers.end() ? pickerIt->second->junk : (pickerIt != room->Containers.end() ? pickerIt->second : nullptr);
   }
}
} // namespace inventory
} // namespace zombie

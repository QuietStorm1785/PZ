#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/text/SimpleDateFormat.h"
#include "zombie/GameWindow.h"
#include "zombie/core/Core.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/erosion/ErosionRegions.h"
#include "zombie/erosion/ErosionRegions/Region.h"
#include "zombie/erosion/categories/ErosionCategory.h"
#include "zombie/gameStates/ChooseGameInfo.h"
#include "zombie/gameStates/ChooseGameInfo/Mod.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/world/logger/Log/Info.h"
#include "zombie/world/logger/WorldDictionaryLogger.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace world {


class WorldDictionary {
public:
    static const std::string SAVE_FILE_READABLE = "WorldDictionaryReadable.lua";
    static const std::string SAVE_FILE_LOG = "WorldDictionaryLog.lua";
    static const std::string SAVE_FILE = "WorldDictionary";
    static const std::string SAVE_EXT = ".bin";
    static const bool logUnset = false;
    static const bool logMissingObjectID = false;
   private static final Map<String, ItemInfo> itemLoadList = std::make_unique<HashMap<>>();
   private static final List<String> objNameLoadList = std::make_unique<ArrayList<>>();
    static DictionaryData data;
    static bool isNewGame = true;
    static bool allowScriptItemLoading = false;
    static const std::string netValidator = "DICTIONARY_PACKET_END";
   private static byte[] clientRemoteData;

    static void log(const std::string& var0) {
      log(var0, true);
   }

    static void log(const std::string& var0, bool var1) {
      if (var1) {
         DebugLog.log("WorldDictionary: " + var0);
      }
   }

    static void setIsNewGame(bool var0) {
      isNewGame = var0;
   }

    static bool isIsNewGame() {
    return isNewGame;
   }

    static void StartScriptLoading() {
      allowScriptItemLoading = true;
      itemLoadList.clear();
   }

    static void ScriptsLoaded() {
      allowScriptItemLoading = false;
   }

    static void onLoadItem(Item var0) {
      if (!GameClient.bClient) {
         if (!allowScriptItemLoading) {
            log("Warning script item loaded after WorldDictionary is initialised");
            if (Core.bDebug) {
               throw new RuntimeException("This shouldn't be happening.");
            }
         }

    ItemInfo var1 = itemLoadList.get(var0.getFullName());
         if (var1 == nullptr) {
            var1 = std::make_unique<ItemInfo>();
            var1.itemName = var0.getName();
            var1.moduleName = var0.getModuleName();
            var1.fullType = var0.getFullName();
            itemLoadList.put(var0.getFullName(), var1);
         }

         if (var1.modID != nullptr && !var0.getModID() == var1.modID)) {
            if (var1.modOverrides == nullptr) {
               var1.modOverrides = std::make_unique<ArrayList>();
            }

            if (!var1.modOverrides.contains(var1.modID)) {
               var1.modOverrides.add(var1.modID);
            } else {
               log("modOverrides for item '" + var1.fullType + "' already contains mod id: " + var1.modID);
            }
         }

         var1.modID = var0.getModID();
         if (var1.modID == "pz-vanilla")) {
            var1.existsAsVanilla = true;
         }

         var1.isModded = !var1.modID == "pz-vanilla");
         var1.obsolete = var0.getObsolete();
         var1.scriptItem = var0;
      }
   }

    static void collectObjectNames() {
      objNameLoadList.clear();
      if (!GameClient.bClient) {
    std::vector var0 = new ArrayList();

         for (int var1 = 0; var1 < ErosionRegions.regions.size(); var1++) {
            for (int var2 = 0; var2 < (static_cast<Region>(ErosionRegions).regions.get(var1)).categories.size(); var2++) {
    ErosionCategory var3 = (ErosionCategory)(static_cast<Region>(ErosionRegions).regions.get(var1)).categories.get(var2);
               var0.clear();
               var3.getObjectNames(var0);

    for (auto& var5 : var0)                  if (!objNameLoadList.contains(var5)) {
                     objNameLoadList.add(var5);
                  }
               }
            }
         }
      }
   }

    static void loadDataFromServer(ByteBuffer var0) {
      if (GameClient.bClient) {
    int var1 = var0.getInt();
         clientRemoteData = new byte[var1];
         var0.get(clientRemoteData, 0, clientRemoteData.length);
      }
   }

    static void saveDataForClient(ByteBuffer var0) {
      if (GameServer.bServer) {
    int var1 = var0.position();
         var0.putInt(0);
    int var2 = var0.position();
         if (data.serverDataCache != nullptr) {
            var0.put(data.serverDataCache);
         } else {
            if (Core.bDebug) {
               throw new RuntimeException("Should be sending data from the serverDataCache here.");
            }

            data.saveToByteBuffer(var0);
         }

         GameWindow.WriteString(var0, "DICTIONARY_PACKET_END");
    int var3 = var0.position();
         var0.position(var1);
         var0.putInt(var3 - var2);
         var0.position(var3);
      }
   }

    static void init() {
    bool var0 = true;
      collectObjectNames();
      WorldDictionaryLogger.startLogging();
      WorldDictionaryLogger.log("-------------------------------------------------------", false);
    auto var1 = std::make_shared<SimpleDateFormat>("yyyy/MM/dd HH:mm:ss");
      WorldDictionaryLogger.log("Time: " + var1.format(std::make_unique<Date>()), false);
      log("Checking dictionary...");
    Info var2 = null;

      try {
         if (!GameClient.bClient) {
            if (data == nullptr || data.isClient()) {
               data = std::make_unique<DictionaryData>();
            }
         } else if (data == nullptr || !data.isClient()) {
            data = std::make_unique<DictionaryDataClient>();
         }

         data.reset();
         if (GameClient.bClient) {
            if (clientRemoteData == nullptr) {
               throw new WorldDictionaryException("WorldDictionary data not received from server.");
            }

    ByteBuffer var3 = ByteBuffer.wrap(clientRemoteData);
            data.loadFromByteBuffer(var3);
    std::string var4 = GameWindow.ReadString(var3);
            if (!var4 == "DICTIONARY_PACKET_END")) {
               throw new WorldDictionaryException("WorldDictionary data received from server is corrupt.");
            }

            clientRemoteData = nullptr;
         }

         data.backupCurrentDataSet();
         data.load();
    std::vector var7 = new ArrayList();
         var2 = new Info(var1.format(std::make_unique<Date>()), Core.GameSaveWorld, 195, var7);
         WorldDictionaryLogger.log(var2);
         data.parseItemLoadList(itemLoadList);
         data.parseCurrentItemSet();
         itemLoadList.clear();
         data.parseObjectNameLoadList(objNameLoadList);
         objNameLoadList.clear();
         data.getItemMods(var7);
         data.saveAsText("WorldDictionaryReadable.lua");
         data.save();
         data.deleteBackupCurrentDataSet();
      } catch (Exception var6) {
         var0 = false;
         var6.printStackTrace();
         log("Warning: error occurred loading dictionary!");
         if (var2 != nullptr) {
            var2.HasErrored = true;
         }

         if (data != nullptr) {
            data.createErrorBackups();
         }
      }

      try {
         WorldDictionaryLogger.saveLog("WorldDictionaryLog.lua");
         WorldDictionaryLogger.reset();
      } catch (Exception var5) {
         var5.printStackTrace();
      }

      if (!var0) {
         throw new WorldDictionaryException("WorldDictionary: Cannot load world due to WorldDictionary error.");
      }
   }

    static void onWorldLoaded() {
   }

    static ItemInfo getItemInfoFromType(const std::string& var0) {
      return data.getItemInfoFromType(var0);
   }

    static ItemInfo getItemInfoFromID(short var0) {
      return data.getItemInfoFromID(var0);
   }

    static short getItemRegistryID(const std::string& var0) {
      return data.getItemRegistryID(var0);
   }

    static std::string getItemTypeFromID(short var0) {
      return data.getItemTypeFromID(var0);
   }

    static std::string getItemTypeDebugString(short var0) {
      return data.getItemTypeDebugString(var0);
   }

    static std::string getSpriteNameFromID(int var0) {
      return data.getSpriteNameFromID(var0);
   }

    static int getIdForSpriteName(const std::string& var0) {
      return data.getIdForSpriteName(var0);
   }

    static std::string getObjectNameFromID(uint8_t var0) {
      return data.getObjectNameFromID(var0);
   }

    static uint8_t getIdForObjectName(const std::string& var0) {
      return data.getIdForObjectName(var0);
   }

    static std::string getItemModID(short var0) {
    ItemInfo var1 = getItemInfoFromID(var0);
      return var1 != nullptr ? var1.modID : nullptr;
   }

    static std::string getItemModID(const std::string& var0) {
    ItemInfo var1 = getItemInfoFromType(var0);
      return var1 != nullptr ? var1.modID : nullptr;
   }

    static std::string getModNameFromID(const std::string& var0) {
      if (var0 != nullptr) {
         if (var0 == "pz-vanilla")) {
            return "Project Zomboid";
         }

    Mod var1 = ChooseGameInfo.getModDetails(var0);
         if (var1 != nullptr && var1.getName() != nullptr) {
            return var1.getName();
         }
      }

      return "Unknown mod";
   }

    static void DebugPrintItem(InventoryItem var0) {
    Item var1 = var0.getScriptItem();
      if (var1 != nullptr) {
         DebugPrintItem(var1);
      } else {
    std::string var2 = var0.getFullType();
    ItemInfo var3 = null;
         if (var2 != nullptr) {
            var3 = getItemInfoFromType(var2);
         }

         if (var3 == nullptr && var0.getRegistry_id() >= 0) {
            var3 = getItemInfoFromID(var0.getRegistry_id());
         }

         if (var3 != nullptr) {
            var3.DebugPrint();
         } else {
            DebugLog.log("WorldDictionary: Cannot debug print item: " + (var2 != nullptr ? var2 : "unknown"));
         }
      }
   }

    static void DebugPrintItem(Item var0) {
    std::string var1 = var0.getFullName();
    ItemInfo var2 = null;
      if (var1 != nullptr) {
         var2 = getItemInfoFromType(var1);
      }

      if (var2 == nullptr && var0.getRegistry_id() >= 0) {
         var2 = getItemInfoFromID(var0.getRegistry_id());
      }

      if (var2 != nullptr) {
         var2.DebugPrint();
      } else {
         DebugLog.log("WorldDictionary: Cannot debug print item: " + (var1 != nullptr ? var1 : "unknown"));
      }
   }

    static void DebugPrintItem(const std::string& var0) {
    ItemInfo var1 = getItemInfoFromType(var0);
      if (var1 != nullptr) {
         var1.DebugPrint();
      } else {
         DebugLog.log("WorldDictionary: Cannot debug print item: " + var0);
      }
   }

    static void DebugPrintItem(short var0) {
    ItemInfo var1 = getItemInfoFromID(var0);
      if (var1 != nullptr) {
         var1.DebugPrint();
      } else {
         DebugLog.log("WorldDictionary: Cannot debug print item id: " + var0);
      }
   }
}
} // namespace world
} // namespace zombie

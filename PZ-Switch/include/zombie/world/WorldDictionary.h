#pragma once
#include "java/text/SimpleDateFormat.h"
#include "zombie/GameWindow.h"
#include "zombie/core/Core.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/erosion/ErosionRegions.h"
#include "zombie/erosion/categories/ErosionCategory.h"
#include "zombie/gameStates/ChooseGameInfo.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/world/logger/Log.h"
#include "zombie/world/logger/WorldDictionaryLogger.h"
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace world {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class WorldDictionary {
public:
 static const std::string SAVE_FILE_READABLE = "WorldDictionaryReadable.lua";
 static const std::string SAVE_FILE_LOG = "WorldDictionaryLog.lua";
 static const std::string SAVE_FILE = "WorldDictionary";
 static const std::string SAVE_EXT = ".bin";
 static const bool logUnset = false;
 static const bool logMissingObjectID = false;
private
 static Map<String, ItemInfo> itemLoadList =
 std::make_unique<HashMap<>>();
private
 static List<String> objNameLoadList = std::make_unique<ArrayList<>>();
 static DictionaryData data;
 static bool isNewGame = true;
 static bool allowScriptItemLoading = false;
 static const std::string netValidator = "DICTIONARY_PACKET_END";
private
 static byte[] clientRemoteData;

 static void log(const std::string &string) { log(string, true); }

 static void log(const std::string &string, bool boolean0) {
 if (boolean0) {
 DebugLog.log("WorldDictionary: " + string);
 }
 }

 static void setIsNewGame(bool boolean0) { isNewGame = boolean0; }

 static bool isIsNewGame() { return isNewGame; }

 static void StartScriptLoading() {
 allowScriptItemLoading = true;
 itemLoadList.clear();
 }

 static void ScriptsLoaded() { allowScriptItemLoading = false; }

 static void onLoadItem(Item item) {
 if (!GameClient.bClient) {
 if (!allowScriptItemLoading) {
 log("Warning script item loaded after WorldDictionary is initialised");
 if (Core.bDebug) {
 throw RuntimeException("This shouldn't be happening.");
 }
 }

 ItemInfo itemInfo = itemLoadList.get(item.getFullName());
 if (itemInfo.empty()) {
 itemInfo = std::make_unique<ItemInfo>();
 itemInfo.itemName = item.getName();
 itemInfo.moduleName = item.getModuleName();
 itemInfo.fullType = item.getFullName();
 itemLoadList.put(item.getFullName(), itemInfo);
 }

 if (itemInfo.modID != nullptr && !item.getModID() == itemInfo.modID) {
 if (itemInfo.modOverrides.empty()) {
 itemInfo.modOverrides = std::make_unique<ArrayList<>>();
 }

 if (!itemInfo.modOverrides.contains(itemInfo.modID) {
 itemInfo.modOverrides.add(itemInfo.modID);
 } else {
 log("modOverrides for item '" + itemInfo.fullType +
 "' already contains mod id: " + itemInfo.modID);
 }
 }

 itemInfo.modID = item.getModID();
 if (itemInfo.modID == "pz-vanilla")) {
 itemInfo.existsAsVanilla = true;
 }

 itemInfo.isModded = !itemInfo.modID == "pz-vanilla");
 itemInfo.obsolete = item.getObsolete();
 itemInfo.scriptItem = item;
 }
 }

 static void collectObjectNames() {
 objNameLoadList.clear();
 if (!GameClient.bClient) {
 std::vector arrayList = new ArrayList();

 for (int int0 = 0; int0 < ErosionRegions.regions.size(); int0++) {
 for (int int1 = 0;
 int1 < ErosionRegions.regions.get(int0).categories.size();
 int1++) {
 ErosionCategory erosionCategory =
 ErosionRegions.regions.get(int0).categories.get(int1);
 arrayList.clear();
 erosionCategory.getObjectNames(arrayList);

 for (auto &string : arrayList)
 if (!objNameLoadList.contains(string) {
 objNameLoadList.add(string);
 }
 }
 }
 }
 }
}

static void
loadDataFromServer(ByteBuffer byteBuffer) {
 if (GameClient.bClient) {
 int int0 = byteBuffer.getInt();
 clientRemoteData = new byte[int0];
 byteBuffer.get(clientRemoteData, 0, clientRemoteData.length);
 }
}

static void saveDataForClient(ByteBuffer byteBuffer) {
 if (GameServer.bServer) {
 int int0 = byteBuffer.position();
 byteBuffer.putInt(0);
 int int1 = byteBuffer.position();
 if (data.serverDataCache != nullptr) {
 byteBuffer.put(data.serverDataCache);
 } else {
 if (Core.bDebug) {
 throw RuntimeException(
 "Should be sending data from the serverDataCache here.");
 }

 data.saveToByteBuffer(byteBuffer);
 }

 GameWindow.WriteString(byteBuffer, "DICTIONARY_PACKET_END");
 int int2 = byteBuffer.position();
 byteBuffer.position(int0);
 byteBuffer.putInt(int2 - int1);
 byteBuffer.position(int2);
 }
}

static void init() {
 bool boolean0 = true;
 collectObjectNames();
 WorldDictionaryLogger.startLogging();
 WorldDictionaryLogger.log(
 "-------------------------------------------------------", false);
 SimpleDateFormat simpleDateFormat =
 new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
 WorldDictionaryLogger.log(
 "Time: " + simpleDateFormat.format(std::make_unique<Date>()), false);
 log("Checking dictionary...");
 Log.Info info = nullptr;

 try {
 if (!GameClient.bClient) {
 if (data.empty() || data.isClient()) {
 data = std::make_unique<DictionaryData>();
 }
 } else if (data.empty() || !data.isClient()) {
 data = std::make_unique<DictionaryDataClient>();
 }

 data.reset();
 if (GameClient.bClient) {
 if (clientRemoteData.empty()) {
 throw WorldDictionaryException(
 "WorldDictionary data not received from server.");
 }

 ByteBuffer byteBuffer = ByteBuffer.wrap(clientRemoteData);
 data.loadFromByteBuffer(byteBuffer);
 std::string string = GameWindow.ReadString(byteBuffer);
 if (!string == "DICTIONARY_PACKET_END")) {
 throw WorldDictionaryException(
 "WorldDictionary data received from server is corrupt.");
 }

 clientRemoteData = nullptr;
 }

 data.backupCurrentDataSet();
 data.load();
 std::vector arrayList = new ArrayList();
 info = new Log.Info(simpleDateFormat.format(std::make_unique<Date>()),
 Core.GameSaveWorld, 195, arrayList);
 WorldDictionaryLogger.log(info);
 data.parseItemLoadList(itemLoadList);
 data.parseCurrentItemSet();
 itemLoadList.clear();
 data.parseObjectNameLoadList(objNameLoadList);
 objNameLoadList.clear();
 data.getItemMods(arrayList);
 data.saveAsText("WorldDictionaryReadable.lua");
 data.save();
 data.deleteBackupCurrentDataSet();
 } catch (Exception exception0) {
 boolean0 = false;
 exception0.printStackTrace();
 log("Warning: error occurred loading dictionary!");
 if (info != nullptr) {
 info.HasErrored = true;
 }

 if (data != nullptr) {
 data.createErrorBackups();
 }
 }

 try {
 WorldDictionaryLogger.saveLog("WorldDictionaryLog.lua");
 WorldDictionaryLogger.reset();
 } catch (Exception exception1) {
 exception1.printStackTrace();
 }

 if (!boolean0) {
 throw WorldDictionaryException(
 "WorldDictionary: Cannot load world due to WorldDictionary error.");
 }
}

static void onWorldLoaded() {}

static ItemInfo getItemInfoFromType(const std::string &string) {
 return data.getItemInfoFromType(string);
}

static ItemInfo getItemInfoFromID(short short0) {
 return data.getItemInfoFromID(short0);
}

static short getItemRegistryID(const std::string &string) {
 return data.getItemRegistryID(string);
}

static std::string getItemTypeFromID(short short0) {
 return data.getItemTypeFromID(short0);
}

static std::string getItemTypeDebugString(short short0) {
 return data.getItemTypeDebugString(short0);
}

static std::string getSpriteNameFromID(int int0) {
 return data.getSpriteNameFromID(int0);
}

static int getIdForSpriteName(const std::string &string) {
 return data.getIdForSpriteName(string);
}

static std::string getObjectNameFromID(uint8_t byte0) {
 return data.getObjectNameFromID(byte0);
}

static uint8_t getIdForObjectName(const std::string &string) {
 return data.getIdForObjectName(string);
}

static std::string getItemModID(short short0) {
 ItemInfo itemInfo = getItemInfoFromID(short0);
 return itemInfo != nullptr ? itemInfo.modID : nullptr;
}

static std::string getItemModID(const std::string &string) {
 ItemInfo itemInfo = getItemInfoFromType(string);
 return itemInfo != nullptr ? itemInfo.modID : nullptr;
}

static std::string getModNameFromID(const std::string &string) {
 if (string != nullptr) {
 if (string == "pz-vanilla")) {
 return "Project Zomboid";
 }

 ChooseGameInfo.Mod mod = ChooseGameInfo.getModDetails(string);
 if (mod != nullptr && mod.getName() != nullptr) {
 return mod.getName();
 }
 }

 return "Unknown mod";
}

static void DebugPrintItem(InventoryItem item1) {
 Item item0 = item1.getScriptItem();
 if (item0 != nullptr) {
 DebugPrintItem(item0);
 } else {
 std::string string = item1.getFullType();
 ItemInfo itemInfo = nullptr;
 if (string != nullptr) {
 itemInfo = getItemInfoFromType(string);
 }

 if (itemInfo.empty() && item1.getRegistry_id() >= 0) {
 itemInfo = getItemInfoFromID(item1.getRegistry_id());
 }

 if (itemInfo != nullptr) {
 itemInfo.DebugPrint();
 } else {
 DebugLog.log("WorldDictionary: Cannot debug print item: " +
 (string != nullptr ? string : "unknown"));
 }
 }
}

static void DebugPrintItem(Item item) {
 std::string string = item.getFullName();
 ItemInfo itemInfo = nullptr;
 if (string != nullptr) {
 itemInfo = getItemInfoFromType(string);
 }

 if (itemInfo.empty() && item.getRegistry_id() >= 0) {
 itemInfo = getItemInfoFromID(item.getRegistry_id());
 }

 if (itemInfo != nullptr) {
 itemInfo.DebugPrint();
 } else {
 DebugLog.log("WorldDictionary: Cannot debug print item: " +
 (string != nullptr ? string : "unknown"));
 }
}

static void DebugPrintItem(const std::string &string) {
 ItemInfo itemInfo = getItemInfoFromType(string);
 if (itemInfo != nullptr) {
 itemInfo.DebugPrint();
 } else {
 DebugLog.log("WorldDictionary: Cannot debug print item: " + string);
 }
}

static void DebugPrintItem(short short0) {
 ItemInfo itemInfo = getItemInfoFromID(short0);
 if (itemInfo != nullptr) {
 itemInfo.DebugPrint();
 } else {
 DebugLog.log("WorldDictionary: Cannot debug print item id: " + short0);
 }
}
}
} // namespace world
} // namespace zombie

#pragma once
#include "com/google/common/io/Files.h"
#include "java/time/Instant.h"
#include "zombie/GameWindow.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Core.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameServer.h"
#include "zombie/scripting/ScriptManager.h"
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

class DictionaryData {
public:
protected
 Map<Short, ItemInfo> itemIdToInfoMap = std::make_unique<HashMap<>>();
protected
 Map<String, ItemInfo> itemTypeToInfoMap = std::make_unique<HashMap<>>();
protected
 Map<String, Integer> spriteNameToIdMap = std::make_unique<HashMap<>>();
protected
 Map<Integer, String> spriteIdToNameMap = std::make_unique<HashMap<>>();
protected
 Map<String, Byte> objectNameToIdMap = std::make_unique<HashMap<>>();
protected
 Map<Byte, String> objectIdToNameMap = std::make_unique<HashMap<>>();
protected
 ArrayList<String> unsetObject = std::make_unique<ArrayList<>>();
protected
 ArrayList<String> unsetSprites = std::make_unique<ArrayList<>>();
 short NextItemID = 0;
 int NextSpriteNameID = 0;
 uint8_t NextObjectNameID = 0;
protected
 byte[] serverDataCache;
 File dataBackupPath;

 bool isClient() { return false; }

 void reset() {
 this->NextItemID = 0;
 this->NextSpriteNameID = 0;
 this->NextObjectNameID = 0;
 this->itemIdToInfoMap.clear();
 this->itemTypeToInfoMap.clear();
 this->objectIdToNameMap.clear();
 this->objectNameToIdMap.clear();
 this->spriteIdToNameMap.clear();
 this->spriteNameToIdMap.clear();
 }

 ItemInfo getItemInfoFromType(const std::string &string) {
 return this->itemTypeToInfoMap.get(string);
 }

 ItemInfo getItemInfoFromID(short short0) {
 return this->itemIdToInfoMap.get(short0);
 }

 short getItemRegistryID(const std::string &string) {
 ItemInfo itemInfo = this->itemTypeToInfoMap.get(string);
 if (itemInfo != nullptr) {
 return itemInfo.registryID;
 } else {
 if (Core.bDebug) {
 DebugLog.log("WARNING: Cannot get registry id for item: " + string);
 }

 return -1;
 }
 }

 std::string getItemTypeFromID(short short0) {
 ItemInfo itemInfo = this->itemIdToInfoMap.get(short0);
 return itemInfo != nullptr ? itemInfo.fullType : nullptr;
 }

 std::string getItemTypeDebugString(short short0) {
 std::string string = this->getItemTypeFromID(short0);
 if (string.empty()) {
 string = "Unknown";
 }

 return string;
 }

 std::string getSpriteNameFromID(int int0) {
 if (int0 >= 0) {
 if (this->spriteIdToNameMap.containsKey(int0) {
 return this->spriteIdToNameMap.get(int0);
 }

 IsoSprite sprite = IsoSprite.getSprite(IsoSpriteManager.instance, int0);
 if (sprite != nullptr && sprite.name != nullptr) {
 return sprite.name;
 }
 }

 DebugLog.log("WorldDictionary, Couldnt find sprite name for ID '" + int0 +
 "'.");
 return nullptr;
 }

 int getIdForSpriteName(const std::string &string) {
 if (string != nullptr) {
 if (this->spriteNameToIdMap.containsKey(string) {
 return this->spriteNameToIdMap.get(string);
 }

 IsoSprite sprite = IsoSpriteManager.instance.getSprite(string);
 if (sprite != nullptr && sprite.ID >= 0 && sprite.ID != 20000000 &&
 sprite.name == string) {
 return sprite.ID;
 }
 }

 return -1;
 }

 std::string getObjectNameFromID(uint8_t byte0) {
 if (byte0 >= 0) {
 if (this->objectIdToNameMap.containsKey(byte0) {
 return this->objectIdToNameMap.get(byte0);
 }

 if (Core.bDebug) {
 DebugLog.log("WorldDictionary, Couldnt find object name for ID '" +
 byte0 + "'.");
 }
 }

 return nullptr;
 }

 uint8_t getIdForObjectName(const std::string &string) {
 if (string != nullptr) {
 if (this->objectNameToIdMap.containsKey(string) {
 return this->objectNameToIdMap.get(string);
 }

 if (Core.bDebug) {
 }
 }

 return -1;
 }

 void getItemMods(List<String> list0) {
 list0.clear();

 for (Entry entry : this->itemIdToInfoMap.entrySet()) {
 if (!list0.contains(((ItemInfo)entry.getValue()).modID) {
 list0.add(((ItemInfo)entry.getValue()).modID);
 }

 if (((ItemInfo)entry.getValue()).modOverrides != nullptr) {
 std::vector list1 = ((ItemInfo)entry.getValue()).modOverrides;

 for (int int0 = 0; int0 < list1.size(); int0++) {
 if (!list0.contains(list1.get(int0)) {
 list0.add((String)list1.get(int0);
 }
 }
 }
 }
 }

 void getModuleList(List<String> list) {
 for (Entry entry : this->itemIdToInfoMap.entrySet()) {
 if (!list.contains(((ItemInfo)entry.getValue()).moduleName) {
 list.add(((ItemInfo)entry.getValue()).moduleName);
 }
 }
 }

 void parseItemLoadList(ItemInfo > map) {
 for (Entry entry : map.entrySet()) {
 ItemInfo itemInfo0 = (ItemInfo)entry.getValue();
 ItemInfo itemInfo1 = this->itemTypeToInfoMap.get(itemInfo0.fullType);
 if (itemInfo1.empty()) {
 if (!itemInfo0.obsolete) {
 if (this->NextItemID >= 32767) {
 throw WorldDictionaryException(
 "Max item ID value reached for WorldDictionary!");
 }

 itemInfo0.registryID = this->NextItemID++;
 itemInfo0.isLoaded = true;
 this->itemTypeToInfoMap.put(itemInfo0.fullType, itemInfo0);
 this->itemIdToInfoMap.put(itemInfo0.registryID, itemInfo0);
 WorldDictionaryLogger.log(new Log.RegisterItem(itemInfo0.copy()));
 }
 } else {
 if (itemInfo1.removed && !itemInfo0.obsolete) {
 itemInfo1.removed = false;
 WorldDictionaryLogger.log(new Log.ReinstateItem(itemInfo1.copy()));
 }

 if (!itemInfo1.modID == itemInfo0.modID) {
 std::string string = itemInfo1.modID;
 itemInfo1.modID = itemInfo0.modID;
 itemInfo1.isModded = !itemInfo0.modID == "pz-vanilla");
 WorldDictionaryLogger.log(new Log.ModIDChangedItem(
 itemInfo1.copy(), string, itemInfo1.modID);
 }

 if (itemInfo0.obsolete && (!itemInfo1.obsolete || !itemInfo1.removed) {
 itemInfo1.obsolete = true;
 itemInfo1.removed = true;
 WorldDictionaryLogger.log(new Log.ObsoleteItem(itemInfo1.copy()));
 }

 itemInfo1.isLoaded = true;
 }
 }
 }

 void parseCurrentItemSet() {
 for (Entry entry : this->itemTypeToInfoMap.entrySet()) {
 ItemInfo itemInfo = (ItemInfo)entry.getValue();
 if (!itemInfo.isLoaded) {
 itemInfo.removed = true;
 WorldDictionaryLogger.log(new Log.RemovedItem(itemInfo.copy(), false);
 }

 if (itemInfo.scriptItem.empty()) {
 itemInfo.scriptItem =
 ScriptManager.instance.getSpecificItem(itemInfo.fullType);
 }

 if (itemInfo.scriptItem != nullptr) {
 itemInfo.scriptItem.setRegistry_id(itemInfo.registryID);
 } else {
 itemInfo.removed = true;
 WorldDictionaryLogger.log(new Log.RemovedItem(itemInfo.copy(), true);
 }
 }
 }

 void parseObjectNameLoadList(List<String> list) {
 for (int int0 = 0; int0 < list.size(); int0++) {
 std::string string = (String)list.get(int0);
 if (!this->objectNameToIdMap.containsKey(string) {
 if (this->NextObjectNameID >= 127) {
 WorldDictionaryLogger.log("Max value for object names reached.");
 if (Core.bDebug) {
 throw WorldDictionaryException(
 "Max value for object names reached.");
 }
 } else {
 uint8_t byte0 = this->NextObjectNameID++;
 this->objectIdToNameMap.put(byte0, string);
 this->objectNameToIdMap.put(string, byte0);
 WorldDictionaryLogger.log(new Log.RegisterObject(string, byte0);
 }
 }
 }
 }

 void backupCurrentDataSet() {
 this->dataBackupPath = nullptr;
 if (!Core.getInstance().isNoSave()) {
 File file = new File(ZomboidFileSystem.instance.getFileNameInCurrentSave(
 "WorldDictionary.bin"));
 if (file.exists()) {
 long long0 = Instant.now().getEpochSecond();
 this->dataBackupPath =
 new File(ZomboidFileSystem.instance.getFileNameInCurrentSave(
 "WorldDictionary_" + long0 + ".bak"));
 Files.copy(file, this->dataBackupPath);
 }
 }
 }

 void deleteBackupCurrentDataSet() {
 if (Core.getInstance().isNoSave()) {
 this->dataBackupPath = nullptr;
 } else {
 if (this->dataBackupPath != nullptr) {
 this->dataBackupPath.delete();
 }

 this->dataBackupPath = nullptr;
 }
 }

 void createErrorBackups() {
 if (!Core.getInstance().isNoSave()) {
 try {
 WorldDictionary.log("Attempting to copy WorldDictionary backups...");
 long long0 = Instant.now().getEpochSecond();
 std::string string =
 ZomboidFileSystem.instance.getFileNameInCurrentSave("WD_ERROR_" +
 long0) +
 File.separator;
 WorldDictionary.log("path = " + string);
 File file0 = new File(string);
 bool boolean0 = true;
 if (!file0.exists()) {
 boolean0 = file0.mkdir();
 }

 if (!boolean0) {
 WorldDictionary.log("Could not create backup folder folder.");
 return;
 }

 if (this->dataBackupPath != nullptr) {
 File file1 = new File(string + "WorldDictionary_backup.bin");
 if (this->dataBackupPath.exists()) {
 Files.copy(this->dataBackupPath, file1);
 }
 }

 File file2 =
 new File(ZomboidFileSystem.instance.getFileNameInCurrentSave(
 "WorldDictionaryLog.lua"));
 File file3 = new File(string + "WorldDictionaryLog.lua");
 if (file2.exists()) {
 Files.copy(file2, file3);
 }

 File file4 =
 new File(ZomboidFileSystem.instance.getFileNameInCurrentSave(
 "WorldDictionaryReadable.lua"));
 File file5 = new File(string + "WorldDictionaryReadable.lua");
 if (file4.exists()) {
 Files.copy(file4, file5);
 }

 File file6 =
 new File(ZomboidFileSystem.instance.getFileNameInCurrentSave(
 "WorldDictionary.bin"));
 File file7 = new File(string + "WorldDictionary.bin");
 if (file6.exists()) {
 Files.copy(file6, file7);
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 }
 }

 void load() {
 if (!Core.getInstance().isNoSave()) {
 std::string string = ZomboidFileSystem.instance.getFileNameInCurrentSave(
 "WorldDictionary.bin");
 File file = new File(string);
 if (!file.exists()) {
 if (!WorldDictionary.isIsNewGame()) {
 throw WorldDictionaryException(
 "WorldDictionary data file is missing from world folder.");
 }
 } else {
 try {
 try(FileInputStream fileInputStream = new FileInputStream(file) {
 DebugLog.log("Loading WorldDictionary:" + string);
 ByteBuffer byteBuffer = ByteBuffer.allocate((int)file.length());
 byteBuffer.clear();
 int int0 = fileInputStream.read(byteBuffer.array());
 byteBuffer.limit(int0);
 this->loadFromByteBuffer(byteBuffer);
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 throw WorldDictionaryException("Error loading WorldDictionary.",
 exception);
 }
 }
 }
 }

 void loadFromByteBuffer(ByteBuffer byteBuffer) {
 this->NextItemID = byteBuffer.getShort();
 this->NextObjectNameID = byteBuffer.get();
 this->NextSpriteNameID = byteBuffer.getInt();
 std::vector arrayList0 = new ArrayList();
 int int0 = byteBuffer.getInt();

 for (int int1 = 0; int1 < int0; int1++) {
 arrayList0.add(GameWindow.ReadString(byteBuffer);
 }

 std::vector arrayList1 = new ArrayList();
 int int2 = byteBuffer.getInt();

 for (int int3 = 0; int3 < int2; int3++) {
 arrayList1.add(GameWindow.ReadString(byteBuffer);
 }

 int int4 = byteBuffer.getInt();

 for (int int5 = 0; int5 < int4; int5++) {
 ItemInfo itemInfo = new ItemInfo();
 itemInfo.load(byteBuffer, 195, arrayList0, arrayList1);
 this->itemIdToInfoMap.put(itemInfo.registryID, itemInfo);
 this->itemTypeToInfoMap.put(itemInfo.fullType, itemInfo);
 }

 int int6 = byteBuffer.getInt();

 for (int int7 = 0; int7 < int6; int7++) {
 uint8_t byte0 = byteBuffer.get();
 std::string string0 = GameWindow.ReadString(byteBuffer);
 this->objectIdToNameMap.put(byte0, string0);
 this->objectNameToIdMap.put(string0, byte0);
 }

 int int8 = byteBuffer.getInt();

 for (int int9 = 0; int9 < int8; int9++) {
 int int10 = byteBuffer.getInt();
 std::string string1 = GameWindow.ReadString(byteBuffer);
 this->spriteIdToNameMap.put(int10, string1);
 this->spriteNameToIdMap.put(string1, int10);
 }
 }

 void save() {
 if (!Core.getInstance().isNoSave()) {
 try {
 byte[] bytes = new byte[5242880];
 ByteBuffer byteBuffer = ByteBuffer.wrap(bytes);
 this->saveToByteBuffer(byteBuffer);
 byteBuffer.flip();
 if (GameServer.bServer) {
 bytes = new byte[byteBuffer.limit()];
 byteBuffer.get(bytes, 0, bytes.length);
 this->serverDataCache = bytes;
 }

 File file0 =
 new File(ZomboidFileSystem.instance.getFileNameInCurrentSave(
 "WorldDictionary.tmp"));
 FileOutputStream fileOutputStream = new FileOutputStream(file0);
 fileOutputStream.getChannel().truncate(0L);
 fileOutputStream.write(byteBuffer.array(), 0, byteBuffer.limit());
 fileOutputStream.flush();
 fileOutputStream.close();
 File file1 =
 new File(ZomboidFileSystem.instance.getFileNameInCurrentSave(
 "WorldDictionary.bin"));
 Files.copy(file0, file1);
 file0.delete();
 } catch (Exception exception) {
 exception.printStackTrace();
 throw WorldDictionaryException("Error saving WorldDictionary.",
 exception);
 }
 }
 }

 void saveToByteBuffer(ByteBuffer byteBuffer) {
 byteBuffer.putShort(this->NextItemID);
 byteBuffer.put(this->NextObjectNameID);
 byteBuffer.putInt(this->NextSpriteNameID);
 std::vector arrayList0 = new ArrayList();
 this->getItemMods(arrayList0);
 byteBuffer.putInt(arrayList0.size());

 for (auto &string0 : arrayList0)
 GameWindow.WriteString(byteBuffer, string0);
 }

 std::vector arrayList1 = new ArrayList();
 this->getModuleList(arrayList1);
 byteBuffer.putInt(arrayList1.size());

 for (auto &string1 : arrayList1)
 GameWindow.WriteString(byteBuffer, string1);
}

byteBuffer.putInt(this->itemIdToInfoMap.size());

for (Entry entry0 : this->itemIdToInfoMap.entrySet()) {
 ItemInfo itemInfo = (ItemInfo)entry0.getValue();
 itemInfo.save(byteBuffer, arrayList0, arrayList1);
}

byteBuffer.putInt(this->objectIdToNameMap.size());

for (Entry entry1 : this->objectIdToNameMap.entrySet()) {
 byteBuffer.put((Byte)entry1.getKey());
 GameWindow.WriteString(byteBuffer, (String)entry1.getValue());
}

byteBuffer.putInt(this->spriteIdToNameMap.size());

for (Entry entry2 : this->spriteIdToNameMap.entrySet()) {
 byteBuffer.putInt((Integer)entry2.getKey());
 GameWindow.WriteString(byteBuffer, (String)entry2.getValue());
}
}

void saveAsText(const std::string &string1) {
 if (!Core.getInstance().isNoSave()) {
 File file0 = new File(ZomboidFileSystem.instance.getCurrentSaveDir() +
 File.separator);
 if (file0.exists() && file0.isDirectory()) {
 std::string string0 =
 ZomboidFileSystem.instance.getFileNameInCurrentSave(string1);
 File file1 = new File(string0);

 try(FileWriter fileWriter = new FileWriter(file1, false) {
 fileWriter.write("--[[ ---- ITEMS ---- --]]" + System.lineSeparator());
 fileWriter.write("items = {" + System.lineSeparator());

 for (Entry entry0 : this->itemIdToInfoMap.entrySet()) {
 fileWriter.write("\t{" + System.lineSeparator());
 ((ItemInfo)entry0.getValue()).saveAsText(fileWriter, "\t\t");
 fileWriter.write("\t}," + System.lineSeparator());
 }

 fileWriter.write("}" + System.lineSeparator());
 fileWriter.write(
 StringConcatFactory
 .makeConcatWithConstants<"makeConcatWithConstants", "\u0001">(
 System.lineSeparator()));
 fileWriter.write("--[[ ---- OBJECTS ---- --]]" +
 System.lineSeparator());
 fileWriter.write("objects = {" + System.lineSeparator());

 for (Entry entry1 : this->objectIdToNameMap.entrySet()) {
 fileWriter.write("\t" + entry1.getKey() + " = \"" +
 (String)entry1.getValue() + "\"," +
 System.lineSeparator());
 }

 fileWriter.write("}" + System.lineSeparator());
 fileWriter.write(
 StringConcatFactory
 .makeConcatWithConstants<"makeConcatWithConstants", "\u0001">(
 System.lineSeparator()));
 fileWriter.write("--[[ ---- SPRITES ---- --]]" +
 System.lineSeparator());
 fileWriter.write("sprites = {" + System.lineSeparator());

 for (Entry entry2 : this->spriteIdToNameMap.entrySet()) {
 fileWriter.write("\t" + entry2.getKey() + " = \"" +
 (String)entry2.getValue() + "\"," +
 System.lineSeparator());
 }

 fileWriter.write("}" + System.lineSeparator());
 }
 catch (Exception exception) {
 exception.printStackTrace();
 throw WorldDictionaryException(
 "Error saving WorldDictionary as text.", exception);
 }
 }
 }
}
}
} // namespace world
} // namespace zombie

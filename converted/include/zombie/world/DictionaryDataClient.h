#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/scripting/ScriptManager.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace world {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class DictionaryDataClient : public DictionaryData {
public:
 bool isClient() {
 return true;
 }

 void parseItemLoadList(ItemInfo> var1) {
 }

 void parseCurrentItemSet() {
 for (Entry entry : this->itemTypeToInfoMap.entrySet()) {
 ItemInfo itemInfo = (ItemInfo)entry.getValue();
 if (!itemInfo.removed && itemInfo.scriptItem.empty()) {
 itemInfo.scriptItem = ScriptManager.instance.getSpecificItem(itemInfo.fullType);
 }

 if (itemInfo.scriptItem != nullptr) {
 itemInfo.scriptItem.setRegistry_id(itemInfo.registryID);
 itemInfo.scriptItem.setModID(itemInfo.modID);
 itemInfo.isLoaded = true;
 } else if (!itemInfo.removed) {
 throw WorldDictionaryException("Warning client has no script for item " + itemInfo.fullType);
 }
 }
 }

 void parseObjectNameLoadList(List<String> var1) {
 }

 void backupCurrentDataSet() {
 }

 void deleteBackupCurrentDataSet() {
 }

 void createErrorBackups() {
 }

 void load() {
 }

 void save() {
 }

 void saveToByteBuffer(ByteBuffer var1) {
 }
}
} // namespace world
} // namespace zombie

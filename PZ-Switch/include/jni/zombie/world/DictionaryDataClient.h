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


class DictionaryDataClient :  DictionaryData {
:
    bool isClient() {
    return true;
   }

    void parseItemLoadList(ItemInfo> var1) {
   }

    void parseCurrentItemSet() {
      for (Entry var2 : this.itemTypeToInfoMap.entrySet()) {
    ItemInfo var3 = (ItemInfo)var2.getValue();
         if (!var3.removed && var3.scriptItem == nullptr) {
            var3.scriptItem = ScriptManager.instance.getSpecificItem(var3.fullType);
         }

         if (var3.scriptItem != nullptr) {
            var3.scriptItem.setRegistry_id(var3.registryID);
            var3.scriptItem.setModID(var3.modID);
            var3.isLoaded = true;
         } else if (!var3.removed) {
            throw WorldDictionaryException("Warning client has no script for item " + var3.fullType);
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

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/world/ItemInfo.h"
#include "zombie/world/logger/Log/BaseLog.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace world {
namespace logger {


class Log {
public:
    const ItemInfo itemInfo;

   public Log$BaseItemLog(ItemInfo var1) {
      this.itemInfo = var1;
   }

   abstract void saveAsText(FileWriter var1, std::string var2) throws IOException;

    std::string getItemString() {
      return "fulltype = \""
         + this.itemInfo.getFullType()
         + "\", registeryID = "
         + this.itemInfo.getRegistryID()
         + ", existsVanilla = "
         + this.itemInfo.isExistsAsVanilla()
         + ", isModded = "
         + this.itemInfo.isModded()
         + ", modID = \""
         + this.itemInfo.getModID()
         + "\", obsolete = "
         + this.itemInfo.isObsolete()
         + ", removed = "
         + this.itemInfo.isRemoved()
         + ", isLoaded = "
         + this.itemInfo.isLoaded();
   }
}
} // namespace logger
} // namespace world
} // namespace zombie

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/world/ItemInfo.h"
#include "zombie/world/logger/Log/BaseItemLog.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace world {
namespace logger {


class Log {
public:
    const std::string oldModID;
    const std::string newModID;

   public Log$ModIDChangedItem(ItemInfo var1, std::string var2, std::string var3) {
      super(var1);
      this.oldModID = var2;
      this.newModID = var3;
   }

    void saveAsText(FileWriter var1, const std::string& var2) {
      var1.write(var2 + "{ type = \"modchange_item\", oldModID = \"" + this.oldModID + "\", " + this.getItemString() + " }" + System.lineSeparator());
   }
}
} // namespace logger
} // namespace world
} // namespace zombie

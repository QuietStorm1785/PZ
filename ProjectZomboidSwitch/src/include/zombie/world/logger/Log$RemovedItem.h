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
    const bool isScriptMissing;

   public Log$RemovedItem(ItemInfo var1, boolean var2) {
      super(var1);
      this.isScriptMissing = var2;
   }

    void saveAsText(FileWriter var1, const std::string& var2) {
      var1.write(var2 + "{ type = \"removed_item\", scriptMissing = " + this.isScriptMissing + ", " + this.getItemString() + " }" + System.lineSeparator());
   }
}
} // namespace logger
} // namespace world
} // namespace zombie

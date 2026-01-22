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
   public Log$RegisterItem(ItemInfo var1) {
      super(var1);
   }

    void saveAsText(FileWriter var1, const std::string& var2) {
      var1.write(var2 + "{ type = \"reg_item\", " + this.getItemString() + " }" + System.lineSeparator());
   }
}
} // namespace logger
} // namespace world
} // namespace zombie

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/world/logger/Log/BaseLog.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace world {
namespace logger {


class Log {
public:
    const std::string objectName;
    const int ID;

   public Log$RegisterObject(std::string var1, int var2) {
      this.objectName = var1;
      this.ID = var2;
   }

    void saveAsText(FileWriter var1, const std::string& var2) {
      var1.write(var2 + "{ type = \"reg_obj\", id = " + this.ID + ", obj = \"" + this.objectName + "\" }" + System.lineSeparator());
   }
}
} // namespace logger
} // namespace world
} // namespace zombie

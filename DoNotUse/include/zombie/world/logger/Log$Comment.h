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
    std::string txt;

   public Log$Comment(std::string var1) {
      this.ignoreSaveCheck = true;
      this.txt = var1;
   }

    void saveAsText(FileWriter var1, const std::string& var2) {
      var1.write(var2 + "-- " + this.txt + System.lineSeparator());
   }
}
} // namespace logger
} // namespace world
} // namespace zombie

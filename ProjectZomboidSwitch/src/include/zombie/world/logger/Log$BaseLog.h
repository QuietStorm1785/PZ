#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace zombie {
namespace world {
namespace logger {


class Log {
public:
    bool ignoreSaveCheck = false;

    bool isIgnoreSaveCheck() {
      return this.ignoreSaveCheck;
   }

   abstract void saveAsText(FileWriter var1, std::string var2) throws IOException;
}
} // namespace logger
} // namespace world
} // namespace zombie

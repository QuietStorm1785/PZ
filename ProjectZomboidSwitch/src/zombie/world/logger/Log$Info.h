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
   protected const List<std::string> mods;
    const std::string timeStamp;
    const std::string saveWorld;
    const int worldVersion;
    bool HasErrored = false;

   public Log$Info(std::string var1, std::string var2, int var3, List<std::string> var4) {
      this.ignoreSaveCheck = true;
      this.timeStamp = var1;
      this.saveWorld = var2;
      this.worldVersion = var3;
      this.mods = var4;
   }

    void saveAsText(FileWriter var1, const std::string& var2) {
      var1.write(var2 + "{" + System.lineSeparator());
      var1.write(var2 + "\ttype = \"info\"," + System.lineSeparator());
      var1.write(var2 + "\ttimeStamp = \"" + this.timeStamp + "\"," + System.lineSeparator());
      var1.write(var2 + "\tsaveWorld = \"" + this.saveWorld + "\"," + System.lineSeparator());
      var1.write(var2 + "\tworldVersion = " + this.worldVersion + "," + System.lineSeparator());
      var1.write(var2 + "\thasErrored = " + this.HasErrored + "," + System.lineSeparator());
      var1.write(var2 + "\titemMods = {" + System.lineSeparator());

      for (int var3 = 0; var3 < this.mods.size(); var3++) {
         var1.write(var2 + "\t\t\"" + this.mods.get(var3) + "\"," + System.lineSeparator());
      }

      var1.write(var2 + "\t}," + System.lineSeparator());
      var1.write(var2 + "}," + System.lineSeparator());
   }
}
} // namespace logger
} // namespace world
} // namespace zombie

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace network {


class ServerSettingsManager {
public:
   ServerSettingsManager$1(ServerSettingsManager var1) {
      this.this$0 = var1;
   }

    bool accept(Path var1) {
    std::string var2 = var1.getFileName();
      return !Files.isDirectory(var1) && var2.endsWith(".ini") && !var2.endsWith("_zombies.ini") && this.this$0.isValidName(var2.replace(".ini", ""));
   }
}
} // namespace network
} // namespace zombie

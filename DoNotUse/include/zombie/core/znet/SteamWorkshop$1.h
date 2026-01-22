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
namespace core {
namespace znet {


class SteamWorkshop {
public:
   SteamWorkshop$1(SteamWorkshop var1) {
      this.this$0 = var1;
   }

    bool accept(Path var1) {
      return Files.isDirectory(var1);
   }
}
} // namespace znet
} // namespace core
} // namespace zombie

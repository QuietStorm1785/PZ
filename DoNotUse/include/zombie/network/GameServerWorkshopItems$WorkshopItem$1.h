#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/network/GameServerWorkshopItems/WorkshopItem.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace network {


class GameServerWorkshopItems {
public:
   GameServerWorkshopItems$WorkshopItem$1(WorkshopItem var1) {
      this.this$0 = var1;
   }

    FileVisitResult visitFile(Path var1, BasicFileAttributes var2) {
      Files.delete(var1);
      return FileVisitResult.CONTINUE;
   }

    FileVisitResult postVisitDirectory(Path var1, std::ios_base::failure var2) {
      Files.delete(var1);
      return FileVisitResult.CONTINUE;
   }
}
} // namespace network
} // namespace zombie

#pragma once
#include <stack>
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
namespace Lua {


class LuaManager {
public:
    FileVisitResult preVisitDirectory(Path var1, BasicFileAttributes var2) {
      return FileVisitResult.CONTINUE;
   }

    FileVisitResult visitFile(Path var1, BasicFileAttributes var2) {
      Files.delete(var1);
      return FileVisitResult.CONTINUE;
   }

    FileVisitResult visitFileFailed(Path var1, std::ios_base::failure var2) {
      var2.printStackTrace();
      return FileVisitResult.CONTINUE;
   }

    FileVisitResult postVisitDirectory(Path var1, std::ios_base::failure var2) {
      Files.delete(var1);
      return FileVisitResult.CONTINUE;
   }
}
} // namespace Lua
} // namespace zombie

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


class ZomboidFileSystem {
:
   ZomboidFileSystem$1(ZomboidFileSystem var1) {
      this.this$0 = var1;
   }

    bool accept(Path var1) {
      return Files.isDirectory(var1) && Files.exists(var1.resolve("mod.info"));
   }
}
} // namespace zombie

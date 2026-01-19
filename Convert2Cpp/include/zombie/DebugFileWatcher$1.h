#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <filesystem>

namespace zombie {


class DebugFileWatcher {
public:
   DebugFileWatcher$1(DebugFileWatcher var1) {
      this.this$0 = var1;
   }

    FileVisitResult preVisitDirectory(Path var1, BasicFileAttributes var2) {
      this.this$0.registerDir(var1);
      return FileVisitResult.CONTINUE;
   }
}
} // namespace zombie

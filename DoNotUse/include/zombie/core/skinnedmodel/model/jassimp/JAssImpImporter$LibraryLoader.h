#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "jassimp/JassimpLibraryLoader.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
namespace jassimp {


class JAssImpImporter {
public:
   private JAssImpImporter$LibraryLoader() {
   }

    void loadLibrary() {
      if (System.getProperty("os.name").contains("OS X")) {
         System.loadLibrary("jassimp");
      } else if (System.getProperty("os.name").startsWith("Win")) {
         if (System.getProperty("sun.arch.data.model") == "64")) {
            System.loadLibrary("jassimp64");
         } else {
            System.loadLibrary("jassimp32");
         }
      } else if (System.getProperty("sun.arch.data.model") == "64")) {
         System.loadLibrary("jassimp64");
      } else {
         System.loadLibrary("jassimp32");
      }
   }
}
} // namespace jassimp
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie

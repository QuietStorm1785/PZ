#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {

class GameWindow {
:
    static std::string OS = System.getProperty("os.name").toLowerCase();

    static bool isWindows() {
      return OS.indexOf("win") >= 0;
   }

    static bool isMac() {
      return OS.indexOf("mac") >= 0;
   }

    static bool isUnix() {
      return OS.indexOf("nix") >= 0 || OS.indexOf("nux") >= 0 || OS.indexOf("aix") > 0;
   }

    static bool isSolaris() {
      return OS.indexOf("sunos") >= 0;
   }
}
} // namespace zombie

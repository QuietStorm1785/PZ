#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace worldMap {

class WorldMapJNI {
:
    static void init() {
   }

    static void writeToStdErr(const std::string& var0) {
      System.err.println(var0);
   }
}
} // namespace worldMap
} // namespace zombie

#pragma once
#include <string>
#include <string_view>
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

    static void writeToStdErr(std::string_view var0) {
      System.err.println(var0);
   }
}
} // namespace worldMap
} // namespace zombie

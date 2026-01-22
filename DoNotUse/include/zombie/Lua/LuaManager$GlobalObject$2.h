#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace Lua {


class LuaManager {
public:
    int compare(File var1, File var2) {
      return int64_t.valueOf(var2.lastModified()).compareTo(var1.lastModified());
   }
}
} // namespace Lua
} // namespace zombie

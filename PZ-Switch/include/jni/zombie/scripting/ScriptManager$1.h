#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace scripting {


class ScriptManager {
:
   ScriptManager$1(ScriptManager var1) {
      this.this$0 = var1;
   }

    int compare(std::string_view var1, std::string_view var2) {
    std::string var3 = new File(var1).getName();
    std::string var4 = new File(var2).getName();
      if (var3.startsWith("template_") && !var4.startsWith("template_")) {
         return -1;
      } else {
         return !var3.startsWith("template_") && var4.startsWith("template_") ? 1 : var1.compareTo(var2);
      }
   }
}
} // namespace scripting
} // namespace zombie

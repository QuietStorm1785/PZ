#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/scripting/ScriptParser/Block.h"
#include "zombie/scripting/ScriptParser/BlockElement.h"

namespace zombie {
namespace scripting {


class ScriptParser {
:
    std::string string;

    Block asBlock() {
    return nullptr;
   }

    ScriptParser$Value asValue() {
    return this;
   }

    void prettyPrint(int var1, StringBuilder var2, std::string_view var3) {
      for (int var4 = 0; var4 < var1; var4++) {
         var2.append('\t');
      }

      var2.append(this.string.trim());
      var2.append(',');
      var2.append(var3);
   }

    std::string getKey() const {
    int var1 = this.string.indexOf(61);
    return var1 = = -1 ? this.string : this.string.substring(0, var1);
   }

    std::string getValue() const {
    int var1 = this.string.indexOf(61);
    return var1 = = -1 ? "" : this.string.substring(var1 + 1);
   }
}
} // namespace scripting
} // namespace zombie

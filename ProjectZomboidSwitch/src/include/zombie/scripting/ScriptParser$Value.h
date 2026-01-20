#pragma once
#include <sstream>
#include <string>
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
public:
    std::string string;

    Block asBlock() {
    return nullptr;
   }

   public ScriptParser$Value asValue() {
    return this;
   }

    void prettyPrint(int var1, std::stringstream var2, const std::string& var3) {
      for (int var4 = 0; var4 < var1; var4++) {
         var2.append('\t');
      }

      var2.append(this.string.trim());
      var2.append(',');
      var2.append(var3);
   }

    std::string getKey() {
    int var1 = this.string.indexOf(61);
    return var1 = = -1 ? this.string : this.string.substr(0, var1);
   }

    std::string getValue() {
    int var1 = this.string.indexOf(61);
    return var1 = = -1 ? "" : this.string.substr(var1 + 1);
   }
}
} // namespace scripting
} // namespace zombie

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/math/PZMath.h"
#include "zombie/scripting/ScriptParser.h"
#include "zombie/scripting/ScriptParser/Block.h"
#include "zombie/scripting/ScriptParser/Value.h"

namespace zombie {
namespace scripting {
namespace objects {


class SoundTimelineScript : public BaseScriptObject {
public:
    std::string eventName;
   private std::unordered_map<std::string, int> positionByName = std::make_unique<std::unordered_map<>>();

    void Load(const std::string& var1, const std::string& var2) {
      this.eventName = var1;
    Block var3 = ScriptParser.parse(var2);
      var3 = (Block)var3.children.get(0);

      for (Value var5 : var3.values) {
    std::string var6 = var5.getKey().trim();
    std::string var7 = var5.getValue().trim();
         this.positionByName.put(var6, PZMath.tryParseInt(var7, 0));
      }
   }

    std::string getEventName() {
      return this.eventName;
   }

    int getPosition(const std::string& var1) {
      return this.positionByName.containsKey(var1) ? this.positionByName.get(var1) : -1;
   }

    void reset() {
      this.positionByName.clear();
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/JavaFunction.h"
#include "se/krka/kahlua/vm/LuaCallFrame.h"

namespace zombie {
namespace network {


class CoopMaster {
public:
   CoopMaster$12(CoopMaster var1) {
      this.this$0 = var1;
   }

    int call(LuaCallFrame var1, int var2) {
    void* var3 = var1.get(1);
      var1.push(this.this$0.getPlayerSaveFolder((std::string)var3));
    return 1;
   }
}
} // namespace network
} // namespace zombie

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
   CoopMaster$10(CoopMaster var1) {
      this.this$0 = var1;
   }

    int call(LuaCallFrame var1, int var2) {
      this.this$0.abortServer();
    return 0;
   }
}
} // namespace network
} // namespace zombie

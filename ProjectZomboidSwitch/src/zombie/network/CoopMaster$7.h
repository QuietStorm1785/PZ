#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/JavaFunction.h"
#include "se/krka/kahlua/vm/LuaCallFrame.h"
#include "zombie/core/znet/SteamUtils.h"

namespace zombie {
namespace network {


class CoopMaster {
public:
   CoopMaster$7(CoopMaster var1) {
      this.this$0 = var1;
   }

    int call(LuaCallFrame var1, int var2) {
      if (this.this$0.serverSteamID != nullptr) {
         var1.push(SteamUtils.convertSteamIDToString(this.this$0.serverSteamID));
    return 1;
      } else {
    return 0;
      }
   }
}
} // namespace network
} // namespace zombie

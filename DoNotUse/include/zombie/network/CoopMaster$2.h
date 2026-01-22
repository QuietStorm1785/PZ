#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/JavaFunction.h"
#include "se/krka/kahlua/vm/LuaCallFrame.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace network {


class CoopMaster {
public:
   CoopMaster$2(CoopMaster var1) {
      this.this$0 = var1;
   }

    int call(LuaCallFrame var1, int var2) {
    bool var3 = false;
      if (var2 == 4) {
    void* var4 = var1.get(1);
    void* var5 = var1.get(2);
    void* var6 = var1.get(3);
         if (!(dynamic_cast<std*>(var4) != nullptr::string) || !(dynamic_cast<std*>(var5) != nullptr::string) || !(dynamic_cast<double*>(var6) != nullptr)) {
    return 0;
         }

         try {
            this.this$0.softreset((std::string)var4, (std::string)var5, ((double)var6).intValue());
            var3 = true;
         } catch (IOException var8) {
            var8.printStackTrace();
         }
      } else {
         DebugLog.log(DebugType.Network, "[CoopMaster] wrong number of arguments: " + var2);
      }

      var1.push(var3);
    return 1;
   }
}
} // namespace network
} // namespace zombie

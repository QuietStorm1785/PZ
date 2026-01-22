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
   CoopMaster$4(CoopMaster var1) {
      this.this$0 = var1;
   }

    int call(LuaCallFrame var1, int var2) {
      if (var2 == 4) {
    void* var3 = var1.get(1);
    void* var4 = var1.get(2);
    void* var5 = var1.get(3);
         if (dynamic_cast<std*>(var3) != nullptr::string && dynamic_cast<std*>(var4) != nullptr::string && dynamic_cast<std*>(var5) != nullptr::string) {
            this.this$0.sendMessage((std::string)var3, (std::string)var4, (std::string)var5);
         }
      } else if (var2 == 3) {
    void* var6 = var1.get(1);
    void* var7 = var1.get(2);
         if (dynamic_cast<std*>(var6) != nullptr::string && dynamic_cast<std*>(var7) != nullptr::string) {
            this.this$0.sendMessage((std::string)var6, (std::string)var7);
         }
      }

    return 0;
   }
}
} // namespace network
} // namespace zombie

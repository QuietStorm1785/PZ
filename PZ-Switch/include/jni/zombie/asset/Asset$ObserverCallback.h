#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/asset/Asset/State.h"

namespace zombie {
namespace asset {


class Asset {
:
    void invoke(State var1, State var2, Asset var3) {
    int var4 = this.size();

      for (int var5 = 0; var5 < var4; var5++) {
         this.get(var5).onStateChanged(var1, var2, var3);
      }
   }
}
} // namespace asset
} // namespace zombie

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/inventory/CompressIdenticalItems/PerCallData.h"
#include <filesystem>

namespace zombie {
namespace inventory {


class CompressIdenticalItems {
public:
    PerCallData saveVars;
    ByteBuffer itemCompareBuffer = ByteBuffer.allocate(1024);

   private CompressIdenticalItems$PerThreadData() {
   }

    PerCallData allocSaveVars() {
      if (this.saveVars == nullptr) {
         return std::make_unique<PerCallData>();
      } else {
    PerCallData var1 = this.saveVars;
         var1.reset();
         this.saveVars = this.saveVars.next;
    return var1;
      }
   }
}
} // namespace inventory
} // namespace zombie

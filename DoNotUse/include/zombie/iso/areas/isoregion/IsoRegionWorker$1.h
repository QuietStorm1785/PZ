#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {


class IsoRegionWorker {
public:
   IsoRegionWorker$1(IsoRegionWorker var1) {
      this.this$0 = var1;
   }

    bool accept(File var1, const std::string& var2) {
      return var2.startsWith("datachunk_") && var2.endsWith(".bin");
   }
}
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie

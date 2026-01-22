#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/config/BooleanConfigOption.h"
#include "zombie/config/ConfigOption.h"

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {


class IsoRegionsRenderer {
public:
    int index;
    int zLevel = 0;

   public IsoRegionsRenderer$BooleanDebugOption(std::vector<ConfigOption> var1, std::string var2, boolean var3, int var4) {
      super(var2, var3);
      this.index = var1.size();
      this.zLevel = var4;
      var1.push_back(this);
   }

   public IsoRegionsRenderer$BooleanDebugOption(std::vector<ConfigOption> var1, std::string var2, boolean var3) {
      super(var2, var3);
      this.index = var1.size();
      var1.push_back(this);
   }

    int getIndex() {
      return this.index;
   }
}
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Color.h"

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {


class IsoRegionsLogger {
public:
    std::string str;
    IsoRegionLogType type;
    Color col;

    std::string getStr() {
      return this.str;
   }

    IsoRegionLogType getType() {
      return this.type;
   }

    Color getColor() {
      if (this.col != nullptr) {
         return this.col;
      } else {
         return this.type == IsoRegionLogType.Warn ? Color.red : Color.white;
      }
   }
}
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie

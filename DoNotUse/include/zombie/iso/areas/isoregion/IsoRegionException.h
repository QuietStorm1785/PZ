#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {

class IsoRegionException : public Exception {
public:
    public IsoRegionException(const std::string& var1) {
      super(var1);
   }

    public IsoRegionException(const std::string& var1, std::exception var2) {
      super(var1, var2);
   }
}
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie

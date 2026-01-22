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
namespace jobs {

class JobDebugResetAllData : public RegionJob {
public:
    protected JobDebugResetAllData() {
      super(RegionJobType.DebugResetAllData);
   }
}
} // namespace jobs
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie

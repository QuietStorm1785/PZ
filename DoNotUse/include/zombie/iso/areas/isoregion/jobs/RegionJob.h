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

class RegionJob {
public:
    const RegionJobType type;

    protected RegionJob(RegionJobType var1) {
      this.type = var1;
   }

    void reset() {
   }

    RegionJobType getJobType() {
      return this.type;
   }
}
} // namespace jobs
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie

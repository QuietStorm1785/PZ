#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {
namespace jobs {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class JobApplyChanges : public RegionJob {
public:
 bool saveToDisk;

protected
 JobApplyChanges() { super(RegionJobType.ApplyChanges); }

 void reset() { this->saveToDisk = false; }

 bool isSaveToDisk() { return this->saveToDisk; }
}
} // namespace jobs
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie

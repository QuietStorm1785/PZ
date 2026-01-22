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

enum class RegionJobType {
   SquareUpdate,
   ChunkUpdate,
   ApplyChanges,
   ServerSendFullData,
   DebugResetAllData;
}
} // namespace jobs
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie

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

// $VF: synthetic class
class RegionJobManager {
public:
   static {
      try {
         $SwitchMap$zombie$iso$areas$isoregion$jobs$RegionJobType[RegionJobType.SquareUpdate.ordinal()] = 1;
      } catch (NoSuchFieldError var5) {
      }

      try {
         $SwitchMap$zombie$iso$areas$isoregion$jobs$RegionJobType[RegionJobType.ApplyChanges.ordinal()] = 2;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$iso$areas$isoregion$jobs$RegionJobType[RegionJobType.ChunkUpdate.ordinal()] = 3;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$iso$areas$isoregion$jobs$RegionJobType[RegionJobType.ServerSendFullData.ordinal()] = 4;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$iso$areas$isoregion$jobs$RegionJobType[RegionJobType.DebugResetAllData.ordinal()] = 5;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace jobs
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie

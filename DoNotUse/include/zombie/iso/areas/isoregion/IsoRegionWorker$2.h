#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/areas/isoregion/jobs/RegionJobType.h"

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {


// $VF: synthetic class
class IsoRegionWorker {
public:
   static {
      try {
         $SwitchMap$zombie$iso$areas$isoregion$jobs$RegionJobType[RegionJobType.ServerSendFullData.ordinal()] = 1;
      } catch (NoSuchFieldError var5) {
      }

      try {
         $SwitchMap$zombie$iso$areas$isoregion$jobs$RegionJobType[RegionJobType.DebugResetAllData.ordinal()] = 2;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$iso$areas$isoregion$jobs$RegionJobType[RegionJobType.SquareUpdate.ordinal()] = 3;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$iso$areas$isoregion$jobs$RegionJobType[RegionJobType.ChunkUpdate.ordinal()] = 4;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$iso$areas$isoregion$jobs$RegionJobType[RegionJobType.ApplyChanges.ordinal()] = 5;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie

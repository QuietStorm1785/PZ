#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/areas/isoregion/jobs/RegionJobManager/1.h"
#include <algorithm>

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {
namespace jobs {


class RegionJobManager {
public:
   private static const ConcurrentLinkedQueue<JobSquareUpdate> poolSquareUpdate = std::make_unique<ConcurrentLinkedQueue<>>();
   private static const ConcurrentLinkedQueue<JobChunkUpdate> poolChunkUpdate = std::make_unique<ConcurrentLinkedQueue<>>();
   private static const ConcurrentLinkedQueue<JobApplyChanges> poolApplyChanges = std::make_unique<ConcurrentLinkedQueue<>>();
   private static const ConcurrentLinkedQueue<JobServerSendFullData> poolServerSendFullData = std::make_unique<ConcurrentLinkedQueue<>>();
   private static const ConcurrentLinkedQueue<JobDebugResetAllData> poolDebugResetAllData = std::make_unique<ConcurrentLinkedQueue<>>();

    static JobSquareUpdate allocSquareUpdate(int var0, int var1, int var2, uint8_t var3) {
    JobSquareUpdate var4 = poolSquareUpdate.poll();
      if (var4 == nullptr) {
         var4 = std::make_unique<JobSquareUpdate>();
      }

      var4.worldSquareX = var0;
      var4.worldSquareY = var1;
      var4.worldSquareZ = var2;
      var4.newSquareFlags = var3;
    return var4;
   }

    static JobChunkUpdate allocChunkUpdate() {
    JobChunkUpdate var0 = poolChunkUpdate.poll();
      if (var0 == nullptr) {
         var0 = std::make_unique<JobChunkUpdate>();
      }

    return var0;
   }

    static JobApplyChanges allocApplyChanges(bool var0) {
    JobApplyChanges var1 = poolApplyChanges.poll();
      if (var1 == nullptr) {
         var1 = std::make_unique<JobApplyChanges>();
      }

      var1.saveToDisk = var0;
    return var1;
   }

    static JobServerSendFullData allocServerSendFullData(UdpConnection var0) {
    JobServerSendFullData var1 = poolServerSendFullData.poll();
      if (var1 == nullptr) {
         var1 = std::make_unique<JobServerSendFullData>();
      }

      var1.targetConn = var0;
    return var1;
   }

    static JobDebugResetAllData allocDebugResetAllData() {
    JobDebugResetAllData var0 = poolDebugResetAllData.poll();
      if (var0 == nullptr) {
         var0 = std::make_unique<JobDebugResetAllData>();
      }

    return var0;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    static void release(RegionJob var0) {
      var0.reset();
      switch (1.$SwitchMap$zombie$iso$areas$isoregion$jobs$RegionJobType[var0.getJobType().ordinal()]) {
         case 1:
            poolSquareUpdate.push_back((JobSquareUpdate)var0);
            break;
         case 2:
            poolApplyChanges.push_back((JobApplyChanges)var0);
            break;
         case 3:
            poolChunkUpdate.push_back((JobChunkUpdate)var0);
            break;
         case 4:
            poolServerSendFullData.push_back((JobServerSendFullData)var0);
            break;
         case 5:
            poolDebugResetAllData.push_back((JobDebugResetAllData)var0);
            break;
         default:
            if (Core.bDebug) {
               throw RuntimeException("No pooling for this job type?");
            }
      }
   }
}
} // namespace jobs
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie

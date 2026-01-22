#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {

class IsoObjectSyncRequests {
public:
    int x;
    int y;
    int z;
    uint8_t objIndex;
    long reqTime;
    int reqCount;

   private IsoObjectSyncRequests$SyncData(IsoObjectSyncRequests var1) {
      this.this$0 = var1;
   }
}
} // namespace iso
} // namespace zombie

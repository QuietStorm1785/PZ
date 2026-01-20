#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {

class WorldObjectsSyncRequests {
public:
    int x;
    int y;
    long hashCodeWorldObjects;
    long reqTime;
    int reqCount;

   private WorldObjectsSyncRequests$SyncData(WorldObjectsSyncRequests var1) {
      this.this$0 = var1;
   }
}
} // namespace iso
} // namespace zombie

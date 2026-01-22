#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {

class ObjectsSyncRequests {
public:
    int x;
    int y;
    int z;
    long hash;
    long reqTime;
    int reqCount;

   private ObjectsSyncRequests$SyncIsoObject(ObjectsSyncRequests var1) {
      this.this$0 = var1;
   }

    int hashCode() {
      return (int)(this.x + this.y + this.z + this.hash);
   }
}
} // namespace iso
} // namespace zombie

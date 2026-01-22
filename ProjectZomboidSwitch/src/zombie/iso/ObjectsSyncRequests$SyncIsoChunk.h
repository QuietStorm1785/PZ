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
    long hashCodeObjects;
    long reqTime;
    int reqCount;

   private ObjectsSyncRequests$SyncIsoChunk(ObjectsSyncRequests var1) {
      this.this$0 = var1;
   }
}
} // namespace iso
} // namespace zombie

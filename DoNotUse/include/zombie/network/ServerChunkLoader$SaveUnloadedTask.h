#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/WorldReuserThread.h"
#include "zombie/network/ServerChunkLoader/SaveTask.h"

namespace zombie {
namespace network {


class ServerChunkLoader {
public:
    const IsoChunk chunk;

   public ServerChunkLoader$SaveUnloadedTask(ServerChunkLoader var1, IsoChunk var2) {
      this.this$0 = var1;
      this.chunk = var2;
   }

    void save() {
      this.chunk.Save(false);
   }

    void release() {
      WorldReuserThread.instance.addReuseChunk(this.chunk);
   }

    int wx() {
      return this.chunk.wx;
   }

    int wy() {
      return this.chunk.wy;
   }
}
} // namespace network
} // namespace zombie

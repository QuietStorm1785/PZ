#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoChunk.h"
#include "zombie/network/ClientChunkRequest/Chunk.h"
#include "zombie/network/ServerChunkLoader/SaveTask.h"

namespace zombie {
namespace network {


class ServerChunkLoader {
public:
    const ClientChunkRequest ccr;
    const Chunk chunk;

   public ServerChunkLoader$SaveLoadedTask(ServerChunkLoader var1, ClientChunkRequest var2, Chunk var3) {
      this.this$0 = var1;
      this.ccr = var2;
      this.chunk = var3;
   }

    void save() {
    long var1 = ChunkChecksum.getChecksumIfExists(this.chunk.wx, this.chunk.wy);
      this.this$0.crcSave.reset();
      this.this$0.crcSave.update(this.chunk.bb.array(), 0, this.chunk.bb.position());
      if (var1 != this.this$0.crcSave.getValue()) {
         ChunkChecksum.setChecksum(this.chunk.wx, this.chunk.wy, this.this$0.crcSave.getValue());
         IsoChunk.SafeWrite("map_", this.chunk.wx, this.chunk.wy, this.chunk.bb);
      }
   }

    void release() {
      this.ccr.releaseChunk(this.chunk);
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

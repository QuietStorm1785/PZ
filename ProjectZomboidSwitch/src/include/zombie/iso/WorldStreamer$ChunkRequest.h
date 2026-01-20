#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace iso {


class WorldStreamer {
public:
   static const ArrayDeque<WorldStreamer$ChunkRequest> pool = std::make_unique<ArrayDeque<>>();
    IsoChunk chunk;
    int requestNumber;
   boolean[] partsReceived = nullptr;
    long crc;
    ByteBuffer bb;
   transient int flagsMain;
   transient int flagsUDP;
   transient int flagsWS;
    long time;
   WorldStreamer$ChunkRequest next;

   private WorldStreamer$ChunkRequest() {
   }

    bool isReceived() {
      if (this.partsReceived == nullptr) {
    return false;
      } else {
         for (int var1 = 0; var1 < this.partsReceived.length; var1++) {
            if (!this.partsReceived[var1]) {
    return false;
            }
         }

    return true;
      }
   }

   static WorldStreamer$ChunkRequest alloc() {
      return pool.empty() ? new WorldStreamer$ChunkRequest() : pool.pop();
   }

    static void release(WorldStreamer$ChunkRequest var0) {
      var0.chunk = nullptr;
      var0.partsReceived = nullptr;
      var0.bb = nullptr;
      var0.flagsMain = 0;
      var0.flagsUDP = 0;
      var0.flagsWS = 0;
      pool.push(var0);
   }
}
} // namespace iso
} // namespace zombie

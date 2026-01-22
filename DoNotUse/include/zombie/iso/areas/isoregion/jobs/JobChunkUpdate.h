#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/areas/isoregion/ChunkUpdate.h"
#include "zombie/iso/areas/isoregion/IsoRegions.h"
#include "zombie/iso/areas/isoregion/data/DataChunk.h"
#include "zombie/iso/areas/isoregion/data/DataRoot.h"
#include "zombie/network/GameClient.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {
namespace jobs {


class JobChunkUpdate : public RegionJob {
public:
    ByteBuffer buffer = ByteBuffer.allocate(65536);
    int chunkCount = 0;
    int bufferMaxBytes = 0;
    long netTimeStamp = -1L;
    UdpConnection targetConn;

    protected JobChunkUpdate() {
      super(RegionJobType.ChunkUpdate);
   }

    void reset() {
      this.chunkCount = 0;
      this.bufferMaxBytes = 0;
      this.netTimeStamp = -1L;
      this.targetConn = nullptr;
      this.buffer.clear();
   }

    UdpConnection getTargetConn() {
      return this.targetConn;
   }

    void setTargetConn(UdpConnection var1) {
      this.targetConn = var1;
   }

    int getChunkCount() {
      return this.chunkCount;
   }

    ByteBuffer getBuffer() {
      return this.buffer;
   }

    long getNetTimeStamp() {
      return this.netTimeStamp;
   }

    void setNetTimeStamp(long var1) {
      this.netTimeStamp = var1;
   }

    bool readChunksPacket(DataRoot var1, List<int> var2) {
      this.buffer.position(0);
    int var3 = this.buffer.getInt();
    int var4 = this.buffer.getInt();

      for (int var5 = 0; var5 < var4; var5++) {
    int var6 = this.buffer.getInt();
    int var7 = this.buffer.getInt();
    int var8 = this.buffer.getInt();
    int var9 = this.buffer.getInt();
         var1.select.reset(var8 * 10, var9 * 10, 0, true, false);
         if (GameClient.bClient) {
            if (this.netTimeStamp != -1L && this.netTimeStamp < var1.select.chunk.getLastUpdateStamp()) {
    int var10 = this.buffer.position();
    int var11 = this.buffer.getInt();
               this.buffer.position(var10 + var11);
               continue;
            }

            var1.select.chunk.setLastUpdateStamp(this.netTimeStamp);
         } else {
    int var12 = IsoRegions.hash(var8, var9);
            if (!var2.contains(var12)) {
               var2.push_back(var12);
            }
         }

         var1.select.chunk.load(this.buffer, var7, true);
         var1.select.chunk.setDirtyAllActive();
      }

    return true;
   }

    bool saveChunksToDisk() {
      if (Core.getInstance().isNoSave()) {
    return true;
      } else if (this.chunkCount <= 0) {
    return false;
      } else {
         this.buffer.position(0);
    int var1 = this.buffer.getInt();
    int var2 = this.buffer.getInt();

         for (int var3 = 0; var3 < var2; var3++) {
            this.buffer.mark();
    int var4 = this.buffer.getInt();
    int var5 = this.buffer.getInt();
    int var6 = this.buffer.getInt();
    int var7 = this.buffer.getInt();
            this.buffer.reset();
    File var8 = IsoRegions.getChunkFile(var6, var7);

            try {
    FileOutputStream var9 = std::make_shared<FileOutputStream>(var8);
               var9.getChannel().truncate(0L);
               var9.write(this.buffer.array(), this.buffer.position(), var4);
               var9.flush();
               var9.close();
            } catch (Exception var10) {
               DebugLog.log(var10.getMessage());
               var10.printStackTrace();
            }

            this.buffer.position(this.buffer.position() + var4);
         }

    return true;
      }
   }

    bool saveChunksToNetBuffer(ByteBuffer var1) {
      IsoRegions.log("Server max bytes buffer = " + this.bufferMaxBytes + ", chunks = " + this.chunkCount);
      var1.put(this.buffer.array(), 0, this.bufferMaxBytes);
    return true;
   }

    bool readChunksFromNetBuffer(ByteBuffer var1, long var2) {
      this.netTimeStamp = var2;
      var1.mark();
      this.bufferMaxBytes = var1.getInt();
      this.chunkCount = var1.getInt();
      var1.reset();
      IsoRegions.log("Client max bytes buffer = " + this.bufferMaxBytes + ", chunks = " + this.chunkCount);
      this.buffer.position(0);
      this.buffer.put(var1.array(), var1.position(), this.bufferMaxBytes);
    return true;
   }

    bool canAddChunk() {
      return this.buffer.position() + 1024 < this.buffer.capacity();
   }

    int startBufferBlock() {
      if (this.chunkCount == 0) {
         this.buffer.position(0);
         this.buffer.putInt(0);
         this.buffer.putInt(0);
      }

    int var1 = this.buffer.position();
      this.buffer.putInt(0);
    return var1;
   }

    void endBufferBlock(int var1) {
      this.bufferMaxBytes = this.buffer.position();
      this.buffer.position(var1);
      this.buffer.putInt(this.bufferMaxBytes - var1);
      this.chunkCount++;
      this.buffer.position(0);
      this.buffer.putInt(this.bufferMaxBytes);
      this.buffer.putInt(this.chunkCount);
      this.buffer.position(this.bufferMaxBytes);
   }

    bool addChunkFromDataChunk(DataChunk var1) {
      if (this.buffer.position() + 1024 >= this.buffer.capacity()) {
    return false;
      } else {
    int var2 = this.startBufferBlock();
         this.buffer.putInt(195);
         this.buffer.putInt(var1.getChunkX());
         this.buffer.putInt(var1.getChunkY());
         var1.save(this.buffer);
         this.endBufferBlock(var2);
    return true;
      }
   }

    bool addChunkFromIsoChunk(IsoChunk var1) {
      if (this.buffer.position() + 1024 >= this.buffer.capacity()) {
    return false;
      } else {
    int var2 = this.startBufferBlock();
         this.buffer.putInt(195);
         this.buffer.putInt(var1.wx);
         this.buffer.putInt(var1.wy);
         ChunkUpdate.writeIsoChunkIntoBuffer(var1, this.buffer);
         this.endBufferBlock(var2);
    return true;
      }
   }

    bool addChunkFromFile(ByteBuffer var1) {
      if (this.buffer.position() + var1.limit() >= this.buffer.capacity()) {
    return false;
      } else {
         var1.getInt();
    int var2 = this.startBufferBlock();
         this.buffer.putInt(var1.getInt());
         this.buffer.putInt(var1.getInt());
         this.buffer.putInt(var1.getInt());
         var1.mark();
    int var3 = var1.getInt();
         var1.reset();
         this.buffer.put(var1.array(), var1.position(), var3);
         this.endBufferBlock(var2);
    return true;
      }
   }
}
} // namespace jobs
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie

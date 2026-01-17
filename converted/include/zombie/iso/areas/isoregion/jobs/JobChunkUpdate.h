#pragma once
#include "zombie/core/Core.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/areas/isoregion/ChunkUpdate.h"
#include "zombie/iso/areas/isoregion/IsoRegions.h"
#include "zombie/iso/areas/isoregion/data/DataChunk.h"
#include "zombie/iso/areas/isoregion/data/DataRoot.h"
#include "zombie/network/GameClient.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {
namespace jobs {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class JobChunkUpdate : public RegionJob {
public:
  ByteBuffer buffer = ByteBuffer.allocate(65536);
  int chunkCount = 0;
  int bufferMaxBytes = 0;
  long netTimeStamp = -1L;
  UdpConnection targetConn;

protected
  JobChunkUpdate() { super(RegionJobType.ChunkUpdate); }

  void reset() {
    this.chunkCount = 0;
    this.bufferMaxBytes = 0;
    this.netTimeStamp = -1L;
    this.targetConn = nullptr;
    this.buffer.clear();
  }

  UdpConnection getTargetConn() { return this.targetConn; }

  void setTargetConn(UdpConnection udpConnection) {
    this.targetConn = udpConnection;
  }

  int getChunkCount() { return this.chunkCount; }

  ByteBuffer getBuffer() { return this.buffer; }

  long getNetTimeStamp() { return this.netTimeStamp; }

  void setNetTimeStamp(long long0) { this.netTimeStamp = long0; }

  bool readChunksPacket(DataRoot dataRoot, List<Integer> list) {
    this.buffer.position(0);
    int int0 = this.buffer.getInt();
    int int1 = this.buffer.getInt();

    for (int int2 = 0; int2 < int1; int2++) {
      int int3 = this.buffer.getInt();
      int int4 = this.buffer.getInt();
      int int5 = this.buffer.getInt();
      int int6 = this.buffer.getInt();
      dataRoot.select.reset(int5 * 10, int6 * 10, 0, true, false);
      if (GameClient.bClient) {
        if (this.netTimeStamp != -1L &&
            this.netTimeStamp < dataRoot.select.chunk.getLastUpdateStamp()) {
          int int7 = this.buffer.position();
          int int8 = this.buffer.getInt();
          this.buffer.position(int7 + int8);
          continue;
        }

        dataRoot.select.chunk.setLastUpdateStamp(this.netTimeStamp);
      } else {
        int int9 = IsoRegions.hash(int5, int6);
        if (!list.contains(int9)) {
          list.add(int9);
        }
      }

      dataRoot.select.chunk.load(this.buffer, int4, true);
      dataRoot.select.chunk.setDirtyAllActive();
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
      int int0 = this.buffer.getInt();
      int int1 = this.buffer.getInt();

      for (int int2 = 0; int2 < int1; int2++) {
        this.buffer.mark();
        int int3 = this.buffer.getInt();
        int int4 = this.buffer.getInt();
        int int5 = this.buffer.getInt();
        int int6 = this.buffer.getInt();
        this.buffer.reset();
        File file = IsoRegions.getChunkFile(int5, int6);

        try {
          FileOutputStream fileOutputStream = new FileOutputStream(file);
          fileOutputStream.getChannel().truncate(0L);
          fileOutputStream.write(this.buffer.array(), this.buffer.position(),
                                 int3);
          fileOutputStream.flush();
          fileOutputStream.close();
        } catch (Exception exception) {
          DebugLog.log(exception.getMessage());
          exception.printStackTrace();
        }

        this.buffer.position(this.buffer.position() + int3);
      }

      return true;
    }
  }

  bool saveChunksToNetBuffer(ByteBuffer byteBuffer) {
    IsoRegions.log("Server max bytes buffer = " + this.bufferMaxBytes +
                   ", chunks = " + this.chunkCount);
    byteBuffer.put(this.buffer.array(), 0, this.bufferMaxBytes);
    return true;
  }

  bool readChunksFromNetBuffer(ByteBuffer byteBuffer, long long0) {
    this.netTimeStamp = long0;
    byteBuffer.mark();
    this.bufferMaxBytes = byteBuffer.getInt();
    this.chunkCount = byteBuffer.getInt();
    byteBuffer.reset();
    IsoRegions.log("Client max bytes buffer = " + this.bufferMaxBytes +
                   ", chunks = " + this.chunkCount);
    this.buffer.position(0);
    this.buffer.put(byteBuffer.array(), byteBuffer.position(),
                    this.bufferMaxBytes);
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

    int int0 = this.buffer.position();
    this.buffer.putInt(0);
    return int0;
  }

  void endBufferBlock(int int0) {
    this.bufferMaxBytes = this.buffer.position();
    this.buffer.position(int0);
    this.buffer.putInt(this.bufferMaxBytes - int0);
    this.chunkCount++;
    this.buffer.position(0);
    this.buffer.putInt(this.bufferMaxBytes);
    this.buffer.putInt(this.chunkCount);
    this.buffer.position(this.bufferMaxBytes);
  }

  bool addChunkFromDataChunk(DataChunk dataChunk) {
    if (this.buffer.position() + 1024 >= this.buffer.capacity()) {
      return false;
    } else {
      int int0 = this.startBufferBlock();
      this.buffer.putInt(195);
      this.buffer.putInt(dataChunk.getChunkX());
      this.buffer.putInt(dataChunk.getChunkY());
      dataChunk.save(this.buffer);
      this.endBufferBlock(int0);
      return true;
    }
  }

  bool addChunkFromIsoChunk(IsoChunk chunk) {
    if (this.buffer.position() + 1024 >= this.buffer.capacity()) {
      return false;
    } else {
      int int0 = this.startBufferBlock();
      this.buffer.putInt(195);
      this.buffer.putInt(chunk.wx);
      this.buffer.putInt(chunk.wy);
      ChunkUpdate.writeIsoChunkIntoBuffer(chunk, this.buffer);
      this.endBufferBlock(int0);
      return true;
    }
  }

  bool addChunkFromFile(ByteBuffer byteBuffer) {
    if (this.buffer.position() + byteBuffer.limit() >= this.buffer.capacity()) {
      return false;
    } else {
      byteBuffer.getInt();
      int int0 = this.startBufferBlock();
      this.buffer.putInt(byteBuffer.getInt());
      this.buffer.putInt(byteBuffer.getInt());
      this.buffer.putInt(byteBuffer.getInt());
      byteBuffer.mark();
      int int1 = byteBuffer.getInt();
      byteBuffer.reset();
      this.buffer.put(byteBuffer.array(), byteBuffer.position(), int1);
      this.endBufferBlock(int0);
      return true;
    }
  }
}
} // namespace jobs
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie

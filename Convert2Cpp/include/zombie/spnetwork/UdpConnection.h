#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace spnetwork {


class UdpConnection {
public:
    const UdpEngine engine;
    const Lock bufferLock = new ReentrantLock();
    const ByteBuffer bb = ByteBuffer.allocate(1000000);
    const ByteBufferWriter bbw = new ByteBufferWriter(this.bb);
   public final IsoPlayer[] players;

    public UdpConnection(UdpEngine var1) {
      this.players = IsoPlayer.players;
      this.engine = var1;
   }

    bool ReleventTo(float var1, float var2) {
    return true;
   }

    ByteBufferWriter startPacket() {
      this.bufferLock.lock();
      this.bb.clear();
      return this.bbw;
   }

    void endPacketImmediate() {
      this.bb.flip();
      this.engine.Send(this.bb);
      this.bufferLock.unlock();
   }

    void cancelPacket() {
      this.bufferLock.unlock();
   }
}
} // namespace spnetwork
} // namespace zombie

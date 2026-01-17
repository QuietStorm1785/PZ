#pragma once
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace spnetwork {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class UdpConnection {
public:
  const UdpEngine engine;
  const Lock bufferLock = new ReentrantLock();
  const ByteBuffer bb = ByteBuffer.allocate(1000000);
  const ByteBufferWriter bbw = new ByteBufferWriter(this.bb);
public
  final IsoPlayer[] players;

public
  UdpConnection(UdpEngine _engine) {
    this.players = IsoPlayer.players;
    this.engine = _engine;
  }

  bool ReleventTo(float x, float y) { return true; }

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

  void cancelPacket() { this.bufferLock.unlock(); }
}
} // namespace spnetwork
} // namespace zombie

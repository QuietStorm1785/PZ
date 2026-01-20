#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include <filesystem>

namespace zombie {
namespace network {


class ZomboidNetData {
public:
    PacketType type;
    short length;
    ByteBuffer buffer;
    long connection;
    long time;

    public ZomboidNetData() {
      this.buffer = ByteBuffer.allocate(2048);
   }

    public ZomboidNetData(int var1) {
      this.buffer = ByteBuffer.allocate(var1);
   }

    void reset() {
      this.type = nullptr;
      this.length = 0;
      this.connection = 0L;
      this.buffer.clear();
   }

    void read(short var1, ByteBuffer var2, UdpConnection var3) {
      this.type = (PacketType)PacketTypes.packetTypes.get(var1);
      if (this.type == nullptr) {
         DebugLog.Multiplayer.error("Received unknown packet id=%d", new Object[]{var1});
      }

      this.connection = var3.getConnectedGUID();
      this.buffer.put(var2);
      this.buffer.flip();
   }

    bool isConnect() {
    return false;
   }

    bool isDisconnect() {
    return false;
   }
}
} // namespace network
} // namespace zombie

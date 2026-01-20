#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/network/IZomboidPacket.h"
#include <filesystem>

namespace zombie {
namespace spnetwork {


class ZomboidNetData {
public:
    short type;
    short length;
    ByteBuffer buffer;
    UdpConnection connection;

    public ZomboidNetData() {
      this.buffer = ByteBuffer.allocate(2048);
   }

    public ZomboidNetData(int var1) {
      this.buffer = ByteBuffer.allocate(var1);
   }

    void reset() {
      this.type = 0;
      this.length = 0;
      this.buffer.clear();
      this.connection = nullptr;
   }

    void read(short var1, ByteBuffer var2, UdpConnection var3) {
      this.type = var1;
      this.connection = var3;
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
} // namespace spnetwork
} // namespace zombie

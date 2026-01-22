#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/packets/INetworkPacket.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
namespace hit {


class Instance {
public:
    short ID;

    void set(short var1) {
      this.ID = var1;
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.ID = var1.getShort();
   }

    void write(ByteBufferWriter var1) {
      var1.putShort(this.ID);
   }

    bool isConsistent() {
      return this.ID != -1;
   }

    std::string getDescription() {
      return "ID=" + this.ID;
   }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

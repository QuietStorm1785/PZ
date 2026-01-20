#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {


class INetworkPacket {
public:
    virtual ~INetworkPacket() = default;
    void parse(ByteBuffer var1, UdpConnection var2);

    void write(ByteBufferWriter var1);

   default int getPacketSizeBytes() {
    return 0;
   }

   default boolean isConsistent() {
    return true;
   }

   default std::string getDescription() {
      return this.getClass().getSimpleName();
   }

   default void log(UdpConnection var1, std::string var2) {
   }
}
} // namespace packets
} // namespace network
} // namespace zombie

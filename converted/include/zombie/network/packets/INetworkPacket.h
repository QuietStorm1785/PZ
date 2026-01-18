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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class INetworkPacket {
public:
 virtual ~INetworkPacket() = default;
 void parse(ByteBuffer b, UdpConnection connection);

 void write(ByteBufferWriter b);

 default int getPacketSizeBytes() {
 return 0;
 }

 default boolean isConsistent() {
 return true;
 }

 default String getDescription() {
 return this->getClass().getSimpleName();
 }

 default void log(UdpConnection connection, String tag) {
 }
}
} // namespace packets
} // namespace network
} // namespace zombie

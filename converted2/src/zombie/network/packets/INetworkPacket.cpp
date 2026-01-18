#include "zombie/network/packets/INetworkPacket.h"

namespace zombie {
namespace network {
namespace packets {

void INetworkPacket::parse(ByteBuffer b, UdpConnection connection) {
  // TODO: Implement parse
}

void INetworkPacket::write(ByteBufferWriter b) {
  // TODO: Implement write
}

} // namespace packets
} // namespace network
} // namespace zombie

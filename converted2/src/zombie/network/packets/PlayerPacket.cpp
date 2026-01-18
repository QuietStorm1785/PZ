#include "zombie/network/packets/PlayerPacket.h"

namespace zombie {
namespace network {
namespace packets {

void PlayerPacket::parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
  // TODO: Implement parse
}

void PlayerPacket::write(ByteBufferWriter byteBufferWriter) {
  // TODO: Implement write
}

int PlayerPacket::getPacketSizeBytes() {
  // TODO: Implement getPacketSizeBytes
  return 0;
}

bool PlayerPacket::set(IsoPlayer player) {
  // TODO: Implement set
  return false;
}

void PlayerPacket::copy(PlayerPacket playerPacket0) {
  // TODO: Implement copy
}

} // namespace packets
} // namespace network
} // namespace zombie

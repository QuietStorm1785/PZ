#include "zombie/network/packets/SyncInjuriesPacket.h"

namespace zombie {
namespace network {
namespace packets {

bool SyncInjuriesPacket::set(IsoPlayer playerx) {
  // TODO: Implement set
  return false;
}

bool SyncInjuriesPacket::process() {
  // TODO: Implement process
  return false;
}

void SyncInjuriesPacket::parse(ByteBuffer byteBuffer,
                               UdpConnection udpConnection) {
  // TODO: Implement parse
}

void SyncInjuriesPacket::write(ByteBufferWriter byteBufferWriter) {
  // TODO: Implement write
}

int SyncInjuriesPacket::getPacketSizeBytes() {
  // TODO: Implement getPacketSizeBytes
  return 0;
}

std::string SyncInjuriesPacket::getDescription() {
  // TODO: Implement getDescription
  return "";
}

} // namespace packets
} // namespace network
} // namespace zombie

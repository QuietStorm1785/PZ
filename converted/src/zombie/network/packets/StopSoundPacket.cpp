#include "zombie/network/packets/StopSoundPacket.h"

namespace zombie {
namespace network {
namespace packets {

void StopSoundPacket::set(IsoMovingObject movingObject,
                          const std::string &string, bool boolean0) {
  // TODO: Implement set
}

void StopSoundPacket::process() {
  // TODO: Implement process
}

void StopSoundPacket::parse(ByteBuffer byteBuffer,
                            UdpConnection udpConnection) {
  // TODO: Implement parse
}

void StopSoundPacket::write(ByteBufferWriter byteBufferWriter) {
  // TODO: Implement write
}

int StopSoundPacket::getPacketSizeBytes() {
  // TODO: Implement getPacketSizeBytes
  return 0;
}

std::string StopSoundPacket::getDescription() {
  // TODO: Implement getDescription
  return "";
}

} // namespace packets
} // namespace network
} // namespace zombie

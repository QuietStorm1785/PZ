#include "zombie/network/packets/PlayWorldSoundPacket.h"

namespace zombie {
namespace network {
namespace packets {

void PlayWorldSoundPacket::set(const std::string &string, int int0, int int1,
                               uint8_t byte0) {
  // TODO: Implement set
}

void PlayWorldSoundPacket::process() {
  // TODO: Implement process
}

std::string PlayWorldSoundPacket::getName() {
  // TODO: Implement getName
  return "";
}

int PlayWorldSoundPacket::getX() {
  // TODO: Implement getX
  return 0;
}

int PlayWorldSoundPacket::getY() {
  // TODO: Implement getY
  return 0;
}

void PlayWorldSoundPacket::parse(ByteBuffer byteBuffer, UdpConnection var2) {
  // TODO: Implement parse
}

void PlayWorldSoundPacket::write(ByteBufferWriter byteBufferWriter) {
  // TODO: Implement write
}

bool PlayWorldSoundPacket::isConsistent() {
  // TODO: Implement isConsistent
  return false;
}

int PlayWorldSoundPacket::getPacketSizeBytes() {
  // TODO: Implement getPacketSizeBytes
  return 0;
}

std::string PlayWorldSoundPacket::getDescription() {
  // TODO: Implement getDescription
  return "";
}

} // namespace packets
} // namespace network
} // namespace zombie

#include "zombie/network/packets/PlayerID.h"

namespace zombie {
namespace network {
namespace packets {

void PlayerID::set(IsoPlayer playerx) {
  // TODO: Implement set
}

void PlayerID::parsePlayer(UdpConnection udpConnection) {
  // TODO: Implement parsePlayer
}

void PlayerID::parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
  // TODO: Implement parse
}

void PlayerID::write(ByteBufferWriter byteBufferWriter) {
  // TODO: Implement write
}

bool PlayerID::isConsistent() {
  // TODO: Implement isConsistent
  return false;
}

std::string PlayerID::getDescription() {
  // TODO: Implement getDescription
  return "";
}

IsoPlayer PlayerID::getCharacter() {
  // TODO: Implement getCharacter
  return nullptr;
}

} // namespace packets
} // namespace network
} // namespace zombie

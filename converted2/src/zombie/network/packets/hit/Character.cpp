#include "zombie/network/packets/hit/Character.h"

namespace zombie {
namespace network {
namespace packets {
namespace hit {

void Character::set(IsoGameCharacter character1) {
  // TODO: Implement set
}

void Character::parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
  // TODO: Implement parse
}

void Character::write(ByteBufferWriter byteBufferWriter) {
  // TODO: Implement write
}

bool Character::isConsistent() {
  // TODO: Implement isConsistent
  return false;
}

std::string Character::getDescription() {
  // TODO: Implement getDescription
  return "";
}

std::string Character::getFlagsDescription() {
  // TODO: Implement getFlagsDescription
  return "";
}

void Character::process() {
  // TODO: Implement process
}

void Character::react() {
  // TODO: Implement react
}

float Character::getX() {
  // TODO: Implement getX
  return 0;
}

float Character::getY() {
  // TODO: Implement getY
  return 0;
}

} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

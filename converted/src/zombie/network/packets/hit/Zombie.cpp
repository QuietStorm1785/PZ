#include "zombie/network/packets/hit/Zombie.h"

namespace zombie {
namespace network {
namespace packets {
namespace hit {

void Zombie::set(IsoZombie zombie1, bool boolean0) {
  // TODO: Implement set
}

void Zombie::parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
  // TODO: Implement parse
}

void Zombie::write(ByteBufferWriter byteBufferWriter) {
  // TODO: Implement write
}

bool Zombie::isConsistent() {
  // TODO: Implement isConsistent
  return false;
}

std::string Zombie::getDescription() {
  // TODO: Implement getDescription
  return "";
}

void Zombie::process() {
  // TODO: Implement process
}

void Zombie::react(HandWeapon weapon) {
  // TODO: Implement react
}

IsoGameCharacter Zombie::getCharacter() {
  // TODO: Implement getCharacter
  return nullptr;
}

} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

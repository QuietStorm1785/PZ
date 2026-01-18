#include "zombie/network/packets/hit/AttackVars.h"

namespace zombie {
namespace network {
namespace packets {
namespace hit {

void AttackVars::setWeapon(HandWeapon weapon) {
  // TODO: Implement setWeapon
}

HandWeapon AttackVars::getWeapon(IsoLivingCharacter livingCharacter) {
  // TODO: Implement getWeapon
  return nullptr;
}

void AttackVars::parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
  // TODO: Implement parse
}

void AttackVars::write(ByteBufferWriter byteBufferWriter) {
  // TODO: Implement write
}

int AttackVars::getPacketSizeBytes() {
  // TODO: Implement getPacketSizeBytes
  return 0;
}

std::string AttackVars::getDescription() {
  // TODO: Implement getDescription
  return "";
}

void AttackVars::copy(AttackVars attackVars0) {
  // TODO: Implement copy
}

void AttackVars::clear() {
  // TODO: Implement clear
}

} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

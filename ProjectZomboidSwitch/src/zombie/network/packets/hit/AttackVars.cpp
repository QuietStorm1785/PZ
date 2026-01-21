#include <string>
#include "zombie/network/packets/hit/AttackVars.h"

namespace zombie {
namespace network {
namespace packets {
namespace hit {

void AttackVars::setWeapon(HandWeapon var1) {
    // TODO: Implement setWeapon
}

HandWeapon AttackVars::getWeapon(IsoLivingCharacter var1) {
    // TODO: Implement getWeapon
    return nullptr;
}

void AttackVars::parse(ByteBuffer var1, UdpConnection var2) {
    // TODO: Implement parse
}

void AttackVars::write(ByteBufferWriter var1) {
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

void AttackVars::copy(AttackVars var1) {
    // TODO: Implement copy
}

void AttackVars::clear() {
    // TODO: Implement clear
}

} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

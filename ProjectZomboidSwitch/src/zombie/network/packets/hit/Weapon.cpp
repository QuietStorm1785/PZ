#include <string>
#include "zombie/network/packets/hit/Weapon.h"

namespace zombie {
namespace network {
namespace packets {
namespace hit {

void Weapon::set(HandWeapon var1) {
    // TODO: Implement set
}

void Weapon::parse(ByteBuffer var1, IsoLivingCharacter var2) {
    // TODO: Implement parse
}

void Weapon::parse(ByteBuffer var1, UdpConnection var2) {
    // TODO: Implement parse
}

void Weapon::write(ByteBufferWriter var1) {
    // TODO: Implement write
}

bool Weapon::isConsistent() {
    // TODO: Implement isConsistent
    return false;
}

std::string Weapon::getDescription() {
    // TODO: Implement getDescription
    return "";
}

HandWeapon Weapon::getWeapon() {
    // TODO: Implement getWeapon
    return nullptr;
}

} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

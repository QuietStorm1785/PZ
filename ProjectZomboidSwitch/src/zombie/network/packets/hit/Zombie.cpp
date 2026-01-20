#include <string>
#include "zombie\network\packets\hit/Zombie.h"

namespace zombie {
namespace network {
namespace packets {
namespace hit {

void Zombie::set(IsoZombie var1, bool var2) {
    // TODO: Implement set
}

void Zombie::parse(ByteBuffer var1, UdpConnection var2) {
    // TODO: Implement parse
}

void Zombie::write(ByteBufferWriter var1) {
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

void Zombie::react(HandWeapon var1) {
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

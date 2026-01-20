#include <string>
#include "zombie\network\packets/PlayerID.h"

namespace zombie {
namespace network {
namespace packets {

void PlayerID::set(IsoPlayer var1) {
    // TODO: Implement set
}

void PlayerID::parsePlayer(UdpConnection var1) {
    // TODO: Implement parsePlayer
}

void PlayerID::parse(ByteBuffer var1, UdpConnection var2) {
    // TODO: Implement parse
}

void PlayerID::write(ByteBufferWriter var1) {
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

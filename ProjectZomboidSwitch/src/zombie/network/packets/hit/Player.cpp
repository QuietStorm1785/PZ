#include <string>
#include "zombie\network\packets\hit/Player.h"

namespace zombie {
namespace network {
namespace packets {
namespace hit {

void Player::set(IsoPlayer var1, bool var2) {
    // TODO: Implement set
}

void Player::parsePlayer(UdpConnection var1) {
    // TODO: Implement parsePlayer
}

void Player::parse(ByteBuffer var1, UdpConnection var2) {
    // TODO: Implement parse
}

void Player::write(ByteBufferWriter var1) {
    // TODO: Implement write
}

bool Player::isConsistent() {
    // TODO: Implement isConsistent
    return false;
}

std::string Player::getDescription() {
    // TODO: Implement getDescription
    return "";
}

void Player::process() {
    // TODO: Implement process
}

void Player::attack(HandWeapon var1, bool var2) {
    // TODO: Implement attack
}

IsoGameCharacter Player::getCharacter() {
    // TODO: Implement getCharacter
    return nullptr;
}

IsoPlayer Player::getPlayer() {
    // TODO: Implement getPlayer
    return nullptr;
}

bool Player::isRelevant(UdpConnection var1) {
    // TODO: Implement isRelevant
    return false;
}

} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

#include "zombie/network/packets/hit/Player.h"

namespace zombie {
namespace network {
namespace packets {
namespace hit {

void Player::set(IsoPlayer player1, bool boolean0) {
 // TODO: Implement set
}

void Player::parsePlayer(UdpConnection udpConnection) {
 // TODO: Implement parsePlayer
}

void Player::parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
 // TODO: Implement parse
}

void Player::write(ByteBufferWriter byteBufferWriter) {
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

void Player::attack(HandWeapon weapon, bool boolean0) {
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

bool Player::isRelevant(UdpConnection udpConnection) {
 // TODO: Implement isRelevant
 return false;
}

} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

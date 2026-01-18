#include "zombie/network/packets/hit/PlayerHitZombiePacket.h"

namespace zombie {
namespace network {
namespace packets {
namespace hit {

public
PlayerHitZombiePacket::PlayerHitZombiePacket() {
  // TODO: Implement PlayerHitZombiePacket
  return nullptr;
}

void PlayerHitZombiePacket::parse(ByteBuffer byteBuffer,
                                  UdpConnection udpConnection) {
  // TODO: Implement parse
}

void PlayerHitZombiePacket::write(ByteBufferWriter byteBufferWriter) {
  // TODO: Implement write
}

bool PlayerHitZombiePacket::isConsistent() {
  // TODO: Implement isConsistent
  return false;
}

std::string PlayerHitZombiePacket::getDescription() {
  // TODO: Implement getDescription
  return "";
}

void PlayerHitZombiePacket::preProcess() {
  // TODO: Implement preProcess
}

void PlayerHitZombiePacket::process() {
  // TODO: Implement process
}

void PlayerHitZombiePacket::postProcess() {
  // TODO: Implement postProcess
}

void PlayerHitZombiePacket::react() {
  // TODO: Implement react
}

bool PlayerHitZombiePacket::validate(UdpConnection udpConnection) {
  // TODO: Implement validate
  return false;
}

} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

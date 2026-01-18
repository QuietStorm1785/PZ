#include "zombie/network/packets/DeadZombiePacket.h"

namespace zombie {
namespace network {
namespace packets {

void DeadZombiePacket::set(IsoGameCharacter character) {
 // TODO: Implement set
}

void DeadZombiePacket::process() {
 // TODO: Implement process
}

void DeadZombiePacket::parse(ByteBuffer byteBuffer,
 UdpConnection udpConnection) {
 // TODO: Implement parse
}

void DeadZombiePacket::write(ByteBufferWriter byteBufferWriter) {
 // TODO: Implement write
}

std::string DeadZombiePacket::getDescription() {
 // TODO: Implement getDescription
 return "";
}

IsoZombie DeadZombiePacket::getZombie() {
 // TODO: Implement getZombie
 return nullptr;
}

} // namespace packets
} // namespace network
} // namespace zombie

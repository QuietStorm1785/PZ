#include "zombie/network/packets/DeadPlayerPacket.h"

namespace zombie {
namespace network {
namespace packets {

void DeadPlayerPacket::set(IsoGameCharacter character) {
 // TODO: Implement set
}

void DeadPlayerPacket::process() {
 // TODO: Implement process
}

void DeadPlayerPacket::parse(ByteBuffer byteBuffer,
 UdpConnection udpConnection) {
 // TODO: Implement parse
}

void DeadPlayerPacket::write(ByteBufferWriter byteBufferWriter) {
 // TODO: Implement write
}

std::string DeadPlayerPacket::getDescription() {
 // TODO: Implement getDescription
 return "";
}

IsoPlayer DeadPlayerPacket::getPlayer() {
 // TODO: Implement getPlayer
 return nullptr;
}

} // namespace packets
} // namespace network
} // namespace zombie

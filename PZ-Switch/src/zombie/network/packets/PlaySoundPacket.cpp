#include "zombie/network/packets/PlaySoundPacket.h"

namespace zombie {
namespace network {
namespace packets {

void PlaySoundPacket::set(const std::string &string, bool boolean0,
 IsoMovingObject movingObject) {
 // TODO: Implement set
}

void PlaySoundPacket::process() {
 // TODO: Implement process
}

std::string PlaySoundPacket::getName() {
 // TODO: Implement getName
 return "";
}

IsoMovingObject PlaySoundPacket::getMovingObject() {
 // TODO: Implement getMovingObject
 return nullptr;
}

void PlaySoundPacket::parse(ByteBuffer byteBuffer,
 UdpConnection udpConnection) {
 // TODO: Implement parse
}

void PlaySoundPacket::write(ByteBufferWriter byteBufferWriter) {
 // TODO: Implement write
}

bool PlaySoundPacket::isConsistent() {
 // TODO: Implement isConsistent
 return false;
}

int PlaySoundPacket::getPacketSizeBytes() {
 // TODO: Implement getPacketSizeBytes
 return 0;
}

std::string PlaySoundPacket::getDescription() {
 // TODO: Implement getDescription
 return "";
}

} // namespace packets
} // namespace network
} // namespace zombie

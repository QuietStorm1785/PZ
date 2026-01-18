#include "zombie/network/packets/Disinfect.h"

namespace zombie {
namespace network {
namespace packets {

void Disinfect::set(IsoGameCharacter character0, IsoGameCharacter character1,
 BodyPart bodyPartx, InventoryItem item) {
 // TODO: Implement set
}

void Disinfect::parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
 // TODO: Implement parse
}

void Disinfect::write(ByteBufferWriter byteBufferWriter) {
 // TODO: Implement write
}

void Disinfect::process() {
 // TODO: Implement process
}

bool Disinfect::isConsistent() {
 // TODO: Implement isConsistent
 return false;
}

bool Disinfect::validate(UdpConnection udpConnection) {
 // TODO: Implement validate
 return false;
}

std::string Disinfect::getDescription() {
 // TODO: Implement getDescription
 return "";
}

} // namespace packets
} // namespace network
} // namespace zombie

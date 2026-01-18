#include "zombie/network/packets/RemoveGlass.h"

namespace zombie {
namespace network {
namespace packets {

void RemoveGlass::set(IsoGameCharacter character0, IsoGameCharacter character1,
                      BodyPart bodyPartx, bool boolean0) {
  // TODO: Implement set
}

void RemoveGlass::parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
  // TODO: Implement parse
}

void RemoveGlass::write(ByteBufferWriter byteBufferWriter) {
  // TODO: Implement write
}

void RemoveGlass::process() {
  // TODO: Implement process
}

bool RemoveGlass::isConsistent() {
  // TODO: Implement isConsistent
  return false;
}

bool RemoveGlass::validate(UdpConnection udpConnection) {
  // TODO: Implement validate
  return false;
}

std::string RemoveGlass::getDescription() {
  // TODO: Implement getDescription
  return "";
}

} // namespace packets
} // namespace network
} // namespace zombie

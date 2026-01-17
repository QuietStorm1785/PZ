#include "zombie/network/packets/RemoveBullet.h"

namespace zombie {
namespace network {
namespace packets {

void RemoveBullet::set(IsoGameCharacter character0, IsoGameCharacter character1,
                       BodyPart bodyPartx) {
  // TODO: Implement set
}

void RemoveBullet::parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
  // TODO: Implement parse
}

void RemoveBullet::write(ByteBufferWriter byteBufferWriter) {
  // TODO: Implement write
}

void RemoveBullet::process() {
  // TODO: Implement process
}

bool RemoveBullet::isConsistent() {
  // TODO: Implement isConsistent
  return false;
}

bool RemoveBullet::validate(UdpConnection udpConnection) {
  // TODO: Implement validate
  return false;
}

std::string RemoveBullet::getDescription() {
  // TODO: Implement getDescription
  return "";
}

} // namespace packets
} // namespace network
} // namespace zombie

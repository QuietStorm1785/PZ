#include "zombie/network/packets/hit/Hit.h"

namespace zombie {
namespace network {
namespace packets {
namespace hit {

void Hit::set(bool boolean0, float float0, float float1, float float2,
              float float3) {
  // TODO: Implement set
}

void Hit::parse(ByteBuffer byteBuffer, UdpConnection var2) {
  // TODO: Implement parse
}

void Hit::write(ByteBufferWriter byteBufferWriter) {
  // TODO: Implement write
}

std::string Hit::getDescription() {
  // TODO: Implement getDescription
  return "";
}

void Hit::process(IsoGameCharacter character1, IsoGameCharacter character0) {
  // TODO: Implement process
}

float Hit::getDamage() {
  // TODO: Implement getDamage
  return 0;
}

} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

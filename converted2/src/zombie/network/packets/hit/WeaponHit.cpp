#include "zombie/network/packets/hit/WeaponHit.h"

namespace zombie {
namespace network {
namespace packets {
namespace hit {

void WeaponHit::set(bool boolean0, float float0, float float4, float float1,
                    float float2, float float3, bool boolean1) {
  // TODO: Implement set
}

void WeaponHit::parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
  // TODO: Implement parse
}

void WeaponHit::write(ByteBufferWriter byteBufferWriter) {
  // TODO: Implement write
}

std::string WeaponHit::getDescription() {
  // TODO: Implement getDescription
  return "";
}

void WeaponHit::process(IsoGameCharacter character1,
                        IsoGameCharacter character0, HandWeapon weapon) {
  // TODO: Implement process
}

} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

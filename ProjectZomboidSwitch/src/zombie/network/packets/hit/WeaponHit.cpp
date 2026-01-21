#include <string>
#include "zombie/network/packets/hit/WeaponHit.h"

namespace zombie {
namespace network {
namespace packets {
namespace hit {

void WeaponHit::set(bool var1, float var2, float var3, float var4, float var5, float var6, bool var7) {
    // TODO: Implement set
}

void WeaponHit::parse(ByteBuffer var1, UdpConnection var2) {
    // TODO: Implement parse
}

void WeaponHit::write(ByteBufferWriter var1) {
    // TODO: Implement write
}

std::string WeaponHit::getDescription() {
    // TODO: Implement getDescription
    return "";
}

void WeaponHit::process(IsoGameCharacter var1, IsoGameCharacter var2, HandWeapon var3) {
    // TODO: Implement process
}

} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

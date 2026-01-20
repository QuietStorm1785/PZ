#include <string>
#include "zombie\network\packets\hit/Hit.h"

namespace zombie {
namespace network {
namespace packets {
namespace hit {

void Hit::set(bool var1, float var2, float var3, float var4, float var5) {
    // TODO: Implement set
}

void Hit::parse(ByteBuffer var1, UdpConnection var2) {
    // TODO: Implement parse
}

void Hit::write(ByteBufferWriter var1) {
    // TODO: Implement write
}

std::string Hit::getDescription() {
    // TODO: Implement getDescription
    return "";
}

void Hit::process(IsoGameCharacter var1, IsoGameCharacter var2) {
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

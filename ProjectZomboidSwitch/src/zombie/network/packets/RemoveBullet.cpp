#include <string>
#include "zombie\network\packets/RemoveBullet.h"

namespace zombie {
namespace network {
namespace packets {

void RemoveBullet::set(IsoGameCharacter var1, IsoGameCharacter var2, BodyPart var3) {
    // TODO: Implement set
}

void RemoveBullet::parse(ByteBuffer var1, UdpConnection var2) {
    // TODO: Implement parse
}

void RemoveBullet::write(ByteBufferWriter var1) {
    // TODO: Implement write
}

void RemoveBullet::process() {
    // TODO: Implement process
}

bool RemoveBullet::isConsistent() {
    // TODO: Implement isConsistent
    return false;
}

bool RemoveBullet::validate(UdpConnection var1) {
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

#include <string>
#include "zombie\network\packets\hit/PlayerBodyPart.h"

namespace zombie {
namespace network {
namespace packets {
namespace hit {

void PlayerBodyPart::set(BodyPart var1) {
    // TODO: Implement set
}

void PlayerBodyPart::parse(ByteBuffer var1, IsoGameCharacter var2) {
    // TODO: Implement parse
}

void PlayerBodyPart::parse(ByteBuffer var1, UdpConnection var2) {
    // TODO: Implement parse
}

void PlayerBodyPart::write(ByteBufferWriter var1) {
    // TODO: Implement write
}

std::string PlayerBodyPart::getDescription() {
    // TODO: Implement getDescription
    return "";
}

BodyPart PlayerBodyPart::getBodyPart() {
    // TODO: Implement getBodyPart
    return nullptr;
}

} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

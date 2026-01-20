#include <string>
#include "zombie\network\packets\hit/MovingObject.h"

namespace zombie {
namespace network {
namespace packets {
namespace hit {

void MovingObject::setMovingObject(IsoMovingObject var1) {
    // TODO: Implement setMovingObject
}

IsoMovingObject MovingObject::getMovingObject() {
    // TODO: Implement getMovingObject
    return nullptr;
}

void MovingObject::parse(ByteBuffer var1, UdpConnection var2) {
    // TODO: Implement parse
}

void MovingObject::write(ByteBufferWriter var1) {
    // TODO: Implement write
}

int MovingObject::getPacketSizeBytes() {
    // TODO: Implement getPacketSizeBytes
    return 0;
}

std::string MovingObject::getDescription() {
    // TODO: Implement getDescription
    return "";
}

} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

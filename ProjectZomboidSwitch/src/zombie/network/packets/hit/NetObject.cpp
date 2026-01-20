#include <string>
#include "zombie\network\packets\hit/NetObject.h"

namespace zombie {
namespace network {
namespace packets {
namespace hit {

void NetObject::setObject(IsoObject var1) {
    // TODO: Implement setObject
}

IsoObject NetObject::getObject() {
    // TODO: Implement getObject
    return nullptr;
}

void NetObject::parse(ByteBuffer var1, UdpConnection var2) {
    // TODO: Implement parse
}

void NetObject::write(ByteBufferWriter var1) {
    // TODO: Implement write
}

int NetObject::getPacketSizeBytes() {
    // TODO: Implement getPacketSizeBytes
    return 0;
}

std::string NetObject::getDescription() {
    // TODO: Implement getDescription
    return "";
}

} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

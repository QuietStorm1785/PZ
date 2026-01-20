#include <string>
#include "zombie\network\packets/ActionPacket.h"

namespace zombie {
namespace network {
namespace packets {

void ActionPacket::set(bool var1, BaseAction var2) {
    // TODO: Implement set
}

void ActionPacket::parse(ByteBuffer var1, UdpConnection var2) {
    // TODO: Implement parse
}

void ActionPacket::write(ByteBufferWriter var1) {
    // TODO: Implement write
}

bool ActionPacket::isConsistent() {
    // TODO: Implement isConsistent
    return false;
}

std::string ActionPacket::getDescription() {
    // TODO: Implement getDescription
    return "";
}

bool ActionPacket::isRelevant(UdpConnection var1) {
    // TODO: Implement isRelevant
    return false;
}

void ActionPacket::process() {
    // TODO: Implement process
}

} // namespace packets
} // namespace network
} // namespace zombie

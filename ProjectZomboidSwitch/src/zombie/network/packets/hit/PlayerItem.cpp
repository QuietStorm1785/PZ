#include <string>
#include "zombie\network\packets\hit/PlayerItem.h"

namespace zombie {
namespace network {
namespace packets {
namespace hit {

void PlayerItem::set(InventoryItem var1) {
    // TODO: Implement set
}

void PlayerItem::parse(ByteBuffer var1, UdpConnection var2) {
    // TODO: Implement parse
}

void PlayerItem::write(ByteBufferWriter var1) {
    // TODO: Implement write
}

bool PlayerItem::isConsistent() {
    // TODO: Implement isConsistent
    return false;
}

std::string PlayerItem::getDescription() {
    // TODO: Implement getDescription
    return "";
}

InventoryItem PlayerItem::getItem() {
    // TODO: Implement getItem
    return nullptr;
}

} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

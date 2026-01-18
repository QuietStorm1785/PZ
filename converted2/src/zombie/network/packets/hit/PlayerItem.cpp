#include "zombie/network/packets/hit/PlayerItem.h"

namespace zombie {
namespace network {
namespace packets {
namespace hit {

void PlayerItem::set(InventoryItem itemx) {
  // TODO: Implement set
}

void PlayerItem::parse(ByteBuffer byteBuffer, UdpConnection var2) {
  // TODO: Implement parse
}

void PlayerItem::write(ByteBufferWriter byteBufferWriter) {
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

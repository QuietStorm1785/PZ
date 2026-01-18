#include "zombie/network/packets/AddXp.h"

namespace zombie {
namespace network {
namespace packets {

void AddXp::set(IsoPlayer player, PerkFactory.Perk perkx, int int0) {
 // TODO: Implement set
}

void AddXp::parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
 // TODO: Implement parse
}

void AddXp::write(ByteBufferWriter byteBufferWriter) {
 // TODO: Implement write
}

void AddXp::process() {
 // TODO: Implement process
}

bool AddXp::isConsistent() {
 // TODO: Implement isConsistent
 return false;
}

bool AddXp::validate(UdpConnection udpConnection) {
 // TODO: Implement validate
 return false;
}

std::string AddXp::getDescription() {
 // TODO: Implement getDescription
 return "";
}

} // namespace packets
} // namespace network
} // namespace zombie

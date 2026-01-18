#include "zombie/network/packets/hit/PlayerHitVehiclePacket.h"

namespace zombie {
namespace network {
namespace packets {
namespace hit {

public
PlayerHitVehiclePacket::PlayerHitVehiclePacket() {
 // TODO: Implement PlayerHitVehiclePacket
 return nullptr;
}

void PlayerHitVehiclePacket::set(IsoPlayer player, BaseVehicle vehiclex,
 HandWeapon weapon, bool boolean0) {
 // TODO: Implement set
}

void PlayerHitVehiclePacket::parse(ByteBuffer byteBuffer,
 UdpConnection udpConnection) {
 // TODO: Implement parse
}

void PlayerHitVehiclePacket::write(ByteBufferWriter byteBufferWriter) {
 // TODO: Implement write
}

bool PlayerHitVehiclePacket::isConsistent() {
 // TODO: Implement isConsistent
 return false;
}

std::string PlayerHitVehiclePacket::getDescription() {
 // TODO: Implement getDescription
 return "";
}

void PlayerHitVehiclePacket::process() {
 // TODO: Implement process
}

bool PlayerHitVehiclePacket::validate(UdpConnection udpConnection) {
 // TODO: Implement validate
 return false;
}

} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

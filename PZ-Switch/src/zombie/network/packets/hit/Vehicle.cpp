#include "zombie/network/packets/hit/Vehicle.h"

namespace zombie {
namespace network {
namespace packets {
namespace hit {

void Vehicle::set(BaseVehicle vehicle1) {
 // TODO: Implement set
}

void Vehicle::parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
 // TODO: Implement parse
}

void Vehicle::write(ByteBufferWriter byteBufferWriter) {
 // TODO: Implement write
}

bool Vehicle::isConsistent() {
 // TODO: Implement isConsistent
 return false;
}

std::string Vehicle::getDescription() {
 // TODO: Implement getDescription
 return "";
}

void Vehicle::process(IsoGameCharacter character, HandWeapon weapon) {
 // TODO: Implement process
}

BaseVehicle Vehicle::getVehicle() {
 // TODO: Implement getVehicle
 return nullptr;
}

float Vehicle::getX() {
 // TODO: Implement getX
 return 0;
}

float Vehicle::getY() {
 // TODO: Implement getY
 return 0;
}

} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

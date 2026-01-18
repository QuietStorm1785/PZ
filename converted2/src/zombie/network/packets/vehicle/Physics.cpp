#include "zombie/network/packets/vehicle/Physics.h"

namespace zombie {
namespace network {
namespace packets {
namespace vehicle {

void Physics::parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
  // TODO: Implement parse
}

void Physics::write(ByteBufferWriter byteBufferWriter) {
  // TODO: Implement write
}

bool Physics::set(BaseVehicle vehiclex) {
  // TODO: Implement set
  return false;
}

bool Physics::isConsistent() {
  // TODO: Implement isConsistent
  return false;
}

void Physics::process() {
  // TODO: Implement process
}

bool Physics::isRelevant(UdpConnection udpConnection) {
  // TODO: Implement isRelevant
  return false;
}

} // namespace vehicle
} // namespace packets
} // namespace network
} // namespace zombie

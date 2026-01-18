#include "zombie/network/packets/hit/VehicleHit.h"

namespace zombie {
namespace network {
namespace packets {
namespace hit {

void VehicleHit::set(bool boolean0, float float0, float float1, float float2, float float3, int int0, float float4, bool boolean1, bool boolean2) {
 // TODO: Implement set
}

void VehicleHit::parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
 // TODO: Implement parse
}

void VehicleHit::write(ByteBufferWriter byteBufferWriter) {
 // TODO: Implement write
}

std::string VehicleHit::getDescription() {
 // TODO: Implement getDescription
 return "";
}

void VehicleHit::process(IsoGameCharacter character0, IsoGameCharacter character1, BaseVehicle vehicle) {
 // TODO: Implement process
}

float VehicleHit::getSpeed() {
 // TODO: Implement getSpeed
 return 0;
}

bool VehicleHit::isVehicle() {
 // TODO: Implement isVehicle
 return false;
}

} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

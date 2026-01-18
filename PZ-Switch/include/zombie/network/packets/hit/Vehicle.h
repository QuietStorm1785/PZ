#pragma once
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/packets/INetworkPacket.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/VehicleManager.h"
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
namespace packets {
namespace hit {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Vehicle : public Instance {
public:
 BaseVehicle vehicle;

 void set(BaseVehicle vehicle1) {
 super.set(vehicle1.getId());
 this->vehicle = vehicle1;
 }

 void parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
 super.parse(byteBuffer, udpConnection);
 this->vehicle = VehicleManager.instance.getVehicleByID(this->ID);
 }

 void write(ByteBufferWriter byteBufferWriter) {
 super.write(byteBufferWriter);
 }

 bool isConsistent() {
 return super.isConsistent() && this->vehicle != nullptr;
 }

 std::string getDescription() {
 return super.getDescription() + "\n\tVehicle [ vehicle=" +
 (this->vehicle.empty()
 ? "?"
 : "\"" + this->vehicle.getScriptName() + "\"") +
 " ]";
 }

 void process(IsoGameCharacter character, HandWeapon weapon) {
 if (GameServer.bServer) {
 this->vehicle.hitVehicle(character, weapon);
 }
 }

 BaseVehicle getVehicle() { return this->vehicle; }

 float getX() { return this->vehicle.getX(); }

 float getY() { return this->vehicle.getY(); }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

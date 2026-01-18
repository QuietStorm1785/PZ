#pragma once
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/packets/INetworkPacket.h"
#include "zombie/vehicles/BaseVehicle.h"
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

class VehicleHit : public Hit {
public:
 int vehicleDamage;
 float vehicleSpeed;
 bool isVehicleHitFromBehind;
 bool isTargetHitFromBehind;

 void set(bool boolean0, float float0, float float1, float float2,
 float float3, int int0, float float4, bool boolean1, bool boolean2) {
 super.set(boolean0, float0, float1, float2, float3);
 this->vehicleDamage = int0;
 this->vehicleSpeed = float4;
 this->isVehicleHitFromBehind = boolean1;
 this->isTargetHitFromBehind = boolean2;
 }

 void parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
 super.parse(byteBuffer, udpConnection);
 this->vehicleDamage = byteBuffer.getInt();
 this->vehicleSpeed = byteBuffer.getFloat();
 this->isVehicleHitFromBehind = byteBuffer.get() != 0;
 this->isTargetHitFromBehind = byteBuffer.get() != 0;
 }

 void write(ByteBufferWriter byteBufferWriter) {
 super.write(byteBufferWriter);
 byteBufferWriter.putInt(this->vehicleDamage);
 byteBufferWriter.putFloat(this->vehicleSpeed);
 byteBufferWriter.putBoolean(this->isVehicleHitFromBehind);
 byteBufferWriter.putBoolean(this->isTargetHitFromBehind);
 }

 std::string getDescription() {
 return super.getDescription() + "\n\tVehicle [ speed=" + this->vehicleSpeed +
 " | damage=" + this->vehicleDamage + " | target-hit=" +
 (this->isTargetHitFromBehind ? "FRONT" : "BEHIND") +
 " | vehicle-hit=" +
 (this->isVehicleHitFromBehind ? "FRONT" : "REAR") + " ]";
 }

 void process(IsoGameCharacter character0, IsoGameCharacter character1,
 BaseVehicle vehicle) {
 super.process(character0, character1);
 if (GameServer.bServer) {
 if (this->vehicleDamage != 0) {
 if (this->isVehicleHitFromBehind) {
 vehicle.addDamageFrontHitAChr(this->vehicleDamage);
 } else {
 vehicle.addDamageRearHitAChr(this->vehicleDamage);
 }

 vehicle.transmitBlood();
 }
 } else if (GameClient.bClient) {
 if (character1 instanceof IsoZombie) {
 ((IsoZombie)character1)
 .applyDamageFromVehicle(this->vehicleSpeed, this->damage);
 } else if (character1 instanceof IsoPlayer) {
 ((IsoPlayer)character1).getDamageFromHitByACar(this->vehicleSpeed);
 ((IsoPlayer)character1).actionContext.reportEvent("washit");
 character1.setVariable("hitpvp", false);
 }
 }
 }

 float getSpeed() { return this->vehicleSpeed; }

 bool isVehicle() { return true; }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

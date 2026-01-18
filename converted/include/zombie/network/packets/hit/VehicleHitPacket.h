#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/packets/INetworkPacket.h"
#include "zombie/vehicles/BaseVehicle.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
namespace hit {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class VehicleHitPacket : public HitCharacterPacket {
public:
 const Player wielder = new Player();
 const Vehicle vehicle = new Vehicle();

 public VehicleHitPacket(HitCharacterPacket.HitType hitType) {
 super(hitType);
 }

 void set(IsoPlayer player, BaseVehicle vehiclex, bool boolean0) {
 this->wielder.set(player, boolean0);
 this->vehicle.set(vehiclex);
 }

 void parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
 this->wielder.parse(byteBuffer, udpConnection);
 this->wielder.parsePlayer(nullptr);
 this->vehicle.parse(byteBuffer, udpConnection);
 }

 void write(ByteBufferWriter byteBufferWriter) {
 super.write(byteBufferWriter);
 this->wielder.write(byteBufferWriter);
 this->vehicle.write(byteBufferWriter);
 }

 bool isRelevant(UdpConnection udpConnection) {
 return this->wielder.isRelevant(udpConnection);
 }

 bool isConsistent() {
 return super.isConsistent() && this->wielder.isConsistent() && this->vehicle.isConsistent();
 }

 std::string getDescription() {
 return super.getDescription() + "\n\tWielder " + this->wielder.getDescription() + "\n\tVehicle " + this->vehicle.getDescription();
 }

 void preProcess() {
 this->wielder.process();
 }

 void postProcess() {
 this->wielder.process();
 }

 void attack() {
 }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

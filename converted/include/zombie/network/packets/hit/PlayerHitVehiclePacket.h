#pragma once
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/network/PacketValidator.h"
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

class PlayerHitVehiclePacket : public PlayerHitPacket {
public:
  const Vehicle vehicle = new Vehicle();

public
  PlayerHitVehiclePacket() {
    super(HitCharacterPacket.HitType.PlayerHitVehicle);
  }

  void set(IsoPlayer player, BaseVehicle vehiclex, HandWeapon weapon,
           bool boolean0) {
    super.set(player, weapon, boolean0);
    this.vehicle.set(vehiclex);
  }

  void parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
    super.parse(byteBuffer, udpConnection);
    this.vehicle.parse(byteBuffer, udpConnection);
  }

  void write(ByteBufferWriter byteBufferWriter) {
    super.write(byteBufferWriter);
    this.vehicle.write(byteBufferWriter);
  }

  bool isConsistent() {
    return super.isConsistent() && this.vehicle.isConsistent();
  }

  std::string getDescription() {
    return super.getDescription() + "\n\tVehicle " +
           this.vehicle.getDescription();
  }

  void process() {
    this.vehicle.process(this.wielder.getCharacter(), this.weapon.getWeapon());
  }

  bool validate(UdpConnection udpConnection) {
    return PacketValidator.checkLongDistance(
        udpConnection, this.wielder, this.vehicle,
        PlayerHitVehiclePacket.class.getSimpleName());
  }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

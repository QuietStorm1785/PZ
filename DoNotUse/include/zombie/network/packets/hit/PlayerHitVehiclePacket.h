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
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/network/PacketValidator.h"
#include "zombie/network/packets/INetworkPacket.h"
#include "zombie/network/packets/hit/HitCharacterPacket/HitType.h"
#include "zombie/vehicles/BaseVehicle.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
namespace hit {


class PlayerHitVehiclePacket : public PlayerHitPacket {
public:
    const Vehicle vehicle = std::make_shared<Vehicle>();

    public PlayerHitVehiclePacket() {
      super(HitType.PlayerHitVehicle);
   }

    void set(IsoPlayer var1, BaseVehicle var2, HandWeapon var3, bool var4) {
      super.set(var1, var3, var4);
      this.vehicle.set(var2);
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      super.parse(var1, var2);
      this.vehicle.parse(var1, var2);
   }

    void write(ByteBufferWriter var1) {
      super.write(var1);
      this.vehicle.write(var1);
   }

    bool isConsistent() {
      return super.isConsistent() && this.vehicle.isConsistent();
   }

    std::string getDescription() {
      return super.getDescription() + "\n\tVehicle " + this.vehicle.getDescription();
   }

    void process() {
      this.vehicle.process(this.wielder.getCharacter(), this.weapon.getWeapon());
   }

    bool validate(UdpConnection var1) {
      return PacketValidator.checkLongDistance(var1, this.wielder, this.vehicle, PlayerHitVehiclePacket.class.getSimpleName());
   }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

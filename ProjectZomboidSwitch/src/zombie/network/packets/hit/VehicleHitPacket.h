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
#include "zombie/network/packets/hit/HitCharacterPacket/HitType.h"
#include "zombie/vehicles/BaseVehicle.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
namespace hit {


class VehicleHitPacket : public HitCharacterPacket {
public:
    const Player wielder = std::make_shared<Player>();
    const Vehicle vehicle = std::make_shared<Vehicle>();

    public VehicleHitPacket(HitType var1) {
      super(var1);
   }

    void set(IsoPlayer var1, BaseVehicle var2, bool var3) {
      this.wielder.set(var1, var3);
      this.vehicle.set(var2);
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.wielder.parse(var1, var2);
      this.wielder.parsePlayer(nullptr);
      this.vehicle.parse(var1, var2);
   }

    void write(ByteBufferWriter var1) {
      super.write(var1);
      this.wielder.write(var1);
      this.vehicle.write(var1);
   }

    bool isRelevant(UdpConnection var1) {
      return this.wielder.isRelevant(var1);
   }

    bool isConsistent() {
      return super.isConsistent() && this.wielder.isConsistent() && this.vehicle.isConsistent();
   }

    std::string getDescription() {
      return super.getDescription() + "\n\tWielder " + this.wielder.getDescription() + "\n\tVehicle " + this.vehicle.getDescription();
   }

    void preProcess() {
      this.wielder.process();
   }

    void postProcess() {
      this.wielder.process();
   }

    void attack() {
   }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/PacketValidator.h"
#include "zombie/network/packets/INetworkPacket.h"
#include "zombie/network/packets/hit/HitCharacterPacket/HitType.h"
#include "zombie/vehicles/BaseVehicle.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
namespace hit {


class VehicleHitZombiePacket : public VehicleHitPacket {
public:
    const Zombie target = std::make_shared<Zombie>();
    const VehicleHit vehicleHit = std::make_shared<VehicleHit>();
    const Fall fall = std::make_shared<Fall>();

    public VehicleHitZombiePacket() {
      super(HitType.VehicleHitZombie);
   }

    void set(IsoPlayer var1, IsoZombie var2, BaseVehicle var3, float var4, bool var5, int var6, float var7, bool var8) {
      super.set(var1, var3, false);
      this.target.set(var2, false);
      this.vehicleHit.set(false, var4, var2.getHitForce(), var2.getHitDir().x, var2.getHitDir().y, var6, var7, var8, var5);
      this.fall.set(var2.getHitReactionNetworkAI());
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      super.parse(var1, var2);
      this.target.parse(var1, var2);
      this.vehicleHit.parse(var1, var2);
      this.fall.parse(var1, var2);
   }

    void write(ByteBufferWriter var1) {
      super.write(var1);
      this.target.write(var1);
      this.vehicleHit.write(var1);
      this.fall.write(var1);
   }

    bool isConsistent() {
      return super.isConsistent() && this.target.isConsistent() && this.vehicleHit.isConsistent();
   }

    std::string getDescription() {
      return super.getDescription()
         + "\n\tTarget "
         + this.target.getDescription()
         + "\n\tVehicleHit "
         + this.vehicleHit.getDescription()
         + "\n\tFall "
         + this.fall.getDescription();
   }

    void preProcess() {
      super.preProcess();
      this.target.process();
   }

    void process() {
      this.vehicleHit.process(this.wielder.getCharacter(), this.target.getCharacter(), this.vehicle.getVehicle());
      this.fall.process(this.target.getCharacter());
   }

    void postProcess() {
      super.postProcess();
      this.target.process();
   }

    void react() {
      this.target.react();
   }

    void postpone() {
      this.target.getCharacter().getNetworkCharacterAI().setVehicleHit(this);
   }

    bool validate(UdpConnection var1) {
      if (!PacketValidator.checkSpeed(var1, this.vehicleHit, VehicleHitZombiePacket.class.getSimpleName())) {
    return false;
      } else {
         return !PacketValidator.checkShortDistance(var1, this.wielder, this.target, VehicleHitZombiePacket.class.getSimpleName())
            ? false
            : PacketValidator.checkDamage(var1, this.vehicleHit, VehicleHitZombiePacket.class.getSimpleName());
      }
   }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

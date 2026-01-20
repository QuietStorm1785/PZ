#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/packets/INetworkPacket.h"
#include "zombie/vehicles/BaseVehicle.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
namespace hit {


class VehicleHit : public Hit {
public:
    int vehicleDamage;
    float vehicleSpeed;
    bool isVehicleHitFromBehind;
    bool isTargetHitFromBehind;

    void set(bool var1, float var2, float var3, float var4, float var5, int var6, float var7, bool var8, bool var9) {
      super.set(var1, var2, var3, var4, var5);
      this.vehicleDamage = var6;
      this.vehicleSpeed = var7;
      this.isVehicleHitFromBehind = var8;
      this.isTargetHitFromBehind = var9;
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      super.parse(var1, var2);
      this.vehicleDamage = var1.getInt();
      this.vehicleSpeed = var1.getFloat();
      this.isVehicleHitFromBehind = var1.get() != 0;
      this.isTargetHitFromBehind = var1.get() != 0;
   }

    void write(ByteBufferWriter var1) {
      super.write(var1);
      var1.putInt(this.vehicleDamage);
      var1.putFloat(this.vehicleSpeed);
      var1.putBoolean(this.isVehicleHitFromBehind);
      var1.putBoolean(this.isTargetHitFromBehind);
   }

    std::string getDescription() {
      return super.getDescription()
         + "\n\tVehicle [ speed="
         + this.vehicleSpeed
         + " | damage="
         + this.vehicleDamage
         + " | target-hit="
         + (this.isTargetHitFromBehind ? "FRONT" : "BEHIND")
         + " | vehicle-hit="
         + (this.isVehicleHitFromBehind ? "FRONT" : "REAR")
         + " ]";
   }

    void process(IsoGameCharacter var1, IsoGameCharacter var2, BaseVehicle var3) {
      super.process(var1, var2);
      if (GameServer.bServer) {
         if (this.vehicleDamage != 0) {
            if (this.isVehicleHitFromBehind) {
               var3.addDamageFrontHitAChr(this.vehicleDamage);
            } else {
               var3.addDamageRearHitAChr(this.vehicleDamage);
            }

            var3.transmitBlood();
         }
      } else if (GameClient.bClient) {
         if (dynamic_cast<IsoZombie*>(var2) != nullptr) {
            ((IsoZombie)var2).applyDamageFromVehicle(this.vehicleSpeed, this.damage);
         } else if (dynamic_cast<IsoPlayer*>(var2) != nullptr) {
            ((IsoPlayer)var2).getDamageFromHitByACar(this.vehicleSpeed);
            ((IsoPlayer)var2).actionContext.reportEvent("washit");
            var2.setVariable("hitpvp", false);
         }
      }
   }

    float getSpeed() {
      return this.vehicleSpeed;
   }

    bool isVehicle() {
    return true;
   }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/packets/INetworkPacket.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/VehicleManager.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
namespace hit {


class Vehicle : public Instance {
public:
    BaseVehicle vehicle;

    void set(BaseVehicle var1) {
      super.set(var1.getId());
      this.vehicle = var1;
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      super.parse(var1, var2);
      this.vehicle = VehicleManager.instance.getVehicleByID(this.ID);
   }

    void write(ByteBufferWriter var1) {
      super.write(var1);
   }

    bool isConsistent() {
      return super.isConsistent() && this.vehicle != nullptr;
   }

    std::string getDescription() {
      return super.getDescription() + "\n\tVehicle [ vehicle=" + (this.vehicle == nullptr ? "?" : "\"" + this.vehicle.getScriptName() + "\"") + " ]";
   }

    void process(IsoGameCharacter var1, HandWeapon var2) {
      if (GameServer.bServer) {
         this.vehicle.hitVehicle(var1, var2);
      }
   }

    BaseVehicle getVehicle() {
      return this.vehicle;
   }

    float getX() {
      return this.vehicle.getX();
   }

    float getY() {
      return this.vehicle.getY();
   }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

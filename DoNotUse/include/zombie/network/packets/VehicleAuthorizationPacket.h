#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/BaseVehicle/Authorization.h"
#include "zombie/vehicles/BaseVehicle/ServerVehicleState.h"
#include "zombie/vehicles/VehicleManager.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {


class VehicleAuthorizationPacket {
public:
    short vehicleId = -1;
    Authorization authorization = Authorization.Server;
    short authorizationPlayer = -1;

    void set(BaseVehicle var1, UdpConnection var2) {
    ServerVehicleState var3 = var1.connectionState[var2.index];
      var3.setAuthorization(var1);
      this.authorization = var1.netPlayerAuthorization;
      this.authorizationPlayer = var1.netPlayerId;
      this.vehicleId = var1.getId();
   }

    void process() {
    BaseVehicle var1 = VehicleManager.instance.getVehicleByID(this.vehicleId);
      if (var1 != nullptr) {
         DebugLog.Vehicle.trace("vehicle=%d netPlayerAuthorization=%s netPlayerId=%d", var1.getId(), this.authorization.name(), this.authorizationPlayer);
         var1.netPlayerFromServerUpdate(this.authorization, this.authorizationPlayer);
      }
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.vehicleId = var1.getShort();
      this.authorization = Authorization.valueOf(var1.get());
      this.authorizationPlayer = var1.getShort();
   }

    void write(ByteBufferWriter var1) {
      var1.putShort(this.vehicleId);
      var1.putByte(this.authorization.index());
      var1.putShort(this.authorizationPlayer);
   }

    std::string getDescription() {
    return nullptr;
   }
}
} // namespace packets
} // namespace network
} // namespace zombie

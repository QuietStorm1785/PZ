#pragma once
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class VehicleAuthorizationPacket {
public:
  short vehicleId = -1;
  BaseVehicle.Authorization authorization = BaseVehicle.Authorization.Server;
  short authorizationPlayer = -1;

  void set(BaseVehicle vehicle, UdpConnection udpConnection) {
    BaseVehicle.ServerVehicleState serverVehicleState =
        vehicle.connectionState[udpConnection.index];
    serverVehicleState.setAuthorization(vehicle);
    this.authorization = vehicle.netPlayerAuthorization;
    this.authorizationPlayer = vehicle.netPlayerId;
    this.vehicleId = vehicle.getId();
  }

  void process() {
    BaseVehicle vehicle =
        VehicleManager.instance.getVehicleByID(this.vehicleId);
    if (vehicle != nullptr) {
      DebugLog.Vehicle.trace(
          "vehicle=%d netPlayerAuthorization=%s netPlayerId=%d",
          vehicle.getId(), this.authorization.name(), this.authorizationPlayer);
      vehicle.netPlayerFromServerUpdate(this.authorization,
                                        this.authorizationPlayer);
    }
  }

  void parse(ByteBuffer byteBuffer, UdpConnection var2) {
    this.vehicleId = byteBuffer.getShort();
    this.authorization = BaseVehicle.Authorization.valueOf(byteBuffer.get());
    this.authorizationPlayer = byteBuffer.getShort();
  }

  void write(ByteBufferWriter byteBufferWriter) {
    byteBufferWriter.putShort(this.vehicleId);
    byteBufferWriter.putByte(this.authorization.index());
    byteBufferWriter.putShort(this.authorizationPlayer);
  }

  std::string getDescription() { return null; }
}
} // namespace packets
} // namespace network
} // namespace zombie

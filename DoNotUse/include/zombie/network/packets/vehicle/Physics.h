#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/physics/Bullet.h"
#include "zombie/core/physics/WorldSimulation.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/network/packets/INetworkPacket.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/VehicleInterpolationData.h"
#include "zombie/vehicles/VehicleManager.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
namespace vehicle {


class Physics : public VehicleInterpolationData {
public:
   private static const float[] buffer = new float[27];
    short id;
    float force;
    BaseVehicle vehicle;
    bool hasAuth;

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.id = var1.getShort();
      this.time = var1.getLong();
      this.force = var1.getFloat();
      this.x = var1.getFloat();
      this.y = var1.getFloat();
      this.z = var1.getFloat();
      this.qx = var1.getFloat();
      this.qy = var1.getFloat();
      this.qz = var1.getFloat();
      this.qw = var1.getFloat();
      this.vx = var1.getFloat();
      this.vy = var1.getFloat();
      this.vz = var1.getFloat();
      this.engineSpeed = var1.getFloat();
      this.throttle = var1.getFloat();
      this.setNumWheels(var1.getShort());

      for (int var3 = 0; var3 < this.wheelsCount; var3++) {
         this.wheelSteering[var3] = var1.getFloat();
         this.wheelRotation[var3] = var1.getFloat();
         this.wheelSkidInfo[var3] = var1.getFloat();
         this.wheelSuspensionLength[var3] = var1.getFloat();
      }

      this.vehicle = VehicleManager.instance.getVehicleByID(this.id);
      if (this.vehicle != nullptr) {
         this.hasAuth = this.vehicle.hasAuthorization(var2);
      }
   }

    void write(ByteBufferWriter var1) {
      var1.putShort(this.id);
      var1.putLong(this.time);
      var1.putFloat(this.force);
      var1.putFloat(this.x);
      var1.putFloat(this.y);
      var1.putFloat(this.z);
      var1.putFloat(this.qx);
      var1.putFloat(this.qy);
      var1.putFloat(this.qz);
      var1.putFloat(this.qw);
      var1.putFloat(this.vx);
      var1.putFloat(this.vy);
      var1.putFloat(this.vz);
      var1.putFloat(this.engineSpeed);
      var1.putFloat(this.throttle);
      var1.putShort(this.wheelsCount);

      for (int var2 = 0; var2 < this.wheelsCount; var2++) {
         var1.putFloat(this.wheelSteering[var2]);
         var1.putFloat(this.wheelRotation[var2]);
         var1.putFloat(this.wheelSkidInfo[var2]);
         var1.putFloat(this.wheelSuspensionLength[var2]);
      }
   }

    bool set(BaseVehicle var1) {
      if (Bullet.getOwnVehiclePhysics(var1.VehicleID, buffer) != 0) {
    return false;
      } else {
         this.id = var1.getId();
         this.time = WorldSimulation.instance.time;
         this.force = var1.getForce();
    int var2 = 0;
         this.x = buffer[var2++];
         this.y = buffer[var2++];
         this.z = buffer[var2++];
         this.qx = buffer[var2++];
         this.qy = buffer[var2++];
         this.qz = buffer[var2++];
         this.qw = buffer[var2++];
         this.vx = buffer[var2++];
         this.vy = buffer[var2++];
         this.vz = buffer[var2++];
         this.engineSpeed = (float)var1.getEngineSpeed();
         this.throttle = var1.throttle;
         this.wheelsCount = (short)buffer[var2++];

         for (int var3 = 0; var3 < this.wheelsCount; var3++) {
            this.wheelSteering[var3] = buffer[var2++];
            this.wheelRotation[var3] = buffer[var2++];
            this.wheelSkidInfo[var3] = buffer[var2++];
            this.wheelSuspensionLength[var3] = buffer[var2++];
         }

    return true;
      }
   }

    bool isConsistent() {
      return super.isConsistent() && this.vehicle != nullptr && (GameClient.bClient && !this.hasAuth || GameServer.bServer && this.hasAuth);
   }

    void process() {
      if (this.isConsistent()) {
         if (GameClient.bClient) {
            this.vehicle.interpolation.interpolationDataAdd(this.vehicle, this);
         } else if (GameServer.bServer) {
            this.vehicle.setClientForce(this.force);
            this.vehicle.setX(this.x);
            this.vehicle.setY(this.y);
            this.vehicle.setZ(this.z);
            this.vehicle.savedRot.x = this.qx;
            this.vehicle.savedRot.y = this.qy;
            this.vehicle.savedRot.z = this.qz;
            this.vehicle.savedRot.w = this.qw;
            this.vehicle
               .jniTransform
               .origin
               .set(this.vehicle.x - WorldSimulation.instance.offsetX, this.vehicle.z, this.vehicle.y - WorldSimulation.instance.offsetY);
            this.vehicle.jniTransform.setRotation(this.vehicle.savedRot);
            this.vehicle.jniLinearVelocity.x = this.vx;
            this.vehicle.jniLinearVelocity.y = this.vy;
            this.vehicle.jniLinearVelocity.z = this.vz;
            this.vehicle.engineSpeed = this.engineSpeed;
            this.vehicle.throttle = this.throttle;
            this.setNumWheels(this.wheelsCount);

            for (int var1 = 0; var1 < this.wheelsCount; var1++) {
               this.vehicle.wheelInfo[var1].steering = this.wheelSteering[var1];
               this.vehicle.wheelInfo[var1].rotation = this.wheelRotation[var1];
               this.vehicle.wheelInfo[var1].skidInfo = this.wheelSkidInfo[var1];
               this.vehicle.wheelInfo[var1].suspensionLength = this.wheelSuspensionLength[var1];
            }
         }
      } else if (GameClient.bClient) {
         VehicleManager.instance.sendRequestGetFull(this.id, PacketType.Vehicles);
      }
   }

    bool isRelevant(UdpConnection var1) {
      return var1.RelevantTo(this.x, this.y);
   }
}
} // namespace vehicle
} // namespace packets
} // namespace network
} // namespace zombie

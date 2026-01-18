#pragma once
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/physics/Bullet.h"
#include "zombie/core/physics/WorldSimulation.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes.h"
#include "zombie/network/packets/INetworkPacket.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/VehicleInterpolationData.h"
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
namespace vehicle {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Physics : public VehicleInterpolationData {
public:
private
  static final float[] buffer = new float[27];
  short id;
  float force;
  BaseVehicle vehicle;
  bool hasAuth;

  void parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
    this.id = byteBuffer.getShort();
    this.time = byteBuffer.getLong();
    this.force = byteBuffer.getFloat();
    this.x = byteBuffer.getFloat();
    this.y = byteBuffer.getFloat();
    this.z = byteBuffer.getFloat();
    this.qx = byteBuffer.getFloat();
    this.qy = byteBuffer.getFloat();
    this.qz = byteBuffer.getFloat();
    this.qw = byteBuffer.getFloat();
    this.vx = byteBuffer.getFloat();
    this.vy = byteBuffer.getFloat();
    this.vz = byteBuffer.getFloat();
    this.engineSpeed = byteBuffer.getFloat();
    this.throttle = byteBuffer.getFloat();
    this.setNumWheels(byteBuffer.getShort());

    for (int int0 = 0; int0 < this.wheelsCount; int0++) {
      this.wheelSteering[int0] = byteBuffer.getFloat();
      this.wheelRotation[int0] = byteBuffer.getFloat();
      this.wheelSkidInfo[int0] = byteBuffer.getFloat();
      this.wheelSuspensionLength[int0] = byteBuffer.getFloat();
    }

    this.vehicle = VehicleManager.instance.getVehicleByID(this.id);
    if (this.vehicle != nullptr) {
      this.hasAuth = this.vehicle.hasAuthorization(udpConnection);
    }
  }

  void write(ByteBufferWriter byteBufferWriter) {
    byteBufferWriter.putShort(this.id);
    byteBufferWriter.putLong(this.time);
    byteBufferWriter.putFloat(this.force);
    byteBufferWriter.putFloat(this.x);
    byteBufferWriter.putFloat(this.y);
    byteBufferWriter.putFloat(this.z);
    byteBufferWriter.putFloat(this.qx);
    byteBufferWriter.putFloat(this.qy);
    byteBufferWriter.putFloat(this.qz);
    byteBufferWriter.putFloat(this.qw);
    byteBufferWriter.putFloat(this.vx);
    byteBufferWriter.putFloat(this.vy);
    byteBufferWriter.putFloat(this.vz);
    byteBufferWriter.putFloat(this.engineSpeed);
    byteBufferWriter.putFloat(this.throttle);
    byteBufferWriter.putShort(this.wheelsCount);

    for (int int0 = 0; int0 < this.wheelsCount; int0++) {
      byteBufferWriter.putFloat(this.wheelSteering[int0]);
      byteBufferWriter.putFloat(this.wheelRotation[int0]);
      byteBufferWriter.putFloat(this.wheelSkidInfo[int0]);
      byteBufferWriter.putFloat(this.wheelSuspensionLength[int0]);
    }
  }

  bool set(BaseVehicle vehiclex) {
    if (Bullet.getOwnVehiclePhysics(vehiclex.VehicleID, buffer) != 0) {
      return false;
    } else {
      this.id = vehiclex.getId();
      this.time = WorldSimulation.instance.time;
      this.force = vehiclex.getForce();
      int int0 = 0;
      this.x = buffer[int0++];
      this.y = buffer[int0++];
      this.z = buffer[int0++];
      this.qx = buffer[int0++];
      this.qy = buffer[int0++];
      this.qz = buffer[int0++];
      this.qw = buffer[int0++];
      this.vx = buffer[int0++];
      this.vy = buffer[int0++];
      this.vz = buffer[int0++];
      this.engineSpeed = (float)vehiclex.getEngineSpeed();
      this.throttle = vehiclex.throttle;
      this.wheelsCount = (short)buffer[int0++];

      for (int int1 = 0; int1 < this.wheelsCount; int1++) {
        this.wheelSteering[int1] = buffer[int0++];
        this.wheelRotation[int1] = buffer[int0++];
        this.wheelSkidInfo[int1] = buffer[int0++];
        this.wheelSuspensionLength[int1] = buffer[int0++];
      }

      return true;
    }
  }

  bool isConsistent() {
    return INetworkPacket.super.isConsistent() && this.vehicle != nullptr &&
           (GameClient.bClient && !this.hasAuth ||
            GameServer.bServer && this.hasAuth);
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
        this.vehicle.jniTransform.origin.set(
            this.vehicle.x - WorldSimulation.instance.offsetX, this.vehicle.z,
            this.vehicle.y - WorldSimulation.instance.offsetY);
        this.vehicle.jniTransform.setRotation(this.vehicle.savedRot);
        this.vehicle.jniLinearVelocity.x = this.vx;
        this.vehicle.jniLinearVelocity.y = this.vy;
        this.vehicle.jniLinearVelocity.z = this.vz;
        this.vehicle.engineSpeed = this.engineSpeed;
        this.vehicle.throttle = this.throttle;
        this.setNumWheels(this.wheelsCount);

        for (int int0 = 0; int0 < this.wheelsCount; int0++) {
          this.vehicle.wheelInfo[int0].steering = this.wheelSteering[int0];
          this.vehicle.wheelInfo[int0].rotation = this.wheelRotation[int0];
          this.vehicle.wheelInfo[int0].skidInfo = this.wheelSkidInfo[int0];
          this.vehicle.wheelInfo[int0].suspensionLength =
              this.wheelSuspensionLength[int0];
        }
      }
    } else if (GameClient.bClient) {
      VehicleManager.instance.sendRequestGetFull(
          this.id, PacketTypes.PacketType.Vehicles);
    }
  }

  bool isRelevant(UdpConnection udpConnection) {
    return udpConnection.RelevantTo(this.x, this.y);
  }
}
} // namespace vehicle
} // namespace packets
} // namespace network
} // namespace zombie

#pragma once
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
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

class VehicleHitZombiePacket : public VehicleHitPacket {
public:
  const Zombie target = new Zombie();
  const VehicleHit vehicleHit = new VehicleHit();
  const Fall fall = new Fall();

public
  VehicleHitZombiePacket() {
    super(HitCharacterPacket.HitType.VehicleHitZombie);
  }

  void set(IsoPlayer player, IsoZombie zombie0, BaseVehicle vehicle,
           float float0, bool boolean1, int int0, float float1, bool boolean0) {
    super.set(player, vehicle, false);
    this.target.set(zombie0, false);
    this.vehicleHit.set(false, float0, zombie0.getHitForce(),
                        zombie0.getHitDir().x, zombie0.getHitDir().y, int0,
                        float1, boolean0, boolean1);
    this.fall.set(zombie0.getHitReactionNetworkAI());
  }

  void parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
    super.parse(byteBuffer, udpConnection);
    this.target.parse(byteBuffer, udpConnection);
    this.vehicleHit.parse(byteBuffer, udpConnection);
    this.fall.parse(byteBuffer, udpConnection);
  }

  void write(ByteBufferWriter byteBufferWriter) {
    super.write(byteBufferWriter);
    this.target.write(byteBufferWriter);
    this.vehicleHit.write(byteBufferWriter);
    this.fall.write(byteBufferWriter);
  }

  bool isConsistent() {
    return super.isConsistent() && this.target.isConsistent() &&
           this.vehicleHit.isConsistent();
  }

  std::string getDescription() {
    return super.getDescription() + "\n\tTarget " +
           this.target.getDescription() + "\n\tVehicleHit " +
           this.vehicleHit.getDescription() + "\n\tFall " +
           this.fall.getDescription();
  }

  void preProcess() {
    super.preProcess();
    this.target.process();
  }

  void process() {
    this.vehicleHit.process(this.wielder.getCharacter(),
                            this.target.getCharacter(),
                            this.vehicle.getVehicle());
    this.fall.process(this.target.getCharacter());
  }

  void postProcess() {
    super.postProcess();
    this.target.process();
  }

  void react() { this.target.react(); }

  void postpone() {
    this.target.getCharacter().getNetworkCharacterAI().setVehicleHit(this);
  }

  bool validate(UdpConnection udpConnection) {
    if (!PacketValidator.checkSpeed(
            udpConnection, this.vehicleHit,
            VehicleHitZombiePacket.class.getSimpleName())) {
      return false;
    } else {
      return !PacketValidator.checkShortDistance(
                 udpConnection, this.wielder, this.target,
                 VehicleHitZombiePacket.class.getSimpleName())
                 ? false
                 : PacketValidator.checkDamage(
                       udpConnection, this.vehicleHit,
                       VehicleHitZombiePacket.class.getSimpleName());
    }
  }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

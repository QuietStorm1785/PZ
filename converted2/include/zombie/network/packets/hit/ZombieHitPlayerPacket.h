#pragma once
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/PacketValidator.h"
#include "zombie/network/packets/INetworkPacket.h"
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

class ZombieHitPlayerPacket : public HitCharacterPacket {
public:
  const Zombie wielder = new Zombie();
  const Player target = new Player();
  const Bite bite = new Bite();

public
  ZombieHitPlayerPacket() { super(HitCharacterPacket.HitType.ZombieHitPlayer); }

  void set(IsoZombie zombie0, IsoPlayer player) {
    this.wielder.set(zombie0, false);
    this.target.set(player, false);
    this.bite.set(zombie0);
  }

  void parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
    this.wielder.parse(byteBuffer, udpConnection);
    this.target.parse(byteBuffer, udpConnection);
    this.target.parsePlayer(udpConnection);
    this.bite.parse(byteBuffer, udpConnection);
  }

  void write(ByteBufferWriter byteBufferWriter) {
    super.write(byteBufferWriter);
    this.wielder.write(byteBufferWriter);
    this.target.write(byteBufferWriter);
    this.bite.write(byteBufferWriter);
  }

  bool isRelevant(UdpConnection udpConnection) {
    return this.target.isRelevant(udpConnection);
  }

  bool isConsistent() {
    return super.isConsistent() && this.target.isConsistent() &&
           this.wielder.isConsistent();
  }

  std::string getDescription() {
    return super.getDescription() + "\n\tWielder " +
           this.wielder.getDescription() + "\n\tTarget " +
           this.target.getDescription() + "\n\tBite " +
           this.bite.getDescription();
  }

  void preProcess() {
    this.wielder.process();
    this.target.process();
  }

  void process() {
    this.bite.process((IsoZombie)this.wielder.getCharacter(),
                      this.target.getCharacter());
  }

  void postProcess() {
    this.wielder.process();
    this.target.process();
  }

  void attack() {}

  void react() {
    this.wielder.react();
    this.target.react();
  }

  bool validate(UdpConnection udpConnection) {
    if (!PacketValidator.checkShortDistance(
            udpConnection, this.wielder, this.target,
            ZombieHitPlayerPacket.class.getSimpleName())) {
      return false;
    } else {
      return !PacketValidator.checkOwner(
                 udpConnection, this.wielder,
                 ZombieHitPlayerPacket.class.getSimpleName())
                 ? false
                 : PacketValidator.checkTarget(
                       udpConnection, this.target,
                       ZombieHitPlayerPacket.class.getSimpleName());
    }
  }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

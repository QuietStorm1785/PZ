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
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
namespace hit {


class ZombieHitPlayerPacket : public HitCharacterPacket {
public:
    const Zombie wielder = std::make_shared<Zombie>();
    const Player target = std::make_shared<Player>();
    const Bite bite = std::make_shared<Bite>();

    public ZombieHitPlayerPacket() {
      super(HitType.ZombieHitPlayer);
   }

    void set(IsoZombie var1, IsoPlayer var2) {
      this.wielder.set(var1, false);
      this.target.set(var2, false);
      this.bite.set(var1);
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.wielder.parse(var1, var2);
      this.target.parse(var1, var2);
      this.target.parsePlayer(var2);
      this.bite.parse(var1, var2);
   }

    void write(ByteBufferWriter var1) {
      super.write(var1);
      this.wielder.write(var1);
      this.target.write(var1);
      this.bite.write(var1);
   }

    bool isRelevant(UdpConnection var1) {
      return this.target.isRelevant(var1);
   }

    bool isConsistent() {
      return super.isConsistent() && this.target.isConsistent() && this.wielder.isConsistent();
   }

    std::string getDescription() {
      return super.getDescription()
         + "\n\tWielder "
         + this.wielder.getDescription()
         + "\n\tTarget "
         + this.target.getDescription()
         + "\n\tBite "
         + this.bite.getDescription();
   }

    void preProcess() {
      this.wielder.process();
      this.target.process();
   }

    void process() {
      this.bite.process((IsoZombie)this.wielder.getCharacter(), this.target.getCharacter());
   }

    void postProcess() {
      this.wielder.process();
      this.target.process();
   }

    void attack() {
   }

    void react() {
      this.wielder.react();
      this.target.react();
   }

    bool validate(UdpConnection var1) {
      if (!PacketValidator.checkShortDistance(var1, this.wielder, this.target, ZombieHitPlayerPacket.class.getSimpleName())) {
    return false;
      } else {
         return !PacketValidator.checkOwner(var1, this.wielder, ZombieHitPlayerPacket.class.getSimpleName())
            ? false
            : PacketValidator.checkTarget(var1, this.target, ZombieHitPlayerPacket.class.getSimpleName());
      }
   }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

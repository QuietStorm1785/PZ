#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/network/PacketValidator.h"
#include "zombie/network/packets/INetworkPacket.h"
#include "zombie/network/packets/hit/HitCharacterPacket/HitType.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
namespace hit {


class PlayerHitPlayerPacket : public PlayerHitPacket {
public:
    const Player target = std::make_shared<Player>();
    const WeaponHit hit = std::make_shared<WeaponHit>();
    const Fall fall = std::make_shared<Fall>();

    public PlayerHitPlayerPacket() {
      super(HitType.PlayerHitPlayer);
   }

    void set(IsoPlayer var1, IsoPlayer var2, HandWeapon var3, float var4, bool var5, float var6, bool var7, bool var8) {
      super.set(var1, var3, var7);
      this.target.set(var2, false);
      this.hit.set(var5, var4, var6, var2.getHitForce(), var2.getHitDir().x, var2.getHitDir().y, var8);
      this.fall.set(var2.getHitReactionNetworkAI());
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      super.parse(var1, var2);
      this.target.parse(var1, var2);
      this.target.parsePlayer(nullptr);
      this.hit.parse(var1, var2);
      this.fall.parse(var1, var2);
   }

    void write(ByteBufferWriter var1) {
      super.write(var1);
      this.target.write(var1);
      this.hit.write(var1);
      this.fall.write(var1);
   }

    bool isConsistent() {
      return super.isConsistent() && this.target.isConsistent() && this.hit.isConsistent();
   }

    std::string getDescription() {
      return super.getDescription()
         + "\n\tTarget "
         + this.target.getDescription()
         + "\n\tHit "
         + this.hit.getDescription()
         + "\n\tFall "
         + this.fall.getDescription();
   }

    void preProcess() {
      super.preProcess();
      this.target.process();
   }

    void process() {
      this.hit.process(this.wielder.getCharacter(), this.target.getCharacter(), this.weapon.getWeapon());
      this.fall.process(this.target.getCharacter());
   }

    void postProcess() {
      super.postProcess();
      this.target.process();
   }

    bool validate(UdpConnection var1) {
      if (!PacketValidator.checkPVP(var1, this.wielder, this.target, PlayerHitPlayerPacket.class.getSimpleName())) {
    return false;
      } else {
         return !PacketValidator.checkLongDistance(var1, this.wielder, this.target, PlayerHitPlayerPacket.class.getSimpleName())
            ? false
            : PacketValidator.checkDamage(var1, this.hit, PlayerHitPlayerPacket.class.getSimpleName());
      }
   }

    void attack() {
      this.wielder.attack(this.weapon.getWeapon(), true);
   }

    void react() {
      this.target.react();
   }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoLivingCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/network/packets/INetworkPacket.h"
#include "zombie/network/packets/hit/HitCharacterPacket/HitType.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
namespace hit {


class PlayerHitPacket : public HitCharacterPacket {
public:
    const Player wielder = std::make_shared<Player>();
    const Weapon weapon = std::make_shared<Weapon>();

    public PlayerHitPacket(HitType var1) {
      super(var1);
   }

    void set(IsoPlayer var1, HandWeapon var2, bool var3) {
      this.wielder.set(var1, var3);
      this.weapon.set(var2);
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.wielder.parse(var1, var2);
      this.wielder.parsePlayer(var2);
      this.weapon.parse(var1, (IsoLivingCharacter)this.wielder.getCharacter());
   }

    void write(ByteBufferWriter var1) {
      super.write(var1);
      this.wielder.write(var1);
      this.weapon.write(var1);
   }

    bool isRelevant(UdpConnection var1) {
      return this.wielder.isRelevant(var1);
   }

    bool isConsistent() {
      return super.isConsistent() && this.weapon.isConsistent() && this.wielder.isConsistent();
   }

    std::string getDescription() {
      return super.getDescription() + "\n\tWielder " + this.wielder.getDescription() + "\n\tWeapon " + this.weapon.getDescription();
   }

    void preProcess() {
      this.wielder.process();
   }

    void postProcess() {
      this.wielder.process();
   }

    void attack() {
      this.wielder.attack(this.weapon.getWeapon(), false);
   }

    void react() {
   }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

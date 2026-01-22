#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/packets/INetworkPacket.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
namespace hit {


class Hit {
public:
    static const float MAX_DAMAGE = 100.0F;
    bool ignore;
    float damage;
    float hitForce;
    float hitDirectionX;
    float hitDirectionY;

    void set(bool var1, float var2, float var3, float var4, float var5) {
      this.ignore = var1;
      this.damage = Math.min(var2, 100.0F);
      this.hitForce = var3;
      this.hitDirectionX = var4;
      this.hitDirectionY = var5;
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.ignore = var1.get() != 0;
      this.damage = var1.getFloat();
      this.hitForce = var1.getFloat();
      this.hitDirectionX = var1.getFloat();
      this.hitDirectionY = var1.getFloat();
   }

    void write(ByteBufferWriter var1) {
      var1.putBoolean(this.ignore);
      var1.putFloat(this.damage);
      var1.putFloat(this.hitForce);
      var1.putFloat(this.hitDirectionX);
      var1.putFloat(this.hitDirectionY);
   }

    std::string getDescription() {
      return "\n\tHit [ ignore="
         + this.ignore
         + " | damage="
         + this.damage
         + " | force="
         + this.hitForce
         + " | dir=( "
         + this.hitDirectionX
         + " ; "
         + this.hitDirectionY
         + " ) ]";
   }

    void process(IsoGameCharacter var1, IsoGameCharacter var2) {
      var2.getHitDir().set(this.hitDirectionX, this.hitDirectionY);
      var2.setHitForce(this.hitForce);
      if (GameServer.bServer && dynamic_cast<IsoZombie*>(var2) != nullptr && dynamic_cast<IsoPlayer*>(var1) != nullptr) {
         ((IsoZombie)var2).addAggro(var1, this.damage);
         DebugLog.Damage
            .noise("AddAggro zombie=%d player=%d ( \"%s\" ) damage=%f", var2.getOnlineID(), var1.getOnlineID(), ((IsoPlayer)var1).getUsername(), this.damage);
      }

      var2.setAttackedBy(var1);
   }

    float getDamage() {
      return this.damage;
   }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

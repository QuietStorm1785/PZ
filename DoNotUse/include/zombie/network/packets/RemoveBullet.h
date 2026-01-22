#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/BodyDamage/BodyPart.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/PacketValidator.h"
#include "zombie/network/packets/hit/Player.h"
#include "zombie/network/packets/hit/PlayerBodyPart.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {


class RemoveBullet {
public:
    const Player wielder = std::make_shared<Player>();
    const Player target = std::make_shared<Player>();
    PlayerBodyPart bodyPart = std::make_shared<PlayerBodyPart>();

    void set(IsoGameCharacter var1, IsoGameCharacter var2, BodyPart var3) {
      this.wielder.set(var1);
      this.target.set(var2);
      this.bodyPart.set(var3);
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.wielder.parse(var1, var2);
      this.wielder.parsePlayer(var2);
      this.target.parse(var1, var2);
      this.target.parsePlayer(nullptr);
      this.bodyPart.parse(var1, this.target.getCharacter());
   }

    void write(ByteBufferWriter var1) {
      this.wielder.write(var1);
      this.target.write(var1);
      this.bodyPart.write(var1);
   }

    void process() {
    int var1 = this.wielder.getCharacter().getPerkLevel(Perks.Doctor);
      if (!this.wielder.getPlayer().isAccessLevel("None")) {
         var1 = 10;
      }

      if (this.wielder.getCharacter().HasTrait("Hemophobic")) {
         this.wielder.getCharacter().getStats().setPanic(this.wielder.getCharacter().getStats().getPanic() + 50.0F);
      }

      this.wielder.getCharacter().getXp().AddXP(Perks.Doctor, 20.0F);
    float var2 = 80 - var1;
      this.bodyPart.getBodyPart().setAdditionalPain(this.bodyPart.getBodyPart().getAdditionalPain() + var2);
      this.bodyPart.getBodyPart().setHaveBullet(false, var1);
   }

    bool isConsistent() {
      return this.wielder.getCharacter() != nullptr
         && this.wielder.getCharacter() instanceof IsoPlayer
         && this.target.getCharacter() != nullptr
         && this.target.getCharacter() instanceof IsoPlayer
         && this.bodyPart.getBodyPart() != nullptr;
   }

    bool validate(UdpConnection var1) {
      if (GameClient.bClient && !this.bodyPart.getBodyPart().haveBullet()) {
         DebugLog.General.warn(this.getClass().getSimpleName() + ": Validate error: " + this.getDescription());
    return false;
      } else {
         return PacketValidator.checkShortDistance(var1, this.wielder, this.target, this.getClass().getSimpleName());
      }
   }

    std::string getDescription() {
    std::string var1 = "\n\t" + this.getClass().getSimpleName() + " [";
      var1 = var1 + "wielder=" + this.wielder.getDescription() + " | ";
      var1 = var1 + "target=" + this.target.getDescription() + " | ";
      return var1 + "bodyPart=" + this.bodyPart.getDescription() + "] ";
   }
}
} // namespace packets
} // namespace network
} // namespace zombie

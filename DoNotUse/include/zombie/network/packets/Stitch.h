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
#include "zombie/inventory/InventoryItem.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/PacketValidator.h"
#include "zombie/network/packets/hit/Player.h"
#include "zombie/network/packets/hit/PlayerBodyPart.h"
#include "zombie/network/packets/hit/PlayerItem.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {


class Stitch {
public:
    const Player wielder = std::make_shared<Player>();
    const Player target = std::make_shared<Player>();
    PlayerBodyPart bodyPart = std::make_shared<PlayerBodyPart>();
    PlayerItem item = std::make_shared<PlayerItem>();
    float stitchTime = 0.0F;
    bool doIt = false;
    bool infect = false;

    void set(IsoGameCharacter var1, IsoGameCharacter var2, BodyPart var3, InventoryItem var4, bool var5) {
      this.wielder.set(var1);
      this.target.set(var2);
      this.bodyPart.set(var3);
      if (var4 != nullptr) {
         this.item.set(var4);
      }

      this.stitchTime = var3.getStitchTime();
      this.doIt = var5;
      this.infect = var3.isInfectedWound();
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.wielder.parse(var1, var2);
      this.wielder.parsePlayer(var2);
      this.target.parse(var1, var2);
      this.target.parsePlayer(nullptr);
      this.bodyPart.parse(var1, this.target.getCharacter());
      this.item.parse(var1, var2);
      this.stitchTime = var1.getFloat();
      this.doIt = var1.get() == 1;
      this.infect = var1.get() == 1;
   }

    void write(ByteBufferWriter var1) {
      this.wielder.write(var1);
      this.target.write(var1);
      this.bodyPart.write(var1);
      this.item.write(var1);
      var1.putFloat(this.stitchTime);
      var1.putBoolean(this.doIt);
      var1.putBoolean(this.infect);
   }

    void process() {
    int var1 = this.wielder.getCharacter().getPerkLevel(Perks.Doctor);
      if (!this.wielder.getPlayer().isAccessLevel("None")) {
         var1 = 10;
      }

    uint8_t var2 = 20;
      if (this.doIt) {
         if (this.wielder.getCharacter().getInventory().contains("SutureNeedleHolder") || this.item.getItem().getType() == "SutureNeedle")) {
            var2 = 10;
         }
      } else {
         var2 = 5;
      }

      if (this.wielder.getCharacter().getCharacterTraits().Hemophobic.isSet()) {
         this.wielder.getCharacter().getStats().setPanic(this.wielder.getCharacter().getStats().getPanic() + 50.0F);
      }

      if (this.item.getItem() != nullptr) {
         this.item.getItem().Use();
      }

      if (this.bodyPart.getBodyPart().isGetStitchXp()) {
         this.wielder.getCharacter().getXp().AddXP(Perks.Doctor, 15.0F);
      }

      this.bodyPart.getBodyPart().setStitched(this.doIt);
    int var3 = var2 - var1 * 1;
      if (var3 < 0) {
         var3 = 0;
      }

      if (!this.wielder.getPlayer().isAccessLevel("None")) {
         this.bodyPart.getBodyPart().setAdditionalPain(this.bodyPart.getBodyPart().getAdditionalPain() + var3);
      }

      if (this.doIt) {
         this.bodyPart.getBodyPart().setStitchTime(this.stitchTime);
      }

      if (this.infect) {
         this.bodyPart.getBodyPart().setInfectedWound(true);
      }
   }

    bool isConsistent() {
      return this.wielder.getCharacter() != nullptr
         && this.wielder.getCharacter() instanceof IsoPlayer
         && this.target.getCharacter() != nullptr
         && this.target.getCharacter() instanceof IsoPlayer
         && this.bodyPart.getBodyPart() != nullptr
         && this.stitchTime < 50.0F
         && this.stitchTime >= 0.0F;
   }

    bool validate(UdpConnection var1) {
      if (!GameClient.bClient || !this.doIt || this.bodyPart.getBodyPart().isDeepWounded() && !this.bodyPart.getBodyPart().haveGlass()) {
         if (GameClient.bClient && !this.doIt && !this.bodyPart.getBodyPart().stitched()) {
            DebugLog.General.warn(this.getClass().getSimpleName() + ": Validate error: " + this.getDescription());
    return false;
         } else {
            return PacketValidator.checkShortDistance(var1, this.wielder, this.target, this.getClass().getSimpleName());
         }
      } else {
         DebugLog.General.warn(this.getClass().getSimpleName() + ": Validate error: " + this.getDescription());
    return false;
      }
   }

    std::string getDescription() {
    std::string var1 = "\n\t" + this.getClass().getSimpleName() + " [";
      var1 = var1 + "wielder=" + this.wielder.getDescription() + " | ";
      var1 = var1 + "target=" + this.target.getDescription() + " | ";
      var1 = var1 + "bodyPart=" + this.bodyPart.getDescription() + " | ";
      var1 = var1 + "item=" + this.item.getDescription() + " | ";
      var1 = var1 + "stitchTime=" + this.stitchTime + " | ";
      var1 = var1 + "doIt=" + this.doIt + " | ";
      return var1 + "infect=" + this.infect + "] ";
   }
}
} // namespace packets
} // namespace network
} // namespace zombie

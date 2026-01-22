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
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/inventory/types/Food.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/PacketValidator.h"
#include "zombie/network/packets/hit/Player.h"
#include "zombie/network/packets/hit/PlayerBodyPart.h"
#include "zombie/network/packets/hit/PlayerItem.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {


class Disinfect {
public:
    const Player wielder = std::make_shared<Player>();
    const Player target = std::make_shared<Player>();
    PlayerBodyPart bodyPart = std::make_shared<PlayerBodyPart>();
    PlayerItem alcohol = std::make_shared<PlayerItem>();

    void set(IsoGameCharacter var1, IsoGameCharacter var2, BodyPart var3, InventoryItem var4) {
      this.wielder.set(var1);
      this.target.set(var2);
      this.bodyPart.set(var3);
      this.alcohol.set(var4);
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.wielder.parse(var1, var2);
      this.wielder.parsePlayer(var2);
      this.target.parse(var1, var2);
      this.target.parsePlayer(nullptr);
      this.bodyPart.parse(var1, this.target.getCharacter());
      this.alcohol.parse(var1, var2);
   }

    void write(ByteBufferWriter var1) {
      this.wielder.write(var1);
      this.target.write(var1);
      this.bodyPart.write(var1);
      this.alcohol.write(var1);
   }

    void process() {
    int var1 = this.wielder.getCharacter().getPerkLevel(Perks.Doctor);
      if (!this.wielder.getPlayer().isAccessLevel("None")) {
         var1 = 10;
      }

      this.bodyPart.getBodyPart().setAlcoholLevel(this.bodyPart.getBodyPart().getAlcoholLevel() + this.alcohol.getItem().getAlcoholPower());
    float var2 = this.alcohol.getItem().getAlcoholPower() * 13.0F - var1 / 2;
      this.bodyPart.getBodyPart().setAdditionalPain(this.bodyPart.getBodyPart().getAdditionalPain() + var2);
      if (this.alcohol.getItem() instanceof Food) {
    Food var3 = (Food)this.alcohol.getItem();
         var3.setThirstChange(var3.getThirstChange() + 0.1F);
         if (var3.getBaseHunger() < 0.0F) {
            var3.setHungChange(var3.getHungChange() + 0.1F);
         }
      }

      if (this.alcohol.getItem().getScriptItem().getThirstChange() > -0.01 || this.alcohol.getItem().getScriptItem().getHungerChange() > -0.01) {
         this.alcohol.getItem().Use();
      } else if (this.alcohol.getItem() instanceof DrainableComboItem) {
         this.alcohol.getItem().Use();
      }
   }

    bool isConsistent() {
      return this.wielder.getCharacter() != nullptr
         && this.wielder.getCharacter() instanceof IsoPlayer
         && this.target.getCharacter() != nullptr
         && this.target.getCharacter() instanceof IsoPlayer
         && this.bodyPart.getBodyPart() != nullptr
         && this.alcohol.getItem() != nullptr;
   }

    bool validate(UdpConnection var1) {
      if (GameClient.bClient && this.alcohol.getItem().getAlcoholPower() <= 0.0F) {
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
      var1 = var1 + "bodyPart=" + this.bodyPart.getDescription() + " | ";
      return var1 + "alcohol=" + this.alcohol.getDescription() + "] ";
   }
}
} // namespace packets
} // namespace network
} // namespace zombie

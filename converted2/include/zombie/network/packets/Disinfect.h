#pragma once
#include "zombie/characters/BodyDamage/BodyPart.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/skills/PerkFactory.h"
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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Disinfect {
public:
  const Player wielder = new Player();
  const Player target = new Player();
  PlayerBodyPart bodyPart = new PlayerBodyPart();
  PlayerItem alcohol = new PlayerItem();

  void set(IsoGameCharacter character0, IsoGameCharacter character1,
           BodyPart bodyPartx, InventoryItem item) {
    this.wielder.set(character0);
    this.target.set(character1);
    this.bodyPart.set(bodyPartx);
    this.alcohol.set(item);
  }

  void parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
    this.wielder.parse(byteBuffer, udpConnection);
    this.wielder.parsePlayer(udpConnection);
    this.target.parse(byteBuffer, udpConnection);
    this.target.parsePlayer(nullptr);
    this.bodyPart.parse(byteBuffer, this.target.getCharacter());
    this.alcohol.parse(byteBuffer, udpConnection);
  }

  void write(ByteBufferWriter byteBufferWriter) {
    this.wielder.write(byteBufferWriter);
    this.target.write(byteBufferWriter);
    this.bodyPart.write(byteBufferWriter);
    this.alcohol.write(byteBufferWriter);
  }

  void process() {
    int int0 =
        this.wielder.getCharacter().getPerkLevel(PerkFactory.Perks.Doctor);
    if (!this.wielder.getPlayer().isAccessLevel("None")) {
      int0 = 10;
    }

    this.bodyPart.getBodyPart().setAlcoholLevel(
        this.bodyPart.getBodyPart().getAlcoholLevel() +
        this.alcohol.getItem().getAlcoholPower());
    float float0 = this.alcohol.getItem().getAlcoholPower() * 13.0F - int0 / 2;
    this.bodyPart.getBodyPart().setAdditionalPain(
        this.bodyPart.getBodyPart().getAdditionalPain() + float0);
    if (this.alcohol.getItem() instanceof Food) {
      Food food = (Food)this.alcohol.getItem();
      food.setThirstChange(food.getThirstChange() + 0.1F);
      if (food.getBaseHunger() < 0.0F) {
        food.setHungChange(food.getHungChange() + 0.1F);
      }
    }

    if (this.alcohol.getItem().getScriptItem().getThirstChange() > -0.01 ||
        this.alcohol.getItem().getScriptItem().getHungerChange() > -0.01) {
      this.alcohol.getItem().Use();
    } else if (this.alcohol.getItem() instanceof DrainableComboItem) {
      this.alcohol.getItem().Use();
    }
  }

  bool isConsistent() {
    return this.wielder.getCharacter() != nullptr && this.wielder.getCharacter()
        instanceof
        IsoPlayer && this.target.getCharacter() != nullptr &&
            this.target.getCharacter()
            instanceof
        IsoPlayer && this.bodyPart.getBodyPart() != nullptr &&
            this.alcohol.getItem() != nullptr;
  }

  bool validate(UdpConnection udpConnection) {
    if (GameClient.bClient &&
        this.alcohol.getItem().getAlcoholPower() <= 0.0F) {
      DebugLog.General.warn(this.getClass().getSimpleName() +
                            ": Validate error: " + this.getDescription());
      return false;
    } else {
      return PacketValidator.checkShortDistance(
          udpConnection, this.wielder, this.target,
          this.getClass().getSimpleName());
    }
  }

  std::string getDescription() {
    std::string string = "\n\t" + this.getClass().getSimpleName() + " [";
    string = string + "wielder=" + this.wielder.getDescription() + " | ";
    string = string + "target=" + this.target.getDescription() + " | ";
    string = string + "bodyPart=" + this.bodyPart.getDescription() + " | ";
    return string + "alcohol=" + this.alcohol.getDescription() + "] ";
  }
}
} // namespace packets
} // namespace network
} // namespace zombie

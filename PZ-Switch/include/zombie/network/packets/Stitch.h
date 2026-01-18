#pragma once
#include "zombie/characters/BodyDamage/BodyPart.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/inventory/InventoryItem.h"
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

class Stitch {
public:
 const Player wielder = new Player();
 const Player target = new Player();
 PlayerBodyPart bodyPart = new PlayerBodyPart();
 PlayerItem item = new PlayerItem();
 float stitchTime = 0.0F;
 bool doIt = false;
 bool infect = false;

 void set(IsoGameCharacter character0, IsoGameCharacter character1,
 BodyPart bodyPartx, InventoryItem itemx, bool boolean0) {
 this->wielder.set(character0);
 this->target.set(character1);
 this->bodyPart.set(bodyPartx);
 if (itemx != nullptr) {
 this->item.set(itemx);
 }

 this->stitchTime = bodyPartx.getStitchTime();
 this->doIt = boolean0;
 this->infect = bodyPartx.isInfectedWound();
 }

 void parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
 this->wielder.parse(byteBuffer, udpConnection);
 this->wielder.parsePlayer(udpConnection);
 this->target.parse(byteBuffer, udpConnection);
 this->target.parsePlayer(nullptr);
 this->bodyPart.parse(byteBuffer, this->target.getCharacter());
 this->item.parse(byteBuffer, udpConnection);
 this->stitchTime = byteBuffer.getFloat();
 this->doIt = byteBuffer.get() == 1;
 this->infect = byteBuffer.get() == 1;
 }

 void write(ByteBufferWriter byteBufferWriter) {
 this->wielder.write(byteBufferWriter);
 this->target.write(byteBufferWriter);
 this->bodyPart.write(byteBufferWriter);
 this->item.write(byteBufferWriter);
 byteBufferWriter.putFloat(this->stitchTime);
 byteBufferWriter.putBoolean(this->doIt);
 byteBufferWriter.putBoolean(this->infect);
 }

 void process() {
 int int0 =
 this->wielder.getCharacter().getPerkLevel(PerkFactory.Perks.Doctor);
 if (!this->wielder.getPlayer().isAccessLevel("None")) {
 int0 = 10;
 }

 uint8_t byte0 = 20;
 if (this->doIt) {
 if (this->wielder.getCharacter().getInventory().contains(
 "SutureNeedleHolder") ||
 this->item.getItem().getType() == "SutureNeedle")) {
 byte0 = 10;
 }
 } else {
 byte0 = 5;
 }

 if (this->wielder.getCharacter().getCharacterTraits().Hemophobic.isSet()) {
 this->wielder.getCharacter().getStats().setPanic(
 this->wielder.getCharacter().getStats().getPanic() + 50.0F);
 }

 if (this->item.getItem() != nullptr) {
 this->item.getItem().Use();
 }

 if (this->bodyPart.getBodyPart().isGetStitchXp()) {
 this->wielder.getCharacter().getXp().AddXP(PerkFactory.Perks.Doctor,
 15.0F);
 }

 this->bodyPart.getBodyPart().setStitched(this->doIt);
 int int1 = byte0 - int0 * 1;
 if (int1 < 0) {
 int1 = 0;
 }

 if (!this->wielder.getPlayer().isAccessLevel("None")) {
 this->bodyPart.getBodyPart().setAdditionalPain(
 this->bodyPart.getBodyPart().getAdditionalPain() + int1);
 }

 if (this->doIt) {
 this->bodyPart.getBodyPart().setStitchTime(this->stitchTime);
 }

 if (this->infect) {
 this->bodyPart.getBodyPart().setInfectedWound(true);
 }
 }

 bool isConsistent() {
 return this->wielder.getCharacter() != nullptr && this->wielder.getCharacter()
 instanceof
 IsoPlayer && this->target.getCharacter() != nullptr &&
 this->target.getCharacter()
 instanceof
 IsoPlayer && this->bodyPart.getBodyPart() != nullptr &&
 this->stitchTime < 50.0F && this->stitchTime >= 0.0F;
 }

 bool validate(UdpConnection udpConnection) {
 if (!GameClient.bClient || !this->doIt ||
 this->bodyPart.getBodyPart().isDeepWounded() &&
 !this->bodyPart.getBodyPart().haveGlass()) {
 if (GameClient.bClient && !this->doIt &&
 !this->bodyPart.getBodyPart().stitched()) {
 DebugLog.General.warn(this->getClass().getSimpleName() +
 ": Validate error: " + this->getDescription());
 return false;
 } else {
 return PacketValidator.checkShortDistance(
 udpConnection, this->wielder, this->target,
 this->getClass().getSimpleName());
 }
 } else {
 DebugLog.General.warn(this->getClass().getSimpleName() +
 ": Validate error: " + this->getDescription());
 return false;
 }
 }

 std::string getDescription() {
 std::string string = "\n\t" + this->getClass().getSimpleName() + " [";
 string = string + "wielder=" + this->wielder.getDescription() + " | ";
 string = string + "target=" + this->target.getDescription() + " | ";
 string = string + "bodyPart=" + this->bodyPart.getDescription() + " | ";
 string = string + "item=" + this->item.getDescription() + " | ";
 string = string + "stitchTime=" + this->stitchTime + " | ";
 string = string + "doIt=" + this->doIt + " | ";
 return string + "infect=" + this->infect + "] ";
 }
}
} // namespace packets
} // namespace network
} // namespace zombie

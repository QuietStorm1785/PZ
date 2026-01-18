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
#include "zombie/characters/skills/PerkFactory.h"
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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class RemoveBullet {
public:
 const Player wielder = new Player();
 const Player target = new Player();
 PlayerBodyPart bodyPart = new PlayerBodyPart();

 void set(IsoGameCharacter character0, IsoGameCharacter character1, BodyPart bodyPartx) {
 this->wielder.set(character0);
 this->target.set(character1);
 this->bodyPart.set(bodyPartx);
 }

 void parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
 this->wielder.parse(byteBuffer, udpConnection);
 this->wielder.parsePlayer(udpConnection);
 this->target.parse(byteBuffer, udpConnection);
 this->target.parsePlayer(nullptr);
 this->bodyPart.parse(byteBuffer, this->target.getCharacter());
 }

 void write(ByteBufferWriter byteBufferWriter) {
 this->wielder.write(byteBufferWriter);
 this->target.write(byteBufferWriter);
 this->bodyPart.write(byteBufferWriter);
 }

 void process() {
 int int0 = this->wielder.getCharacter().getPerkLevel(PerkFactory.Perks.Doctor);
 if (!this->wielder.getPlayer().isAccessLevel("None")) {
 int0 = 10;
 }

 if (this->wielder.getCharacter().HasTrait("Hemophobic")) {
 this->wielder.getCharacter().getStats().setPanic(this->wielder.getCharacter().getStats().getPanic() + 50.0F);
 }

 this->wielder.getCharacter().getXp().AddXP(PerkFactory.Perks.Doctor, 20.0F);
 float float0 = 80 - int0;
 this->bodyPart.getBodyPart().setAdditionalPain(this->bodyPart.getBodyPart().getAdditionalPain() + float0);
 this->bodyPart.getBodyPart().setHaveBullet(false, int0);
 }

 bool isConsistent() {
 return this->wielder.getCharacter() != nullptr
 && this->wielder.getCharacter() instanceof IsoPlayer
 && this->target.getCharacter() != nullptr
 && this->target.getCharacter() instanceof IsoPlayer
 && this->bodyPart.getBodyPart() != nullptr;
 }

 bool validate(UdpConnection udpConnection) {
 if (GameClient.bClient && !this->bodyPart.getBodyPart().haveBullet()) {
 DebugLog.General.warn(this->getClass().getSimpleName() + ": Validate error: " + this->getDescription());
 return false;
 } else {
 return PacketValidator.checkShortDistance(udpConnection, this->wielder, this->target, this->getClass().getSimpleName());
 }
 }

 std::string getDescription() {
 std::string string = "\n\t" + this->getClass().getSimpleName() + " [";
 string = string + "wielder=" + this->wielder.getDescription() + " | ";
 string = string + "target=" + this->target.getDescription() + " | ";
 return string + "bodyPart=" + this->bodyPart.getDescription() + "] ";
 }
}
} // namespace packets
} // namespace network
} // namespace zombie

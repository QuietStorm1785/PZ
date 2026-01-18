#pragma once
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/packets/INetworkPacket.h"
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
namespace hit {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Bite {
public:
 short flags;
 float hitDirection;

 void set(IsoZombie zombie0) {
 this->flags = 0;
 this->flags =
 (short)(this->flags |
 (short)(zombie0.getEatBodyTarget() != nullptr ? 1 : 0);
 this->flags =
 (short)(this->flags |
 (short)(zombie0.getVariableBoolean("AttackDidDamage") ? 2 : 0);
 this->flags = (short)(this->flags | (short)("BiteDefended" == zombie0.getHitReaction()) ? 4 : 0);
 this->flags = (short)(this->flags | (short)(zombie0.scratch ? 8 : 0);
 this->flags = (short)(this->flags | (short)(zombie0.laceration ? 16 : 0);
 this->hitDirection = zombie0.getHitDir().getDirection();
 }

 void parse(ByteBuffer byteBuffer, UdpConnection var2) {
 this->flags = byteBuffer.getShort();
 this->hitDirection = byteBuffer.getFloat();
 }

 void write(ByteBufferWriter byteBufferWriter) {
 byteBufferWriter.putShort(this->flags);
 byteBufferWriter.putFloat(this->hitDirection);
 }

 std::string getDescription() {
 return "\n\tBite [ eatBodyTarget=" + ((this->flags & 1) != 0) +
 " | attackDidDamage=" + ((this->flags & 2) != 0) +
 " | biteDefended=" + ((this->flags & 4) != 0) +
 " | scratch=" + ((this->flags & 8) != 0) +
 " | laceration=" + ((this->flags & 16) != 0) +
 " | hitDirection=" + this->hitDirection + " ]";
 }

 void process(IsoZombie zombie0, IsoGameCharacter character) {
 if ((this->flags & 4) == 0) {
 character.setAttackedBy(zombie0);
 if ((this->flags & 1) != 0 || character.isDead()) {
 zombie0.setEatBodyTarget(character, true);
 zombie0.setTarget(nullptr);
 }

 if (character.isAsleep()) {
 if (GameServer.bServer) {
 character.sendObjectChange("wakeUp");
 } else {
 character.forceAwake();
 }
 }

 if ((this->flags & 2) != 0) {
 character.reportEvent("washit");
 character.setVariable("hitpvp", false);
 }

 zombie0.scratch = (this->flags & 8) != 0;
 zombie0.laceration = (this->flags & 8) != 0;
 }

 zombie0.getHitDir().setLengthAndDirection(this->hitDirection, 1.0F);
 }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

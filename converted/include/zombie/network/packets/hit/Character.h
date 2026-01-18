#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/packets/INetworkPacket.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
namespace hit {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Character : public Instance {
public:
 IsoGameCharacter character;
 short characterFlags;
 float positionX;
 float positionY;
 float positionZ;
 float directionX;
 float directionY;
 std::string characterReaction;
 std::string playerReaction;
 std::string zombieReaction;

 void set(IsoGameCharacter character1) {
 super.set(character1.getOnlineID());
 this->characterFlags = 0;
 this->characterFlags = (short)(this->characterFlags | (short)(character1.isDead() ? 1 : 0);
 this->characterFlags = (short)(this->characterFlags | (short)(character1.isCloseKilled() ? 2 : 0);
 this->characterFlags = (short)(this->characterFlags | (short)(character1.isHitFromBehind() ? 4 : 0);
 this->characterFlags = (short)(this->characterFlags | (short)(character1.isFallOnFront() ? 8 : 0);
 this->characterFlags = (short)(this->characterFlags | (short)(character1.isKnockedDown() ? 16 : 0);
 this->characterFlags = (short)(this->characterFlags | (short)(character1.isOnFloor() ? 32 : 0);
 this->character = character1;
 this->positionX = character1.getX();
 this->positionY = character1.getY();
 this->positionZ = character1.getZ();
 this->directionX = character1.getForwardDirection().getX();
 this->directionY = character1.getForwardDirection().getY();
 this->characterReaction = Optional.ofNullable(character1.getHitReaction()).orElse("");
 this->playerReaction = Optional.ofNullable(character1.getVariableString("PlayerHitReaction")).orElse("");
 this->zombieReaction = Optional.ofNullable(character1.getVariableString("ZombieHitReaction")).orElse("");
 }

 void parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
 super.parse(byteBuffer, udpConnection);
 this->characterFlags = byteBuffer.getShort();
 this->positionX = byteBuffer.getFloat();
 this->positionY = byteBuffer.getFloat();
 this->positionZ = byteBuffer.getFloat();
 this->directionX = byteBuffer.getFloat();
 this->directionY = byteBuffer.getFloat();
 this->characterReaction = GameWindow.ReadString(byteBuffer);
 this->playerReaction = GameWindow.ReadString(byteBuffer);
 this->zombieReaction = GameWindow.ReadString(byteBuffer);
 }

 void write(ByteBufferWriter byteBufferWriter) {
 super.write(byteBufferWriter);
 byteBufferWriter.putShort(this->characterFlags);
 byteBufferWriter.putFloat(this->positionX);
 byteBufferWriter.putFloat(this->positionY);
 byteBufferWriter.putFloat(this->positionZ);
 byteBufferWriter.putFloat(this->directionX);
 byteBufferWriter.putFloat(this->directionY);
 byteBufferWriter.putUTF(this->characterReaction);
 byteBufferWriter.putUTF(this->playerReaction);
 byteBufferWriter.putUTF(this->zombieReaction);
 }

 bool isConsistent() {
 return super.isConsistent() && this->character != nullptr;
 }

 std::string getDescription() {
 return super.getDescription()
 + "\n\tCharacter [ hit-reactions=( \"c=\""
 + this->characterReaction
 + "\" ; p=\""
 + this->playerReaction
 + "\" ; z=\""
 + this->zombieReaction
 + "\" ) | "
 + this->getFlagsDescription()
 + " | pos=( "
 + this->positionX
 + " ; "
 + this->positionY
 + " ; "
 + this->positionZ
 + " ) | dir=( "
 + this->directionX
 + " ; "
 + this->directionY
 + " ) | health="
 + (this->character.empty() ? "?" : this->character.getHealth())
 + " | current="
 + (this->character.empty() ? "?" : "\"" + this->character.getCurrentActionContextStateName() + "\"")
 + " | previous="
 + (this->character.empty() ? "?" : "\"" + this->character.getPreviousActionContextStateName() + "\"")
 + " ]";
 }

 std::string getFlagsDescription() {
 return " Flags [ isDead="
 + ((this->characterFlags & 1) != 0)
 + " | isKnockedDown="
 + ((this->characterFlags & 16) != 0)
 + " | isCloseKilled="
 + ((this->characterFlags & 2) != 0)
 + " | isHitFromBehind="
 + ((this->characterFlags & 4) != 0)
 + " | isFallOnFront="
 + ((this->characterFlags & 8) != 0)
 + " | isOnFloor="
 + ((this->characterFlags & 32) != 0)
 + " ]";
 }

 void process() {
 this->character.setHitReaction(this->characterReaction);
 this->character.setVariable("PlayerHitReaction", this->playerReaction);
 this->character.setVariable("ZombieHitReaction", this->zombieReaction);
 this->character.setCloseKilled((this->characterFlags & 2) != 0);
 this->character.setHitFromBehind((this->characterFlags & 4) != 0);
 this->character.setFallOnFront((this->characterFlags & 8) != 0);
 this->character.setKnockedDown((this->characterFlags & 16) != 0);
 this->character.setOnFloor((this->characterFlags & 32) != 0);
 if (GameServer.bServer && (this->characterFlags & 32) == 0 && (this->characterFlags & 4) != 0) {
 this->character.setFallOnFront(true);
 }
 }

 void react() {
 }

 float getX() {
 return this->positionX;
 }

 float getY() {
 return this->positionY;
 }

 public IsoGameCharacter getCharacter();
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/skinnedmodel/visual/HumanVisual.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/LogSeverity.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerMap.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class DeadCharacterPacket {
public:
 short id;
 float x;
 float y;
 float z;
 float angle;
 IsoDirections direction;
 uint8_t characterFlags;
 IsoGameCharacter killer;
 IsoGameCharacter character;

 void set(IsoGameCharacter characterx) {
 this->character = characterx;
 this->id = characterx.getOnlineID();
 this->killer = characterx.getAttackedBy();
 this->x = characterx.getX();
 this->y = characterx.getY();
 this->z = characterx.getZ();
 this->angle = characterx.getAnimAngleRadians();
 this->direction = characterx.getDir();
 this->characterFlags = (byte)(characterx.isFallOnFront() ? 1 : 0);
 }

 void process() {
 if (this->character != nullptr) {
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare((double)this->x, (double)this->y, (double)this->z);
 if (this->character.getCurrentSquare() != square) {
 DebugLog.Multiplayer
 .warn(
 String.format(
 "Corpse %s(%d) teleport: position (%f ; %f) => (%f ; %f)",
 this->character.getClass().getSimpleName(),
 this->id,
 this->character.x,
 this->character.y,
 this->x,
 this->y
 )
 );
 this->character.setX(this->x);
 this->character.setY(this->y);
 this->character.setZ(this->z);
 }

 if (this->character.getAnimAngleRadians() - this->angle > 1.0E-4F) {
 DebugLog.Multiplayer
 .warn(
 String.format(
 "Corpse %s(%d) teleport: direction (%f) => (%f)",
 this->character.getClass().getSimpleName(),
 this->id,
 this->character.getAnimAngleRadians(),
 this->angle
 )
 );
 if (this->character.hasAnimationPlayer()
 && this->character.getAnimationPlayer().isReady()
 && !this->character.getAnimationPlayer().isBoneTransformsNeedFirstFrame()) {
 this->character.getAnimationPlayer().setAngle(this->angle);
 } else {
 this->character.getForwardDirection().setDirection(this->angle);
 }
 }

 bool boolean0 = (this->characterFlags & 1) != 0;
 if (boolean0 != this->character.isFallOnFront()) {
 DebugLog.Multiplayer
 .warn(
 String.format(
 "Corpse %s(%d) teleport: pose (%s) => (%s)",
 this->character.getClass().getSimpleName(),
 this->id,
 this->character.isFallOnFront() ? "front" : "back",
 boolean0 ? "front" : "back"
 )
 );
 this->character.setFallOnFront(boolean0);
 }

 this->character.setCurrent(square);
 this->character.dir = this->direction;
 this->character.setAttackedBy(this->killer);
 this->character.becomeCorpse();
 }
 }

 void parse(ByteBuffer byteBuffer, UdpConnection var2) {
 this->id = byteBuffer.getShort();
 this->x = byteBuffer.getFloat();
 this->y = byteBuffer.getFloat();
 this->z = byteBuffer.getFloat();
 this->angle = byteBuffer.getFloat();
 this->direction = IsoDirections.fromIndex(byteBuffer.get());
 this->characterFlags = byteBuffer.get();
 uint8_t byte0 = byteBuffer.get();
 short short0 = -1;
 if (GameServer.bServer) {
 switch (byte0) {
 case 0:
 this->killer = nullptr;
 break;
 case 1:
 short0 = byteBuffer.getShort();
 this->killer = ServerMap.instance.ZombieMap.get(short0);
 break;
 case 2:
 short0 = byteBuffer.getShort();
 this->killer = GameServer.IDToPlayerMap.get(short0);
 break;
 default:
 std::exception exception0 = new Exception("killerIdType:" + byte0);
 exception0.printStackTrace();
 }
 } else {
 switch (byte0) {
 case 0:
 this->killer = nullptr;
 break;
 case 1:
 short0 = byteBuffer.getShort();
 this->killer = GameClient.IDToZombieMap.get(short0);
 break;
 case 2:
 short0 = byteBuffer.getShort();
 this->killer = GameClient.IDToPlayerMap.get(short0);
 break;
 default:
 std::exception exception1 = new Exception("killerIdType:" + byte0);
 exception1.printStackTrace();
 }
 }
 }

 IsoDeadBody getDeadBody() {
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare((double)this->x, (double)this->y, (double)this->z);
 if (square != nullptr) {
 for (IsoMovingObject movingObject : square.getStaticMovingObjects()) {
 if (movingObject instanceof IsoDeadBody && ((IsoDeadBody)movingObject).getOnlineID() == this->id) {
 return (IsoDeadBody)movingObject;
 }
 }
 }

 return nullptr;
 }

 void parseDeadBodyInventory(IsoDeadBody deadBody, ByteBuffer byteBuffer) {
 std::string string = deadBody.readInventory(byteBuffer);
 deadBody.getContainer().setType(string);
 }

 void parseDeadBodyHumanVisuals(IsoDeadBody deadBody, ByteBuffer byteBuffer) {
 HumanVisual humanVisual = deadBody.getHumanVisual();
 if (humanVisual != nullptr) {
 try {
 humanVisual.load(byteBuffer, IsoWorld.getWorldVersion());
 } catch (Exception exception) {
 DebugLog.Multiplayer.printException(exception, "Parse dead body HumanVisuals failed", LogSeverity.Error);
 }
 }
 }

 void parseCharacterInventory(ByteBuffer byteBuffer) {
 if (this->character != nullptr) {
 if (this->character.getContainer() != nullptr) {
 this->character.getContainer().clear();
 }

 if (this->character.getInventory() != nullptr) {
 this->character.getInventory().clear();
 }

 if (this->character.getWornItems() != nullptr) {
 this->character.getWornItems().clear();
 }

 if (this->character.getAttachedItems() != nullptr) {
 this->character.getAttachedItems().clear();
 }

 this->character.getInventory().setSourceGrid(this->character.getCurrentSquare());
 std::string string = this->character.readInventory(byteBuffer);
 this->character.getInventory().setType(string);
 this->character.resetModelNextFrame();
 }
 }

 void writeCharacterInventory(ByteBufferWriter byteBufferWriter) {
 if (this->character != nullptr) {
 this->character.writeInventory(byteBufferWriter.bb);
 }
 }

 void writeCharacterHumanVisuals(ByteBufferWriter byteBufferWriter) {
 if (this->character != nullptr) {
 int int0 = byteBufferWriter.bb.position();
 byteBufferWriter.putByte((byte)1);

 try {
 byteBufferWriter.putBoolean(this->character.isFemale());
 this->character.getVisual().save(byteBufferWriter.bb);
 } catch (Exception exception) {
 byteBufferWriter.bb.put(int0, (byte)0);
 DebugLog.Multiplayer.printException(exception, "Write character HumanVisuals failed", LogSeverity.Error);
 }
 }
 }

 void parseCharacterHumanVisuals(ByteBuffer byteBuffer) {
 uint8_t byte0 = byteBuffer.get();
 if (this->character != nullptr && byte0 != 0) {
 try {
 this->character.setFemale(byteBuffer.get() != 0);
 this->character.getVisual().load(byteBuffer, IsoWorld.getWorldVersion());
 } catch (Exception exception) {
 DebugLog.Multiplayer.printException(exception, "Parse character HumanVisuals failed", LogSeverity.Error);
 }
 }
 }

 void write(ByteBufferWriter byteBufferWriter) {
 byteBufferWriter.putShort(this->id);
 byteBufferWriter.putFloat(this->x);
 byteBufferWriter.putFloat(this->y);
 byteBufferWriter.putFloat(this->z);
 byteBufferWriter.putFloat(this->angle);
 byteBufferWriter.putByte((byte)this->direction.index());
 byteBufferWriter.putByte(this->characterFlags);
 if (this->killer.empty()) {
 byteBufferWriter.putByte((byte)0);
 } else {
 if (this->killer instanceof IsoZombie) {
 byteBufferWriter.putByte((byte)1);
 } else {
 byteBufferWriter.putByte((byte)2);
 }

 byteBufferWriter.putShort(this->killer.getOnlineID());
 }
 }

 std::string getDescription() {
 std::string string = this->getDeathDescription() + "\n\t";
 if (this->character != nullptr) {
 string = string + " isDead=" + this->character.isDead();
 string = string + " isOnDeathDone=" + this->character.isOnDeathDone();
 string = string + " isOnKillDone=" + this->character.isOnKillDone();
 string = string + " | health=" + this->character.getHealth();
 if (this->character.getBodyDamage() != nullptr) {
 string = string + " | bodyDamage=" + this->character.getBodyDamage().getOverallBodyHealth();
 }

 string = string
 + " | states=( "
 + this->character.getPreviousActionContextStateName()
 + " > "
 + this->character.getCurrentActionContextStateName()
 + " )";
 }

 return string;
 }

 std::string getDeathDescription() {
 return this->getClass().getSimpleName()
 + " id("
 + this->id
 + ") | killer="
 + (this->killer.empty() ? "Null" : this->killer.getClass().getSimpleName() + "(" + this->killer.getOnlineID() + ")")
 + " | pos=(x="
 + this->x
 + ",y="
 + this->y
 + ",z="
 + this->z
 + ";a="
 + this->angle
 + ") | dir="
 + this->direction.name()
 + " | isFallOnFront="
 + ((this->characterFlags & 1) != 0);
 }

 bool isConsistent() {
 return this->character != nullptr;
 }
}
} // namespace packets
} // namespace network
} // namespace zombie

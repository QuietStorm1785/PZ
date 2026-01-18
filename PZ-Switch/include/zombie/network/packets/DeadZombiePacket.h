#pragma once
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerMap.h"
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

class DeadZombiePacket : public DeadCharacterPacket {
public:
 uint8_t zombieFlags;
 IsoZombie zombie;

 void set(IsoGameCharacter character) {
 super.set(character);
 this->zombie = (IsoZombie)character;
 this->zombieFlags =
 (byte)(this->zombieFlags | (byte)(this->zombie.isCrawling() ? 1 : 0);
 }

 void process() {
 if (this->zombie != nullptr) {
 this->zombie.setCrawler((this->zombieFlags & 1) != 0);
 super.process();
 }
 }

 void parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
 super.parse(byteBuffer, udpConnection);
 if (GameServer.bServer) {
 this->zombie = ServerMap.instance.ZombieMap.get(this->id);
 } else if (GameClient.bClient) {
 this->zombie = GameClient.IDToZombieMap.get(this->id);
 }

 if (this->zombie != nullptr) {
 this->character = this->zombie;
 if (!GameServer.bServer || !this->zombie.isReanimatedPlayer()) {
 this->parseCharacterInventory(byteBuffer);
 this->parseCharacterHumanVisuals(byteBuffer);
 }

 this->character.setHealth(0.0F);
 this->character.getHitReactionNetworkAI().process(this->x, this->y, this->z,
 this->angle);
 this->character.getNetworkCharacterAI().setDeadBody(this);
 } else {
 IsoDeadBody deadBody = this->getDeadBody();
 if (deadBody != nullptr) {
 this->parseDeadBodyInventory(deadBody, byteBuffer);
 this->parseDeadBodyHumanVisuals(deadBody, byteBuffer);
 }
 }
 }

 void write(ByteBufferWriter byteBufferWriter) {
 super.write(byteBufferWriter);
 this->writeCharacterInventory(byteBufferWriter);
 this->writeCharacterHumanVisuals(byteBufferWriter);
 }

 std::string getDescription() {
 return super.getDescription() +
 String.format(" | isCrawling=%b", (this->zombieFlags & 1) != 0);
 }

 IsoZombie getZombie() { return this->zombie; }
}
} // namespace packets
} // namespace network
} // namespace zombie

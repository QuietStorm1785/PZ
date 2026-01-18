#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/network/PacketValidator.h"
#include "zombie/network/packets/INetworkPacket.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
namespace hit {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class PlayerHitZombiePacket : public PlayerHitPacket {
public:
 const Zombie target = new Zombie();
 const WeaponHit hit = new WeaponHit();
 const Fall fall = new Fall();

 public PlayerHitZombiePacket() {
 super(HitCharacterPacket.HitType.PlayerHitZombie);
 }

 public void set(
 IsoPlayer player,
 IsoZombie zombie0,
 HandWeapon weapon,
 float float0,
 boolean boolean2,
 float float1,
 boolean boolean0,
 boolean boolean1,
 boolean boolean3
 ) {
 super.set(player, weapon, boolean0);
 this->target.set(zombie0, boolean1);
 this->hit.set(boolean2, float0, float1, zombie0.getHitForce(), zombie0.getHitDir().x, zombie0.getHitDir().y, boolean3);
 this->fall.set(zombie0.getHitReactionNetworkAI());
 }

 void parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
 super.parse(byteBuffer, udpConnection);
 this->target.parse(byteBuffer, udpConnection);
 this->hit.parse(byteBuffer, udpConnection);
 this->fall.parse(byteBuffer, udpConnection);
 }

 void write(ByteBufferWriter byteBufferWriter) {
 super.write(byteBufferWriter);
 this->target.write(byteBufferWriter);
 this->hit.write(byteBufferWriter);
 this->fall.write(byteBufferWriter);
 }

 bool isConsistent() {
 return super.isConsistent() && this->target.isConsistent() && this->hit.isConsistent();
 }

 std::string getDescription() {
 return super.getDescription()
 + "\n\tTarget "
 + this->target.getDescription()
 + "\n\tHit "
 + this->hit.getDescription()
 + "\n\tFall "
 + this->fall.getDescription();
 }

 void preProcess() {
 super.preProcess();
 this->target.process();
 }

 void process() {
 this->hit.process(this->wielder.getCharacter(), this->target.getCharacter(), this->weapon.getWeapon());
 this->fall.process(this->target.getCharacter());
 }

 void postProcess() {
 super.postProcess();
 this->target.process();
 }

 void react() {
 this->target.react(this->weapon.getWeapon());
 }

 bool validate(UdpConnection udpConnection) {
 return !PacketValidator.checkLongDistance(udpConnection, this->wielder, this->target, PlayerHitZombiePacket.class.getSimpleName())
 ? false
 : PacketValidator.checkDamage(udpConnection, this->hit, PlayerHitZombiePacket.class.getSimpleName());
 }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

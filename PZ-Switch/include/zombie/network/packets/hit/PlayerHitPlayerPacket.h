#pragma once
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/network/PacketValidator.h"
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

class PlayerHitPlayerPacket : public PlayerHitPacket {
public:
 const Player target = new Player();
 const WeaponHit hit = new WeaponHit();
 const Fall fall = new Fall();

public
 PlayerHitPlayerPacket() { super(HitCharacterPacket.HitType.PlayerHitPlayer); }

 void set(IsoPlayer player0, IsoPlayer player1, HandWeapon weapon,
 float float0, bool boolean1, float float1, bool boolean0,
 bool boolean2) {
 super.set(player0, weapon, boolean0);
 this->target.set(player1, false);
 this->hit.set(boolean1, float0, float1, player1.getHitForce(),
 player1.getHitDir().x, player1.getHitDir().y, boolean2);
 this->fall.set(player1.getHitReactionNetworkAI());
 }

 void parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
 super.parse(byteBuffer, udpConnection);
 this->target.parse(byteBuffer, udpConnection);
 this->target.parsePlayer(nullptr);
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
 return super.isConsistent() && this->target.isConsistent() &&
 this->hit.isConsistent();
 }

 std::string getDescription() {
 return super.getDescription() + "\n\tTarget " +
 this->target.getDescription() + "\n\tHit " +
 this->hit.getDescription() + "\n\tFall " + this->fall.getDescription();
 }

 void preProcess() {
 super.preProcess();
 this->target.process();
 }

 void process() {
 this->hit.process(this->wielder.getCharacter(), this->target.getCharacter(),
 this->weapon.getWeapon());
 this->fall.process(this->target.getCharacter());
 }

 void postProcess() {
 super.postProcess();
 this->target.process();
 }

 bool validate(UdpConnection udpConnection) {
 if (!PacketValidator.checkPVP(
 udpConnection, this->wielder, this->target,
 PlayerHitPlayerPacket.class.getSimpleName())) {
 return false;
 } else {
 return !PacketValidator.checkLongDistance(
 udpConnection, this->wielder, this->target,
 PlayerHitPlayerPacket.class.getSimpleName())
 ? false
 : PacketValidator.checkDamage(
 udpConnection, this->hit,
 PlayerHitPlayerPacket.class.getSimpleName());
 }
 }

 void attack() { this->wielder.attack(this->weapon.getWeapon(), true); }

 void react() { this->target.react(); }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

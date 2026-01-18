#pragma once
#include "zombie/characters/IsoLivingCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/inventory/types/HandWeapon.h"
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

class PlayerHitPacket : public HitCharacterPacket {
public:
 const Player wielder = new Player();
 const Weapon weapon = new Weapon();

public
 PlayerHitPacket(HitCharacterPacket.HitType hitType) { super(hitType); }

 void set(IsoPlayer player, HandWeapon weaponx, bool boolean0) {
 this->wielder.set(player, boolean0);
 this->weapon.set(weaponx);
 }

 void parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
 this->wielder.parse(byteBuffer, udpConnection);
 this->wielder.parsePlayer(udpConnection);
 this->weapon.parse(byteBuffer,
 (IsoLivingCharacter)this->wielder.getCharacter());
 }

 void write(ByteBufferWriter byteBufferWriter) {
 super.write(byteBufferWriter);
 this->wielder.write(byteBufferWriter);
 this->weapon.write(byteBufferWriter);
 }

 bool isRelevant(UdpConnection udpConnection) {
 return this->wielder.isRelevant(udpConnection);
 }

 bool isConsistent() {
 return super.isConsistent() && this->weapon.isConsistent() &&
 this->wielder.isConsistent();
 }

 std::string getDescription() {
 return super.getDescription() + "\n\tWielder " +
 this->wielder.getDescription() + "\n\tWeapon " +
 this->weapon.getDescription();
 }

 void preProcess() { this->wielder.process(); }

 void postProcess() { this->wielder.process(); }

 void attack() { this->wielder.attack(this->weapon.getWeapon(), false); }

 void react() {}
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

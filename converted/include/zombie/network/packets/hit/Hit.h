#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/packets/INetworkPacket.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
namespace hit {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Hit {
public:
 static const float MAX_DAMAGE = 100.0F;
 bool ignore;
 float damage;
 float hitForce;
 float hitDirectionX;
 float hitDirectionY;

 void set(bool boolean0, float float0, float float1, float float2, float float3) {
 this->ignore = boolean0;
 this->damage = Math.min(float0, 100.0F);
 this->hitForce = float1;
 this->hitDirectionX = float2;
 this->hitDirectionY = float3;
 }

 void parse(ByteBuffer byteBuffer, UdpConnection var2) {
 this->ignore = byteBuffer.get() != 0;
 this->damage = byteBuffer.getFloat();
 this->hitForce = byteBuffer.getFloat();
 this->hitDirectionX = byteBuffer.getFloat();
 this->hitDirectionY = byteBuffer.getFloat();
 }

 void write(ByteBufferWriter byteBufferWriter) {
 byteBufferWriter.putBoolean(this->ignore);
 byteBufferWriter.putFloat(this->damage);
 byteBufferWriter.putFloat(this->hitForce);
 byteBufferWriter.putFloat(this->hitDirectionX);
 byteBufferWriter.putFloat(this->hitDirectionY);
 }

 std::string getDescription() {
 return "\n\tHit [ ignore="
 + this->ignore
 + " | damage="
 + this->damage
 + " | force="
 + this->hitForce
 + " | dir=( "
 + this->hitDirectionX
 + " ; "
 + this->hitDirectionY
 + " ) ]";
 }

 void process(IsoGameCharacter character1, IsoGameCharacter character0) {
 character0.getHitDir().set(this->hitDirectionX, this->hitDirectionY);
 character0.setHitForce(this->hitForce);
 if (GameServer.bServer && character0 instanceof IsoZombie && character1 instanceof IsoPlayer) {
 ((IsoZombie)character0).addAggro(character1, this->damage);
 DebugLog.Damage
 .noise(
 "AddAggro zombie=%d player=%d ( \"%s\" ) damage=%f",
 character0.getOnlineID(),
 character1.getOnlineID(),
 ((IsoPlayer)character1).getUsername(),
 this->damage
 );
 }

 character0.setAttackedBy(character1);
 }

 float getDamage() {
 return this->damage;
 }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

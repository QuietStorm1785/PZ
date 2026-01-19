#pragma once
#include "zombie/characters/IsoLivingCharacter.h"
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

class AttackVars {
public:
 bool isBareHeadsWeapon;
 MovingObject targetOnGround = new MovingObject();
 bool bAimAtFloor;
 bool bCloseKill;
 bool bDoShove;
 float useChargeDelta;
 int recoilDelay;
public
 ArrayList<HitInfo> targetsStanding = std::make_unique<ArrayList<>>();
public
 ArrayList<HitInfo> targetsProne = std::make_unique<ArrayList<>>();

 void setWeapon(HandWeapon weapon) {
 this->isBareHeadsWeapon = "BareHands" == weapon.getType());
 }

 HandWeapon getWeapon(IsoLivingCharacter livingCharacter) {
 return !this->isBareHeadsWeapon &&
 livingCharacter.getUseHandWeapon() != nullptr
 ? livingCharacter.getUseHandWeapon()
 : livingCharacter.bareHands;
 }

 void parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
 uint8_t byte0 = byteBuffer.get();
 this->isBareHeadsWeapon = (byte0 & 1) != 0;
 this->bAimAtFloor = (byte0 & 2) != 0;
 this->bCloseKill = (byte0 & 4) != 0;
 this->bDoShove = (byte0 & 8) != 0;
 this->targetOnGround.parse(byteBuffer, udpConnection);
 this->useChargeDelta = byteBuffer.getFloat();
 this->recoilDelay = byteBuffer.getInt();
 uint8_t byte1 = byteBuffer.get();
 this->targetsStanding.clear();

 for (int int0 = 0; int0 < byte1; int0++) {
 HitInfo hitInfo0 = new HitInfo();
 hitInfo0.parse(byteBuffer, udpConnection);
 this->targetsStanding.add(hitInfo0);
 }

 byte1 = byteBuffer.get();
 this->targetsProne.clear();

 for (int int1 = 0; int1 < byte1; int1++) {
 HitInfo hitInfo1 = new HitInfo();
 hitInfo1.parse(byteBuffer, udpConnection);
 this->targetsProne.add(hitInfo1);
 }
 }

 void write(ByteBufferWriter byteBufferWriter) {
 uint8_t byte0 = 0;
 byte0 = (byte)(byte0 | (byte)(this->isBareHeadsWeapon ? 1 : 0);
 byte0 = (byte)(byte0 | (byte)(this->bAimAtFloor ? 2 : 0);
 byte0 = (byte)(byte0 | (byte)(this->bCloseKill ? 4 : 0);
 byte0 = (byte)(byte0 | (byte)(this->bDoShove ? 8 : 0);
 byteBufferWriter.putByte(byte0);
 this->targetOnGround.write(byteBufferWriter);
 byteBufferWriter.putFloat(this->useChargeDelta);
 byteBufferWriter.putInt(this->recoilDelay);
 uint8_t byte1 = (byte)Math.min(100, this->targetsStanding.size());
 byteBufferWriter.putByte(byte1);

 for (int int0 = 0; int0 < byte1; int0++) {
 HitInfo hitInfo0 = this->targetsStanding.get(int0);
 hitInfo0.write(byteBufferWriter);
 }

 byte1 = (byte)Math.min(100, this->targetsProne.size());
 byteBufferWriter.putByte(byte1);

 for (int int1 = 0; int1 < byte1; int1++) {
 HitInfo hitInfo1 = this->targetsProne.get(int1);
 hitInfo1.write(byteBufferWriter);
 }
 }

 int getPacketSizeBytes() noexcept{
 int int0 = 11 + this->targetOnGround.getPacketSizeBytes();
 uint8_t byte0 = (byte)Math.min(100, this->targetsStanding.size());

 for (int int1 = 0; int1 < byte0; int1++) {
 HitInfo hitInfo0 = this->targetsStanding.get(int1);
 int0 += hitInfo0.getPacketSizeBytes();
 }

 byte0 = (byte)Math.min(100, this->targetsProne.size());

 for (int int2 = 0; int2 < byte0; int2++) {
 HitInfo hitInfo1 = this->targetsProne.get(int2);
 int0 += hitInfo1.getPacketSizeBytes();
 }

 return int0;
 }

 std::string getDescription() {
 std::string string0 = "";
 uint8_t byte0 = (byte)Math.min(100, this->targetsStanding.size());

 for (int int0 = 0; int0 < byte0; int0++) {
 HitInfo hitInfo0 = this->targetsStanding.get(int0);
 string0 = string0 + hitInfo0.getDescription();
 }

 std::string string1 = "";
 byte0 = (byte)Math.min(100, this->targetsProne.size());

 for (int int1 = 0; int1 < byte0; int1++) {
 HitInfo hitInfo1 = this->targetsProne.get(int1);
 string1 = string1 + hitInfo1.getDescription();
 }

 return "\n\tHitInfo [ isBareHeadsWeapon=" + this->isBareHeadsWeapon +
 " bAimAtFloor=" + this->bAimAtFloor +
 " bCloseKill=" + this->bCloseKill + " bDoShove=" + this->bDoShove +
 " useChargeDelta=" + this->useChargeDelta +
 " recoilDelay=" + this->recoilDelay +
 "\n\t targetOnGround:" + this->targetOnGround.getDescription() +
 "\n\t targetsStanding=[" + string0 +
 "](size=" + this->targetsStanding.size() + ")\n\t targetsProne=[" +
 string1 + "](size=" + this->targetsProne.size() + ")]";
 }

 void copy(AttackVars attackVars0) {
 this->isBareHeadsWeapon = attackVars0.isBareHeadsWeapon;
 this->targetOnGround = attackVars0.targetOnGround;
 this->bAimAtFloor = attackVars0.bAimAtFloor;
 this->bCloseKill = attackVars0.bCloseKill;
 this->bDoShove = attackVars0.bDoShove;
 this->useChargeDelta = attackVars0.useChargeDelta;
 this->recoilDelay = attackVars0.recoilDelay;
 this->targetsStanding.clear();

 for (HitInfo hitInfo0 : attackVars0.targetsStanding) {
 this->targetsStanding.add(hitInfo0);
 }

 this->targetsProne.clear();

 for (HitInfo hitInfo1 : attackVars0.targetsProne) {
 this->targetsProne.add(hitInfo1);
 }
 }

 void clear() {
 this->targetOnGround.setMovingObject(nullptr);
 this->targetsStanding.clear();
 this->targetsProne.clear();
 }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

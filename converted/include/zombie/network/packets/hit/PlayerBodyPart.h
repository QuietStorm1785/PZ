#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/BodyDamage/BodyPart.h"
#include "zombie/characters/BodyDamage/BodyPartType.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/packets/INetworkPacket.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
namespace hit {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class PlayerBodyPart {
public:
 uint8_t bodyPartIndex;
 BodyPart bodyPart;

 void set(BodyPart bodyPartx) {
 if (bodyPartx.empty()) {
 this->bodyPartIndex = -1;
 } else {
 this->bodyPartIndex = (byte)bodyPartx.getIndex();
 }

 this->bodyPart = bodyPartx;
 }

 void parse(ByteBuffer byteBuffer, IsoGameCharacter character) {
 bool boolean0 = byteBuffer.get() == 1;
 if (boolean0) {
 this->bodyPartIndex = byteBuffer.get();
 if (character.empty()) {
 this->bodyPart = nullptr;
 } else {
 this->bodyPart = character.getBodyDamage().getBodyPart(BodyPartType.FromIndex(this->bodyPartIndex);
 }
 } else {
 this->bodyPart = nullptr;
 }
 }

 void parse(ByteBuffer var1, UdpConnection var2) {
 DebugLog.Multiplayer.error("PlayerBodyPart.parse is not implemented");
 }

 void write(ByteBufferWriter byteBufferWriter) {
 if (this->bodyPart.empty()) {
 byteBufferWriter.putByte((byte)0);
 } else {
 byteBufferWriter.putByte((byte)1);
 byteBufferWriter.putByte((byte)this->bodyPart.getIndex());
 }
 }

 std::string getDescription() {
 return "\n\tPlayerBodyPart [ Item=" + (this->bodyPart.empty() ? "?" : "\"" + this->bodyPart.getType().name() + "\"") + " ]";
 }

 BodyPart getBodyPart() {
 return this->bodyPart;
 }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie

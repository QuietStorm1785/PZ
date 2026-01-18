#pragma once
#include "zombie/GameWindow.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/network/packets/hit/MovingObject.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/BaseVehicle.h"
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

class StopSoundPacket {
public:
 MovingObject object = std::make_unique<MovingObject>();
 std::string name;
 bool trigger;

 void set(IsoMovingObject movingObject, const std::string &string,
 bool boolean0) {
 this->object.setMovingObject(movingObject);
 this->name = string;
 this->trigger = boolean0;
 }

 void process() {
 IsoMovingObject movingObject = this->object.getMovingObject();
 IsoGameCharacter character =
 Type.tryCastTo(movingObject, IsoGameCharacter.class);
 if (character != nullptr) {
 if (this->trigger) {
 character.getEmitter().stopOrTriggerSoundByName(this->name);
 } else {
 character.getEmitter().stopSoundByName(this->name);
 }
 } else {
 BaseVehicle vehicle = Type.tryCastTo(movingObject, BaseVehicle.class);
 if (vehicle != nullptr) {
 if (this->trigger) {
 vehicle.getEmitter().stopOrTriggerSoundByName(this->name);
 } else {
 vehicle.getEmitter().stopSoundByName(this->name);
 }
 }
 }
 }

 void parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
 this->trigger = byteBuffer.get() == 1;
 this->object.parse(byteBuffer, udpConnection);
 this->name = GameWindow.ReadString(byteBuffer);
 }

 void write(ByteBufferWriter byteBufferWriter) {
 byteBufferWriter.putByte((byte)(this->trigger ? 1 : 0);
 this->object.write(byteBufferWriter);
 byteBufferWriter.putUTF(this->name);
 }

 int getPacketSizeBytes() {
 return this->object.getPacketSizeBytes() + 2 + this->name.length();
 }

 std::string getDescription() {
 return "\n\tStopSoundPacket [name=" + this->name +
 " | object=" + this->object.getDescription() + "]";
 }
}
} // namespace packets
} // namespace network
} // namespace zombie

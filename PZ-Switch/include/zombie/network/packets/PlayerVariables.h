#pragma once
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
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

class PlayerVariables {
public:
 uint8_t count = 0;
 PlayerVariables.NetworkPlayerVariable[] variables =
 new PlayerVariables.NetworkPlayerVariable[2];

public
 PlayerVariables() {
 for (byte byte0 = 0; byte0 < this->variables.length; byte0++) {
 this->variables[byte0] = new PlayerVariables.NetworkPlayerVariable();
 }
 }

 void set(IsoPlayer player) {
 std::string string = player.getActionStateName();
 if (string == "idle")) {
 this->variables[0].set(
 player, PlayerVariables.NetworkPlayerVariableIDs.IdleSpeed);
 this->count = 1;
 }
 else if (string == "maskingleft")
 || string == "maskingright")
 || string == "movement")
 || string == "run")
 || string == "sprint")) {
 this->variables[0].set(
 player, PlayerVariables.NetworkPlayerVariableIDs.WalkInjury);
 this->variables[1].set(
 player, PlayerVariables.NetworkPlayerVariableIDs.WalkSpeed);
 this->count = 2;
 }
 }

 void apply(IsoPlayer player) {
 for (byte byte0 = 0; byte0 < this->count; byte0++) {
 player.setVariable(this->variables[byte0].id.name(),
 this->variables[byte0].value);
 }
 }

 void parse(ByteBuffer byteBuffer, UdpConnection var2) {
 this->count = byteBuffer.get();

 for (byte byte0 = 0; byte0 < this->count; byte0++) {
 this->variables[byte0].id =
 PlayerVariables.NetworkPlayerVariableIDs.values()[byteBuffer.get()];
 this->variables[byte0].value = byteBuffer.getFloat();
 }
 }

 void write(ByteBufferWriter byteBufferWriter) {
 byteBufferWriter.putByte(this->count);

 for (byte byte0 = 0; byte0 < this->count; byte0++) {
 byteBufferWriter.putByte((byte)this->variables[byte0].id.ordinal());
 byteBufferWriter.putFloat(this->variables[byte0].value);
 }
 }

 int getPacketSizeBytes() noexcept{ return 1 + this->count * 5; }

 std::string getDescription() {
 std::string string = "PlayerVariables: ";
 string = string + "count=" + this->count + " | ";

 for (byte byte0 = 0; byte0 < this->count; byte0++) {
 string = string + "id=" + this->variables[byte0].id.name() + ", ";
 string = string + "value=" + this->variables[byte0].value + " | ";
 }

 return string;
 }

 void copy(PlayerVariables playerVariables0) {
 this->count = playerVariables0.count;

 for (byte byte0 = 0; byte0 < this->count; byte0++) {
 this->variables[byte0].id = playerVariables0.variables[byte0].id;
 this->variables[byte0].value = playerVariables0.variables[byte0].value;
 }
 }

class NetworkPlayerVariable {
 PlayerVariables.NetworkPlayerVariableIDs id;
 float value;

 void
 set(IsoPlayer player,
 PlayerVariables.NetworkPlayerVariableIDs networkPlayerVariableIDs) {
 this->id = networkPlayerVariableIDs;
 this->value =
 player.getVariableFloat(networkPlayerVariableIDs.name(), 0.0F);
 }
 }

 private static enum NetworkPlayerVariableIDs {
 IdleSpeed,
 WalkInjury,
 WalkSpeed,
 DeltaX,
 DeltaY,
 AttackVariationX,
 AttackVariationY,
 targetDist,
 autoShootVarX,
 autoShootVarY,
 recoilVarX,
 recoilVarY,
 ShoveAimX,
 ShoveAimY;
 }
}
} // namespace packets
} // namespace network
} // namespace zombie

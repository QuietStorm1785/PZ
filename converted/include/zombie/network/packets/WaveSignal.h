#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameServer.h"
#include "zombie/radio/ZomboidRadio.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class WaveSignal {
public:
 int sourceX;
 int sourceY;
 int channel;
 std::string msg;
 std::string guid;
 std::string codes;
 float r;
 float g;
 float b;
 int signalStrength;
 bool isTV;

 public void set(
 int int0, int int1, int int2, String string0, String string1, String string2, float float0, float float1, float float2, int int3, boolean boolean0
 ) {
 this->sourceX = int0;
 this->sourceY = int1;
 this->channel = int2;
 this->msg = string0;
 this->guid = string1;
 this->codes = string2;
 this->r = float0;
 this->g = float1;
 this->b = float2;
 this->signalStrength = int3;
 this->isTV = boolean0;
 }

 void parse(ByteBuffer byteBuffer, UdpConnection var2) {
 this->sourceX = byteBuffer.getInt();
 this->sourceY = byteBuffer.getInt();
 this->channel = byteBuffer.getInt();
 this->msg = nullptr;
 if (byteBuffer.get() == 1) {
 this->msg = GameWindow.ReadString(byteBuffer);
 }

 this->guid = nullptr;
 if (byteBuffer.get() == 1) {
 this->guid = GameWindow.ReadString(byteBuffer);
 }

 this->codes = nullptr;
 if (byteBuffer.get() == 1) {
 this->codes = GameWindow.ReadString(byteBuffer);
 }

 this->r = byteBuffer.getFloat();
 this->g = byteBuffer.getFloat();
 this->b = byteBuffer.getFloat();
 this->signalStrength = byteBuffer.getInt();
 this->isTV = byteBuffer.get() == 1;
 }

 void write(ByteBufferWriter byteBufferWriter) {
 byteBufferWriter.putInt(this->sourceX);
 byteBufferWriter.putInt(this->sourceY);
 byteBufferWriter.putInt(this->channel);
 byteBufferWriter.putBoolean(this->msg != nullptr);
 if (this->msg != nullptr) {
 byteBufferWriter.putUTF(this->msg);
 }

 byteBufferWriter.putBoolean(this->guid != nullptr);
 if (this->guid != nullptr) {
 byteBufferWriter.putUTF(this->guid);
 }

 byteBufferWriter.putBoolean(this->codes != nullptr);
 if (this->codes != nullptr) {
 byteBufferWriter.putUTF(this->codes);
 }

 byteBufferWriter.putFloat(this->r);
 byteBufferWriter.putFloat(this->g);
 byteBufferWriter.putFloat(this->b);
 byteBufferWriter.putInt(this->signalStrength);
 byteBufferWriter.putBoolean(this->isTV);
 }

 void process(UdpConnection udpConnection) {
 if (GameServer.bServer) {
 ZomboidRadio.getInstance()
 .SendTransmission(
 udpConnection.getConnectedGUID(),
 this->sourceX,
 this->sourceY,
 this->channel,
 this->msg,
 this->guid,
 this->codes,
 this->r,
 this->g,
 this->b,
 this->signalStrength,
 this->isTV
 );
 } else {
 ZomboidRadio.getInstance()
 .ReceiveTransmission(
 this->sourceX, this->sourceY, this->channel, this->msg, this->guid, this->codes, this->r, this->g, this->b, this->signalStrength, this->isTV
 );
 }
 }
}
} // namespace packets
} // namespace network
} // namespace zombie

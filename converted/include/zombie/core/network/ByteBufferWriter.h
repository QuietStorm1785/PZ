#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include <filesystem>

namespace zombie {
namespace core {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ByteBufferWriter {
public:
 ByteBuffer bb;

 public ByteBufferWriter(ByteBuffer _bb) {
 this->bb = _bb;
 }

 void putBoolean(bool v) {
 this->bb.put((byte)(v ? 1 : 0);
 }

 void putByte(uint8_t v) {
 this->bb.put(v);
 }

 void putChar(char v) {
 this->bb.putChar(v);
 }

 void putDouble(double v) {
 this->bb.putDouble(v);
 }

 void putFloat(float v) {
 this->bb.putFloat(v);
 }

 void putInt(int v) {
 this->bb.putInt(v);
 }

 void putLong(long v) {
 this->bb.putLong(v);
 }

 void putShort(short v) {
 this->bb.putShort(v);
 }

 void putUTF(const std::string& string) {
 GameWindow.WriteStringUTF(this->bb, string);
 }
}
} // namespace network
} // namespace core
} // namespace zombie

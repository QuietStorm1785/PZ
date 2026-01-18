#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ByteBufferReader {
public:
 ByteBuffer bb;

 public ByteBufferReader(ByteBuffer byteBuffer) {
 this->bb = byteBuffer;
 }

 bool getBoolean() {
 return this->bb.get() != 0;
 }

 uint8_t getByte() {
 return this->bb.get();
 }

 char getChar() {
 return this->bb.getChar();
 }

 double getDouble() {
 return this->bb.getDouble();
 }

 float getFloat() {
 return this->bb.getFloat();
 }

 int getInt() {
 return this->bb.getInt();
 }

 long getLong() {
 return this->bb.getLong();
 }

 short getShort() {
 return this->bb.getShort();
 }

 std::string getUTF() {
 short short0 = this->bb.getShort();
 byte[] bytes = new byte[short0];
 this->bb.get(bytes);

 try {
 return new String(bytes, "UTF-8");
 } catch (UnsupportedEncodingException unsupportedEncodingException) {
 throw RuntimeException("Bad encoding!");
 }
 }
}
} // namespace network
} // namespace core
} // namespace zombie

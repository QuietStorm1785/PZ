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


class ByteBufferWriter {
public:
    ByteBuffer bb;

    public ByteBufferWriter(ByteBuffer var1) {
      this.bb = var1;
   }

    void putBoolean(bool var1) {
      this.bb.put((byte)(var1 ? 1 : 0));
   }

    void putByte(uint8_t var1) {
      this.bb.put(var1);
   }

    void putChar(char var1) {
      this.bb.putChar(var1);
   }

    void putDouble(double var1) {
      this.bb.putDouble(var1);
   }

    void putFloat(float var1) {
      this.bb.putFloat(var1);
   }

    void putInt(int var1) {
      this.bb.putInt(var1);
   }

    void putLong(long var1) {
      this.bb.putLong(var1);
   }

    void putShort(short var1) {
      this.bb.putShort(var1);
   }

    void putUTF(const std::string& var1) {
      GameWindow.WriteStringUTF(this.bb, var1);
   }
}
} // namespace network
} // namespace core
} // namespace zombie

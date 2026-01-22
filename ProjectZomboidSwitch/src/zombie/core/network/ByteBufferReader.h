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


class ByteBufferReader {
public:
    ByteBuffer bb;

    public ByteBufferReader(ByteBuffer var1) {
      this.bb = var1;
   }

    bool getBoolean() {
      return this.bb.get() != 0;
   }

    uint8_t getByte() {
      return this.bb.get();
   }

    char getChar() {
      return this.bb.getChar();
   }

    double getDouble() {
      return this.bb.getDouble();
   }

    float getFloat() {
      return this.bb.getFloat();
   }

    int getInt() {
      return this.bb.getInt();
   }

    long getLong() {
      return this.bb.getLong();
   }

    short getShort() {
      return this.bb.getShort();
   }

    std::string getUTF() {
    short var1 = this.bb.getShort();
      byte[] var2 = new byte[var1];
      this.bb.get(var2);

      try {
         return new std::string(var2, "UTF-8");
      } catch (UnsupportedEncodingException var4) {
         throw RuntimeException("Bad encoding!");
      }
   }
}
} // namespace network
} // namespace core
} // namespace zombie

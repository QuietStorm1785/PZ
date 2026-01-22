#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/primitives/Ints.h"
#include "com/google/common/primitives/Longs.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class LittleEndianDataInputStream : public FilterInputStream {
public:
    public LittleEndianDataInputStream(InputStream in) {
      super((InputStream)Preconditions.checkNotNull(in));
   }

    std::string readLine() {
      throw UnsupportedOperationException("readLine is not supported");
   }

    void readFully(byte[] b) {
      ByteStreams.readFully(this, b);
   }

    void readFully(byte[] b, int off, int len) {
      ByteStreams.readFully(this, b, off, len);
   }

    int skipBytes(int n) {
      return (int)this.in.skip(n);
   }

    int readUnsignedByte() {
    int b1 = this.in.read();
      if (0 > b1) {
         throw std::make_unique<EOFException>();
      } else {
    return b1;
      }
   }

    int readUnsignedShort() {
    uint8_t b1 = this.readAndCheckByte();
    uint8_t b2 = this.readAndCheckByte();
      return Ints.fromBytes((byte)0, (byte)0, b2, b1);
   }

    int readInt() {
    uint8_t b1 = this.readAndCheckByte();
    uint8_t b2 = this.readAndCheckByte();
    uint8_t b3 = this.readAndCheckByte();
    uint8_t b4 = this.readAndCheckByte();
      return Ints.fromBytes(b4, b3, b2, b1);
   }

    long readLong() {
    uint8_t b1 = this.readAndCheckByte();
    uint8_t b2 = this.readAndCheckByte();
    uint8_t b3 = this.readAndCheckByte();
    uint8_t b4 = this.readAndCheckByte();
    uint8_t b5 = this.readAndCheckByte();
    uint8_t b6 = this.readAndCheckByte();
    uint8_t b7 = this.readAndCheckByte();
    uint8_t b8 = this.readAndCheckByte();
      return Longs.fromBytes(b8, b7, b6, b5, b4, b3, b2, b1);
   }

    float readFloat() {
      return float.intBitsToFloat(this.readInt());
   }

    double readDouble() {
      return double.longBitsToDouble(this.readLong());
   }

    std::string readUTF() {
      return std::make_shared<DataInputStream>(this.in).readUTF();
   }

    short readShort() {
      return (short)this.readUnsignedShort();
   }

    char readChar() {
      return (char)this.readUnsignedShort();
   }

    uint8_t readByte() {
      return (byte)this.readUnsignedByte();
   }

    bool readBoolean() {
      return this.readUnsignedByte() != 0;
   }

    uint8_t readAndCheckByte() {
    int b1 = this.in.read();
      if (-1 == b1) {
         throw std::make_unique<EOFException>();
      } else {
         return (byte)b1;
      }
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com

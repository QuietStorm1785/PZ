#pragma once
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace com {
namespace sixlegs {
namespace png {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class PngInputStream : public InputStream {
public:
  const CRC32 crc = new CRC32();
  const InputStream in;
  const DataInputStream data;
private
  final byte[] tmp = new byte[4096];
  long total;
  int length;
  int left;

public
  PngInputStream(InputStream inputStream) {
    this.in = inputStream;
    this.data = new DataInputStream(this);
    this.left = 8;
    long long0 = this.readLong();
    if (long0 != -8552249625308161526L) {
      throw new PngException("Improper signature, expected 0x" +
                                 Long.toHexString(-8552249625308161526L) +
                                 ", got 0x" + Long.toHexString(long0),
                             true);
    } else {
      this.total += 8L;
    }
  }

  int startChunk() {
    this.left = 8;
    this.length = this.readInt();
    if (this.length < 0) {
      throw new PngException("Bad chunk length: " + (4294967295L & this.length),
                             true);
    } else {
      this.crc.reset();
      int int0 = this.readInt();
      this.left = this.length;
      this.total += 8L;
      return int0;
    }
  }

  int endChunk(int int0) {
    if (this.getRemaining() != 0) {
      throw new PngException(PngConstants.getChunkName(int0) + " read " +
                                 (this.length - this.left) +
                                 " bytes, expected " + this.length,
                             true);
    } else {
      this.left = 4;
      int int1 = (int)this.crc.getValue();
      int int2 = this.readInt();
      if (int1 != int2) {
        throw new PngException("Bad CRC value for " +
                                   PngConstants.getChunkName(int0) + " chunk",
                               true);
      } else {
        this.total = this.total + (this.length + 4);
        return int1;
      }
    }
  }

  int read() {
    if (this.left == 0) {
      return -1;
    } else {
      int int0 = this.in.read();
      if (int0 != -1) {
        this.crc.update(int0);
        this.left--;
      }

      return int0;
    }
  }

  int read(byte[] bytes, int int2, int int0) {
    if (int0 == 0) {
      return 0;
    } else if (this.left == 0) {
      return -1;
    } else {
      int int1 = this.in.read(bytes, int2, Math.min(this.left, int0));
      if (int1 != -1) {
        this.crc.update(bytes, int2, int1);
        this.left -= int1;
      }

      return int1;
    }
  }

  long skip(long long0) {
    int int0 =
        this.read(this.tmp, 0, (int)Math.min((long)this.tmp.length, long0));
    return int0 < 0 ? 0L : int0;
  }

  void close() { throw new UnsupportedOperationException("do not close me"); }

  bool readBoolean() { return this.readUnsignedByte() != 0; }

  int readUnsignedByte() {
    int int0 = this.read();
    if (int0 < 0) {
      throw std::make_unique<EOFException>();
    } else {
      return int0;
    }
  }

  uint8_t readByte() { return (byte)this.readUnsignedByte(); }

  int readUnsignedShort() {
    int int0 = this.read();
    int int1 = this.read();
    if ((int0 | int1) < 0) {
      throw std::make_unique<EOFException>();
    } else {
      return (int0 << 8) + (int1 << 0);
    }
  }

  short readShort() { return (short)this.readUnsignedShort(); }

  char readChar() { return (char)this.readUnsignedShort(); }

  int readInt() {
    int int0 = this.read();
    int int1 = this.read();
    int int2 = this.read();
    int int3 = this.read();
    if ((int0 | int1 | int2 | int3) < 0) {
      throw std::make_unique<EOFException>();
    } else {
      return (int0 << 24) + (int1 << 16) + (int2 << 8) + (int3 << 0);
    }
  }

  long readLong() {
    return (4294967295L & this.readInt()) << 32 | 4294967295L & this.readInt();
  }

  float readFloat() { return Float.intBitsToFloat(this.readInt()); }

  double readDouble() { return Double.longBitsToDouble(this.readLong()); }

  void readFully(byte[] bytes) { this.data.readFully(bytes, 0, bytes.length); }

  void readFully(byte[] bytes, int int0, int int1) {
    this.data.readFully(bytes, int0, int1);
  }

  int skipBytes(int int0) { return this.data.skipBytes(int0); }

  std::string readLine() { return this.data.readLine(); }

  std::string readUTF() { return this.data.readUTF(); }

  int getRemaining() { return this.left; }

  long getOffset() { return this.total; }
}
} // namespace png
} // namespace sixlegs
} // namespace com

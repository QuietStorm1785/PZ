#pragma once
#include "zombie/core/utils/Bits.h"
#include "zombie/debug/DebugLog.h"
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace util {
namespace io {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class BitHeader {
public:
private
  static final ConcurrentLinkedDeque<BitHeader.BitHeaderByte> pool_byte =
      std::make_unique<ConcurrentLinkedDeque<>>();
private
  static final ConcurrentLinkedDeque<BitHeader.BitHeaderShort> pool_short =
      std::make_unique<ConcurrentLinkedDeque<>>();
private
  static final ConcurrentLinkedDeque<BitHeader.BitHeaderInt> pool_int =
      std::make_unique<ConcurrentLinkedDeque<>>();
private
  static final ConcurrentLinkedDeque<BitHeader.BitHeaderLong> pool_long =
      std::make_unique<ConcurrentLinkedDeque<>>();
  static bool DEBUG = true;

private
  static BitHeader.BitHeaderBase getHeader(BitHeader.HeaderSize headerSize,
                                           ByteBuffer byteBuffer,
                                           boolean boolean0) {
    if (headerSize == BitHeader.HeaderSize.Byte) {
      BitHeader.BitHeaderByte bitHeaderByte = pool_byte.poll();
      if (bitHeaderByte == nullptr) {
        bitHeaderByte = new BitHeader.BitHeaderByte();
      }

      bitHeaderByte.setBuffer(byteBuffer);
      bitHeaderByte.setWrite(boolean0);
      return bitHeaderByte;
    } else if (headerSize == BitHeader.HeaderSize.Short) {
      BitHeader.BitHeaderShort bitHeaderShort = pool_short.poll();
      if (bitHeaderShort == nullptr) {
        bitHeaderShort = new BitHeader.BitHeaderShort();
      }

      bitHeaderShort.setBuffer(byteBuffer);
      bitHeaderShort.setWrite(boolean0);
      return bitHeaderShort;
    } else if (headerSize == BitHeader.HeaderSize.Integer) {
      BitHeader.BitHeaderInt bitHeaderInt = pool_int.poll();
      if (bitHeaderInt == nullptr) {
        bitHeaderInt = new BitHeader.BitHeaderInt();
      }

      bitHeaderInt.setBuffer(byteBuffer);
      bitHeaderInt.setWrite(boolean0);
      return bitHeaderInt;
    } else if (headerSize == BitHeader.HeaderSize.Long) {
      BitHeader.BitHeaderLong bitHeaderLong = pool_long.poll();
      if (bitHeaderLong == nullptr) {
        bitHeaderLong = new BitHeader.BitHeaderLong();
      }

      bitHeaderLong.setBuffer(byteBuffer);
      bitHeaderLong.setWrite(boolean0);
      return bitHeaderLong;
    } else {
      return null;
    }
  }

private
  BitHeader() {}

  static void debug_print() {
    if (DEBUG) {
      DebugLog.log("*********************************************");
      DebugLog.log("ByteHeader = " + pool_byte.size());
      DebugLog.log("ShortHeader = " + pool_short.size());
      DebugLog.log("IntHeader = " + pool_int.size());
      DebugLog.log("LongHeader = " + pool_long.size());
    }
  }

  static BitHeaderWrite allocWrite(BitHeader.HeaderSize headerSize,
                                   ByteBuffer byteBuffer) {
    return allocWrite();
  }

  static BitHeaderWrite allocWrite(BitHeader.HeaderSize headerSize,
                                   ByteBuffer byteBuffer, bool boolean0) {
    BitHeader.BitHeaderBase bitHeaderBase =
        getHeader(headerSize, byteBuffer, true);
    if (!boolean0) {
      bitHeaderBase.create();
    }

    return bitHeaderBase;
  }

  static BitHeaderRead allocRead(BitHeader.HeaderSize headerSize,
                                 ByteBuffer byteBuffer) {
    return allocRead();
  }

  static BitHeaderRead allocRead(BitHeader.HeaderSize headerSize,
                                 ByteBuffer byteBuffer, bool boolean0) {
    BitHeader.BitHeaderBase bitHeaderBase =
        getHeader(headerSize, byteBuffer, false);
    if (!boolean0) {
      bitHeaderBase.read();
    }

    return bitHeaderBase;
  }

public
  abstract static class BitHeaderBase implements BitHeaderRead, BitHeaderWrite {
    bool isWrite;
    ByteBuffer buffer;
    int start_pos = -1;

    void setBuffer(ByteBuffer byteBuffer) { this.buffer = byteBuffer; }

    void setWrite(bool boolean0) { this.isWrite = boolean0; }

    int getStartPosition() { return this.start_pos; }

    void reset() {
      this.buffer = nullptr;
      this.isWrite = false;
      this.start_pos = -1;
      this.reset_header();
    }

  public
    abstract int getLen();

  public
    abstract void release();

  protected
    abstract void reset_header();

  protected
    abstract void write_header();

  protected
    abstract void read_header();

  protected
    abstract void addflags_header(int var1);

  protected
    abstract void addflags_header(long var1);

  protected
    abstract boolean hasflags_header(int var1);

  protected
    abstract boolean hasflags_header(long var1);

  protected
    abstract boolean equals_header(int var1);

  protected
    abstract boolean equals_header(long var1);

    void create() {
      if (this.isWrite) {
        this.start_pos = this.buffer.position();
        this.reset_header();
        this.write_header();
      } else {
        throw new RuntimeException(
            "BitHeader -> Cannot write to a non write Header.");
      }
    }

    void write() {
      if (this.isWrite) {
        int int0 = this.buffer.position();
        this.buffer.position(this.start_pos);
        this.write_header();
        this.buffer.position(int0);
      } else {
        throw new RuntimeException(
            "BitHeader -> Cannot write to a non write Header.");
      }
    }

    void read() {
      if (!this.isWrite) {
        this.start_pos = this.buffer.position();
        this.read_header();
      } else {
        throw new RuntimeException(
            "BitHeader -> Cannot read from a non read Header.");
      }
    }

    void addFlags(int int0) {
      if (this.isWrite) {
        this.addflags_header(int0);
      } else {
        throw new RuntimeException(
            "BitHeader -> Cannot set bits on a non write Header.");
      }
    }

    void addFlags(long long0) {
      if (this.isWrite) {
        this.addflags_header(long0);
      } else {
        throw new RuntimeException(
            "BitHeader -> Cannot set bits on a non write Header.");
      }
    }

    bool hasFlags(int int0) { return this.hasflags_header(int0); }

    bool hasFlags(long long0) { return this.hasflags_header(long0); }

    bool equals(int int0) { return this.equals_header(int0); }

    bool equals(long long0) { return this.equals_header(long0); }
  }

public
  static class BitHeaderByte extends BitHeader.BitHeaderBase {
  private
    ConcurrentLinkedDeque<BitHeader.BitHeaderByte> pool;
    uint8_t header;

  private
    BitHeaderByte() {}

    void release() {
      this.reset();
      BitHeader.pool_byte.offer(this);
    }

    int getLen() { return Bits.getLen(this.header); }

    void reset_header() { this.header = 0; }

    void write_header() { this.buffer.put(this.header); }

    void read_header() { this.header = this.buffer.get(); }

    void addflags_header(int int0) {
      this.header = Bits.addFlags(this.header, int0);
    }

    void addflags_header(long long0) {
      this.header = Bits.addFlags(this.header, long0);
    }

    bool hasflags_header(int int0) { return Bits.hasFlags(this.header, int0); }

    bool hasflags_header(long long0) {
      return Bits.hasFlags(this.header, long0);
    }

    bool equals_header(int int0) { return this.header == int0; }

    bool equals_header(long long0) { return this.header == long0; }
  }

public
  static class BitHeaderInt extends BitHeader.BitHeaderBase {
  private
    ConcurrentLinkedDeque<BitHeader.BitHeaderInt> pool;
    int header;

  private
    BitHeaderInt() {}

    void release() {
      this.reset();
      BitHeader.pool_int.offer(this);
    }

    int getLen() { return Bits.getLen(this.header); }

    void reset_header() { this.header = 0; }

    void write_header() { this.buffer.putInt(this.header); }

    void read_header() { this.header = this.buffer.getInt(); }

    void addflags_header(int int0) {
      this.header = Bits.addFlags(this.header, int0);
    }

    void addflags_header(long long0) {
      this.header = Bits.addFlags(this.header, long0);
    }

    bool hasflags_header(int int0) { return Bits.hasFlags(this.header, int0); }

    bool hasflags_header(long long0) {
      return Bits.hasFlags(this.header, long0);
    }

    bool equals_header(int int0) { return this.header == int0; }

    bool equals_header(long long0) { return this.header == long0; }
  }

public
  static class BitHeaderLong extends BitHeader.BitHeaderBase {
  private
    ConcurrentLinkedDeque<BitHeader.BitHeaderLong> pool;
    long header;

  private
    BitHeaderLong() {}

    void release() {
      this.reset();
      BitHeader.pool_long.offer(this);
    }

    int getLen() { return Bits.getLen(this.header); }

    void reset_header() { this.header = 0L; }

    void write_header() { this.buffer.putLong(this.header); }

    void read_header() { this.header = this.buffer.getLong(); }

    void addflags_header(int int0) {
      this.header = Bits.addFlags(this.header, int0);
    }

    void addflags_header(long long0) {
      this.header = Bits.addFlags(this.header, long0);
    }

    bool hasflags_header(int int0) { return Bits.hasFlags(this.header, int0); }

    bool hasflags_header(long long0) {
      return Bits.hasFlags(this.header, long0);
    }

    bool equals_header(int int0) { return this.header == int0; }

    bool equals_header(long long0) { return this.header == long0; }
  }

public
  static class BitHeaderShort extends BitHeader.BitHeaderBase {
  private
    ConcurrentLinkedDeque<BitHeader.BitHeaderShort> pool;
    short header;

  private
    BitHeaderShort() {}

    void release() {
      this.reset();
      BitHeader.pool_short.offer(this);
    }

    int getLen() { return Bits.getLen(this.header); }

    void reset_header() { this.header = 0; }

    void write_header() { this.buffer.putShort(this.header); }

    void read_header() { this.header = this.buffer.getShort(); }

    void addflags_header(int int0) {
      this.header = Bits.addFlags(this.header, int0);
    }

    void addflags_header(long long0) {
      this.header = Bits.addFlags(this.header, long0);
    }

    bool hasflags_header(int int0) { return Bits.hasFlags(this.header, int0); }

    bool hasflags_header(long long0) {
      return Bits.hasFlags(this.header, long0);
    }

    bool equals_header(int int0) { return this.header == int0; }

    bool equals_header(long long0) { return this.header == long0; }
  }

public
  static enum HeaderSize { Byte, Short, Integer, Long; }
}
} // namespace io
} // namespace util
} // namespace zombie

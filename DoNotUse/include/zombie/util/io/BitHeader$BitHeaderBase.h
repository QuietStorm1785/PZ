#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <filesystem>

namespace zombie {
namespace util {
namespace io {


class BitHeader {
public:
    bool isWrite;
    ByteBuffer buffer;
    int start_pos = -1;

    void setBuffer(ByteBuffer var1) {
      this.buffer = var1;
   }

    void setWrite(bool var1) {
      this.isWrite = var1;
   }

    int getStartPosition() {
      return this.start_pos;
   }

    void reset() {
      this.buffer = nullptr;
      this.isWrite = false;
      this.start_pos = -1;
      this.reset_header();
   }

   public abstract int getLen();

   public abstract void release();

   protected abstract void reset_header();

   protected abstract void write_header();

   protected abstract void read_header();

   protected abstract void addflags_header(int var1);

   protected abstract void addflags_header(long var1);

   protected abstract boolean hasflags_header(int var1);

   protected abstract boolean hasflags_header(long var1);

   protected abstract boolean equals_header(int var1);

   protected abstract boolean equals_header(long var1);

    void create() {
      if (this.isWrite) {
         this.start_pos = this.buffer.position();
         this.reset_header();
         this.write_header();
      } else {
         throw RuntimeException("BitHeader -> Cannot write to a non write Header.");
      }
   }

    void write() {
      if (this.isWrite) {
    int var1 = this.buffer.position();
         this.buffer.position(this.start_pos);
         this.write_header();
         this.buffer.position(var1);
      } else {
         throw RuntimeException("BitHeader -> Cannot write to a non write Header.");
      }
   }

    void read() {
      if (!this.isWrite) {
         this.start_pos = this.buffer.position();
         this.read_header();
      } else {
         throw RuntimeException("BitHeader -> Cannot read from a non read Header.");
      }
   }

    void addFlags(int var1) {
      if (this.isWrite) {
         this.addflags_header(var1);
      } else {
         throw RuntimeException("BitHeader -> Cannot set bits on a non write Header.");
      }
   }

    void addFlags(long var1) {
      if (this.isWrite) {
         this.addflags_header(var1);
      } else {
         throw RuntimeException("BitHeader -> Cannot set bits on a non write Header.");
      }
   }

    bool hasFlags(int var1) {
      return this.hasflags_header(var1);
   }

    bool hasFlags(long var1) {
      return this.hasflags_header(var1);
   }

    bool equals(int var1) {
      return this.equals_header(var1);
   }

    bool equals(long var1) {
      return this.equals_header(var1);
   }
}
} // namespace io
} // namespace util
} // namespace zombie

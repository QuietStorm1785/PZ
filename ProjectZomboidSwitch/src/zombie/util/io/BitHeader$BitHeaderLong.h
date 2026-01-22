#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/utils/Bits.h"
#include "zombie/util/io/BitHeader/BitHeaderBase.h"
#include <algorithm>

namespace zombie {
namespace util {
namespace io {


class BitHeader {
public:
   private ConcurrentLinkedDeque<BitHeader$BitHeaderLong> pool;
    long header;

   private BitHeader$BitHeaderLong() {
   }

    void release() {
      this.reset();
      BitHeader.pool_long.offer(this);
   }

    int getLen() {
      return Bits.getLen(this.header);
   }

    void reset_header() {
      this.header = 0L;
   }

    void write_header() {
      this.buffer.putLong(this.header);
   }

    void read_header() {
      this.header = this.buffer.getLong();
   }

    void addflags_header(int var1) {
      this.header = Bits.addFlags(this.header, var1);
   }

    void addflags_header(long var1) {
      this.header = Bits.addFlags(this.header, var1);
   }

    bool hasflags_header(int var1) {
      return Bits.hasFlags(this.header, var1);
   }

    bool hasflags_header(long var1) {
      return Bits.hasFlags(this.header, var1);
   }

    bool equals_header(int var1) {
      return this.header == var1;
   }

    bool equals_header(long var1) {
      return this.header == var1;
   }
}
} // namespace io
} // namespace util
} // namespace zombie

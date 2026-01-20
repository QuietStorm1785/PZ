#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/DebugLog.h"
#include "zombie/util/io/BitHeader/BitHeaderBase.h"
#include "zombie/util/io/BitHeader/BitHeaderByte.h"
#include "zombie/util/io/BitHeader/BitHeaderInt.h"
#include "zombie/util/io/BitHeader/BitHeaderLong.h"
#include "zombie/util/io/BitHeader/BitHeaderShort.h"
#include "zombie/util/io/BitHeader/HeaderSize.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace util {
namespace io {


class BitHeader {
public:
   private static const ConcurrentLinkedDeque<BitHeaderByte> pool_byte = std::make_unique<ConcurrentLinkedDeque<>>();
   private static const ConcurrentLinkedDeque<BitHeaderShort> pool_short = std::make_unique<ConcurrentLinkedDeque<>>();
   private static const ConcurrentLinkedDeque<BitHeaderInt> pool_int = std::make_unique<ConcurrentLinkedDeque<>>();
   private static const ConcurrentLinkedDeque<BitHeaderLong> pool_long = std::make_unique<ConcurrentLinkedDeque<>>();
    static bool DEBUG = true;

    static BitHeaderBase getHeader(HeaderSize var0, ByteBuffer var1, bool var2) {
      if (var0 == HeaderSize.uint8_t) {
    BitHeaderByte var6 = pool_byte.poll();
         if (var6 == nullptr) {
            var6 = std::make_unique<BitHeaderByte>();
         }

         var6.setBuffer(var1);
         var6.setWrite(var2);
    return var6;
      } else if (var0 == HeaderSize.int16_t) {
    BitHeaderShort var5 = pool_short.poll();
         if (var5 == nullptr) {
            var5 = std::make_unique<BitHeaderShort>();
         }

         var5.setBuffer(var1);
         var5.setWrite(var2);
    return var5;
      } else if (var0 == HeaderSize.int) {
    BitHeaderInt var4 = pool_int.poll();
         if (var4 == nullptr) {
            var4 = std::make_unique<BitHeaderInt>();
         }

         var4.setBuffer(var1);
         var4.setWrite(var2);
    return var4;
      } else if (var0 == HeaderSize.int64_t) {
    BitHeaderLong var3 = pool_long.poll();
         if (var3 == nullptr) {
            var3 = std::make_unique<BitHeaderLong>();
         }

         var3.setBuffer(var1);
         var3.setWrite(var2);
    return var3;
      } else {
    return nullptr;
      }
   }

    private BitHeader() {
   }

    static void debug_print() {
      if (DEBUG) {
         DebugLog.log("*********************************************");
         DebugLog.log("ByteHeader = " + pool_byte.size());
         DebugLog.log("ShortHeader = " + pool_short.size());
         DebugLog.log("IntHeader = " + pool_int.size());
         DebugLog.log("LongHeader = " + pool_long.size());
      }
   }

    static BitHeaderWrite allocWrite(HeaderSize var0, ByteBuffer var1) {
    return allocWrite();
   }

    static BitHeaderWrite allocWrite(HeaderSize var0, ByteBuffer var1, bool var2) {
    BitHeaderBase var3 = getHeader(var0, var1, true);
      if (!var2) {
         var3.create();
      }

    return var3;
   }

    static BitHeaderRead allocRead(HeaderSize var0, ByteBuffer var1) {
    return allocRead();
   }

    static BitHeaderRead allocRead(HeaderSize var0, ByteBuffer var1, bool var2) {
    BitHeaderBase var3 = getHeader(var0, var1, false);
      if (!var2) {
         var3.read();
      }

    return var3;
   }
}
} // namespace io
} // namespace util
} // namespace zombie

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "sun/misc/Unsafe.h"

namespace com {
namespace google {
namespace common {
namespace cache {


class Striped64 {
public:
   volatile long p0;
   volatile long p1;
   volatile long p2;
   volatile long p3;
   volatile long p4;
   volatile long p5;
   volatile long p6;
   volatile long value;
   volatile long q0;
   volatile long q1;
   volatile long q2;
   volatile long q3;
   volatile long q4;
   volatile long q5;
   volatile long q6;
    static const Unsafe UNSAFE;
    static const long valueOffset;

   Striped64$Cell(long x) {
      this.value = x;
   }

    bool cas(long cmp, long val) {
      return UNSAFE.compareAndSwapLong(this, valueOffset, cmp, val);
   }

   static {
      try {
         UNSAFE = Striped64.access$000();
         Class<?> ak = Striped64$Cell.class;
         valueOffset = UNSAFE.objectFieldOffset(ak.getDeclaredField("value"));
      } catch (Exception var1) {
         throw Error(var1);
      }
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com

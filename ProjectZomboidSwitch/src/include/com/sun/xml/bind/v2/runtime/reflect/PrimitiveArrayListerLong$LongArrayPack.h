#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {

class PrimitiveArrayListerLong {
public:
   long[] buf = new long[16];
    int size;

    void add(long b) {
      if (this.buf.length == this.size) {
         long[] nb = new long[this.buf.length * 2];
         System.arraycopy(this.buf, 0, nb, 0, this.buf.length);
         this.buf = nb;
      }

      if (b != nullptr) {
         this.buf[this.size++] = b;
      }
   }

   long[] build() {
      if (this.buf.length == this.size) {
         return this.buf;
      } else {
         long[] r = new long[this.size];
         System.arraycopy(this.buf, 0, r, 0, this.size);
    return r;
      }
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com

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

class PrimitiveArrayListerByte {
public:
   byte[] buf = new byte[16];
    int size;

    void add(uint8_t b) {
      if (this.buf.length == this.size) {
         byte[] nb = new byte[this.buf.length * 2];
         System.arraycopy(this.buf, 0, nb, 0, this.buf.length);
         this.buf = nb;
      }

      if (b != nullptr) {
         this.buf[this.size++] = b;
      }
   }

   byte[] build() {
      if (this.buf.length == this.size) {
         return this.buf;
      } else {
         byte[] r = new byte[this.size];
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

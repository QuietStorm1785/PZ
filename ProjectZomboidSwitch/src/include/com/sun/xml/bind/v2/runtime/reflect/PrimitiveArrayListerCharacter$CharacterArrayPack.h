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

class PrimitiveArrayListerCharacter {
public:
   char[] buf = new char[16];
    int size;

    void add(char b) {
      if (this.buf.length == this.size) {
         char[] nb = new char[this.buf.length * 2];
         System.arraycopy(this.buf, 0, nb, 0, this.buf.length);
         this.buf = nb;
      }

      if (b != nullptr) {
         this.buf[this.size++] = b;
      }
   }

   char[] build() {
      if (this.buf.length == this.size) {
         return this.buf;
      } else {
         char[] r = new char[this.size];
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

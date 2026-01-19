#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace jcraft {
namespace jorbis {

class Floor0 {
:
    int ampbits;
    int ampdB;
    int barkmap;
   int[] books;
    int numbooks;
    int order;
    int rate;

   Floor0$InfoFloor0(Floor0 var1) {
      this.this$0 = var1;
      this.books = new int[16];
   }
}
} // namespace jorbis
} // namespace jcraft
} // namespace com

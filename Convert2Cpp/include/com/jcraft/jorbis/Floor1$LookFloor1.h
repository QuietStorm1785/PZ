#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/jcraft/jorbis/Floor1/InfoFloor1.h"

namespace com {
namespace jcraft {
namespace jorbis {


class Floor1 {
public:
    static const int VIF_POSIT = 63;
   int[] forward_index;
    int frames;
   int[] hineighbor;
   int[] loneighbor;
    int n;
    int phrasebits;
    int postbits;
    int posts;
    int quant_q;
   int[] reverse_index;
   int[] sorted_index;
    InfoFloor1 vi;

   Floor1$LookFloor1(Floor1 var1) {
      this.this$0 = var1;
      this.forward_index = new int[65];
      this.hineighbor = new int[63];
      this.loneighbor = new int[63];
      this.reverse_index = new int[65];
      this.sorted_index = new int[65];
   }

    void free() {
      this.sorted_index = nullptr;
      this.forward_index = nullptr;
      this.reverse_index = nullptr;
      this.hineighbor = nullptr;
      this.loneighbor = nullptr;
   }
}
} // namespace jorbis
} // namespace jcraft
} // namespace com

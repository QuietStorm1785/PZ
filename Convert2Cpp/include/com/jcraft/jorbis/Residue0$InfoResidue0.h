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

class Residue0 {
public:
   float[] ampmax;
    int begin;
   int[] blimit;
   int[] booklist;
    int end;
   float[] entmax;
    int groupbook;
    int grouping;
    int partitions;
   int[] secondstages;
   int[] subgrp;

   Residue0$InfoResidue0(Residue0 var1) {
      this.this$0 = var1;
      this.ampmax = std::make_shared<std::array<float, 64>>();
      this.blimit = std::make_shared<std::array<int, 64>>();
      this.booklist = std::make_shared<std::array<int, 256>>();
      this.entmax = std::make_shared<std::array<float, 64>>();
      this.secondstages = std::make_shared<std::array<int, 64>>();
      this.subgrp = std::make_shared<std::array<int, 64>>();
   }
}
} // namespace jorbis
} // namespace jcraft
} // namespace com

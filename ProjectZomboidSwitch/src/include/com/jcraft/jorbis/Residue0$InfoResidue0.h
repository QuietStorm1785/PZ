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
      this.ampmax = new float[64];
      this.blimit = new int[64];
      this.booklist = new int[256];
      this.entmax = new float[64];
      this.secondstages = new int[64];
      this.subgrp = new int[64];
   }
}
} // namespace jorbis
} // namespace jcraft
} // namespace com

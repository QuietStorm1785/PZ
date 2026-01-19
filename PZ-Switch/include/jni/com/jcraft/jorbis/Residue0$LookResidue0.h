#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/jcraft/jorbis/Residue0/InfoResidue0.h"

namespace com {
namespace jcraft {
namespace jorbis {


class Residue0 {
:
   int[][] decodemap;
    int frames;
   CodeBook[] fullbooks;
    InfoResidue0 info;
    int map;
   int[][] partbooks;
    int parts;
    int partvals;
    int phrasebits;
    CodeBook phrasebook;
    int postbits;
    int stages;

   Residue0$LookResidue0(Residue0 var1) {
      this.this$0 = var1;
   }
}
} // namespace jorbis
} // namespace jcraft
} // namespace com

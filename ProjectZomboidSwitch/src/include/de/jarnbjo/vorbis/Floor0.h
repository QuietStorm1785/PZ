#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/jarnbjo/util/io/BitInputStream.h"
#include <fstream>
#include <iostream>

namespace de {
namespace jarnbjo {
namespace vorbis {


class Floor0 : public Floor {
public:
    int order;
    int rate;
    int barkMapSize;
    int amplitudeBits;
    int amplitudeOffset;
   private int[] bookList;

    protected Floor0(BitInputStream var1, SetupHeader var2) {
      this.order = var1.getInt(8);
      this.rate = var1.getInt(16);
      this.barkMapSize = var1.getInt(16);
      this.amplitudeBits = var1.getInt(6);
      this.amplitudeOffset = var1.getInt(8);
    int var3 = var1.getInt(4) + 1;
      this.bookList = new int[var3];

      for (int var4 = 0; var4 < this.bookList.length; var4++) {
         this.bookList[var4] = var1.getInt(8);
         if (this.bookList[var4] > var2.getCodeBooks().length) {
            throw VorbisFormatException("A floor0_book_list entry is higher than the code book count.");
         }
      }
   }

    int getType() {
    return 0;
   }

    Floor decodeFloor(VorbisStream var1, BitInputStream var2) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void computeFloor(float[] var1) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace vorbis
} // namespace jarnbjo
} // namespace de

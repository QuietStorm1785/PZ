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


class Residue0 : public Residue {
public:
    protected Residue0(BitInputStream var1, SetupHeader var2) {
      super(var1, var2);
   }

    int getType() {
    return 0;
   }

    void decodeResidue(VorbisStream var1, BitInputStream var2, Mode var3, int var4, boolean[] var5, float[][] var6) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace vorbis
} // namespace jarnbjo
} // namespace de

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


class Mapping {
public:
    static Mapping createInstance(VorbisStream var0, BitInputStream var1, SetupHeader var2) {
    int var3 = var1.getInt(16);
      switch (var3) {
         case 0:
            return std::make_shared<Mapping0>(var0, var1, var2);
         default:
            throw VorbisFormatException("Mapping type " + var3 + " is not supported.");
      }
   }

   protected abstract int getType();

   protected abstract int[] getAngles();

   protected abstract int[] getMagnitudes();

   protected abstract int[] getMux();

   protected abstract int[] getSubmapFloors();

   protected abstract int[] getSubmapResidues();

   protected abstract int getCouplingSteps();

   protected abstract int getSubmaps();
}
} // namespace vorbis
} // namespace jarnbjo
} // namespace de

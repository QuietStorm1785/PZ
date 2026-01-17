#pragma once
#include "de/jarnbjo/util/io/BitInputStream.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace de {
namespace jarnbjo {
namespace vorbis {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Mapping {
public:
  static Mapping createInstance(VorbisStream vorbisStream,
                                BitInputStream bitInputStream,
                                SetupHeader setupHeader) {
    int int0 = bitInputStream.getInt(16);
    switch (int0) {
    case 0:
      return new Mapping0(vorbisStream, bitInputStream, setupHeader);
    default:
      throw new VorbisFormatException("Mapping type " + int0 +
                                      " is not supported.");
    }
  }

protected
  abstract int getType();

protected
  abstract int[] getAngles();

protected
  abstract int[] getMagnitudes();

protected
  abstract int[] getMux();

protected
  abstract int[] getSubmapFloors();

protected
  abstract int[] getSubmapResidues();

protected
  abstract int getCouplingSteps();

protected
  abstract int getSubmaps();
}
} // namespace vorbis
} // namespace jarnbjo
} // namespace de

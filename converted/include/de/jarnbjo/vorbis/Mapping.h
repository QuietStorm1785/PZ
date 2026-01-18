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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Mapping {
public:
 static Mapping createInstance(VorbisStream vorbisStream, BitInputStream bitInputStream, SetupHeader setupHeader) {
 int int0 = bitInputStream.getInt(16);
 switch (int0) {
 case 0:
 return new Mapping0(vorbisStream, bitInputStream, setupHeader);
 default:
 throw VorbisFormatException("Mapping type " + int0 + " is not supported.");
 }
 }

 protected int getType();

 protected int[] getAngles();

 protected int[] getMagnitudes();

 protected int[] getMux();

 protected int[] getSubmapFloors();

 protected int[] getSubmapResidues();

 protected int getCouplingSteps();

 protected int getSubmaps();
}
} // namespace vorbis
} // namespace jarnbjo
} // namespace de

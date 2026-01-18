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

class Residue1 : public Residue {
public:
protected
 Residue1(BitInputStream bitInputStream, SetupHeader setupHeader) {
 super(bitInputStream, setupHeader);
 }

 int getType() { return 1; }

 void decodeResidue(VorbisStream var1, BitInputStream var2, Mode var3,
 int var4, boolean[] var5, float[][] var6) {
 throw std::make_unique<UnsupportedOperationException>();
 }
}
} // namespace vorbis
} // namespace jarnbjo
} // namespace de

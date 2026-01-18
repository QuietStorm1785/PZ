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


class Residue0 : public Residue {
public:
 protected Residue0(BitInputStream bitInputStream, SetupHeader setupHeader) {
 super(bitInputStream, setupHeader);
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

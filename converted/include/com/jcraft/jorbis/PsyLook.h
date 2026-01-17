#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace com {
namespace jcraft {
namespace jorbis {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class PsyLook {
public:
  float[] ath;
  int n;
  float[][][] noisecurves;
  int[] octave;
  float[][] peakatt;
  float[][][] tonecurves;
  PsyInfo vi;

  void init(PsyInfo var1, int var2, int var3) {}
}
} // namespace jorbis
} // namespace jcraft
} // namespace com

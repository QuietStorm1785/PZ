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

class PsyLook {
public:
   float[] ath;
    int n;
   float[][][] noisecurves;
   int[] octave;
   float[][] peakatt;
   float[][][] tonecurves;
    PsyInfo vi;

    void init(PsyInfo var1, int var2, int var3) {
   }
}
} // namespace jorbis
} // namespace jcraft
} // namespace com

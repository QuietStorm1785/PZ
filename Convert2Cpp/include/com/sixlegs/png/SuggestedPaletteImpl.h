#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace sixlegs {
namespace png {

class SuggestedPaletteImpl {
public:
    const std::string name;
    const int sampleDepth;
   private final byte[] bytes;
    const int entrySize;
    const int sampleCount;

    public SuggestedPaletteImpl(const std::string& var1, int var2, byte[] var3) {
      this.name = var1;
      this.sampleDepth = var2;
      this.bytes = var3;
      this.entrySize = var2 == 8 ? 6 : 10;
      this.sampleCount = var3.length / this.entrySize;
   }

    std::string getName() {
      return this.name;
   }

    int getSampleCount() {
      return this.sampleCount;
   }

    int getSampleDepth() {
      return this.sampleDepth;
   }

    void getSample(int var1, short[] var2) {
    int var3 = var1 * this.entrySize;
      if (this.sampleDepth == 8) {
         for (int var4 = 0; var4 < 4; var4++) {
    int var5 = 255 & this.bytes[var3++];
            var2[var4] = (short)var5;
         }
      } else {
         for (int var8 = 0; var8 < 4; var8++) {
    int var9 = 255 & this.bytes[var3++];
    int var6 = 255 & this.bytes[var3++];
            var2[var8] = (short)(var9 << 8 | var6);
         }
      }
   }

    int getFrequency(int var1) {
    int var2 = (var1 + 1) * this.entrySize - 2;
    int var3 = 255 & this.bytes[var2];
    int var4 = 255 & this.bytes[var2 + 1];
      return var3 << 8 | var4;
   }
}
} // namespace png
} // namespace sixlegs
} // namespace com

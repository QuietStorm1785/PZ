#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace com {
namespace sixlegs {
namespace png {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class SuggestedPaletteImpl {
public:
  const std::string name;
  const int sampleDepth;
private
  final byte[] bytes;
  const int entrySize;
  const int sampleCount;

public
  SuggestedPaletteImpl(const std::string &string, int int0, byte[] bytesx) {
    this.name = string;
    this.sampleDepth = int0;
    this.bytes = bytesx;
    this.entrySize = int0 == 8 ? 6 : 10;
    this.sampleCount = bytesx.length / this.entrySize;
  }

  std::string getName() { return this.name; }

  int getSampleCount() { return this.sampleCount; }

  int getSampleDepth() { return this.sampleDepth; }

  void getSample(int int1, short[] shorts) {
    int int0 = int1 * this.entrySize;
    if (this.sampleDepth == 8) {
      for (int int2 = 0; int2 < 4; int2++) {
        int int3 = 255 & this.bytes[int0++];
        shorts[int2] = (short)int3;
      }
    } else {
      for (int int4 = 0; int4 < 4; int4++) {
        int int5 = 255 & this.bytes[int0++];
        int int6 = 255 & this.bytes[int0++];
        shorts[int4] = (short)(int5 << 8 | int6);
      }
    }
  }

  int getFrequency(int int1) {
    int int0 = (int1 + 1) * this.entrySize - 2;
    int int2 = 255 & this.bytes[int0];
    int int3 = 255 & this.bytes[int0 + 1];
    return int2 << 8 | int3;
  }
}
} // namespace png
} // namespace sixlegs
} // namespace com

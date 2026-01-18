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

class IdentificationHeader {
public:
  int version;
  int channels;
  int sampleRate;
  int bitrateMaximum;
  int bitrateNominal;
  int bitrateMinimum;
  int blockSize0;
  int blockSize1;
  bool framingFlag;
private
  MdctFloat[] mdct = new MdctFloat[2];
  static const long HEADER = 126896460427126L;

public
  IdentificationHeader(BitInputStream bitInputStream) {
    long long0 = bitInputStream.getLong(48);
    if (long0 != 126896460427126L) {
      throw new VorbisFormatException(
          "The identification header has an illegal leading.");
    } else {
      this.version = bitInputStream.getInt(32);
      this.channels = bitInputStream.getInt(8);
      this.sampleRate = bitInputStream.getInt(32);
      this.bitrateMaximum = bitInputStream.getInt(32);
      this.bitrateNominal = bitInputStream.getInt(32);
      this.bitrateMinimum = bitInputStream.getInt(32);
      int int0 = bitInputStream.getInt(8);
      this.blockSize0 = 1 << (int0 & 15);
      this.blockSize1 = 1 << (int0 >> 4);
      this.mdct[0] = new MdctFloat(this.blockSize0);
      this.mdct[1] = new MdctFloat(this.blockSize1);
      this.framingFlag = bitInputStream.getInt(8) != 0;
    }
  }

  int getSampleRate() { return this.sampleRate; }

  int getMaximumBitrate() { return this.bitrateMaximum; }

  int getNominalBitrate() { return this.bitrateNominal; }

  int getMinimumBitrate() { return this.bitrateMinimum; }

  int getChannels() { return this.channels; }

  int getBlockSize0() { return this.blockSize0; }

  int getBlockSize1() { return this.blockSize1; }

  MdctFloat getMdct0() { return this.mdct[0]; }

  MdctFloat getMdct1() { return this.mdct[1]; }

  int getVersion() { return this.version; }
}
} // namespace vorbis
} // namespace jarnbjo
} // namespace de

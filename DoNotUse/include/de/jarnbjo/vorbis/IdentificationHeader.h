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
   private MdctFloat[] mdct = new MdctFloat[2];
    static const long HEADER = 126896460427126L;

    public IdentificationHeader(BitInputStream var1) {
    long var2 = var1.getLong(48);
      if (var2 != 126896460427126L) {
         throw VorbisFormatException("The identification header has an illegal leading.");
      } else {
         this.version = var1.getInt(32);
         this.channels = var1.getInt(8);
         this.sampleRate = var1.getInt(32);
         this.bitrateMaximum = var1.getInt(32);
         this.bitrateNominal = var1.getInt(32);
         this.bitrateMinimum = var1.getInt(32);
    int var4 = var1.getInt(8);
         this.blockSize0 = 1 << (var4 & 15);
         this.blockSize1 = 1 << (var4 >> 4);
         this.mdct[0] = std::make_shared<MdctFloat>(this.blockSize0);
         this.mdct[1] = std::make_shared<MdctFloat>(this.blockSize1);
         this.framingFlag = var1.getInt(8) != 0;
      }
   }

    int getSampleRate() {
      return this.sampleRate;
   }

    int getMaximumBitrate() {
      return this.bitrateMaximum;
   }

    int getNominalBitrate() {
      return this.bitrateNominal;
   }

    int getMinimumBitrate() {
      return this.bitrateMinimum;
   }

    int getChannels() {
      return this.channels;
   }

    int getBlockSize0() {
      return this.blockSize0;
   }

    int getBlockSize1() {
      return this.blockSize1;
   }

    MdctFloat getMdct0() {
      return this.mdct[0];
   }

    MdctFloat getMdct1() {
      return this.mdct[1];
   }

    int getVersion() {
      return this.version;
   }
}
} // namespace vorbis
} // namespace jarnbjo
} // namespace de

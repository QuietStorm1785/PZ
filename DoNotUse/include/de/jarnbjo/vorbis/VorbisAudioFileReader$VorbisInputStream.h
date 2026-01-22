#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/jarnbjo/ogg/EndOfOggStreamException.h"
#include <fstream>
#include <iostream>

namespace de {
namespace jarnbjo {
namespace vorbis {


class VorbisAudioFileReader {
public:
    VorbisStream source;
   private byte[] buffer = new byte[8192];

   public VorbisAudioFileReader$VorbisInputStream(VorbisStream var1) {
      this.source = var1;
   }

    int read() {
    return 0;
   }

    int read(byte[] var1) {
      return this.read(var1, 0, var1.length);
   }

    int read(byte[] var1, int var2, int var3) {
      try {
         return this.source.readPcm(var1, var2, var3);
      } catch (EndOfOggStreamException var5) {
         return -1;
      }
   }
}
} // namespace vorbis
} // namespace jarnbjo
} // namespace de

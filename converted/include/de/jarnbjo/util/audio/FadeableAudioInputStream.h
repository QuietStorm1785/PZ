#pragma once
#include "javax/sound/sampled/AudioInputStream.h"
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
namespace util {
namespace audio {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class FadeableAudioInputStream : public AudioInputStream {
public:
  AudioInputStream stream;
  bool fading = false;
  double phi = 0.0;

public
  FadeableAudioInputStream(AudioInputStream audioInputStream) {
    super(audioInputStream, audioInputStream.getFormat(), -1L);
  }

  void fadeOut() {
    this.fading = true;
    this.phi = 0.0;
  }

  int read(byte[] bytes) { return this.read(bytes, 0, bytes.length); }

  int read(byte[] bytes, int int1, int int2) {
    int int0 = super.read(bytes, int1, int2);
    if (this.fading) {
      int int3 = 0;
      int int4 = 0;
      int int5 = 0;
      double double0 = 0.0;

      for (int int6 = int1; int6 < int1 + int0; int6 += 4) {
        int3 = int6 + 1;
        int4 = bytes[int6] & 255;
        int4 |= bytes[int3++] << 8;
        int5 = bytes[int3++] & 255;
        int5 |= bytes[int3] << 8;
        if (this.phi < Math.PI / 2) {
          this.phi += 1.5E-5;
        }

        double0 = Math.cos(this.phi);
        int4 = (int)(int4 * double0);
        int5 = (int)(int5 * double0);
        int3 = int6 + 1;
        bytes[int6] = (byte)(int4 & 0xFF);
        bytes[int3++] = (byte)(int4 >> 8 & 0xFF);
        bytes[int3++] = (byte)(int5 & 0xFF);
        bytes[int3++] = (byte)(int5 >> 8 & 0xFF);
      }
    }

    return int0;
  }
}
} // namespace audio
} // namespace util
} // namespace jarnbjo
} // namespace de

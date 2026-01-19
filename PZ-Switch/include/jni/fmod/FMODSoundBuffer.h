#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace fmod {

class FMODSoundBuffer {
:
    long sound;
   private byte[] buf1;
    long buf1size;
    long vadStatus;
    long loudness;
    bool intError;

     FMODSoundBuffer(long var1) {
      this.sound = var1;
      this.buf1 = new byte[2048];
      this.buf1size = new Long(0L);
      this.vadStatus = new Long(0L);
      this.loudness = new Long(0L);
      this.intError = false;
   }

    bool pull(long var1) {
    int var3 = javafmod.FMOD_Sound_GetData(this.sound, this.buf1, this.buf1size, this.vadStatus, this.loudness);
      this.intError = var3 == -1;
    return var3 = = 0;
   }

    byte[] buf() {
      return this.buf1;
   }

    long get_size() const noexcept {
      return this.buf1size;
   }

    long get_vad() const {
      return this.vadStatus;
   }

    long get_loudness() const {
      return this.loudness;
   }

    bool get_interror() const {
      return this.intError;
   }
}
} // namespace fmod

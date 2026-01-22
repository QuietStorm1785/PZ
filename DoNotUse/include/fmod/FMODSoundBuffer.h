#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace fmod {

class FMODSoundBuffer {
public:
    long sound;
   private byte[] buf1;
    long buf1size;
    long vadStatus;
    long loudness;
    bool intError;

    public FMODSoundBuffer(long var1) {
      this.sound = var1;
      this.buf1 = new byte[2048];
      this.buf1size = std::make_shared<int64_t>(0L);
      this.vadStatus = std::make_shared<int64_t>(0L);
      this.loudness = std::make_shared<int64_t>(0L);
      this.intError = false;
   }

    bool pull(long var1) {
    int var3 = javafmod.FMOD_Sound_GetData(this.sound, this.buf1, this.buf1size, this.vadStatus, this.loudness);
      this.intError = var3 == -1;
    return var3 = = 0;
   }

   public byte[] buf() {
      return this.buf1;
   }

    long get_size() {
      return this.buf1size;
   }

    long get_vad() {
      return this.vadStatus;
   }

    long get_loudness() {
      return this.loudness;
   }

    bool get_interror() {
      return this.intError;
   }
}
} // namespace fmod

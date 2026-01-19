#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace fmod {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class FMODSoundBuffer {
public:
 long sound;
private
 byte[] buf1;
 long buf1size;
 long vadStatus;
 long loudness;
 bool intError;

public
 FMODSoundBuffer(long long0) {
 this->sound = long0;
 this->buf1 = new byte[2048];
 this->buf1size = new Long(0L);
 this->vadStatus = new Long(0L);
 this->loudness = new Long(0L);
 this->intError = false;
 }

 bool pull(long var1) {
 int int0 = javafmod.FMOD_Sound_GetData(this->sound, this->buf1, this->buf1size,
 this->vadStatus, this->loudness);
 this->intError = int0 == -1;
 return int0 = = 0;
 }

public
 byte[] buf() { return this->buf1; }

 long get_size() noexcept{ return this->buf1size; }

 long get_vad() { return this->vadStatus; }

 long get_loudness() { return this->loudness; }

 bool get_interror() { return this->intError; }
}
} // namespace fmod

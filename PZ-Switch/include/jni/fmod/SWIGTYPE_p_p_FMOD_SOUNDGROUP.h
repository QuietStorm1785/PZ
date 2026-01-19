#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace fmod {

class SWIGTYPE_p_p_FMOD_SOUNDGROUP {
:
    long swigCPtr;

    protected SWIGTYPE_p_p_FMOD_SOUNDGROUP(long var1, bool var3) {
      this.swigCPtr = var1;
   }

    protected SWIGTYPE_p_p_FMOD_SOUNDGROUP() {
      this.swigCPtr = 0L;
   }

    static long getCPtr(SWIGTYPE_p_p_FMOD_SOUNDGROUP var0) {
    return var0 = = nullptr ? 0L : var0.swigCPtr;
   }
}
} // namespace fmod

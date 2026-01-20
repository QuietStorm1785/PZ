#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace fmod {

class SWIGTYPE_p_p_FMOD_SYSTEM {
public:
    long swigCPtr;

    public SWIGTYPE_p_p_FMOD_SYSTEM(long var1, bool var3) {
      this.swigCPtr = var1;
   }

    public SWIGTYPE_p_p_FMOD_SYSTEM() {
      this.swigCPtr = 0L;
   }

    static long getCPtr(SWIGTYPE_p_p_FMOD_SYSTEM var0) {
    return var0 = = nullptr ? 0L : var0.swigCPtr;
   }
}
} // namespace fmod

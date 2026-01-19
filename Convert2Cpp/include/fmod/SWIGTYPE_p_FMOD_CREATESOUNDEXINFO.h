#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace fmod {

class SWIGTYPE_p_FMOD_CREATESOUNDEXINFO {
public:
    long swigCPtr;

    protected SWIGTYPE_p_FMOD_CREATESOUNDEXINFO(long var1, bool var3) {
      this.swigCPtr = var1;
   }

    protected SWIGTYPE_p_FMOD_CREATESOUNDEXINFO() {
      this.swigCPtr = 0L;
   }

    static long getCPtr(SWIGTYPE_p_FMOD_CREATESOUNDEXINFO var0) {
    return var0 = = null ? 0L : var0.swigCPtr;
   }
}
} // namespace fmod

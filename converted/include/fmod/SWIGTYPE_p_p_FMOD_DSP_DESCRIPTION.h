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

class SWIGTYPE_p_p_FMOD_DSP_DESCRIPTION {
public:
  long swigCPtr;

protected
  SWIGTYPE_p_p_FMOD_DSP_DESCRIPTION(long long0, bool var3) {
    this.swigCPtr = long0;
  }

protected
  SWIGTYPE_p_p_FMOD_DSP_DESCRIPTION() { this.swigCPtr = 0L; }

  static long
  getCPtr(SWIGTYPE_p_p_FMOD_DSP_DESCRIPTION sWIGTYPE_p_p_FMOD_DSP_DESCRIPTION) {
    return sWIGTYPE_p_p_FMOD_DSP_DESCRIPTION = =
               null ? 0L : sWIGTYPE_p_p_FMOD_DSP_DESCRIPTION.swigCPtr;
  }
}
} // namespace fmod

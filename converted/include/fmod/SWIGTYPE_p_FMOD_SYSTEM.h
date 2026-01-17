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

class SWIGTYPE_p_FMOD_SYSTEM {
public:
  long swigCPtr;

protected
  SWIGTYPE_p_FMOD_SYSTEM(long long0, bool var3) { this.swigCPtr = long0; }

protected
  SWIGTYPE_p_FMOD_SYSTEM() { this.swigCPtr = 0L; }

  static long getCPtr(SWIGTYPE_p_FMOD_SYSTEM sWIGTYPE_p_FMOD_SYSTEM) {
    return sWIGTYPE_p_FMOD_SYSTEM = =
               null ? 0L : sWIGTYPE_p_FMOD_SYSTEM.swigCPtr;
  }
}
} // namespace fmod

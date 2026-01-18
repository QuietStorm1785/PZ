#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace fmod {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class SWIGTYPE_p_FMOD_SOUND_TYPE {
public:
 long swigCPtr;

 protected SWIGTYPE_p_FMOD_SOUND_TYPE(long long0, bool var3) {
 this->swigCPtr = long0;
 }

 protected SWIGTYPE_p_FMOD_SOUND_TYPE() {
 this->swigCPtr = 0L;
 }

 static long getCPtr(SWIGTYPE_p_FMOD_SOUND_TYPE sWIGTYPE_p_FMOD_SOUND_TYPE) {
 return sWIGTYPE_p_FMOD_SOUND_TYPE = = nullptr ? 0L : sWIGTYPE_p_FMOD_SOUND_TYPE.swigCPtr;
 }
}
} // namespace fmod

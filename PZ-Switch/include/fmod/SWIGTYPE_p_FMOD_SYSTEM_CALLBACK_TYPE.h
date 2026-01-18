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

class SWIGTYPE_p_FMOD_SYSTEM_CALLBACK_TYPE {
public:
 long swigCPtr;

protected
 SWIGTYPE_p_FMOD_SYSTEM_CALLBACK_TYPE(long long0, bool var3) {
 this->swigCPtr = long0;
 }

protected
 SWIGTYPE_p_FMOD_SYSTEM_CALLBACK_TYPE() { this->swigCPtr = 0L; }

 static long getCPtr(SWIGTYPE_p_FMOD_SYSTEM_CALLBACK_TYPE
 sWIGTYPE_p_FMOD_SYSTEM_CALLBACK_TYPE) {
 return sWIGTYPE_p_FMOD_SYSTEM_CALLBACK_TYPE = =
 nullptr ? 0L : sWIGTYPE_p_FMOD_SYSTEM_CALLBACK_TYPE.swigCPtr;
 }
}
} // namespace fmod

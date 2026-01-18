#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace fmod {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class SWIGTYPE_p_FMOD_FILE_ASYNCREAD_CALLBACK {
public:
 long swigCPtr;

 protected SWIGTYPE_p_FMOD_FILE_ASYNCREAD_CALLBACK(long long0, bool var3) {
 this->swigCPtr = long0;
 }

 protected SWIGTYPE_p_FMOD_FILE_ASYNCREAD_CALLBACK() {
 this->swigCPtr = 0L;
 }

 static long getCPtr(SWIGTYPE_p_FMOD_FILE_ASYNCREAD_CALLBACK sWIGTYPE_p_FMOD_FILE_ASYNCREAD_CALLBACK) {
 return sWIGTYPE_p_FMOD_FILE_ASYNCREAD_CALLBACK = = nullptr ? 0L : sWIGTYPE_p_FMOD_FILE_ASYNCREAD_CALLBACK.swigCPtr;
 }
}
} // namespace fmod

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

class SWIGTYPE_p_FMOD_PLUGINTYPE {
public:
 long swigCPtr;

protected
 SWIGTYPE_p_FMOD_PLUGINTYPE(long long0, bool var3) { this->swigCPtr = long0; }

protected
 SWIGTYPE_p_FMOD_PLUGINTYPE() { this->swigCPtr = 0L; }

 static long getCPtr(SWIGTYPE_p_FMOD_PLUGINTYPE sWIGTYPE_p_FMOD_PLUGINTYPE) {
 return sWIGTYPE_p_FMOD_PLUGINTYPE = =
 nullptr ? 0L : sWIGTYPE_p_FMOD_PLUGINTYPE.swigCPtr;
 }
}
} // namespace fmod

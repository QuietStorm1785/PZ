#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace fmod {
namespace fmod {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class FMOD_STUDIO_PARAMETER_ID {
public:
 const long nativePtr;

 public FMOD_STUDIO_PARAMETER_ID(long arg0) {
 this->nativePtr = arg0;
 }

 long address() {
 return this->nativePtr;
 }
}
} // namespace fmod
} // namespace fmod

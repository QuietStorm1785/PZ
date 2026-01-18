#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace fmod {
namespace fmod {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class FMOD_STUDIO_PARAMETER_ID {
public:
  const long nativePtr;

public
  FMOD_STUDIO_PARAMETER_ID(long arg0) { this.nativePtr = arg0; }

  long address() { return this.nativePtr; }
}
} // namespace fmod
} // namespace fmod

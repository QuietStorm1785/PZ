#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace fmod {
namespace fmod {

class FMOD_STUDIO_PARAMETER_ID {
public:
    const long nativePtr;

    public FMOD_STUDIO_PARAMETER_ID(long var1) {
      this.nativePtr = var1;
   }

    long address() {
      return this.nativePtr;
   }
}
} // namespace fmod
} // namespace fmod

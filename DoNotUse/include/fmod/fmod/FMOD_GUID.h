#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace fmod {
namespace fmod {

class FMOD_GUID {
public:
    const long address;

    public FMOD_GUID(long var1) {
      this.address = var1;
   }

    long address() {
      return this.address;
   }
}
} // namespace fmod
} // namespace fmod

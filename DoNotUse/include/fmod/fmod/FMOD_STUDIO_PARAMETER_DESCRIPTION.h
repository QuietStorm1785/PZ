#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace fmod {
namespace fmod {

class FMOD_STUDIO_PARAMETER_DESCRIPTION {
public:
    const std::string name;
    const FMOD_STUDIO_PARAMETER_ID id;
    const int flags;
    const int globalIndex;

    public FMOD_STUDIO_PARAMETER_DESCRIPTION(const std::string& var1, FMOD_STUDIO_PARAMETER_ID var2, int var3, int var4) {
      this.name = var1;
      this.id = var2;
      this.flags = var3;
      this.globalIndex = var4;
   }

    bool isGlobal() {
      return (this.flags & FMOD_STUDIO_PARAMETER_FLAGS.FMOD_STUDIO_PARAMETER_GLOBAL.bit) != 0;
   }
}
} // namespace fmod
} // namespace fmod

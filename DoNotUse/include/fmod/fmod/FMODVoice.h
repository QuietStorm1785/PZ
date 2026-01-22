#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace fmod {
namespace fmod {

class FMODVoice {
public:
    std::string sound;
    float priority;

    public FMODVoice(const std::string& var1, float var2) {
      this.priority = var2;
      this.sound = var1;
   }
}
} // namespace fmod
} // namespace fmod

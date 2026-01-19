#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODFootstep.h"
#include "fmod/fmod/FMODVoice.h"

namespace zombie {
namespace audio {


class DummySoundBank : public BaseSoundBank {
public:
    void addVoice(const std::string& var1, const std::string& var2, float var3) {
   }

    void addFootstep(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4, const std::string& var5) {
   }

    FMODVoice getVoice(const std::string& var1) {
    return null;
   }

    FMODFootstep getFootstep(const std::string& var1) {
    return null;
   }
}
} // namespace audio
} // namespace zombie

#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODFootstep.h"
#include "fmod/fmod/FMODVoice.h"

namespace zombie {
namespace audio {


class DummySoundBank :  BaseSoundBank {
:
    void addVoice(std::string_view var1, std::string_view var2, float var3) {
   }

    void addFootstep(std::string_view var1, std::string_view var2, std::string_view var3, std::string_view var4, std::string_view var5) {
   }

    FMODVoice getVoice(std::string_view var1) {
    return nullptr;
   }

    FMODFootstep getFootstep(std::string_view var1) {
    return nullptr;
   }
}
} // namespace audio
} // namespace zombie

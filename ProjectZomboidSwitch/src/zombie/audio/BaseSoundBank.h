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


class BaseSoundBank {
public:
    static BaseSoundBank instance;

   public abstract void addVoice(std::string var1, std::string var2, float var3);

   public abstract void addFootstep(std::string var1, std::string var2, std::string var3, std::string var4, std::string var5);

   public abstract FMODVoice getVoice(std::string var1);

   public abstract FMODFootstep getFootstep(std::string var1);
}
} // namespace audio
} // namespace zombie

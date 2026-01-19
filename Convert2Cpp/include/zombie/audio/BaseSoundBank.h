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

   public abstract void addVoice(String var1, String var2, float var3);

   public abstract void addFootstep(String var1, String var2, String var3, String var4, String var5);

   public abstract FMODVoice getVoice(String var1);

   public abstract FMODFootstep getFootstep(String var1);
}
} // namespace audio
} // namespace zombie

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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class BaseSoundBank {
public:
 static BaseSoundBank instance;

 public void addVoice(String alias, String sound, float priority);

 public void addFootstep(String alias, String grass, String wood, String concrete, String upstairs);

 public FMODVoice getVoice(String alias);

 public FMODFootstep getFootstep(String alias);
}
} // namespace audio
} // namespace zombie

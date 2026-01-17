#pragma once
#include "fmod/fmod/FMODFootstep.h"
#include "fmod/fmod/FMODVoice.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace audio {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class BaseSoundBank {
public:
  static BaseSoundBank instance;

public
  abstract void addVoice(String alias, String sound, float priority);

public
  abstract void addFootstep(String alias, String grass, String wood,
                            String concrete, String upstairs);

public
  abstract FMODVoice getVoice(String alias);

public
  abstract FMODFootstep getFootstep(String alias);
}
} // namespace audio
} // namespace zombie

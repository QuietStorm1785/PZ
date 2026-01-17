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

class DummySoundBank : public BaseSoundBank {
public:
  void addVoice(const std::string &alias, const std::string &sound,
                float priority) {}

  void addFootstep(const std::string &alias, const std::string &grass,
                   const std::string &wood, const std::string &concrete,
                   const std::string &upstairs) {}

  FMODVoice getVoice(const std::string &alias) { return null; }

  FMODFootstep getFootstep(const std::string &alias) { return null; }
}
} // namespace audio
} // namespace zombie

#pragma once
#include "fmod/fmod/FMODFootstep.h"
#include "fmod/fmod/FMODVoice.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace audio {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class DummySoundBank : public BaseSoundBank {
public:
 void addVoice(std::string_view alias, std::string_view sound,
 float priority) {}

 void addFootstep(std::string_view alias, std::string_view grass,
 std::string_view wood, std::string_view concrete,
 std::string_view upstairs) {}

 FMODVoice getVoice(std::string_view alias) { return nullptr; }

 FMODFootstep getFootstep(std::string_view alias) { return nullptr; }
}
} // namespace audio
} // namespace zombie

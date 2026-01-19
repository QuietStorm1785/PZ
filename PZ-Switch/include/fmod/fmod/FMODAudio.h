#pragma once
#include "zombie/audio/BaseSoundEmitter.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace fmod {
namespace fmod {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class FMODAudio {
public:
 BaseSoundEmitter emitter;

public
 FMODAudio(BaseSoundEmitter arg0) { this->emitter = arg0; }

 bool isPlaying() { return !this->emitter.empty(); }

 void setVolume(float arg0) { this->emitter.setVolumeAll(arg0); }

 void start() {}

 void pause() {}

 void stop() { this->emitter.stopAll(); }

 void setName(std::string_view arg0) {}

 std::string getName() { return nullptr; }
}
} // namespace fmod
} // namespace fmod

#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace fmod {
namespace fmod {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

enum class FMOD_STUDIO_PLAYBACK_STATE {
  FMOD_STUDIO_PLAYBACK_PLAYING(0), FMOD_STUDIO_PLAYBACK_SUSTAINING(1),
  FMOD_STUDIO_PLAYBACK_STOPPED(2), FMOD_STUDIO_PLAYBACK_STARTING(3),
  FMOD_STUDIO_PLAYBACK_STOPPING(4), FMOD_STUDIO_PLAYBACK_STATE(5);

  int index;

  private FMOD_STUDIO_PLAYBACK_STATE(int int1){this.index = int1;}
} // namespace fmod
} // namespace fmod
} // namespace fmod

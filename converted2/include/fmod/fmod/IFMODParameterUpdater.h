#pragma once
#include "zombie/audio/FMODParameterList.h"
#include "zombie/audio/GameSoundClip.h"
#include <algorithm>
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

class IFMODParameterUpdater {
public:
  virtual ~IFMODParameterUpdater() = default;
  FMODParameterList getFMODParameters();

  void startEvent(long arg0, GameSoundClip arg1, BitSet arg2);

  void updateEvent(long arg0, GameSoundClip arg1);

  void stopEvent(long arg0, GameSoundClip arg1, BitSet arg2);
}
} // namespace fmod
} // namespace fmod

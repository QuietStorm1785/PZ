#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/FMODParameterList.h"
#include "zombie/audio/GameSoundClip.h"
#include <algorithm>

namespace fmod {
namespace fmod {


class IFMODParameterUpdater {
public:
    virtual ~IFMODParameterUpdater() = default;
    FMODParameterList getFMODParameters();

    void startEvent(long var1, GameSoundClip var3, BitSet var4);

    void updateEvent(long var1, GameSoundClip var3);

    void stopEvent(long var1, GameSoundClip var3, BitSet var4);
}
} // namespace fmod
} // namespace fmod

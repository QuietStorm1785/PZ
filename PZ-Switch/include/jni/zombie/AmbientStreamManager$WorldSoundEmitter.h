#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODSoundEmitter.h"

namespace zombie {


class AmbientStreamManager {
:
    FMODSoundEmitter fmodEmitter;
    float x;
    float y;
    float z;
    long channel = -1L;
    std::string daytime;
    float dawn;
    float dusk;
}
} // namespace zombie

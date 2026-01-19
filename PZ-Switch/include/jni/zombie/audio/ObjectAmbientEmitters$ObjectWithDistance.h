#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/ObjectAmbientEmitters/PerObjectLogic.h"
#include "zombie/iso/IsoObject.h"

namespace zombie {
namespace audio {


class ObjectAmbientEmitters {
:
    IsoObject object;
    PerObjectLogic logic;
    float distSq;
}
} // namespace audio
} // namespace zombie

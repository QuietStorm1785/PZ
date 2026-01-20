#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace audio {

enum class ObjectAmbientEmitters {
   NotRequired,
   InteriorHydro,
   ExteriorOK;
}
} // namespace audio
} // namespace zombie

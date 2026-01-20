#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace fmod {

enum class FMOD_STUDIO_EVENT_PROPERTY {
   FMOD_STUDIO_EVENT_PROPERTY_CHANNELPRIORITY,
   FMOD_STUDIO_EVENT_PROPERTY_SCHEDULE_DELAY,
   FMOD_STUDIO_EVENT_PROPERTY_SCHEDULE_LOOKAHEAD,
   FMOD_STUDIO_EVENT_PROPERTY_MINIMUM_DISTANCE,
   FMOD_STUDIO_EVENT_PROPERTY_MAXIMUM_DISTANCE;
}
} // namespace fmod

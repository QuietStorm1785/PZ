#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace fmod {
namespace fmod {

class FMOD_STUDIO_EVENT_CALLBACK {
public:
    void started(long var1) {
   }

    void stopped(long var1) {
   }

    void timelineMarker(long var1, const std::string& var3, int var4) {
   }
}
} // namespace fmod
} // namespace fmod

#pragma once
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

class FMOD_STUDIO_EVENT_CALLBACK {
public:
 void started(long arg0) {}

 void stopped(long arg0) {}

 void timelineMarker(long arg0, std::string_view arg1, int arg2) {}
}
} // namespace fmod
} // namespace fmod

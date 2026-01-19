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

class FMODVoice {
public:
 std::string sound;
 float priority;

public
 FMODVoice(std::string_view arg0, float arg1) {
 this->priority = arg1;
 this->sound = arg0;
 }
}
} // namespace fmod
} // namespace fmod

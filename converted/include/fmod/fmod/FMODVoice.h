#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace fmod {
namespace fmod {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class FMODVoice {
public:
 std::string sound;
 float priority;

 public FMODVoice(const std::string& arg0, float arg1) {
 this->priority = arg1;
 this->sound = arg0;
 }
}
} // namespace fmod
} // namespace fmod

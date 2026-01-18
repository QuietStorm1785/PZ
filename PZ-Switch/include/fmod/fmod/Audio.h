#pragma once
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

class Audio {
public:
 virtual ~Audio() = default;
 bool isPlaying();

 void setVolume(float arg0);

 void start();

 void pause();

 void stop();

 void setName(const std::string &arg0);

 std::string getName();
}
} // namespace fmod
} // namespace fmod

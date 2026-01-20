#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace radio {
namespace StorySounds {

class StoryEmitter {
public:
    long sound;
    long channel;
    float volume;
    float x;
    float y;
    float z;
    float minRange;
    float maxRange;
}
} // namespace StorySounds
} // namespace radio
} // namespace zombie

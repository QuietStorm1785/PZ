#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace fmod {
namespace fmod {

class Audio {
public:
    virtual ~Audio() = default;
    bool isPlaying();

    void setVolume(float var1);

    void start();

    void pause();

    void stop();

    void setName(const std::string& var1);

    std::string getName();
}
} // namespace fmod
} // namespace fmod

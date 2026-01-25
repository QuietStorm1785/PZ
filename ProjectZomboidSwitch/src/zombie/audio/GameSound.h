// ...existing code...
#pragma once
#include <string>
#include <vector>
#include <memory>
#include <cstdint>
#include "fmod/fmod/FMODManager.h"
#include "fmod/fmod/FMOD_STUDIO_PARAMETER_DESCRIPTION.h"
#include "zombie/SystemDisabler.h"
#include "zombie/audio/GameSoundClip.h"
#include "zombie/audio/GameSound/MasterVolume.h"
#include "zombie/core/Rand.h"

namespace zombie {
namespace audio {

class GameSound {
public:
    std::string name;
    std::string category = "General";
    bool loop = false;
    bool is3D = true;
    std::vector<GameSoundClip> clips;
    float userVolume = 1.0f;
    MasterVolume master = MasterVolume::Primary;
    int maxInstancesPerEmitter = -1;
    short reloadEpoch = 0;

    std::string getName() const { return name; }
    std::string getCategory() const { return category; }
    bool isLooped() const { return loop; }
    void setUserVolume(float v) { userVolume = std::max(0.0f, std::min(2.0f, v)); }
    float getUserVolume() const { return !SystemDisabler::getEnableAdvancedSoundOptions() ? 1.0f : userVolume; }
    GameSoundClip& getRandomClip();
    std::string getMasterName() const;
    int numClipsUsingParameter(const std::string& paramName) const;
    void reset();
    MasterVolume getMasterVolumeType() const { return master; }
};

} // namespace audio
} // namespace zombie

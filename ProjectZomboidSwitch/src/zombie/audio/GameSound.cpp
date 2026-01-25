// ...existing code...
#include "zombie/audio/GameSound.h"
#include "fmod/fmod/FMODManager.h"
#include <algorithm>

namespace zombie {
namespace audio {

GameSoundClip& GameSound::getRandomClip() {
    if (clips.empty()) throw std::runtime_error("No clips available");
    return clips[zombie::core::Rand::Next(clips.size())];
}

std::string GameSound::getMasterName() const {
    // Assuming MasterVolume is an enum class with a name() method or similar
    // If not, implement a mapping from enum to string
    switch (master) {
        case MasterVolume::Primary: return "Primary";
        case MasterVolume::Sound: return "Sound";
        case MasterVolume::Ambient: return "Ambient";
        case MasterVolume::Music: return "Music";
        case MasterVolume::VehicleEngine: return "VehicleEngine";
        default: return "Unknown";
    }
}

int GameSound::numClipsUsingParameter(const std::string& paramName) const {
    auto paramDesc = FMODManager::instance().getParameterDescription(paramName);
    if (!paramDesc) return 0;
    int count = 0;
    for (const auto& clip : clips) {
        if (clip.hasParameter(*paramDesc)) ++count;
    }
    return count;
}

void GameSound::reset() {
    name.clear();
    category = "General";
    loop = false;
    is3D = true;
    clips.clear();
    userVolume = 1.0f;
    master = MasterVolume::Primary;
    maxInstancesPerEmitter = -1;
    ++reloadEpoch;
}

} // namespace audio
} // namespace zombie

// ...existing code...
#include "zombie/audio/GameSoundClip.h"
#include "zombie/audio/GameSound.h"
#include "zombie/SoundManager.h"
#include "zombie/core/Core.h"
#include <algorithm>

namespace zombie {
namespace audio {

GameSoundClip::GameSoundClip(GameSound& gs)
    : gameSound(gs) {
    reloadEpoch = gs.reloadEpoch;
}

float GameSoundClip::getEffectiveVolume() const {
    float v = 1.0f;
    switch (gameSound.getMasterVolumeType()) {
        case GameSound::MasterVolume::Sound:
            v = SoundManager::instance().getSoundVolume(); break;
        case GameSound::MasterVolume::Ambient:
            v = SoundManager::instance().getAmbientVolume(); break;
        case GameSound::MasterVolume::Music:
            v = SoundManager::instance().getMusicVolume(); break;
        case GameSound::MasterVolume::VehicleEngine:
            v = SoundManager::instance().getVehicleEngineVolume(); break;
        default: break;
    }
    v *= volume;
    return v * gameSound.getUserVolume();
}

float GameSoundClip::getEffectiveVolumeInMenu() const {
    float v = 1.0f;
    switch (gameSound.getMasterVolumeType()) {
        case GameSound::MasterVolume::Sound:
            v = Core::getInstance().getOptionSoundVolume() / 10.0f; break;
        case GameSound::MasterVolume::Ambient:
            v = Core::getInstance().getOptionAmbientVolume() / 10.0f; break;
        case GameSound::MasterVolume::Music:
            v = Core::getInstance().getOptionMusicVolume() / 10.0f; break;
        case GameSound::MasterVolume::VehicleEngine:
            v = Core::getInstance().getOptionVehicleEngineVolume() / 10.0f; break;
        default: break;
    }
    v *= volume;
    return v * gameSound.getUserVolume();
}

GameSoundClip* GameSoundClip::checkReloaded() {
    if (reloadEpoch == gameSound.reloadEpoch)
        return this;
    GameSoundClip* found = nullptr;
    for (auto& clip : gameSound.clips) {
        if (&clip == this) return this;
        if (!clip.event.empty() && clip.event == event) found = &clip;
        if (!clip.file.empty() && clip.file == file) found = &clip;
    }
    if (!found) {
        reloadEpoch = gameSound.reloadEpoch;
        return this;
    }
    return found;
}

bool GameSoundClip::hasSustainPoints() const {
    return eventDescription && eventDescription->bHasSustainPoints;
}

bool GameSoundClip::hasParameter(const FMOD_STUDIO_PARAMETER_DESCRIPTION& param) const {
    return eventDescription && eventDescription->hasParameter(param);
}

} // namespace audio
} // namespace zombie

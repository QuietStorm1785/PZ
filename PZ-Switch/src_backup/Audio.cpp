#include "Audio.h"

namespace zombie {
namespace audio {

Sound::Sound(const std::string& path, SoundCategory category)
    : path(path), category(category), volume(1.0f) {
}

WorldSound::WorldSound(const std::string& path, Vec3 position)
    : Sound(path, SoundCategory::SFX), position(position) {
}

void WorldSound::play() {
    // Will be implemented with SDL_mixer
}

void WorldSound::stop() {
    // Will be implemented with SDL_mixer
}

void WorldSound::pause() {
    // Will be implemented with SDL_mixer
}

void WorldSound::setVolume(float vol) {
    volume = std::max(0.0f, std::min(vol, 1.0f));
}

bool AudioManager::initialize() {
    masterVolume = 1.0f;
    categoryVolumes[SoundCategory::MUSIC] = 1.0f;
    categoryVolumes[SoundCategory::SFX] = 1.0f;
    categoryVolumes[SoundCategory::VOICE] = 1.0f;
    categoryVolumes[SoundCategory::AMBIENT] = 1.0f;
    categoryVolumes[SoundCategory::UI] = 1.0f;
    
    return true;
}

void AudioManager::shutdown() {
    sounds.clear();
}

std::shared_ptr<Sound> AudioManager::loadSound(const std::string& path, SoundCategory category) {
    auto sound = std::make_shared<WorldSound>(path, Vec3(0, 0, 0));
    sounds[path] = sound;
    return sound;
}

void AudioManager::playSound(const std::string& soundId) {
    auto it = sounds.find(soundId);
    if (it != sounds.end()) {
        it->second->play();
    }
}

void AudioManager::stopSound(const std::string& soundId) {
    auto it = sounds.find(soundId);
    if (it != sounds.end()) {
        it->second->stop();
    }
}

void AudioManager::playWorldSound(const std::string& path, Vec3 position) {
    auto sound = std::make_shared<WorldSound>(path, position);
    sound->play();
}

void AudioManager::setMasterVolume(float vol) {
    masterVolume = std::max(0.0f, std::min(vol, 1.0f));
}

void AudioManager::setCategoryVolume(SoundCategory category, float vol) {
    categoryVolumes[category] = std::max(0.0f, std::min(vol, 1.0f));
}

void AudioManager::update(float deltaTime) {
    // Update 3D audio positioning
}

} // namespace audio
} // namespace zombie

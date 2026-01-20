#include <string>
#include "zombie\audio/GameSound.h"

namespace zombie {
namespace audio {

std::string GameSound::getName() {
    // TODO: Implement getName
    return "";
}

std::string GameSound::getCategory() {
    // TODO: Implement getCategory
    return "";
}

bool GameSound::isLooped() {
    // TODO: Implement isLooped
    return false;
}

void GameSound::setUserVolume(float var1) {
    // TODO: Implement setUserVolume
}

float GameSound::getUserVolume() {
    // TODO: Implement getUserVolume
    return 0;
}

GameSoundClip GameSound::getRandomClip() {
    // TODO: Implement getRandomClip
    return nullptr;
}

std::string GameSound::getMasterName() {
    // TODO: Implement getMasterName
    return "";
}

int GameSound::numClipsUsingParameter(const std::string& var1) {
    // TODO: Implement numClipsUsingParameter
    return 0;
}

void GameSound::reset() {
    // TODO: Implement reset
}

} // namespace audio
} // namespace zombie

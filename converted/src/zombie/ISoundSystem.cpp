#include "zombie/ISoundSystem.h"

namespace zombie {

void ISoundSystem::init() {
 // TODO: Implement init
}

void ISoundSystem::update() {
 // TODO: Implement update
}

void ISoundSystem::purge() {
 // TODO: Implement purge
}

void ISoundSystem::fadeOutAll(float var1) {
 // TODO: Implement fadeOutAll
}

void ISoundSystem::cacheSound(ISoundSystem.SoundFormat var1, const std::string& var2, const std::string& var3, int var4) {
 // TODO: Implement cacheSound
}

void ISoundSystem::cacheSound(ISoundSystem.SoundFormat var1, const std::string& var2, const std::string& var3) {
 // TODO: Implement cacheSound
}

void ISoundSystem::clearSoundCache() {
 // TODO: Implement clearSoundCache
}

int ISoundSystem::countInstances(const std::string& var1) {
 // TODO: Implement countInstances
 return 0;
}

void ISoundSystem::setInstanceLimit(const std::string& var1, int var2, ISoundSystem.InstanceFailAction var3) {
 // TODO: Implement setInstanceLimit
}

bool ISoundSystem::isStreamed() {
 // TODO: Implement isStreamed
 return false;
}

bool ISoundSystem::isLooped() {
 // TODO: Implement isLooped
 return false;
}

bool ISoundSystem::isPlaying() {
 // TODO: Implement isPlaying
 return false;
}

int ISoundSystem::countInstances() {
 // TODO: Implement countInstances
 return 0;
}

void ISoundSystem::setLooped(bool var1) {
 // TODO: Implement setLooped
}

void ISoundSystem::pause() {
 // TODO: Implement pause
}

void ISoundSystem::stop() {
 // TODO: Implement stop
}

void ISoundSystem::play() {
 // TODO: Implement play
}

void ISoundSystem::blendVolume(float var1, float var2, bool var3) {
 // TODO: Implement blendVolume
}

void ISoundSystem::setVolume(float var1) {
 // TODO: Implement setVolume
}

float ISoundSystem::getVolume() {
 // TODO: Implement getVolume
 return 0;
}

void ISoundSystem::setPanning(float var1) {
 // TODO: Implement setPanning
}

float ISoundSystem::getPanning() {
 // TODO: Implement getPanning
 return 0;
}

void ISoundSystem::setPitch(float var1) {
 // TODO: Implement setPitch
}

float ISoundSystem::getPitch() {
 // TODO: Implement getPitch
 return 0;
}

bool ISoundSystem::disposed() {
 // TODO: Implement disposed
 return false;
}

} // namespace zombie

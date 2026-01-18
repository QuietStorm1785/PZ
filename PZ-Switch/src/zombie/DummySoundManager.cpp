#include "zombie/DummySoundManager.h"

namespace zombie {

bool DummySoundManager::isRemastered() {
 // TODO: Implement isRemastered
 return false;
}

void DummySoundManager::update1() {
 // TODO: Implement update1
}

void DummySoundManager::update3() {
 // TODO: Implement update3
}

void DummySoundManager::update2() {
 // TODO: Implement update2
}

void DummySoundManager::update4() {
 // TODO: Implement update4
}

void DummySoundManager::CacheSound(const std::string &file) {
 // TODO: Implement CacheSound
}

void DummySoundManager::StopSound(Audio SoundEffect) {
 // TODO: Implement StopSound
}

void DummySoundManager::StopMusic() {
 // TODO: Implement StopMusic
}

void DummySoundManager::Purge() {
 // TODO: Implement Purge
}

void DummySoundManager::stop() {
 // TODO: Implement stop
}

bool DummySoundManager::HasMusic(Audio var1) {
 // TODO: Implement HasMusic
 return false;
}

void DummySoundManager::Update() {
 // TODO: Implement Update
}

Audio DummySoundManager::Start(Audio musicTrack, float f,
 const std::string &PrefMusic) {
 // TODO: Implement Start
 return nullptr;
}

Audio DummySoundManager::PrepareMusic(const std::string &name) {
 // TODO: Implement PrepareMusic
 return nullptr;
}

void DummySoundManager::PlayWorldSoundWav(const std::string &name,
 IsoGridSquare source, float pitchVar,
 float radius, float maxGain,
 int choices, bool ignoreOutside) {
 // TODO: Implement PlayWorldSoundWav
}

Audio DummySoundManager::PlayWorldSoundWav(const std::string &name, bool loop,
 IsoGridSquare source, float pitchVar,
 float radius, float maxGain,
 bool ignoreOutside) {
 // TODO: Implement PlayWorldSoundWav
 return nullptr;
}

Audio DummySoundManager::PlayWorldSoundWav(const std::string &name,
 IsoGridSquare source, float pitchVar,
 float radius, float maxGain,
 bool ignoreOutside) {
 // TODO: Implement PlayWorldSoundWav
 return nullptr;
}

Audio DummySoundManager::PlayWorldSound(const std::string &name,
 IsoGridSquare source, float pitchVar,
 float radius, float maxGain,
 int choices, bool ignoreOutside) {
 // TODO: Implement PlayWorldSound
 return nullptr;
}

Audio DummySoundManager::PlayWorldSound(const std::string &name, bool loop,
 IsoGridSquare source, float pitchVar,
 float radius, float maxGain,
 bool ignoreOutside) {
 // TODO: Implement PlayWorldSound
 return nullptr;
}

Audio DummySoundManager::PlayWorldSoundImpl(const std::string &name, bool loop,
 int sx, int sy, int sz,
 float pitchVar, float radius,
 float maxGain, bool ignoreOutside) {
 // TODO: Implement PlayWorldSoundImpl
 return nullptr;
}

Audio DummySoundManager::PlayWorldSound(const std::string &name,
 IsoGridSquare source, float pitchVar,
 float radius, float maxGain,
 bool ignoreOutside) {
 // TODO: Implement PlayWorldSound
 return nullptr;
}

void DummySoundManager::update3D() {
 // TODO: Implement update3D
}

Audio DummySoundManager::PlaySoundWav(const std::string &name, int variations,
 bool loop, float maxGain) {
 // TODO: Implement PlaySoundWav
 return nullptr;
}

Audio DummySoundManager::PlaySoundWav(const std::string &name, bool loop,
 float maxGain) {
 // TODO: Implement PlaySoundWav
 return nullptr;
}

Audio DummySoundManager::PlaySoundWav(const std::string &name, bool loop,
 float maxGain, float pitchVar) {
 // TODO: Implement PlaySoundWav
 return nullptr;
}

Audio DummySoundManager::PlayJukeboxSound(const std::string &name, bool loop,
 float maxGain) {
 // TODO: Implement PlayJukeboxSound
 return nullptr;
}

Audio DummySoundManager::PlaySoundEvenSilent(const std::string &name, bool loop,
 float maxGain) {
 // TODO: Implement PlaySoundEvenSilent
 return nullptr;
}

Audio DummySoundManager::PlaySound(const std::string &name, bool loop,
 float maxGain) {
 // TODO: Implement PlaySound
 return nullptr;
}

Audio DummySoundManager::PlaySound(const std::string &name, bool loop,
 float pitchVar, float maxGain) {
 // TODO: Implement PlaySound
 return nullptr;
}

Audio DummySoundManager::PlayMusic(const std::string &n,
 const std::string &name, bool loop,
 float maxGain) {
 // TODO: Implement PlayMusic
 return nullptr;
}

void DummySoundManager::PlayAsMusic(const std::string &name, Audio musicTrack,
 bool loop, float volume) {
 // TODO: Implement PlayAsMusic
}

void DummySoundManager::setMusicState(const std::string &stateName) {
 // TODO: Implement setMusicState
}

void DummySoundManager::setMusicWakeState(IsoPlayer player,
 const std::string &stateName) {
 // TODO: Implement setMusicWakeState
}

void DummySoundManager::DoMusic(const std::string &name, bool bLoop) {
 // TODO: Implement DoMusic
}

float DummySoundManager::getMusicPosition() {
 // TODO: Implement getMusicPosition
 return 0;
}

void DummySoundManager::CheckDoMusic() {
 // TODO: Implement CheckDoMusic
}

void DummySoundManager::stopMusic(const std::string &name) {
 // TODO: Implement stopMusic
}

void DummySoundManager::playMusicNonTriggered(const std::string &name,
 float gain) {
 // TODO: Implement playMusicNonTriggered
}

void DummySoundManager::playAmbient(const std::string &name) {
 // TODO: Implement playAmbient
}

void DummySoundManager::playMusic(const std::string &name) {
 // TODO: Implement playMusic
}

bool DummySoundManager::isPlayingMusic() {
 // TODO: Implement isPlayingMusic
 return false;
}

bool DummySoundManager::IsMusicPlaying() {
 // TODO: Implement IsMusicPlaying
 return false;
}

void DummySoundManager::PlayAsMusic(const std::string &name, Audio musicTrack,
 float volume, bool bloop) {
 // TODO: Implement PlayAsMusic
}

long DummySoundManager::playUISound(const std::string &name) {
 // TODO: Implement playUISound
 return 0;
}

bool DummySoundManager::isPlayingUISound(const std::string &name) {
 // TODO: Implement isPlayingUISound
 return false;
}

bool DummySoundManager::isPlayingUISound(long eventInstance) {
 // TODO: Implement isPlayingUISound
 return false;
}

void DummySoundManager::stopUISound(long eventInstance) {
 // TODO: Implement stopUISound
}

void DummySoundManager::FadeOutMusic(const std::string &name, int milli) {
 // TODO: Implement FadeOutMusic
}

Audio DummySoundManager::BlendThenStart(Audio musicTrack, float f,
 const std::string &PrefMusic) {
 // TODO: Implement BlendThenStart
 return nullptr;
}

void DummySoundManager::BlendVolume(Audio audio, float targetVolume,
 float blendSpeedAlpha) {
 // TODO: Implement BlendVolume
}

void DummySoundManager::BlendVolume(Audio audio, float targetVolume) {
 // TODO: Implement BlendVolume
}

void DummySoundManager::setSoundVolume(float volume) {
 // TODO: Implement setSoundVolume
}

float DummySoundManager::getSoundVolume() {
 // TODO: Implement getSoundVolume
 return 0;
}

void DummySoundManager::setMusicVolume(float volume) {
 // TODO: Implement setMusicVolume
}

float DummySoundManager::getMusicVolume() {
 // TODO: Implement getMusicVolume
 return 0;
}

void DummySoundManager::setVehicleEngineVolume(float volume) {
 // TODO: Implement setVehicleEngineVolume
}

float DummySoundManager::getVehicleEngineVolume() {
 // TODO: Implement getVehicleEngineVolume
 return 0;
}

void DummySoundManager::setAmbientVolume(float volume) {
 // TODO: Implement setAmbientVolume
}

float DummySoundManager::getAmbientVolume() {
 // TODO: Implement getAmbientVolume
 return 0;
}

void DummySoundManager::playNightAmbient(const std::string &choice) {
 // TODO: Implement playNightAmbient
}

void DummySoundManager::pauseSoundAndMusic() {
 // TODO: Implement pauseSoundAndMusic
}

void DummySoundManager::resumeSoundAndMusic() {
 // TODO: Implement resumeSoundAndMusic
}

void DummySoundManager::debugScriptSounds() {
 // TODO: Implement debugScriptSounds
}

void DummySoundManager::registerEmitter(BaseSoundEmitter emitter) {
 // TODO: Implement registerEmitter
}

void DummySoundManager::unregisterEmitter(BaseSoundEmitter emitter) {
 // TODO: Implement unregisterEmitter
}

bool DummySoundManager::isListenerInRange(float x, float y, float range) {
 // TODO: Implement isListenerInRange
 return false;
}

Audio DummySoundManager::PlayWorldSoundWavImpl(const std::string &name,
 bool loop, IsoGridSquare source,
 float pitchVar, float radius,
 float maxGain,
 bool ignoreOutside) {
 // TODO: Implement PlayWorldSoundWavImpl
 return nullptr;
}

std::string DummySoundManager::getCurrentMusicName() {
 // TODO: Implement getCurrentMusicName
 return "";
}

std::string DummySoundManager::getCurrentMusicLibrary() {
 // TODO: Implement getCurrentMusicLibrary
 return "";
}

} // namespace zombie

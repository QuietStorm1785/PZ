#include "zombie/SoundManager.h"

namespace zombie {

void SoundManager::timelineMarker(long var1, const std::string &string,
 int int0) {
 // TODO: Implement timelineMarker
}

FMODParameterList SoundManager::getFMODParameters() {
 // TODO: Implement getFMODParameters
 return nullptr;
}

void SoundManager::startEvent(long eventInstance, GameSoundClip clip,
 BitSet parameterSet) {
 // TODO: Implement startEvent
}

void SoundManager::updateEvent(long eventInstance, GameSoundClip clip) {
 // TODO: Implement updateEvent
}

void SoundManager::stopEvent(long eventInstance, GameSoundClip clip,
 BitSet parameterSet) {
 // TODO: Implement stopEvent
}

bool SoundManager::isRemastered() {
 // TODO: Implement isRemastered
 return false;
}

void SoundManager::BlendVolume(Audio audio, float targetVolume) {
 // TODO: Implement BlendVolume
}

void SoundManager::BlendVolume(Audio audio, float targetVolume,
 float blendSpeedAlpha) {
 // TODO: Implement BlendVolume
}

Audio SoundManager::BlendThenStart(Audio musicTrack, float f,
 const std::string &PrefMusic) {
 // TODO: Implement BlendThenStart
 return nullptr;
}

void SoundManager::FadeOutMusic(const std::string &name, int milli) {
 // TODO: Implement FadeOutMusic
}

void SoundManager::PlayAsMusic(const std::string &name, Audio musicTrack,
 float volume, bool bloop) {
 // TODO: Implement PlayAsMusic
}

long SoundManager::playUISound(const std::string &name) {
 // TODO: Implement playUISound
 return 0;
}

bool SoundManager::isPlayingUISound(const std::string &name) {
 // TODO: Implement isPlayingUISound
 return false;
}

bool SoundManager::isPlayingUISound(long eventInstance) {
 // TODO: Implement isPlayingUISound
 return false;
}

void SoundManager::stopUISound(long eventInstance) {
 // TODO: Implement stopUISound
}

bool SoundManager::IsMusicPlaying() {
 // TODO: Implement IsMusicPlaying
 return false;
}

bool SoundManager::isPlayingMusic() {
 // TODO: Implement isPlayingMusic
 return false;
}

void SoundManager::gatherInGameEventInstances() {
 // TODO: Implement gatherInGameEventInstances
}

void SoundManager::pauseSoundAndMusic() {
 // TODO: Implement pauseSoundAndMusic
}

void SoundManager::resumeSoundAndMusic() {
 // TODO: Implement resumeSoundAndMusic
}

void SoundManager::debugScriptSound(Item item, const std::string &string) {
 // TODO: Implement debugScriptSound
}

void SoundManager::debugScriptSounds() {
 // TODO: Implement debugScriptSounds
}

void SoundManager::registerEmitter(BaseSoundEmitter emitter) {
 // TODO: Implement registerEmitter
}

void SoundManager::unregisterEmitter(BaseSoundEmitter emitter) {
 // TODO: Implement unregisterEmitter
}

bool SoundManager::isListenerInRange(float x, float y, float range) {
 // TODO: Implement isListenerInRange
 return false;
}

void SoundManager::playNightAmbient(const std::string &choice) {
 // TODO: Implement playNightAmbient
}

void SoundManager::playMusic(const std::string &name) {
 // TODO: Implement playMusic
}

void SoundManager::playAmbient(const std::string &name) {
 // TODO: Implement playAmbient
}

void SoundManager::playMusicNonTriggered(const std::string &name, float gain) {
 // TODO: Implement playMusicNonTriggered
}

void SoundManager::stopMusic(const std::string &name) {
 // TODO: Implement stopMusic
}

void SoundManager::CheckDoMusic() {
 // TODO: Implement CheckDoMusic
}

float SoundManager::getMusicPosition() {
 // TODO: Implement getMusicPosition
 return 0;
}

void SoundManager::DoMusic(const std::string &name, bool bLoop) {
 // TODO: Implement DoMusic
}

void SoundManager::PlayAsMusic(const std::string &name, Audio musicTrack,
 bool loop, float volume) {
 // TODO: Implement PlayAsMusic
}

void SoundManager::setMusicState(const std::string &stateName) {
 // TODO: Implement setMusicState
}

void SoundManager::setMusicWakeState(IsoPlayer player,
 const std::string &stateName) {
 // TODO: Implement setMusicWakeState
}

Audio SoundManager::PlayMusic(const std::string &n, const std::string &name,
 bool loop, float maxGain) {
 // TODO: Implement PlayMusic
 return nullptr;
}

Audio SoundManager::PlaySound(const std::string &name, bool loop, float maxGain,
 float pitchVar) {
 // TODO: Implement PlaySound
 return nullptr;
}

Audio SoundManager::PlaySound(const std::string &name, bool loop,
 float maxGain) {
 // TODO: Implement PlaySound
 return nullptr;
}

Audio SoundManager::PlaySoundEvenSilent(const std::string &name, bool loop,
 float maxGain) {
 // TODO: Implement PlaySoundEvenSilent
 return nullptr;
}

Audio SoundManager::PlayJukeboxSound(const std::string &name, bool loop,
 float maxGain) {
 // TODO: Implement PlayJukeboxSound
 return nullptr;
}

Audio SoundManager::PlaySoundWav(const std::string &name, bool loop,
 float maxGain, float pitchVar) {
 // TODO: Implement PlaySoundWav
 return nullptr;
}

Audio SoundManager::PlaySoundWav(const std::string &name, bool loop,
 float maxGain) {
 // TODO: Implement PlaySoundWav
 return nullptr;
}

Audio SoundManager::PlaySoundWav(const std::string &name, int variations,
 bool loop, float maxGain) {
 // TODO: Implement PlaySoundWav
 return nullptr;
}

void SoundManager::update3D() {
 // TODO: Implement update3D
}

Audio SoundManager::PlayWorldSound(const std::string &name,
 IsoGridSquare source, float pitchVar,
 float radius, float maxGain,
 bool ignoreOutside) {
 // TODO: Implement PlayWorldSound
 return nullptr;
}

Audio SoundManager::PlayWorldSound(const std::string &name, bool loop,
 IsoGridSquare source, float pitchVar,
 float radius, float maxGain,
 bool ignoreOutside) {
 // TODO: Implement PlayWorldSound
 return nullptr;
}

Audio SoundManager::PlayWorldSoundImpl(const std::string &name, bool loop,
 int sx, int sy, int sz, float pitchVar,
 float radius, float maxGain,
 bool ignoreOutside) {
 // TODO: Implement PlayWorldSoundImpl
 return nullptr;
}

Audio SoundManager::PlayWorldSound(const std::string &name,
 IsoGridSquare source, float pitchVar,
 float radius, float maxGain, int choices,
 bool ignoreOutside) {
 // TODO: Implement PlayWorldSound
 return nullptr;
}

Audio SoundManager::PlayWorldSoundWav(const std::string &name,
 IsoGridSquare source, float pitchVar,
 float radius, float maxGain,
 bool ignoreOutside) {
 // TODO: Implement PlayWorldSoundWav
 return nullptr;
}

Audio SoundManager::PlayWorldSoundWav(const std::string &name, bool loop,
 IsoGridSquare source, float pitchVar,
 float radius, float maxGain,
 bool ignoreOutside) {
 // TODO: Implement PlayWorldSoundWav
 return nullptr;
}

Audio SoundManager::PlayWorldSoundWavImpl(const std::string &name, bool loop,
 IsoGridSquare source, float pitchVar,
 float radius, float maxGain,
 bool ignoreOutside) {
 // TODO: Implement PlayWorldSoundWavImpl
 return nullptr;
}

void SoundManager::PlayWorldSoundWav(const std::string &name,
 IsoGridSquare source, float pitchVar,
 float radius, float maxGain, int choices,
 bool ignoreOutside) {
 // TODO: Implement PlayWorldSoundWav
}

Audio SoundManager::PrepareMusic(const std::string &name) {
 // TODO: Implement PrepareMusic
 return nullptr;
}

Audio SoundManager::Start(Audio musicTrack, float f,
 const std::string &PrefMusic) {
 // TODO: Implement Start
 return nullptr;
}

void SoundManager::Update() {
 // TODO: Implement Update
}

bool SoundManager::HasMusic(Audio var1) {
 // TODO: Implement HasMusic
 return false;
}

void SoundManager::Purge() {
 // TODO: Implement Purge
}

void SoundManager::stop() {
 // TODO: Implement stop
}

void SoundManager::StopMusic() {
 // TODO: Implement StopMusic
}

void SoundManager::StopSound(Audio SoundEffect) {
 // TODO: Implement StopSound
}

void SoundManager::CacheSound(const std::string &file) {
 // TODO: Implement CacheSound
}

void SoundManager::update4() {
 // TODO: Implement update4
}

void SoundManager::update2() {
 // TODO: Implement update2
}

void SoundManager::update3() {
 // TODO: Implement update3
}

void SoundManager::update1() {
 // TODO: Implement update1
}

void SoundManager::setSoundVolume(float volume) {
 // TODO: Implement setSoundVolume
}

float SoundManager::getSoundVolume() {
 // TODO: Implement getSoundVolume
 return 0;
}

void SoundManager::setAmbientVolume(float volume) {
 // TODO: Implement setAmbientVolume
}

float SoundManager::getAmbientVolume() {
 // TODO: Implement getAmbientVolume
 return 0;
}

void SoundManager::setMusicVolume(float volume) {
 // TODO: Implement setMusicVolume
}

float SoundManager::getMusicVolume() {
 // TODO: Implement getMusicVolume
 return 0;
}

void SoundManager::setVehicleEngineVolume(float volume) {
 // TODO: Implement setVehicleEngineVolume
}

float SoundManager::getVehicleEngineVolume() {
 // TODO: Implement getVehicleEngineVolume
 return 0;
}

std::string SoundManager::getCurrentMusicName() {
 // TODO: Implement getCurrentMusicName
 return "";
}

std::string SoundManager::getCurrentMusicLibrary() {
 // TODO: Implement getCurrentMusicLibrary
 return "";
}

void SoundManager::updateMusic() {
 // TODO: Implement updateMusic
}

public
SoundManager::AmbientSoundEffect(const std::string &_name) {
 // TODO: Implement AmbientSoundEffect
 return nullptr;
}

void SoundManager::setVolume(float volume) {
 // TODO: Implement setVolume
}

void SoundManager::start() {
 // TODO: Implement start
}

void SoundManager::pause() {
 // TODO: Implement pause
}

void SoundManager::stop() {
 // TODO: Implement stop
}

bool SoundManager::isPlaying() {
 // TODO: Implement isPlaying
 return false;
}

void SoundManager::setName(const std::string &choice) {
 // TODO: Implement setName
}

std::string SoundManager::getName() {
 // TODO: Implement getName
 return "";
}

void SoundManager::update() {
 // TODO: Implement update
}

bool SoundManager::isPlaying() {
 // TODO: Implement isPlaying
 return false;
}

void SoundManager::update() {
 // TODO: Implement update
}

float SoundManager::getPosition() {
 // TODO: Implement getPosition
 return 0;
}

void SoundManager::stop() {
 // TODO: Implement stop
}

} // namespace zombie

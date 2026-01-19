#pragma once
#include "fmod/fmod/Audio.h"
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/iso/IsoGridSquare.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class DummySoundManager : public BaseSoundManager {
public:
private
 static ArrayList<Audio> ambientPieces = std::make_unique<ArrayList<>>();

 bool isRemastered() { return false; }

 void update1() {}

 void update3() {}

 void update2() {}

 void update4() {}

 void CacheSound(std::string_view file) {}

 void StopSound(Audio SoundEffect) {}

 void StopMusic() {}

 void Purge() {}

 void stop() {}

 bool HasMusic(Audio var1) { return false; }

 void Update() {}

 Audio Start(Audio musicTrack, float f, std::string_view PrefMusic) {
 return nullptr;
 }

 Audio PrepareMusic(std::string_view name) { return nullptr; }

 void PlayWorldSoundWav(std::string_view name, IsoGridSquare source,
 float pitchVar, float radius, float maxGain,
 int choices, bool ignoreOutside) {}

 Audio PlayWorldSoundWav(std::string_view name, bool loop,
 IsoGridSquare source, float pitchVar, float radius,
 float maxGain, bool ignoreOutside) {
 return nullptr;
 }

 Audio PlayWorldSoundWav(std::string_view name, IsoGridSquare source,
 float pitchVar, float radius, float maxGain,
 bool ignoreOutside) {
 return nullptr;
 }

 Audio PlayWorldSound(std::string_view name, IsoGridSquare source,
 float pitchVar, float radius, float maxGain, int choices,
 bool ignoreOutside) {
 return nullptr;
 }

 Audio PlayWorldSound(std::string_view name, bool loop, IsoGridSquare source,
 float pitchVar, float radius, float maxGain,
 bool ignoreOutside) {
 return nullptr;
 }

 Audio PlayWorldSoundImpl(std::string_view name, bool loop, int sx, int sy,
 int sz, float pitchVar, float radius, float maxGain,
 bool ignoreOutside) {
 return nullptr;
 }

 Audio PlayWorldSound(std::string_view name, IsoGridSquare source,
 float pitchVar, float radius, float maxGain,
 bool ignoreOutside) {
 return nullptr;
 }

 void update3D() {}

 Audio PlaySoundWav(std::string_view name, int variations, bool loop,
 float maxGain) {
 return nullptr;
 }

 Audio PlaySoundWav(std::string_view name, bool loop, float maxGain) {
 return nullptr;
 }

 Audio PlaySoundWav(std::string_view name, bool loop, float maxGain,
 float pitchVar) {
 return nullptr;
 }

 Audio PlayJukeboxSound(std::string_view name, bool loop, float maxGain) {
 return nullptr;
 }

 Audio PlaySoundEvenSilent(std::string_view name, bool loop, float maxGain) {
 return nullptr;
 }

 Audio PlaySound(std::string_view name, bool loop, float maxGain) {
 return nullptr;
 }

 Audio PlaySound(std::string_view name, bool loop, float pitchVar,
 float maxGain) {
 return nullptr;
 }

 Audio PlayMusic(std::string_view n, std::string_view name, bool loop,
 float maxGain) {
 return nullptr;
 }

 void PlayAsMusic(std::string_view name, Audio musicTrack, bool loop,
 float volume) {}

 void setMusicState(std::string_view stateName) {}

 void setMusicWakeState(IsoPlayer player, std::string_view stateName) {}

 void DoMusic(std::string_view name, bool bLoop) {}

 float getMusicPosition() { return 0.0F; }

 void CheckDoMusic() {}

 void stopMusic(std::string_view name) {}

 void playMusicNonTriggered(std::string_view name, float gain) {}

 void playAmbient(std::string_view name) {}

 void playMusic(std::string_view name) {}

 bool isPlayingMusic() { return false; }

 bool IsMusicPlaying() { return false; }

 void PlayAsMusic(std::string_view name, Audio musicTrack, float volume,
 bool bloop) {}

 long playUISound(std::string_view name) { return 0L; }

 bool isPlayingUISound(std::string_view name) { return false; }

 bool isPlayingUISound(long eventInstance) { return false; }

 void stopUISound(long eventInstance) {}

 void FadeOutMusic(std::string_view name, int milli) {}

 Audio BlendThenStart(Audio musicTrack, float f,
 std::string_view PrefMusic) {
 return nullptr;
 }

 void BlendVolume(Audio audio, float targetVolume, float blendSpeedAlpha) {}

 void BlendVolume(Audio audio, float targetVolume) {}

 void setSoundVolume(float volume) {}

 float getSoundVolume() { return 0.0F; }

 void setMusicVolume(float volume) {}

 float getMusicVolume() { return 0.0F; }

 void setVehicleEngineVolume(float volume) {}

 float getVehicleEngineVolume() { return 0.0F; }

 void setAmbientVolume(float volume) {}

 float getAmbientVolume() { return 0.0F; }

 void playNightAmbient(std::string_view choice) {}

public
 ArrayList<Audio> getAmbientPieces() { return ambientPieces; }

 void pauseSoundAndMusic() {}

 void resumeSoundAndMusic() {}

 void debugScriptSounds() {}

 void registerEmitter(BaseSoundEmitter emitter) {}

 void unregisterEmitter(BaseSoundEmitter emitter) {}

 bool isListenerInRange(float x, float y, float range) { return false; }

 Audio PlayWorldSoundWavImpl(std::string_view name, bool loop,
 IsoGridSquare source, float pitchVar,
 float radius, float maxGain, bool ignoreOutside) {
 return nullptr;
 }

 std::string getCurrentMusicName() { return nullptr; }

 std::string getCurrentMusicLibrary() { return nullptr; }
}
} // namespace zombie

#pragma once
#include "fmod/fmod/Audio.h"
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/iso/IsoGridSquare.h"
#include <cstdint>
#include <memory>
#include <string>
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

  void CacheSound(const std::string &file) {}

  void StopSound(Audio SoundEffect) {}

  void StopMusic() {}

  void Purge() {}

  void stop() {}

  bool HasMusic(Audio var1) { return false; }

  void Update() {}

  Audio Start(Audio musicTrack, float f, const std::string &PrefMusic) {
    return null;
  }

  Audio PrepareMusic(const std::string &name) { return null; }

  void PlayWorldSoundWav(const std::string &name, IsoGridSquare source,
                         float pitchVar, float radius, float maxGain,
                         int choices, bool ignoreOutside) {}

  Audio PlayWorldSoundWav(const std::string &name, bool loop,
                          IsoGridSquare source, float pitchVar, float radius,
                          float maxGain, bool ignoreOutside) {
    return null;
  }

  Audio PlayWorldSoundWav(const std::string &name, IsoGridSquare source,
                          float pitchVar, float radius, float maxGain,
                          bool ignoreOutside) {
    return null;
  }

  Audio PlayWorldSound(const std::string &name, IsoGridSquare source,
                       float pitchVar, float radius, float maxGain, int choices,
                       bool ignoreOutside) {
    return null;
  }

  Audio PlayWorldSound(const std::string &name, bool loop, IsoGridSquare source,
                       float pitchVar, float radius, float maxGain,
                       bool ignoreOutside) {
    return null;
  }

  Audio PlayWorldSoundImpl(const std::string &name, bool loop, int sx, int sy,
                           int sz, float pitchVar, float radius, float maxGain,
                           bool ignoreOutside) {
    return null;
  }

  Audio PlayWorldSound(const std::string &name, IsoGridSquare source,
                       float pitchVar, float radius, float maxGain,
                       bool ignoreOutside) {
    return null;
  }

  void update3D() {}

  Audio PlaySoundWav(const std::string &name, int variations, bool loop,
                     float maxGain) {
    return null;
  }

  Audio PlaySoundWav(const std::string &name, bool loop, float maxGain) {
    return null;
  }

  Audio PlaySoundWav(const std::string &name, bool loop, float maxGain,
                     float pitchVar) {
    return null;
  }

  Audio PlayJukeboxSound(const std::string &name, bool loop, float maxGain) {
    return null;
  }

  Audio PlaySoundEvenSilent(const std::string &name, bool loop, float maxGain) {
    return null;
  }

  Audio PlaySound(const std::string &name, bool loop, float maxGain) {
    return null;
  }

  Audio PlaySound(const std::string &name, bool loop, float pitchVar,
                  float maxGain) {
    return null;
  }

  Audio PlayMusic(const std::string &n, const std::string &name, bool loop,
                  float maxGain) {
    return null;
  }

  void PlayAsMusic(const std::string &name, Audio musicTrack, bool loop,
                   float volume) {}

  void setMusicState(const std::string &stateName) {}

  void setMusicWakeState(IsoPlayer player, const std::string &stateName) {}

  void DoMusic(const std::string &name, bool bLoop) {}

  float getMusicPosition() { return 0.0F; }

  void CheckDoMusic() {}

  void stopMusic(const std::string &name) {}

  void playMusicNonTriggered(const std::string &name, float gain) {}

  void playAmbient(const std::string &name) {}

  void playMusic(const std::string &name) {}

  bool isPlayingMusic() { return false; }

  bool IsMusicPlaying() { return false; }

  void PlayAsMusic(const std::string &name, Audio musicTrack, float volume,
                   bool bloop) {}

  long playUISound(const std::string &name) { return 0L; }

  bool isPlayingUISound(const std::string &name) { return false; }

  bool isPlayingUISound(long eventInstance) { return false; }

  void stopUISound(long eventInstance) {}

  void FadeOutMusic(const std::string &name, int milli) {}

  Audio BlendThenStart(Audio musicTrack, float f,
                       const std::string &PrefMusic) {
    return null;
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

  void playNightAmbient(const std::string &choice) {}

public
  ArrayList<Audio> getAmbientPieces() { return ambientPieces; }

  void pauseSoundAndMusic() {}

  void resumeSoundAndMusic() {}

  void debugScriptSounds() {}

  void registerEmitter(BaseSoundEmitter emitter) {}

  void unregisterEmitter(BaseSoundEmitter emitter) {}

  bool isListenerInRange(float x, float y, float range) { return false; }

  Audio PlayWorldSoundWavImpl(const std::string &name, bool loop,
                              IsoGridSquare source, float pitchVar,
                              float radius, float maxGain, bool ignoreOutside) {
    return null;
  }

  std::string getCurrentMusicName() { return null; }

  std::string getCurrentMusicLibrary() { return null; }
}
} // namespace zombie

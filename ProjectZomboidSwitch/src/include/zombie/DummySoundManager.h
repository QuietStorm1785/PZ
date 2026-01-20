#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/Audio.h"
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/iso/IsoGridSquare.h"

namespace zombie {


class DummySoundManager : public BaseSoundManager {
public:
   private static std::vector<Audio> ambientPieces = std::make_unique<std::vector<>>();

    bool isRemastered() {
    return false;
   }

    void update1() {
   }

    void update3() {
   }

    void update2() {
   }

    void update4() {
   }

    void CacheSound(const std::string& var1) {
   }

    void StopSound(Audio var1) {
   }

    void StopMusic() {
   }

    void Purge() {
   }

    void stop() {
   }

    bool HasMusic(Audio var1) {
    return false;
   }

    void Update() {
   }

    Audio Start(Audio var1, float var2, const std::string& var3) {
    return nullptr;
   }

    Audio PrepareMusic(const std::string& var1) {
    return nullptr;
   }

    void PlayWorldSoundWav(const std::string& var1, IsoGridSquare var2, float var3, float var4, float var5, int var6, bool var7) {
   }

    Audio PlayWorldSoundWav(const std::string& var1, bool var2, IsoGridSquare var3, float var4, float var5, float var6, bool var7) {
    return nullptr;
   }

    Audio PlayWorldSoundWav(const std::string& var1, IsoGridSquare var2, float var3, float var4, float var5, bool var6) {
    return nullptr;
   }

    Audio PlayWorldSound(const std::string& var1, IsoGridSquare var2, float var3, float var4, float var5, int var6, bool var7) {
    return nullptr;
   }

    Audio PlayWorldSound(const std::string& var1, bool var2, IsoGridSquare var3, float var4, float var5, float var6, bool var7) {
    return nullptr;
   }

    Audio PlayWorldSoundImpl(const std::string& var1, bool var2, int var3, int var4, int var5, float var6, float var7, float var8, bool var9) {
    return nullptr;
   }

    Audio PlayWorldSound(const std::string& var1, IsoGridSquare var2, float var3, float var4, float var5, bool var6) {
    return nullptr;
   }

    void update3D() {
   }

    Audio PlaySoundWav(const std::string& var1, int var2, bool var3, float var4) {
    return nullptr;
   }

    Audio PlaySoundWav(const std::string& var1, bool var2, float var3) {
    return nullptr;
   }

    Audio PlaySoundWav(const std::string& var1, bool var2, float var3, float var4) {
    return nullptr;
   }

    Audio PlayJukeboxSound(const std::string& var1, bool var2, float var3) {
    return nullptr;
   }

    Audio PlaySoundEvenSilent(const std::string& var1, bool var2, float var3) {
    return nullptr;
   }

    Audio PlaySound(const std::string& var1, bool var2, float var3) {
    return nullptr;
   }

    Audio PlaySound(const std::string& var1, bool var2, float var3, float var4) {
    return nullptr;
   }

    Audio PlayMusic(const std::string& var1, const std::string& var2, bool var3, float var4) {
    return nullptr;
   }

    void PlayAsMusic(const std::string& var1, Audio var2, bool var3, float var4) {
   }

    void setMusicState(const std::string& var1) {
   }

    void setMusicWakeState(IsoPlayer var1, const std::string& var2) {
   }

    void DoMusic(const std::string& var1, bool var2) {
   }

    float getMusicPosition() {
      return 0.0F;
   }

    void CheckDoMusic() {
   }

    void stopMusic(const std::string& var1) {
   }

    void playMusicNonTriggered(const std::string& var1, float var2) {
   }

    void playAmbient(const std::string& var1) {
   }

    void playMusic(const std::string& var1) {
   }

    bool isPlayingMusic() {
    return false;
   }

    bool IsMusicPlaying() {
    return false;
   }

    void PlayAsMusic(const std::string& var1, Audio var2, float var3, bool var4) {
   }

    long playUISound(const std::string& var1) {
    return 0L;
   }

    bool isPlayingUISound(const std::string& var1) {
    return false;
   }

    bool isPlayingUISound(long var1) {
    return false;
   }

    void stopUISound(long var1) {
   }

    void FadeOutMusic(const std::string& var1, int var2) {
   }

    Audio BlendThenStart(Audio var1, float var2, const std::string& var3) {
    return nullptr;
   }

    void BlendVolume(Audio var1, float var2, float var3) {
   }

    void BlendVolume(Audio var1, float var2) {
   }

    void setSoundVolume(float var1) {
   }

    float getSoundVolume() {
      return 0.0F;
   }

    void setMusicVolume(float var1) {
   }

    float getMusicVolume() {
      return 0.0F;
   }

    void setVehicleEngineVolume(float var1) {
   }

    float getVehicleEngineVolume() {
      return 0.0F;
   }

    void setAmbientVolume(float var1) {
   }

    float getAmbientVolume() {
      return 0.0F;
   }

    void playNightAmbient(const std::string& var1) {
   }

   public std::vector<Audio> getAmbientPieces() {
    return ambientPieces;
   }

    void pauseSoundAndMusic() {
   }

    void resumeSoundAndMusic() {
   }

    void debugScriptSounds() {
   }

    void registerEmitter(BaseSoundEmitter var1) {
   }

    void unregisterEmitter(BaseSoundEmitter var1) {
   }

    bool isListenerInRange(float var1, float var2, float var3) {
    return false;
   }

    Audio PlayWorldSoundWavImpl(const std::string& var1, bool var2, IsoGridSquare var3, float var4, float var5, float var6, bool var7) {
    return nullptr;
   }

    std::string getCurrentMusicName() {
    return nullptr;
   }

    std::string getCurrentMusicLibrary() {
    return nullptr;
   }
}
} // namespace zombie

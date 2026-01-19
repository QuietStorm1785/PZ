#pragma once
#include <string>
#include <string_view>
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


class DummySoundManager :  BaseSoundManager {
:
   private static ArrayList<Audio> ambientPieces = std::make_unique<ArrayList<>>();

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

    void CacheSound(std::string_view var1) {
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

    Audio Start(Audio var1, float var2, std::string_view var3) {
    return nullptr;
   }

    Audio PrepareMusic(std::string_view var1) {
    return nullptr;
   }

    void PlayWorldSoundWav(std::string_view var1, IsoGridSquare var2, float var3, float var4, float var5, int var6, bool var7) {
   }

    Audio PlayWorldSoundWav(std::string_view var1, bool var2, IsoGridSquare var3, float var4, float var5, float var6, bool var7) {
    return nullptr;
   }

    Audio PlayWorldSoundWav(std::string_view var1, IsoGridSquare var2, float var3, float var4, float var5, bool var6) {
    return nullptr;
   }

    Audio PlayWorldSound(std::string_view var1, IsoGridSquare var2, float var3, float var4, float var5, int var6, bool var7) {
    return nullptr;
   }

    Audio PlayWorldSound(std::string_view var1, bool var2, IsoGridSquare var3, float var4, float var5, float var6, bool var7) {
    return nullptr;
   }

    Audio PlayWorldSoundImpl(std::string_view var1, bool var2, int var3, int var4, int var5, float var6, float var7, float var8, bool var9) {
    return nullptr;
   }

    Audio PlayWorldSound(std::string_view var1, IsoGridSquare var2, float var3, float var4, float var5, bool var6) {
    return nullptr;
   }

    void update3D() {
   }

    Audio PlaySoundWav(std::string_view var1, int var2, bool var3, float var4) {
    return nullptr;
   }

    Audio PlaySoundWav(std::string_view var1, bool var2, float var3) {
    return nullptr;
   }

    Audio PlaySoundWav(std::string_view var1, bool var2, float var3, float var4) {
    return nullptr;
   }

    Audio PlayJukeboxSound(std::string_view var1, bool var2, float var3) {
    return nullptr;
   }

    Audio PlaySoundEvenSilent(std::string_view var1, bool var2, float var3) {
    return nullptr;
   }

    Audio PlaySound(std::string_view var1, bool var2, float var3) {
    return nullptr;
   }

    Audio PlaySound(std::string_view var1, bool var2, float var3, float var4) {
    return nullptr;
   }

    Audio PlayMusic(std::string_view var1, std::string_view var2, bool var3, float var4) {
    return nullptr;
   }

    void PlayAsMusic(std::string_view var1, Audio var2, bool var3, float var4) {
   }

    void setMusicState(std::string_view var1) {
   }

    void setMusicWakeState(IsoPlayer var1, std::string_view var2) {
   }

    void DoMusic(std::string_view var1, bool var2) {
   }

    float getMusicPosition() const {
      return 0.0F;
   }

    void CheckDoMusic() {
   }

    void stopMusic(std::string_view var1) {
   }

    void playMusicNonTriggered(std::string_view var1, float var2) {
   }

    void playAmbient(std::string_view var1) {
   }

    void playMusic(std::string_view var1) {
   }

    bool isPlayingMusic() {
    return false;
   }

    bool IsMusicPlaying() {
    return false;
   }

    void PlayAsMusic(std::string_view var1, Audio var2, float var3, bool var4) {
   }

    long playUISound(std::string_view var1) {
    return 0L;
   }

    bool isPlayingUISound(std::string_view var1) {
    return false;
   }

    bool isPlayingUISound(long var1) {
    return false;
   }

    void stopUISound(long var1) {
   }

    void FadeOutMusic(std::string_view var1, int var2) {
   }

    Audio BlendThenStart(Audio var1, float var2, std::string_view var3) {
    return nullptr;
   }

    void BlendVolume(Audio var1, float var2, float var3) {
   }

    void BlendVolume(Audio var1, float var2) {
   }

    void setSoundVolume(float var1) {
   }

    float getSoundVolume() const {
      return 0.0F;
   }

    void setMusicVolume(float var1) {
   }

    float getMusicVolume() const {
      return 0.0F;
   }

    void setVehicleEngineVolume(float var1) {
   }

    float getVehicleEngineVolume() const {
      return 0.0F;
   }

    void setAmbientVolume(float var1) {
   }

    float getAmbientVolume() const {
      return 0.0F;
   }

    void playNightAmbient(std::string_view var1) {
   }

    ArrayList<Audio> getAmbientPieces() {
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

    Audio PlayWorldSoundWavImpl(std::string_view var1, bool var2, IsoGridSquare var3, float var4, float var5, float var6, bool var7) {
    return nullptr;
   }

    std::string getCurrentMusicName() const {
    return nullptr;
   }

    std::string getCurrentMusicLibrary() const {
    return nullptr;
   }
}
} // namespace zombie

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


class BaseSoundManager {
public:
    bool AllowMusic = true;

   public abstract boolean isRemastered();

   public abstract void update1();

   public abstract void update3();

   public abstract void update2();

   public abstract void update4();

   public abstract void CacheSound(std::string var1);

   public abstract void StopSound(Audio var1);

   public abstract void StopMusic();

   public abstract void Purge();

   public abstract void stop();

   protected abstract boolean HasMusic(Audio var1);

   public abstract void Update();

   public abstract Audio Start(Audio var1, float var2, std::string var3);

   public abstract Audio PrepareMusic(std::string var1);

   public abstract void PlayWorldSoundWav(std::string var1, IsoGridSquare var2, float var3, float var4, float var5, int var6, boolean var7);

   public abstract Audio PlayWorldSoundWav(std::string var1, boolean var2, IsoGridSquare var3, float var4, float var5, float var6, boolean var7);

   public abstract Audio PlayWorldSoundWav(std::string var1, IsoGridSquare var2, float var3, float var4, float var5, boolean var6);

   public abstract Audio PlayWorldSound(std::string var1, IsoGridSquare var2, float var3, float var4, float var5, int var6, boolean var7);

   public abstract Audio PlayWorldSound(std::string var1, boolean var2, IsoGridSquare var3, float var4, float var5, float var6, boolean var7);

   public abstract Audio PlayWorldSoundImpl(std::string var1, boolean var2, int var3, int var4, int var5, float var6, float var7, float var8, boolean var9);

   public abstract Audio PlayWorldSound(std::string var1, IsoGridSquare var2, float var3, float var4, float var5, boolean var6);

   public abstract void update3D();

   public abstract Audio PlaySoundWav(std::string var1, int var2, boolean var3, float var4);

   public abstract Audio PlaySoundWav(std::string var1, boolean var2, float var3);

   public abstract Audio PlaySoundWav(std::string var1, boolean var2, float var3, float var4);

   public abstract Audio PlayWorldSoundWavImpl(std::string var1, boolean var2, IsoGridSquare var3, float var4, float var5, float var6, boolean var7);

   public abstract Audio PlayJukeboxSound(std::string var1, boolean var2, float var3);

   public abstract Audio PlaySoundEvenSilent(std::string var1, boolean var2, float var3);

   public abstract Audio PlaySound(std::string var1, boolean var2, float var3);

   public abstract Audio PlaySound(std::string var1, boolean var2, float var3, float var4);

   public abstract Audio PlayMusic(std::string var1, std::string var2, boolean var3, float var4);

   public abstract void PlayAsMusic(std::string var1, Audio var2, boolean var3, float var4);

   public abstract void setMusicState(std::string var1);

   public abstract void setMusicWakeState(IsoPlayer var1, std::string var2);

   public abstract void DoMusic(std::string var1, boolean var2);

   public abstract float getMusicPosition();

   public abstract void CheckDoMusic();

   public abstract void stopMusic(std::string var1);

   public abstract void playMusicNonTriggered(std::string var1, float var2);

   public abstract void playAmbient(std::string var1);

   public abstract void playMusic(std::string var1);

   public abstract boolean isPlayingMusic();

   public abstract boolean IsMusicPlaying();

   public abstract std::string getCurrentMusicName();

   public abstract std::string getCurrentMusicLibrary();

   public abstract void PlayAsMusic(std::string var1, Audio var2, float var3, boolean var4);

   public abstract long playUISound(std::string var1);

   public abstract boolean isPlayingUISound(std::string var1);

   public abstract boolean isPlayingUISound(long var1);

   public abstract void stopUISound(long var1);

   public abstract void FadeOutMusic(std::string var1, int var2);

   public abstract Audio BlendThenStart(Audio var1, float var2, std::string var3);

   public abstract void BlendVolume(Audio var1, float var2, float var3);

   public abstract void BlendVolume(Audio var1, float var2);

   public abstract void setSoundVolume(float var1);

   public abstract float getSoundVolume();

   public abstract void setAmbientVolume(float var1);

   public abstract float getAmbientVolume();

   public abstract void setMusicVolume(float var1);

   public abstract float getMusicVolume();

   public abstract void setVehicleEngineVolume(float var1);

   public abstract float getVehicleEngineVolume();

   public abstract void playNightAmbient(std::string var1);

   public abstract std::vector<Audio> getAmbientPieces();

   public abstract void pauseSoundAndMusic();

   public abstract void resumeSoundAndMusic();

   public abstract void debugScriptSounds();

   public abstract void registerEmitter(BaseSoundEmitter var1);

   public abstract void unregisterEmitter(BaseSoundEmitter var1);

   public abstract boolean isListenerInRange(float var1, float var2, float var3);
}
} // namespace zombie

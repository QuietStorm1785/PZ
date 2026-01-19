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
:
    bool AllowMusic = true;

    abstract boolean isRemastered();

    abstract void update1();

    abstract void update3();

    abstract void update2();

    abstract void update4();

    abstract void CacheSound(String var1);

    abstract void StopSound(Audio var1);

    abstract void StopMusic();

    abstract void Purge();

    abstract void stop();

   protected abstract boolean HasMusic(Audio var1);

    abstract void Update();

    abstract Audio Start(Audio var1, float var2, String var3);

    abstract Audio PrepareMusic(String var1);

    abstract void PlayWorldSoundWav(String var1, IsoGridSquare var2, float var3, float var4, float var5, int var6, boolean var7);

    abstract Audio PlayWorldSoundWav(String var1, boolean var2, IsoGridSquare var3, float var4, float var5, float var6, boolean var7);

    abstract Audio PlayWorldSoundWav(String var1, IsoGridSquare var2, float var3, float var4, float var5, boolean var6);

    abstract Audio PlayWorldSound(String var1, IsoGridSquare var2, float var3, float var4, float var5, int var6, boolean var7);

    abstract Audio PlayWorldSound(String var1, boolean var2, IsoGridSquare var3, float var4, float var5, float var6, boolean var7);

    abstract Audio PlayWorldSoundImpl(String var1, boolean var2, int var3, int var4, int var5, float var6, float var7, float var8, boolean var9);

    abstract Audio PlayWorldSound(String var1, IsoGridSquare var2, float var3, float var4, float var5, boolean var6);

    abstract void update3D();

    abstract Audio PlaySoundWav(String var1, int var2, boolean var3, float var4);

    abstract Audio PlaySoundWav(String var1, boolean var2, float var3);

    abstract Audio PlaySoundWav(String var1, boolean var2, float var3, float var4);

    abstract Audio PlayWorldSoundWavImpl(String var1, boolean var2, IsoGridSquare var3, float var4, float var5, float var6, boolean var7);

    abstract Audio PlayJukeboxSound(String var1, boolean var2, float var3);

    abstract Audio PlaySoundEvenSilent(String var1, boolean var2, float var3);

    abstract Audio PlaySound(String var1, boolean var2, float var3);

    abstract Audio PlaySound(String var1, boolean var2, float var3, float var4);

    abstract Audio PlayMusic(String var1, String var2, boolean var3, float var4);

    abstract void PlayAsMusic(String var1, Audio var2, boolean var3, float var4);

    abstract void setMusicState(String var1);

    abstract void setMusicWakeState(IsoPlayer var1, String var2);

    abstract void DoMusic(String var1, boolean var2);

    abstract float getMusicPosition();

    abstract void CheckDoMusic();

    abstract void stopMusic(String var1);

    abstract void playMusicNonTriggered(String var1, float var2);

    abstract void playAmbient(String var1);

    abstract void playMusic(String var1);

    abstract boolean isPlayingMusic();

    abstract boolean IsMusicPlaying();

    abstract String getCurrentMusicName();

    abstract String getCurrentMusicLibrary();

    abstract void PlayAsMusic(String var1, Audio var2, float var3, boolean var4);

    abstract long playUISound(String var1);

    abstract boolean isPlayingUISound(String var1);

    abstract boolean isPlayingUISound(long var1);

    abstract void stopUISound(long var1);

    abstract void FadeOutMusic(String var1, int var2);

    abstract Audio BlendThenStart(Audio var1, float var2, String var3);

    abstract void BlendVolume(Audio var1, float var2, float var3);

    abstract void BlendVolume(Audio var1, float var2);

    abstract void setSoundVolume(float var1);

    abstract float getSoundVolume();

    abstract void setAmbientVolume(float var1);

    abstract float getAmbientVolume();

    abstract void setMusicVolume(float var1);

    abstract float getMusicVolume();

    abstract void setVehicleEngineVolume(float var1);

    abstract float getVehicleEngineVolume();

    abstract void playNightAmbient(String var1);

    abstract ArrayList<Audio> getAmbientPieces();

    abstract void pauseSoundAndMusic();

    abstract void resumeSoundAndMusic();

    abstract void debugScriptSounds();

    abstract void registerEmitter(BaseSoundEmitter var1);

    abstract void unregisterEmitter(BaseSoundEmitter var1);

    abstract boolean isListenerInRange(float var1, float var2, float var3);
}
} // namespace zombie

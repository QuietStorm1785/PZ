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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class BaseSoundManager {
public:
 bool AllowMusic = true;

 public boolean isRemastered();

 public void update1();

 public void update3();

 public void update2();

 public void update4();

 public void CacheSound(String file);

 public void StopSound(Audio SoundEffect);

 public void StopMusic();

 public void Purge();

 public void stop();

 protected boolean HasMusic(Audio var1);

 public void Update();

 public Audio Start(Audio musicTrack, float f, String PrefMusic);

 public Audio PrepareMusic(String name);

 public void PlayWorldSoundWav(String name, IsoGridSquare source, float pitchVar, float radius, float maxGain, int choices, boolean ignoreOutside);

 public Audio PlayWorldSoundWav(String name, boolean loop, IsoGridSquare source, float pitchVar, float radius, float maxGain, boolean ignoreOutside);

 public Audio PlayWorldSoundWav(String name, IsoGridSquare source, float pitchVar, float radius, float maxGain, boolean ignoreOutside);

 public Audio PlayWorldSound(String name, IsoGridSquare source, float pitchVar, float radius, float maxGain, int choices, boolean ignoreOutside);

 public Audio PlayWorldSound(String name, boolean loop, IsoGridSquare source, float pitchVar, float radius, float maxGain, boolean ignoreOutside);

 public Audio PlayWorldSoundImpl(
 String name, boolean loop, int sx, int sy, int sz, float pitchVar, float radius, float maxGain, boolean ignoreOutside
 );

 public Audio PlayWorldSound(String name, IsoGridSquare source, float pitchVar, float radius, float maxGain, boolean ignoreOutside);

 public void update3D();

 public Audio PlaySoundWav(String name, int variations, boolean loop, float maxGain);

 public Audio PlaySoundWav(String name, boolean loop, float maxGain);

 public Audio PlaySoundWav(String name, boolean loop, float maxGain, float pitchVar);

 public Audio PlayWorldSoundWavImpl(
 String name, boolean loop, IsoGridSquare source, float pitchVar, float radius, float maxGain, boolean ignoreOutside
 );

 public Audio PlayJukeboxSound(String name, boolean loop, float maxGain);

 public Audio PlaySoundEvenSilent(String name, boolean loop, float maxGain);

 public Audio PlaySound(String name, boolean loop, float maxGain);

 public Audio PlaySound(String name, boolean loop, float pitchVar, float maxGain);

 public Audio PlayMusic(String n, String name, boolean loop, float maxGain);

 public void PlayAsMusic(String name, Audio musicTrack, boolean loop, float volume);

 public void setMusicState(String stateName);

 public void setMusicWakeState(IsoPlayer player, String stateName);

 public void DoMusic(String name, boolean bLoop);

 public float getMusicPosition();

 public void CheckDoMusic();

 public void stopMusic(String name);

 public void playMusicNonTriggered(String name, float gain);

 public void playAmbient(String name);

 public void playMusic(String name);

 public boolean isPlayingMusic();

 public boolean IsMusicPlaying();

 public String getCurrentMusicName();

 public String getCurrentMusicLibrary();

 public void PlayAsMusic(String name, Audio musicTrack, float volume, boolean bloop);

 public long playUISound(String name);

 public boolean isPlayingUISound(String name);

 public boolean isPlayingUISound(long eventInstance);

 public void stopUISound(long eventInstance);

 public void FadeOutMusic(String name, int milli);

 public Audio BlendThenStart(Audio musicTrack, float f, String PrefMusic);

 public void BlendVolume(Audio audio, float targetVolume, float blendSpeedAlpha);

 public void BlendVolume(Audio audio, float targetVolume);

 public void setSoundVolume(float volume);

 public float getSoundVolume();

 public void setAmbientVolume(float volume);

 public float getAmbientVolume();

 public void setMusicVolume(float volume);

 public float getMusicVolume();

 public void setVehicleEngineVolume(float volume);

 public float getVehicleEngineVolume();

 public void playNightAmbient(String choice);

 public ArrayList<Audio> getAmbientPieces();

 public void pauseSoundAndMusic();

 public void resumeSoundAndMusic();

 public void debugScriptSounds();

 public void registerEmitter(BaseSoundEmitter emitter);

 public void unregisterEmitter(BaseSoundEmitter emitter);

 public boolean isListenerInRange(float x, float y, float range);
}
} // namespace zombie

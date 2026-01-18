#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ISoundSystem {
public:
 virtual ~ISoundSystem() = default;
 void init();

 void update();

 void purge();

 void fadeOutAll(float var1);

 ISoundSystem.ISoundInstance playSound(ISoundSystem.SoundFormat var1,
 String var2, String var3, int var4,
 boolean var5, boolean var6, float var7);

 ISoundSystem.ISoundInstance playSound(ISoundSystem.SoundFormat var1,
 String var2, String var3, int var4,
 boolean var5, boolean var6, float var7,
 float var8);

 ISoundSystem.ISoundInstance playSound(ISoundSystem.SoundFormat var1,
 String var2, String var3, int var4,
 boolean var5, boolean var6, float var7,
 float var8, float var9);

 ISoundSystem.ISoundInstance playSound(ISoundSystem.SoundFormat var1,
 String var2, String var3, boolean var4,
 boolean var5, float var6);

 ISoundSystem.ISoundInstance playSound(ISoundSystem.SoundFormat var1,
 String var2, String var3, boolean var4,
 boolean var5, float var6, float var7);

 ISoundSystem.ISoundInstance playSound(ISoundSystem.SoundFormat var1,
 String var2, String var3, boolean var4,
 boolean var5, float var6, float var7,
 float var8);

 void cacheSound(ISoundSystem.SoundFormat var1, const std::string &var2,
 const std::string &var3, int var4);

 void cacheSound(ISoundSystem.SoundFormat var1, const std::string &var2,
 const std::string &var3);

 void clearSoundCache();

 int countInstances(const std::string &var1);

 void setInstanceLimit(const std::string &var1, int var2,
 ISoundSystem.InstanceFailAction var3);

public
 interface ISoundInstance {
 bool isStreamed();

 bool isLooped();

 bool isPlaying();

 int countInstances();

 void setLooped(bool var1);

 void pause();

 void stop();

 void play();

 void blendVolume(float var1, float var2, bool var3);

 void setVolume(float var1);

 float getVolume();

 void setPanning(float var1);

 float getPanning();

 void setPitch(float var1);

 float getPitch();

 bool disposed();
 }

public
 static enum InstanceFailAction { FailToPlay, StopOldest, StopRandom; }

 public static enum SoundFormat { Ogg, Wav; }
}
} // namespace zombie

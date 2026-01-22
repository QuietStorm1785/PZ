#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ISoundSystem/ISoundInstance.h"
#include "zombie/ISoundSystem/InstanceFailAction.h"
#include "zombie/ISoundSystem/SoundFormat.h"

namespace zombie {


class ISoundSystem {
public:
    virtual ~ISoundSystem() = default;
    void init();

    void update();

    void purge();

    void fadeOutAll(float var1);

    ISoundInstance playSound(SoundFormat var1, const std::string& var2, const std::string& var3, int var4, bool var5, bool var6, float var7);

    ISoundInstance playSound(SoundFormat var1, const std::string& var2, const std::string& var3, int var4, bool var5, bool var6, float var7, float var8);

    ISoundInstance playSound(SoundFormat var1, const std::string& var2, const std::string& var3, int var4, bool var5, bool var6, float var7, float var8, float var9);

    ISoundInstance playSound(SoundFormat var1, const std::string& var2, const std::string& var3, bool var4, bool var5, float var6);

    ISoundInstance playSound(SoundFormat var1, const std::string& var2, const std::string& var3, bool var4, bool var5, float var6, float var7);

    ISoundInstance playSound(SoundFormat var1, const std::string& var2, const std::string& var3, bool var4, bool var5, float var6, float var7, float var8);

    void cacheSound(SoundFormat var1, const std::string& var2, const std::string& var3, int var4);

    void cacheSound(SoundFormat var1, const std::string& var2, const std::string& var3);

    void clearSoundCache();

    int countInstances(const std::string& var1);

    void setInstanceLimit(const std::string& var1, int var2, InstanceFailAction var3);
}
} // namespace zombie

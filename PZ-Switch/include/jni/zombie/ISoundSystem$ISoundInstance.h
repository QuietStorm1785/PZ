#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {

class ISoundSystem {
:
    virtual ~ISoundSystem() = default;
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
} // namespace zombie

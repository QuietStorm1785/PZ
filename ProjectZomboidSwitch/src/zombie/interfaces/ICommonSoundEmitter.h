#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace interfaces {

class ICommonSoundEmitter {
public:
    virtual ~ICommonSoundEmitter() = default;
    void setPos(float var1, float var2, float var3);

    long playSound(const std::string& var1);

    long playSound(const std::string& var1, bool var2);

    void tick();

    bool isEmpty();

    void setPitch(long var1, float var3);

    void setVolume(long var1, float var3);

    bool hasSustainPoints(long var1);

    void triggerCue(long var1);

    int stopSound(long var1);

    void stopOrTriggerSound(long var1);

    void stopOrTriggerSoundByName(const std::string& var1);

    bool isPlaying(long var1);

    bool isPlaying(const std::string& var1);
}
} // namespace interfaces
} // namespace zombie

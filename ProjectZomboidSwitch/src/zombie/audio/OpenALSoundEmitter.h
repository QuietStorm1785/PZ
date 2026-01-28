#ifndef OPENAL_SOUNDEMITTER_H
#define OPENAL_SOUNDEMITTER_H

#include "zombie/audio/BaseSoundEmitter.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

namespace zombie {
namespace audio {

class OpenALSoundEmitter : public BaseSoundEmitter {
private:
    static inline ALCdevice* device_ = nullptr;
    static inline ALCcontext* context_ = nullptr;
public:
    OpenALSoundEmitter();
    ~OpenALSoundEmitter() override;

    void randomStart() override;
    void setPos(float x, float y, float z) override;
    int stopSound(int64_t id) override;
    void stopSoundLocal(int64_t id) override;
    int stopSoundByName(const std::string& name) override;
    void stopOrTriggerSound(int64_t id) override;
    void stopOrTriggerSoundByName(const std::string& name) override;
    void setVolume(int64_t id, float volume) override;
    void setPitch(int64_t id, float pitch) override;
    bool hasSustainPoints(int64_t id) override;
    void setParameterValue(int64_t id, const std::string& param, float value) override;
    void setTimelinePosition(int64_t id, const std::string& position) override;
    void triggerCue(int64_t id) override;
    void setVolumeAll(float volume) override;
    void stopAll() override;
    int64_t playSound(const std::string& name) override;
    int64_t playSound(const std::string& name, zombie::characters::IsoGameCharacter* character) override;
    int64_t playSound(const std::string& name, int x, int y, int z) override;
    int64_t playSound(const std::string& name, zombie::iso::IsoGridSquare* square) override;
    int64_t playSoundImpl(const std::string& name, zombie::iso::IsoGridSquare* square) override;
    int64_t playSound(const std::string& name, bool flag) override;
    int64_t playSoundImpl(const std::string& name, bool flag, zombie::iso::IsoObject* obj) override;
    int64_t playSound(const std::string& name, zombie::iso::IsoObject* obj) override;
    int64_t playSoundImpl(const std::string& name, zombie::iso::IsoObject* obj) override;
    int64_t playClip(GameSoundClip& clip, zombie::iso::IsoObject* obj) override;
    int64_t playAmbientSound(const std::string& name) override;
    int64_t playSoundLooped(const std::string& name) override;
    int64_t playSoundLoopedImpl(const std::string& name) override;
    int64_t playAmbientLoopedImpl(const std::string& name) override;
    void set3D(int64_t id, bool is3D) override;
    void tick() override;
    bool hasSoundsToStart() const override;
    bool isEmpty() const override;
    bool isPlaying(int64_t id) const override;
    bool isPlaying(const std::string& name) const override;
    bool restart(int64_t id) override;

private:
    struct SoundInstance {
        ALuint source = 0;
        ALuint buffer = 0;
        std::string name;
        bool loop = false;
    };
    std::unordered_map<int64_t, SoundInstance> sounds_;
    int64_t nextId_ = 1;
    void cleanupStopped();
};


// --- OpenAL SoundEmitter interface ---
void initOpenAL();
void releaseOpenAL();
void updateOpenAL();
void set3DListenerAttributesOpenAL(float x, float y, float z, float vx, float vy, float vz, float fx, float fy, float fz, float ux, float uy, float uz);
void setLoopCountOpenAL(int64_t id, int loopCount);
float getPositionOpenAL(int64_t id);
void setPositionOpenAL(int64_t id, float seconds);
void setMuteOpenAL(int64_t id, bool mute);
bool getMuteOpenAL(int64_t id) const;
void setPanOpenAL(int64_t id, float pan);
void addGroupOpenAL(int64_t id);
void setGroupVolumeOpenAL(int64_t id, float volume);
void stopGroupOpenAL(int64_t id);
void createChannelGroupOpenAL(const std::string& groupName);
void setReverbPropertiesOpenAL(float decayTime, float density, float diffusion);
void setChannelReverbPropertiesOpenAL(int64_t id, float reverbLevel);

} // namespace audio
} // namespace zombie

#endif // OPENAL_SOUNDEMITTER_H

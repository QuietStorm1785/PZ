#pragma once
#include <string>
#include <memory>
#include <map>
#include <algorithm>
#include <cmath>

namespace zombie {
namespace audio {

struct Vec3 {
    float x, y, z;
    Vec3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
};

enum class SoundCategory {
    MUSIC,
    AMBIENT,
    SFX,
    VOICE,
    UI
};

class Sound {
public:
    Sound(const std::string& path, SoundCategory category);
    virtual ~Sound() = default;
    
    virtual void play() = 0;
    virtual void stop() = 0;
    virtual void pause() = 0;
    virtual void setVolume(float vol) = 0;
    
    float getVolume() const { return volume; }
    const std::string& getPath() const { return path; }
    SoundCategory getCategory() const { return category; }
    
protected:
    std::string path;
    SoundCategory category;
    float volume;
};

class WorldSound : public Sound {
public:
    WorldSound(const std::string& path, Vec3 position);
    
    void play() override;
    void stop() override;
    void pause() override;
    void setVolume(float vol) override;
    
    void setPosition(Vec3 pos) { position = pos; }
    Vec3 getPosition() const { return position; }
    
private:
    Vec3 position;
};

class AudioManager {
public:
    static AudioManager& getInstance() {
        static AudioManager instance;
        return instance;
    }
    
    bool initialize();
    void shutdown();
    
    std::shared_ptr<Sound> loadSound(const std::string& path, SoundCategory category);
    void playSound(const std::string& soundId);
    void stopSound(const std::string& soundId);
    
    void playWorldSound(const std::string& path, Vec3 position);
    
    void setMasterVolume(float vol);
    void setCategoryVolume(SoundCategory category, float vol);
    
    void update(float deltaTime);
    
private:
    AudioManager() = default;
    ~AudioManager();
    
    std::map<std::string, std::shared_ptr<Sound>> sounds;
    std::map<SoundCategory, float> categoryVolumes;
    float masterVolume;
};

} // namespace audio
} // namespace zombie

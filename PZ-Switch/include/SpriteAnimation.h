#pragma once
#include "Sprite.h"
#include <vector>
#include <string>
#include <unordered_map>

namespace zombie {

// Forward declarations
namespace assets { class TextureManager; }

namespace graphics {

/**
 * Animation frame - references a region of a sprite sheet
 */
struct AnimationFrame {
    int x, y, width, height;     // Source rectangle in texture
    int offsetX, offsetY;         // Render offset
    int originalWidth, originalHeight; // Original size before crop
    float duration;               // Frame duration in seconds
    
    AnimationFrame() 
        : x(0), y(0), width(0), height(0)
        , offsetX(0), offsetY(0)
        , originalWidth(0), originalHeight(0)
        , duration(0.1f) {}
};

/**
 * Animation - sequence of frames
 */
class Animation {
public:
    Animation();
    Animation(const std::string& name);
    ~Animation();
    
    void setName(const std::string& n) { name = n; }
    std::string getName() const { return name; }
    
    void addFrame(const AnimationFrame& frame);
    void setFrameDuration(float seconds);
    void setLoop(bool loop) { looping = loop; }
    bool isLooping() const { return looping; }
    
    int getFrameCount() const { return static_cast<int>(frames.size()); }
    const AnimationFrame& getFrame(int index) const;
    
    float getTotalDuration() const;
    
private:
    std::string name;
    std::vector<AnimationFrame> frames;
    bool looping;
};

/**
 * AnimatedSprite - Sprite with animation support
 */
class AnimatedSprite : public Sprite {
public:
    AnimatedSprite();
    AnimatedSprite(SDL_Texture* texture);
    ~AnimatedSprite();
    
    // Animation management
    void addAnimation(const std::string& name, const Animation& anim);
    void setAnimation(const std::string& name);
    std::string getCurrentAnimation() const { return currentAnimName; }
    
    // Playback control
    void play();
    void pause();
    void stop();
    void setSpeed(float speed) { playbackSpeed = speed; }
    
    bool isPlaying() const { return playing; }
    bool isPaused() const { return paused; }
    
    // Update animation
    void update(float deltaTime);
    
    // Current frame info
    int getCurrentFrame() const { return currentFrame; }
    void setFrame(int frame);
    
private:
    std::unordered_map<std::string, Animation> animations;
    std::string currentAnimName;
    Animation* currentAnim;
    
    int currentFrame;
    float frameTime;
    float playbackSpeed;
    bool playing;
    bool paused;
    
    void applyCurrentFrame();
};

/**
 * Animation loader - loads from PZ texture pack format
 */
class AnimationLoader {
public:
    static bool loadFromFile(const std::string& txtPath, 
                            const std::string& pngPath,
                            AnimatedSprite* sprite,
                            assets::TextureManager* texMgr);
    
    static bool parseAnimationFile(const std::string& path,
                                   std::unordered_map<std::string, Animation>& animations);
    
private:
    static void parseAnimationLine(const std::string& line,
                                   std::unordered_map<std::string, Animation>& animations);
};

} // namespace graphics
} // namespace zombie

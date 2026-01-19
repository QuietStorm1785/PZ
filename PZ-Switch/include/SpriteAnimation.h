#pragma once
#include "Sprite.h"
#include <vector>
#include <string>
#include <string_view>
#include <unordered_map>

namespace zombie {

// Forward declarations
namespace assets { class TextureManager; }

namespace graphics {

/**
 * Animation frame - references a region of a sprite sheet
 */
struct AnimationFrame {
 int x, y, width, height; // Source rectangle in texture
 int offsetX, offsetY; // Render offset
 int originalWidth, originalHeight; // Original size before crop
 float duration; // Frame duration in seconds
 
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
 Animation(std::string_view name);
 ~Animation();
 
 void setName(std::string_view n) { name = n; }
 std::string getName() const { return name; }
 
 void addFrame(const AnimationFrame& frame);
 void setFrameDuration(float seconds);
 void setLoop(bool loop) { looping = loop; }
 bool isLooping() const { return looping; }
 
 int getFrameCount() const noexcept { return static_cast<int>(frames.size()); }
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
 void addAnimation(std::string_view name, const Animation& anim);
 void setAnimation(std::string_view name);
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
 static bool loadFromFile(std::string_view txtPath, 
 std::string_view pngPath,
 AnimatedSprite* sprite,
 assets::TextureManager* texMgr);
 
 static bool parseAnimationFile(std::string_view path,
 std::unordered_map<std::string, Animation>& animations);
 
private:
 static void parseAnimationLine(std::string_view line,
 std::unordered_map<std::string, Animation>& animations);
};

} // namespace graphics
} // namespace zombie

#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <map>

namespace zombie {
namespace animation {

struct AnimationFrame {
 int spriteIndex;
 float duration;
};

class Animation {
public:
 Animation(std::string_view name);
 ~Animation() = default;
 
 void addFrame(int spriteIndex, float duration);
 const std::string& getName() const { return name; }
 
 int getFrameCount() const noexcept { return frames.size(); }
 const AnimationFrame& getFrame(int index) const { return frames[index]; }
 
 bool isLooping() const { return looping; }
 void setLooping(bool loop) { looping = loop; }
 
 float getTotalDuration() const;
 
private:
 std::string name;
 std::vector<AnimationFrame> frames;
 bool looping;
};

class AnimationController {
public:
 AnimationController();
 ~AnimationController() = default;
 
 void addAnimation(std::shared_ptr<Animation> anim);
 bool playAnimation(std::string_view name);
 void stopAnimation();
 
 void update(float deltaTime);
 
 int getCurrentFrame() const { return currentFrame; }
 int getCurrentSpriteIndex() const;
 bool isPlaying() const { return playing; }
 
private:
 std::map<std::string, std::shared_ptr<Animation>> animations;
 std::shared_ptr<Animation> currentAnimation;
 
 bool playing;
 int currentFrame;
 float elapsedTime;
};

class SpriteAnimation {
public:
 SpriteAnimation(std::string_view spritesheetPath, int frameWidth, int frameHeight);
 ~SpriteAnimation() = default;
 
 void setGridSize(int cols, int rows);
 int getTotalFrames() const { return frameCount; }
 
private:
 std::string spritesheetPath;
 int frameWidth, frameHeight;
 int frameCount;
 int columns, rows;
};

} // namespace animation
} // namespace zombie

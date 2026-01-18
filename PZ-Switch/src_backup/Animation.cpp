#include "Animation.h"

namespace zombie {
namespace animation {

Animation::Animation(const std::string& name)
    : name(name), looping(false) {
}

void Animation::addFrame(int spriteIndex, float duration) {
    frames.push_back({spriteIndex, duration});
}

float Animation::getTotalDuration() const {
    float total = 0.0f;
    for (const auto& frame : frames) {
        total += frame.duration;
    }
    return total;
}

AnimationController::AnimationController()
    : playing(false), currentFrame(0), elapsedTime(0.0f) {
}

void AnimationController::addAnimation(std::shared_ptr<Animation> anim) {
    if (anim) {
        animations[anim->getName()] = anim;
    }
}

bool AnimationController::playAnimation(const std::string& name) {
    auto it = animations.find(name);
    if (it != animations.end()) {
        currentAnimation = it->second;
        playing = true;
        currentFrame = 0;
        elapsedTime = 0.0f;
        return true;
    }
    return false;
}

void AnimationController::stopAnimation() {
    playing = false;
}

void AnimationController::update(float deltaTime) {
    if (!playing || !currentAnimation || currentAnimation->getFrameCount() == 0) {
        return;
    }
    
    elapsedTime += deltaTime;
    
    float frameDuration = currentAnimation->getFrame(currentFrame).duration;
    if (elapsedTime >= frameDuration) {
        elapsedTime -= frameDuration;
        currentFrame++;
        
        if (currentFrame >= currentAnimation->getFrameCount()) {
            if (currentAnimation->isLooping()) {
                currentFrame = 0;
            } else {
                playing = false;
            }
        }
    }
}

int AnimationController::getCurrentSpriteIndex() const {
    if (currentAnimation && currentFrame < currentAnimation->getFrameCount()) {
        return currentAnimation->getFrame(currentFrame).spriteIndex;
    }
    return 0;
}

SpriteAnimation::SpriteAnimation(const std::string& spritesheetPath, int frameWidth, int frameHeight)
    : spritesheetPath(spritesheetPath), frameWidth(frameWidth), frameHeight(frameHeight), frameCount(0) {
}

void SpriteAnimation::setGridSize(int cols, int rows) {
    columns = cols;
    rows = rows;
    frameCount = cols * rows;
}

} // namespace animation
} // namespace zombie

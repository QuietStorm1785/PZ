#include "SpriteAnimation.h"
#include "TextureManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace zombie {
namespace graphics {

// Animation implementation

Animation::Animation()
    : name("default")
    , looping(true)
{
}

Animation::Animation(const std::string& n)
    : name(n)
    , looping(true)
{
}

Animation::~Animation() {
}

void Animation::addFrame(const AnimationFrame& frame) {
    frames.push_back(frame);
}

void Animation::setFrameDuration(float seconds) {
    for (auto& frame : frames) {
        frame.duration = seconds;
    }
}

const AnimationFrame& Animation::getFrame(int index) const {
    static AnimationFrame emptyFrame;
    if (index < 0 || index >= static_cast<int>(frames.size())) {
        return emptyFrame;
    }
    return frames[index];
}

float Animation::getTotalDuration() const {
    float total = 0.0f;
    for (const auto& frame : frames) {
        total += frame.duration;
    }
    return total;
}

// AnimatedSprite implementation

AnimatedSprite::AnimatedSprite()
    : Sprite()
    , currentAnim(nullptr)
    , currentFrame(0)
    , frameTime(0.0f)
    , playbackSpeed(1.0f)
    , playing(false)
    , paused(false)
{
}

AnimatedSprite::AnimatedSprite(SDL_Texture* texture)
    : Sprite(texture)
    , currentAnim(nullptr)
    , currentFrame(0)
    , frameTime(0.0f)
    , playbackSpeed(1.0f)
    , playing(false)
    , paused(false)
{
}

AnimatedSprite::~AnimatedSprite() {
}

void AnimatedSprite::addAnimation(const std::string& name, const Animation& anim) {
    animations[name] = anim;
    
    // If this is the first animation, make it current
    if (animations.size() == 1) {
        setAnimation(name);
    }
}

void AnimatedSprite::setAnimation(const std::string& name) {
    auto it = animations.find(name);
    if (it != animations.end()) {
        currentAnimName = name;
        currentAnim = &it->second;
        currentFrame = 0;
        frameTime = 0.0f;
        applyCurrentFrame();
    }
}

void AnimatedSprite::play() {
    playing = true;
    paused = false;
}

void AnimatedSprite::pause() {
    paused = true;
}

void AnimatedSprite::stop() {
    playing = false;
    paused = false;
    currentFrame = 0;
    frameTime = 0.0f;
    applyCurrentFrame();
}

void AnimatedSprite::setFrame(int frame) {
    if (!currentAnim) return;
    
    currentFrame = frame;
    if (currentFrame < 0) currentFrame = 0;
    if (currentFrame >= currentAnim->getFrameCount()) {
        currentFrame = currentAnim->getFrameCount() - 1;
    }
    
    applyCurrentFrame();
}

void AnimatedSprite::update(float deltaTime) {
    if (!playing || paused || !currentAnim) {
        return;
    }
    
    int frameCount = currentAnim->getFrameCount();
    if (frameCount == 0) return;
    
    frameTime += deltaTime * playbackSpeed;
    
    const AnimationFrame& frame = currentAnim->getFrame(currentFrame);
    
    // Check if it's time to advance frame
    if (frameTime >= frame.duration) {
        frameTime -= frame.duration;
        currentFrame++;
        
        // Handle looping
        if (currentFrame >= frameCount) {
            if (currentAnim->isLooping()) {
                currentFrame = 0;
            } else {
                currentFrame = frameCount - 1;
                playing = false;
            }
        }
        
        applyCurrentFrame();
    }
}

void AnimatedSprite::applyCurrentFrame() {
    if (!currentAnim) return;
    
    int frameCount = currentAnim->getFrameCount();
    if (frameCount == 0) return;
    
    const AnimationFrame& frame = currentAnim->getFrame(currentFrame);
    
    // Set source rectangle for sprite
    setSourceRect(frame.x, frame.y, frame.width, frame.height);
}

// AnimationLoader implementation

bool AnimationLoader::loadFromFile(const std::string& txtPath,
                                  const std::string& pngPath,
                                  AnimatedSprite* sprite,
                                  assets::TextureManager* texMgr) {
    if (!sprite || !texMgr) {
        return false;
    }
    
    // Load texture
    SDL_Texture* texture = texMgr->loadTexture(pngPath);
    if (!texture) {
        std::cerr << "Failed to load animation texture: " << pngPath << std::endl;
        return false;
    }
    
    sprite->setTexture(texture);
    
    // Parse animation data
    std::unordered_map<std::string, Animation> animations;
    if (!parseAnimationFile(txtPath, animations)) {
        std::cerr << "Failed to parse animation file: " << txtPath << std::endl;
        return false;
    }
    
    // Add animations to sprite
    for (const auto& pair : animations) {
        sprite->addAnimation(pair.first, pair.second);
    }
    
    // Auto-play first animation
    if (!animations.empty()) {
        sprite->setAnimation(animations.begin()->first);
        sprite->play();
    }
    
    return true;
}

bool AnimationLoader::parseAnimationFile(const std::string& path,
                                        std::unordered_map<std::string, Animation>& animations) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return false;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        parseAnimationLine(line, animations);
    }
    
    file.close();
    
    // Set default frame duration for all animations
    for (auto& pair : animations) {
        pair.second.setFrameDuration(0.1f); // 10 FPS default
    }
    
    return !animations.empty();
}

void AnimationLoader::parseAnimationLine(const std::string& line,
                                        std::unordered_map<std::string, Animation>& animations) {
    // Format: AnimName_Direction_Frame = x y w h offsetX offsetY origW origH
    // Example: Baseballbat_1_Walk_0 = 153 66 18 15 57 63 164 128
    
    size_t equalsPos = line.find('=');
    if (equalsPos == std::string::npos) return;
    
    std::string frameName = line.substr(0, equalsPos);
    std::string frameData = line.substr(equalsPos + 1);
    
    // Trim whitespace
    size_t start = frameName.find_first_not_of(" \t");
    size_t end = frameName.find_last_not_of(" \t");
    if (start != std::string::npos && end != std::string::npos) {
        frameName = frameName.substr(start, end - start + 1);
    }
    
    // Extract animation name (everything before last underscore)
    size_t lastUnderscore = frameName.find_last_of('_');
    if (lastUnderscore == std::string::npos) return;
    
    std::string animName = frameName.substr(0, lastUnderscore);
    
    // Parse frame data
    std::istringstream iss(frameData);
    AnimationFrame frame;
    
    if (!(iss >> frame.x >> frame.y >> frame.width >> frame.height 
              >> frame.offsetX >> frame.offsetY 
              >> frame.originalWidth >> frame.originalHeight)) {
        return;
    }
    
    // Create animation if it doesn't exist
    if (animations.find(animName) == animations.end()) {
        animations[animName] = Animation(animName);
    }
    
    animations[animName].addFrame(frame);
}

} // namespace graphics
} // namespace zombie

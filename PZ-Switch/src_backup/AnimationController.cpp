#include "AnimationController.h"
#include <cmath>
#include <iostream>

namespace zombie {
namespace characters {

AnimationController::AnimationController(zombie::graphics::AnimatedSprite* spr)
    : sprite(spr)
    , currentState(State::IDLE)
    , currentDirection(Direction::SOUTH)
    , currentAnimationName("")
{
}

void AnimationController::setState(State newState) {
    if (currentState != newState) {
        currentState = newState;
        updateSpriteAnimation();
    }
}

void AnimationController::setDirection(Direction dir) {
    if (currentDirection != dir) {
        currentDirection = dir;
        updateSpriteAnimation();
    }
}

void AnimationController::setDirection(int dir) {
    if (dir >= 0 && dir <= 7) {
        setDirection(static_cast<Direction>(dir));
    }
}

void AnimationController::update(float deltaTime) {
    if (sprite) {
        sprite->update(deltaTime);
    }
}

void AnimationController::playAnimation(const std::string& name, bool loop) {
    if (!sprite) return;
    
    sprite->setAnimation(name);
    if (loop) {
        sprite->play();
    }
    currentAnimationName = name;
}

void AnimationController::stopAnimation() {
    if (sprite) {
        sprite->stop();
    }
}

void AnimationController::registerAnimation(State state, Direction dir, const std::string& animName) {
    std::string key = makeAnimationKey(state, dir);
    animationMap[key] = animName;
}

void AnimationController::registerAnimation(const std::string& stateName, const std::string& animName) {
    animationMap[stateName] = animName;
}

std::string AnimationController::getCurrentAnimationName() const {
    return currentAnimationName;
}

std::string AnimationController::makeAnimationKey(State state, Direction dir) const {
    std::string key = std::string(AnimationHelpers::stateName(state)) + "_" + 
                     std::string(AnimationHelpers::directionName(dir));
    return key;
}

void AnimationController::updateSpriteAnimation() {
    if (!sprite) return;
    
    // Try to find animation for current state and direction
    std::string key = makeAnimationKey(currentState, currentDirection);
    
    auto it = animationMap.find(key);
    if (it != animationMap.end()) {
        // Found specific animation for state + direction
        if (currentAnimationName != it->second) {
            sprite->setAnimation(it->second);
            sprite->play();
            currentAnimationName = it->second;
        }
        return;
    }
    
    // Fallback: try state-only animation (direction-agnostic)
    std::string stateKey = std::string(AnimationHelpers::stateName(currentState));
    it = animationMap.find(stateKey);
    if (it != animationMap.end()) {
        if (currentAnimationName != it->second) {
            sprite->setAnimation(it->second);
            sprite->play();
            currentAnimationName = it->second;
        }
        return;
    }
    
    // No animation found
    std::cerr << "AnimationController: No animation registered for " << key << std::endl;
}

// ===== Animation Helper Functions =====

namespace AnimationHelpers {

constexpr float PI_F = 3.14159265358979323846f;

AnimationController::Direction velocityToDirection(float vx, float vy) {
    // No movement
    if (vx == 0 && vy == 0) {
        return AnimationController::Direction::SOUTH; // Default
    }
    
    // Calculate angle in radians
    float angle = std::atan2(vy, vx);
    
    // Convert to degrees (0-360)
    float degrees = angle * 180.0f / PI_F;
    if (degrees < 0) degrees += 360.0f;
    
    // Map to 8 directions (45 degree sectors)
    // 0° = East, 90° = South, 180° = West, 270° = North
    if (degrees >= 337.5f || degrees < 22.5f) {
        return AnimationController::Direction::EAST;
    } else if (degrees >= 22.5f && degrees < 67.5f) {
        return AnimationController::Direction::SOUTH_EAST;
    } else if (degrees >= 67.5f && degrees < 112.5f) {
        return AnimationController::Direction::SOUTH;
    } else if (degrees >= 112.5f && degrees < 157.5f) {
        return AnimationController::Direction::SOUTH_WEST;
    } else if (degrees >= 157.5f && degrees < 202.5f) {
        return AnimationController::Direction::WEST;
    } else if (degrees >= 202.5f && degrees < 247.5f) {
        return AnimationController::Direction::NORTH_WEST;
    } else if (degrees >= 247.5f && degrees < 292.5f) {
        return AnimationController::Direction::NORTH;
    } else {
        return AnimationController::Direction::NORTH_EAST;
    }
}

float directionToAngle(AnimationController::Direction dir) {
    switch (dir) {
        case AnimationController::Direction::EAST: return 0.0f;
        case AnimationController::Direction::SOUTH_EAST: return 45.0f;
        case AnimationController::Direction::SOUTH: return 90.0f;
        case AnimationController::Direction::SOUTH_WEST: return 135.0f;
        case AnimationController::Direction::WEST: return 180.0f;
        case AnimationController::Direction::NORTH_WEST: return 225.0f;
        case AnimationController::Direction::NORTH: return 270.0f;
        case AnimationController::Direction::NORTH_EAST: return 315.0f;
        default: return 0.0f;
    }
}

const char* directionName(AnimationController::Direction dir) {
    switch (dir) {
        case AnimationController::Direction::NORTH: return "north";
        case AnimationController::Direction::NORTH_EAST: return "north_east";
        case AnimationController::Direction::EAST: return "east";
        case AnimationController::Direction::SOUTH_EAST: return "south_east";
        case AnimationController::Direction::SOUTH: return "south";
        case AnimationController::Direction::SOUTH_WEST: return "south_west";
        case AnimationController::Direction::WEST: return "west";
        case AnimationController::Direction::NORTH_WEST: return "north_west";
        default: return "unknown";
    }
}

const char* stateName(AnimationController::State state) {
    switch (state) {
        case AnimationController::State::IDLE: return "idle";
        case AnimationController::State::WALK: return "walk";
        case AnimationController::State::RUN: return "run";
        case AnimationController::State::ATTACK: return "attack";
        case AnimationController::State::INTERACT: return "interact";
        case AnimationController::State::USE_ITEM: return "use_item";
        case AnimationController::State::DEATH: return "death";
        default: return "unknown";
    }
}

} // namespace AnimationHelpers

} // namespace characters
} // namespace zombie

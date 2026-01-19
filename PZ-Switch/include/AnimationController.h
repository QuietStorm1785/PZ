#pragma once
#include "SpriteAnimation.h"
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>

namespace zombie {
namespace characters {

/**
 * AnimationController - Manages character animation states
 * 
 * Automatically switches animations based on character state:
 * - Movement direction (8 directions: N, NE, E, SE, S, SW, W, NW)
 * - Movement speed (idle, walk, run)
 * - Actions (attack, interact, use item)
 */
class AnimationController {
public:
 enum class State {
 IDLE,
 WALK,
 RUN,
 ATTACK,
 INTERACT,
 USE_ITEM,
 DEATH
 };
 
 enum class Direction {
 SOUTH = 0, // Down
 SOUTH_EAST = 1,
 EAST = 2, // Right
 NORTH_EAST = 3,
 NORTH = 4, // Up
 NORTH_WEST = 5,
 WEST = 6, // Left
 SOUTH_WEST = 7
 };
 
 AnimationController(zombie::graphics::AnimatedSprite* sprite);
 ~AnimationController() = default;
 
 // State management
 void setState(State newState);
 void setDirection(Direction dir);
 void setDirection(int dir); // 0-7
 
 State getState() const { return currentState; }
 Direction getDirection() const { return currentDirection; }
 
 // Update animation based on current state
 void update(float deltaTime);
 
 // Direct animation control (bypasses state system)
 void playAnimation(std::string_view name, bool loop = true);
 void stopAnimation();
 
 // Animation registration
 void registerAnimation(State state, Direction dir, std::string_view animName);
 void registerAnimation(std::string_view stateName, std::string_view animName);
 
 // Get current animation name
 std::string getCurrentAnimationName() const;
 
private:
 zombie::graphics::AnimatedSprite* sprite;
 
 State currentState;
 Direction currentDirection;
 std::string currentAnimationName;
 
 // Animation mapping: "state_direction" -> animation name
 std::unordered_map<std::string, std::string> animationMap;
 
 // Helper to build animation key
 std::string makeAnimationKey(State state, Direction dir) const;
 
 // Update sprite to match current state
 void updateSpriteAnimation();
};

/**
 * Direction helper functions
 */
namespace AnimationHelpers {
 // Convert velocity to direction (8-way)
 AnimationController::Direction velocityToDirection(float vx, float vy);
 
 // Convert direction to angle (degrees)
 float directionToAngle(AnimationController::Direction dir);
 
 // Get direction name string
 const char* directionName(AnimationController::Direction dir);
 
 // Get state name string
 const char* stateName(AnimationController::State state);
}

} // namespace characters
} // namespace zombie

#pragma once

namespace zombie {
namespace gameStates {

enum class StateAction {
 Continue, // Move to next state
 Remain // Stay in current state
};

/**
 * Base class for all game states
 * Converted from zombie.gameStates.GameState
 */
class GameState {
public:
 virtual ~GameState() = default;
 
 // Called when entering this state
 virtual void enter() {}
 
 // Called when exiting this state
 virtual void exit() {}
 
 // Update logic (called every frame)
 // Returns Continue to move to next state, Remain to stay
 virtual StateAction update() { return StateAction::Continue; }
 
 // Render this state
 virtual void render() {}
 
 // Override to redirect to a different state
 virtual GameState* redirectState() { return nullptr; }
};

} // namespace gameStates
} // namespace zombie

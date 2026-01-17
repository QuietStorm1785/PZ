#pragma once
#include <vector>
#include <memory>
#include "GameState.h"

namespace zombie {
namespace gameStates {

/**
 * Manages game state transitions and updates
 * Converted from zombie.gameStates.GameStateMachine
 */
class GameStateMachine {
public:
    GameStateMachine();
    
    // Add a state to the machine
    void addState(std::unique_ptr<GameState> state);
    
    // Update current state
    void update();
    
    // Render current state
    void render();
    
    // State control
    void setLooping(bool loop) { looping = loop; }
    void setLoopToState(int index) { loopToState = index; }
    
    int getCurrentStateIndex() const { return stateIndex; }
    GameState* getCurrentState() const { return currentState; }
    
private:
    std::vector<std::unique_ptr<GameState>> states;
    GameState* currentState;
    
    bool firstRun;
    bool looping;
    int stateIndex;
    int loopToState;
};

} // namespace gameStates
} // namespace zombie

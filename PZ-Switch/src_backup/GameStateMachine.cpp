#include "GameStateMachine.h"

namespace zombie {
namespace gameStates {

GameStateMachine::GameStateMachine()
    : currentState(nullptr)
    , firstRun(true)
    , looping(true)
    , stateIndex(0)
    , loopToState(0)
{
}

void GameStateMachine::addState(std::unique_ptr<GameState> state) {
    states.push_back(std::move(state));
}

void GameStateMachine::update() {
    // First run initialization
    if (firstRun) {
        if (currentState == nullptr && !states.empty()) {
            currentState = states[stateIndex].get();
        }
        
        if (currentState) {
            currentState->enter();
        }
        firstRun = false;
    }
    
    // No current state - handle looping
    if (currentState == nullptr) {
        if (looping) {
            stateIndex = loopToState;
            if (stateIndex < static_cast<int>(states.size())) {
                currentState = states[stateIndex].get();
                currentState->enter();
            }
        } else {
            return; // No looping, done
        }
    }
    
    // Update current state
    if (currentState) {
        StateAction action = currentState->update();
        
        if (action == StateAction::Continue) {
            // Exit current state
            currentState->exit();
            
            // Check for redirect
            GameState* redirected = currentState->redirectState();
            
            if (redirected) {
                // Use redirected state
                redirected->enter();
                currentState = redirected;
            } else {
                // Move to next state
                stateIndex++;
                
                if (stateIndex < static_cast<int>(states.size())) {
                    currentState = states[stateIndex].get();
                    currentState->enter();
                } else {
                    currentState = nullptr; // End of states
                }
            }
        }
        // StateAction::Remain - stay in current state
    }
}

void GameStateMachine::render() {
    if (currentState) {
        currentState->render();
    }
}

} // namespace gameStates
} // namespace zombie

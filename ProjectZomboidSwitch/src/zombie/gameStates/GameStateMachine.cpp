#include "zombie/gameStates/GameStateMachine.h"

namespace zombie {
namespace gameStates {


void GameStateMachine::render() {
    if (current) {
        current->render();
    }
}

void GameStateMachine::update() {
    if (States.empty()) {
        if (!forceNext) {
            return;
        }
        States.push_back(forceNext);
        forceNext = nullptr;
    }

    if (firstrun) {
        if (!current && StateIndex < States.size()) {
            current = States[StateIndex];
        }
        if (current) {
            // std::cout << "STATE: enter " << typeid(*current).name() << std::endl;
            current->enter();
        }
        firstrun = false;
    }

    if (!current) {
        if (!Loop) {
            return;
        }
        StateIndex = LoopToState;
        if (States.empty()) {
            return;
        }
        current = States[StateIndex];
        if (StateIndex < States.size()) {
            // std::cout << "STATE: enter " << typeid(*current).name() << std::endl;
            current->enter();
        }
    }

    if (current) {
        std::shared_ptr<GameState> nextState = nullptr;
        if (forceNext) {
            // std::cout << "STATE: exit " << typeid(*current).name() << std::endl;
            current->exit();
            nextState = forceNext;
            forceNext = nullptr;
        } else {
            auto action = current->update();
            if (action == StateAction::Continue) {
                // std::cout << "STATE: exit " << typeid(*current).name() << std::endl;
                current->exit();
                if (!yieldStack.empty()) {
                    current = yieldStack.top();
                    yieldStack.pop();
                    // std::cout << "STATE: reenter " << typeid(*current).name() << std::endl;
                    current->reenter();
                    return;
                }
                nextState = current->redirectState();
            } else if (action == StateAction::Yield) {
                // std::cout << "STATE: yield " << typeid(*current).name() << std::endl;
                current->yield();
                yieldStack.push(current);
                nextState = current->redirectState();
            } else {
                return;
            }
        }

        if (!nextState) {
            StateIndex++;
            if (StateIndex < States.size()) {
                current = States[StateIndex];
                // std::cout << "STATE: enter " << typeid(*current).name() << std::endl;
                current->enter();
            } else {
                current = nullptr;
            }
        } else {
            // std::cout << "STATE: enter " << typeid(*nextState).name() << std::endl;
            nextState->enter();
            current = nextState;
        }
    }
}

void GameStateMachine::forceNextState(std::shared_ptr<GameState> state) {
    forceNext = state;
}


} // namespace gameStates
} // namespace zombie

#include "zombie/ai/StateMachine.h"

namespace zombie {
namespace ai {

StateMachine::StateMachine(IsoGameCharacter var1)
    : m_owner(var1), m_isLocked(false), activeStateChanged(0), m_currentState(nullptr), m_previousState(nullptr) {
    // Initialize subStates if needed
}

void StateMachine::changeState(State var1, Iterable<State> var2) {
    changeState(var1, var2, false);
}

void StateMachine::changeState(State var1, Iterable<State> var2, bool var3) {
    if (!m_isLocked) {
        changeRootState(var1, var3);
        for (auto& slot : m_subStates) {
            slot.shouldBeActive = false;
        }
        for (auto& state : var2) {
            if (state != nullptr) {
                ensureSubstateActive(state);
            }
        }
        for (auto it = m_subStates.begin(); it != m_subStates.end(); ) {
            if (!it->shouldBeActive && !it->empty()) {
                removeSubstate(*it);
                it = m_subStates.erase(it);
            } else {
                ++it;
            }
        }
    }
}

void StateMachine::changeRootState(State var1, bool var2) {
    if (m_currentState == var1) {
        if (var2 && m_currentState != nullptr) {
            stateEnter(m_currentState);
        }
        return;
    }
    m_previousState = m_currentState;
    m_currentState = var1;
    activeStateChanged++;
    if (m_currentState != nullptr) {
        stateEnter(m_currentState);
    }
}

void StateMachine::ensureSubstateActive(State var1) {
    auto slot = getExistingSlot(var1);
    if (slot == nullptr) {
        // Create new slot if not found
        SubstateSlot newSlot(var1);
        newSlot.shouldBeActive = true;
        m_subStates.push_back(newSlot);
    } else {
        slot->shouldBeActive = true;
    }
}

SubstateSlot* StateMachine::getExistingSlot(State var1) {
    for (auto& slot : m_subStates) {
        if (slot.getState() == var1) {
            return &slot;
        }
    }
    return nullptr;
}

void StateMachine::removeSubstate(State var1) {
    for (auto it = m_subStates.begin(); it != m_subStates.end(); ++it) {
        if (it->getState() == var1) {
            m_subStates.erase(it);
            break;
        }
    }
}

void StateMachine::removeSubstate(SubstateSlot& var1) {
    for (auto it = m_subStates.begin(); it != m_subStates.end(); ++it) {
        if (&(*it) == &var1) {
            m_subStates.erase(it);
            break;
        }
    }
}

bool StateMachine::isSubstate(State var1) {
    for (const auto& slot : m_subStates) {
        if (slot.getState() == var1) {
            return true;
        }
    }
    return false;
}

State StateMachine::getCurrent() {
    return m_currentState;
}

State StateMachine::getPrevious() {
    return m_previousState;
}

int StateMachine::getSubStateCount() {
    return static_cast<int>(m_subStates.size());
}

State StateMachine::getSubStateAt(int var1) {
    if (var1 >= 0 && var1 < static_cast<int>(m_subStates.size())) {
        return m_subStates[var1].getState();
    }
    return nullptr;
}

void StateMachine::revertToPreviousState(State var1) {
    if (m_previousState != nullptr && m_currentState == var1) {
        changeRootState(m_previousState, false);
    }
}

void StateMachine::update() {
    if (m_currentState != nullptr) {
        m_currentState->execute(m_owner);
    }
    for (auto& slot : m_subStates) {
        if (slot.getState() != nullptr) {
            slot.getState()->execute(m_owner);
        }
    }
}

void StateMachine::logCurrentState() {
    std::string stateName = m_currentState ? m_currentState->getName() : "None";
    DebugLog::AI.debug("StateMachine::logCurrentState: %s", stateName.c_str());
}

void StateMachine::stateEnter(State var1) {
    if (var1 != nullptr) {
        var1->enter(m_owner);
    }
}

void StateMachine::stateExit(State var1) {
    if (var1 != nullptr) {
        var1->exit(m_owner);
    }
}

void StateMachine::stateAnimEvent(int var1, AnimEvent var2) {
    State state = getSubStateAt(var1);
    if (state != nullptr) {
        state->animEvent(m_owner, var2);
    }
}

bool StateMachine::isLocked() {
    return m_isLocked;
}

void StateMachine::setLocked(bool var1) {
    m_isLocked = var1;
}

} // namespace ai
} // namespace zombie

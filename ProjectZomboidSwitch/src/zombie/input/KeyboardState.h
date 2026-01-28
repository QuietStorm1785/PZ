#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <SDL2/SDL.h>

namespace zombie {
namespace input {


class KeyboardState {
public:
    KeyboardState() : m_isCreated(false), m_wasPolled(false) {
        m_keyDownStates.resize(SDL_NUM_SCANCODES, false);
    }

    void poll() {
        m_wasPolled = true;
        const Uint8* state = SDL_GetKeyboardState(nullptr);
        for (int i = 0; i < SDL_NUM_SCANCODES; ++i) {
            m_keyDownStates[i] = state[i];
        }
        m_isCreated = true;
    }

    bool wasPolled() const { return m_wasPolled; }
    void reset() { m_wasPolled = false; }
    bool isCreated() const { return m_isCreated; }
    bool isKeyDown(int scancode) const {
        if (scancode < 0 || scancode >= (int)m_keyDownStates.size()) return false;
        return m_keyDownStates[scancode];
    }
    int getKeyCount() const { return (int)m_keyDownStates.size(); }

private:
    bool m_isCreated;
    std::vector<bool> m_keyDownStates;
    bool m_wasPolled;
};
} // namespace input
} // namespace zombie

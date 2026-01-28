// SDL2-based GameKeyboard implementation
#include "GameKeyboard.h"
#include <SDL2/SDL.h>
#include <cstring>

GameKeyboard::GameKeyboard() {
    currentKeys_ = SDL_GetKeyboardState(&numKeys_);
    lastKeys_.resize(numKeys_, 0);
}

void GameKeyboard::update() {
    // Save previous state
    if (numKeys_ > 0) {
        std::memcpy(lastKeys_.data(), currentKeys_, numKeys_);
    }
    SDL_PumpEvents();
    currentKeys_ = SDL_GetKeyboardState(nullptr);
}

bool GameKeyboard::isKeyDown(SDL_Scancode scancode) const {
    return currentKeys_ && currentKeys_[scancode];
}

bool GameKeyboard::isKeyPressed(SDL_Scancode scancode) const {
    return currentKeys_ && lastKeys_.size() > (size_t)scancode && currentKeys_[scancode] && !lastKeys_[scancode];
}

bool GameKeyboard::isKeyReleased(SDL_Scancode scancode) const {
    return currentKeys_ && lastKeys_.size() > (size_t)scancode && !currentKeys_[scancode] && lastKeys_[scancode];
}

void GameKeyboard::handleEvent(const SDL_Event& event) {
    // For future event-based logic if needed
}
}

KeyEventQueue GameKeyboard::getEventQueue() {
    // TODO: Implement getEventQueue
    return nullptr;
}

KeyEventQueue GameKeyboard::getEventQueuePolling() {
    // TODO: Implement getEventQueuePolling
    return nullptr;
}

} // namespace input
} // namespace zombie

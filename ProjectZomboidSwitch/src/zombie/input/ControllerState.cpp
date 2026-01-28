#include "ControllerState.h"
#include <SDL2/SDL.h>
#include <cstring>

ControllerState::ControllerState() {
    // Open all available controllers up to MAX_CONTROLLERS
    numControllers_ = 0;
    for (int i = 0; i < SDL_NumJoysticks() && numControllers_ < MAX_CONTROLLERS; ++i) {
        if (SDL_IsGameController(i)) {
            controllers_[numControllers_] = SDL_GameControllerOpen(i);
            if (controllers_[numControllers_]) {
                ++numControllers_;
            }
        }
    }
    isCreated_ = (numControllers_ > 0);
    wasPolled_ = false;
}

ControllerState::~ControllerState() {
    for (int i = 0; i < numControllers_; ++i) {
        if (controllers_[i]) {
            SDL_GameControllerClose(controllers_[i]);
            controllers_[i] = nullptr;
        }
    }
    numControllers_ = 0;
}

void ControllerState::poll() {
    wasPolled_ = true;
    // SDL2 handles polling internally; just call SDL_GameControllerUpdate if needed
    SDL_GameControllerUpdate();
}

bool ControllerState::wasPolled() const {
    return wasPolled_;
}

void ControllerState::reset() {
    wasPolled_ = false;
}

bool ControllerState::isCreated() const {
    return isCreated_;
}

SDL_GameController* ControllerState::getController(int idx) const {
    if (idx < 0 || idx >= numControllers_) return nullptr;
    return controllers_[idx];
}

bool ControllerState::isButtonDown(int idx, SDL_GameControllerButton button) const {
    if (auto c = getController(idx)) {
        return SDL_GameControllerGetButton(c, button) != 0;
    }
    return false;
}

Sint16 ControllerState::getAxis(int idx, SDL_GameControllerAxis axis) const {
    if (auto c = getController(idx)) {
        return SDL_GameControllerGetAxis(c, axis);
    }
    return 0;
}

int ControllerState::getNumControllers() const {
    return numControllers_;
}

#include "MouseState.h"
#include <SDL2/SDL.h>

MouseState::MouseState() {
    buttonDownStates_.resize(5, false);
}

void MouseState::update() {
    SDL_PumpEvents();
    int mouseX, mouseY;
    Uint32 buttons = SDL_GetMouseState(&mouseX, &mouseY);
    x_ = mouseX;
    y_ = mouseY;
    buttonDownStates_[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
    buttonDownStates_[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
    buttonDownStates_[2] = buttons & SDL_BUTTON(SDL_BUTTON_MIDDLE);
    buttonDownStates_[3] = buttons & SDL_BUTTON(4);
    buttonDownStates_[4] = buttons & SDL_BUTTON(5);
    created_ = true;

    // Handle wheel events
    dWheel_ = 0;
    SDL_Event event;
    while (SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_MOUSEWHEEL, SDL_MOUSEWHEEL)) {
        if (event.type == SDL_MOUSEWHEEL) {
            dWheel_ += event.wheel.y;
        }
    }
}

int MouseState::getX() const {
    return x_;
}

int MouseState::getY() const {
    return y_;
}

bool MouseState::isButtonDown(int button) const {
    if (button < 0 || button >= (int)buttonDownStates_.size()) return false;
    return buttonDownStates_[button];
}

int MouseState::getDWheel() const {
    return dWheel_;
}

void MouseState::resetDWheel() {
    dWheel_ = 0;
}

int MouseState::getButtonCount() const {
    return (int)buttonDownStates_.size();
}

bool MouseState::isCreated() const {
    return created_;
}

void MouseState::setCursorPosition(int x, int y) {
    SDL_WarpMouseInWindow(nullptr, x, y);
    x_ = x;
    y_ = y;
}

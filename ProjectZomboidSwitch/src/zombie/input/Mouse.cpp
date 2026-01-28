#include <string>
#include "zombie/input/Mouse.h"

namespace zombie {
namespace input {

int Mouse::getWheelState() {
    // TODO: Implement getWheelState
    return 0;

#include "Mouse.h"
#include <SDL2/SDL.h>
#include <algorithm>
#include <iostream>

Mouse::Mouse() {
    buttonDownStates_.resize(5, false);
}

void Mouse::update() {
    leftWasDown_ = leftDown_;
    rightWasDown_ = rightDown_;
    middleWasDown_ = middleDown_;
    wheelDelta_ = 0;

    SDL_PumpEvents();
    int mouseX, mouseY;
    Uint32 buttons = SDL_GetMouseState(&mouseX, &mouseY);
    x_ = mouseX;
    y_ = mouseY;
    leftDown_ = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
    rightDown_ = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
    middleDown_ = buttons & SDL_BUTTON(SDL_BUTTON_MIDDLE);
    buttonDownStates_[0] = leftDown_;
    buttonDownStates_[1] = rightDown_;
    buttonDownStates_[2] = middleDown_;
    buttonDownStates_[3] = buttons & SDL_BUTTON(4);
    buttonDownStates_[4] = buttons & SDL_BUTTON(5);

    // Handle wheel events
    SDL_Event event;
    while (SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_MOUSEWHEEL, SDL_MOUSEWHEEL)) {
        if (event.type == SDL_MOUSEWHEEL) {
            wheelDelta_ += event.wheel.y;
        }
    }
}

void Mouse::poll() {
    // No-op for SDL2, as SDL_PumpEvents is called in update
}

void Mouse::setXY(int newX, int newY) {
    SDL_WarpMouseInWindow(nullptr, newX, newY);
    x_ = newX;
    y_ = newY;
}

int Mouse::getX() const {
    return x_;
}

int Mouse::getY() const {
    return y_;
}

int Mouse::getWheelState() const {
    return wheelDelta_;
}

bool Mouse::isButtonDown(int button) const {
    if (button < 0 || button >= (int)buttonDownStates_.size()) return false;
    return buttonDownStates_[button];
}

bool Mouse::isLeftDown() const {
    return leftDown_;
}
bool Mouse::isLeftPressed() const {
    return !leftWasDown_ && leftDown_;
}
bool Mouse::isLeftReleased() const {
    return leftWasDown_ && !leftDown_;
}
bool Mouse::isLeftUp() const {
    return !leftDown_;
}
bool Mouse::isMiddleDown() const {
    return middleDown_;
}
bool Mouse::isMiddlePressed() const {
    return !middleWasDown_ && middleDown_;
}
bool Mouse::isMiddleReleased() const {
    return middleWasDown_ && !middleDown_;
}
bool Mouse::isMiddleUp() const {
    return !middleDown_;
}
bool Mouse::isRightDown() const {
    return rightDown_;
}
bool Mouse::isRightPressed() const {
    return !rightWasDown_ && rightDown_;
}
bool Mouse::isRightReleased() const {
    return rightWasDown_ && !rightDown_;
}
bool Mouse::isRightUp() const {
    return !rightDown_;
}

void Mouse::setCursorVisible(bool visible) {
    cursorVisible_ = visible;
    SDL_ShowCursor(visible ? SDL_ENABLE : SDL_DISABLE);
}

bool Mouse::isCursorVisible() const {
    return cursorVisible_;
}

void Mouse::renderCursorTexture() {
    // Rendering custom cursor is handled elsewhere, or use SDL_SetCursor for custom cursors
}

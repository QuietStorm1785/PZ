#include "InputManager.h"
#include <cstring>
#include <iostream>

namespace zombie {
namespace input {

InputManager* InputManager::instance = nullptr;

InputManager* InputManager::getInstance() {
    if (!instance) {
        instance = new InputManager();
    }
    return instance;
}

InputManager::InputManager()
    : currentKeyState(nullptr)
    , mouseX(0)
    , mouseY(0)
    , prevMouseX(0)
    , prevMouseY(0)
    , mouseDeltaX(0)
    , mouseDeltaY(0)
    , currentMouseState(0)
    , previousMouseState(0)
    , gamepad(nullptr)
    , textInputActive(false)
{
    std::memset(previousKeyState, 0, sizeof(previousKeyState));
    currentKeyState = SDL_GetKeyboardState(nullptr);
    
    // Try to open first available gamepad
    openFirstGamepad();
}

InputManager::~InputManager() {
    if (gamepad) {
        SDL_GameControllerClose(gamepad);
        gamepad = nullptr;
    }
}

void InputManager::update() {
    updateKeyboard();
    updateMouse();
    updateGamepad();
}

void InputManager::updateKeyboard() {
    // Copy current state to previous
    std::memcpy(previousKeyState, currentKeyState, SDL_NUM_SCANCODES);
    
    // Get new current state
    currentKeyState = SDL_GetKeyboardState(nullptr);
}

void InputManager::updateMouse() {
    previousMouseState = currentMouseState;
    
    prevMouseX = mouseX;
    prevMouseY = mouseY;
    
    currentMouseState = SDL_GetMouseState(&mouseX, &mouseY);
    
    mouseDeltaX = mouseX - prevMouseX;
    mouseDeltaY = mouseY - prevMouseY;
}

void InputManager::updateGamepad() {
    if (!gamepad) return;
    
    // Update button states
    for (auto& pair : currentButtonState) {
        previousButtonState[pair.first] = pair.second;
    }
    
    // Gamepad state is updated through events
}

bool InputManager::isKeyDown(SDL_Scancode key) const {
    return currentKeyState[key] != 0;
}

bool InputManager::isKeyPressed(SDL_Scancode key) const {
    return currentKeyState[key] != 0 && previousKeyState[key] == 0;
}

bool InputManager::isKeyReleased(SDL_Scancode key) const {
    return currentKeyState[key] == 0 && previousKeyState[key] != 0;
}

bool InputManager::isMouseButtonDown(int button) const {
    return (currentMouseState & SDL_BUTTON(button)) != 0;
}

bool InputManager::isMouseButtonPressed(int button) const {
    return (currentMouseState & SDL_BUTTON(button)) != 0 &&
           (previousMouseState & SDL_BUTTON(button)) == 0;
}

bool InputManager::isMouseButtonReleased(int button) const {
    return (currentMouseState & SDL_BUTTON(button)) == 0 &&
           (previousMouseState & SDL_BUTTON(button)) != 0;
}

float InputManager::getAxisValue(int axis) const {
    auto it = axisValues.find(axis);
    if (it != axisValues.end()) {
        return it->second;
    }
    return 0.0f;
}

bool InputManager::isGamepadButtonDown(int button) const {
    auto it = currentButtonState.find(button);
    if (it != currentButtonState.end()) {
        return it->second;
    }
    return false;
}

bool InputManager::isGamepadButtonPressed(int button) const {
    auto itCurrent = currentButtonState.find(button);
    auto itPrevious = previousButtonState.find(button);
    
    bool current = (itCurrent != currentButtonState.end()) ? itCurrent->second : false;
    bool previous = (itPrevious != previousButtonState.end()) ? itPrevious->second : false;
    
    return current && !previous;
}

void InputManager::startTextInput() {
    textInputActive = true;
    textInput.clear();
    SDL_StartTextInput();
}

void InputManager::stopTextInput() {
    textInputActive = false;
    SDL_StopTextInput();
}

void InputManager::clearTextInput() {
    textInput.clear();
}

void InputManager::processEvent(const SDL_Event& event) {
    switch (event.type) {
        case SDL_CONTROLLERDEVICEADDED:
            if (!gamepad) {
                openFirstGamepad();
            }
            break;
            
        case SDL_CONTROLLERDEVICEREMOVED:
            if (gamepad && event.cdevice.which == SDL_JoystickInstanceID(
                    SDL_GameControllerGetJoystick(gamepad))) {
                SDL_GameControllerClose(gamepad);
                gamepad = nullptr;
            }
            break;
            
        case SDL_CONTROLLERBUTTONDOWN:
            currentButtonState[event.cbutton.button] = true;
            break;
            
        case SDL_CONTROLLERBUTTONUP:
            currentButtonState[event.cbutton.button] = false;
            break;
            
        case SDL_CONTROLLERAXISMOTION:
            // Normalize axis value to -1.0 to 1.0
            axisValues[event.caxis.axis] = event.caxis.value / 32768.0f;
            break;
            
        case SDL_TEXTINPUT:
            if (textInputActive) {
                textInput += event.text.text;
            }
            break;
            
        case SDL_KEYDOWN:
            if (textInputActive && event.key.keysym.sym == SDLK_BACKSPACE && !textInput.empty()) {
                textInput.pop_back();
            }
            break;
    }
}

void InputManager::openFirstGamepad() {
    for (int i = 0; i < SDL_NumJoysticks(); i++) {
        if (SDL_IsGameController(i)) {
            gamepad = SDL_GameControllerOpen(i);
            if (gamepad) {
                std::cout << "Opened gamepad: " << SDL_GameControllerName(gamepad) << std::endl;
                break;
            }
        }
    }
}

} // namespace input
} // namespace zombie

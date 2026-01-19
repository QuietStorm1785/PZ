#include "InputManager.h"
#include "Config.h"
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cctype>

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

namespace {
SDL_GameControllerButton stringToButton(const std::string& name) {
 std::string lower = name;
 std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

 if (lower == "a") return SDL_CONTROLLER_BUTTON_A;
 if (lower == "b") return SDL_CONTROLLER_BUTTON_B;
 if (lower == "x") return SDL_CONTROLLER_BUTTON_X;
 if (lower == "y") return SDL_CONTROLLER_BUTTON_Y;
 if (lower == "l" || lower == "lb" || lower == "leftshoulder") return SDL_CONTROLLER_BUTTON_LEFTSHOULDER;
 if (lower == "r" || lower == "rb" || lower == "rightshoulder") return SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;
 if (lower == "zl" || lower == "lt") return SDL_CONTROLLER_BUTTON_LEFTSHOULDER; // Map trigger to shoulder button
 if (lower == "zr" || lower == "rt") return SDL_CONTROLLER_BUTTON_RIGHTSHOULDER; // Map trigger to shoulder button
 if (lower == "start" || lower == "plus") return SDL_CONTROLLER_BUTTON_START;
 if (lower == "select" || lower == "minus" || lower == "back") return SDL_CONTROLLER_BUTTON_BACK;
 if (lower == "guide" || lower == "home") return SDL_CONTROLLER_BUTTON_GUIDE;
 if (lower == "ls" || lower == "leftstick") return SDL_CONTROLLER_BUTTON_LEFTSTICK;
 if (lower == "rs" || lower == "rightstick") return SDL_CONTROLLER_BUTTON_RIGHTSTICK;
 if (lower == "dpup" || lower == "dpad_up") return SDL_CONTROLLER_BUTTON_DPAD_UP;
 if (lower == "dpdown" || lower == "dpad_down") return SDL_CONTROLLER_BUTTON_DPAD_DOWN;
 if (lower == "dpleft" || lower == "dpad_left") return SDL_CONTROLLER_BUTTON_DPAD_LEFT;
 if (lower == "dpright" || lower == "dpad_right") return SDL_CONTROLLER_BUTTON_DPAD_RIGHT;
 return SDL_CONTROLLER_BUTTON_INVALID;
}

SDL_GameControllerButton defaultActionButton(const std::string& action) {
 std::string lower = action;
 std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
 // Nintendo Switch defaults: A interact, B sprint, Y inventory, ZL shove/aim, ZR attack/run, Plus pause
 if (lower == "confirm") return SDL_CONTROLLER_BUTTON_A;
 if (lower == "cancel") return SDL_CONTROLLER_BUTTON_B;
 if (lower == "interact") return SDL_CONTROLLER_BUTTON_A;
 if (lower == "inventory") return SDL_CONTROLLER_BUTTON_Y;
 if (lower == "sprint") return SDL_CONTROLLER_BUTTON_B;
 if (lower == "aim" || lower == "shove") return SDL_CONTROLLER_BUTTON_LEFTSHOULDER; // ZL mapped to shoulder
 if (lower == "fire") return SDL_CONTROLLER_BUTTON_RIGHTSHOULDER; // ZR mapped to shoulder
 if (lower == "pause") return SDL_CONTROLLER_BUTTON_START;
 if (lower == "map") return SDL_CONTROLLER_BUTTON_BACK;
 if (lower == "radial") return SDL_CONTROLLER_BUTTON_LEFTSTICK; // Quick radial on L3
 return SDL_CONTROLLER_BUTTON_INVALID;
}
} // namespace

void InputManager::configureFromSwitchConfig(const zombie::config::SwitchConfig& cfg) {
 controllerDeadzone = cfg.controllerDeadzone;
 triggerThreshold = cfg.triggerThreshold;
 lookSensitivity = cfg.lookSensitivity;

 actionBindings.clear();
 for (const auto& pair : cfg.controllerBindings) {
 SDL_GameControllerButton btn = stringToButton(pair.first);
 if (btn == SDL_CONTROLLER_BUTTON_INVALID) {
 std::cerr << "InputManager: Unknown controller binding key '" << pair.first << "'" << '\n';
 continue;
 }
 actionBindings[pair.second] = btn; // action name from config value
 }
}

bool InputManager::isActionDown(const std::string& action) const {
 SDL_GameControllerButton btn = SDL_CONTROLLER_BUTTON_INVALID;
 auto it = actionBindings.find(action);
 if (it != actionBindings.end()) {
 btn = it->second;
 } else {
 btn = defaultActionButton(action);
 }
 if (btn == SDL_CONTROLLER_BUTTON_INVALID) return false;
 return isGamepadButtonDown(btn);
}

bool InputManager::isActionPressed(const std::string& action) const {
 SDL_GameControllerButton btn = SDL_CONTROLLER_BUTTON_INVALID;
 auto it = actionBindings.find(action);
 if (it != actionBindings.end()) {
 btn = it->second;
 } else {
 btn = defaultActionButton(action);
 }
 if (btn == SDL_CONTROLLER_BUTTON_INVALID) return false;
 return isGamepadButtonPressed(btn);
}

void InputManager::openFirstGamepad() {
 for (int i = 0; i < SDL_NumJoysticks(); i++) {
 if (SDL_IsGameController(i)) {
 gamepad = SDL_GameControllerOpen(i);
 if (gamepad) {
 std::cout << "Opened gamepad: " << SDL_GameControllerName(gamepad) << '\n';
 break;
 }
 }
 }
}

void InputManager::rebindAction(const std::string& action, const std::string& buttonName) {
 std::string lower = buttonName;
 std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
 
 SDL_GameControllerButton btn = stringToButton(lower);
 if (btn == SDL_CONTROLLER_BUTTON_INVALID) {
 std::cerr << "InputManager: Invalid button name '" << buttonName << "'" << '\n';
 return;
 }
 
 actionBindings[action] = btn;
 std::cout << "InputManager: Rebound '" << action << "' to button '" << buttonName << "'" << '\n';
}

} // namespace input
} // namespace zombie

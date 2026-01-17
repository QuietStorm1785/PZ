#pragma once
#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>
#include <algorithm>

namespace zombie { namespace config { struct SwitchConfig; } }

namespace zombie {
namespace input {

/**
 * InputManager - Centralized input handling
 */
class InputManager {
public:
    static InputManager* getInstance();
    
    InputManager();
    ~InputManager();
    
    // Update - call once per frame
    void update();
    
    // Keyboard state
    bool isKeyDown(SDL_Scancode key) const;
    bool isKeyPressed(SDL_Scancode key) const;  // Just pressed this frame
    bool isKeyReleased(SDL_Scancode key) const; // Just released this frame
    
    // Mouse state
    int getMouseX() const { return mouseX; }
    int getMouseY() const { return mouseY; }
    int getMouseDeltaX() const { return mouseDeltaX; }
    int getMouseDeltaY() const { return mouseDeltaY; }
    
    bool isMouseButtonDown(int button) const;
    bool isMouseButtonPressed(int button) const;
    bool isMouseButtonReleased(int button) const;
    
    // Mouse buttons
    enum MouseButton {
        LEFT = SDL_BUTTON_LEFT,
        MIDDLE = SDL_BUTTON_MIDDLE,
        RIGHT = SDL_BUTTON_RIGHT
    };
    
    // Gamepad support
    bool hasGamepad() const { return gamepad != nullptr; }
    float getAxisValue(int axis) const;
    bool isGamepadButtonDown(int button) const;
    bool isGamepadButtonPressed(int button) const;

    // Controller config
    void configureFromSwitchConfig(const zombie::config::SwitchConfig& cfg);
    float getControllerDeadzone() const { return controllerDeadzone; }
    float getTriggerThreshold() const { return triggerThreshold; }
    float getLookSensitivity() const { return lookSensitivity; }

    // Setters for live configuration
    void setControllerDeadzone(float deadzone) { controllerDeadzone = std::clamp(deadzone, 0.0f, 0.8f); }
    void setLookSensitivity(float sensitivity) { lookSensitivity = std::clamp(sensitivity, 0.1f, 2.0f); }
    void rebindAction(const std::string& action, const std::string& buttonName);

    // Action bindings (controller)
    bool isActionDown(const std::string& action) const;
    bool isActionPressed(const std::string& action) const;
    
    // Text input
    void startTextInput();
    void stopTextInput();
    bool isTextInputActive() const { return textInputActive; }
    std::string getTextInput() const { return textInput; }
    void clearTextInput();
    
    // Event processing
    void processEvent(const SDL_Event& event);
    
private:
    static InputManager* instance;
    
    // Keyboard
    const Uint8* currentKeyState;
    Uint8 previousKeyState[SDL_NUM_SCANCODES];
    
    // Mouse
    int mouseX, mouseY;
    int prevMouseX, prevMouseY;
    int mouseDeltaX, mouseDeltaY;
    Uint32 currentMouseState;
    Uint32 previousMouseState;
    
    // Gamepad
    SDL_GameController* gamepad;
    std::unordered_map<int, bool> currentButtonState;
    std::unordered_map<int, bool> previousButtonState;
    std::unordered_map<int, float> axisValues;

    // Controller tuning and bindings
    float controllerDeadzone = 0.15f;
    float triggerThreshold = 0.15f;
    float lookSensitivity = 1.0f;
    std::unordered_map<std::string, SDL_GameControllerButton> actionBindings; // action -> button
    
    // Text input
    bool textInputActive;
    std::string textInput;
    
    // Internal
    void updateKeyboard();
    void updateMouse();
    void updateGamepad();
    void openFirstGamepad();
};

} // namespace input
} // namespace zombie

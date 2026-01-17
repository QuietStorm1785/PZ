#pragma once
#include "UI.h"
#include <string>
#include <functional>
#include <memory>

namespace zombie {
namespace ui {

/**
 * A UI component for rebinding controller buttons to actions.
 * Shows the action name and waits for a button press, then stores the mapping.
 */
class ControllerRebindUI : public UIElement {
public:
    using RebindCallback = std::function<void(const std::string& action, const std::string& buttonName)>;

    explicit ControllerRebindUI(const std::string& id);

    // Start rebinding for an action (e.g., "interact", "attack")
    void startRebind(const std::string& actionName);

    // Cancel the current rebind
    void cancelRebind();

    // Check if actively waiting for input
    bool isRebinding() const { return rebinding; }

    // Set callback invoked when a button is pressed during rebind
    void setRebindCallback(RebindCallback cb) { onRebindComplete = cb; }

    // UIElement overrides
    void render() override;
    void handleInput(int x, int y, bool pressed) override;
    void update(float deltaTime) override;

    // Handle controller button presses directly
    void handleControllerButtonPress(int buttonCode);

private:
    std::string currentAction;
    bool rebinding;
    float rebindTimeout;
    RebindCallback onRebindComplete;

    std::string buttonCodeToName(int buttonCode);
};

} // namespace ui
} // namespace zombie

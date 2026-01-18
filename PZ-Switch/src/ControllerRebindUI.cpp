#include "ControllerRebindUI.h"
#include "Core.h"
#include <SDL2/SDL.h>
#include <iostream>

namespace zombie {
namespace ui {

ControllerRebindUI::ControllerRebindUI(const std::string& id)
 : UIElement(id, Vec4(0, 0, 0, 0))
 , rebinding(false)
 , rebindTimeout(0.0f)
{
}

void ControllerRebindUI::startRebind(const std::string& actionName) {
 currentAction = actionName;
 rebinding = true;
 rebindTimeout = 0.0f;
 std::cout << "Rebinding action: " << actionName << " - Press any controller button..." << std::endl;
}

void ControllerRebindUI::cancelRebind() {
 rebinding = false;
 currentAction.clear();
}

void ControllerRebindUI::render() {
 if (!rebinding || !isVisible()) return;

 auto* core = core::Core::getInstance();
 if (!core) return;

 // Draw semi-transparent overlay
 core->drawFilledRect(0, 0, static_cast<float>(core->getScreenWidth()),
 static_cast<float>(core->getScreenHeight()),
 0, 0, 0, 150);

 // Draw prompt box
 float boxW = 400.0f;
 float boxH = 150.0f;
 float boxX = (core->getScreenWidth() - boxW) / 2.0f;
 float boxY = (core->getScreenHeight() - boxH) / 2.0f;

 core->drawFilledRect(boxX, boxY, boxW, boxH, 40, 40, 40, 255);
 core->drawRect(boxX, boxY, boxW, boxH, 200, 200, 200, 255);

 // Draw text prompts (would use font rendering in real implementation)
 // For now just visual feedback
}

void ControllerRebindUI::update(float deltaTime) {
 if (!rebinding) return;

 rebindTimeout += deltaTime;
 // Timeout after 5 seconds
 if (rebindTimeout >= 5.0f) {
 cancelRebind();
 }
}

void ControllerRebindUI::handleInput(int x, int y, bool pressed) {
 // Mouse input not used for rebinding
}

void ControllerRebindUI::handleControllerButtonPress(int buttonCode) {
 if (!rebinding) return;

 std::string buttonName = buttonCodeToName(buttonCode);
 if (!buttonName.empty() && onRebindComplete) {
 onRebindComplete(currentAction, buttonName);
 }
 cancelRebind();
}

std::string ControllerRebindUI::buttonCodeToName(int buttonCode) {
 switch (buttonCode) {
 case SDL_CONTROLLER_BUTTON_A: return "a";
 case SDL_CONTROLLER_BUTTON_B: return "b";
 case SDL_CONTROLLER_BUTTON_X: return "x";
 case SDL_CONTROLLER_BUTTON_Y: return "y";
 case SDL_CONTROLLER_BUTTON_LEFTSHOULDER: return "lb";
 case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER: return "rb";
 case SDL_CONTROLLER_BUTTON_START: return "plus";
 case SDL_CONTROLLER_BUTTON_BACK: return "minus";
 case SDL_CONTROLLER_BUTTON_LEFTSTICK: return "ls";
 case SDL_CONTROLLER_BUTTON_RIGHTSTICK: return "rs";
 case SDL_CONTROLLER_BUTTON_GUIDE: return "home";
 case SDL_CONTROLLER_BUTTON_DPAD_UP: return "dpup";
 case SDL_CONTROLLER_BUTTON_DPAD_DOWN: return "dpdown";
 case SDL_CONTROLLER_BUTTON_DPAD_LEFT: return "dpleft";
 case SDL_CONTROLLER_BUTTON_DPAD_RIGHT: return "dpright";
 default: return "";
 }
}

} // namespace ui
} // namespace zombie

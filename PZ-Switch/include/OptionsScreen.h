#pragma once
#include "GameState.h"
#include "UI.h"
#include "ControllerRebindUI.h"
#include <memory>
#include <vector>
#include <string>
#include <functional>
#include "Config.h"

namespace zombie {
namespace ui {

/**
 * Options/Settings menu screen accessible from main menu.
 * Allows configuration of:
 * - Controller sensitivity
 * - Deadzone
 * - Keybind remapping
 */
class OptionsScreen : public gameStates::GameState {
public:
 using BackCallback = std::function<void()>;

 explicit OptionsScreen(BackCallback onBack);

 void enter() override;
 void exit() override;
 gameStates::StateAction update() override;
 void render() override;
 gameStates::GameState* redirectState() override;

 void setBackTarget(gameStates::GameState* state) { backTarget = state; }

private:
 void buildUI();
 void clearUI();
 void applySettings();
 void onRebindComplete(const std::string& action, const std::string& buttonName);

 BackCallback backCallback;
 std::vector<std::string> elementIds;
 std::shared_ptr<ControllerRebindUI> rebindUI;
 bool backRequested {false};
 gameStates::GameState* backTarget {nullptr};
 gameStates::GameState* pendingRedirect {nullptr};

 // Settings (temporary, synced to config on apply)
 float sensitivity;
 float deadzone;
 float brightness;
 float masterVolume;
 float musicVolume;
 float sfxVolume;
 bool vsyncEnabled;
 float isoCursorVisibility;
 bool showCursorWhileAiming;
 int aimOutlineMode;
 bool lockCursor;
 bool uiOffscreenRendering;
 int uiRenderingFps;
 int inventoryButtonSize;
 bool showModInfoTooltip;
 bool showSurvivalGuide;
 bool autosaveEnabled;
};

} // namespace ui
} // namespace zombie

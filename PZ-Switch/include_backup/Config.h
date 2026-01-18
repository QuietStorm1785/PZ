#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace zombie {
namespace config {

struct SwitchConfig {
    // Paths
    std::string mediaPath = "media/";
    std::vector<std::string> texturePacks;
    bool buildPackAtlas = false;
    int atlasMaxWidth = 2048;
    int atlasMaxHeight = 2048;

    // Graphics
    int width = 1280;
    int height = 720;
    bool fullscreen = false;
    bool vsync = true;
    int fpsCap = 60;

    // Controller
    float controllerDeadzone = 0.2f;
    float triggerThreshold = 0.15f;
    float lookSensitivity = 1.0f;
    std::unordered_map<std::string, std::string> controllerBindings;
};

struct GraphicsAudioOptions {
    float brightness = 1.0f;      // 0.0 (dark) to 1.0 (full bright)
    float masterVolume = 1.0f;    // 0.0 - 1.0
    float musicVolume = 1.0f;     // 0.0 - 1.0 (not yet wired separately)
    float sfxVolume = 1.0f;       // 0.0 - 1.0 (not yet wired separately)
    bool vsync = true;
    float isoCursorVisibility = 0.30f; // 0.0 = hidden, 1.0 = fully visible
    bool showCursorWhileAiming = false;
    int aimOutlineMode = 0;            // 0=None, 1=Ranged, 2=Any
    bool lockCursorToWindow = false;
    bool uiOffscreenRendering = false;
    int uiRenderingFps = 30;           // 10-30 reasonable range
    int inventoryButtonSize = 1;       // 0=Small,1=Medium,2=Large
    bool showModInfoTooltip = true;
    bool showSurvivalGuide = true;
    bool autosaveEnabled = true;       // autosave every 5 minutes
};

struct ControllerKeys {
    std::unordered_map<std::string, std::string> bindings; // action -> button name
};

// Loads a simple INI-style config for Nintendo Switch builds.
// Returns true if the file was parsed; false means defaults are kept.
bool loadSwitchConfig(const std::string& path, SwitchConfig& outConfig);
bool loadOptionsConfig(const std::string& path, GraphicsAudioOptions& outConfig);
bool saveOptionsConfig(const std::string& path, const GraphicsAudioOptions& cfg);
bool loadKeysConfig(const std::string& path, ControllerKeys& outKeys);
bool saveKeysConfig(const std::string& path, const ControllerKeys& keys);

// Runtime globals for options/keys (loaded at startup)
extern GraphicsAudioOptions gOptionsConfig;
extern ControllerKeys gKeysConfig;

} // namespace config
} // namespace zombie

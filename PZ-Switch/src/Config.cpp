#include "Config.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>

namespace zombie {
namespace config {

GraphicsAudioOptions gOptionsConfig{};
ControllerKeys gKeysConfig{};

namespace {
std::string trim(const std::string& input) {
 size_t start = 0;
 while (start < input.size() && std::isspace(static_cast<unsigned char>(input[start]))) {
 ++start;
 }
 size_t end = input.size();
 while (end > start && std::isspace(static_cast<unsigned char>(input[end - 1]))) {
 --end;
 }
 return input.substr(start, end - start);
}

std::string toLower(std::string value) {
 std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c) {
 return static_cast<char>(std::tolower(c));
 });
 return value;
}

bool parseBool(const std::string& value, bool defaultValue) {
 std::string v = toLower(trim(value));
 if (v == "true" || v == "1" || v == "yes" || v == "on") return true;
 if (v == "false" || v == "0" || v == "no" || v == "off") return false;
 return defaultValue;
}

int parseInt(const std::string& value, int defaultValue) {
 try {
 return std::stoi(value);
 } catch (...) {
 return defaultValue;
 }
}

float parseFloat(const std::string& value, float defaultValue) {
 try {
 return std::stof(value);
 } catch (...) {
 return defaultValue;
 }
}

std::vector<std::string> splitList(const std::string& value) {
 std::vector<std::string> result;
 std::stringstream ss(value);
 std::string item;
 while (std::getline(ss, item, ',')) {
 std::string entry = trim(item);
 if (!entry.empty()) {
 result.push_back(entry);
 }
 }
 return result;
}

} // namespace

bool loadSwitchConfig(const std::string& path, SwitchConfig& outConfig) {
 // Start with defaults
 SwitchConfig cfg;

 std::ifstream file(path);
 if (!file.is_open()) {
 std::cerr << "Switch config not found: " << path << " (using defaults)" << '\n';
 outConfig = cfg;
 return false;
 }

 std::string section;
 std::string line;
 while (std::getline(file, line)) {
 line = trim(line);
 if (line.empty() || line[0] == '#' || line[0] == ';') {
 continue; // Skip comments and empty lines
 }

 if (line.front() == '[' && line.back() == ']') {
 section = toLower(trim(line.substr(1, line.size() - 2)));
 continue;
 }

 size_t eq = line.find('=');
 if (eq == std::string::npos) {
 continue;
 }

 std::string key = toLower(trim(line.substr(0, eq)));
 std::string value = trim(line.substr(eq + 1));

 if (section == "paths") {
 if (key == "media") cfg.mediaPath = value;
 else if (key == "texture_packs") cfg.texturePacks = splitList(value);
 else if (key == "build_pack_atlas") cfg.buildPackAtlas = parseBool(value, cfg.buildPackAtlas);
 else if (key == "atlas_max_width") cfg.atlasMaxWidth = parseInt(value, cfg.atlasMaxWidth);
 else if (key == "atlas_max_height") cfg.atlasMaxHeight = parseInt(value, cfg.atlasMaxHeight);
 } else if (section == "graphics") {
 if (key == "width") cfg.width = parseInt(value, cfg.width);
 else if (key == "height") cfg.height = parseInt(value, cfg.height);
 else if (key == "fullscreen") cfg.fullscreen = parseBool(value, cfg.fullscreen);
 else if (key == "vsync") cfg.vsync = parseBool(value, cfg.vsync);
 else if (key == "fps_cap") cfg.fpsCap = parseInt(value, cfg.fpsCap);
 } else if (section == "controller") {
 if (key == "deadzone") cfg.controllerDeadzone = parseFloat(value, cfg.controllerDeadzone);
 else if (key == "trigger_threshold") cfg.triggerThreshold = parseFloat(value, cfg.triggerThreshold);
 else if (key == "look_sensitivity") cfg.lookSensitivity = parseFloat(value, cfg.lookSensitivity);
 else {
 // Store arbitrary button->action binding
 cfg.controllerBindings[key] = value;
 }
 }
 }

 // Normalize media path to ensure trailing slash for TextureManager
 if (!cfg.mediaPath.empty() && cfg.mediaPath.back() != '/' && cfg.mediaPath.back() != '\\') {
 cfg.mediaPath.push_back('/');
 }

 outConfig = cfg;
 std::cout << "Loaded Switch config: " << path << '\n';
 return true;
}

bool loadOptionsConfig(const std::string& path, GraphicsAudioOptions& outConfig) {
 GraphicsAudioOptions cfg;
 std::ifstream file(path);
 if (!file.is_open()) {
 std::cerr << "Options.ini not found: " << path << " (using defaults)" << '\n';
 outConfig = cfg;
 return false;
 }

 std::string section;
 std::string line;
 while (std::getline(file, line)) {
 line = trim(line);
 if (line.empty() || line[0] == '#' || line[0] == ';') continue;
 if (line.front() == '[' && line.back() == ']') {
 section = toLower(trim(line.substr(1, line.size() - 2)));
 continue;
 }

 size_t eq = line.find('=');
 if (eq == std::string::npos) continue;
 std::string key = toLower(trim(line.substr(0, eq)));
 std::string value = trim(line.substr(eq + 1));

 if (section == "graphics") {
 if (key == "brightness") cfg.brightness = std::clamp(parseFloat(value, cfg.brightness), 0.0f, 1.0f);
 else if (key == "vsync") cfg.vsync = parseBool(value, cfg.vsync);
 else if (key == "iso_cursor_visibility") cfg.isoCursorVisibility = std::clamp(parseFloat(value, cfg.isoCursorVisibility), 0.0f, 1.0f);
 else if (key == "lock_cursor_to_window") cfg.lockCursorToWindow = parseBool(value, cfg.lockCursorToWindow);
 else if (key == "ui_offscreen_rendering") cfg.uiOffscreenRendering = parseBool(value, cfg.uiOffscreenRendering);
 else if (key == "ui_rendering_fps") cfg.uiRenderingFps = parseInt(value, cfg.uiRenderingFps);
 } else if (section == "audio") {
 if (key == "master_volume") cfg.masterVolume = std::clamp(parseFloat(value, cfg.masterVolume), 0.0f, 1.0f);
 else if (key == "music_volume") cfg.musicVolume = std::clamp(parseFloat(value, cfg.musicVolume), 0.0f, 1.0f);
 else if (key == "sfx_volume") cfg.sfxVolume = std::clamp(parseFloat(value, cfg.sfxVolume), 0.0f, 1.0f);
 } else if (section == "ui") {
 if (key == "show_cursor_while_aiming") cfg.showCursorWhileAiming = parseBool(value, cfg.showCursorWhileAiming);
 else if (key == "aim_outline_mode") cfg.aimOutlineMode = std::clamp(parseInt(value, cfg.aimOutlineMode), 0, 2);
 else if (key == "inventory_button_size") cfg.inventoryButtonSize = std::clamp(parseInt(value, cfg.inventoryButtonSize), 0, 2);
 else if (key == "show_mod_info_tooltip") cfg.showModInfoTooltip = parseBool(value, cfg.showModInfoTooltip);
 else if (key == "show_survival_guide") cfg.showSurvivalGuide = parseBool(value, cfg.showSurvivalGuide);
 else if (key == "autosave_enabled") cfg.autosaveEnabled = parseBool(value, cfg.autosaveEnabled);
 }
 }

 outConfig = cfg;
 std::cout << "Loaded Options.ini: " << path << '\n';
 return true;
}

bool saveOptionsConfig(const std::string& path, const GraphicsAudioOptions& cfg) {
 std::ofstream file(path, std::ios::trunc);
 if (!file.is_open()) {
 std::cerr << "Failed to write Options.ini at " << path << '\n';
 return false;
 }

 file << "[Graphics]\n";
 file << "Brightness=" << cfg.brightness << "\n";
 file << "VSync=" << (cfg.vsync ? "true" : "false") << "\n";
 file << "Iso_Cursor_Visibility=" << cfg.isoCursorVisibility << "\n";
 file << "Lock_Cursor_To_Window=" << (cfg.lockCursorToWindow ? "true" : "false") << "\n";
 file << "UI_Offscreen_Rendering=" << (cfg.uiOffscreenRendering ? "true" : "false") << "\n";
 file << "UI_Rendering_FPS=" << cfg.uiRenderingFps << "\n\n";

 file << "[Audio]\n";
 file << "Master_Volume=" << cfg.masterVolume << "\n";
 file << "Music_Volume=" << cfg.musicVolume << "\n";
 file << "SFX_Volume=" << cfg.sfxVolume << "\n\n";

 file << "[UI]\n";
 file << "Show_Cursor_While_Aiming=" << (cfg.showCursorWhileAiming ? "true" : "false") << "\n";
 file << "Aim_Outline_Mode=" << cfg.aimOutlineMode << "\n";
 file << "Inventory_Button_Size=" << cfg.inventoryButtonSize << "\n";
 file << "Show_Mod_Info_Tooltip=" << (cfg.showModInfoTooltip ? "true" : "false") << "\n";
 file << "Show_Survival_Guide=" << (cfg.showSurvivalGuide ? "true" : "false") << "\n";
 file << "Autosave_Enabled=" << (cfg.autosaveEnabled ? "true" : "false") << "\n";

 std::cout << "Saved Options.ini to " << path << '\n';
 return true;
}

bool loadKeysConfig(const std::string& path, ControllerKeys& outKeys) {
 ControllerKeys cfg;
 std::ifstream file(path);
 if (!file.is_open()) {
 std::cerr << "keys.ini not found: " << path << " (using defaults)" << '\n';
 outKeys = cfg;
 return false;
 }

 std::string line;
 while (std::getline(file, line)) {
 line = trim(line);
 if (line.empty() || line[0] == '#' || line[0] == ';' || line.front() == '[') continue;
 size_t eq = line.find('=');
 if (eq == std::string::npos) continue;
 std::string action = toLower(trim(line.substr(0, eq)));
 std::string button = toLower(trim(line.substr(eq + 1)));
 if (!action.empty() && !button.empty()) {
 cfg.bindings[action] = button;
 }
 }

 outKeys = cfg;
 std::cout << "Loaded keys.ini: " << path << '\n';
 return true;
}

bool saveKeysConfig(const std::string& path, const ControllerKeys& keys) {
 std::ofstream file(path, std::ios::trunc);
 if (!file.is_open()) {
 std::cerr << "Failed to write keys.ini at " << path << '\n';
 return false;
 }

 file << "[Controller]\n";
 for (const auto& pair : keys.bindings) {
 file << pair.first << "=" << pair.second << "\n";
 }

 std::cout << "Saved keys.ini to " << path << '\n';
 return true;
}

} // namespace config
} // namespace zombie

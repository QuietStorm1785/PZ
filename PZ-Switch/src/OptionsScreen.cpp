#include "OptionsScreen.h"
#include "Core.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "Config.h"
#include "SaveLoad.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <ctime>

namespace zombie {
namespace ui {

OptionsScreen::OptionsScreen(BackCallback onBack)
 : backCallback(std::move(onBack))
 , sensitivity(1.0f)
 , deadzone(0.2f)
 , brightness(zombie::config::gOptionsConfig.brightness)
 , masterVolume(zombie::config::gOptionsConfig.masterVolume)
 , musicVolume(zombie::config::gOptionsConfig.musicVolume)
 , sfxVolume(zombie::config::gOptionsConfig.sfxVolume)
 , vsyncEnabled(zombie::config::gOptionsConfig.vsync)
 , isoCursorVisibility(zombie::config::gOptionsConfig.isoCursorVisibility)
 , showCursorWhileAiming(zombie::config::gOptionsConfig.showCursorWhileAiming)
 , aimOutlineMode(zombie::config::gOptionsConfig.aimOutlineMode)
 , lockCursor(zombie::config::gOptionsConfig.lockCursorToWindow)
 , uiOffscreenRendering(zombie::config::gOptionsConfig.uiOffscreenRendering)
 , uiRenderingFps(zombie::config::gOptionsConfig.uiRenderingFps)
 , inventoryButtonSize(zombie::config::gOptionsConfig.inventoryButtonSize)
 , showModInfoTooltip(zombie::config::gOptionsConfig.showModInfoTooltip)
 , showSurvivalGuide(zombie::config::gOptionsConfig.showSurvivalGuide)
 , autosaveEnabled(zombie::config::gOptionsConfig.autosaveEnabled)
{
}

void OptionsScreen::enter() {
 std::cout << "Entering Options Screen" << std::endl;
 // Sync from global config on enter
 auto* inputMgr = input::InputManager::getInstance();
 sensitivity = inputMgr->getLookSensitivity();
 deadzone = inputMgr->getControllerDeadzone();
 brightness = zombie::config::gOptionsConfig.brightness;
 masterVolume = zombie::config::gOptionsConfig.masterVolume;
 musicVolume = zombie::config::gOptionsConfig.musicVolume;
 sfxVolume = zombie::config::gOptionsConfig.sfxVolume;
 vsyncEnabled = zombie::config::gOptionsConfig.vsync;
 isoCursorVisibility = zombie::config::gOptionsConfig.isoCursorVisibility;
 showCursorWhileAiming = zombie::config::gOptionsConfig.showCursorWhileAiming;
 aimOutlineMode = zombie::config::gOptionsConfig.aimOutlineMode;
 lockCursor = zombie::config::gOptionsConfig.lockCursorToWindow;
 uiOffscreenRendering = zombie::config::gOptionsConfig.uiOffscreenRendering;
 uiRenderingFps = zombie::config::gOptionsConfig.uiRenderingFps;
 inventoryButtonSize = zombie::config::gOptionsConfig.inventoryButtonSize;
 showModInfoTooltip = zombie::config::gOptionsConfig.showModInfoTooltip;
 showSurvivalGuide = zombie::config::gOptionsConfig.showSurvivalGuide;
 autosaveEnabled = zombie::config::gOptionsConfig.autosaveEnabled;
 buildUI();
}

void OptionsScreen::exit() {
 std::cout << "Exiting Options Screen" << std::endl;
 clearUI();
}

gameStates::StateAction OptionsScreen::update() {
 if (backRequested && backTarget) {
 pendingRedirect = backTarget;
 backRequested = false;
 return gameStates::StateAction::Continue;
 }
 // UI handling is done by UIManager in the main loop
 return gameStates::StateAction::Remain;
}

void OptionsScreen::render() {
 auto* core = core::Core::getInstance();
 if (!core) return;

 // Draw background
 core->drawFilledRect(0, 0,
 static_cast<float>(core->getScreenWidth()),
 static_cast<float>(core->getScreenHeight()),
 60, 60, 80, 255);
}

void OptionsScreen::buildUI() {
 auto& uiMgr = UIManager::getInstance();

 // Layout helpers
 const float baseX = 100.0f;
 const float baseY = 50.0f;
 const float spacing = 60.0f;

 // Sensitivity
 Vec4 sensLabelBounds(baseX, baseY, 180.0f, 40.0f);
 auto sensLabel = std::make_shared<UIButton>("sens_label", sensLabelBounds, "Look Sensitivity");
 sensLabel->setOnClick([]() {});
 uiMgr.addElement(sensLabel);
 elementIds.push_back("sens_label");

 Vec4 sensIncBounds(baseX + 220.0f, baseY, 50.0f, 40.0f);
 auto sensInc = std::make_shared<UIButton>("sens_inc", sensIncBounds, "+");
 sensInc->setOnClick([this]() {
 sensitivity = std::min(2.0f, sensitivity + 0.1f);
 std::cout << "Sensitivity: " << sensitivity << std::endl;
 });
 uiMgr.addElement(sensInc);
 elementIds.push_back("sens_inc");

 Vec4 sensDecBounds(baseX + 280.0f, baseY, 50.0f, 40.0f);
 auto sensDec = std::make_shared<UIButton>("sens_dec", sensDecBounds, "-");
 sensDec->setOnClick([this]() {
 sensitivity = std::max(0.1f, sensitivity - 0.1f);
 std::cout << "Sensitivity: " << sensitivity << std::endl;
 });
 uiMgr.addElement(sensDec);
 elementIds.push_back("sens_dec");

 // Deadzone
 Vec4 deadzBounds(baseX, baseY + spacing, 180.0f, 40.0f);
 auto deadzLabel = std::make_shared<UIButton>("deadz_label", deadzBounds, "Deadzone");
 deadzLabel->setOnClick([]() {});
 uiMgr.addElement(deadzLabel);
 elementIds.push_back("deadz_label");

 Vec4 deadzIncBounds(baseX + 220.0f, baseY + spacing, 50.0f, 40.0f);
 auto deadzInc = std::make_shared<UIButton>("deadz_inc", deadzIncBounds, "+");
 deadzInc->setOnClick([this]() {
 deadzone = std::min(0.8f, deadzone + 0.05f);
 std::cout << "Deadzone: " << deadzone << std::endl;
 });
 uiMgr.addElement(deadzInc);
 elementIds.push_back("deadz_inc");

 Vec4 deadzDecBounds(baseX + 280.0f, baseY + spacing, 50.0f, 40.0f);
 auto deadzDec = std::make_shared<UIButton>("deadz_dec", deadzDecBounds, "-");
 deadzDec->setOnClick([this]() {
 deadzone = std::max(0.0f, deadzone - 0.05f);
 std::cout << "Deadzone: " << deadzone << std::endl;
 });
 uiMgr.addElement(deadzDec);
 elementIds.push_back("deadz_dec");

 // Brightness
 Vec4 brightLabelBounds(baseX, baseY + spacing * 2.0f, 180.0f, 40.0f);
 auto brightLabel = std::make_shared<UIButton>("bright_label", brightLabelBounds, "Brightness");
 brightLabel->setOnClick([]() {});
 uiMgr.addElement(brightLabel);
 elementIds.push_back("bright_label");

 Vec4 brightIncBounds(baseX + 220.0f, baseY + spacing * 2.0f, 50.0f, 40.0f);
 auto brightInc = std::make_shared<UIButton>("bright_inc", brightIncBounds, "+");
 brightInc->setOnClick([this]() {
 brightness = std::min(1.0f, brightness + 0.05f);
 std::cout << "Brightness: " << brightness << std::endl;
 });
 uiMgr.addElement(brightInc);
 elementIds.push_back("bright_inc");

 Vec4 brightDecBounds(baseX + 280.0f, baseY + spacing * 2.0f, 50.0f, 40.0f);
 auto brightDec = std::make_shared<UIButton>("bright_dec", brightDecBounds, "-");
 brightDec->setOnClick([this]() {
 brightness = std::max(0.0f, brightness - 0.05f);
 std::cout << "Brightness: " << brightness << std::endl;
 });
 uiMgr.addElement(brightDec);
 elementIds.push_back("bright_dec");

 // Audio controls
 Vec4 masterLabelBounds(baseX, baseY + spacing * 3.0f, 180.0f, 40.0f);
 auto masterLabel = std::make_shared<UIButton>("master_label", masterLabelBounds, "Master Vol");
 masterLabel->setOnClick([]() {});
 uiMgr.addElement(masterLabel);
 elementIds.push_back("master_label");

 Vec4 masterIncBounds(baseX + 220.0f, baseY + spacing * 3.0f, 50.0f, 40.0f);
 auto masterInc = std::make_shared<UIButton>("master_inc", masterIncBounds, "+");
 masterInc->setOnClick([this]() {
 masterVolume = std::min(1.0f, masterVolume + 0.05f);
 std::cout << "Master Volume: " << masterVolume << std::endl;
 });
 uiMgr.addElement(masterInc);
 elementIds.push_back("master_inc");

 Vec4 masterDecBounds(baseX + 280.0f, baseY + spacing * 3.0f, 50.0f, 40.0f);
 auto masterDec = std::make_shared<UIButton>("master_dec", masterDecBounds, "-");
 masterDec->setOnClick([this]() {
 masterVolume = std::max(0.0f, masterVolume - 0.05f);
 std::cout << "Master Volume: " << masterVolume << std::endl;
 });
 uiMgr.addElement(masterDec);
 elementIds.push_back("master_dec");

 Vec4 musicLabelBounds(baseX, baseY + spacing * 4.0f, 180.0f, 40.0f);
 auto musicLabel = std::make_shared<UIButton>("music_label", musicLabelBounds, "Music Vol");
 musicLabel->setOnClick([]() {});
 uiMgr.addElement(musicLabel);
 elementIds.push_back("music_label");

 Vec4 musicIncBounds(baseX + 220.0f, baseY + spacing * 4.0f, 50.0f, 40.0f);
 auto musicInc = std::make_shared<UIButton>("music_inc", musicIncBounds, "+");
 musicInc->setOnClick([this]() {
 musicVolume = std::min(1.0f, musicVolume + 0.05f);
 std::cout << "Music Volume: " << musicVolume << std::endl;
 });
 uiMgr.addElement(musicInc);
 elementIds.push_back("music_inc");

 Vec4 musicDecBounds(baseX + 280.0f, baseY + spacing * 4.0f, 50.0f, 40.0f);
 auto musicDec = std::make_shared<UIButton>("music_dec", musicDecBounds, "-");
 musicDec->setOnClick([this]() {
 musicVolume = std::max(0.0f, musicVolume - 0.05f);
 std::cout << "Music Volume: " << musicVolume << std::endl;
 });
 uiMgr.addElement(musicDec);
 elementIds.push_back("music_dec");

 Vec4 sfxLabelBounds(baseX, baseY + spacing * 5.0f, 180.0f, 40.0f);
 auto sfxLabel = std::make_shared<UIButton>("sfx_label", sfxLabelBounds, "SFX Vol");
 sfxLabel->setOnClick([]() {});
 uiMgr.addElement(sfxLabel);
 elementIds.push_back("sfx_label");

 Vec4 sfxIncBounds(baseX + 220.0f, baseY + spacing * 5.0f, 50.0f, 40.0f);
 auto sfxInc = std::make_shared<UIButton>("sfx_inc", sfxIncBounds, "+");
 sfxInc->setOnClick([this]() {
 sfxVolume = std::min(1.0f, sfxVolume + 0.05f);
 std::cout << "SFX Volume: " << sfxVolume << std::endl;
 });
 uiMgr.addElement(sfxInc);
 elementIds.push_back("sfx_inc");

 Vec4 sfxDecBounds(baseX + 280.0f, baseY + spacing * 5.0f, 50.0f, 40.0f);
 auto sfxDec = std::make_shared<UIButton>("sfx_dec", sfxDecBounds, "-");
 sfxDec->setOnClick([this]() {
 sfxVolume = std::max(0.0f, sfxVolume - 0.05f);
 std::cout << "SFX Volume: " << sfxVolume << std::endl;
 });
 uiMgr.addElement(sfxDec);
 elementIds.push_back("sfx_dec");

 // Additional settings start
 const float optBaseY = baseY + spacing * 6.0f;

 auto makeBoolLabel = [](const std::string& prefix, bool value) {
 return prefix + (value ? "On" : "Off");
 };

 // VSync toggle
 Vec4 vsyncBounds(baseX, optBaseY, 280.0f, 40.0f);
 auto vsyncBtn = std::make_shared<UIButton>("vsync_toggle", vsyncBounds, makeBoolLabel("VSync: ", vsyncEnabled));
 vsyncBtn->setOnClick([this, vsyncBtn, makeBoolLabel]() {
 vsyncEnabled = !vsyncEnabled;
 vsyncBtn->setLabel(makeBoolLabel("VSync: ", vsyncEnabled));
 std::cout << "VSync: " << (vsyncEnabled ? "On" : "Off") << std::endl;
 });
 uiMgr.addElement(vsyncBtn);
 elementIds.push_back("vsync_toggle");

 // Iso cursor visibility cycle
 static const std::vector<float> isoOptions {0.0f, 0.05f, 0.10f, 0.15f, 0.30f, 0.50f, 0.75f};
 int isoIndex = 0;
 {
 float best = 1.0f;
 for (size_t i = 0; i < isoOptions.size(); ++i) {
 float diff = std::fabs(isoCursorVisibility - isoOptions[i]);
 if (diff <= best) {
 best = diff;
 isoIndex = static_cast<int>(i);
 }
 }
 }
 auto formatIso = [&]() {
 int pct = static_cast<int>(isoOptions[isoIndex] * 100.0f + 0.5f);
 return std::string("Iso Cursor: ") + std::to_string(pct) + "%";
 };
 Vec4 isoBounds(baseX, optBaseY + spacing * 1.0f, 280.0f, 40.0f);
 auto isoBtn = std::make_shared<UIButton>("iso_cursor", isoBounds, formatIso());
 isoBtn->setOnClick([this, isoBtn, formatIso, &isoIndex]() mutable {
 isoIndex = (isoIndex + 1) % static_cast<int>(isoOptions.size());
 isoCursorVisibility = isoOptions[isoIndex];
 isoBtn->setLabel(formatIso());
 std::cout << "Iso Cursor visibility: " << isoCursorVisibility << std::endl;
 });
 uiMgr.addElement(isoBtn);
 elementIds.push_back("iso_cursor");

 // Show cursor while aiming
 Vec4 showAimBounds(baseX, optBaseY + spacing * 2.0f, 320.0f, 40.0f);
 auto showAimBtn = std::make_shared<UIButton>("show_cursor_aim", showAimBounds, makeBoolLabel("Show Cursor While Aiming: ", showCursorWhileAiming));
 showAimBtn->setOnClick([this, showAimBtn, makeBoolLabel]() {
 showCursorWhileAiming = !showCursorWhileAiming;
 showAimBtn->setLabel(makeBoolLabel("Show Cursor While Aiming: ", showCursorWhileAiming));
 std::cout << "Show cursor while aiming: " << (showCursorWhileAiming ? "On" : "Off") << std::endl;
 });
 uiMgr.addElement(showAimBtn);
 elementIds.push_back("show_cursor_aim");

 // Aim outline mode
 static const std::vector<std::string> outlineOptions {"None", "Ranged Weapons", "Any Weapon"};
 int outlineIndex = std::clamp(aimOutlineMode, 0, static_cast<int>(outlineOptions.size()) - 1);
 auto formatOutline = [&]() {
 return std::string("Aim Outline: ") + outlineOptions[outlineIndex];
 };
 Vec4 outlineBounds(baseX, optBaseY + spacing * 3.0f, 300.0f, 40.0f);
 auto outlineBtn = std::make_shared<UIButton>("aim_outline", outlineBounds, formatOutline());
 outlineBtn->setOnClick([this, outlineBtn, formatOutline, &outlineIndex]() mutable {
 outlineIndex = (outlineIndex + 1) % static_cast<int>(outlineOptions.size());
 aimOutlineMode = outlineIndex;
 outlineBtn->setLabel(formatOutline());
 std::cout << "Aim outline mode: " << aimOutlineMode << std::endl;
 });
 uiMgr.addElement(outlineBtn);
 elementIds.push_back("aim_outline");

 // Lock cursor to window
 Vec4 lockBounds(baseX, optBaseY + spacing * 4.0f, 280.0f, 40.0f);
 auto lockBtn = std::make_shared<UIButton>("lock_cursor", lockBounds, makeBoolLabel("Lock Cursor To Window: ", lockCursor));
 lockBtn->setOnClick([this, lockBtn, makeBoolLabel]() {
 lockCursor = !lockCursor;
 lockBtn->setLabel(makeBoolLabel("Lock Cursor To Window: ", lockCursor));
 std::cout << "Lock cursor: " << (lockCursor ? "On" : "Off") << std::endl;
 });
 uiMgr.addElement(lockBtn);
 elementIds.push_back("lock_cursor");

 // UI offscreen rendering
 Vec4 offscreenBounds(baseX, optBaseY + spacing * 5.0f, 340.0f, 40.0f);
 auto offscreenBtn = std::make_shared<UIButton>("ui_offscreen", offscreenBounds, makeBoolLabel("UI Offscreen Rendering: ", uiOffscreenRendering));
 offscreenBtn->setOnClick([this, offscreenBtn, makeBoolLabel]() {
 uiOffscreenRendering = !uiOffscreenRendering;
 offscreenBtn->setLabel(makeBoolLabel("UI Offscreen Rendering: ", uiOffscreenRendering));
 std::cout << "UI offscreen rendering: " << (uiOffscreenRendering ? "On" : "Off") << std::endl;
 });
 uiMgr.addElement(offscreenBtn);
 elementIds.push_back("ui_offscreen");

 // UI rendering FPS
 static const std::vector<int> fpsOptions {30, 25, 20, 15, 10};
 int fpsIndex = 0;
 {
 int bestDiff = 1000;
 for (size_t i = 0; i < fpsOptions.size(); ++i) {
 int diff = std::abs(uiRenderingFps - fpsOptions[i]);
 if (diff <= bestDiff) {
 bestDiff = diff;
 fpsIndex = static_cast<int>(i);
 }
 }
 }
 auto formatFps = [&]() {
 return std::string("UI Rendering FPS: ") + std::to_string(fpsOptions[fpsIndex]);
 };
 Vec4 fpsBounds(baseX, optBaseY + spacing * 6.0f, 320.0f, 40.0f);
 auto fpsBtn = std::make_shared<UIButton>("ui_fps", fpsBounds, formatFps());
 fpsBtn->setOnClick([this, fpsBtn, formatFps, &fpsIndex]() mutable {
 fpsIndex = (fpsIndex + 1) % static_cast<int>(fpsOptions.size());
 uiRenderingFps = fpsOptions[fpsIndex];
 fpsBtn->setLabel(formatFps());
 std::cout << "UI rendering FPS: " << uiRenderingFps << std::endl;
 });
 uiMgr.addElement(fpsBtn);
 elementIds.push_back("ui_fps");

 // Inventory button size
 static const std::vector<std::string> invSizes {"Small", "Medium", "Large"};
 int invIndex = std::clamp(inventoryButtonSize, 0, static_cast<int>(invSizes.size()) - 1);
 auto formatInv = [&]() {
 return std::string("Inventory Button Size: ") + invSizes[invIndex];
 };
 Vec4 invBounds(baseX, optBaseY + spacing * 7.0f, 340.0f, 40.0f);
 auto invBtn = std::make_shared<UIButton>("inv_size", invBounds, formatInv());
 invBtn->setOnClick([this, invBtn, formatInv, &invIndex]() mutable {
 invIndex = (invIndex + 1) % static_cast<int>(invSizes.size());
 inventoryButtonSize = invIndex;
 invBtn->setLabel(formatInv());
 std::cout << "Inventory button size: " << inventoryButtonSize << std::endl;
 });
 uiMgr.addElement(invBtn);
 elementIds.push_back("inv_size");

 // Show mod info tooltip
 Vec4 modInfoBounds(baseX, optBaseY + spacing * 8.0f, 360.0f, 40.0f);
 auto modInfoBtn = std::make_shared<UIButton>("mod_info", modInfoBounds, makeBoolLabel("Show Mod Info Tooltips: ", showModInfoTooltip));
 modInfoBtn->setOnClick([this, modInfoBtn, makeBoolLabel]() {
 showModInfoTooltip = !showModInfoTooltip;
 modInfoBtn->setLabel(makeBoolLabel("Show Mod Info Tooltips: ", showModInfoTooltip));
 std::cout << "Show mod info tooltip: " << (showModInfoTooltip ? "On" : "Off") << std::endl;
 });
 uiMgr.addElement(modInfoBtn);
 elementIds.push_back("mod_info");

 // Show survival guide
 Vec4 guideBounds(baseX, optBaseY + spacing * 9.0f, 340.0f, 40.0f);
 auto guideBtn = std::make_shared<UIButton>("survival_guide", guideBounds, makeBoolLabel("Show Survival Guide: ", showSurvivalGuide));
 guideBtn->setOnClick([this, guideBtn, makeBoolLabel]() {
 showSurvivalGuide = !showSurvivalGuide;
 guideBtn->setLabel(makeBoolLabel("Show Survival Guide: ", showSurvivalGuide));
 std::cout << "Show survival guide: " << (showSurvivalGuide ? "On" : "Off") << std::endl;
 });
 uiMgr.addElement(guideBtn);
 elementIds.push_back("survival_guide");

 // Autosave toggle
 Vec4 autosaveBounds(baseX, optBaseY + spacing * 10.0f, 280.0f, 40.0f);
 auto autosaveBtn = std::make_shared<UIButton>("autosave_toggle", autosaveBounds, makeBoolLabel("Autosave: ", autosaveEnabled));
 autosaveBtn->setOnClick([this, autosaveBtn, makeBoolLabel]() {
 autosaveEnabled = !autosaveEnabled;
 autosaveBtn->setLabel(makeBoolLabel("Autosave: ", autosaveEnabled));
 std::cout << "Autosave: " << (autosaveEnabled ? "On" : "Off") << std::endl;
 });
 uiMgr.addElement(autosaveBtn);
 elementIds.push_back("autosave_toggle");

 // Save Now button
 Vec4 saveNowBounds(baseX, optBaseY + spacing * 11.0f, 200.0f, 40.0f);
 auto saveNowBtn = std::make_shared<UIButton>("save_now", saveNowBounds, "Save Now");
 saveNowBtn->setOnClick([]() {
 saveload::GameSaveData g{};
 g.gameVersion = 1;
 g.timestamp = static_cast<uint64_t>(std::time(nullptr));
 g.playerName = "Player";
 g.playedMinutes = 0;
 saveload::WorldSaveData w{};
 auto& mgr = saveload::SaveGameManager::getInstance();
 bool ok = mgr.saveGameSVI("manual", g, w);
 std::cout << (ok ? "Manual save completed" : "Manual save failed")
 << " at " << mgr.getSavePath() << std::endl;
 });
 uiMgr.addElement(saveNowBtn);
 elementIds.push_back("save_now");

 // Rebind buttons for common actions (pushed below extra options)
 const std::vector<std::string> actions = {"interact", "sprint", "fire", "inventory"};
 float rebindY = optBaseY + spacing * 10.5f;

 for (size_t i = 0; i < actions.size(); ++i) {
 Vec4 rebindBounds(baseX, rebindY + (i * 50.0f), 350.0f, 40.0f);
 auto rebindBtn = std::make_shared<UIButton>(
 "rebind_" + actions[i],
 rebindBounds,
 "Rebind " + actions[i]
 );
 const auto& actionName = actions[i];
 rebindBtn->setOnClick([this, actionName]() {
 if (rebindUI) {
 rebindUI->startRebind(actionName);
 }
 });
 uiMgr.addElement(rebindBtn);
 elementIds.push_back("rebind_" + actions[i]);
 }

 // Apply / Back buttons
 Vec4 applyBounds(baseX, rebindY + spacing * 5.0f, 150.0f, 40.0f);
 auto applyBtn = std::make_shared<UIButton>("apply_settings", applyBounds, "Apply");
 applyBtn->setOnClick([this]() {
 applySettings();
 });
 uiMgr.addElement(applyBtn);
 elementIds.push_back("apply_settings");

 Vec4 backBounds(baseX + 200.0f, rebindY + spacing * 5.0f, 150.0f, 40.0f);
 auto backBtn = std::make_shared<UIButton>("back_to_menu", backBounds, "Back");
 backBtn->setOnClick([this]() {
 if (backCallback) {
 backCallback();
 }
 backRequested = true;
 });
 uiMgr.addElement(backBtn);
 elementIds.push_back("back_to_menu");

 // Create and register rebind UI component
 rebindUI = std::make_shared<ControllerRebindUI>("rebind_prompt");
 rebindUI->setRebindCallback([this](const std::string& action, const std::string& btn) {
 onRebindComplete(action, btn);
 });
 uiMgr.addElement(rebindUI);
 elementIds.push_back("rebind_prompt");
}

void OptionsScreen::clearUI() {
 auto& uiMgr = UIManager::getInstance();
 for (const auto& id : elementIds) {
 uiMgr.removeElement(id);
 }
 elementIds.clear();
 rebindUI.reset();
}

void OptionsScreen::applySettings() {
 auto* inputMgr = input::InputManager::getInstance();
 inputMgr->setLookSensitivity(sensitivity);
 inputMgr->setControllerDeadzone(deadzone);
 // Update global config
 zombie::config::gOptionsConfig.brightness = brightness;
 zombie::config::gOptionsConfig.masterVolume = masterVolume;
 zombie::config::gOptionsConfig.musicVolume = musicVolume;
 zombie::config::gOptionsConfig.sfxVolume = sfxVolume;
 zombie::config::gOptionsConfig.vsync = vsyncEnabled;
 zombie::config::gOptionsConfig.isoCursorVisibility = isoCursorVisibility;
 zombie::config::gOptionsConfig.showCursorWhileAiming = showCursorWhileAiming;
 zombie::config::gOptionsConfig.aimOutlineMode = aimOutlineMode;
 zombie::config::gOptionsConfig.lockCursorToWindow = lockCursor;
 zombie::config::gOptionsConfig.uiOffscreenRendering = uiOffscreenRendering;
 zombie::config::gOptionsConfig.uiRenderingFps = uiRenderingFps;
 zombie::config::gOptionsConfig.inventoryButtonSize = inventoryButtonSize;
 zombie::config::gOptionsConfig.showModInfoTooltip = showModInfoTooltip;
 zombie::config::gOptionsConfig.showSurvivalGuide = showSurvivalGuide;
 zombie::config::gOptionsConfig.autosaveEnabled = autosaveEnabled;

 // Persist options and keys
 zombie::config::saveOptionsConfig("config/Options.ini", zombie::config::gOptionsConfig);
 zombie::config::saveKeysConfig("config/keys.ini", zombie::config::gKeysConfig);

 // Apply audio immediately
 auto* snd = audio::SoundManager::getInstance();
 snd->setMasterVolume(masterVolume);
 snd->setMusicVolume(musicVolume);
 snd->setSoundVolume(sfxVolume);

 // Apply vsync immediately when possible
 if (auto* core = core::Core::getInstance()) {
 core->setVSyncEnabled(vsyncEnabled);
 }

 std::cout << "Settings applied: sensitivity=" << sensitivity
 << ", deadzone=" << deadzone
 << ", brightness=" << brightness
 << ", masterVol=" << masterVolume
 << ", musicVol=" << musicVolume
 << ", sfxVol=" << sfxVolume
 << ", vsync=" << (vsyncEnabled ? "on" : "off")
 << ", isoCursor=" << isoCursorVisibility
 << ", cursorWhileAiming=" << (showCursorWhileAiming ? "on" : "off")
 << ", aimOutline=" << aimOutlineMode
 << ", lockCursor=" << (lockCursor ? "on" : "off")
 << ", uiOffscreen=" << (uiOffscreenRendering ? "on" : "off")
 << ", uiFps=" << uiRenderingFps
 << ", invBtnSize=" << inventoryButtonSize
 << ", modInfo=" << (showModInfoTooltip ? "on" : "off")
 << ", survivalGuide=" << (showSurvivalGuide ? "on" : "off")
 << std::endl;
}

void OptionsScreen::onRebindComplete(const std::string& action, const std::string& buttonName) {
 auto* inputMgr = input::InputManager::getInstance();
 inputMgr->rebindAction(action, buttonName);
 // Track in keys config for persistence
 zombie::config::gKeysConfig.bindings[action] = buttonName;
 std::cout << "Rebound action '" << action << "' to button '" << buttonName << "'" << std::endl;
}

gameStates::GameState* OptionsScreen::redirectState() {
 auto* target = pendingRedirect;
 pendingRedirect = nullptr;
 return target;
}

} // namespace ui
} // namespace zombie

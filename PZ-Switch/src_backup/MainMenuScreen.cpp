#include "MainMenuScreen.h"
#include "Core.h"
#include <iostream>

namespace zombie {
namespace ui {

MainMenuScreen::MainMenuScreen(StartCallback onStart, ContinueCallback onContinue, OptionsCallback onOptions, QuitCallback onQuit)
    : startCallback(std::move(onStart))
    , continueCallback(std::move(onContinue))
    , optionsCallback(std::move(onOptions))
    , quitCallback(std::move(onQuit))
    , startRequested(false)
    , continueRequested(false)
    , optionsRequested(false)
    , quitRequested(false) {
}

void MainMenuScreen::enter() {
    startRequested = false;
    continueRequested = false;
    optionsRequested = false;
    quitRequested = false;
    buildUI();
    std::cout << "Entering Main Menu Screen" << std::endl;
}

void MainMenuScreen::exit() {
    clearUI();
    std::cout << "Exiting Main Menu Screen" << std::endl;
}

gameStates::StateAction MainMenuScreen::update() {
    if (optionsRequested && optionsState) {
        pendingRedirect = optionsState;
        optionsRequested = false;
        if (optionsCallback) {
            optionsCallback();
        }
        return gameStates::StateAction::Continue;
    }

    if (optionsRequested) {
        if (optionsCallback) {
            optionsCallback();
        }
        // Note: State transition to options happens via redirectState or state machine logic
        optionsRequested = false;
    }
    if (quitRequested) {
        if (quitCallback) {
            quitCallback();
        }
    }
    if (continueRequested) {
        bool ok = true;
        if (continueCallback) {
            ok = continueCallback();
        }
        continueRequested = false;
        if (ok && ingameState) {
            pendingRedirect = ingameState;
            return gameStates::StateAction::Continue;
        }
    }
    if (startRequested) {
        if (startCallback) {
            startCallback();
        }
        if (ingameState) {
            pendingRedirect = ingameState;
            startRequested = false;
            return gameStates::StateAction::Continue;
        }
        return gameStates::StateAction::Remain;
    }
    return gameStates::StateAction::Remain;
}

gameStates::GameState* MainMenuScreen::redirectState() {
    auto* target = pendingRedirect;
    pendingRedirect = nullptr;
    return target;
}

void MainMenuScreen::render() {
    // UI rendering handled by UIManager; nothing additional here.
}

void MainMenuScreen::buildUI() {
    auto& uiMgr = UIManager::getInstance();

    // Create three basic buttons stacked vertically
    const float baseX = 200.0f;
    const float baseY = 200.0f;
    const float spacing = 50.0f;

    struct ButtonSpec {
        std::string id;
        std::string label;
        std::function<void()> cb;
    };

    std::vector<ButtonSpec> buttons = {
        {"btn_continue", "Continue", [this]() { continueRequested = true; }},
        {"btn_start", "Start", [this]() { startRequested = true; }},
        {"btn_sandbox", "Sandbox", [this]() { startRequested = true; }},
        {"btn_options", "Options", [this]() { optionsRequested = true; }},
        {"btn_quit", "Quit", [this]() { quitRequested = true; }}
    };

    for (size_t i = 0; i < buttons.size(); ++i) {
        Vec4 bounds(baseX, baseY + spacing * static_cast<float>(i), 160.0f, 32.0f);
        auto btn = std::make_shared<UIButton>(buttons[i].id, bounds, buttons[i].label);
        btn->setOnClick(buttons[i].cb);
        uiMgr.addElement(btn);
        elementIds.push_back(buttons[i].id);
    }
}

void MainMenuScreen::clearUI() {
    auto& uiMgr = UIManager::getInstance();
    for (const auto& id : elementIds) {
        uiMgr.removeElement(id);
    }
    elementIds.clear();
}

} // namespace ui
} // namespace zombie

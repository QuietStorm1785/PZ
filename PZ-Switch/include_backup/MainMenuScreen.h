#pragma once
#include "GameState.h"
#include "UI.h"
#include <memory>
#include <vector>
#include <functional>
#include "GameState.h"

namespace zombie {
namespace ui {

class MainMenuScreen : public gameStates::GameState {
public:
    using StartCallback = std::function<void()>;
    using ContinueCallback = std::function<bool()>;
    using OptionsCallback = std::function<void()>;
    using QuitCallback = std::function<void()>;

    MainMenuScreen(StartCallback onStart, ContinueCallback onContinue, OptionsCallback onOptions, QuitCallback onQuit);
    ~MainMenuScreen() override = default;

    void enter() override;
    void exit() override;
    gameStates::StateAction update() override;
    void render() override;
    gameStates::GameState* redirectState() override;

    void setOptionsState(gameStates::GameState* state) { optionsState = state; }
    void setIngameState(gameStates::GameState* state) { ingameState = state; }

private:
    void buildUI();
    void clearUI();

    StartCallback startCallback;
    ContinueCallback continueCallback;
    OptionsCallback optionsCallback;
    QuitCallback quitCallback;
    bool startRequested;
    bool continueRequested;
    bool optionsRequested;
    bool quitRequested;
    gameStates::GameState* optionsState {nullptr};
    gameStates::GameState* ingameState {nullptr};
    gameStates::GameState* pendingRedirect {nullptr};

    std::vector<std::string> elementIds;
};

} // namespace ui
} // namespace zombie

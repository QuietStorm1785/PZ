
// SDL2-based controller state for up to 16 controllers
#pragma once
#include <vector>
#include <cstdint>
#include <SDL2/SDL.h>

class ControllerState {
public:
    static constexpr int MAX_CONTROLLERS = 16;
    ControllerState();
    ~ControllerState();
    void poll();
    bool wasPolled() const;
    void reset();
    bool isCreated() const;
    SDL_GameController* getController(int idx) const;
    bool isButtonDown(int idx, SDL_GameControllerButton button) const;
    Sint16 getAxis(int idx, SDL_GameControllerAxis axis) const;
    int getNumControllers() const;

private:
    SDL_GameController* controllers_[MAX_CONTROLLERS] = {nullptr};
    bool isCreated_ = false;
    bool wasPolled_ = false;
    int numControllers_ = 0;
};
};

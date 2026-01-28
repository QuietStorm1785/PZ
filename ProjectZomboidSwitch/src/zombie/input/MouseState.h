
#pragma once
#include <vector>
#include <cstdint>
#include <SDL2/SDL.h>

class MouseState {
public:
    MouseState();
    void update();
    int getX() const;
    int getY() const;
    bool isButtonDown(int button) const;
    int getDWheel() const;
    void resetDWheel();
    int getButtonCount() const;
    bool isCreated() const;
    void setCursorPosition(int x, int y);

private:
    int x_ = 0;
    int y_ = 0;
    int dWheel_ = 0;
    std::vector<bool> buttonDownStates_;
    bool created_ = false;
};

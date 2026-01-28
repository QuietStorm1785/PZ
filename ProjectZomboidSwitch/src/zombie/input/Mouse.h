
#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <SDL2/SDL.h>

namespace zombie {
namespace input {


class Mouse {
public:
    Mouse();
    void update();
    void poll();
    void setXY(int x, int y);
    int getX() const;
    int getY() const;
    int getWheelState() const;
    bool isButtonDown(int button) const;
    bool isLeftDown() const;
    bool isLeftPressed() const;
    bool isLeftReleased() const;
    bool isLeftUp() const;
    bool isMiddleDown() const;
    bool isMiddlePressed() const;
    bool isMiddleReleased() const;
    bool isMiddleUp() const;
    bool isRightDown() const;
    bool isRightPressed() const;
    bool isRightReleased() const;
    bool isRightUp() const;
    void setCursorVisible(bool visible);
    bool isCursorVisible() const;
    void renderCursorTexture();

private:
    int x_ = 0;
    int y_ = 0;
    int wheelDelta_ = 0;
    std::vector<bool> buttonDownStates_;
    bool leftDown_ = false, leftWasDown_ = false;
    bool rightDown_ = false, rightWasDown_ = false;
    bool middleDown_ = false, middleWasDown_ = false;
    bool cursorVisible_ = true;
};
} // namespace input
} // namespace zombie

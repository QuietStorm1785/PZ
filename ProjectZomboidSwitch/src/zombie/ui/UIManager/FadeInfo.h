#pragma once
#include <cstdint>

namespace zombie {
namespace ui {

class FadeInfo {
public:
    int playerIndex = 0;
    bool fadeBeforeUI = false;
    int fadeTime = 0;
    bool fadingOut = false;
    float fadeAlpha = 1.0f;

    FadeInfo(int idx) : playerIndex(idx) {}

    void setFadeBeforeUI(bool val) { fadeBeforeUI = val; }
    void setFadeTime(int t) { fadeTime = t; }
    void setFadingOut(bool val) { fadingOut = val; }
    float getFadeAlpha() const { return fadeAlpha; }
    void update() {/* TODO: implement fade logic */}
    void render() {/* TODO: implement fade rendering */}
    void FadeIn(int t) { fadeTime = t; fadingOut = false; }
    void FadeOut(int t) { fadeTime = t; fadingOut = true; }
};

} // namespace ui
} // namespace zombie

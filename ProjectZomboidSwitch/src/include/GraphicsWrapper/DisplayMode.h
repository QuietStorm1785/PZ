#pragma once
// Stub for org/lwjglx/opengl/DisplayMode.h
// TODO: Implement display mode abstraction if needed

namespace GraphicsWrapper {
    class DisplayMode {
    public:
        int width;
        int height;
        int refreshRate;
        DisplayMode(int w = 800, int h = 600, int rr = 60) : width(w), height(h), refreshRate(rr) {}
    };
}

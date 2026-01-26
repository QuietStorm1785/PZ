#pragma once
#include <memory>
#include <vector>
#include "IndieGL.h"
#include "IsoPlayer.h"
#include "IsoCell.h"
#include "IsoGridSquare.h"
#include "Color.h"

// LightningState: Enum for lightning FX state
enum class LightningState {
    Idle,
    ApplyLightning
};

// AnimTimer: Simple timer stub (expand as needed)
class AnimTimer {
public:
    AnimTimer() : time(0.0f) {}
    void reset() { time = 0.0f; }
    void update(float dt) { time += dt; }
    float getTime() const { return time; }
private:
    float time;
};

// Forward declaration for ThunderStorm (if needed)
class ThunderStorm;

// PlayerLightningInfo: Holds per-player lightning FX state
struct PlayerLightningInfo {
    LightningState lightningState;
    AnimTimer timer;
    float lightningStrength;
    float lightningMod;
    ClimateColorInfo lightningColor;
    ClimateColorInfo outColor;
    int x;
    int y;
    int distance;

    PlayerLightningInfo()
        : lightningState(LightningState::Idle),
          lightningStrength(1.0f),
          lightningMod(0.0f),
          x(0), y(0), distance(0) {
        // Default color: white
        lightningColor = ClimateColorInfo(1.0f, 1.0f, 1.0f, 1.0f);
        outColor = ClimateColorInfo(1.0f, 1.0f, 1.0f, 1.0f);
    }
};

// IsoLightningFX: Handles lightning visual and audio effects
class IsoLightningFX {
public:
    IsoLightningFX();
    ~IsoLightningFX();

    void init();
    void update(float deltaTime);
    void render();
    void triggerLightning(float intensity = 1.0f);
    bool isActive() const;
    float getCurrentIntensity() const;

private:
    void startFlash(float intensity);
    void endFlash();
    void playThunder();

    bool active;
    float flashTimer;
    float flashDuration;
    float intensity;
    float thunderDelay;
    float thunderTimer;
    Color flashColor;
};

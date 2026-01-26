#include "IsoLightningFX.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

IsoLightningFX::IsoLightningFX()
    : active(false), flashTimer(0.0f), flashDuration(0.0f), intensity(0.0f), thunderDelay(0.0f), thunderTimer(0.0f), flashColor(1.0f, 1.0f, 1.0f, 1.0f) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

IsoLightningFX::~IsoLightningFX() {}

void IsoLightningFX::init() {
    active = false;
    flashTimer = 0.0f;
    flashDuration = 0.0f;
    intensity = 0.0f;
    thunderDelay = 0.0f;
    thunderTimer = 0.0f;
    flashColor = Color(1.0f, 1.0f, 1.0f, 1.0f);
}

void IsoLightningFX::update(float deltaTime) {
    if (!active) return;
    flashTimer += deltaTime;
    if (flashTimer >= flashDuration) {
        endFlash();
    }
    if (thunderDelay > 0.0f) {
        thunderTimer += deltaTime;
        if (thunderTimer >= thunderDelay) {
            playThunder();
            thunderDelay = 0.0f;
        }
    }
}

void IsoLightningFX::render() {
    if (!active) return;
    // Render a full-screen white flash with alpha based on intensity
    IndieGL::setBlendMode(IndieGL::BlendMode::Additive);
    IndieGL::setColor(flashColor.r, flashColor.g, flashColor.b, intensity);
    IndieGL::drawFullscreenQuad();
    IndieGL::setBlendMode(IndieGL::BlendMode::Normal);
}

void IsoLightningFX::triggerLightning(float newIntensity) {
    startFlash(newIntensity);
    thunderDelay = 0.5f + static_cast<float>(std::rand()) / RAND_MAX * 1.5f; // 0.5-2.0s delay
    thunderTimer = 0.0f;
}

bool IsoLightningFX::isActive() const {
    return active;
}

float IsoLightningFX::getCurrentIntensity() const {
    return intensity;
}

void IsoLightningFX::startFlash(float newIntensity) {
    active = true;
    intensity = std::clamp(newIntensity, 0.0f, 1.0f);
    flashDuration = 0.15f + 0.1f * intensity; // 0.15-0.25s
    flashTimer = 0.0f;
    flashColor = Color(1.0f, 1.0f, 1.0f, 1.0f);
}

void IsoLightningFX::endFlash() {
    active = false;
    intensity = 0.0f;
    flashTimer = 0.0f;
    flashDuration = 0.0f;
}

void IsoLightningFX::playThunder() {
    // Legacy logic: play a random thunder sound effect, with pitch/volume variation for realism
    // This is a stub for integration with the actual audio system
    // In the original Java, thunder sounds were randomly selected from a set
    // and played with slight pitch/volume variation for realism.
    // Here, we simulate that logic:

    constexpr int thunderSoundCount = 3; // e.g., "thunder1", "thunder2", "thunder3"
    int thunderVariant = std::rand() % thunderSoundCount;
    std::string soundName = "thunder" + std::to_string(thunderVariant + 1); // "thunder1", ...

    // Randomize pitch and volume slightly for realism
    float baseVolume = 1.0f;
    float basePitch = 1.0f;
    float volume = baseVolume * (0.85f + static_cast<float>(std::rand()) / RAND_MAX * 0.3f); // 0.85-1.15
    float pitch = basePitch * (0.95f + static_cast<float>(std::rand()) / RAND_MAX * 0.1f);   // 0.95-1.05

    // Integrate with your audio system here:
    // AudioManager::getInstance().playSound(soundName, volume, pitch);

    // For now, print to console as a stub
    printf("[IsoLightningFX] Playing thunder sound: %s (volume=%.2f, pitch=%.2f)\n", soundName.c_str(), volume, pitch);

    // TODO: Integrate with actual audio system when available
}

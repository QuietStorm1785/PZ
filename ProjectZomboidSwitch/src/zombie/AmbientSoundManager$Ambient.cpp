#include "zombie/AmbientSoundManager$Ambient.h"

namespace zombie {

bool AmbientSoundManager$Ambient::finished() {
    // Return true if the ambient sound's duration has expired or it is marked as finished
    // Assumes 'duration' is a member variable counting down, and/or a 'finishedFlag' exists
    if (duration <= 0) return true;
    if (finishedFlag) return true;
    return false;
}

void AmbientSoundManager$Ambient::update() {
    // Decrement duration if greater than zero
    if (duration > 0) {
        --duration;
        if (duration == 0) {
            finishedFlag = true;
        }
    }
    // Fade out volume as duration nears zero (simple linear fade)
    if (duration > 0 && maxDuration > 0) {
        float fadeRatio = static_cast<float>(duration) / static_cast<float>(maxDuration);
        if (fadeRatio < 0.2f) { // Start fading out in last 20% of duration
            volume = baseVolume * fadeRatio / 0.2f;
        } else {
            volume = baseVolume;
        }
    }

    // Update position if velocity is set (simple movement)
    x += vx;
    y += vy;
}

} // namespace zombie

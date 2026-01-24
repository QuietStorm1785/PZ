#include "zombie/ai/WalkingOnTheSpot.h"

namespace zombie {
namespace ai {

bool WalkingOnTheSpot::check(float var1, float var2) {
    if (IsoUtils::DistanceToSquared(x, y, var1, var2) < 0.010000001f) {
        time += GameTime::getInstance().getMultiplier();
    } else {
        x = var1;
        y = var2;
        time = 0.0f;
    }
    return time > 400.0f;
}

void WalkingOnTheSpot::reset(float var1, float var2) {
    x = var1;
    y = var2;
    time = 0.0f;
}

} // namespace ai
} // namespace zombie

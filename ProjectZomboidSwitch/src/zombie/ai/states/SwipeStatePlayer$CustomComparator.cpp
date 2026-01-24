#include "zombie/ai/states/SwipeStatePlayer$CustomComparator.h"

namespace zombie {
namespace ai {
namespace states {

int SwipeStatePlayer$CustomComparator::compare(HitInfo var1, HitInfo var2) {
    // Example: compare by distance, then by prone status
    if (!var1.target || !var2.target) return 0;
    float dist1 = var1.attacker->getDistance(var1.target);
    float dist2 = var2.attacker->getDistance(var2.target);
    if (dist1 < dist2) return -1;
    if (dist1 > dist2) return 1;
    // Prefer standing over prone
    bool prone1 = var1.target->isProne();
    bool prone2 = var2.target->isProne();
    if (prone1 && !prone2) return 1;
    if (!prone1 && prone2) return -1;
    return 0;
}

} // namespace states
} // namespace ai
} // namespace zombie
